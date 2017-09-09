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

import com.gensym.math.datafit.*;
import com.gensym.math.matrix.*;

import com.gensym.nols.data.*;
import com.gensym.nols.main.*;
import com.gensym.nols.util.*;

import com.gensym.DEBUG;

public class NolNewAnnModelWizard  extends NolWizardDialog{

	private	JTextField modelName;
	private	JTextField caseName;
	private	JTextField dataSeriesName;
	private	JTextField numberField;
	private JTextArea modelDescript;
	private JList caseList;
	private JList dataSeriesList;
	private DefaultListModel caseListModel;
	private DefaultListModel dataSeriesListModel;

	private LoadFromExistModelDialog loadFromExistModelDialog;
	private ControlAction actionListener;

	private	VarClassifyTableModel varClassifyTableModel;
	private	JTable varClassifyTableView;

	private	StructTableModel structTableModel;
	private	JTable structTableView;

	private TableSorter selectionSorter;

	private JLabel numOfVariable;
	private JLabel numOfSample;
	private boolean noFire;

	private JRadioButton grossCheck;
	private JRadioButton noiseCheck;

	private NolMainFrame frame;	 


	// parameters for modeling.

	private Preprocessor preprocessor;
	private DataSeries dataSeries;
	private NolAnnModel model;
	private Vector varNames;
	private Vector namesForOutputs;
	private Vector usedVarNames;
	private Vector outVarNames;

	private static final String GENERAL_LABEL = "NewAnnModelWizard_GeneralLabel";
	private static final String COMMENT_LABEL = "CommentLabel";
	private static final String NAMEEDITLABEL = "NewAnnModelWizard_NameEditLabel";
	private static final String PREPROCESSOR_LABEL = "NewAnnModelWizard_PreprocessorLabel";
	private static final String PREPROCESSOR = "NewAnnModelWizard_Preprocessor";
	private static final String DATASOURCE_LABEL = "NewAnnModelWizard_OutputDataSourceLabel";
	private static final String DATASERIES = "NewAnnModelWizard_DataSeries";
	private static final String VARIABLE = "NewAnnModelWizard_Variable";
	private static final String SAMPLE = "NewAnnModelWizard_Sample";
	private static final String CLASSIFICATION_LABEL = "NewAnnModelWizard_ClassificationLabel";
	private static final String NODELAY_LABEL = "NewAnnModelWizard_NoDelayLabel";
	private static final String DELAY_LABEL = "NewAnnModelWizard_DelayLabel";
	private static final String HOUR = "NewAnnModelWizard_Hour";
	private static final String MINUTE = "NewAnnModelWizard_Minute";
	private static final String SECOND = "NewAnnModelWizard_Second";
	private static final String DELAYS = "NewAnnModelWizard_Delays";
	private static final String SETTING_LABEL = "NewAnnModelWizard_SettingLabel";
	private static final String SETTING_BORDER = "NewAnnModelWizard_SettingBorder";
	private static final String THRESHOLD = "NewAnnModelWizard_Threshold";
	private static final String CALCULATERATINGS = "NewAnnModelWizard_CalculateRatings";
	private static final String STRUCTURE_LABEL = "NewAnnModelWizard_StructureLabel";
	private static final String OUTPUT = "NewAnnModelWizard_Output";
	private static final String INPUT = "NewAnnModelWizard_Input";
	private static final String UNUSED = "NewAnnModelWizard_Unused";
	private static final String MINDELAY = "NewAnnModelWizard_MinDelay";
	private static final String MAXDELAY = "NewAnnModelWizard_MaxDelay";
	private static final String INTERVAL = "NewAnnModelWizard_Interval";
	private static final String DELAY = "NewAnnModelWizard_Delay";
	private static final String RATING = "NewAnnModelWizard_Rating";
	private static final String USED = "NewAnnModelWizard_Used";
	private static final String NOOUTPUTISSPECIFIED = "NewAnnModelWizard_NoOutputIsSpecified";
	private static final String NOINPUTISSPECIFIED = "NewAnnModelWizard_NoInputIsSpecified";
	private static final String NOLFINITEDATA = "NewAnnModelWizard_NoFiniteData";
	private static final String THRESHOLDTOOLTIP = "NewAnnModelWizard_ThresholdToolTip";
	private static final String LOADFROMEXISTMODEL = "NewAnnModelWizard_LoadFromModel";
	private static final String LOADFROMDISK = "NewAnnModelWizard_LoadFromDisk";
	private static final String PREDICTIVEMODEL = "NewAnnModelWizard_PredictiveModel";
	private static final String NOMODELSELECTED = "NewAnnModelWizard_NoModelSelected";
	private static final String NONAMEFORTHISMODEL = "NewAnnModelWizard_NoNameForThisModel";
	private static final String LAYERNUMBER = "NewAnnModelWizard_LayerNumber";
	private static final String WRONGLAYERNUMBER = "NewAnnModelWizard_WrongLayerNumber";
	private static final String WRONGSTRUCTURE = "NewAnnModelWizard_WrongStructure";

