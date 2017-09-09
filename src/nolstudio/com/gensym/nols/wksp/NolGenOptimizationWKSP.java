package com.gensym.nols.wksp;

import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.nio.charset.Charset;
import java.util.*;
import javax.swing.*;
import javax.swing.table.*;
import javax.swing.event.*;
import javax.swing.border.*;

import com.gensym.math.matrix.*;

import com.gensym.nols.main.*;
import com.gensym.nols.data.*;
import com.gensym.nols.util.*;

import com.gensym.DEBUG;

public class NolGenOptimizationWKSP extends NolInternalFrame {

	private static final String OPTIMIZATIONWKSP_NAME = "NameLabel";
    private static final String OPTIMIZATIONWKSP_COMMENT = "CommentLabel";
    private static final String OPTIMIZATIONWKSP_MODE= "OptimizationWKSP_Mode";
    private static final String OPTIMIZATIONWKSP_USEDMODELS = "OptimizationWKSP_UsedModels";
    private static final String OPTIMIZATIONWKSP_RUN = "OptimizationWKSP_Run";
    private static final String OPTIMIZATIONWKSP_ENTER = "OptimizationWKSP_Enter";
    private static final String OPTIMIZATIONWKSP_GOTHROUGHDATA = "OptimizationWKSP_GoThroughData";
    private static final String OPTIMIZATIONWKSP_EXPORT = "OptimizationWKSP_Export";
    private static final String OPTIMIZATIONWKSP_BUILD = "OptimizationWKSP_Build";
    private static final String OPTIMIZATIONWKSP_STOP = "OptimizationWKSP_Stop";
	
	private static final String DELETE = "DeleteLabel";
    private static final String OPTIMIZATIONWKSP_GENERAL = "GeneralLabel";
    private static final String OPTIMIZATIONWKSP_VARIABLES = "VariableLabel";
    private static final String OPTIMIZATIONWKSP_WEIGHTS = "OptimizationWKSP_Weights";
    private static final String OPTIMIZATIONWKSP_VARIABLEBOUNDS = "OptimizationWKSP_VariableBounds";
	

    private static final String OPTIMIZATIONWKSP_VARIABLE = "VariableLabel";

    private static final String OPTIMIZATIONWKSP_DELAY = "OptimizationWKSP_Delay";
    private static final String OPTIMIZATIONWKSP_RESULT = "OptimizationWKSP_Result";
    private static final String OPTIMIZATIONWKSP_VALUESLIDER = "OptimizationWKSP_ValueSlider";

    private static final String OPTIMIZATIONWKSP_LINEARWEIGHT = "OptimizationWKSP_LinearWeight";
    private static final String OPTIMIZATIONWKSP_SETPOINTWEIGHT = "OptimizationWKSP_SetpointWeight";
    private static final String OPTIMIZATIONWKSP_SLBWEIGHT = "OptimizationWKSP_SLBWeight";
    private static final String OPTIMIZATIONWKSP_SUBWEIGHT = "OptimizationWKSP_SUBWeight";
	
    private static final String OPTIMIZATIONWKSP_SETPOINT = "OptimizationWKSP_Setpoint";
    private static final String OPTIMIZATIONWKSP_SUB = "OptimizationWKSP_SUB";
    private static final String OPTIMIZATIONWKSP_UB = "OptimizationWKSP_UB";
    private static final String OPTIMIZATIONWKSP_LB = "OptimizationWKSP_LB";
    private static final String OPTIMIZATIONWKSP_SLB = "OptimizationWKSP_SLB";
    private static final String OPTIMIZATIONWKSP_MIN = "OptimizationWKSP_Min";
    private static final String OPTIMIZATIONWKSP_MAX = "OptimizationWKSP_Max";

    private static final String OPTIMIZATIONWKSP_STATEVARIABLE = "OptimizationWKSP_StateVariable";
    private static final String OPTIMIZATIONWKSP_MANIPULATEDVARIABLE = "OptimizationWKSP_ManipulatedVariable";
    private static final String OPTIMIZATIONWKSP_OUTPUTVARIABLE = "OptimizationWKSP_OutputVariable";
    private static final String OPTIMIZATIONWKSP_EXOGENOUSVARIABLE = "OptimizationWKSP_ExogenousVariable";

    private static final String NODATASERIES = "OptimizationWKSP_NoDataSeries";
    private static final String NOVALIDSETPOINT = "OptimizationWKSP_NoSetpoint";
    private static final String ERRORINMAKINGOPTIMIZER = "OptimizationWKSP_ErrorInMakingOptimizer";
    private static final String NOVALIDELICENSE = "OptimizationWKSP_NoValidLicense";
    private static final String SELECTDATASERIES = "OptimizationWKSP_SelectDataSeries";
    private static final String DATASERIES = "OptimizationWKSP_DataSeries";

	private NolMainFrame frame;

	private	JTextField optimizationName;
	private JTextArea descriptArea;
	private JLabel modeChoice;
	private JList modelList;
	private JPanel varListPane;
	private JPanel controlButtonPane;
	private JButton runBut;
	private JButton exportBut;
	private JButton stopBut;
	private JButton deleteBut;
	private JLabel runCountLabel;
	private JLabel runCount;
	private DefaultListModel modelListModel;
	private ControlAction actionListener;
	private boolean noFire;
	private NolOptimizeModel model;

	private Vector maniVars;
	private Vector stateVars;
	private Vector exogVars;
	private Vector outputVars;
	private Vector inputVars;
	private Vector varContentInPane;
	private NolGenOptimization optimization;
	private Vector variables;

	private	ConstraintsTableModel constraintsTableModel;
	private	JTable constraintsTableView;

	
 	private	VariableTableModel variableTableModel;
	private	JTable variableTableView;

