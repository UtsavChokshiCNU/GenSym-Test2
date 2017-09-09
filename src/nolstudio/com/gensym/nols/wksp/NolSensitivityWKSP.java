package com.gensym.nols.wksp;

import java.awt.*;
import java.awt.event.*;
import java.util.*;

import javax.swing.*;
import javax.swing.table.*;
import javax.swing.border.*;

import com.gensym.math.Utilities;
import com.gensym.math.matrix.*;

import com.gensym.nols.main.*;
import com.gensym.nols.data.*;
import com.gensym.nols.util.*;

public class NolSensitivityWKSP extends NolInternalFrame {

	private NolMainFrame frame;

//	private JButton calculateBut;
//	private JButton stopBut;
	private JButton exportBut;
	private JButton exportParaBut;
	private ControlAction actionListener;
	private boolean noFire;
	private boolean isCalculated;
	private boolean hasTwoEnsembles;
	private JTabbedPane varTabbedPane;
	private JTextArea infoLabel;

	private boolean isAbsolute;
	private boolean isChart;

	private NolModel2 model;
	private Vector inputVars;
	private Vector inputNameWithDelays;
	private Vector outputVars;
	private Vector stateInputVars;
	private Vector stateOutputVars;
	private Vector varContentInPane;

 	private	SensitivityTableModel signedSensitivityTableModel;
 	private	SensitivityColorTableModel signedSensitivityColorTableModel;
 	private	SensitivityTableModel absSensitivityTableModel;
 	private	SensitivityColorTableModel absSensitivityColorTableModel;
	private	JTable sensitivityTableView;

 	private	SensitivityTableModel signedSensitivityTableModel1;
 	private	SensitivityColorTableModel signedSensitivityColorTableModel1;
 	private	SensitivityTableModel absSensitivityTableModel1;
 	private	SensitivityColorTableModel absSensitivityColorTableModel1;
	private	JTable sensitivityTableView1;

	private TableSorter signedSorterNumber;
	private TableSorter signedSorterColor;
	private TableSorter absSorterNumber;
	private TableSorter absSorterColor;
	
	private TableSorter signedSorterNumber1;
	private TableSorter signedSorterColor1;
	private TableSorter absSorterNumber1;
	private TableSorter absSorterColor1;
	
	private Matrix signedSensitivityValues;
	private Matrix scaledSignedSensitivityValues;
	private Matrix absSensitivityValues;
	private Matrix scaledAbsSensitivityValues;

	private Matrix signedSensitivityValues1;
	private Matrix scaledSignedSensitivityValues1;
	private Matrix absSensitivityValues1;
	private Matrix scaledAbsSensitivityValues1;

	private Matrix sampleMatrix = null;
	private Matrix sampleMatrix1 = null;	//for state model

	private int sigDigits = 8;

	private Vector usedchecks;	//add for neil

	private String exportString;
	
	private static final String MODELNAME = "SensitivityWKSP_ModelName";
	private static final String VARIABLENAME = "NameLabel";
    private static final String PREPROCESSOR = "SensitivityWKSP_Preprocessor";
    private static final String EXPORT = "SensitivityWKSP_Export";
    private static final String SHOW = "SensitivityWKSP_Show";
    private static final String NUMBER = "SensitivityWKSP_Number";
    private static final String CHART = "SensitivityWKSP_Chart";
    private static final String VALUE = "SensitivityWKSP_Value";
    private static final String SIGNED = "SensitivityWKSP_Signed";
    private static final String ABSOLUTE = "SensitivityWKSP_Absolute";
    private static final String STATEMODEL = "SensitivityWKSP_StateModel";
    private static final String OUTPUTMODEL = "SensitivityWKSP_OutputModel";
    private static final String SIGNEDDEFINITION = "SensitivityWKSP_SignedDefinition";
    private static final String ABSDEFINITION = "SensitivityWKSP_AbsDefinition";
    private static final String CLICKTOSORT = "SensitivityWKSP_ClickToSort";
    private static final String USEDFORFUTURE = "SensitivityWKSP_UsedForFuture";
    private static final String EXPORTPARAMETER = "SensitivityWKSP_ExportParameter";

	private static int COLUMNWIDTH = 100;
	private static int LASTCOLUMNWIDTH = 20;