    private static final String OK_BUTTON_LABEL = "OkButtonLabel";
    private static final String CANCEL_BUTTON_LABEL = "CancelButtonLabel";

	private int oldLayerNumber;

	public NolNewAnnModelWizard (NolMainFrame dw) {
		super((JFrame)dw, "Create New Back Propagation Model", true, 5);
		frame = (NolMainFrame)dw;
		actionListener = new ControlAction();
		varNames = new Vector();
		namesForOutputs = new Vector();
		usedVarNames= new Vector();
		outVarNames = new Vector();
		initializeLayout();
		initDataDisplay();
		oldLayerNumber = 5;
	}

	private void initializeLayout(){

		stepPanes.setElementAt(getGeneralPanel(),0);
		stepPanes.setElementAt(getCasePanel(),1);
		stepPanes.setElementAt(getDataSourcePanel(),2);
		stepPanes.setElementAt(getClassificationPanel(),3);
		stepPanes.setElementAt(getStructurePane(),4);
	}

	private JPanel getGeneralPanel(){
		JPanel genPane = new JPanel(new BorderLayout());
		URL url = this.getClass().getResource("largeann.gif");
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
		caseName = new JTextField();
		caseName.setEditable(false);
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
		JTextArea infoLabel = new JTextArea(s);
		infoLabel.setEditable(false);
		infoLabel.setLineWrap(true);
		infoLabel.setWrapStyleWord(true);
		infoLabel.setBackground(infoPane.getBackground());
		infoPane.add(infoLabel);
		classPane.add("North",infoPane);
 	

		JPanel cenPane = new JPanel(new BorderLayout());
		JPanel modePane = new JPanel(new GridLayout(1,3,5,5));
		modePane.add(new JLabel("Run Mode:"));
		ButtonGroup group = new ButtonGroup();
		noiseCheck = new JRadioButton("Filter Noise Only");
		grossCheck = new JRadioButton("Correct Gross Errors");
		noiseCheck.setSelected(true);
		noiseCheck.setActionCommand("Filter Noise Only");
		noiseCheck.addActionListener(actionListener);
		grossCheck.setActionCommand("Correct Gross Errors");
		grossCheck.addActionListener(actionListener);
		group.add(noiseCheck);
		group.add(grossCheck);
		modePane.add(noiseCheck);
		modePane.add(grossCheck);
		
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
		cenPane.add("North",modePane);
		cenPane.add("Center",varPane);

		classPane.add("Center",cenPane);

		return classPane;
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

		JPanel cenPane = new JPanel(new GridLayout());
 		cenPane.setBorder(new EmptyBorder(10,10,10,10));
 		JPanel autoPane = new JPanel(new BorderLayout());

		structTableModel = new StructTableModel();

		structTableView = new JTable(structTableModel);
		structTableView.setDefaultRenderer(AbstractButton.class, 
			new AutoSelectRenderer());

		structTableView.setSelectionMode(0);
		structTableView.setSelectionBackground(Color.white);
		structTableView.setCellSelectionEnabled(true);
		structTableView.setSelectionForeground(Color.black);
		JScrollPane listScrollPane = new JScrollPane(structTableView);
		listScrollPane.setBackground(Color.white);

		
		JPanel actPane = new JPanel(new GridLayout(1,2,10,10));
		actPane.add(new JLabel(frame.getNolResourceString(LAYERNUMBER)+":", SwingConstants.CENTER));
 		numberField = new JTextField();
		numberField.setText("5");
		numberField.setToolTipText(frame.getNolResourceString(THRESHOLDTOOLTIP));
		numberField.addActionListener(actionListener);
		actPane.add(numberField);
		
		autoPane.add("Center",listScrollPane);
		autoPane.add("North",actPane);

		cenPane.add(autoPane);

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
		String title = "Create New Autoassociative Model - "+setTitleForStep(currentStep);
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
		String title = "Create New Autoassociative Model - "+setTitleForStep(currentStep);
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
			if(!resetStructTableModelParameter()){
				super.modifyStep(false);
			}
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
		noFire = false;
	}