 	private	BoundsTableModel boundsTableModel;
	private	JTable boundsTableView;

	private Thread optThread;
	private Matrix initX;

	private JComboBox modelChoice0;
	private JComboBox VariableChoice0;
	private JComboBox modelChoice;
	private JComboBox VariableChoice;
	private JTextField constraintLabel;
	private JTextArea constraintContentArea;
	private JTextArea objContentArea;
	private JComboBox constraintSenseBox;

/*
	private URL url1 = this.getClass().getResource("neg-infinity.gif");
	private ImageIcon negInfinity = new ImageIcon(url1);
	
	private URL url2 = this.getClass().getResource("pos-infinity.gif");
	private ImageIcon posInfinity = new ImageIcon(url2);
*/
	private int sigDigits = 8;
	
	private static boolean isCalculating;
	
	public NolGenOptimizationWKSP (NolMainFrame frame, NolGenOptimization optimization){ //for demo only
		super(frame.getProject().getRawDataSource());
		this.frame = frame;	 
		noFire = true;
		actionListener = new ControlAction();
		this.optimization = optimization;
//		initX = optimization.getInitX();
		initialLayout();
		initDataDisplay();
		noFire = false;
	}

	private void initialLayout(){
		JPanel workPane = new JPanel(new BorderLayout());
		JTabbedPane detailedTabbedPane = new JTabbedPane();
		detailedTabbedPane.addTab(frame.getNolResourceString(OPTIMIZATIONWKSP_GENERAL), getGeneralPanel());
		detailedTabbedPane.setSelectedIndex(0);
		detailedTabbedPane.addTab(frame.getNolResourceString(OPTIMIZATIONWKSP_VARIABLES), getVarPanel());
		detailedTabbedPane.addTab(frame.getNolResourceString(OPTIMIZATIONWKSP_VARIABLEBOUNDS), getBoundPanel());
		detailedTabbedPane.addTab(frame.getNolResourceString("OptimizationWKSP_Constraint"), getConstraintPanel());
		detailedTabbedPane.addTab(frame.getNolResourceString("OptimizationWKSP_Objective"), getObjectivePanel());
		detailedTabbedPane.addTab(frame.getNolResourceString("OptimizationWKSP_Status"), getStatusPanel());
		detailedTabbedPane.addChangeListener(new TabPaneChangeListener());
		workPane.add("Center", detailedTabbedPane);
		workPane.add("East",getControlPanel());
		setContentPane(workPane);
	}

	private JPanel getGeneralPanel(){
		JPanel infoPane = new JPanel(new BorderLayout());
		JPanel namePane = new JPanel(new GridLayout(2,2,10,10));
		namePane.setBorder(new EmptyBorder(12,12,10,12));

		namePane.add(new JLabel(frame.getNolResourceString(OPTIMIZATIONWKSP_NAME)+":"));
		optimizationName = new JTextField();
		optimizationName.addActionListener(actionListener);
		namePane.add(optimizationName);
		namePane.add(new JLabel(frame.getNolResourceString(OPTIMIZATIONWKSP_MODE)+":"));

		modeChoice = new JLabel();
		namePane.add(modeChoice);

		JPanel modelListPane = new JPanel(new GridLayout());
		modelListPane.setBorder(new TitledBorder(new EmptyBorder(7, 7, 7, 7),               
			frame.getNolResourceString(OPTIMIZATIONWKSP_USEDMODELS)+":", TitledBorder.LEFT , TitledBorder.TOP));
		modelList = new JList(getModelListModel());
		modelList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		modelList.addListSelectionListener(actionListener);
		JScrollPane listScrollPane = new JScrollPane(modelList);
		listScrollPane.setBorder(BorderFactory.createLoweredBevelBorder());
		listScrollPane.setPreferredSize(NolMainFrame.vpad50);
		modelListPane.add(listScrollPane);

		JPanel descriptPane = new JPanel(new GridLayout());
		descriptPane.setBorder(new TitledBorder(new EmptyBorder(7, 7, 7, 7),               
			frame.getNolResourceString(OPTIMIZATIONWKSP_COMMENT)+":", TitledBorder.LEFT , TitledBorder.TOP));
		descriptArea = new JTextArea();
		descriptArea.getDocument().addDocumentListener((DocumentListener)actionListener);
		listScrollPane = new JScrollPane(descriptArea);
		listScrollPane.setBorder(BorderFactory.createLoweredBevelBorder());
		listScrollPane.setPreferredSize(NolMainFrame.vpad50); 
		descriptPane.add(listScrollPane);

		JPanel cenPane = new JPanel(new GridLayout(2,1,5,5));
		cenPane.add(modelListPane);
		cenPane.add(descriptPane);
		infoPane.add("North",namePane);
		infoPane.add("Center",cenPane);
		return infoPane;
	}

	private JPanel getVarPanel(){
		JPanel varPane  = new JPanel(new GridLayout());
 		varPane.setBorder(new EmptyBorder(10,10,10,10));

		varListPane = new JPanel();

		variableTableModel = new VariableTableModel();
		variableTableView = new JTable(variableTableModel);
		variableTableView.setSelectionMode(0);
		variableTableView.setCellSelectionEnabled(true);
		JScrollPane listScrollPane = new JScrollPane(variableTableView);
		listScrollPane.setBackground(Color.white);

		varPane.add(listScrollPane);
		return varPane;
	}