	public NolSensitivityWKSP (NolMainFrame frame, NolModel2 model){ //for demo only
		super(model.getPreprocessor());
		setTitle("Sensitivities for model ["+model.getName()+"]");

		this.frame = frame;
		this.model = model;
		actionListener = new ControlAction();
		hasTwoEnsembles = false;
		if(model instanceof NolOptimizeModel){
			inputVars = model.getInputs();
			inputNameWithDelays = (Vector)inputVars.clone();
			outputVars = model.getOutputs();	
			if(((NolOptimizeModel)model).getStateModel() != null){
				hasTwoEnsembles = true;
				stateInputVars = ((NolOptimizeModel)model).getStateInput();
				stateOutputVars = ((NolOptimizeModel)model).getState();	
			}
		}else{
			Vector inputNames = model.getInputs();
			Vector inputDelays = model.getInputDelays();
			Vector outputDelays = model.getOutputDelays();
			inputVars = new Vector();
			inputNameWithDelays = new Vector();
			outputVars = model.getOutputs();	
			for(int i=0;i<outputVars.size();i++){
  				long[] dls = (long[])outputDelays.elementAt(i);
				for(int j=0;j<dls.length;j++){
					if((dls[j] > 0L)){
						String name = (String)outputVars.elementAt(i);
						inputVars.addElement(name);
						double ddls = dls[j]/60000.0;
						inputNameWithDelays.addElement(name+"("+ddls+")");
					}
				}
			}
			for(int i=0;i<inputNames.size();i++){
  				long[] dls = (long[])inputDelays.elementAt(i);
				if(dls.length == 0 || (dls.length == 1 && dls[0] == 0L)){
					inputVars.addElement(inputNames.elementAt(i));
					inputNameWithDelays.addElement(inputNames.elementAt(i));
				}else {
					for(int j=0;j<dls.length;j++){
						String name = (String)inputNames.elementAt(i);
						inputVars.addElement(name);
						double ddls = dls[j]/60000.0;
						inputNameWithDelays.addElement(name+"("+ddls+")");
					}
				}
			}
		}
		usedchecks = new Vector();
		for(int i=0;i<inputNameWithDelays.size();i++){
			JCheckBox check = new JCheckBox(){
				@Override
				public float getAlignmentY() { return 0.0f; }			
			};
			check.setBackground(Color.white);
			check.setSelected(true);
			usedchecks.addElement(check);
		}
		isCalculated = false;
		isAbsolute = false;
		isChart = true;
		noFire = false;
		initialLayout();
		initDataDisplay();
		calculateSensitivities();
	}

	private void initialLayout(){
		getContentPane().setLayout(new BorderLayout());  		
		JPanel centerPane = new JPanel(new BorderLayout());
		centerPane.add("Center",getVarPanel());    
		centerPane.add("North", getModelNamePanel());
		getContentPane().add("Center",centerPane);
		getContentPane().add("East",getControlPanel());	
	}

	private JPanel getModelNamePanel(){

		JPanel namePanel = new JPanel(new BorderLayout());

		JPanel infoPane = new JPanel(new GridLayout());
 		infoPane.setBorder(new EmptyBorder(10,10,10,10));
		infoLabel = new JTextArea(frame.getNolResourceString(SIGNEDDEFINITION));
		infoLabel.setLineWrap(true);
		infoLabel.setWrapStyleWord(true);
		infoLabel.setEditable(false);
		infoLabel.setBackground(infoPane.getBackground());
		infoPane.add(infoLabel);

		JPanel contentPanel = new JPanel(new GridLayout(1,4,5,5));
		
		contentPanel.setBorder(new EmptyBorder(10, 10, 10, 10));               
		contentPanel.add(new JLabel(frame.getNolResourceString(MODELNAME)+":"));
		contentPanel.add(new JLabel(model.getName()));
		contentPanel.add(new JLabel(frame.getNolResourceString(PREPROCESSOR)+":"));
		contentPanel.add(new JLabel(model.getPreprocessor().getName()));

		namePanel.add("North",infoPane);
		namePanel.add("Center",contentPanel);
		return namePanel;
	}

