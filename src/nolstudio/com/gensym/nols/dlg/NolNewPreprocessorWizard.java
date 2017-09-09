package com.gensym.nols.dlg;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.net.URL;
import java.text.*;

import javax.swing.*;
import javax.swing.event.*;
import javax.swing.border.*;

import com.gensym.nols.data.*;
import com.gensym.nols.main.*;
import com.gensym.math.MathException;

import com.gensym.DEBUG;

public class NolNewPreprocessorWizard  extends NolWizardDialog{
	private JTextField preprocessorName;
	private JTextArea preprocessorDescript;
	private JTextArea includeArea;
	private JTextArea excludeArea;
	private JButton joinLabelButton;
	private JButton deleteJoinLabelButton;
	private JList singleLabelList;
	private JList multilabelList;
	private DefaultListModel singleLabelListModel;
	private DefaultListModel multilabelListModel;
	private NolMainFrame frame;
	private RawDataSource rawDataSource;
	private ControlAction actionListener;
	private boolean noFire;
	private boolean isSingle;

	private NolSelectPanel dataSeriesSelectPanel;
	private NolSelectPanel varSelectPanel;

	private ViewFilter viewFilter;
	private Vector selectedDataSeries;
	private Vector includePatterns;
	private Vector excludePatterns;
	private Vector joinedLabels;
	private Vector labels;


	private JCheckBox isResample;
	private JComboBox dsBox ;
	private JTextField oldStartTime ;
	private JTextField oldEndTime ;
	private JTextField newStartTime ;
	private JTextField newEndTime ;
	private JTextField newIntervalTime;
	private Vector resamplers;
	private Preprocessor preprocessor;

		
	private static final String GENERAL_LABEL = "NewPreprocessorWizard_GeneralLabel";
	private static final String COMMENT_LABEL = "CommentLabel";
	private static final String NAMEEDITLABEL = "NewPreprocessorWizard_NameEditLabel";
	private static final String VARIABLE_LABEL = "NewPreprocessorWizard_VariableLabel";
	private static final String VARIABLE = "NewPreprocessorWizard_Variable";
	private static final String DATASELECTION_LABEL = "NewPreprocessorWizard_DataSelectionLabel";
	private static final String DATASERIES = "NewPreprocessorWizard_DataSeries";
	private static final String QUERY_LABEL = "NewPreprocessorWizard_QueryLabel";
	private static final String SAMPLE_LABEL = "NewPreprocessorWizard_SampleLabel";
	private static final String ADD = "NewPreprocessorWizard_Add";
	private static final String DELETE = "NewPreprocessorWizard_Delete";
	private static final String EXCLUDE = "NewPreprocessorWizard_Exclude";
	private static final String LABELS = "NewPreprocessorWizard_Labels";
	private static final String JOINEDLABELS = "NewPreprocessorWizard_JoinedLabels";
	private static final String DEFINEJOINEDLABEL = "NewPreprocessorWizard_DefineJoinedLabel";
	private static final String NODATASERIESINFOR = "NewPreprocessorWizard_NoDataSeriesInfor";
	private static final String ONEDATASERIESINFOR = "NewPreprocessorWizard_OneDataSeriesInfo";
	private static final String TIMECONFLICTINFOR = "NewPreprocessorWizard_TimeConflictInfor";
	private static final String NAMECONFLICTINFOR = "NewPreprocessorWizard_NameConflictInfor";
	private static final String ONELABELINFOR = "NewPreprocessorWizard_OneLabelInfor";
	private static final String NOVARIABLEINFOR = "NewPreprocessorWizard_NoVariableInfor";
	private static final String NONAMEFORPREPROCESSOR = "NewPreprocessorWizard_NoNameForPreprocessor";

	

	public NolNewPreprocessorWizard (JFrame dw) {
		super(dw, "Create New Preprocessor", true, 4);
		frame = (NolMainFrame)dw;
		actionListener = new ControlAction();
		selectedDataSeries = new Vector();
		viewFilter = new ViewFilter();
		includePatterns = new Vector();
		excludePatterns = new Vector();
		joinedLabels = new Vector();
		noFire = false;
		initializeLayout();
	}

	private void initializeLayout(){
		stepPanes.setElementAt(getGeneralPanel(),0);
		stepPanes.setElementAt(getDataSelectPanel(),1);
		stepPanes.setElementAt(getVarPanel(),2);
		stepPanes.setElementAt(getQueryPane(),3);
//		stepPanes.setElementAt(getResamplePane(),4);
	}