	private JPanel getBoundPanel(){
		JPanel bPane = new JPanel(new GridLayout());
 		bPane.setBorder(new EmptyBorder(10,10,10,10));

		JPanel outPane = new JPanel(new GridLayout());
		boundsTableModel = new BoundsTableModel();
		boundsTableView = new JTable(boundsTableModel);
		boundsTableView.setSelectionMode(0);
		boundsTableView.setCellSelectionEnabled(true);
		JScrollPane listScrollPane = new JScrollPane(boundsTableView);
		listScrollPane.setBackground(Color.white);
		outPane.add(listScrollPane);

		bPane.add(outPane);

		return bPane;
	}

	private JPanel getConstraintPanel(){
		JPanel cPane = new JPanel(new GridLayout(2,1,5,5));
 		cPane.setBorder(new EmptyBorder(10,10,10,10));

		constraintsTableModel = new ConstraintsTableModel();
		constraintsTableView = new JTable(constraintsTableModel);
		constraintsTableView.setSelectionMode(0);
		constraintsTableView.setCellSelectionEnabled(true);
		constraintsTableView.setDefaultRenderer(JComponent.class, 
			new ConstraintTableRenderer());
		DefaultListSelectionModel rowSelectionModel =  (DefaultListSelectionModel)constraintsTableView.getSelectionModel();
		rowSelectionModel.addListSelectionListener(actionListener); 

		JScrollPane listScrollPane = new JScrollPane(constraintsTableView);
		listScrollPane.setBackground(Color.white);
		cPane.add(listScrollPane);

		JPanel constraintContentPanel = new JPanel(new BorderLayout());
		constraintContentPanel.setBorder(BorderFactory.createTitledBorder("Constraint Contents:"));
		
		JPanel cnPane = new JPanel(new GridLayout(1,3,5,5));
		constraintLabel = new JTextField("");
		cnPane.add(constraintLabel);
		String[] choices = {"<=","=","=>"};
		constraintSenseBox = new JComboBox(choices);
		cnPane.add(constraintSenseBox);
		JButton	modifyConstraintBut = new JButton("Modify");
		modifyConstraintBut.setActionCommand("Modify");
		modifyConstraintBut.addActionListener(actionListener);
		cnPane.add(modifyConstraintBut);

		constraintContentPanel.add("North",cnPane);

		constraintContentArea = new JTextArea();
		constraintContentArea.setLineWrap(true);
		JScrollPane areaScrollPane = new JScrollPane(constraintContentArea);
		constraintContentPanel.add("Center",areaScrollPane);

		JPanel chPane = new JPanel(new GridLayout(1,2,5,5));
		JPanel mPane = new JPanel(new GridLayout());
		JPanel vPane = new JPanel(new GridLayout());
		mPane.setBorder(BorderFactory.createTitledBorder("Models:"));
		vPane.setBorder(BorderFactory.createTitledBorder("Variables:"));
		modelChoice0 = new JComboBox();
		modelChoice0.setActionCommand("ModelChoiceForConst");
		modelChoice0.addActionListener(actionListener);
		VariableChoice0 = new JComboBox();
		VariableChoice0.setActionCommand("VarChoiceForConst");
		VariableChoice0.addActionListener(actionListener);
		mPane.add(modelChoice0);
		vPane.add(VariableChoice0);
		chPane.add(mPane);
		chPane.add(vPane);

		constraintContentPanel.add("South",chPane);

		cPane.add(constraintContentPanel);
		return cPane;
	}

	private JPanel getObjectivePanel(){
		JPanel oPane = new JPanel(new BorderLayout());
 		oPane.setBorder(new EmptyBorder(10,10,10,10));
		
		JPanel conPane = new JPanel(new BorderLayout());
		conPane.setBorder(BorderFactory.createTitledBorder("Contents:"));

		objContentArea = new JTextArea();
		objContentArea.setLineWrap(true);
		JScrollPane listScrollPane = new JScrollPane(objContentArea);
		listScrollPane.setBackground(Color.white);
		conPane.add("Center",listScrollPane);

	    JPanel bPane = new JPanel();
		JButton but = new JButton(frame.getNolResourceString(OPTIMIZATIONWKSP_ENTER));
		but.setActionCommand("Enter");
		but.addActionListener(actionListener);
	    bPane.add(but);
		conPane.add("South",bPane);

		oPane.add("Center",conPane);

		JPanel chPane = new JPanel(new GridLayout(1,2,5,5));
		JPanel mPane = new JPanel(new GridLayout());
		JPanel vPane = new JPanel(new GridLayout());
		mPane.setBorder(BorderFactory.createTitledBorder("Models:"));
		vPane.setBorder(BorderFactory.createTitledBorder("Variables:"));
		modelChoice = new JComboBox();
		modelChoice.setActionCommand("ModelChoiceForObjective");
		modelChoice.addActionListener(actionListener);
		VariableChoice = new JComboBox();
		VariableChoice.setActionCommand("VarChoiceForObjective");
		VariableChoice.addActionListener(actionListener);
		mPane.add(modelChoice);
		vPane.add(VariableChoice);
		chPane.add(mPane);
		chPane.add(vPane);

		oPane.add("South",chPane);

		return oPane;
	}

	private JPanel getStatusPanel(){
		JPanel oPane = new JPanel(new GridLayout(2,1,5,5));
 		oPane.setBorder(new EmptyBorder(10,10,10,10));
		
		JPanel conPane = new JPanel(new GridLayout());
		conPane.setBorder(BorderFactory.createTitledBorder("Building Status:"));

		JTextArea buildStatusArea = new JTextArea();
		JScrollPane blistScrollPane = new JScrollPane(buildStatusArea);
		blistScrollPane.setBackground(Color.white);
		conPane.add(blistScrollPane);
		oPane.add(conPane);

		JPanel runPane = new JPanel(new GridLayout());
		runPane.setBorder(BorderFactory.createTitledBorder("Running Status:"));

		JTextArea runStatusArea = new JTextArea();
		JScrollPane rlistScrollPane = new JScrollPane(runStatusArea);
		rlistScrollPane.setBackground(Color.white);
		runPane.add(rlistScrollPane);
		oPane.add(runPane);
		return oPane;
	}

