package com.gensym.nols.wksp;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import javax.swing.*;
import javax.swing.border.*;

import com.gensym.nols.main.*;
import com.gensym.nols.chart.line.*;
import com.gensym.math.matrix.*;
import com.gensym.math.*;

import com.gensym.nols.data.*;
import com.gensym.nols.util.*;

import com.gensym.nols.chart.scatter.*;

public class NolValidatePcaWKSP extends NolInternalFrame implements ActionListener, ChartListener, RawDataSourceListener, PreprocessorListener, Runnable {
	private ScatterChart twoDchart;
	private MultiLineChart singlechart;
	private MultiLineChart spechart;

	protected boolean zooming;
	protected int zoomFlag; //0:xy; 1:x; 2:y.
	private Vector varsShown;
	private Vector varsFullyQualifiedNameShown;
	private Vector varsContainingNaNs;
	private NolPcaModel model;
	private DefaultListModel varListModel;
	
	private NolMainFrame frame;
	private JComboBox xaxis;
	private JComboBox yaxis;
	private JLabel twoDChartLabel;
	private JButton zoomOutButton;
	private JButton singlezoomOutButton;
	private JButton spezoomOutButton;
	private int zoomInCounterX;
	private int zoomInCounterY;
	private int singlezoomInCounterX;
	private int spezoomInCounterX;

	private String command;
	private Object source;
	private int state;
	private Matrix validateScore;
	private Matrix validateRes;
	private DataSeries dataSeries;
	private JComboBox singlefactorChoice;


	private JLabel singleChartLabel;
	private JLabel speChartLabel;

	private static final boolean DEBUG = false;

	private static final String ZOOM = "ProjectionChartFrame_Zoom";
	private static final String XAXIS = "ProjectionChartFrame_XAxis";
	private static final String YAXIS = "ProjectionChartFrame_YAxis";
	private static final String XANDY = "ProjectionChartFrame_XAndY";
	private static final String ZOOMIN = "ProjectionChartFrame_ZoomIn";
	private static final String ZOOMOUT = "ProjectionChartFrame_ZoomOut";
	private static final String VARIABLES = "ProjectionChartFrame_Variables";
	private static final String ADD = "ProjectionChartFrame_Add";
	private static final String REMOVE = "ProjectionChartFrame_Remove";
	private static final String SHOW = "ProjectionChartFrame_Show";
	private static final String DATASERIES = "ProjectionChartFrame_DataSeries";
	private static final String ADDDATASERIES = "ProjectionChartFrame_AddDataSeries";
	private static final String REMOVEDATASERIES = "ProjectionChartFrame_RemoveDataSeries";
	private static final String EXPORT = "ProjectionChartFrame_Export";
	private static final String FACTOR = "ProjectionChartFrame_Factor";
	private static final String NFACTOR = "ProjectionChartFrame_Number_Factor";

	public NolValidatePcaWKSP (NolMainFrame frame, NolPcaModel model, DataSeries ds) throws MathException {
		super();
		state = 0; // the default state, everything ok.
		// 1 = error state 1, chart is empty, var list full, PC choice empty
		// 2 = higher error state

		this.frame = frame;
		this.model = model;
		this.dataSeries = ds;

		zoomFlag = 0;

		twoDchart = new ScatterChart(getBackground());
		twoDchart.holdOn();
		twoDchart.addChartListener(this);
		twoDchart.setAxisColor(Color.black);
		twoDchart.setAxisColor(Color.black);
		twoDchart.setBackground(Color.lightGray);

		spechart = new MultiLineChart(MultiLineChart.SHARED_Y_LAYOUT_STYLE, MultiLineChart.ROW_MODE,getBackground());
		spechart.holdOn();
		spechart.addChartListener(this);
		spechart.setAxisColor(Color.black);
		spechart.setAxisColor(Color.black);
		spechart.setBackground(Color.lightGray);	
		spechart.holdOff();


		singlechart = new MultiLineChart(MultiLineChart.SHARED_Y_LAYOUT_STYLE, MultiLineChart.ROW_MODE,getBackground());
		singlechart.holdOn();
		singlechart.addChartListener(this);
		singlechart.setAxisColor(Color.black);
		singlechart.setAxisColor(Color.black);
		singlechart.setBackground(Color.lightGray);
		
		setTitle();
		initialLayout();
		initializeData(ds);
		initialControlDisplay();
		twoDchart.setFortyFiveDegreeLine(false);
		spechart.holdOff();
		singlechart.holdOff();
		twoDchart.holdOff();

	}