	private JPanel getGeneralPanel(){
		JPanel genPane = new JPanel(new BorderLayout());
		URL url = this.getClass().getResource("largePreprocessor.gif");
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
		preprocessorName = new JTextField();
		preprocessorName.addActionListener(actionListener);
		namePane.add(preprocessorName);
		namePane.add(new JLabel(frame.getNolResourceString(COMMENT_LABEL)+":"));
 		cenPane.add("North",namePane);

		JPanel descripPane = new JPanel(new GridLayout());
 		descripPane.setBorder(new EmptyBorder(0,10,10,10));
		preprocessorDescript = new JTextArea();
		JScrollPane listScrollPane = new JScrollPane(preprocessorDescript);
		listScrollPane.setBorder(BorderFactory.createLoweredBevelBorder());
		descripPane.add(listScrollPane);
 		cenPane.add("Center",descripPane);

 		genPane.add("Center",cenPane);
		return genPane;
	}

	private JPanel getVarPanel(){
		JPanel variablePane = new JPanel(new BorderLayout());
		JPanel infoPane = new JPanel(new GridLayout());
 		infoPane.setBorder(new EmptyBorder(10,10,10,10));
		String s = frame.getNolResourceString(VARIABLE_LABEL);
		JTextArea infoLabel = new JTextArea(s);
		infoLabel.setEditable(false);
		infoLabel.setLineWrap(true);
		infoLabel.setWrapStyleWord(true);
		infoLabel.setBackground(infoPane.getBackground());
		infoPane.add(infoLabel);
		variablePane.add("North",infoPane);
		varSelectPanel = new NolSelectPanel(frame.getNolResourceString(VARIABLE)+":");
		variablePane.add("Center",varSelectPanel);
		return variablePane;
	}

	private JPanel getDataSelectPanel(){
		JPanel dataPane = new JPanel(new BorderLayout());
		JPanel infoPane = new JPanel(new GridLayout());
 		infoPane.setBorder(new EmptyBorder(10,10,10,10));
		String s = frame.getNolResourceString(DATASELECTION_LABEL);
		JTextArea infoLabel = new JTextArea(s);
		infoLabel.setEditable(false);
		infoLabel.setLineWrap(true);
		infoLabel.setWrapStyleWord(true);
		infoLabel.setBackground(infoPane.getBackground());
		infoPane.add(infoLabel);
		dataPane.add("North",infoPane);

		dataSeriesSelectPanel = new NolSelectPanel(frame.getNolResourceString(DATASERIES)+":");
		dataPane.add("Center",dataSeriesSelectPanel);
		return dataPane;
	}

 	private JPanel getQueryPane(){
		JPanel queryPane = new JPanel(new BorderLayout());
		JPanel infoPane = new JPanel(new GridLayout());
 		infoPane.setBorder(new EmptyBorder(10,10,10,10));
		String s = frame.getNolResourceString(QUERY_LABEL);
		JTextArea infoLabel = new JTextArea(s);
		infoLabel.setEditable(false);
		infoLabel.setLineWrap(true);
		infoLabel.setWrapStyleWord(true);
		infoLabel.setBackground(infoPane.getBackground());
		infoPane.add(infoLabel);
		queryPane.add("North",infoPane);

		JPanel labelPane = new JPanel(new BorderLayout());
		JPanel pane = new JPanel(new GridLayout(2,1,5,5));
		pane.add(getIncludePane());
		pane.add(getExcludePane());
		labelPane.add("Center",pane);
		labelPane.add("North",getLabelListPane());
		
		queryPane.add("Center",labelPane);
		
		return queryPane;
	}

