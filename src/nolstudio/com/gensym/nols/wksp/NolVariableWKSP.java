package com.gensym.nols.wksp;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import javax.swing.*;
import javax.swing.table.*;
import javax.swing.event.*;
import javax.swing.border.*;

import com.gensym.math.*;

import com.gensym.nols.util.*;
import com.gensym.nols.dlg.*;
import com.gensym.nols.data.*;
import com.gensym.nols.main.*;

public class NolVariableWKSP  extends NolInternalFrame{
	private NolMainFrame frame;
	private Variable varObj;
	private JTextField tagField;
	private JTextField nameField;
	private JTextField unitField;
	private JTextArea descriptArea;
	private ColoredSquare plotColorBlock;
	private Action actionListener;
	private JLabel caseName;
	private JLabel dataName;
	private JLabel sampleCount;
	private JLabel validCount;

	private	StatisticsTableModel statisticsTableModel;
	private	JTable statisticsTableView;

	
    protected static final String VARIABLEWKSP_GENERAL= "GeneralLabel";
    protected static final String VARIABLEWKSP_COMMENT= "CommentLabel";
    protected static final String VARIABLEWKSP_NAME= "NameLabel";
    protected static final String VARIABLEWKSP_TAG= "VariableWKSP_Tag";
    protected static final String VARIABLEWKSP_UNIT= "VariableWKSP_Unit";
    protected static final String VARIABLEWKSP_PLOTCOLOR= "VariableWKSP_PlotColor";
    protected static final String VARIABLEWKSP_DATASOURCE= "VariableWKSP_DataSource";
    protected static final String VARIABLEWKSP_SAMPLES= "VariableWKSP_Samples";
    protected static final String VARIABLEWKSP_VALID= "VariableWKSP_Valid";
    protected static final String VARIABLEWKSP_DATASERIES= "VariableWKSP_DataSeries";
    protected static final String VARIABLEWKSP_STATISTICS= "VariableWKSP_Statistics";
    protected static final String VARIABLEWKSP_LINECHART= "VariableWKSP_LineChart";
    protected static final String VARIABLEWKSP_HISTOGRAM= "VariableWKSP_Histogram";
    protected static final String VARIABLEWKSP_CHANGECOLOR= "VariableWKSP_ChangeColor";
    protected static final String VARIABLEWKSP_APPLYLABEL= "VariableWKSP_ApplyLabel";
    protected static final String VARIABLEWKSP_VALUE= "VariableWKSP_Value";


	public NolVariableWKSP (NolMainFrame frame,Variable varObj){
		super(varObj.getDataSource());
		this.frame = frame;
		this.varObj = varObj;
		String title = varObj.getDataSource().getName()+"."+
			varObj.getDataSeries().getName()+"."+varObj.getName();
		setTitle(title);
		actionListener = new ControlAction();
		initLayout();
		initDataDisplay();
	}

	private void initDataDisplay(){
		tagField.setText(varObj.getTag());
		nameField.setText(varObj.getName());
		unitField.setText(varObj.getUnit());

		if(!(varObj.getDataSeries().getDataSource() instanceof RawDataSource)){
			nameField.setEditable(false);
			unitField.setEditable(false);
		}
		descriptArea.setText(varObj.getComment());
		plotColorBlock.setShowColor(varObj.getPlotColor());

		caseName.setText(varObj.getDataSource().getName());
		dataName.setText(varObj.getDataSeries().getName());
		double[] values = new double[11];
		values[10] = varObj.getDataSeries().getRow();
		sampleCount.setText(String.valueOf((int)values[10]));
		int valc = 0;

		double[] data = varObj.getDataSeries().getVarArray(varObj);
		if(data != null){
			for(int i=0;i<data.length;i++){
				if(Double.isNaN(data[i])){
					valc++;
				}
			}
		}
		validCount.setText(String.valueOf((int)values[10]-valc));
		double[] stat = varObj.getStatistics();
		for(int i = 0; i < stat.length; i++) {
			values[i] = stat[i];
		}
		statisticsTableModel.setContent(values);
		
	}
	private void initLayout(){
		JPanel workPane = new JPanel(new BorderLayout());
													    
		JTabbedPane detailedTabbedPane = new JTabbedPane();
		detailedTabbedPane.addTab(frame.getNolResourceString(VARIABLEWKSP_GENERAL), getGeneralPanel());
		detailedTabbedPane.setSelectedIndex(0);
		detailedTabbedPane.addTab(frame.getNolResourceString(VARIABLEWKSP_STATISTICS), getStatisticPanel());

		workPane.add("Center", detailedTabbedPane);
		workPane.add("East",getControlPanel());
		setContentPane(workPane);

	}
	
