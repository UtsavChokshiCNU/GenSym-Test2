/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ConfigurableFileChooser.java
 *
 */
package com.gensym.uitools.utils;

import java.awt.Component;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.Frame;
import java.awt.Insets;
import javax.swing.JPanel;
import javax.swing.JButton;
import javax.swing.JFileChooser;
import javax.swing.filechooser.FileSystemView;
import javax.swing.border.EmptyBorder;
import com.gensym.message.Resource;
import javax.swing.JDialog;
import javax.swing.JTabbedPane;
import java.awt.Container;
import java.awt.BorderLayout;
import java.util.Vector;
import javax.swing.SwingUtilities;
import javax.swing.Icon;

public class ConfigurableJFileChooser extends JFileChooser {
  private static String optionsLabel = "Options...";//i18n.getString("FileOptions");
  private static String defaultName = "Path";//i18n.getString("Path");
  private JDialog dialog = null;
  private int returnValue = ERROR_OPTION;
  private JTabbedPane tabbedPane;    
  private Vector optionsPanels = new Vector();
  private boolean useOptionsButton;// = true;
  private Icon pathIcon;

  public ConfigurableJFileChooser(String path, FileSystemView fsv) {
    super(path, fsv);
    setName(defaultName);
    if (getUseOptionsButton())
      addOptionsButton();
  }

  public void setPathIcon(Icon pathIcon){
    this.pathIcon = pathIcon;
  }
  
  /**
   * Adds the component in a new tab, using the component's 
   * name for the tab name.
   * @param optionsPanel The component to add.
   * @param icon The iconic representation for this component(or null)
   */
  public void addOptionsPanel(Component optionsPanel, Icon icon) {
    if (tabbedPane == null) {
      tabbedPane = new JTabbedPane();
      if(!getUseOptionsButton()) 
	tabbedPane.addTab(getName(),pathIcon,this);
    }
    tabbedPane.addTab(optionsPanel.getName(),icon,optionsPanel);
    optionsPanels.addElement(optionsPanel);
  }

  /**
   * Removes the tab for this component.
   * @param optionsPanel The component to remove.
   */  
  public void removeOptionsPanel(Component optionsPanel) {
    optionsPanels.removeElement(optionsPanel);
    tabbedPane.remove(optionsPanel);
    if (optionsPanels.isEmpty()) {
      if (!getUseOptionsButton())
	tabbedPane.remove(this);
      tabbedPane = null;
    }
  }

  /**
   * @return if the style is currently set to have the options tabs
   * launched in a seperate window through a button on the main file
   * chooser page.
   */
  public boolean getUseOptionsButton(){
    return useOptionsButton;
  }

  /**
   * Sets the style either to have the options tabs launched in a seperate
   * window through a button on the main file chooser page, or to have 
   * each page as a tab at the top level.
   */  
  public void setUseOptionsButton(boolean useOptionsButton){
    if (getUseOptionsButton() == useOptionsButton) return;
    if (useOptionsButton) 
      addOptionsButton();
    else {
     setAccessory(null);
     if (tabbedPane != null)
       tabbedPane.add(this);
    }
    this.useOptionsButton = useOptionsButton;
  }

  private void addOptionsButton() {
    JButton optionsButton = new JButton(optionsLabel);
    optionsButton.setMargin(new Insets(2,8,2,3));
    optionsButton.addActionListener(new ActionListener() {
      @Override
      public void actionPerformed(ActionEvent ae) {
	JDialog dlg = new JDialog();
	dlg.setTitle(getApproveButtonText()+" "+ConfigurableJFileChooser.optionsLabel);
	dlg.setModal(true);
	Container contentPane = dlg.getContentPane();
	contentPane.setLayout(new BorderLayout());
	contentPane.add(tabbedPane);
	dlg.pack();
	dlg.setLocationRelativeTo(ConfigurableJFileChooser.this);
	dlg.setVisible(true);
      }
    });
    JPanel panel = new JPanel();
    panel.setBorder(new EmptyBorder(0,6,0,5));
    panel.add(optionsButton);
    setAccessory(panel);    
  }

  @Override
  public int showDialog(Component parent, String approveButtonText) {
    dialog = createDialog(parent, approveButtonText, true);
    dialog.setVisible(true);
    return returnValue;
  }

  public JDialog createDialog(Component parent, String approveButtonText, boolean modal) {
    Frame currentFrame = parent instanceof Frame ? (Frame) parent
      : (Frame)SwingUtilities.getAncestorOfClass(Frame.class, parent);
    JDialog dlg = new JDialog(currentFrame, modal);
    configureDialog(approveButtonText, modal, dlg);
    dlg.setLocationRelativeTo(parent);
    return dlg;
  }
  
  private void configureDialog(String approveButtonText, boolean modal, JDialog dlg) {
    if(approveButtonText != null) {
      setApproveButtonText(approveButtonText);
      setDialogType(CUSTOM_DIALOG);
    }
    String title = getDialogTitle();
    if (title == null)
      title = getUI().getDialogTitle(this);
    dlg.setTitle(title);
    dlg.setDefaultCloseOperation(dlg.DO_NOTHING_ON_CLOSE);//maybe add window listener instead
    Container contentPane = dlg.getContentPane();
    contentPane.setLayout(new BorderLayout());
    contentPane.add(getContent());
    dlg.pack();
    rescanCurrentDirectory();
  }  

  /**
   * @return Either this file chooser page or the top level tabbed 
   * pane in which it and any options pages are placed
   */
  public Component getContent() {
    if (tabbedPane == null || getUseOptionsButton()) 
      return this;
    else 
      return tabbedPane;
  }
  
  @Override
  public void approveSelection() {
    returnValue = APPROVE_OPTION;
    if(dialog != null) {
      dialog.setVisible(false);
    }
    fireActionPerformed(APPROVE_SELECTION);
  }

  @Override
  public void cancelSelection() {
    returnValue = CANCEL_OPTION;
    if(dialog != null) {
      dialog.setVisible(false);
    }
    fireActionPerformed(CANCEL_SELECTION);
  }
    
}