	private JPanel getResamplePane(){
		JPanel resamplePane = new JPanel(new BorderLayout());
		JPanel infoPane = new JPanel(new GridLayout());
 		infoPane.setBorder(new EmptyBorder(10,10,10,10));
		String s = frame.getNolResourceString(SAMPLE_LABEL);
		JTextArea infoLabel = new JTextArea(s);
		infoLabel.setEditable(false);
		infoLabel.setLineWrap(true);
		infoLabel.setWrapStyleWord(true);
		infoLabel.setBackground(infoPane.getBackground());
		infoPane.add(infoLabel);
		resamplePane.add("North",infoPane);

		JPanel selectPane = new JPanel(new GridLayout(7,2,5,5));
 		selectPane.setBorder(new EmptyBorder(10,10,10,10));
		selectPane.add(new JLabel("Do you want to resampe the dataseries?"));
		isResample = new JCheckBox();
		selectPane.add(isResample);
		
		selectPane.add(new JLabel("Select the dataseries to resample:"));
		dsBox = new JComboBox();
		dsBox.addItemListener(actionListener);
		selectPane.add(dsBox);
		
		selectPane.add(new JLabel("Existing start time:"));
		oldStartTime = new JTextField();
		selectPane.add(oldStartTime);
		
		selectPane.add(new JLabel("Existing end time:"));
		oldEndTime = new JTextField();
		selectPane.add(oldEndTime);

		selectPane.add(new JLabel("New start time:"));
		newStartTime = new JTextField();
		selectPane.add(newStartTime);

		selectPane.add(new JLabel("New end time:"));
		newEndTime = new JTextField();
		selectPane.add(newEndTime);

		selectPane.add(new JLabel("New interval (Second):"));
		newIntervalTime = new JTextField();
		selectPane.add(newIntervalTime);

		resamplePane.add("Center",selectPane);
		
		return resamplePane;
	}

	private JPanel getIncludePane(){
		JPanel includePane = new JPanel();
		includePane.setLayout(new BorderLayout());
		includePane.setBorder(BorderFactory.createTitledBorder("Include:"));
		includeArea = new JTextArea("All points");
		includeArea.setEditable(false);
		includeArea.setBackground(Color.white);
		JScrollPane areaScrollPane = new JScrollPane(includeArea);
		areaScrollPane.setBorder(BorderFactory.createLoweredBevelBorder());
		includePane.add("Center",areaScrollPane);
		JPanel control = new JPanel(new GridLayout(2,1,5,5));
		control.setBorder(new TitledBorder(new EmptyBorder(1, 1, 1, 1),               
				"", TitledBorder.LEFT , TitledBorder.TOP));
		JButton but = new JButton(frame.getNolResourceString(ADD));
		but.setActionCommand("includeAdd");
		but.addActionListener(actionListener);
		control.add(but);
		but = new JButton(frame.getNolResourceString(DELETE));
		but.setActionCommand("includeDelete");
		but.addActionListener(actionListener);
		control.add(but);
		includePane.add("East",control);
		return includePane; 
	}

	private JPanel getExcludePane(){
		JPanel excludePane = new JPanel();
		excludePane.setLayout(new BorderLayout());
		excludePane.setBorder(BorderFactory.createTitledBorder(
			frame.getNolResourceString(EXCLUDE)+":"));
		excludeArea = new JTextArea("");
		excludeArea.setBackground(Color.white);
		JScrollPane areaScrollPane = new JScrollPane(excludeArea);
		areaScrollPane.setBorder(BorderFactory.createLoweredBevelBorder());
		excludePane.add("Center",areaScrollPane);
		JPanel control = new JPanel(new GridLayout(2,1,5,5));
		control.setBorder(new TitledBorder(new EmptyBorder(1, 1, 1, 1),               
				"", TitledBorder.LEFT , TitledBorder.TOP));
		JButton but = new JButton(frame.getNolResourceString(ADD));
		but.setActionCommand("excludeAdd");
		but.addActionListener(actionListener);
		control.add(but);
		but = new JButton(frame.getNolResourceString(DELETE));
		but.setActionCommand("excludeDelete");
		but.addActionListener(actionListener);
		control.add(but);
		excludePane.add("East",control);
		return excludePane; 
	}

