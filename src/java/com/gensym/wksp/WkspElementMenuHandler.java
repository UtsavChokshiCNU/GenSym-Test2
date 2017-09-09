package com.gensym.wksp;


import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.jgi.*;
import com.gensym.ntw.*;
import com.gensym.draw.*;
import java.awt.*; //Rectangle
import java.awt.event.*;
import java.util.Locale;
import com.gensym.classes.Item;
import com.gensym.classes.KbWorkspace;
import com.gensym.dlgruntime.DialogManager;

class WkspElementMenuHandler implements ActionListener, Runnable {
  private static boolean wkspElementMenuHandlerDebugP = false;
  private static final Resource i18n =
  Resource.getBundle("com.gensym.resources.MenuStrings");
  private static MenuItem cutMenuItm, copyMenuItm, pasteMenuItm, enableMenuItm,
                          disableMenuItm, describeMenuItm, createSubWkspMenuItm,
			  editMenuItm, propMenuItm, currentItm,
    flipHorizontallyItm, flipVerticallyItm,
    changeColorItm,restoreToNormalSizeItm;
  private String action;
  private static PopupMenu thePopup;
  private static final Symbol ADMINISTRATOR_ = Symbol.intern ("ADMINISTRATOR");

  static PopupMenu create () {
    thePopup = new PopupMenu ();
    thePopup.add (cutMenuItm = new MenuItem (i18n.getString("Edit_Cut")));
    cutMenuItm.setActionCommand ("CUT");
    thePopup.add (copyMenuItm = new MenuItem (i18n.getString("Edit_Copy")));
    copyMenuItm.setActionCommand ("COPY");
    thePopup.add (pasteMenuItm = new MenuItem (i18n.getString("Edit_Paste")));
    pasteMenuItm.setActionCommand ("PASTE");

    /*
    thePopup.addSeparator ();
    Menu rotateFlipMenu
      = new Menu(i18n.getString("Layout_RotateFlip"), false);
    rotateFlipMenu.add (i18n.getString("Layout_RotateFlip_RotateAroundObjectCenter"));
    rotateFlipMenu.add (i18n.getString("Layout_RotateFlip_SelectCenterOfRotation"));
    rotateFlipMenu.add (i18n.getString("Layout_RotateFlip_SpecifyRotation"));
    rotateFlipMenu.addSeparator();
    rotateFlipMenu.add (flipHorizontallyItm
			= new MenuItem (i18n.getString("Layout_RotateFlip_FlipHorizontally")));
    rotateFlipMenu.add (flipVerticallyItm
			= new MenuItem(i18n.getString("Layout_RotateFlip_FlipVertically")));
    thePopup.add (rotateFlipMenu);
    
    Menu colorMenu
      = new Menu("Color", false);
    colorMenu.add(changeColorItm
		  = new MenuItem("Change Icon Color To Red"));//hack
    thePopup.add (colorMenu);
    thePopup.add (restoreToNormalSizeItm
		  = new MenuItem("Normalize Size"));
    thePopup.addSeparator ();

    thePopup.add (enableMenuItm = new MenuItem ("Enable"));//i18n.getString("Edit_Disable")));
    thePopup.add (disableMenuItm = new MenuItem (i18n.getString("Edit_Disable")));

    thePopup.add (describeMenuItm = new MenuItem (i18n.getString("Edit_Describe")));
    thePopup.add (createSubWkspMenuItm
		  = new MenuItem (i18n.getString("Edit_CreateSubworkspace")));
		  */
    thePopup.addSeparator ();
    thePopup.add (editMenuItm = new MenuItem (i18n.getString("Edit")));
    editMenuItm.setActionCommand ("EDIT");
    thePopup.add (propMenuItm = new MenuItem (i18n.getString ("Properties")));
    propMenuItm.setActionCommand ("PROPERTIES");

    pasteMenuItm.setEnabled (false);
    WkspElementMenuHandler handler = new WkspElementMenuHandler ();
    cutMenuItm.addActionListener (handler);
    copyMenuItm.addActionListener (handler);
    pasteMenuItm.addActionListener (handler);
    //flipHorizontallyItm.addActionListener (handler);
    //flipVerticallyItm.addActionListener (handler);
    //changeColorItm.addActionListener (handler);
    //restoreToNormalSizeItm.addActionListener(handler);
    //enableMenuItm.addActionListener (handler);
    //disableMenuItm.addActionListener (handler);
    //describeMenuItm.addActionListener (handler);
    //createSubWkspMenuItm.addActionListener (handler);
    editMenuItm.addActionListener (handler);
    propMenuItm.addActionListener (handler);

    return thePopup;
  }

  @Override
  public void actionPerformed (ActionEvent ae) {
    if (wkspElementMenuHandlerDebugP)
      System.out.println ("Somebody selected " + ae + " from a thePopup menu!");
    currentItm = (MenuItem)ae.getSource ();
    String x = ae.getActionCommand ();
    System.out.println ("Action command = " + x);
    action = x;
    new NtwNotification (NtwNotification.STATUSCHANGE,
			 0, "", this, NtwNotification.ACTIVITY_START).send ();
    new Thread (this).start ();
    if (wkspElementMenuHandlerDebugP)
      System.out.println ("PopupMenu Selection Thread : RETURNING!");
  }

  @Override
  public void run () {
    if (wkspElementMenuHandlerDebugP)
      System.out.println ("Running action of choosing from popupMenu!");

    MenuContainer mc = thePopup.getParent ();
    if (wkspElementMenuHandlerDebugP)
      System.out.println ("Popup Menu parent = " + mc);
    WorkspaceView wksp = (WorkspaceView)mc;
    WorkspaceElement[] selection = wksp.getSelection ();    
    if (selection.length == 0)
      return;
    WorkspaceElement currentElement = selection[0];

    try {
      if (action.equals ("CUT")) {
	//currentElement.requestDelete();
      } else if (action.equals ("COPY")) {
	//currentElement.requestClone(wksp.getWorkspace(),,0);
      } else if (currentItm == flipVerticallyItm){
	//currentElement.requestFlipVertically();
      } else if (currentItm == flipHorizontallyItm) {
	//currentElement.requestFlipHorizontally();
      } else if (currentItm == changeColorItm) {
	//currentElement.requestChangeColor(Symbol.intern("ICON-COLOR"), Symbol.intern("red"));
      }
      else if (currentItm == restoreToNormalSizeItm) {
	//currentElement.requestRestoreNormalSize();
      } else if (currentItm == enableMenuItm) {
       //currentElement.requestEnable();
      } else if (currentItm == disableMenuItm) {
	//currentElement.requestDisable();
      } else if (action.equals ("EDIT")) {
	//This should be going through the command handler
	Item it = currentElement.getItem();
      } else if (action.equals ("PROPERTIES")) {
	// do nothing - cuz this whole file is obsolete
      } else if (currentItm instanceof UserMenuItem) {
	((UserMenuItem)currentItm).fire();
      } 
    }
    catch (Exception g2ae) {
      // fix this: there will be new notification scheme
      Trace.exception (g2ae);
      new NtwNotification (NtwNotification.EXCEPTION,
			   0, g2ae.toString (),
			   this, NtwNotification.ACTIVITY_STOP).send ();
    }
    new NtwNotification (NtwNotification.STATUSCHANGE,
			 0, "", this, NtwNotification.ACTIVITY_STOP).send ();
  }
  
  public static MenuItem getPopupMenu () {
    return thePopup;
  }

  public static Resource getI18n() {
    return i18n;
  }
}
