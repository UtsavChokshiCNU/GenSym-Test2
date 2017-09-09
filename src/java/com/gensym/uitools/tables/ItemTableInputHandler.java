package com.gensym.uitools.tables;

import java.awt.BorderLayout;
import java.awt.Dialog;
import java.awt.Font;
import java.awt.Frame;
import java.awt.Insets;
import java.awt.Point;
import java.awt.Window;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import javax.swing.JPanel;
import javax.swing.JTable;
import javax.swing.SwingConstants;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;

import com.gensym.classes.Item;
import com.gensym.dlg.ErrorDialog;
import com.gensym.jgi.G2Access;
import com.gensym.jgi.G2AccessException;
import com.gensym.message.Resource; 
import com.gensym.message.Trace;
import com.gensym.ntw.TwAccess;
import com.gensym.ntw.util.ShortItemCommands;
import com.gensym.ui.RepresentationConstraints;
import com.gensym.ui.menu.CMenu;
import com.gensym.ui.menu.CMenuBar;
import com.gensym.ui.menu.CPopupMenu;
import com.gensym.uitools.utils.FontUtil;
import com.gensym.uitools.tables.ItemTableModel;
import com.gensym.util.Symbol;


public class ItemTableInputHandler extends MouseAdapter
implements ListSelectionListener
{
  private static Insets menuInsets = new Insets(2,0,2,0);
  private CPopupMenu popupMenu;
  private ShortItemCommands commands;
  protected JTable table;
  private RepresentationConstraints menuConstraints =
  new RepresentationConstraints(RepresentationConstraints.TEXT_AND_ICON,
				SwingConstants.LEFT, 
				SwingConstants.CENTER, 
				SwingConstants.RIGHT, 
				SwingConstants.CENTER);
  
  public ItemTableInputHandler(JTable table, ShortItemCommands commands){
    this.commands = commands;
    this.table = table;
  }

  private CPopupMenu popup;
  private CPopupMenu createPopupMenu() {
    if (popup == null)
      popup = new CPopupMenu();
    popup.removeAll();
    popup.add(commands, menuConstraints);
    FontUtil.initMenuElement(popup, menuInsets, FontUtil.sanserifPlain11);
    return popup;
  }
  
  private void doActions(String cmdKey,
			 int[] selectedRows,
			 ItemTableModel model) {
    try {
      /*if (frame != null)
	frame.setCursor(Cursor.getPredefinedCursor(Cursor.WAIT_CURSOR));*/
      for (int i=0;i<selectedRows.length;i++) {
	int selectedRow = selectedRows[i];
	//this returns either null or Item
	Item row = model.getRow(selectedRow);
	if (row != null) {
	  try {
	    commands.doAction(cmdKey, row);
	  } catch (G2AccessException g2ae) {
	    Trace.exception(g2ae);
	  }
	}
      }
    } finally {
      /*if (frame != null)
	frame.setCursor(Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));    	*/
    }      
  }

  protected ItemTableModel getModel() {
    return (ItemTableModel)table.getModel();
  }

  protected int[] getSelectedRows() {
    return table.getSelectedRows();
  }
  
  @Override
  public void mouseClicked (MouseEvent e) {
    if (!e.isPopupTrigger() && e.getClickCount()>1) {
      doActions(commands.PROPERTIES,
		getSelectedRows(),
		getModel());
    }
  }

  @Override
  public void mouseReleased(MouseEvent e) {
    if (e.isPopupTrigger()) //intelNT
      doPopup(e);
  }
  
  @Override
  public void mousePressed(MouseEvent e) {
    if (e.isPopupTrigger())//Solaris
      doPopup(e);
  }
  
  private void doPopup(MouseEvent e) {
    int x = e.getX();
    int y = e.getY();
    int row = table.rowAtPoint(new Point(x,y));
    table.setRowSelectionInterval(row,row);
    if (popupMenu == null)
      popupMenu = createPopupMenu();
    boolean ok = true;
    
    int[] selectedRows = getSelectedRows();
    ItemTableModel model = getModel();
    for (int i=0;i<selectedRows.length&&ok;i++) 
      ok = (model.getRow(selectedRows[i]) != null);
    if (!ok) return;
    popupMenu.setInvoker(table);
    popupMenu.show(table, x+1, y+1);
  }

  @Override
  public void valueChanged(ListSelectionEvent lse) {
    int[] selectedRows = getSelectedRows();
    Item[] selectedItems = new Item[selectedRows.length];
    for (int i=0;i<selectedRows.length;i++) {
      selectedItems[i]=getModel().getRow(selectedRows[i]);
      //if (getModel().getRow(selectedRows[i] == null)
    }
    commands.setSelection(selectedItems);    
  }
}
