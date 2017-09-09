package com.gensym.uitools.inspect;

import com.gensym.ui.AbstractCommand;
import com.gensym.ui.CommandInformation;
import com.gensym.classes.Item;
import com.gensym.classes.KbWorkspace;
import com.gensym.classes.ImplAccess;
import com.gensym.dlgruntime.ResourceInstantiationException;
import java.net.MalformedURLException;
import com.gensym.ntw.TwAccess;
import com.gensym.jgi.G2AccessException;
import com.gensym.message.Trace;
import java.awt.event.ActionEvent;
import com.gensym.util.Symbol;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import java.util.Enumeration;
import com.gensym.dlg.ErrorDialog;
import com.gensym.uitools.tables.ItemTableModel;
import java.util.Hashtable;
import java.awt.Window;

public class InspectItemCommands extends AbstractCommand
{
  private Item[] selection;
  public static final String PROPERTIES = "Properties";
  public static final String GO_TO = "GoTo";
  public static final String HIDE = "Hide";
  private static final String shortResource = "InspectItemCommandsShortResource";
  private static final String longResource = "InspectItemCommandsLongResource";
  private static final Symbol ITEM_ = Symbol.intern("ITEM");
  private static final Symbol GO_TO_ITEM_ = Symbol.intern("GO-TO-ITEM");
  protected static final int WKSP = 0;
  protected static final int ITEM = 1;
  private ItemTableModel model;
  private Window window;

  public InspectItemCommands() {
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
			       null, null, true)});
    setSelection(null);
  }

  public void setModel(ItemTableModel model) {
    this.model = model;
  }

  public void setWindow(Window window) {
    this.window = window;
  }
  private Hashtable selectionContainments=new Hashtable();;
  public void setSelection(Item[] items) {
    selectionContainments.clear();
    this.selection = items;
    int count = 0;
    if (items != null)
      count = items.length;
    boolean available = count > 0;
    setAvailable(GO_TO, available);
    setAvailable(HIDE, available);
    setAvailable(PROPERTIES, available);
    if (items == null) return;
    for (int i=0;i<count;i++) {
      try {
	Item item = items[i];

        boolean isItemPrivate = false;
        if ((item != null)&& (com.gensym.core.GensymApplication.getApplication()!= null))
          isItemPrivate = com.gensym.core.GensymApplication.getApplication().checkIfPrivate(item, false);

	if (item == null || isItemPrivate == true) {
	  setAvailable(GO_TO, false);
	  setAvailable(PROPERTIES, false);
	  return;
	}
	Item[] selectionContainment = getWorkspaceAndItemOnWksp(item);
	if (selectionContainment == null) {
	  setAvailable(GO_TO, false);
	  selectionContainments.clear();
	  return;
	}
	selectionContainments.put(item, selectionContainment);
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
	context.getDialogManager().editItem(window, item,
					    context.getUserMode (),
					    java.util.Locale.getDefault ());
      } catch (ResourceInstantiationException rie) {
	Trace.exception(rie);
      } catch (MalformedURLException murle) {
	Trace.exception(murle);
      }
    } else if (HIDE.equals(cmdKey)) {
      if (model != null && item != null) {
	model.removeRow(item);
	model.update();
      }
    } else if (GO_TO.equals(cmdKey)) {
      Item[] items = (Item[])selectionContainments.get(item);
      goToItem((Item)items[ITEM], (KbWorkspace)items[WKSP]);
    }
  }

  @Override
  public void actionPerformed(ActionEvent e){
    String cmdKey = e.getActionCommand();
    for (int i=0;i<selection.length;i++) {
      try {
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
       throws G2AccessException
  {
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
