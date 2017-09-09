package com.gensym.nols.wksp;

import java.awt.*;
import java.awt.event.*;
import java.net.URL;
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

public class NolRecusivePredVsActWKSP extends NolInternalFrame {

	private NolAutorecursiveModel model;
	private Vector predictions;
	private ControlAction actionListener;
	private boolean noFire;
	private boolean showOutputLineChart;
 	private JPanel outputViewPane;
 	private JPanel outputLegendPane;
	private JPanel outputExportPane;
	private JComboBox outputVarChoice;
	private JRadioButton plotTrain;
	private JRadioButton plotTest;
	private LineChart outputLineChart;
	private ScatChart outputScatChart;
	
	// new in 2.1
	private int currentModelOption;
	private int outputDisplayIndex;

	private int horizon;
	private int maxHorizon;
	private JTextField hrfield;

	private ColoredSquare outputPredLine;
	private ColoredSquare outputActLine;
	private Color predictedColor;  // MK added, 5/16/99 so colors persist when changing plots
	private Color actualColor; 
	private JButton outputPredLineBut;
	private JButton outputActLineBut;
	private NolMainFrame frame;	 


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
    private static final String HORIZON = "ModelPredVsActWKSP_PredictHorizon";
	

	public NolRecusivePredVsActWKSP (NolMainFrame frame, NolModel2 model) { 
		super(model.getPreprocessor());
		this.frame = frame;	 
		noFire = false;
		showOutputLineChart = false;
		this.model = (NolAutorecursiveModel)model;
		setTitle("Predicted vs Actual of "+model.getName());
		actionListener = new ControlAction();
		predictions = new Vector();
		outputPredLine = new ColoredSquare(Color.yellow); 
		outputActLine = new ColoredSquare(Color.green); 
		predictedColor = Color.yellow;
		actualColor = Color.green;
		outputDisplayIndex = 0;
		getContentPane().setLayout(new BorderLayout());
		getContentPane().add("Center",getOutputPredvsActPanel());
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


		pane0 = new JPanel(new GridLayout(1,3,5,5));
		pane0.setBorder(new TitledBorder(new EmptyBorder(1, 1, 1, 1),               
			frame.getNolResourceString(HORIZON)+":", TitledBorder.LEFT , TitledBorder.TOP));

		URL url = this.getClass().getResource("down.gif");
		ImageIcon butIcon = new ImageIcon(url);

		JButton downButton = new JButton(butIcon);
		downButton.setActionCommand("decreaseHorizon");
 		downButton.addActionListener(actionListener);

		url = this.getClass().getResource("up.gif");
		butIcon = new ImageIcon(url);

		JButton upButton = new JButton(butIcon);
		upButton.setActionCommand("increaseHorizon");
 		upButton.addActionListener(actionListener);
		
		hrfield  = new JTextField("0");
		hrfield.setEditable(false);
		pane0.add(downButton);
		pane0.add(hrfield);
		pane0.add(upButton);
		control.add(pane0);

		control.add(Box.createRigidArea(NolMainFrame.vpad300));
		control.add(Box.createVerticalGlue());

		predActPane.add("Center",listScrollPane);
		predActPane.add("East",control);
		return predActPane;
	}
	
	public void initialDisplay(){
		noFire = true;
		currentModelOption = -1;  // ensemble
		maxHorizon = 100;
		Vector outs = model.getOutputs();
		Vector ins = model.getInputs();
		Matrix X = Matlib.createMatrix();
		Matrix Y = Matlib.createMatrix();
		Matrix YP = Matlib.createMatrix();
		try{
			long[] outputTime = model.prepareTrainingSet(X, Y);
			if(outputTime == null){
				outputTime = new long[Y.getRows()];
				for(int r=0;r<outputTime.length;r++){
					outputTime[r] = (long)r*1000;
				}
			}

			outputVarChoice.removeAllItems();
			for(int j=0;j<outs.size();j++){
				String name = outs.elementAt(j).toString();
				outputVarChoice.addItem(name);
			}

			EnsembleModel net = (EnsembleModel) model.getModel();
			net.evaluate(X,YP);
			Matlib.clear(X);
			Prediction p = new Prediction(outputTime,Y,YP,0);
			predictions.addElement(p);
		} catch(MathException evt){
			System.err.println("Non-Fatal exception preparing training set: " + evt.getMessage());
			evt.printStackTrace();
		}
		horizon  = 0;
		refreshChartDisplay(horizon);
		noFire = false;
	}

