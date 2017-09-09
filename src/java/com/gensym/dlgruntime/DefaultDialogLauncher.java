/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	Native Dialog Launcher - Ndm.java
 *
 *     
 *   Modifications:
 *
 */


package com.gensym.dlgruntime;

import java.awt.*;
import java.util.*;
import java.awt.event.*;
import com.gensym.core.UiApplication;
import com.gensym.message.*;
import com.gensym.classes.Item;
import com.gensym.controls.ItemProxy;
import com.gensym.controls.DialogCommand;

/**
 *  This Class is used to launch serialized dialogs
 */

public class DefaultDialogLauncher implements DialogLauncher, DialogCommandListener {

  /**
   * This is public because the DialogTestingResource in com.gensym.beaneditor
   * needs to use the cmdBean that it has as the key for the dialog being
   * launched. That object is not recognized as a DialogCommand by the
   * DefaultDialogLauncher because the former is loaded by the G2ClassLoader
   * and this class is loaded by the system ClassLoader.
   *
   * @undocumented
   */
  protected Hashtable dialogs = new Hashtable();

  /*
   * Standard Tracing Requirements
   */
  private static MessageKey traceKey =
  Trace.registerMessageKey("com.gensym.dlgruntime.launch",
			   DefaultDialogLauncher.class);
  private static Resource i18nTrace =
  Trace.getBundle("com.gensym.dlgruntime.TraceMessages", Locale.getDefault());

  private static final int DEF_TRACE_LEVEL = 5;
  private static final int DEF_WARN_LEVEL  = 2;

  private static ItemProxy[] emptyProxies = new ItemProxy[0];
  private static Item[] emptyItems = new Item[0];

