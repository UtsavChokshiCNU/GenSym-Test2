/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 TraceDialog.java
 *
 */
package com.gensym.shell.dialogs;

import java.awt.Button;
import java.awt.Frame;
import java.awt.Insets;
import java.awt.GridBagConstraints;
import java.awt.Label;
import java.awt.Panel;
import java.awt.TextField;
import com.gensym.dlg.CommandConstants;
import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.StandardDialogClient;
import com.gensym.message.Resource;
import com.gensym.uiutil.StandardGridBagPanel;

public class TraceDialog extends StandardDialog implements CommandConstants {

  private TracePanel tracePanel = null;

  public TraceDialog (Frame parentFrame, String title, boolean isModal,
		      StandardDialogClient client) {   
 
    super (parentFrame, title, isModal,
	   new String[] {OK_LABEL, CANCEL_LABEL},
	   new int[] {OK, CANCEL},
	   new TracePanel(),
	   client);

    tracePanel = (TracePanel) getDialogComponent();
    pack (); 
  }

  /**
   * @return The TextField that is used for entering the keys for filtering
   * trace messages.
   */ 
  public TextField getKeysTextField(){
    return tracePanel.getKeysTextField();
  }

  /**
   * @return The TextField that is used for entering the level for filtering
   * trace messages. Default value is  Trace.ALL_LEVELS
   */
  public TextField getLevelTextField(){
    return tracePanel.getLevelTextField();
  }

  /**
   * @return The TextField that is used for entering message strings for
   * filtering trace messages
   */
  public TextField getMessagesTextField(){
    return tracePanel.getMessagesTextField();
  }

  
  /**
   * Called from StandardDialog to lay out buttons
   */
  @Override
  public int getButtonAlignment () {
    return CENTER;
  }
}

class TracePanel extends StandardGridBagPanel {

  private Label     keysLabel = null;
  private TextField keysTF = null;
  private Label     levelLabel = null;
  private TextField levelTF = null;
  private Label     messagesLabel = null;
  private TextField messagesTF = null;

  private static Resource shortBundle = Resource.getBundle("com/gensym/shell/dialogs/ShellDialogResources");

  public TracePanel () {

    GridBagConstraints gridC = new GridBagConstraints ();
   
    setLayout (gridBagLayout);

    gridC.insets = new Insets (10, 10, 10, 10);
    gridC.fill = GridBagConstraints.BOTH;
    gridC.weightx = 1.0;

    String str = shortBundle.getString("TracePanelKeysLabel");
    gridC.gridwidth = GridBagConstraints.RELATIVE; 
    addComponent(keysLabel = new Label(str), gridC);
    gridC.gridwidth = GridBagConstraints.REMAINDER; // end row
    addComponent(keysTF = new TextField("", 20), gridC);

    str = shortBundle.getString("TracePanelLevelLabel");
    gridC.gridwidth = GridBagConstraints.RELATIVE; 
    addComponent(levelLabel = new Label(str), gridC);
    gridC.gridwidth = GridBagConstraints.REMAINDER; // end row
    addComponent(levelTF = new TextField("", 20), gridC);

    str = shortBundle.getString("TracePanelMessagesLabel");
    gridC.gridwidth = GridBagConstraints.RELATIVE; 
    addComponent(messagesLabel = new Label(str), gridC);
    gridC.gridwidth = GridBagConstraints.REMAINDER; // end row
    addComponent(messagesTF = new TextField("", 10), gridC);
  }

  public Label getKeysLabel() {
    return keysLabel;
  }

  public TextField getKeysTextField() {
    return keysTF;
  } 

  public Label getLevelLabel() {
    return levelLabel;
  }

  public TextField getLevelTextField() {
    return levelTF;
  }

  public Label getMessagesLabel() {
    return messagesLabel;
  }

  public TextField getMessagesTextField() {
    return messagesTF;
  }
}
