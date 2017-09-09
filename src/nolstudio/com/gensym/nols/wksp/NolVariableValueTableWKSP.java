package com.gensym.nols.wksp;

import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.util.*;
import javax.swing.*;
import javax.swing.table.*;
import javax.swing.border.*;

import com.gensym.math.Utilities;
import com.gensym.math.MathException;
import com.gensym.math.matrix.*;

import com.gensym.nols.main.*;
import com.gensym.nols.data.*;
import com.gensym.nols.util.*;
import com.gensym.nols.dlg.*;

public class NolVariableValueTableWKSP extends NolInternalFrame {

	private NolMainFrame frame;
	private JButton exportBut;
	private ControlAction actionListener;
	private boolean noFire;

 	private	VariableValueTableModel variableValueTableModel;
	private	JTable variableValueTableView;
	private ColumnSorter valueSorter;
 	private	ThresholdTableModel thresholdTableModel;
	private	JTable thresholdTableView;

	private Matrix YP;	//To do: This should be deleted when this window is deleted. gchen 2003..4.20
	private static boolean isCalculating;
	private NolRhoModel model;
	private int[] sortColumns;
    

	public NolVariableValueTableWKSP (NolMainFrame frame, NolRhoModel model){ //for demo only
		super(frame.getProject().getRawDataSource());
		this.frame = frame;	 
		this.model = model;	 
		noFire = false;
		setTitle(model.getName()+" Output Table");
		actionListener = new ControlAction();
		YP = Matlib.createMatrix();
		int nout = model.getNout();
		sortColumns = new int[nout];
		for(int i=0;i<nout;i++){
			sortColumns[i] = i+1;
		}
		initialLayout();
		initDataDisplay();
	}

	private void initialLayout(){
		JPanel workPane = new JPanel(new BorderLayout());
		workPane.add("Center", getVarPanel());
		workPane.add("East",getControlPanel());
		setContentPane(workPane);
	}

	private JPanel getVarPanel(){
		JPanel varPane  = new JPanel(new BorderLayout());
 		varPane.setBorder(new EmptyBorder(10,10,10,10));
		
		JTextArea infoLabel = new JTextArea(frame.getNolResourceString("VariableValueTableWKSP_Info"));
		infoLabel.setEditable(false);
		infoLabel.setLineWrap(true);
		infoLabel.setWrapStyleWord(true);
		infoLabel.setBackground(varPane.getBackground());

		varPane.add("North",infoLabel);

		JPanel variableValuePane = new JPanel(new GridLayout());
		variableValueTableModel = new VariableValueTableModel(model);
		valueSorter = new ColumnSorter(variableValueTableModel,sortColumns); 

		variableValueTableView = new JTable(valueSorter);
		variableValueTableView.setSelectionMode(0);
		variableValueTableView.setCellSelectionEnabled(true);
		valueSorter.addMouseListenerToHeaderInTable(variableValueTableView);
		JScrollPane listScrollPane = new JScrollPane(variableValueTableView);
		listScrollPane.setBackground(Color.white);
		variableValuePane.add(listScrollPane);
		varPane.add("Center",variableValuePane);

		JPanel bottomPane = new JPanel(new GridLayout());
		bottomPane.setBorder(new TitledBorder(new EmptyBorder(0, 0, 0, 0),               
			frame.getNolResourceString("VariableValueTableWKSP_Threshold")+":", TitledBorder.LEFT , TitledBorder.TOP));
		thresholdTableModel = new ThresholdTableModel();
		thresholdTableView = new JTable(thresholdTableModel);
		thresholdTableView.setSelectionMode(0);
		thresholdTableView.setCellSelectionEnabled(true);
		listScrollPane = new JScrollPane(thresholdTableView);
		listScrollPane.setBackground(Color.white);
		listScrollPane.setPreferredSize(NolMainFrame.vpad40);
		bottomPane.add(listScrollPane);

		varPane.add("South",bottomPane);
		return varPane;
	}

	private JPanel getControlPanel(){
		JPanel control = new JPanel();
		control.setBackground(getContentPane().getBackground());
		control.setLayout(new BoxLayout(control, BoxLayout.Y_AXIS));
		control.setBorder(new EmptyBorder(10, 10, 10, 10));

		JPanel controlButtonPane = new JPanel(new GridLayout(1,1,5,5));
		exportBut = new JButton(frame.getNolResourceString("VariableValueTableWKSP_Export"));
		exportBut.setActionCommand("Export...");
		exportBut.addActionListener(actionListener);
 		controlButtonPane.add(exportBut);

//		JButton but = new JButton(frame.getNolResourceString("VariableValueTableWKSP_Chart"));
//		but.setActionCommand("Chart...");
//		but.addActionListener(actionListener);
// 		controlButtonPane.add(but);

		control.add(Box.createRigidArea(NolMainFrame.vpad15));
		control.add(controlButtonPane);
		control.add(Box.createRigidArea(NolMainFrame.vpad500));
		control.add(Box.createVerticalGlue());
		return control;
	}

