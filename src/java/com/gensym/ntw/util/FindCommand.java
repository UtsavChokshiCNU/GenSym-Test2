package com.gensym.ntw.util;

import java.awt.Window;
import java.awt.event.ActionEvent;
import javax.swing.JTable;
import com.gensym.dlg.InputDialog;
import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.StandardDialogClient;
import com.gensym.jgi.G2AccessException;
import com.gensym.message.Resource;
import com.gensym.message.Trace;
import com.gensym.ui.AbstractCommand;
import com.gensym.ui.CommandInformation;

class FindCommand extends AbstractCommand {

  protected static final String shortResource = "CommandShortResource";
  protected static final String longResource = "CommandLongResource";
  private static final int FIND_CODE = 10;
  private static final int FIND_NEXT_CODE = 1;
  protected static Resource i18n = Resource.getBundle("com/gensym/ntw/util/CommandShortResource");

  protected KbMessageTableView msgTableView;
  protected static TableView tableView;
  private static final String FIND = "Find";
  private DialogClient dialogClient;

  FindCommand(KbMessageTableView msgTableView) {
    super(new CommandInformation[]
      {new CommandInformation(FIND, true, shortResource, longResource,
			      "findimage.gif", null , null, true)});
    this.msgTableView = msgTableView;
    dialogClient = new DialogClient();
    tableView = msgTableView.getTableView();
    setAvailable(FIND, true);
  }

  @Override
  public void actionPerformed(ActionEvent event) {
    new SearchDialog(msgTableView, msgTableView.getParentWindow(), dialogClient).setVisible(true);
  }

  class SearchDialog extends InputDialog {
    private Window centerWindow;

    SearchDialog(KbMessageTableView msgTableView, Window centerWindow, DialogClient dialogClient) {
      super(msgTableView.getParentFrame(centerWindow),
	    i18n.getString("Search"), 
	    false, new String[]{i18n.getString("FindMessageContaining")}, 
            new String[]{""}, new String[]{i18n.getString(FIND),
					   i18n.getString("FindNext"),
					   i18n.getString("Dismiss")},
	    new int[]{FIND_CODE, FIND_NEXT_CODE, CANCEL}, dialogClient);
      this.centerWindow = centerWindow;
      setDefaultButton(FIND_CODE);
      setInitialFocus(0);
      setDefaultCloseOperation(DISPOSE_ON_CLOSE);
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
      JTable table = tableView.getTable();
      String message;
      String results = ((InputDialog)dlg).getResults()[0];
      int i = -1;
      try { 
	if (btnCode == FIND_CODE) {
	  for (i=0; i<table.getRowCount(); i++) {
	    message = ((KbMessage)tableView.getTableViewMessage(i)).
	      getMessage().getText();
	    if (message.indexOf(results) > -1) {
	      table.setRowSelectionInterval(i, i);
	      tableView.scrollpane.getVerticalScrollBar().
		setValue(i*table.getRowHeight());
	      break;
	    }
	  }
	}
	if (btnCode == FIND_NEXT_CODE && table.getSelectedRow() > -1) {
	  for (int j=table.getSelectedRow()+1; j<table.getRowCount(); j++) {
	    message = ((KbMessage)tableView.getTableViewMessage(j)).
	      getMessage().getText();
	    if (message.indexOf(results) > -1) {
	      table.setRowSelectionInterval(j, j);
	      tableView.scrollpane.getVerticalScrollBar().
		setValue(j*table.getRowHeight());
	      break;
	    }
	  }
	}
      } catch (G2AccessException gae) {
	Trace.exception(gae);
      }
    }
  }
}
