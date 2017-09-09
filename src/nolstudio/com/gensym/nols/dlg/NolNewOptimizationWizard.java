package com.gensym.nols.dlg;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.net.URL;

import javax.swing.table.*;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.border.*;

import com.gensym.nols.data.*;
import com.gensym.nols.main.*;

import com.gensym.DEBUG;

public class NolNewOptimizationWizard  extends NolWizardDialog{
	private JTextField optimizationName;
	private JTextArea optimizationDescript;
	private JTextField modelName;
	private JList modelList;
	private JLabel preprocessorName;
	private DefaultListModel modelListModel;
	private int digits = 5;

 	private	TargetTableModel targetTableModel;
	private	JTable targetTableView;

 	private	PenaltyTableModel penaltyTableModel;
	private	JTable penaltyTableView;

	private NolMainFrame frame;
	private boolean noFire;
	private NolOptimizeModel model;
	private NolOptimization optimization;
	private ControlAction actListener;
	
	private static final String GENERAL_LABEL = "NewOptimizationWizard_GeneralLabel";
    private static final String NAMEEDITLABEL = "NewOptimizationWizard_NameEditLabel";
	private static final String COMMA_LABEL = "CommentLabel";
	private static final String MODEL_LABEL = "NewOptimizationWizard_ModelLabel";
	private static final String MODEL = "NewOptimizationWizard_Model";
	private static final String PREPROCESSOR = "NewOptimizationWizard_Preprocessor";
	private static final String AVAILABLEMODELS = "NewOptimizationWizard_AvailableModels";
	private static final String WEIGHT_LABEL = "NewOptimizationWizard_WeightLabel";
	private static final String BOUND_LABEL = "NewOptimizationWizard_BoundLabel";
	private static final String VARIABLE = "NewOptimizationWizard_Variable";
	private static final String LINEARWEIGHT = "NewOptimizationWizard_LinearWeight";
	private static final String SETPOINTWEIGHT = "NewOptimizationWizard_SetpointWeight";
	private static final String SLBWEIGHT = "NewOptimizationWizard_SLBWeight";
	private static final String SUBWEIGHT = "NewOptimizationWizard_SUBWeight";
	private static final String NONAMEFORTHISOPTIMIZATION = "NewOptimizationWizard_NoNameForThisOptimization";

	

	public NolNewOptimizationWizard (NolMainFrame frame) {
		super((JFrame)frame, "", true, 4);
		this.frame = frame;
		actListener = new ControlAction(); 
		noFire = false;
		initializeLayout();
	}

	private void initializeLayout(){
		stepPanes.setElementAt(getGeneralPanel(),0);
		stepPanes.setElementAt(getModelPanel(),1);
		stepPanes.setElementAt(getWeightPane(),2);
		stepPanes.setElementAt(getBoundsPane(),3);
	}

	private JPanel getGeneralPanel(){
		JPanel genPane = new JPanel(new BorderLayout());
		URL url = this.getClass().getResource("largeOptimizer.gif");
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
		namePane.add(new JLabel(frame.getNolResourceString(NAMEEDITLABEL)));
		optimizationName = new JTextField();
		optimizationName.addActionListener(actListener);
		namePane.add(optimizationName);

		cenPane.add("North",namePane);

		JPanel descripPane = new JPanel(new GridLayout());
		descripPane.setBorder(new TitledBorder(new EmptyBorder(10, 5, 25, 5),               
			frame.getNolResourceString(COMMA_LABEL)+":", TitledBorder.LEFT , TitledBorder.TOP));

		optimizationDescript = new JTextArea();
		JScrollPane listScrollPane = new JScrollPane(optimizationDescript);
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
		sourcePane.add(modelName);
		sourcePane.add(new JLabel(frame.getNolResourceString(PREPROCESSOR)+":"));
		preprocessorName = new JLabel();
		sourcePane.add(preprocessorName);

 		cenPane.add("North",sourcePane);

		JPanel listPane = new JPanel(new BorderLayout());
		modelList = new JList(getModelListModel());
		modelList.setBackground(Color.white);
		modelList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		modelList.addListSelectionListener(actListener);
		JScrollPane listScrollPane = new JScrollPane(modelList);
		listScrollPane.setBorder(BorderFactory.createLoweredBevelBorder());
		listScrollPane.setPreferredSize(NolMainFrame.vpad50);
		listPane.add("North",new JLabel(frame.getNolResourceString(AVAILABLEMODELS)+":"));
		listPane.add("Center",listScrollPane);

  		cenPane.add("Center",listPane);

		modelPane.add("Center",cenPane);
		
		return modelPane;
	}
	
