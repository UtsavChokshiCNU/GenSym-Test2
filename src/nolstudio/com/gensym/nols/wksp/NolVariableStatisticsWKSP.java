package com.gensym.nols.wksp;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.text.*;
import java.io.*;
import javax.swing.*;
import javax.swing.table.*;
import javax.swing.event.*;
import javax.swing.border.*;

import com.gensym.math.*;

import com.gensym.nols.util.*;
import com.gensym.nols.dlg.*;
import com.gensym.nols.data.*;
import com.gensym.nols.main.*;

import com.gensym.DEBUG;

public class NolVariableStatisticsWKSP  extends NolInternalFrame{
	private NolMainFrame frame;
	private DataSeries dataSeries;

	private	StatisticsTableModel statisticsTableModel;
	private	JTable statisticsTableView;
	private NolTableSorterWithColumIndex statisticsTableSorter;
	private Action actionListener;

    private static final String DATASERIESNAME = "VariableStatistics_DataSeriesName";
    private static final String ROW = "VariableStatistics_Row";
    private static final String MINIMUM = "VariableStatistics_Minimum";
    private static final String MAXIMUM = "VariableStatistics_Maximum";
    private static final String RANGE = "VariableStatistics_Range";
    private static final String MEAN = "VariableStatistics_Mean";
    private static final String MEDIAN = "VariableStatistics_Median";
    private static final String STDDEV = "VariableStatistics_StdDev";
    private static final String VARIANCE = "VariableStatistics_Variance";
    private static final String SKEWNESS = "VariableStatistics_Skewness";
    private static final String KURTOSIS = "VariableStatistics_Kurtosis";
    private static final String CLICKTOSORT = "VariableStatistics_ClickToSort";
	

	public NolVariableStatisticsWKSP (NolMainFrame frame, DataSeries ds){
		super(ds.getDataSource());
		this.frame = frame;
		dataSeries = ds;
		String title = "Statistics of variables in ["+ds.getDataSource().getName()+"."+
			ds.getName()+"]";
		setTitle(title);
		actionListener = new ControlAction();
		initLayout();
	}

	private void initLayout(){

		JPanel namePane = new JPanel(new GridLayout(1,4,5,5));
		namePane.setBorder(new EmptyBorder(10,20,10,20));

//		namePane.add(new JLabel("DataSeries Name:"));
		namePane.add(new JLabel(frame.getNolResourceString(DATASERIESNAME)+":"));
		namePane.add(new JLabel(dataSeries.getName()));
		namePane.add(new JLabel(frame.getNolResourceString(ROW)+":"));
		namePane.add(new JLabel(String.valueOf(dataSeries.getRow())));

		JPanel cenPane = new JPanel(new GridLayout());
  		cenPane.setBorder(new EmptyBorder(10,10,10,10));

		statisticsTableModel = new StatisticsTableModel(dataSeries);
		statisticsTableSorter = new NolTableSorterWithColumIndex(statisticsTableModel); 
		
		statisticsTableView = new JTable(statisticsTableSorter);
//		statisticsTableView = new JTable(statisticsTableModel);
		statisticsTableView.setSelectionBackground(Color.white);
		statisticsTableView.setCellSelectionEnabled(false);
		statisticsTableView.setSelectionForeground(Color.black);
		statisticsTableView.setAutoResizeMode(JTable.AUTO_RESIZE_OFF);
		statisticsTableView.getTableHeader().setToolTipText(frame.getNolResourceString(CLICKTOSORT));
		statisticsTableSorter.addMouseListenerToHeaderInTable(statisticsTableView);
		TableColumnModel cm1 = statisticsTableView.getColumnModel();
		cm1.getColumn(0).setWidth(100);

		JScrollPane listScrollPane = new JScrollPane(statisticsTableView);
		listScrollPane.setBackground(Color.white);

		cenPane.add(listScrollPane);

		getContentPane().setLayout(new BorderLayout());
		getContentPane().add("North",namePane);
		getContentPane().add("Center",cenPane);
		getContentPane().add("East",getControlPanel());
	}

	private JPanel getControlPanel(){
		JPanel control = new JPanel();
//		control.setBackground(getContentPane().getBackground());
		control.setLayout(new BoxLayout(control, BoxLayout.Y_AXIS));
		control.setBorder(new EmptyBorder(10, 10, 10, 10));

		JPanel pane0 = new JPanel(new GridLayout(1,1,5,5));
		JButton but = new JButton("Export...");
		but.setActionCommand("Export...");
		but.addActionListener(actionListener);
		pane0.add(but);

		control.add(Box.createRigidArea(NolMainFrame.vpad15));
		control.add(pane0);
		control.add(Box.createRigidArea(NolMainFrame.vpad500));
		control.add(Box.createVerticalGlue());
		return control;
	}

