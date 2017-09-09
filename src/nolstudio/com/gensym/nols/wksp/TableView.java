package com.gensym.nols.wksp;

import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.net.URL;
import java.util.*;

import javax.swing.text.*;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.border.*;

public class TableView  extends JScrollPane implements TableModelListener{

	private TableRowHeader rowHeader;
	private TableColumnHeader columnHeader;
	private TableCellPane cellPane;
	private int defaultRowNumber;
	private int defaultColumnNumber;
	private ScollBarListener scrollbarListener;
	private JLabel positionDisp;
	private NolInternalFrame holder;

	public TableView (NolInternalFrame holder, TableDataModel dataModel){
		super();
		this.holder = holder;
		int row = dataModel.getNumberOfRows();
		int column = dataModel.getNumberOfColumns();
		defaultRowNumber = 20;
		defaultRowNumber = 5;
		if(row<defaultRowNumber) {
			row = defaultRowNumber;
		}
		if(column<defaultColumnNumber) {
			column = defaultColumnNumber;
		}

		rowHeader  = new TableRowHeader("", this,dataModel);
		columnHeader  = new TableColumnHeader("",this,dataModel);
		cellPane  = new TableCellPane("",this,dataModel);
		cellPane.addMouseListener(holder);
		positionDisp = new JLabel("");
		dataModel.addTableDataEventListener(cellPane);
		dataModel.addTableDataEventListener(rowHeader);
		dataModel.addTableDataEventListener(columnHeader);
		setViewportView(cellPane);
		setRowHeaderView(rowHeader);
		setColumnHeaderView(columnHeader);
		setCorner(ScrollPaneConstants.LOWER_LEFT_CORNER,positionDisp);
		JScrollBar hbar = getHorizontalScrollBar();
		JScrollBar vbar = getVerticalScrollBar();
		scrollbarListener = new ScollBarListener();
		hbar.addAdjustmentListener(scrollbarListener);
		vbar.addAdjustmentListener(scrollbarListener);
//		hbar.setUnitIncrement(10);
//		vbar.setUnitIncrement(20);
//		hbar.setBlockIncrement(100);
//		vbar.setBlockIncrement(100);
//		vbar = getVerticalScrollBar();
//		System.out.println("v p="+vbar.getUnitIncrement());
//		System.out.println("h p="+hbar.getUnitIncrement());

//		setCorner(LOWER_LEFT_CORNER, cornerLL);
//		setCorner(LOWER_RIGHT_CORNER, cornerLR);
//		setCorner(UPPER_LEFT_CORNER, cornerUL);
//		setCorner(UPPER_RIGHT_CORNER, cornerUR);
	}

	@Override
	public void tableDataChanged(TableDataEvent e) {
//		System.out.println("e.id=" +e.getID());
	}

	public void setWidth(int width){
		columnHeader.setWidth(width);
		cellPane.setWidth(width);
	}

	class ScollBarListener implements AdjustmentListener{
		private int vValue = 0;
		private int vValue1 = 0;
		private int hValue = 0;

		@Override
		public void adjustmentValueChanged(AdjustmentEvent e){
			if(e.getAdjustable() instanceof JScrollBar){
				JScrollBar bar = (JScrollBar)e.getAdjustable();
				if(bar.getOrientation() == 0){
//					 System.out.println("h va="+e.getValue());
//					 System.out.println("h ty="+e.getAdjustmentType());
					 int cValue = e.getValue();
					 if(cValue==hValue) {
						 return;
					 }
					 if((cValue-hValue) == 1){
						 hValue = cValue+119;
						 if(hValue>bar.getMaximum()) {
							 hValue = bar.getMaximum(); 
						 }
						 bar.setValue(hValue);
					 }else if((hValue-cValue) ==1){
						 hValue = cValue-119;
						 if(hValue<0){
							 hValue = 0; 
						 }
						 bar.setValue(hValue);
					 }else{
						 hValue = cValue;
					 }
				}else if(bar.getOrientation() == 1){
					 int cValue = e.getValue();
//					 System.out.println("ver va1="+cValue);
//					 System.out.println("ver va2="+vValue1);
//					 System.out.println("ver va3="+vValue);
					 if(cValue==vValue) {
						 return;
					 }
					 if((cValue-vValue) == 1){
						 vValue = cValue+19;
						 bar.setValue(vValue);
					 }else if((vValue-cValue)==1 || Math.abs(vValue1-cValue)==1){
						 vValue = cValue-19;
						 if(vValue<0) {
							 vValue = 0; 
						 }
						 bar.setValue(vValue);
					 }else{
						 vValue = ((cValue+19)/20)*20;
						 bar.setValue(vValue);
					 }
					 vValue1 = cValue;
				}
			}
		}
	}
}