	private JPanel getControlPanel(){
		JPanel control = new JPanel();
		control.setBackground(getContentPane().getBackground());
		control.setLayout(new BoxLayout(control, BoxLayout.Y_AXIS));
		control.setBorder(new EmptyBorder(10, 10, 10, 10));

		controlButtonPane = new JPanel(new GridLayout(7,1,5,5));
		runBut = new JButton(frame.getNolResourceString(OPTIMIZATIONWKSP_RUN));
		runBut.setActionCommand("Run");
		runBut.addActionListener(actionListener);
  		controlButtonPane.add(runBut);
		exportBut = new JButton(frame.getNolResourceString(OPTIMIZATIONWKSP_EXPORT));
		exportBut.setActionCommand("Export...");
		exportBut.addActionListener(actionListener);
 		controlButtonPane.add(exportBut);
		JButton buildBut = new JButton(frame.getNolResourceString(OPTIMIZATIONWKSP_BUILD));
		buildBut.setActionCommand("Build...");
		buildBut.addActionListener(actionListener);
 		controlButtonPane.add(buildBut);
		deleteBut = new JButton(frame.getNolResourceString(DELETE));
		deleteBut.setActionCommand("Delete");
		deleteBut.addActionListener(actionListener);
  		controlButtonPane.add(deleteBut);

		stopBut = new JButton(frame.getNolResourceString(OPTIMIZATIONWKSP_STOP));
		stopBut.setActionCommand("Stop");
		stopBut.setEnabled(false);
  		controlButtonPane.add(stopBut);
		stopBut.addActionListener(actionListener);
  		runCountLabel = new JLabel();
		runCountLabel.setHorizontalAlignment(SwingConstants.CENTER);
		controlButtonPane.add(runCountLabel);
		runCount = new JLabel();
		runCount.setHorizontalAlignment(SwingConstants.CENTER);
   		controlButtonPane.add(runCount);

		control.add(Box.createRigidArea(NolMainFrame.vpad15));
		control.add(controlButtonPane);
		control.add(Box.createRigidArea(NolMainFrame.vpad500));
		control.add(Box.createVerticalGlue());
		return control;
	}

	private DefaultListModel getModelListModel() {
		if (modelListModel == null) {
			modelListModel = new DefaultListModel();
		}	
		return modelListModel;
	}	
	
	private void initDataDisplay(){
		Project project = frame.getProject();
		optimizationName.setText(optimization.getName());
		descriptArea.setText(optimization.getComment());
		setTitle("Optimization:["+optimization.getName()+"]");
		int objsen = optimization.getObjSen();
		if(objsen == 1){
			modeChoice.setText("Minimization");
		}else{
			modeChoice.setText("Maximization");
		}
		Vector models = optimization.getModels();
		getModelListModel().removeAllElements();
		for(int i=0;i<models.size();i++){			
			getModelListModel().addElement(models.elementAt(i));
			modelChoice.addItem(models.elementAt(i));
			modelChoice0.addItem(models.elementAt(i));
		}
		variables = optimization.getVariables();
		variableTableModel.setContents(variables);
		for(int i=0;i<variables.size();i++){			
			VariableChoice0.addItem(variables.elementAt(i));
			VariableChoice.addItem(variables.elementAt(i));
		}
		refreshVarBoundsTable(variables);
		constraintsTableModel.setContents(optimization.getConstraints());


		objContentArea.setText(optimization.getObjective().getContent());

/*		model = optimization.getModel();
		varContentInPane = new Vector();
		
		maniVars = model.getManipulate();
		outputVars = model.getOutputs();
		inputVars = model.getInputs();
		stateVars = model.getState();
		exogVars = model.getExogenous();	

		getModelListModel().removeAllElements();
		getModelListModel().addElement(model.getName());
		modeChoice.setText(model.getName());
		Vector models = project.getOptimizationModels();
		int n = models.size();
		if(n<1) return;
		refreshVarDisplay();
		refreshVarWeightTable();
		refreshVarBoundsTable();
		refreshVarBoundTable((String)outputVars.elementAt(0));
		if(optimization.isCalculated()){
			refreshVarDataDisplay();
			runBut.setEnabled(false);
		}
*/	}

	private void refreshVarDataDisplay(){
/*		Matrix Y = optimization.getYResult();
		Matrix X = optimization.getXResult();
//		Matlib.disp(X,"refreshVarDataDisplay X=");
//		Matlib.disp(Y,"refreshVarDataDisplay Y=");
		int sc = stateVars.size();
		int vc = varContentInPane.size();
		Vector stateInputs = model.getStateInput();
		int sic = stateInputs.size();
		for(int i=0;i<vc;i++){
			VarContentPane contentPane = (VarContentPane)varContentInPane.elementAt(i);
			int outIndex = outputVars.indexOf(contentPane.varName);
			int stateIndex = stateVars.indexOf(contentPane.varName);
			int stateInputIndex = stateInputs.indexOf(contentPane.varName);
			int inputIndex = inputVars.indexOf(contentPane.varName);


			if(outIndex != -1){
				double value = Y.get(0,sc+outIndex);
				contentPane.currentValueLabel.setText(DataUtilities.doubleToString(value,sigDigits));
				contentPane.varSlider.setValues(5,value);
			}else if(stateIndex != -1){
				double value = Y.get(0,stateIndex);
				contentPane.currentValueLabel.setText(DataUtilities.doubleToString(value,sigDigits));
				contentPane.varSlider.setValues(5,value);
			}else if(stateInputIndex != -1){
				double value = X.get(0,stateInputIndex);
				contentPane.currentValueLabel.setText(DataUtilities.doubleToString(value,sigDigits));
				contentPane.varSlider.setValues(5,value);
			}else if(inputIndex != -1){
				int stateInputCount = 0;
				for(int j=0;j<inputIndex;j++){
					if(stateInputs.contains(inputVars.elementAt(j))){
						stateInputCount++;
					}
				}
				double value = X.get(0,sic+inputIndex-stateInputCount);
				contentPane.currentValueLabel.setText(DataUtilities.doubleToString(value,sigDigits));
				contentPane.varSlider.setValues(5,value);
			}
			double[] bb = optimization.getBounds(contentPane.varName);
			refreshSlider(contentPane.varName,0,bb[2]);		
		}
		varListPane.repaint(0l);
		varListPane.validate();
*/
	}

