package com.gensym.nols.wksp;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.GridLayout;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.io.File;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.net.URL;
import java.util.Vector;

import javax.swing.AbstractAction;
import javax.swing.BorderFactory;
import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.DefaultListModel;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JComponent;
import javax.swing.JDialog;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTabbedPane;
import javax.swing.JTable;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.ListSelectionModel;
import javax.swing.SwingConstants;
import javax.swing.border.EmptyBorder;
import javax.swing.border.TitledBorder;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import javax.swing.event.DocumentEvent;
import javax.swing.event.DocumentListener;
import javax.swing.event.InternalFrameAdapter;
import javax.swing.event.InternalFrameEvent;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import javax.swing.table.AbstractTableModel;

import com.gensym.DEBUG;
import com.gensym.math.MathException;
import com.gensym.math.Utilities;
import com.gensym.math.matrix.Matlib;
import com.gensym.math.matrix.Matrix;
import com.gensym.math.opt.OptException;
import com.gensym.nols.data.DataSeries;
import com.gensym.nols.data.DataUtilities;
import com.gensym.nols.data.INolOptimizeModel;
import com.gensym.nols.data.NolOptimization;
import com.gensym.nols.data.NolOptimizationThread;
import com.gensym.nols.data.OptimizationListener;
import com.gensym.nols.data.Preprocessor;
import com.gensym.nols.data.Project;
import com.gensym.nols.data.RawDataSource;
import com.gensym.nols.data.ResponseSurfaceSimulation;
import com.gensym.nols.data.Variable;
import com.gensym.nols.deploy.OnlineOptimizer;
import com.gensym.nols.dlg.NolFileFilter;
import com.gensym.nols.dlg.NolSingleChoiceDialog;
import com.gensym.nols.main.NolMainFrame;
import com.gensym.nols.util.NolSlider;
import com.gensym.nols.util.NolSliderEvent;
import com.gensym.nols.util.NolSliderListener;

public class NolOptimizationWKSP extends NolInternalFrame {

	private static final String OPTIMIZATIONWKSP_NAME = "NameLabel";
    private static final String OPTIMIZATIONWKSP_COMMENT = "CommentLabel";
    private static final String OPTIMIZATIONWKSP_MODEL= "OptimizationWKSP_Model";
    private static final String OPTIMIZATIONWKSP_VALIDMODELS = "OptimizationWKSP_ValidModels";
    private static final String OPTIMIZATIONWKSP_RUN = "OptimizationWKSP_Run";
    private static final String OPTIMIZATIONWKSP_GOTHROUGHDATA = "OptimizationWKSP_GoThroughData";
    private static final String OPTIMIZATIONWKSP_EXPORT = "OptimizationWKSP_Export";
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

    private static final String NEWNMX = "OptimizationWKSP_NewNMX";
    private static final String YES = "YesButtonLabel";
    private static final String NO = "NoButtonLabel";
    private static final String SECONDLABEL = "SecondLabel";
    private static final String MINUTELABEL = "MinuteLabel";
    private static final String HOURLABEL = "HourLabel";
    private static final String RECALCULATEDIALOGTITLE = "OptimizationWKSP_RecalculateDialogTitle";
    private static final String RECALCULATEDIALOGLABEL = "OptimizationWKSP_RecalculateDialogLabel";

	private static final int NUMBER_OF_COLUMNS_IN_VARS_PANE = 4;
	
	private NolMainFrame frame;

	private	JTextField optimizationName;
	private JTextArea descriptArea;
	private JLabel modelChoice;
	private JList modelList;
	private JPanel varListPane;
	private JPanel controlButtonPane;
	private JButton runBut;
	private JButton throughDataBut;
	private JButton exportBut;
	private JButton stopBut;
	private JButton deleteBut;
	private JLabel runCountLabel;
	private JLabel runCount;
	private DefaultListModel modelListModel;
	private ControlAction actionListener;
	private boolean noFire;
	private INolOptimizeModel model;
	private Vector maniVars;
	private Vector stateVars;
	private Vector exogVars;
	private Vector outputVars;
	private Vector inputVars;
	private Vector varContentInPane;
	private NolOptimization optimization;
	private int delayTimeUnit;
	
	private WeightTableModel weightTableModel;
	private JTable weightTableView;

 	private	SingleBoundsTableModel singleBoundsTableModel;
	private	JTable singleBoundsTableView;

 	private	BoundsTableModel boundsTableModel;
	private	JTable boundsTableView;

	private Thread optThread;
	private NolOptimizationThread runningThread;

	private Matrix initX;

	private ReCalculateConfirmDialog rCDLG;
/*
	private URL url1 = this.getClass().getResource("neg-infinity.gif");
	private ImageIcon negInfinity = new ImageIcon(url1);
	
	private URL url2 = this.getClass().getResource("pos-infinity.gif");
	private ImageIcon posInfinity = new ImageIcon(url2);
*/
	private int sigDigits = 8;
	private DelaysStorage delaysStorage;
	
	private static boolean isCalculating;
	
	public NolOptimizationWKSP (NolMainFrame frame,
			NolOptimization optimization) { //for demo only
		super(frame.getProject().getRawDataSource());
		this.frame = frame;	 
		noFire = false;
		actionListener = new ControlAction();
		this.optimization = optimization;
		delayTimeUnit = optimization.getModel().getDelayTimeUnit();
			
		initX = optimization.getInitX();
		initialLayout();
		initDataDisplay();
		addInternalFrameListener(new OptInternalFrameAdapter());
	}

	private void initialLayout(){
		JPanel workPane = new JPanel(new BorderLayout());
		JTabbedPane detailedTabbedPane = new JTabbedPane();
		detailedTabbedPane.addTab(frame.getNolResourceString(OPTIMIZATIONWKSP_GENERAL), getGeneralPanel());
		detailedTabbedPane.setSelectedIndex(0);
		detailedTabbedPane.addTab(frame.getNolResourceString(OPTIMIZATIONWKSP_VARIABLES), getVarPanel());
		detailedTabbedPane.addTab(frame.getNolResourceString(OPTIMIZATIONWKSP_VARIABLEBOUNDS), getBoundPanel());
		detailedTabbedPane.addTab(frame.getNolResourceString(OPTIMIZATIONWKSP_WEIGHTS), getWeightPanel());
		detailedTabbedPane.addChangeListener(new TabPaneChangeListener());
		workPane.add("Center", detailedTabbedPane);
		workPane.add("East",getControlPanel());
		setContentPane(workPane);
	}

