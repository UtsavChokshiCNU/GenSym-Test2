/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 MDIFrame.java
 *
 */

package com.gensym.mdi;

import java.util.Vector;
import java.awt.FlowLayout;
import java.awt.GridLayout;
import java.awt.Color;
import java.awt.Dimension;
import javax.swing.JMenuBar;
import javax.swing.JMenu;
import java.awt.Graphics;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JRootPane;
import javax.swing.JButton;
import javax.swing.KeyStroke;
import com.gensym.ui.Command;

/** MDIFrame is the "frame window" in a Multiple Document Interface.  
 *  It maintains the menu bar, toolbars, and the status bar.  
 *  Management of the child windows is delegated to the manager (MDIManager). 
 *
 * @see com.gensym.mdi.MDIManager */

public class MDIFrame extends JFrame{
  private static final int DEFAULT_WIDTH = 700;
  private static final int DEFAULT_HEIGHT = 550;
  private MDIManager manager;
  private JMenuBar defaultMenuBar;
  private JMenu defaultWindowMenu;
  private MDIToolBarPanel defaultToolBarPanel;
  private MDIToolBarPanel currentToolBarPanel;
  private MDIStatusBar statusBar;

  /** 
   *  Creates a MDIFrame with a title.
   */
  public MDIFrame(String title){
    this(title, null, null, null);
  }

  /** 
   *  Creates a MDIFrame with a title and default menu bar and toolbar.
   */
  public MDIFrame(String title, JMenuBar mb, JMenu windowMenu, MDIToolBarPanel tb){
    super(title);
    init();
    setDefaultMenuBar(mb, windowMenu);
    setDefaultToolBarPanel(tb);
  }

  private void init(){
    manager = new MDIManager(this);
    placeManager(manager);
    setBackground(Color.lightGray);
    setSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
  }
  
/**
 * @undocumented
 */
  protected void placeManager(MDIManager manager) {
    getContentPane().add(manager, "Center");
  }
  
  @Override
  protected JRootPane createRootPane(){
    return new JRootPane(){
      @Override
      public void setDefaultButton(JButton button){
	super.setDefaultButton(button);
	unregisterKeyboardAction(KeyStroke.getKeyStroke('\n', 0, false));
	unregisterKeyboardAction(KeyStroke.getKeyStroke('\n', 0, true));
      }
    };
  }

  /** 
   *  Returns the MDIManager 
   */
  public MDIManager getManager(){
    return manager;
  }

  /** 
   *  Returns the default menu bar.  
   *  The default menu bar is visible when there are no child documents. 
   */
  public JMenuBar getDefaultMenuBar(){
    return defaultMenuBar;
  }

  /**
   *  Returns the default window menu contained in the default menu bar.
   *  If if the default menu bar doesn't have a window menu, then null
   *  is returned.
   */
  public JMenu getDefaultWindowMenu(){
    return defaultWindowMenu;
  }

  public void setDefaultWindowMenu(JMenu windowMenu) {
    defaultWindowMenu = windowMenu;
  }
  
  /** 
   *  Sets the default menu bar to the specified menu bar. If there is no
   *  window menu, pass in null. If the manager has no documents, then the 
   *  menu bar is set visible. 
   */
  public void setDefaultMenuBar(JMenuBar defaultMenuBar){
    this.defaultMenuBar = defaultMenuBar;
    if (manager.getDocumentCount() == 0) setJMenuBar(defaultMenuBar);
  }

  /** 
   *  Sets the default menu bar to the specified menu bar and the default 
   *  window  menu to the specified window menu.  The windowMenu should be 
   *  a menu contained in the menu bar.  The window menu is maintained by the 
   *  MDIManager and contains a list of all the documents.  If there is no
   *  window menu, pass in null. If the manager has no
   *  documents, then the menu bar is set visible. 
   */
  public void setDefaultMenuBar(JMenuBar defaultMenuBar, JMenu windowMenu){
    this.defaultMenuBar = defaultMenuBar;
    this.defaultWindowMenu = windowMenu;
    if (manager.getDocumentCount() == 0) setJMenuBar(defaultMenuBar);
  }

  /** 
   *  Returns the default toolbar panel. 
   */
  public MDIToolBarPanel getDefaultToolBarPanel(){
    return defaultToolBarPanel;
  }

  /** 
   *  Sets the default toolbar panel for this frame.  If the manager has no
   *  documents, then the toolbar panel is set as the current toolbar panel.
   */
  public void setDefaultToolBarPanel(MDIToolBarPanel toolBarPanel){
    defaultToolBarPanel = toolBarPanel;
    if (manager.getDocumentCount() == 0) setToolBarPanel(defaultToolBarPanel);
  }

  /** 
   *  Sets the current toolbar panel and adds it beneath the menu bar. 
   */
  public void setToolBarPanel(MDIToolBarPanel toolBarPanel){
    if (currentToolBarPanel != null)
      getContentPane().remove(currentToolBarPanel);
    currentToolBarPanel = toolBarPanel;
    if (currentToolBarPanel != null){
      getContentPane().add(currentToolBarPanel, "North");
      validate();
    }
  }

  /** 
   * Returns the current toolbar panel.  If no current toolbar panel exists,
   * then null is returned.
   */
  public MDIToolBarPanel getToolBarPanel(){
    return currentToolBarPanel;
  }

  /** 
   *  @undocumented
   */
  public MDIStatusBar getStatusBar(){
    return statusBar;
  }

  /** 
   *  @undocumented
   */
  public void setStatusBar(MDIStatusBar statusBar){
    if (this.statusBar != null) getContentPane().remove(this.statusBar);
    this.statusBar = statusBar;
    if (statusBar == null) {
      getContentPane().validate();
      return;
    }
    getContentPane().add(statusBar, "South");
  }

  @Override
  public void setJMenuBar(JMenuBar menuBar){
    super.setJMenuBar(menuBar);
    validate();//need to force re-layout, bug?
  }
}

