package com.gensym.nols.wksp;

import java.awt.*;
import java.awt.event.*;
import java.util.*;

import javax.swing.*;
import javax.swing.border.*;

import com.gensym.math.*;
import com.gensym.math.matrix.*;
import com.gensym.math.datafit.*;

import com.gensym.nols.main.*;
import com.gensym.nols.util.*;
import com.gensym.nols.dlg.*;
import com.gensym.nols.data.*;
import com.gensym.nols.chart.line.*;
import com.gensym.nols.chart.scatter.*;

public class NolModelPredVsActWKSP extends NolInternalFrame {

	private NolModel2 model;
	private Matrix Y;
	private Matrix YP;
	private Matrix[] YPred;
	private Matrix[] YPredMask;
	private Matrix S;
	private Matrix SP;
	private Matrix[] SPred;
	private Matrix[] SPredMask;
	private ControlAction actionListener;
	private boolean twoModels;
	private boolean noFire;
	private boolean showOutputLineChart;
	private boolean showStateLineChart;
	private long[] outputTime;
	private long[] stateTime;
 	private JPanel outputViewPane;
 	private JPanel stateViewPane;
 	private JPanel outputLegendPane;
 	private JPanel stateLegendPane;
	private JPanel outputExportPane;
 	private JPanel stateExportPane;
	private JComboBox outputVarChoice;
	private JComboBox stateVarChoice;
	private JComboBox outputModelChoice;
	private JComboBox stateModelChoice;
	private JRadioButton plotTrain;
	private JRadioButton plotTest;
	private JRadioButton plotTrain2;
	private JRadioButton plotTest2;
	private LineChart outputLineChart;
	private ScatChart outputScatChart;
	private LineChart stateLineChart;
	private ScatChart stateScatChart;
	// new in 2.1
	private int currentPlotOption;
	private int currentModelOption;
	private int outputDisplayIndex;
	private int stateDisplayIndex;

	private ColoredSquare outputPredLine;
	private ColoredSquare outputActLine;
	private ColoredSquare statePredLine;
	private ColoredSquare stateActLine;
	private Color predictedColor;  // MK added, 5/16/99 so colors persist when changing plots
	private Color actualColor; 
	private JButton outputPredLineBut;
	private JButton statePredLineBut;
	private JButton outputActLineBut;
	private JButton stateActLineBut;
	private NolMainFrame frame;	 

	private static int PLOT_ALL = 0;
	private static int PLOT_TRAIN = 1;
	private static int PLOT_TEST = 2;
	
	private JButton outputZoomOutButton;
	private int outputLineZoomInCounterX;
	private int outputScatZoomInCounterX;
	private JButton stateZoomOutButton;
	private int stateLineZoomInCounterX;
	private int stateScatZoomInCounterX;

    private static final String MODELCOMPONENT = "ModelPredVsActWKSP_ModelComponent";
    private static final String ALLDATA = "ModelPredVsActWKSP_AllData";
    private static final String TRAININGDATA = "ModelPredVsActWKSP_TrainingData";
    private static final String TESTINGDATA = "ModelPredVsActWKSP_TestingData";
    private static final String PLOT = "ModelPredVsActWKSP_Plot";
    private static final String VARIABLE = "ModelPredVsActWKSP_Variable";
    private static final String CHARTSTYLE = "ModelPredVsActWKSP_ChartStyle";
    private static final String XYCHART = "ModelPredVsActWKSP_XYChart";
    private static final String LINECHART = "ModelPredVsActWKSP_LineChart";
    private static final String LEGEND = "ModelPredVsActWKSP_Legend";
    private static final String ACT = "ModelPredVsActWKSP_Act";
    private static final String PRED = "ModelPredVsActWKSP_Pred";
    private static final String EXPORT = "ModelPredVsActWKSP_Export";
    private static final String OUTPUTMODEL = "ModelPredVsActWKSP_OutputModel";
    private static final String STATEMODEL = "ModelPredVsActWKSP_StateModel";

	public NolModelPredVsActWKSP (NolMainFrame frame, NolModel2 model) { 
		super(model.getPreprocessor());
		this.frame = frame;	 
		noFire = false;
		showOutputLineChart = false;
		showStateLineChart = false;
		this.model = model;
		setTitle("Predicted vs Actual of "+model.getName());
		actionListener = new ControlAction();
		Y = Matlib.createMatrix();
		YP = Matlib.createMatrix();
		S = Matlib.createMatrix();
		SP = Matlib.createMatrix();
		outputPredLine = new ColoredSquare(Color.yellow); 
		outputActLine = new ColoredSquare(Color.green); 
		statePredLine = new ColoredSquare(Color.yellow); 
		stateActLine = new ColoredSquare(Color.green); 
		predictedColor = Color.yellow;
		actualColor = Color.green;
		outputDisplayIndex = 0;
		stateDisplayIndex = 0;
		twoModels = false;
		if(model instanceof NolOptimizeModel){
			if(((NolOptimizeModel)model).getStateModel() != null){
				twoModels = true;
			}
		}
		getContentPane().setLayout(new BorderLayout());
		if(twoModels){
//			if(DEBUG.more){
			JTabbedPane detailedTabbedPane = new JTabbedPane();
			detailedTabbedPane.addTab(frame.getNolResourceString(OUTPUTMODEL), getOutputPredvsActPanel());
//				detailedTabbedPane.addTab("Output Model", getOutputPredvsActPanel());
			detailedTabbedPane.setSelectedIndex(0);
			detailedTabbedPane.addTab(frame.getNolResourceString(STATEMODEL), getStatePredvsActPanel());
//				detailedTabbedPane.addTab("State Model", getStatePredvsActPanel());
			getContentPane().add("Center",detailedTabbedPane);
//			}else{
//				getStatePredvsActPanel();
//				getContentPane().add("Center",getOutputPredvsActPanel());
//			}
		}else{
			getContentPane().add("Center",getOutputPredvsActPanel());
		}
		//getContentPane().add("North", getModelNamePanel());
		initialDisplay();
	}

	public NolModel2 getModel(){
		return model;
	}

