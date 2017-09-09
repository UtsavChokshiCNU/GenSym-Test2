package com.gensym.nols.chart.scatter;
import java.awt.*;
import java.awt.event.*;
import java.util.*;
import javax.swing.*;
import javax.swing.border.*;

import com.gensym.nols.chart.line.*;
import com.gensym.math.matrix.*;

import com.gensym.nols.wksp.*;
import com.gensym.nols.data.*;
import com.gensym.nols.dlg.*;
import com.gensym.nols.main.*;

 /**
 * NolXYChartFrame
 * @version     1.0 September 2, 1998
 * @author      Brian O. Bush
 **/

public class NolXYChartFrame extends NolInternalFrame implements ActionListener, ChartListener, 
RawDataSourceListener, PreprocessorListener // , SimulationListener
{
	private NolMainFrame frame;
	private ScatterChart chart;
	private boolean zooming;
	private int zoomFlag;
	private Vector varsShown;
	private Vector varsCommonNameShown;

	private Variable varX;
	private Variable varY;
	private DataSeries dataSeriesX;
	private DataSource dataSourceX;
	private DataSeries dataSeriesY;
	private DataSource dataSourceY;
	private Project project;
	private JButton zoomOutButton;
	private int zoomInCounterX;
	private int zoomInCounterY;

//	protected JPopupMenu popUp;
	private ControlAction actionListener;

	private NolSingleChoiceDialog choiceDialog;
		
	private static final boolean DEBUG = false;
		
	private static final String ZOOM = "XYChartFrame_Zoom";
	private static final String XAXIS = "XYChartFrame_XAxis";
	private static final String YAXIS = "XYChartFrame_YAxis";
	private static final String XANDY = "XYChartFrame_XAndY";
	private static final String ZOOMIN = "XYChartFrame_ZoomIn";
	private static final String ZOOMOUT = "XYChartFrame_ZoomOut";

	public NolXYChartFrame (NolMainFrame frame, Variable varObjX, Variable varObjY) {
		super();
		this.frame = frame;
		this.varX = varObjX;
		this.dataSeriesX = varObjX.getDataSeries();
		this.dataSourceX = varObjX.getDataSource();
		this.varY = varObjY;
		this.dataSeriesY = varObjY.getDataSeries();
		this.dataSourceY = varObjY.getDataSource();
		
		this.project = dataSourceY.getProject();
		
		varsShown = new Vector(0, 10);
		varsShown.addElement(varX);
		varsShown.addElement(varY);

		// listeners for data source X

		if(dataSourceX instanceof RawDataSource) {
			if(DEBUG) {
				System.out.println("added Raw data source X listener...");
			}
			((RawDataSource)dataSourceX).removeListener(this);
			((RawDataSource)dataSourceX).addListener(this);
		}
		else if(dataSourceX instanceof Preprocessor) {
			if(DEBUG) {
				System.out.println("added Preprocessor X listener...");
			}
			((Preprocessor)dataSourceX).removeListener(this);
			((Preprocessor)dataSourceX).addListener(this);
		}
		else if(dataSourceX instanceof NolSimulation) {
			if(DEBUG) {
				System.out.println("added Simulation X listener...");
			}
			((NolSimulation)dataSourceX).removeListener(this);
			((NolSimulation)dataSourceX).addListener(this);
			}

		// listeners for data source Y
		
		if(dataSourceY instanceof RawDataSource) {
			if(DEBUG) {
				System.out.println("added Raw data source Y listener...");
			}
			((RawDataSource)dataSourceY).removeListener(this);
			((RawDataSource)dataSourceY).addListener(this);
		}
		else if(dataSourceY instanceof Preprocessor) {
			if(DEBUG) {
				System.out.println("added Preprocessor Y listener...");
			}
			((Preprocessor)dataSourceY).removeListener(this);
			((Preprocessor)dataSourceY).addListener(this);
		}
		else if(dataSourceY instanceof NolSimulation) {
			if(DEBUG) {
				System.out.println("added Simulation Y listener...");
			}
			((NolSimulation)dataSourceY).removeListener(this);
			((NolSimulation)dataSourceY).addListener(this);
		}

		zoomFlag = 0;
		chart = new ScatterChart(getBackground());
		chart.holdOn();
		chart.addChartListener(this);
		chart.setAxisColor(Color.black);

		// popup menu
/*		actionListener =  new ControlAction();	
		popUp = new JPopupMenu();
		JMenuItem popUpItem = new JMenuItem("Zoom In");
		popUpItem.setActionCommand("Zoom In");
		popUpItem.addActionListener(actionListener);
		popUp.add(popUpItem);
		popUpItem = new JMenuItem("Zoom Out");
		popUpItem.setActionCommand("Zoom Out");
		popUpItem.addActionListener(actionListener);
		popUp.add(popUpItem);
		popUpItem = new JMenuItem("Label Color...");
		popUpItem.setActionCommand("Label Color...");
		popUpItem.addActionListener(actionListener);
		popUp.add(popUpItem); */

		initializeData();
		setTitle();
		initialLayout();
		chart.setFortyFiveDegreeLine(false);
		chart.holdOff();
	}

	/** remove all the listeners before chart is shutdown, added by Brian O. Bush, Feb 17, 1999 **/
	public void removeListeners() {
		if(dataSourceX instanceof RawDataSource) 
			((RawDataSource)dataSourceX).removeListener(this);
		else if(dataSource instanceof Preprocessor) 
			((Preprocessor)dataSourceX).removeListener(this);
		else if(dataSource instanceof NolSimulation) 
			((NolSimulation)dataSourceX).removeListener(this);

		if(dataSourceY instanceof RawDataSource) 
			((RawDataSource)dataSourceY).removeListener(this);
		else if(dataSource instanceof Preprocessor) 
			((Preprocessor)dataSourceY).removeListener(this);
		else if(dataSource instanceof NolSimulation) 
			((NolSimulation)dataSourceY).removeListener(this);

		chart.removeChartListener(this);
	}

	private void setTitle(){
		String title = "X-Y Chart - " + dataSourceX.getName() + "." + dataSeriesX.getName() + "." + varX.getName() +  "  vs.  " +
			dataSourceY.getName() + "." + dataSeriesY.getName() + "." + varY.getName();
		setTitle(title);
		Point p = this.getLocation();
		this.setLocation(p.x+1,p.y);
		this.setLocation(p.x,p.y);
	}
	
	public Vector getVariables() {
		return varsShown;
	}

	private void initializeData() {
		Matrix X = dataSeriesX.getDataMatrix();
		Matrix Y = dataSeriesY.getDataMatrix();
		
		int rows = X.getRows();
		double[] x = new double[rows];
		double[] y = new double[rows];
		for(int r = 0; r < rows; r++){
			x[r] = X.get(r, varX.getColumnIndex());
			y[r] = Y.get(r, varY.getColumnIndex());
		}
		int nData = x.length;
		int nLabels = project.getNumberOfLabels();
		boolean isOriginal = false;
		if(dataSourceX instanceof RawDataSource || dataSourceY instanceof RawDataSource) {
			isOriginal = true;
		}
		Color plotColor = Color.green;
		int plotSymbol = 1;
		LineFormat connectorFormat = new LineFormat(plotColor, 1);
		byte[] markers = new byte[nData];
		int baseSize = 6;  // what if chart has been zoomed?
		int highlightSize = 10;
		Color highlightColor = null;
		MarkerFormat unhighlightedMarker = new MarkerFormat
			(plotSymbol, plotColor, highlightColor, baseSize, highlightSize);
		MarkerFormat[] markerFormats;
		if (isOriginal && nLabels > 0) {
			markerFormats = new MarkerFormat[nLabels + 1];
			Vector labels = project.getLabels();
			markerFormats = new MarkerFormat[nLabels + 1];
			markerFormats[0] = unhighlightedMarker;
			for (int i=0; i<nLabels; i++) {
				NolLabel label = (NolLabel)labels.elementAt(i);
				highlightColor = label.getLabelColor();
				markerFormats[i+1] = new MarkerFormat
					(plotSymbol, plotColor, highlightColor, baseSize, highlightSize);  
			}

			Vector labMat = new Vector();
			if(dataSourceX instanceof RawDataSource){
				labMat.addElement(((RawDataSource)dataSourceX).getLabelMatrix(varX));
			}
				
			if(dataSourceY instanceof RawDataSource){
				labMat.addElement(((RawDataSource)dataSourceY).getLabelMatrix(varY));
			}
			labelsToMarkers(labMat, markers); 
		} else {
			markerFormats = new MarkerFormat[1];
			markerFormats[0] = unhighlightedMarker;
		}
		chart.addDataSeries("1p/2p", x, y, markerFormats, markers);
		chart.repaint();	
		chart.validate();
	}

	public void refreshDataSeriesName(DataSeries ds) {
		boolean found = false;
		for(int i = 0; i < varsShown.size(); i++) {
			Variable var = (Variable) varsShown.elementAt(i);
			if(var.getDataSeries().getName().equals(ds.getName())) { 
				found = true; 
				break; 
			}
		}
		if(found) {
			setTitle();
		}
	}

	public void refreshVariableName(Variable var) {
		if(varsShown.contains(var)) {
			setTitle();
		}
	}

	public ScatterChart getChart(){
		return chart;
	}

	private void initialLayout() {
		JPanel controls = new JPanel();
		controls.setLayout(new BoxLayout(controls, BoxLayout.Y_AXIS));
		controls.add(Box.createRigidArea(NolMainFrame.vpad20));
		JPanel zoomPane = new JPanel(new GridLayout(5,1,10,10));
		zoomPane.setBorder(BorderFactory.createTitledBorder(frame.getNolResourceString(ZOOM)+":"));		
		ButtonGroup group = new ButtonGroup();
		JRadioButton radio = new JRadioButton(frame.getNolResourceString(XAXIS));
		radio.setActionCommand("X Axis");
		radio.addActionListener(this);
		group.add(radio);
		zoomPane.add(radio);
		radio = new JRadioButton(frame.getNolResourceString(YAXIS));
		radio.setActionCommand("Y Axis");
		radio.addActionListener(this);
		group.add(radio);
		zoomPane.add(radio);
		radio = new JRadioButton(frame.getNolResourceString(XANDY), true);
		radio.setActionCommand("X and Y");
		radio.addActionListener(this);
		group.add(radio);
		zoomPane.add(radio);
		JButton zoom = new JButton(frame.getNolResourceString(ZOOMIN));
		zoom.setActionCommand("Zoom In");
		zoomInCounterX = 0;
		zoomInCounterY = 0;
		zoom.addActionListener(this);
		zoomPane.add(zoom);
		zoomOutButton = new JButton(frame.getNolResourceString(ZOOMOUT));
		zoomOutButton.setActionCommand("Zoom Out");
		zoomOutButton.addActionListener(this);
		zoomOutButton.setEnabled(false);
		zoomPane.add(zoomOutButton);

		controls.add(Box.createRigidArea(NolMainFrame.vpad20));
		controls.add(zoomPane);
		controls.add(Box.createRigidArea(NolMainFrame.vpad300));		

		JPanel chartPane = new JPanel(new GridLayout());
		chartPane.setBorder(new EmptyBorder(20,20,20,20));
		chartPane.add(chart);

 		getContentPane().setLayout(new BorderLayout());
		getContentPane().add("Center", chartPane);
		getContentPane().add("East", controls);
	}

	private void labelsToMarkers(Vector labels, byte[] markers){
		//System.out.println("matrix = "+labelMatrix.length+", nLabels = "+labelOrder.length+", nData = "+markers.length+" matrix rows = "+labelMatrix[0].length);
		int nData = markers.length;
		int[] labelOrder = project.getLabelOrder();
		int nLabels = labelOrder.length;
		int nVars = labels.size();
		for (int j=0; j < nData; j++) {
			markers[j] = 0;
		}
		int cc = 0;
		for (int r=0; r < nData; r++) {
			for (int i = 0; i < nLabels; i++) {
				if(markers[r]>0) {
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
				if(cc == nVars){
					markers[r] = (byte) (labelOrder[i] + 1);
				}
			}
		}		
	}
	
	@Override
	public void actionPerformed(ActionEvent e) {
		//System.out.println("action ="+e.getActionCommand());
		String command = e.getActionCommand();
		if ("Zoom In".equals(command)){
			zoomIn();
		}else if ("Zoom Out".equals(command)) {
			zoomOut();
		}else if ("X and Y".equals(command)) {
			zoomFlag = 0;
			if(zoomInCounterX>0 && zoomInCounterY>0){
				zoomOutButton.setEnabled(true);
			}else {
				zoomOutButton.setEnabled(false);
			}
		}else if ("X Axis".equals(command)) {
			zoomFlag = 1;
			if(zoomInCounterX>0){
				zoomOutButton.setEnabled(true);
			}else {
				zoomOutButton.setEnabled(false);
			}
		}else if ("Y Axis".equals(command)) {
			zoomFlag = 2;
			if(zoomInCounterY>0) {
				zoomOutButton.setEnabled(true);
			}else {
				zoomOutButton.setEnabled(false);
			}
		}
	}

	public void zoomIn() {
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
		if(zoomFlag == 0) {
			zoomInCounterX--;
			zoomInCounterY--;
			if(zoomInCounterX <= 0 || zoomInCounterY <= 0) 
				zoomOutButton.setEnabled(false);
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
	}

	//  CHART EVENT LISTENERS

	@Override
	public void chartPointSelected(ChartEvent e) {
		//if(DEBUG) System.out.println("chartPointSelected: Chart frame received ChartEvent");
		if(!(dataSourceX instanceof RawDataSource && dataSourceY instanceof RawDataSource)) {
			return;  // can't label anything but raw data!
		}
		boolean labelSelectStatus = ((RawDataSource)dataSourceX).getSelectStatus();
		int[] order =  project.getLabelOrder();
		if(order.length == 0){
			return;	
		}
		int labelNumber = order[0];
		Component c = e.getSubcomponentSource();
		if (!(c instanceof ScatterPlot)) {
			return;
		}
		// select or unselect point on plot
		ScatterPlot plot = (ScatterPlot) c;
		// find the point
		int[] point = plot.findPoint(e.getX(), e.getY());
		if (point == null){
			return;
		}
		Vector vars = new Vector();
		vars.addElement(varX);
		vars.addElement(varY);
		((RawDataSource)dataSourceX).labelPoints(labelNumber, vars, point[1], point[1], labelSelectStatus);
	}

	@Override
	public void chartAreaSelected(ChartEvent e) {
		if(DEBUG) {
			System.out.println("chartAreaSelected: Chart frame received ChartEvent");
		}
		chart.hideSelectionBox();  // is this necessary???
		if(!(dataSourceX instanceof RawDataSource && dataSourceY instanceof RawDataSource)) {
			return;  // can't label anything but raw data!
		}
		boolean labelSelectStatus = ((RawDataSource)dataSourceX).getSelectStatus();
		int[] order =  project.getLabelOrder();
		if(order.length == 0) {
			return;
		}
		int labelNumber = order[0];
		Rectangle rb = e.getSelectionRectangle(); // rubber band rectangle
		int[][] rowArrays = chart.findSelectedRows(rb);
		Vector vars = new Vector();
		vars.addElement(varX);
		vars.addElement(varY);
		((RawDataSource)dataSourceX).labelPoints(labelNumber, vars, rowArrays[0], labelSelectStatus);
	}

	@Override
	public void chartPopupTriggered(ChartEvent e) {
/*		Component c = e.getSubcomponentSource();
System.out.println("Pop up on "+c.getClass().getName()+" at"+e.getX()+", "+e.getY());
		popUp.show(this, e.getX(), e.getY());
		popUp.pack();
		popUp.setVisible(true);
*/	}

	// RAW DATA EVENT LISTENERS
	
	@Override
	public void DataSeriesAdded(RawDataEvent e){}
	@Override
	public void DataSeriesRemoved(RawDataEvent e){}

	@Override
	public void LabelCategoryAdded(RawDataEvent evt) {
		updatePlotsForLabels((RawDataSource)evt.getRawDataSource());
	} 
	
	@Override
	public void LabelCategoryRemoved(RawDataEvent evt) {
		updatePlotsForLabels((RawDataSource)evt.getRawDataSource());
	}

	@Override
	public void LabelColorChanged(RawDataEvent evt) {
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
	public void DataPointsLabeled(RawDataEvent evt){
		if(DEBUG) {
			System.out.println("DataPointsLabeled: Labeling event");
		}
		Vector vars = evt.getVarObjects();
		boolean found = true;
		for(int i = 0; i < varsShown.size(); i++){
			Variable var = (Variable) varsShown.elementAt(i);
			if(var.getDataSource() instanceof RawDataSource){
				if(!vars.contains(var)){
					found = false;
					break;
				}
			}
		}
		if(!found) {
			return;
		}
		if(DEBUG) {
			System.out.println("label event accepted, thus the chart contains at least one variable from RawDataSource.");
		}
		byte[] markers = chart.getMarkerArray("1p/2p");
		Vector labMat = new Vector();
		if(dataSourceX instanceof RawDataSource){
			labMat.addElement(((RawDataSource)dataSourceX).getLabelMatrix(varX));
			if(DEBUG) {
				System.out.println("labeling X");
			}
		}
		if(dataSourceY instanceof RawDataSource){
			labMat.addElement(((RawDataSource)dataSourceY).getLabelMatrix(varY));
			if(DEBUG) {
				System.out.println("labeling Y");
			}
		}
		labelsToMarkers(labMat, markers); 
		chart.setMarkerArray("1p/2p", markers);
		chart.hideSelectionBox();
		chart.invalidateAll();  // invalidate the entire region
		chart.repaint();
		chart.validate();
	}


	@Override
	public void LabelOrderChanged(RawDataEvent evt) {
		updatePlotsForLabels((RawDataSource)evt.getRawDataSource());
	}
	
	@Override
	public void FormulaListChanged(PreprocessorEvent evt) {} 

	@Override
	public void DataChanged(PreprocessorEvent evt)  {
		initializeData();
	}

	private void updatePlotsForLabels(RawDataSource rawDataSource){
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
		if(nLabels > 0){
			markerFormats = new MarkerFormat[nLabels + 1];
			markerFormats[0] = unhighlightedMarker;
			for (int i=0; i<nLabels; i++) {
				NolLabel label = (NolLabel)theLabels.elementAt(i);
				highlightColor = label.getLabelColor();
				markerFormats[i+1] = new MarkerFormat
					(plotSymbol, plotColor, highlightColor, baseSize, highlightSize);  
			}
		} else {
			markerFormats = new MarkerFormat[1];
			markerFormats[0] = unhighlightedMarker;
		}
		chart.setMarkerFormat("1p/2p", markerFormats);
		int nData = dataSeriesX.getRow();  // both data series should have the same length
		byte[] markers = new byte[nData];
		Vector labMat = new Vector();
		if(dataSourceX instanceof RawDataSource){
			labMat.addElement(((RawDataSource)dataSourceX).getLabelMatrix(varX));
		}
		if(dataSourceY instanceof RawDataSource){
			labMat.addElement(((RawDataSource)dataSourceY).getLabelMatrix(varY));
		}
		labelsToMarkers(labMat, markers); 
		chart.setMarkerArray("1p/2p", markers);
		chart.repaint();	
		chart.validate();
	}


	class ControlAction extends AbstractAction {
		ControlAction() { super("controlAction");}
        @Override
		public void actionPerformed(ActionEvent e) {
			String command = e.getActionCommand();
			if(command.equals("Zoom In")) {
				zoomIn();
			}
			else if(command.equals("Zoom Out")) {
				zoomOut();
			}
			else if(command.equals("Label Color...")) {
	/*			NolColorChooser colorChooser = new NolColorChooser(frame, "Color Chooser");
				colorChooser.setLocation(new Point(200,200));
				colorChooser.setVisible(true);
				Color color = colorChooser.getSelectedColor();
				if(colorChooser.getResult()){
					colorChooser.dispose();		
				}else{
					colorChooser.dispose();	
					return;
				}
			//	labelChanged(); */
			}
		}	
	}




}