	private JComponent getVarPanel(){
		
		signedSensitivityTableModel = new SensitivityTableModel(inputNameWithDelays,outputVars);
		signedSensitivityColorTableModel = new SensitivityColorTableModel(inputNameWithDelays,outputVars);
		absSensitivityTableModel = new SensitivityTableModel(inputNameWithDelays,outputVars);
		absSensitivityColorTableModel = new SensitivityColorTableModel(inputNameWithDelays,outputVars);


		signedSorterNumber = new TableSorter(signedSensitivityTableModel); //ADDED THIS FOR  SORTING GCHEN 6.7.99
		signedSorterColor = new TableSorter(signedSensitivityColorTableModel); //ADDED THIS FOR  SORTING GCHEN 6.7.99
		absSorterNumber = new TableSorter(absSensitivityTableModel); //ADDED THIS FOR  SORTING GCHEN 6.7.99
		absSorterColor = new TableSorter(absSensitivityColorTableModel); //ADDED THIS FOR  SORTING GCHEN 6.7.99

//		sensitivityTableView = new JTable(signedSensitivityTableModel);
//		sensitivityTableView = new JTable(signedSorterNumber);
		sensitivityTableView = new JTable(signedSorterColor);
		sensitivityTableView.getTableHeader().setToolTipText(frame.getNolResourceString(CLICKTOSORT));
		turnOffAutoColumn(sensitivityTableView);

		signedSorterNumber.addMouseListenerToHeaderInTable(sensitivityTableView);
		signedSorterColor.addMouseListenerToHeaderInTable(sensitivityTableView);
		absSorterNumber.addMouseListenerToHeaderInTable(sensitivityTableView);
		absSorterColor.addMouseListenerToHeaderInTable(sensitivityTableView);

		SensitivityTableRenderer render = new SensitivityTableRenderer();
		sensitivityTableView.setDefaultRenderer(ColoredBar.class, 
			render);
		sensitivityTableView.setDefaultRenderer(JToggleButton.class, 
			render);	//add for neil
		sensitivityTableView.setSelectionMode(0);
		sensitivityTableView.setCellSelectionEnabled(true);
		JScrollPane varScrollPane = new JScrollPane(sensitivityTableView);
		varScrollPane.setBackground(Color.white);

		if(hasTwoEnsembles){
			signedSensitivityTableModel1 = new SensitivityTableModel(stateInputVars,stateOutputVars);
			signedSensitivityColorTableModel1 = new SensitivityColorTableModel(stateInputVars,stateOutputVars);
			absSensitivityTableModel1 = new SensitivityTableModel(stateInputVars,stateOutputVars);
			absSensitivityColorTableModel1 = new SensitivityColorTableModel(stateInputVars,stateOutputVars);

			signedSorterNumber1 = new TableSorter(signedSensitivityTableModel1); //ADDED THIS FOR  SORTING GCHEN 6.7.99
			signedSorterColor1 = new TableSorter(signedSensitivityColorTableModel1); //ADDED THIS FOR  SORTING GCHEN 6.7.99
			absSorterNumber1 = new TableSorter(absSensitivityTableModel1); //ADDED THIS FOR  SORTING GCHEN 6.7.99
			absSorterColor1 = new TableSorter(absSensitivityColorTableModel1); //ADDED THIS FOR  SORTING GCHEN 6.7.99
			
//			sensitivityTableView1 = new JTable(signedSorterNumber1);
			sensitivityTableView1 = new JTable(signedSorterColor1);
			sensitivityTableView1.getTableHeader().setToolTipText(frame.getNolResourceString(CLICKTOSORT));
			turnOffAutoColumn(sensitivityTableView1);

			signedSorterNumber1.addMouseListenerToHeaderInTable(sensitivityTableView1);
			signedSorterColor1.addMouseListenerToHeaderInTable(sensitivityTableView1);
			absSorterNumber1.addMouseListenerToHeaderInTable(sensitivityTableView1);
			absSorterColor1.addMouseListenerToHeaderInTable(sensitivityTableView1);

			SensitivityTableRenderer render1 = new SensitivityTableRenderer();
			sensitivityTableView1.setDefaultRenderer(ColoredBar.class, 
				render1);
			sensitivityTableView1.setDefaultRenderer(JToggleButton.class, 
				render1);	//add for neil

			sensitivityTableView1.setSelectionMode(0);
			sensitivityTableView1.setCellSelectionEnabled(true);
			JScrollPane varScrollPane1 = new JScrollPane(sensitivityTableView1);
			varScrollPane1.setBackground(Color.white);
			varTabbedPane = new JTabbedPane();
			varTabbedPane.addTab(frame.getNolResourceString(OUTPUTMODEL), varScrollPane);
			varTabbedPane.setSelectedIndex(0);
			varTabbedPane.addTab(frame.getNolResourceString(STATEMODEL), varScrollPane1);
			return varTabbedPane;
		}else{
			return varScrollPane;
		}

	}

	private void turnOffAutoColumn(JTable table){
		int cc = table.getColumnCount();
		if(cc>4){
			table.setAutoResizeMode(JTable.AUTO_RESIZE_OFF);
			setMinWithColumn(table);
		}else{
			table.setAutoResizeMode(JTable.AUTO_RESIZE_ALL_COLUMNS);
		}
		table.getTableHeader().setReorderingAllowed(false);

		TableColumnModel cm = table.getColumnModel();
		TableColumn cl = cm.getColumn(cc-1);
		cl.setPreferredWidth(LASTCOLUMNWIDTH);
	}

	private void setMinWithColumn(JTable table){
		TableColumnModel cm = table.getColumnModel();
		int cc = cm.getColumnCount();
		for(int i=0;i<cc;i++){
		TableColumn cl = cm.getColumn(i);
			cl.setMinWidth(COLUMNWIDTH);
		}

	}