	private JPanel getLabelListPane(){
		JPanel labelListPane = new JPanel();
		labelListPane.setLayout(new GridLayout(1,2,5,5));

		JPanel pane = new JPanel(new GridLayout());
		pane.setBorder(BorderFactory.createTitledBorder(
			frame.getNolResourceString(LABELS)+":"));
		singleLabelList = new JList(getSingleLabelListModel());
		singleLabelList.setBackground(Color.white);
		singleLabelList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		singleLabelList.addListSelectionListener(actionListener);

		JScrollPane listScrollPane = new JScrollPane(singleLabelList);
		listScrollPane.setBorder(BorderFactory.createLoweredBevelBorder());
		listScrollPane.setPreferredSize(NolMainFrame.vpad50);
		pane.add(listScrollPane);
		labelListPane.add(pane);

		pane = new JPanel(new BorderLayout());
		pane.setBorder(BorderFactory.createTitledBorder(
			frame.getNolResourceString(JOINEDLABELS)+":"));
		multilabelList = new JList(getMultilabelListModel());
		multilabelList.setBackground(Color.white);
		multilabelList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		multilabelList.addListSelectionListener(actionListener);
		listScrollPane = new JScrollPane(multilabelList);
		listScrollPane.setPreferredSize(NolMainFrame.vpad50);
		listScrollPane.setBorder(BorderFactory.createLoweredBevelBorder());

		joinLabelButton = new JButton(frame.getNolResourceString(DEFINEJOINEDLABEL));
		joinLabelButton.setActionCommand("Define Joined Label");
		joinLabelButton.addActionListener(actionListener);
		deleteJoinLabelButton = new JButton(frame.getNolResourceString(DELETE));
		deleteJoinLabelButton.setActionCommand("Delete Joined Label");
		deleteJoinLabelButton.addActionListener(actionListener);
		JPanel pane0 = new JPanel();
		pane0.add(joinLabelButton);
		pane0.add(deleteJoinLabelButton);
		pane.add("South",pane0);
		pane.add("Center",listScrollPane);
		labelListPane.add(pane);
		return labelListPane; 
	}

	private DefaultListModel getSingleLabelListModel() {
		if (singleLabelListModel == null) {
			singleLabelListModel = new DefaultListModel();
		}	
		return singleLabelListModel;
	}	

	private DefaultListModel getMultilabelListModel() {
		if (multilabelListModel == null) {
			multilabelListModel = new DefaultListModel();
		}	
		return multilabelListModel;
	}
	
	public void resetData(){
		isOK = false;
		Project project = frame.getProject();
		// MK 5/10/99 -- provide clean new view filter to each preprocessor
		// avoid sharing bug in 2.0 Rev. 0, where two preprocessor were pointing at the same view filter
		viewFilter = new ViewFilter();
		rawDataSource = project.getRawDataSource();
		int dc = rawDataSource.getNumberOfDataSeries();
		Vector dss = rawDataSource.getDataSeries();
		if(dss.isEmpty()) {
			return;
		}
		Vector contents = new Vector(dc);
		Vector selected = new Vector();
		Vector varTags = new Vector();
		DataSeries ds = (DataSeries)dss.elementAt(0);
		boolean hasTimeStamps = ds.getHasTimeStamps();
		contents.addElement(ds); 
		selected.addElement(ds); 
		Vector varObjs = ds.getVarObjects();
		for(int i=1;i<varObjs.size();i++){
			varTags.addElement(((Variable)varObjs.elementAt(i)).getTag());
		}
		for(int i=1;i<dc;i++){
			DataSeries ds1 = (DataSeries)dss.elementAt(i);
			contents.addElement(ds1); 
			if(hasTimeStamps){
				if(ds1.getHasTimeStamps()){
					Vector varObjs1 = ds1.getVarObjects();
					boolean valid = true;
					for(int j=0;j<varObjs1.size();j++){
						if(varTags.contains(((Variable)varObjs1.elementAt(j)).getTag())){
							valid = false;
							break;
						}
					}
					if(valid){
						for(int j=0;j<varObjs1.size();j++){
							varTags.addElement(((Variable)varObjs1.elementAt(j)).getTag());   // MK 2/15/99 changed i to j
						}
						selected.addElement(ds1); 
					}
					if(DEBUG.debugFlag){
						System.out.println("selected valid="+valid );
					}
				}
			}
		}
		dataSeriesSelectPanel.setContents(contents,selected);
		int count = 1;
		while(true){
			String cName = "Preprocessor"+count;
			if(project.getPreprocessorIndexByName(cName) == -1){
				preprocessorName.setText(cName);
				break;
			}
			count++;
		}
		preprocessorDescript.setText("");
		labels = project.getLabels();
		if(labels.size() <2){
			joinLabelButton.setEnabled(false);
			deleteJoinLabelButton.setEnabled(false);
		}else{
			joinLabelButton.setEnabled(true);
			deleteJoinLabelButton.setEnabled(true);
		}
		refreshSingleList();
		includePatterns.removeAllElements();
		excludePatterns.removeAllElements();
		refreshIncludeArea();
		refreshExcludeArea();
		refreshVarSelectPanel();
	}

