package com.gensym.nols.wksp;

import java.awt.*;
import java.awt.event.*;
import java.util.*;

import javax.swing.*;
import javax.swing.table.*;
import javax.swing.border.*;

import com.gensym.math.Utilities;
import com.gensym.math.*;
import com.gensym.math.matrix.*;
import com.gensym.math.datafit.*;

import com.gensym.nols.main.*;
import com.gensym.nols.util.*;
import com.gensym.nols.dlg.*;
import com.gensym.nols.data.*;
import com.gensym.nols.chart.line.*;
import com.gensym.nols.chart.scatter.*;

public class NolValidateModelWKSP extends NolInternalFrame {

	private ControlAction actionListener;
	private boolean validValidation;
	private boolean noFire;
	private boolean twoModels;
	private boolean showOutputLineChart;
	private boolean showStateLineChart;
	private boolean validateDataCalculated;

 	private	StatisticsTableModel statisticsTableModel;
	private	JTable statisticsTableView;
	private NolModel2 model;
	private Matrix Y;
	private Matrix YPred;
	private Matrix S;
	private Matrix SPred;
	private long[] outputTime;
	private long[] stateTime;
	private int maxDelayModel1;

	private JTextField trainCase;
	private JTextField trainDataName;
	private JList testDataName;

	private Vector testPreprocessors;
	private Vector testDataSeries;
 	private JPanel outputViewPane;
 	private JPanel stateViewPane;
 	private JPanel outputLegendPane;
 	private JPanel stateLegendPane;

	private JComboBox outputChoice;
	private JComboBox stateChoice;
	private JTextArea textDisplay;

	private JComboBox varChoiceY; // bbush 7-29-98
	private JComboBox varChoiceX; 
	
	private NolMainFrame frame;	  //for demo only
	private Vector validateDataSeries;
	private Vector validateProcessedDataSeries;
	private LineChart outputLineChart;
	private ScatChart outputScatChart;
	private LineChart stateLineChart;
	private ScatChart stateScatChart;

	private ColoredSquare outputPredLine;
	private ColoredSquare outputActLine;
	private ColoredSquare statePredLine;
	private ColoredSquare stateActLine;
	private JButton outputPredLineBut;
	private JButton statePredLineBut;
	private JButton outputActLineBut;
	private JButton stateActLineBut;

	private JButton outputZoomOutButton;
	private int outputLineZoomInCounterX;
	private int outputScatZoomInCounterX;
	private JButton stateZoomOutButton;
	private int stateLineZoomInCounterX;
	private int stateScatZoomInCounterX;

    protected static final String MODELNAME= "ValidateModelWKSP_ModelName";
    protected static final String PREPROCESSOR = "ValidateModelWKSP_Preprocessor";
    protected static final String TESTINGDATASERIES = "ValidateModelWKSP_TestingDataSeries";
    protected static final String VARIABLE = "ValidateModelWKSP_Variable";
    protected static final String STATISTICS = "ValidateModelWKSP_Statistics";
    protected static final String VALUE = "ValidateModelWKSP_Value";
    protected static final String CHARTSTYLE = "ValidateModelWKSP_ChartStyle";
    protected static final String XYCHART = "ValidateModelWKSP_XYChart";
    protected static final String LINECHART = "ValidateModelWKSP_LineChart";
    protected static final String LEGEND = "ValidateModelWKSP_Legend";
    protected static final String ACT = "ValidateModelWKSP_Act";
    protected static final String PRED = "ValidateModelWKSP_Pred";
    protected static final String EXPORT = "ValidateModelWKSP_Export";
    protected static final String STATEMODEL = "ValidateModelWKSP_StateModel";
    protected static final String OUTPUTMODEL = "ValidateModelWKSP_OutputModel";
    protected static final String RMSE = "ValidateModelWKSP_RMSE";
    protected static final String CORRCOEF = "ValidateModelWKSP_CORRCOEF";

