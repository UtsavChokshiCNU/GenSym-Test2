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

import com.gensym.math.*;
import com.gensym.math.matrix.*;

import com.gensym.nols.data.*;
import com.gensym.nols.main.*;
import com.gensym.nols.util.*;

import com.gensym.DEBUG;

public class NolNewPcaModelWizard  extends NolWizardDialog
	implements NolNewModelWizard{

	private	JTextField modelName;
	private	JTextField caseName;
	private	JTextField dataSeriesName;
	private JTextArea modelDescript;
	private JTextField numberField;
	private JButton calculateDelay;
	private JList caseList;
	private JList dataSeriesList;
	private DefaultListModel caseListModel;
	private DefaultListModel dataSeriesListModel;

	private LoadFromExistModelDialog loadFromExistModelDialog;
	private ControlAction actionListener;


	private	AutoSelectionNoDelayTableModel autoSelectionNoDelayTableModel;
	private	JTable autoSelectionTableView;

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
	private NolPcaModel model;
	private Vector varNames;
	private Vector usedVarNames;

	private static final String GENERAL_LABEL = "NewPcaModelWizard_GeneralLabel";
	private static final String DATASOURCE_LABEL = "NewPcaModelWizard_OutputDataSourceLabel";
	private static final String SETTING_LABEL = "NewPcaModelWizard_SettingLabel";

	private static final String COMMENT_LABEL = "CommentLabel";
	private static final String NAMEEDITLABEL = "NewBpnModelWizard_NameEditLabel";
	private static final String PREPROCESSOR_LABEL = "NewBpnModelWizard_PreprocessorLabel";
	private static final String PREPROCESSOR = "NewBpnModelWizard_Preprocessor";
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
	private static final String SETTING_BORDER = "NewBpnModelWizard_SettingBorder";
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

	public NolNewPcaModelWizard (NolMainFrame dw) {
		super((JFrame)dw, "Create New PCA Model", true, 4);
		frame = (NolMainFrame)dw;
		actionListener = new ControlAction();
		noFire = false;
		varNames = new Vector();
		usedVarNames= new Vector();
		initializeLayout();
		initDataDisplay();
	}

	private void initializeLayout(){
		stepPanes.setElementAt(getGeneralPanel(),0);
		stepPanes.setElementAt(getCasePanel(),1);
		stepPanes.setElementAt(getDataSourcePanel(),2);
		stepPanes.setElementAt(getSettingPane(),3);
	}

	private JPanel getGeneralPanel(){
		JPanel genPane = new JPanel(new BorderLayout());
		URL url = this.getClass().getResource("largepca.gif");
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
	
	private JPanel getSettingPane(){
		JPanel setPane = new JPanel(new BorderLayout());
		JPanel infoPane = new JPanel(new GridLayout());
 		infoPane.setBorder(new EmptyBorder(10,10,10,10));
		String s = frame.getNolResourceString(SETTING_LABEL);
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

		autoSelectionNoDelayTableModel = new AutoSelectionNoDelayTableModel();

		selectionNoDelaySorter = new TableSorter(autoSelectionNoDelayTableModel); //ADDED THIS FOR  SORTING GCHEN 6.7.99

		
		autoSelectionTableView = new JTable(selectionNoDelaySorter);
		autoSelectionTableView.setDefaultRenderer(AbstractButton.class, 
			new AutoSelectRenderer());
		selectionNoDelaySorter.addMouseListenerToHeaderInTable(autoSelectionTableView);

		autoSelectionTableView.setSelectionMode(0);
		autoSelectionTableView.setSelectionBackground(Color.white);
		autoSelectionTableView.setCellSelectionEnabled(true);
		autoSelectionTableView.setSelectionForeground(Color.black);
		JScrollPane listScrollPane = new JScrollPane(autoSelectionTableView);
		listScrollPane.setBackground(Color.white);

		autoPane.add("Center",listScrollPane);

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
		String title = "Create Principal Component Analysis Model- "+setTitleForStep(currentStep);
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
		String title = "Create Principal Component Analysis Model- "+setTitleForStep(currentStep);
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
			title = title + " - Settings";
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
			condition = condition && project.getPlsModelIndexByName(mName) == -1  && project.getPcaModelIndexByName(mName) == -1; 
	
			if(condition){
				modelName.setText(mName);
				break;
			}
			count++;
		}
		noFire = false;
	}

	public NolPcaModel getModel(){
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
		
		for(int i=0;i<vpNames.size();i++){
			String name = vpNames.elementAt(i).toString();
			Variable varObj = preprocessor.getVariableFromVariableName(name);
			double std = varObj.getSTD();
			double range = varObj.getRange();
			if(std>0 && range >0){
				varNames.addElement(name);
				usedVarNames.addElement(name);
			}
		}
		autoSelectionNoDelayTableModel.setNames(usedVarNames);	
		selectionNoDelaySorter.setModel(autoSelectionNoDelayTableModel);
		autoSelectionTableView.setModel(selectionNoDelaySorter);
	}

	private void selectedDataSeries(int selectedIndex){
		dataSeries  = preprocessor.getDataSeries(selectedIndex);
		dataSeriesName.setText(dataSeries.getName());

		Vector varObjs = dataSeries.getVarObjects();
		int row = dataSeries.getRow();
		numOfVariable.setText(String.valueOf(varObjs.size()));
		numOfSample.setText(String.valueOf(row));
	}

	private void loadParaFromExistModel(){
		Vector models = new Vector();
		models.addAll(frame.getProject().getPcaModels());
		getLoadFromExistModelDialog().setContent(models);
		getLoadFromExistModelDialog().setBounds(200,200,300,200);
		getLoadFromExistModelDialog().setVisible(true);
		if(getLoadFromExistModelDialog().isOk()){
			int index = getLoadFromExistModelDialog().getSelectedIndex();
			if(index >=0){
				NolPcaModel existModel = (NolPcaModel)models.elementAt(index);
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
		Vector inputs = modelPara.inputs;
		modelDescript.setText(modelPara.comment);
		if(inputs.isEmpty())
			return false;
		String varName = inputs.elementAt(0).toString();
		int dindex = preprocessor.getDataSeriesIndex(preprocessor.getDataSeriesFromVariableName(varName).getName());
		selectedDataSeries(dindex);
		autoSelectionNoDelayTableModel.setNames(inputs);
		selectionNoDelaySorter.setModel(autoSelectionNoDelayTableModel);
		return true;
	}

	private boolean updateParameterFromExistingModel(NolModel2 existModel){
		String prepName = existModel.getPreprocessor().getName();
		int pindex = frame.getProject().getPreprocessorIndexByName(prepName);
		if(pindex == -1){
			return false;
		}
		selectedPreprocessor(pindex);
		Vector inputs = existModel.getInputs();
		modelDescript.setText(existModel.getComment());
		if(inputs.isEmpty())
			return false;
		String varName = inputs.elementAt(0).toString();
		int dindex = preprocessor.getDataSeriesIndex(preprocessor.getDataSeriesFromVariableName(varName).getName());
		selectedDataSeries(dindex);
		autoSelectionNoDelayTableModel.setNames(inputs);
		selectionNoDelaySorter.setModel(autoSelectionNoDelayTableModel);
		return true;
	}

	@Override
	public void receiveRatingResults(Vector inVars, Vector delays, Vector outVars, Vector ratings){}
	
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
			if(command.equals("loadFromModel")){
				loadParaFromExistModel();
  			}else if(command.equals("loadFromDisk")){
				loadParaFromFile();
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

	class AutoSelectionNoDelayTableModel extends AbstractTableModel{
		private int row,col;
		private int digits = 5;
		private Vector names;
		private Vector usedchecks;
		private String[] colHd = {
			frame.getNolResourceString(VARIABLE),
			frame.getNolResourceString(USED)};

		public AutoSelectionNoDelayTableModel(){
			row = 0;
			col = 2;
			names = new Vector();
			usedchecks = new Vector();
		}

		public void setNames(Vector names){
			this.names = names;
			int nc = names.size();
			usedchecks.removeAllElements();

			for(int i=0;i<nc;i++){
				String n = (String)names.elementAt(i);
				JCheckBox check = new JCheckBox(){
					@Override
					public float getAlignmentY() { return 0.0f; }			
				};
				check.setBackground(Color.white);
				check.setSelected(true);
				usedchecks.addElement(check);
			}
			row = names.size();				
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
		Vector usedNames = new Vector();		
		Vector names = autoSelectionNoDelayTableModel.getNames();
		if(names.isEmpty()){
			frame.showOKDialog(frame.getNolResourceString(NOINPUTISSPECIFIED));
			return false;
		}	
		Vector usedChecks = autoSelectionNoDelayTableModel.getUsedChecks();
		for(int i=0;i<names.size();i++){
			if(((JCheckBox)usedChecks.elementAt(i)).isSelected()){ 
				usedNames.addElement(names.elementAt(i));
			}
		}
		int nin = usedNames.size();
		if(nin == 0){
			frame.showOKDialog(frame.getNolResourceString(NOINPUTISSPECIFIED));
			return false;
		}
		model = new NolPcaModel(modelName.getText(),usedNames, preprocessor);

		String comment = modelDescript.getText();
		if(comment != null)
			model.setComment(comment);
		try{
			model.train();
			model.setIsTrained(true);
		}catch(MathException ev){
			model.setIsTrained(false);
System.out.println("pca training ev="+ev.getMessage());
			//do something if can not train the model.
		}
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
			if(!choiceVector.isEmpty()) {
				choiceList.setSelectedIndex(0);
			}
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
}