	@Override
	public void setVisible(boolean v){
		stepPane.removeAll();
		stepPane.add((JPanel)stepPanes.elementAt(0));
		stepPane.validate();
		stepPane.repaint(0l);
		currentStep = 0;
		modifyStep(true);
		String title = "Create New Preprocessor - "+setTitleForStep(currentStep);
		title = title + " - General";
		setTitle(title);
		super.setVisible(v);
	}

	@Override
	protected void modifyStep(boolean isNext){
		super.modifyStep(isNext);
		String title = "Create New Preprocessor - "+setTitleForStep(currentStep);
		if(currentStep == 1){
			title = title + " - General";
			finishButton.setEnabled(false);
		}else if(currentStep == 2){
			if(isNext){
				if(preprocessorName.getText().equals("")){
					frame.showOKDialog(frame.getNolResourceString(NONAMEFORPREPROCESSOR));
					super.modifyStep(false);
					finishButton.setEnabled(false);
				}
			}
			title = title + " - Data Series";
			finishButton.setEnabled(false);
		}else if(currentStep == 3){
			title = title + " - Variable";
			if(isNext){
				if(!refreshVarSelectPanel()){
					super.modifyStep(false);
					finishButton.setEnabled(false);
				}
			}
		}else if(currentStep == 4){
			title = title + " - Query";
		}else if(currentStep == 5){
			title = title + " - Resampling";
			if(isNext){
				refreshResamplePanel();
			}
		}
		if(DEBUG.debugFlag){
			System.out.println(title);
		}
		setTitle(title);
	}

	public String getPreprocessorName(){
		return preprocessorName.getText();
	}


	public String getPreprocessorComment(){
		return preprocessorDescript.getText();
	}

	public Vector getVariables(){
		int vars = varSelectPanel.getSelectedListModel().size();
		Vector selectedVariables = new Vector(vars);
		for(int i=0;i<vars;i++){
			String n = (String)varSelectPanel.getSelectedListModel().elementAt(i); 
			if(DEBUG.debugFlag){
				System.out.println("new case selected varname="+n);
			}
			boolean found = false;
			for(int c=0;c<selectedDataSeries.size();c++){
				DataSeries ds = (DataSeries)selectedDataSeries.elementAt(c);
				Vector varObjs = ds.getVarObjects();
				for(int r=0;r<ds.getColumn();r++){
					Variable varObj = (Variable)varObjs.elementAt(r);
					String varName = ds.getName()+"."+ varObj.getName();
					if(varName.equals(n)){
						selectedVariables.addElement(varObj);
					}
				}
			}
		}
		return selectedVariables;
	}

	public ViewFilter getViewFilter(){ 
/*		LabelPattern[] showPatterns = getLabelPatterns(includePatterns);
		if(showPatterns != null) viewFilter.setPatternsToShow(showPatterns);
		LabelPattern[] hidePatterns = getLabelPatterns(excludePatterns);
		if(hidePatterns != null) viewFilter.setPatternsToHide(hidePatterns);
*/		return viewFilter;
	}
	
	public boolean checkLabelPatterns(){
		LabelPattern[] showPatterns = getLabelPatterns(includePatterns);
		LabelPattern[] hidePatterns = getLabelPatterns(excludePatterns);

		if(showPatterns != null && hidePatterns != null){
			for(int i=0;i<showPatterns.length;i++){
				for(int j=0;j<hidePatterns.length;j++){
					if(showPatterns[i].equals(hidePatterns[j]))
						return false;
				}
			}
		}		
		if(DEBUG.debugFlag){
			System.out.println("showPatterns length="+showPatterns.length);
			System.out.println("hidePatterns length="+hidePatterns.length);
		}
		if(showPatterns != null){
			viewFilter.setPatternsToShow(showPatterns);
		}
		if(hidePatterns != null) {
			viewFilter.setPatternsToHide(hidePatterns);
		}
		return true;
	}
   	
