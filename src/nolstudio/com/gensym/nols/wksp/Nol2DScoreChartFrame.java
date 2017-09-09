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
import com.gensym.nols.dlg.*;
import com.gensym.nols.util.*;

import com.gensym.nols.chart.scatter.*;

public class Nol2DScoreChartFrame extends NolInternalFrame implements ActionListener, ChartListener, RawDataSourceListener, PreprocessorListener, Runnable {
	private ScatterChart chart;
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
	private JButton zoomOutButton;
	private int zoomInCounterX;
	private int zoomInCounterY;

	private Vector insertedColorBlocks;
	private Vector insertedColorIndeces;

	protected JPopupMenu popUp;
	private String command;
	private Object source;
	private int state;

	private NolList dataList;
	private DefaultListModel dataListModel;

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

	public Nol2DScoreChartFrame (NolMainFrame frame, NolPcaModel model) throws MathException {
		super();
		state = 0; // the default state, everything ok.
		// 1 = error state 1, chart is empty, var list full, PC choice empty
		// 2 = higher error state

		this.frame = frame;
		this.model = model;

		zoomFlag = 0;

		chart = new ScatterChart(getBackground());
		chart.holdOn();
		chart.addChartListener(this);
		chart.setAxisColor(Color.black);

		chart.setAxisColor(Color.black);

		setTitle();
		initialLayout();
		initializeData();
		initialControlDisplay();
		
		chart.setFortyFiveDegreeLine(false);
		chart.holdOff();

		insertedColorBlocks = new Vector();
		insertedColorIndeces = new Vector();
	}

	private void initialLayout() {
		
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
		zoom.setActionCommand("Zoom In");
		zoomInCounterX = 0;
		zoomInCounterY = 0;
		zoomPane.add(zoom);
		zoom.addActionListener(this);
		zoomOutButton = new JButton(frame.getNolResourceString(ZOOMOUT));
		zoomOutButton.setActionCommand("Zoom Out");
		zoomOutButton.setEnabled(false);
		zoomPane.add(zoomOutButton);
		zoomOutButton.addActionListener(this);

		JPanel controls = new JPanel();
		controls.setLayout(new BoxLayout(controls, BoxLayout.Y_AXIS));

		
		JPanel controls1 = new JPanel();
		controls1.setLayout(new BoxLayout(controls1, BoxLayout.Y_AXIS));
		controls1.add(showPane);
		controls1.add(zoomPane);
		controls1.add(Box.createRigidArea(NolMainFrame.vpad100));
		
		controls.add(Box.createRigidArea(NolMainFrame.vpad20));
		controls.add(controls1);
		controls.add(Box.createRigidArea(NolMainFrame.vpad150));


		JPanel chartPane = new JPanel(new GridLayout());
		chartPane.setBorder(new EmptyBorder(20,20,20,20));
		chartPane.add(chart);

 		getContentPane().setLayout(new BorderLayout());
		getContentPane().add("Center", chartPane);
		getContentPane().add("East", controls);
	}

	private void setTitle() {
		String title = "2D Score Plot - "+ model.getName();
		setTitle(title);
		Point p = this.getLocation();
		this.setLocation(p.x+1,p.y);
		this.setLocation(p.x,p.y);
	}
	

	public DefaultListModel getVarListModel() {
		if (varListModel == null) {
			varListModel = new DefaultListModel();
		}
		return varListModel;
	}

	public DefaultListModel getDataListModel() {
		if (dataListModel == null) {
			dataListModel = new DefaultListModel();
		}
		return dataListModel;
	}

	public ScatterChart getChart() {
		return chart;
	}

	private void initializeData() throws MathException {

		Project2 project = frame.getProject();
		Matrix score = model.getScore();
		Matrix T =  Matlib.createMatrix();
		Matlib.getColumns(score, 0, 1, T);
		// Put the scores in double arrays for plotting
		Matlib.transpose(T, T);
		double[][] xy = Matlib.create2DArray(T);
		Matlib.clear(T);
 		double[] x = xy[0];
		double[] y = xy[1];
		int nData = x.length;
		// Build the plot
		int nLabels = project.getNumberOfLabels();
		boolean isOriginal = false;
		if(dataSource instanceof RawDataSource) {
			isOriginal = true;
		}
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
		chart.addDataSeries("Base", x, y, markerFormats, markers); 
	}