	private JPanel getGeneralPanel(){
		JPanel infoPane = new JPanel(new BorderLayout());
		JPanel namePane = new JPanel(new GridLayout(2,2,10,10));
		namePane.setBorder(new EmptyBorder(12,12,10,12));

		//frame.getNolResourceString(DATASERIES_NAME)+":"
		namePane.add(new JLabel(frame.getNolResourceString(OPTIMIZATIONWKSP_NAME)+":"));
		optimizationName = new JTextField();
		optimizationName.addActionListener(actionListener);
		namePane.add(optimizationName);
		namePane.add(new JLabel(frame.getNolResourceString(OPTIMIZATIONWKSP_MODEL)+":"));

		modelChoice = new JLabel();
//		modelChoice.addActionListener(actionListener);
		namePane.add(modelChoice);

		JPanel modelListPane = new JPanel(new GridLayout());
		modelListPane.setBorder(new TitledBorder(new EmptyBorder(7, 7, 7, 7),               
			frame.getNolResourceString(OPTIMIZATIONWKSP_VALIDMODELS)+":", TitledBorder.LEFT , TitledBorder.TOP));
		modelList = new JList(getModelListModel());
//		modelList.setBackground(Color.white);
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
		JPanel varPane  = new JPanel(new BorderLayout());
 		varPane.setBorder(new EmptyBorder(10,10,10,10));

		varListPane = new JPanel();
		varListPane.setLayout(new BoxLayout(varListPane, BoxLayout.Y_AXIS));
		varListPane.setBackground(Color.white);
 		
		JScrollPane listScrollPane = new JScrollPane(varListPane);
		listScrollPane.setBorder(BorderFactory.createLoweredBevelBorder());
		listScrollPane.setColumnHeaderView(new VarContentHeaderPane(frame, delayTimeUnit));
		varPane.add("Center", listScrollPane);

		JPanel bottomPane = new JPanel(new GridLayout());
		bottomPane.setBorder(new TitledBorder(new EmptyBorder(0, 0, 0, 0),               
			frame.getNolResourceString(OPTIMIZATIONWKSP_VARIABLEBOUNDS)+":", TitledBorder.LEFT , TitledBorder.TOP));
		singleBoundsTableModel = new SingleBoundsTableModel();
		singleBoundsTableView = new JTable(singleBoundsTableModel);
		singleBoundsTableView.setSelectionMode(0);
		singleBoundsTableView.setCellSelectionEnabled(true);
		listScrollPane = new JScrollPane(singleBoundsTableView);
		listScrollPane.setBackground(Color.white);
		listScrollPane.setPreferredSize(NolMainFrame.vpad40);
		bottomPane.add(listScrollPane);

		varPane.add("South",bottomPane);
		return varPane;
	}

	private JPanel getWeightPanel(){
		JPanel wPane = new JPanel(new GridLayout());
 		wPane.setBorder(new EmptyBorder(10,10,10,10));

		JPanel outPane = new JPanel(new GridLayout());
		weightTableModel = new WeightTableModel();
		weightTableView = new JTable(weightTableModel);
		weightTableView.setSelectionMode(0);
		weightTableView.setCellSelectionEnabled(true);
		JScrollPane listScrollPane = new JScrollPane(weightTableView);
		listScrollPane.setBackground(Color.white);
		outPane.add(listScrollPane);

		wPane.add(outPane);

		return wPane;
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
//		JButton but = new JButton("Report...");
//		but.setActionCommand("Report...");
//		but.addActionListener(actionListener);
// 		controlButtonPane.add(but);
		throughDataBut = new JButton(frame.getNolResourceString(OPTIMIZATIONWKSP_GOTHROUGHDATA));
		throughDataBut.setActionCommand("Go Through Data...");
		throughDataBut.addActionListener(actionListener);
 		controlButtonPane.add(throughDataBut);
//		if(DEBUG.more){
		exportBut = new JButton(frame.getNolResourceString(OPTIMIZATIONWKSP_EXPORT));
		exportBut.setActionCommand("Export...");
		exportBut.addActionListener(actionListener);
 		controlButtonPane.add(exportBut);
//		}
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
		if(frame.isDemoVersion()){
			exportBut.setEnabled(false);
		}else{
			exportBut.setEnabled(true);
		}

		Project project = frame.getProject();
		optimizationName.setText(optimization.getName());
		setTitle("Optimization:["+optimization.getName()+"]");

		model = optimization.getModel();
		varContentInPane = new Vector();
		
		delaysStorage = new DelaysStorage();
		maniVars = model.getManipulate();
		outputVars = model.getOutputs();
		inputVars = model.getInputs();
		stateVars = model.getState();
		exogVars = model.getExogenous();
		delaysStorage.add(inputVars, model.getInputDelays());
		delaysStorage.add(outputVars, model.getOutputDelays());
		delaysStorage.add(stateVars, model.getStateDelays());
		delaysStorage.add(model.getStateInput(), model.getStateInputDelays());

		getModelListModel().removeAllElements();
		getModelListModel().addElement(model.getName());
		modelChoice.setText(model.getName());
		Vector models = project.getOptimizationModels();
		int n = models.size();
		if(n<1){
			return;
		}
		refreshVarDisplay();
		refreshVarWeightTable();
		refreshVarBoundsTable();
		refreshVarBoundTable((String)outputVars.elementAt(0),
				delaysStorage.getDelaysFor((String)outputVars.elementAt(0))[0]);
		if(optimization.isCalculated()){
			refreshVarDataDisplay();
			runBut.setEnabled(false);
		}
	}

	private void addVarContentPane(String colObj, int varType, long delay) {
		VarContentPane contentPane = new VarContentPane(colObj, varType,
				delay);
		varListPane.add(contentPane);
		varContentInPane.addElement(contentPane);
	}
	
	private void refreshVars(Vector<String> vars, int varType) {
		for(String var : vars) {
			for (Long delay : delaysStorage.getDelaysFor(var)) {
				addVarContentPane(var, varType, delay);
			}
		}
	}
	
	private void refreshVarDisplay(){
		varListPane.removeAll();
		varContentInPane.removeAllElements();
		
		refreshVars(outputVars, 0);
		refreshVars(maniVars, 1);
		refreshVars(stateVars, 2);
		refreshVars(exogVars, 3);

		varListPane.add(Box.createVerticalGlue());
		varListPane.repaint(0l);
		varListPane.validate();		
		refreshVarSliders();
	}

	public void refreshVarSliders(){
		int vc = varContentInPane.size();
		for(int i=0;i<vc;i++){
			VarContentPane contentPane = (VarContentPane)varContentInPane.elementAt(i);
			double[] ww = optimization.getWeights(contentPane.varName);
			boolean show = false;
			if(Double.compare(ww[1], 0.0) != 0){
				show = true;
			}else{
				show = false;
			}
//			System.out.println("name="+contentPane.varName+"  show="+show+"  ww[1] ="+ww[1] );
			if(exogVars.contains(contentPane.varName)){
				ww[1] = 1.0;
				show = true;
			}
//			System.out.println("name="+contentPane.varName+"  show="+show+"  ww[1] ="+ww[1] );

			contentPane.varSlider.setShowSetpoint(show);

			if(Double.compare(ww[2], 0.0) != 0){
				show = true;
			}else{
				show = false;
			}
			contentPane.varSlider.setShowSoftLow(show);

			if(Double.compare(ww[3], 0.0) != 0){
				show = true;
			}else{
				show = false;
			}
			contentPane.varSlider.setShowSoftHigh(show);
			contentPane.varSlider.repaint(0l);
			contentPane.varSlider.validate();
		}			
	}

