package com.gensym.nols.wksp;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.border.*;

import com.gensym.nols.main.*;
import com.gensym.nols.chart.line.*;
import com.gensym.math.matrix.*;
import com.gensym.math.*;

import com.gensym.nols.data.*;

public class NolResidualChartFrame extends NolInternalFrame implements ActionListener, ChartListener, RawDataSourceListener, PreprocessorListener, Runnable {
	private MultiLineChart chart;
	protected boolean zooming;
	private NolPcaModel model;
	
	private NolMainFrame frame;
	
	private JButton zoomOutButton;
	private int zoomInCounterX;

	private String command;
	private Object source;

	private JLabel chartLabel;

	private static final boolean DEBUG = false;

	private static final String ZOOM = "ProjectionChartFrame_Zoom";
	private static final String ZOOMIN = "ProjectionChartFrame_ZoomIn";
	private static final String ZOOMOUT = "ProjectionChartFrame_ZoomOut";
	private static final String SHOW = "ProjectionChartFrame_Show";

	public NolResidualChartFrame (NolMainFrame frame, NolPcaModel model) throws MathException {
		super();

		this.frame = frame;
		this.model = model;
		chart = new MultiLineChart(MultiLineChart.SHARED_Y_LAYOUT_STYLE, MultiLineChart.ROW_MODE,getBackground());
		chart.holdOn();
		chart.addChartListener(this);
		chart.setAxisColor(Color.black);

		chart.setAxisColor(Color.black);
		chart.setBackground(Color.lightGray);

		setTitle();
		initialLayout();
		initializeData();
		
		chart.holdOff();
	}

	private void initialLayout() {
		
		JPanel zoomPane = new JPanel(new GridLayout(2,1,5,5));
		zoomPane.setBorder(BorderFactory.createTitledBorder(frame.getNolResourceString(ZOOM)+":"));		
		JButton zoom = new JButton(frame.getNolResourceString(ZOOMIN));
		zoom.setActionCommand("Zoom In");
		zoomInCounterX = 0;
		zoomPane.add(zoom);
		zoom.addActionListener(this);
		zoomOutButton = new JButton(frame.getNolResourceString(ZOOMOUT));
		zoomOutButton.setActionCommand("Zoom Out");
		zoomOutButton.setEnabled(false);
		zoomPane.add(zoomOutButton);
		zoomOutButton.addActionListener(this);

		JPanel controls = new JPanel();
		controls.setLayout(new BoxLayout(controls, BoxLayout.Y_AXIS));

		controls.add(Box.createRigidArea(NolMainFrame.vpad20));
		controls.add(zoomPane);
		controls.add(Box.createRigidArea(NolMainFrame.vpad500));

		JPanel chartPane = new JPanel(new BorderLayout());
		chartPane.setBorder(new EmptyBorder(10,10,10,10));
		chartPane.add("Center", chart);
		chartLabel = new JLabel();
		chartLabel.setHorizontalAlignment(SwingConstants.CENTER); 
		chartPane.add("North", chartLabel);

 		getContentPane().setLayout(new BorderLayout());
		getContentPane().add("Center", chartPane);
		getContentPane().add("East", controls);
	}

	private void setTitle() {
		String title = frame.getNolResourceString("ResidualFrame_Chart_Label")+" - "+ model.getName();
		setTitle(title);
		Point p = this.getLocation();
		this.setLocation(p.x+1,p.y);
		this.setLocation(p.x,p.y);
	}
	

	public MultiLineChart getChart() {
		return chart;
	}

	private void initializeData() throws MathException {

		Project2 project = frame.getProject();
//		Matrix res = model.getT2Statistics();
		Matrix res = model.getSPEStatistics();
		double[] x = Matlib.create1DArray(res);
		chartLabel.setText(frame.getNolResourceString("ResidualFrame_Chart_Label"));
		double q = model.getQ();
//		double q = model.getT2Limits();
		showChart(x,q);
	}

	private void showChart(double[] x, double q){
		int nData = x.length;
		long[] time = new long[nData];
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
		chart.removeAllDataSeries();
		chart.addDataSeries("SPE", time, x, markerFormats, markers, connectorFormat);

		plotColor = Color.red;
		plotSymbol = 1;
		connectorFormat = new LineFormat(plotColor, 1);
		highlightColor = null;
		markerFormats = new MarkerFormat[1];
		markerFormats[0] = new MarkerFormat
			(plotSymbol, plotColor, highlightColor, baseSize, highlightSize);
		chart.addDataSeries("Q", time, qLimit, markerFormats, markers, connectorFormat);
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
		if ("Zoom In".equals(command)) {
			zoomIn();
		}else if ("Zoom Out".equals(command)){
			zoomOut();
		}
		setWaitCursor(false);
	}


	public void zoomIn() {
		//System.out.println("***STARTING ZOOM IN ACTION***");
		if(!zoomOutButton.isEnabled()) 
			zoomOutButton.setEnabled(true);
		zoomInCounterX++;
		chart.zoomIn();
	}

	public void zoomOut() {
		//System.out.println("***STARTING ZOOM OUT ACTION***");
		zoomInCounterX--;
		if(zoomInCounterX <= 0) {
			zoomOutButton.setEnabled(false);
		}
		chart.zoomOut();
		if(zoomInCounterX<0) {
			zoomInCounterX = 0;
		}
	}

	//  CHART EVENT LISTENERS
	
	@Override
	public void chartPointSelected(ChartEvent e){}
	@Override
	public void chartAreaSelected(ChartEvent e){}
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

	/**
	  *
	  * DataPointsLabeled (RawDataEvent e)
	  * modified by bbush, 10-7-98
	  **/
	@Override
	public void DataPointsLabeled(RawDataEvent evt) {}
	@Override
	public void LabelOrderChanged(RawDataEvent evt) {}
	@Override
	public void FormulaListChanged(PreprocessorEvent evt) {} 
	@Override
	public void DataChanged(PreprocessorEvent evt) {}															   
}

