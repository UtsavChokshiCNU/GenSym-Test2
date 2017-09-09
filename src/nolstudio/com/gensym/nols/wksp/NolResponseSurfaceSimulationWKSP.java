package com.gensym.nols.wksp;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import javax.swing.*;
import javax.swing.table.*;
import javax.swing.event.*;
import javax.swing.border.*;

import com.gensym.nols.data.*;
import com.gensym.nols.main.*;
import com.gensym.nols.dlg.*;

import com.gensym.math.Utilities;
import com.gensym.DEBUG;

public class NolResponseSurfaceSimulationWKSP  extends NolInternalFrame{
	protected static final String SIMULATIONWKSP_NAME = "NameLabel";
    protected static final String SIMULATIONWKSP_COMMENT = "CommentLabel";
    protected static final String SIMULATIONWKSP_MODEL= "SimulationWKSP_Model";
    protected static final String SIMULATIONWKSP_MODELTYPE = "SimulationWKSP_ModelType";
    protected static final String SIMULATIONWKSP_POINTS = "SimulationWKSP_Points";
    protected static final String SIMULATIONWKSP_VARIABLE = "VariableLabel";
    protected static final String SIMULATIONWKSP_START = "SimulationWKSP_Start";
    protected static final String SIMULATIONWKSP_END = "SimulationWKSP_End";
    protected static final String SIMULATIONWKSP_RUN = "SimulationWKSP_Run";
    protected static final String SIMULATIONWKSP_OUTPUTINSPREADSHEET = "SimulationWKSP_OutputInSpreadsheet";
    protected static final String SIMULATIONWKSP_INPUTINSPREADSHEET = "SimulationWKSP_InputInSpreadsheet";
    protected static final String SIMULATIONWKSP_LINECHART = "SimulationWKSP_LineChart";
    protected static final String DELETE = "DeleteLabel";

    protected static final String MODELNOTTRAINED = "SimulationWKSP_ModelNotTrained";
	

	private NolMainFrame frame;
	private JTextField simulationName;
	private JTextArea descriptArea;
	private JLabel modelName;
	private JLabel modelType;
	private JTextField numberOfPoint;
	private JButton runBut;
	private ResponseSurfaceSimulation simulation;
	private Action actionListener;
 	
	private int digits = 5;
	private	VarTableModel varTableModel;
	private	JTable varTableView;
	private NolModel2 model;

	public NolResponseSurfaceSimulationWKSP (NolMainFrame frame, ResponseSurfaceSimulation simulation){

		super(frame.getProject().getRawDataSource());
		this.frame = frame;
		this.simulation = simulation;
		String title = "Simulation:["+simulation.getName()+"]";
		setTitle(title);
		actionListener = new ControlAction();
		initLayout();
		initDataDisplay();
	}

	private void initLayout(){
		JPanel workPane = new JPanel(new BorderLayout());
													    
		JPanel cenPane = new JPanel(new BorderLayout());

		JPanel infoPane = new JPanel(new BorderLayout());
		JPanel namePane = new JPanel(new GridLayout(2,4,10,10));
		namePane.setBorder(new EmptyBorder(12,12,10,12));
		namePane.add(new JLabel(frame.getNolResourceString(SIMULATIONWKSP_NAME)+":"));
		simulationName = new JTextField();
		simulationName.addActionListener(actionListener);
		namePane.add(simulationName);
		namePane.add(new JLabel(frame.getNolResourceString(SIMULATIONWKSP_MODEL)+":"));
		modelName = new JLabel();
		namePane.add(modelName);
		namePane.add(new JLabel(frame.getNolResourceString(SIMULATIONWKSP_POINTS)+":"));
		numberOfPoint = new JTextField();
		numberOfPoint.addActionListener(actionListener);
		namePane.add(numberOfPoint);

		namePane.add(new JLabel(frame.getNolResourceString(SIMULATIONWKSP_MODELTYPE)+":"));
		modelType = new JLabel();
		namePane.add(modelType);

		
		JPanel descriptPane = new JPanel(new GridLayout());
		descriptPane.setBorder(new TitledBorder(new EmptyBorder(7, 7, 7, 7),               
			frame.getNolResourceString(SIMULATIONWKSP_COMMENT)+":", TitledBorder.LEFT , TitledBorder.TOP));
		descriptArea = new JTextArea();
		descriptArea.getDocument().addDocumentListener((DocumentListener)actionListener);
		JScrollPane listScrollPane = new JScrollPane(descriptArea);
		listScrollPane.setBorder(BorderFactory.createLoweredBevelBorder());
		listScrollPane.setPreferredSize(NolMainFrame.vpad50); 
		descriptPane.add(listScrollPane);

		infoPane.add("North",namePane);
		infoPane.add("Center",descriptPane);

		JPanel varPane = new JPanel(new GridLayout());
		varPane.setBorder(new EmptyBorder(10,10,10,10));
		varTableModel = new VarTableModel();
		varTableView = new JTable(varTableModel);
		varTableView.setSelectionMode(0);
		varTableView.setCellSelectionEnabled(true);
		listScrollPane = new JScrollPane(varTableView);
		listScrollPane.setBackground(Color.white);
		varPane.add(listScrollPane);

		cenPane.add("North",infoPane);
		cenPane.add("Center",varPane);

		
		workPane.add("Center",cenPane);
		workPane.add("East",getControlPanel());
		setContentPane(workPane);

	}

