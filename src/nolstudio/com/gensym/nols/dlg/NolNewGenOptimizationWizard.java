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
//import com.gensym.gos.data.*;

public class NolNewGenOptimizationWizard  extends NolWizardDialog{
	private JTextField optimizationName;
	private JTextArea optimizationDescript;
	private JTextField modelName;
	private JList modelList;
	private DefaultListModel modelListModel;
	private int digits = 5;

 	private	ConstraintsTableModel constraintsTableModel;
	private	JTable constraintsTableView;

 	private	BoundsTableModel boundsTableModel;
	private	JTable boundsTableView;

 	private	DefineVarTableModel defineVarTableModel;
	private	JTable defineVarTableView;

	private JFrame frame;
	private boolean noFire;
	private ControlAction actListener;
	private NolSelectPanel modelSelectPanel;

	private NolGenOptimization optimization;
	private Objective objective;
	private Project2 projectManager;
	private JList availableList;
	private DefaultListModel availableListModel;
	private Vector totalAvailableVarNames;
	private Vector newDefinedVariableNames;
	private Vector usedVars;
	private Vector constraints;
	private JTextField newVarName;
	private JTextField constNumberField;
	private JTextArea objContentArea;
	private JCheckBox minBox;
	
	private static final String GENERAL_LABEL = "NolNewGenOptimizationWizard_GeneralLabel";
    private static final String NAMEEDITLABEL = "NolNewGenOptimizationWizard_NameEditLabel";
	private static final String COMMA_LABEL = "CommentLabel";
	private static final String MODELSELECT_LABEL = "NolNewGenOptimizationWizard_ModelSelectionLabel";
	private static final String MODEL = "NolNewGenOptimizationWizard_Model";
	private static final String VARIABLE_LABEL = "NolNewGenOptimizationWizard_VariableLabel";
	private static final String OBJECTIVE_LABEL = "NolNewGenOptimizationWizard_ObjectiveLabel";
	private static final String NOMODELSELECTED = "NolNewGenOptimizationWizard_NoModelSelected";
	private static final String INDEPENDENT = "NolNewGenOptimizationWizard_Independent";
	private static final String EXOGENOUS = "NolNewGenOptimizationWizard_Exogenous";
	

	private static final String AVAILABLEMODELS = "NolNewGenOptimizationWizard_AvailableModels";
	private static final String BOUND_LABEL = "NolNewGenOptimizationWizard_BoundLabel";
	private static final String VARIABLE = "NolNewGenOptimizationWizard_Variable";
	private static final String LINEARWEIGHT = "NolNewGenOptimizationWizard_LinearWeight";
	private static final String SETPOINTWEIGHT = "NolNewGenOptimizationWizard_SetpointWeight";
	private static final String LOWERBOUNDS = "NolNewGenOptimizationWizard_LB";
	private static final String UPPERBOUNDS = "NolNewGenOptimizationWizard_UB";
	private static final String INITIALVALUE = "NolNewGenOptimizationWizard_InitialValue";
	private static final String CONSTRAINTS_LABEL = "NolNewGenOptimizationWizard_ConstraintsLabel";
	private static final String CONSTRAINTS = "NolNewGenOptimizationWizard_Constraints";


	private static final String NONAMEFORTHISOPTIMIZATION = "NolNewGenOptimizationWizard_NoNameForThisOptimization";

  private Resource uiLabels = Resource.getBundle("com.gensym.nols.dlg.UILabels");


	public NolNewGenOptimizationWizard (JFrame frame) {
		super((JFrame)frame, "", true, 6);
		this.frame = frame;
		actListener = new ControlAction(); 
		totalAvailableVarNames = new Vector();
		newDefinedVariableNames = new Vector();
		usedVars = new Vector();
		constraints = new Vector();
		noFire = false;
		initializeLayout();
		projectManager = ((NolMainFrame)frame).getProject();

	}

	private void refresh(){
		Rectangle bounds = getBounds();
		setBounds(bounds.x,bounds.y,bounds.width+1,bounds.height+1);
		validate();
		repaint(0l);
		setBounds(bounds);
		validate();
		repaint(0l);
	}

	private void initializeLayout(){
		stepPanes.setElementAt(getGeneralPanel(),0);
		stepPanes.setElementAt(getModelPanel(),1);
		stepPanes.setElementAt(getVariablePane(),2);
		stepPanes.setElementAt(getBoundsPane(),3);
		stepPanes.setElementAt(getConstraintsPane(),4);
		stepPanes.setElementAt(getObjectivePanel(),5);
 	}