	private LabelPattern[] getLabelPatterns(Vector labelPatterns){
		Project project = frame.getProject();
		int numberOfLabels = project.getNumberOfLabels();
		int p = labelPatterns.size();
		if(p==0) {
			return new LabelPattern[0];
		}
		LabelPattern[] patterns = new LabelPattern[p];
		Vector prjLabels = project.getLabels();
		
		for(int i=0;i<p;i++){
			LabelPattern pattern = new LabelPattern();
			Vector labelsPresent = new Vector();
			Vector labelsAbsent = new Vector();
			Object lab = labelPatterns.elementAt(i);
			if(lab instanceof String){
				if(((String)lab).equals("Unlabeled")){
					for(int j=0;j<numberOfLabels;j++){
						labelsAbsent.addElement(prjLabels.elementAt(j));
					}
				}
			}else if(lab instanceof NolLabel){
				labelsPresent.addElement(lab);
			}else{
				Vector jLabels = (Vector)lab;
				int c = jLabels.size();
				for(int j=0;j<c;j++){
					labelsPresent.addElement(jLabels.elementAt(j));
				}
			}
			pattern.setLabelsPresent(labelsPresent);
			pattern.setLabelsAbsent(labelsAbsent);
			pattern.setExistLabels(frame.getProject().getLabels());
			patterns[i] = pattern;
		}
		return patterns;
	}
	
	private void addToMultiList(Vector jLabel) {
		if(!joinedLabels.contains(jLabel)){
			joinedLabels.addElement(jLabel);
			refreshMultiList();
		}
	}

   	private void deleteFromMultiList(int index) {
		int c = joinedLabels.size();
		if(index>=0&&index<c){
			joinedLabels.removeElementAt(index);
		}
		refreshMultiList();
	}

   	private void refreshMultiList() {
		getMultilabelListModel().removeAllElements();
		int c = joinedLabels.size();
		for(int i=0;i<c;i++){
			Vector jLabel = (Vector)joinedLabels.elementAt(i);
			String n = joinedLabelString(jLabel); 
			getMultilabelListModel().addElement(n);
		}
	}
		
	private boolean refreshVarSelectPanel() {
		selectedDataSeries.removeAllElements();
		int sdc = dataSeriesSelectPanel.getSelectedListModel().size();
		if(sdc == 0){
			frame.showOKDialog(frame.getNolResourceString(NODATASERIESINFOR));
			return false;
		}
		if(sdc>1){
			boolean validRowBasedData = true;
 			for(int i=0;i<sdc;i++){
  				DataSeries ds = (DataSeries)dataSeriesSelectPanel.getSelectedListModel().elementAt(i); 
				if(!ds.getHasTimeStamps()){
					validRowBasedData = false;
					break;
				}
			}
			if(!validRowBasedData){
				frame.showOKDialog(frame.getNolResourceString(ONEDATASERIESINFOR));
				return false;
			}
			for(int i=0;i<sdc;i++){
				boolean found  = false;
				boolean valid  = true;
				DataSeries ds = (DataSeries)dataSeriesSelectPanel.getSelectedListModel().elementAt(i); 
				for(int j=0;j<selectedDataSeries.size();j++){  
					DataSeries ds1 = (DataSeries)selectedDataSeries.elementAt(j); 
					if(ds.getHasTimeStamps() != ds1.getHasTimeStamps()){
						valid = false;
						break;
					}
					Vector vars1 = ds1.getVarObjects();
					for(int k=0;k<vars1.size();k++){
						Variable v1 = (Variable)vars1.elementAt(k);
						if(ds.getVarByTag(v1.getTag()) != null){
							found = true;
							break;
						}
					}
					if(found){
						break;
					}
				}
				if(DEBUG.debugFlag){
					System.out.println("new case selected data series="+ds.getName());
				}
				if(!valid){
					frame.showOKDialog(frame.getNolResourceString(TIMECONFLICTINFOR));
					return false;
				}
				if(found){
					frame.showOKDialog(frame.getNolResourceString(NAMECONFLICTINFOR));
					return false;
				}
				selectedDataSeries.addElement(ds);
			}
		}else{
			selectedDataSeries.addElement(dataSeriesSelectPanel.getSelectedListModel().elementAt(0));
		}

		int dc = selectedDataSeries.size();
		if(dc == 0){
			frame.showOKDialog(frame.getNolResourceString(NODATASERIESINFOR));
			return false;
		}

		Vector contents = new Vector();
		for(int i=0;i<dc;i++){
			DataSeries ds = (DataSeries)selectedDataSeries.elementAt(i);
			Vector varObjs = ds.getVarObjects();
			for(int j=0;j<varObjs.size();j++){
				Variable varObj = (Variable)varObjs.elementAt(j);
				String varName = ds.getName()+"."+ varObj.getName();
				contents.addElement(varName);
			}
		}
		varSelectPanel.setSelectedContents(contents);
		return true;
	
	}