	public DataSeries getDataSeries(){
		return dataSeries;
	}

	class StatisticsTableModel extends NolSortingTableModel{
		private int row,col;
		private String[] colHd = {" ",
			frame.getNolResourceString(MINIMUM),
			frame.getNolResourceString(MAXIMUM),
			frame.getNolResourceString(RANGE),
			frame.getNolResourceString(MEAN),
			frame.getNolResourceString(MEDIAN),
			frame.getNolResourceString(STDDEV),
			frame.getNolResourceString(VARIANCE),
			frame.getNolResourceString(SKEWNESS),
			frame.getNolResourceString(KURTOSIS)
		};
		
		private int digits = 5;
		private DataSeries ds;
		private String[] rowHd;
		public StatisticsTableModel(DataSeries ds){
			col = 10;
			this.ds = ds;
			Vector varObjs = ds.getVarObjects();
			row = varObjs.size();
			rowHd = new String[row];
			for(int i=0;i<row;i++){
				rowHd[i] = varObjs.elementAt(i).toString();
			}
		}
		@Override
		public int getColumnCount() { return col; }
		@Override
		public int getRowCount() { return row;}
		@Override
		public Object getValueAt(int r, int c){
			if(c == 0){
				return rowHd[r];
			}else{
				Variable varObj = (Variable)ds.getVarObjects().elementAt(r);
				if(c == 1){				
					double value = varObj.getMinValue();
					return Utilities.formatDouble(value, digits);
				}else if(c == 2){				
					double value = varObj.getMaxValue();
					return Utilities.formatDouble(value, digits);
				}else if(c == 3){				
					double value = varObj.getRange();
					return Utilities.formatDouble(value, digits);
				}else if(c == 4){
					double value = varObj.getMeanValue();
					return Utilities.formatDouble(value, digits);
				}else if(c == 5){
					double value = varObj.getMedianValue();
					return Utilities.formatDouble(value, digits);
				}else if(c == 6){
					double value = varObj.getSTD();
					return Utilities.formatDouble(value, digits);
				}else if(c == 7){
					double value = varObj.getVariance();
					return Utilities.formatDouble(value, digits);
				}else if(c == 8){
					double value = varObj.getSkew();
					return Utilities.formatDouble(value, digits);
				}else if(c == 9){
					double value = varObj.getKurt();
					return Utilities.formatDouble(value, digits);
				}
			}
			return " ";
		}
		@Override
		public String getColumnName(int c) {
			if(c == sortingColumnIndex ){
				if (ascending) {
					return "+ " +colHd[c];
				}else{
					return "- " +colHd[c];
				}
			}
			return colHd[c];
		}
		@Override
		public Class getColumnClass(int c) {
			return getValueAt(0, c).getClass();
		}
		@Override
		public boolean isCellEditable(int r, int c) {
			return false;
		}
		@Override
		public void setValueAt(Object aValue, int r, int c) {
		}
	}

/** The inner control listener class.*/
    class ControlAction extends AbstractAction{
		ControlAction() {super("controlAction");}
        @Override
		public void actionPerformed(ActionEvent e) {
			String command = e.getActionCommand();
			if(command.equals("Export...")){
 				JFileChooser fileChooser = new JFileChooser();
				fileChooser.setDialogTitle("Export Variable Statistics");
				NolFileFilter filter1 = new NolFileFilter(
				new String[] {"csv"}, "ASCII Statistics File"
				);
				fileChooser.addChoosableFileFilter(filter1);
				fileChooser.setFileFilter(filter1);
				fileChooser.setDialogType(JFileChooser.SAVE_DIALOG);

				fileChooser.setSelectedFile(new File(dataSeries.getName()+".csv"));
				fileChooser.setLocation(200,200);			
				int retval = fileChooser.showSaveDialog(frame);

				fileChooser.setFileFilter(null);
				fileChooser.removeChoosableFileFilter(filter1);

				if(retval == JFileChooser.CANCEL_OPTION){
					return;
				}
				File currentPath = fileChooser.getSelectedFile();
				if(currentPath == null){
					return;
				}

				String path = currentPath.getPath();
				int dotInd = path.indexOf(".");
				if(dotInd == -1){
					path = path+".csv";
				}	
				// try to start writing
				try {
					dataSeries.writeVariableStatistics(path);
				}catch (Exception evt) {
					frame.showOKDialog("Error in writing variable statistics.");
				}
				Toolkit.getDefaultToolkit().beep();
			}
		}
	}
}