	private void initialLayout(){
		JPanel workPane = new JPanel(new GridLayout());
													    
		JTabbedPane detailedTabbedPane = new JTabbedPane();
		detailedTabbedPane.addTab("2D chart", get2DPanel());
		detailedTabbedPane.setSelectedIndex(0);
		detailedTabbedPane.addTab("Single PC Chart", getSinglePCPanel());
		detailedTabbedPane.addTab("SPE Chart", getSPEPanel());

		workPane.add(detailedTabbedPane);
		setContentPane(workPane);

	}

	private JPanel get2DPanel() {
		
		JPanel showPane = new JPanel(new GridLayout(2,2,5,5));
		showPane.setBorder(BorderFactory.createTitledBorder(frame.getNolResourceString(SHOW)+":"));
		showPane.add(new JLabel(frame.getNolResourceString(XAXIS)+":"));
		xaxis = new JComboBox();
		Dimension dim = new Dimension(55,20);
		xaxis.setPreferredSize(dim);
		xaxis.setMinimumSize(dim);
		xaxis.setMaximumSize(dim);
		showPane.add(xaxis);
		showPane.add(new JLabel(frame.getNolResourceString(YAXIS)+":"));
		yaxis = new JComboBox();
		yaxis.setPreferredSize(dim);
		yaxis.setMinimumSize(dim);
		yaxis.setMaximumSize(dim);
		showPane.add(yaxis);

		JPanel zoomPane = new JPanel(new GridLayout(5,1,5,5));
		zoomPane.setBorder(BorderFactory.createTitledBorder(frame.getNolResourceString(ZOOM)+":"));		
		ButtonGroup group = new ButtonGroup();
		JRadioButton radio = new JRadioButton(frame.getNolResourceString(XAXIS));
		radio.setActionCommand("X Axis");
		group.add(radio);
		zoomPane.add(radio);
		radio.addActionListener(this);
		radio = new JRadioButton(frame.getNolResourceString(YAXIS));
		radio.setActionCommand("Y Axis");
		group.add(radio);
		zoomPane.add(radio);
		radio.addActionListener(this);
		radio = new JRadioButton(frame.getNolResourceString(XANDY), true);
		radio.setActionCommand("X and Y");
		group.add(radio);
		zoomPane.add(radio);
		radio.addActionListener(this);
		JButton zoom = new JButton(frame.getNolResourceString(ZOOMIN));
		zoom.setActionCommand("2D Zoom In");
		zoomInCounterX = 0;
		zoomInCounterY = 0;
		zoomPane.add(zoom);
		zoom.addActionListener(this);
		zoomOutButton = new JButton(frame.getNolResourceString(ZOOMOUT));
		zoomOutButton.setActionCommand("2D Zoom Out");
		zoomOutButton.setEnabled(false);
		zoomPane.add(zoomOutButton);
		zoomOutButton.addActionListener(this);

		JPanel legendPane = new JPanel(new GridLayout(2,2,10,10));
		legendPane.setBorder(BorderFactory.createTitledBorder(frame.getNolResourceString("ValidateModelWKSP_Legend")+":"));
		ColoredSquare outputPredLine = new ColoredSquare(Color.red); 
		ColoredSquare outputActLine = new ColoredSquare(Color.green); 
		JButton	but = new JButton(outputActLine);
		legendPane.add(but);
		legendPane.add(new JLabel(frame.getNolResourceString("ValidateModelWKSP_Orig")));
		but = new JButton(outputPredLine);
		legendPane.add(but);
		legendPane.add(new JLabel(frame.getNolResourceString("ValidateModelWKSP_Vali")));

		JPanel controls1 = new JPanel();
		controls1.setLayout(new BoxLayout(controls1, BoxLayout.Y_AXIS));
		controls1.add(Box.createRigidArea(NolMainFrame.vpad20));
		controls1.add(showPane);
		controls1.add(zoomPane);
		controls1.add(legendPane);
		controls1.add(Box.createRigidArea(NolMainFrame.vpad200));
		
		
		JPanel chartPane = new JPanel(new BorderLayout());
		chartPane.setBorder(new EmptyBorder(10,10,10,10));
		chartPane.add("Center", twoDchart);
		twoDChartLabel = new JLabel();
		twoDChartLabel.setHorizontalAlignment(SwingConstants.CENTER); 
		chartPane.add("North", twoDChartLabel);
		
		JPanel twodpanel = new JPanel();
		twodpanel.setLayout(new BorderLayout());


		twodpanel.add("Center", chartPane);
		twodpanel.add("East", controls1);
		return twodpanel;

	}

