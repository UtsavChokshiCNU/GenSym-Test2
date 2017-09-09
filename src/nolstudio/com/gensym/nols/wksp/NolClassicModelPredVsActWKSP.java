package com.gensym.nols.wksp;

import java.awt.*;
import java.awt.event.*;
import java.util.*;

import javax.swing.*;
import javax.swing.border.*;

import com.gensym.math.*;
import com.gensym.math.matrix.*;

import com.gensym.nols.main.*;
import com.gensym.nols.util.*;
import com.gensym.nols.dlg.*;
import com.gensym.nols.data.*;
import com.gensym.nols.chart.line.*;
import com.gensym.nols.chart.scatter.*;

public class NolClassicModelPredVsActWKSP extends NolInternalFrame {

	private NolModel2 model;
	private Matrix Y;
	private Matrix YP;
	private Matrix YError;
	private Matrix YErrorStd;
	private ControlAction actionListener;
	private boolean noFire;
	private boolean showOutputLineChart;
	private long[] outputTime;
 	private JPanel outputViewPane;
 	private JPanel outputLegendPane;
	private JPanel outputExportPane;
	private JComboBox outputVarChoice;
	private JRadioButton plotTrain;
	private JRadioButton plotTest;
	private LineChart outputLineChart;
	private ScatChart outputScatChart;
	// new in 2.1
	private int currentPlotOption;
	private int currentModelOption;
	private int outputDisplayIndex;

	private ColoredSquare outputPredLine;
	private ColoredSquare outputActLine;
	private Color predictedColor;  // MK added, 5/16/99 so colors persist when changing plots
	private Color actualColor; 
	private JButton outputPredLineBut;
	private JButton outputActLineBut;
	private NolMainFrame frame;	 

	private static int PLOT_ALL = 0;
	private static int PLOT_TRAIN = 1;
	private static int PLOT_TEST = 2;

	private JButton outputZoomOutButton;
	private int outputLineZoomInCounterX;
	private int outputScatZoomInCounterX;
	
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

	private JComboBox errorVarChoice;
	private JPanel errorViewPane;
 	private LineChart errorLineChart;

	private JButton errorZoomOutButton;
	private int errorLineZoomInCounterX;
	private int errorDisplayIndex;