  /**
   * Launch the dialog from the resource filling the named ItemProxies
   * with the stubs passed in.
   * <p> NOTE: if <code>component</code> is not a java.awt.Window, it will
   * be placed in a <code>java.awt.Frame</code>, and <code>pack()</code>
   * is called on that frame, so the <code>getPreferredSize()</code>
   * method of the <code>component</code> will help determine the
   * initial size of the resulting dialog.
   */
  @Override
  public void launch (final Component component, final ItemProxy[] proxies,
		  final String[] proxyNames, final Item[] stubs, final DialogCommand cmdBean) {
	ItemProxy[] proxyArray = proxies;
	Item[] stubArray = stubs;
	DialogCommand dlgCmdBean = cmdBean;
	if (proxyNames != null && proxyNames.length != stubArray.length){
      throw new IllegalArgumentException ("ProxyNames and Stubs must be of equal length");
    }
    // Some conveniences for allowing users to pass in null args.
    if (proxyArray == null){
    	proxyArray = emptyProxies;
    }
    if (stubArray == null){
    	stubArray = emptyItems;
    }
    ItemProxy proxy = null;

    // This is for the case when there is only one
    // item specified, and there is only one proxy
    // in the dialog and no name was specified
    if (proxyArray.length == 1 && stubArray.length == 1 && proxyNames == null) {
      proxy = proxyArray[0];
      try {			// throw these!
	proxy.setProxy(stubArray[0]);
	proxy.download();
      } catch (Exception e) {
	Trace.exception (e);
      }
    }
    // Otherwise try to match up the items and
    // the proxies
    else if (proxyNames != null)
      {
	for (int i=0; i < proxyArray.length; i++) {
	  proxy = proxyArray[i];
	  
	  for (int j=0; j < proxyNames.length; j++) {
	    if (proxy.getName().equals(proxyNames[j])) {
	      if (stubArray[j] != null) {
		try {	// throw these
		  proxy.setProxy(stubArray[j]);
		  proxy.download();
		} catch (Exception e) {
		  Trace.exception (e);
		}
	      }
	    }
	  }
	}
      }
    if (dlgCmdBean == null) {
      //System.out.println ("Making Dummy CmdBean!");
      dlgCmdBean = new DialogCommand ();
    }
    dlgCmdBean.addDialogCommandListener(this);
    dlgCmdBean.setProxies (proxyArray);

    Window frame;
    if (component instanceof Window) {
      frame = (Window)component;
      frame.addWindowListener (new DialogWindowAdapter (dlgCmdBean));      
    } else {
      Frame parent = UiApplication.getCurrentFrame();
      synchronized (DefaultDialogLauncher.class) {
        if (parent != null)
          theFrame = parent;
        frame = new DefaultDialog(theFrame, dlgCmdBean);
      }
      //Workaround for bug in TextField: without the panel, focusLost in a TextField is
      //always temporary.
      Panel p = new Panel();
      frame.add(p);
      p.add(component);
      //frame.add(component);
      frame.pack();
      // hack: this color should be set during development, not at launch
      // time. At the very least, it shouldn't be hardcoded
      //frame.setBackground (Color.lightGray);
      frame.validate();
    }
    //System.out.println (">>>> Putting " + cmdBean + " as source for " + frame);
    dialogs.put(dlgCmdBean, frame);
    
    dlgCmdBean.open ();
      
    centerDialog (frame);
    frame.setVisible (true);
    Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "displayDlg");
  }

  private static java.awt.Dimension screenDisplaySize = java.awt.Toolkit.getDefaultToolkit().getScreenSize ();
  private static final int dialogMargin = 25;

  static void centerDialog (java.awt.Window dlg) {
    Component parent = dlg.getParent();
    Window owner = parent instanceof Window ? (Window)parent : theFrame;

    Rectangle frameBnds = owner.getBounds ();
    Rectangle dlgBounds = dlg.getBounds ();
    int dlgWidth        = dlgBounds.width;
    int dlgHeight       = dlgBounds.height;
    int dlgX = frameBnds.x + (frameBnds.width - dlgWidth)/2;
    int dlgY = frameBnds.y + (frameBnds.height - dlgHeight)/2;
    if (dlgX + dlgWidth > screenDisplaySize.width)
      dlgX = screenDisplaySize.width - dialogMargin - dlgWidth;
    if (dlgY + dlgHeight > screenDisplaySize.height)
      dlgY = screenDisplaySize.height - dialogMargin -dlgHeight;
    if (dlgX < 0)
      dlgX = dialogMargin;
    if (dlgY < 0)
      dlgY = dialogMargin;
    dlg.setBounds (dlgX, dlgY, dlgBounds.width, dlgBounds.height);
  }

  private static class DialogWindowAdapter extends WindowAdapter {
    DialogCommand cmdBean;
    DialogWindowAdapter(DialogCommand cmdBean) {
      this.cmdBean = cmdBean;
    }
    
    @Override
    public void windowClosing(WindowEvent e) {
      //System.out.println ("Dialog WindowAdapter informing cmdBean of closing!");
      cmdBean.close ();
    }
  }

  private static volatile Frame theFrame;
  static {
    theFrame = new Frame();
    theFrame.addNotify ();
  }

  /**
   * @undocumented
   */

  public static void registerFrame (Frame f) {
    theFrame = f;
  }
  
  /**
   * A convenience method for launching a dialog that has one and only
   * one (possibly unnamed) ItemProxy.
   */
  @Override
  public void launch (Component component, ItemProxy proxy, Item stub, DialogCommand cmdBean)
  {
    Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "launchDlgSimple", component, stub);
    launch (component, new ItemProxy[] {proxy}, null, new Item[] {stub}, cmdBean);
  }

  //DialogCommandListener
  @Override
  public void dialogShutdown (DialogCommandEvent event) {
    Object source = event.getSource ();
    Object result = dialogs.remove (source);
    ((Dialog)result).dispose();
  }

  @Override
  public void dialogChangesFlushed (DialogCommandEvent event) {
    // Not interested
  }

  @Override
  public void dialogLaunched (DialogCommandEvent event) {
    // ??
  }


  
}