	private JPanel getSinglePCPanel(){
		JPanel singlePane = new JPanel();
		JPanel showPane = new JPanel(new GridLayout(1,2,5,5));
		showPane.setBorder(BorderFactory.createTitledBorder(frame.getNolResourceString(SHOW)+":"));
		showPane.add(new JLabel(frame.getNolResourceString("LoadingChartFrame_Number_Factor")+":"));
		singlefactorChoice = new JComboBox();
		Dimension dim = new Dimension(55,20);
		singlefactorChoice.setPreferredSize(dim);
		singlefactorChoice.setMinimumSize(dim);
		singlefactorChoice.setMaximumSize(dim);
		showPane.add(singlefactorChoice);

		JPanel zoomPane = new JPanel(new GridLayout(2,1,5,5));
		zoomPane.setBorder(BorderFactory.createTitledBorder(frame.getNolResourceString(ZOOM)+":"));		
		JButton zoom = new JButton(frame.getNolResourceString(ZOOMIN));
		zoom.setActionCommand("Single Zoom In");
		singlezoomInCounterX = 0;
		zoomPane.add(zoom);
		zoom.addActionListener(this);
		singlezoomOutButton = new JButton(frame.getNolResourceString(ZOOMOUT));
		singlezoomOutButton.setActionCommand("Single Zoom Out");
		singlezoomOutButton.setEnabled(false);
		zoomPane.add(singlezoomOutButton);
		singlezoomOutButton.addActionListener(this);

		JPanel controls = new JPanel();
		controls.setLayout(new BoxLayout(controls, BoxLayout.Y_AXIS));

		controls.add(Box.createRigidArea(NolMainFrame.vpad20));
		controls.add(showPane);
		controls.add(zoomPane);
		controls.add(Box.createRigidArea(NolMainFrame.vpad500));

		JPanel chartPane = new JPanel(new BorderLayout());
		chartPane.setBorder(new EmptyBorder(10,10,10,10));
		chartPane.add("Center", singlechart);
		singleChartLabel = new JLabel();
		singleChartLabel.setHorizontalAlignment(SwingConstants.CENTER); 
		chartPane.add("North", singleChartLabel);

 		singlePane.setLayout(new BorderLayout());
		singlePane.add("Center", chartPane);
		singlePane.add("East", controls);

		return singlePane;
	}

