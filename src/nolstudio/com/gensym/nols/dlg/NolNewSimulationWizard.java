package com.gensym.nols.dlg;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.net.URL;

import javax.swing.table.*;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.border.*;

import com.gensym.math.Utilities;

import com.gensym.nols.data.*;
import com.gensym.nols.main.*;

import com.gensym.DEBUG;

public class NolNewSimulationWizard  extends NolWizardDialog{
	private JTextField simulationName;
	private JTextArea simulationDescript;
	private JTextField modelName;
	private JTextField numberOfPoint;
	private JRadioButton dynamicRadio;
	private JList modelList;
	private DefaultListModel modelListModel;
	private int digits = 5;


 	private	VarTableModel varTableModel;
	private	JTable varTableView;

	private NolMainFrame frame;
	private boolean noFire;
	private int modelType;
	private int modelIndex;
	private int numberOfPointValue;
	private ControlAction actListener;
	private ResponseSurfaceSimulation simulation;
	
	private static final String GENERAL_LABEL = "NewSimulationWizard_GeneralLabel";
	private static final String COMMENT_LABEL = "CommentLabel";
	private static final String NAMEEDITLABEL = "NewSimulationWizard_NameEditLabel";
	private static final String MODEL_LABEL = "NewSimulationWizard_ModelLabel";
	private static final String MODEL = "NewSimulationWizard_Model";
	private static final String SETTING_LABEL = "NewSimulationWizard_Label";
	private static final String NUMBEROFPOINTS = "NewSimulationWizard_NumberOfPoints";
	private static final String VARIABLE = "NewSimulationWizard_Variable";
	private static final String START = "NewSimulationWizard_Start";
	private static final String END = "NewSimulationWizard_End";

	private static final String MODELNOTTRAINED = "NewSimulationWizard_ModelNotTrained";
	private static final String NONAMEFORTHISSIMULATION = "NewSimulationWizard_NoNameForThisSimulation";
	
	
	
	public NolNewSimulationWizard (NolMainFrame frame) {
		super((JFrame)frame, "", true, 3);
		this.frame = frame;
		actListener = new ControlAction(); 
		modelType = -1;
		modelIndex = -1;
		numberOfPointValue = 10;
		noFire = false;
		initializeLayout();
	}

	private void initializeLayout(){
		stepPanes.setElementAt(getGeneralPanel(),0);
		stepPanes.setElementAt(getModelPanel(),1);
		stepPanes.setElementAt(getSettingPanel(),2);
	}

	private JPanel getGeneralPanel(){
		JPanel genPane = new JPanel(new BorderLayout());
		URL url = this.getClass().getResource("largeSimulation.gif");
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

		JPanel namePane = new JPanel(new GridLayout(2,1,10,5));
 		namePane.setBorder(new EmptyBorder(10,10,10,10));
		namePane.add(new JLabel(frame.getNolResourceString(NAMEEDITLABEL)+":"));
		simulationName = new JTextField();
		simulationName.addActionListener(actListener);
		namePane.add(simulationName);

		cenPane.add("North",namePane);

		JPanel descripPane = new JPanel(new GridLayout());
		descripPane.setBorder(new TitledBorder(new EmptyBorder(10, 5, 25, 5),               
			frame.getNolResourceString(COMMENT_LABEL)+":", TitledBorder.LEFT , TitledBorder.TOP));

		simulationDescript = new JTextArea();
		JScrollPane listScrollPane = new JScrollPane(simulationDescript);
		listScrollPane.setBorder(BorderFactory.createLoweredBevelBorder());
		descripPane.add(listScrollPane);

		cenPane.add("Center",descripPane);

 		genPane.add("Center",cenPane);
		return genPane;
	}

	private JPanel getModelPanel(){
		JPanel modelPane = new JPanel(new BorderLayout());
		JPanel infoPane = new JPanel(new GridLayout());
 		infoPane.setBorder(new EmptyBorder(10,10,10,10));
		String s = frame.getNolResourceString(MODEL_LABEL);
		JTextArea infoLabel = new JTextArea(s);
		infoLabel.setEditable(false);
		infoLabel.setLineWrap(true);
		infoLabel.setWrapStyleWord(true);
		infoLabel.setBackground(infoPane.getBackground());
		infoPane.add(infoLabel);
		modelPane.add("North",infoPane);

		JPanel cenPane = new JPanel(new BorderLayout());
 		cenPane.setBorder(new EmptyBorder(10,10,10,10));

		JPanel sourcePane = new JPanel(new GridLayout(1,2,20,20));
 		sourcePane.setBorder(new EmptyBorder(0,0,10,0));
		sourcePane.add(new JLabel(frame.getNolResourceString(MODEL)+":"));
		modelName = new JTextField();
		modelName.setEditable(false);
		modelName.addActionListener(actListener);
		sourcePane.add(modelName);

 		cenPane.add("North",sourcePane);

		JPanel listPane = new JPanel(new GridLayout());
		modelList = new JList(getModelListModel());
		modelList.setBackground(Color.white);
		modelList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		modelList.addListSelectionListener(actListener);
		JScrollPane listScrollPane = new JScrollPane(modelList);
		listScrollPane.setBorder(BorderFactory.createLoweredBevelBorder());
		listScrollPane.setPreferredSize(NolMainFrame.vpad50);
		listPane.add(listScrollPane);
  		cenPane.add("Center",listPane);
		modelPane.add("Center",cenPane);		
		return modelPane;
	}	
	