	private JPanel getControlPanel(){
		JPanel control = new JPanel();
		control.setBackground(getModelNamePanel().getBackground());
		control.setLayout(new BoxLayout(control, BoxLayout.Y_AXIS));
		control.setBorder(new EmptyBorder(10, 10, 10, 10));

/*		JPanel controlButtonPane = new JPanel(new GridLayout(2,1,5,5));
		calculateBut = new JButton(frame.getNolResourceString(CALCULATE));
		calculateBut.setActionCommand("Calculate");
		calculateBut.addActionListener(actionListener);
  		controlButtonPane.add(calculateBut);
		JButton but = new JButton("Report...");
		but.addActionListener(actionListener);
// 		controlButtonPane.add(but);
*/

		JPanel showRadioButtonPane = new JPanel(new GridLayout(2,1,5,5));
		showRadioButtonPane.setBorder(new TitledBorder(frame.getNolResourceString(SHOW)+":"));
		ButtonGroup group = new ButtonGroup();
		JRadioButton radio = new JRadioButton(frame.getNolResourceString(CHART),true);
		radio.setActionCommand("Chart");
		radio.addActionListener(actionListener);
		group.add(radio);
 		showRadioButtonPane.add(radio);
		radio = new JRadioButton(frame.getNolResourceString(NUMBER));
		radio.setActionCommand("Number");
		radio.addActionListener(actionListener);
		group.add(radio);
 		showRadioButtonPane.add(radio);

		JPanel valueRadioButtonPane = new JPanel(new GridLayout(2,1,5,5));
		valueRadioButtonPane.setBorder(new TitledBorder(frame.getNolResourceString(VALUE)+":"));
		group = new ButtonGroup();
		radio = new JRadioButton(frame.getNolResourceString(SIGNED),true);
		radio.setActionCommand("Signed");
		radio.addActionListener(actionListener);
		group.add(radio);
 		valueRadioButtonPane.add(radio);
		radio = new JRadioButton(frame.getNolResourceString(ABSOLUTE));
		radio.setActionCommand("Absolute");
		radio.addActionListener(actionListener);
		group.add(radio);
 		valueRadioButtonPane.add(radio);

		JPanel controlButtonPane = new JPanel(new GridLayout(2,1,5,5));
		exportBut = new JButton(frame.getNolResourceString(EXPORT));
		exportBut.setActionCommand("Export");
		exportBut.addActionListener(actionListener);
		exportBut.setEnabled(false);
 		controlButtonPane.add(exportBut);

		exportParaBut = new JButton(frame.getNolResourceString(EXPORTPARAMETER));
		exportParaBut.setActionCommand("ExportParameters");
		exportParaBut.addActionListener(actionListener);
		exportParaBut.setEnabled(false);
 		controlButtonPane.add(exportParaBut);

		control.add(Box.createRigidArea(NolMainFrame.vpad15));
		control.add(showRadioButtonPane);
		control.add(valueRadioButtonPane);
		control.add(Box.createRigidArea(NolMainFrame.vpad15));
		control.add(controlButtonPane);
		control.add(Box.createRigidArea(NolMainFrame.vpad500));
		control.add(Box.createVerticalGlue());
		return control;
	}
	
	private void initDataDisplay(){
		
		int ni = inputVars.size();
		int no = outputVars.size();
		signedSensitivityValues = Matlib.createMatrix(ni,no);
		absSensitivityValues = Matlib.createMatrix(ni,no);
		scaledSignedSensitivityValues = Matlib.createMatrix(ni,no);
		scaledAbsSensitivityValues = Matlib.createMatrix(ni,no);
		for(int c=0;c<no;c++){
			for(int r=0;r<ni;r++){
				signedSensitivityValues.set(r,c,Double.NaN);
				absSensitivityValues.set(r,c,Double.NaN);
			}
		}
		Matlib.copy(signedSensitivityValues,scaledSignedSensitivityValues);
		Matlib.copy(absSensitivityValues,scaledAbsSensitivityValues);

		if(hasTwoEnsembles){
			ni = stateInputVars.size();
			no = stateOutputVars.size();
			signedSensitivityValues1 = Matlib.createMatrix(ni,no);
			absSensitivityValues1 = Matlib.createMatrix(ni,no);
			scaledSignedSensitivityValues1 = Matlib.createMatrix(ni,no);
			scaledAbsSensitivityValues1 = Matlib.createMatrix(ni,no);
			for(int c=0;c<no;c++){
				for(int r=0;r<ni;r++){
					signedSensitivityValues1.set(r,c,Double.NaN);
					absSensitivityValues1.set(r,c,Double.NaN);
				}
			}
			Matlib.copy(signedSensitivityValues1,scaledSignedSensitivityValues1);
			Matlib.copy(absSensitivityValues1,scaledAbsSensitivityValues1);
		}

	}

	public NolModel2 getModel(){
		return model;
	}
	
	
	private void refreshSensitivityDataDisplay(){
		if(!isCalculated)
			calculateSensitivities();
	}
	
	public void calculateSensitivities(){
		if(hasTwoEnsembles){
			SensitivityThread senThread = new SensitivityThread(this, model, 
				signedSensitivityValues,absSensitivityValues, inputVars, sampleMatrix,
				signedSensitivityValues1,absSensitivityValues1, stateInputVars, sampleMatrix1);
			Thread thread = new Thread(senThread);
			int prior = thread.getPriority()-3;
			if(prior <Thread.MIN_PRIORITY) {
				prior = Thread.MIN_PRIORITY;
			}
			thread.setPriority(prior);
			thread.start();
		}else{
			SensitivityThread senThread = new SensitivityThread(this, model, 
				signedSensitivityValues,absSensitivityValues, inputVars, sampleMatrix);
			Thread thread = new Thread(senThread);
			int prior = thread.getPriority()-3;
			if(prior <Thread.MIN_PRIORITY) {
				prior = Thread.MIN_PRIORITY;
			}
			thread.setPriority(prior);
			thread.start();
		}	
	}