	private void refreshVarDataDisplay(){
		Matrix Y = optimization.getYResult();
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
				int delaysBefore = 0; 
				for(int j=0;j<inputIndex;j++){
					if(stateInputs.contains(inputVars.elementAt(j))){
						stateInputCount++;
					} else {
						delaysBefore += delaysStorage.getDelaysFor((String)inputVars.elementAt(j)).length-1; 
					}
				}
				int dc = 0;
				Long d[] = delaysStorage.getDelaysFor(contentPane.varName);
				for(dc=0; dc<d.length;dc++){
					if (d[dc]== contentPane.delay){
						break;
					}
				}
				double value = X.get(0,sic+inputIndex-stateInputCount+delaysBefore+dc);
				contentPane.currentValueLabel.setText(DataUtilities.doubleToString(value,sigDigits));
				contentPane.varSlider.setValues(5,value);
			}
			double[] bb = optimization.getBounds(contentPane.varName, contentPane.delay);
			refreshSlider(contentPane.varName,0,bb[2],contentPane.delay);
		}
		varListPane.repaint(0l);
		varListPane.validate();
	}

	private void refreshVarWeightTable(){
		int nm = maniVars.size();
		int ns = stateVars.size();
		int no = outputVars.size();
		Vector varNames = new Vector();
		Vector weights = new Vector();
		for(int i=0;i<no;i++){
			String colObj = (String)outputVars.elementAt(i);
			double[] ww = optimization.getWeights(colObj);
			varNames.addElement(colObj);
			weights.addElement(ww);
		}
		for(int i=0;i<nm;i++){
			String colObj = (String)maniVars.elementAt(i);
			double[] ww = optimization.getWeights(colObj);
			varNames.addElement(colObj);
			weights.addElement(ww);
		}
		for(int i=0;i<ns;i++){
			String colObj = (String)stateVars.elementAt(i);
			double[] ww = optimization.getWeights(colObj);
			varNames.addElement(colObj);
			weights.addElement(ww);
		}
		weightTableModel.setContents(varNames,weights);
		weightTableView.repaint(0l);
		weightTableView.validate();
	}

	private void refreshVarBoundsTable(){
		int nv = varContentInPane.size();		
		Vector varNames = new Vector();
		Vector bounds = new Vector();
		Vector delays = new Vector();
		for (int i=0;i<nv;i++) {
			VarContentPane contentPane = (VarContentPane)varContentInPane.elementAt(i);

			double[] bb = optimization.getBounds(contentPane.varName, contentPane.delay);
			varNames.addElement(contentPane.varName);
			bounds.addElement(bb);
			delays.addElement(contentPane.delay);
		}
		boundsTableModel.setContents(varNames, bounds, delays);
		boundsTableView.repaint(0l);
		boundsTableView.validate();
	}

	private void refreshVarBoundTable(String colObj, long delay){
		double[] bb = optimization.getBounds(colObj, delay);
		singleBoundsTableModel.setContents(colObj, bb, delay);
		singleBoundsTableView.repaint(0l);
		singleBoundsTableView.validate();
	}

	private void refreshVarBoundTable(String colObj, double[] bb, long delay){
		singleBoundsTableModel.setContents(colObj, bb, delay);
		singleBoundsTableView.repaint(0l);
		singleBoundsTableView.validate();
	}

	private void showVarReachBound(){
		int vc = varContentInPane.size();
		String varN = "";
		for(int i=0;i<vc;i++){
			VarContentPane contentPane = (VarContentPane)varContentInPane.elementAt(i);
			double[] vals = contentPane.varSlider.getValues();
			if(vals[5]<vals[0] || vals[5]>vals[3]){
				refreshVarBoundTable(contentPane.varName, contentPane.delay);
				break;
			}
		}
	}

	private void refreshSlider(String vn, int type, double value){
		for(int i=0;i<varContentInPane.size();i++){
			VarContentPane contentPane = (VarContentPane)varContentInPane.elementAt(i);
			if(contentPane.varName.equals(vn)){
				contentPane.varSlider.setValues(type,value);
				contentPane.varSlider.repaint(0l);
				contentPane.varSlider.validate();
				break;
			}
		}
	}

	private void refreshSlider(String vn, int type, double value, long delay){
		for(int i=0;i<varContentInPane.size();i++){
			VarContentPane contentPane = (VarContentPane)varContentInPane.elementAt(i);
			if(contentPane.varName.equals(vn) && contentPane.delay == delay) { 
				contentPane.varSlider.setValues(type,value);
				contentPane.varSlider.repaint(0l);
				contentPane.varSlider.validate();
				break;
			}
		}
	}

	private boolean checkInput(){
		return true;
	}
	
	public NolOptimization getOptimization(){
		return optimization;
	}

	public void goThroughDataSeries(){
	
		Project project = frame.getProject();
		Vector availDataSeries = new Vector();
		Vector seriesNames = new Vector();
		RawDataSource rds = project.getRawDataSource(); // SOURCE LEVEL - only one data source
		
		for(int j = 0; j < rds.getNumberOfDataSeries(); j++) { // SERIES level
			DataSeries ds = rds.getDataSeries(j);
			boolean match = true;
			for(int c=0;c<outputVars.size();c++){
				String n = (String)outputVars.elementAt(c);
				if(ds.getVarByName(n) == null){
					match = false;
					break;
				}
			}
			if(match){
				for(int c=0;c<exogVars.size();c++){
					String n = (String)exogVars.elementAt(c);
					if(ds.getVarByName(n) == null){
						match = false;
						break;
					}
				}
			}
			if(match){
				availDataSeries.addElement(ds);
				seriesNames.addElement(ds.getDataSource().getName()+ds.getName());
			}
		}

		// SOURCE: Preprocessors
		for(int i = 0; i < project.getNumberOfPreprocessors(); i++) { // SOURCE LEVEL
			Preprocessor prep = project.getPreprocessorByIndex(i);
			Vector pds = project.getProcessedDataByPreprocessor(prep);
			if(!pds.isEmpty()){
				for(int j=0;j<pds.size();j++){
					DataSeries ds = (DataSeries)pds.elementAt(j);
					boolean match = true;
					for(int c=0;c<outputVars.size();c++){
						String n = (String)outputVars.elementAt(c);
						if(ds.getVarByName(n) == null){
							match = false;
							break;
						}
					}
					if(match){
						for(int c=0;c<exogVars.size();c++){
							String n = (String)exogVars.elementAt(c);
							if(ds.getVarByName(n) == null){
								match = false;
								break;
							}
						}
					}
					if(match){
						availDataSeries.addElement(ds);
						seriesNames.addElement(ds.getDataSource().getName()+ds.getName());
					}
				}
			}
		}

		for(int i = 0; i < project.getNumberOfSimulations(); i++) {
			ResponseSurfaceSimulation sim = project.getSimulation(i);
			for(int j = 0; j < sim.getNumberOfDataSeries(); j++) { // SERIES level
				DataSeries ds = sim.getDataSeries(j);
				boolean match = true;
				for(int c=0;c<outputVars.size();c++){
					String n = (String)outputVars.elementAt(c);
					if(ds.getVarByName(n) == null){
						match = false;
						break;
					}
				}
				if(match){
					for(int c=0;c<exogVars.size();c++){
						String n = (String)exogVars.elementAt(c);
						if(ds.getVarByName(n) == null){
							match = false;
							break;
						}
					}
				}
				if(match){
					availDataSeries.addElement(ds);
					seriesNames.addElement(ds.getDataSource().getName()+ds.getName());
				}
			}
		}
 		if(availDataSeries.isEmpty()){

			frame.showOKDialog(frame.getNolResourceString(NODATASERIES));
//			frame.showOKDialog("No data series is matched for this optimization.");
			return;
		}

		NolSingleChoiceDialog singleChoiceDialog = new NolSingleChoiceDialog
			(frame,frame.getNolResourceString(SELECTDATASERIES),frame.getNolResourceString(DATASERIES)+":", new Vector(), false);
		singleChoiceDialog.setContent
			(frame.getNolResourceString(SELECTDATASERIES),frame.getNolResourceString(DATASERIES)+":", seriesNames, false);
		
		singleChoiceDialog.pack();
		singleChoiceDialog.setBounds(200, 200, 320, 300);
		singleChoiceDialog.setVisible(true);
		if(!singleChoiceDialog.getResult()){
			return;
		}
		int index = singleChoiceDialog.getSelectedIndex();
		if(index < 0){
			return;
		}

		DataSeries ds = (DataSeries)availDataSeries.elementAt(index);

		int ne = exogVars.size();
		int nm = maniVars.size();
		int ns = stateVars.size();
		int no = outputVars.size();
		int row = ds.getRow();
		int col = no+ne;
		Matrix Y = Matlib.createMatrix(row,col);
		int cc;
		for(int c=0;c<col;c++){
			String n="";
			if(c<no){
			  n = (String)outputVars.elementAt(c);
			  cc = ds.getVarIndexByName(n);
			}else{
			  n = (String)exogVars.elementAt(c-no);
			  cc = ds.getVarIndexByName(n);
			}
			try{
				for(int r=0;r<row;r++){
					Y.set(r,c,ds.getValueAt(r,cc));
				}
			} catch (MathException e) {
				System.err.println("Exception: "+e.getMessage());
				e.printStackTrace();
			}
		}
		Matrix I = Matlib.createMatrix(row,1);
		Matlib.findFiniteRows(Y,I);
		try{
			Matlib.getRows(Y,I,Y);
		}catch(MathException evt){
			frame.showOKDialog(frame.getNolResourceString(NOVALIDSETPOINT));
//			frame.showOKDialog("No valid setpoint values.");
			return;
		}
		Matlib.clear(I); // memory leak if not cleared; added by Brian O. Bush, Feb 5, 1998
		if(Y.getRows() == 0 ){
			frame.showOKDialog(frame.getNolResourceString(NOVALIDSETPOINT));
//			frame.showOKDialog("No valid setpoint values.");
			return;
		}

		DataSeries newYDs = new DataSeries(Y);
		newYDs.setName("setpoints");
		newYDs.setDataSource(optimization);
		for(int c=0;c<col;c++){
			String n="";
			Variable varObj = null;
			if(c<no){
			  n = (String)outputVars.elementAt(c);
			  varObj = ds.getVarByName(n);
			}else{
			  n = (String)exogVars.elementAt(c-no);
			  varObj = ds.getVarByName(n);
			}
			try {
				newYDs.setVariableParameters(c,varObj.getTag(),varObj.getName(),varObj.getUnit());
			} catch (MathException ex) {
				// should never be here
			}
		}

		int xcol = 	no+ns+nm;
		Matrix newX = Matlib.zeros(Y.getRows(),xcol);
 		DataSeries newXDs = new DataSeries(newX);
		newXDs.setName("results");
		newXDs.setDataSource(optimization);
		for(int c=0;c<no;c++){
			String n = (String)outputVars.elementAt(c);
			Variable varObj = ds.getVarByName(n);
			try {
				newXDs.setVariableParameters(c,varObj.getTag(),varObj.getName(),varObj.getUnit());
			} catch (MathException ex) {
				// should never be here
			}
		}
		for(int c=0;c<ns;c++){
			String n = (String)stateVars.elementAt(c);
			Variable varObj = ds.getVarByName(n);
			try {
				newXDs.setVariableParameters(no+c,varObj.getTag(),varObj.getName(),varObj.getUnit());
			} catch (MathException ex) {
				// should never be here
			}
		}
		for(int c=0;c<nm;c++){
			String n = (String)maniVars.elementAt(c);
			Variable varObj = ds.getVarByName(n);
			try {
				newXDs.setVariableParameters(no+ns+c,varObj.getTag(),varObj.getName(),varObj.getUnit());
			} catch (MathException ex) {
				// should never be here
			}
		}
/*		Vector varObjs = newYDs.getVarObjects();
		for(int r=0;r<Y.getRows();r++){
			for(int c=0;c<col;c++){
				String varName=varObjs.elementAt(c).toString();
				double[] bb = optimization.getBounds(varName);
				bb[2] = Y.get(r,c);
			}
 			optimization.setCalculated(false);
			try{
				optimization.calulationOptimization();
			}catch(MathException evt){
				frame.showOKDialog("Error calculate optimization.");
				return;
			}
			refreshVarDataDisplay(); 	
			Matrix XResult = optimization.getXResult();
			for(int c=0;c<XResult.getCols();c++){
				newXDs.setValueAt(r,c,XResult.get(0,c));
			}
		}
*/	
		
		
		if(!optimization.getDataSeries().isEmpty()){
			((DataSeries)optimization.getDataSeries().elementAt(0)).emptyDataSeries();
			((DataSeries)optimization.getDataSeries().elementAt(1)).emptyDataSeries();
		}
		optimization.getDataSeries().removeAllElements();
		optimization.getDataSeries().addElement(newYDs);
		optimization.getDataSeries().addElement(newXDs);
		frame.getProjectTree().addDataSeries(newXDs,false);
		frame.getProjectTree().addDataSeries(newYDs,false);
		
		stopBut.setEnabled(true);
		runBut.setEnabled(false);
		throughDataBut.setEnabled(false);
		deleteBut.setEnabled(false);

/*		controlButtonPane.add(stopBut);
		controlButtonPane.add(runCount);
		controlButtonPane.repaint(0l);
		controlButtonPane.validate();
*/

		
		if(isCalculating){
			return;
		}
		isCalculating = true;

		runningThread = 
			new NolOptimizationThread(optimization,newYDs);
		runningThread.addListener((OptimizationListener)actionListener);

		optThread = new Thread(runningThread);
		int prior = optThread.getPriority()-3;
		if(prior <Thread.MIN_PRIORITY){
			prior = Thread.MIN_PRIORITY;
		}
		optThread.setPriority(prior);
		optThread.start();
	}

   /**
     * Control action implementation
     */
    class ControlAction extends AbstractAction implements 
		ListSelectionListener, DocumentListener,OptimizationListener,Runnable{

		private String command;
		private Object source;
		ControlAction(){super("controlAction");}
			
		@Override
		public void completeNewSample(int row){
			refreshVarDataDisplay(); 
			int ne = exogVars.size();
			int nm = maniVars.size();
			int ns = stateVars.size();
			int no = outputVars.size();
			Vector stateInputs = model.getStateInput();
			int sic = stateInputs.size();

			Matrix XResult = optimization.getXResult();
			Matrix YResult = optimization.getYResult();
			DataSeries newXDs = (DataSeries)optimization.getDataSeries().elementAt(1);
			try {
				for(int c=0;c<no;c++){
					newXDs.setValueAt(row,c,YResult.get(0,ns+c));
				}
				for(int c=0;c<ns;c++){
					newXDs.setValueAt(row,no+c,YResult.get(0,c));
				}
				int cc=0;
				for(int c=0;c<nm;c++){
					String n = (String)maniVars.elementAt(c);
					int stateInputIndex = stateInputs.indexOf(n);
					if(stateInputIndex != -1){
						double value = XResult.get(0,stateInputIndex);
						newXDs.setValueAt(row,no+ns+c,value);
					}else{
						double value = XResult.get(0,sic+cc);
						newXDs.setValueAt(row,no+ns+c,value);
						cc++;
					}
				}
			} catch (MathException e) {
				System.err.println("Exception: "+e.getMessage());
				e.printStackTrace();
			}
			int rr = newXDs.getRow();
			runCountLabel.setText("Calculated/All");
			runCount.setText("("+String.valueOf(row+1)+"/"+String.valueOf(rr+1)+")");
		}

		@Override
		public void completeCalculation(){
			DataSeries inputData = (DataSeries)optimization.getDataSeries().elementAt(0);
			DataSeries outputData = (DataSeries)optimization.getDataSeries().elementAt(1);
			inputData.calculateVarStatistics();
			outputData.calculateVarStatistics();

			runCountLabel.setText("");
			runCount.setText("");
			stopBut.setEnabled(false);
			throughDataBut.setEnabled(true);
/*			controlButtonPane.remove(stopBut);
			controlButtonPane.remove(runCount);
*/
			controlButtonPane.repaint(0l);
			controlButtonPane.validate();
			isCalculating = false;
		}
		@Override
		public void valueChanged(ListSelectionEvent e){
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
/*			if(source == modelChoice){
				int index = modelChoice.getSelectedIndex();
				Vector ms = project.getOptimizationModels();
				currentModel = (NolModel2)ms.elementAt(index);
				if(currentModel instanceof NolOptimizeModel){
					maniVars = model.getInputs();
					outputVars = model.getOutputs();	
					stateVars = model.getState();
					exogVars = model.getExogenous();	
				}else{
					maniVars = currentModel.getInputs();
					outputVars = currentModel.getOutputs();	
					stateVars = new Vector();
					exogVars = new Vector();
				}
				refreshVarDisplay();
*/			if(command.equals("Run")){
//System.out.println("isCalculating="+isCalculating);
				if(isCalculating) {
					return;
				}
				isCalculating = true;
				if(optimization.isCalculated()){
					isCalculating = false;
					return;
				}
				boolean firstTime = true;
				boolean continueTraining = false;
				int nmx = -1;
				Matrix P = Matlib.createMatrix();
				for(;;){
					if(firstTime){
						try{
							setWaitCursor(true);
							optimization.calculationOptimization();
							continueTraining = false;
							setWaitCursor(false);
						}catch(MathException evt){
							setWaitCursor(false);
							if(evt instanceof OptException){
								int flag = ((OptException)evt).getFlag();
//System.out.println("flag0="+flag);
								if(flag == 0){
									nmx = reCalculate();
									if(nmx>0){
//System.out.println("nmx="+nmx);
										continueTraining = true;
										P = ((OptException)evt).getSimplexMatrix();
									}else{
										continueTraining = false;
									}
								}
							}
						}
						firstTime = false;
					}else{
//System.out.println("continueTraining="+continueTraining);
						if(continueTraining){
							try{
								setWaitCursor(true);
								optimization.reCalulationOptimization(P,nmx);
								continueTraining = false;
								setWaitCursor(false);
							}catch(MathException evt){
								setWaitCursor(false);
								if(evt instanceof OptException){
									int flag = ((OptException)evt).getFlag();
									if(flag == 0){
										nmx = reCalculate();
										if(nmx>0){
											continueTraining = true;
											P = ((OptException)evt).getSimplexMatrix();
										}else{
											continueTraining = false;
										}
									}
								}
							}
						}else{
//							System.out.println("break");
							break;
						}
					}
				}
				refreshVarDataDisplay();
				showVarReachBound();
				runBut.setEnabled(false);
				isCalculating = false;
			}else if(command.equals("Delete")){
				frame.removeOptimization(optimization);
			}else if(command.equals("Go Through Data...")){
				if(isCalculating){
					return;
				}
				goThroughDataSeries();
			}else if(command.equals("Export...")){
 				JFileChooser fileChooser = new JFileChooser();
				fileChooser.setDialogTitle("Export Optimization");
				NolFileFilter filter1 = new NolFileFilter(
				new String[] {"opt"}, "Binary Optmization File"
				);
				fileChooser.addChoosableFileFilter(filter1);
				fileChooser.setFileFilter(filter1);
				fileChooser.setDialogType(JFileChooser.SAVE_DIALOG);

				fileChooser.setSelectedFile(new File(optimization.getName()+".opt"));
				fileChooser.setLocation(200,200);			
				
				File currentDirectory = new File(NolMainFrame.miscDirectory);
				if(currentDirectory.exists()) {
					fileChooser.setCurrentDirectory(currentDirectory);
				}
							
				int retval = fileChooser.showSaveDialog(frame);

				fileChooser.setFileFilter(null);
				fileChooser.removeChoosableFileFilter(filter1);

				if(retval == JFileChooser.CANCEL_OPTION){
					return;
				}
				File currentPath = fileChooser.getSelectedFile();
				if(currentPath == null){
					return;
				}

				String file = currentPath.getName();
				String directory = currentPath.getParent();

	/*			FileDialog fileDialog = new FileDialog((Frame)frame);
				fileDialog.setMode(FileDialog.SAVE);
				fileDialog.setFile(optimization.getName()+".opt");
				fileDialog.setTitle("Export Optimization");
				fileDialog.setLocation(200,200);			
				fileDialog.show();

				String file = fileDialog.getFile();
				if (file == null) return;
				String directory = fileDialog.getDirectory();
	*/			   
				// try to start writing
				
				String pName = file;
				int dotInd = file.indexOf(".");
				if(dotInd == -1){
					file = file+".opt";
				}else{
					pName = file.substring(0,dotInd);	
				}
				OnlineOptimizer optimizer = null;
				try{
					optimizer = new OnlineOptimizer(pName,optimization);
				}catch(MathException evt){
					Toolkit.getDefaultToolkit().beep();
					frame.showOKDialog(frame.getNolResourceString(ERRORINMAKINGOPTIMIZER));
//					frame.showOKDialog("Error in making the online optimizer.");
					return;
				}
				try {
					Class versionManagerClass = Class.forName("com.gensym.nols.data.VersionManagerForOnlineOptimizer");
					Object versionManager = versionManagerClass.newInstance();
					Method method = versionManagerClass.getMethod("setOptimizer",new Class[] {optimizer.getClass()});
					method.invoke(versionManager,new Object[] {optimizer});
					method = versionManagerClass.getMethod("saveToFile",new Class[] {directory.getClass(), file.getClass()});
					method.invoke(versionManager,new Object[] {directory, file});
				} catch (ClassNotFoundException ex) {
					frame.showOKDialog(frame.getNolResourceString(NOVALIDELICENSE));
				} catch (InstantiationException ex) {
					frame.showOKDialog(frame.getNolResourceString(NOVALIDELICENSE));
				} catch (IllegalAccessException ex) {
					frame.showOKDialog(frame.getNolResourceString(NOVALIDELICENSE));
				} catch (NoSuchMethodException ex) {
					frame.showOKDialog(frame.getNolResourceString(NOVALIDELICENSE));
				} catch (InvocationTargetException ex) {
					frame.showOKDialog(frame.getNolResourceString(NOVALIDELICENSE));
				} catch (RuntimeException ex) {
					frame.showOKDialog(frame.getNolResourceString(NOVALIDELICENSE));
				}
				//VersionManagerForOnlineOptimizer verObj = new VersionManagerForOnlineOptimizer();
				//verObj.setOptimizer(optimizer);
				//verObj.saveToFile(directory,file);				
				Toolkit.getDefaultToolkit().beep();

			}else if(command.equals("Stop")){
				isCalculating = false;
				runningThread.setStop(true);
//				optThread.stop();
				runCountLabel.setText("");
				runCount.setText("");
				stopBut.setEnabled(false);
				runBut.setEnabled(false);
				throughDataBut.setEnabled(true);
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
					frame.getProjectTree().changeOptimizationName(optimization,true);
				}else{
					nm = optimization.getName();
					optimizationName.setText(nm);
				}
			}else{
/*				int c = exogVars.size();
				for(int i=0;i<c;i++){
					String name = ((Variable)exogVars.elementAt(i)).getName();
					if(command.equals(name)){
						JFrame frame = getFrame();
						SingleVarSetDialog singleDialog = new SingleVarSetDialog(frame, "Set Parameters for"+name, true);
						singleDialog.pack();
						singleDialog.show();
						return;
					}
				}
				c = maniVars.size();
				for(int i=0;i<c;i++){
					String name = ((Variable)maniVars.elementAt(i)).getName();
					if(command.equals(name)){
						JFrame frame = getFrame();
						SingleVarSetDialog singleDialog = new SingleVarSetDialog(frame, "Set Parameters for"+name, true);
						singleDialog.pack();
						singleDialog.show();
						return;
					}
				}
				c = stateVars.size();
				for(int i=0;i<c;i++){
					String name = ((Variable)stateVars.elementAt(i)).getName();
					if(command.equals(name)){
						JFrame frame = getFrame();
						SingleVarSetDialog singleDialog = new SingleVarSetDialog(frame, "Set Parameters for"+name, true);
						singleDialog.pack();
						singleDialog.show();
						return;
					}
				}
				c = outputVars.size();
				for(int i=0;i<c;i++){
					String name = ((Variable)outputVars.elementAt(i)).getName();
					if(command.equals(name)){
						JFrame frame = getFrame();
						SingleVarSetDialog singleDialog = new SingleVarSetDialog(frame, "Set Parameters for"+name, true);
						singleDialog.pack();
						singleDialog.show();
						return;
					}
				}*/
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

	class WeightTableModel extends AbstractTableModel{
		private int row,col;
		private Vector names;
		private Vector weights;
		private String[] colHd = {
			frame.getNolResourceString(OPTIMIZATIONWKSP_VARIABLE),
			frame.getNolResourceString(OPTIMIZATIONWKSP_LINEARWEIGHT),
			frame.getNolResourceString(OPTIMIZATIONWKSP_SETPOINTWEIGHT),
			frame.getNolResourceString(OPTIMIZATIONWKSP_SLBWEIGHT),
			frame.getNolResourceString(OPTIMIZATIONWKSP_SUBWEIGHT)};

//			"Variable","Linear Weight","Setpoint Weight","SLB Weight","SUB Weight"};
		public WeightTableModel(){
			row = 0;
			col = 5;
			names = new Vector();
		}
		public void setContents(Vector names,Vector weights){
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
				return names.elementAt(r);
			}else if(c == 1){
				double[] ww = (double[])weights.elementAt(r);
				return String.valueOf(ww[0]);
			}else if(c == 2){
				double[] ww = (double[])weights.elementAt(r);
				return String.valueOf(ww[1]);
			}else if(c == 3){
				double[] ww = (double[])weights.elementAt(r);
				return String.valueOf(ww[2]);
			}else if(c == 4){
				double[] ww = (double[])weights.elementAt(r);
				return String.valueOf(ww[3]);
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
					double[] ww = (double[])weights.elementAt(r);
					ww[0] = v;
				}catch( NumberFormatException evt){
					System.err.println("Non-Fatal exception: " + evt.getMessage());
					evt.printStackTrace();
				}
			}else if(c==2){
				try{
					double v = Double.valueOf((String)aValue).doubleValue();
					double[] ww = (double[])weights.elementAt(r);
					ww[1] = v;
				}catch( NumberFormatException evt){
					System.err.println("Non-Fatal exception: " + evt.getMessage());
					evt.printStackTrace();
				}
			}else if(c==3){
				try{
					double v = Double.valueOf((String)aValue).doubleValue();
					double[] ww = (double[])weights.elementAt(r);
					ww[2] = v;
				}catch( NumberFormatException evt){
					System.err.println("Non-Fatal exception: " + evt.getMessage());
					evt.printStackTrace();				
				}
			}else if(c==4){
				try{
					double v = Double.valueOf((String)aValue).doubleValue();
					double[] ww = (double[])weights.elementAt(r);
					ww[3] = v;
				}catch( NumberFormatException evt){
					System.err.println("Non-Fatal exception: " + evt.getMessage());
					evt.printStackTrace();
				}
			}
			optimization.setCalculated(false);
			runBut.setEnabled(true);
		}
		public Vector getNames(){
			return names;
		}
	}

	class BoundsTableModel extends AbstractTableModel{
		private int row,col;
		private Vector names;
		private Vector bounds;
		private Vector delays;
		private String[] colHd; 

		public BoundsTableModel(){
			row = 0;
			col = 6;
			names = new Vector();
			InitColHd();
		}
		
		private void InitColHd()
		{
//			"Variable","Linear Weight","Setpoint Weight","SLB Weight","SUB Weight"};
			colHd = new String[6];
			colHd[0] = frame.getNolResourceString(OPTIMIZATIONWKSP_VARIABLE);
			colHd[1] = frame.getNolResourceString(OPTIMIZATIONWKSP_DELAY);
			switch (delayTimeUnit) {
			case 1: 
				colHd[1] += "(" + frame.getNolResourceString(HOURLABEL) + ")"; 
				break; 			
			case 2: 
				colHd[1] += "(" + frame.getNolResourceString(MINUTELABEL) + ")";
				break;
			case 3: 
				colHd[1] += "(" + frame.getNolResourceString(SECONDLABEL) + ")"; 
				break;
			default: 
				colHd[1] += "";
			}
			colHd[2] = frame.getNolResourceString(OPTIMIZATIONWKSP_LB);
			colHd[3] = frame.getNolResourceString(OPTIMIZATIONWKSP_SLB);
			colHd[4]= frame.getNolResourceString(OPTIMIZATIONWKSP_SUB);
			colHd[5] = frame.getNolResourceString(OPTIMIZATIONWKSP_UB);
		}

	   
	
		public void setContents(Vector names, Vector bounds, Vector delays){
			this.names = names;
			this.bounds = bounds;
			this.delays = delays;
			row = names.size();
		}
		@Override
		public int getColumnCount() { return col; }
		@Override
		public int getRowCount() { return row;}
		@Override
		public Object getValueAt(int r, int c){
			double[] bb = (double[])bounds.elementAt(r);
			switch (c) {
				case 0:	
					return names.elementAt(r);
				case 1:
					long d = (Long)delays.elementAt(r);
					double convertedDelay = d;
					switch (delayTimeUnit) {
						case 1:	
							convertedDelay = d / (double)(1000 * 60 * 60); 
							break; //Hours
						case 2: 
							convertedDelay = d / (double)(1000 * 60);
							break;	  //Minutes
						case 3: 
							convertedDelay = d / 1000d;
							break;	 		  //Seconds
						default:
					}
					return String.valueOf(convertedDelay);
				case 2:
					return String.valueOf(bb[0]);
				case 3:
					return String.valueOf(bb[1]);
				case 4:
					return String.valueOf(bb[3]);
				case 5:
					return String.valueOf(bb[4]);
				default:
					return "";
			}
		}
		@Override
		public String getColumnName(int c) {
			return colHd[c];
		}
		@Override
		public boolean isCellEditable(int r, int c) {
			return !(c<2);
		}		
		@Override
		public void setValueAt(Object aValue, int r, int c) {
			double[] bb = (double[])bounds.elementAt(r);
			String varName = (String)names.elementAt(r);
			if(c==2){
				try{
					double v = Double.valueOf((String)aValue).doubleValue();
					if(v>bb[4]){
						v = bb[4];
					}
					bb[0] = v;
					refreshSlider(varName, 1, v);
					if(bb[1] < v){
						bb[1] = v;
						refreshSlider(varName, 3, v);
					}
				}catch( NumberFormatException evt){
				}
			}else if(c==3){
				try{
					double v = Double.valueOf((String)aValue).doubleValue();
					if(v<bb[0]){
						v = bb[0];
					}else if(v>bb[4]){
						v = bb[4];
					}
					bb[1] = v;
					refreshSlider(varName, 3, v);
				}catch( NumberFormatException evt){
				}
			}else if(c==4){
				try{
					double v = Double.valueOf((String)aValue).doubleValue();
					if(v<bb[0]){
						v = bb[0];
					}else if(v>bb[4]){
						v = bb[4];
					}
					bb[3] = v;
					refreshSlider(varName, 4, v);
				}catch( NumberFormatException evt){
				}
			}else if(c==5){
				try{
					double v = Double.valueOf((String)aValue).doubleValue();
					if(v<bb[0]){
						v = bb[0];
					}
					bb[4] = v;
					refreshSlider(varName, 2, v);
					if(bb[3] > v){
						bb[3] = v;
						refreshSlider(varName, 4, v);
					}
				}catch( NumberFormatException evt){
				}
			}
			boundsTableView.repaint(0l);
			boundsTableView.validate();
			optimization.setCalculated(false);
			runBut.setEnabled(true);
		}
		public Vector getNames(){
			return names;
		}
	}

	class SingleBoundsTableModel extends AbstractTableModel{
		private int row,col;
		private String varName;
		private double[] bounds;
		private long delay;
		private String[] colHd = {
			frame.getNolResourceString(OPTIMIZATIONWKSP_VARIABLES),
			frame.getNolResourceString(OPTIMIZATIONWKSP_DELAY),
			frame.getNolResourceString(OPTIMIZATIONWKSP_SETPOINT),
			frame.getNolResourceString(OPTIMIZATIONWKSP_LB),
			frame.getNolResourceString(OPTIMIZATIONWKSP_SLB),
			frame.getNolResourceString(OPTIMIZATIONWKSP_SUB),
			frame.getNolResourceString(OPTIMIZATIONWKSP_UB),
			frame.getNolResourceString(OPTIMIZATIONWKSP_MIN),
			frame.getNolResourceString(OPTIMIZATIONWKSP_MAX)};
//		private String[] colHd = {"Variable","Setpoint","LB","SLB","SUB","UB","Min","Max"};
		private int digits = 5;

		public SingleBoundsTableModel(){
			row = 1;
			col = 9;
		}
		public void setContents(String varName, double[] bounds, long delay){
			this.varName = varName;
			this.bounds = bounds;
			this.delay = delay;
		}
		@Override
		public int getColumnCount() { return col; }
		@Override
		public int getRowCount() { return row;}

		@Override
		public Object getValueAt(final int r, final int c) {
			int column = c;
			if (bounds == null){
				column = -1;
			}
			switch (column) {
			case 0:
				if (varName == null) {
					return "name";
				}else {
					return varName;
				}
			case 1:
				double convertedDelay = delay;
				switch (delayTimeUnit) {
					case 1:	
						convertedDelay = delay / (double)(1000 * 60 * 60); 
						break; //Hours
					case 2: 
						convertedDelay = delay / (double)(1000 * 60); 
						break;	  //Minutes
					case 3: 
						convertedDelay = delay / 1000d; 
						break;	 		  //Seconds
					default:
				}
				return String.valueOf(convertedDelay);
			case 2:
				return Utilities.formatDouble(bounds[2], digits);
			case 3:
				return Utilities.formatDouble(bounds[0], digits);
			case 4:
				return Utilities.formatDouble(bounds[1], digits);
			case 5:
				return Utilities.formatDouble(bounds[3], digits);
			case 6:
				return Utilities.formatDouble(bounds[4], digits);
			case 7:
				return Utilities.formatDouble(bounds[5], digits);
			case 8:
				return Utilities.formatDouble(bounds[6], digits);
			default:
				return "";
			}
		}
		@Override
		public String getColumnName(int c) {
			return colHd[c];
		}
		@Override
		public boolean isCellEditable(int r, int c) {
			return !((c<2) || (c>6));
		}		
		@Override
		public void setValueAt(Object aValue, int r, int c) {
			if(c==2){
				try{
					double v = Double.valueOf((String)aValue).doubleValue();
					if(v<bounds[0]){
						v = bounds[0];
					}else if(v>bounds[4]){
						v = bounds[4];
					}
					bounds[2] = v;
					refreshSlider(varName, 0, v, delay);
				}catch( NumberFormatException evt){
//					System.err.println("Non-Fatal exception: " + evt.getMessage());
//					evt.printStackTrace();
				}
			}else if(c==3){
				try{
					double v = Double.valueOf((String)aValue).doubleValue();
					if(v>bounds[4]){
						v = bounds[4];
					}
					bounds[0] = v;
					refreshSlider(varName, 1, v, delay);
					if(bounds[1] < v){
						bounds[1] = v;
						refreshSlider(varName, 3, v, delay);
						singleBoundsTableView.repaint(0l);
						singleBoundsTableView.validate();
					}
				}catch( NumberFormatException evt){
//					System.err.println("Non-Fatal exception: " + evt.getMessage());
//					evt.printStackTrace();				
				}
			}else if(c==4){
				try{
					double v = Double.valueOf((String)aValue).doubleValue();
					if(v<bounds[0]){
						v = bounds[0];
					}else if(v>bounds[4]){
						v = bounds[4];
					}
					bounds[1] = v;
					refreshSlider(varName, 3, v, delay);
				}catch( NumberFormatException evt){
//					System.err.println("Non-Fatal exception: " + evt.getMessage());
//					evt.printStackTrace();
				}
			}else if(c==5){
				try{
					double v = Double.valueOf((String)aValue).doubleValue();
					if(v<bounds[0]){
						v = bounds[0];
					}else if(v>bounds[4]){
						v = bounds[4];
					}
					bounds[3] = v;
					refreshSlider(varName, 4, v, delay);
				}catch( NumberFormatException evt){
//					System.err.println("Non-Fatal exception: " + evt.getMessage());
//					evt.printStackTrace();
				}
			}else if(c==6){
				try{
					double v = Double.valueOf((String)aValue).doubleValue();
					if(v<bounds[0]){
						v = bounds[0];
					}
					bounds[4] = v;
					refreshSlider(varName, 2, v, delay);
					if(bounds[3] > v){
						bounds[3] = v;
						refreshSlider(varName, 4, v, delay);
						singleBoundsTableView.repaint(0l);
						singleBoundsTableView.validate();
					}
				}catch( NumberFormatException evt){
//					System.err.println("Non-Fatal exception: " + evt.getMessage());
//					evt.printStackTrace();
				}
			}
/*			}else if(c==6){
				try{
					double v = Double.valueOf((String)aValue).doubleValue();
					bounds[5] = v;
				}catch( NumberFormatException evt){}
			}else if(c==7){
				try{
					double v = Double.valueOf((String)aValue).doubleValue();
					bounds[6] = v;
				}catch( NumberFormatException evt){}
			}
*/
			optimization.setCalculated(false);
			runBut.setEnabled(true);
		}
		public String getVarName(){
			return varName;
		}
		public long getDelay(){
			return delay;
		}
	}


	class VarContentPane extends JPanel implements MouseListener, NolSliderListener{
		protected String varName;
		protected int colorType;
		protected NolSlider varSlider;
		protected BorderedTextField currentValueLabel;
		protected double lb, slb, sub, ub;
		private long delay;

		public VarContentPane(String n, int type, long aDelay) {
			delay = aDelay;
			varName = n;
			colorType = type;
			initialLayout();
		}

		private void initialLayout() {
			setLayout(new GridLayout(1, NUMBER_OF_COLUMNS_IN_VARS_PANE, 0, 0));
			BorderedTextField nameLabel = new BorderedTextField(varName);
			nameLabel.addMouseListener(this);
			int stype = 0;
			double[] bb = optimization.getBounds(varName, delay);
			if(colorType == 3) {
				stype = 1;
				// signature: public NolSlider(double min, double max,
				// 		double sp, int t){
				varSlider = new NolSlider(bb[5], bb[6], bb[2], stype);
			}else{
				// signature: public NolSlider(double min, double max,
				//		double lb, double slb, double sub, double ub,
				//		double sp, int t)
				varSlider = new NolSlider(bb[5], bb[6], bb[0], bb[1], bb[3],
						bb[4], bb[2], stype);
			}
			varSlider.addNolSliderListener(this);
			currentValueLabel = new BorderedTextField("",varName);
			currentValueLabel.addMouseListener(this);
			
			if(colorType == 0){
				setBackground(new Color(242,244,176));
				nameLabel.setToolTipText(frame.getNolResourceString(
						OPTIMIZATIONWKSP_OUTPUTVARIABLE));
				currentValueLabel.setToolTipText(frame.getNolResourceString(
						OPTIMIZATIONWKSP_OUTPUTVARIABLE));
			}else if(colorType == 1){
				setBackground(new Color(232,235,207));
				nameLabel.setToolTipText(frame.getNolResourceString(
						OPTIMIZATIONWKSP_MANIPULATEDVARIABLE));
				currentValueLabel.setToolTipText(frame.getNolResourceString(
						OPTIMIZATIONWKSP_MANIPULATEDVARIABLE));
			}else if(colorType == 2){
				setBackground(new Color(200,204,28));
				nameLabel.setToolTipText(frame.getNolResourceString(
						OPTIMIZATIONWKSP_STATEVARIABLE));
				currentValueLabel.setToolTipText(frame.getNolResourceString(
						OPTIMIZATIONWKSP_STATEVARIABLE));
			}else if(colorType == 3){
				setBackground(new Color(119,121,17));
				nameLabel.setToolTipText(frame.getNolResourceString(
						OPTIMIZATIONWKSP_EXOGENOUSVARIABLE));
				currentValueLabel.setToolTipText(frame.getNolResourceString(
						OPTIMIZATIONWKSP_EXOGENOUSVARIABLE));
			}

			add(nameLabel);
			double convertedDelay = delay;
			switch (delayTimeUnit) {
				case 1:	
					convertedDelay = delay / (double)(1000 * 60 * 60); 
					break; //Hours
				case 2: 
					convertedDelay = delay / (double)(1000 * 60); 
					break;	  //Minutes
				case 3: 
					convertedDelay = delay / 1000d; 
					break;	 		  //Seconds
				default:
			}
			add(new BorderedTextField(Double.toString(convertedDelay), varName));
			add(varSlider);
			add(currentValueLabel);
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
			if(m.getSource() instanceof BorderedTextField){ 
				 BorderedTextField varText = (BorderedTextField)m.getSource();
				 String fieldVarName = varText.getVarName();
				 refreshVarBoundTable(fieldVarName, delay);
			}
		}
		@Override
		public void valueChanged(NolSliderEvent evt){
			double[] bb = optimization.getBounds(varName, delay);
			bb[0] = evt.getLowLimit();
			bb[1] = evt.getSoftLow();
			bb[2] = evt.getSetpoint();
			bb[3] = evt.getSoftHigh();
			bb[4] = evt.getHighLimit();			
			refreshVarBoundTable(varName, bb, delay);
			optimization.setCalculated(false);
			runBut.setEnabled(true);
		}

		public long getDelayValue() {
			return delay;
		}
	}

	static class VarContentHeaderPane extends JPanel {
		
		private static final String[] LABEL_NAMES = new String [] {
			OPTIMIZATIONWKSP_VARIABLE, OPTIMIZATIONWKSP_DELAY,
			OPTIMIZATIONWKSP_VALUESLIDER, OPTIMIZATIONWKSP_RESULT};

		public VarContentHeaderPane(NolMainFrame mainFrame, int delayTimeUnit) {
			setLayout(new GridLayout(1, NUMBER_OF_COLUMNS_IN_VARS_PANE, 0, 0));
			String delayLabel = "";
			for (int i = 0; i < NUMBER_OF_COLUMNS_IN_VARS_PANE; i++) {
				BorderedLabel col;
				if (OPTIMIZATIONWKSP_DELAY.equals(LABEL_NAMES[i])) {
					switch (delayTimeUnit) {
						case 1: 
							delayLabel = "(" + mainFrame.getNolResourceString(HOURLABEL) + ")"; 
							break; 			
						case 2: 
							delayLabel = "(" + mainFrame.getNolResourceString(MINUTELABEL) + ")"; 
							break;
						case 3: 
							delayLabel = "(" + mainFrame.getNolResourceString(SECONDLABEL) + ")"; 
							break;
						default: 
							delayLabel = "";
					}  
					col = new BorderedLabel(mainFrame
							.getNolResourceString(LABEL_NAMES[i])+ delayLabel);
				} else {
					col = new BorderedLabel(mainFrame
						.getNolResourceString(LABEL_NAMES[i]));
				}
				
				col.setHorizontalAlignment(SwingConstants.CENTER);
				add(col);
			}
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
		
		public String getText() {
			return text;
		}
    }
    
    static class BorderedLabel extends JLabel {

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
					refreshVarSliders();
				}
			}
		}
	}

	private int reCalculate(){
		getRCDLG().setNMAX(optimization.getMaxIteration());
		getRCDLG().setVisible(true);
		return getRCDLG().getResult();
	}

	private ReCalculateConfirmDialog getRCDLG(){
		if(rCDLG == null){
			rCDLG = new ReCalculateConfirmDialog(frame, 
				frame.getNolResourceString(RECALCULATEDIALOGTITLE), 
				frame.getNolResourceString(RECALCULATEDIALOGLABEL), 
				optimization.getMaxIteration());
		}
		return rCDLG;
	}

	private class ReCalculateConfirmDialog extends JDialog {
		private int result;
		private JTextField newNMX;
		private ButtonAction buttonListener;
		private Font labelFont = new Font("Dialog", Font.BOLD, 14);

		public ReCalculateConfirmDialog(JFrame dw, String title, String labelText, int nmx) {
			super(dw, title, true);
			result = nmx;
			//Create middle section.
			JPanel workSpace = new JPanel(new BorderLayout());
 			workSpace.setBorder(new EmptyBorder(10,10,10,10));
			String iconLocation = "info.gif";
			URL url = this.getClass().getResource(iconLocation);
			ImageIcon butIcon = new ImageIcon(url);			
			workSpace.add("West",new JLabel(butIcon));

			JPanel labelPane = new JPanel(new GridLayout());
 			labelPane.setBorder(new EmptyBorder(10,10,0,0));
			JTextArea labelArea = new JTextArea(labelText);
			labelArea.setFont(labelFont);
			labelArea.setLineWrap(true);
			labelArea.setWrapStyleWord(true);
			labelArea.setEditable(false);
			labelArea.setBackground(labelPane.getBackground());
			labelPane.add(labelArea);
			workSpace.add("Center",labelPane);


			JPanel southPane = new JPanel(new GridLayout(2,1,5,5));
			JPanel editPane = new JPanel(new GridLayout());
			editPane.setBorder(new TitledBorder(new EmptyBorder(5, 25, 5, 25),               
				frame.getNolResourceString(NEWNMX)+":", TitledBorder.LEFT , TitledBorder.TOP));
			newNMX = new JTextField(nmx+"");
			editPane.add(newNMX);
			JPanel controlPane = new JPanel(new FlowLayout(FlowLayout.CENTER));
			buttonListener = new ButtonAction();
			JButton button = new JButton(frame.getNolResourceString(YES));
			button.setActionCommand("Yes");
			button.addActionListener(buttonListener);
			controlPane.add(button);
			button = new JButton(frame.getNolResourceString(NO));
			button.setActionCommand("No");
			button.addActionListener(buttonListener);
			controlPane.add(button);

			southPane.add(editPane);
			southPane.add(controlPane);

			getContentPane().setLayout(new BorderLayout());
			getContentPane().add("Center", workSpace);
			getContentPane().add("South", southPane);
			setBounds(200,200,400,250);	 // initialize size
		}


		public int getResult(){
			return result;
		}

		public void setNMAX(int nmax){
			result = nmax;
			newNMX.setText(result+"");
		}

		class ButtonAction extends AbstractAction {
			ButtonAction() {super("title");}
			@Override
			public void actionPerformed(ActionEvent event) {
				String command = event.getActionCommand(); 
				if(command.equals("No")){
					result = -1;
				}else if(command.equals("Yes")){
  					String s = newNMX.getText();
					try{
						int c = Integer.valueOf(s).intValue();
						if(c>0){
							result = c;
						}else{
							result = -1;
						}
					}catch(NumberFormatException  evt){
							result = -1;
					}
				}
				ReCalculateConfirmDialog.this.setVisible(false);
			}
		}
	}

 	class OptInternalFrameAdapter extends InternalFrameAdapter {
		OptInternalFrameAdapter() {super();}
		@Override
		public void internalFrameClosed(InternalFrameEvent e){
//System.out.println("closing window");
			isCalculating = false;
			if(optThread != null&&runningThread!= null){
				runningThread.setStop(true);
//				optThread.stop();
			}
			runCountLabel.setText("");
			runCount.setText("");
			stopBut.setEnabled(false);
			runBut.setEnabled(true);
			throughDataBut.setEnabled(true);
			deleteBut.setEnabled(true);
			controlButtonPane.repaint(0l);
			controlButtonPane.validate();
		}
	}

	public Vector<VarContentPane> getVarContentPanes() {
		return varContentInPane;
	}
}

