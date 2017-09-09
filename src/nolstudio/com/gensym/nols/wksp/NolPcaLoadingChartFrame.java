package com.gensym.nols.wksp;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import javax.swing.*;
import javax.swing.border.*;
import javax.swing.table.*;

import com.gensym.nols.main.*;
import com.gensym.nols.chart.line.*;
import com.gensym.math.matrix.*;
import com.gensym.math.*;

import com.gensym.nols.data.*;
import com.gensym.nols.dlg.*;
import com.gensym.nols.util.*;

public class NolPcaLoadingChartFrame extends NolInternalFrame implements ActionListener, ChartListener, RawDataSourceListener, PreprocessorListener, Runnable {
	private MultiLineChart chart;
	protected boolean zooming;
	private NolPcaModel model;
	
	private NolMainFrame frame;
	private JComboBox factorChoice;
	
	private JButton zoomOutButton;
	private int zoomInCounterX;

	private String command;
	private Object source;
	private NolList varList;

	private JLabel chartLabel;

	private	LoadingTableModel loadingTableModel;
	private	JTable loadingTableview;
	private TableSorter loadingSorter;

	private static final boolean DEBUG = false;

	private static final String ZOOM = "ProjectionChartFrame_Zoom";
	private static final String ZOOMIN = "ProjectionChartFrame_ZoomIn";
	private static final String ZOOMOUT = "ProjectionChartFrame_ZoomOut";
	private static final String SHOW = "ProjectionChartFrame_Show";

	private static int COLUMNWIDTH = 100;
	private static int LASTCOLUMNWIDTH = 20;
	private int sigDigits = 8;

	public NolPcaLoadingChartFrame (NolMainFrame frame, NolPcaModel model) throws MathException {
		super();

		this.frame = frame;
		this.model = model;
		chart = new MultiLineChart(MultiLineChart.SHARED_Y_LAYOUT_STYLE, MultiLineChart.ROW_MODE,getBackground());
		chart.holdOn();
		chart.addChartListener(this);
		chart.setAxisColor(Color.black);

		chart.setAxisColor(Color.black);
		setTitle();
		initialLayout();
		initializeData();
		initialControlDisplay();
		
		chart.holdOff();
	}

	private void initialLayout() {
		
		JPanel showPane = new JPanel(new GridLayout(1,2,5,5));
		showPane.setBorder(BorderFactory.createTitledBorder(frame.getNolResourceString(SHOW)+":"));
		showPane.add(new JLabel(frame.getNolResourceString("LoadingChartFrame_Number_Factor")+":"));
		factorChoice = new JComboBox();
		Dimension dim = new Dimension(55,20);
		factorChoice.setPreferredSize(dim);
		factorChoice.setMinimumSize(dim);
		factorChoice.setMaximumSize(dim);
		showPane.add(factorChoice);

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

		JPanel listPane = new JPanel(new GridLayout(1,1,5,5));
		listPane.setBorder(BorderFactory.createTitledBorder(frame.getNolResourceString("VariableLabel")+":"));
		DefaultListModel varListModel = new DefaultListModel();
		varList = new NolList(varListModel);
		JScrollPane listScrollPane = new JScrollPane(varList);
		listScrollPane.setBorder(BorderFactory.createLoweredBevelBorder());
		dim = new Dimension(100,200);
		listScrollPane.setPreferredSize(dim);
		listScrollPane.setMinimumSize(dim);
		listScrollPane.setMaximumSize(dim);
		listPane.add(listScrollPane);

		JPanel controls = new JPanel();
		controls.setLayout(new BoxLayout(controls, BoxLayout.Y_AXIS));

		controls.add(Box.createRigidArea(NolMainFrame.vpad20));
		controls.add(showPane);
		controls.add(listPane);
		controls.add(zoomPane);
		controls.add(Box.createRigidArea(NolMainFrame.vpad500));

		JPanel chartPane = new JPanel(new BorderLayout());
		chartPane.setBorder(new EmptyBorder(10,10,10,10));
		chartPane.add("Center", chart);
		chartLabel = new JLabel();
		chartLabel.setHorizontalAlignment(SwingConstants.CENTER); 
		chartPane.add("North", chartLabel);

		Vector inputs = model.getInputs();
		Matrix loadings = model.getLoadings();
		loadingTableModel = new LoadingTableModel(inputs,loadings);
		loadingSorter = new TableSorter(loadingTableModel); 
		loadingTableview = new JTable(loadingSorter);
		loadingSorter.addMouseListenerToHeaderInTable(loadingTableview);
		turnOffAutoColumn(loadingTableview);
		loadingTableview.setSelectionMode(0);
		loadingTableview.setCellSelectionEnabled(true);
		JScrollPane tablePane = new JScrollPane(loadingTableview);
		tablePane.setBackground(Color.white);
		
		JPanel contentPane = new JPanel(new BorderLayout());
		contentPane.add("Center", chartPane);
		contentPane.add("East", controls);

		JTabbedPane detailedTabbedPane = new JTabbedPane();
 		detailedTabbedPane.addTab("Chart", contentPane);
		detailedTabbedPane.setSelectedIndex(0);
		detailedTabbedPane.addTab("Table", tablePane);


		getContentPane().setLayout(new GridLayout());
		getContentPane().add(detailedTabbedPane);
	}

