/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 MDIFrameManager.java
 *
 */

package com.gensym.mdi;

import javax.swing.DefaultDesktopManager;
import javax.swing.JInternalFrame;
import javax.swing.JComponent;

/** This class should be used in the MDI package only.
 *  It is the desktop manager for the MDI client.  All actions
 *  on MDI child frames are re-directed to the desktop manager.
 *  The desktop manager can then tell the MDI client client. */
class MDIFrameManager extends DefaultDesktopManager {

  @Override
  public void closeFrame(JInternalFrame c){
    if (c instanceof MDIDocument){
      MDIDocument child = (MDIDocument)c;
      MDIManager client = (MDIManager)child.getDesktopPane();
      client.frameClosing((MDIDocument)child);
      super.closeFrame(child);
      client.frameClosed();
    }
    else super.closeFrame(c);
  }

  @Override
  public void activateFrame(JInternalFrame c){
    if (c instanceof MDIDocument){
      MDIDocument child = (MDIDocument)c;
      super.activateFrame(child);
      MDIManager client = (MDIManager)child.getDesktopPane();
      client.frameActivated((MDIDocument)child);
    }
    else super.activateFrame(c);
  }

  @Override
  public void deactivateFrame(JInternalFrame c){
    if (c instanceof MDIDocument){
      MDIDocument child = (MDIDocument)c;
      super.deactivateFrame(child);
      MDIManager client = (MDIManager)child.getDesktopPane();
      client.frameDeactivated((MDIDocument)child);
    }
    else super.deactivateFrame(c);
  }

  @Override
  public void beginDraggingFrame(JComponent c){
    if (c instanceof MDIDocument){
      MDIDocument child = (MDIDocument)c;
      child.oldX = child.getX();
      child.oldY = child.getY();
    }
    super.beginDraggingFrame(c);
  }

  @Override
  public void endDraggingFrame(JComponent c){
    if (c instanceof MDIDocument){
      MDIDocument child = (MDIDocument)c;
      if (child.oldX == -1) return;
      if ((child.oldX != child.getX())||(child.oldY != child.getY())){
	MDIManager client = (MDIManager)child.getDesktopPane();
	client.removeChildFromPositions(child);
      }
    }
    super.endDraggingFrame(c);
  }

  @Override
  public void beginResizingFrame(JComponent c, int direction){
    if (c instanceof MDIDocument){
      MDIDocument child = (MDIDocument)c;
      child.oldSize = child.getSize();
    }
    super.beginResizingFrame(c, direction);
  }

  @Override
  public void endResizingFrame(JComponent c){
    MDIDocument child = (MDIDocument)c;
    if (!child.oldSize.equals(child.getSize())){
      MDIManager client = (MDIManager)child.getDesktopPane();
      client.removeChildFromPositions(child);
    }
    super.endResizingFrame(child);
  }

  @Override
  public void iconifyFrame(JInternalFrame c){
    if (c instanceof MDIDocument){
      MDIDocument child = (MDIDocument)c;
      MDIManager client = (MDIManager)child.getDesktopPane();
      client.removeChildFromPositions(child); 
      try{
	child.setSelected(true);
	client.activateNextDocument();
      }
      catch(java.beans.PropertyVetoException ex){}
    }   
    super.iconifyFrame(c);
  }

  //This is a workaround for a SWING bug: A deiconified internal frame is selected but positioned in the back.
  
  @Override
  public void deiconifyFrame(JInternalFrame c){
    super.deiconifyFrame(c);
    java.awt.Component parent = c.getParent();
    if (parent instanceof javax.swing.JLayeredPane)
      ((javax.swing.JLayeredPane)parent).setPosition(c, 0);
  }
  

}
