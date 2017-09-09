/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 OpenProjectDialog.java
 *
 */
package com.gensym.shell.dialogs;

import java.awt.Frame;
import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.StandardDialogClient;
import com.gensym.files.URLFile;
import com.gensym.message.Resource;
import com.gensym.ntw.TwAccess;
import javax.swing.JFileChooser;
import com.gensym.ntw.util.G2FileChooser;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

public class OpenProjectDialog extends StandardDialog {
  private static Resource i18n = Resource.getBundle("com/gensym/shell/dialogs/Messages");    
  protected G2FileChooser chooser;
  protected OpenProjectOptionsPanel optionsPanel;

  public OpenProjectDialog (Frame frame, String title, boolean isModal,
			    TwAccess connection, StandardDialogClient client) { 
    this (frame, title, isModal, false, connection, client);
  }

  public OpenProjectDialog (Frame frame, String title, boolean isModal, boolean withOptions,
			    TwAccess connection, StandardDialogClient client) {
    super (frame, title, isModal, null, null, null, client);
    chooser = new G2FileChooser(connection);
    chooser.setPathIcon(DialogIcons.openIcon);    
    chooser.setApproveButtonText(i18n.getString("OpenButtonLabel"));
    if (withOptions) {
      optionsPanel = createOptionsPanel();
      chooser.addOptionsPanel(optionsPanel, null);    
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
  
  protected OpenProjectOptionsPanel createOptionsPanel() {
    return new OpenProjectOptionsPanel();
  }
  
  @Override
  public void setVisible(boolean visible) {
    if (visible)
      chooser.rescanCurrentDirectory();    
    super.setVisible(visible);
  }
  
  public void setConnection(TwAccess cxn) {
    chooser.setConnection(cxn);    
    boolean isG260 = (cxn.getG2Version().getMajorVersion() >= 6);
    boolean sccsie = isG260 && true;//read this from the server-parameters sys-table  
  }
    
  public void setAutomaticallyResolveConflicts(boolean autoResolve) {
    if (optionsPanel == null)
      throw new IllegalStateException(i18n.getString("noOptionsPanel"));        
    optionsPanel.setAutomaticallyResolveConflicts(autoResolve);
  }

  public boolean getAutomaticallyResolveConflicts() {
    if (optionsPanel == null)
      throw new IllegalStateException(i18n.getString("noOptionsPanel"));        
    return optionsPanel.getAutomaticallyResolveConflicts();
  }

  public void setBringFormatsUpToDate(boolean bringFormatsUpToDate) {
    if (optionsPanel == null)
      throw new IllegalStateException(i18n.getString("noOptionsPanel"));        
    optionsPanel.setBringFormatsUpToDate(bringFormatsUpToDate);
  }

  public boolean getBringFormatsUpToDate() {
    if (optionsPanel == null)
      throw new IllegalStateException(i18n.getString("noOptionsPanel"));        
    return optionsPanel.getBringFormatsUpToDate();
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