	public void refreshTitle(){
		String title = varObj.getDataSource().getName()+"."+
			varObj.getDataSeries().getName()+"."+varObj.getName();
		setTitle(title);
	}

	private JPanel getGeneralPanel(){
		
		JPanel genPane = new JPanel(new BorderLayout());
													    
		JPanel cenPane = new JPanel(new BorderLayout());
		cenPane.setBorder(new EmptyBorder(10,10,10,10));

		JPanel namePane = new JPanel(new GridLayout(4,2,5,5));
		namePane.setBorder(new EmptyBorder(10,10,10,10));
		
		namePane.add(new JLabel(frame.getNolResourceString(VARIABLEWKSP_TAG)+":"));
		tagField = new JTextField();
//		tagField.setEditable(false);
		tagField.addActionListener(actionListener);
		namePane.add(tagField);
		namePane.add(new JLabel(frame.getNolResourceString(VARIABLEWKSP_NAME)+":"));
		nameField = new JTextField();
		nameField.addActionListener(actionListener);
		namePane.add(nameField);
		namePane.add(new JLabel(frame.getNolResourceString(VARIABLEWKSP_UNIT)+":"));
		unitField = new JTextField();
		unitField.addActionListener(actionListener);
		namePane.add(unitField);
		namePane.add(new JLabel(frame.getNolResourceString(VARIABLEWKSP_PLOTCOLOR)+":"));
		plotColorBlock = new ColoredSquare(Color.red, true);
		namePane.add(plotColorBlock);
		

		JPanel descriptPane = new JPanel(new GridLayout());
		descriptPane.setBorder(new TitledBorder(new EmptyBorder(1, 1, 1, 1),               
			frame.getNolResourceString(VARIABLEWKSP_COMMENT)+":", TitledBorder.LEFT , TitledBorder.TOP));
		descriptArea = new JTextArea();
		descriptArea.getDocument().addDocumentListener((DocumentListener)actionListener);
		JScrollPane listScrollPane = new JScrollPane(descriptArea);
		listScrollPane.setBorder(BorderFactory.createLoweredBevelBorder());
		listScrollPane.setPreferredSize(NolMainFrame.vpad40); 
		descriptPane.add(listScrollPane);

		cenPane.add("North",namePane);
		cenPane.add("Center",descriptPane);


		JPanel southPane = new JPanel(new GridLayout(2,4,5,5));
		caseName = new JLabel();
		dataName = new JLabel();
		sampleCount = new JLabel();
		validCount = new JLabel();
		southPane.setBorder(new EmptyBorder(10, 10, 10, 10));               
		southPane.add(new JLabel(frame.getNolResourceString(VARIABLEWKSP_DATASOURCE)+":"));
		southPane.add(caseName);
		southPane.add(new JLabel(frame.getNolResourceString(VARIABLEWKSP_DATASERIES)+":"));
		southPane.add(dataName);
		southPane.add(new JLabel(frame.getNolResourceString(VARIABLEWKSP_SAMPLES)+":"));
		southPane.add(sampleCount);
		southPane.add(new JLabel(frame.getNolResourceString(VARIABLEWKSP_VALID)+":"));
		southPane.add(validCount);

		cenPane.add("South",southPane);
		genPane.add(cenPane);

		return genPane;
	}