	public void endSensitivityCalculation(){
		int ni = inputVars.size();
		int no = outputVars.size();
		Matlib.copy(signedSensitivityValues,scaledSignedSensitivityValues);
		Matlib.copy(absSensitivityValues,scaledAbsSensitivityValues);
		double[] maxAbsValue1 = new double[no];
		double[] maxAbsValue2 = new double[no];
		for(int c=0;c<no;c++){
			maxAbsValue1[c] = 0;
			maxAbsValue2[c] = 0;
			for(int r=0;r<ni;r++){
				double v = Math.abs(signedSensitivityValues.get(r,c));
				if(v>maxAbsValue1[c])
					maxAbsValue1[c] = v;
				v = Math.abs(absSensitivityValues.get(r,c));
				if(v>maxAbsValue2[c])
					maxAbsValue2[c] = v;
			}
		}
		for(int c=0;c<no;c++){
			if(maxAbsValue1[c] >0){
				double scalor = 1.0/maxAbsValue1[c];
				for(int r=0;r<ni;r++){
					scaledSignedSensitivityValues.set(r,c,scaledSignedSensitivityValues.get(r,c)*scalor);
				}
			}
			if(maxAbsValue2[c] >0){
				double scalor = 1.0/maxAbsValue2[c];
				for(int r=0;r<ni;r++){
					scaledAbsSensitivityValues.set(r,c,scaledAbsSensitivityValues.get(r,c)*scalor);
				}
			}
		}

		signedSensitivityTableModel.setValues(signedSensitivityValues);
		absSensitivityTableModel.setValues(absSensitivityValues);

		signedSensitivityColorTableModel.setValues(scaledSignedSensitivityValues);
		absSensitivityColorTableModel.setValues(scaledAbsSensitivityValues);
		sensitivityTableView.repaint(0l);
		sensitivityTableView.validate();

		if(hasTwoEnsembles){
			ni = stateInputVars.size();
			no = stateOutputVars.size();
			Matlib.copy(signedSensitivityValues1,scaledSignedSensitivityValues1);
			Matlib.copy(absSensitivityValues1,scaledAbsSensitivityValues1);
			maxAbsValue1 = new double[no];
			maxAbsValue2 = new double[no];
			for(int c=0;c<no;c++){
				maxAbsValue1[c] = 0;
				maxAbsValue2[c] = 0;
				for(int r=0;r<ni;r++){
					double v = Math.abs(signedSensitivityValues1.get(r,c));
					if(v>maxAbsValue1[c])
						maxAbsValue1[c] = v;
					v = Math.abs(absSensitivityValues1.get(r,c));
					if(v>maxAbsValue2[c])
						maxAbsValue2[c] = v;
				}
			}
			for(int c=0;c<no;c++){
				if(maxAbsValue1[c] >0){
					double scalor = 1.0/maxAbsValue1[c];
					for(int r=0;r<ni;r++){
						scaledSignedSensitivityValues1.set(r,c,scaledSignedSensitivityValues1.get(r,c)*scalor);
					}
				}
				if(maxAbsValue2[c] >0){
					double scalor = 1.0/maxAbsValue2[c];
					for(int r=0;r<ni;r++){
						scaledAbsSensitivityValues1.set(r,c,scaledAbsSensitivityValues1.get(r,c)*scalor);
					}
				}
			}
			signedSensitivityTableModel1.setValues(signedSensitivityValues1);
			absSensitivityTableModel1.setValues(absSensitivityValues1);

			signedSensitivityColorTableModel1.setValues(scaledSignedSensitivityValues1);
			absSensitivityColorTableModel1.setValues(scaledAbsSensitivityValues1);
			sensitivityTableView1.repaint(0l);
			sensitivityTableView1.validate();
		}
		isCalculated = true;
		exportBut.setEnabled(true);
		exportParaBut.setEnabled(true);
		exportString = sensitivityToString();

	}

/** Control action implementation */
    class ControlAction extends AbstractAction {
		boolean calculatePressed = false;
		ControlAction(){super("controlAction");}
			