	public NolValidateModelWKSP (NolMainFrame frame, NolModel2 model, Vector validateDataSeries){ //for demo only
		super(model.getPreprocessor());
		this.frame = frame;	  //for demo only
		this.validateDataSeries = validateDataSeries;
		validateProcessedDataSeries = new Vector();
		validValidation = true;
		noFire = false;
		showOutputLineChart = false;
		showStateLineChart = false;
		validateDataCalculated = false;
		this.model = model;
		testDataSeries = new Vector();
		testPreprocessors = new Vector();
		setTitle("Validate Predictive Model:"+model.getName());
		actionListener = new ControlAction();
		Y = Matlib.createMatrix();
		YPred = Matlib.createMatrix();
		S = Matlib.createMatrix();
		SPred = Matlib.createMatrix();

		outputPredLine = new ColoredSquare(Color.yellow); 
		outputActLine = new ColoredSquare(Color.green); 
		statePredLine = new ColoredSquare(Color.yellow); 
		stateActLine = new ColoredSquare(Color.green); 

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
				detailedTabbedPane.setSelectedIndex(0);
				detailedTabbedPane.addTab(frame.getNolResourceString(STATEMODEL), getStatePredvsActPanel());
				getContentPane().add("Center",detailedTabbedPane);
//			}else{
//				getStatePredvsActPanel();
//				getContentPane().add("Center",getOutputPredvsActPanel());
//			}
		}else{
			getContentPane().add("Center",getOutputPredvsActPanel());
		}
		getContentPane().add("North", getModelNamePanel());
		try{
			initialDisplay();
		} catch (Exception evt){
			frame.showOKDialog("There is a problem with the validation data.");
			evt.printStackTrace();
		}
	}

	public boolean isValidValidation(){
		return validValidation;
	}

	public NolModel2 getModel(){
		return model;
	}
	private JPanel getModelNamePanel(){

		JPanel namePanel = new JPanel(new GridLayout(1,2,5,5));
		JPanel modelInfoPanel = new JPanel(new GridLayout(2,2,5,5));
		modelInfoPanel.setBorder(new EmptyBorder(10, 10, 10, 10));               
		modelInfoPanel.add(new JLabel(frame.getNolResourceString(MODELNAME)+":"));
		modelInfoPanel.add(new JLabel(model.getName()));
		modelInfoPanel.add(new JLabel(frame.getNolResourceString(PREPROCESSOR)+":"));
		modelInfoPanel.add(new JLabel(model.getPreprocessor().getName()));

		JPanel testPanel = new JPanel(new GridLayout());
		testPanel.setBorder(new TitledBorder(new EmptyBorder(1, 1, 1, 1),               
			frame.getNolResourceString(TESTINGDATASERIES)+":", TitledBorder.LEFT , TitledBorder.TOP));
		testDataName = new JList();
		testDataName.setBackground(Color.white);
		JScrollPane listScrollPane = new JScrollPane(testDataName);
		listScrollPane.setBorder(BorderFactory.createLoweredBevelBorder());
		listScrollPane.setPreferredSize(NolMainFrame.vpad50);
		testPanel.add(listScrollPane);

		JPanel varPane = new JPanel(new GridLayout());
		varPane.setBorder(new TitledBorder(new EmptyBorder(1, 1, 1, 1),               
			"Validation Statistics:", TitledBorder.LEFT , TitledBorder.TOP));
		statisticsTableModel = new StatisticsTableModel();
		statisticsTableView = new JTable(statisticsTableModel);
		statisticsTableView.setSelectionMode(0);
		statisticsTableView.setCellSelectionEnabled(true);
		listScrollPane = new JScrollPane(statisticsTableView);
		listScrollPane.setPreferredSize(NolMainFrame.vpad150);
		listScrollPane.setBackground(Color.white);
		varPane.add(listScrollPane);

		JPanel pane2 = new JPanel(new BorderLayout());
		pane2.add("North",modelInfoPanel);
		pane2.add("Center",testPanel);

		namePanel.add(pane2);
		namePanel.add(varPane);
		return namePanel;

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

		outputChoice = new JComboBox();
		outputChoice.addActionListener(actionListener);
		pane0.add(outputChoice);
		control.add(Box.createRigidArea(NolMainFrame.vpad15));
		control.add(pane0);

		pane0 = new JPanel(new GridLayout(2,1,10,10));
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
		control.add(Box.createRigidArea(NolMainFrame.vpad15));
		control.add(pane0);
		control.add(Box.createRigidArea(NolMainFrame.vpad15));
		outputLegendPane = new JPanel(new GridLayout(2,1,10,10));
		outputLegendPane.setBorder(BorderFactory.createTitledBorder(frame.getNolResourceString(LEGEND)+":"));
		outputLegendPane.add(new JLabel("X: "+frame.getNolResourceString(ACT)));
		outputLegendPane.add(new JLabel("Y: "+frame.getNolResourceString(PRED)));
		control.add(outputLegendPane);
		control.add(Box.createRigidArea(NolMainFrame.vpad15));

		JPanel butPane = new JPanel(new GridLayout());
		butPane.setBorder(new EmptyBorder(5,5,5,5));
		JButton but = new JButton(frame.getNolResourceString(EXPORT));
		but.setActionCommand("outputExport");
		but.addActionListener(actionListener);
		butPane.add(but);
		control.add(butPane);

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

		stateChoice = new JComboBox();
		stateChoice.addActionListener(actionListener);
		pane0.add(stateChoice);
		control.add(Box.createRigidArea(NolMainFrame.vpad15));
		control.add(pane0);

		pane0 = new JPanel(new GridLayout(2,1,10,10));
		pane0.setBorder(BorderFactory.createTitledBorder("Chart Style:"));
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
		control.add(Box.createRigidArea(NolMainFrame.vpad15));
		control.add(pane0);
		control.add(Box.createRigidArea(NolMainFrame.vpad15));
		stateLegendPane = new JPanel(new GridLayout(2,1,10,10));
		stateLegendPane.setBorder(BorderFactory.createTitledBorder(frame.getNolResourceString(LEGEND)+":"));
		stateLegendPane.add(new JLabel("X: "+frame.getNolResourceString(ACT)));
		stateLegendPane.add(new JLabel("Y: "+frame.getNolResourceString(PRED)));
		control.add(stateLegendPane);
		control.add(Box.createRigidArea(NolMainFrame.vpad15));

		JPanel butPane = new JPanel(new GridLayout());
		butPane.setBorder(new EmptyBorder(5,5,5,5));
		JButton but = new JButton(frame.getNolResourceString(EXPORT));
		but.setActionCommand("stateExport");
		but.addActionListener(actionListener);
		butPane.add(but);
		control.add(butPane);

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
		Vector outs = model.getOutputs();
		Vector ins = model.getInputs();
		outputChoice.removeAllItems();
		for(int j=0;j<outs.size();j++){
			String name = outs.elementAt(j).toString();
			outputChoice.addItem(name);
		}
		testDataName.setListData(validateDataSeries);
		Preprocessor prep = model.getPreprocessor();
		try{
			prep.applyPreprocessor(validateDataSeries,validateProcessedDataSeries);
		} catch (Exception evt){
			System.out.println("applyPreprocessor Exception " + evt.getMessage());
			evt.printStackTrace();
		}

		int cc = validateProcessedDataSeries.size();
		boolean hasEmptyData = false;
		for(int i=0;i<cc;i++){
			DataSeries ds = (DataSeries)validateProcessedDataSeries.elementAt(i);
//			System.out.println("ds.isEmpty()="+ds.isEmpty());
			if(ds.isEmpty()){
				hasEmptyData = true;
			}
		}

		if(hasEmptyData){
			validValidation = false;
			return;
		}

		if(model instanceof NolOptimizeModel){
			Vector state = ((NolOptimizeModel)model).getState();
			if(twoModels){
				for(int j=0;j<state.size();j++){
					String name = state.elementAt(j).toString();
					stateChoice.addItem(name);
				}
			}
			Matrix X = Matlib.createMatrix();
			try{
				outputTime = model.prepareTrainingSetFromDataSeries(validateProcessedDataSeries,X,Y);
				if(outputTime == null){
					outputTime = new long[Y.getRows()];
					for(int r=0;r<outputTime.length;r++){
						outputTime[r] = (long)r*1000;
					}
				}
			} catch (MathException evt){
				System.err.println("Non-Fatal exception preparing training data: " + evt.getMessage());
				evt.printStackTrace();	
			}
			Model net = model.getModel();

			if(X.getRows() == 0){// check if there is data for evaluation 1/14/2000
				Matlib.clear(X); 
				Toolkit.getDefaultToolkit().beep();
				frame.showOKDialog("There is no valid data for validating output model.");
				return;
			}
			
			try{
				net.evaluate(X,YPred);
			}catch(MathException evt){
				System.err.println("Non-Fatal exception: " + evt.getMessage());
				evt.printStackTrace();
			}
			Matlib.clear(X); // memory leak if not cleared; added by Brian O. Bush, Feb 5, 1998

			if(twoModels){
				Matrix I = Matlib.createMatrix();
				try{
					stateTime = ((NolOptimizeModel)model).prepareTrainingSet2FromDataSeries(validateProcessedDataSeries,I, S);
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
				net = ((NolOptimizeModel)model).getStateModel();

				if(I.getRows() == 0){// check if there is data for evaluation 1/14/2000
					Matlib.clear(I); 	
					Toolkit.getDefaultToolkit().beep();
					frame.showOKDialog("There is no valid data for validating state model.");
					return;
				}


				try{
					net.evaluate(I,SPred);
				}catch(MathException evt){
					System.err.println("Non-Fatal exception: " + evt.getMessage());
					evt.printStackTrace();
				}
				Matlib.clear(I); // memory leak if not cleared; added by Brian O. Bush, Feb 5, 1998
			}
		}else{
			Matrix X = Matlib.createMatrix();
			try{
				outputTime = model.prepareTrainingSetFromDataSeries(validateProcessedDataSeries,X,Y);
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
			
			
			if(X.getRows() == 0){// check if there is data for evaluation 1/14/2000
				Matlib.clear(X); 
				Toolkit.getDefaultToolkit().beep();
				frame.showOKDialog("There is no valid data for validation.");
				return;
			}

//System.out.println("validate x col="+X.getCols()+" x row="+X.getRows());
			try{
				model.evaluate(X,YPred);
			}catch(MathException evt){
				System.err.println("Non-Fatal exception: " + evt.getMessage());
				evt.printStackTrace();
			}
			Matlib.clear(X); // memory leak if not cleared; added by Brian O. Bush, Feb 5, 1998
		}
	
 		refreshChartDisplay();
		Vector variables = new Vector();
		Vector rmse = new Vector();
		Vector corrcoef = new Vector();
		getModelStatistics(variables, rmse, corrcoef);
		statisticsTableModel.setContent(variables,rmse,corrcoef);
		noFire = false;
	}

	private void getModelStatistics(Vector variables, Vector rmse, Vector corrcoef){
		int digits = 4;
		Matrix RMSEmatrix = Matlib.createMatrix();
		Matrix CORR = Matlib.createMatrix();
		try {
			ValidationParameters.calculateValidationStatistics(Y,YPred,RMSEmatrix,CORR);
		} catch(MathException e){
			System.err.println("Non-Fatal exception: " + e.getMessage());
			e.printStackTrace();
		}
		Vector names = model.getOutputVarNames();
		for(int i=0;i<Y.getCols();i++) {
			variables.addElement(names.elementAt(i));
			rmse.addElement(Utilities.formatDouble(RMSEmatrix.get(i), digits));
			corrcoef.addElement(Utilities.formatDouble(CORR.get(i), digits));
		}
		if(twoModels) {
			try {
				ValidationParameters.calculateValidationStatistics(S,SPred,RMSEmatrix,CORR);
			} catch(MathException e){
				System.err.println("Non-Fatal exception: " + e.getMessage());
				e.printStackTrace();
			}
			names = ((NolOptimizeModel) model).getState();
			for(int i=0;i<S.getCols();i++) {
				variables.addElement(names.elementAt(i));
				rmse.addElement(Utilities.formatDouble(RMSEmatrix.get(i), digits));
				corrcoef.addElement(Utilities.formatDouble(CORR.get(i), digits));
			}
		}
		Matlib.clear(RMSEmatrix);
		Matlib.clear(CORR);
	}

	private void refreshChartDisplay(){
		if(Y.getRows() == 0 || YPred.getRows() == 0){
			return;
		}
		if(Y.getRows() != YPred.getRows()) {
			return;
		}
		Matrix temp	= Matlib.createMatrix();
		Matlib.transpose(Y,temp);
		double[][] yy = Matlib.create2DArray(temp);
		double[] y = yy[0];

		Matlib.transpose(YPred,temp);
		double[][] yypp = Matlib.create2DArray(temp);
		double[] yp = yypp[0];
		outputLineChart = new LineChart(outputTime, y, yp,getBackground());
		outputScatChart = new ScatChart(y,yp,false,getBackground());
		showOutputChart();

		if(twoModels){
			Matlib.transpose(S,temp);
			double[][] ss = Matlib.create2DArray(temp);
			double[] s = ss[0];

			Matlib.transpose(SPred,temp);
			double[][] sspp = Matlib.create2DArray(temp);
			double[] sp = sspp[0];
			stateLineChart = new LineChart(stateTime, s, sp,getBackground());
			stateScatChart = new ScatChart(s,sp,false,getBackground());
			showStateChart();
		}
		Matlib.clear(temp); // memory leak if not cleared; added by Brian O. Bush, Feb 5, 1998
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
			outputLegendPane.add(new JLabel(frame.getNolResourceString(ACT)));
			outputLegendPane.add(outputPredLineBut);
			outputLegendPane.add(new JLabel(frame.getNolResourceString(PRED)));
		}else{
			outputLegendPane.setLayout(new GridLayout(2,1,10,10));
			outputLegendPane.add(new JLabel("X: "+frame.getNolResourceString(ACT)));
			outputLegendPane.add(new JLabel("Y: "+frame.getNolResourceString(PRED)));
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
				stateLegendPane.add(new JLabel(frame.getNolResourceString(ACT)));
				stateLegendPane.add(statePredLineBut);
				stateLegendPane.add(new JLabel(frame.getNolResourceString(PRED)));
			}else{
				stateLegendPane.setLayout(new GridLayout(2,1,10,10));
				stateLegendPane.add(new JLabel("X: "+frame.getNolResourceString(ACT)));
				stateLegendPane.add(new JLabel("Y: "+frame.getNolResourceString(PRED)));
			}
			stateLegendPane.repaint();
			stateLegendPane.validate();
		}
	}

  	private void refreshOutputChartDisplay(String varName){
		if(Y.getRows() == 0 || YPred.getRows() == 0) {
			return;
		}
		if(Y.getRows() != YPred.getRows()){
			return;
		}

		Vector outs = model.getOutputs();
		int index = 0;
		for(int j=0;j<outs.size();j++){
			String name = outs.elementAt(j).toString();
			if(varName.equals(name)){
				index = j;
				break;
			}
		}

		Matrix temp	= Matlib.createMatrix();
		Matlib.transpose(Y,temp);
		double[][] yy = Matlib.create2DArray(temp);
		double[] y = yy[index];

		Matlib.transpose(YPred,temp);
		double[][] yypp = Matlib.create2DArray(temp);
		double[] yp = yypp[index];

		Matlib.clear(temp); // memory leak if not cleared; added by Brian O. Bush, Feb 5, 1998

		outputLineChart = new LineChart(outputTime, y, yp,getBackground());
		outputScatChart = new ScatChart(y,yp,false,getBackground());
		showOutputChart();
	}

  	private void refreshStateChartDisplay(String varName){
		if(S.getRows() == 0 || SPred.getRows() == 0){
			return;
		}
		if(S.getRows() != SPred.getRows()){
			return;
		}

		Vector states = ((NolOptimizeModel)model).getState();
		int index = 0;
		for(int j=0;j<states.size();j++){
			String name = states.elementAt(j).toString();
			if(varName.equals(name)){
				index = j;
				break;
			}
		}

		Matrix temp	= Matlib.createMatrix();
		Matlib.transpose(S,temp);
		double[][] ss = Matlib.create2DArray(temp);
		double[] s = ss[index];

		Matlib.transpose(SPred,temp);
		double[][] sspp = Matlib.create2DArray(temp);
		double[] sp = sspp[index];

		Matlib.clear(temp); // memory leak if not cleared; added by Brian O. Bush, Feb 5, 1998

		stateLineChart = new LineChart(stateTime, s, sp,getBackground());
		stateScatChart = new ScatChart(s,sp,false,getBackground());
		showStateChart();
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
	}