	private void preparePredictionData(int h){
		Matrix X = Matlib.createMatrix();
		Matrix Y = Matlib.createMatrix();
		Matrix YP = Matlib.createMatrix();
		try{
			long[] outputTime = model.prepareDataSet(X, Y,h,predictions);
			EnsembleModel net = (EnsembleModel) model.getModel();
			net.evaluate(X,YP);
			Matlib.clear(X);
			Prediction p = new Prediction(outputTime,Y,YP,h);
//System.out.println("get here 04 add p");
			predictions.addElement(p);
		} catch(MathException evt){
			System.err.println("Non-Fatal exception preparing training set: " + evt.getMessage());
			evt.printStackTrace();
		}
	}

	private void refreshChartDisplay(int horizon) {
		int s = predictions.size();
		if(s == 0){
			return;
		}
		Prediction p = (Prediction)predictions.elementAt(s - 1);
		if(horizon > p.getHorizon()){
			for(int i=s;i<horizon+1;i++){
				preparePredictionData(i);	
			}
		}

		Prediction pp = (Prediction)predictions.elementAt(0);
		for(int i=0;i<predictions.size();i++){
			pp = (Prediction)predictions.elementAt(i);
			if(horizon == pp.getHorizon()){
//System.out.println("get here 04 i="+i);
				break;
			}
			if(i== predictions.size()-1){
				return;
			}
		}
//System.out.println("get here 04");
//System.out.println("get here 04 pp.getHorizon()="+pp.getHorizon());
		Matrix Y = pp.getY();
		Matrix YP = pp.getYP();
		long[] outputTime = pp.getTimeStamps();

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
		double[][] yypp = Matlib.create2DArray(temp);
		double[] yp = yypp[outputDisplayIndex];
		outputLineChart = new LineChart(outputTime, y, yp, getBackground());
		outputScatChart = new ScatChart(y,yp,false, getBackground());
		showOutputChart();
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
		ScatChart(double[] y, double[] ypred, boolean connectors,Color back){
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

	private Prediction getCurrentPrediction(){
		Prediction pp = (Prediction)predictions.elementAt(0);
		for(int i=0;i<predictions.size();i++){
			pp = (Prediction)predictions.elementAt(i);
			if(horizon == pp.getHorizon()){
				break;
			}
			if(i== predictions.size()-1){
				return null;
			}
		}
		return pp;
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
					Prediction p = getCurrentPrediction();
					Matrix YP = p.getYP();
					Matrix Y = p.getY();
					long[] outputTime = p.getTimeStamps();
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
					Prediction p = getCurrentPrediction();
					Matrix YP = p.getYP();
					Matrix Y = p.getY();
					long[] outputTime = p.getTimeStamps();
					Matrix YPAll = Matlib.createMatrix();
					Matlib.appendColumns(Y,YP,YPAll);
					DataSeries ds = new DataSeries(YPAll);
					ds.setName(model.getName()+frame.getNolResourceString(PRED));
					ds.setTimeStamps(outputTime);
					Preprocessor prep = model.getPreprocessor();
					Vector outs = model.getOutputs();
					int col = Y.getCols();
/*
		System.out.println("YP.getCols()="+YP.getCols());
		System.out.println("YP.getRows()="+YP.getRows());
		System.out.println("Y.getCols()="+Y.getCols());
		System.out.println("YPAll.getCols()="+YPAll.getCols());
		System.out.println("Y.getRows()="+Y.getRows());
		System.out.println("YPAll.getRows()="+YPAll.getRows());
*/
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
			}else if(command.equals("output Line Chart")){
				showOutputLineChart = true;
				showOutputChart();
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
				refreshChartDisplay(horizon);
				noFire = false;
			}else if(command.equals("decreaseHorizon")) {
//System.out.println("decreaseHorizon");
				if(horizon <= 0) {
					return;
				}
				horizon = horizon - 1;
				refreshChartDisplay(horizon);
				hrfield.setText(horizon+"");
			}else if(command.equals("increaseHorizon")) {
//System.out.println("increaseHorizon");
				if(horizon >= maxHorizon) {
					return;
				}
				horizon = horizon + 1;
				hrfield.setText(horizon+"");
				refreshChartDisplay(horizon);
			}
		}
    }
}
