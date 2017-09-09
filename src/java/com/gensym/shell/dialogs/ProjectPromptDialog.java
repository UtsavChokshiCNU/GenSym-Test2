/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ProjectPromptDialog.java
 *
 */
package com.gensym.shell.dialogs;

import java.awt.Frame;

import com.gensym.dlg.QuestionDialog;
import com.gensym.dlg.StandardDialogClient;
import com.gensym.util.Symbol;

public class ProjectPromptDialog extends QuestionDialog {

  public static final Symbol NEW_PROJECT_   = Symbol.intern("NEW_PROJECT");
  public static final Symbol CLOSE_PROJECT_ = Symbol.intern("CLOSE_PROJECT");

  private Symbol reasonForPrompt;

  public ProjectPromptDialog (Frame frame, String title, boolean isModal,
			      String prompt, Symbol reasonForPrompt, StandardDialogClient client) {  
    super (frame, title, isModal, prompt, client);
    this.reasonForPrompt = reasonForPrompt;
  }

  public Symbol getReasonForPrompt() {
    return reasonForPrompt;
  }

}
