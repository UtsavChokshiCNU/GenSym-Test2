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
import com.gensym.math.*;
import com.gensym.math.datafit.*;
import com.gensym.math.matrix.*;

import com.gensym.nols.data.*;
import com.gensym.nols.main.*;
import com.gensym.nols.util.*;

import com.gensym.DEBUG;

public class NolNewPlsModelWizard  extends NolWizardDialog
	implements NolNewModelWizard{

	private	JTextField modelName;
	private	JTextField caseName;
	private	JTextField dataSeriesName;
	private JTextArea modelDescript;
	private JTextField ratingThreshold;
	private JTextField numberField;
	private JButton calculateDelay;
	private JList caseList;
	private JList dataSeriesList;
	private DefaultListModel caseListModel;
	private DefaultListModel dataSeriesListModel;

	private AdvancedDialog advancedDialog;
	private LoadFromExistModelDialog loadFromExistModelDialog;
	private ControlAction actionListener;

	private	VarClassifyTableModel varClassifyTableModel;
	private	JTable varClassifyTableView;

	private	DelayTableModel delayTableModel;
	private	JTable delayTableView;

	private	AutoSelectionTableModel autoSelectionTableModel;
	private	AutoSelectionNoDelayTableModel autoSelectionNoDelayTableModel;
	private	JTable autoSelectionTableView;

	private TableSorter selectionSorter;
	private TableSorter selectionNoDelaySorter;

	private JRadioButton autoStructFlag;
	private JRadioButton manualStructFlag;
	private JLabel numOfVariable;
	private JLabel numOfSample;

	private NolMainFrame frame;	 

	private int delayTimeSettingFlag;  //1:hour 2: minut 3: second
	private boolean noFire;
	private boolean hasTimeStamps;

	// parameters for modeling.

	private Preprocessor preprocessor;
	private DataSeries dataSeries;
	private NolPlsModel model;
	private Vector varNames;
	private Vector namesForOutputs;
	private Vector usedVarNames;
	private Vector outVarNames;
	private boolean[] varDelayCalculated;
	private Vector delays;
	private long[] delayIntervals;
	private Vector delaysSettings;
	private Vector varRatings;
	private double ratingThresholdValue;


	private JTextField factorNumber;
	private JCheckBox fixFactor;

	private static final String GENERAL_LABEL = "NewPlsModelWizard_GeneralLabel";
	private static final String COMMENT_LABEL = "CommentLabel";
	private static final String NAMEEDITLABEL = "NewBpnModelWizard_NameEditLabel";
	private static final String PREPROCESSOR_LABEL = "NewBpnModelWizard_PreprocessorLabel";
	private static final String PREPROCESSOR = "NewBpnModelWizard_Preprocessor";
	private static final String DATASOURCE_LABEL = "NewBpnModelWizard_OutputDataSourceLabel";
	private static final String DATASERIES = "NewBpnModelWizard_DataSeries";
	private static final String VARIABLE = "NewBpnModelWizard_Variable";
	private static final String SAMPLE = "NewBpnModelWizard_Sample";
	private static final String CLASSIFICATION_LABEL = "NewBpnModelWizard_ClassificationLabel";
	private static final String NODELAY_LABEL = "NewBpnModelWizard_NoDelayLabel";
	private static final String DELAY_LABEL = "NewBpnModelWizard_DelayLabel";
	private static final String HOUR = "NewBpnModelWizard_Hour";
	private static final String MINUTE = "NewBpnModelWizard_Minute";
	private static final String SECOND = "NewBpnModelWizard_Second";
	private static final String DELAYS = "NewBpnModelWizard_Delays";
	private static final String SETTING_LABEL = "NewBpnModelWizard_SettingLabel";
	private static final String SETTING_BORDER = "NewBpnModelWizard_SettingBorder";
	private static final String THRESHOLD = "NewBpnModelWizard_Threshold";
	private static final String CALCULATERATINGS = "NewBpnModelWizard_CalculateRatings";
	private static final String STRUCTURE_LABEL = "NewBpnModelWizard_StructureLabel";
	private static final String OUTPUT = "NewBpnModelWizard_Output";
	private static final String INPUT = "NewBpnModelWizard_Input";
	private static final String UNUSED = "NewBpnModelWizard_Unused";
	private static final String MINDELAY = "NewBpnModelWizard_MinDelay";
	private static final String MAXDELAY = "NewBpnModelWizard_MaxDelay";
	private static final String INTERVAL = "NewBpnModelWizard_Interval";
	private static final String DELAY = "NewBpnModelWizard_Delay";
	private static final String RATING = "NewBpnModelWizard_Rating";
	private static final String USED = "NewBpnModelWizard_Used";
	private static final String NOOUTPUTISSPECIFIED = "NewBpnModelWizard_NoOutputIsSpecified";
	private static final String NOINPUTISSPECIFIED = "NewBpnModelWizard_NoInputIsSpecified";
	private static final String NOLFINITEDATA = "NewBpnModelWizard_NoFiniteData";
	private static final String THRESHOLDTOOLTIP = "NewBpnModelWizard_ThresholdToolTip";
	private static final String LOADFROMEXISTMODEL = "NewBpnModelWizard_LoadFromModel";
	private static final String LOADFROMDISK = "NewBpnModelWizard_LoadFromDisk";
	private static final String PREDICTIVEMODEL = "NewBpnModelWizard_PredictiveModel";
	private static final String NOMODELSELECTED = "NewBpnModelWizard_NoModelSelected";
	private static final String NONAMEFORTHISMODEL = "NewBpnModelWizard_NoNameForThisModel";
	private static final String LAYERNUMBER = "NewBpnModelWizard_LayerNumber";
	private static final String WRONGLAYERNUMBER = "NewBpnModelWizard_WrongLayerNumber";
	private static final String WRONGSTRUCTURE = "NewBpnModelWizard_WrongStructure";
	
    private static final String OK_BUTTON_LABEL = "OkButtonLabel";
    private static final String CANCEL_BUTTON_LABEL = "CancelButtonLabel";

	public NolNewPlsModelWizard (NolMainFrame dw) {
		super((JFrame)dw, "Create New Partial Least Square Model", true, 6);
		frame = (NolMainFrame)dw;
		actionListener = new ControlAction();
		noFire = false;
		varNames = new Vector();
		namesForOutputs = new Vector();
		usedVarNames= new Vector();
		outVarNames = new Vector();
		delays = new Vector();
		delaysSettings = new Vector();
		varRatings = new Vector();
		ratingThresholdValue = 3.0;
		delayTimeSettingFlag = 2;
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
	}

	private JPanel getGeneralPanel(){
		JPanel genPane = new JPanel(new BorderLayout());
		URL url = this.getClass().getResource("largepls.gif");
		ImageIcon importIcon = new ImageIcon(url);

		JPanel infoPane = new JPanel(new BorderLayout());
 		infoPane.setBorder(new EmptyBorder(10,10,10,10));

		String s = frame.getNolResourceString(GENERAL_LABEL);
		
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

 	private JPanel getDelayPane(){
		JPanel delayPane = new JPanel(new BorderLayout());
		JPanel infoPane = new JPanel(new GridLayout());
 		infoPane.setBorder(new EmptyBorder(10,10,10,10));
		String s = frame.getNolResourceString(DELAY_LABEL);
//		String s = "You can specify delays to account for time lags between \n"+
//			       "inputs and outputs.  Delays are measured in terms of \n"+
//				   "time.";
		JTextArea infoLabel = new JTextArea(s);
		infoLabel.setEditable(false);
		infoLabel.setLineWrap(true);
		infoLabel.setWrapStyleWord(true);
		infoLabel.setBackground(infoPane.getBackground());
		infoPane.add(infoLabel);
		delayPane.add("North",infoPane);

		JPanel cenPane = new JPanel(new BorderLayout());

		JPanel timePane = new JPanel(new GridLayout(1,3,5,5));
		ButtonGroup group = new ButtonGroup();
		JRadioButton radio = new JRadioButton(frame.getNolResourceString(HOUR));
		radio.setActionCommand("Hour");
//		JRadioButton radio = new JRadioButton("Hour");
		radio.addActionListener(actionListener);
		group.add(radio);
		timePane.add(radio);
		radio = new JRadioButton(frame.getNolResourceString(MINUTE),true);
		radio.setActionCommand("Minute");
//		radio = new JRadioButton("Minute",true);
		radio.addActionListener(actionListener);
		group.add(radio);
		timePane.add(radio);
		radio = new JRadioButton(frame.getNolResourceString(SECOND));
		radio.setActionCommand("Second");
//		radio = new JRadioButton("Second");
		radio.addActionListener(actionListener);
		group.add(radio);
		timePane.add(radio);

 		cenPane.setBorder(new EmptyBorder(10,10,10,10));
  		JPanel delPane = new JPanel(new GridLayout());
		delPane.setBorder(BorderFactory.createTitledBorder(frame.getNolResourceString(DELAYS)+":"));
//		delPane.setBorder(BorderFactory.createTitledBorder("Delays:"));

		delayTableModel = new DelayTableModel();
		delayTableView = new JTable(delayTableModel);
		delayTableView.setSelectionMode(0);
		delayTableView.setSelectionBackground(Color.white);
		delayTableView.setCellSelectionEnabled(true);
		delayTableView.setSelectionForeground(Color.black);
		JScrollPane listScrollPane = new JScrollPane(delayTableView);
		listScrollPane.setBackground(Color.white);
		delPane.add(listScrollPane);

		cenPane.add("North",timePane);
		cenPane.add("Center",delPane);
		delayPane.add("Center",cenPane);

		return delayPane;
	}

 	private JPanel getNoDelayPane(){
		JPanel delayPane = new JPanel(new GridLayout());
		JPanel infoPane = new JPanel(new GridLayout());
 		infoPane.setBorder(new EtchedBorder(EtchedBorder.LOWERED));
		infoPane.setBackground(Color.white);
		String s = frame.getNolResourceString(NODELAY_LABEL);
//		String s = "   There are no time-stamps, thus you need not specify\n"+
//					"   time delays. If you wish to set time delays,\n"+
//					"   you must add time-stamps to data series.";
		JTextArea infoLabel = new JTextArea(s);
		infoLabel.setEditable(false);
		infoLabel.setLineWrap(true);
		infoLabel.setWrapStyleWord(true);
		infoLabel.setBackground(Color.white);
		infoPane.add(infoLabel);
		JPanel cenPane = new JPanel(new GridLayout());
 		cenPane.add(infoPane);
		cenPane.setBorder(new EmptyBorder(10,10,10,10));
		delayPane.add(cenPane);
		return delayPane;
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
		autoSelectionNoDelayTableModel = new AutoSelectionNoDelayTableModel();

		selectionSorter = new TableSorter(autoSelectionTableModel); //ADDED THIS FOR  SORTING GCHEN 6.7.99
		selectionNoDelaySorter = new TableSorter(autoSelectionNoDelayTableModel); //ADDED THIS FOR  SORTING GCHEN 6.7.99

		
		autoSelectionTableView = new JTable(selectionSorter);
		autoSelectionTableView.setDefaultRenderer(AbstractButton.class, 
			new AutoSelectRenderer());
		selectionSorter.addMouseListenerToHeaderInTable(autoSelectionTableView);
		selectionNoDelaySorter.addMouseListenerToHeaderInTable(autoSelectionTableView);

		autoSelectionTableView.setSelectionMode(0);
		autoSelectionTableView.setSelectionBackground(Color.white);
		autoSelectionTableView.setCellSelectionEnabled(true);
		autoSelectionTableView.setSelectionForeground(Color.black);
		JScrollPane listScrollPane = new JScrollPane(autoSelectionTableView);
		listScrollPane.setBackground(Color.white);

		
		JPanel actPane = new JPanel(new GridLayout(2,3,10,10));
		actPane.setBorder(new EmptyBorder(10, 10, 10, 10));               

		actPane.add(new JLabel(frame.getNolResourceString(THRESHOLD)+":", SwingConstants.CENTER));
 		ratingThreshold = new JTextField();
		ratingThreshold.setToolTipText(frame.getNolResourceString(THRESHOLDTOOLTIP));
		ratingThreshold.addActionListener(actionListener);
		actPane.add(ratingThreshold);
		calculateDelay = new JButton(frame.getNolResourceString(CALCULATERATINGS));
		calculateDelay.addActionListener(actionListener);
		actPane.add(calculateDelay);
		
		actPane.add(new JLabel(frame.getNolResourceString("NewPlsModelWizard_FactorNumber")+":", SwingConstants.CENTER));
 		factorNumber = new JTextField();
		factorNumber.setEnabled(false);
		factorNumber.setToolTipText(frame.getNolResourceString("NewPlsModelWizard_FactorNumberToolTip"));
		factorNumber.addActionListener(actionListener);
		actPane.add(factorNumber);
		fixFactor = new JCheckBox(frame.getNolResourceString("NewPlsModelWizard_FixFactor"));
		fixFactor.addActionListener(actionListener);
		actPane.add(fixFactor);

		autoPane.add("Center",listScrollPane);
		autoPane.add("South",actPane);

		cenPane.add(autoPane);
		setPane.add("Center",cenPane);


		return setPane;
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
		String title = "Create New Partial Least Square Model - "+setTitleForStep(currentStep);
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
		String title = "Create New Partial Least Square Model - "+setTitleForStep(currentStep);
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
				condition = condition || project.getPlsModelIndexByName(mName) != -1 || project.getPcaModelIndexByName(mName) != -1; 
				
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
			title = title + " - Delay";
		}else if(currentStep == 6){
			title = title + " - Settings";
			resetStructParameter();
		}
		if(DEBUG.debugFlag){
			System.out.println(title);
		}
		setTitle(title);
	}

	private boolean resetStructParameter(){
		int c = varNames.size();
		Vector outchecks = varClassifyTableModel.getOutputChecks();
		Vector inchecks = varClassifyTableModel.getInputChecks();
		int nout = 0;
		int inputCols = 0;
		
		Vector names = null;
		if(hasTimeStamps){
			names= autoSelectionTableModel.getNamesWithDelay();
		}else{
			names= autoSelectionNoDelayTableModel.getNames();
		}
		if(names.isEmpty()){
			frame.showOKDialog(frame.getNolResourceString(NOINPUTISSPECIFIED));
			return false;
		}
		
		Vector newDelayValues = readDelaysFromAutoSelectChecks();		
		for(int i=0;i<c;i++){
			if(((JRadioButton)outchecks.elementAt(i)).isSelected()){
				long[] dls = (long[])newDelayValues.elementAt(i);
				nout++;
				for(int j=0;j<dls.length;j++){
					if(dls[j]>0)
						inputCols++;
				}
			}else if(((JRadioButton)inchecks.elementAt(i)).isSelected()){
				long[] dls = (long[])newDelayValues.elementAt(i);
				inputCols = inputCols+dls.length;
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
		factorNumber.setText(""+(inputCols/2));
		return true;
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
			condition = condition && project.getPlsModelIndexByName(mName) == -1  && project.getPcaModelIndexByName(mName) == -1; 
			
			if(condition){
				modelName.setText(mName);
				break;
			}
			count++;
		}
		ratingThreshold.setText(Utilities.formatDouble(ratingThresholdValue, 3));

		fixFactor.setSelected(false);
		factorNumber.setEnabled(false);
		noFire = false;
	}

	public NolPlsModel getModel(){
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
		Project project = frame.getProject();
		preprocessor = project.getPreprocessorByIndex(selectedIndex);
		hasTimeStamps = preprocessor.getDataSeries(0).getHasTimeStamps();
		if(hasTimeStamps){
			stepPanes.setElementAt(getDelayPane(),4);
		}else{
			stepPanes.setElementAt(getNoDelayPane(),4);
		}
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
		delays.removeAllElements();
		delaysSettings.removeAllElements();
		varRatings.removeAllElements();
		
		for(int i=0;i<vpNames.size();i++){
			String name = vpNames.elementAt(i).toString();
			Variable varObj = preprocessor.getVariableFromVariableName(name);
			double std = varObj.getSTD();
			if(std>0){
				varNames.addElement(name);
				usedVarNames.addElement(name);
				delays.addElement(new long[1]);
				delaysSettings.addElement(new long[2]);
				varRatings.addElement(new double[0]);
			}
		}
		delayIntervals = new long[varNames.size()];
		varDelayCalculated = new boolean[varNames.size()];
		varClassifyTableModel.setNames(varNames);
		delayTableModel.setNames(usedVarNames);
		if(hasTimeStamps){
			autoSelectionTableModel.setNames(usedVarNames);	
			selectionSorter.setModel(autoSelectionTableModel);
			autoSelectionTableView.setModel(selectionSorter);
		}else{
			autoSelectionNoDelayTableModel.setNames(usedVarNames);	
			selectionNoDelaySorter.setModel(autoSelectionNoDelayTableModel);
			autoSelectionTableView.setModel(selectionNoDelaySorter);
		}
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
		Vector models = new Vector();
		models.addAll(frame.getProject().getPlsModels());
		getLoadFromExistModelDialog().setContent(models);
		getLoadFromExistModelDialog().setBounds(200,200,300,200);
		getLoadFromExistModelDialog().setVisible(true);
		if(getLoadFromExistModelDialog().isOk()){
			int index = getLoadFromExistModelDialog().getSelectedIndex();
			if(index >=0){
				NolPlsModel existModel = (NolPlsModel)models.elementAt(index);
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
		if(currentDirectory == null){
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
		Vector inputDelays = modelPara.inputDelays;
		long divide = 60000;
		if(delayTimeSettingFlag == 1){
			divide = 3600000;
		}else if(delayTimeSettingFlag == 3){
			divide = 1000;
		}
		if(inputs.size() != inputDelays.size()){
			return true;
		}

//		System.out.println("before delay arrangement");
		for(int i=0;i<inputDelays.size();i++){
			long[] dls = (long[])inputDelays.elementAt(i);
			String inputVarName = inputs.elementAt(i).toString();
			int index = varNames.indexOf(inputVarName);
			long[] dsets = (long[])delaysSettings.elementAt(index);
			dsets[0] = dls[0];
			dsets[1] = dls[dls.length-1];
			if (dls.length > 1 ){
 				delayIntervals[index] = dls[1] - dls[0];
			}else{ 
				delayIntervals[index] = 0;
			}
		}
		arrangeDelays();
		calculateDelay.setEnabled(true);
		if(hasTimeStamps){
			autoSelectionTableModel.setNames(usedVarNames);
			selectionSorter.setModel(autoSelectionTableModel);
		}else{
			autoSelectionNoDelayTableModel.setNames(usedVarNames);
			selectionNoDelaySorter.setModel(autoSelectionNoDelayTableModel);
		}
		delayTableView.validate();
		delayTableView.repaint(0l);
		return true;
	}

	private boolean updateParameterFromExistingModel(NolModel2 existModel){
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
		Vector inputDelays = existModel.getInputDelays();
		long divide = 60000;
		if(delayTimeSettingFlag == 1){
			divide = 3600000;
		}else if(delayTimeSettingFlag == 3){
			divide = 1000;
		}
		if(inputs.size() != inputDelays.size()){
			return true;
		}

//		System.out.println("before delay arrangement");
		for(int i=0;i<inputDelays.size();i++){
			long[] dls = (long[])inputDelays.elementAt(i);
			String inputVarName = inputs.elementAt(i).toString();
			int index = varNames.indexOf(inputVarName);
			long[] dsets = (long[])delaysSettings.elementAt(index);
			dsets[0] = dls[0];
			dsets[1] = dls[dls.length-1];
			if (dls.length > 1 ){
 				delayIntervals[index] = dls[1] - dls[0];
			}else{ 
				delayIntervals[index] = 0;
			}
		}
		arrangeDelays();
		calculateDelay.setEnabled(true);
		if(hasTimeStamps){
			autoSelectionTableModel.setNames(usedVarNames);
			selectionSorter.setModel(autoSelectionTableModel);
		}else{
			autoSelectionNoDelayTableModel.setNames(usedVarNames);
			selectionNoDelaySorter.setModel(autoSelectionNoDelayTableModel);
		}
		delayTableView.validate();
		delayTableView.repaint(0l);
		return true;
	}

	private AdvancedDialog getAdvancedDialog(){	 
		if(advancedDialog == null){
			advancedDialog = new AdvancedDialog(frame,"Define Model Advanced Settings",true);
			advancedDialog.setBounds(200,200,550,370);
		}
		return advancedDialog;
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
			if(noFire){
				return;
			}
			String command = e.getActionCommand();
			if(command.equals("Calculate Ratings")){
				calculateDelay.setEnabled(false);
				calculateRatings();
			}else if(command.equals("Hour")){
				if(delayTimeSettingFlag == 1) {
					return;
				}
				convertDelayFromTimeUnits(delayTimeSettingFlag,1);
				delayTimeSettingFlag = 1;
			}else if(command.equals("Minute")){
				if(delayTimeSettingFlag == 2){
					return;
				}
				convertDelayFromTimeUnits(delayTimeSettingFlag,2);
				delayTimeSettingFlag = 2;
			}else if(command.equals("Second")){
				if(delayTimeSettingFlag == 3){
					return;
				}
				convertDelayFromTimeUnits(delayTimeSettingFlag,3);
				delayTimeSettingFlag = 3;
			}else if(command.equals("Auto")){
			}else if(command.equals("Manual")){
			}else if(command.equals("Settings...")){
				getAdvancedDialog().setVisible(true);
  			}else if(command.equals("OKProp") || command.equals("CancelProp")){
				getAdvancedDialog().setVisible(false);
			}else if(e.getSource().equals(ratingThreshold)){
  				String s = ratingThreshold.getText();
				try{
					double c = Double.valueOf(s).doubleValue();
					if(c>0){
						ratingThresholdValue = c;
						if(hasTimeStamps){
							autoSelectionTableModel.goThrouthThreshold();
						}else{
							autoSelectionNoDelayTableModel.goThrouthThreshold();
						}
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
			}else if(e.getSource().equals(fixFactor)){
				if (fixFactor.isSelected()){
					factorNumber.setEnabled(true);
				}else{
					factorNumber.setEnabled(false);
				}
			}
		}

		@Override
		public void valueChanged(ListSelectionEvent e){
			if(!e.getValueIsAdjusting()){
				return;
			}
			if(noFire){
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
				if(!varDelayCalculated[i]){
					long[] dls = (long[])delays.elementAt(i);
					for(int j=0;j<dls.length;j++){
						if(dls[j]>0){
							inVars.addElement(varObj);					
							delaysForRating.addElement(dls);
							ins++;
							break;
						}
					}
				}
			}
			if(((JRadioButton)inChecks.elementAt(i)).isSelected()){
				if(!varDelayCalculated[i]){
					String varName = (String)varNames.elementAt(i);
					Variable varObj = preprocessor.getVariableFromVariableName(varName);
					inVars.addElement(varObj);
					delaysForRating.addElement(delays.elementAt(i));
					ins++;
				}
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


	private void arrangeDelays(){
		int col = delaysSettings.size();
		for(int i=0;i<col;i++){
			delays.setElementAt(convertDelays((long[])delaysSettings.elementAt(i),
				delayIntervals[i]),i);
		}
	}

	private long[] convertDelays(long[] dset,long interval){
		long newInterv;
		if(interval <= 0){
			newInterv = dset[1]-dset[0]+1;
		}else {
			newInterv = interval;
		}
		int length = ((int)((dset[1]-dset[0])/newInterv))+1;

		long[] dls = new long[length];
		for(int p=0;p<length;p++){
			dls[p] = dset[0]+newInterv*p;
		}
		return dls;
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

			if (DEBUG.debugFlag){
				System.out.println("varName="+n);
			}
			double[] rvalues = (double[])ratings.elementAt(i);
			varRatings.setElementAt(rvalues,oldVarIndex);
			varDelayCalculated[oldVarIndex] = true;
		}
		if(hasTimeStamps){
			autoSelectionTableModel.setNames(usedVarNames);
			selectionSorter.setModel(autoSelectionTableModel);
		}else{
			autoSelectionNoDelayTableModel.setNames(usedVarNames);
			selectionNoDelaySorter.setModel(autoSelectionNoDelayTableModel);
		}
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
		if(hasTimeStamps){
			for(int i=0;i<vc;i++){
/*				if(((JRadioButton)outChecks.elementAt(i)).isSelected() 
					|| ((JRadioButton)inChecks.elementAt(i)).isSelected()){
					usedVarNames.addElement(varNames.elementAt(i));
				}
*/
				if(((JRadioButton)inChecks.elementAt(i)).isSelected()){
					usedVarNames.addElement(varNames.elementAt(i));
				}

				if(((JRadioButton)outChecks.elementAt(i)).isSelected()){
					outVarNames.addElement(varNames.elementAt(i));
				}
				varDelayCalculated[i] = false;
			}
			delayTableModel.resetNames(usedVarNames);
			autoSelectionTableModel.setNames(usedVarNames);
			selectionSorter.setModel(autoSelectionTableModel);
		}else{
			for(int i=0;i<vc;i++){
				if(((JRadioButton)inChecks.elementAt(i)).isSelected()){
					usedVarNames.addElement(varNames.elementAt(i));
				}
				varDelayCalculated[i] = false;
			}
			autoSelectionNoDelayTableModel.setNames(usedVarNames);
			selectionNoDelaySorter.setModel(autoSelectionNoDelayTableModel);
		}
		calculateDelay.setEnabled(true);
	}

	private void convertDelayFromTimeUnits(int from, int to){

		double divide1 = 60000;
		if(from == 1)
			divide1 = 3600000;
		else if(from == 3)
			divide1 = 1000;

		double divide2 = 60000;
		if(to == 1)
			divide2 = 3600000;
		else if(to == 3)
			divide2 = 1000;

		double ratio = divide2/divide1;
		int count = delaysSettings.size();
		for(int i=0;i<count;i++){
			long[] dset = (long[])delaysSettings.elementAt(i);
			double val = ((double)dset[0])*ratio;
			dset[0]= (long)val;
			val = ((double)dset[1])*ratio;
			dset[1]= (long)val;
		}
		for(int i=0;i<delayIntervals.length;i++){
			double val = ((double)delayIntervals[i])*ratio;
			delayIntervals[i] = (long)val;
		}
		delayTableView.validate();
		delayTableView.repaint(0l);
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

	class DelayTableModel extends AbstractTableModel{
		private int row,col;
		private Vector names;
		private String[] colHd = {
			frame.getNolResourceString(VARIABLE),
			frame.getNolResourceString(MINDELAY),
			frame.getNolResourceString(MAXDELAY),
			frame.getNolResourceString(INTERVAL)};
//		private String[] colHd = {"Variable","Min Delay", "Max Delay","Interval"};

		public DelayTableModel(){
			row = 0;
			col = 4;
			names = null;
		}

		public void resetNames(Vector names){
			this.names = names;
			row = names.size();
		}

		public void setNames(Vector names){
			long divide = 60000;
			if(delayTimeSettingFlag == 1)
				divide = 3600000;
			else if(delayTimeSettingFlag == 3)
				divide = 1000;

			this.names = names;
			row = names.size();
			for(int r=0;r<names.size();r++){
				String n = (String)names.elementAt(r);
				int rr = varNames.indexOf(n);			
				long[] dset = (long[])delaysSettings.elementAt(rr);
				if(outVarNames.contains(n)){
					dset[0] = divide;
					dset[1] = divide;
					delayIntervals[rr] = 0;
				}else{
					dset[0] = 0;
					dset[1] = 0;
					delayIntervals[rr] = 0;
				}
			}

		}
		@Override
		public int getColumnCount() { return col; }
		@Override
		public int getRowCount() { return row;}
		@Override
		public Object getValueAt(int r, int c){
			long divide = 60000;
			if(delayTimeSettingFlag == 1)
				divide = 3600000;
			else if(delayTimeSettingFlag == 3)
				divide = 1000;

			if(c == 0){
				return names.elementAt(r);
			}else if(c == 1){
				String n = (String)names.elementAt(r);
				int rr = varNames.indexOf(n);
				long[] dset = (long[])delaysSettings.elementAt(rr);
				double val = ((double)dset[0])/((double)divide);
				return String.valueOf(val);
			}else if(c == 2){
				String n = (String)names.elementAt(r);
				int rr = varNames.indexOf(n);
				long[] dset = (long[])delaysSettings.elementAt(rr);
				double val = ((double)dset[1])/((double)divide);
				return String.valueOf(val);
			}else if(c == 3){
				String n = (String)names.elementAt(r);
				int rr = varNames.indexOf(n);
				double val = ((double)delayIntervals[rr])/((double)divide);
				return String.valueOf(val);
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
			if(c==0)
				return false;
			return true;
		}

		@Override
		public void setValueAt(Object aValue, int r, int c) {
			long divide = 60000;
			if(delayTimeSettingFlag == 1)
				divide = 3600000;
			else if(delayTimeSettingFlag == 3)
				divide = 1000;

			delayTableView.requestFocus();
			long value = 0;
			try{
				value = (long)((Double.valueOf((String)aValue).doubleValue())*divide);
			}catch(NumberFormatException evt){
			}
			String n = (String)names.elementAt(r);
			int rr = varNames.indexOf(n);
			
			if(value<=0L && outVarNames.contains(n)){	
				if(c==1 || c==2){
					delayTableView.validate();
					delayTableView.repaint(0l);
					return;
				}
			}

			if(value<0L ){
				value =0L;
			}
			if(c==1){
				long[] dset = (long[])delaysSettings.elementAt(rr);
				if(value > dset[1]){
					dset[1] = value;
					dset[0] = value;
				}else{
					dset[0] = value;
					if(delayIntervals[rr] == 0)
						delayIntervals[rr] = divide;

				}
				varDelayCalculated[rr] = false;
			}else if(c==2){
				long[] dset = (long[])delaysSettings.elementAt(rr);
				if(value < dset[0]){
					dset[1] = dset[0];
				}else{
					dset[1] = value;
					if(delayIntervals[rr] == 0)
						delayIntervals[rr] = divide;
				}
				varDelayCalculated[rr] = false;
			}else if(c==3){
				long[] dset = (long[])delaysSettings.elementAt(rr);
				if(value > 0 ){ 
					if(value >(dset[1]-dset[0]))
						delayIntervals[rr] = (dset[1]-dset[0]);
					else
						delayIntervals[rr] = value;
				}
				varDelayCalculated[rr] = false;
			}
			arrangeDelays();
			calculateDelay.setEnabled(true);
			if(hasTimeStamps){
				autoSelectionTableModel.setNames(usedVarNames);
				selectionSorter.setModel(autoSelectionTableModel);
			}else{
				autoSelectionNoDelayTableModel.setNames(usedVarNames);
				selectionNoDelaySorter.setModel(autoSelectionNoDelayTableModel);
			}
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
		private String[] colHd = {
			frame.getNolResourceString(VARIABLE),
			frame.getNolResourceString(DELAY),
			frame.getNolResourceString(RATING),
			frame.getNolResourceString(USED)};
//		private String[] colHd = {"Variable","Delay","Rating", "Used"};

		public AutoSelectionTableModel(){
			row = 0;
			col = 4;
			names = new Vector();
			nameswithdelay = new Vector();
			delayValues = new Vector();
			ratings = new Vector();
			usedchecks = new Vector();
		}

		public void setNames(Vector names){
			this.names = names;
			int nc = names.size();
			nameswithdelay.removeAllElements();
			delayValues.removeAllElements();
			ratings.removeAllElements();
			usedchecks.removeAllElements();

			long divide = 60000;
			if(delayTimeSettingFlag == 1)
				divide = 3600000;
			else if(delayTimeSettingFlag == 3)
				divide = 1000;

			for(int i=0;i<nc;i++){
				String n = (String)names.elementAt(i);
				int rr = varNames.indexOf(n);
				int outindex = outVarNames.indexOf(n);
				long[] dls = (long[])delays.elementAt(rr);
				double[] rates = (double[])varRatings.elementAt(rr);
				for(int j=0;j<dls.length;j++){
					if(!(outindex !=-1 && dls[j] == 0l)){
						nameswithdelay.addElement(n);
						double val = ((double)dls[j])/((double)divide);
						delayValues.addElement(String.valueOf(val));
						if(!varDelayCalculated[rr]){
							ratings.addElement("");
						}else{
							ratings.addElement(Utilities.formatDouble(rates[j], digits));
						}
						JCheckBox check = new JCheckBox(){
							@Override
							public float getAlignmentY() { return 0.0f; }			
						};
						check.setBackground(Color.white);
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
		@Override
		public int getColumnCount() { return col; }
		@Override
		public int getRowCount() { return row;}
		@Override
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

		public Vector getNamesWithDelay(){
			return nameswithdelay;
		}

		@Override
		public void setValueAt(Object aValue, int r, int c) {
//			System.out.println("value="+ aValue);
		}
	}



	class AutoSelectionNoDelayTableModel extends AbstractTableModel{
		private int row,col;
		private int digits = 5;
		private Vector names;
		private Vector ratings;
		private Vector usedchecks;
		private String[] colHd = {
			frame.getNolResourceString(VARIABLE),
			frame.getNolResourceString(RATING),
			frame.getNolResourceString(USED)};
//		private String[] colHd = {"Variable","Rating", "Used"};

		public AutoSelectionNoDelayTableModel(){
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
				if(!varDelayCalculated[rr]){
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
		public Vector getNames(){
			return names;
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
		@Override
		public void setValueAt(Object aValue, int r, int c) {
		}
	}


	@Override
	protected boolean finishAction(){
		Matlib.pack() ;
		int c = varNames.size();
		Vector ins = new Vector();
		Vector outs = new Vector();
		Vector outchecks = varClassifyTableModel.getOutputChecks();
		Vector inchecks = varClassifyTableModel.getInputChecks();
		Vector outDelays = new Vector();
		Vector inDelays = new Vector();
		int nout = 0;
		int inputCols = 0;
		int ndls = 0;
		
		Vector names = null;
		if(hasTimeStamps){
			names= autoSelectionTableModel.getNamesWithDelay();
		}else{
			names= autoSelectionNoDelayTableModel.getNames();
		}
		if(names.isEmpty()){
			frame.showOKDialog(frame.getNolResourceString(NOINPUTISSPECIFIED));
			return false;
		}
	
		Vector newDelayValues = readDelaysFromAutoSelectChecks();		
		for(int i=0;i<c;i++){
			if(((JRadioButton)outchecks.elementAt(i)).isSelected()){
				long[] dls = (long[])newDelayValues.elementAt(i);
				outDelays.addElement(dls);
				outs.addElement(varNames.elementAt(i));
				nout++;
				for(int j=0;j<dls.length;j++){
					if(dls[j]>0)
						inputCols++;
				}
			}else if(((JRadioButton)inchecks.elementAt(i)).isSelected()){
				long[] dls = (long[])newDelayValues.elementAt(i);
				if(dls.length > 0){
					inDelays.addElement(dls);
					ins.addElement(varNames.elementAt(i));
				}
				inputCols = inputCols+dls.length;
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
		int nfactor = 1;
		if(fixFactor.isSelected()){
  			String s = factorNumber.getText();
			try{
				nfactor = Integer.valueOf(s).intValue();
			}catch(NumberFormatException  evt){
				nfactor = 1;
			}
		}
		if(nfactor < 1){
			nfactor = 1;
		}

		ArchitectureParameters AP = new ArchitectureParameters(inputCols,nout,0,nfactor);
		model = new NolPlsModel(AP,modelName.getText(),outs ,
			ins,outDelays,inDelays, preprocessor);
		model.setFixedFactor(fixFactor.isSelected());
		model.setFixedFactorNumber(nfactor);
		buildModel(model);
		model.setIsTrained(true);
		String comment = modelDescript.getText();
		model.setDelayTimeUnit(delayTimeSettingFlag);
		model.setHasTimeStamps(hasTimeStamps);
		if(comment != null)
			model.setComment(comment);
		return true;
	}

	public Vector readDelaysFromAutoSelectChecks(){
		Vector usedChecks = null;
		Vector names = null;
		
		if(hasTimeStamps){
			usedChecks = autoSelectionTableModel.getUsedChecks();
			names= autoSelectionTableModel.getNamesWithDelay();
		}else{
			usedChecks = autoSelectionNoDelayTableModel.getUsedChecks();
			names= autoSelectionNoDelayTableModel.getNames();
		}
		if(names.isEmpty()) 
			return new Vector(); //Add for special case robust.
		String n = (String)names.elementAt(0);
		int rold = varNames.indexOf(n);
		int c=0;
		Vector delaySettings = new Vector();
		for(int i=0;i<delays.size();i++){
			long[] dls = (long[])delays.elementAt(i);
			long[] newdls = new long[dls.length];
			delaySettings.addElement(newdls);
		}

		for(int i=0;i<names.size();i++){
			n = (String)names.elementAt(i);
			int rr = varNames.indexOf(n);
			long[] newdls = (long[])delaySettings.elementAt(rr);
			long[] dls = (long[])delays.elementAt(rr);
			if(rr == rold){
				if(((JCheckBox)usedChecks.elementAt(i)).isSelected()){ 
					newdls[c] = dls[c];
				}else{
					newdls[c] = -1;
				}
				c++;
			}else{
				c = 0;
				if(((JCheckBox)usedChecks.elementAt(i)).isSelected()){ 
					newdls[c] = dls[c];
				}else{
					newdls[c] = -1;
				}
				c++;
				rold = rr;
			}
		}
		for(int i=0;i<delaySettings.size();i++){
			long[] newdls = (long[])delaySettings.elementAt(i);
			int count = 0;
			for(int j=0;j<newdls.length;j++){
				if(newdls[j]>-1)
					count++;
			}
			if(count>0){
				long[] ndls = new long[count];
				int l=0;
				for(int k=0;k<newdls.length;k++){
					if(newdls[k]>-1){
						ndls[l] = newdls[k];
						l++;
					}
				}
				delaySettings.setElementAt(ndls,i);
			}else{
				delaySettings.setElementAt(new long[0],i);
			}
		}
		return delaySettings;
	}

	class AdvancedDialog extends JDialog{
		AdvancedDialog(JFrame frame, String title, boolean flag){
			super(frame,title,flag);
			initialDialogLayout();
		}
		private void initialDialogLayout(){
			JPanel modelTypePane = new JPanel(new GridLayout(1,3,25,25));
			modelTypePane.setBorder(BorderFactory.createTitledBorder("Model Types:"));

			URL url = this.getClass().getResource("linear.gif");
			ImageIcon linear = new ImageIcon(url);
			url = this.getClass().getResource("bpn.gif");
			ImageIcon bpn = new ImageIcon(url);
			url = this.getClass().getResource("nlpls.gif");
			ImageIcon nlpls = new ImageIcon(url);
			url = this.getClass().getResource("rbf.gif");
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
			control.setBackground(getContentPane().getBackground());
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
				if(nofire) {
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
				if(clickCount != 2) {
					return;
				}
				isOk = okFired();
				closeDialog();
			}
		}
	}

	private boolean buildModel(NolPlsModel model){
		Matlib.pack() ;
		Matrix X = Matlib.createMatrix();
		Matrix Y = Matlib.createMatrix();
		try{
			model.prepareTrainingSet(X, Y);
			if(X.getRows() <10){
				frame.showOKDialog(frame.getNolResourceString("TrainDialog_NoDataForTraining"));
				return false;
			}
			model.train(X, Y);
		}catch (MathException evt){
			System.err.println("Non-Fatal exception: " + evt.getMessage());
			evt.printStackTrace();	
			return false;
		}
		return true;
	}
}