	private JPanel getWeightPane(){
		URL url = this.getClass().getResource("objective.gif");
		ImageIcon functionImage = new ImageIcon(url);

		JPanel outputPane = new JPanel(new BorderLayout());
		JPanel infoPane = new JPanel(new BorderLayout());
 		infoPane.setBorder(new EmptyBorder(10,10,10,10));
		String s = frame.getNolResourceString(WEIGHT_LABEL);
		JTextArea infoLabel = new JTextArea(s);
		infoLabel.setEditable(false);
		infoLabel.setLineWrap(true);
		infoLabel.setWrapStyleWord(true);
		infoLabel.setBackground(infoPane.getBackground());
		infoPane.add("North",infoLabel);
		infoPane.add("South",new JLabel(functionImage));
 		outputPane.add("North",infoPane);



		JPanel cenPane = new JPanel(new GridLayout());
 		cenPane.setBorder(new EmptyBorder(10,10,10,10));

		targetTableModel = new TargetTableModel();
		targetTableView = new JTable(targetTableModel);
		targetTableView.setSelectionMode(0);
		targetTableView.setCellSelectionEnabled(true);
		JScrollPane listScrollPane = new JScrollPane(targetTableView);
		listScrollPane.setBackground(Color.white);
		cenPane.add(listScrollPane);

		outputPane.add("Center",cenPane);
		
		return outputPane; 
	}
	
	private JPanel getBoundsPane(){
		URL url = this.getClass().getResource("objective.gif");
		ImageIcon functionImage = new ImageIcon(url);

		JPanel penPane = new JPanel(new BorderLayout());
		JPanel infoPane = new JPanel(new BorderLayout());
 		infoPane.setBorder(new EmptyBorder(10,10,10,10));
		String s = frame.getNolResourceString(BOUND_LABEL);
		JTextArea infoLabel = new JTextArea(s);
		infoLabel.setEditable(false);
		infoLabel.setLineWrap(true);
		infoLabel.setWrapStyleWord(true);
		infoLabel.setBackground(infoPane.getBackground());
		infoPane.add("North",infoLabel);
		infoPane.add("South",new JLabel(functionImage));
		penPane.add("North",infoPane);

		JPanel cenPane = new JPanel(new GridLayout());
 		cenPane.setBorder(new EmptyBorder(10,10,10,10));

		penaltyTableModel = new PenaltyTableModel();
		penaltyTableView = new JTable(penaltyTableModel);
		penaltyTableView.setSelectionMode(0);
		penaltyTableView.setCellSelectionEnabled(true);
		JScrollPane listScrollPane = new JScrollPane(penaltyTableView);
		listScrollPane.setBackground(Color.white);
		cenPane.add(listScrollPane);

		penPane.add("Center",cenPane);
		
		return penPane; 
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
		optimizationDescript.setText("");
	}

	private void refreshVarTableView(){
		if(model == null){
			return;
		}
		Vector outputs = model.getOutputs();
		Vector states = model.getState();
		Vector manis = model.getManipulate();
		Vector varNames = new Vector();
		Vector targetWeights = new Vector();
		Vector penaltyWeights = new Vector();
		for(int i=0;i<outputs.size();i++){
			varNames.addElement(outputs.elementAt(i));
			double[] tw = new double[2];
			tw[1] = 1.0;
			targetWeights.addElement(tw);
			double[] pw = new double[2];
			penaltyWeights.addElement(pw);
		}
		for(int i=0;i<states.size();i++){
			varNames.addElement(states.elementAt(i));	
			double[] tw = new double[2];
			targetWeights.addElement(tw);
			double[] pw = new double[2];
			penaltyWeights.addElement(pw);
		}
		for(int i=0;i<manis.size();i++){
			varNames.addElement(manis.elementAt(i));	
			double[] tw = new double[2];
			targetWeights.addElement(tw);
			double[] pw = new double[2];
			penaltyWeights.addElement(pw);
		}
		targetTableModel.setContents(varNames,targetWeights);
		penaltyTableModel.setContents(varNames,penaltyWeights);
		
		targetTableView.validate();
		targetTableView.repaint(0l);
		penaltyTableView.validate();
		penaltyTableView.repaint(0l);
	}

