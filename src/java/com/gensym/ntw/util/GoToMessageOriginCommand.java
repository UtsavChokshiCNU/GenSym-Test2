/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 GoToMessageOriginCommand.java
 *
 */

package com.gensym.ntw.util;

import java.awt.event.ActionEvent;
import com.gensym.ui.CommandInformation;
import com.gensym.jgi.G2Access;
import com.gensym.jgi.G2AccessException;
import com.gensym.util.Symbol;
import com.gensym.dlg.WarningDialog;
import com.gensym.message.Trace;
import com.gensym.classes.Message;
import com.gensym.classes.Item;
import com.gensym.classes.ImplAccess;

class GoToMessageOriginCommand extends GoToItemCommand{

  private static final String GO_TO_MESSAGE_ORIGIN = "GoToMessageOrigin";
  private static final Symbol G2_GET_ORIGIN_OF_MESSAGE_ = Symbol.intern("G2-GET-ORIGIN-OF-MESSAGE");

  GoToMessageOriginCommand(KbMessageTableView msgTableView){
    super(new CommandInformation[]{
      new CommandInformation(GO_TO_MESSAGE_ORIGIN, true, shortResource, longResource, "goto.gif", 
			     null, null, true)},
      msgTableView);
  }

  @Override
  public void actionPerformed(ActionEvent event){
    int selectedRow = table.getSelectedRow();
    if (selectedRow == -1) return;
    TableViewMessage viewMsg = tableView.getTableViewMessage(selectedRow);
    if (viewMsg instanceof KbMessage){
      Message message = ((KbMessage)viewMsg).getMessage();
      try{
	G2Access cxn = ((ImplAccess)message).getContext();
	Item item = (Item)cxn.callRPC(G2_GET_ORIGIN_OF_MESSAGE_, new java.lang.Object[] {message});
	goToItem(item);
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

}
