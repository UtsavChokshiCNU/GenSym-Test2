/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 GoToItemCommand.java
 *
 */

package com.gensym.ntw.util;

import java.awt.Frame;
import java.util.Enumeration;
import com.gensym.ui.CommandInformation;
import com.gensym.jgi.G2AccessException;
import com.gensym.dlg.WarningDialog;
import com.gensym.util.Symbol;
import com.gensym.util.Sequence;
import com.gensym.util.Structure;
import com.gensym.classes.Item;
import com.gensym.classes.KbWorkspace;

abstract class GoToItemCommand extends SingleSelectionCommand{

  private static final Symbol ITEM_ = Symbol.intern("ITEM");
  private static final Symbol GO_TO_ITEM_ = Symbol.intern("GO-TO-ITEM");

  protected static final int WKSP = 0;
  protected static final int ITEM = 1;

  GoToItemCommand(CommandInformation[] info, KbMessageTableView msgTableView){
    super(info, msgTableView);
  }

  protected void goToItem(Item item) throws G2AccessException{
    Item[] items = getWorkspaceAndItemOnWksp(item);
    goToItem((Item)items[ITEM], (KbWorkspace)items[WKSP]);
  }
  
  //Assumes item is actually on the wksp
  protected void goToItem(Item item, KbWorkspace wksp) throws G2AccessException{
    if (wksp != null){
      Structure particulars = new Structure();
      particulars.setAttributeValue(ITEM_, item);
      particulars.setAttributeValue(GO_TO_ITEM_, new Boolean(true));
      wksp.show(particulars);
    }
    else{
      Frame frame = msgTableView.getParentFrame(msgTableView.getParentWindow());
      new CenteredWarningDialog(msgTableView, msgTableView.getParentWindow(),
				frame.getTitle(), true, 
				i18n.getString("ItemIsNotOnWksp"), 
				null).setVisible(true);
    }
  }

  protected Item[] getWorkspaceAndItemOnWksp(Item item) throws G2AccessException{
    Sequence containment = item.getContainmentHierarchy();
    Enumeration items = containment.elements();
    Item itemOnWksp = item;
    while (items.hasMoreElements()){
      Item itm = (Item)items.nextElement();
      if (itm instanceof KbWorkspace){
	Item[] itms = new Item[2];
	itms[WKSP] = itm;
	itms[ITEM] = itemOnWksp;
	return itms;
      }
      else itemOnWksp = itm;
    }
    return null;
  }
}