	private void refreshVarBoundsTable(Vector variables){
		boundsTableModel.setContents(variables);
		boundsTableView.repaint(0l);
		boundsTableView.validate();
	}
	
	private boolean checkInput(){
		return true;
	}
	
	public NolGenOptimization getOptimization(){
		return optimization;
	}

	private void exportMakefile(String directory){
		String userDir = directory +"\\builds\\"+optimization.getName();
		String binDir = directory +	"\\builds\\bin";

//		String content = "cd "+userDir+"\nnmake /f makefile.nt\ncopy "+userDir+"\\OptProb.dll "+ binDir+"\\"+optimization.getName() + ".dll\n";
		String content = "cd "+userDir+"\nnmake /f makefile.nt > out.txt\n";
		try{
			File SourceFile = null;
			String fileName = "make.bat";
			SourceFile = new File(userDir,fileName);
			
			FileOutputStream outStream = null;
		    Writer writer = null;
		    BufferedWriter Source = null;
		    try {
				outStream = new FileOutputStream(SourceFile);
				writer = new OutputStreamWriter(outStream, Charset.defaultCharset());
				Source = new BufferedWriter(writer);
				Source.write(content);
		    }finally {
		    	closeSilently(Source);
		    	closeSilently(writer);
		    	closeSilently(outStream);
		    }
		}catch(IOException evt){
			evt.printStackTrace();
		}
	}
   /**
     * Control action implementation
     */
    class ControlAction extends AbstractAction implements 
		ListSelectionListener, DocumentListener,Runnable{

		private String command;
		private Object source;
		ControlAction(){super("controlAction");}
			
		@Override
		public void valueChanged(ListSelectionEvent e){
			if(e.getValueIsAdjusting()){
				int index = constraintsTableView.getSelectedRow();
				Vector csts = optimization.getConstraints();
				Constraint cst = (Constraint)csts.elementAt(index);
				constraintLabel.setText(cst.getName());
				constraintContentArea.setText(cst.getContent());
				String sen = cst.getSense();
				if(sen.equals("L")){
					constraintSenseBox.setSelectedIndex(0);
				}else if(sen.equals("E")){
					constraintSenseBox.setSelectedIndex(1);
				}else if(sen.equals("G")){
					constraintSenseBox.setSelectedIndex(2);
				}

			}
		}

		@Override
		public void actionPerformed(ActionEvent e) {
			if(noFire){
				return;
			}
			command = e.getActionCommand ();
			source = e.getSource ();
			new Thread (this).start();
		}
		
		@Override
		public void run () {
			if(command.equals("Modify")){
				int index = constraintsTableView.getSelectedRow();
				if(index > -1){
					Vector csts = optimization.getConstraints();
					Constraint cst = (Constraint)csts.elementAt(index);
					cst.setContent(constraintContentArea.getText());
					constraintsTableModel.setDefinedRow(index);
					cst.setDefined(true);
					if(constraintSenseBox.getSelectedIndex() == 0){
						cst.setSense("L");
					}else if(constraintSenseBox.getSelectedIndex() == 1){
						cst.setSense("E");
					}else if(constraintSenseBox.getSelectedIndex() == 2){
						cst.setSense("G");
					}
				}
				refreshDisplay();

			}else if(command.equals("Delete")){
				frame.removeGenOptimization(optimization);
			}else if(command.equals("Export...")){
			  System.out.println("build GosApplication.miscDirectory="+NolMainFrame.rootDirectory);
	// Get the directories
			  String directory = NolMainFrame.rootDirectory;
			  String applicationDir = directory+"\\builds\\"+optimization.getName();
			  File dir = new File(applicationDir);
			  if(!dir.exists()){
				dir.mkdir();
			  }

			  //change current working directory
			  System.setProperty("user.dir",applicationDir);

			  // Copy the necessary files to the build directory.
			  
			  String libSourceDir = directory+"\\builds\\libs";
			  Runtime rt = Runtime.getRuntime(); 
			  String cmd;
			  try{
				  exportMakefile(directory);
				  cmd = "cmd /c \"copy "+libSourceDir+"\\nnet.c "+applicationDir;
				  rt.exec(cmd);
				  cmd = "cmd /c \"copy "+libSourceDir+"\\nnet.h "+applicationDir;
				  rt.exec(cmd);
				  cmd = "cmd /c \"copy "+libSourceDir+"\\com_gensym_gos_deploy_OnlineManager.h "+applicationDir;
				  rt.exec(cmd);
				  cmd = "cmd /c \"copy "+libSourceDir+"\\FRONTKEY.H "+applicationDir;
				  rt.exec(cmd);
				  cmd = "cmd /c \"copy "+libSourceDir+"\\FRONTMIP.H "+applicationDir;
				  rt.exec(cmd);
				  cmd = "cmd /c \"copy "+libSourceDir+"\\FRONTMIP.DLL "+applicationDir;
				  rt.exec(cmd);
				  rt.exec(cmd);
				  cmd = "cmd /c \"copy "+libSourceDir+"\\OptProb.h "+applicationDir;
				  rt.exec(cmd);
				  cmd = "cmd /c \"copy "+libSourceDir+"\\makefile.nt "+applicationDir;
				  rt.exec(cmd);
				  cmd = "cmd /c \"copy "+libSourceDir+"\\frontmip.lib "+applicationDir;
				  rt.exec(cmd);
				  optimization.writeToFile(applicationDir);
			  }catch(Exception evt){
				System.out.println("evt="+evt);
			  }
			  Toolkit.getDefaultToolkit().beep();
			}else if(command.equals("Build...")){
			  String directory = NolMainFrame.rootDirectory;
			  String applicationDir = directory+"\\builds\\"+optimization.getName();
			  File dir = new File(applicationDir);
			  if(!dir.exists()){
				return;
			  }
			  Runtime rt = Runtime.getRuntime(); 
			  String cmd ;
			  try{
				  cmd = "\""+applicationDir+"\\make.bat\"";
System.out.println("before exec");
				  Process proc = rt.exec(cmd);
System.out.println("after exec");
					
				  InputStream inStream = proc.getInputStream();
				  byte[] b = new byte[2000];
				  inStream.read(b);
				  String outStr = new String(b, Charset.defaultCharset());
System.out.println("outStr="+outStr);
				  proc.waitFor();
System.out.println("exitValue()="+proc.exitValue());
			  }catch(Exception evt){
				System.out.println("evt="+evt);
			  }
			}else if(command.equals("Stop")){
				isCalculating = false;
//				runningThread.setStop(true);
//				optThread.stop();
				runCountLabel.setText("");
				runCount.setText("");
				stopBut.setEnabled(false);
				runBut.setEnabled(false);
				deleteBut.setEnabled(true);
//				controlButtonPane.remove(stopBut);
//				controlButtonPane.remove(runCount);
				controlButtonPane.repaint(0l);
				controlButtonPane.validate();
			}else if(source.equals(optimizationName)){
				String nm = optimizationName.getText();
				if(nm.length() > 0){
					optimization.setName(nm);
					setTitle("Optimization:["+optimization.getName()+"]");
//					frame.getProjectTree().changeOptimizationName(optimization,true);
				}else{
					nm = optimization.getName();
					optimizationName.setText(nm);
				}
			}else if(command.equals("ModelChoiceForConst")){
				NolModel2 model2 = (NolModel2)modelChoice0.getSelectedItem();
				constraintContentArea.append(model2.getModelString());
			}else if(command.equals("VarChoiceForConst")){
				String varName = VariableChoice0.getSelectedItem().toString();
				constraintContentArea.append(varName);
			}else if(command.equals("ModelChoiceForObjective")){
				NolModel2 model2 = (NolModel2)modelChoice.getSelectedItem();
				objContentArea.append(model2.getModelString());
			}else if(command.equals("VarChoiceForObjective")){
				String varName = VariableChoice.getSelectedItem().toString();
				objContentArea.append(varName);
			}else if(command.equals("Enter")){
				Objective objective = optimization.getObjective();
				objective.setContent(objContentArea.getText());
			} 
		}
		@Override
		public void changedUpdate(DocumentEvent e){}
		@Override
		public void insertUpdate(DocumentEvent e){
			String com = descriptArea.getText();
			optimization.setComment(com);
		}
		@Override
		public void removeUpdate(DocumentEvent e){
			String com = descriptArea.getText();
			optimization.setComment(com);
		}
    }