	private JPanel getSettingPanel(){
		JPanel setPane1 = new JPanel(new BorderLayout());
		JPanel infoPane = new JPanel(new GridLayout());
 		infoPane.setBorder(new EmptyBorder(10,10,10,10));
		String s = frame.getNolResourceString(SETTING_LABEL);
		JTextArea infoLabel = new JTextArea(s);
		infoLabel.setEditable(false);
		infoLabel.setLineWrap(true);
		infoLabel.setWrapStyleWord(true);
		infoLabel.setBackground(infoPane.getBackground());
		infoPane.add(infoLabel);
		setPane1.add("North",infoPane);

		JPanel cenPane = new JPanel(new BorderLayout());
 		cenPane.setBorder(new EmptyBorder(10,10,10,10));

		JPanel sourcePane = new JPanel(new GridLayout(1,2,20,20));
 		sourcePane.setBorder(new EmptyBorder(0,0,10,0));
		sourcePane.add(new JLabel(frame.getNolResourceString(NUMBEROFPOINTS)+":"));
		numberOfPoint = new JTextField();
		numberOfPoint.addActionListener(actListener);
		sourcePane.add(numberOfPoint);

 		cenPane.add("North",sourcePane);

		JPanel varPane = new JPanel(new GridLayout());
		varTableModel = new VarTableModel();
		varTableView = new JTable(varTableModel);
		varTableView.setSelectionMode(0);
		varTableView.setCellSelectionEnabled(true);
		JScrollPane listScrollPane = new JScrollPane(varTableView);
		listScrollPane.setBackground(Color.white);
		varPane.add(listScrollPane);
  		cenPane.add("Center",varPane);
		setPane1.add("Center",cenPane);
		return setPane1;
	}

	private DefaultListModel getModelListModel() {
		if (modelListModel == null) {
			modelListModel = new DefaultListModel();
		}	
		return modelListModel;
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
		simulationDescript.setText("");
		varTableView.validate();
		varTableView.repaint(0l);
	}

	private void initDataDisplay(){
		Project2 project = frame.getProject();
		int count = 1;
		while(true){
			String sName = "Simulation"+count;
			if(project.getSimulationIndexByName(sName) == -1){
				simulationName.setText(sName);
				break;
			}
			count++;
		}
		getModelListModel().removeAllElements();
		Vector pmodels  = project.getPredictiveModels();
		for(int i=0;i<pmodels.size();i++){
			getModelListModel().addElement(((NolModel2)pmodels.elementAt(i)).getName());
		}
		Vector omodels  = project.getOptimizationModels();
		for(int i=0;i<omodels.size();i++){
			getModelListModel().addElement(((NolModel2)omodels.elementAt(i)).getName());
		}
		Vector bmodels  = project.getBpnModels();
		for(int i=0;i<bmodels.size();i++){
			getModelListModel().addElement(((NolModel2)bmodels.elementAt(i)).getName());
		}
		Vector amodels  = project.getAnnModels();
		for(int i=0;i<amodels.size();i++){
			getModelListModel().addElement(((NolModel2)amodels.elementAt(i)).getName());
		}
		Vector rmodels  = project.getRbfnModels();
		for(int i=0;i<rmodels.size();i++){
			getModelListModel().addElement(((NolModel2)rmodels.elementAt(i)).getName());
		}
		if(!pmodels.isEmpty()){
			modelType = 0;
			modelIndex = 0;
		}else if(!omodels.isEmpty()){
			modelType = 1;
			modelIndex = 0;
		}else if(!bmodels.isEmpty()){
			modelType = 2;
			modelIndex = 0;
		}else if(!amodels.isEmpty()){
			modelType = 3;
			modelIndex = 0;
		}else if(!rmodels.isEmpty()){
			modelType = 4;
			modelIndex = 0;
		}
		if(!getModelListModel().isEmpty()){
			refreshVarTableView();
			modelName.setText(getModelListModel().elementAt(0).toString());
		}else{
			modelName.setText("");
			varTableModel.setNames(new Vector(),new Vector(),new Vector());
		}
		numberOfPointValue = 10;
		numberOfPoint.setText(String.valueOf(numberOfPointValue));
	}