	private JPanel getGeneralPanel(){
		JPanel genPane = new JPanel(new BorderLayout());
		URL url = this.getClass().getResource("largeOptimizer.gif");
		ImageIcon importIcon = new ImageIcon(url);

		JPanel infoPane = new JPanel(new BorderLayout());
 		infoPane.setBorder(new EmptyBorder(10,10,10,10));

		String s = uiLabels.getString(GENERAL_LABEL);
		JTextArea infoLabel = new JTextArea(s);
		infoLabel.setBackground(infoPane.getBackground());
		infoLabel.setLineWrap(true);
		infoLabel.setEditable(false);
		infoPane.add("Center",infoLabel);
		infoPane.add("West",new JLabel(importIcon));

		genPane.add("North",infoPane);

		JPanel cenPane = new JPanel(new BorderLayout());

		JPanel namePane = new JPanel(new GridLayout(2,1,10,5));
 		namePane.setBorder(new EmptyBorder(10,10,10,10));
		namePane.add(new JLabel(uiLabels.getString(NAMEEDITLABEL)));
		optimizationName = new JTextField();
		optimizationName.addActionListener(actListener);
		namePane.add(optimizationName);

		cenPane.add("North",namePane);

		JPanel descripPane = new JPanel(new GridLayout());
		descripPane.setBorder(new TitledBorder(new EmptyBorder(10, 5, 25, 5),               
			uiLabels.getString(COMMA_LABEL)+":", TitledBorder.LEFT , TitledBorder.TOP));
		optimizationDescript = new JTextArea();
		JScrollPane listScrollPane = new JScrollPane(optimizationDescript);
		listScrollPane.setBorder(BorderFactory.createLoweredBevelBorder());
		descripPane.add(listScrollPane);
		optimizationDescript.setBorder(BorderFactory.createLoweredBevelBorder());

		cenPane.add("Center",descripPane);

 		genPane.add("Center",cenPane);
		return genPane;
	}

	private JPanel getModelPanel(){
		JPanel modelPane = new JPanel(new BorderLayout());
		JPanel infoPane = new JPanel(new GridLayout());
 		infoPane.setBorder(new EmptyBorder(10,10,10,10));
		String s = uiLabels.getString(MODELSELECT_LABEL);
		JTextArea infoLabel = new JTextArea(s);
		infoLabel.setBackground(infoPane.getBackground());
		infoLabel.setLineWrap(true);
		infoLabel.setEditable(false);
		infoPane.add(infoLabel);
		modelPane.add("North",infoPane);
		modelSelectPanel = new NolSelectPanel(uiLabels.getString(MODEL)+":");
		modelPane.add("Center",modelSelectPanel);
		return modelPane;
	}