	class BoundsTableModel extends AbstractTableModel{
		private int row,col;
		private Vector varObjs;
		private String[] colHd = {
			frame.getNolResourceString(OPTIMIZATIONWKSP_VARIABLE),
			frame.getNolResourceString(OPTIMIZATIONWKSP_LB),
			frame.getNolResourceString(OPTIMIZATIONWKSP_UB)};

		public BoundsTableModel(){
			row = 0;
			col = 3;
			varObjs = new Vector();
		}
		public void setContents(Vector vars){
			this.varObjs = vars;
			row = varObjs.size();
		}
		@Override
		public int getColumnCount() { return col; }
		@Override
		public int getRowCount() { return row;}
		@Override
		public Object getValueAt(int r, int c){
			if(c == 0){
				return varObjs.elementAt(r).toString();
			}else if(c == 1){
				double w = ((Variable)varObjs.elementAt(r)).getHardLowerBound();
				if(Double.compare(w, Double.POSITIVE_INFINITY) == 0){
					return "+INFINITY";
				}else if(Double.compare(w, Double.NEGATIVE_INFINITY) == 0){
					return "-INFINITY";
				}else{
					return String.valueOf(w);
				}
			}else if(c == 2){
				double w = ((Variable)varObjs.elementAt(r)).getHardUpperBound();
				if(Double.compare(w, Double.POSITIVE_INFINITY) == 0){
					return "+INFINITY";
				}else if(Double.compare(w, Double.NEGATIVE_INFINITY) == 0){
					return "-INFINITY";
				}else{
					return String.valueOf(w);
				}
			}
			return "";
		}
		@Override
		public String getColumnName(int c) {
			return colHd[c];
		}
		@Override
		public boolean isCellEditable(int r, int c) {
			if(c==0)
				return false;
			return true;
		}		
		@Override
		public void setValueAt(Object aValue, int r, int c) {
			Variable var = (Variable)varObjs.elementAt(r);
			double bb4 = var.getHardUpperBound();
			double bb1 = var.getHardLowerBound();
			if(c==1){
				try{
					double v = Double.valueOf((String)aValue).doubleValue();
					if(v>bb4){
						v = bb4;
					}
					var.setHardLowerBound(v);
				}catch( NumberFormatException evt){
				}
			}else if(c==2){
				try{
					double v = Double.valueOf((String)aValue).doubleValue();
					if(v<bb1){
						v = bb1;
					}
					var.setHardUpperBound(v);
				}catch( NumberFormatException evt){
				}
			}
			boundsTableView.repaint(0l);
			boundsTableView.validate();
			optimization.setCalculated(false);
			runBut.setEnabled(true);
		}
	}