	private JPanel getSPEPanel(){
		JPanel spePane = new JPanel();
		JPanel zoomPane = new JPanel(new GridLayout(2,1,5,5));
		zoomPane.setBorder(BorderFactory.createTitledBorder(frame.getNolResourceString(ZOOM)+":"));		
		JButton zoom = new JButton(frame.getNolResourceString(ZOOMIN));
		zoom.setActionCommand("SPE Zoom In");
		spezoomInCounterX = 0;
		zoomPane.add(zoom);
		zoom.addActionListener(this);
		spezoomOutButton = new JButton(frame.getNolResourceString(ZOOMOUT));
		spezoomOutButton.setActionCommand("SPE Zoom Out");
		spezoomOutButton.setEnabled(false);
		zoomPane.add(spezoomOutButton);
		spezoomOutButton.addActionListener(this);

		JPanel controls = new JPanel();
		controls.setLayout(new BoxLayout(controls, BoxLayout.Y_AXIS));

		controls.add(Box.createRigidArea(NolMainFrame.vpad20));
		controls.add(zoomPane);
		controls.add(Box.createRigidArea(NolMainFrame.vpad500));

		JPanel chartPane = new JPanel(new BorderLayout());
		chartPane.setBorder(new EmptyBorder(10,10,10,10));
		chartPane.add("Center", spechart);
		speChartLabel = new JLabel();
		speChartLabel.setHorizontalAlignment(SwingConstants.CENTER); 
		chartPane.add("North", speChartLabel);

 		spePane.setLayout(new BorderLayout());
		spePane.add("Center", chartPane);
		spePane.add("East", controls);
		return spePane;
	}

	private void setTitle() {
		String title = "Validation Plot - "+ model.getName();
		setTitle(title);
		Point p = this.getLocation();
		this.setLocation(p.x+1,p.y);
		this.setLocation(p.x,p.y);
	}
	
/*	public ScatterChart getChart() {
		return chart;
	}
  */
	public DefaultListModel getVarListModel() {
		if (varListModel == null) {
			varListModel = new DefaultListModel();
		}
		return varListModel;
	}


	private void initializeData(DataSeries dataSeries) throws MathException {

		Vector inputs = model.getInputs();
		int nVar = dataSeries.getColumn();
		Matrix X0 = dataSeries.getDataMatrix();  // do not clear or change X0, it is permanent!
		// temporary matrices, must be cleared
		Matrix X = Matlib.createMatrix();  
		int ncols = X0.getCols();
		Matrix S = Matlib.createMatrix(1,ncols);
		for(int i=0; i<ncols; i++) {
			Variable var = dataSeries.getVarByIndex(i);
			boolean included = inputs.contains(var.getName());
			if (included) {
				S.set(0,i,1.0);
			}else{
				S.set(0,i,0.0);
			}
		}
		Matlib.getColumns(X0, S, X);
		if(validateScore == null){
			validateScore = Matlib.createMatrix();
		}
		if(validateRes == null) {
			validateRes = Matlib.createMatrix();
		}
		model.fullEvaluate(X,validateScore,validateRes);

		Matrix score = model.getScore();
		Matrix T =  Matlib.createMatrix();
		Matlib.getColumns(score, 0, 1, T);
		// Put the scores in double arrays for plotting
		Matlib.transpose(T, T);
		double[][] xy = Matlib.create2DArray(T);
 		double[] x = xy[0];
		double[] y = xy[1];
		int nData = x.length;
		// Build the plot
		Color plotColor = Color.green;
		int plotSymbol = 1;
		LineFormat connectorFormat = new LineFormat(plotColor, 1);
		byte[] markers = new byte[nData];
		int baseSize = 4;  // what if chart has been zoomed?
		int highlightSize = 10;
		Color highlightColor = null;
		MarkerFormat unhighlightedMarker = new MarkerFormat
			(plotSymbol, plotColor, highlightColor, baseSize, highlightSize);
		MarkerFormat[] markerFormats;
		markerFormats = new MarkerFormat[1];
		markerFormats[0] = unhighlightedMarker;
		twoDchart.addDataSeries("Base", x, y, markerFormats, markers); 

		Matlib.getColumns(validateScore, 0, 1, T);
		// Put the scores in double arrays for plotting
		Matlib.transpose(T, T);
		xy = Matlib.create2DArray(T);
 		x = xy[0];
		y = xy[1];
		nData = x.length;
		markers = new byte[nData];
		plotColor = Color.red;
		connectorFormat = new LineFormat(plotColor, 1);
		highlightColor = Color.red;
		unhighlightedMarker = new MarkerFormat
			(plotSymbol, plotColor, highlightColor, baseSize, highlightSize);
		markerFormats = new MarkerFormat[1];
		markerFormats[0] = unhighlightedMarker;
		twoDchart.addDataSeries(dataSeries.getName(), x, y,markerFormats, markers); 		
		twoDChartLabel.setText(frame.getNolResourceString("ValidationChartFrame_Chart_Label")+":"+ dataSeries.getName());

	
	

		Matlib.getColumns(score, 0, 0, T);
		// Put the scores in double arrays for plotting
		x = Matlib.create1DArray(T);
		Matlib.getColumns(validateScore, 0, 0, T);
		y = Matlib.create1DArray(T);
		singleChartLabel.setText(frame.getNolResourceString("ScoreChartFrame_Chart_Label")+" 1");
		Matrix pclims = model.getScoreLimits();
		double pclimit = pclims.get(0);
		showSingleChart(x,y,pclimit);

		
		Matrix res = model.getSPEStatistics();
		x = Matlib.create1DArray(res);
		y = Matlib.create1DArray(validateRes);
		speChartLabel.setText(frame.getNolResourceString("ResidualFrame_Chart_Label"));
		double q = model.getQ();
		showSPEChart(x,y,q);

		Matlib.clear(X);
		Matlib.clear(S);
		Matlib.clear(T);
	
	}



