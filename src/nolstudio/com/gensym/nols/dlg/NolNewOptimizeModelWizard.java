package com.gensym.nols.dlg;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
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

public class NolNewOptimizeModelWizard  extends NolWizardDialog 
	implements NolNewModelWizard{

	private	JTextField modelName;
	private	JTextField caseName;
	private	JTextField outputDataSeriesName;
	private	JTextField stateDataSeriesName;
	private JTextArea modelDescript;

	private JTextField ratingThreshold1;
	private JTextField ratingThreshold2;

	private JButton calculateDelay1;
	private JButton calculateDelay2;

	private JButton advancedStruct;
	private JList caseList;
	private JList outputDataSeriesList;
	private JList stateDataSeriesList;
	private DefaultListModel caseListModel;
	private DefaultListModel outputDataSeriesListModel;
	private DefaultListModel stateDataSeriesListModel;

	private ControlAction actionListener;

	private	VarClassifyTableModel varClassifyTableModel;
	private	JTable varClassifyTableView;

	private	DelayTableModel delayTableModel1;
	private	JTable delayTableView1;
	private	DelayTableModel delayTableModel2;
	private	JTable delayTableView2;

	private	AutoSelectionTableModel autoSelectionTableModel1;
	private	AutoSelectionNoDelayTableModel autoSelectionNoDelayTableModel1;
	private	JTable autoSelectionTableView1;
	private	AutoSelectionTableModel autoSelectionTableModel2;
	private	AutoSelectionNoDelayTableModel autoSelectionNoDelayTableModel2;
	private	JTable autoSelectionTableView2;

	private TableSorter selectionSorter1;
	private TableSorter selectionNoDelaySorter1;
	private TableSorter selectionSorter2;
	private TableSorter selectionNoDelaySorter2;

	
	private JRadioButton autoStructFlag;
	private JRadioButton manualStructFlag;
	private JLabel numOfVariable1;
	private JLabel numOfSample1;
	private JLabel numOfVariable2;
	private JLabel numOfSample2;

	private NolMainFrame frame;	 

	private int delayTimeSettingFlag1;  //1:hour 2: minut 3: second
	private int delayTimeSettingFlag2;  //1:hour 2: minut 3: second
	private boolean noFire;
	private boolean hasTimeStamps;

	// parameters for modeling.

	private Preprocessor preprocessor;
	private DataSeries dataSeries1;
	private DataSeries dataSeries2;

	// parameters for modeling.
	private NolOptimizeModel model;
	private boolean[] varDelayCalculated1;
	private boolean[] varDelayCalculated2;
	private Vector varNames;
	private Vector namesForOutputs;
	private Vector outVarNames;
	private Vector namesForStates;
	private Vector stateVarNames;
	private Vector model1VarNames;
	private Vector model2VarNames;
	private Vector delays1;
	private Vector delays2;
	private long[] delayIntervals1;
	private long[] delayIntervals2;
	private Vector delaysSettings1;
	private Vector delaysSettings2;
	private Vector varRatings1;
	private Vector varRatings2;
	private double ratingThresholdValue1;
	private double ratingThresholdValue2;

	private static final String GENERAL_LABEL = "NewOptimizeModelWizard_GeneralLabel";
	private static final String COMMENT_LABEL = "CommentLabel";
	private static final String NAMEEDITLABEL = "NewOptimizeModelWizard_NameEditLabel";
	private static final String PREPROCESSOR_LABEL = "NewOptimizeModelWizard_PreprocessorLabel";
	private static final String PREPROCESSOR = "NewOptimizeModelWizard_Preprocessor";
	private static final String OUTPUTDATASOURCE_LABEL = "NewOptimizeModelWizard_OutputDataSourceLabel";
	private static final String DATASERIES = "NewOptimizeModelWizard_DataSeries";
	private static final String VARIABLE = "NewOptimizeModelWizard_Variable";
	private static final String SAMPLE = "NewOptimizeModelWizard_Sample";
	private static final String STATEDATASOURCE_LABEL = "NewOptimizeModelWizard_StateDataSourceLabel";
	private static final String CLASSIFICATION_LABEL = "NewOptimizeModelWizard_ClassificationLabel";
	private static final String NODELAY_LABEL = "NewOptimizeModelWizard_NoDelayLabel";
	private static final String DELAY_LABEL = "NewOptimizeModelWizard_DelayLabel";
	private static final String HOUR = "NewOptimizeModelWizard_Hour";
	private static final String MINUTE = "NewOptimizeModelWizard_Minute";
	private static final String SECOND = "NewOptimizeModelWizard_Second";
	private static final String DELAYS = "NewOptimizeModelWizard_Delays";
	private static final String SETTING1_LABEL = "NewOptimizeModelWizard_Setting1Label";
	private static final String SETTING1_BORDER = "NewOptimizeModelWizard_Setting1Border";
	private static final String THRESHOLD = "NewOptimizeModelWizard_Threshold";
	private static final String CALCULATERATINGS = "NewOptimizeModelWizard_CalculateRatings";
	private static final String DELAY2_LABEL = "NewOptimizeModelWizard_Delay2Label";
	private static final String SETTING2_LABEL = "NewOptimizeModelWizard_Setting2Label";
	private static final String STRUCTURE_LABEL = "NewOptimizeModelWizard_StructureLabel";
	private static final String OUTPUT = "NewOptimizeModelWizard_Output";
	private static final String MANIPULATE = "NewOptimizeModelWizard_Manipulate";
	private static final String STATE = "NewOptimizeModelWizard_State";
	private static final String EXOGENOUS = "NewOptimizeModelWizard_Exogenous";
	private static final String UNUSED = "NewOptimizeModelWizard_Unused";
	private static final String MINTIMESHIFT = "NewOptimizeModelWizard_MinTimeShift";
	private static final String MAXTIMESHIFT = "NewOptimizeModelWizard_MaxTimeShift";
	private static final String INTERVAL = "NewOptimizeModelWizard_Interval";
	private static final String TIMESHIFT = "NewOptimizeModelWizard_TimeShift";
	private static final String RATING = "NewOptimizeModelWizard_Rating";
	private static final String USED = "NewOptimizeModelWizard_Used";
	private static final String NOOUTPUTISSPECIFIED = "NewOptimizeModelWizard_NoOutputIsSpecified";
	private static final String NOINPUTISSPECIFIED = "NewOptimizeModelWizard_NoInputIsSpecified";
	private static final String NOINPUTFORSTATEMODEL = "NewOptimizeModelWizard_NoInputForStateModel";
	private static final String NOLFINITEDATA = "NewOptimizeModelWizard_NoFiniteData";
	private static final String THRESHOLDTOOLTIP = "NewOptimizeModelWizard_ThresholdToolTip";
	private static final String NONAMEFORTHISMODEL = "NewOptimizeModelWizard_NoNameForThisModel";
	

	public NolNewOptimizeModelWizard (NolMainFrame dw) {
		super((JFrame)dw, "Create New Optimization Model", true, 9);
		frame = (NolMainFrame)dw;
		actionListener = new ControlAction();
		noFire = false;
		varNames = new Vector();
		namesForOutputs = new Vector();
		stateVarNames = new Vector();
		namesForStates = new Vector();
		outVarNames = new Vector();
		model1VarNames = new Vector();
		model2VarNames = new Vector();
		delays1 = new Vector();
		delays2 = new Vector();
		delaysSettings1 = new Vector();
		delaysSettings2 = new Vector();
		varRatings1 = new Vector();
		varRatings2 = new Vector();
		ratingThresholdValue1 = 3.0;
		ratingThresholdValue2 = 3.0;
		delayTimeSettingFlag1 = 2;
		delayTimeSettingFlag2 = 2;
		initializeLayout();
		initDataDisplay();
	}

	private void initializeLayout(){

		stepPanes.setElementAt(getGeneralPanel(),0);
		stepPanes.setElementAt(getCasePanel(),1);
		stepPanes.setElementAt(getOutputDataSourcePanel(),2);
		stepPanes.setElementAt(getStateDataSourcePanel(),3);
		stepPanes.setElementAt(getClassificationPanel(),4);
		stepPanes.setElementAt(getDelay1Pane(),5);
		stepPanes.setElementAt(getSetting1Pane(),6);
		stepPanes.setElementAt(getDelay2Pane(),7);
		stepPanes.setElementAt(getSetting2Pane(),8);
//		stepPanes.setElementAt(getStructurePane(),8);
	}

	private JPanel getGeneralPanel(){
		JPanel genPane = new JPanel(new BorderLayout());
		URL url = this.getClass().getResource("largeOptimizationModel.gif");
		ImageIcon importIcon = new ImageIcon(url);

		JPanel infoPane = new JPanel(new BorderLayout());
 		infoPane.setBorder(new EmptyBorder(10,10,10,10));

		String s = frame.getNolResourceString(GENERAL_LABEL);
//		String s = "A optimization model is used to for solving\n"+
//			"an optimization problem.";
		
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
//		namePane.add(new JLabel("Enter the name for this model:"));
		modelName = new JTextField();
		modelName.addActionListener(actionListener);
		namePane.add(modelName);
		namePane.add(new JLabel(frame.getNolResourceString(COMMENT_LABEL)+":"));
//		namePane.add(new JLabel("Comment:"));
 		cenPane.add("North",namePane);

		JPanel descripPane = new JPanel(new GridLayout());
 		descripPane.setBorder(new EmptyBorder(0,10,10,10));
		modelDescript = new JTextArea();
		JScrollPane listScrollPane = new JScrollPane(modelDescript);
		listScrollPane.setBorder(BorderFactory.createLoweredBevelBorder());
		descripPane.add(listScrollPane);
 		cenPane.add("Center",descripPane);

 		genPane.add("Center",cenPane);
		return genPane;
	}

	private JPanel getCasePanel(){
		JPanel dataPane = new JPanel(new BorderLayout());
		JPanel infoPane = new JPanel(new GridLayout());
 		infoPane.setBorder(new EmptyBorder(10,10,10,10));
		String s = frame.getNolResourceString(PREPROCESSOR_LABEL);
//		String s = "What preprocessor has been used to create data for this model? ";
		JTextArea infoLabel = new JTextArea(s);
		infoLabel.setLineWrap(true);
		infoLabel.setWrapStyleWord(true);
		infoLabel.setEditable(false);
		infoLabel.setBackground(infoPane.getBackground());
		infoPane.add(infoLabel);

		dataPane.add("North",infoPane);

		JPanel cenPane = new JPanel(new BorderLayout());
 		cenPane.setBorder(new EmptyBorder(10,10,10,10));

		JPanel sourcePane = new JPanel(new GridLayout(1,2,20,20));
 		sourcePane.setBorder(new EmptyBorder(0,0,10,0));
		sourcePane.add(new JLabel(frame.getNolResourceString(PREPROCESSOR)+":"));
		caseName = new JTextField();
		caseName.setEditable(false);
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

	private JPanel getOutputDataSourcePanel(){
		JPanel dataPane = new JPanel(new BorderLayout());
		JPanel infoPane = new JPanel(new GridLayout());
 		infoPane.setBorder(new EmptyBorder(10,10,10,10));
		String s = frame.getNolResourceString(OUTPUTDATASOURCE_LABEL);
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
		outputDataSeriesName = new JTextField();
		outputDataSeriesName.setEditable(false);
		sourcePane.add(outputDataSeriesName);

 		cenPane.add("North",sourcePane);

		JPanel listPane = new JPanel(new GridLayout());
		outputDataSeriesList = new JList(getOutputDataSeriesListModel());
		outputDataSeriesList.setBackground(Color.white);
		outputDataSeriesList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		outputDataSeriesList.addListSelectionListener(actionListener);
		JScrollPane listScrollPane = new JScrollPane(outputDataSeriesList);
		listScrollPane.setBorder(BorderFactory.createLoweredBevelBorder());
		listScrollPane.setPreferredSize(NolMainFrame.vpad50);
		listPane.add(listScrollPane);

  		cenPane.add("Center",listPane);

		JPanel numPane = new JPanel(new GridLayout(1,4,10,10));
 		numPane.setBorder(new EmptyBorder(10,0,10,0));
		numPane.add(new JLabel(frame.getNolResourceString(VARIABLE)+":"));
		numOfVariable1  = new JLabel();
		numPane.add(numOfVariable1);
		numPane.add(new JLabel(frame.getNolResourceString(SAMPLE)+":"));
		numOfSample1  = new JLabel();
		numPane.add(numOfSample1);

  		cenPane.add("South",numPane);

		dataPane.add("Center",cenPane);
		
		return dataPane;
	}

	private JPanel getStateDataSourcePanel(){
		JPanel dataPane = new JPanel(new BorderLayout());
		JPanel infoPane = new JPanel(new GridLayout());
 		infoPane.setBorder(new EmptyBorder(10,10,10,10));
		String s = frame.getNolResourceString(STATEDATASOURCE_LABEL);
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
		stateDataSeriesName = new JTextField();
		stateDataSeriesName.setEditable(false);
		sourcePane.add(stateDataSeriesName);

 		cenPane.add("North",sourcePane);

		JPanel listPane = new JPanel(new GridLayout());
		stateDataSeriesList = new JList(getStateDataSeriesListModel());
		stateDataSeriesList.setBackground(Color.white);
		stateDataSeriesList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		stateDataSeriesList.addListSelectionListener(actionListener);
		JScrollPane listScrollPane = new JScrollPane(stateDataSeriesList);
		listScrollPane.setBorder(BorderFactory.createLoweredBevelBorder());
		listScrollPane.setPreferredSize(NolMainFrame.vpad50);
		listPane.add(listScrollPane);

  		cenPane.add("Center",listPane);

		JPanel numPane = new JPanel(new GridLayout(1,4,10,10));
 		numPane.setBorder(new EmptyBorder(10,0,10,0));
		numPane.add(new JLabel(frame.getNolResourceString(VARIABLE)+":"));
		numOfVariable2  = new JLabel();
		numPane.add(numOfVariable2);
		numPane.add(new JLabel(frame.getNolResourceString(SAMPLE)+":"));
		numOfSample2  = new JLabel();
		numPane.add(numOfSample2);

  		cenPane.add("South",numPane);

		dataPane.add("Center",cenPane);
		
		return dataPane;
	}

	private JPanel getClassificationPanel(){
		JPanel classPane = new JPanel(new BorderLayout());
		JPanel infoPane = new JPanel(new GridLayout());
 		infoPane.setBorder(new EmptyBorder(10,10,10,10));
		String s = frame.getNolResourceString(CLASSIFICATION_LABEL);
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

  	private JPanel getNoDelayPane(){
		JPanel delayPane = new JPanel(new GridLayout());
		JPanel infoPane = new JPanel(new GridLayout());
 		infoPane.setBorder(new EtchedBorder(EtchedBorder.LOWERED));
		infoPane.setBackground(Color.white);
		String s = frame.getNolResourceString(NODELAY_LABEL);
//		String s = "   There are no time-stamps, thus you need not specify\n"+
//					"   time delays. However, If you wish to set time delays,\n"+
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
	
	private JPanel getDelay1Pane(){
		JPanel delayPane = new JPanel(new BorderLayout());
		JPanel infoPane = new JPanel(new GridLayout());
 		infoPane.setBorder(new EmptyBorder(10,10,10,10));
		String s = frame.getNolResourceString(DELAY_LABEL);
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
		radio.setActionCommand("Hour1");
		radio.addActionListener(actionListener);
		group.add(radio);
		timePane.add(radio);
		radio = new JRadioButton(frame.getNolResourceString(MINUTE),true);
		radio.setActionCommand("Minute1");
		radio.addActionListener(actionListener);
		group.add(radio);
		timePane.add(radio);
		radio = new JRadioButton(frame.getNolResourceString(SECOND));
		radio.setActionCommand("Second1");
		radio.addActionListener(actionListener);
		group.add(radio);
		timePane.add(radio);

 		cenPane.setBorder(new EmptyBorder(10,10,10,10));
  		JPanel delPane = new JPanel(new GridLayout());
		delPane.setBorder(BorderFactory.createTitledBorder(frame.getNolResourceString(DELAYS)+":"));

		delayTableModel1 = new DelayTableModel();
		delayTableView1 = new JTable(delayTableModel1);
		delayTableView1.setSelectionMode(0);
		delayTableView1.setSelectionBackground(Color.white);
		delayTableView1.setCellSelectionEnabled(true);
		delayTableView1.setSelectionForeground(Color.black);
		JScrollPane listScrollPane = new JScrollPane(delayTableView1);
		listScrollPane.setBackground(Color.white);
		delPane.add(listScrollPane);

		cenPane.add("North",timePane);
		cenPane.add("Center",delPane);
		delayPane.add("Center",cenPane);

		return delayPane;
	}

 	private JPanel getSetting1Pane(){
		JPanel setPane = new JPanel(new BorderLayout());
		JPanel infoPane = new JPanel(new GridLayout());
 		infoPane.setBorder(new EmptyBorder(10,10,10,10));
		String s = frame.getNolResourceString(SETTING1_LABEL);
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
			frame.getNolResourceString(SETTING1_BORDER)));
		autoSelectionTableModel1 = new AutoSelectionTableModel();
		autoSelectionNoDelayTableModel1 = new AutoSelectionNoDelayTableModel();
		
		selectionSorter1 = new TableSorter(autoSelectionTableModel1); //ADDED THIS FOR  SORTING GCHEN 6.7.99
		selectionNoDelaySorter1 = new TableSorter(autoSelectionNoDelayTableModel1); //ADDED THIS FOR  SORTING GCHEN 6.7.99
		
		autoSelectionTableView1 = new JTable(selectionSorter1);
		autoSelectionTableView1.setDefaultRenderer(AbstractButton.class, 
			new AutoSelectRenderer());
		selectionSorter1.addMouseListenerToHeaderInTable(autoSelectionTableView1);
		selectionNoDelaySorter1.addMouseListenerToHeaderInTable(autoSelectionTableView1);
		
		autoSelectionTableView1.setSelectionMode(0);
		autoSelectionTableView1.setSelectionBackground(Color.white);
		autoSelectionTableView1.setCellSelectionEnabled(true);
		autoSelectionTableView1.setSelectionForeground(Color.black);
		JScrollPane listScrollPane = new JScrollPane(autoSelectionTableView1);
		listScrollPane.setBackground(Color.white);

		
		JPanel actPane = new JPanel(new GridLayout(1,3,10,10));
		actPane.setBorder(new EmptyBorder(10, 10, 10, 10));               

		actPane.add(new JLabel(frame.getNolResourceString(THRESHOLD)+":", SwingConstants.CENTER));
 		ratingThreshold1 = new JTextField("");
		ratingThreshold1.setToolTipText(frame.getNolResourceString(THRESHOLDTOOLTIP));
		ratingThreshold1.addActionListener(actionListener);
		actPane.add(ratingThreshold1);
//		actPane.add(new JLabel("Recommended: 0.5", SwingConstants.CENTER));
		calculateDelay1 = new JButton(frame.getNolResourceString(CALCULATERATINGS));
		calculateDelay1.setActionCommand("Calculate Ratings");
		calculateDelay1.addActionListener(actionListener);
		actPane.add(calculateDelay1);
		
		autoPane.add("Center",listScrollPane);
		autoPane.add("South",actPane);

		cenPane.add(autoPane);
		setPane.add("Center",cenPane);


		return setPane;
	}

 	private JPanel getDelay2Pane(){
		JPanel delayPane = new JPanel(new BorderLayout());
		JPanel infoPane = new JPanel(new GridLayout());
 		infoPane.setBorder(new EmptyBorder(10,10,10,10));
		String s = frame.getNolResourceString(DELAY2_LABEL);
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
		radio.setActionCommand("Hour2");
		radio.addActionListener(actionListener);
		group.add(radio);
		timePane.add(radio);
		radio = new JRadioButton(frame.getNolResourceString(MINUTE),true);
		radio.setActionCommand("Minute2");
		radio.addActionListener(actionListener);
		group.add(radio);
		timePane.add(radio);
		radio = new JRadioButton(frame.getNolResourceString(SECOND));
		radio.setActionCommand("Second2");
		radio.addActionListener(actionListener);
		group.add(radio);
		timePane.add(radio);

		cenPane.setBorder(new EmptyBorder(10,10,10,10));
  		JPanel delPane = new JPanel(new GridLayout());
		delPane.setBorder(BorderFactory.createTitledBorder(frame.getNolResourceString(DELAYS)+":"));

		delayTableModel2 = new DelayTableModel();
		delayTableView2 = new JTable(delayTableModel2);
		delayTableView2.setSelectionMode(0);
		delayTableView2.setSelectionBackground(Color.white);
		delayTableView2.setCellSelectionEnabled(true);
		delayTableView2.setSelectionForeground(Color.black);
		JScrollPane listScrollPane = new JScrollPane(delayTableView2);
		listScrollPane.setBackground(Color.white);
		delPane.add(listScrollPane);

		cenPane.add("North",timePane);
		cenPane.add("Center",delPane);
		delayPane.add("Center",cenPane);

		return delayPane;
	}

 	private JPanel getSetting2Pane(){
		JPanel setPane = new JPanel(new BorderLayout());
		JPanel infoPane = new JPanel(new GridLayout());
 		infoPane.setBorder(new EmptyBorder(10,10,10,10));
		String s = frame.getNolResourceString(SETTING2_LABEL);
		JTextArea infoLabel = new JTextArea(s);
		infoLabel.setLineWrap(true);
		infoLabel.setWrapStyleWord(true);
		infoLabel.setEditable(false);
		infoLabel.setBackground(infoPane.getBackground());
		infoPane.add(infoLabel);
		setPane.add("North",infoPane);

		JPanel cenPane = new JPanel(new GridLayout());
 		cenPane.setBorder(new EmptyBorder(10,10,10,10));
 		JPanel autoPane = new JPanel(new BorderLayout());
		autoPane.setBorder(BorderFactory.createTitledBorder("Automatically Select Variables & Calculate Delays:"));

		autoSelectionTableModel2 = new AutoSelectionTableModel();
		autoSelectionNoDelayTableModel2 = new AutoSelectionNoDelayTableModel();
		
		selectionSorter2 = new TableSorter(autoSelectionTableModel2); //ADDED THIS FOR  SORTING GCHEN 6.7.99
		selectionNoDelaySorter2 = new TableSorter(autoSelectionNoDelayTableModel2); //ADDED THIS FOR  SORTING GCHEN 6.7.99
		

		
		autoSelectionTableView2 = new JTable(selectionSorter1);
		autoSelectionTableView2.setDefaultRenderer(AbstractButton.class, 
			new AutoSelectRenderer());
		selectionSorter2.addMouseListenerToHeaderInTable(autoSelectionTableView2);
		selectionNoDelaySorter2.addMouseListenerToHeaderInTable(autoSelectionTableView2);

		autoSelectionTableView2.setSelectionMode(0);
		autoSelectionTableView2.setSelectionBackground(Color.white);
		autoSelectionTableView2.setCellSelectionEnabled(true);
		autoSelectionTableView2.setSelectionForeground(Color.black);
		JScrollPane listScrollPane = new JScrollPane(autoSelectionTableView2);
		listScrollPane.setBackground(Color.white);

		
		JPanel actPane = new JPanel(new GridLayout(1,3,10,10));
		actPane.setBorder(new EmptyBorder(10, 10, 10, 10));               

		actPane.add(new JLabel(frame.getNolResourceString(THRESHOLD)+":", SwingConstants.CENTER));
 		ratingThreshold2 = new JTextField("");
		ratingThreshold2.setToolTipText(frame.getNolResourceString(THRESHOLDTOOLTIP));
		ratingThreshold2.addActionListener(actionListener);
		actPane.add(ratingThreshold2);
//		actPane.add(new JLabel("Recommended: 0.5", SwingConstants.CENTER));
		calculateDelay2 = new JButton(frame.getNolResourceString(CALCULATERATINGS));
		calculateDelay2.setActionCommand("Calculate Ratings");
		calculateDelay2.addActionListener(actionListener);
		actPane.add(calculateDelay2);
		
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
			@Override
			public float getAlignmentX() { return 1.0f; }			
		};
		advancedStruct.setEnabled(false);
  		advancedStruct.addActionListener(actionListener);
		advancePane.add(advancedStruct);

		JTextArea structDescrip = new JTextArea(){
			Dimension dim = new Dimension(350,70);
			@Override
			public Dimension getPreferredSize() { return  dim;}			
			@Override
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
		}	
		return caseListModel;
	}	

	private DefaultListModel getOutputDataSeriesListModel() {
		if (outputDataSeriesListModel == null) {
			outputDataSeriesListModel = new DefaultListModel();
		}	
		return outputDataSeriesListModel;
	}	

	private DefaultListModel getStateDataSeriesListModel() {
		if (stateDataSeriesListModel == null) {
			stateDataSeriesListModel = new DefaultListModel();
		}	
		return stateDataSeriesListModel;
	}	

	
	public void resetData(){
		isOK = false;
		stepPane.removeAll();
		stepPane.add((JPanel)stepPanes.elementAt(0));
		stepPane.validate();
		stepPane.repaint(0l);
		currentStep = 1;
		modifyStep(false);
		String title = "Create New Optimization Model - "+setTitleForStep(currentStep);
		title = title + " - General";
		setTitle(title);
		initDataDisplay();
		modelDescript.setText("");
	}

	@Override
	protected void modifyStep(boolean isNext){
		super.modifyStep(isNext);
		String title = "Create New Optimization Model - "+setTitleForStep(currentStep);
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
			title = title + " - Data Source for Output";
			finishButton.setEnabled(false);
		}else if(currentStep == 4){
			title = title + " - Data Source for State";
			finishButton.setEnabled(false);
		}else if(currentStep == 5){
			title = title + " - Classification";
			finishButton.setEnabled(false);
		}else if(currentStep == 6){
			title = title + " - Delay for output model";
		}else if(currentStep == 7){
			title = title + " - Setting for output model";
		}else if(currentStep == 8){
			title = title + " - Delay for state model";
		}else if(currentStep == 9){
			title = title + " - Setting for state model";
		}else if(currentStep == 10){
			title = title + " - Structure";
		}
		if(DEBUG.debugFlag){
			System.out.println(title);
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
		selectedOutputDataSeries(0);
		selectedStateDataSeries(0);
		outputDataSeriesList.setSelectedIndex(0);
		stateDataSeriesList.setSelectedIndex(0);
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
		ratingThreshold1.setText(Utilities.formatDouble(ratingThresholdValue1, 3));
		ratingThreshold2.setText(Utilities.formatDouble(ratingThresholdValue2, 3));

		noFire = false;
	}
	
	public NolOptimizeModel getModel(){
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
		hasTimeStamps = preprocessor.getDataSeries(0).getHasTimeStamps();
		if(hasTimeStamps){
			stepPanes.setElementAt(getDelay1Pane(),5);
			stepPanes.setElementAt(getDelay2Pane(),7);
		}else{
			stepPanes.setElementAt(getNoDelayPane(),5);
			stepPanes.setElementAt(getNoDelayPane(),7);
		}
		caseName.setText(preprocessor.getName());
		int d = preprocessor.getNumberOfDataSeries();
		getOutputDataSeriesListModel().removeAllElements();
		getStateDataSeriesListModel().removeAllElements();
		for(int i=0;i<d;i++){
			String name = preprocessor.getDataSeriesName(i); 	
			getOutputDataSeriesListModel().addElement(name);
			getStateDataSeriesListModel().addElement(name);
		}
		outputDataSeriesList.validate();
		stateDataSeriesList.validate();

		Vector vpNames = preprocessor.getVariableNames();
		varNames.removeAllElements();
		model1VarNames.removeAllElements();
		model2VarNames.removeAllElements();
		delays1.removeAllElements();
		delays2.removeAllElements();
		delaysSettings1.removeAllElements();
		delaysSettings2.removeAllElements();
		varRatings1.removeAllElements();
		varRatings2.removeAllElements();

		for(int i=0;i<vpNames.size();i++){
			String name = vpNames.elementAt(i).toString();
			Variable varObj = preprocessor.getVariableFromVariableName(name);
			double std = varObj.getSTD();
			if(std>0){
				varNames.addElement(name);
				model1VarNames.addElement(name);
	//			delays1.addElement(new long[0]);
	//			delays2.addElement(new long[0]);
				delays1.addElement(new long[1]);
				delays2.addElement(new long[1]);
				delaysSettings1.addElement(new long[2]);
				delaysSettings2.addElement(new long[2]);
				varRatings1.addElement(new double[0]);
				varRatings2.addElement(new double[0]);
			}

		}
		delayIntervals1 = new long[varNames.size()];
		delayIntervals2 = new long[varNames.size()];
		varDelayCalculated1 = new boolean[varNames.size()];
		varDelayCalculated2 = new boolean[varNames.size()];
		varClassifyTableModel.setNames(varNames);
		if(hasTimeStamps){
			delayTableModel1.setNames(model1VarNames,true);
			delayTableModel2.setNames(model2VarNames, false);
			autoSelectionTableModel1.setNames(model1VarNames,true);
			autoSelectionTableModel2.setNames(model2VarNames,false);
			
			selectionSorter1.setModel(autoSelectionTableModel1);
			selectionSorter2.setModel(autoSelectionTableModel2);

			autoSelectionTableView1.setModel(selectionSorter1);
			autoSelectionTableView2.setModel(selectionSorter2);
			if(DEBUG.debugFlag){
				System.out.println("hasTimeStamps"+hasTimeStamps);
				System.out.println("autoSelectionTableModel1");
			}
		}else{
			autoSelectionNoDelayTableModel1.setNames(model1VarNames,true);
			autoSelectionNoDelayTableModel2.setNames(model2VarNames,false);					
			selectionNoDelaySorter1.setModel(autoSelectionNoDelayTableModel1);
			selectionNoDelaySorter2.setModel(autoSelectionNoDelayTableModel2);
			autoSelectionTableView1.setModel(selectionNoDelaySorter1);
			autoSelectionTableView2.setModel(selectionNoDelaySorter2);
		}
	}

	private void selectedOutputDataSeries(int selectedIndex){
		dataSeries1  = preprocessor.getDataSeries(selectedIndex);
 		outputDataSeriesName.setText(dataSeries1.getName());		
		Vector varObjs = dataSeries1.getVarObjects();

		namesForOutputs.removeAllElements();
		outVarNames.removeAllElements();

		for(int i=0;i<varObjs.size();i++){
			String name = varObjs.elementAt(i).toString();
			namesForOutputs.addElement(name);
		}
		int row = dataSeries1.getRow();
		numOfVariable1.setText(String.valueOf(varObjs.size()));
		numOfSample1.setText(String.valueOf(row));
	}
	
	private void selectedStateDataSeries(int selectedIndex){
  		dataSeries2  = preprocessor.getDataSeries(selectedIndex);
 		stateDataSeriesName.setText(dataSeries2.getName());		
		Vector varObjs = dataSeries2.getVarObjects();

		namesForStates.removeAllElements();
		stateVarNames.removeAllElements();

		for(int i=0;i<varObjs.size();i++){
			String name = varObjs.elementAt(i).toString();
			namesForStates.addElement(name);
		}
		int row = dataSeries2.getRow();
		numOfVariable2.setText(String.valueOf(varObjs.size()));
		numOfSample2.setText(String.valueOf(row));
	}
	
	private void convertDelayFromTimeUnits1(int from, int to){

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
		for(int i=0;i<delaysSettings1.size();i++){
			long[] dset = (long[])delaysSettings1.elementAt(i);
			double val = ((double)dset[0])*ratio;
			dset[0]= (long)val;
			val = ((double)dset[1])*ratio;
			dset[1]= (long)val;
		}
		for(int i=0;i<delayIntervals1.length;i++){
			double val = ((double)delayIntervals1[i])*ratio;
			delayIntervals1[i] = (long)val;
		}
		delayTableView1.validate();
		delayTableView1.repaint(0l);
	}
	
	private void convertDelayFromTimeUnits2(int from, int to){

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
		for(int i=0;i<delaysSettings2.size();i++){
			long[] dset = (long[])delaysSettings2.elementAt(i);
			double val = ((double)dset[0])*ratio;
			dset[0]= (long)val;
			val = ((double)dset[1])*ratio;
			dset[1]= (long)val;
		}
		for(int i=0;i<delayIntervals2.length;i++){
			double val = ((double)delayIntervals2[i])*ratio;
			delayIntervals2[i] = (long)val;
		}
		delayTableView2.validate();
		delayTableView2.repaint(0l);
	}
	
	
	class ControlAction extends AbstractAction implements ListSelectionListener {
		ControlAction() {	super("controlAction");}
        @Override
		public void actionPerformed(ActionEvent e) {
			if(noFire){
				return;
			}
			String command = e.getActionCommand();
			if(e.getSource().equals(calculateDelay1)){
//				calculateDelay1.setEnabled(false);
				calculateRatings(true);
			}else if(e.getSource().equals(calculateDelay2)){
//				calculateDelay2.setEnabled(false);
				calculateRatings(false);
			}else if(command.equals("Hour1")){
				if(delayTimeSettingFlag1 == 1){
					return;
				}
				convertDelayFromTimeUnits1(delayTimeSettingFlag1,1);
				delayTimeSettingFlag1 = 1;
			}else if(command.equals("Minute1")){
				if(delayTimeSettingFlag1 == 2){
					return;
				}
				convertDelayFromTimeUnits1(delayTimeSettingFlag1,2);
				delayTimeSettingFlag1 = 2;
			}else if(command.equals("Second1")){
				if(delayTimeSettingFlag1 == 3){
					return;
				}
				convertDelayFromTimeUnits1(delayTimeSettingFlag1,3);
				delayTimeSettingFlag1 = 3;
			}else if(command.equals("Hour2")){
				if(delayTimeSettingFlag2 == 1){
					return;
				}
				convertDelayFromTimeUnits2(delayTimeSettingFlag2,1);
				delayTimeSettingFlag2 = 1;
			}else if(command.equals("Minute2")){
				if(delayTimeSettingFlag2 == 2){
					return;
				}
				convertDelayFromTimeUnits2(delayTimeSettingFlag2,2);
				delayTimeSettingFlag2 = 2;
			}else if(command.equals("Second2")){
				if(delayTimeSettingFlag2 == 3){
					return;
				}
				convertDelayFromTimeUnits2(delayTimeSettingFlag2,3);
				delayTimeSettingFlag2 = 3;
			}else if(e.getSource().equals(ratingThreshold1)){
  				String s = ratingThreshold1.getText();
				try{
					double c = Double.valueOf(s).doubleValue();
					if(c>0){
						ratingThresholdValue1 = c;
						if(hasTimeStamps){
							autoSelectionTableModel1.goThrouthThreshold();
						}else{
							autoSelectionNoDelayTableModel1.goThrouthThreshold();
						}
						autoSelectionTableView1.validate();
						autoSelectionTableView1.repaint(0l);
					}
				}catch(NumberFormatException  evt){
					ratingThreshold1.setText(Utilities.formatDouble(ratingThresholdValue1, 3));
				}
			}else if(e.getSource().equals(ratingThreshold2)){
  				String s = ratingThreshold2.getText();
				try{
					double c = Double.valueOf(s).doubleValue();
					if(c>0){
						ratingThresholdValue2 = c;
						if(hasTimeStamps){
							autoSelectionTableModel2.goThrouthThreshold();
						}else{
							autoSelectionNoDelayTableModel2.goThrouthThreshold();
						}
						autoSelectionTableView2.validate();
						autoSelectionTableView2.repaint(0l);
					}
				}catch(NumberFormatException  evt){
					ratingThreshold2.setText(Utilities.formatDouble(ratingThresholdValue2, 3));
				}
			}else if(e.getSource().equals(modelName)){
				if(modelName.getText().equals("")){
					frame.showOKDialog(frame.getNolResourceString(NONAMEFORTHISMODEL));
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
				selectedOutputDataSeries(0);
				selectedStateDataSeries(0);
				outputDataSeriesList.setSelectedIndex(0);
				stateDataSeriesList.setSelectedIndex(0);
				noFire = false;
			}else if(e.getSource().equals(outputDataSeriesList)){
				noFire = true;
				int dindex = outputDataSeriesList.getSelectedIndex();
				if(dindex == -1){
					noFire = false;
					return;
				}
				selectedOutputDataSeries(dindex);
				noFire = false;
			}else if(e.getSource().equals(stateDataSeriesList)){
				noFire = true;
				int dindex = stateDataSeriesList.getSelectedIndex();
				if(dindex == -1){
					noFire = false;
					return;
				}
				selectedStateDataSeries(dindex);
				noFire = false;
			}
		}
	
	}				
	
	private void calculateRatings(boolean calculateModel1){
		int col = varNames.size();
		Vector outChecks = varClassifyTableModel.getOutputChecks();
		Vector maniChecks = varClassifyTableModel.getManiChecks();
		Vector stateChecks = varClassifyTableModel.getStateChecks();
		Vector exogChecks = varClassifyTableModel.getExogChecks();

		int outs = 0;
		int ins = 0;
		Vector inVars = new Vector(0,10);
		Vector outVars = new Vector(0,10);
		Vector delaysForRating = new Vector(0,10);
		// get variable classification
		if(calculateModel1){
			for(int i=0;i<col;i++){
				if(((JRadioButton)outChecks.elementAt(i)).isSelected()){
					String varName = (String)varNames.elementAt(i);
					Variable varObj = preprocessor.getVariableFromVariableName(varName);
					outVars.addElement(varObj);
					outs++;
				}else if(((JRadioButton)maniChecks.elementAt(i)).isSelected() ||
					((JRadioButton)stateChecks.elementAt(i)).isSelected() ||
					((JRadioButton)exogChecks.elementAt(i)).isSelected()  ){
					if(!varDelayCalculated1[i]){
						String varName = (String)varNames.elementAt(i);
						Variable varObj = preprocessor.getVariableFromVariableName(varName);
						inVars.addElement(varObj);
						delaysForRating.addElement(delays1.elementAt(i));
						ins++;
					}
				}
			}
		}else{
			for(int i=0;i<col;i++){
				if(((JRadioButton)stateChecks.elementAt(i)).isSelected()){
					String varName = (String)varNames.elementAt(i);
					Variable varObj = preprocessor.getVariableFromVariableName(varName);
					outVars.addElement(varObj);
					outs++;
				}else if(((JRadioButton)maniChecks.elementAt(i)).isSelected() ||
					((JRadioButton)exogChecks.elementAt(i)).isSelected()  ){
					if(!varDelayCalculated2[i]){
						String varName = (String)varNames.elementAt(i);
						Variable varObj = preprocessor.getVariableFromVariableName(varName);
						inVars.addElement(varObj);
						delaysForRating.addElement(delays2.elementAt(i));
						ins++;
					}
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
		
	private void arrangeDelays(boolean isModel1){
		if(isModel1){
			int col = delaysSettings1.size();
			for(int i=0;i<col;i++){
				delays1.setElementAt(convertDelays((long[])delaysSettings1.elementAt(i),
					delayIntervals1[i]),i);
			}
		}else{
			int col = delaysSettings2.size();
			for(int i=0;i<col;i++){
				delays2.setElementAt(convertDelays((long[])delaysSettings2.elementAt(i),
					delayIntervals2[i]),i);
			}
		}
	}

	private long[] convertDelays(long[] dset,long interval){
		long newInterv;
		if(interval <= 0){
			newInterv = dset[1]-dset[0]+1;
		}
		else newInterv = interval;
		int length = ((int)((dset[1]-dset[0])/newInterv))+1;

		long[] dls = new long[length];
		for(int p=0;p<length;p++){
			dls[p] = dset[0]+newInterv*p;
		}
		return dls;
	}

	@Override
	public void receiveRatingResults(Vector inVars, Vector delays, Vector outVars, Vector ratings) {

		int nr = ratings.size();
		if (nr == 0){
			frame.showOKDialog(frame.getNolResourceString(NOLFINITEDATA));
			return;
		}

		int col = varNames.size();
		Vector outChecks = varClassifyTableModel.getOutputChecks();
		boolean calculateModel1 = false;
		for(int i=0;i<col;i++){
			if(((JRadioButton)outChecks.elementAt(i)).isSelected()){
				String varName = (String)varNames.elementAt(i);
				Variable varObj = preprocessor.getVariableFromVariableName(varName);
				if(outVars.contains(varObj)){
					calculateModel1 = true;
					break;
				}
			}
		}		
		if(calculateModel1){
			int nv = inVars.size();
			for(int i=0;i<nv;i++){
				String n = inVars.elementAt(i).toString();
				int oldVarIndex = varNames.indexOf(n);

				if (DEBUG.debugFlag){
					System.out.println("varName="+n);
				}
				double[] rvalues = (double[])ratings.elementAt(i);
				varRatings1.setElementAt(rvalues,oldVarIndex);
				varDelayCalculated1[oldVarIndex] = true;
			}
			if(hasTimeStamps){
				autoSelectionTableModel1.setNames(model1VarNames,true);
				selectionSorter1.setModel(autoSelectionTableModel1);
			
			}else{
				autoSelectionNoDelayTableModel1.setNames(model1VarNames,true);
				selectionNoDelaySorter1.setModel(autoSelectionNoDelayTableModel1);
			}
			autoSelectionTableView1.validate();
			autoSelectionTableView1.repaint(0l); 
		}else{
			int nv = inVars.size();
			for(int i=0;i<nv;i++){
				String n = inVars.elementAt(i).toString();
				int oldVarIndex = varNames.indexOf(n);

				if (DEBUG.debugFlag){
					System.out.println("varName="+n);
				}
				double[] rvalues = (double[])ratings.elementAt(i);
				varRatings2.setElementAt(rvalues,oldVarIndex);
				varDelayCalculated2[oldVarIndex] = true;
			}
			if(hasTimeStamps){
				autoSelectionTableModel2.setNames(model2VarNames,false);
				selectionSorter2.setModel(autoSelectionTableModel2);
			}else{
				autoSelectionNoDelayTableModel2.setNames(model2VarNames,false);
				selectionNoDelaySorter2.setModel(autoSelectionNoDelayTableModel2);
			}
			autoSelectionTableView2.validate();
			autoSelectionTableView2.repaint(0l); 
		}
	}
	
	private boolean checkInputOutput(){
		Vector outChecks = varClassifyTableModel.getOutputChecks();
		Vector maniChecks = varClassifyTableModel.getManiChecks();
		int vc = varNames.size();
		boolean hasIn = false;
		boolean hasOut = false;
		for(int i=0;i<vc;i++){
			if(((JRadioButton)maniChecks.elementAt(i)).isSelected()){
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
		Vector maniChecks = varClassifyTableModel.getManiChecks();
		Vector stateChecks = varClassifyTableModel.getStateChecks();
		Vector exogChecks = varClassifyTableModel.getExogChecks();
		int vc = varNames.size();
		model1VarNames.removeAllElements();
		model2VarNames.removeAllElements();
		int sc = 0;
		for(int i=0;i<vc;i++){
			if(((JRadioButton)stateChecks.elementAt(i)).isSelected())
				sc++;
		}
		for(int i=0;i<vc;i++){
			if(((JRadioButton)maniChecks.elementAt(i)).isSelected()
				|| ((JRadioButton)stateChecks.elementAt(i)).isSelected()
				|| ((JRadioButton)exogChecks.elementAt(i)).isSelected()
				){
				model1VarNames.addElement(varNames.elementAt(i));
			}
			if(sc > 0){
				if(((JRadioButton)maniChecks.elementAt(i)).isSelected()
					|| ((JRadioButton)exogChecks.elementAt(i)).isSelected()
					){
					model2VarNames.addElement(varNames.elementAt(i));
				}
				varDelayCalculated2[i] = false;
				calculateDelay2.setEnabled(true);
			}
			varDelayCalculated1[i] = false;
			calculateDelay1.setEnabled(true);
		}
		delayTableModel1.setNames(model1VarNames,true);
		delayTableModel2.setNames(model2VarNames, false);
		if(hasTimeStamps){
			autoSelectionTableModel1.setNames(model1VarNames,true);
			autoSelectionTableModel2.setNames(model2VarNames,false);
			selectionSorter1.setModel(autoSelectionTableModel1);
			selectionSorter2.setModel(autoSelectionTableModel2);
		}else{
			autoSelectionNoDelayTableModel1.setNames(model1VarNames,true);
			autoSelectionNoDelayTableModel2.setNames(model2VarNames,false);
			selectionNoDelaySorter1.setModel(autoSelectionNoDelayTableModel1);
			selectionNoDelaySorter2.setModel(autoSelectionNoDelayTableModel2);
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
					if(check.isSelected()){
						if(table.equals(autoSelectionTableView1)){
//							autoSelectionTableModel1.refreshShiftChecks(row,column);
						}else if(table.equals(autoSelectionTableView2)){
//							autoSelectionTableModel2.refreshShiftChecks(row,column);
						}
					}		  				
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
		private Vector outputchecks;
		private Vector manichecks;
		private Vector statechecks;
		private Vector exogchecks;
		private Vector unusedchecks;
//		private String[] colHd = {"Variable","Output","Manipulate","State","Exogenous","Unused"};
		private String[] colHd = {
			frame.getNolResourceString(VARIABLE),
			frame.getNolResourceString(OUTPUT),
			frame.getNolResourceString(MANIPULATE),
			frame.getNolResourceString(STATE),
			frame.getNolResourceString(EXOGENOUS),
			frame.getNolResourceString(UNUSED)};
		public VarClassifyTableModel(){
			row = 0;
			col = 6;
			names = null;
			outputchecks = new Vector();
			manichecks = new Vector();
			statechecks = new Vector();
			exogchecks = new Vector();
			unusedchecks  = new Vector();
		}
		public void setNames(Vector names){
			this.names = names;
			row = names.size();
			outputchecks.removeAllElements();
			manichecks.removeAllElements();
			statechecks.removeAllElements();
			exogchecks.removeAllElements();
			unusedchecks.removeAllElements();
			ButtonGroup group;
			for(int r=0;r<row;r++){
				group = new ButtonGroup();
				JRadioButton check = new JRadioButton(){
					@Override
					public float getAlignmentY() { return 0.0f; }			
				};
				check.setBackground(Color.white);
				group.add(check);
				outputchecks.addElement(check);
				check = new JRadioButton(){
					@Override
					public float getAlignmentY() { return 0.0f; }			
				};
				check.setBackground(Color.white);
				group.add(check);
				check.setSelected(true);
				manichecks.addElement(check);
				check = new JRadioButton(){
					@Override
					public float getAlignmentY() { return 0.0f; }			
				};
				check.setBackground(Color.white);
				group.add(check);
				statechecks.addElement(check);
				check = new JRadioButton(){
					@Override
					public float getAlignmentY() { return 0.0f; }			
				};
				check.setBackground(Color.white);
				group.add(check);
				exogchecks.addElement(check);
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
				return manichecks.elementAt(r);
			}else if(c == 3){
				String name = (String)names.elementAt(r);
				if(namesForStates.contains(name)){
					return statechecks.elementAt(r);
				}else{
					JRadioButton check = (JRadioButton)statechecks.elementAt(r);
					check.setEnabled(false);
					return check;
				}
			}else if(c == 4){
				return exogchecks.elementAt(r);
			}else if(c == 5){
				return unusedchecks.elementAt(r);
			}
			return "";
		}
         
		@Override
		public String getColumnName(int c) {
			return colHd[c];
		}

		public Vector getOutputChecks(){
			return outputchecks;
		}
           
		public Vector getManiChecks(){
			return manichecks;
		}

		public Vector getStateChecks(){
			return statechecks;
		}

		public Vector getExogChecks(){
			return exogchecks;
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
		private boolean isModel1;
		private String[] colHd = {
			frame.getNolResourceString(VARIABLE),
			frame.getNolResourceString(MINTIMESHIFT),
			frame.getNolResourceString(MAXTIMESHIFT),
			frame.getNolResourceString(INTERVAL)};
//		private String[] colHd = {"Variable","Min Time Shift", "Max Time Shift","Interval"};

		public DelayTableModel(){
			row = 0;
			col = 4;
			names = null;
			isModel1 = true;
		}

		public void setNames(Vector names, boolean isModel1){
			this.names = names;
			this.isModel1 = isModel1;
			row = names.size();
		}
		@Override
		public int getColumnCount() { return col; }
		@Override
		public int getRowCount() { return row;}
		@Override
		public Object getValueAt(int r, int c){
			long divide1 = 60000;
			if(delayTimeSettingFlag1 == 1)
				divide1 = 3600000;
			else if(delayTimeSettingFlag1 == 3)
				divide1 = 1000;

			long divide2 = 60000;
			if(delayTimeSettingFlag2 == 1)
				divide2 = 3600000;
			else if(delayTimeSettingFlag2 == 3)
				divide2 = 1000;

			if(c == 0){
				return names.elementAt(r);
			}else if(c == 1){
				String n = (String)names.elementAt(r);
				int rr = varNames.indexOf(n);
				long[] dset = null;
				double val = 0;
				if(isModel1){
					dset = (long[])delaysSettings1.elementAt(rr);
					val = ((double)dset[0])/((double)divide1);
				}else{
					dset = (long[])delaysSettings2.elementAt(rr);
					val = ((double)dset[0])/((double)divide2);
				}
				return String.valueOf(val);
			}else if(c == 2){
				String n = (String)names.elementAt(r);
				int rr = varNames.indexOf(n);
				long[] dset = null;
				double val = 0;
				if(isModel1){
					dset = (long[])delaysSettings1.elementAt(rr);
					val = ((double)dset[1])/((double)divide1);
				}else{
					dset = (long[])delaysSettings2.elementAt(rr);
					val = ((double)dset[1])/((double)divide2);
				}
				return String.valueOf(val);
			}else if(c == 3){
				String n = (String)names.elementAt(r);
				int rr = varNames.indexOf(n);
				double val = 0;
				if(isModel1){
					val = ((double)delayIntervals1[rr])/((double)divide1);
				}else{
					val = ((double)delayIntervals2[rr])/((double)divide2);
				}
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
			long divide1 = 60000;
			if(delayTimeSettingFlag1 == 1)
				divide1 = 3600000;
			else if(delayTimeSettingFlag1 == 3)
				divide1 = 1000;

			long divide2 = 60000;
			if(delayTimeSettingFlag2 == 1)
				divide2 = 3600000;
			else if(delayTimeSettingFlag2 == 3)
				divide2 = 1000;

			if(isModel1)
				delayTableView1.requestFocus();
			else
				delayTableView2.requestFocus();
			try{
				long value = 0;
				if(isModel1)
					value = (long)((Double.valueOf((String)aValue).doubleValue())*divide1);
				else
					value = (long)((Double.valueOf((String)aValue).doubleValue())*divide2);

				String n = (String)names.elementAt(r);
				int rr = varNames.indexOf(n);
				if(c==1){
					long[] dset;
					if(isModel1)
						dset = (long[])delaysSettings1.elementAt(rr);
					else
						dset = (long[])delaysSettings2.elementAt(rr);
					if(value > dset[1]){
						dset[1] = value;
						dset[0] = value;
					}else{
						dset[0] = value;
						if(isModel1)
							delayIntervals1[rr] = divide1;
						else
							delayIntervals2[rr] = divide2;
					}
				}else if(c==2){
					long[] dset = null;
					if(isModel1)
						dset = (long[])delaysSettings1.elementAt(rr);
					else
						dset = (long[])delaysSettings2.elementAt(rr);
					if(value < dset[0]){
						dset[1] = dset[0];
					}else{
						dset[1] = value;
						if(isModel1)
							delayIntervals1[rr] = divide1;
						else
							delayIntervals2[rr] = divide2;
					}
				}else if(c==3){
					long[] dset = null;
					if(isModel1)
						dset = (long[])delaysSettings1.elementAt(rr);
					else
						dset = (long[])delaysSettings2.elementAt(rr);
					if(value > 0 ){ 
						if(value >(dset[1]-dset[0]))
							if(isModel1)
								delayIntervals1[rr] = (dset[1]-dset[0]);
							else
								delayIntervals2[rr] = (dset[1]-dset[0]);
						else
							if(isModel1)
								delayIntervals1[rr] = value;
							else
								delayIntervals2[rr] = value;
					}
				}
				arrangeDelays(isModel1);
				if(isModel1){
					varDelayCalculated1[rr] = false;
					calculateDelay1.setEnabled(true);
				}else{
					varDelayCalculated2[rr] = false;
					calculateDelay2.setEnabled(true);
				}
			}catch(NumberFormatException evt){
				System.err.println("Non-Fatal exception: " + evt.getMessage());
				evt.printStackTrace();
			}
			if(isModel1){
				if(hasTimeStamps){
					autoSelectionTableModel1.setNames(model1VarNames,true);
					selectionSorter1.setModel(autoSelectionTableModel1);
				}else{
					autoSelectionNoDelayTableModel1.setNames(model1VarNames,true);
					selectionNoDelaySorter2.setModel(autoSelectionNoDelayTableModel2);
				}
				delayTableView1.validate();
				delayTableView1.repaint(0l);
			}else{
				if(hasTimeStamps){
					autoSelectionTableModel2.setNames(model2VarNames,false);
					selectionSorter2.setModel(autoSelectionTableModel2);
				}else{
					autoSelectionNoDelayTableModel2.setNames(model2VarNames,false);
					selectionNoDelaySorter2.setModel(autoSelectionNoDelayTableModel2);
				}
				delayTableView2.validate();
				delayTableView2.repaint(0l);
			}
		}
	}

	class AutoSelectionTableModel extends AbstractTableModel{
		private int row,col;
		private int digits = 5;
		private boolean isModel1;
		private Vector names;
		private Vector nameswithdelay;
		private Vector delayValues;
		private Vector ratings;
		private Vector usedchecks;
		private String[] colHd = {
			frame.getNolResourceString(VARIABLE),
			frame.getNolResourceString(TIMESHIFT),
			frame.getNolResourceString(RATING),
			frame.getNolResourceString(USED)};
//		private String[] colHd = {"Variable","Time Shift","Rating", "Used"};

		public AutoSelectionTableModel(){
			row = 0;
			col = 4;
			isModel1 = true;
			names = new Vector();
			nameswithdelay = new Vector();
			delayValues = new Vector();
			ratings = new Vector();
			usedchecks = new Vector();
		}

		public void setNames(Vector names, boolean isModel1){
			this.names = names;
			this.isModel1 = isModel1;
			int nc = names.size();
			nameswithdelay.removeAllElements();
			delayValues.removeAllElements();
			ratings.removeAllElements();
			usedchecks.removeAllElements();

			long divide1 = 60000;
			if(delayTimeSettingFlag1 == 1)
				divide1 = 3600000;
			else if(delayTimeSettingFlag1 == 3)
				divide1 = 1000;

			long divide2 = 60000;
			if(delayTimeSettingFlag2 == 1)
				divide2 = 3600000;
			else if(delayTimeSettingFlag2 == 3)
				divide2 = 1000;

			if(isModel1){
				for(int i=0;i<nc;i++){
					String n = (String)names.elementAt(i);
					int rr = varNames.indexOf(n);
					long[] dls = (long[])delays1.elementAt(rr);
					double[] rates = (double[])varRatings1.elementAt(rr);
					for(int j=0;j<dls.length;j++){
						nameswithdelay.addElement(n);
						double val = ((double)dls[j])/((double)divide1);
						delayValues.addElement(String.valueOf(val));
						if(!varDelayCalculated1[rr]){
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
			}else{
 				for(int i=0;i<nc;i++){
					String n = (String)names.elementAt(i);
					int rr = varNames.indexOf(n);
					long[] dls = (long[])delays2.elementAt(rr);
					double[] rates = (double[])varRatings2.elementAt(rr);
					for(int j=0;j<dls.length;j++){
						nameswithdelay.addElement(n);
						double val = ((double)dls[j])/((double)divide2);
						delayValues.addElement(String.valueOf(val));
						if(!varDelayCalculated2[rr]){
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
		if(DEBUG.debugFlag){
			System.out.println("Setnames row="+row);
		}
			goThrouthThreshold();
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
     
		public void refreshShiftChecks(int rr,int cc){
			if(cc != 3){
				return;
			}
			String oldn = (String)nameswithdelay.elementAt(rr);
			for(int r=0;r<row;r++){
				String n = (String)nameswithdelay.elementAt(r);
				JCheckBox check =  (JCheckBox)usedchecks.elementAt(r);
				if(r != rr){
					if(n.equals(oldn)){
						if(check.isSelected()){
							check.setSelected(false);
						}
					}
				}
			}
		}

		public void goThrouthThreshold(){
			double thresholdValue = ratingThresholdValue2;
			if(isModel1)
				thresholdValue = ratingThresholdValue1;
			if(row == 0){
				return;
			}
			String n0 = "";
			String n1 = "";
			boolean unchecked = true;
			double varThresh = thresholdValue; 
			Vector sameNameChecks = new Vector();

			for(int r=0;r<row;r++){
				JCheckBox check =  (JCheckBox)usedchecks.elementAt(r);
				check.setSelected(false);
			}
			
			for(int r=0;r<row;r++){
				String rateStr = (String)ratings.elementAt(r);
				n1 = (String)nameswithdelay.elementAt(r);
				JCheckBox check =  (JCheckBox)usedchecks.elementAt(r);
				if(!n1.equals(n0)){
					varThresh = thresholdValue;
					sameNameChecks.removeAllElements();
					try{
						double c = Double.valueOf(rateStr).doubleValue();
						if(c>=varThresh){
							check.setSelected(true);
							varThresh = c;
						}else{
							check.setSelected(false);
						}
					}catch(NumberFormatException  evt){
						check.setSelected(false);
					}
					sameNameChecks.addElement(check);
					n0 = n1;
				}else{
					try{
						double c = Double.valueOf(rateStr).doubleValue();
						if(c>=varThresh){
							check.setSelected(true);
							for(int i=0;i<sameNameChecks.size();i++){
								((JCheckBox)sameNameChecks.elementAt(i)).setSelected(false);
							}
							varThresh = c;
						}else{
							check.setSelected(false);
						}
					}catch(NumberFormatException  evt){
						check.setSelected(false);
					}
					sameNameChecks.addElement(check);
				}
			}
		}
	/* Following code if for verion beta 1.0*/
	/* end */
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
			System.out.println("value="+ aValue);
		}
	}


	class AutoSelectionNoDelayTableModel extends AbstractTableModel{
		private int row,col;
		private int digits = 5;
		private Vector names;
		private Vector ratings;
		private Vector usedchecks;
		private boolean isModel1;
		private String[] colHd = {
			frame.getNolResourceString(VARIABLE),
			frame.getNolResourceString(RATING),
			frame.getNolResourceString(USED)};
//		private String[] colHd = {"Variable","Rating", "Used"};

		public AutoSelectionNoDelayTableModel(){
			row = 0;
			col = 3;
			isModel1 = true;
			names = new Vector();
			ratings = new Vector();
			usedchecks = new Vector();
		}

		public void setNames(Vector names, boolean isModel1){
			this.names = names;
			this.isModel1 = isModel1;
			int nc = names.size();
			ratings.removeAllElements();
			usedchecks.removeAllElements();

			if(isModel1){
				for(int i=0;i<nc;i++){
					String n = (String)names.elementAt(i);
					int rr = varNames.indexOf(n);
					double[] rates = (double[])varRatings1.elementAt(rr);
					if(!varDelayCalculated1[rr]){
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
			}else{
				for(int i=0;i<nc;i++){
					String n = (String)names.elementAt(i);
					int rr = varNames.indexOf(n);
					double[] rates = (double[])varRatings2.elementAt(rr);
					if(!varDelayCalculated2[rr]){
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
			}
			row = names.size();				
			goThrouthThreshold();
		}

		public void goThrouthThreshold(){
			double thresholdValue = ratingThresholdValue2;
			if(isModel1)
				thresholdValue = ratingThresholdValue1;
			for(int r=0;r<row;r++){
				String rateStr = (String)ratings.elementAt(r);
				JCheckBox check =  (JCheckBox)usedchecks.elementAt(r);
 				if(rateStr.equals("")){
					check.setSelected(true);
				}else{
					try{
						double c = Double.valueOf(rateStr).doubleValue();
						if(c>=thresholdValue)
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
		Vector outChecks = varClassifyTableModel.getOutputChecks();
		Vector maniChecks = varClassifyTableModel.getManiChecks();
		Vector stateChecks = varClassifyTableModel.getStateChecks();
		Vector exogChecks = varClassifyTableModel.getExogChecks();
		
		Vector ins = new Vector();
		Vector outs = new Vector();
		Vector states = new Vector();
		Vector stateinputs = new Vector();
		Vector manis = new Vector();
		Vector exogs = new Vector();

		Vector outDelays = new Vector();
		Vector inDelays = new Vector();
		Vector stateDelays = new Vector();
		Vector stateinputDelays = new Vector();

		int inputCols1 = 0;
		int inputCols2 = 0;
		int nout1 = 0;
		int nout2 = 0;
		Vector model1DelayValues = new Vector();
		Vector model2DelayValues = new Vector();
		readDelaysFromAutoSelectChecks(model1DelayValues,model2DelayValues);		

		for(int i=0;i<c;i++){
			if(((JRadioButton)outChecks.elementAt(i)).isSelected()){
				long[] dls = (long[])model1DelayValues.elementAt(i);
				outDelays.addElement(dls);
				outs.addElement(varNames.elementAt(i));
				nout1++;
			}else if(((JRadioButton)stateChecks.elementAt(i)).isSelected()||
				((JRadioButton)maniChecks.elementAt(i)).isSelected()||
				((JRadioButton)exogChecks.elementAt(i)).isSelected() ){

				long[] dls = (long[])model1DelayValues.elementAt(i);
				if(dls.length > 0){
					inDelays.addElement(dls);
					ins.addElement(varNames.elementAt(i));
				}
				inputCols1 = inputCols1+dls.length;
			}
				

			if(((JRadioButton)stateChecks.elementAt(i)).isSelected()){
				long[] dls = (long[])model2DelayValues.elementAt(i);
				stateDelays.addElement(dls);
				states.addElement(varNames.elementAt(i));
				nout2++;
			}else if(((JRadioButton)maniChecks.elementAt(i)).isSelected() ||
				((JRadioButton)exogChecks.elementAt(i)).isSelected()){
				long[] dls = (long[])model2DelayValues.elementAt(i);
				if(dls.length > 0){
					stateinputDelays.addElement(dls);
					stateinputs.addElement(varNames.elementAt(i));
				}
				inputCols2 = inputCols2+dls.length;
			}
		}

		if(nout1 == 0){
			frame.showOKDialog(frame.getNolResourceString(NOOUTPUTISSPECIFIED));
//			frame.showOKDialog("No output is specified.");
			return false;
		}
		if(inputCols1 == 0){
			frame.showOKDialog(frame.getNolResourceString(NOINPUTISSPECIFIED));
//			frame.showOKDialog("No input is specified.");
			return false;
		}
		EnsembleModel outputensemble = new EnsembleModel(new ArchitectureParameters(inputCols1,nout1,0,0));
		boolean oneM = true;
		if(nout2 != 0 ){
			if(inputCols2 == 0){
				frame.showOKDialog(frame.getNolResourceString(NOINPUTFORSTATEMODEL));
//				frame.showOKDialog("No input for state model.");
				return false;
			}
			for(int t=0;t<states.size();t++){
				if(ins.contains(states.elementAt(t))){
					oneM = false;
					break;
				}
			}
		}

		for(int i=0;i<c;i++){
			if(((JRadioButton)maniChecks.elementAt(i)).isSelected()){
				long[] dls1 = (long[])model1DelayValues.elementAt(i);
				long[] dls2 = (long[])model2DelayValues.elementAt(i);
				if(oneM){
					if(dls1.length > 0){
						manis.addElement(varNames.elementAt(i));
					}
				}else{
					if(dls1.length > 0 || dls2.length > 0 ){
						manis.addElement(varNames.elementAt(i));
					}
				}
			}
			if(((JRadioButton)exogChecks.elementAt(i)).isSelected()){
				long[] dls1 = (long[])model1DelayValues.elementAt(i);
				long[] dls2 = (long[])model2DelayValues.elementAt(i);
				if(oneM){
					if(dls1.length > 0){
						exogs.addElement(varNames.elementAt(i));
					}
				}else{
					if(dls1.length > 0 || dls2.length > 0 ){
						exogs.addElement(varNames.elementAt(i));
					}
				}
			}
		}
		if(oneM){
			model = new NolOptimizeModel(outputensemble,modelName.getText(), 
				outs, ins, manis,exogs,outDelays,inDelays,preprocessor) ;		
		}else{
			EnsembleModel stateensemble = new EnsembleModel(new ArchitectureParameters(inputCols2,nout2,0,0));
			model = new NolOptimizeModel(outputensemble, stateensemble, modelName.getText(), 
				outs, ins, states, stateinputs,manis,exogs,outDelays,inDelays,
				stateDelays,stateinputDelays,preprocessor);		
		}
		String comment = modelDescript.getText();
		model.setDelayTimeUnit(delayTimeSettingFlag1);
		model.setHasTimeStamps(hasTimeStamps);
		if(comment != null)
			model.setComment(comment);
		return true;
	}

	public void readDelaysFromAutoSelectChecks(Vector model1DelayValues,Vector model2DelayValues){
		model1DelayValues.removeAllElements();
		model2DelayValues.removeAllElements();


		if(hasTimeStamps){
			for(int i=0;i<delays1.size();i++){
				long[] dls1 = (long[])delays1.elementAt(i);
				long[] newdls1 = new long[dls1.length];
				model1DelayValues.addElement(newdls1);
			}
			for(int i=0;i<delays2.size();i++){
				long[] dls2 = (long[])delays2.elementAt(i);
				long[] newdls2 = new long[dls2.length];
				model2DelayValues.addElement(newdls2);
			}
			Vector usedChecks1 = autoSelectionTableModel1.getUsedChecks();
			Vector namewithdelays1 = autoSelectionTableModel1.getNamesWithDelay();
			String n = (String)namewithdelays1.elementAt(0);
			int rold = varNames.indexOf(n);
			int c=0;
			for(int i=0;i<namewithdelays1.size();i++){
				n = (String)namewithdelays1.elementAt(i);
				int rr = varNames.indexOf(n);
				long[] newdls = (long[])model1DelayValues.elementAt(rr);
				long[] dls = (long[])delays1.elementAt(rr);
				if(rr == rold){
					if(((JCheckBox)usedChecks1.elementAt(i)).isSelected()){ 
						newdls[c] = dls[c];
					}else{
						newdls[c] = -1;
					}
					c++;
				}else{
					c = 0;
					if(((JCheckBox)usedChecks1.elementAt(i)).isSelected()){ 
						newdls[c] = dls[c];
					}else{
						newdls[c] = -1;
					}
					c++;
					rold = rr;
				}
			}
			for(int i=0;i<model1DelayValues.size();i++){
				long[] newdls = (long[])model1DelayValues.elementAt(i);
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
					model1DelayValues.setElementAt(ndls,i);
				}else{
					model1DelayValues.setElementAt(new long[0],i);
				}

			}
			Vector usedChecks2 = autoSelectionTableModel2.getUsedChecks();
			Vector namewithdelays2 = autoSelectionTableModel2.getNamesWithDelay();
			if(!namewithdelays2.isEmpty()){
				n = (String)namewithdelays2.elementAt(0);
				rold = varNames.indexOf(n);
				c = 0;
				for(int i=0;i<namewithdelays2.size();i++){
					n = (String)namewithdelays2.elementAt(i);
					int rr = varNames.indexOf(n);
					long[] newdls = (long[])model2DelayValues.elementAt(rr);
					long[] dls = (long[])delays2.elementAt(rr);
					if(rr == rold){
						if(((JCheckBox)usedChecks2.elementAt(i)).isSelected()){ 
							newdls[c] = dls[c];
						}else{
							newdls[c] = -1;
						}
						c++;
					}else{
						c = 0;
						if(((JCheckBox)usedChecks2.elementAt(i)).isSelected()){ 
							newdls[c] = dls[c];
						}else{
							newdls[c] = -1;
						}
						c++;
						rold = rr;
					}
				}
				for(int i=0;i<model2DelayValues.size();i++){
					long[] newdls = (long[])model2DelayValues.elementAt(i);
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
						model2DelayValues.setElementAt(ndls,i);
					}else{
						model2DelayValues.setElementAt(new long[0],i);
					}
				}
			}
		}else{
			for(int i=0;i<delays1.size();i++){
				model1DelayValues.addElement(new long[0]);
			}
			for(int i=0;i<delays2.size();i++){
				model2DelayValues.addElement(new long[0]);
			}
			Vector usedChecks1 = autoSelectionNoDelayTableModel1.getUsedChecks();
			Vector names1 = autoSelectionNoDelayTableModel1.getNames();
			for(int i=0;i<usedChecks1.size();i++){
				String n = (String)names1.elementAt(i);
				int rr = varNames.indexOf(n);
				if(((JCheckBox)usedChecks1.elementAt(i)).isSelected()){ 
					model1DelayValues.setElementAt(new long[1],rr);
				}else{
					model1DelayValues.setElementAt(new long[0],rr);
				}
			}
			Vector usedChecks2 = autoSelectionNoDelayTableModel2.getUsedChecks();
			Vector names2 = autoSelectionNoDelayTableModel2.getNames();
			for(int i=0;i<usedChecks2.size();i++){
				String n = (String)names2.elementAt(i);
				int rr = varNames.indexOf(n);
				if(((JCheckBox)usedChecks2.elementAt(i)).isSelected()){ 
					model2DelayValues.setElementAt(new long[1],rr);
				}else{
					model2DelayValues.setElementAt(new long[0],rr);
				}
			}
		}
	}
	
	public boolean verifyConvertDelayFromTimeUnits1() {
		return delayIntervals1[0] == 0;
	}
	
	public boolean verifyConvertDelayFromTimeUnits2() {
		return delayIntervals2[0] == 0;
	}
}
