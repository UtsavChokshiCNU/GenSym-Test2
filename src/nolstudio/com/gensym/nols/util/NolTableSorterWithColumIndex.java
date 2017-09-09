package com.gensym.nols.util;
/**
 * A sorter for TableModels. The sorter has a model (conforming to TableModel) 
 * and itself implements TableModel. TableSorter does not store or copy 
 * the data in the TableModel, instead it maintains an array of 
 * integers which it keeps the same size as the number of rows in its 
 * model. When the model changes it notifies the sorter that something 
 * has changed eg. "rowsAdded" so that its internal array of integers 
 * can be reallocated. As requests are made of the sorter (like 
 * getValueAt(row, col) it redirects them to its model via the mapping 
 * array. That way the TableSorter appears to hold another copy of the table 
 * with the rows in a different order. The sorting algorthm used is stable 
 * which means that it does not move around rows when its comparison 
 * function returns 0 to denote that they are equivalent. 
 *
 * @version 1.5 12/17/97
 * @author Philip Milne
 */

import java.util.*;

import javax.swing.table.TableModel;
import javax.swing.event.TableModelEvent;

// Imports for picking up mouse events from the JTable. 

import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.InputEvent;
import javax.swing.JTable;
import javax.swing.table.*;

public class NolTableSorterWithColumIndex extends TableSorter {
	protected int sortingColumnIndex = -1;
    public NolTableSorterWithColumIndex() {
		super();
        indexes = new int[0]; // for consistency
    }

    public NolTableSorterWithColumIndex(TableModel model) {
		super(model);
    }

	private void setSortingColumnIndex(int c){
		sortingColumnIndex = c;
		if( model instanceof NolSortingTableModel){
			((NolSortingTableModel)model).setSortingColumnIndex(c);
			((NolSortingTableModel)model).setSortingAscending(ascending);
		}
	}


    // There is no-where else to put this. 
    // Add a mouse listener to the Table to trigger a table sort 
    // when a column heading is clicked in the JTable. 
    @Override
    public void addMouseListenerToHeaderInTable(JTable table) { 
        final NolTableSorterWithColumIndex sorter = this; 
        final JTable tableView = table; 
        tableView.setColumnSelectionAllowed(false); 
        MouseAdapter listMouseListener = new MouseAdapter() {
            @Override
			public void mouseClicked(MouseEvent e) {
                TableColumnModel columnModel = tableView.getColumnModel();
                int viewColumn = columnModel.getColumnIndexAtX(e.getX()); 
                int column = tableView.convertColumnIndexToModel(viewColumn); 
                if (e.getClickCount() == 1 && column != -1) {
                    //System.out.println("Sorting ..."); 
//                    int shiftPressed = e.getModifiers()&InputEvent.SHIFT_MASK; 
 //                   boolean ascending = (shiftPressed == 0); 
					ascending = !ascending;
                    sorter.sortByColumn(column, ascending); 
					setSortingColumnIndex(column);

					TableModel tm = tableView.getModel(); 
					int count = tm.getColumnCount();
					for (int i=0;i<count;i++){
						TableColumn tc = tableView.getColumnModel().getColumn(i);
						tc.setHeaderValue(tm.getColumnName(i));
						tc.setPreferredWidth(tc.getPreferredWidth());
					}
					tableView.getTableHeader().resizeAndRepaint();
                }
            }
        };
        JTableHeader th = tableView.getTableHeader(); 
        th.addMouseListener(listMouseListener); 
    }
}
