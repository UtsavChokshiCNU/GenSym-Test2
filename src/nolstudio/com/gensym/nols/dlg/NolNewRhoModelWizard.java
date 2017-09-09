package com.gensym.nols.dlg;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.util.zip.*;
import java.io.*;
import java.net.URL;

import javax.swing.*;
import javax.swing.event.*;
import javax.swing.table.*;
import javax.swing.border.*;

import com.gensym.math.Utilities;
import com.gensym.math.datafit.*;
import com.gensym.math.matrix.*;

import com.gensym.nols.data.*;
import com.gensym.nols.main.*;
import com.gensym.nols.util.*;

import com.gensym.DEBUG;

public class NolNewRhoModelWizard  extends NolWizardDialog
	implements NolNewModelWizard{

	private	JTextField modelName;
	private	JTextField caseName;
	private	JTextField dataSeriesName;
	private JTextArea modelDescript;
	private JTextField ratingThreshold;
	private JButton calculateDelay;
	private JList caseList;
	private JList dataSeriesList;
	private DefaultListModel caseListModel;
	private DefaultListModel dataSeriesListModel;

	private LoadFromExistModelDialog loadFromExistModelDialog;
	private ControlAction actionListener;

	private	VarClassifyTableModel varClassifyTableModel;
	private	JTable varClassifyTableView;

	private	AutoSelectionTableModel autoSelectionTableModel;
	private	JTable autoSelectionTableView;

	private TableSorter selectionSorter;

	private JLabel numOfVariable;
	private JLabel numOfSample;

	private NolMainFrame frame;	 

	private boolean noFire;

	// parameters for modeling.

	private Preprocessor preprocessor;
	private DataSeries dataSeries;
	private NolRhoModel model;
	private Vector varNames;
	private Vector namesForOutputs;
	private Vector usedVarNames;
	private Vector outVarNames;
	private Vector varRatings;
	private double ratingThresholdValue;
	private boolean[] varRateCalculated;

	private JRadioButton ellipCheck;
	private JRadioButton spheCheck;
	private JTextField ratioField;
	private JToggleButton overlapButton;
	private JLabel outputNodesLabel;
	private JLabel inputNodesLabel;
	private JTextField hiddenNodesField;


	private static final String GENERAL_LABEL = "NewRhoModelWizard_GeneralLabel";
	private static final String COMMENT_LABEL = "CommentLabel";
	private static final String NAMEEDITLABEL = "NewRhoModelWizard_NameEditLabel";
	private static final String PREPROCESSOR_LABEL = "NewRhoModelWizard_PreprocessorLabel";
	private static final String PREPROCESSOR = "NewRhoModelWizard_Preprocessor";
	private static final String DATASOURCE_LABEL = "NewRhoModelWizard_OutputDataSourceLabel";
	private static final String DATASERIES = "NewRhoModelWizard_DataSeries";
	private static final String VARIABLE = "NewRhoModelWizard_Variable";
	private static final String SAMPLE = "NewRhoModelWizard_Sample";
	private static final String CLASSIFICATION_LABEL = "NewRhoModelWizard_ClassificationLabel";
	private static final String NODELAY_LABEL = "NewRhoModelWizard_NoDelayLabel";
	private static final String DELAY_LABEL = "NewRhoModelWizard_DelayLabel";
	private static final String HOUR = "NewRhoModelWizard_Hour";
	private static final String MINUTE = "NewRhoModelWizard_Minute";
	private static final String SECOND = "NewRhoModelWizard_Second";
	private static final String DELAYS = "NewRhoModelWizard_Delays";
	private static final String SETTING_LABEL = "NewRhoModelWizard_SettingLabel";
	private static final String SETTING_BORDER = "NewRhoModelWizard_SettingBorder";
	private static final String THRESHOLD = "NewRhoModelWizard_Threshold";
	private static final String CALCULATERATINGS = "NewRhoModelWizard_CalculateRatings";
	private static final String STRUCTURE_LABEL = "NewRhoModelWizard_StructureLabel";
	private static final String OUTPUT = "NewRhoModelWizard_Output";
	private static final String INPUT = "NewRhoModelWizard_Input";
	private static final String UNUSED = "NewRhoModelWizard_Unused";
	private static final String MINDELAY = "NewRhoModelWizard_MinDelay";
	private static final String MAXDELAY = "NewRhoModelWizard_MaxDelay";
	private static final String INTERVAL = "NewRhoModelWizard_Interval";
	private static final String DELAY = "NewRhoModelWizard_Delay";
	private static final String RATING = "NewRhoModelWizard_Rating";
	private static final String USED = "NewRhoModelWizard_Used";
	private static final String NOOUTPUTISSPECIFIED = "NewRhoModelWizard_NoOutputIsSpecified";
	private static final String NOINPUTISSPECIFIED = "NewRhoModelWizard_NoInputIsSpecified";
	private static final String NOLFINITEDATA = "NewRhoModelWizard_NoFiniteData";
	private static final String THRESHOLDTOOLTIP = "NewRhoModelWizard_ThresholdToolTip";
	private static final String LOADFROMEXISTMODEL = "NewRhoModelWizard_LoadFromModel";
	private static final String LOADFROMDISK = "NewRhoModelWizard_LoadFromDisk";
	private static final String PREDICTIVEMODEL = "NewRhoModelWizard_PredictiveModel";
	private static final String NOMODELSELECTED = "NewRhoModelWizard_NoModelSelected";
	private static final String NONAMEFORTHISMODEL = "NewRhoModelWizard_NoNameForThisModel";
	private static final String LAYERNUMBER = "NewRhoModelWizard_LayerNumber";
	

    private static final String OK_BUTTON_LABEL = "OkButtonLabel";
    private static final String CANCEL_BUTTON_LABEL = "CancelButtonLabel";

	public NolNewRhoModelWizard (NolMainFrame dw) {
//		super((JFrame)dw, "Create New Predictive Model", true, 7); //if DEBUG.more = true
		super((JFrame)dw, "Create New Back Propagation Model", true, 6);
		frame = (NolMainFrame)dw;
		actionListener = new ControlAction();
		noFire = false;
		varNames = new Vector();
		namesForOutputs = new Vector();
		usedVarNames= new Vector();
		outVarNames = new Vector();
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
		stepPanes.setElementAt(getSettingPane(),4);
		stepPanes.setElementAt(getStructurePane(),5);
	}

	private JPanel getGeneralPanel(){
		JPanel genPane = new JPanel(new BorderLayout());
		URL url = this.getClass().getResource("largerho.gif");
		ImageIcon importIcon = new ImageIcon(url);

		JPanel infoPane = new JPanel(new BorderLayout());
 		infoPane.setBorder(new EmptyBorder(10,10,10,10));

		String s = frame.getNolResourceString(GENERAL_LABEL);
//		String s = "A predictive model is used to calculate one \n"+
//			       "or more output variables as a function of other\n"+
//				   "input variables."
//			;
		
		JTextArea infoLabel = new JTextArea(s);
		infoLabel.setEditable(false);
		infoLabel.setLineWrap(true);
		infoLabel.setWrapStyleWord(true);
		infoLabel.setBackground(infoPane.getBackground());
		infoPane.add("Center",infoLabel);
		infoPane.add("West",new JLabel(importIcon));

		genPane.add("North",infoPane);

		JPanel cenPane = new JPanel(new BorderLayout());
		JPanel namePane = new JPanel(new GridLayout(3,1,10,5));
 		namePane.setBorder(new EmptyBorder(10,10,10,10));
		namePane.add(new JLabel(frame.getNolResourceString(NAMEEDITLABEL)+":"));
		modelName = new JTextField();
		modelName.setEditable(true);
		modelName.addActionListener(actionListener);
		namePane.add(modelName);
		namePane.add(new JLabel(frame.getNolResourceString(COMMENT_LABEL)+":"));
 		cenPane.add("North",namePane);

		JPanel descripPane = new JPanel(new GridLayout());
 		descripPane.setBorder(new EmptyBorder(0,10,10,10));
		modelDescript = new JTextArea();
		JScrollPane listScrollPane = new JScrollPane(modelDescript);
		listScrollPane.setBorder(BorderFactory.createLoweredBevelBorder());
		descripPane.add(listScrollPane);
 		cenPane.add("Center",descripPane);

		JPanel butPane = new JPanel(new GridLayout(1,2,10,10));
 		butPane.setBorder(new TitledBorder(new EmptyBorder(1, 10, 1, 10),               
			"Load Model Parameters:", TitledBorder.LEFT , TitledBorder.TOP));
		JButton but = new JButton(frame.getNolResourceString(LOADFROMEXISTMODEL));
		but.setActionCommand("loadFromModel");
		but.addActionListener(actionListener);
		butPane.add(but);
		but = new JButton(frame.getNolResourceString(LOADFROMDISK));
		but.setActionCommand("loadFromDisk");
		but.addActionListener(actionListener);
		butPane.add(but);
 		cenPane.add("South",butPane);

		genPane.add("Center",cenPane);
		return genPane;
	}

	private JPanel getCasePanel(){
		JPanel dataPane = new JPanel(new BorderLayout());
		JPanel infoPane = new JPanel(new GridLayout());
 		infoPane.setBorder(new EmptyBorder(10,10,10,10));
		String s = frame.getNolResourceString(PREPROCESSOR_LABEL);
//		String s = "What preprocessor has been used to process data for this model? ";
		JTextArea infoLabel = new JTextArea(s);
		infoLabel.setEditable(false);
		infoLabel.setLineWrap(true);
		infoLabel.setWrapStyleWord(true);
		infoLabel.setBackground(infoPane.getBackground());
		infoPane.add(infoLabel);

		dataPane.add("North",infoPane);

		JPanel cenPane = new JPanel(new BorderLayout());
 		cenPane.setBorder(new EmptyBorder(10,10,10,10));

		JPanel sourcePane = new JPanel(new GridLayout(1,2,20,20));
 		sourcePane.setBorder(new EmptyBorder(0,0,10,0));
		sourcePane.add(new JLabel(frame.getNolResourceString(PREPROCESSOR)+":"));
//		sourcePane.add(new JLabel("Preprocessor:"));
		caseName = new JTextField();
		caseName.setEditable(false);
//		caseName.addActionListener(actionListener);
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
		String s = frame.getNolResourceString(DATASOURCE_LABEL);
//		String s = "Select one data series that contains outputs for this model:";
		JTextArea infoLabel = new JTextArea(s);
		infoLabel.setEditable(false);
		infoLabel.setLineWrap(true);
		infoLabel.setWrapStyleWord(true);
		infoLabel.setBackground(infoPane.getBackground());
		infoPane.add(infoLabel);

		dataPane.add("North",infoPane);

		JPanel cenPane = new JPanel(new BorderLayout());
 		cenPane.setBorder(new EmptyBorder(10,10,10,10));

		JPanel sourcePane = new JPanel(new GridLayout(1,2,10,10));
 		sourcePane.setBorder(new EmptyBorder(0,0,10,0));
		sourcePane.add(new JLabel(frame.getNolResourceString(DATASERIES)+":"));
//		sourcePane.add(new JLabel("Data Series:"));
		dataSeriesName = new JTextField();
		dataSeriesName.setEditable(false);
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
		numPane.add(new JLabel(frame.getNolResourceString(VARIABLE)+":"));
//		numPane.add(new JLabel("Variable:"));
		numOfVariable  = new JLabel();
		numPane.add(numOfVariable);
		numPane.add(new JLabel(frame.getNolResourceString(SAMPLE)+":"));
//		numPane.add(new JLabel("Sample:"));
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
		String s = frame.getNolResourceString(CLASSIFICATION_LABEL);
//		String s = "Designate inputs and outputs for this model.  If a variable \n"+
//			"should not be used, check the unused button..";
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
		varPane.setBorder(BorderFactory.createTitledBorder(frame.getNolResourceString(VARIABLE)+":"));
//		varPane.setBorder(BorderFactory.createTitledBorder("Variable:"));

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

	
	private JPanel getSettingPane(){
		JPanel setPane = new JPanel(new BorderLayout());
		JPanel infoPane = new JPanel(new GridLayout());
 		infoPane.setBorder(new EmptyBorder(10,10,10,10));
		String s = frame.getNolResourceString(SETTING_LABEL);
//		String s = "If you would like the program to find the most important\n"+
//			       "inputs, select Calculate Ratings. \n"+
//				   "You can change the selection threshold, or manually \n"+
//				   "override the automatic selection.";
		JTextArea infoLabel = new JTextArea(s);
		infoLabel.setEditable(false);
		infoLabel.setLineWrap(true);
		infoLabel.setWrapStyleWord(true);
		infoLabel.setBackground(infoPane.getBackground());
		infoPane.add(infoLabel);
		setPane.add("North",infoPane);

		JPanel cenPane = new JPanel(new GridLayout());
 		cenPane.setBorder(new EmptyBorder(10,10,10,10));
 		JPanel autoPane = new JPanel(new BorderLayout());
		autoPane.setBorder(BorderFactory.createTitledBorder(
			frame.getNolResourceString(SETTING_BORDER)));

//		autoPane.setBorder(BorderFactory.createTitledBorder("Automatically Select Variables & Calculate Delays:"));

		autoSelectionTableModel = new AutoSelectionTableModel();
		selectionSorter = new TableSorter(autoSelectionTableModel); //ADDED THIS FOR  SORTING GCHEN 6.7.99
		
		autoSelectionTableView = new JTable(selectionSorter);
		autoSelectionTableView.setDefaultRenderer(AbstractButton.class, 
			new AutoSelectRenderer());
		selectionSorter.addMouseListenerToHeaderInTable(autoSelectionTableView);

		autoSelectionTableView.setSelectionMode(0);
		autoSelectionTableView.setSelectionBackground(Color.white);
		autoSelectionTableView.setCellSelectionEnabled(true);
		autoSelectionTableView.setSelectionForeground(Color.black);
		JScrollPane listScrollPane = new JScrollPane(autoSelectionTableView);
		listScrollPane.setBackground(Color.white);

		
		JPanel actPane = new JPanel(new GridLayout(1,3,10,10));
		actPane.setBorder(new EmptyBorder(10, 10, 10, 10));               

		actPane.add(new JLabel(frame.getNolResourceString(THRESHOLD)+":", SwingConstants.CENTER));
 		ratingThreshold = new JTextField();
		ratingThreshold.setToolTipText(frame.getNolResourceString(THRESHOLDTOOLTIP));
		ratingThreshold.addActionListener(actionListener);
		actPane.add(ratingThreshold);
		calculateDelay = new JButton(frame.getNolResourceString(CALCULATERATINGS));
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
		String s = frame.getNolResourceString(STRUCTURE_LABEL);
		JTextArea infoLabel = new JTextArea(s);
		infoLabel.setEditable(false);
		infoLabel.setLineWrap(true);
		infoLabel.setWrapStyleWord(true);
		infoLabel.setBackground(infoPane.getBackground());
		infoPane.add(infoLabel);
		structurePane.add("North",infoPane);

		JPanel cenPane = new JPanel(new GridLayout(6,2,10,10));
 		cenPane.setBorder(new EmptyBorder(20,20,20,20));

		cenPane.add(new JLabel("Input Nodes:"));
 		inputNodesLabel = new JLabel("1");
		cenPane.add(inputNodesLabel);
		cenPane.add(new JLabel("Hidden Nodes:"));
 		hiddenNodesField = new JTextField("1");
		cenPane.add(hiddenNodesField);
		cenPane.add(new JLabel("Output Nodes:"));
 		outputNodesLabel = new JLabel("1");
		cenPane.add(outputNodesLabel);
		cenPane.add(new JLabel("Unit Overlap:"));
		overlapButton = new JToggleButton("Automatic");
		overlapButton.addActionListener(actionListener);
		cenPane.add(overlapButton);
		cenPane.add(new JLabel("Fixed Overlap Ratio:"));
		ratioField = new JTextField("1.0");
		ratioField.setEnabled(false);
		cenPane.add(ratioField);
		cenPane.add(new JLabel("Hidden Unit Shape:"));

		JPanel checkPane = new JPanel(new GridLayout(1,2,5,5));
		ButtonGroup group = new ButtonGroup();
		ellipCheck = new JRadioButton("Elliptical");
		spheCheck = new JRadioButton("Spherical");
		spheCheck.setSelected(true);
		group.add(spheCheck);
		group.add(ellipCheck);
		checkPane.add(ellipCheck);
		checkPane.add(spheCheck);

		cenPane.add(checkPane);

		structurePane.add("Center",cenPane);
		return structurePane;
	}
  
	private DefaultListModel getCaseListModel() {
		if (caseListModel == null) {
			caseListModel = new DefaultListModel();
		}	
		return caseListModel;
	}	

	private DefaultListModel getDataSeriesListModel() {
		if (dataSeriesListModel == null) {
			dataSeriesListModel = new DefaultListModel();
		}	
		return dataSeriesListModel;
	}	

	
	@Override
	public void setVisible(boolean v){
		stepPane.removeAll();
		stepPane.add((JPanel)stepPanes.elementAt(0));
		stepPane.validate();
		stepPane.repaint(0l);
		currentStep = 0;
		modifyStep(true);
		String title = "Create New Rho Net - "+setTitleForStep(currentStep);
		title = title + " - General";
		setTitle(title);
		super.setVisible(v);
	}

	public void resetData(){
		isOK = false;
		stepPane.removeAll();
		stepPane.add((JPanel)stepPanes.elementAt(0));
		stepPane.validate();
		stepPane.repaint(0l);
		currentStep = 0;
		modifyStep(true);
		initDataDisplay();
		modelDescript.setText("");
	}

	@Override
	protected void modifyStep(boolean isNext){
		super.modifyStep(isNext);
		String title = "Create New Rho Net - "+setTitleForStep(currentStep);
		if(currentStep == 1){
			title = title + " - General";
			finishButton.setEnabled(false);
		}else if(currentStep == 2){
			Project2 project	 = frame.getProject();
			if(isNext){
				String mName = modelName.getText(); 
				if(mName.equals("")){
					frame.showOKDialog(frame.getNolResourceString(NONAMEFORTHISMODEL));
					super.modifyStep(false);
					finishButton.setEnabled(false);
					return;
				}
				
				boolean condition = project.getPredictiveModelIndexByName(mName) != -1 || project.getOptimizationModelIndexByName(mName) != -1;
				condition = condition || project.getBpnModelIndexByName(mName) != -1 || project.getAnnModelIndexByName(mName) != -1;
				condition = condition || project.getRbfnModelIndexByName(mName) != -1 || project.getRhoModelIndexByName(mName) != -1;
				
				if(condition){
					frame.showOKDialog("The model name exist! Please enter new name.");
					super.modifyStep(false);
					finishButton.setEnabled(false);
					return;
				}
			}
			title = title + " - Preprocessor";
			finishButton.setEnabled(false);
		}else if(currentStep == 3){
			title = title + " - Data Source";
			finishButton.setEnabled(false);
		}else if(currentStep == 4){
			title = title + " - Classification";
			finishButton.setEnabled(false);
		}else if(currentStep == 5){
			title = title + " - Settings";
		}else if(currentStep == 6){
			if(!resetStructParameter()){
				super.modifyStep(false);
			}
			title = title + " - Structure";
		}
		setTitle(title);
	}

 	private void initDataDisplay(){
		noFire = true;
		Project2 project	 = frame.getProject();
		int n = project.getNumberOfPreprocessors();
		if(n<0){
			noFire = false;
			return;
		}
		getCaseListModel().removeAllElements();
		for(int i=0;i<n;i++){
			Preprocessor prep = project.getPreprocessorByIndex(i);
			if(!prep.getDataSeries().isEmpty()){
				getCaseListModel().addElement(prep.getName());
			}
		}
		selectedPreprocessor(0);
		caseList.setSelectedIndex(0);
		selectedDataSeries(0);
		dataSeriesList.setSelectedIndex(0);
		int count = 1;
		while(true){
			String mName = "Model"+count;
			
			boolean condition = project.getPredictiveModelIndexByName(mName) == -1 && project.getOptimizationModelIndexByName(mName) == -1;
			condition = condition && project.getBpnModelIndexByName(mName) == -1 && project.getAnnModelIndexByName(mName) == -1;
			condition = condition && project.getRbfnModelIndexByName(mName) == -1 && project.getRhoModelIndexByName(mName) == -1;

			if(condition){
				modelName.setText(mName);
				break;
			}
			count++;
		}
		ratingThreshold.setText(Utilities.formatDouble(ratingThresholdValue, 3));
		noFire = false;
	}

	public NolRhoModel getModel(){
		if(model == null){
			return null;
		}
		return model;
	}

  	@Override
	public JFrame getFrame(){
		return frame;
	}

	private void selectedPreprocessor(int selectedIndex){
		Project2 project = frame.getProject();
		preprocessor = project.getPreprocessorByIndex(selectedIndex);
		caseName.setText(preprocessor.getName());
		int d = preprocessor.getNumberOfDataSeries();
		getDataSeriesListModel().removeAllElements();
		for(int i=0;i<d;i++){
			String name = preprocessor.getDataSeriesName(i); 	
			getDataSeriesListModel().addElement(name);
		}
		dataSeriesList.validate();
		dataSeriesList.repaint(0l);

		Vector vpNames = preprocessor.getVariableNames();
		varNames.removeAllElements();
		usedVarNames.removeAllElements();
		outVarNames.removeAllElements();
		varRatings.removeAllElements();
		
		for(int i=0;i<vpNames.size();i++){
			String name = vpNames.elementAt(i).toString();
			Variable varObj = preprocessor.getVariableFromVariableName(name);
			double std = varObj.getSTD();
//			if(std>0){
			varNames.addElement(name);
			usedVarNames.addElement(name);
			varRatings.addElement(new double[0]);
//			}
		}
		varRateCalculated = new boolean[varNames.size()];
		varClassifyTableModel.setNames(varNames);
		autoSelectionTableModel.setNames(usedVarNames);	
		selectionSorter.setModel(autoSelectionTableModel);
		autoSelectionTableView.setModel(selectionSorter);
	}

	private void selectedDataSeries(int selectedIndex){
		dataSeries  = preprocessor.getDataSeries(selectedIndex);
		dataSeriesName.setText(dataSeries.getName());
		namesForOutputs.removeAllElements();
		outVarNames.removeAllElements();

		Vector varObjs = dataSeries.getVarObjects();
		for(int i=0;i<varObjs.size();i++){
			String name = varObjs.elementAt(i).toString();
			namesForOutputs.addElement(name);
		}
		int row = dataSeries.getRow();
		numOfVariable.setText(String.valueOf(varObjs.size()));
		numOfSample.setText(String.valueOf(row));
	}

	private void loadParaFromExistModel(){
		Vector models = frame.getProject().getRhoModels();
		getLoadFromExistModelDialog().setContent(models);
		getLoadFromExistModelDialog().setBounds(200,200,300,200);
		getLoadFromExistModelDialog().setVisible(true);
		if(getLoadFromExistModelDialog().isOk()){
			int index = getLoadFromExistModelDialog().getSelectedIndex();
			if(index >=0){
				NolRhoModel existModel = (NolRhoModel)models.elementAt(index);
				if(updateParameterFromExistingModel(existModel)){
					currentStep = 1;
					modifyStep(true);
				}
			}else{
				frame.showOKDialog(frame.getNolResourceString(NOMODELSELECTED));
			}
		}
	}

	private void loadParaFromFile(){
		JFileChooser fileChooser = new JFileChooser();
		fileChooser.setDialogTitle("Import Model Parameter");
		NolFileFilter filter1 = new NolFileFilter(
		new String[] {"mp"}, "Model Parameter File"
		);
		fileChooser.addChoosableFileFilter(filter1);
		fileChooser.setFileFilter(filter1);
		String projectDirectory = frame.getProjectDirectory();

		File currentDirectory = new File(projectDirectory);
		if(currentDirectory.exists()) {
			fileChooser.setCurrentDirectory(currentDirectory);
		}
		int retval = fileChooser.showOpenDialog(frame);
		fileChooser.setFileFilter(null);
		fileChooser.removeChoosableFileFilter(filter1);

		if(retval == JFileChooser.CANCEL_OPTION){
			return;
		}

		currentDirectory = fileChooser.getSelectedFile();
		if(currentDirectory == null) {
			return;
		}

		String file = currentDirectory.getName();
		String directory = currentDirectory.getParent();
		try{		
			File sourceFile;
			if(directory==null)
				sourceFile = new File(file);	
			else
				sourceFile = new File(directory,file);
			FileInputStream fis = new FileInputStream(sourceFile); // Read from file
			GZIPInputStream gzis = new GZIPInputStream(fis);     // Uncompress
			ObjectInputStream in = new ObjectInputStream(gzis);  // Read objects
			NolModelParameter modelPara = (NolModelParameter)in.readObject();
			in.close(); // Close the stream.
			if(updateParameterFromExistingParameter(modelPara)){
				currentStep = 0;
				modifyStep(true);
			}else{
				frame.showOKDialog("The model parameters are not applicable with current project.");
			}
		}catch (Exception evt) { System.out.println(evt); }
	}
	
	private boolean updateParameterFromExistingParameter(NolModelParameter modelPara){

		int pindex = frame.getProject().getPreprocessorIndexByName(modelPara.preprocessorName);
		if(pindex == -1){
			return false;
		}
		selectedPreprocessor(pindex);
		Vector outs = modelPara.outputs;
		Vector inputs = modelPara.inputs;
		modelDescript.setText(modelPara.comment);
		if(outs.isEmpty())
			return false;
		String outVarName = outs.elementAt(0).toString();
		int dindex = preprocessor.getDataSeriesIndex(preprocessor.getDataSeriesFromVariableName(outVarName).getName());
		selectedDataSeries(dindex);
		Vector inputchecks = varClassifyTableModel.getInputChecks();
		for(int i=0;i<inputchecks.size();i++){
			JRadioButton radio = (JRadioButton)inputchecks.elementAt(i);
			radio.setSelected(false);
		}
		Vector outputchecks = varClassifyTableModel.getOutputChecks();
		for(int i=0;i<outputchecks.size();i++){
			JRadioButton radio = (JRadioButton)outputchecks.elementAt(i);
			radio.setSelected(false);
		}
		Vector unusedchecks = varClassifyTableModel.getUnUsedChecks();
		for(int i=0;i<unusedchecks.size();i++){
			JRadioButton radio = (JRadioButton)unusedchecks.elementAt(i);
			radio.setSelected(true);
		}
		for(int i=0;i<outs.size();i++){
			String varName = (String)outs.elementAt(i);
			int vindex = varNames.indexOf(varName);
			JRadioButton radio = (JRadioButton)outputchecks.elementAt(vindex);
			radio.setSelected(true);
		}
		for(int i=0;i<inputs.size();i++){
			String varName = (String)inputs.elementAt(i);
			int vindex = varNames.indexOf(varName);
			JRadioButton radio = (JRadioButton)inputchecks.elementAt(vindex);
			radio.setSelected(true);
		}
		refreshChecks(0,0);
		if(checkInputOutput()){
			finishButton.setEnabled(true);
		}else{		
			finishButton.setEnabled(false);
		}
		autoSelectionTableModel.setNames(usedVarNames);
		selectionSorter.setModel(autoSelectionTableModel);
		return true;
	}

	private boolean updateParameterFromExistingModel(NolRhoModel existModel){
	String prepName = existModel.getPreprocessor().getName();
		int pindex = frame.getProject().getPreprocessorIndexByName(prepName);
		if(pindex == -1){
			return false;
		}
		selectedPreprocessor(pindex);
		Vector outs = existModel.getOutputs();
		Vector inputs = existModel.getInputs();
		modelDescript.setText(existModel.getComment());
		if(outs.isEmpty())
			return false;
		String outVarName = outs.elementAt(0).toString();
		int dindex = preprocessor.getDataSeriesIndex(preprocessor.getDataSeriesFromVariableName(outVarName).getName());
		selectedDataSeries(dindex);
		Vector inputchecks = varClassifyTableModel.getInputChecks();
		for(int i=0;i<inputchecks.size();i++){
			JRadioButton radio = (JRadioButton)inputchecks.elementAt(i);
			radio.setSelected(false);
		}
		Vector outputchecks = varClassifyTableModel.getOutputChecks();
		for(int i=0;i<outputchecks.size();i++){
			JRadioButton radio = (JRadioButton)outputchecks.elementAt(i);
			radio.setSelected(false);
		}
		Vector unusedchecks = varClassifyTableModel.getUnUsedChecks();
		for(int i=0;i<unusedchecks.size();i++){
			JRadioButton radio = (JRadioButton)unusedchecks.elementAt(i);
			radio.setSelected(true);
		}
		for(int i=0;i<outs.size();i++){
			String varName = (String)outs.elementAt(i);
			int vindex = varNames.indexOf(varName);
			JRadioButton radio = (JRadioButton)outputchecks.elementAt(vindex);
			radio.setSelected(true);
		}
		for(int i=0;i<inputs.size();i++){
			String varName = (String)inputs.elementAt(i);
			int vindex = varNames.indexOf(varName);
			JRadioButton radio = (JRadioButton)inputchecks.elementAt(vindex);
			radio.setSelected(true);
		}
		refreshChecks(0,0);
		if(checkInputOutput()){
			finishButton.setEnabled(true);
		}else{		
			finishButton.setEnabled(false);
		}
		autoSelectionTableModel.setNames(usedVarNames);
		selectionSorter.setModel(autoSelectionTableModel);
		return true;
	}


	private LoadFromExistModelDialog getLoadFromExistModelDialog(){	 
		if(loadFromExistModelDialog == null){
			loadFromExistModelDialog = new LoadFromExistModelDialog(frame,"Load Parameters From Existing Model.",true);
			loadFromExistModelDialog.setBounds(200,200,300,200);
		}
		return loadFromExistModelDialog;
	}

	class ControlAction extends AbstractAction implements ListSelectionListener {
		ControlAction() {	super("controlAction");}
        @Override
		public void actionPerformed(ActionEvent e) {
			if(noFire) {
				return;
			}
			String command = e.getActionCommand();
			if(command.equals("Calculate Ratings")){
				calculateDelay.setEnabled(false);
				calculateRatings();
			}else if(e.getSource().equals(ratingThreshold)){
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
  			}else if(command.equals("loadFromModel")){
				loadParaFromExistModel();
  			}else if(command.equals("loadFromDisk")){
				loadParaFromFile();
			}else if(e.getSource().equals(modelName)){
				if(modelName.getText().equals("")){
					frame.showOKDialog(frame.getNolResourceString(NONAMEFORTHISMODEL));
				}
			}else if(e.getSource().equals(overlapButton)){
				if(overlapButton.isSelected()){
					ratioField.setEnabled(true);
				}else{
					ratioField.setEnabled(false);
				}
			}
		}

		@Override
		public void valueChanged(ListSelectionEvent e){
			if(!e.getValueIsAdjusting()) {
				return;
			}
			if(noFire) {
				return;
			}
			if(e.getSource().equals(caseList)){
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
			}else if(e.getSource().equals(dataSeriesList)){
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
		Vector delaysForRating = new Vector(0,10);
		// get variable classification
		for(int i=0;i<col;i++){
			if(((JRadioButton)outChecks.elementAt(i)).isSelected()){
				String varName = (String)varNames.elementAt(i);
				Variable varObj = preprocessor.getVariableFromVariableName(varName);
				outVars.addElement(varObj);
				outs++;
			}
			if(((JRadioButton)inChecks.elementAt(i)).isSelected()){
				String varName = (String)varNames.elementAt(i);
				Variable varObj = preprocessor.getVariableFromVariableName(varName);
				inVars.addElement(varObj);
				delaysForRating.addElement(new long[1]);
				ins++;
			}
		}
		if(outs == 0 || ins == 0){	
			return;
		}
		Vector Ratings = new Vector();
		RankThread rankThread = new RankThread(this, inVars, delaysForRating, outVars, Ratings);
		Thread rankRunningThread = new Thread(rankThread);
		int prior = rankRunningThread.getPriority()-3;
		if(prior <Thread.MIN_PRIORITY){
			prior = Thread.MIN_PRIORITY;
		}
		rankRunningThread.setPriority(prior);
		rankRunningThread.start();
	}

	@Override
	public void receiveRatingResults(Vector inVars, Vector delays, Vector outVars, Vector ratings) {
		int nv = inVars.size();
		if (DEBUG.debugFlag){
			System.out.println("ratings size ="+ratings.size());
		}

		int nr = ratings.size();
		if (nr == 0){
			frame.showOKDialog(frame.getNolResourceString(NOLFINITEDATA));
			return;
		}

		for(int i=0;i<nv;i++){
			String n = inVars.elementAt(i).toString();
			int oldVarIndex = varNames.indexOf(n);
			double[] rvalues = (double[])ratings.elementAt(i);
			varRatings.setElementAt(rvalues,oldVarIndex);
			varRateCalculated[oldVarIndex] = true;
		}
		autoSelectionTableModel.setNames(usedVarNames);
		selectionSorter.setModel(autoSelectionTableModel);
		autoSelectionTableView.validate();
		autoSelectionTableView.repaint(0l); 
	}

	
	private boolean checkInputOutput(){
		Vector outChecks = varClassifyTableModel.getOutputChecks();
		Vector inChecks = varClassifyTableModel.getInputChecks();
		int vc = varNames.size();
		boolean hasIn = false;
		boolean hasOut = false;
		for(int i=0;i<vc;i++){
			if(((JRadioButton)inChecks.elementAt(i)).isSelected()){
				hasIn = true;
			}
			if(((JRadioButton)outChecks.elementAt(i)).isSelected()){
				hasOut = true;
			}
		}
		if(hasIn && hasOut){
			return true;
		}else{
			return false;
		}
	}

	private void refreshChecks(int row, int col){
		Vector outChecks = varClassifyTableModel.getOutputChecks();
		Vector inChecks = varClassifyTableModel.getInputChecks();
		int vc = varNames.size();
		usedVarNames.removeAllElements();
		outVarNames.removeAllElements();
		for(int i=0;i<vc;i++){
			if(((JRadioButton)inChecks.elementAt(i)).isSelected()){
				usedVarNames.addElement(varNames.elementAt(i));
			}

			if(((JRadioButton)outChecks.elementAt(i)).isSelected()){
				outVarNames.addElement(varNames.elementAt(i));
			}
			varRateCalculated[i] = false;
		}
		autoSelectionTableModel.setNames(usedVarNames);
		selectionSorter.setModel(autoSelectionTableModel);
		calculateDelay.setEnabled(true);
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
					refreshChecks(row,column);
				}
				if(check.isEnabled()){
					cell.add(check);
				}
				if(checkInputOutput()){
					finishButton.setEnabled(true);
				}else{		
					finishButton.setEnabled(false);
				}
				return 	cell;
			}
			return null;
		}
	}

	class AutoSelectRenderer extends JComponent 
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
		private String[] colHd = {
			frame.getNolResourceString(VARIABLE),
			frame.getNolResourceString(OUTPUT),
			frame.getNolResourceString(INPUT),
			frame.getNolResourceString(UNUSED)};
//		private String[] colHd = {"Variable","Output","Input","Unused"};
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
				String name = (String)names.elementAt(r);
				if(namesForOutputs.contains(name)){
					return outputchecks.elementAt(r);
				}else{
					JRadioButton check = (JRadioButton)outputchecks.elementAt(r);
					check.setEnabled(false);
					return check;
				}
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

	class AutoSelectionTableModel extends AbstractTableModel{
		private int row,col;
		private int digits = 5;
		private Vector names;
		private Vector ratings;
		private Vector usedchecks;
		private String[] colHd = {
			frame.getNolResourceString(VARIABLE),
			frame.getNolResourceString(RATING),
			frame.getNolResourceString(USED)};
//		private String[] colHd = {"Variable","Delay","Rating", "Used"};

		public AutoSelectionTableModel(){
			row = 0;
			col = 3;
			names = new Vector();
			ratings = new Vector();
			usedchecks = new Vector();
		}

		public void setNames(Vector names){
			this.names = names;
			int nc = names.size();
			ratings.removeAllElements();
			usedchecks.removeAllElements();

			for(int i=0;i<nc;i++){
				String n = (String)names.elementAt(i);
				int rr = varNames.indexOf(n);
				double[] rates = (double[])varRatings.elementAt(rr);
				if(!varRateCalculated[rr]){
					ratings.addElement("");
				}else{
					ratings.addElement(Utilities.formatDouble(rates[0], digits));
				}
				JCheckBox check = new JCheckBox(){
					@Override
					public float getAlignmentY() { return 0.0f; }			
				};
				check.setBackground(Color.white);
				usedchecks.addElement(check);
			}
			row = names.size();				
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
		@Override
		public int getColumnCount() { return col; }
		@Override
		public int getRowCount() { return row;}
		@Override
		public Object getValueAt(int r, int c){
			if(c == 0){
				return names.elementAt(r);
			}else if(c == 1){
				return ratings.elementAt(r);
			}else if(c == 2){
				return usedchecks.elementAt(r);
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

		public Vector getUsedChecks(){
			return usedchecks;
		}

		public Vector getNames(){
			return names;
		}

		@Override
		public void setValueAt(Object aValue, int r, int c) {
		}
	}


	private boolean resetStructParameter(){
		int c = varNames.size();
		Vector outchecks = varClassifyTableModel.getOutputChecks();
		int nout = 0;
		int inputCols = 0;
		Vector checks= autoSelectionTableModel.getUsedChecks();
		if(checks.isEmpty()){
			frame.showOKDialog(frame.getNolResourceString(NOINPUTISSPECIFIED));
			return false;
		}
		
		for(int i=0;i<c;i++){
			if(((JRadioButton)outchecks.elementAt(i)).isSelected()){
				nout++;
			}
		}
		for(int i=0;i<checks.size();i++){
			if(((JCheckBox)checks.elementAt(i)).isSelected()){
				inputCols++;
			}
		}
		if(nout == 0){
			frame.showOKDialog(frame.getNolResourceString(NOOUTPUTISSPECIFIED));
			return false;
		}
		if(inputCols == 0){
			frame.showOKDialog(frame.getNolResourceString(NOINPUTISSPECIFIED));
			return false;
		}
		
		outputNodesLabel.setText(String.valueOf(nout));
		inputNodesLabel.setText(String.valueOf(inputCols));
		hiddenNodesField.setText(String.valueOf((nout+inputCols)/2));
		return true;
	}

	@Override
	protected boolean finishAction(){
		Matlib.pack() ;
		int c = varNames.size();
		Vector ins = new Vector();
		Vector outs = new Vector();
		Vector outchecks = varClassifyTableModel.getOutputChecks();
		Vector inchecks = varClassifyTableModel.getInputChecks();
		Vector inDelays = new Vector();
		Vector outDelays = new Vector();
		int nout = 0;
		int inputCols = 0;
		
		Vector names = autoSelectionTableModel.getNames();
		Vector checks= autoSelectionTableModel.getUsedChecks();
		if(names.isEmpty()){
			frame.showOKDialog(frame.getNolResourceString(NOINPUTISSPECIFIED));
			return false;
		}
	
		for(int i=0;i<c;i++){
			if(((JRadioButton)outchecks.elementAt(i)).isSelected()){
				outDelays.addElement(new long[1]);
				outs.addElement(varNames.elementAt(i));
				nout++;
			}
		}
		for(int i=0;i<checks.size();i++){
			if(((JCheckBox)checks.elementAt(i)).isSelected()){
				inDelays.addElement(new long[1]);
				int rold = varNames.indexOf(names.elementAt(i));
				ins.addElement(varNames.elementAt(rold));
				inputCols++;
			}
		}
		if(nout == 0){
			frame.showOKDialog(frame.getNolResourceString(NOOUTPUTISSPECIFIED));
			return false;
		}
		if(inputCols == 0){
			frame.showOKDialog(frame.getNolResourceString(NOINPUTISSPECIFIED));
			return false;
		}

		int nlayers = 3;
		int[] nodes	= new int[nlayers];
		nodes[0] = inputCols;
		nodes[1] = Integer.valueOf(hiddenNodesField.getText()).intValue();
		nodes[2] = nout;

		double overlap = 0.0;
		if(overlapButton.isSelected())
			overlap = Double.valueOf(ratioField.getText()).doubleValue();

		int shape = 0;
		if(ellipCheck.isSelected()){
			shape = 1;
		}

//System.out.println("node0=	"+ inputCols);
//System.out.println("node1=	"+ nodes[1]);
//System.out.println("node2=	"+ nodes[2]);
//System.out.println("overlap=	"+ overlap);
//System.out.println("shape=	"+ shape);

		ClassicRbfn net = new ClassicRbfn(nodes, overlap, shape);
		net.setBias(0);
		model = new NolRhoModel(net,modelName.getText(),outs ,
			ins,outDelays,inDelays, preprocessor);
		boolean hasTimeStamps = preprocessor.getDataSeries(0).getHasTimeStamps();
		model.setHasTimeStamps(hasTimeStamps);
		String comment = modelDescript.getText();
		if(comment != null)
			model.setComment(comment);
		return true;
	}


	class LoadFromExistModelDialog extends JDialog{
		private DefaultListModel choiceListModel;
		private NolList	choiceList;
		private JButton okButton, cancelButton;
		private	DialogAction dialogListener;
		private boolean nofire = false;
		private boolean isOk;
		LoadFromExistModelDialog(JFrame frame, String title, boolean flag){
			super(frame,title,flag);
			dialogListener = new DialogAction();
			initialDialogLayout();
		}
		private void initialDialogLayout(){
			choiceListModel = new DefaultListModel();
 			choiceList = new NolList(choiceListModel);
			choiceList.setBackground(Color.white);
			choiceList.addMouseListener((MouseListener)dialogListener);
			choiceList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
			JScrollPane listScrollPane = new JScrollPane(choiceList);
			listScrollPane.setBorder(BorderFactory.createLoweredBevelBorder());
			
			// Create the choice combo boxes to be placed at the top of the dialog
			JLabel choiceLabel = new JLabel(frame.getNolResourceString(PREDICTIVEMODEL));

			// now put it all together
			JPanel cenPane = new JPanel(new BorderLayout());
 			cenPane.setBorder(new EmptyBorder(10, 10, 10, 10));
			cenPane.add("North", choiceLabel);
			cenPane.add("Center", listScrollPane);
			getContentPane().setLayout(new BorderLayout());
			getContentPane().add("Center", cenPane);
			getContentPane().add("East", getControlPane());
			// Initialize this dialog to its preferred size.
			pack();
		}

		private JPanel getControlPane(){
			JPanel control = new JPanel();
			control.setBackground(getContentPane().getBackground());
			control.setLayout(new BoxLayout(control, BoxLayout.Y_AXIS));
			control.setBorder(new EmptyBorder(10, 10, 10, 10));

			JPanel pane0 = new JPanel(new GridLayout(5,1,5,5));
			okButton = new JButton(frame.getNolResourceString(OK_BUTTON_LABEL));
			okButton.setActionCommand("OK");
			cancelButton = new JButton(frame.getNolResourceString(CANCEL_BUTTON_LABEL));
			cancelButton.setActionCommand("Cancel");
			okButton.addActionListener(dialogListener);
			cancelButton.addActionListener(dialogListener);
			pane0.add(okButton);
			pane0.add(cancelButton);
			control.add(Box.createRigidArea(NolMainFrame.vpad15));
			control.add(pane0);
			control.add(Box.createRigidArea(NolMainFrame.vpad500));
			control.add(Box.createVerticalGlue());
			return control;
		}

		private boolean okFired() {
			int selectedIndex = choiceList.getSelectedIndex();
			if(selectedIndex<0){
				return false;
			}
			return true;
		}
		
		public void setContent(Vector choiceVector){
			nofire  = true;
			// clean up content from maybe last time...
			choiceListModel.removeAllElements();
			// now fill the variable dialog with variables
			choiceList.addObjects(choiceVector);
			if(!choiceVector.isEmpty()) 
				choiceList.setSelectedIndex(0);
			nofire = false;
		}

		public int getSelectedIndex() {
			return choiceList.getSelectedIndex();
		}
		private void closeDialog() {
			this.setVisible(false);
		}
		public boolean isOk() {
			return isOk;
		}
		class DialogAction extends AbstractAction implements MouseListener{
			DialogAction() {	super("title");}
			@Override
			public void actionPerformed(ActionEvent event) {
				if(nofire){
					return;
				}
				if (event.getSource().equals(okButton)) {
					isOk = okFired();
					closeDialog();
				} else if(event.getSource().equals(cancelButton)){
					isOk = false;
					closeDialog();
				}
			}
			@Override
			public void mousePressed(MouseEvent m) {}
			@Override
			public void mouseEntered(MouseEvent m) {}
			@Override
			public void mouseExited(MouseEvent m) {}
			@Override
			public void mouseReleased(MouseEvent m) {}
			public void mouseDragged(MouseEvent m) {}
			public void mouseMoved(MouseEvent m) {}
			@Override
			public void mouseClicked(MouseEvent m) {
				int clickCount =  m.getClickCount();
				if(clickCount != 2){
					return;
				}
				isOk = okFired();
				closeDialog();
			}
		}
	}
}