	class VariableTableModel extends AbstractTableModel{
		private int row,col;
		private Vector names;
		private String[] colHd = {
			frame.getNolResourceString(OPTIMIZATIONWKSP_VARIABLES),
			frame.getNolResourceString("OptimizationWKSP_VariableInitial"),
			frame.getNolResourceString("OptimizationWKSP_Result")};
		private int digits = 5;

		public VariableTableModel(){
			row = 0;
			col = 3;
		}
		public void setContents(Vector names){
			this.names = names;
			row = names.size();
		}
		@Override
		public int getColumnCount() { return col; }
		@Override
		public int getRowCount() { return row;}
		@Override
		public Object getValueAt(int r, int c){
			if(c == 0){
				if(names == null || names.isEmpty()) 
					return "name";
				else 
					return names.elementAt(r);
			}else if(c == 1){
				double w = ((Variable)names.elementAt(r)).getInitialValue();
				return String.valueOf(w);
			}else if(c == 2){
				double w = ((Variable)names.elementAt(r)).getResultValue();
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
			if(c==0)
				return false;
			return true;
		}		
		@Override
		public void setValueAt(Object aValue, int r, int c) {
			if(c==1){
				try{
					double v = Double.valueOf((String)aValue).doubleValue();
				    ((Variable)names.elementAt(r)).setInitialValue(v);
				}catch( NumberFormatException evt){
					System.err.println("Non-Fatal exception: " + evt.getMessage());
					evt.printStackTrace();
				}
			}
			optimization.setCalculated(false);
			runBut.setEnabled(true);
		}
	}


	class VarContentPane extends JPanel implements MouseListener, NolSliderListener{
		protected String varName;
		protected int colorType;
		protected NolSlider varSlider;
		protected BorderedTextField currentValueLabel;
		protected double lb,slb,sub,ub;

		public VarContentPane(String n, int type){
			varName = n;
			colorType = type;
			initialLayout();
		}

		private void initialLayout(){
			setLayout(new GridLayout(1,3,0,0));
			BorderedTextField nameLabel = new BorderedTextField(varName);
			nameLabel.addMouseListener(this);
			int stype = 0;
/*			double[] bb = optimization.getBounds(varName);	 
			if(colorType == 3) {
				stype = 1;
				// signature: public NolSlider(double min, double max, double sp, int t){
				varSlider = new NolSlider(bb[5],bb[6],bb[2],stype);
			}else{
				// signature: public NolSlider(double min, double max, double lb, double slb, double sub, double ub, double sp, int t)
				varSlider = new NolSlider(bb[5],bb[6],bb[0],bb[1],bb[3],bb[4],bb[2],stype);
			}
			varSlider.addNolSliderListener(this);
			currentValueLabel = new BorderedTextField("",varName);
			currentValueLabel.addMouseListener(this);
			
			if(colorType == 0){
				setBackground(new Color(242,244,176));
				nameLabel.setToolTipText(frame.getNolResourceString(OPTIMIZATIONWKSP_OUTPUTVARIABLE));
				currentValueLabel.setToolTipText(frame.getNolResourceString(OPTIMIZATIONWKSP_OUTPUTVARIABLE));
			}else if(colorType == 1){
				setBackground(new Color(232,235,207));
				nameLabel.setToolTipText(frame.getNolResourceString(OPTIMIZATIONWKSP_MANIPULATEDVARIABLE));
				currentValueLabel.setToolTipText(frame.getNolResourceString(OPTIMIZATIONWKSP_MANIPULATEDVARIABLE));
			}else if(colorType == 2){
				setBackground(new Color(200,204,28));
				nameLabel.setToolTipText(frame.getNolResourceString(OPTIMIZATIONWKSP_STATEVARIABLE));
				currentValueLabel.setToolTipText(frame.getNolResourceString(OPTIMIZATIONWKSP_STATEVARIABLE));
			}else if(colorType == 3){
				setBackground(new Color(119,121,17));
				nameLabel.setToolTipText(frame.getNolResourceString(OPTIMIZATIONWKSP_EXOGENOUSVARIABLE));
				currentValueLabel.setToolTipText(frame.getNolResourceString(OPTIMIZATIONWKSP_EXOGENOUSVARIABLE));
			}

			add(nameLabel);
			add(varSlider);
			add(currentValueLabel);
*/		}
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
		public void mouseClicked(MouseEvent m) {}
		@Override
		public void valueChanged(NolSliderEvent evt){
/*			double[] bb = optimization.getBounds(varName);	 
			bb[0] = evt.getLowLimit();
			bb[1] = evt.getSoftLow();
			bb[2] = evt.getSetpoint();
			bb[3] = evt.getSoftHigh();
			bb[4] = evt.getHighLimit();			
			refreshVarBoundTable(varName);
			optimization.setCalculated(false);
			runBut.setEnabled(true);
*/		}
	}