	public void refreshVariableName(Variable var) {
		boolean found = false;
		if(varsShown.contains(var)) {
			int index = varsShown.indexOf(var);
			varsFullyQualifiedNameShown.removeElementAt(varsShown.indexOf(var));
			String name = var.getDataSource().getName() + "." + var.getDataSeries().getName() + "." + var.getName();
			varsFullyQualifiedNameShown.insertElementAt(name, index);
			initialControlDisplay();
			setTitle();
		}
	}

	public void refreshDataSeriesName(DataSeries ds) {
		boolean found = false;
		Variable theVar = null;
		for(int i = 0; i < varsShown.size(); i++) {
			Variable var = (Variable) varsShown.elementAt(i);
			if(var.getDataSeries().getName().equals(ds.getName())) { 
				theVar = var;
				found = true; 
				break; 
			}
		}

		if(found) {
			int index = varsShown.indexOf(theVar);
			varsFullyQualifiedNameShown.removeElementAt(varsShown.indexOf(theVar));
			String name = theVar.getDataSource().getName() + "." + theVar.getDataSeries().getName() + "." + theVar.getName();
			varsFullyQualifiedNameShown.insertElementAt(name, index);
			setTitle();
		}

	}

	private void initialControlDisplay(){
		xaxis.removeActionListener(this);
		yaxis.removeActionListener(this);
		Matrix score = model.getScore();
		int nPC = score.getCols();
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
	}

	private void displayNewXYData(){
		int xindex = xaxis.getSelectedIndex();
		int yindex = yaxis.getSelectedIndex();
		if(xindex<0 || yindex < 0) {
			return;
		}
		Matrix score = model.getScore();
		Project2 project = frame.getProject();
		DataSeries dataSeries = model.getDataSeries();
		DataSource dataSource = dataSeries.getDataSource();
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
		int nLabels = project.getNumberOfLabels();
		Vector labels = new Vector();
//get the label of shown variables.
/*		for(int i = 0; i < varsShown.size(); i++) {
			Variable var = (Variable)varsShown.elementAt(i);
			if(dataSource instanceof RawDataSource) {
				labels.addElement(((RawDataSource)dataSource).getLabelMatrix(var));
			}
		}
*/		
		byte[] markers = new byte[nData];
		labelsToMarkers(labels, markers); 
		chart.setDataSeries("Base", x, y, markers); 

/*		int nds = insertedDataSeries.size();
		for(int i=0;i<nds;i++){
			DataSeries ds = (DataSeries)insertedDataSeries.elementAt(i);
			Matrix scoreTemp = (Matrix)insertedScores.elementAt(i);
			double[] xx = null, yy = null;
			try {
				Matlib.getColumn(scoreTemp,xindex,T);
				Matlib.transpose(T,T);
				xx = Matlib.create1DArray(T);
				Matlib.getColumn(scoreTemp,yindex,T);
				Matlib.transpose(T,T);
				yy = Matlib.create1DArray(T);
			} catch(MathException e) {
				System.err.println("Non-Fatal exception: " + e.getMessage());
				e.printStackTrace();
			}
			byte[] dmarkers = new byte[xx.length];
			chart.setDataSeries(ds.getName(), xx, yy, dmarkers); 		
		}
*/		Matlib.clear(T);
	}

