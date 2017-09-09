/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 SaveProjectDialog.java
 *
 */
package com.gensym.shell.dialogs;

import java.awt.Frame;
import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.StandardDialogClient;
import com.gensym.files.URLFile;
import javax.swing.JFileChooser;
import com.gensym.message.Resource;
import com.gensym.ntw.TwAccess;
import com.gensym.ntw.util.G2FileChooser;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.Component;

public class SaveProjectDialog extends StandardDialog {
  static Resource i18n = Resource.getBundle("com/gensym/shell/dialogs/Messages");
  protected G2FileChooser chooser;
  private BasicSaveOptionsPanel basicOptionsPanel;
  private boolean allFile;

  public SaveProjectDialog (Frame frame, String title, boolean isModal,
			    TwAccess connection, StandardDialogClient client) { 
    this(frame, title, isModal, false, connection, client);
  }

  public SaveProjectDialog (Frame frame, String title, boolean isModal, boolean withOptions,
			    TwAccess connection, StandardDialogClient client) {
    super (frame, title, isModal, null, null, null, client);
    chooser = new G2FileChooser(connection);
    chooser.setPathIcon(DialogIcons.saveIcon);
    chooser.setApproveButtonText(i18n.getString("SaveButtonLabel"));    
    if (withOptions) {
      createOptionsPanels(connection);      
    }
    chooser.addActionListener(new ActionListener() {
      @Override
      public void actionPerformed(ActionEvent ae) {
	String cmd = ae.getActionCommand();
	if (chooser.APPROVE_SELECTION.equals(cmd)) 
	  dispatchCallback(OK);
	else if (chooser.CANCEL_SELECTION.equals(cmd)) 
	  dispatchCallback(CANCEL);
      }
    });
    getContentPane().add(chooser.getContent());
    pack();            
  }

  @Override
  protected void dispatchCallback (int code) {
    super.dispatchCallback(code);
  }
  
  public boolean isAllFile(){
    return allFile;
  }

  public void setAllFile(boolean allFile){
    this.allFile = allFile;
  }
  
  protected void createOptionsPanels(TwAccess connection) {
    basicOptionsPanel = new BasicSaveOptionsPanel();
    chooser.addOptionsPanel(basicOptionsPanel, null);
  }

  @Override
  public void setVisible(boolean visible) {
    if (visible)
      chooser.rescanCurrentDirectory();    
    super.setVisible(visible);
  }

  public void setConnection(TwAccess connection){
    chooser.setConnection(connection);
    boolean isG260 = (connection.getG2Version().getMajorVersion() >= 6);
    boolean sccsie = isG260 && true;//read this from the server-parameters sys-table      
  }

  public void setShowProgress(boolean showProgress) {
    if (basicOptionsPanel == null)
      throw new IllegalStateException(i18n.getString("noOptionsPanel"));
    basicOptionsPanel.setShowProgress(showProgress);
  }
  
  public boolean getShowProgress() {
    if (basicOptionsPanel == null)
      throw new IllegalStateException(i18n.getString("noOptionsPanel"));
    return basicOptionsPanel.getShowProgress();
  }
  
  public void setSaveWorkspaceLayout(boolean saveWorkspaceLayout) {
    if (basicOptionsPanel == null)
      throw new IllegalStateException(i18n.getString("noOptionsPanel"));
    basicOptionsPanel.setSaveWorkspaceLayout(saveWorkspaceLayout);
  }

  public boolean getSaveWorkspaceLayout() {
    if (basicOptionsPanel == null)
      throw new IllegalStateException(i18n.getString("noOptionsPanel"));
    return basicOptionsPanel.getSaveWorkspaceLayout();
  }

  public void setSaveRequiredModules(boolean saveRequiredModules) {
    if (basicOptionsPanel == null)
      throw new IllegalStateException(i18n.getString("noOptionsPanel"));
    basicOptionsPanel.setSaveRequiredModules(saveRequiredModules);
  }

  public boolean getSaveRequiredModules() {
    if (basicOptionsPanel == null)
      throw new IllegalStateException(i18n.getString("noOptionsPanel"));
    return basicOptionsPanel.getSaveRequiredModules();
  }

  /**
   * @deprecated
   */  
  public URLFile getURLFile() {
    return null;
  }

  /**
   * @deprecated
   */  
  public void setURLFile(URLFile urlFile) {
  }

  public String getG2FileSpecification() {
    return chooser.getG2FileSpecification();
  }

  public void setG2FileSpecification(String path) {
    chooser.setG2FileSpecification(path);
  }

}

