
package com.gensym.ntw.util;

import java.awt.Component;
import java.awt.Container;
import java.awt.Window;
import java.awt.Frame;
import java.awt.Dialog;
import java.awt.Point;
import java.awt.Dimension;
import java.awt.Rectangle;
import java.awt.Image;
import java.awt.Toolkit;
import java.awt.Graphics;
import java.awt.BorderLayout;
import java.awt.event.WindowListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.util.Hashtable;
import java.util.Enumeration;

import javax.swing.JApplet;
import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JWindow;

import com.gensym.message.Trace;
import com.gensym.core.UiApplication;
import com.gensym.util.Symbol;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.ItemEvent;
import com.gensym.util.ItemListener;
import com.gensym.jgi.G2Access;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.G2CommunicationException;
import com.gensym.classes.ImplAccess;
import com.gensym.classes.Item;
import com.gensym.classes.KbWorkspace;
import com.gensym.ntw.TwAccess;
import com.gensym.ntw.TwConnection;
import com.gensym.ntw.TwConnectionAdapter;
import com.gensym.ntw.TwConnectionEvent;
import com.gensym.ntw.WorkspaceShowingListener;
import com.gensym.ntw.WorkspaceShowingEvent;
import com.gensym.ntw.util.WorkspaceDisplayStyle;
import com.gensym.draw.LWScrollbar;
import com.gensym.draw.ViewScrollbar;
import com.gensym.wksp.WorkspaceView;
import com.gensym.wksp.configurations.ConfigurationSupport;
import com.gensym.wksp.configurations.ConfigurationSymbols;

public class DefaultWorkspaceShowingAdapter implements WorkspaceShowingListener, ConfigurationSymbols {

  private ConnectionLoginAdapter connectionLoginAdapter;
  private TwAccess connection;
  private Hashtable displayTable = new Hashtable (5);
  private Hashtable containers = new Hashtable (5);
  private Hashtable containerStack = new Hashtable (5);

  private static final Symbol UIL_DIALOG_SUBWORKSPACE_ =
                 Symbol.intern ("UIL-DIALOG-SUBWORKSPACE");

  public DefaultWorkspaceShowingAdapter (){
    this (null);
  }

  /**
   * Creates a DefaultWorkspaceShowingAdapter
   * @throws com.gensym.jgi.G2CommunicationException
   */
  public DefaultWorkspaceShowingAdapter (TwAccess connection) {
    try{
      setConnection(connection);
    }
    catch(G2AccessException ex){
      Trace.exception(ex);
      throw new G2CommunicationException(ex);
    }
    registerStyle (UIL_DIALOG_SUBWORKSPACE_,
		   new WorkspaceDisplayStyle (true, true, false, false));
  }

  /**
   * Accepts a new connection created in a single connection application.
   * This may be null if the connection has been closed.
   * @param connection the new connection or null
   */
  protected void setConnection (TwAccess connection) throws G2AccessException {
    if (this.connection != null && this.connection.equals (connection))
      return;
    if (this.connection != null)
      this.connection.removeWorkspaceShowingListener (this);
    if (connection != null){
      if (connection.isLoggedIn())
	connection.addWorkspaceShowingListener(this);
      else
	connection.addTwConnectionListener(connectionLoginAdapter);
    }
    this.connection = connection;
  }

  /**
   * Implements the show of the kb-workspace.
   * Simply adds a new WorkspaceView to the center the Frame. It assumes that
   * the Frame has a BorderLayout. Sublcasses can specialize this method
   * to do something more specific.
   * @param event the workspace-showing event that is being handled
   * @see com.gensym.ntw.util.UiApplication
   */
  @Override
  public void showWorkspace (WorkspaceShowingEvent evt) {
    showWorkspace((TwConnection)evt.getSource(), (KbWorkspace)evt.getWorkspace(), evt.getParticulars());
  }


  /**
   * @undocumented
   */
  public void showWorkspace(TwConnection connection, KbWorkspace wksp){
    showWorkspace(connection, wksp, null);
  }