	private JPanel getControlPanel(){
		JPanel control = new JPanel();
		control.setBackground(getContentPane().getBackground());
		control.setLayout(new BoxLayout(control, BoxLayout.Y_AXIS));
		control.setBorder(new EmptyBorder(10, 10, 10, 10));

		JPanel pane0 = new JPanel(new GridLayout(5,1,5,5));
		runBut  = new JButton(frame.getNolResourceString(SIMULATIONWKSP_RUN));
		runBut.setActionCommand("Run");
		runBut.setEnabled(false);
		runBut.addActionListener(actionListener);
  		pane0.add(runBut);
		JButton but = new JButton(frame.getNolResourceString(SIMULATIONWKSP_OUTPUTINSPREADSHEET));
		but.setActionCommand("Output in Spreadsheet");
		but.addActionListener(actionListener);
  		pane0.add(but);
		but = new JButton(frame.getNolResourceString(SIMULATIONWKSP_INPUTINSPREADSHEET));
		but.setActionCommand("Input in Spreadsheet");
		but.addActionListener(actionListener);
  		pane0.add(but);
		but = new JButton(frame.getNolResourceString(SIMULATIONWKSP_LINECHART));
		but.setActionCommand("Line Chart...");
		but.addActionListener(actionListener);
  		pane0.add(but);
		but = new JButton(frame.getNolResourceString(DELETE));
		but.setActionCommand("Delete");
		but.addActionListener(actionListener);
//		but.setEnabled(false); //Temp gchen 10/18/98
  		pane0.add(but);
		control.add(Box.createRigidArea(NolMainFrame.vpad15));
		control.add(pane0);
		control.add(Box.createRigidArea(NolMainFrame.vpad500));
		control.add(Box.createVerticalGlue());
		return control;
	}


	private void initDataDisplay(){
		simulationName.setText(simulation.getName());
		model = simulation.getModel();
		modelName.setText(model.getName()); 
		if(model instanceof NolOptimizeModel){
			modelType.setText("Optimization");
		}else{
			modelType.setText("Predictive");
		}
		numberOfPoint.setText(String.valueOf(simulation.getNumberOfPoints()));
		descriptArea.setText(simulation.getComment());
		refreshVarTableView();
	}