	private JPanel getVariablePane(){
		JPanel penPane = new JPanel(new BorderLayout());

		JPanel infoPane = new JPanel(new GridLayout());
 		infoPane.setBorder(new EmptyBorder(10,10,10,10));
		String s = uiLabels.getString(VARIABLE_LABEL);
		JTextArea infoLabel = new JTextArea(s);
		infoLabel.setBackground(infoPane.getBackground());
		infoLabel.setLineWrap(true);
		infoLabel.setEditable(false);
		infoPane.add(infoLabel);

		penPane.add("North",infoPane);

		JPanel cenPane = new JPanel(new BorderLayout());
 		cenPane.setBorder(new EmptyBorder(10,10,10,10));
		
		JPanel definedListPane = new JPanel();
		definedListPane.setBorder(new TitledBorder(new EmptyBorder(1, 1, 1, 1),               
				"Defined Input Variables:", TitledBorder.LEFT , TitledBorder.TOP));
		definedListPane.setLayout(new GridLayout());

		defineVarTableModel = new DefineVarTableModel();
		defineVarTableView = new JTable(defineVarTableModel);
		defineVarTableView.setSelectionMode(0);
		defineVarTableView.setCellSelectionEnabled(true);
		defineVarTableView.setDefaultRenderer(AbstractButton.class, 
			new ClassifyRenderer());
		JScrollPane listScrollPane2 = new JScrollPane(defineVarTableView);
		listScrollPane2.setBackground(Color.white);
		definedListPane.add(listScrollPane2);
		cenPane.add("Center",definedListPane);

		
/*		JPanel availListPane = new JPanel();
		availListPane.setBorder(new TitledBorder(new EmptyBorder(1, 1, 1, 1),               
			"Available Variables:", TitledBorder.LEFT , TitledBorder.TOP));
		availListPane.setLayout(new GridLayout());
		availableListModel = new DefaultListModel(); 
		availableList = new JList(availableListModel);
		availableList.setBackground(Color.white);
		JScrollPane listScrollPane1 = new JScrollPane(availableList);
		listScrollPane1.setBorder(BorderFactory.createLoweredBevelBorder());
		availListPane.add(listScrollPane1);
		cenPane.add(availListPane);
  */
		JPanel actionPane = new JPanel(new BorderLayout());
		actionPane.setBorder(new TitledBorder(new EmptyBorder(1, 1, 1, 1),               
				"", TitledBorder.LEFT , TitledBorder.TOP));

		JPanel labelPane = new JPanel(new GridLayout(1,2,5,5));
		labelPane.setBorder(new TitledBorder(new EmptyBorder(1, 1, 1, 1),               
				"", TitledBorder.LEFT , TitledBorder.TOP));
		JLabel label1 = new JLabel("New Variable:");
		labelPane.add(label1);
		newVarName = new JTextField();
		labelPane.add(newVarName);
		actionPane.add("Center",labelPane);


		JPanel buttonPane = new JPanel(new GridLayout(1,2,5,5));
		buttonPane.setBorder(new TitledBorder(new EmptyBorder(1, 1, 1, 1),               
				"", TitledBorder.LEFT , TitledBorder.TOP));
		JButton addbut = new JButton("Add");
		addbut.setActionCommand(uiLabels.getString("AddLabel"));
		addbut.addActionListener(actListener);
		buttonPane.add(addbut);
		JButton removebut = new JButton(uiLabels.getString("RemoveLabel"));
		removebut.setActionCommand("Remove");
		removebut.addActionListener(actListener);
		buttonPane.add(removebut);
		actionPane.add("East",buttonPane);
		
		cenPane.add("South",actionPane);
		
		penPane.add("Center",cenPane);
		return penPane; 
	}
	

	
	private JPanel getBoundsPane(){
		JPanel boundPane = new JPanel(new BorderLayout());
		JPanel infoPane = new JPanel(new BorderLayout());
 		infoPane.setBorder(new EmptyBorder(10,10,10,10));
		String s = uiLabels.getString(BOUND_LABEL);
		JTextArea infoLabel = new JTextArea(s);
		infoLabel.setLineWrap(true);
		infoLabel.setEditable(false);
		infoLabel.setBackground(infoPane.getBackground());
		infoPane.add("North",infoLabel);
		boundPane.add("North",infoPane);

		JPanel cenPane = new JPanel(new GridLayout());
 		cenPane.setBorder(new EmptyBorder(10,10,10,10));

		boundsTableModel = new BoundsTableModel();
		boundsTableView = new JTable(boundsTableModel);
		boundsTableView.setSelectionMode(0);
		boundsTableView.setCellSelectionEnabled(true);
		JScrollPane listScrollPane = new JScrollPane(boundsTableView);
		listScrollPane.setBackground(Color.white);
		cenPane.add(listScrollPane);

		boundPane.add("Center",cenPane);
		
		return boundPane; 
	}
	
 	private JPanel getConstraintsPane(){
		JPanel constraintsPane = new JPanel(new BorderLayout());
		JPanel infoPane = new JPanel(new GridLayout());
 		infoPane.setBorder(new EmptyBorder(10,10,10,10));
		String s = uiLabels.getString(CONSTRAINTS_LABEL);
		JTextArea infoLabel = new JTextArea(s);
		infoLabel.setEditable(false);
		infoLabel.setBackground(infoPane.getBackground());
		infoPane.add(infoLabel);
		constraintsPane.add("North",infoPane);

		JPanel cenPane = new JPanel(new BorderLayout());
 		cenPane.setBorder(new EmptyBorder(10,10,10,10));

		JPanel numberPane = new JPanel(new GridLayout(1,2,5,5));
		numberPane.add(new JLabel("Enter the number of constraints:"));
		constNumberField	= new JTextField();
		constNumberField.addActionListener(actListener);
		numberPane.add(constNumberField);

  	JPanel conPane = new JPanel(new GridLayout());
		conPane.setBorder(BorderFactory.createTitledBorder(uiLabels.getString(CONSTRAINTS)+":"));

		constraintsTableModel = new ConstraintsTableModel();
		constraintsTableView = new JTable(constraintsTableModel);
		constraintsTableView.setSelectionMode(0);
		constraintsTableView.setCellSelectionEnabled(true);
		JScrollPane listScrollPane = new JScrollPane(constraintsTableView);
		listScrollPane.setBackground(Color.white);
		conPane.add(listScrollPane);


		cenPane.add("North",numberPane);
		cenPane.add("Center",conPane);
		constraintsPane.add("Center",cenPane);

		return constraintsPane;
	}
	