	public NolAnnModel getModel(){
		if(model == null){
			return null;
		}
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
		dataSeriesList.validate();
		dataSeriesList.repaint(0l);

		Vector vpNames = preprocessor.getVariableNames();
		varNames.removeAllElements();
		usedVarNames.removeAllElements();
		outVarNames.removeAllElements();
		
		for(int i=0;i<vpNames.size();i++){
			String name = vpNames.elementAt(i).toString();
			Variable varObj = preprocessor.getVariableFromVariableName(name);
			double std = varObj.getSTD();
			if(std>0){
				varNames.addElement(name);
				usedVarNames.addElement(name);
			}
		}
		varClassifyTableModel.setNames(varNames);
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
		Vector models = frame.getProject().getAnnModels();
		getLoadFromExistModelDialog().setContent(models);
		getLoadFromExistModelDialog().setBounds(200,200,300,200);
		getLoadFromExistModelDialog().setVisible(true);
		if(getLoadFromExistModelDialog().isOk()){
			int index = getLoadFromExistModelDialog().getSelectedIndex();
			if(index >=0){
				NolAnnModel existModel = (NolAnnModel)models.elementAt(index);
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
		}catch (Exception evt) { 
			System.out.println(evt); 
		}
	}
	
	private boolean updateParameterFromExistingParameter(NolModelParameter modelPara){

		int pindex = frame.getProject().getPreprocessorIndexByName(modelPara.preprocessorName);
		if(pindex == -1){
			return false;
		}
		selectedPreprocessor(pindex);
		Vector outs = modelPara.outputs;
		modelDescript.setText(modelPara.comment);
		if(outs.isEmpty())
			return false;
		String outVarName = outs.elementAt(0).toString();
		int dindex = preprocessor.getDataSeriesIndex(preprocessor.getDataSeriesFromVariableName(outVarName).getName());
		selectedDataSeries(dindex);
		Vector usedchecks = varClassifyTableModel.getUsedChecks();
		for(int i=0;i<usedchecks.size();i++){
			JCheckBox radio = (JCheckBox)usedchecks.elementAt(i);
			radio.setSelected(false);
		}
		for(int i=0;i<outs.size();i++){
			String varName = (String)outs.elementAt(i);
			int vindex = varNames.indexOf(varName);
			JCheckBox radio = (JCheckBox)usedchecks.elementAt(vindex);
			radio.setSelected(true);
		}
		if(checkInputOutput()){
			finishButton.setEnabled(true);
		}else{		
			finishButton.setEnabled(false);
		}
		return true;
	}

	private boolean updateParameterFromExistingModel(NolAnnModel existModel){
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
		Vector usedchecks = varClassifyTableModel.getUsedChecks();
		for(int i=0;i<usedchecks.size();i++){
			JCheckBox radio = (JCheckBox)usedchecks.elementAt(i);
			radio.setSelected(false);
		}
		for(int i=0;i<outs.size();i++){
			String varName = (String)outs.elementAt(i);
			int vindex = varNames.indexOf(varName);
			JCheckBox radio = (JCheckBox)usedchecks.elementAt(vindex);
			radio.setSelected(true);
		}
		if(checkInputOutput()){
			finishButton.setEnabled(true);
		}else{		
			finishButton.setEnabled(false);
		}
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
			if(command.equals("loadFromModel")){
				loadParaFromExistModel();
  			}else if(command.equals("Filter Noise Only")){
				varClassifyTableModel.setColumn(2);
				varClassifyTableView.repaint(0L);
				varClassifyTableView.validate();
  			}else if(command.equals("Correct Gross Errors")){
//System.out.println("Correct Gross Errors");
				varClassifyTableModel.setColumn(3);
				varClassifyTableView.repaint(0L);
				varClassifyTableView.validate();
			}else if(command.equals("loadFromDisk")){
				loadParaFromFile();
			}else if(e.getSource().equals(modelName)){
				if(modelName.getText().equals("")){
					frame.showOKDialog(frame.getNolResourceString(NONAMEFORTHISMODEL));
				}
			}else if(e.getSource().equals(numberField)){
				int nlayers = Integer.valueOf(numberField.getText()).intValue();
				if(nlayers <3 || nlayers > 5) {
					frame.showOKDialog(frame.getNolResourceString(WRONGLAYERNUMBER));
					numberField.setText(""+oldLayerNumber);
					return;
				}
				oldLayerNumber = nlayers;
				structTableModel.setNumberOfNodes(nlayers);
				Dimension  dim = getSize();
				setSize(dim.width+10,dim.height+10);
				validate();
				repaint(0l);
				setSize(dim);
				validate();
				repaint(0l);
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
	
	
	private boolean checkInputOutput(){
		Vector usedChecks = varClassifyTableModel.getUsedChecks();
		int vc = varNames.size();
		boolean hasOut = false;
		for(int i=0;i<vc;i++){
			if(((JCheckBox)usedChecks.elementAt(i)).isSelected()){
				hasOut = true;
			}
		}
		if(hasOut){
			return true;
		}else{
			return false;
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
		private Vector usedchecks;
		private double[] noiseStd;
		private String[] colHd = {"Variable","Used","Noise STD"};
		public VarClassifyTableModel(){
			row = 0;
			col = 2;
			names = null;
			usedchecks = new Vector();
			noiseStd = new double[0];
		}
		public void setNames(Vector names){
			this.names = names;
			row = names.size();
			noiseStd = new double[row];
			usedchecks.removeAllElements();
			for(int r=0;r<row;r++){
				JCheckBox check = new JCheckBox(){
					@Override
					public float getAlignmentY() { return 0.0f; }			
				};
				check.setSelected(true);
				check.setBackground(Color.white);
				usedchecks.addElement(check);
				noiseStd[r] = 1.0;
			}
		}

		public void setColumn(int col){
			this.col = col;
			fireTableChanged(new TableModelEvent(this,TableModelEvent.HEADER_ROW));
//System.out.println("col="+col);
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
				return usedchecks.elementAt(r);
			}else if(c == 2){
				return String.valueOf(noiseStd[r]);
			}
			return "";
		}
         
		@Override
		public String getColumnName(int c) {
			return colHd[c];
		}

		public Vector getUsedChecks(){
			return usedchecks;
		}
           
		@Override
		public Class getColumnClass(int c) {
			return getValueAt(0, c).getClass();
		}

		@Override
		public boolean isCellEditable(int r, int c) {
			if(c==2){
				return true;
			}
			return false;
		}
		
		public double[] getNoiseStd(){
			return noiseStd;
		}

		@Override
		public void setValueAt(Object aValue, int r, int c) {
			if(c==2){
				try{
					noiseStd[r] = Double.valueOf((String)aValue).doubleValue();
				}catch(NumberFormatException evt){
					noiseStd[r] = 1.0;
				}
			}
		}
	}

 	class StructTableModel extends AbstractTableModel{
		private int row,col;
		private int digits = 5;
		private int[] nodes;
		private Vector linearchecks;
		private Vector sigmoidchecks;
		private String[] colHd = {"Layer", "Nodes", "Linear","Sigmoid"};

		public StructTableModel(){
			row = 5;
			col = 4;
			nodes =  new int[5];
			linearchecks = new Vector();
			sigmoidchecks = new Vector();  
			setParameter(2,2);
		}

		public void setParameter(int nout, int nin){
			linearchecks.removeAllElements();
			sigmoidchecks.removeAllElements();
			nodes[0] = nin;
			for(int i=1;i<row-1;i++){
				nodes[i] = (nin+nout)/2;
			}
			nodes[row-1] = nout;
			nodes[(row/2)] = 1;


			for(int i=0;i<row;i++){
				ButtonGroup group = new  ButtonGroup();
				JRadioButton linear = new JRadioButton(){
					@Override
					public float getAlignmentY() { return 0.0f; }			
				};
				linear.setBackground(Color.white);
				group.add(linear);
				JRadioButton sigmoid = new JRadioButton(){
					@Override
					public float getAlignmentY() { return 0.0f; }			
				};
				group.add(sigmoid);
				sigmoid.setBackground(Color.white);
				if(i == 0 || i == row-1 || i == row/2){
					linear.setSelected(true);
				}
				else sigmoid.setSelected(true);

				linearchecks.addElement(linear);
				sigmoidchecks.addElement(sigmoid);
			}
		}

		public void setNumberOfNodes(int nn){
			int nout = nodes[row-1];
			int nin = nodes[0];
			row = nn;
			nodes =  new int[nn];
			setParameter(nout,nin);
		}

		@Override
		public int getColumnCount() { return col; }
		@Override
		public int getRowCount() { return row;}
		@Override
		public Object getValueAt(int r, int c){
			if(c == 0){
				return String.valueOf(r+1);
			}else if(c == 1){
				return String.valueOf(nodes[r]);
			}else if(c == 2){
				return linearchecks.elementAt(r);
			}else if(c == 3){
				return sigmoidchecks.elementAt(r);
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
			if(c == 0){
				return false;
			}
			if(r == 0 ){
				return false;
			}
			if(r == row-1 ){
				return false;
			}
			if(c == 1){
				return true;
			}
			return false;
		}

		public int[] getTransferFunctions(){
			int[] tf = new int[row];
			for(int i=0;i<row;i++){
				JRadioButton sigmoid = (JRadioButton)sigmoidchecks.elementAt(i);
				if(sigmoid.isSelected())
					tf[i] = 1;
			}
			return tf;
		}

		public int[] getNodes(){
			return nodes;
		}

		@Override
		public void setValueAt(Object aValue, int r, int c) {
			if(c==1) 
				nodes[r] = Integer.valueOf((String)aValue).intValue();
		}
	}

	private boolean resetStructTableModelParameter(){
		int c = varNames.size();
		Vector usedchecks = varClassifyTableModel.getUsedChecks();
		int nout = 0;
		for(int i=0;i<c;i++){
			if(((JCheckBox)usedchecks.elementAt(i)).isSelected()){
				nout++;
			}
		}
		if(nout == 0){
			frame.showOKDialog(frame.getNolResourceString(NOOUTPUTISSPECIFIED));
			return false;
		}
		structTableModel.setParameter(nout,nout);
		return true;
	}

	@Override
	protected boolean finishAction(){
		Matlib.pack() ;
		int c = varNames.size();
		Vector ins = new Vector();
		Vector outs = new Vector();
		Vector usedchecks = varClassifyTableModel.getUsedChecks();
		Vector outDelays = new Vector();
		Vector inDelays = new Vector();

		int nout = 0;
	
		for(int i=0;i<c;i++){
			if(((JCheckBox)usedchecks.elementAt(i)).isSelected()){
				ins.addElement(varNames.elementAt(i));
				outs.addElement(varNames.elementAt(i));	
				outDelays.addElement(new long[1]);	
				inDelays.addElement(new long[1]);	
				nout++;
			}
		}

		if(nout == 0){
			frame.showOKDialog(frame.getNolResourceString(NOOUTPUTISSPECIFIED));
			return false;
		}

		int nlayers = Integer.valueOf(numberField.getText()).intValue();
		int[] tf = structTableModel.getTransferFunctions();
		int[] nodes	= structTableModel.getNodes();

		if(nlayers < 2){
			frame.showOKDialog(frame.getNolResourceString(WRONGSTRUCTURE));
			return false;
		}

		if(nlayers != tf.length || nlayers != nodes.length){
			frame.showOKDialog(frame.getNolResourceString(WRONGSTRUCTURE));
			return false;
		}

		if(nodes[0] != nout || nodes[nodes.length-1] != nout){
			frame.showOKDialog(frame.getNolResourceString(WRONGSTRUCTURE));
			return false;
		}

		
		ClassicBpn net = new ClassicBpn(nlayers,tf,nodes);
		model = new NolAnnModel(net,modelName.getText(),outs ,
			ins,outDelays,inDelays, preprocessor);
		model.setNormalStd(varClassifyTableModel.getNoiseStd());
		int runMode = 0;
		if(grossCheck.isSelected()){
			runMode = 1;
		}
		model.setRunMode(runMode);
		String comment = modelDescript.getText();
		boolean hasTimeStamps = preprocessor.getDataSeries(0).getHasTimeStamps();
		model.setHasTimeStamps(hasTimeStamps);
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
				if(clickCount != 2){
					return;
				}
				isOk = okFired();
				closeDialog();
			}
		}
	}
}