	private JPanel getStatisticPanel(){
		JPanel statPane = new JPanel(new GridLayout());

		JPanel cenPane = new JPanel(new GridLayout());
  		cenPane.setBorder(new EmptyBorder(10,10,10,10));

		statisticsTableModel = new StatisticsTableModel();
		statisticsTableView = new JTable(statisticsTableModel);
		statisticsTableView.setSelectionBackground(Color.white);
		statisticsTableView.setCellSelectionEnabled(false);
		statisticsTableView.setSelectionForeground(Color.black);
		JScrollPane listScrollPane = new JScrollPane(statisticsTableView);
		listScrollPane.setBackground(Color.white);

		cenPane.add(listScrollPane);
		statPane.add(cenPane);
		return statPane;
	}

	private JPanel getControlPanel(){
		JPanel control = new JPanel();
		control.setBackground(getContentPane().getBackground());
		control.setLayout(new BoxLayout(control, BoxLayout.Y_AXIS));
		control.setBorder(new EmptyBorder(10, 10, 10, 10));

		JPanel pane0 = new JPanel(new GridLayout(5,1,5,5));
		JButton but = new JButton(frame.getNolResourceString(VARIABLEWKSP_LINECHART));
		but.setActionCommand("Line Chart...");
		but.addActionListener(actionListener);
  		pane0.add(but);
		but = new JButton(frame.getNolResourceString(VARIABLEWKSP_HISTOGRAM));
		but.setActionCommand("Histogram...");
		but.addActionListener(actionListener);
  		pane0.add(but);
		but = new JButton(frame.getNolResourceString(VARIABLEWKSP_CHANGECOLOR));
		but.setActionCommand("Change Color...");
		but.addActionListener(actionListener);
  		pane0.add(but);
		but = new JButton(frame.getNolResourceString(VARIABLEWKSP_APPLYLABEL));
		but.setActionCommand("Apply Label...");
		but.addActionListener(actionListener);
		but.setEnabled(false); //Temp Gchen 9/9/98
  		pane0.add(but);
		control.add(Box.createRigidArea(NolMainFrame.vpad15));
		control.add(pane0);
		control.add(Box.createRigidArea(NolMainFrame.vpad500));
		control.add(Box.createVerticalGlue());
		return control;
	}

	private void refreshDisplay(){
		Rectangle rv = this.getBounds();
		this.setBounds(rv.x,rv.y,rv.width+1,rv.height);
		this.paintImmediately(rv.x,rv.y,rv.width+1,rv.height);
		this.validate();
		this.setBounds(rv.x,rv.y,rv.width,rv.height);
		this.validate();
	}