	private void initDataDisplay(){
		Project project = frame.getProject();
		int count = 1;
		while(true){
			String oName = "Optimization"+count;
			if(project.getOptimizationIndexByName(oName) == -1){
				optimizationName.setText(oName);
				break;
			}
			count++;
		}
		Vector omodels  = project.getOptimizationModels();
		getModelListModel().removeAllElements();
		for(int i=0;i<omodels.size();i++){
			NolOptimizeModel model1 =(NolOptimizeModel)omodels.elementAt(i);
			String n = model1.getName();
			getModelListModel().addElement(n);
		}

		noFire = true;
		model =(NolOptimizeModel)omodels.elementAt(0);
		refreshVarTableView();
		modelName.setText(model.getName());
		preprocessorName.setText(model.getPreprocessor().getName());
		noFire = false;

	}

	@Override
	protected void modifyStep(boolean isNext){
		super.modifyStep(isNext);
		String title = "Create New Optimization - "+setTitleForStep(currentStep);
		if(currentStep == 1){
			title = title + " - General";
		}else if(currentStep == 2){
			if(isNext){
				if(optimizationName.getText().equals("")){
					frame.showOKDialog(frame.getNolResourceString(NONAMEFORTHISOPTIMIZATION));
					super.modifyStep(false);
					finishButton.setEnabled(false);
				}
			}
			title = title + " - Model";
		}else if(currentStep == 3){
			title = title + " - Target Weight";
		}else if(currentStep == 4){
			title = title + " - Bound Weight";
		}
		if(DEBUG.debugFlag){
			System.out.println(title);
		}
		setTitle(title);
	}

	public NolOptimization getOptimization(){
		if(optimization ==null){
			return null;
		}
		return optimization;
	}

	@Override
	protected boolean finishAction(){
		Project project = frame.getProject();
		optimization = new NolOptimization(project,optimizationName.getText());
		optimization.setComment(optimizationDescript.getText());
		optimization.setModel(model);
		project.addOptimization(optimization);
		Vector varObjs = targetTableModel.getNames();
		Vector tw = targetTableModel.getWeights();
		Vector pw = penaltyTableModel.getWeights();
		for(int i=0;i<varObjs.size();i++){
			double[] ww = new double[4];
			double[] twd = (double[])tw.elementAt(i);
			double[] pwd = (double[])pw.elementAt(i);
			ww[0] = twd[0];
			ww[1] = twd[1];
			ww[2] = pwd[0];
			ww[3] = pwd[1];
			optimization.putWeights(varObjs.elementAt(i),ww);
		}
		return true;
	}