	private void refreshSingleList() {
		getSingleLabelListModel().removeAllElements();
		getSingleLabelListModel().addElement("Unlabeled");
		int c = labels.size();
		for(int i=0;i<c;i++)
			getSingleLabelListModel().addElement((NolLabel)labels.elementAt(i));
	}


	private String joinedLabelString(Vector jLabel){
		int c = jLabel.size();
		String n = "";
		if(c>0){
			for(int i=0;i<c-1;i++)
				n = n+jLabel.elementAt(i).toString()+" and ";	
			n = n+jLabel.elementAt(c-1).toString();
		}
		return n;
	}

	private void refreshIncludeArea(){
		int c = includePatterns.size();
		String n = "All points";
		if(c > 0){
			n = "";
			for(int i=0;i<c-1;i++){
				Object lab = includePatterns.elementAt(i);
				if(lab instanceof String){
					n = n + "Any point unlabeled plus ";
				}else if(lab instanceof NolLabel){
					n = n + "Any point labeled with "+lab.toString() + " plus ";
				}else{
					n = n + "Any point labeled with "+joinedLabelString((Vector)lab) + " plus ";
				}
				n = n + "\n";
			}
			Object lab = includePatterns.elementAt(c-1);
			if(lab instanceof String){
				n = n + "Any point unlabeled";
			}else if(lab instanceof NolLabel){
				n = n + "Any point labeled with "+lab.toString();			
			}else{
				n = n + "Any point labeled with "+joinedLabelString((Vector)lab);
			}
		}		
		includeArea.setText(n);
	}

	private void refreshExcludeArea(){
		int c = excludePatterns.size();
		String n = "";
		if(c > 0){
			for(int i=0;i<c-1;i++){
				Object lab = excludePatterns.elementAt(i);
				if(lab instanceof String){
					n = n + "Any point unlabeled plus ";
				}else if(lab instanceof NolLabel){
					n = n + "Any point labeled with "+lab.toString() + " plus ";
				}else{
					n = n + "Any point labeled with "+joinedLabelString((Vector)lab) + " plus ";
				}
				n = n + "\n";
			}
			Object lab = excludePatterns.elementAt(c-1);
			if(lab instanceof String){
				n = n + "Any point unlabeled";
			}else if(lab instanceof NolLabel){
				n = n + "Any point labeled with "+lab.toString();			
			}else{
				n = n + "Any point labeled with "+joinedLabelString((Vector)lab);
			}
		}		
		excludeArea.setText(n);
	}

	private void refreshResamplePanel(){
		int sdc = dataSeriesSelectPanel.getSelectedListModel().size();
		if(sdc==0) {
			return;
		}
		boolean validRowBasedData = true;
 		for(int i=0;i<sdc;i++){
  			DataSeries ds = (DataSeries)dataSeriesSelectPanel.getSelectedListModel().elementAt(i); 
			if(!ds.getHasTimeStamps()){
				validRowBasedData = false;
				break;
			}
		}
		if(!validRowBasedData){
			return;
		}
		dsBox.removeAllItems();
		for(int i=0;i<sdc;i++){
			DataSeries ds = (DataSeries)dataSeriesSelectPanel.getSelectedListModel().elementAt(i); 
			dsBox.addItem(ds.getName());
		}
			dsBox.addItem("TEST");

		DataSeries ds0 = (DataSeries)dataSeriesSelectPanel.getSelectedListModel().elementAt(0); 
		long[] ts = ds0.getTimeStamps();
		SimpleDateFormat fmt = new SimpleDateFormat("M/d/y H:m:s");
		oldStartTime.setText(fmt.format(new Date(ts[0])));
		oldEndTime.setText(fmt.format(new Date(ts[ts.length-1])));

//			DataSeries ds = (DataSeries)selectedDataSeries.elementAt(i);
	}

