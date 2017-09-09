/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ShortItemCommands.java
 *
 */
package com.gensym.ntw.util;

import java.net.MalformedURLException;
import java.awt.event.ActionEvent;
import com.gensym.ui.AbstractCommand;
import com.gensym.ui.CommandInformation;
import com.gensym.classes.Item;
import com.gensym.classes.KbWorkspace;
import com.gensym.classes.ImplAccess;
import com.gensym.dlg.StandardDialog;
import com.gensym.dlgruntime.ResourceInstantiationException;
import com.gensym.jgi.G2AccessException;
import com.gensym.message.Trace;
import com.gensym.ntw.TwAccess;
import com.gensym.ntw.util.DescribeTable;
import com.gensym.uitools.utils.WhiteBackgroundJScrollPane;
import com.gensym.util.Symbol;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import java.util.Enumeration;
import com.gensym.dlg.ErrorDialog;
import com.gensym.uitools.tables.ItemTableModel;

public class ShortItemCommands extends AbstractCommand
{
  private Item[] selection;
  public static final String PROPERTIES = "Properties";
  public static final String GO_TO = "GoTo";
  public static final String HIDE = "Hide";
  public static final String DESCRIBE = "Describe";
  private static final String shortResource = "CommandShortResource";
  private static final String longResource = "CommandLongResource";
  private static final Symbol ITEM_ = Symbol.intern("ITEM");
  private static final Symbol GO_TO_ITEM_ = Symbol.intern("GO-TO-ITEM");
  private static final Symbol G2_GET_DESCRIPTION_OF_ITEM_ = Symbol.intern
  ("G2_GET-DESCRIPTION-OF-ITEM");
  protected static final int WKSP = 0;
  protected static final int ITEM = 1;
  private ItemTableModel model;

  public ShortItemCommands() {
    super(new CommandInformation[]{
      new CommandInformation(GO_TO, true,
			     shortResource, longResource,
			     "goto.gif",
			     null, null, true),
	new CommandInformation(HIDE, true,
			       shortResource, longResource,
			       "delete.gif",
			       null, null, true),
	new CommandInformation(PROPERTIES, true,
			       shortResource, longResource,
			       "properties.gif",
			       null, null, true),
	new CommandInformation(DESCRIBE, true,
			       shortResource, longResource,
			       "describe.gif",
			       null, null, true)});
  }

  public void setModel(ItemTableModel model) {
    this.model = model;
  }

  public void setSelection(Item[] items) {
    this.selection = items;
    boolean available = items != null && items.length > 0;
    setAvailable(GO_TO, available);
    setAvailable(HIDE, available);
    setAvailable(PROPERTIES, available);
    setAvailable(DESCRIBE, available);
    for (int i=0;i<items.length;i++) {
      try {
	Item item = items[i];
        //Managing accessibility based on context to avoid that user
        //that doesn't have the correct privilege can go to, describe or
        //show the properties of private items
        boolean isItemPrivate = false;
        if ((item != null)&& (com.gensym.core.GensymApplication.getApplication()!= null))
          isItemPrivate = com.gensym.core.GensymApplication.getApplication().checkIfPrivate(item, false);

	if (isItemPrivate == true) {
          setAvailable(GO_TO, false);
          setAvailable(PROPERTIES, false);
          setAvailable(DESCRIBE, false);
        }

	if (getWorkspaceAndItemOnWksp(item) == null)
	  setAvailable(GO_TO, false);
      } catch(G2AccessException g2ae) {
	Trace.exception(g2ae);
	setAvailable(GO_TO, false);
	return;
      }
    }
  }

  public void doAction(String cmdKey,
		       Item item)
       throws G2AccessException
  {
    if (PROPERTIES.equals(cmdKey)) {
      TwAccess context = (TwAccess) ((ImplAccess)item).getContext ();
      try {
	context.getDialogManager().editItem(item,
					    context.getUserMode (),
					    java.util.Locale.getDefault ());
      } catch (ResourceInstantiationException rie) {
	Trace.exception(rie);
      } catch (MalformedURLException murle) {
	Trace.exception(murle);
      }
    } else if (HIDE.equals(cmdKey)) {
      if (model != null) {
	model.removeRow(item);
	model.update();
      }
    } else if (GO_TO.equals(cmdKey)) {
      Item[] items = getWorkspaceAndItemOnWksp(item);
      goToItem((Item)items[ITEM], (KbWorkspace)items[WKSP]);

    } else if (DESCRIBE.equals(cmdKey)) {
     new DescribeDlg(item).setVisible(true);

    }
  }

  @Override
  public void actionPerformed(ActionEvent e){
    String cmdKey = e.getActionCommand();
    for (int i=0;i<selection.length;i++) {
      try {
	if (selection[i] != null)
	  doAction(cmdKey, selection[i]);
      } catch (G2AccessException g2ae) {
	Trace.exception(g2ae);
      }
    }
  }

  //Assumes item is actually on the wksp
  static void goToItem(Item item, KbWorkspace wksp)
       throws G2AccessException
  {
    if (wksp != null){
      Structure particulars = new Structure();
      if (!(item instanceof com.gensym.classes.Connection)) {
	//show doesn't work well with connections(6/12/99)
	particulars.setAttributeValue(ITEM_, item);
	particulars.setAttributeValue(GO_TO_ITEM_, new Boolean(true));
      }
      wksp.show(particulars);
    }
  }

  static Item[] getWorkspaceAndItemOnWksp(Item item)
       throws G2AccessException{
    if (item == null) return null;
    Sequence containment = item.getContainmentHierarchy();
    containment.insertElementAt(item, 0);
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

class DescribeDlg extends StandardDialog {

  public static final String DLG_TITLE = "Describe Dialog";

  public DescribeDlg (Item item){
    super(null, DLG_TITLE, false,
	  new String[]{DISMISS_LABEL}, new int[]{DISMISS},
	  new WhiteBackgroundJScrollPane(new DescribeTable(item)), null);
    setSize(422, 327);
   }
}