	private void showSingleChart(final double[] x, final double[] y, final double limit){
		double[] xPoints = x;
		double[] yPoints = y;
		int nData = xPoints.length;
		long[] time = new long[nData];
		if(yPoints.length != nData){
			if (yPoints.length < nData){
				double[] yy = new double[nData];
				for(int r=0;r<yPoints.length;r++){
					yy[r] = yPoints[r];
				}
				for(int r=yPoints.length;r<nData;r++){
					yy[r] = Double.NaN;
				}
				yPoints = yy;
			}else{
				double[] xx = new double[yPoints.length];
				for(int r=0;r<nData;r++){
					xx[r] = xPoints[r];
				}
				for(int r=nData;r<yPoints.length;r++){
					xx[r] = Double.NaN;
				}
				xPoints = xx;
			}
		}
		double[] suplimit = new double[nData];
		double[] slowlimit = new double[nData];
		for(int r=0;r<time.length;r++){
			time[r] = (long)r*1000;
			suplimit[r] = limit;
			slowlimit[r] = -limit;
		}
		Color plotColor = Color.green;
		int plotSymbol = 0;
		LineFormat connectorFormat = new LineFormat(plotColor, 1);
		byte[] markers = new byte[nData];
		int baseSize = 6;  // what if chart has been zoomed?
		int highlightSize = 10;
		Color highlightColor = null;
		MarkerFormat unhighlightedMarker = new MarkerFormat
			(plotSymbol, plotColor, highlightColor, baseSize, highlightSize);
		MarkerFormat[] markerFormats = new MarkerFormat[1];
		markerFormats[0] = unhighlightedMarker;	
		singlechart.removeAllDataSeries();
		singlechart.addDataSeries("Score", time, xPoints, markerFormats, markers, connectorFormat);

		plotColor = Color.red;
		plotSymbol = 1;
		connectorFormat = new LineFormat(plotColor, 1);
		highlightColor = null;
		markerFormats = new MarkerFormat[1];
		markerFormats[0] = new MarkerFormat
			(plotSymbol, plotColor, highlightColor, baseSize, highlightSize);
		singlechart.addDataSeries("lowLimit", time, yPoints, markerFormats, markers, connectorFormat);

		plotColor = Color.yellow;
		plotSymbol = 1;
		connectorFormat = new LineFormat(plotColor, 1);
		highlightColor = null;
		markerFormats = new MarkerFormat[1];
		markerFormats[0] = new MarkerFormat
			(plotSymbol, plotColor, highlightColor, baseSize, highlightSize);
		singlechart.addDataSeries("upLimit", time, suplimit, markerFormats, markers, connectorFormat);
		singlechart.addDataSeries("lowLimit", time, slowlimit, markerFormats, markers, connectorFormat);
	}