	@Override
	protected boolean finishAction(){
		if(!checkLabelPatterns()){
			frame.showOKDialog(frame.getNolResourceString(ONELABELINFOR));
			return false;
		}
		if(getVariables().isEmpty()){
			frame.showOKDialog(frame.getNolResourceString(NOVARIABLEINFOR));
			return false;
		}

		Project2 project = frame.getProject();
		if(project.getPreprocessorIndexByName(getPreprocessorName()) != -1){
			frame.showOKDialog(frame.getNolResourceString("MainFrame_HaveSameNamePreprocessor"));
			return false;
		}
		
		try{
			preprocessor = new Preprocessor(getPreprocessorName(), project, getVariables(), viewFilter);
			preprocessor.setComment(getPreprocessorComment());
/*			if(isResample.isSelected()){
				SimpleDateFormat fmt = new SimpleDateFormat("M/d/y H:m:s");
				Calendar currentCalendar = Calendar.getInstance();
				Date dt= fmt.parse(newStartTime.getText());
				currentCalendar.setTime(dt);
				long t1 = currentCalendar.getTime().getTime();
				dt= fmt.parse(newEndTime.getText());
				currentCalendar.setTime(dt);
				long t2 = currentCalendar.getTime().getTime();
				long t3 = Long.valueOf(newIntervalTime.getText()).longValue();
				t3 = t3 * 1000;
				preprocessor.resampleData(t1,t2,t3);
			}
		}catch(java.text.ParseException e){
*/	 
		}catch(MathException e){
			preprocessor = new Preprocessor();
		}
		return true;
	}

	public Preprocessor getPreprocessor(){
		return preprocessor;
	}

    class ControlAction extends AbstractAction implements ListSelectionListener, ItemListener {
		ControlAction() {	super("controlAction");}
        @Override
		public void actionPerformed(ActionEvent e) {
			String command = e.getActionCommand();
			if(command.equals("includeAdd")){
				if(isSingle){
					if(singleLabelList.isSelectionEmpty()){
						return;
					}
					Object item = singleLabelList.getSelectedValue();
					if(!includePatterns.contains(item)){
						includePatterns.addElement(item);
						refreshIncludeArea();
					}
				}else{
					if(multilabelList.isSelectionEmpty()) {
						return;
					}
					int c = multilabelList.getSelectedIndex();
					Object item = joinedLabels.elementAt(c);
					if(!includePatterns.contains(item)){
						includePatterns.addElement(item);
						refreshIncludeArea();
					}
				}
			}else if(command.equals("includeDelete")){
				int c = includePatterns.size();
				if(c>0){
					includePatterns.removeElementAt(c-1);
 					refreshIncludeArea();
				}
			}else if(command.equals("excludeAdd")){
				if(isSingle){
					if(singleLabelList.isSelectionEmpty()) {
						return;
					}
					Object item = singleLabelList.getSelectedValue();
					if(!excludePatterns.contains(item)){
						excludePatterns.addElement(item);
						refreshExcludeArea();
					}
				}else{
					if(multilabelList.isSelectionEmpty()) {
						return;
					}
					int c = multilabelList.getSelectedIndex();
					Object item = joinedLabels.elementAt(c);
					if(!excludePatterns.contains(item)){
						excludePatterns.addElement(item);
						refreshExcludeArea();
					}
				}
			}else if(command.equals("excludeDelete")){
				int c = excludePatterns.size();
				if(c>0){
					excludePatterns.removeElementAt(c-1);
 					refreshExcludeArea();
				}
			}else if(command.equals("Define Joined Label")){
					NolJoinedLabel labelDialog = new NolJoinedLabel(
							frame, "Input Joined Label", labels);
					labelDialog.setBounds(100,100,400,250);
					labelDialog.setVisible(true);
					if(labelDialog.getResult()){
						addToMultiList(labelDialog.getJoindLabel());
					}
			}else if(command.equals("Delete Joined Label")){
				if(multilabelList.isSelectionEmpty()){
					return;
				}
				int index = multilabelList.getSelectedIndex();
				deleteFromMultiList(index);
			}else if(e.getSource().equals(preprocessorName)){
				if(preprocessorName.getText().equals("")){
					frame.showOKDialog(frame.getNolResourceString(NONAMEFORPREPROCESSOR));
				}
			}
		}

		@Override
		public void valueChanged(ListSelectionEvent e){
			if(e.getSource().equals(singleLabelList)){
				isSingle = true;
				multilabelList.clearSelection();
			}else if(e.getSource().equals(multilabelList)){
				isSingle = false;
				singleLabelList.clearSelection();
			}
		}

		@Override
		public void itemStateChanged(ItemEvent e){
//System.out.println("select change");			
		}
	}
	
	public Vector getResamplers(){
		return resamplers;
	}
}