  private void showWorkspace (TwConnection connection, KbWorkspace wksp, Structure showingParticulars) {
    WorkspaceDisplayStyle desiredStyle = findStyle (wksp);
    WorkspaceDisplayer displayer;
    Container prevContainer = (Container)containers.get (wksp);
    // check if the style restricts this show
    if (desiredStyle != null) {
      if (!desiredStyle.allowMultipleViews ()) {
	if ((displayer = (WorkspaceDisplayer)displayTable.remove (wksp)) != null) {
	  displayer.displayWorkspace (connection,
				      wksp,
				      showingParticulars);
	  return;
	}
	if (prevContainer != null) {
	  if (prevContainer instanceof Window)
	    com.gensym.ntw.util.WindowUtil.centerFrame ((Window)prevContainer);
	  prevContainer.setVisible (true);
	  ensureWorkspaceOnTop (prevContainer, wksp);
	  return;
	}
      }
    }
    java.lang.Object wkspContainerOrDisplayer;
    if (prevContainer == null)
      wkspContainerOrDisplayer = getDisplayContainer (wksp, desiredStyle);
    else
      wkspContainerOrDisplayer = prevContainer;
    if (wkspContainerOrDisplayer instanceof WorkspaceDisplayer) {
      ((WorkspaceDisplayer)wkspContainerOrDisplayer).displayWorkspace (connection,
								       wksp,
								       showingParticulars);
      displayTable.put (wksp, wkspContainerOrDisplayer);
    } else if (wkspContainerOrDisplayer instanceof Container) {
      Container wkspContainer = (Container) wkspContainerOrDisplayer;
      if (prevContainer == null) {
	try {
	  wksp.addItemListener (deletionListener);
	} catch (G2AccessException g2ae) {
	  Trace.exception (g2ae);
	  return;
	}
      }
      containers.put (wksp, wkspContainer);
      Container containerOrContentPane = getContainerOrContentPane(wkspContainer);
      containerOrContentPane.setLayout (new BorderLayout());
      Container wkspWrapper = makeViewOrWrapper (wksp, desiredStyle);
      Sequence currentStack = (Sequence) containerStack.get (wkspContainer);
      if (currentStack == null)
	currentStack = new Sequence (1);
      else
	if (currentStack.size () > 0)
	  wkspContainer.remove ((Component)currentStack.lastElement ());
      currentStack.addElement (wkspWrapper);
      containerStack.put (wkspContainer, currentStack);
      containerOrContentPane.add (wkspWrapper, BorderLayout.CENTER);
      if (wkspContainer instanceof Window) {
	Window w = (Window)wkspContainer;
	w.pack ();
	com.gensym.ntw.util.WindowUtil.centerFrame (w);
      } else {
	//invalidate & validate?
      }
      wkspContainer.setVisible (true);
    } else
      throw new IllegalArgumentException ("getDisplayContainer should return a java.awt.Container or a com.gensym.ntw.util.WorkspaceDisplayer. Instead got a " + wkspContainerOrDisplayer.getClass().getName());
  }
  
  private Container getContainerOrContentPane(Container wkspContainer){
    if (wkspContainer instanceof JApplet)
      return ((JApplet)wkspContainer).getContentPane();
    else if (wkspContainer instanceof JDialog)
      return ((JDialog)wkspContainer).getContentPane();
    else if (wkspContainer instanceof JFrame)
      return ((JFrame)wkspContainer).getContentPane();
    else if (wkspContainer instanceof JWindow)
      return ((JWindow)wkspContainer).getContentPane();
    else return wkspContainer;
  }
  
  private ItemListener deletionListener = new ItemListener () {
    @Override
    public void receivedInitialValues (ItemEvent ie) {}
    @Override
    public void itemModified (ItemEvent ie) {}
    @Override
    public void itemDeleted (ItemEvent ie) {
      KbWorkspace wksp = (KbWorkspace) ie.getSource ();
      Container displayContainer = (Container) containers.get (wksp);
      if (displayContainer != null)
	clearAllViews (displayContainer, wksp);
    }
  };

  private WorkspaceView getViewFromWrapper (Container wkspWrapper) {
    if (wkspWrapper instanceof WorkspaceView)
      return (WorkspaceView)wkspWrapper;
    else
      return ((WorkspaceWrapper)wkspWrapper).view;
  }