		@Override
		public void actionPerformed(ActionEvent e) {
			if(noFire) {
				return;
			}
			String command = e.getActionCommand();
			if(command.equals("Calculate")){
				if(calculatePressed) {
					return;
				}
				calculatePressed = true;
				refreshSensitivityDataDisplay();
				calculatePressed = false;
			}else if(command.equals("Export")){
				frame.exportStringAction(model.getName()+"_sen",exportString);
			}else if(command.equals("ExportParameters")){
				Object paraObj = newParametersToObject();
				if(paraObj.equals("")){
					frame.showOKDialog("There is no input variable selected.");
				}else{
					frame.exportStringAction(model.getName()+"_para",paraObj);
				}
			}else if(command.equals("Signed")){
  				if(!isAbsolute) {
  					return;
  				}
				infoLabel.setText(frame.getNolResourceString(SIGNEDDEFINITION));
				if(isChart){
//					sensitivityTableView.setModel(signedSorterColor);	
					sensitivityTableView.setModel(signedSorterColor);	
					sensitivityTableView.sizeColumnsToFit(-1);
					if(hasTwoEnsembles){
						sensitivityTableView1.setModel(signedSorterColor1);	
						sensitivityTableView1.sizeColumnsToFit(-1);
					}
				}else{
//					sensitivityTableView.setModel(signedSensitivityTableModel);	
					sensitivityTableView.setModel(signedSorterNumber);	
					sensitivityTableView.sizeColumnsToFit(-1);
					if(hasTwoEnsembles){
						sensitivityTableView1.setModel(signedSorterNumber1);			
						sensitivityTableView1.sizeColumnsToFit(-1);
					}
				}
				sensitivityTableView.repaint(0l);
				sensitivityTableView.validate();
				if(hasTwoEnsembles){
					sensitivityTableView1.repaint(0l);
					sensitivityTableView1.validate();
				}
				isAbsolute = false;
			}else if(command.equals("Absolute")){
  				if(isAbsolute){
  					return;
  				}
				infoLabel.setText(frame.getNolResourceString(ABSDEFINITION));
				if(isChart){
					sensitivityTableView.setModel(absSorterColor);	
					sensitivityTableView.sizeColumnsToFit(-1);
					if(hasTwoEnsembles){
						sensitivityTableView1.setModel(absSorterColor1);	
						sensitivityTableView1.sizeColumnsToFit(-1);
					}
				}else{
					sensitivityTableView.setModel(absSorterNumber);	
					sensitivityTableView.sizeColumnsToFit(-1);
					if(hasTwoEnsembles){
						sensitivityTableView1.setModel(absSorterNumber1);	
						sensitivityTableView1.sizeColumnsToFit(-1);
					}
				}
				sensitivityTableView.repaint(0l);
				sensitivityTableView.validate();
				if(hasTwoEnsembles){
					sensitivityTableView1.repaint(0l);
					sensitivityTableView1.validate();
				}
				isAbsolute = true;
			}else if(command.equals("Number")){
				if(!isChart) {
					return;
				}
				if(isAbsolute){
					sensitivityTableView.setModel(absSorterNumber);	
					sensitivityTableView.sizeColumnsToFit(-1);
					if(hasTwoEnsembles){
						sensitivityTableView1.setModel(absSorterNumber1);
						sensitivityTableView1.sizeColumnsToFit(-1);
					}
				}else{
					sensitivityTableView.setModel(signedSorterNumber);	
					sensitivityTableView.sizeColumnsToFit(-1);
					if(hasTwoEnsembles){
						sensitivityTableView1.setModel(signedSorterNumber1);
						sensitivityTableView1.sizeColumnsToFit(-1);
					}
				}
				sensitivityTableView.repaint(0l);
				sensitivityTableView.validate();
				if(hasTwoEnsembles){
					sensitivityTableView1.repaint(0l);
					sensitivityTableView1.validate();
				}
				isChart = false;
			}else if(command.equals("Chart")){
				if(isChart) {
					return;
				}
				if(isAbsolute){
					sensitivityTableView.setModel(absSorterColor);
					sensitivityTableView.sizeColumnsToFit(-1);
					if(hasTwoEnsembles){
						sensitivityTableView1.setModel(absSorterColor1);
						sensitivityTableView1.sizeColumnsToFit(-1);
					}
				}else{
					sensitivityTableView.setModel(signedSorterColor);
					sensitivityTableView.sizeColumnsToFit(-1);
					if(hasTwoEnsembles){
						sensitivityTableView1.setModel(signedSorterColor1);
						sensitivityTableView1.sizeColumnsToFit(-1);
					}
				}
				sensitivityTableView.repaint(0l);
				sensitivityTableView.validate();
				if(hasTwoEnsembles){
					sensitivityTableView1.repaint(0l);
					sensitivityTableView1.validate();
				}
				isChart = true;
			}else{
			} 
		}
    }


	class SensitivityTableModel extends AbstractTableModel{
		private int row,col;
		private String[] colHd;
		private String[] rowHd;
		private Vector inputs, outputs;
		private Matrix values = null;

		public SensitivityTableModel(Vector inputs, Vector outputs){
			this.inputs = inputs;
			this.outputs = outputs;
			row = inputs.size();
			col = outputs.size()+1;
			colHd = new String[col+1];
			rowHd = new String[row];		
			colHd[0] = frame.getNolResourceString(VARIABLENAME);			
			colHd[col] = frame.getNolResourceString(USEDFORFUTURE);			
			for(int i=1;i<col;i++){
				colHd[i] = outputs.elementAt(i-1).toString();
			}
			for(int i=0;i<row;i++){
				rowHd[i] = inputs.elementAt(i).toString();
			}
		}
		@Override
		public int getColumnCount() { return col+1; }
		@Override
		public int getRowCount() { return row;}
		
		public void setValues(Matrix values){
			this.values = values;
		}

		@Override
		public Object getValueAt(int r, int c){
			if(c == 0){
				return rowHd[r];
			}else {
				if(values == null) {
					return "";
				}
				if(c == col){
					return usedchecks.elementAt(r);
				}else if(Double.isNaN(values.get(r,c-1))){
					return "";
				}else{
					return Utilities.formatDouble(values.get(r,c-1), sigDigits);
				}
			}
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
		@Override
		public Class getColumnClass(int c) {
			return getValueAt(0, c).getClass();
		}
	}


	class SensitivityColorTableModel extends AbstractTableModel{
		private int row,col;
		private String[] colHd;
		private String[] rowHd;
		private ColoredBar[][] blocks;
 		private Vector inputs, outputs;
		private Matrix values = null;

		public SensitivityColorTableModel(Vector inputs, Vector outputs){
			this.inputs = inputs;
			this.outputs = outputs;
			row = inputs.size();
			col = outputs.size()+1;

			colHd = new String[col+1];	  	//add for neil
			rowHd = new String[row];		
			
			colHd[0] = frame.getNolResourceString(VARIABLENAME);
			colHd[col] = frame.getNolResourceString(USEDFORFUTURE);
			
			for(int i=1;i<col;i++){
				colHd[i] = outputs.elementAt(i-1).toString();
			}
			for(int i=0;i<row;i++){
				rowHd[i] = inputs.elementAt(i).toString();
			}
			blocks = new ColoredBar[row][col-1];
			for(int c=0;c<col-1;c++){
				for(int r=0;r<row;r++){
					blocks[r][c] = new ColoredBar(Color.white, true, 1.0, 1);
				}
			}

		}