	private JPanel getOutputPredvsActPanel(){
		JPanel predActPane = new JPanel(new BorderLayout());
		outputViewPane = new JPanel(new GridLayout());
		outputViewPane.setBackground(Color.white);
		JScrollPane listScrollPane = new JScrollPane(outputViewPane);
		listScrollPane.setBackground(Color.white);
		listScrollPane.setBorder(BorderFactory.createLoweredBevelBorder());

		JPanel control = new JPanel();
		control.setBackground(getContentPane().getBackground());
		control.setLayout(new BoxLayout(control, BoxLayout.Y_AXIS));

		JPanel pane0 = new JPanel(new GridLayout());
		pane0.setBorder(new TitledBorder(new EmptyBorder(1, 1, 1, 1),               
			frame.getNolResourceString(VARIABLE)+":", TitledBorder.LEFT , TitledBorder.TOP));
//		pane0.setBorder(new TitledBorder(new EmptyBorder(1,1,1,1),"Variable:", TitledBorder.LEFT, TitledBorder.TOP));
		outputVarChoice = new JComboBox();
		outputVarChoice.addActionListener(actionListener);
		pane0.add(outputVarChoice);
		control.add(pane0);

		pane0 = new JPanel(new GridLayout());
		pane0.setBorder(new TitledBorder(new EmptyBorder(1, 1, 1, 1),               
			frame.getNolResourceString(MODELCOMPONENT)+":", TitledBorder.LEFT , TitledBorder.TOP));
//		pane0.setBorder(new TitledBorder(new EmptyBorder(1,1,1,1),"Model Component:", TitledBorder.LEFT, TitledBorder.TOP));
		outputModelChoice = new JComboBox();
		outputModelChoice.addActionListener(actionListener);
		pane0.add(outputModelChoice);
		control.add(pane0);

		pane0 = new JPanel(new GridLayout(3,1,0,0));
		pane0.setBorder(BorderFactory.createTitledBorder(frame.getNolResourceString(PLOT)+":"));
//		pane0.setBorder(BorderFactory.createTitledBorder("Plot:"));
		ButtonGroup plotOption = new ButtonGroup();
		JRadioButton plotAll = new JRadioButton(frame.getNolResourceString(ALLDATA),true) ;
//		JRadioButton plotAll = new JRadioButton("All data",true);
		plotAll.setActionCommand("plotAll");
		plotAll.addActionListener(actionListener);
		plotTrain = new JRadioButton(frame.getNolResourceString(TRAININGDATA)) ;
//		plotTrain = new JRadioButton("Training data");
		plotTrain.setActionCommand("plotTrain");
		plotTrain.addActionListener(actionListener);
		plotTest = new JRadioButton(frame.getNolResourceString(TESTINGDATA)) ;
//		plotTest = new JRadioButton("Testing data");
		plotTest.setActionCommand("plotTest");
		plotTest.addActionListener(actionListener);
		plotOption.add(plotAll);
		plotOption.add(plotTrain);
		plotOption.add(plotTest);
		plotAll.setSelected(true);
  		pane0.add(plotAll);
		pane0.add(plotTrain);
		pane0.add(plotTest);
		//control.add(Box.createRigidArea(NolMainFrame.vpad5)); 
		control.add(pane0);

		pane0 = new JPanel(new GridLayout(2,1,0,0));
		pane0.setBorder(BorderFactory.createTitledBorder(frame.getNolResourceString(CHARTSTYLE)+":"));
		ButtonGroup group = new ButtonGroup();
		JRadioButton chartStyleXY = new JRadioButton(frame.getNolResourceString(XYCHART),true) ;
		chartStyleXY.setActionCommand("output X-Y Chart");
		chartStyleXY.addActionListener(actionListener);
		JRadioButton chartStyleLine = new JRadioButton(frame.getNolResourceString(LINECHART)) ;
		chartStyleLine.setActionCommand("output Line Chart");
		chartStyleLine.addActionListener(actionListener);
		group.add(chartStyleXY);
		group.add(chartStyleLine);
  		pane0.add(chartStyleXY);
		pane0.add(chartStyleLine);
		//control.add(Box.createRigidArea(NolMainFrame.vpad5));
		control.add(pane0);
		//control.add(Box.createRigidArea(NolMainFrame.vpad5));
		outputLegendPane = new JPanel(new GridLayout(2,1,0,0));
		outputLegendPane.setBorder(BorderFactory.createTitledBorder(frame.getNolResourceString(LEGEND)+":"));
		outputLegendPane.add(new JLabel("X: "+frame.getNolResourceString(ACT)));
		outputLegendPane.add(new JLabel("Y: "+frame.getNolResourceString(PRED)));
		control.add(outputLegendPane);
		//control.add(Box.createRigidArea(NolMainFrame.vpad5));

		outputExportPane = new JPanel(new GridLayout(2,1,5,5));
		outputExportPane.setBorder(BorderFactory.createTitledBorder(frame.getNolResourceString(EXPORT)));   // must be localized!
		JButton but = new JButton("All Outputs...");		
		but.setActionCommand("outputExportAll");
		but.addActionListener(actionListener);
		outputExportPane.add(but);
		but = new JButton("Displayed Output...");
		but.setActionCommand("outputExportViewed");
		but.addActionListener(actionListener);
		outputExportPane.add(but);
		control.add(outputExportPane);

		JPanel zoomPane = new JPanel(new GridLayout(1,2,5,5));
		zoomPane.setBorder(BorderFactory.createTitledBorder(frame.getNolResourceString("ModelWKSP_Zoom")+":"));		
		JButton zoom = new JButton(frame.getNolResourceString("ModelWKSP_ZoomIn"));
		zoom.setActionCommand("Output Zoom In");
		outputLineZoomInCounterX = 0;
		outputScatZoomInCounterX = 0;
		zoomPane.add(zoom);
		zoom.addActionListener(actionListener);
		outputZoomOutButton = new JButton(frame.getNolResourceString("ModelWKSP_ZoomOut"));
		outputZoomOutButton.setActionCommand("Output Zoom Out");
		outputZoomOutButton.setEnabled(false);
		zoomPane.add(outputZoomOutButton);
		outputZoomOutButton.addActionListener(actionListener);

		control.add(zoomPane);

		control.add(Box.createRigidArea(NolMainFrame.vpad300));
		control.add(Box.createVerticalGlue());

		predActPane.add("Center",listScrollPane);
		predActPane.add("East",control);
		return predActPane;
	}
	
