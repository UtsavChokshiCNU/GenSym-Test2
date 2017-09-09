/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 DeleteCommand.java
 *
 */

package com.gensym.ntw.util;

import java.awt.Frame;
import java.awt.Window;
import java.awt.Toolkit;
import java.awt.Image;
import java.awt.event.ActionEvent;
import javax.swing.JTable;
import javax.swing.event.ListSelectionListener;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.TableModelListener;
import javax.swing.event.TableModelEvent;
import com.gensym.ui.AbstractCommand;
import com.gensym.ui.CommandInformation;
import com.gensym.jgi.G2AccessException;
import com.gensym.dlg.WarningDialog;
import com.gensym.dlg.QuestionDialog;
import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.StandardDialogClient;
import com.gensym.message.Trace;
import com.gensym.classes.Message;

/* This class is used to delete messages from the message board.  
   Not to be confused with deleting items from workspaces. 
   That would be found in com/gensym/shell/commands/ItemCommands.java */

class DeleteCommand extends MultiSelectionCommand{

  private static Image image;
  private static final Class thisClass = com.gensym.dlg.QuestionDialog.class;

  static {
    image =  Toolkit.getDefaultToolkit ().getImage (thisClass.getResource ("question.gif"));
  }

  private static final String DELETE = "Delete";
  private boolean promptBeforeDelete = false;
  private int[] selectedRows;

  DeleteCommand(KbMessageTableView msgTableView){
    super(new CommandInformation[]{
      new CommandInformation(DELETE, true, shortResource, longResource, "delete.gif", 
			     null, null, true)},
      msgTableView);
  }

  void setPromptBeforeDelete(boolean prompt){
    promptBeforeDelete = prompt;
  }

  @Override
  public void actionPerformed(ActionEvent event){
    selectedRows = table.getSelectedRows();
    if (selectedRows == null) return;
    if (promptBeforeDelete){
      String message;
      if (selectedRows.length == 1)
	message = i18n.getString("DeleteRowQuestion");
      else
	message = i18n.getString("DeleteRowsQuestion");
      new YesNoDialog(msgTableView, msgTableView.getParentWindow(), message).setVisible(true);
    }
    else
      doDelete();
    selectedRows = null;
  }

  private void doDelete(){
    table.clearSelection();
    for (int i=selectedRows.length - 1; i>=0; i--){
      TableViewMessage viewMsg = tableView.getTableViewMessage(selectedRows[i]);
      tableView.removeTableViewMessage(viewMsg);
      if (viewMsg instanceof KbMessage){
	Message message = ((KbMessage)viewMsg).getMessage();
	try{
	  message.delete(true, true);
	}
	catch(G2AccessException ex){
	  Trace.exception(ex);
	  new CenteredWarningDialog(msgTableView, msgTableView.getParentWindow(),
				    i18n.getString("ErrorTitle"), true, 
				    i18n.format("CommunicationError", ex.toString()), 
				    null).setVisible(true);
	}
      }
    }
    updateAvailability();
  }

  class YesNoDialog extends QuestionDialog{
    private Window centerWindow;

    YesNoDialog(KbMessageTableView msgTableView, Window centerWindow, String message){
      super(msgTableView.getParentFrame(centerWindow), msgTableView.getParentFrame(centerWindow).getTitle(), 
	    true, new String[]{YES_LABEL, NO_LABEL}, 
            new int[]{YES, NO}, message, image, null);
      setClient (new DialogClient());
      this.centerWindow = centerWindow;
      setDefaultButton(YES);
    }

    @Override
    public void setVisible(boolean visible){
      if (visible)
	WindowUtil.centerFrame (centerWindow, this);
      show();
    }
  }

  class DialogClient implements StandardDialogClient{
    @Override
    public void dialogDismissed(StandardDialog dlg, int btnCode){
      if (btnCode == dlg.YES)
	doDelete();
    }
  }
}
