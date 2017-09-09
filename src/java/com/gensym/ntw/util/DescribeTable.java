/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 DescribeTable.java
 *
 */
package com.gensym.ntw.util;

import java.awt.Font;
import java.awt.Component;
import java.awt.event.MouseListener;
import java.util.Enumeration;
import javax.swing.JComponent;
import javax.swing.border.EmptyBorder;
import javax.swing.JTable;
import javax.swing.event.ListSelectionListener;
import com.gensym.classes.Item;
import com.gensym.classes.ImplAccess;
import com.gensym.jgi.G2AccessException;
import com.gensym.message.Trace;
import com.gensym.ntw.TwAccess;
import com.gensym.ntw.util.ShortItemCommands;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.uitools.tables.ItemTableModel;
import com.gensym.uitools.tables.ItemTableInputHandler;
import com.gensym.uitools.utils.JExplorerTableCellRenderer;


/**
 * A class that produces a table with the item description
 * of the specified G2 Item. This class uses the
 * {@link com.gensym.uitools.tables.ItemTableModel} as the table
 * Model, and the {@link com.gensym.uitools.utils.JExplorerTableCellRenderer}
 * as the cell renderer. This table must be inserted directly into a
 * {@link javax.swing.JScrollPane} to operate correctly.
 */

public class DescribeTable extends JTable {

  private static Font theFont = new Font("sansserif", Font.PLAIN, 11);
  private static Font theBoldFont = new Font("sansserif", Font.BOLD, 11);
  private static EmptyBorder noBorder = new EmptyBorder(0,0,0,0);
  private static EmptyBorder leftBorder = new EmptyBorder(0,10,0,0);  
  private ItemTableModel tableModel;
  private static final Symbol G2_GET_DESCRIPTION_OF_ITEM_ = Symbol.intern
      ("G2-GET-DESCRIPTION-OF-ITEM");
  private static final Symbol TABLE_HEADER_ = Symbol.intern("TABLE-HEADER");
  
/**
 * The constructor for the class.
 * @param {@link com.gensym.classes.Item} the G2 Item for which
 * the description is displayed
 */
  public DescribeTable(Item item) {
    super();
    //create the table, adding the model
    tableModel = new ItemTableModel();
    tableModel.addColumn (TABLE_HEADER_);
    setTableHeader(null);
    setShowGrid(false);
    setIntercellSpacing(new java.awt.Dimension(0,0));
    setRowHeight(20);

    //populate the table
    if (item == null) return;
    try{ 
      getItemDescription(item);
    } catch (G2AccessException gae){
      Trace.exception (gae);
    }
    //render the table
    setModel(tableModel);
    TableCellRenderer cellRenderer = new TableCellRenderer(tableModel);
    setDefaultRenderer(Object.class, cellRenderer);

    //add listeners
    ShortItemCommands shortItemCommands = new ShortItemCommands();
    shortItemCommands.setModel(tableModel);
    ItemTableInputHandler inputHandler =
      new ItemTableInputHandler(this, shortItemCommands);
    getSelectionModel().addListSelectionListener((ListSelectionListener)inputHandler);
    addMouseListener(inputHandler);
  }
  
/**
 * This method populates the JTable with Item descriptions,
 * uses {@link com.gensym.uitools.tables.ItemTableModel} as the
 * table model, and {@link com.gensym.uitools.tables.ItemTableInputHandler}
 * as the table mouse listener
 */
  private void getItemDescription(Item item) throws G2AccessException {
    
    if (item == null) return;
    
    TwAccess context = (TwAccess)((ImplAccess)item).getContext();
    Sequence description = (Sequence)context.callRPC(G2_GET_DESCRIPTION_OF_ITEM_,
						     new Object[] {item});
    Enumeration e = description.elements();
    while(e.hasMoreElements()) {
      Object elt = e.nextElement();
      if (elt instanceof String)
	tableModel.addLabel((String)(elt));
	
      else tableModel.addRow((Item)(elt));
    }
  }


  class TableCellRenderer extends JExplorerTableCellRenderer
  {
    private ItemTableModel model;
    TableCellRenderer(ItemTableModel model) {
      super(model);
      this.model = model;
    }
    void setModel(ItemTableModel model) {
      this.model = model;
      setJTableIconFactory(model);
    }
    @Override
    public Component getTableCellRendererComponent(JTable table,
						   Object value,
						   boolean isSelected,
						   boolean hasFocus,
						   int row,
						   int column){
      JComponent component = (JComponent)
	super.getTableCellRendererComponent(table,
					    value,
					    isSelected,
					    hasFocus,
					    row,
					    column);
      if (model != null && model.getRow(row) == null) {
	component.setFont(theBoldFont);
	component.setBorder(noBorder);
      } else {
	component.setBorder(leftBorder);
	component.setFont(theFont);
      }
      return component;
    }
  }
  

    
}


  
  
  