	private JPanel getStatePredvsActPanel(){
		JPanel predActPane = new JPanel(new BorderLayout());
		stateViewPane = new JPanel(new GridLayout());
		stateViewPane.setBackground(Color.white);
		JScrollPane listScrollPane = new JScrollPane(stateViewPane);
		listScrollPane.setBackground(Color.white);
		listScrollPane.setBorder(BorderFactory.createLoweredBevelBorder());

		JPanel control = new JPanel();
		control.setBackground(getContentPane().getBackground());
		control.setLayout(new BoxLayout(control, BoxLayout.Y_AXIS));

		JPanel pane0 = new JPanel(new GridLayout());
		pane0.setBorder(new TitledBorder(new EmptyBorder(1, 1, 1, 1),               
			frame.getNolResourceString(VARIABLE)+":", TitledBorder.LEFT , TitledBorder.TOP));

		stateVarChoice = new JComboBox();
		stateVarChoice.addActionListener(actionListener);
		pane0.add(stateVarChoice);
		control.add(pane0);

		pane0 = new JPanel(new GridLayout());
		pane0.setBorder(new TitledBorder(new EmptyBorder(1, 1, 1, 1),               
			frame.getNolResourceString(MODELCOMPONENT)+":", TitledBorder.LEFT , TitledBorder.TOP));
		stateModelChoice = new JComboBox();
		stateModelChoice.addActionListener(actionListener);
		pane0.add(stateModelChoice);
		control.add(pane0);

		pane0 = new JPanel(new GridLayout(3,1,0,0));
		pane0.setBorder(BorderFactory.createTitledBorder(frame.getNolResourceString(PLOT)+":"));
		ButtonGroup plotOption = new ButtonGroup();
		JRadioButton plotAll2 = new JRadioButton(frame.getNolResourceString(ALLDATA),true) ;
		plotAll2.setActionCommand("plotAll");
		plotAll2.addActionListener(actionListener);
		plotTrain2 = new JRadioButton(frame.getNolResourceString(TRAININGDATA)) ;
		plotTrain2.setActionCommand("plotTrain");
		plotTrain2.addActionListener(actionListener);
		plotTest2 = new JRadioButton(frame.getNolResourceString(TESTINGDATA)) ;
		plotTest2.setActionCommand("plotTest");
		plotTest2.addActionListener(actionListener);
		plotOption.add(plotAll2);
		plotOption.add(plotTrain2);
		plotOption.add(plotTest2);
		plotAll2.setSelected(true);
  		pane0.add(plotAll2);
		pane0.add(plotTrain2);
		pane0.add(plotTest2);
		//control.add(Box.createRigidArea(NolMainFrame.vpad5)); 
		control.add(pane0);

		pane0 = new JPanel(new GridLayout(2,1,0,0));
		pane0.setBorder(BorderFactory.createTitledBorder(frame.getNolResourceString(CHARTSTYLE)+":"));
		ButtonGroup group = new ButtonGroup();
		JRadioButton chartStyleXY = new JRadioButton(frame.getNolResourceString(XYCHART),true) ;
		chartStyleXY.setActionCommand("state X-Y Chart");
		chartStyleXY.addActionListener(actionListener);
		JRadioButton chartStyleLine = new JRadioButton(frame.getNolResourceString(LINECHART)) ;
		chartStyleLine.setActionCommand("state Line Chart");
		chartStyleLine.addActionListener(actionListener);
		group.add(chartStyleXY);
		group.add(chartStyleLine);
  		pane0.add(chartStyleXY);
		pane0.add(chartStyleLine);
		//control.add(Box.createRigidArea(NolMainFrame.vpad5));
		control.add(pane0);
		//control.add(Box.createRigidArea(NolMainFrame.vpad5));
		stateLegendPane = new JPanel(new GridLayout(2,1,0,0));
		stateLegendPane.setBorder(BorderFactory.createTitledBorder(frame.getNolResourceString(LEGEND)+":"));
		stateLegendPane.add(new JLabel("X: "+frame.getNolResourceString(ACT)));
		stateLegendPane.add(new JLabel("Y: "+frame.getNolResourceString(PRED)));
		control.add(stateLegendPane);
		//control.add(Box.createRigidArea(NolMainFrame.vpad5));

		stateExportPane = new JPanel(new GridLayout(2,1,5,5));
		stateExportPane.setBorder(BorderFactory.createTitledBorder(frame.getNolResourceString(EXPORT)));   // must be localized!
		JButton but = new JButton("All States...");	
		but.setActionCommand("stateExportAll");
		but.addActionListener(actionListener);
		stateExportPane.add(but);
		but = new JButton("Displayed State...");
		but.setActionCommand("stateExportViewed");
		but.addActionListener(actionListener);
		stateExportPane.add(but);
		control.add(stateExportPane);
		//control.add(Box.createRigidArea(NolMainFrame.vpad5));

		JPanel zoomPane = new JPanel(new GridLayout(1,2,5,5));
		zoomPane.setBorder(BorderFactory.createTitledBorder(frame.getNolResourceString("ModelWKSP_Zoom")+":"));		
		JButton zoom = new JButton(frame.getNolResourceString("ModelWKSP_ZoomIn"));
		zoom.setActionCommand("State Zoom In");
		stateLineZoomInCounterX = 0;
		stateScatZoomInCounterX = 0;
		zoomPane.add(zoom);
		zoom.addActionListener(actionListener);
		stateZoomOutButton = new JButton(frame.getNolResourceString("ModelWKSP_ZoomOut"));
		stateZoomOutButton.setActionCommand("State Zoom Out");
		stateZoomOutButton.setEnabled(false);
		zoomPane.add(stateZoomOutButton);
		stateZoomOutButton.addActionListener(actionListener);

		control.add(zoomPane);

		control.add(Box.createRigidArea(NolMainFrame.vpad300));
		control.add(Box.createVerticalGlue());

		predActPane.add("Center",listScrollPane);
		predActPane.add("East",control);
		return predActPane;
	}
	