	private void labelsToMarkers(Vector labels, byte[] markers){
		//System.out.println("matrix = "+labelMatrix.length+", nLabels = "+labelOrder.length+", nData = "+markers.length+" matrix rows = "+labelMatrix[0].length);
		Project2 project = frame.getProject();
		int nData = markers.length;
		int[] labelOrder = project.getLabelOrder();
		int nLabels = labelOrder.length;
		int nVars = labels.size();
		for (int j=0; j < nData; j++){
			markers[j] = 0;
		}
		if(nVars == 0 || nLabels == 0){
			return;
		}
		int cc = 0;
		for (int r=0; r < nData; r++) {
			for (int i = 0; i < nLabels; i++) {
				if(markers[r]>0){
					break;
				}
				cc = 0;
 				for(int c = 0; c < nVars; c++){
					boolean[][] labelMatrix	= (boolean[][])labels.elementAt(c);
					//System.out.println("j = "+j+", i = "+i+", order = "+labelOrder[i]);
					if(labelMatrix[labelOrder[i]][r]) {
						cc++;
					}
				}
				if(cc == nVars && cc != 0) {
					markers[r] = (byte) (labelOrder[i] + 1);
				}
			}
		}		
	}


	private boolean hasSameVariables(DataSeries ds){
		int vs = varsFullyQualifiedNameShown.size();
		for(int i=0;i<vs;i++){
			String vname = (String)varsFullyQualifiedNameShown.elementAt(i);
			Variable var = ds.getVarByName(vname);
			if(var == null){
				return false;
			}
		}
		return true;
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
			}
			else zoomOutButton.setEnabled(false);
		} else if ("Y Axis".equals(command)){
			zoomFlag = 2;
			if(zoomInCounterY>0){
				zoomOutButton.setEnabled(true);
			}else {
				zoomOutButton.setEnabled(false);
			}
		} else if(source.equals(xaxis) || source.equals(yaxis)){
			displayNewXYData();
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
			chart.zoomIn();
		} else if(zoomFlag == 1) {
			zoomInCounterX++;
			chart.zoomInX();
		} else if(zoomFlag == 2) {
			zoomInCounterY++;
			chart.zoomInY();
		}
	}

	public void zoomOut() {
		//System.out.println("***STARTING ZOOM OUT ACTION***");
		if(zoomFlag == 0) {
			zoomInCounterX--;
			zoomInCounterY--;
			if(zoomInCounterX <= 0 || zoomInCounterY <= 0) {
				zoomOutButton.setEnabled(false);
			}
			chart.zoomOut();
		} else if(zoomFlag == 1) {
			zoomInCounterX--;
			if(zoomInCounterX <= 0) {
				zoomOutButton.setEnabled(false);
			}
			chart.zoomOutX();
		} else if(zoomFlag == 2) {
			zoomInCounterY--;
			if(zoomInCounterY <= 0) {
				zoomOutButton.setEnabled(false);
			}
			chart.zoomOutY();
		}
		if(zoomInCounterX<0) {
			zoomInCounterX = 0;
		}
		if(zoomInCounterY<0) {
			zoomInCounterY = 0;
		}
	}

	//  CHART EVENT LISTENERS
	
	@Override
	public void chartPointSelected(ChartEvent e) {
/*		if(DEBUG) System.out.println("chartPointSelected: Chart frame received ChartEvent");
		if(!(dataSource instanceof RawDataSource)) return;
		boolean labelSelectStatus = ((RawDataSource)dataSource).getSelectStatus();
		int[] order =  project.getLabelOrder();
		if(order.length == 0) { 
			return;	
		}
		int labelNumber = order[0];
		Component c = e.getSubcomponentSource();
		if (!(c instanceof ScatterPlot)) return;
		// select or unselect point on plot
		ScatterPlot plot = (ScatterPlot) c;
		// find the point
		int[] point = plot.findPoint(e.getX(), e.getY());
		if (point == null) { if(DEBUG) System.out.println("chartPointSelected: found no point"); return; }
		else {
			if(DEBUG) System.out.println("chartPointSelected: found " + point[1]);
		}
		
		if(DEBUG) System.out.println("chartPointSelected: about to label point");
		((RawDataSource)dataSource).labelPoints(labelNumber, varsShown, point[1], point[1], labelSelectStatus);
*/	}

	@Override
	public void chartAreaSelected(ChartEvent e) {
/*		if(DEBUG) System.out.println("chartAreaSelected: Chart frame received ChartEvent");
		//chart.hideSelectionBox();
		if(!(dataSource instanceof RawDataSource)) return;
		boolean labelSelectStatus = ((RawDataSource)dataSource).getSelectStatus();
		int[] order =  project.getLabelOrder();
		if(order.length == 0) return;
		int labelNumber = order[0];

		Rectangle rb = e.getSelectionRectangle(); // rubber band rectangle
		int[][] rowArrays = chart.findSelectedRows(rb);

		if(rowArrays[0].length == 0) { 
			if(DEBUG) System.out.println("chartAreaSelected: found no points"); 
			return; 
		}
		else if(DEBUG) {
			for(int i = 0; i < rowArrays[0].length; i++) 
				System.out.println("chartAreaSelected: found " + rowArrays[0][i]);
		}

		//int[] varNumbers = new int[varsShown.size()];
		Hashtable hashy = new Hashtable(varsShown.size());
	//	for(int i = 0; i < dataSeries.getColumn(); i++) {
		for(int i = 0; i < varsShown.size(); i++) {
		//	Variable var = (Variable) dataSeries.getVarByIndex(i);
			Variable var = (Variable) varsShown.elementAt(i);
			hashy.put(var, rowArrays[0]);
		}	
		if(DEBUG) System.out.println("chartPointSelected: about to label point");
		((RawDataSource)dataSource).labelPoints(labelNumber, hashy, labelSelectStatus);
*/	}

	@Override
	public void chartPopupTriggered(ChartEvent e){}


	// RAW DATA EVENT LISTENERS

	@Override
	public void DataSeriesAdded(RawDataEvent e){}
	@Override
	public void DataSeriesRemoved(RawDataEvent e){}

	@Override
	public void LabelCategoryAdded(RawDataEvent evt) {
		if(DEBUG) {
			System.out.println("LabelCategoryAdded: RawDataEvent");
		}
		updatePlotsForLabels((RawDataSource)evt.getRawDataSource());
	} 
	
	@Override
	public void LabelCategoryRemoved(RawDataEvent evt) {
		if(DEBUG) {
			System.out.println("LabelCategoryRemoved: RawDataEvent");
		}
		updatePlotsForLabels((RawDataSource)evt.getRawDataSource());
	}

	@Override
	public void LabelColorChanged(RawDataEvent evt) {
		if(DEBUG) {
			System.out.println("LabelColorChanged: RawDataEvent");
		}
		updatePlotsForLabels((RawDataSource)evt.getRawDataSource());
	}

	@Override
	public void LabelNameChanged(RawDataEvent evt) {}

	/**
	  *
	  * DataPointsLabeled (RawDataEvent e)
	  * modified by bbush, 10-7-98
	  **/
	@Override
	public void DataPointsLabeled(RawDataEvent evt) {
		if(DEBUG) {
			System.out.println("DataPointsLabeled: Labeling event");
		}
		Vector vars = evt.getVarObjects();
		RawDataSource datsr = (RawDataSource)evt.getRawDataSource();
		byte[] markers = chart.getMarkerArray("Base");
		int cVar = varsShown.size();
		Vector labels = new Vector(cVar);
		for(int i = 0; i < cVar; i++) {
			Variable var = (Variable) varsShown.elementAt(i);
			labels.addElement(datsr.getLabelMatrix(var));
		}
		labelsToMarkers(labels, markers); 
		chart.setMarkerArray("Base",markers);
		chart.invalidateAll();  // invalidate the entire region
		repaint();
	}


	@Override
	public void LabelOrderChanged(RawDataEvent evt) {
		updatePlotsForLabels((RawDataSource)evt.getRawDataSource());
	}

	@Override
	public void FormulaListChanged(PreprocessorEvent evt) {} 

	@Override
	public void DataChanged(PreprocessorEvent evt) {
		try {
			refreshData();
		} catch (MathException e) {
			System.err.println("Non-Fatal exception: " + e.getMessage());
			e.printStackTrace();
		}
	}

	private void updatePlotsForLabels(RawDataSource rawDataSource){
		if(DEBUG) {
			System.out.println("updatePlotsForLabels: Projection chart frame received RawDataSource event");
		}
		Project2 project = frame.getProject();
		DataSeries dataSeries = model.getDataSeries();
		DataSource dataSource = dataSeries.getDataSource();

		int nLabels = project.getNumberOfLabels();
		Color plotColor = Color.green;
		int plotSymbol = 1;
		Vector theLabels = project.getLabels();
		int baseSize = 6;  // what if chart has been zoomed?
		int highlightSize = 10;
		Color highlightColor = null;
		MarkerFormat[] markerFormats;
		MarkerFormat unhighlightedMarker = new MarkerFormat
			(plotSymbol, plotColor, highlightColor, baseSize, highlightSize);
		if(nLabels > 0){  // if we have some labels
			markerFormats = new MarkerFormat[nLabels + 1];
			markerFormats[0] = unhighlightedMarker;

			for (int i=0; i<nLabels; i++) {
				NolLabel label = (NolLabel)theLabels.elementAt(i);
				highlightColor = label.getLabelColor();
				markerFormats[i+1] = new MarkerFormat
					(plotSymbol, plotColor, highlightColor, baseSize, highlightSize);  
			}

			Variable[] Vars = new Variable[varsShown.size()];
			int nVar = dataSeries.getColumn();
			int nData = dataSeries.getRow();
			int c = 0;
			for(int i=0; i < nVar; i++) {
				Variable var = dataSeries.getVarByIndex(i);
				if(varsShown.contains(var)){
					Vars[c] = var;
					c++;
				}
			}
			Vector labels = new Vector(Vars.length);
			for(int i = 0; i < Vars.length; i++) {
				labels.addElement(((RawDataSource)dataSource).getLabelMatrix(Vars[i]));
			}
			byte[] markers = new byte[nData];
			labelsToMarkers(labels, markers); 
			chart.setMarkerArray("Base", markers);
		} else {
			markerFormats = new MarkerFormat[1];
			markerFormats[0] = unhighlightedMarker;
		}
		chart.setMarkerFormat("Base", markerFormats);
		chart.repaint();	
		chart.validate();
	}

	private void refreshData() throws MathException {
/*		Matrix X0 = dataSeries.getDataMatrix();   // do not clear or operate on X0
		// temporary matrices
		Matrix T = Matlib.createMatrix();
		Matrix goodRows = Matlib.createMatrix();
		Matrix badCols = Matlib.createMatrix();  
		Matrix S = Matlib.ones(1,X0.getCols());
		Matrix Xtemp = Matlib.createMatrix();
		Matrix X = Matlib.createMatrix();
		int ncols = X0.getCols();
		//System.out.println("Showing "+varsShown.size()+" variables");
		for(int i=0; i<ncols; i++){
			Variable var = dataSeries.getVarByIndex(i);
			if(!varsShown.contains(var) || varsContainingNaNs.contains(var)) S.set(0,i,0.0);  // eliminate this variable
		}
		Matlib.sum(S,Xtemp);   
		if(Xtemp.get(0) > 0.0) Matlib.getColumns(X0, S, X);
		else Matlib.copy(X0,X);
		Matlib.findFiniteRows(X, goodRows);
		Matlib.sum(goodRows,S);
		if(Math.rint(S.get(0,0))<goodRows.getElements()) Matlib.getRows(X, goodRows, X);
		Matlib.mean(X, Xmean);
		Matlib.stdnonzero(X, Xstd);
		Matlib.normalize(X, Xmean, Xstd, X);
		//System.out.println("X is "+X.getRows()+" by "+X.getCols());
		if((X.getCols() == 0) || (X.getRows() == 0)) {
			state = 1;
			frame.showOKDialog("No valid data to plot");
			Matlib.clear(X);
			Matlib.clear(goodRows);
			Matlib.clear(badCols);
			Matlib.clear(Xtemp);
			Matlib.clear(S);
			return;
		}
		state = 0;

//System.out.println("maxNFactor= "+maxNFactor);
		Stats.pca(X, P, Variants); 
		Matlib.getColumns(P,0,maxNFactor-1,P);

//		Stats.pca(X,Math.min(X.getCols(),maxNFactor),P);
		Matlib.multiply(X, P, S);
		int row = goodRows.getRows();
		int col = S.getCols();
		score.redimension(row,col);
		int rr=0;
		for(int r = 0; r < row; r++) {
			if(goodRows.get(r,0) == 1.0){
				for(int c=0;c<col;c++){
					score.set(r,c,S.get(rr,c));
				}
				rr++;
			}else{
				for(int c=0;c<col;c++){
					score.set(r,c,Double.NaN);
				}
			}
		}
		Matlib.getColumns(score, 0, 1, T);
		Matlib.transpose(T,T);
		double[][] xy = Matlib.create2DArray(T);
		double[] x = xy[0];
		double[] y = xy[1];
		int nData = x.length;
		byte[] markers = new byte[nData];
		if(dataSource instanceof RawDataSource) {
			Vector labels = new Vector(varsShown.size());
			for(int i = 0; i < varsShown.size(); i++){
				labels.addElement(((RawDataSource)dataSource).getLabelMatrix((Variable) varsShown.elementAt(i)));
			}
			labelsToMarkers(labels, markers); 
		}
		chart.setDataSeries("Base", x, y, markers); 		
		Matlib.clear(S);
		Matlib.clear(Xtemp);
		Matlib.clear(T);
		Matlib.clear(X);
		Matlib.clear(badCols);
		Matlib.clear(goodRows);
		if((ncols - varsContainingNaNs.size()) > varsShown.size()) addButton.setEnabled(true);
		else addButton.setEnabled(false);
		if(varsShown.size() > 2) removeButton.setEnabled(true);
		else removeButton.setEnabled(false);
		goThroughInsertedDataSeries();
*/	}

	private void goThroughInsertedDataSeries()throws MathException {
/*		int nds = insertedDataSeries.size();
		if(nds == 0){
			removeDataButton.setEnabled(false);
			return;
		}
		Matrix T = Matlib.createMatrix();
		Matrix Xtemp = Matlib.createMatrix();
		Matrix X = Matlib.createMatrix();
		Matrix S = Matlib.createMatrix();

		for(int d=0;d<nds;d++){
			DataSeries ds = (DataSeries)insertedDataSeries.elementAt(d);
			Matrix X0 = ds.getDataMatrix();   // do not clear or operate on X0
			int ncols = X0.getCols();
			S.redimension(1,ncols);
			for(int i=0; i<ncols; i++){
				Variable var = ds.getVarByIndex(i);
				Variable var0 = dataSeries.getVarByName(var.getName());
				S.set(0,i,1.0);
				if(var0 != null){
					if(!varsShown.contains(var0) || varsContainingNaNs.contains(var0)) S.set(0,i,0.0);
				}else{
					S.set(0,i,0.0);
				}
			}
			Matlib.sum(S,Xtemp);   
			if(Xtemp.get(0) > 0.0) Matlib.getColumns(X0, S, X);
			else Matlib.copy(X0,X);
			if(X.getCols() != Xmean.getCols()){
				frame.showOKDialog("The column numbers don't match");
				break;
			}
			Matlib.normalize(X, Xmean, Xstd, X);
			state = 0;
			Matrix scoreTemp = (Matrix)insertedScores.elementAt(d);
			Matlib.multiply(X,P,scoreTemp);
			Matlib.getColumns(scoreTemp, 0, 1, T);
			Matlib.transpose(T,T);
			double[][] xy = Matlib.create2DArray(T);
			double[] x = xy[0];
			double[] y = xy[1];
			int nData = x.length;
			byte[] markers = new byte[nData];
			chart.setDataSeries(ds.getName(), x, y, markers); 		
		}
		Matlib.clear(T);
		Matlib.clear(Xtemp);
		Matlib.clear(S);
		Matlib.clear(X);
		removeDataButton.setEnabled(true);
*/	}
/*	private void addDataSeries(DataSeries ds)throws MathException {
		int xindex = xaxis.getSelectedIndex();
		int yindex = yaxis.getSelectedIndex();
		if(xindex<0 || yindex < 0) return;

		if(insertedDataSeries.contains(ds)){
			return;
		}
		Matrix X0 = ds.getDataMatrix();   // do not clear or operate on X0
		Matrix T = Matlib.createMatrix();
		Matrix badCols = Matlib.createMatrix();  
		Matrix S = Matlib.ones(1,X0.getCols());
		Matrix Xtemp = Matlib.createMatrix();
		Matrix X = Matlib.createMatrix();
		int ncols = X0.getCols();
		for(int i=0; i<ncols; i++){
			Variable var = ds.getVarByIndex(i);
			Variable var0 = dataSeries.getVarByName(var.getName());
			if(var0 != null){
				if(!varsShown.contains(var0) || varsContainingNaNs.contains(var0)) S.set(0,i,0.0);
			}else{
				S.set(0,i,0.0);
			}
		}
		Matlib.sum(S,Xtemp);   
		if(Xtemp.get(0) > 0.0) Matlib.getColumns(X0, S, X);
		else Matlib.copy(X0,X);
		if(X.getCols() != Xmean.getCols()){
			frame.showOKDialog("The column numbers don't match");
			Matlib.clear(Xtemp);
			Matlib.clear(X);
			Matlib.clear(badCols);
			Matlib.clear(S);
			Matlib.clear(T);
			return;
		}
		Matlib.normalize(X, Xmean, Xstd, X);
		state = 0;
		Matrix scoreTemp = Matlib.createMatrix();
		Matlib.multiply(X,P,scoreTemp);

		Matlib.getColumn(scoreTemp,xindex,T);
		Matlib.transpose(T,T);
		double[] x = Matlib.create1DArray(T);
		Matlib.getColumn(scoreTemp,yindex,T);
		Matlib.transpose(T,T);
		double[] y = Matlib.create1DArray(T);
		int nData = x.length;
		byte[] markers = new byte[nData];
		Color plotColor = ColorMap.colors[ColorMap.defaultPlotColors[insertedIndex]];
		int plotSymbol = 1;
		LineFormat connectorFormat = new LineFormat(plotColor, 1);

		int baseSize = 2;  // what if chart has been zoomed?
		int highlightSize = 10;
		Color highlightColor = null;
		MarkerFormat unhighlightedMarker = new MarkerFormat
			(plotSymbol, plotColor, highlightColor, baseSize, highlightSize);
		MarkerFormat[] markerFormats;
		markerFormats = new MarkerFormat[1];
		markerFormats[0] = unhighlightedMarker;

		chart.addDataSeries(ds.getName(), x, y,markerFormats, markers); 		
		insertedDataSeries.addElement(ds);
		insertedScores.addElement(scoreTemp);

		insertedColorIndeces.addElement(new Integer(insertedIndex));
		insertedColorBlocks.addElement(new ColoredSquare(plotColor));
		getDataListModel().addElement(ds.getDataSource().getName()+"."+ds.getName());
		removeDataButton.setEnabled(true);
		insertedIndex++;
		Matlib.clear(Xtemp);
		Matlib.clear(X);
		Matlib.clear(badCols);
		Matlib.clear(S);
		Matlib.clear(T);
	}
  */
    class ListCellRenderer extends DefaultListCellRenderer{ //changed for 1.2.2 gchen 1.31.00
		ListCellRenderer() {
			super();
		}
		@Override
		public Component getListCellRendererComponent(
				JList list, 
				Object value, 
				int modelIndex, 
				boolean isSelected, 
				boolean cellHasFocus) 
			{
			String dsName = (String)value;
			int index = getDataListModel().indexOf(dsName);
			int blockIndex = ((Integer)insertedColorIndeces.elementAt(index)).intValue();
			setIcon((ColoredSquare)insertedColorBlocks.elementAt(blockIndex));
			return super.getListCellRendererComponent(list, dsName, index, isSelected, cellHasFocus);
		}
    }
}
