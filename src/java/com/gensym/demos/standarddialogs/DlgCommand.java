/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 DlgCommand.java
 *
 */
package com.gensym.demos.standarddialogs;

import java.awt.Component;
import java.awt.Panel;
import java.awt.event.ActionEvent;
import java.util.Vector;
import com.gensym.dlg.CommandConstants;
import com.gensym.dlg.ErrorDialog;
import com.gensym.dlg.InputDialog;
import com.gensym.dlg.MessageDialog;
import com.gensym.dlg.QuestionDialog;
import com.gensym.dlg.SelectionDialog;
import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.StandardDialogClient;
import com.gensym.dlg.WarningDialog;
import com.gensym.mdi.MDIFrame;
import com.gensym.ui.AbstractStructuredCommand;
import com.gensym.ui.CommandInformation;
import com.gensym.ui.CommandGroupInformation;
import com.gensym.ui.StructuredCommandInformation;
import com.gensym.util.Structure;
import com.gensym.util.Symbol;

/**
 * DlgCommand demonstrates how to use many of the dialogs in com.gensym.dlg.
 * It provides examples for the following dialogs:<p>
 * <ul>
 * <li> ErrorDialog
 * <li> MessageDialog
 * <li> QuestionDialog
 * <li> WarningDialog
 * <li> InputDialog
 * <li> SelectionDialog
 * </ul>
 * <p>
 * To run the demo for DlgCommand, type: <p><p>
 * java com.gensym.demos.standarddialogs.DlgTestApp
 */
public class DlgCommand extends AbstractStructuredCommand implements StandardDialogClient, CommandConstants {
  private static final String ERROR_DIALOG = "ErrorDialog";
  private static final String MESSAGE_DIALOG = "MessageDialog";
  private static final String QUESTION_DIALOG = "QuestionDialog";
  private static final String WARNING_DIALOG = "WarningDialog";
  private static final String INPUT_DIALOG = "InputDialog";
  private static final String SELECTION_DIALOG = "SelectionDialog";
  private static final String EXIT_APP = "ExitApp";

  private static final String shortResource = "CommandShortResource";
  private static final String longResource = "CommandLongResource";

  private MDIFrame appFrame = null;

  private static ErrorDialog errorDialog;
  private static MessageDialog messageDialog;
  private static QuestionDialog questionDialog;
  private static InputDialog inputDialog;
  private static SelectionDialog selectionDialog;
  private static WarningDialog warningDialog;

  String[] selectionDialogInitialValues  = {"Apples", "Bananas", "Grapes",
					    "Oranges", "Pears", "Peaches"};

  public DlgCommand(MDIFrame parentFrame){
    super(new StructuredCommandInformation[]{
      new CommandGroupInformation("StandardDlgs", new CommandInformation[]{
        new CommandInformation(ERROR_DIALOG, true, 
			       shortResource, longResource,
			       null, null, null, true),
	new CommandInformation(MESSAGE_DIALOG, true, 
			       shortResource, longResource,
			       null, null, null, true),
        new CommandInformation(QUESTION_DIALOG, true, 
			       shortResource, longResource,
			       null, null, null, true),
        new CommandInformation(INPUT_DIALOG, true, 
			       shortResource, longResource,
			       null, null, null, true),
        new CommandInformation(SELECTION_DIALOG, true, 
			       shortResource, longResource,
			       null, null, null, true),
        new CommandInformation(WARNING_DIALOG, true,
			       shortResource, longResource,
			       null, null, null, true)}),
	new CommandGroupInformation("UtilityDialogs", new CommandInformation[]{
	  new CommandInformation(EXIT_APP, true,
				 shortResource, longResource,
				 null, null, null, true)})});
    appFrame = parentFrame;
  }

  @Override
  public void actionPerformed(ActionEvent e){
    String cmdKey = e.getActionCommand();
    
    if (cmdKey.equals(ERROR_DIALOG))
      handleErrorDialog();
    else if (cmdKey.equals(MESSAGE_DIALOG))
      handleMessageDialog();
    else if (cmdKey.equals(QUESTION_DIALOG))
      handleQuestionDialog();
    else if (cmdKey.equals(INPUT_DIALOG))
      handleInputDialog();
    else if (cmdKey.equals(SELECTION_DIALOG))
      handleSelectionDialog();
    else if (cmdKey.equals(WARNING_DIALOG))
      handleWarningDialog();
    else if (cmdKey.equals(EXIT_APP))
      handleExitApp();
  }