	public void initialDisplay(){
		noFire = true;
		currentPlotOption = PLOT_ALL;
		currentModelOption = -1;  // ensemble
		Vector outs = model.getOutputs();
		Vector ins = model.getInputs();
		Matrix X = Matlib.createMatrix();
		Matrix I = Matlib.createMatrix();
		if(model instanceof NolOptimizeModel){
			Vector state = ((NolOptimizeModel)model).getState();
			if(twoModels){
				for(int j=0;j<state.size();j++){
					String name = state.elementAt(j).toString();
					stateVarChoice.addItem(name);
				}
				stateModelChoice.addItem("Entire ensemble");
				EnsembleModel net = (EnsembleModel) ((NolOptimizeModel)model).getStateModel();
				for (int i=0;i<net.getModelSize();i++) {
					stateModelChoice.addItem("Submodel "+(i+1));
				}
			}
			Vector mani = ((NolOptimizeModel)model).getManipulate();
			Vector exog = ((NolOptimizeModel)model).getExogenous();
			try{
				outputTime = model.prepareTrainingSet(X, Y);
				if(outputTime == null){
					// create fake times for plotting
					outputTime = new long[Y.getRows()];
					for(int r=0;r<outputTime.length;r++){
						outputTime[r] = (long)r*1000;
					}
				}
			} catch (MathException evt){
				System.err.println("Non-Fatal exception preparing training data: " + evt.getMessage());
				evt.printStackTrace();	
			}
			if(twoModels){
				try{
					stateTime = ((NolOptimizeModel)model).prepareTrainingSet2(I, S);
					if(stateTime == null){
						stateTime = new long[S.getRows()];
						for(int r=0;r<stateTime.length;r++){
							stateTime[r] = (long)r*1000;
						}
					}
				} catch (MathException evt){
					System.err.println("Non-Fatal exception preparing training data: " + evt.getMessage());
					evt.printStackTrace();	
				}
			}
		}else{
			try{
				outputTime = model.prepareTrainingSet(X, Y);
				if(outputTime == null){
					outputTime = new long[Y.getRows()];
					for(int r=0;r<outputTime.length;r++){
						outputTime[r] = (long)r*1000;
					}
				}
			} catch(MathException evt){
				System.err.println("Non-Fatal exception preparing training set: " + evt.getMessage());
				evt.printStackTrace();
			}
		}
		outputVarChoice.removeAllItems();
		for(int j=0;j<outs.size();j++){
			String name = outs.elementAt(j).toString();
			outputVarChoice.addItem(name);
		}

		calculatePredictions(X,I);
		Matlib.clear(X);
		Matlib.clear(I);
		// determine whether we can show training and test subsets, models didn't store this into prior to V2.1
		boolean preV21Model = false;
		EnsembleModel net = (EnsembleModel) model.getModel();
		outputModelChoice.removeAllItems();
		outputModelChoice.addItem("Entire ensemble");
		for (int i=0;i<net.getModelSize();i++) {
			outputModelChoice.addItem("Submodel "+(i+1));
			TrainableModel trainableModel = (TrainableModel) net.getModel(i);
			
			if(trainableModel.testingSamples==null){
				preV21Model = true;
//System.out.println("model.testingSamples==null) and i="+i);
			}else{
//	System.out.println("model.testingSamples!=null) and i="+i);
			}
		}
		if(preV21Model) {
			plotTrain.setEnabled(false);
		}
		if(preV21Model) {
			plotTest.setEnabled(false);
		}
		if(twoModels) {
			if(preV21Model) {
				plotTrain2.setEnabled(false);
			}
			if(preV21Model) {
				plotTest2.setEnabled(false);
			}
		}
		refreshChartDisplay();
		noFire = false;
	}


	private void calculatePredictions(Matrix X, Matrix I) {
		EnsembleModel net = (EnsembleModel) model.getModel();
		int nout = net.getNout();
		YPred = new Matrix[nout];
		YPredMask = new Matrix[nout];
		for (int i=0;i<nout;i++) {
			YPred[i] = Matlib.createMatrix();
			YPredMask[i] = Matlib.createMatrix();
		}
		try {
			net.evaluateSubmodels(X,YPred);
			applyMask(net,YPred,YPredMask);
		} catch (MathException evt) {
			System.err.println("Non-Fatal exception preparing training data: " + evt.getMessage());
			evt.printStackTrace();
		}
		if(model instanceof NolOptimizeModel && twoModels) {
			net = (EnsembleModel) ((NolOptimizeModel)model).getStateModel();
			nout = net.getNout();
			SPred = new Matrix[nout];
			SPredMask = new Matrix[nout];
			for (int i=0;i<nout;i++) {
				SPred[i] = Matlib.createMatrix();
				SPredMask[i] = Matlib.createMatrix();
			}

			try {
				net.evaluateSubmodels(I,SPred);
				applyMask(net,SPred,SPredMask);
			} catch (MathException evt) {
				System.err.println("Non-Fatal exception preparing training data: " + evt.getMessage());
				evt.printStackTrace();
			}
		}
	}

	private void applyMask() {
		// apply the current all/train/test mask to data
		EnsembleModel net = (EnsembleModel) model.getModel();
		applyMask(net,YPred,YPredMask);
		if(twoModels) {
			net = (EnsembleModel) ((NolOptimizeModel)model).getStateModel();
			applyMask(net,SPred,SPredMask);
		}
	}

	private void applyMask(EnsembleModel net, Matrix[] M, Matrix[] MT) {
		int nmodels = M[0].getCols();
		int ndata = M[0].getRows();
		int nout = M.length;
		// always freshly copy contents of M to MT
		for (int i=0;i<nout;i++) {
			Matlib.copy(M[i],MT[i]);
		}
		if(currentPlotOption==PLOT_ALL) {
			return;
		}
		boolean isTest = false;
		if(currentPlotOption==PLOT_TEST) {
			isTest = true;
		}
		double NaN = Double.NaN;
		for (int i=0;i<nmodels;i++) {
			TrainableModel trainableModel = (TrainableModel) net.getModel(i);
			if(trainableModel.testingSamples==null) {
				return;  // this should never happen since buttons are disabled
			}
			boolean[] testingSamples = trainableModel.testingSamples;
			if(isTest) {
				for(int j=0;j<ndata;j++) {
					if(!testingSamples[j]) {
						for(int k=0;k<nout;k++) {
							MT[k].set(j,i,NaN);
						}
					}
				}
			} else {
				for(int j=0;j<ndata;j++) {
					if(testingSamples[j]) {
						for(int k=0;k<nout;k++) {
							MT[k].set(j,i,NaN);
						}
					}
				}
			}
		}
//System.out.println("Applied mask, isTest = "+isTest);
//Matlib.disp(MT[0], "Masked data MT[0] = ");
	}