	private JPanel getObjectivePanel(){
		URL url = this.getClass().getResource("objective.gif");
		ImageIcon functionImage = new ImageIcon(url);

		JPanel objPane = new JPanel(new BorderLayout());
		JPanel infoPane = new JPanel(new BorderLayout());
 		infoPane.setBorder(new EmptyBorder(10,10,10,10));
		String s = uiLabels.getString(OBJECTIVE_LABEL);
		JTextArea infoLabel = new JTextArea(s);
		infoLabel.setBackground(infoPane.getBackground());
		infoLabel.setLineWrap(true);
		infoLabel.setEditable(false);
		infoPane.add("North",infoLabel);
		infoPane.add("South",new JLabel(functionImage));
 		objPane.add("North",infoPane);

		JPanel cenPane = new JPanel(new BorderLayout());
 		cenPane.setBorder(new EmptyBorder(10,10,10,10));

		JPanel checkPane = new JPanel(new GridLayout(1,2,5,5));
		checkPane.add(new JLabel("This is a minimization problem?"));
		minBox	= new JCheckBox();
		checkPane.add(minBox);

		JPanel conPane = new JPanel(new GridLayout());
		conPane.setBorder(BorderFactory.createTitledBorder("Contents:"));

		objContentArea = new JTextArea();
		JScrollPane listScrollPane = new JScrollPane(objContentArea);
		listScrollPane.setBackground(Color.white);
		conPane.add(listScrollPane);
		cenPane.add("North",checkPane);
		cenPane.add("Center",conPane);
		objPane.add("Center",cenPane);

		return objPane; 
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

		Vector contents	= (Vector)projectManager.getPredictiveModels().clone();
		Vector selected = new Vector();
		modelSelectPanel.setContents(contents,selected);
		minBox.setSelected(true);
		totalAvailableVarNames.removeAllElements();
		usedVars.removeAllElements();
		newDefinedVariableNames.removeAllElements();
		constraints.removeAllElements();
		noFire = false;
		refreshDefinedTable();
		refreshVarTableView();
	}

	private void refreshVarTableView(){
		boundsTableModel.setContents(usedVars);
	}

	private void refreshConstrTableView(int count){
		constraints.removeAllElements();
		for(int i=0;i<count;i++){
			Constraint con = new Constraint(i,"cstr"+i,"E",0.0);
			constraints.addElement(con);
		}
		constraintsTableModel.setContents(constraints);
		refresh();
	}