		@Override
		public int getColumnCount() { return col+1; }
		@Override
		public int getRowCount() { return row;}

		@Override
		public Object getValueAt(int r, int c){
			if(c == 0){
				return rowHd[r];
			}else if(c == col){
				return usedchecks.elementAt(r);
			}else {
				return blocks[r][c-1];
			}
		}

		@Override
		public String getColumnName(int c) {
			return colHd[c];
		}

		@Override
		public boolean isCellEditable(int r, int c) {
			return false;
		}
		
		public void setValues(Matrix values) {
			this.values = values;
			for(int c=1;c<col;c++){
				boolean neg = false;
				boolean pos = false;
				int flag =0;
 				for(int r=0;r<row;r++){
					double val = values.get(r,c-1);
					if(val >0) {
						pos = true;
					}
					if(val <0) {
						neg = true;
					}
				}
 				
 				if (pos && !neg) {
					flag = 1;
 				} else if (neg && !pos) {
					flag = -1;
				}
				
				for(int r=0;r<row;r++){
					double val = values.get(r,c-1);
					if(Double.isNaN(val)){
						blocks[r][c-1].setShowColor(Color.white);
					}else{
						if(val >= 0){
							blocks[r][c-1].setShowColor(new Color(255,0,0));
						}else{
							blocks[r][c-1].setShowColor(new Color(0,0,255));
						}
						blocks[r][c-1].setValue(val);
						blocks[r][c-1].setFlag(flag);
					}
				}
			}
		}


		@Override
		public void setValueAt(Object aValue, int r, int c) {
		}

		@Override
		public Class getColumnClass(int c) {
			return getValueAt(0, c).getClass();
		}

	}


	class SensitivityTableRenderer extends JComponent 
		implements TableCellRenderer, java.io.Serializable{
		@Override
		public Component getTableCellRendererComponent(JTable table,
                                               Object value,
                                               boolean isSelected,
                                               boolean hasFocus,
                                               int row,
                                               int column){
			if(value instanceof ColoredBar){
				ColoredBar block = (ColoredBar)value;
				return 	block;
			}
			
			if(value instanceof JToggleButton){
				JPanel cell = new JPanel(new FlowLayout(FlowLayout.CENTER,0,0));
				cell.setBackground(Color.white);
				JToggleButton check = (JToggleButton)value;
				if(isSelected){
					check.setSelected(!check.isSelected());
					table.clearSelection();
				}
				cell.add(check);
				return 	cell;
			}
			
			return null;
		}
	}

	
	private String sensitivityToString() {
		int sizeB = signedSensitivityValues.getRows()*signedSensitivityValues.getCols()*8;
		sizeB = sizeB + absSensitivityValues.getRows()*absSensitivityValues.getCols()*8;
		if(hasTwoEnsembles){
			sizeB = sizeB + signedSensitivityValues1.getRows()*signedSensitivityValues1.getCols()*8;
			sizeB = sizeB + absSensitivityValues1.getRows()*absSensitivityValues1.getCols()*8;
		}			

		StringBuffer s = new StringBuffer(sizeB);  // estimate size
		
		s.append("signed Sensitivity Values:\n");
		s.append("Variable_Name");
		int	col = outputVars.size();
		for(int i=0;i<col;i++){
			s.append("\t");
			s.append(outputVars.elementAt(i).toString());
		}
		s.append("\n");
		int row = signedSensitivityValues.getRows();
		for(int r=0;r<row;r++){
			s.append(inputNameWithDelays.elementAt(r).toString());
			for(int c=0;c<col;c++){
				s.append("\t");
				String vstr = "";
				if(!Double.isNaN(signedSensitivityValues.get(r,c))){
					vstr = Utilities.formatDouble(signedSensitivityValues.get(r,c), sigDigits);
				}
				s.append(vstr);
			}
			s.append("\n");
		}
 			
		s.append("\n");
		s.append("absolute Sensitivity Values:\n");
		s.append("Variable_Name");
		col = outputVars.size();
		for(int i=0;i<col;i++){
			s.append("\t");
			s.append(outputVars.elementAt(i).toString());
		}
		s.append("\n");
		row = absSensitivityValues.getRows();
		for(int r=0;r<row;r++){
			s.append(inputNameWithDelays.elementAt(r).toString());
			for(int c=0;c<col;c++){
				s.append("\t");
				String vstr = "";
				if(!Double.isNaN(absSensitivityValues.get(r,c))){
					vstr = Utilities.formatDouble(absSensitivityValues.get(r,c), sigDigits);
				}
				s.append(vstr);
			}
			s.append("\n");
		}
 			
		if(hasTwoEnsembles){
			s.append("signed Sensitivity Values for state model:\n");
			s.append("Variable_Name");
			col = stateOutputVars.size();
			for(int i=0;i<col;i++){
				s.append("\t");
				s.append(stateOutputVars.elementAt(i).toString());
			}
			s.append("\n");
			row = signedSensitivityValues1.getRows();
			for(int r=0;r<row;r++){
				s.append(stateInputVars.elementAt(r).toString());
				for(int c=0;c<col;c++){
					s.append("\t");
					String vstr = "";
					if(!Double.isNaN(signedSensitivityValues1.get(r,c))){
						vstr = Utilities.formatDouble(signedSensitivityValues1.get(r,c), sigDigits);
					}
					s.append(vstr);
				}
				s.append("\n");
			}
 				
			s.append("\n");
			s.append("absolute Sensitivity Values for state model:\n");
			s.append("Variable_Name");
			col = stateOutputVars.size();
			for(int i=0;i<col;i++){
				s.append("\t");
				s.append(stateOutputVars.elementAt(i).toString());
			}
			s.append("\n");
			row = absSensitivityValues1.getRows();
			for(int r=0;r<row;r++){
				s.append(stateInputVars.elementAt(r).toString());
				for(int c=0;c<col;c++){
					s.append("\t");
					String vstr = "";
					if(!Double.isNaN(absSensitivityValues1.get(r,c))){
						vstr = Utilities.formatDouble(absSensitivityValues1.get(r,c), sigDigits);
					}
					s.append(vstr);
				}
				s.append("\n");
			}
		}			
		return s.toString();
	}
	
	
	