	private void showSPEChart(final double[] x, final double[] y, final double q){
		double[] xPoints = x;
		double[] yPoints = y;
		int nData = xPoints.length;
		long[] time = new long[nData];
		if(yPoints.length != nData){
			if (yPoints.length < nData){
				double[] yy = new double[nData];
				for(int r=0;r<yPoints.length;r++){
					yy[r] = yPoints[r];
				}
				for(int r=yPoints.length;r<nData;r++){
					yy[r] = Double.NaN;
				}
				yPoints = yy;
			}else{
				double[] xx = new double[yPoints.length];
				for(int r=0;r<nData;r++){
					xx[r] = xPoints[r];
				}
				for(int r=nData;r<yPoints.length;r++){
					xx[r] = Double.NaN;
				}
				xPoints = xx;
			}
		}
		double[] qLimit = new double[nData];
		for(int r=0;r<time.length;r++){
			time[r] = (long)r*1000;
			qLimit[r] = q;
		}
		Color plotColor = Color.green;
		int plotSymbol = 0;
		LineFormat connectorFormat = new LineFormat(plotColor, 1);
		byte[] markers = new byte[nData];
		int baseSize = 6;  // what if chart has been zoomed?
		int highlightSize = 10;
		Color highlightColor = null;
		MarkerFormat unhighlightedMarker = new MarkerFormat
			(plotSymbol, plotColor, highlightColor, baseSize, highlightSize);
		MarkerFormat[] markerFormats = new MarkerFormat[1];
		markerFormats[0] = unhighlightedMarker;	
		spechart.removeAllDataSeries();
		spechart.addDataSeries("SPE", time, xPoints, markerFormats, markers, connectorFormat);

		plotColor = Color.red;
		plotSymbol = 1;
		connectorFormat = new LineFormat(plotColor, 1);
		highlightColor = null;
		markerFormats = new MarkerFormat[1];
		markerFormats[0] = new MarkerFormat
			(plotSymbol, plotColor, highlightColor, baseSize, highlightSize);
		spechart.addDataSeries("Validate SPE", time, yPoints, markerFormats, markers, connectorFormat);

		plotColor = Color.yellow;
		plotSymbol = 1;
		connectorFormat = new LineFormat(plotColor, 1);
		highlightColor = null;
		markerFormats = new MarkerFormat[1];
		markerFormats[0] = new MarkerFormat
			(plotSymbol, plotColor, highlightColor, baseSize, highlightSize);
		spechart.addDataSeries("Q", time, qLimit, markerFormats, markers, connectorFormat);
	}

	private void initialControlDisplay(){
		xaxis.removeActionListener(this);
		yaxis.removeActionListener(this);
		Matrix score = model.getScore();
		int nPC = model.getRetainedFactorNumber();
		xaxis.removeAllItems();
		yaxis.removeAllItems();
		for(int i = 1; i <= nPC; i++){
			String name = "PC "+i;
			xaxis.addItem(name);
			yaxis.addItem(name);			
		}
		yaxis.setSelectedIndex(1);
		// defered adding listeners, to prevent extra events during initialization
		xaxis.addActionListener(this);
		yaxis.addActionListener(this);

		singlefactorChoice.removeAllItems();
		for(int i = 1; i <= nPC; i++){
			String name = "PC "+i;
			singlefactorChoice.addItem(name);
		}
		singlefactorChoice.setSelectedIndex(0);
		// defered adding listeners, to prevent extra events during initialization
		singlefactorChoice.addActionListener(this);
	}