	private void findMedian(Matrix M, Matrix Y) {
		if(M.getCols() == 1){
			Matlib.copy(M,Y);
			return;
		}
		try {
			Matrix temp = Matlib.createMatrix();
			Y.redimension(0,0); // empty Y to make room for predictions
			Matlib.transpose(M,temp);
			Matlib.median(temp,temp);  // median ignores NaN elements
			Matlib.transpose(temp,temp);
			Matlib.appendColumns(Y,temp,Y);
			Matlib.clear(temp);
		} catch (MathException evt) {
			System.err.println("Non-Fatal exception in findMedian: " + evt.getMessage());
			evt.printStackTrace();
		}
	}

	private void refreshChartDisplay() {
		if(currentModelOption==-1) {
			findMedian(YPredMask[outputDisplayIndex],YP);  // entire ensemble
		}else {
			try {
				Matlib.getColumn(YPredMask[outputDisplayIndex],currentModelOption,YP);
			} catch (MathException e) {
				System.err.println("Non-Fatal exception refreshing charts: " + e.getMessage());
				e.printStackTrace();
			}
		}
		if(Y.getRows() == 0 || YP.getRows() == 0){
			return;
		}
		if(Y.getRows() != YP.getRows()){
			return;
		}
		Matrix temp	= Matlib.createMatrix();
		Matlib.transpose(Y,temp);
		double[][] yy = Matlib.create2DArray(temp);
		double[] y = yy[outputDisplayIndex];

		double[] yp = Matlib.create1DArray(YP);
		outputLineChart = new LineChart(outputTime, y, yp,getBackground());
		outputScatChart = new ScatChart(y,yp,false,getBackground());
		showOutputChart();

		if(twoModels) {
			if(currentModelOption==-1) {
				findMedian(SPredMask[stateDisplayIndex],SP);  // entire ensemble
			}else {
				try {
					Matlib.getColumn(SPredMask[stateDisplayIndex],currentModelOption,SP);
				} catch (MathException e) {
					System.err.println("Non-Fatal exception refreshing charts: " + e.getMessage());
					e.printStackTrace();
				}
			}
			Matlib.transpose(S,temp);
			double[][] ss = Matlib.create2DArray(temp);
			double[] s = ss[stateDisplayIndex];

			double[] sp = Matlib.create1DArray(SP);
			stateLineChart = new LineChart(stateTime, s, sp,getBackground());
			stateScatChart = new ScatChart(s,sp,false,getBackground());
			showStateChart();
		}
		Matlib.clear(temp); 
	}

 	private void showOutputChart(){
		outputViewPane.removeAll();
		if(showOutputLineChart){
			outputViewPane.add(outputLineChart.getChart());
		}else{
			JPanel chartPane = new JPanel(new GridLayout());
			chartPane.setBorder(new EmptyBorder(15,0,0,0));               
			chartPane.add(outputScatChart.getChart());
			outputViewPane.add(chartPane);
		}
		outputViewPane.repaint();
		outputViewPane.validate();

 		outputLegendPane.removeAll();
		if(showOutputLineChart){
			outputLegendPane.setLayout(new GridLayout(2,2,5,5));
			outputActLineBut = new JButton(outputActLine);
			outputActLineBut.setActionCommand("outputactualColor");
			outputActLineBut.addActionListener(actionListener);
			outputPredLineBut = new JButton(outputPredLine);
			outputPredLineBut.addActionListener(actionListener);
			outputPredLineBut.setActionCommand("outputpredictColor");
			outputPredLineBut.setToolTipText("Change predicted line color.");
 			outputActLineBut.setToolTipText("Change actual line color.");
			outputLegendPane.add(outputActLineBut);
			outputLegendPane.add(new JLabel("Actual"));
			outputLegendPane.add(outputPredLineBut);
			outputLegendPane.add(new JLabel("Predicted"));
		}else{
			outputLegendPane.setLayout(new GridLayout(2,1,10,10));
			outputLegendPane.add(new JLabel("X: Actual"));
			outputLegendPane.add(new JLabel("Y: Predicted"));
		}
		outputLegendPane.repaint();
		outputLegendPane.validate();
	}

 	private void showStateChart(){
		if(twoModels){
			stateViewPane.removeAll();
			if(showStateLineChart){
				stateViewPane.add(stateLineChart.getChart());
			}else{
				JPanel chartPane = new JPanel(new GridLayout());
				chartPane.setBorder(new EmptyBorder(15,0,0,0));               
				chartPane.add(stateScatChart.getChart());
				stateViewPane.add(chartPane);
			}
			stateViewPane.repaint();
			stateViewPane.validate();

 			stateLegendPane.removeAll();
			if(showStateLineChart){
				stateLegendPane.setLayout(new GridLayout(2,2,5,5));
				stateActLineBut = new JButton(stateActLine);
				stateActLineBut.setActionCommand("stateactualColor");
				stateActLineBut.addActionListener(actionListener);
				statePredLineBut = new JButton(statePredLine);
				statePredLineBut.addActionListener(actionListener);
				statePredLineBut.setActionCommand("statepredictColor");
				statePredLineBut.setToolTipText("Change predicted line color.");
 				stateActLineBut.setToolTipText("Change actual line color.");
				stateLegendPane.add(stateActLineBut);
				stateLegendPane.add(new JLabel("Actual"));
				stateLegendPane.add(statePredLineBut);
				stateLegendPane.add(new JLabel("Predicted"));
			}else{
				stateLegendPane.setLayout(new GridLayout(2,1,10,10));
				stateLegendPane.add(new JLabel("X: Actual"));
				stateLegendPane.add(new JLabel("Y: Predicted"));
			}
			stateLegendPane.repaint();
			stateLegendPane.validate();
		}
	}