  /**
   * Implements the hide of the kb-workspace.
   * Simply disposes the WorkspaceView displaying the kb-workspace from
   * its list of children.
   * @param event the workspace-showing event that is being handled
   * @see com.gensym.wksp.WorkspaceView#dispose
   */
  @Override
  public void hideWorkspace (WorkspaceShowingEvent evt) {
    KbWorkspace wksp = (KbWorkspace)evt.getWorkspace();
    if (wksp == null) return;	// When does this happen? -vkp, 5/1/98

    WorkspaceDisplayer displayer;
    if ((displayer = (WorkspaceDisplayer)displayTable.remove (wksp)) != null) {
      displayer.removeWorkspace ((TwConnection)evt.getSource(),
				 wksp,
				 evt.getParticulars());
    } else {
      Container displayContainer = (Container) containers.remove (wksp);
      if (displayContainer == null) {
	if (com.gensym.core.GensymApplication.getDevOption ())
	  System.err.println ("\n\n NO DISPLAY CONTAINER FOUND FOR : " + wksp + "\n\n");
	return;
      }
      clearAllViews (displayContainer, wksp);
    }
  }

  private void clearAllViews (Container displayContainer, KbWorkspace wksp) {
    Sequence showingWksps = (Sequence) containerStack.get (displayContainer);
    int wkspIndex;
    while ((wkspIndex = getIndexOfWkspInStack (showingWksps, wksp)) >= 0) {
      Container wkspWrapper = (Container) showingWksps.elementAt (wkspIndex);
      Container wkspContainer = wkspWrapper.getParent ();
      wkspContainer.remove (wkspWrapper);
      WorkspaceView view = getViewFromWrapper (wkspWrapper);
      view.dispose ();
      showingWksps.removeElementAt (wkspIndex);
      if (showingWksps.size () == 0) {
	if (wkspContainer instanceof Window)
	  wkspContainer.setVisible (false);
      } else {
	int newSize = showingWksps.size ();
	if (wkspIndex == newSize) { // if removed last/visible view, show previous
	  wkspWrapper = (Container) showingWksps.elementAt (wkspIndex - 1);
	  wkspContainer.add (wkspWrapper, BorderLayout.CENTER);
	}
      }
    }
  }

  // called only in case of one occurrence in stack
  private void ensureWorkspaceOnTop (Container wkspContainer, KbWorkspace wksp) {
    Sequence showingWksps = (Sequence) containerStack.get (wkspContainer);
    int i = getIndexOfWkspInStack (showingWksps, wksp);
    // make it visible
    Container lastWrapper = (Container) showingWksps.lastElement ();
    wkspContainer.remove (lastWrapper);
    Container wkspWrapper = (Container) showingWksps.elementAt (i);
    wkspContainer.add (wkspWrapper);
    // reorder stack
    showingWksps.removeElementAt (i);
    showingWksps.addElement (wkspWrapper);
  }

  private int getIndexOfWkspInStack (Sequence showingWksps, KbWorkspace wksp) {
    for (int i=showingWksps.size(); i-->0;) {
      Container wkspWrapper = (Container) showingWksps.elementAt (i);
      if (getViewFromWrapper(wkspWrapper).getItem().equals (wksp))
	return i;
    }
    return -1;
  }

  private Container makeViewOrWrapper (KbWorkspace wksp, WorkspaceDisplayStyle desiredStyle) {
    WorkspaceView wkspView = WorkspaceView.createWorkspaceView(this, wksp);
    wkspView.setDoubleBuffered (true);
    Container wrapper;
    if (desiredStyle != null && desiredStyle.isScrollbarsVisible ()) {
      wrapper = new WorkspaceWrapper (wkspView);
      wrapper.setLayout (new BorderLayout ());
      wrapper.add (wkspView, BorderLayout.CENTER);
      Rectangle initialBounds = wkspView.getBounds();
      int initialLeft = initialBounds.x;
      int initialTop = initialBounds.y;
      int initialWidth = initialBounds.width;
      int initialHeight = initialBounds.height;
      ViewScrollbar hscroll = new ViewScrollbar (wkspView, LWScrollbar.HORIZONTAL, 0, 1,
						 initialLeft, initialLeft + initialWidth);
      ViewScrollbar vscroll = new ViewScrollbar (wkspView, LWScrollbar.VERTICAL, 0, 1,
						 initialTop, initialTop + initialHeight);
      wkspView.addScrollbar(vscroll, false);
      wkspView.addScrollbar(hscroll, true);
      wrapper.add (hscroll, BorderLayout.SOUTH);
      wrapper.add (vscroll, BorderLayout.EAST);
    } else
      wrapper = wkspView;
    return wrapper;
  }