	public NolClassicModelPredVsActWKSP (NolMainFrame frame, NolModel2 model) { 
		super(model.getPreprocessor());
		this.frame = frame;	 
		noFire = false;
		showOutputLineChart = false;
		this.model = model;
		setTitle("Predicted vs Actual of "+model.getName());
		actionListener = new ControlAction();
		Y = Matlib.createMatrix();
		YP = Matlib.createMatrix();
		YError = Matlib.createMatrix();
		YErrorStd = Matlib.createMatrix();
		outputPredLine = new ColoredSquare(Color.yellow); 
		outputActLine = new ColoredSquare(Color.green); 
		predictedColor = Color.yellow;
		actualColor = Color.green;
		outputDisplayIndex = 0;
		errorDisplayIndex = 0;

		JTabbedPane detailedTabbedPane = new JTabbedPane();
 		detailedTabbedPane.addTab(frame.getNolResourceString("ModelWKSP_PredVsAct"), getOutputPredvsActPanel());
		detailedTabbedPane.setSelectedIndex(0);
		detailedTabbedPane.addTab(frame.getNolResourceString("ModelWKSP_Error"), getErrorPanel());

		getContentPane().setLayout(new GridLayout());
		getContentPane().add(detailedTabbedPane);
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
	
	private JPanel getErrorPanel(){
		JPanel errorPane = new JPanel(new BorderLayout());
		errorViewPane = new JPanel(new GridLayout());
		errorViewPane.setBackground(Color.white);
		JScrollPane listScrollPane = new JScrollPane(errorViewPane);
		listScrollPane.setBackground(Color.white);
		listScrollPane.setBorder(BorderFactory.createLoweredBevelBorder());

		JPanel control = new JPanel();
		control.setBackground(getContentPane().getBackground());
		control.setLayout(new BoxLayout(control, BoxLayout.Y_AXIS));

		JPanel pane0 = new JPanel(new GridLayout());
		pane0.setBorder(BorderFactory.createTitledBorder(frame.getNolResourceString(VARIABLE)+":"));		
		errorVarChoice = new JComboBox();
		errorVarChoice.addActionListener(actionListener);
		pane0.add(errorVarChoice);
		control.add(pane0);
		
		JPanel zoomPane = new JPanel(new GridLayout(1,2,5,5));
		zoomPane.setBorder(BorderFactory.createTitledBorder(frame.getNolResourceString("ModelWKSP_Zoom")+":"));		
		JButton zoom = new JButton(frame.getNolResourceString("ModelWKSP_ZoomIn"));
		zoom.setActionCommand("Error Zoom In");
		errorLineZoomInCounterX = 0;
		zoomPane.add(zoom);
		zoom.addActionListener(actionListener);
		errorZoomOutButton = new JButton(frame.getNolResourceString("ModelWKSP_ZoomOut"));
		errorZoomOutButton.setActionCommand("Error Zoom Out");
		errorZoomOutButton.setEnabled(false);
		zoomPane.add(errorZoomOutButton);
		errorZoomOutButton.addActionListener(actionListener);
		control.add(zoomPane);

		control.add(Box.createRigidArea(NolMainFrame.vpad500));
		control.add(Box.createVerticalGlue());

		errorPane.add("Center",listScrollPane);
		errorPane.add("East",control);
		return errorPane;
	}

	public void initialDisplay(){
		noFire = true;
		currentPlotOption = PLOT_ALL;
		currentModelOption = -1;  // ensemble
		Vector outs = model.getOutputs();
		Vector ins = model.getInputs();
		Matrix X = Matlib.createMatrix();
		Matrix I = Matlib.createMatrix();
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
		outputVarChoice.removeAllItems();
		errorVarChoice.removeAllItems();
		for(int j=0;j<outs.size();j++){
			String name = outs.elementAt(j).toString();
			outputVarChoice.addItem(name);
			errorVarChoice.addItem(name);
		}

		calculatePredictions(X);
		Matlib.clear(X);
		// determine whether we can show training and test subsets, models didn't store this into prior to V2.1
		plotTrain.setEnabled(false);
		plotTest.setEnabled(false);
		refreshChartDisplay();
		refreshErrorChartDisplay();
		noFire = false;
	}


	private void calculatePredictions(Matrix X) {
		try {
			model.evaluate(X,YP);
			Matlib.subtract(Y,YP,YError);
			Matlib.stdnonzero(YError, YErrorStd);
		} catch (MathException evt) {
			System.err.println("Non-Fatal exception preparing training data: " + evt.getMessage());
			evt.printStackTrace();
		}
	}

	private void refreshChartDisplay() {
		if(Y.getRows() == 0 || YP.getRows() == 0) {
			return;
		}
		if(Y.getRows() != YP.getRows()){
			return;
		}
		Matrix temp	= Matlib.createMatrix();
		Matlib.transpose(Y,temp);
		double[][] yy = Matlib.create2DArray(temp);
		double[] y = yy[outputDisplayIndex];

		Matlib.transpose(YP,temp);
		double[][] yyp = Matlib.create2DArray(temp);
		double[] yp = yyp[outputDisplayIndex];

		outputLineChart = new LineChart(outputTime, y, yp,getBackground());
		outputScatChart = new ScatChart(y,yp,false,getBackground());
		showOutputChart();

		Matlib.clear(temp); 
	}

	private void refreshErrorChartDisplay(){

		Matrix temp	= Matlib.createMatrix();
		Matlib.transpose(YError,temp);
		double[][] yye = Matlib.create2DArray(temp);
		double[] ye = yye[errorDisplayIndex];
		double[] base = new double[ye.length];

		Matlib.transpose(YErrorStd,temp);
		double[] yyestd = Matlib.create1DArray(temp);
		double yestd = yyestd[errorDisplayIndex];
		double[] upl = new double[ye.length];
		double[] lowl = new double[ye.length];
		for(int i=0;i<ye.length;i++){
			upl[i] = 2.0*yestd;
			lowl[i] = - 2.0*yestd;
		}
		errorLineChart = new LineChart(outputTime, ye,base,upl,lowl,getBackground());
		errorViewPane.removeAll();
		errorViewPane.add(errorLineChart.getChart());
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


/** LineChart implementation  */
    class LineChart extends Object{
		private MultiLineChart chart;

		LineChart(long[] time, double[] y, double[] ypred, Color backColor){
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

		LineChart(long[] time, double[] y,Color backColor){
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
			chart.setAxisColor(Color.black);
		}
		
		LineChart(long[] time, double[] ye, double[] base,double[] upl, double[] lowl,Color backColor){
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
			highlightColor = plotColor;
			markerFormats[1] = new MarkerFormat
				(plotSymbol, plotColor, highlightColor, baseSize, highlightSize);  
			chart.addDataSeries("Error", time, ye, markerFormats, markers, connectorFormat);
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
			chart.addDataSeries("Mean", time, base, markerFormats, markers, connectorFormat);

			plotColor = Color.red;
			plotSymbol = 1;
			connectorFormat = new LineFormat(plotColor, 1);
			highlightColor = null;
			markerFormats = new MarkerFormat[2];
			markerFormats[0] = new MarkerFormat
				(plotSymbol, plotColor, highlightColor, baseSize, highlightSize);
			highlightColor = predictedColor;
			markerFormats[1] = new MarkerFormat
				(plotSymbol, plotColor, highlightColor, baseSize, highlightSize);  
			chart.addDataSeries("Upper Limit", time, upl, markerFormats, markers, connectorFormat);
			plotColor = Color.red;
			plotSymbol = 1;
			connectorFormat = new LineFormat(plotColor, 1);
			highlightColor = null;
			markerFormats = new MarkerFormat[2];
			markerFormats[0] = new MarkerFormat
				(plotSymbol, plotColor, highlightColor, baseSize, highlightSize);
			highlightColor = predictedColor;
			markerFormats[1] = new MarkerFormat
				(plotSymbol, plotColor, highlightColor, baseSize, highlightSize);  
			chart.addDataSeries("Lower Limit", time, lowl, markerFormats, markers, connectorFormat);
			chart.setAxisColor(Color.black);
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
			}else if(command.equals("outputExportAll")) {
				try{
					Matrix YPAll = Matlib.createMatrix();
					Matlib.appendColumns(YP,Y,YPAll);
					DataSeries ds = new DataSeries(YPAll);
					ds.setName(model.getName()+frame.getNolResourceString(PRED));
					if(model.getHasTimeStamps()) {
						ds.setTimeStamps(outputTime);
					}
					Preprocessor prep = model.getPreprocessor();
					Vector outs = model.getOutputs();
					int col = Y.getCols();
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
			}else if(command.equals("output X-Y Chart")){
				showOutputLineChart = false;
				showOutputChart();
				if(outputScatZoomInCounterX <= 0) {
					outputZoomOutButton.setEnabled(false);
				}else {
					outputZoomOutButton.setEnabled(true);
				}
			}else if(command.equals("output Line Chart")){
				showOutputLineChart = true;
				showOutputChart();
				if(outputLineZoomInCounterX <= 0) {
					outputZoomOutButton.setEnabled(false);
				}else {
					outputZoomOutButton.setEnabled(true);
				}
			}else if(command.equals("plotAll")) {
				currentPlotOption = PLOT_ALL;
				refreshChartDisplay();
			}else if(command.equals("plotTrain")) {
				currentPlotOption = PLOT_TRAIN;
				refreshChartDisplay();
			}else if(command.equals("plotTest")) {
				currentPlotOption = PLOT_TEST;
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
			}else if(command.equals("Error Zoom In")){
				if(!errorZoomOutButton.isEnabled()) 
					errorZoomOutButton.setEnabled(true);
				errorLineChart.getChart().zoomIn();
				errorLineZoomInCounterX++;
			}else if(command.equals("Error Zoom Out")){
				errorLineZoomInCounterX--;
				if(errorLineZoomInCounterX <= 0) {
					errorZoomOutButton.setEnabled(false);
				}
				errorLineChart.getChart().zoomOut();
				if(errorLineZoomInCounterX<0) {
					errorLineZoomInCounterX = 0;
				}
			}else if(e.getSource().equals(errorVarChoice)) {  // Variable Choice on Predicted vs Actual pane
				noFire = true;
				String varName = (String)errorVarChoice.getSelectedItem();
				Vector outs = model.getOutputs();
				int index = 0;
				for(int j=0;j<outs.size();j++){
					String name = outs.elementAt(j).toString();
					if(varName.equals(name)){
						index = j;
						break;
					}
				}
				errorDisplayIndex = index;
				refreshErrorChartDisplay();
				noFire = false;
			}
		}
    }
}