 	class ControlAction extends AbstractAction implements ListSelectionListener {
		ControlAction() { super("controlAction");}
        @Override
		public void actionPerformed(ActionEvent e) {
			String command = e.getActionCommand();			
			if(e.getSource().equals(optimizationName)){
				if(optimizationName.getText().equals("")){
					frame.showOKDialog(frame.getNolResourceString(NONAMEFORTHISOPTIMIZATION));
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
			if(e.getSource().equals(modelList)){
 				noFire = true;
				int mindex = modelList.getSelectedIndex();
				if(mindex == -1){
					noFire = false;
					return;
				}
				Project project = frame.getProject();
				String mName = (String)getModelListModel().elementAt(mindex);
				int oindex = project.getOptimizationModelIndexByName(mName);
				if(oindex == -1){
					noFire = false;
					return;
				}
				model =  project.getOptimizationModel(oindex);
				refreshVarTableView();
				modelName.setText(mName);
				preprocessorName.setText(model.getPreprocessor().getName());
				noFire = false;
			}
		}
	}

	class TargetTableModel extends AbstractTableModel{
		private int row,col;
		private Vector names;
		private Vector weights;
		private String[] colHd = {frame.getNolResourceString(VARIABLE),
			frame.getNolResourceString(LINEARWEIGHT),
			frame.getNolResourceString(SETPOINTWEIGHT)};

//		private String[] colHd = {"Variable","Linear Weight(W0)","Setpoint Weight(W1)"};
		public TargetTableModel(){
			row = 0;
			col = 3;
			names = new Vector();
		}
		public void setContents(Vector names, Vector weights){
			this.names = names;
			this.weights = weights;
			row = names.size();
		}
		@Override
		public int getColumnCount() { return col; }
		@Override
		public int getRowCount() { return row;}
		@Override
		public Object getValueAt(int r, int c){
			if(c == 0){
				return names.elementAt(r).toString();
			}else if(c == 1){
				double[] w = (double[])weights.elementAt(r);
				return String.valueOf(w[0]);
			}else if(c == 2){
				double[] w = (double[])weights.elementAt(r);
				return String.valueOf(w[1]);
			}
			return "";
		}
		@Override
		public String getColumnName(int c) {
			return colHd[c];
		}
		@Override
		public boolean isCellEditable(int r, int c) {
			if(c==1||c==2){
				return true;
			}
			return false;
		}		
		@Override
		public void setValueAt(Object aValue, int r, int c) {
			if(c==1){
				try{
					double v = Double.valueOf((String)aValue).doubleValue();
					double[] w = (double[])weights.elementAt(r);
					w[0] = v;
				}catch( NumberFormatException evt){
					System.err.println("Non-Fatal exception: " + evt.getMessage());
					evt.printStackTrace();
				}
			}else if(c==2){
				try{
					double v = Double.valueOf((String)aValue).doubleValue();
					double[] w = (double[])weights.elementAt(r);
					w[1] = v;
				}catch( NumberFormatException evt){
					System.err.println("Non-Fatal exception: " + evt.getMessage());
					evt.printStackTrace();
				}
			}
		}
		public Vector getNames(){
			return names;
		}
		public Vector getWeights(){
			return weights;
		}
	}

	class PenaltyTableModel extends AbstractTableModel{
		private int row,col;
		private Vector names, weights;
		private String[] colHd = {frame.getNolResourceString(VARIABLE),
			frame.getNolResourceString(SLBWEIGHT),
			frame.getNolResourceString(SUBWEIGHT)};
//		private String[] colHd = {"Variable","SLB Weight(W2)","SUB Weight(W3)"};
		public PenaltyTableModel(){
			row = 0;
			col = 3;
			names = new Vector();
		}
		public void setContents(Vector names, Vector weights){
			this.names = names;
			this.weights = weights;
			row = names.size();
		}
		@Override
		public int getColumnCount() { return col; }
		@Override
		public int getRowCount() { return row;}
		@Override
		public Object getValueAt(int r, int c){
			if(c == 0){
				return names.elementAt(r).toString();
			}else if(c == 1){
				double[] w = (double[])weights.elementAt(r);
				return String.valueOf(w[0]);
			}else if(c == 2){
				double[] w = (double[])weights.elementAt(r);
				return String.valueOf(w[1]);
			}
			return "";
		}
		@Override
		public String getColumnName(int c) {
			return colHd[c];
		}
		@Override
		public boolean isCellEditable(int r, int c) {
			if(c==1||c==2){
				return true;
			}
			return false;
		}		
		@Override
		public void setValueAt(Object aValue, int r, int c) {
			if(c==1){
				try{
					double v = Double.valueOf((String)aValue).doubleValue();
					double[] w = (double[])weights.elementAt(r);
					w[0] = v;
				}catch( NumberFormatException evt){
					System.err.println("Non-Fatal exception: " + evt.getMessage());
					evt.printStackTrace();
				}
			}else if(c==2){
				try{
					double v = Double.valueOf((String)aValue).doubleValue();
					double[] w = (double[])weights.elementAt(r);
					w[1] = v;
				}catch( NumberFormatException evt){
					System.err.println("Non-Fatal exception: " + evt.getMessage());
					evt.printStackTrace();
				}
			}
		}
		public Vector getNames(){
			return names;
		}
		public Vector getWeights(){
			return weights;
		}
	}

}