	private void changeOutputActualLineColor(Color color){
		MultiLineChart chart = outputLineChart.getChart();
		if(chart.getPlotCount() == 2){	
			LineFormat lineFormat = chart.getLineFormat(0);
			lineFormat.setColor(color);
			MarkerFormat[] markerFormats = chart.getMarkerFormats(0);
			for(int i=0;i<markerFormats.length;i++)		  {
				markerFormats[i].setForegroundColor(color);
			}
		}
		outputActLine.setShowColor(color);
		outputActLine.repaint();
		outputActLine.validate();
		chart.invalidateAll();
		chart.repaint();
		outputViewPane.validate();
		outputViewPane.repaint();
		actualColor = color;  	// store color, MK added 5/16/99
	}

	private void changeStateActualLineColor(Color color){
		MultiLineChart chart = stateLineChart.getChart();
		if(chart.getPlotCount() == 2){	
			LineFormat lineFormat = chart.getLineFormat(0);
			lineFormat.setColor(color);
			MarkerFormat[] markerFormats = chart.getMarkerFormats(0);
			for(int i=0;i<markerFormats.length;i++)		  {
				markerFormats[i].setForegroundColor(color);
			}
		}
		stateActLine.setShowColor(color);
		stateActLine.repaint();
		stateActLine.validate();
		chart.invalidateAll();
		chart.repaint();
		stateViewPane.validate();
		stateViewPane.repaint();
		// store color, added 5/16/99
		actualColor = color;
	}

	public void	changeOutputPredLineColor(Color color){
		MultiLineChart chart = outputLineChart.getChart();
		if(chart.getPlotCount() == 2){	
			LineFormat lineFormat = chart.getLineFormat(1);
			lineFormat.setColor(color);
			MarkerFormat[] markerFormats = chart.getMarkerFormats(1);
			for(int i=0;i<markerFormats.length;i++)		  {
				markerFormats[i].setForegroundColor(color);
			}
		}
		outputPredLine.setShowColor(color);
		outputPredLine.repaint();
		outputPredLine.validate();
		chart.invalidateAll();
		chart.repaint();
		outputViewPane.validate();
		outputViewPane.repaint();
		// store color, added 5/16/99
		predictedColor = color;
	}

	public void	changeStatePredLineColor(Color color){
		MultiLineChart chart = stateLineChart.getChart();
		if(chart.getPlotCount() == 2){	
			LineFormat lineFormat = chart.getLineFormat(1);
			lineFormat.setColor(color);
			MarkerFormat[] markerFormats = chart.getMarkerFormats(1);
			for(int i=0;i<markerFormats.length;i++)		  {
				markerFormats[i].setForegroundColor(color);
			}
		}
		statePredLine.setShowColor(color);
		statePredLine.repaint();
		statePredLine.validate();
		chart.invalidateAll();
		chart.repaint();
		stateViewPane.validate();
		stateViewPane.repaint();
		predictedColor = color;  // store color, added 5/16/99
	}

/** LineChart implementation  */
    class LineChart extends Object{
		private MultiLineChart chart;

		LineChart(long[] time, double[] y, double[] ypred,Color backColor){
			chart = new MultiLineChart(MultiLineChart.SHARED_Y_LAYOUT_STYLE, MultiLineChart.ROW_MODE, backColor);
			int nData = time.length; 
			Color plotColor = actualColor;
			int plotSymbol = 0;
			LineFormat connectorFormat = new LineFormat(plotColor, 1);
			byte[] markers = new byte[nData];
			int baseSize = 6;  // what if chart has been zoomed?
			int highlightSize = 10;
			Color highlightColor = null;
			MarkerFormat unhighlightedMarker = new MarkerFormat
				(plotSymbol, plotColor, highlightColor, baseSize, highlightSize);
			MarkerFormat[] markerFormats = new MarkerFormat[2];
			markerFormats[0] = unhighlightedMarker;
			highlightColor = actualColor;
			markerFormats[1] = new MarkerFormat
				(plotSymbol, plotColor, highlightColor, baseSize, highlightSize);  
			chart.addDataSeries("Y", time, y, markerFormats, markers, connectorFormat);
			plotColor = predictedColor;
			plotSymbol = 1;
			connectorFormat = new LineFormat(plotColor, 1);
			highlightColor = null;
			markerFormats = new MarkerFormat[2];
			markerFormats[0] = new MarkerFormat
				(plotSymbol, plotColor, highlightColor, baseSize, highlightSize);
			highlightColor = predictedColor;
			markerFormats[1] = new MarkerFormat
				(plotSymbol, plotColor, highlightColor, baseSize, highlightSize);  
			chart.addDataSeries("YPred", time, ypred, markerFormats, markers, connectorFormat);
			chart.setAxisColor(Color.black);
		}

		public void setData(double[] y, double[] ypred){

		}
		
		public MultiLineChart getChart(){
			return chart;
		}
	
	}

	/**
     * ScatChart implementation
     */
    class ScatChart extends Object{
		private ScatterChart chart;
		ScatChart(double[] y, double[] ypred, boolean connectors, Color back){
			chart = new ScatterChart(back);
			int nData = y.length;
			Color plotColor = Color.green;
			int plotSymbol = 1;
			LineFormat connectorFormat = new LineFormat(plotColor, 1);
			byte[] markers = new byte[nData];
			int baseSize = 6;  // what if chart has been zoomed?
			int highlightSize = 10;
			Color highlightColor = null;
			MarkerFormat unhighlightedMarker = new MarkerFormat
				(plotSymbol, plotColor, highlightColor, baseSize, highlightSize);
			MarkerFormat[] markerFormats = new MarkerFormat[2];
			markerFormats[0] = unhighlightedMarker;
			highlightColor = Color.green;
			markerFormats[1] = new MarkerFormat(plotSymbol, plotColor, highlightColor, baseSize, highlightSize);  
			if(connectors){
				chart.setConnectorsState(true); // add connectors if requested, bbush 8-3-98
			}
			chart.addDataSeries("1p/2p", y, ypred, markerFormats, markers); 
		}

		public void setData(double[] y, double[] ypred){

		}

		public ScatterChart getChart(){
			return chart;
		}
	
	}