	private void refreshVarTableView(){
		Project project = frame.getProject();
		Vector names = new Vector();
		Vector mins = new Vector();
		Vector maxs = new Vector();
		if(!(model instanceof NolOptimizeModel)){
			Vector outputs = model.getOutputs();
			Vector inputs = model.getInputs();
			Vector outputDelays = model.getOutputDelays();
			Vector inputDelays = model.getInputDelays();
			Preprocessor prep = model.getPreprocessor();
			for(int i=0;i<outputDelays.size();i++){
				long[] dls = (long[])outputDelays.elementAt(i);
				for(int j=0;j<dls.length;j++){
					if(dls[j]>0){
						String varName = (String)outputs.elementAt(i);
						double[] minmax = simulation.getMinMax(varName);						
						names.addElement(varName);
						mins.addElement(Utilities.formatDouble(minmax[0], digits));
						maxs.addElement(Utilities.formatDouble(minmax[1], digits));
						break;
					}
				}
			}
			for(int i=0;i<inputs.size();i++){
				String varName = (String)inputs.elementAt(i);
				double[] minmax = simulation.getMinMax(varName);						
				names.addElement(varName);
				mins.addElement(Utilities.formatDouble(minmax[0], digits));
				maxs.addElement(Utilities.formatDouble(minmax[1], digits));
			}
			varTableModel.setNames(names,mins,maxs);
			varTableView.setModel(varTableModel);
			varTableView.validate();
			varTableView.repaint(0l);
		}else{
			NolOptimizeModel optmodel = (NolOptimizeModel)model;
			Vector manis = optmodel.getManipulate();
			Vector exogs = optmodel.getExogenous();
			Preprocessor prep = optmodel.getPreprocessor();
			for(int i=0;i<manis.size();i++){
				String varName = (String)manis.elementAt(i);
				double[] minmax = simulation.getMinMax(varName);						
				names.addElement(varName);
				mins.addElement(Utilities.formatDouble(minmax[0], digits));
				maxs.addElement(Utilities.formatDouble(minmax[1], digits));
			}
			for(int i=0;i<exogs.size();i++){
				String varName = (String)exogs.elementAt(i);
				double[] minmax = simulation.getMinMax(varName);						
				names.addElement(varName);
				mins.addElement(Utilities.formatDouble(minmax[0], digits));
				maxs.addElement(Utilities.formatDouble(minmax[1], digits));
			}
			varTableModel.setNames(names,mins,maxs);
			varTableView.setModel(varTableModel);
			varTableView.validate();
			varTableView.repaint(0l);
		}
	}

	private void refreshDisplay(){
		Rectangle rv = this.getBounds();
		this.setBounds(rv.x,rv.y,rv.width+1,rv.height);
		this.paintImmediately(rv.x,rv.y,rv.width+1,rv.height);
		this.validate();
		this.setBounds(rv.x,rv.y,rv.width,rv.height);
		this.validate();
	}

	public ResponseSurfaceSimulation getSimulation(){
		return simulation;
	}

