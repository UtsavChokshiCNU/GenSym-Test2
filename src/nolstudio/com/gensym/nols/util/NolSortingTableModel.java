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
import javax.swing.*;
import javax.swing.table.*;

public class NolSortingTableModel extends AbstractTableModel{
	private int row,col;
	protected int sortingColumnIndex = -1;
	protected boolean ascending	= false;

	public NolSortingTableModel(){
		sortingColumnIndex = -1;
	}
	public void setSortingColumnIndex(int c){
		sortingColumnIndex = c;
	}
	public void setSortingAscending(boolean a){
		ascending = a;
	}

	@Override
	public Object getValueAt(int r, int c){
		return "";
	}
	@Override
	public int getColumnCount() { return col; }
	@Override
	public int getRowCount() { return row;}
}