	private void refreshVarTableView(){
		Project2 project = frame.getProject();
		Vector names = new Vector();
		Vector mins = new Vector();
		Vector maxs = new Vector();
		if(modelType == 0){
			NolModel2 model = (NolModel2)project.getPredictiveModels().elementAt(modelIndex);
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
						Variable colObj = prep.getVariableFromVariableName(varName);
						double[] statistic = colObj.getStatistics();						
						names.addElement(colObj.getName());
						mins.addElement(Utilities.formatDouble(statistic[0], digits));
						maxs.addElement(Utilities.formatDouble(statistic[0], digits));
						break;
					}
				}
			}
			for(int i=0;i<inputs.size();i++){
				String varName = (String)inputs.elementAt(i);
				Variable colObj = prep.getVariableFromVariableName(varName);
				double[] statistic = colObj.getStatistics();
				names.addElement(colObj.getName());
				mins.addElement(Utilities.formatDouble(statistic[0], digits));
				maxs.addElement(Utilities.formatDouble(statistic[0], digits));
			}
			varTableModel.setNames(names,mins,maxs);
			varTableView.setModel(varTableModel);
			varTableView.validate();
			varTableView.repaint(0l);
		}else if(modelType == 1){
			NolOptimizeModel model = (NolOptimizeModel)project.getOptimizationModels().elementAt(modelIndex);
			Vector manis = model.getManipulate();
			Vector exogs = model.getExogenous();
			Preprocessor prep = model.getPreprocessor();
			for(int i=0;i<manis.size();i++){
				String varName = (String)manis.elementAt(i);
				Variable colObj = prep.getVariableFromVariableName(varName);
				double[] statistic = colObj.getStatistics();						
				names.addElement(colObj.getName());
				mins.addElement(Utilities.formatDouble(statistic[0], digits));
				maxs.addElement(Utilities.formatDouble(statistic[0], digits));
			}
			for(int i=0;i<exogs.size();i++){
				String varName = (String)exogs.elementAt(i);
				Variable colObj = prep.getVariableFromVariableName(varName);
				double[] statistic = colObj.getStatistics();
				names.addElement(colObj.getName());
				mins.addElement(Utilities.formatDouble(statistic[0], digits));
				maxs.addElement(Utilities.formatDouble(statistic[0], digits));
			}
			varTableModel.setNames(names,mins,maxs);
			varTableView.setModel(varTableModel);
			varTableView.validate();
			varTableView.repaint(0l);
		}else if(modelType == 2 || modelType == 3 || modelType == 4){
			NolModel2 model = null;
			if(modelType == 2){
				model = (NolModel2)project.getBpnModels().elementAt(modelIndex);
			}else if(modelType == 3){
				model = (NolModel2)project.getAnnModels().elementAt(modelIndex);
			}else if(modelType == 4){
				model = (NolModel2)project.getRbfnModels().elementAt(modelIndex);
			}
			Vector outputs = model.getOutputs();
			Vector inputs = model.getInputs();
			Preprocessor prep = model.getPreprocessor();
			for(int i=0;i<inputs.size();i++){
				String varName = (String)inputs.elementAt(i);
				Variable colObj = prep.getVariableFromVariableName(varName);
				double[] statistic = colObj.getStatistics();
				names.addElement(colObj.getName());
				mins.addElement(Utilities.formatDouble(statistic[0], digits));
				maxs.addElement(Utilities.formatDouble(statistic[0], digits));
			}
			varTableModel.setNames(names,mins,maxs);
			varTableView.setModel(varTableModel);
			varTableView.validate();
			varTableView.repaint(0l);
		}
	}


	@Override
	protected void modifyStep(boolean isNext){
		super.modifyStep(isNext);
		String title = "Create New Simulation - "+setTitleForStep(currentStep);
		if(currentStep == 1){
			title = title + " - General";
		}else if(currentStep == 2){
			if(isNext){
				if(simulationName.getText().equals("")){
					frame.showOKDialog(frame.getNolResourceString(NONAMEFORTHISSIMULATION));
					super.modifyStep(false);
					finishButton.setEnabled(false);
				}
			}
			title = title + " - Model";
		}else if(currentStep == 3){
			title = title + " - Setting";
			varTableView.requestFocus();
		}
		if(DEBUG.debugFlag){
			System.out.println(title);
		}
		setTitle(title);
	}

	public ResponseSurfaceSimulation getSimulation(){
		if(simulation != null)
			return simulation;
		return null;

	}

	@Override
	protected boolean finishAction(){
		Project2 project = frame.getProject();
		NolModel2 model = null;
		if(modelType == 0){
			model = (NolModel2)project.getPredictiveModels().elementAt(modelIndex);
		}else if(modelType == 1){
			model = (NolOptimizeModel)project.getOptimizationModels().elementAt(modelIndex);
		}else if(modelType == 2){
			model = (NolModel2)project.getBpnModels().elementAt(modelIndex);
		}else if(modelType == 3){
			model = (NolModel2)project.getAnnModels().elementAt(modelIndex);
		}else if(modelType == 4){
			model = (NolModel2)project.getRbfnModels().elementAt(modelIndex);
		}
		try {
			simulation = new ResponseSurfaceSimulation(project,model);
		} catch (Exception e) {
			System.err.println("Exception: "+e.getMessage());
			e.printStackTrace();
			return false;
		}
		Vector names = varTableModel.getNames();
		Vector min = varTableModel.getMin();
		Vector max = varTableModel.getMax();
		for(int i=0;i<names.size();i++){
			String varName = (String)names.elementAt(i);
			double minValue = Double.valueOf((String)min.elementAt(i)).doubleValue();
			double maxValue = Double.valueOf((String)max.elementAt(i)).doubleValue();
			simulation.setMinMax(varName,minValue,maxValue);	//-1 meams delay for optimization model.
		}
		simulation.setName(simulationName.getText());
		try{
			int v = Integer.valueOf(numberOfPoint.getText()).intValue();
			numberOfPointValue = v;
		}catch( NumberFormatException evt){
			System.err.println("Non-Fatal exception: " + evt.getMessage());
			evt.printStackTrace();
		}
		simulation.setNumberOfPoints(numberOfPointValue);
		simulation.setComment(simulationDescript.getText());
		if(model.isTrained()){
			System.out.println("calulationSimulation");
			simulation.calulationSimulation();
		}else{
			frame.showOKDialog(frame.getNolResourceString(MODELNOTTRAINED));
		}
		if(DEBUG.debugFlag){
			System.out.println("calulationSimulation");
		}
		project.addSimulation(simulation);
		return true;
	}

 	class ControlAction extends AbstractAction implements ListSelectionListener {
		ControlAction() { super("controlAction");}
        @Override
		public void actionPerformed(ActionEvent e) {
			String command = e.getActionCommand();
			if(e.getSource().equals(numberOfPoint)){
				try{
					int v = Integer.valueOf(numberOfPoint.getText()).intValue();
					numberOfPointValue = v;
				}catch( NumberFormatException evt){
					System.err.println("Non-Fatal exception: " + evt.getMessage());
					evt.printStackTrace();
				}
			}else if(e.getSource().equals(simulationName)){
				if(simulationName.getText().equals("")){
					frame.showOKDialog(frame.getNolResourceString(NONAMEFORTHISSIMULATION));
				}
			}

			
		}
		@Override
		public void valueChanged(ListSelectionEvent e){
			if(!e.getValueIsAdjusting()) {
				return;
			}
			if(noFire){
				return;
			}
			if(e.getSource().equals(modelList)){
				noFire = true;
				int mindex = modelList.getSelectedIndex();
				if(mindex == -1){
					noFire = false;
					return;
				}
				Project2 project = frame.getProject();
				String mName = (String)getModelListModel().elementAt(mindex);
				int pindex = project.getPredictiveModelIndexByName(mName);
				int oindex = project.getOptimizationModelIndexByName(mName);
				int bindex = project.getBpnModelIndexByName(mName);
				int aindex = project.getAnnModelIndexByName(mName);
				int rindex = project.getRbfnModelIndexByName(mName);
				if(pindex != -1){
					modelType = 0;
					modelIndex = pindex;
				}else if(oindex != -1){
					modelType = 1;
					modelIndex = oindex;
				}else if(bindex != -1){
					modelType = 2;
					modelIndex = bindex;
				}else if(aindex != -1){
					modelType = 3;
					modelIndex = aindex;
				}else if(rindex != -1){
					modelType = 4;
					modelIndex = rindex;
				}
				refreshVarTableView();
				modelName.setText(mName);
				noFire = false;
			}
		}
	}

	class VarTableModel extends AbstractTableModel{
		private int row,col;
		private Vector names;
		private Vector min,max;
		private String[] colHd = {
			frame.getNolResourceString(VARIABLE),
			frame.getNolResourceString(START),
			frame.getNolResourceString(END)};
//		private String[] colHd = {"Variable","Start","End"};
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
			if(c==2 || c==1){
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
				}catch( NumberFormatException evt){
					System.err.println("Non-Fatal exception: " + evt.getMessage());
					evt.printStackTrace();
				}
			}else if(c == 2){
				try{
					double v = Double.valueOf((String)aValue).doubleValue();
					max.setElementAt(aValue,r);
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
