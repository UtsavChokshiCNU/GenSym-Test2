package com.gensym.nols.dlg;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.util.zip.*;
import java.io.*;
import java.net.URL;

import javax.swing.text.*;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.table.*;
import javax.swing.border.*;

import com.gensym.math.Utilities;
import com.gensym.math.*;
import com.gensym.math.datafit.*;
import com.gensym.math.matrix.*;
import com.gensym.math.rank.*;
import com.gensym.math.stats.Stats;

import com.gensym.nols.data.*;
import com.gensym.nols.main.*;
import com.gensym.nols.util.*;

import com.gensym.DEBUG;

public class NolDataSeriesVarClassificationDialog  extends JDialog{

	private ControlAction actionListener;

	private	VarClassifyTableModel varClassifyTableModel;
	private	JTable varClassifyTableView;
	private int result;
	private NolMainFrame frame;	 

	private DataSeries dataSeries;
	private Vector varNames;
	private Vector usedVarNames;
	private Vector outVarNames;
	
    private static final String OK_BUTTON_LABEL = "OkButtonLabel";
    private static final String CANCEL_BUTTON_LABEL = "CancelButtonLabel";

	public NolDataSeriesVarClassificationDialog (NolMainFrame dw, DataSeries ds) {
		super((JFrame)dw, "Classify Data Series Variables", true);
		frame = (NolMainFrame)dw;
		result = -1;
		dataSeries = ds;
		actionListener = new ControlAction();
		varNames = new Vector();
		usedVarNames= new Vector();
		outVarNames = new Vector();
		initializeLayout();
		initDataDisplay();
	}

	private void initializeLayout(){
		JPanel classPane = new JPanel(new BorderLayout());
		JPanel infoPane = new JPanel(new GridLayout());
 		infoPane.setBorder(new EmptyBorder(10,10,10,10));
		String s = frame.getNolResourceString("DataSeries_ClassificationLabel");
		JTextArea infoLabel = new JTextArea(s);
		infoLabel.setEditable(false);
		infoLabel.setLineWrap(true);
		infoLabel.setWrapStyleWord(true);
		infoLabel.setBackground(infoPane.getBackground());
		infoPane.add(infoLabel);
		classPane.add("North",infoPane);
 	
		JPanel cenPane = new JPanel(new GridLayout());
 		cenPane.setBorder(new EmptyBorder(10,10,10,10));
		JPanel varPane = new JPanel(new GridLayout());
		varPane.setBorder(BorderFactory.createTitledBorder(frame.getNolResourceString("VariableLabel")+":"));

		varClassifyTableModel = new VarClassifyTableModel();
		varClassifyTableView = new JTable(varClassifyTableModel);
		varClassifyTableView.setDefaultRenderer(AbstractButton.class, 
			new ClassifyRenderer());
		varClassifyTableView.setSelectionMode(0);
		varClassifyTableView.setSelectionBackground(Color.white);
		varClassifyTableView.setCellSelectionEnabled(true);
		varClassifyTableView.setSelectionForeground(Color.black);
		JScrollPane listScrollPane = new JScrollPane(varClassifyTableView);
		listScrollPane.setBackground(Color.white);

		varPane.add(listScrollPane);
		cenPane.add(varPane);

		classPane.add("Center",cenPane);
	
		JPanel controlPane = new JPanel();
        controlPane.setLayout(new FlowLayout(FlowLayout.CENTER));
		JButton button1 = new JButton(frame.getNolResourceString("OkButtonLabel"));
		button1.setActionCommand("OK");
		button1.addActionListener(actionListener);
		controlPane.add(button1);
		JButton button = new JButton(frame.getNolResourceString("CancelButtonLabel"));
		button.setActionCommand("Cancel");
		button.addActionListener(actionListener);
		controlPane.add(button);
		getContentPane().setLayout(new BorderLayout());
		getContentPane().add("Center", classPane);
		getContentPane().add("South", controlPane);

	}

	private void initDataDisplay(){
		Vector varObjs = dataSeries.getVarObjects();
		varNames.removeAllElements();
		usedVarNames.removeAllElements();
		outVarNames.removeAllElements();
		for(int i=0;i<varObjs.size();i++){
			varNames.addElement(varObjs.elementAt(i).toString());
		}
		varClassifyTableModel.setNames(varNames);
		
	}