	private Object newParametersToObject() {
		int validInputsNumber = 0;
		Vector inputs = new Vector();
		Vector inputsDelays = new Vector();
		Vector outputsDelays = new Vector();
		int typeFlag = 0;
		if(model instanceof NolOptimizeModel){
			typeFlag = 1;
		}
		if(typeFlag == 1){
			for(int i=0;i<inputNameWithDelays.size();i++){
				JCheckBox check = (JCheckBox)usedchecks.elementAt(i);
				if(check.isSelected()){
					validInputsNumber++;
					inputs.addElement(inputNameWithDelays.elementAt(i));
					inputsDelays.addElement(new long[0]);
				}
			}
		}else{
			Vector outputDelays = (Vector)model.getOutputDelays();
			Vector inputDelays = (Vector)model.getInputDelays();
			Vector inputNames = model.getInputs();

			for(int i=0;i<outputVars.size();i++){
  				long[] dls = (long[])outputDelays.elementAt(i);
				int cc = 0;
				boolean[] selected = new boolean[dls.length];
				for(int j=0;j<dls.length;j++){
					if((dls[j] > 0L)){
						double ddls = dls[j]/60000.0;
						String namewithdelay = (String)outputVars.elementAt(i)+"("+ddls+")";
						int c = inputNameWithDelays.indexOf(namewithdelay);
						JCheckBox check = (JCheckBox)usedchecks.elementAt(c);
						if(check.isSelected()){
							validInputsNumber++;
							cc++;
							selected[j] = true;
						}else{
							selected[j] = false;
						}
					}
				}
				if(cc == 0){
					outputsDelays.addElement(new long[0]);
				}else{
					long[] newdls = new long[cc];
					int c2 = 0;
					for(int j=0;j<dls.length;j++){
						if(selected[j]){
							newdls[c2] = dls[j];
							c2++;
						}
					}
					outputsDelays.addElement(newdls);
				}
			}
			for(int i=0;i<inputNames.size();i++){
  				long[] dls = (long[])inputDelays.elementAt(i);
				if(dls.length == 0 || (dls.length == 1 && dls[0] == 0L)){
					String namewithdelay = (String)inputNames.elementAt(i);
					int c = inputNameWithDelays.indexOf(namewithdelay);
					JCheckBox check = (JCheckBox)usedchecks.elementAt(c);
					if(check.isSelected()){
						validInputsNumber++;
						inputs.addElement(inputNames.elementAt(i));
						inputsDelays.addElement(dls);
					}
				}else {
			 		boolean[] selected = new boolean[dls.length];
					int vn = 0;
					for(int j=0;j<dls.length;j++){
						double ddls = dls[j]/60000.0;
						String namewithdelay = (String)inputNames.elementAt(i)+"("+ddls+")";
						int c = inputNameWithDelays.indexOf(namewithdelay);
						JCheckBox check = (JCheckBox)usedchecks.elementAt(c);
						if(check.isSelected()){
							vn++;
							validInputsNumber++;
							selected[j] = true;
						}
					}
					if(vn>0){
						inputs.addElement(inputNames.elementAt(i));
						long[] newdls = new long[vn];
						int l=0;
						for(int j=0;j<dls.length;j++){
							if(selected[j]){
								newdls[l] = dls[j];
								l++;
							}
						}
						inputsDelays.addElement(newdls);
					}
				}
			}
		}
		
		if(validInputsNumber == 0){
			return "";
		}
		NolModelParameter modelPara = new NolModelParameter();
		modelPara.name=model.getName();
		modelPara.preprocessorName = model.getPreprocessor().getName();
		modelPara.inputs=inputs;
		modelPara.inputDelays=inputsDelays;
		modelPara.outputs=outputVars;
		modelPara.outputDelays=new Vector();
		modelPara.delayTimeUnit=model.getDelayTimeUnit();
		modelPara.isTrained=model.isTrained();
		modelPara.hasTimeStamps=model.getHasTimeStamps();
		modelPara.comment=model.getComment();
		modelPara.typeFlag=typeFlag;
		return modelPara;	
	}
}