	private void runSimulation(){

		if(!model.isTrained()){
			frame.showOKDialog(frame.getNolResourceString(MODELNOTTRAINED));
			return;
		}

		Vector names = 	varTableModel.getNames();
		Vector min = varTableModel.getMin();
		Vector max = varTableModel.getMax();
		for(int i=0;i<names.size();i++){
			String varName = (String)names.elementAt(i);
			double minValue = Double.valueOf((String)min.elementAt(i)).doubleValue();
			double maxValue = Double.valueOf((String)max.elementAt(i)).doubleValue();
			simulation.setMinMax(varName,minValue,maxValue);
		}
		int numberOfPointValue = simulation.getNumberOfPoints();
		try{
			int v = Integer.valueOf(numberOfPoint.getText()).intValue();
			if(v<1){ 
				v=1;
				numberOfPoint.setText(String.valueOf(1));
			}
			numberOfPointValue = v;
		}catch( NumberFormatException evt){
			numberOfPoint.setText(String.valueOf(simulation.getNumberOfPoints()));
		}
		simulation.setNumberOfPoints(numberOfPointValue);
		simulation.setCalculated(false);
		simulation.calulationSimulation();
		if(DEBUG.debugFlag){
			System.out.println("calculationSimulation");
		}
		runBut.setEnabled(false);
	}
	
/** The inner control listener class.*/
    class ControlAction extends AbstractAction implements DocumentListener,Runnable{
		private String command;
		private Object source;
		ControlAction() {super("controlAction");}
        @Override
		public void actionPerformed(ActionEvent e) {
			command = e.getActionCommand ();
			source = e.getSource ();
			new Thread (this).start();
		}
		@Override
		public void run () {
			if(command.equals("Run")){
				setWaitCursor(true);
				runSimulation();
				setWaitCursor(false);
				frame.showOKDialog("Finished running "+simulation.getName()+".");
			}else if(command.equals("Output in Spreadsheet")){
				frame.spreadsheetActionPerformed(simulation.getOutputData());
			}else if(command.equals("Input in Spreadsheet")){
				frame.spreadsheetActionPerformed(simulation.getInputData());
			}else if(command.equals("Line Chart...")){
				DataSeries ds1 = simulation.getOutputData();
				DataSeries ds2 = simulation.getInputData();
				Vector varObjs1 = ds1.getVarObjects();
				Vector varObjs2 = ds2.getVarObjects();
				Vector content1 = new Vector(2);
				Vector content2 = new Vector(2);
				if(DEBUG.debugFlag){
					System.out.println("ds1="+ds1);
					System.out.println("ds2="+ds2);
				}
				content1.addElement(ds1);
				content1.addElement(ds2);
				content2.addElement(varObjs1);
				content2.addElement(varObjs2);
				NolDoubleChoiceDialog doubleChoiceDialog = 
					new NolDoubleChoiceDialog(frame,"Select Variables","DataSeries:", "Variable", content1,content2, true);
				
				doubleChoiceDialog.setContent("Select Variables","DataSeries:", "Variable", content1,content2, true);
				doubleChoiceDialog.pack();
				doubleChoiceDialog.setBounds(200, 200, 320, 300);
				doubleChoiceDialog.setVisible(true);
				if(!doubleChoiceDialog.getResult()){
					return;
				}
				Vector vars = (Vector)doubleChoiceDialog.getSelectedItems();
				frame.lineChartActionPerformed(vars);
			}else if(command.equals("Delete")){
				frame.removeSimulation(simulation);
			}else if(source.equals(numberOfPoint)){
				try{
					int v = Integer.valueOf(numberOfPoint.getText()).intValue();
					runBut.setEnabled(true);
				}catch(NumberFormatException evt){
					numberOfPoint.setText(String.valueOf(simulation.getNumberOfPoints()));
				}
			}else if(source.equals(simulationName)){
				String nm = simulationName.getText();
				if(nm.length() > 0){
					simulation.setName(nm);
					String title = "Simulation:["+simulation.getName()+"]";
					setTitle(title);
					frame.getProjectTree().changeSimulationName(simulation,true);
				}else{
					nm = simulation.getName();
					simulationName.setText(nm);
				}
			}
		}
		@Override
		public void changedUpdate(DocumentEvent e){}
		@Override
		public void insertUpdate(DocumentEvent e){
			String com = descriptArea.getText();
			simulation.setComment(com);
			if(DEBUG.debugFlag){
				System.out.println("get Document event insertUpdate");
			}
		}
		@Override
		public void removeUpdate(DocumentEvent e){
			String com = descriptArea.getText();
			simulation.setComment(com);
		}
    }
	
	class VarTableModel extends AbstractTableModel{
		private int row,col;
		private Vector names;
		private Vector min,max;
		private String[] colHd = {frame.getNolResourceString(SIMULATIONWKSP_VARIABLE),
			frame.getNolResourceString(SIMULATIONWKSP_START),
			frame.getNolResourceString(SIMULATIONWKSP_END)};
		public VarTableModel(){
			row = 0;
			col = 3;
			names = new Vector();
			min = new Vector();
			max = new Vector();
		}
		public void setNames(Vector names, Vector min,Vector max ){
			this.names = names;
			this.min = min;
			this.max = max;
			row = min.size();
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
				return min.elementAt(r);
			}else if(c == 2){
				return max.elementAt(r);
			}
			return "";
		}
		@Override
		public String getColumnName(int c) {
			return colHd[c];
		}
		@Override
		public boolean isCellEditable(int r, int c) {
			if(c==1 || c==2) {
				return true;
			}
			return false;
		}		
		@Override
		public void setValueAt(Object aValue, int r, int c) {
			if(c == 1){
				try{
					double v = Double.valueOf((String)aValue).doubleValue();
					min.setElementAt(aValue,r);
					runBut.setEnabled(true);
				}catch( NumberFormatException evt){
					System.err.println("Non-Fatal exception: " + evt.getMessage());
					evt.printStackTrace();
				}
			}else if(c == 2){
				try{
					double v = Double.valueOf((String)aValue).doubleValue();
					max.setElementAt(aValue,r);
					runBut.setEnabled(true);
				}catch( NumberFormatException evt){
					System.err.println("Non-Fatal exception: " + evt.getMessage());
					evt.printStackTrace();
				}
			}
		}
		public Vector getNames(){
			return names;
		}
		public Vector getMin(){
			return min;
		}
		public Vector getMax(){
			return max;
		}
	}

}