	public Vector getUsedVarNames(){
		return usedVarNames;
	}

	public Vector getOutputVarNames(){
		return outVarNames;
	}

	public int getResult(){
		return result;
	}

	private void finished(){
		Vector unusedchecks = varClassifyTableModel.getUnUsedChecks();
		Vector outputChecks = varClassifyTableModel.getOutputChecks();
		for(int i=0;i<varNames.size();i++){
			JRadioButton check = (JRadioButton)unusedchecks.elementAt(i);
			if(!check.isSelected()){
				usedVarNames.addElement(varNames.elementAt(i));
				JRadioButton outcheck = (JRadioButton)outputChecks.elementAt(i);
				if(outcheck.isSelected()){
					outVarNames.addElement(varNames.elementAt(i));
				}
			}
		}
	}

	class ControlAction extends AbstractAction {
		ControlAction() {	super("controlAction");}
        @Override
		public void actionPerformed(ActionEvent e) {
			String command = e.getActionCommand();
			if(command.equals("OK")){
				result = 1;
				finished();
				NolDataSeriesVarClassificationDialog.this.setVisible(false);
			}else if(command.equals("Cancel")){
				result = -1;
				NolDataSeriesVarClassificationDialog.this.setVisible(false);
			}
		}

	}				
	
	class ClassifyRenderer extends JComponent 
		implements TableCellRenderer, java.io.Serializable{
		@Override
		public Component getTableCellRendererComponent(JTable table,
                                               Object value,
                                               boolean isSelected,
                                               boolean hasFocus,
                                               int row,
                                               int column){
			if(value instanceof JToggleButton){
				JPanel cell = new JPanel(new FlowLayout(FlowLayout.CENTER,0,0));
				cell.setBackground(Color.white);
				JToggleButton check = (JToggleButton)value;
				if(check.isEnabled() && isSelected){
					check.setSelected(!check.isSelected());
					table.clearSelection();
				}
				if(check.isEnabled()){
					cell.add(check);
				}
				return 	cell;
			}
			return null;
		}
	}

	class VarClassifyTableModel extends AbstractTableModel{
		private int row,col;
		private Vector names;
		private Vector inputchecks;
		private Vector outputchecks;
		private Vector unusedchecks;
		private String[] colHd = {
			frame.getNolResourceString("VariableLabel"),
			frame.getNolResourceString("OutputLabel"),
			frame.getNolResourceString("InputLabel"),
			frame.getNolResourceString("UnusedLabel")};
		public VarClassifyTableModel(){
			row = 0;
			col = 4;
			names = null;
			outputchecks = new Vector();
			inputchecks = new Vector();
			unusedchecks = new Vector();
		}
		public void setNames(Vector names){
			this.names = names;
			row = names.size();
			outputchecks.removeAllElements();
			inputchecks.removeAllElements();
			unusedchecks.removeAllElements();
			ButtonGroup group;
			for(int r=0;r<row;r++){
				group = new ButtonGroup();
				JRadioButton check = new JRadioButton(){
					@Override
					public float getAlignmentY() { return 0.0f; }			
				};
				group.add(check);
				check.setBackground(Color.white);
				outputchecks.addElement(check);		 
				check = new JRadioButton(){
					@Override
					public float getAlignmentY() { return 0.0f; }			
				};
				check.setSelected(true);
				check.setBackground(Color.white);
				group.add(check);
				inputchecks.addElement(check);
				check = new JRadioButton(){
					@Override
					public float getAlignmentY() { return 0.0f; }			
				};
				check.setBackground(Color.white);
				group.add(check);
				unusedchecks.addElement(check);
			}
		}
		@Override
		public int getColumnCount() { return col; }
		@Override
		public int getRowCount() { return row;}
		@Override
		public Object getValueAt(int r, int c){
			if(c == 0){
				return names.elementAt(r);
			}else if(c == 1){
				return outputchecks.elementAt(r);
			}else if(c == 2){
				return inputchecks.elementAt(r);
			}else if(c == 3){
				return unusedchecks.elementAt(r);
			}
			return "";
		}
         
		@Override
		public String getColumnName(int c) {
			return colHd[c];
		}

		public Vector getInputChecks(){
			return inputchecks;
		}

		public Vector getOutputChecks(){
			return outputchecks;
		}

		public Vector getUnUsedChecks(){
			return unusedchecks;
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


}
