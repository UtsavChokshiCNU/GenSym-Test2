/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 MDIDocument.java
 *
 */

package com.gensym.mdi;

import java.awt.Component;
import javax.swing.JInternalFrame;
import javax.swing.JMenuBar;
import javax.swing.JMenu;
import javax.swing.Icon;
import java.awt.MenuContainer;
import java.awt.Dimension;
import java.util.Vector;
import java.util.Enumeration;
import com.gensym.message.Resource;

/**
 *  MDIDocuments are internal frames within a Multiple Document Interface
 *  application.  In most modern day MDI-applications, the MDIFrame
 *  contains multiple document types.  For example, a spreadsheet application
 *  may contain both a spreadsheet document and a chart document.
 *  Each document type is typically represented by a subclass of MDIDocument.
 *<p>
 *  Each MDIDocument may have an associated menu bar, window menu, and toolbar panel. 
 *  When the document has focus, its menu bar is set as the active menu for the 
 *  frame window and its toolbar panel is placed below the menu bar.
 *  The document's window menu contains a list of the current 
 *  documents and it is maintained by the MDIManager.  Multiple MDIDocuments
 *  may share a single menu bar.  Typically, each subclass of MDIDocument shares
 *  a menu bar.
 *</p><p>
 *  By default, a MDIDocument has close, iconify, and maximize buttons in the
 *  title bar.
 *</p>
 *  @see com.gensym.mdi.MDIFrame
 *  @see com.gensym.mdi.MDIManager */

public abstract class MDIDocument extends JInternalFrame{
  JMenuBar frameMenuBar;
  JMenu windowMenu;
  MDICheckBoxMenuItem[] menuEntries;
  MDIToolBarPanel toolBarPanel;
  int oldX, oldY;
  Dimension oldSize;
  private static Resource i18n = Resource.getBundle("com.gensym.resources.Errors");
  static final Icon defaultIcon = new JInternalFrame().getFrameIcon();

  /** Creates a resizable, closable, maximizable, and iconifiable MDIDocument 
   *  with no title and no associated menu bar or window menu. */
  public MDIDocument(){
    this(" ", null, null, null, true, true, true, true);
  }

  /** Creates a resizable, closable, maximizable, and iconifiable MDIDocument 
   *  with a title and no associated menu bar or window menu.*/
  public MDIDocument(String title){
    this(title, null, null, null, true, true, true, true);
  }

  /** Creates a resizable, closable, maximizable, and iconifiable MDIDocument 
   *  with no title, and associated menu bar, window menu, and toolbar panel.*/
  public MDIDocument(JMenuBar frameMenuBar, JMenu windowMenu, 
		     MDIToolBarPanel toolBarPanel){
    this("", frameMenuBar, windowMenu, toolBarPanel, true, true, true, true);
  }

  /** Creates a resizable, closable, maximizable, and iconifiable MDIDocument 
   *  with no title, and associated menu bar, window menu, and toolbar.*/
  public MDIDocument(String title, JMenuBar frameMenuBar, JMenu windowMenu, 
		     MDIToolBarPanel toolBarPanel){
    this(title, frameMenuBar, windowMenu, toolBarPanel, true, true, true, true);
 }

  /** Creates a MDIDocument
   *  @param title the title of the frame
   *  @param frameMenuBar a MenuBar to be set when frame has focus
   *  @param windowMenu the menu to be used as the window menu
   *  @param resizable true to allow resizing
   *  @param closable true to allow frame to be closed
   *  @param maximizable true to allow frame to be maximized
   *  @param iconifiable true to allow frame to be iconified */
  public MDIDocument(String title, JMenuBar frameMenuBar, JMenu windowMenu, 
		     MDIToolBarPanel toolBarPanel, boolean resizable, 
		     boolean closable, boolean maximizable, boolean iconifiable){
    super(title, resizable, closable, maximizable, iconifiable);
    if ((frameMenuBar == null)&&(windowMenu != null)){
      IllegalArgumentException ex = new IllegalArgumentException(
       i18n.getString("illegalArgsToMDIChildFrameConstructor"));
      throw ex;
    }
    this.frameMenuBar = frameMenuBar;
    this.windowMenu = windowMenu;
    this.toolBarPanel = toolBarPanel;
    init();
  }

  private void init(){
    menuEntries = new MDICheckBoxMenuItem[2];
    menuEntries[0] = new MDICheckBoxMenuItem(this, toShortString());
    menuEntries[1] = new MDICheckBoxMenuItem(this, toShortString());
    oldX = -1;
    oldY = -1;
    setOpaque(true);
  }

  void setMenuEntriesState(boolean state){
    menuEntries[0].setState(state);
    menuEntries[1].setState(state);
  }

  void removeMenuEntries(){
    java.awt.Container parent;
    parent = menuEntries[0].getParent();
    if (parent != null) parent.remove(menuEntries[0]);
    parent = menuEntries[1].getParent();
    if (parent != null) parent.remove(menuEntries[1]);
  }

  MDICheckBoxMenuItem getMenuEntry(int index){
    return menuEntries[index];
  }

  /** Returns this documents MDIManager. */
  public MDIManager getManager(){
    return (MDIManager)getDesktopPane();
  }

  /** Sets the title of the frame and updates window menu entries to reflect
   *  the title change. */
  @Override
  public void setTitle(String title){
    super.setTitle(title);
    menuEntries[0].setText(title);
    menuEntries[1].setText(title);
  }

  /** Returns the menu bar associated with the document. 
   *  Returns null if no menu bar is associated with the document.*/
  public JMenuBar getDocumentMenuBar(){
    return frameMenuBar;
  }

  /** Returns the window menu associated with the document. 
   *  Returns null if no window menu is associated with the document. */
  public JMenu getWindowMenu(){
    return windowMenu;
  }

  /** Sets the menu bar and window menu associated with the document.
   *  If the document is active, its new menu bar is set as the current menu bar.
   */
  public void setDocumentMenuBar(JMenuBar frameMenuBar, JMenu windowMenu){
    this.frameMenuBar = frameMenuBar;
    this.windowMenu = windowMenu;
    if (isSelected()){
      MDIManager manager = getManager();
      manager.activateMenuBar(this);
    }
  }  

  /** Returns the toolbar panel associated with the child frame. */
  public MDIToolBarPanel getToolBarPanel(){
    return toolBarPanel;
  }

  /** Sets the toolbar panel associated with the documents.
   *  If the document is active, then the toolbar panel is set as the current tool bar panel.
   */
  public void setToolBarPanel(MDIToolBarPanel toolBarPanel){
    this.toolBarPanel = toolBarPanel;
    if (isSelected()){
      MDIManager manager = getManager();
      manager.activateToolBarPanel(this);
    }
  }

  /** Returns short string.  Default behaviour is to return title. */
  public String toShortString(){
    return getTitle();
  }

}