	private void displayNewXYData(){
		int xindex = xaxis.getSelectedIndex();
		int yindex = yaxis.getSelectedIndex();
		if(xindex<0 || yindex < 0){
			return;
		}
		Matrix score = model.getScore();
		Matrix T = Matlib.createMatrix();
		double[] x = null, y = null;
		try {
			Matlib.getColumn(score,xindex,T);
			Matlib.transpose(T,T);
			x = Matlib.create1DArray(T);
			Matlib.getColumn(score,yindex,T);
			Matlib.transpose(T,T);
			y = Matlib.create1DArray(T);
		} catch(MathException e) {
			System.err.println("Non-Fatal exception: " + e.getMessage());
			e.printStackTrace();
		}
		int nData = x.length;
		byte[] markers = new byte[nData];
		twoDchart.setDataSeries("Base", x, y, markers); 

		try {
			Matlib.getColumn(validateScore,xindex,T);
			Matlib.transpose(T,T);
			x = Matlib.create1DArray(T);
			Matlib.getColumn(validateScore,yindex,T);
			Matlib.transpose(T,T);
			y = Matlib.create1DArray(T);
		} catch(MathException e) {
			System.err.println("Non-Fatal exception: " + e.getMessage());
			e.printStackTrace();
		}
  		nData = x.length;
		markers = new byte[nData];
		twoDchart.setDataSeries(dataSeries.getName(), x, y, markers); 

		Matlib.clear(T);
	}

	private void showNewPC()throws MathException {
		int pcNumber = singlefactorChoice.getSelectedIndex();
		Matrix score = model.getScore();
		Matrix T =  Matlib.createMatrix();
		Matlib.getColumns(score, pcNumber, pcNumber, T);
		// Put the scores in double arrays for plotting
		singleChartLabel.setText(frame.getNolResourceString("ScoreChartFrame_Chart_Label")+" "+(pcNumber+1));
		double[] x = Matlib.create1DArray(T);
		Matlib.getColumns(validateScore, pcNumber, pcNumber, T);
		double[] y = Matlib.create1DArray(T);
		Matrix pclims = model.getScoreLimits();
		double pclimit = pclims.get(pcNumber);
		Matlib.clear(T);
		showSingleChart(x,y,pclimit);
	}


	@Override
	public void actionPerformed(ActionEvent e) {
		// handle all actions outside of the main UI thread, otherwise the UI hangs
		command = e.getActionCommand ();
		source = e.getSource ();
		new Thread (this).start ();
	}

	@Override
	public void run() {
//		setWaitCursor(true);
		if ("2D Zoom In".equals(command)) {
			zoomIn();
		}else if ("Single Zoom In".equals(command)) {
			zoomInSingle();
		}else if ("SPE Zoom In".equals(command)){
			zoomInSPE();
		}else if ("2D Zoom Out".equals(command)){
			zoomOut();
		}else if ("Single Zoom Out".equals(command)){
			zoomOutSingle();
		}else if ("SPE Zoom Out".equals(command)) {
			zoomOutSPE();
		}else if ("X and Y".equals(command)){
			zoomFlag = 0;
			if(zoomInCounterX>0 && zoomInCounterY>0) {
				zoomOutButton.setEnabled(true);
			}else {
				zoomOutButton.setEnabled(false);
			}
		} else if ("X Axis".equals(command)){
			zoomFlag = 1;
			if(zoomInCounterX>0) {
				zoomOutButton.setEnabled(true);
			}else {
				zoomOutButton.setEnabled(false);
			}
		} else if ("Y Axis".equals(command)){
			zoomFlag = 2;
			if(zoomInCounterY>0) {
				zoomOutButton.setEnabled(true);
			}else{
				zoomOutButton.setEnabled(false);
			}
		} else if(source.equals(xaxis) || source.equals(yaxis)){
			displayNewXYData();
		}else if(source.equals(singlefactorChoice)){
			try{
				showNewPC();
			}catch(MathException evt){}
		}
		setWaitCursor(false);
	}


