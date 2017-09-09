/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ClassEditorDialog.java
 *
 */
package com.gensym.g2studio.dialogs;

import java.awt.Frame;

import com.gensym.classes.ClassDefinition;
import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.StandardDialogClient;
import com.gensym.shell.util.ConnectionManager;
import com.gensym.util.Symbol;

public class ClassEditorDialog extends StandardDialog {
  private ClassEditorPanel panel;
  private ConnectionManager connectionManager;
  private ClassDefinition classDefinition;

  public ClassEditorDialog (Frame parentFrame, String title, boolean isModal,
			    ConnectionManager connectionManager,
			    StandardDialogClient client) {  
 
    super (parentFrame, title, isModal,
	   new String[] {OK_LABEL, APPLY_LABEL, CANCEL_LABEL},
	   new int[] {OK, APPLY, CANCEL},
	   new ClassEditorPanel(connectionManager),
	   client);

    this.connectionManager = connectionManager;
    panel = (ClassEditorPanel) getDialogComponent();
    executeSetClassDefinition();
    pack ();
  }

  private void executeSetClassDefinition() {
    if (classDefinition != null)
      panel.setClassDefinition(classDefinition);
  }

  public void setClassDefinition(ClassDefinition classDef) {
    classDefinition = classDef;
    executeSetClassDefinition();
  }

  public ClassDefinition getClassDefinition() {
    return classDefinition;
  }

  //public Symbol getClassName () {
  //Symbol className = null;
  //className = panel.getClassName();
  //return className;
  //}
}