	private void initDataDisplay(){
		int count = 1;
		while(true){
			String oName = "Optimization"+count;
			if(projectManager.getOptimizationIndexByName(oName) == -1 && projectManager.getGenOptimizationIndexByName(oName) == -1){
				optimizationName.setText(oName);
				break;
			}
			count++;
		}
		objective = new Objective();
		objContentArea.setText(objective.getContent());
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
					super.modifyStep(false);
					((NolMainFrame)frame).showOKDialog(uiLabels.getString(NONAMEFORTHISOPTIMIZATION));
					finishButton.setEnabled(false);
					return;
				}
			}
			title = title + " - Model";
		}else if(currentStep == 3){
			setAvailableVarList();
			title = title + " - Variables";
		}else if(currentStep == 4){
			refreshVarTableView();
			title = title + " - Input Variable Bounds";
		}else if(currentStep == 5){
			title = title + " - Constraints";
		}else if(currentStep == 6){
			title = title + " - Objective Function";
		}
		setTitle(title);
	}


	private void setAvailableVarList(){
		int sdc = modelSelectPanel.getSelectedListModel().size();
		if(sdc == 0){
			((NolMainFrame)frame).showOKDialog(uiLabels.getString(NOMODELSELECTED));
			return;
		}
 		for(int i=0;i<sdc;i++){
			NolModel2 model = (NolModel2)modelSelectPanel.getSelectedListModel().elementAt(i); 
			Vector inputs = model.getInputs();
			Preprocessor prep = model.getPreprocessor();
			for(int j=0;j<inputs.size();j++){
				String name = (String)inputs.elementAt(j);
				if(!totalAvailableVarNames.contains(name)){
					totalAvailableVarNames.addElement(name);
					Variable var = prep.getVariableFromVariableName(name);
					usedVars.addElement(var);
				}
			}
		}
		refreshDefinedTable();

	}

	public NolGenOptimization getOptimization(){
		if(optimization ==null){
			return null;
		}
		return optimization;
	}

	@Override
	protected boolean finishAction(){
		optimization = new NolGenOptimization(projectManager, optimizationName.getText());

		optimization.setName(optimizationName.getText());
		optimization.setComment(optimizationDescript.getText());
		int sdc = modelSelectPanel.getSelectedListModel().size();
		Vector models  = new Vector(sdc);
		for(int i=0;i<sdc;i++){
			models.addElement(modelSelectPanel.getSelectedListModel().elementAt(i));
		}
		optimization.setModels(models);
		for(int i=0;i<constraints.size();i++){
			optimization.addConstraint((Constraint)constraints.elementAt(i));
		}
		objective.setContent(objContentArea.getText());
		optimization.setObjective(objective);
		Vector vars = defineVarTableModel.getNames();
		Vector indepchecks = defineVarTableModel.getIndepchecks();
		Vector indepVars = new Vector();
		Vector extraVars = new Vector();
		for(int i=0;i<vars.size();i++){
			JRadioButton check = (JRadioButton)indepchecks.elementAt(i);
			if(check.isSelected()){
				indepVars.addElement(vars.elementAt(i));
			}else{
				extraVars.addElement(vars.elementAt(i));
			}
		}
		optimization.setVariables(vars);
		boolean flag = minBox.isSelected();
		if(flag)
			optimization.setObjSen(1);
		else
			optimization.setObjSen(-1);

		projectManager.addGenOptimization(optimization);
		return true;
	}

	private void refreshDefinedTable(){
		defineVarTableModel.setContents(usedVars);
		System.out.println("# of vars ="+usedVars.size());
		refresh();
	}

 	class ControlAction extends AbstractAction implements ListSelectionListener {
		ControlAction() { super("controlAction");}
    @Override
    public void actionPerformed(ActionEvent e) {
			String command = e.getActionCommand();			
			if(e.getSource().equals(constNumberField)){
				int number = 0;
				try{
					number = Integer.valueOf(constNumberField.getText()).intValue();
					if(number <0){
						number = 0;
					}
				}catch( NumberFormatException evt){}
				if(number >0){
					refreshConstrTableView(number);
				}
			}else if(command.equals("Add")){
				System.out.println("pressed add button");
				
				String newName = newVarName.getText();
				OptimizationVariable nvar = new OptimizationVariable(newName);
				if((!totalAvailableVarNames.contains(newName)) && (!newDefinedVariableNames.contains(newName))){
					totalAvailableVarNames.addElement(newName);
					newDefinedVariableNames.addElement(newName);
					usedVars.addElement(nvar);
				}
				refreshDefinedTable();
			}else if(command.equals("Remove")){	   //need to find out whether remove var will affect other stuff.
				System.out.println("pressed remove button");
				int selectedIndex = defineVarTableView.getSelectedRow();
				if(selectedIndex == -1){
					return;
				}
				Vector varNames =  defineVarTableModel.getNames();
				String newName = varNames.elementAt(selectedIndex).toString();
				if(newDefinedVariableNames.contains(newName)){
					totalAvailableVarNames.removeElement(newName);
					newDefinedVariableNames.removeElement(newName);
					usedVars.removeElement(varNames.elementAt(selectedIndex));
				}
				refreshDefinedTable();
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
/*				Project project = frame.getProject();
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
		*/
			}
		}
	}

	class ConstraintsTableModel extends AbstractTableModel{
		private int row,col;
		private Vector constraints;
/*		private String[] colHd = {uiLabels.getString(VARIABLE),
			uiLabels.getString(LINEARWEIGHT),
			uiLabels.getString(SETPOINTWEIGHT)};
	*/
		private String[] colHd = {"#","Name", "Sense","Right Hand Values"};
		public ConstraintsTableModel(){
			row = 0;
			col = 4;
			constraints = new Vector();
		}
		public void setContents(Vector constraints){
			row = constraints.size();
			this.constraints = constraints;
		}
		@Override
		public int getColumnCount() { return col; }
		@Override
		public int getRowCount() { return row;}
		@Override
		public Object getValueAt(int r, int c){
			Constraint constraint = (Constraint)constraints.elementAt(r);
			if(c == 0){
				return String.valueOf(constraint.getNumber());
			}else if(c == 1){
				return constraint.getName();
			}else if(c == 2){
				return constraint.getSense();
			}else if(c == 3){
				return String.valueOf(constraint.getRightHandValue());
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
/*			if(c==1){
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
	*/
		}
	}

	

	class DefineVarTableModel extends AbstractTableModel{
		private int row,col;
		private Vector names,indepchecks,exogchecks;
		private String[] colHd = {uiLabels.getString(VARIABLE),
			uiLabels.getString(INDEPENDENT),
			uiLabels.getString(EXOGENOUS)};
		public DefineVarTableModel(){
			row = 0;
			col = 3;
			names = new Vector();
			indepchecks = new Vector();
			exogchecks = new Vector();
		}

		public void setContents(Vector names){
			this.names = names;
			row = names.size();
			ButtonGroup group;
			indepchecks.removeAllElements();
			exogchecks.removeAllElements();
			for(int r=0;r<row;r++){
				group = new ButtonGroup();
				JRadioButton check = new JRadioButton(){
					@Override
					public float getAlignmentY() { return 0.0f; }			
				};
				check.setBackground(Color.white);
				group.add(check);
				indepchecks.addElement(check);
				check.setSelected(true);
				check = new JRadioButton(){
					@Override
					public float getAlignmentY() { return 0.0f; }			
				};
				check.setBackground(Color.white);
				group.add(check);
				exogchecks.addElement(check);
			}
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
				return indepchecks.elementAt(r);
			}else if(c == 2){
				return exogchecks.elementAt(r);
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
			if(c==1||c==2) {
				return true;
			}
			return false;
		}		
		public Vector getNames(){
			return names;
		}
		public Vector getIndepchecks(){
			return indepchecks;
		}
		public Vector getExogchecks(){
			return exogchecks;
		}
	}

	class BoundsTableModel extends AbstractTableModel{
		private int row,col;
		private Vector names;
		private String[] colHd = {uiLabels.getString(VARIABLE),
			uiLabels.getString(LOWERBOUNDS),
			uiLabels.getString(UPPERBOUNDS),
			uiLabels.getString(INITIALVALUE)};
		public BoundsTableModel(){
			row = 0;
			col = 4;
			names = new Vector();
		}
		public void setContents(Vector names){
			this.names = names;
			row = names.size(); //need to take care of array later
			for(int i=0;i<row;i++){
				Variable var = (Variable)names.elementAt(i);
				var.setInitialValue(var.getMeanValue());
			}
				
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
				double w = ((Variable)names.elementAt(r)).getHardLowerBound();
		System.out.println("getHardLowerBound="+w);
				if(Double.compare(w, Double.POSITIVE_INFINITY) == 0){
					return "+INFINITY";
				}else if(Double.compare(w, Double.NEGATIVE_INFINITY) == 0){
					return "-INFINITY";
				}else{
					return String.valueOf(w);
				}
			}else if(c == 2){
				double w = ((Variable)names.elementAt(r)).getHardUpperBound();
		System.out.println("getHardUpperBound="+w);
				if(Double.compare(w, Double.POSITIVE_INFINITY) == 0){
					return "+INFINITY";
				}else if(Double.compare(w, Double.NEGATIVE_INFINITY) == 0){
					return "-INFINITY";
				}else{
					return String.valueOf(w);
				}
			}else if(c == 3){
				double w = ((Variable)names.elementAt(r)).getInitialValue();
				return String.valueOf(w);
			}
			return "";
		}
		@Override
		public String getColumnName(int c) {
			return colHd[c];
		}
		@Override
		public boolean isCellEditable(int r, int c) {
			if(c==1||c==2||c==3){
				return true;
			}
			return false;
		}		
		@Override
		public void setValueAt(Object aValue, int r, int c) {
			if(c==1 || c==2 || c==3){
				try{
					double v = Double.valueOf((String)aValue).doubleValue();
				}catch( NumberFormatException evt){
					System.err.println("Non-Fatal exception: " + evt.getMessage());
					evt.printStackTrace();
				}
			}
		}
		public Vector getNames(){
			return names;
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
				return 	cell;
			}
			return null;
		}
	}

	public void showFirstTime(){
		setBounds(100, 200, 600, 350);
		resetData();
		setVisible(true);
	}
	
	public boolean verifyAddControlAction() {
		return !totalAvailableVarNames.isEmpty();
	}
	
	public boolean verifyRemoveControlAction() {
		return totalAvailableVarNames != null;
	}
}
