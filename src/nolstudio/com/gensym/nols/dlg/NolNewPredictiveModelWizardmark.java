package com.gensym.nols.dlg;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.io.*;
import java.net.URL;

import com.sun.java.swing.text.*;
import com.sun.java.swing.*;
import com.sun.java.swing.event.*;
import com.sun.java.swing.table.*;
import com.sun.java.swing.border.*;

import com.gensym.math.Utilities;
import com.gensym.math.*;
import com.gensym.math.datafit.*;
import com.gensym.math.matrix.*;
import com.gensym.math.rank.*;
import com.gensym.math.stats.Stats;

import com.gensym.nols.data.*;
import com.gensym.nols.main.*;

import com.gensym.DEBUG;

public class NolNewPredictiveModelWizard  extends NolWizardDialog
	implements NolNewModelWizard{


	private	JTextField modelName;
	private	JTextField caseName;
	private	JTextField dataSeriesName;
	private JTextArea modelDescript;
	private JTextField ratingThreshold;
	private JButton advancedStruct;
	private JButton calculateDelay;
	private JList caseList;
	private JList dataSeriesList;
	private DefaultListModel caseListModel;
	private DefaultListModel dataSeriesListModel;

	private AdvancedDialog advancedDialog;

	private ControlAction actionListener;

	private	VarClassifyTableModel varClassifyTableModel;
	private	JTable varClassifyTableView;

	private	DelayTableModel delayTableModel;
	private	JTable delayTableView;

	private	AutoSelectionTableModel autoSelectionTableModel;
	private	JTable autoSelectionTableView;

	private JRadioButton autoStructFlag;
	private JRadioButton manualStructFlag;
	private JLabel numOfVariable;
	private JLabel numOfSample;

	private NolMainFrame frame;	 

	private boolean noFire;

	// parameters for modeling.

	private Preprocessor preprocessor;
	private DataSeries dataSeries;
	private NolModel model;
	private Vector varNames;
	private Vector usedVarNames;
	private Vector outVarNames;
	private boolean[] varDelayCalculated;
	private Vector delays;
	private int[] delayIntervals;
	private Vector delaysSettings;
	private Vector varRatings;
	private double ratingThresholdValue;

	public NolNewPredictiveModelWizard (NolMainFrame dw) {
		super((JFrame)dw, "Create New Predictive Model", true, 7);
		frame = (NolMainFrame)dw;
		actionListener = new ControlAction();
		noFire = false;
		varNames = new Vector();
		usedVarNames= new Vector();
		outVarNames = new Vector();
		delays = new Vector();
		delaysSettings = new Vector();
		varRatings = new Vector();
		ratingThresholdValue = 3.0;
		initializeLayout();
		initDataDisplay();
	}

	private void initializeLayout(){

		stepPanes.setElementAt(getGeneralPanel(),0);
		stepPanes.setElementAt(getCasePanel(),1);
		stepPanes.setElementAt(getDataSourcePanel(),2);
		stepPanes.setElementAt(getClassificationPanel(),3);
		stepPanes.setElementAt(getDelayPane(),4);
		stepPanes.setElementAt(getSettingPane(),5);
		stepPanes.setElementAt(getStructurePane(),6);
	}

	private JPanel getGeneralPanel(){
		JPanel genPane = new JPanel(new BorderLayout());
		URL url = this.getClass().getResource("../images/largePredictiveModel.gif");
		ImageIcon importIcon = new ImageIcon(url);

		JPanel infoPane = new JPanel(new BorderLayout());
 		infoPane.setBorder(new EmptyBorder(10,10,10,10));

		String s = "A predictive model is used to calculate one \n"+
			       "or more output variables as a function of other\n"+
				   "input variables."
			;
		
		JTextArea infoLabel = new JTextArea(s);
		infoLabel.setEditable(false);
		infoPane.add("Center",infoLabel);
		infoPane.add("West",new JLabel(importIcon));

		genPane.add("North",infoPane);

		JPanel cenPane = new JPanel(new BorderLayout());
		JPanel namePane = new JPanel(new GridLayout(3,1,10,5));
 		namePane.setBorder(new EmptyBorder(10,10,10,10));
		namePane.add(new JLabel("Enter the name for this model:"));
		modelName = new JTextField();
		namePane.add(modelName);
		namePane.add(new JLabel("Comment:"));
 		cenPane.add("North",namePane);

		JPanel descripPane = new JPanel(new GridLayout());
 		descripPane.setBorder(new EmptyBorder(0,10,10,10));
		modelDescript = new JTextArea();
		descripPane.add(modelDescript);
		modelDescript.setBorder(BorderFactory.createLoweredBevelBorder());
 		cenPane.add("Center",descripPane);

 		genPane.add("Center",cenPane);
		return genPane;
	}

	private JPanel getCasePanel(){
		JPanel dataPane = new JPanel(new BorderLayout());
		JPanel infoPane = new JPanel(new GridLayout());
 		infoPane.setBorder(new EmptyBorder(10,10,10,10));
		String s = "What preprocessor has been used to create data for this model? ";
		JTextArea infoLabel = new JTextArea(s);
		infoLabel.setEditable(false);
		infoPane.add(infoLabel);

		dataPane.add("North",infoPane);

		JPanel cenPane = new JPanel(new BorderLayout());
 		cenPane.setBorder(new EmptyBorder(10,10,10,10));

		JPanel sourcePane = new JPanel(new GridLayout(1,2,20,20));
 		sourcePane.setBorder(new EmptyBorder(0,0,10,0));
		sourcePane.add(new JLabel("Preprocessor:"));
		caseName = new JTextField();
		caseName.addActionListener(actionListener);
		sourcePane.add(caseName);

 		cenPane.add("North",sourcePane);

		JPanel listPane = new JPanel(new GridLayout());
		caseList = new JList(getCaseListModel());
		caseList.setBackground(Color.white);
		caseList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		caseList.addListSelectionListener(actionListener);
		JScrollPane listScrollPane = new JScrollPane(caseList);
		listScrollPane.setBorder(BorderFactory.createLoweredBevelBorder());
		listScrollPane.setPreferredSize(NolMainFrame.vpad50);
		listPane.add(listScrollPane);

  		cenPane.add("Center",listPane);

		dataPane.add("Center",cenPane);
		
		return dataPane;
	}

	private JPanel getDataSourcePanel(){
		JPanel dataPane = new JPanel(new BorderLayout());
		JPanel infoPane = new JPanel(new GridLayout());
 		infoPane.setBorder(new EmptyBorder(10,10,10,10));
		String s = "Select one data series as the source of data for this model:";
		JTextArea infoLabel = new JTextArea(s);
		infoLabel.setEditable(false);
		infoLabel.setBackground(Color.lightGray);
		infoPane.add(infoLabel);

		dataPane.add("North",infoPane);

		JPanel cenPane = new JPanel(new BorderLayout());
 		cenPane.setBorder(new EmptyBorder(10,10,10,10));

		JPanel sourcePane = new JPanel(new GridLayout(1,2,10,10));
 		sourcePane.setBorder(new EmptyBorder(0,0,10,0));
		sourcePane.add(new JLabel("Data Series:"));
		dataSeriesName = new JTextField();
		sourcePane.add(dataSeriesName);

 		cenPane.add("North",sourcePane);

		JPanel listPane = new JPanel(new GridLayout());
		dataSeriesList = new JList(getDataSeriesListModel());
		dataSeriesList.setBackground(Color.white);
		dataSeriesList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		dataSeriesList.addListSelectionListener(actionListener);
		JScrollPane listScrollPane = new JScrollPane(dataSeriesList);
		listScrollPane.setBorder(BorderFactory.createLoweredBevelBorder());
		listScrollPane.setPreferredSize(NolMainFrame.vpad50);
		listPane.add(listScrollPane);

  		cenPane.add("Center",listPane);

		JPanel numPane = new JPanel(new GridLayout(1,4,10,10));
 		numPane.setBorder(new EmptyBorder(10,0,10,0));
		numPane.add(new JLabel("Variable:"));
		numOfVariable  = new JLabel();
		numPane.add(numOfVariable);
		numPane.add(new JLabel("Sample:"));
		numOfSample  = new JLabel();
		numPane.add(numOfSample);

  		cenPane.add("South",numPane);

		dataPane.add("Center",cenPane);
		
		return dataPane;
	}
 	private JPanel getClassificationPanel(){
		JPanel classPane = new JPanel(new BorderLayout());
		JPanel infoPane = new JPanel(new GridLayout());
 		infoPane.setBorder(new EmptyBorder(10,10,10,10));
		String s = "Designate inputs and outputs for this model.  If a variable \n"+
			"should not be used, check the unused button..";
		JTextArea infoLabel = new JTextArea(s);
		infoLabel.setEditable(false);
		infoLabel.setBackground(Color.lightGray);
		infoPane.add(infoLabel);
		classPane.add("North",infoPane);
 	
		JPanel cenPane = new JPanel(new GridLayout());
 		cenPane.setBorder(new EmptyBorder(10,10,10,10));
		JPanel varPane = new JPanel(new GridLayout());
		varPane.setBorder(BorderFactory.createTitledBorder("Variable:"));

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

		return classPane;
	}

 	private JPanel getDelayPane(){
		JPanel delayPane = new JPanel(new BorderLayout());
		JPanel infoPane = new JPanel(new GridLayout());
 		infoPane.setBorder(new EmptyBorder(10,10,10,10));
		String s = "You can specify delays to account for time lags between \n"+
			       "inputs and outputs.  Delays are measured in terms of \n"+
				   "number of rows relative to the output.  You can specify\n"+
				   "multiple delays on any input.  For example, if you want \n"+
				   "to include delays of 20, 30, and 40 rows, choose Min \n"+
				   "Delay = 20, Max Delay = 40, and Interval = 10.";
		JTextArea infoLabel = new JTextArea(s);
		infoLabel.setEditable(false);
		infoLabel.setBackground(Color.lightGray);
		infoPane.add(infoLabel);
		delayPane.add("North",infoPane);

		JPanel cenPane = new JPanel(new GridLayout());
 		cenPane.setBorder(new EmptyBorder(10,10,10,10));
  		JPanel delPane = new JPanel(new GridLayout());
		delPane.setBorder(BorderFactory.createTitledBorder("Delays:"));

		delayTableModel = new DelayTableModel();
		delayTableView = new JTable(delayTableModel);
		delayTableView.setSelectionMode(0);
		delayTableView.setSelectionBackground(Color.white);
		delayTableView.setCellSelectionEnabled(true);
		delayTableView.setSelectionForeground(Color.black);
		JScrollPane listScrollPane = new JScrollPane(delayTableView);
		listScrollPane.setBackground(Color.white);
		delPane.add(listScrollPane);

		cenPane.add(delPane);
		delayPane.add("Center",cenPane);

		return delayPane;
	}

 	private JPanel getSettingPane(){
		JPanel setPane = new JPanel(new BorderLayout());
		JPanel infoPane = new JPanel(new GridLayout());
 		infoPane.setBorder(new EmptyBorder(10,10,10,10));
		String s = "If you would like the program to pre-screen the inputs to \n"+
			       "determine which variables are statistically correlated \n"+
				   "with the outputs, select the \"Calculate Ratings\" button.\n"+
				   "If the check mark in the \"Used\" column disappears, there \n"+
				   "is no apparent correlation to the given level of \n"+
				   "significance with the outputs. You can change the selection\n"+
				   "threshold, or manually change the check boxes in the \"Used\"\n"+
				   "column to override the automatic selection.";
		JTextArea infoLabel = new JTextArea(s);
		infoLabel.setEditable(false);
		infoLabel.setBackground(Color.lightGray);
		infoPane.add(infoLabel);
		setPane.add("North",infoPane);

		JPanel cenPane = new JPanel(new GridLayout());
 		cenPane.setBorder(new EmptyBorder(10,10,10,10));
 		JPanel autoPane = new JPanel(new BorderLayout());
		autoPane.setBorder(BorderFactory.createTitledBorder("Automatically Select Variables & Calculate Delays:"));

		autoSelectionTableModel = new AutoSelectionTableModel();
		autoSelectionTableView = new JTable(autoSelectionTableModel);
		autoSelectionTableView.setDefaultRenderer(AbstractButton.class, 
			new AutoSelectRenderer());
		autoSelectionTableView.setSelectionMode(0);
		autoSelectionTableView.setSelectionBackground(Color.white);
		autoSelectionTableView.setCellSelectionEnabled(true);
		autoSelectionTableView.setSelectionForeground(Color.black);
		JScrollPane listScrollPane = new JScrollPane(autoSelectionTableView);
		listScrollPane.setBackground(Color.white);

		
		JPanel actPane = new JPanel(new GridLayout(1,3,10,10));
		actPane.setBorder(new EmptyBorder(10, 10, 10, 10));               

		actPane.add(new JLabel("Threshold:", SwingConstants.CENTER));
 		ratingThreshold = new JTextField();
		ratingThreshold.addActionListener(actionListener);
		actPane.add(ratingThreshold);
		calculateDelay = new JButton("Calculate Ratings");
		calculateDelay.addActionListener(actionListener);
		actPane.add(calculateDelay);
		
		autoPane.add("Center",listScrollPane);
		autoPane.add("South",actPane);

		cenPane.add(autoPane);
		setPane.add("Center",cenPane);


		return setPane;
	}

 	private JPanel getStructurePane(){
		JPanel structurePane = new JPanel(new BorderLayout());
		JPanel infoPane = new JPanel(new GridLayout());
 		infoPane.setBorder(new EmptyBorder(10,10,10,10));
		String s = "Automatic structure determination is recommended. \n"+
				   "Select manual setting for model structure only when\n"+
				   "you are expert user.";
		JTextArea infoLabel = new JTextArea(s);
		infoLabel.setEditable(false);
		infoLabel.setBackground(Color.lightGray);
		infoPane.add(infoLabel);
		structurePane.add("North",infoPane);

		JPanel selectPane = new JPanel(new GridLayout(2,1,10,10));
		selectPane.setBorder(new EmptyBorder(20,20,20,20));
		
		ButtonGroup group1 = new ButtonGroup();
		autoStructFlag = new JRadioButton("Auto",true);
		group1.add(autoStructFlag);
  		autoStructFlag.addActionListener(actionListener);

 		manualStructFlag = new JRadioButton("Manual");
		group1.add(manualStructFlag);
  		manualStructFlag.addActionListener(actionListener);

		selectPane.add(autoStructFlag);
		selectPane.add(manualStructFlag);

		JPanel advancePane = new JPanel(new FlowLayout(FlowLayout.LEFT));
		advancePane.setBorder(new EmptyBorder(0,40,0,40));
		advancedStruct = new JButton("Settings..."){
			public float getAlignmentX() { return 1.0f; }			
		};
		advancedStruct.setEnabled(false);
  		advancedStruct.addActionListener(actionListener);
		advancePane.add(advancedStruct);

		JTextArea structDescrip = new JTextArea(){
			Dimension dim = new Dimension(350,70);
			public Dimension getPreferredSize() { return  dim;}			
			public Dimension getMinimumSize() { return  dim;}			
		};
		JScrollPane listScrollPane = new JScrollPane(structDescrip);
		listScrollPane.setBackground(Color.white);
		listScrollPane.setBorder(BorderFactory.createLoweredBevelBorder());
		JPanel pane0 = new JPanel(new GridLayout());
		pane0.setBorder(new TitledBorder(new EmptyBorder(1, 1, 1, 1),               
			"Structure Description:", TitledBorder.LEFT , TitledBorder.TOP));
		pane0.add(listScrollPane);
		advancePane.add(pane0);

		JPanel repane = new JPanel(new BorderLayout());
		repane.add("North",selectPane);
		repane.add("Center", advancePane);

		structurePane.add("Center",repane);

		return structurePane;
	}

	private DefaultListModel getCaseListModel() {
		if (caseListModel == null) {
			caseListModel = new DefaultListModel();
		};	
		return caseListModel;
	}	

	private DefaultListModel getDataSeriesListModel() {
		if (dataSeriesListModel == null) {
			dataSeriesListModel = new DefaultListModel();
		};	
		return dataSeriesListModel;
	}	

	
	public void setVisible(boolean v){
		stepPane.removeAll();
		stepPane.add((JPanel)stepPanes.elementAt(0));
		stepPane.validate();
		stepPane.repaint(0l);
		currentStep = 1;
		modifyStep(true);
		String title = "Create New Predictive Model - "+setTitleForStep(currentStep);
		title = title + " - General";
		setTitle(title);
		super.setVisible(v);
	}

	public void resetData(){
		stepPane.removeAll();
		stepPane.add((JPanel)stepPanes.elementAt(0));
		stepPane.validate();
		stepPane.repaint(0l);
		currentStep = 1;
		modifyStep(false);
		initDataDisplay();
	}

	protected void modifyStep(boolean isNext){
		super.modifyStep(isNext);
		String title = "Create New Predictive Model - "+setTitleForStep(currentStep);
		if(currentStep == 1){
			title = title + " - General";
		}else if(currentStep == 2){
			title = title + " - Preprocessor";
		}else if(currentStep == 3){
			title = title + " - Data Source";
		}else if(currentStep == 4){
			title = title + " - Classification";
		}else if(currentStep == 5){
			title = title + " - Delay";
		}else if(currentStep == 6){
			title = title + " - Settings";
		}else if(currentStep == 7){
			title = title + " - Structure";
		}
		if(DEBUG.debug){
			System.out.println(title);
		}
		setTitle(title);
	}

 	private void initDataDisplay(){
		noFire = true;
		Project project	 = frame.getProject();
		int n = project.getNumberOfPreprocessors();
		if(n<0){
			noFire = false;
			return;
		}
		getCaseListModel().removeAllElements();
		for(int i=0;i<n;i++){
			Preprocessor prep = project.getPreprocessorByIndex(i);
			getCaseListModel().addElement(prep.getName());
		}
		selectedPreprocessor(0);
		caseList.setSelectedIndex(0);
		selectedDataSeries(0);
		dataSeriesList.setSelectedIndex(0);
		int count = 1;
		while(true){
			String mName = "Model"+count;
			if(project.getPredictiveModelIndexByName(mName) == -1 &&
			   project.getOptimizationModelIndexByName(mName) == -1){
				modelName.setText(mName);
				break;
			}
			count++;
		}
		ratingThreshold.setText(Utilities.formatDouble(ratingThresholdValue, 3));
		noFire = false;
	}

	public NolModel getModel(){
		if(model == null) return null;
		return model;
	}

  	public JFrame getFrame(){
		return frame;
	}

	private void selectedPreprocessor(int selectedIndex){
		Project project = frame.getProject();
		preprocessor = project.getPreprocessorByIndex(selectedIndex);
		caseName.setText(preprocessor.getName());
		int d = preprocessor.getNumberOfDataSeries();
		getDataSeriesListModel().removeAllElements();
		for(int i=0;i<d;i++){
			String name = preprocessor.getDataSeriesName(i); 	
			getDataSeriesListModel().addElement(name);
		}
	}

	private void selectedDataSeries(int selectedIndex){
		dataSeries  = preprocessor.getDataSeries(selectedIndex);
		dataSeriesName.setText(dataSeries.getName());
		Vector varObjs = dataSeries.getVarObjects();
		varNames.removeAllElements();
		usedVarNames.removeAllElements();
		outVarNames.removeAllElements();
		delays.removeAllElements();
		delayIntervals = new int[varObjs.size()];
		delaysSettings.removeAllElements();
		varRatings.removeAllElements();

		for(int i=0;i<varObjs.size();i++){
			String name = varObjs.elementAt(i).toString();
			varNames.addElement(name);
			usedVarNames.addElement(name);
			boolean[] delaychecking = new boolean[1];
			delaychecking[0] = true;
			delays.addElement(delaychecking);
			delaysSettings.addElement(new int[2]);
			varRatings.addElement(new double[0]);
		}
		varDelayCalculated = new boolean[varObjs.size()];
		varClassifyTableModel.setNames(varNames);
		delayTableModel.setNames(usedVarNames);
		autoSelectionTableModel.setNames(usedVarNames);
		int row = dataSeries.getRow();
		numOfVariable.setText(String.valueOf(varObjs.size()));
		numOfSample.setText(String.valueOf(row));
	}


	private AdvancedDialog getAdvancedDialog(){	 
		if(advancedDialog == null){
			JFrame frame = getFrame();
			advancedDialog = new AdvancedDialog(frame,"Define Model Advanced Settings",true);
			advancedDialog.setBounds(200,200,550,370);
		}
		return advancedDialog;
	}

	class ControlAction extends AbstractAction implements ListSelectionListener {
		ControlAction() {	super("controlAction");}
        public void actionPerformed(ActionEvent e) {
			if(noFire) return;
			String command = e.getActionCommand();
			if(command.equals("Calculate Ratings")){
				calculateRatings();
			}else if(command.equals("Auto")){
				advancedStruct.setEnabled(false);
			}else if(command.equals("Manual")){
				advancedStruct.setEnabled(true);
			}else if(command.equals("Settings...")){
				getAdvancedDialog().setVisible(true);
  			}else if(command.equals("OKProp")){
				getAdvancedDialog().setVisible(false);
			}else if(command.equals("CancelProp")){
				getAdvancedDialog().setVisible(false);
			}else if(e.getSource() == ratingThreshold){
  				String s = ratingThreshold.getText();
				try{
					double c = Double.valueOf(s).doubleValue();
					if(c>0){
						ratingThresholdValue = c;
						autoSelectionTableModel.goThrouthThreshold();
						autoSelectionTableView.validate();
						autoSelectionTableView.repaint(0l);
					}
				}catch(NumberFormatException  evt){
					ratingThreshold.setText(Utilities.formatDouble(ratingThresholdValue, 3));
				}
			}
		}

		public void valueChanged(ListSelectionEvent e){
			if(!e.getValueIsAdjusting()) return;
			if(noFire) return;
			if(e.getSource() == caseList){
				noFire = true;
				int cindex = caseList.getSelectedIndex();
				if(cindex == -1){
					noFire = false;
					return;
				}
				selectedPreprocessor(cindex);
				selectedDataSeries(0);
				dataSeriesList.setSelectedIndex(0);
				dataSeriesList.validate();
				dataSeriesList.repaint(0l);
				noFire = false;
			}else if(e.getSource() == dataSeriesList){
				noFire = true;
				int dindex = dataSeriesList.getSelectedIndex();
				if(dindex == -1){
					noFire = false;
					return;
				}
				selectedDataSeries(dindex);
				noFire = false;
			}
		}
	
	}				
	
	private void calculateRatings() {
		int col = varNames.size();
		Vector outChecks = varClassifyTableModel.getOutputChecks();
		Vector inChecks = varClassifyTableModel.getInputChecks();
		int outs = 0;
		int ins = 0;
		Vector inVars = new Vector(0,10);
		Vector outVars = new Vector(0,10);
		Vector delays = new Vector(0,10);
		// get variable classification
		for(int i=0;i<col;i++){
			if(((JRadioButton)outChecks.elementAt(i)).isSelected()){
				Sy.set(0,i,1);
				outs++;
				if(!varDelayCalculated[i]){
					Sx.set(0,i,1.0);
					ins++;
					needCalVarNames.addElement(varNames.elementAt(i));
				}
			}else if(((JRadioButton)inChecks.elementAt(i)).isSelected()){
				if(!varDelayCalculated[i]){
					Sx.set(0,i,1.0);
					ins++;
					needCalVarNames.addElement(varNames.elementAt(i));
				}
			}
		}
		if(outs == 0 || ins == 0){	

			return;
		}
		int dsIndex = dataSeriesList.getSelectedIndex();
		DataSeries ds = preprocessor.getDataSeries(dsIndex);
		Matrix RawData = ds.getDataMatrix();
		Matrix XTemp = Matlib.createMatrix();
		Matrix YTemp = Matlib.createMatrix();
		try{
			Matlib.getColumns(RawData,Sy,YTemp);
			Matlib.getColumns(RawData,Sx,XTemp);
			Matlib.clear(XTemp); // memory leak if not cleared; added by Brian O. Bush, Feb 5, 1998
			Matlib.clear(YTemp); // here too!
			Matrix Xdelays = Matlib.createMatrix(ins,3);
			Matrix Ydelays = Matlib.createMatrix(outs,3);
			for(int r=0;r<outs;r++){
				Ydelays.set(r,0,0);
				Ydelays.set(r,1,-1.0);
				Ydelays.set(r,2,1.0);
			}
			int count = 0;
			int[] dsets;
			for(int c=0;c<col;c++){
				if(Sx.get(0,c)==1.0){
					dsets = (int[])delaysSettings.elementAt(c);
					Xdelays.set(count,0,dsets[0]);
					Xdelays.set(count,1,dsets[1]);
					if(delayIntervals[c] == 0){
						Xdelays.set(count,2,1.0);
					}else{
						Xdelays.set(count,2,delayIntervals[c]);
					}
					count++;
				}
			}
			Vector Ratings = new Vector();
			RankThread rankThread = new RankThread(this, inVars, delays, outVars, Ratings);
			Thread rankRunningThread = new Thread(rankThread);
			int prior = rankRunningThread.getPriority()-3;
			if(prior <Thread.MIN_PRIORITY) prior = Thread.MIN_PRIORITY;
			rankRunningThread.setPriority(prior);
			rankRunningThread.start();

		} catch(MathException evt){
			System.err.println("exception in calculateRatings "+ evt.getMessage());
			evt.printStackTrace();
		}
	}

	public void receiveRatingResults(Vector inVars, Vector delays, Vector outVars, Vector ratings) {
	/*	int rsize = Ratings.size();
		int nvc = needCalVarNames.size();
		boolean[][] delayMasks = new boolean[nvc][]; 
		double[][] ratingValues = new double[nvc][]; 
		for(int i=0;i<nvc;i++){
			String n = (String)needCalVarNames.elementAt(i);
			int oldVarIndex = varNames.indexOf(n);
			if(delayIntervals[oldVarIndex] == 0){
				delayMasks[i] = new boolean[1];
				ratingValues[i] = new double[1];
			}else{
				int[] dsets = (int[])delaysSettings.elementAt(oldVarIndex);
				int range = (dsets[1]-dsets[0])/delayIntervals[oldVarIndex]+1;
				delayMasks[i] = new boolean[range];
				ratingValues[i] = new double[range];
			}
		}
		for(int i=0;i<rsize;i++){
			Matrix rates = (Matrix)Ratings.elementAt(i);
			if (DEBUG.debug){
				Matlib.disp(rates);
			}
			int dr = rates.getRows();
			for(int r=0;r<dr;r++){
				int varIndex = (int)rates.get(r,0);
				String n = (String)needCalVarNames.elementAt(varIndex-1);
				int oldVarIndex = varNames.indexOf(n);					
				int del = (int)rates.get(r,1);
				int[] dsets = (int[])delaysSettings.elementAt(oldVarIndex);
				int dIndexInRow	= 0;
				if(delayIntervals[oldVarIndex]>0)
					dIndexInRow	= (del-dsets[0])/delayIntervals[oldVarIndex];
				if(ratingValues[varIndex-1][dIndexInRow] < rates.get(r,2)){
					ratingValues[varIndex-1][dIndexInRow] = rates.get(r,2);
				}
				if(rates.get(r,3)>0){
					delayMasks[varIndex-1][dIndexInRow] = true;
				}
   			}
		}
		for(int i=0;i<nvc;i++){
			String n = (String)needCalVarNames.elementAt(i);
			int oldVarIndex = varNames.indexOf(n);
			boolean[] delayMask = delayMasks[i];
			double[] rvalues = ratingValues[i];
			delays.setElementAt(delayMask,oldVarIndex);
			varRatings.setElementAt(rvalues,oldVarIndex);
			varDelayCalculated[oldVarIndex] = true;
		}
		autoSelectionTableModel.setNames(usedVarNames);
		autoSelectionTableView.validate();
		autoSelectionTableView.repaint(0l);  */
	}

	
	private boolean checkInputOutput(){
//		int dsIndex = dataChoice.getSelectedIndex();
		int dsIndex = 0;
		if(dsIndex == -1) return false;
		int c = varNames.size();
		if(c==0) return false;
		int ins = 0;
		int outs = 0;
		Vector outChecks = varClassifyTableModel.getOutputChecks();
		Vector inChecks = varClassifyTableModel.getInputChecks();
		for(int i=0;i<c;i++){
			if(((JRadioButton)outChecks.elementAt(i)).isSelected())
				outs++;
			else if(((JRadioButton)inChecks.elementAt(i)).isSelected())
				ins++;
		}
		if(ins ==0 || outs==0) return false; 

//		String mName = modelName.getText();
//		int mindex = project.getModelIndexByName(mName);
//		if(mindex != -1) return false;

// Check whether the name is taken by a transform.
// Need to finish

		return true;
	}

	private void refreshChecks(int row, int col, boolean flag){

		Vector outChecks = varClassifyTableModel.getOutputChecks();
		Vector inChecks = varClassifyTableModel.getInputChecks();
		int vc = varNames.size();
		usedVarNames.removeAllElements();
		outVarNames.removeAllElements();
		for(int i=0;i<vc;i++){
			if(((JRadioButton)outChecks.elementAt(i)).isSelected() 
				|| ((JRadioButton)inChecks.elementAt(i)).isSelected()){
				usedVarNames.addElement(varNames.elementAt(i));
			}
			if(((JRadioButton)outChecks.elementAt(i)).isSelected()){
				outVarNames.addElement(varNames.elementAt(i));
			}
			varDelayCalculated[i] = false;
		}
		delayTableModel.setNames(usedVarNames);
		autoSelectionTableModel.setNames(usedVarNames);
	}

	
	class ClassifyRenderer extends JComponent 
		implements TableCellRenderer, java.io.Serializable{
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
				if(isSelected){
					check.setSelected(!check.isSelected());
					table.clearSelection();
					refreshChecks(row,column,check.isSelected());
				}
				if(checkInputOutput()){
//					createButton.setEnabled(true);
				}else{		
//					createButton.setEnabled(false);
				}
				cell.add(check);
				return 	cell;
			}
			return null;
		}
	}

	class AutoSelectRenderer extends JComponent 
		implements TableCellRenderer, java.io.Serializable{
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


	class VarClassifyTableModel extends AbstractTableModel{
		private int row,col;
		private Vector names;
		private Vector inputchecks;
		private Vector outputchecks;
		private Vector unusedchecks;
		private String[] colHd = {"Variable","Output","Input","Unused"};
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
					public float getAlignmentY() { return 0.0f; }			
				};
				group.add(check);
				outputchecks.addElement(check);		 
				check = new JRadioButton(){
					public float getAlignmentY() { return 0.0f; }			
				};
				check.setSelected(true);
				group.add(check);
				inputchecks.addElement(check);
				check = new JRadioButton(){
					public float getAlignmentY() { return 0.0f; }			
				};
				group.add(check);
				unusedchecks.addElement(check);
			}
		}
		public int getColumnCount() { return col; }
		public int getRowCount() { return row;}
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
         
		public String getColumnName(int c) {
			return colHd[c];
		}

		public Vector getInputChecks(){
			return inputchecks;
		}

		public Vector getOutputChecks(){
			return outputchecks;
		}
           
		public Class getColumnClass(int c) {
			return getValueAt(0, c).getClass();
		}

		public boolean isCellEditable(int r, int c) {
			return false;
		}
		
		public void setValueAt(Object aValue, int r, int c) {
		}
	}

	class DelayTableModel extends AbstractTableModel{
		private int row,col;
		private Vector names;
		private String[] colHd = {"Variable","Min Delay", "Max Delay","Interval"};

		public DelayTableModel(){
			row = 0;
			col = 4;
			names = null;
		}

		public void setNames(Vector names){
			this.names = names;
			row = names.size();
		}
		public int getColumnCount() { return col; }
		public int getRowCount() { return row;}
		public Object getValueAt(int r, int c){
			if(c == 0){
				return names.elementAt(r);
			}else if(c == 1){
				String n = (String)names.elementAt(r);
				int rr = varNames.indexOf(n);
				int[] dset = (int[])delaysSettings.elementAt(rr);
				return String.valueOf(dset[0]);
			}else if(c == 2){
				String n = (String)names.elementAt(r);
				int rr = varNames.indexOf(n);
				int[] dset = (int[])delaysSettings.elementAt(rr);
				return String.valueOf(dset[1]);
			}else if(c == 3){
				String n = (String)names.elementAt(r);
				int rr = varNames.indexOf(n);
				return String.valueOf(delayIntervals[rr]);
			}
			return "";
		}
         
		public String getColumnName(int c) {
			return colHd[c];
		}
		
		public Class getColumnClass(int c) {
			return getValueAt(0, c).getClass();
		}
		
		public boolean isCellEditable(int r, int c) {
			if(c==0)
				return false;
			return true;
		}

		public void setValueAt(Object aValue, int r, int c) {
			System.out.println("value="+ aValue);
			delayTableView.requestFocus();
			try{
				int value = Integer.valueOf((String)aValue).intValue();
				String n = (String)names.elementAt(r);
				int rr = varNames.indexOf(n);
				if(c==1){
					int[] dset = (int[])delaysSettings.elementAt(rr);
					if(value > dset[1]){
						dset[1] = value;
						dset[0] = value;
					}else{
						dset[0] = value;
						delayIntervals[rr] = 1;
					}
					varDelayCalculated[rr] = false;
				}else if(c==2){
					int[] dset = (int[])delaysSettings.elementAt(rr);
					if(value < dset[0]){
						dset[1] = dset[0];
					}else{
						dset[1] = value;
						delayIntervals[rr] = 1;
					}
					varDelayCalculated[rr] = false;
				}else if(c==3){
					int[] dset = (int[])delaysSettings.elementAt(rr);
					if(value > 0 ){ 
						if(value >(dset[1]-dset[0]))
							delayIntervals[rr] = (dset[1]-dset[0]);
						else
							delayIntervals[rr] = value;
					}
					varDelayCalculated[rr] = false;
				}
			}catch(NumberFormatException evt){
				System.err.println("Non-Fatal exception: " + evt.getMessage());
				evt.printStackTrace();
			}
			autoSelectionTableModel.setNames(usedVarNames);
			delayTableView.validate();
			delayTableView.repaint(0l);
		}
	}

	class AutoSelectionTableModel extends AbstractTableModel{
		private int row,col;
		private int digits = 5;
		private Vector names;
		private Vector nameswithdelay;
		private Vector delayValues;
		private Vector ratings;
		private Vector usedchecks;
		private String[] colHd = {"Variable","Delay","Rating", "Used"};

		public AutoSelectionTableModel(){
			row = 0;
			col = 4;
			names = new Vector();
			nameswithdelay = new Vector();
			delayValues = new Vector();;
			ratings = new Vector();;
			usedchecks = new Vector();
		}

		public void setNames(Vector names){
			this.names = names;
			int nc = names.size();
			nameswithdelay.removeAllElements();
			delayValues.removeAllElements();
			ratings.removeAllElements();
			usedchecks.removeAllElements();
			for(int i=0;i<nc;i++){
				String n = (String)names.elementAt(i);
				int rr = varNames.indexOf(n);
				int outindex = outVarNames.indexOf(n);
				int[] dset = (int[])delaysSettings.elementAt(rr);
				boolean[] dlys = (boolean[])delays.elementAt(rr);
				double[] rates = (double[])varRatings.elementAt(rr);
				int interv;
				if(delayIntervals[rr] <= 0) interv = 1;
				else interv = delayIntervals[rr];

				for(int j=0,k=0;j<(dset[1]-dset[0]+1);j=j+interv,k++){
					int ddll = dset[0]+delayIntervals[rr]*k;
					if(!(outindex !=-1 && ddll == 0)){
						nameswithdelay.addElement(n);
						delayValues.addElement(String.valueOf(ddll));
						if(!varDelayCalculated[rr]){
							ratings.addElement("");
						}else{
							ratings.addElement(Utilities.formatDouble(rates[k], digits));
						}
						JCheckBox check = new JCheckBox(){
							public float getAlignmentY() { return 0.0f; }			
						};
						usedchecks.addElement(check);
					}
				}
			}
			row = nameswithdelay.size();
			goThrouthThreshold();
		}
		public void goThrouthThreshold(){
			for(int r=0;r<row;r++){
				String rateStr = (String)ratings.elementAt(r);
				JCheckBox check =  (JCheckBox)usedchecks.elementAt(r);
 				if(rateStr.equals("")){
					check.setSelected(true);
				}else{
					try{
						double c = Double.valueOf(rateStr).doubleValue();
						if(c>=ratingThresholdValue)
							check.setSelected(true);
						else
							check.setSelected(false);
					}catch(NumberFormatException  evt){
						check.setSelected(true);
					}
				}
			}
		}
		public int getColumnCount() { return col; }
		public int getRowCount() { return row;}
		public Object getValueAt(int r, int c){
			if(c == 0){
				return nameswithdelay.elementAt(r);
			}else if(c == 1){
				return delayValues.elementAt(r);
			}else if(c == 2){
				return ratings.elementAt(r);
			}else if(c == 3){
				return usedchecks.elementAt(r);
			}
			return "";
		}
     
		public String getColumnName(int c) {
			return colHd[c];
		}
		
		public Class getColumnClass(int c) {
			return getValueAt(0, c).getClass();
		}
		
		public boolean isCellEditable(int r, int c) {
			return false;
		}

		public Vector getUsedChecks(){
			return usedchecks;
		}

		public Vector getNamesWithDelay(){
			return nameswithdelay;
		}

		public void setValueAt(Object aValue, int r, int c) {
			System.out.println("value="+ aValue);
		}
	}

	protected void finishAction(){
		Matlib.pack() ;
		int c = varNames.size();
		boolean[] ins = new boolean[c];
		boolean[] outs = new boolean[c];
		Vector outchecks = varClassifyTableModel.getOutputChecks();
		Vector inchecks = varClassifyTableModel.getInputChecks();
		Vector outDelays = new Vector();
		Vector inDelays = new Vector();
		Vector outDelaysValues = new Vector();
		Vector inDelaysValues = new Vector();
		int maxDelay = 0;
		int nout = 0;
		int inputCols = 0;
		int ndls = 0;
		readDelaysFromAutoSelectChecks();
		for(int i=0;i<c;i++){
			int[] dsets = (int[])delaysSettings.elementAt(i);
			boolean[] dls = (boolean[])delays.elementAt(i);
			if(((JRadioButton)outchecks.elementAt(i)).isSelected()){
				ndls = 0;
				for(int j=0;j<dls.length;j++){
					if(dls[j]){
						int maxD = dsets[0]+j*delayIntervals[i];
						if(maxD>0){ 
							inputCols++;
							ndls++;
							System.out.println("search in y maxD="+maxD);
						}
						if(maxD > maxDelay)
							maxDelay = maxD;
					}
				}
				int[] idls = new int[ndls];
				ndls = 0;
				for(int j=0;j<dls.length;j++){
					if(dls[j]){
						int maxD = dsets[0]+j*delayIntervals[i];
						if(maxD>0){ 
							idls[ndls] = maxD;
							ndls++;
						}
					}
				}
				outDelays.addElement(delays.elementAt(i));
				outDelaysValues.addElement(idls);
				outs[i] = true;
				nout++;
			}else if(((JRadioButton)inchecks.elementAt(i)).isSelected()){
				boolean found = false;
				ndls = 0;
				for(int j=0;j<dls.length;j++){
					if(dls[j]){
						found = true;
						inputCols++;
						ndls++;
						System.out.println("search in x inputCols="+inputCols+"  i="+i);

						int maxD = dsets[0]+j*delayIntervals[i];
						if(maxD > maxDelay)
							maxDelay = maxD;
					}
				}
				int[] idls = new int[ndls];
				ndls = 0;
				for(int j=0;j<dls.length;j++){
					if(dls[j]){
						idls[ndls] = dsets[0]+j*delayIntervals[i];
						ndls++;
					}
				}
				if(found){
					inDelays.addElement(delays.elementAt(i));
					inDelaysValues.addElement(idls);
					ins[i] = true;
				}
			}
		}
		int dsIndex = dataSeriesList.getSelectedIndex();
		dataSeries = preprocessor.getDataSeries(dsIndex);
		EnsembleModel ensemble = new EnsembleModel(new ArchitectureParameters(inputCols,nout,0,0));
		model = new NolModel(ensemble,modelName.getText(),outs ,
			ins,outDelaysValues,inDelaysValues, dataSeries);

		String comment = modelDescript.getText();
		if(comment == null || comment.equals("")) return;
		model.setComment(comment);
	}

	public void readDelaysFromAutoSelectChecks(){
		Vector usedChecks = autoSelectionTableModel.getUsedChecks();
		Vector namewithdelays = autoSelectionTableModel.getNamesWithDelay();
		String n = (String)namewithdelays.elementAt(0);
		int rold = varNames.indexOf(n);
		int c=0;
		for(int i=0;i<namewithdelays.size();i++){
			n = (String)namewithdelays.elementAt(i);
			int rr = varNames.indexOf(n);
			if(rr == rold){
				c++;
			}else{
				boolean[] dls = new boolean[c];
				delays.setElementAt(dls,rold);
				rold = rr;
				c = 1;
			}
//			System.out.println("in readDelaysFromAutoSelectChecks c ="+c);
//			System.out.println("in readDelaysFromAutoSelectChecks rold ="+rold);
//			System.out.println("in readDelaysFromAutoSelectChecks rr ="+rr);

		}
		if(c>0){
			boolean[] dls = new boolean[c];
			delays.setElementAt(dls,rold);
		}
		n = (String)namewithdelays.elementAt(0);
		rold = varNames.indexOf(n);
		c = 0;
		for(int i=0;i<namewithdelays.size();i++){
			n = (String)namewithdelays.elementAt(i);
			int rr = varNames.indexOf(n);
			boolean[] dls = (boolean[])delays.elementAt(rr);
			if(rr == rold){
				if(((JCheckBox)usedChecks.elementAt(i)).isSelected()){ 
					dls[c] = true;
				}else{
					dls[c] = false;
				}
				c++;
			}else{
				c = 0;
				if(((JCheckBox)usedChecks.elementAt(i)).isSelected()){ 
					dls[c] = true;
				}else{
					dls[c] = false;
				}
				c++;
				rold = rr;
			}
		}
	}

	class AdvancedDialog extends JDialog{
		AdvancedDialog(JFrame frame, String title, boolean flag){
			super(frame,title,flag);
			initialDialogLayout();
		}
		private void initialDialogLayout(){
			JPanel modelTypePane = new JPanel(new GridLayout(1,3,25,25));
			modelTypePane.setBorder(BorderFactory.createTitledBorder("Model Types:"));

			URL url = this.getClass().getResource("../images/linear.gif");
			ImageIcon linear = new ImageIcon(url);
			url = this.getClass().getResource("../images/bpn.gif");
			ImageIcon bpn = new ImageIcon(url);
			url = this.getClass().getResource("../images/nlpls.gif");
			ImageIcon nlpls = new ImageIcon(url);
			url = this.getClass().getResource("../images/rbf.gif");
			ImageIcon rbf = new ImageIcon(url);
	
			ButtonGroup group = new ButtonGroup();
			JToggleButton linearButton = new JToggleButton("Linear",linear);
			linearButton.setVerticalTextPosition(AbstractButton.BOTTOM);
			linearButton.setHorizontalTextPosition(AbstractButton.CENTER);
			JToggleButton nlplsButton = new JToggleButton("NLPLS",nlpls,true);
			nlplsButton.setVerticalTextPosition(AbstractButton.BOTTOM);
			nlplsButton.setHorizontalTextPosition(AbstractButton.CENTER);
			JToggleButton bpnButton = new JToggleButton("BPN",bpn);
			bpnButton.setVerticalTextPosition(AbstractButton.BOTTOM);
			bpnButton.setHorizontalTextPosition(AbstractButton.CENTER);
			JToggleButton rbfButton = new JToggleButton("RBF",rbf);
			rbfButton.setVerticalTextPosition(AbstractButton.BOTTOM);
			rbfButton.setHorizontalTextPosition(AbstractButton.CENTER);
			group.add(linearButton);
			group.add(nlplsButton);
			group.add(bpnButton);
			group.add(rbfButton);
			modelTypePane.add(linearButton);
			modelTypePane.add(nlplsButton);
			modelTypePane.add(bpnButton);
			modelTypePane.add(rbfButton);

			JTabbedPane modelParaPane = new JTabbedPane();
			modelParaPane.addTab("Linear", getLinearPanel());
			modelParaPane.addTab("NLPLS", getNLPLSPanel());
			modelParaPane.addTab("BPN", getBPNPanel());
			modelParaPane.addTab("RBF", getRBFPanel());
			modelParaPane.setSelectedIndex(1);

			getContentPane().setLayout(new BorderLayout());
			JPanel center = new JPanel(new BorderLayout());

			center.add("North",modelTypePane);    
			center.add("Center",modelParaPane);    
			getContentPane().add("Center",center);    
			getContentPane().add("East",getAdvanceControlPanel());    
		}

		private JPanel getLinearPanel(){
			JPanel linePane = new JPanel(new GridLayout(5,2,10,10));
			linePane.setBorder(new EmptyBorder(10, 10, 10, 10));

			linePane.add(new JLabel("Regression Type:"));
			linePane.add(new JLabel("Factors or Bias Value:"));
			ButtonGroup group = new  ButtonGroup();
			JRadioButton olr = new JRadioButton("Ordinary Linear Regression");
			group.add(olr);
			linePane.add(olr);
			linePane.add(new JPanel());
			JRadioButton pcr = new JRadioButton("Principle Component Regression");
			group.add(pcr);
			linePane.add(pcr);
			linePane.add(new JTextField());
			JRadioButton pls = new JRadioButton("Partial Least Square");
			group.add(pls);
			linePane.add(pls);
			linePane.add(new JTextField());
			JRadioButton rr = new JRadioButton("Rigid Linear Regression");
			group.add(rr);
			linePane.add(rr);
			linePane.add(new JTextField());

			JPanel line1Pane = new JPanel(new BorderLayout());
			line1Pane.add("North",linePane);

			return line1Pane;
		}
		private JPanel getNLPLSPanel(){
			JPanel nlplsPane = new JPanel(new GridLayout(2,2,10,10));
			nlplsPane.setBorder(new EmptyBorder(10, 10, 10, 10));

			nlplsPane.add(new JLabel("Factors:"));
			nlplsPane.add(new JTextField());
			nlplsPane.add(new JLabel("Maximum Inner Hidden Nodes:"));
			nlplsPane.add(new JTextField());

			JPanel nlpls1Pane = new JPanel(new BorderLayout());
			nlpls1Pane.add("North",nlplsPane);

			return nlpls1Pane;
		}
		private JPanel getBPNPanel(){
			JPanel bpnPane = new JPanel(new BorderLayout());
			bpnPane.setBorder(new EmptyBorder(10, 10, 10, 10));

			JPanel layPane = new JPanel(new GridLayout(6,3,10,10));
			layPane.add(new JLabel("Layer"));
			layPane.add(new JLabel("Nodes"));
			layPane.add(new JLabel("Transfer Function"));

			layPane.add(new JLabel("1"));
			layPane.add(new JTextField());
			layPane.add(new JLabel("Transfer Function"));

			layPane.add(new JLabel("2"));
			layPane.add(new JTextField());
			layPane.add(new JLabel("Transfer Function"));

			layPane.add(new JLabel("3"));
			layPane.add(new JTextField());
			layPane.add(new JLabel("Transfer Function"));

			layPane.add(new JLabel("4"));
			layPane.add(new JTextField());
			layPane.add(new JLabel("Transfer Function"));

			layPane.add(new JLabel("5"));
			layPane.add(new JTextField());
			layPane.add(new JLabel("Transfer Function"));

			bpnPane.add("North",layPane);
			return bpnPane;
		}
		private JPanel getRBFPanel(){
			JPanel rbfPane = new JPanel(new GridLayout(3,4,10,10));
			rbfPane.setBorder(new EmptyBorder(10, 10, 10, 10));

			rbfPane.add(new JLabel("Hidden Nodes:"));
			rbfPane.add(new JTextField());
			rbfPane.add(new JPanel());
			rbfPane.add(new JPanel());
			rbfPane.add(new JLabel("Unit Overlap:"));
			ButtonGroup group = new  ButtonGroup();
			JRadioButton auto = new JRadioButton("Automatic");
			group.add(auto);
			rbfPane.add(auto);
			JRadioButton fixed = new JRadioButton("Fixed");
			group.add(fixed);
			rbfPane.add(fixed);
			rbfPane.add(new JTextField());

			rbfPane.add(new JLabel("Unit Shapes:"));
			group = new  ButtonGroup();
			JRadioButton elli = new JRadioButton("Elliptical");
			group.add(elli);
			rbfPane.add(elli);
			JRadioButton sphe = new JRadioButton("Spherical");
			group.add(sphe);
			rbfPane.add(sphe);

			JPanel rbf1Pane = new JPanel(new BorderLayout());
			rbf1Pane.add("North",rbfPane);

			return rbf1Pane;
		}

		private JPanel getAdvanceControlPanel(){
			JPanel control = new JPanel();
			control.setBackground(Color.lightGray);
			control.setLayout(new BoxLayout(control, BoxLayout.Y_AXIS));
			control.setBorder(new TitledBorder(new EmptyBorder(1, 1, 1, 1),               
					"", TitledBorder.LEFT , TitledBorder.TOP));

			JPanel pane0 = new JPanel(new GridLayout(2,1,5,5));
			JButton okButton = new JButton("OK");
			okButton.setActionCommand("OKProp");
			JButton cancelButton = new JButton("Cancel");
			cancelButton.setActionCommand("CancelProp");
			pane0.add(okButton);
			pane0.add(cancelButton);
			okButton.addActionListener(actionListener);
			cancelButton.addActionListener(actionListener);
			control.add(Box.createRigidArea(NolMainFrame.vpad15));
			control.add(pane0);
			control.add(Box.createRigidArea(NolMainFrame.vpad500));
			control.add(Box.createVerticalGlue());
			return control;
		}
	}

}