    class ControlAction extends AbstractAction{
		ControlAction() {super("controlAction");}
		@Override
		public void actionPerformed(ActionEvent e) {
			if(noFire) {
				return;
			}
			String command = e.getActionCommand();
			if(command.equals("outputExportViewed")) {
				try{
					Matrix YPAll = Matlib.createMatrix();
					Matlib.getColumn(Y,outputDisplayIndex,YPAll);
					Matlib.appendColumns(YP,YPAll,YPAll);
					DataSeries ds = new DataSeries(YPAll);
					if(model.getHasTimeStamps()) {
						ds.setTimeStamps(outputTime);
					}
					Preprocessor prep = model.getPreprocessor();
					Vector outs = model.getOutputs();
					String varName = (String) outs.elementAt(outputDisplayIndex);
					Variable varObj = prep.getVariableFromVariableName(varName);
					String varTag = varObj.getTag();
					ds.setVariableParameters(0,varTag+"_pred",varName+"_pred","None");
					ds.setVariableParameters(1,varTag,varName,"None");
					ds.setName(model.getName()+frame.getNolResourceString(PRED)+varName);
					frame.exportActionPerformed(ds);
					ds.clearMemory();  // this clears SPAll
					ds = null; 
				}catch(MathException evt){
					Toolkit.getDefaultToolkit().beep();
					frame.showOKDialog("Error in saving data.");
					return;
				}
				Toolkit.getDefaultToolkit().beep();
			}else if(command.equals("stateExportViewed")) {
				try{
					Matrix SPAll = Matlib.createMatrix();
					Matlib.getColumn(S,stateDisplayIndex,SPAll);
					Matlib.appendColumns(SP,SPAll,SPAll);
					DataSeries ds = new DataSeries(SPAll);
					if(model.getHasTimeStamps()) {
						ds.setTimeStamps(stateTime);
					}
					Preprocessor prep = model.getPreprocessor();
					Vector states = ((NolOptimizeModel)model).getState();
					String varName = (String) states.elementAt(stateDisplayIndex);
					Variable varObj = prep.getVariableFromVariableName(varName);
					String varTag = varObj.getTag();
					ds.setVariableParameters(0,varTag+"_pred",varName+"_pred","None");
					ds.setVariableParameters(1,varTag,varName,"None");
					ds.setName(model.getName()+frame.getNolResourceString(PRED)+varName);
					frame.exportActionPerformed(ds);
					ds.clearMemory();  // this clears SPAll
					ds = null;  
				}catch(MathException evt){
					Toolkit.getDefaultToolkit().beep();
					frame.showOKDialog("Error in saving data.");
					return;
				}
				Toolkit.getDefaultToolkit().beep();
			}else if(command.equals("outputExportAll")) {
				try{
					Matrix YPAll = Matlib.createMatrix();
					EnsembleModel.findMedian(YPred,YPAll);				
					Matlib.appendColumns(YPAll,Y,YPAll);
					DataSeries ds = new DataSeries(YPAll);
					ds.setName(model.getName()+frame.getNolResourceString(PRED));
					if(model.getHasTimeStamps()) {
						ds.setTimeStamps(outputTime);
					}
					Preprocessor prep = model.getPreprocessor();
					Vector outs = model.getOutputs();
					int col = Y.getCols();

//		System.out.println("Y.getCols()="+Y.getCols());
//		System.out.println("YPAll.getCols()="+YPAll.getCols());
//		System.out.println("Y.getRows()="+Y.getRows());
//		System.out.println("YPAll.getRows()="+YPAll.getRows());
					for(int c=0;c<col;c++){
						String varName = (String) outs.elementAt(c);
						Variable varObj = prep.getVariableFromVariableName(varName);
						String varTag = varObj.getTag();
						ds.setVariableParameters(c,varTag+"_pred",varName+"_pred","None");
						ds.setVariableParameters(c+col,varTag,varName,"None");
					}
					frame.exportActionPerformed(ds);
					ds.clearMemory();  // this clears YPAll
					ds = null; 
				}catch(MathException evt){
					evt.printStackTrace();
					Toolkit.getDefaultToolkit().beep();
					frame.showOKDialog("Error in saving data.");
					return;
				}
				Toolkit.getDefaultToolkit().beep();
			}else if(command.equals("stateExportAll")) {
				try{
					Matrix SPAll = Matlib.createMatrix();
					EnsembleModel.findMedian(SPred,SPAll);
					Matlib.appendColumns(SPAll,S,SPAll);
					DataSeries ds = new DataSeries(SPAll);
					ds.setName(model.getName()+frame.getNolResourceString(PRED));
					if(model.getHasTimeStamps()) {
						ds.setTimeStamps(stateTime);
					}
					Preprocessor prep = model.getPreprocessor();
					Vector states = ((NolOptimizeModel)model).getState();
					int col = S.getCols();
					for(int c=0;c<col;c++){
						String varName = (String) states.elementAt(c);
						Variable varObj = prep.getVariableFromVariableName(varName);
						String varTag = varObj.getTag();
						ds.setVariableParameters(c,varTag+"_pred",varName+"_pred","None");
						ds.setVariableParameters(c+col,varTag,varName,"None");
					}
					frame.exportActionPerformed(ds);
					ds.clearMemory();  // this clears SPAll
					ds = null; 
				}catch(MathException evt){
					Toolkit.getDefaultToolkit().beep();
					frame.showOKDialog("Error in saving data.");
					return;
				}
				Toolkit.getDefaultToolkit().beep();
			}else if(command.equals("output X-Y Chart")){
				showOutputLineChart = false;
				showOutputChart();
				if(outputScatZoomInCounterX <= 0) {
					outputZoomOutButton.setEnabled(false);
				}else {
					outputZoomOutButton.setEnabled(true);
				}
			}else if(command.equals("state X-Y Chart")){
				showStateLineChart = false;
				showStateChart();
				if(stateScatZoomInCounterX <= 0) {
					stateZoomOutButton.setEnabled(false);
				}else {
					stateZoomOutButton.setEnabled(true);
				}
			}else if(command.equals("output Line Chart")){
				showOutputLineChart = true;
				showOutputChart();
				if(outputLineZoomInCounterX <= 0) {
					outputZoomOutButton.setEnabled(false);
				}else {
					outputZoomOutButton.setEnabled(true);
				}
			}else if(command.equals("state Line Chart")){ 
				showStateLineChart = true;
				showStateChart();
				if(stateLineZoomInCounterX <= 0) {
					stateZoomOutButton.setEnabled(false);
				}else{
					stateZoomOutButton.setEnabled(true);
				}
			}else if(command.equals("plotAll")) {
				currentPlotOption = PLOT_ALL;
				applyMask();
				refreshChartDisplay();
			}else if(command.equals("plotTrain")) {
				currentPlotOption = PLOT_TRAIN;
				applyMask();
				refreshChartDisplay();
			}else if(command.equals("plotTest")) {
				currentPlotOption = PLOT_TEST;
				applyMask();
				refreshChartDisplay();
			} else if(command.equals("outputactualColor")){
				NolColorChooser colorChooser = new NolColorChooser(frame, "Color Chooser");
				colorChooser.setBounds(200,200,300,300);
				colorChooser.setVisible(true);
				Color color = colorChooser.getSelectedColor();
				if(!colorChooser.getResult()){
					colorChooser.dispose();
					return;
				}
				colorChooser.dispose();
				changeOutputActualLineColor(color);
			}else if(command.equals("stateactualColor")){
				NolColorChooser colorChooser = new NolColorChooser(frame, "Color Chooser");
				colorChooser.setBounds(200,200,300,300);
				colorChooser.setVisible(true);
				Color color = colorChooser.getSelectedColor();
				if(!colorChooser.getResult()){
					colorChooser.dispose();
					return;
				}
				colorChooser.dispose();
				changeStateActualLineColor(color);
			}else if(command.equals("outputpredictColor")){
				NolColorChooser colorChooser = new NolColorChooser(frame, "Color Chooser");
				colorChooser.setBounds(200,200,300,300);
				colorChooser.setVisible(true);
				Color color = colorChooser.getSelectedColor();
				if(!colorChooser.getResult()){
					colorChooser.dispose();
					return;
				}
				colorChooser.dispose();
				changeOutputPredLineColor(color);
			}else if(command.equals("statepredictColor")){
				NolColorChooser colorChooser = new NolColorChooser(frame, "Color Chooser");
				colorChooser.setBounds(200,200,300,300);
				colorChooser.setVisible(true);
				Color color = colorChooser.getSelectedColor();
				if(!colorChooser.getResult()){
					colorChooser.dispose();
					return;
				}
				colorChooser.dispose();
				changeStatePredLineColor(color);
			}else if(e.getSource().equals(outputVarChoice)) {  // Variable Choice on Predicted vs Actual pane
				noFire = true;
				String varName = (String)outputVarChoice.getSelectedItem();
				Vector outs = model.getOutputs();
				int index = 0;
				for(int j=0;j<outs.size();j++){
					String name = outs.elementAt(j).toString();
					if(varName.equals(name)){
						index = j;
						break;
					}
				}
				outputDisplayIndex = index;
				refreshChartDisplay();
				noFire = false;
			}else if(e.getSource().equals(stateVarChoice)) {  // Variable Choice on Predicted vs Actual pane
				noFire = true;
				String varName = (String)stateVarChoice.getSelectedItem();
				Vector states = ((NolOptimizeModel)model).getState();
				int index = 0;
				for(int j=0;j<states.size();j++){
					String name = states.elementAt(j).toString();
					if(varName.equals(name)){
						index = j;
						break;
					}
				}
				stateDisplayIndex = index;
				refreshChartDisplay();
				noFire = false;
			}else if(e.getSource().equals(outputModelChoice) || e.getSource().equals(stateModelChoice)) {  
				noFire = true;
				String modelName = (String) ((JComboBox)e.getSource()).getSelectedItem();
				if(modelName.equals("Entire ensemble")){
					currentModelOption = -1;
				}else {
					int index = 1;
					while(index<10) {
						String name = "Submodel "+index;
						if(modelName.equals(name)) {
							break;
						}
						index++;
					}
					currentModelOption = index - 1;  // since 0-based index
				}
				refreshChartDisplay();
				noFire = false;
			}else if(command.equals("Output Zoom In")){
				if(!outputZoomOutButton.isEnabled()) 
					outputZoomOutButton.setEnabled(true);
				if(showOutputLineChart){
					outputLineChart.getChart().zoomIn();
					outputLineZoomInCounterX++;
				}else{
					outputScatChart.getChart().zoomIn();
					outputScatZoomInCounterX++;
				}
			}else if(command.equals("Output Zoom Out")){
				if(showOutputLineChart){
					outputLineZoomInCounterX--;
					if(outputLineZoomInCounterX <= 0){
						outputZoomOutButton.setEnabled(false);
					}
					outputLineChart.getChart().zoomOut();
					if(outputLineZoomInCounterX<0) {
						outputLineZoomInCounterX = 0;
					}
				}else{
					outputScatZoomInCounterX--;
					if(outputScatZoomInCounterX <= 0) {
						outputZoomOutButton.setEnabled(false);
					}
					outputScatChart.getChart().zoomOut();
					if(outputScatZoomInCounterX<0) {
						outputScatZoomInCounterX = 0;
					}
				}
			}else if(command.equals("State Zoom In")){
				if(!stateZoomOutButton.isEnabled()) 
					stateZoomOutButton.setEnabled(true);
				if(showStateLineChart){
					stateLineChart.getChart().zoomIn();
					stateLineZoomInCounterX++;
				}else{
					stateScatChart.getChart().zoomIn();
					stateScatZoomInCounterX++;
				}
			}else if(command.equals("State Zoom Out")){
				if(showStateLineChart){
					stateLineZoomInCounterX--;
					if(stateLineZoomInCounterX <= 0) {
						stateZoomOutButton.setEnabled(false);
					}
					stateLineChart.getChart().zoomOut();
					if(stateLineZoomInCounterX<0) {
						stateLineZoomInCounterX = 0;
					}
				}else{
					stateScatZoomInCounterX--;
					if(stateScatZoomInCounterX <= 0) {
						stateZoomOutButton.setEnabled(false);
					}
					stateScatChart.getChart().zoomOut();
					if(stateScatZoomInCounterX<0) {
						stateScatZoomInCounterX = 0;
					}
				}
			}
		}
    }
}

