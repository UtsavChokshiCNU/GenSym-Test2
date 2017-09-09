package com.gensym.nols.wksp;

import java.awt.event.*;

import java.awt.*;

//public interface TableDataModel extends AdjustmentListener{
public interface TableDataModel{
	
	public abstract void addTableDataEventListener(TableModelListener l);
	public abstract void removeTableDataEventListener(TableModelListener l);
	public abstract void clearTableDataEventListener();
	public abstract String getColumnName(int c);
	public abstract String getRowName(int r);
	public abstract String getValueAt(int r,int c);
	public abstract Color getBackgroundColor(int r,int c);
	public abstract int getNumberOfRows();
	public abstract int getNumberOfColumns();
	public abstract void shiftSelectCell (int r, int c);
	public abstract void selectCell (int r, int c);
	public abstract void selectRow (int r);
	public abstract void selectColumn (int c);
	public abstract void selectArea(int r1, int c1,int r2, int c2);
}