	private void initDataDisplay(){
		noFire = true;
		Matrix X = Matlib.createMatrix();
		Matrix Y = Matlib.createMatrix();
		try{
			long[] outputTime = model.prepareTrainingSet(X, Y);
			if(outputTime == null){
				outputTime = new long[Y.getRows()];
				for(int r=0;r<outputTime.length;r++){
					outputTime[r] = (long)r*1000;
				}
			}
		} catch(MathException evt){
			System.err.println("Non-Fatal exception preparing training set: " + evt.getMessage());
			evt.printStackTrace();
		}
		calculatePredictions(X);
		Matlib.clear(X);
		Matlib.clear(Y);
		// determine whether we can show training and test subsets, models didn't store this into prior to V2.1
		variableValueTableModel.setContents(YP);
		valueSorter.setModel(variableValueTableModel,sortColumns);
		thresholdTableModel.setContents(95.0,YP.getRows());
		noFire = false;

	}

	private void calculatePredictions(Matrix X) {
		try {
			model.evaluate(X,YP);
		} catch (MathException evt) {
			System.err.println("Non-Fatal exception in calculate: " + evt.getMessage());
			evt.printStackTrace();
		}
	}

	public NolRhoModel getModel(){
		return model;
	}

   /**
     * Control action implementation
     */
    class ControlAction extends AbstractAction implements Runnable{

		private String command;
		private Object source;
		ControlAction(){super("controlAction");}
			
		@Override
		public void actionPerformed(ActionEvent e) {
			if(noFire) {
				return;
			}
			command = e.getActionCommand ();
			source = e.getSource ();
			new Thread (this).start();
		}
		
		@Override
		public void run () {
			if(command.equals("Export...")){
 				JFileChooser fileChooser = new JFileChooser();
				fileChooser.setDialogTitle("Export Output Table");
				NolFileFilter filter1 = new NolFileFilter(
					new String[] {"vot"}, "ASCII Output Table"
				);
				fileChooser.addChoosableFileFilter(filter1);
				fileChooser.setFileFilter(filter1);
				fileChooser.setDialogType(JFileChooser.SAVE_DIALOG);

				fileChooser.setSelectedFile(new File(model.getName()+".vot"));
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
				try{
					YP.writeToFile(currentPath.getPath());
				}catch(IOException evt){
					System.err.println("Non-Fatal exception: " + evt.getMessage());
					evt.printStackTrace();
				}
				Toolkit.getDefaultToolkit().beep();

			}else if(command.equals("Chart...")){
				double[] values = Matlib.create1DArray(YP);
				frame.showOutputHistogramWKSP(values, model.getName()+" output histogram");
			} 
		}
    }

	class VariableValueTableModel extends AbstractTableModel{
		private int row,col;
		private Matrix data;
		private String[] colHd = {
			"Index","Values"};
		private int digits = 5;
		public VariableValueTableModel(NolRhoModel model){
			row = 0;
			int nout = model.getNout();
			col = nout+1;
			colHd = new String[col];
			colHd[0] = "Index";
			Vector names = model.getOutputVarNames();
			for(int i=0;i<nout;i++){
				colHd[i+1] = names.elementAt(i).toString();
			}
		}
		public void setContents(Matrix data){
			this.data = data;
			row = data.getRows();
		}

		@Override
		public int getColumnCount() { return col; }
		@Override
		public int getRowCount() { return row;}
		@Override
		public Object getValueAt(int r, int c){
			if(c == 0){
				return Double.valueOf(r);
			}else{
				return data.get(r,c-1);
			}
		}
		@Override
		public Class getColumnClass(int c) {
			return getValueAt(0, c).getClass();
		}
		@Override
		public String getColumnName(int c) {
			return colHd[c];
		}
		@Override
		public boolean isCellEditable(int r, int c) {
			return false;
		}		
		@Override
		public void setValueAt(Object aValue, int r, int c) {
		}
	}

	class ThresholdTableModel extends AbstractTableModel{
		private int row,col;
		private String[] colHd = {"Percentage","Index"};
		private int digits = 5;
		private double percent = 0.0;
		private int thresholdIndex = 0;
		private int totalNumber = 0;

		public ThresholdTableModel(){
			row = 1;
			col = 2;
		}
		public void setContents(double percent, int totalNumber){
			this.percent = percent;
			this.totalNumber = totalNumber;
			thresholdIndex = (int)(totalNumber*(100.0-percent)/100.0);
		}
		@Override
		public int getColumnCount() { return col; }
		@Override
		public int getRowCount() { return row;}
		@Override
		public Object getValueAt(int r, int c){
			if(c == 0){
				return Utilities.formatDouble(percent, digits);
			}else if(c == 1){
				return thresholdIndex;
			}
			return "";
		}
		@Override
		public String getColumnName(int c) {
			return colHd[c];
		}
		@Override
		public boolean isCellEditable(int r, int c) {
			if(c==0)
				return true;
			return false;
		}		
		@Override
		public void setValueAt(Object aValue, int r, int c) {
			if(c==0){
				try{
					double v = Double.parseDouble((String)aValue);
					if(v>100.0){
						v=100.0;
					}
					if(v<0) {
						v=0.0;
					}
					percent = v;
				}catch( NumberFormatException evt){
					System.err.println("Non-Fatal exception: " + evt.getMessage());
					evt.printStackTrace();
				}
				thresholdIndex = (int)(totalNumber*(100.0-percent)/100.0);
			}
		}
	}


}