	public Variable getVariable(){
		return varObj;
	}

/** The inner control listener class.*/
    class ControlAction extends AbstractAction implements DocumentListener, Runnable {
		private String command;
		private Object source;
		ControlAction() {super("controlAction");}
		@Override
		public void actionPerformed(ActionEvent e) {
			// handle all actions outside of the main UI thread, otherwise the UI hangs
			command = e.getActionCommand ();
			source = e.getSource ();
			new Thread (this).start();
		}
        @Override
		public void run() {
			setWaitCursor(true);
			if(command.equals("Line Chart...")){
				Vector vars = new Vector(1);
				vars.addElement(varObj);
				frame.lineChartActionPerformed(vars);
			}else if(command.equals("Histogram...")){
				frame.histogramActionPerformed(varObj);
			}else if(command.equals("Apply Label...")){
			}else if(command.equals("Change Color...")){
				NolColorChooser colorChooser = new NolColorChooser((JFrame)frame, "Color Chooser");
				colorChooser.setBounds(200,200,300,300);
				colorChooser.setVisible(true);
				Color color = colorChooser.getSelectedColor();
				if(colorChooser.getResult()){
					colorChooser.dispose();		
				}else{
					colorChooser.dispose();	
					setWaitCursor(false);
					return;
				}
				varObj.setPlotColor(color);	 //propergate the event gchen 11.18.98
				plotColorBlock.setShowColor(varObj.getPlotColor());
				plotColorBlock.validate();
				plotColorBlock.repaint(0l);
//				frame.changeVariablePlotColor(varObj);

			}else if(source.equals(tagField)){
				String n = tagField.getText();
				if(n == null || n.equals("")){
					tagField.setText(varObj.getTag());
					setWaitCursor(false);
					return;
				}
				if(n.equals(varObj.getTag())){
					setWaitCursor(false);
					return;
				}
				Project project = frame.getProject();
				Vector pdata = project.getProcessedData();
				boolean inUse = false;
				for(int i=0;i<pdata.size();i++){
					DataSeries oldds = (DataSeries)pdata.elementAt(i);
					if(oldds.getVarByName(varObj.getName()) != null){
						inUse = true;
						break;						
					}
				}
				if(inUse){
					frame.showOKDialog("Cannot rename this variable, it is in use.");
					tagField.setText(varObj.getTag());
					setWaitCursor(false);
					return;
				}
				varObj.setTag(n);	 //Gchen temp 11.19.98
					frame.showOKDialog("change tag ="+n);
				frame.changeVariableName(varObj);
				//propergate the event gchen 11.18.98
			}else if(source.equals(nameField)){
				String n = nameField.getText();
				if(n == null || n.equals("")){
					nameField.setText(varObj.getName());
					setWaitCursor(false);
					return;
				}
				if(n.equals(varObj.getName())){
					setWaitCursor(false);
					return;
				}
				Project project = frame.getProject();
				Vector pdata = project.getProcessedData();
				boolean inUse = false;
				for(int i=0;i<pdata.size();i++){
					DataSeries oldds = (DataSeries)pdata.elementAt(i);
					if(oldds.getVarByName(varObj.getName()) != null){
						inUse = true;
						break;						
					}
				}
				if(inUse){
					frame.showOKDialog("Cannot rename this variable, it is in use.");
					nameField.setText(varObj.getName());
					setWaitCursor(false);
					return;
				}
				varObj.setName(n);	 //Gchen temp 11.19.98
				frame.changeVariableName(varObj);
				//propergate the event gchen 11.18.98
			}else if(source.equals(unitField)){
				String u = unitField.getText();
				if(u == null || u.equals("")){
					unitField.setText(varObj.getUnit());
					setWaitCursor(false);
					return;
				}
				if(u.equals(varObj.getUnit())){
					setWaitCursor(false);
					return;
				}
				varObj.setUnit(u);
			}
			setWaitCursor(false);
		}
 		@Override
		public void changedUpdate(DocumentEvent e){	}
		@Override
		public void insertUpdate(DocumentEvent e){
			changeComment();
		}
		@Override
		public void removeUpdate(DocumentEvent e){
			changeComment();
		}
		private void changeComment(){
			String com = descriptArea.getText();
			varObj.setComment(com);
		}
   }
	class StatisticsTableModel extends AbstractTableModel{
		private int row,col;
		private String[] rowHd = {"Mean","Median",
			"STD","Variance","Kurtosis","Skewness",
			"Range","Minimum","Maximum","Sum","Count"};
		private int digits = 5;
		private double[] values;
		private String[] colHd = {frame.getNolResourceString(VARIABLEWKSP_STATISTICS),
			frame.getNolResourceString(VARIABLEWKSP_VALUE)};
		public StatisticsTableModel(){
			row = 0;
			col = 2;
		}
		public void setContent(double[] values){
			this.values = values;
			row = values.length;
		}
		@Override
		public int getColumnCount() { return col; }
		@Override
		public int getRowCount() { return row;}
		@Override
		public Object getValueAt(int r, int c){
			if(c == 0){
				return rowHd[r];
			}else if(c == 1){
				return Utilities.formatDouble(values[r], digits);
			}
			return "";
		}
		@Override
		public String getColumnName(int c) {
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
}