  public void handleErrorDialog(){
    if (errorDialog == null){
      boolean isModal = false;
      errorDialog = new ErrorDialog(null, "Error Dialog", isModal,
				    "This is the error message!",
				    this);
    }

    errorDialog.setVisible(true);
  }

  public void handleMessageDialog(){
    if (messageDialog == null){
      boolean isModal = false;
      messageDialog = new MessageDialog (appFrame, "Message Dialog", isModal,
				         "This is a short message.", 
					 this);
      }

    messageDialog.setVisible(true);
  }

  public void handleQuestionDialog(){
    if (questionDialog == null){
      boolean isModal = false;
      questionDialog = new QuestionDialog(appFrame, "Question Dialog", isModal,
				    "Would you like to save the document before exiting?", this);
    }

    questionDialog.setVisible(true);
  }

  public void handleInputDialog(){
    if (inputDialog == null){
      String[] labels = {"This is a label:", 
			 "This is another label:", 
			 "Label:"};
      String[] initialValues = {"", "", ""};
      String[] buttonLabels = {"OK", "Cancel"};
      boolean isModal = false;
      int textFieldColumns = 30;
      inputDialog = new InputDialog (appFrame, "Input Dialog", isModal,
				     labels, initialValues, this);
      inputDialog.setInputFieldColumns (textFieldColumns);
    }

    inputDialog.setVisible (true);
  }

  public void handleSelectionDialog(){
    if (selectionDialog == null){
      boolean isModal = false;
      boolean allowMultiSelect = false;
      boolean requireSelection = false;
      int initialSelection = 2;
      selectionDialog = new SelectionDialog (appFrame, "Selection Dialog",
					     isModal, "Selection Prompt:",
					     selectionDialogInitialValues, 
					     allowMultiSelect,
					     initialSelection,
					     requireSelection, this);
    }

    selectionDialog.setVisible(true);
  }

  public void handleWarningDialog() {
    if (warningDialog == null) {
      boolean isModal = true;
      warningDialog = new WarningDialog (appFrame, "Warning Dialog", isModal,
					 "this is a warning message, beware!",
					 (StandardDialogClient) this);
    }
 
    warningDialog.setVisible(true);
  }

  public void handleExitApp(){
    closeAllDialogs();
    System.exit(0);
  }

  public void closeAllDialogs(){
    if (errorDialog != null && errorDialog.isShowing())
      errorDialog.setVisible(false);
    if (messageDialog != null && messageDialog.isShowing())
      messageDialog.setVisible(false);
    if (questionDialog != null && questionDialog.isShowing())
      questionDialog.setVisible(false);
    if (inputDialog != null && inputDialog.isShowing())
      inputDialog.setVisible(false);
    if (selectionDialog != null && selectionDialog.isShowing())
      selectionDialog.setVisible(false);
    if (warningDialog != null && warningDialog.isShowing())
      warningDialog.setVisible(false);
  }

  @Override
  public void dialogDismissed (StandardDialog dlg, int code) {
    if (dlg instanceof SelectionDialog){
      SelectionDialog sDlg = (SelectionDialog)dlg;
      int result = sDlg.getResult();
      System.out.println("Selected: "+selectionDialogInitialValues[result]);
    }
    else if (dlg instanceof InputDialog){
      InputDialog inputDlg = (InputDialog)dlg;
      String[] results = inputDlg.getResults();
      for (int i=0; i<results.length; i++)
	System.out.println ("[" + i + "]: " + results[i]);
    }
    else if (dlg instanceof QuestionDialog){
      if (code == YES)
	System.out.println("User would like to save before exiting");
      else
	System.out.println("User does not want to save before exiting");
    }
    else if (dlg instanceof MessageDialog){
      // nothing to do here since there is no follow up action
    }
    else if (dlg instanceof ErrorDialog){
      // nothing to do here since there is no follow up action
    }
    else if (dlg instanceof WarningDialog){
      // nothing to do here since there is no follow up action
    }
    else if (dlg instanceof StandardDialog){
      System.out.println("unhandled case: defaulting to StandardDialog");
    }
  }
}