	public void zoomIn() {
		//System.out.println("***STARTING ZOOM IN ACTION***");
		if(!zoomOutButton.isEnabled()) 
			zoomOutButton.setEnabled(true);
		if(zoomFlag == 0) {
			zoomInCounterX++;
			zoomInCounterY++;
			twoDchart.zoomIn();
		} else if(zoomFlag == 1) {
			zoomInCounterX++;
			twoDchart.zoomInX();
		} else if(zoomFlag == 2) {
			zoomInCounterY++;
			twoDchart.zoomInY();
		}
	}

	public void zoomOut() {
		//System.out.println("***STARTING ZOOM OUT ACTION***");
		if(zoomFlag == 0) {
			zoomInCounterX--;
			zoomInCounterY--;
			if(zoomInCounterX <= 0 || zoomInCounterY <= 0){
				zoomOutButton.setEnabled(false);
			}
			twoDchart.zoomOut();
		} else if(zoomFlag == 1) {
			zoomInCounterX--;
			if(zoomInCounterX <= 0) {
				zoomOutButton.setEnabled(false);
			}
			twoDchart.zoomOutX();
		} else if(zoomFlag == 2) {
			zoomInCounterY--;
			if(zoomInCounterY <= 0) {
				zoomOutButton.setEnabled(false);
			}
			twoDchart.zoomOutY();
		}
		if(zoomInCounterX<0) {
			zoomInCounterX = 0;
		}
		if(zoomInCounterY<0) {
			zoomInCounterY = 0;
		}
	}

	public void zoomInSingle() {
		//System.out.println("***STARTING ZOOM IN ACTION***");
		if(!singlezoomOutButton.isEnabled()) 
			singlezoomOutButton.setEnabled(true);
		singlezoomInCounterX++;
		singlechart.zoomIn();
	}

	public void zoomOutSingle() {
		//System.out.println("***STARTING ZOOM OUT ACTION***");
		singlezoomInCounterX--;
		if(singlezoomInCounterX <= 0) {
			singlezoomOutButton.setEnabled(false);
		}
		singlechart.zoomOut();
		if(singlezoomInCounterX<0){
			singlezoomInCounterX = 0;
		}
	}

	public void zoomInSPE() {
		//System.out.println("***STARTING ZOOM IN ACTION***");
		if(!spezoomOutButton.isEnabled()) 
			spezoomOutButton.setEnabled(true);
		spezoomInCounterX++;
		spechart.zoomIn();
	}

	public void zoomOutSPE() {
		//System.out.println("***STARTING ZOOM OUT ACTION***");
		spezoomInCounterX--;
		if(spezoomInCounterX <= 0){
			spezoomOutButton.setEnabled(false);
		}
		spechart.zoomOut();
		if(spezoomInCounterX<0) {
			spezoomInCounterX = 0;
		}
	}

	//  CHART EVENT LISTENERS
	
	@Override
	public void chartPointSelected(ChartEvent e) {	}

	@Override
	public void chartAreaSelected(ChartEvent e) {}
	@Override
	public void chartPopupTriggered(ChartEvent e){}
	// RAW DATA EVENT LISTENERS
	@Override
	public void DataSeriesAdded(RawDataEvent e){}
	@Override
	public void DataSeriesRemoved(RawDataEvent e){}
	@Override
	public void LabelCategoryAdded(RawDataEvent evt) {} 
	@Override
	public void LabelCategoryRemoved(RawDataEvent evt) {}
	@Override
	public void LabelColorChanged(RawDataEvent evt) {}
	@Override
	public void LabelNameChanged(RawDataEvent evt) {}
	@Override
	public void DataPointsLabeled(RawDataEvent evt) {}
	@Override
	public void LabelOrderChanged(RawDataEvent evt) {}
	@Override
	public void FormulaListChanged(PreprocessorEvent evt) {} 
	@Override
	public void DataChanged(PreprocessorEvent evt) {}
	private void updatePlotsForLabels(RawDataSource rawDataSource){	}
}