	private void setTitle() {
		String title = "PCA Loading Chart - "+ model.getName();
		setTitle(title);
		Point p = this.getLocation();
		this.setLocation(p.x+1,p.y);
		this.setLocation(p.x,p.y);
	}
	
	private void turnOffAutoColumn(JTable table){
		int cc = table.getColumnCount();
		if(cc>4){
			table.setAutoResizeMode(JTable.AUTO_RESIZE_OFF);
			setMinWithColumn(table);
		}else{
			table.setAutoResizeMode(JTable.AUTO_RESIZE_ALL_COLUMNS);
		}

		TableColumnModel cm = table.getColumnModel();
		TableColumn cl = cm.getColumn(cc-1);
		cl.setPreferredWidth(LASTCOLUMNWIDTH);
	}

	private void setMinWithColumn(JTable table){
		TableColumnModel cm = table.getColumnModel();
		int cc = cm.getColumnCount();
		for(int i=0;i<cc;i++){
		TableColumn cl = cm.getColumn(i);
			cl.setMinWidth(COLUMNWIDTH);
		}

	}

	public MultiLineChart getChart() {
		return chart;
	}

	private void initializeData() throws MathException {

		Project2 project = frame.getProject();
		Matrix loading = model.getLoadings();
		Matrix T =  Matlib.createMatrix();
		Matlib.getColumns(loading, 0, 0, T);
		// Put the scores in double arrays for plotting
		double[] x = Matlib.create1DArray(T);
		chartLabel.setText(frame.getNolResourceString("LoadingChartFrame_Chart_Label")+" 1");
		showChart(x);
		Matlib.clear(T);
	}


	private void initialControlDisplay(){
		Matrix score = model.getScore();
		int nPC = score.getCols();
		factorChoice.removeAllItems();
		for(int i = 1; i <= nPC; i++){
			String name = "PC "+i;
			factorChoice.addItem(name);
		}
		factorChoice.setSelectedIndex(0);
		// defered adding listeners, to prevent extra events during initialization
		factorChoice.addActionListener(this);
		Vector names = model.getInputs();
		Vector newNames = new Vector();
		for(int i=0;i<names.size();i++){
			newNames.addElement((i+1) +":"+names.elementAt(i).toString());
		}
		varList.addElements(newNames);
	}

	private void showNewLoading()throws MathException {
		int pcNumber = factorChoice.getSelectedIndex();
		Project2 project = frame.getProject();
		Matrix loading = model.getLoadings();
		Matrix T =  Matlib.createMatrix();
		Matlib.getColumns(loading, pcNumber, pcNumber, T);
		// Put the scores in double arrays for plotting
		chartLabel.setText(frame.getNolResourceString("LoadingChartFrame_Chart_Label")+" "+(pcNumber+1));
		double[] x = Matlib.create1DArray(T);
		showChart(x);
		Matlib.clear(T);
	}

	private void showChart(double[] x){
		int nData = x.length;
		long[] time = new long[nData];
		double[] zeroBase = new double[nData];
		for(int r=0;r<time.length;r++){
			time[r] = (long)r*1000;
			zeroBase[r] = 0.0;
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
		chart.addDataSeries("Loadings", time, x, markerFormats, markers, connectorFormat);

		plotColor = Color.red;
		plotSymbol = 1;
		connectorFormat = new LineFormat(plotColor, 1);
		highlightColor = null;
		markerFormats = new MarkerFormat[1];
		markerFormats[0] = new MarkerFormat
			(plotSymbol, plotColor, highlightColor, baseSize, highlightSize);
		chart.addDataSeries("Zero", time, zeroBase, markerFormats, markers, connectorFormat);
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
		if ("Zoom In".equals(command)){
			zoomIn();
		}else if ("Zoom Out".equals(command)) {
			zoomOut();
		}else if(source.equals(factorChoice)){
			try{
				showNewLoading();
			}catch(MathException evt){}
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

	class LoadingTableModel extends AbstractTableModel{
		private int row,col;
		private String[] colHd;
		private String[] rowHd;
		private Vector inputs;
		private Matrix values;

		public LoadingTableModel(Vector inputs, Matrix values){
			this.inputs = inputs;
			this.values = values;
			row = inputs.size();
			col = values.getCols()+1;
			colHd = new String[col];
			rowHd = new String[row];		
			colHd[0] = frame.getNolResourceString("NameLabel");			
			for(int i=0;i<row;i++){
				rowHd[i] = inputs.elementAt(i).toString();
			}
			for(int i=1;i<col;i++){
				colHd[i] = "PC"+i;
			}
		}
		@Override
		public int getColumnCount() { return col; }
		@Override
		public int getRowCount() { return row;}
		

		@Override
		public Object getValueAt(int r, int c){
			if(c == 0){
				return rowHd[r];
			}else {
				if(Double.isNaN(values.get(r,c-1))){
					return "";
				}else{
					return Utilities.formatDouble(values.get(r,c-1), sigDigits);
				}
			}
		}

		@Override
		public String getColumnName(int c) {
			return colHd[c];
		}
		@Override
		public boolean isCellEditable(int r, int c) {
			return false;
		}		
		@Override
		public void setValueAt(Object aValue, int r, int c) {
		}
		@Override
		public Class getColumnClass(int c) {
			return getValueAt(0, c).getClass();
		}
	}
}