/**	 LineChart implementation     */
    class LineChart extends Object{
		private MultiLineChart chart;

		LineChart(long[] time, double[] y, double[] ypred, Color backColor){
			chart = new MultiLineChart(MultiLineChart.SHARED_Y_LAYOUT_STYLE, MultiLineChart.ROW_MODE, backColor);
			int nData = time.length; 
			Color plotColor = Color.green;
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
			highlightColor = Color.green;
			markerFormats[1] = new MarkerFormat
				(plotSymbol, plotColor, highlightColor, baseSize, highlightSize);  
			chart.addDataSeries("Y", time, y, markerFormats, markers, connectorFormat);


			plotColor = Color.yellow;
			plotSymbol = 1;
			connectorFormat = new LineFormat(plotColor, 1);
			highlightColor = null;
			markerFormats = new MarkerFormat[2];
			markerFormats[0] = new MarkerFormat
				(plotSymbol, plotColor, highlightColor, baseSize, highlightSize);
			highlightColor = Color.yellow;
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
			markerFormats[1] = new MarkerFormat
					(plotSymbol, plotColor, highlightColor, baseSize, highlightSize);  
			if(connectors) {
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

		ControlAction() {
			super("controlAction");
		}

		@Override
		public void actionPerformed(ActionEvent e) {
			if(noFire) {
				return;
			}
			String command = e.getActionCommand();
			if(command.equals("outputExport")){
				try{
					Matrix YPAll = Matlib.createMatrix();
					Matlib.appendColumns(YPred,Y,YPAll);
					DataSeries ds = new DataSeries(YPAll);
					ds.setName(model.getName()+frame.getNolResourceString(PRED));
					if(model.getHasTimeStamps()) {
						ds.setTimeStamps(outputTime);
					}
					Preprocessor prep = model.getPreprocessor();
					Vector outs = model.getOutputs();
					int col = YPred.getCols();
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
					Toolkit.getDefaultToolkit().beep();
					frame.showOKDialog("Error in saving data.");
					return;
				}
				Toolkit.getDefaultToolkit().beep();
			}else if(command.equals("stateExport")){
				try{
					DataSeries ds = new DataSeries(SPred);
					ds.setName(model.getName()+frame.getNolResourceString(PRED));
					if(model.getHasTimeStamps()) {
						ds.setTimeStamps(stateTime);
					}
					Preprocessor prep = model.getPreprocessor();
					Vector states = ((NolOptimizeModel)model).getState();
					for(int c=0;c<SPred.getCols();c++){
						String varName = (String) states.elementAt(c);
						Variable varObj = prep.getVariableFromVariableName(varName);
						String varTag = varObj.getTag();
						ds.setVariableParameters(c,varTag,varName,"None");
					}
					frame.exportActionPerformed(ds);
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
				}
				else outputZoomOutButton.setEnabled(true);
			}else if(command.equals("state X-Y Chart")){
				showStateLineChart = false;
				showStateChart();
				if(stateScatZoomInCounterX <= 0) {
					stateZoomOutButton.setEnabled(false);
				}
				else stateZoomOutButton.setEnabled(true);
			}else if(command.equals("output Line Chart")){
				showOutputLineChart = true;
				showOutputChart();
				if(outputLineZoomInCounterX <= 0) {
					outputZoomOutButton.setEnabled(false);
				}
				else outputZoomOutButton.setEnabled(true);
			}else if(command.equals("state Line Chart")){
				showStateLineChart = true;
				showStateChart();
				if(stateLineZoomInCounterX <= 0) {
					stateZoomOutButton.setEnabled(false);
				}
				else stateZoomOutButton.setEnabled(true);
			}else if(command.equals("outputactualColor")){
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
			}else if(e.getSource().equals(outputChoice)) {  // Variable Choice on Predicted vs Actual pane
				noFire = true;
				String varName = (String)outputChoice.getSelectedItem();
				refreshOutputChartDisplay(varName);
				noFire = false;
			}else if(e.getSource().equals(stateChoice)) {  // Variable Choice on Predicted vs Actual pane
				noFire = true;
				String varName = (String)stateChoice.getSelectedItem();
				refreshStateChartDisplay(varName);
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
					if(outputLineZoomInCounterX <= 0) {
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

	class StatisticsTableModel extends AbstractTableModel{
		private int row,col;
		private Vector variables;
		private Vector rmse;
		private Vector corrcoef;
		private String[] colHd = {frame.getNolResourceString(VARIABLE),
			frame.getNolResourceString(RMSE),
			frame.getNolResourceString(CORRCOEF)
		};
		public StatisticsTableModel(){
			row = 0;
			col = 3;
		}

		public void setContent(Vector variables, Vector rmse, Vector corrcoef){
			this.variables = variables;
			this.rmse = rmse;
			this.corrcoef = corrcoef;
			row = variables.size();
		}
		@Override
		public int getColumnCount() { return col; }
		@Override
		public int getRowCount() { return row;}
		@Override
		public Object getValueAt(int r, int c){
			if(c == 0){
				return variables.elementAt(r);
			}else if(c == 1){
				return rmse.elementAt(r);
			}else if(c==2){
				return corrcoef.elementAt(r);
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
			return false;
		}
		
		@Override
		public void setValueAt(Object aValue, int r, int c) {
		}
	}
}

