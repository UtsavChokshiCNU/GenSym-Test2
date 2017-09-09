package com.gensym.ntw.util;

import java.awt.Window;
import java.awt.event.ActionEvent;
import com.gensym.dlg.QuestionDialog;
import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.StandardDialogClient;
import com.gensym.message.Resource;
import com.gensym.ui.AbstractCommand;
import com.gensym.ui.CommandInformation;

class ClearCommand extends AbstractCommand {

  protected static final String shortResource = "CommandShortResource";
  protected static final String longResource = "CommandLongResource";
  protected static Resource i18n = Resource.getBundle("com/gensym/ntw/util/CommandShortResource");

  protected KbMessageTableView msgTableView;
  protected static TableView tableView;
  private boolean promptBeforeClear = false;
  private static final String CLEAR = "Clear";
  
  ClearCommand(KbMessageTableView msgTableView) {
    super(new CommandInformation[]
      {new CommandInformation(CLEAR, true, shortResource, longResource,
			      "clearimage.gif", null, null, true)});
    this.msgTableView = msgTableView;
    tableView = msgTableView.getTableView();
    setAvailable(CLEAR, true);
  }

  void setPromptBeforeClear(boolean prompt) {
    promptBeforeClear = prompt;
  }

  @Override
  public void actionPerformed(ActionEvent event) {
    if (promptBeforeClear) 
      new YesNoDialog(msgTableView, msgTableView.getParentWindow(),
		      i18n.getString("ClearTableQuestion")).setVisible(true);
    else
      doClear();
  }

  private static void doClear() {
    tableView.clear();
  }

  class YesNoDialog extends QuestionDialog{
    private Window centerWindow;

    YesNoDialog(KbMessageTableView msgTableView, Window centerWindow, String message){
      super(msgTableView.getParentFrame(centerWindow), msgTableView.getParentFrame(centerWindow).getTitle(), 
	    true, new String[]{YES_LABEL, NO_LABEL}, 
            new int[]{YES, NO}, message, null, new DialogClient());
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
  
  static class DialogClient implements StandardDialogClient{
    @Override
    public void dialogDismissed(StandardDialog dlg, int btnCode){
      if (btnCode == dlg.YES)
	doClear();
    }
  }
}