  /**
   *
   */
  class ConnectionLoginAdapter extends TwConnectionAdapter {
    @Override
    public void loggedIn (TwConnectionEvent cxnEvent) {
      TwAccess cxn = (TwAccess) cxnEvent.getSource ();
      try {
	cxn.removeTwConnectionListener(this);
	cxn.addWorkspaceShowingListener (DefaultWorkspaceShowingAdapter.this);
      } catch (G2AccessException gae) {
	// What to do?
	Trace.exception(gae);
      }
    }
  }

  private Frame theFrame;
  private WindowListener beeper = new WindowAdapter () {
    @Override
    public void windowClosing (WindowEvent wEvt) {
      Toolkit.getDefaultToolkit().beep();
    }
  };
  private WindowListener closer = new WindowAdapter () {
    @Override
    public void windowClosing (WindowEvent wEvt) {
      Sequence showingWksps = (Sequence) containerStack.get (wEvt.getSource ());
      for (int i=showingWksps.size(); i-->0;) {
	Container wkspWrapper = (Container) showingWksps.elementAt (i);
	WorkspaceView view = getViewFromWrapper (wkspWrapper);
	KbWorkspace wksp = (KbWorkspace) view.getItem ();
	try {
	  wksp.hide ();
	} catch (G2AccessException g2ae) {
	  Trace.exception (g2ae);
	}
      }
    }
  };
  protected java.lang.Object getDisplayContainer (KbWorkspace wksp,
						  WorkspaceDisplayStyle style) {
    Container displayContainer =  UiApplication.getCurrentFrame ();
    if (theFrame == null)
      theFrame = new Frame ();
    if (displayContainer == null)
      displayContainer = theFrame;
    if (style != null) {
      if (style.isFloating ()) {
	if (style.isTitleDisplayed ()) {
	  displayContainer = new DoubleBufferedDialog (theFrame);
	  Dialog dlg = (Dialog)displayContainer;
	  dlg.setResizable (false);
	  try {
            TwAccess cxn = (TwAccess)((com.gensym.classes.ImplAccess)wksp).getContext ();
            Symbol userMode = cxn.getUserMode ();
	    ConfigurationSupport.setUserMode(userMode);
	    Structure restrictionStruct
	      = ConfigurationSupport.getChoiceRestrictions(wksp, ITEM_MENU_);
	    Boolean permitted 
	      = (Boolean)restrictionStruct.getAttributeValue(PERMITTED_, Boolean.FALSE);
	    Sequence choiceRestrictions
	      = (Sequence) restrictionStruct.getAttributeValue(CHOICE_RESTRICTIONS_, new Sequence());
	    Symbol HIDE_WORKSPACE_ = Symbol.intern ("HIDE-WORKSPACE");
	    Sequence menuChoices = new Sequence ();
	    menuChoices.addElement (HIDE_WORKSPACE_);
	    menuChoices
	    	  = ConfigurationSupport.filterChoicesByRestrictions(menuChoices,
								     choiceRestrictions,
								     permitted.booleanValue());
	    if (menuChoices.size () == 0)
	      dlg.addWindowListener (beeper);
	    else
	      dlg.addWindowListener (closer);
	      
	  } catch (G2AccessException g2ae) {
	    Trace.exception (g2ae);
	  }
	} else
	  displayContainer = new DoubleBufferedWindow (theFrame);
      }
    }
    return displayContainer;
  }


  private Hashtable registryTable = new Hashtable (11);
  private transient ItemListener itemAdapter;

  public void registerStyle (Symbol className_, WorkspaceDisplayStyle style) {
    registryTable.put (className_, style);
  }