	class VarContentHeaderPane extends JPanel{
		public VarContentHeaderPane(){
			setLayout(new GridLayout(1,3,0,0));
			BorderedLabel col1 = new BorderedLabel(frame.getNolResourceString(OPTIMIZATIONWKSP_VARIABLE));
			BorderedLabel col2 = new BorderedLabel(frame.getNolResourceString(OPTIMIZATIONWKSP_VALUESLIDER));
			BorderedLabel col3 = new BorderedLabel(frame.getNolResourceString(OPTIMIZATIONWKSP_RESULT));
			col1.setHorizontalAlignment(SwingConstants.CENTER);
			col2.setHorizontalAlignment(SwingConstants.CENTER);
			col3.setHorizontalAlignment(SwingConstants.CENTER);
			add(col1);
			add(col2);
			add(col3);
		}
	}

    class BorderedTextField extends JComponent {
		String text;
		String varName;

		public BorderedTextField(String v) {
			this();
			text = v;
			varName = v;
		}
		public BorderedTextField(String t,String v) {
			this();
			text = t;
			varName = v;
		}
		public BorderedTextField() {
			super();
		}

		public void setText(String t){
			text = t;
			repaint(0l);
			validate();
		}

		public String getVarName(){
			return varName;
		}

		@Override
		public Dimension getPreferredSize() {
			Dimension size = super.getPreferredSize();
			size.height = 20;
			return size;
		}
		@Override
		public Dimension getMaximumSize() {
			return new Dimension(400, 20);
		}
		@Override
		public void paint(Graphics g) {
			super.paint(g);
			g.setColor(Color.black);
			g.drawString(text,2,15 );
			g.drawRect(0, 0, getWidth(), getHeight());
		}
    }
    
    class BorderedLabel extends JLabel {

		public BorderedLabel(String text) {
			super(text);
		}
		public BorderedLabel() {
			super();
		}
		@Override
		public Dimension getPreferredSize() {
			Dimension size = super.getPreferredSize();
			size.height = 20;
			return size;
		}
		@Override
		public Dimension getMaximumSize() {
			return new Dimension(400, 20);
		}
		@Override
		public void paint(Graphics g) {
			super.paint(g);
			g.setColor(Color.black);
			g.drawRect(0, 0, getWidth(), getHeight());
		}
    }

    class TabPaneChangeListener implements ChangeListener {
		TabPaneChangeListener(){
			super();
		}
		@Override
		public void stateChanged(ChangeEvent e){
			if(DEBUG.debugFlag){
				System.out.println("stateChanged e="+e);
			}
			if(e.getSource() instanceof JTabbedPane){
				JTabbedPane tabPane = (JTabbedPane)e.getSource();
				int index = tabPane.getSelectedIndex();
				if(DEBUG.debugFlag){
					System.out.println("stateChanged index="+index);
				}
				if(index == 1){
				}
			}
		}
	}

	class ConstraintsTableModel extends AbstractTableModel{
		private int row,col;
		private Vector constraints;
		private Vector checks;
		private String[] colHd = {"Name", "Content", "Sense","RHV", "Defined"};
		public ConstraintsTableModel(){
			row = 0;
			col = 5;
			constraints = new Vector();
			checks = new Vector();
		}
		public void setContents(Vector constraints){
			row = constraints.size();
			this.constraints = constraints;
			checks.removeAllElements();
			for(int i=0;i<row;i++){
				Constraint constraint = (Constraint)constraints.elementAt(i);
				JCheckBox check = new JCheckBox(){
					@Override
					public float getAlignmentY() { return 0.0f; }			
				};
				check.setBackground(Color.white);
				Constraint cst = (Constraint)constraints.elementAt(i);
				if(cst.getDefined())
					check.setSelected(true);
				else
					check.setSelected(false);
				checks.addElement(check);			
			}
		}
		@Override
		public int getColumnCount() { return col; }
		@Override
		public int getRowCount() { return row;}
		@Override
		public Object getValueAt(int r, int c){
			Constraint constraint = (Constraint)constraints.elementAt(r);
			if(c == 0){
				return constraint.getName();
			}else if(c == 1){
				return constraint.getContent();
			}else if(c == 2){
				String sen = constraint.getSense();
				if(sen.equals("L")){
					return "<=";
				}else if(sen.equals("E")){
					return "=";
				}else if(sen.equals("G")){
					return "=>";
				}
				return "";
			}else if(c == 3){
				return String.valueOf(constraint.getRightHandValue());
			}else if(c == 4){
				return checks.elementAt(r);
			}
			return "";
		}
		public void setDefinedRow(int r){
			if(r>-1 && r<row){
				JCheckBox check = (JCheckBox)checks.elementAt(r);
				check.setSelected(true);
			}
		}

		@Override
		public String getColumnName(int c) {
			return colHd[c];
		}
		@Override
		public boolean isCellEditable(int r, int c) {
			if(c==1||c==2 || c==3) {
				return true;
			}
			return false;
		}		
		@Override
		public Class getColumnClass(int c) {
			return getValueAt(0, c).getClass();
		}
		@Override
		public void setValueAt(Object aValue, int r, int c) {
			Constraint constraint = (Constraint)constraints.elementAt(r);
			if(c==3){
				try{
					double v = Double.valueOf((String)aValue).doubleValue();
					constraint.setRightHandValue(v);
				}catch( NumberFormatException evt){
					System.err.println("Non-Fatal exception: " + evt.getMessage());
					evt.printStackTrace();
				}
			}
		}
	}
	class ConstraintTableRenderer extends JComponent 
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
				cell.add(check);
				return cell;
			}else if(value instanceof JComponent){
				return (JComponent)value;
			}
			return null;
		}
	}
	private void refreshDisplay(){
		Rectangle rv = this.getBounds();
		this.setBounds(rv.x,rv.y,rv.width+1,rv.height);
		this.paintImmediately(rv.x,rv.y,rv.width+1,rv.height);
		this.validate();
		this.setBounds(rv.x,rv.y,rv.width,rv.height);
		this.validate();
	}
}

