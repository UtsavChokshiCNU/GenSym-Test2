package com.gensym.uitools.inspect;

import com.gensym.uitools.tables.ItemTableModel;
import com.gensym.util.Symbol;
import java.awt.event.ActionListener;
import com.gensym.message.Resource; 
import java.awt.event.ActionEvent;
import com.gensym.dlg.ErrorDialog;
import com.gensym.ntw.TwAccess;
import java.awt.BorderLayout;
import java.awt.Point;
import javax.swing.JPanel;
import java.awt.event.MouseListener;

import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import com.gensym.ui.menu.CPopupMenu;
import com.gensym.ui.RepresentationConstraints;
import javax.swing.SwingConstants;
import com.gensym.message.Trace;
import com.gensym.classes.Item;
import com.gensym.jgi.G2AccessException;
import javax.swing.JTable;
import java.awt.Window;
import java.awt.Frame;
import java.awt.Font;
import java.awt.Insets;
import java.awt.Dialog;

import com.gensym.ui.RepresentationConstraints;
import javax.swing.SwingConstants;
import com.gensym.ui.menu.CMenu;
import com.gensym.ui.menu.CMenuBar;
import com.gensym.jgi.G2Access;
import javax.swing.event.ListSelectionListener;
import javax.swing.event.ListSelectionEvent;
import com.gensym.uitools.utils.FontUtil;

public class TableInputHandler extends MouseAdapter
implements ListSelectionListener
{
  private static Insets menuInsets = new Insets(2,0,2,0);
  private CPopupMenu popupMenu;
  private InspectItemCommands commands;
  protected JTable table;
  private RepresentationConstraints menuConstraints =
  new RepresentationConstraints(RepresentationConstraints.TEXT_AND_ICON,
				SwingConstants.LEFT, 
				SwingConstants.CENTER, 
				SwingConstants.RIGHT, 
				SwingConstants.CENTER);
  
  public TableInputHandler(JTable table, InspectItemCommands commands){
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
	Item row = model.getRow(selectedRow);
	if (row == null) {
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
    popupMenu.setInvoker(table);
    popupMenu.show(table, x+1, y+1);
  }

  @Override
  public void valueChanged(ListSelectionEvent lse) {
    int[] selectedRows = getSelectedRows();
    Item[] selectedItems = new Item[selectedRows.length];
    for (int i=0;i<selectedRows.length;i++) {
      selectedItems[i]=getModel().getRow(selectedRows[i]);
    }
    commands.setSelection(selectedItems);    
  }
}