  public void registerStyle (KbWorkspace wksp, WorkspaceDisplayStyle style) throws G2AccessException {
    registryTable.put (wksp, style);
    if (itemAdapter == null) {
      itemAdapter = new ItemListener () {
	@Override
	public void receivedInitialValues (ItemEvent iEvt) {}
	@Override
	public void itemModified (ItemEvent iEvt) {}
	@Override
	public void itemDeleted (ItemEvent iEvt) {
	java.lang.Object deletedWksp = iEvt.getSource ();
	registryTable.remove (deletedWksp);
	}
      };
    }
    wksp.addItemListener (itemAdapter);
  }

  public void deregisterStyle (Symbol className_) {
    registryTable.remove (className_);
  }

  public void deregisterStyle (KbWorkspace wksp) throws G2AccessException {
    registryTable.remove (wksp);
    wksp.removeItemListener (itemAdapter);
  }
  
  private WorkspaceDisplayStyle findStyle (KbWorkspace wksp) {
    WorkspaceDisplayStyle desiredStyle = (WorkspaceDisplayStyle) registryTable.get (wksp);
    //System.out.println ("\nDefault Displayer : " + desiredStyle + " for " + wksp + " from " + registryTable);
    if (desiredStyle == null) {
      try {
	//System.out.println ("Getting definition = " + wksp.getDefinition().getClassName());
	//System.out.println ("Class Inheritance Path = " + wksp.getDefinition().getClassInheritancePath());
	Sequence clInhPath = wksp.getDefinition ().getClassInheritancePath ();
	for (int i=0; i<clInhPath.size (); i++) {
	  //System.out.println ("Checking " + clInhPath.elementAt (i));
	  if ((desiredStyle = (WorkspaceDisplayStyle)
	       registryTable.get (clInhPath.elementAt (i))) != null)
	    break;
	}
      } catch (G2AccessException gae) {
	Trace.exception (gae);
      }
    }
    //System.out.println ("Default Displayer : Class Lookup " + desiredStyle + " for " + wksp + " from " + registryTable);
   return desiredStyle;
  }

  /**
   * @undocumented
   */
  public void cleanupConnection(G2Access cxn) {
    cleanupConnection(cxn, displayTable);
    cleanupConnection(cxn, containers);
  }

  private void cleanupConnection(G2Access cxn, Hashtable table) {
    if (table != null) {
      // Go through the hashtable, find something that's an item and
      // .equals to the cxn and remove it from the hashtable
      // To try and fix the G2Gateway leak.

      Enumeration keys = table.keys();
      KbWorkspace possibleMatch;
      while (keys.hasMoreElements()) {
	possibleMatch = (KbWorkspace)keys.nextElement();
	G2Access context = ((ImplAccess)possibleMatch).getContext();
	if (cxn.equals(context)) {
	  table.remove(possibleMatch);
	  break;
	}
      }
    }
  }
	
}


class WorkspaceWrapper extends Container {

  WorkspaceView view;

  WorkspaceWrapper (WorkspaceView view) {
    this.view = view;
  }

}

class DoubleBufferedDialog extends Dialog {

  private Image dbf;

  DoubleBufferedDialog (Frame f) {
    super (f);
  }

  @Override
  public void invalidate () {
    super.invalidate ();
    dbf = null;
  }

  @Override
  public void update (Graphics g) {
    paint (g);
  }

  @Override
  public void paint (Graphics g) {
    if (dbf == null) {
      Dimension d = getSize ();
      dbf = createImage (d.width, d.height);
    }
    Graphics offscreenGraphics = dbf.getGraphics ();
    offscreenGraphics.setClip (g.getClip ());
    super.paint (offscreenGraphics);
    g.drawImage (dbf, 0, 0, null);
    offscreenGraphics.dispose ();
  }
}

class DoubleBufferedWindow extends Window {
  
  private Image dbf;

  DoubleBufferedWindow (Frame f) {
    super (f);
  }

  @Override
  public void invalidate () {
    super.invalidate ();
    dbf = null;
  }

  @Override
  public void update (Graphics g) {
    paint (g);
  }

  @Override
  public void paint (Graphics g) {
    if (dbf == null) {
      Dimension d = getSize ();
      dbf = createImage (d.width, d.height);
    }
    Graphics offscreenGraphics = dbf.getGraphics ();
    offscreenGraphics.setClip (g.getClip ());
    super.paint (offscreenGraphics);
    g.drawImage (dbf, 0, 0, null);
    offscreenGraphics.dispose ();
  }

}
