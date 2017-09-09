/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 GoToReferencedItemCommand.java
 *
 */

package com.gensym.ntw.util;

import java.awt.Window;
import java.util.Enumeration;
import java.awt.event.ActionEvent;
import com.gensym.ui.CommandInformation;
import com.gensym.jgi.G2Access;
import com.gensym.jgi.G2AccessException;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.dlg.SelectionDialog;
import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.StandardDialogClient;
import com.gensym.dlg.WarningDialog;
import com.gensym.message.Trace;
import com.gensym.classes.Message;
import com.gensym.classes.Item;
import com.gensym.classes.KbWorkspace;
import com.gensym.classes.ImplAccess;

class GoToReferencedItemCommand extends GoToItemCommand{

  private static final String GO_TO_REFERENCED_ITEM = "GoToReferencedItem";
  private static final Symbol G2_NAME_FOR_ITEM_ = Symbol.intern("G2-NAME-FOR-ITEM");

  private Sequence referencedItems;
  private Sequence wksps;
  private StandardDialogClient dlgClient;

  GoToReferencedItemCommand(KbMessageTableView msgTableView){
    super(new CommandInformation[]{
      new CommandInformation(GO_TO_REFERENCED_ITEM, true, shortResource, longResource, "goto.gif", 
			     null, null, true)},
      msgTableView);
    dlgClient = new DialogClient();
    updateAvailability();
  }

  @Override
  public void actionPerformed(ActionEvent event){
    try{
      referencedItems = getReferencedItems();
      wksps = new Sequence();
      int len = referencedItems.size();
      if (len == 1)
	goToItem((Item)referencedItems.elementAt(0));
      else{
	String[] names = new String[len];
	for(int i=0; i<referencedItems.size(); i++){
	  Item item = (Item)referencedItems.elementAt(i);
	  //Since referenced items can be sub-objects, get item that is actually on a wksp
	  Item[] wkspAndItem = getWorkspaceAndItemOnWksp(item);
	  Item itemOnWksp = (Item)wkspAndItem[ITEM];
	  referencedItems.setElementAt(itemOnWksp, i);
	  wksps.addElement(wkspAndItem[WKSP]);
	  Object name = ((ImplAccess)itemOnWksp).getContext().callRPC(G2_NAME_FOR_ITEM_, 
								      new Object[]{itemOnWksp});
	  if (name instanceof Symbol)
	    names[i] = ((Symbol)name).getPrintValue();
	  else{
	    String className = itemOnWksp.getG2ClassName().getPrintValue();
	    if (className.startsWith("A") || className.startsWith("E") || className.startsWith("I") ||
		className.startsWith("O") || className.startsWith("U"))
	      names[i] = i18n.format("AnItem", className);
	    else
	      names[i] = i18n.format("AItem", className);
	  }
	}

	new CenteredSelectionDialog(msgTableView, msgTableView.getParentWindow(), 
				    i18n.getString("GoToReferencedItem"), true,
				    i18n.getString("SelectAnItem"), names,
				    false, SelectionDialog.NO_SELECTION,
				    true, dlgClient).setVisible(true);
      }
    }
    catch(G2AccessException ex){
      Trace.exception(ex);
      new CenteredWarningDialog(msgTableView, msgTableView.getParentWindow(),
				i18n.getString("ErrorTitle"), true, 
				i18n.format("CommunicationError", ex.toString()), 
				null).setVisible(true);
      referencedItems = null;
      wksps = null;
    }
    referencedItems = null;
    wksps = null;
  }

  private Sequence getReferencedItems() throws G2AccessException{
    int selectedRow = table.getSelectedRow();
    if (selectedRow == -1) return null;
    TableViewMessage viewMsg = tableView.getTableViewMessage(selectedRow);
    if (viewMsg instanceof KbMessage){
      Message message = ((KbMessage)viewMsg).getMessage();
      return message.getReferencedItems();
    }
    return null;
  }

  @Override
  protected void updateAvailability(){
    super.updateAvailability();
    if (isAvailable(GO_TO_REFERENCED_ITEM)){
      try{
	Sequence referencedItems = getReferencedItems();
	setAvailable(GO_TO_REFERENCED_ITEM, !(referencedItems == null));
      }
      catch(G2AccessException ex){
	setAvailable(GO_TO_REFERENCED_ITEM, false);
	Trace.exception(ex);
      }
    }
  }

  class CenteredSelectionDialog extends SelectionDialog{
    private Window centerWindow;

    CenteredSelectionDialog(KbMessageTableView msgTableView, Window centerWindow, 
			    String title, boolean modal,
			    String prompt, String[] initialValues, boolean allowMultipleSelection,
			    int initialSelection, boolean selectionRequired, 
			    StandardDialogClient client){
      super(msgTableView.getParentFrame(centerWindow), title, modal, prompt, initialValues, 
	    allowMultipleSelection, initialSelection, selectionRequired, client);
      //System.out.println("centerWindow="+centerWindow);
      this.centerWindow = centerWindow;
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
      if (dlg.wasCancelled()) return;
      int selection = ((SelectionDialog)dlg).getResult();
      try{
	goToItem((Item)referencedItems.elementAt(selection), (KbWorkspace)wksps.elementAt(selection));
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
