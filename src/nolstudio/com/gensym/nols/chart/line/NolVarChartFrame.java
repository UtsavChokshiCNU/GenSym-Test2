package com.gensym.nols.chart.line;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import javax.swing.*;

import com.gensym.nols.wksp.*;
import com.gensym.nols.data.*;
import com.gensym.nols.dlg.*;
import com.gensym.nols.main.*;
import com.gensym.math.MathException;

 /**
 * NolVarChartFrame
 * @version     1.0 September 1, 1998
 * @author      Gang Chen, Brian O. Bush
 **/

public class NolVarChartFrame extends NolInternalFrame implements ActionListener, ChartListener, RawDataSourceListener, PreprocessorListener//, KeyListener 
{
	private NolMainFrame frame;
	private MultiLineChart chart;
	private Project theProject;
	private NolTripleChoiceDialog choiceDialog;
	private Vector varsShown;
	private Vector varsFullyQualifiedNameShown;
	
	protected JPopupMenu popUp;
	protected Variable popUpVar;
	private ControlAction actionListener;
	private JRadioButton timeModeRadio;
	private JRadioButton rowModeRadio;
	private boolean allowTimeMode;
	private JButton zoomOutButton;
	private JButton removeButton;
	private int zoomInCounter;
	private boolean altPressed;

	private static final boolean DEBUG = false;

	private static final String ZOOMIN = "VarChartFrame_ZoomIn";
	private static final String ZOOMOUT = "VarChartFrame_ZoomOut";
	private static final String ADD = "VarChartFrame_Add";
	private static final String REMOVE = "VarChartFrame_Remove";
 	private static final String STYLE = "VarChartFrame_Style";
  	private static final String STACKED = "VarChartFrame_Stacked";
	private static final String OVERLAY = "VarChartFrame_Overlay";
	private static final String SHAREDYAXIS = "VarChartFrame_SharedYAxis";
	private static final String XAXIS = "VarChartFrame_XAxis";
	private static final String ROW = "VarChartFrame_RowMode";
	private static final String TIME = "VarChartFrame_TimeMode";

	public NolVarChartFrame (NolMainFrame frame, Vector variable) {
		super();
		this.frame = frame;
		altPressed = false;
		
		varsShown = new Vector(0, 10);
		varsFullyQualifiedNameShown = new Vector(0,10);
		chart = new MultiLineChart(MultiLineChart.STACKED_LAYOUT_STYLE, MultiLineChart.ROW_MODE, getBackground());
		chart.addChartListener(this);
		chart.setAxisColor(Color.black);
		this.requestFocus();
		//this.addKeyListener(this);
		actionListener =  new ControlAction();	

		popUp = new JPopupMenu();
		JMenuItem popUpItem = new JMenuItem("Zoom In");
		popUpItem.setActionCommand("Zoom In");
		popUpItem.addActionListener(actionListener);
		popUp.add(popUpItem);

		popUpItem = new JMenuItem("Zoom Out");
		popUpItem.setActionCommand("Zoom Out");
		popUpItem.addActionListener(actionListener);
		popUp.add(popUpItem);

		popUpItem = new JMenuItem("Change Line Color...");
		popUpItem.setActionCommand("Change Line Color...");
		popUpItem.addActionListener(actionListener);
		popUp.add(popUpItem);

		popUpItem = new JMenuItem("Add...");
		popUpItem.setActionCommand("Add...");
		popUpItem.addActionListener(actionListener);
		popUp.add(popUpItem);

		popUpItem = new JMenuItem("Remove");
		popUpItem.setActionCommand("Remove");
		popUpItem.addActionListener(actionListener);
		popUp.add(popUpItem);


		popUpVar = null;   // this is to keep track of the variable that is currently being right-moused

		JPanel controls = new JPanel(true);
		controls.setLayout(new BoxLayout(controls, BoxLayout.Y_AXIS));

		JButton butt;
		JRadioButton radio;
		ButtonGroup group;
		JPanel radioBox, buttons;

		controls.add(Box.createRigidArea(new Dimension(1,20)));
		Dimension vpad10 = new Dimension(1,5);

		buttons = new JPanel();
		buttons.setLayout(new BoxLayout(buttons, BoxLayout.Y_AXIS));
		Dimension dim = new Dimension(90,25);
		butt = new JButton(frame.getNolResourceString(ZOOMIN));
		butt.setActionCommand("Zoom In");
		zoomInCounter = 0;
		butt.addActionListener(this);
		butt.setPreferredSize(dim);
		butt.setMaximumSize(dim);
		buttons.add(butt);
		buttons.add(Box.createRigidArea(vpad10));
		zoomOutButton = new JButton (frame.getNolResourceString(ZOOMOUT));
		zoomOutButton.setActionCommand("Zoom Out");
		zoomOutButton.setEnabled(false);
		zoomOutButton.addActionListener(this);
		zoomOutButton.setPreferredSize(dim);
		zoomOutButton.setMaximumSize(dim);
		buttons.add(zoomOutButton);
		buttons.add(Box.createRigidArea(vpad10));
		butt = new JButton (frame.getNolResourceString(ADD));
		butt.setActionCommand("Add...");
		butt.addActionListener(this);
		butt.setPreferredSize(dim);
		butt.setMaximumSize(dim);
		buttons.add(butt);
		buttons.add(Box.createRigidArea(vpad10));
		removeButton = new JButton (frame.getNolResourceString(REMOVE));
		removeButton.setActionCommand("Remove...");
		removeButton.addActionListener(this);
		removeButton.setPreferredSize(dim);
		removeButton.setMaximumSize(dim);
		buttons.add(removeButton);
		// add buttons to control pane
		controls.add(buttons);
		controls.add(Box.createRigidArea(new Dimension(1,25)));


		// First control, the chart style radio box
		radioBox = new JPanel();
		radioBox.setBorder(BorderFactory.createTitledBorder(frame.getNolResourceString(STYLE)+":"));
		radioBox.setLayout(new BoxLayout(radioBox, BoxLayout.Y_AXIS));
		group = new ButtonGroup();
		radio = new JRadioButton(frame.getNolResourceString(STACKED), true);
		radio.setActionCommand("Stacked");
		radio.addActionListener(this);
		group.add(radio);
		radioBox.add(radio);
		radio = new JRadioButton(frame.getNolResourceString(OVERLAY), false);
		radio.setActionCommand("Overlay");
		radio.addActionListener(this);
		group.add(radio);
		radioBox.add(radio);
		radio = new JRadioButton(frame.getNolResourceString(SHAREDYAXIS), false);
		radio.setActionCommand("Shared Y Axis");
		radio.addActionListener(this);
		group.add(radio);
		radioBox.add(radio);
		controls.add(radioBox);

		// Second control, X Axis style radio box
		radioBox = new JPanel();
		radioBox.setBorder(BorderFactory.createTitledBorder(frame.getNolResourceString(XAXIS)));
		radioBox.setLayout(new BoxLayout(radioBox, BoxLayout.Y_AXIS));
		group = new ButtonGroup();
		rowModeRadio = new JRadioButton(frame.getNolResourceString(ROW), true);
//		rowModeRadio = new JRadioButton("Row               ", true);
		rowModeRadio.setActionCommand("Row mode");
		rowModeRadio.addActionListener(this);
		group.add(rowModeRadio);
		radioBox.add(rowModeRadio);
		timeModeRadio = new JRadioButton(frame.getNolResourceString(TIME), false);
//		timeModeRadio = new JRadioButton("Time         ", false);
		timeModeRadio.setActionCommand("Time mode");
		timeModeRadio.addActionListener(this);
		group.add(timeModeRadio);
		radioBox.add(timeModeRadio);
		controls.add(radioBox);

 		getContentPane().setLayout(new BorderLayout());
		getContentPane().add("Center", chart);
		getContentPane().add("East", controls);

		allowTimeMode = true;
		timeModeRadio.setEnabled(true);

		for(int i = 0; i < variable.size(); i++) {
			Variable var = (Variable) variable.elementAt(i); 
			if(i == 0) // set the project
				this.theProject = var.getDataSource().getProject();
			//System.out.println("adding variable = " + var.getName());
			addDataSeries(var); 
		}
		setTitle();
	}

	private void setTitle() {
		String title = "Line Chart - ";
		Variable var;

		for(int i = 0; i < varsShown.size(); i++) {
			var = (Variable) varsShown.elementAt(i);
			title += var.getDataSource().getName() + "." + var.getDataSeries().getName() + "." + var.getName() + "   ";
		}

		setTitle(title);
		Point p = this.getLocation();
		this.setLocation(p.x+1,p.y);
		this.setLocation(p.x,p.y);
	}
	
	public Vector getVariables() {
		return varsShown;
	}

	public MultiLineChart getChart(){
		return chart;
	}

	/**
	  * removeListeners()
	  * Remove listeners from raw data and/or preprocessors and chart 
	  */
	public void removeListeners() {
		removeVarListeners();
		chart.removeChartListener(this);
	}

	/**
	  * removeVarListeners()
	  * Remove listeners from raw data and/or preprocessors
	  */
	private void removeVarListeners() {
		for(int z = 0; z < varsShown.size(); z++) {
			Variable var = (Variable) varsShown.elementAt(z);
			DataSource source = var.getDataSource();
			source.removeListener(this);
		}
	}

	/**
	  * adjustListeners()
	  * Remove listeners from raw data and/or preprocessors
	  */
	private void adjustListeners() {
		removeVarListeners();
		for(int z = 0; z < varsShown.size(); z++) {
			Variable var = (Variable) varsShown.elementAt(z);
			DataSource source = var.getDataSource();
			if(source instanceof RawDataSource) {
				if(DEBUG) {
					System.out.println("added Raw data source listener...");
				}
				((RawDataSource)source).addListener(this);
			}
			else if(source instanceof Preprocessor) {
				if(DEBUG) {
					System.out.println("added Preprocessor listener...");
				}
				((Preprocessor)source).addListener(this);
			}
			else if(source instanceof NolSimulation) {
				if(DEBUG) {
					System.out.println("added NolSimulation listener...");
				}
				((NolSimulation)source).addListener(this);
			}
			else return;
		}
	}

	/**
	  * addDataSeries(Variable)
	  * Add a data series
	  */
	private void addDataSeries(Variable var) {
		chart.holdOn();
		varsShown.addElement(var);
		String name = var.getDataSource().getName() + "." + var.getDataSeries().getName() + "." + var.getName();
		varsFullyQualifiedNameShown.addElement(name);
		adjustListeners();
		
		DataSeries ds = var.getDataSeries();
		double[] y = ds.getVarArray(var);
		if(y == null) {
			return;
		}
		int nData = y.length;
		if(DEBUG) {
			System.out.println("length=" + nData);
		}

		long[] time = null;
		if(ds.getHasTimeStamps()) 
			 time = ds.getTimeStamps();
		else {
			allowTimeMode = false;
			if(timeModeRadio.isSelected()) {  // we are disabling time mode, switch to row mode
				chart.setMode(MultiLineChart.ROW_MODE); 
				rowModeRadio.setSelected(true);
			}
			timeModeRadio.setEnabled(false);
			time = new long[nData];
			for(int z=0; z < nData; z++) 
				time[z] = (long) z;
		}
/*
		if(DEBUG) {
			for(int i=0; i < nData; i++) 
				System.out.println("y=" + y[i] + " time=" + time[i]);
		}
*/
		int nLabels = theProject.getNumberOfLabels();
		DataSource source = var.getDataSource();
//	boolean isOriginal = false;
//	if(source instanceof RawDataSource) isOriginal = true;
		Color plotColor = var.getPlotColor();
		int plotSymbol = var.getPlotSymbol();
		//System.out.println("plotSymbol=" + plotSymbol);
		LineFormat connectorFormat = new LineFormat(plotColor, 1);
		//System.out.println("num = " + nData);
		byte[] markers = new byte[nData];
		int baseSize = 6;  // what if chart has been zoomed?
		int highlightSize = 10;
		Color highlightColor = null;
		MarkerFormat unhighlightedMarker = new MarkerFormat
			(plotSymbol, plotColor, highlightColor, baseSize, highlightSize);
		MarkerFormat[] markerFormats;
		if ((source instanceof RawDataSource) && (nLabels != -1)) {
			Vector labels = theProject.getLabels();
			boolean[] labelArray = new boolean[labels.size()];
			markerFormats = new MarkerFormat[nLabels + 1];
			markerFormats[0] = unhighlightedMarker;
			for (int i=0; i < nLabels; i++) {
				NolLabel label = (NolLabel)labels.elementAt(i);
				highlightColor = label.getLabelColor();
				//System.out.println("highlightColor=" + highlightColor);
				markerFormats[i+1] = new MarkerFormat
					(plotSymbol, plotColor, highlightColor, baseSize, highlightSize);  
			}
			labelsToMarkers(((RawDataSource)source).getLabelMatrix(var), markers); 
		} else {
			markerFormats = new MarkerFormat[1];
			markerFormats[0] = unhighlightedMarker;
		}
		chart.addDataSeries(name, time, y, markerFormats, markers, connectorFormat);
		if(!removeButton.isEnabled()) {
			removeButton.setEnabled(true);
		}
		chart.holdOff();
	}

	/**
	 * removeDataSeries(Variable)
	 * Remove Data Series
	 *
	 */

	private void removeDataSeries(Variable var) {
		//if(DEBUG) System.out.println("plot count = " + chart.getPlotCount());
		chart.holdOn();
		chart.removeDataSeries(varsShown.indexOf(var));
		varsFullyQualifiedNameShown.removeElementAt(varsShown.indexOf(var));
		varsShown.removeElement(var);
		adjustListeners();
		if(!allowTimeMode) { // check to see if we can allow time mode
			boolean weCanEnable = true;
			for(int i=0; i<varsShown.size(); i++) {
				Variable v = (Variable)varsShown.elementAt(i);
				if(!v.getDataSeries().getHasTimeStamps()) {
					weCanEnable = false;
					break;
				}
			}
			if(weCanEnable) {
				timeModeRadio.setEnabled(true);
			}
		}

		if(varsShown.isEmpty()) {
			removeButton.setEnabled(false);
		}
		chart.holdOff();
	}

	/**
	 * removeAllDataSeries()
	 * Remove all of the Data Series
	 *
	 */

	private void removeAllDataSeries() {
		chart.holdOn();
		varsFullyQualifiedNameShown.removeAllElements();
		varsShown.removeAllElements();
		chart.removeAllDataSeries();
		adjustListeners();
		removeButton.setEnabled(false);
		chart.holdOff();
	}
	
	private void labelsToMarkers(boolean[][] labelMatrix, byte[] markers){
		int[] labelOrder = theProject.getLabelOrder();
		int nLabels = theProject.getNumberOfLabels();
		int nData = markers.length;
		for (int j = 0; j < nData; j++) {
			markers[j] = 0;
			for (int i = 0; i < nLabels; i++) {
				//System.out.println("j = "+j+", i = "+i+", order = "+labelOrder[i]);
				if(labelMatrix[labelOrder[i]][j]) {
					markers[j] = (byte) (labelOrder[i] + 1);  // since 0 is the unhighlighted marker
					break;  // from inner loop
				}
			}
		}
	}

	private void labelsToMarkers(boolean[][] labelMatrix, byte[] markers, int[] rowNumbers) {
		// similar to above, but only evaluate particular row numbers
		int[] labelOrder = theProject.getLabelOrder();
		int nLabels = theProject.getNumberOfLabels();
		int row;
		for (int j = 0; j < rowNumbers.length; j++) {
			row = rowNumbers[j];
			markers[row] = 0;
			for (int i = 0; i < nLabels; i++) {
				//System.out.println("j = "+j+", i = "+i+", order = "+labelOrder[i]);
				if(labelMatrix[labelOrder[i]][row]) {
					markers[row] = (byte) (labelOrder[i] + 1);  // since 0 is the unhighlighted marker
					//System.out.println("marker "+row+" = "+markers[row]);
					break;  // from inner loop
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
		}else if ("Zoom Out".equals(command)){
			zoomOut();
		}else if ("Time mode".equals(command)){
			chart.setMode(MultiLineChart.TIME_MODE);
		}else if ("Row mode".equals(command)){
			chart.setMode(MultiLineChart.ROW_MODE);
		}else if ("Stacked".equals(command)){
			chart.setStyle(MultiLineChart.STACKED_LAYOUT_STYLE);
		}else if ("Overlay".equals(command)){
			chart.setStyle(MultiLineChart.OVERLAY_LAYOUT_STYLE);
		}else if ("Shared Y Axis".equals(command)) {
			chart.setStyle(MultiLineChart.SHARED_Y_LAYOUT_STYLE);
		}else if ("Add...".equals(command)) {  
			addAction();
			//---end of heavy mods by bbush
		}else if ("Remove...".equals(command)) {
			JFrame jframe = getFrame();
			NolSingleChoiceDialog dg = new 
				NolSingleChoiceDialog(jframe, "Select Variables", "Variables:", varsFullyQualifiedNameShown, true);
			dg.setBounds(200, 200, 300, 200);
			dg.setVisible(true);
			if(dg.getResult()) {
				Vector ds = dg.getSelectedItems();
				for(int i = 0; i < ds.size(); i++) {
					Variable var = (Variable)varsShown.elementAt(varsFullyQualifiedNameShown.indexOf(ds.elementAt(i)));
					removeDataSeries(var);
				}
			}
			setTitle();
		}
		
	}

	public void addAction() {
		Vector dataSourceNames = new Vector();
		Vector seriesNames = new Vector();
		Vector varNames = new Vector();

		// SOURCE: Raw Data
		RawDataSource rds = theProject.getRawDataSource(); // SOURCE LEVEL - only one data source
		dataSourceNames.addElement(rds);
		Vector sNames = new Vector();
		Vector vvNames = new Vector();
		for(int j = 0; j < rds.getNumberOfDataSeries(); j++) { // SERIES level
			DataSeries ds = rds.getDataSeries(j);
			sNames.addElement(ds);
			Vector vNames = new Vector();
			for(int k = 0; k < ds.getColumn(); k++) { // VARIABLE level
				Variable var = ds.getVarByIndex(k);
				if(!varsShown.contains(var))
					vNames.addElement(var);
			}
			vvNames.addElement(vNames);
		}
		varNames.addElement(vvNames);
		seriesNames.addElement(sNames);

		// SOURCE: Preprocessors
		for(int i = 0; i < theProject.getNumberOfPreprocessors(); i++) { // SOURCE LEVEL
			Preprocessor pre = theProject.getPreprocessorByIndex(i);
			dataSourceNames.addElement(pre);
			Vector sNames2 = new Vector();
			Vector vvNames2 = new Vector();
			for(int j = 0; j < pre.getNumberOfDataSeries(); j++) { // SERIES level
				DataSeries ds = pre.getDataSeries(j);
				sNames2.addElement(ds);
				Vector vNames = new Vector();
				for(int k = 0; k < ds.getColumn(); k++) { // VARIABLE level
					Variable var = ds.getVarByIndex(k);
					if(!varsShown.contains(var))
						vNames.addElement(var);
				}
				vvNames2.addElement(vNames);
			}
			varNames.addElement(vvNames2);
			seriesNames.addElement(sNames2);
		}

		// SOURCE: Simulations
		for(int i = 0; i < theProject.getNumberOfSimulations(); i++) {
			NolSimulation sim = theProject.getSimulation(i);
			dataSourceNames.addElement(sim);
			Vector sNames3 = new Vector();
			Vector vvNames3 = new Vector();
			for(int j = 0; j < sim.getNumberOfDataSeries(); j++) { // SERIES level
				DataSeries ds = sim.getDataSeries(j);
				sNames3.addElement(ds);
				Vector vNames = new Vector();
				for(int k = 0; k < ds.getColumn(); k++) { // VARIABLE level
					Variable var = ds.getVarByIndex(k);
					vNames.addElement(var);
				}
				vvNames3.addElement(vNames);
			}
			varNames.addElement(vvNames3);
			seriesNames.addElement(sNames3);
		}

		
		getTripleChoiceDialog().setContent("Select Variables", "Data Source:", "Data Series:", "Variable:", dataSourceNames, seriesNames, varNames, true);
		getTripleChoiceDialog().pack();
		getTripleChoiceDialog().setBounds(200, 200, 320, 300);
		getTripleChoiceDialog().setVisible(true);

		if(!getTripleChoiceDialog().getResult()){
			this.repaint(0l);
			this.validate();
			return;
		}

		Vector variableObjects = getTripleChoiceDialog().getSelectedItems();

		for(int i= 0; i < variableObjects.size(); i++) {
			Variable var = (Variable) variableObjects.elementAt(i);
			addDataSeries(var);
		}

		setTitle();
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

	public void refreshVariableName(Variable var) {
		if(varsShown.contains(var)) {
			int index = varsShown.indexOf(var);
			varsFullyQualifiedNameShown.removeElementAt(varsShown.indexOf(var));
			String name = var.getDataSource().getName() + "." + var.getDataSeries().getName() + "." + var.getName();
			varsFullyQualifiedNameShown.insertElementAt(name, index);
			setTitle();
		}
	}

	/** Create or get the super dupper NolTripleChoiceDialog.*/
	private NolTripleChoiceDialog getTripleChoiceDialog(){
		if(choiceDialog == null){
			JFrame jframe = getFrame();
			choiceDialog = new NolTripleChoiceDialog(jframe,"Select Dialog","Choice 1:", "Choice 2:", "Choice 3:", new Vector(), new Vector(), new Vector(), false);
		}
		return choiceDialog;
	}

	@Override
	public void chartPopupTriggered(ChartEvent e) {
		//System.out.println("chartPopupTriggered triggered - right mouse");
//System.out.println("chartPopupTriggered triggered - right mouse getModifiers="+e.getModifiers());

		
		Component c = e.getSubcomponentSource();
		if(c instanceof ComboPlot) {
			ComboPlot plot = (ComboPlot) c;
			String plotName = plot.getName();
			int varIndex = varsFullyQualifiedNameShown.indexOf(plotName);
			Variable var = (Variable)varsShown.elementAt(varIndex);
			popUpVar = var;
			popUp.show(this, getBounds().x, getBounds().y);
			//System.out.println("x = " + e.getX() + " y = " + e.getY());
			popUp.pack();	
			popUp.setVisible(true);
		}
		else if(c instanceof ValueAxis) {
			//System.out.println("right-clicking on axis"); 
		}
	}
	
	@Override
	public void chartPointSelected(ChartEvent e) {
//System.out.println("chartPointSelected triggered - right mouse getModifiers="+e.getModifiers());
		if(e.getModifiers() == 4) {
			return;
		}
		Component c = e.getSubcomponentSource();
		//System.out.println("\nEvent: chartPointSelected = " + e);
		if(c instanceof ComboPlot) {
			ComboPlot plot = (ComboPlot) c;
			String plotName = plot.getName();
	
			int varIndex = varsFullyQualifiedNameShown.indexOf(plotName);
			Variable var = (Variable)varsShown.elementAt(varIndex);

			DataSource dataSource = var.getDataSource();			
			if(!(dataSource instanceof RawDataSource)) {
				return;
			}
			RawDataSource datsr = (RawDataSource)dataSource;
			boolean labelSelectStatus = datsr.getSelectStatus();
		
			int[] order = theProject.getLabelOrder();
			if(order.length == 0) {
				return;		
			}
			int labelNumber = order[0];
			int rowNumber = plot.findPoint(e.getX(), e.getY());
			if (rowNumber == -1) {
				return;
			}
			int[] rowNumbers = {rowNumber};
			
			// select or unselect point on plot
			datsr.labelPoints(labelNumber, var, rowNumbers, labelSelectStatus);
		}
		else {
			return;
		}
	}


	@Override
	public void chartAreaSelected(ChartEvent e) {
		Component c = e.getSubcomponentSource();
		int behavior = chart.getSelectionBoxBehavior();
		// System.out.println("\tchartAreaSelected: Selection box = " + behavior);
		Vector components = new Vector(0, 10);
		Vector intersections = new Vector(0, 10);
		chart.getIntersectingComponents(e.getSelectionRectangle(), components, intersections);
		double uy, ly;
		int firstRow, lastRow;
		Rectangle intersection;
		boolean labelSelectStatus = false;
		int[] order;
		int labelNumber = 0;
		Hashtable hashy = new Hashtable(10);
		RawDataSource datsr = null;

		if (behavior == Chart.VERTICAL_BEHAVIOR) {
			if(DEBUG) {
				System.out.println("\tchartAreaSelected: Chart Behavior is Vertical");
			}
			int index = components.indexOf(chart.xAxis);  // find x axis
			if (index == -1) {
				return;
			}
			// affects all variables, not just the ones plotted
			intersection = (Rectangle) intersections.elementAt(index);
			ValueAxis xaxis = (ValueAxis) components.elementAt(index);
			for (int i = 0; i < components.size(); i++) {
				if (components.elementAt(i) instanceof ComboPlot) {
					ComboPlot plot = (ComboPlot) components.elementAt(i);
					String plotName = plot.getName();
					if(DEBUG) {
						System.out.println("\tchartAreaSelected-VERTICAL: plotName = " + plotName);
					}

					int varIndex = varsFullyQualifiedNameShown.indexOf(plotName);
					if(varIndex >= 0)  { // if component exists
						// note: somehow some components still exist even though they have been removed.
						Variable var = (Variable)varsShown.elementAt(varIndex);
						DataSource dataSource = var.getDataSource();
						if(dataSource instanceof RawDataSource) {  // if dataSource is the raw datasource
							datsr = (RawDataSource)dataSource;
							DataSeries ds = var.getDataSeries();
							//System.out.println("\tchartAreaSelected-VERTICAL: var = " + var.getName());
							labelSelectStatus = datsr.getSelectStatus();
							order =  theProject.getLabelOrder();
							if(order.length == 0) {
								return;		
							}
							labelNumber = order[0];
							intersection = (Rectangle) intersections.elementAt(i);
							int nvars = ds.getColumn();  // get the number of variables
							if(nvars == -1) {
								return;
							}
							if (chart.getMode() == MultiLineChart.TIME_MODE) {
								// -1 (extra pixel) need to allow selection of zero-th point
								long firstTime = xaxis.pixelToCoordinate(intersection.x - 1).longValue();
								long lastTime = xaxis.pixelToCoordinate(intersection.x + intersection.width).longValue();
								for (int varNumber=0; varNumber<nvars; varNumber++) {
									Variable v = ds.getVarByIndex(varNumber);
									int[] rows = labelTimeRange(ds, v, labelNumber, firstTime, lastTime, labelSelectStatus);
									hashy.put(v,rows);
								}
							} else {
								// -1 (extra pixel) need to allow selection of zero-th point
								firstRow = xaxis.pixelToCoordinate(intersection.x - 1).intValue() + 1;
								lastRow = xaxis.pixelToCoordinate(intersection.x + intersection.width).intValue();
								for (int varNumber=0; varNumber < nvars; varNumber++) {
									Variable v = ds.getVarByIndex(varNumber);
									int[] rows = labelRowRange(ds, v, labelNumber, firstRow, lastRow, labelSelectStatus);
									hashy.put(v,rows);
								}
							}
						}
					}
				}
			}
		}
		else {  // JUST RECTANGULAR SELECTION 
			// System.out.println("chartAreaSelected: Chart Behavior is Other than vertical");
			for (int i = 0; i < components.size(); i++) {
				if (components.elementAt(i) instanceof ComboPlot) {
					ComboPlot plot = (ComboPlot) components.elementAt(i);
					String plotName = plot.getName();
					// System.out.println("\nchartAreaSelected: plotName = " + plotName);
					int varIndex = varsFullyQualifiedNameShown.indexOf(plotName);
					if(varIndex >= 0) { // if component exists, not exist index = -1
						// note: somehow some components still exist even though they have been removed.
						//System.out.println("\nchartAreaSelected: varIndex = " + varIndex);
						Variable var = (Variable)varsShown.elementAt(varIndex);		
						DataSource dataSource = var.getDataSource();			
						if(dataSource instanceof RawDataSource) {    // if dataSource is the raw datasource
							datsr = (RawDataSource)dataSource;
							DataSeries ds = var.getDataSeries();
							labelSelectStatus = datsr.getSelectStatus();
							order =  theProject.getLabelOrder();
							if(order.length == 0) {
								return;		
							}
							labelNumber = order[0];
							intersection = (Rectangle) intersections.elementAt(i);
							if (behavior == Chart.HORIZONTAL_BEHAVIOR) {
								firstRow = 0;
								lastRow = ds.getRow();
							} else {
								// -1 (extra pixel) need to allow selection of zero-th point
								// +1 needed because pixelToRow returns row immediately to left of box
								firstRow = plot.pixelToRow(intersection.x - 1) + 1;  
								lastRow = plot.pixelToRow(intersection.x + intersection.width);
							}
							uy = plot.pixelToY(intersection.y);
							ly = plot.pixelToY(intersection.y + intersection.height);
							if (firstRow <= lastRow) {
								int [] rows = labelDataRange(ds, var, labelNumber, ly, uy, firstRow, lastRow, labelSelectStatus);
								hashy.put(var, rows);
							}
						}
					}
				}
			}
		}
		// now update all of the labels...
		if(datsr != null){
			datsr.labelPoints(labelNumber, hashy, labelSelectStatus);
		}
	}

	public int[] labelDataRange(final DataSeries dataSeries, final Variable var, final int labelNumber, 
			final double lowerBound, final double upperBound, final int firstRow, final int lastRow, 
			final boolean newLabel) {
		
		int firstRowIndex = firstRow;
		int lastRowIndex = lastRow;
		DataSource dataSource = var.getDataSource();
		RawDataSource datsr = (RawDataSource)dataSource;
		int row = dataSeries.getRow();  // get the number of rows
		if(row == -1) { 
			int[] temp = new int[0]; 
			return temp; 
		}
		if (firstRowIndex < 0) {
			firstRowIndex = 0;
		}
		if (lastRowIndex >= row) {
			lastRowIndex = row;
		}
		int selected = 0;
		int[] possibleRowNumbers = new int[lastRowIndex-firstRowIndex+1];
		if(DEBUG) {
			System.out.println("lebeling data range: first row = " + firstRowIndex + " LastRow = " + lastRowIndex + " LabelNumber = " + labelNumber);
		}
		for(int i = firstRowIndex; i < lastRowIndex; i++) {  // note loop is inclusive
			try {
				double y = dataSeries.getValueAt(i, var.getColumnIndex());
				if(!Double.isNaN(y)) {
					if (y >= lowerBound && y <= upperBound) {
						possibleRowNumbers[selected++] = i;
					}
				}
			} catch (MathException e) {
				System.err.println("Fatal Error: Attempted to access data that is not present");
				e.printStackTrace();
			}
		}
		int[] rowNumbers = new int[selected];
		for(int i = 0; i < selected; i++) {
			rowNumbers[i] = possibleRowNumbers[i];
		}
		return rowNumbers;
	}

	
	private int[] labelRowRange(final DataSeries dataSeries, final Variable var, final int labelNumber, 
			final int firstRow, final int lastRow, final boolean newLabel) {
		//if(DEBUG) System.out.println("labelRowRange");
		int firstRowIndex = firstRow;
		int lastRowIndex = lastRow;
		DataSource dataSource = var.getDataSource();
		RawDataSource datsr = (RawDataSource)dataSource;
		int row = dataSeries.getRow();
		if(row == -1) { 
			int[] temp = new int[0]; 
			return temp; 
		}
		if (firstRowIndex < 0){
			firstRowIndex = 0;
		}
		if (lastRowIndex >= row) {
			lastRowIndex = row - 1;
		}
		int[] possibleRowNumbers = new int[Math.abs(lastRowIndex-firstRowIndex+1)];
		int selected = 0;
		for(int i=firstRowIndex; i<=lastRowIndex; ++i) {  // loop is inclusive
			possibleRowNumbers[selected++] = i;
		}
		int[] rowNumbers = new int[selected];
		for(int i = 0; i < selected; i++){
			rowNumbers[i] = possibleRowNumbers[i];
		}
		return rowNumbers;
	}

	private int[] labelTimeRange(DataSeries dataSeries, Variable var, int labelNumber, long lowTime, long highTime, boolean newLabel) {
		//if(DEBUG) System.out.println("labelTimeRange");
		// labels points in the range lowTime to highTime
		DataSource dataSource = var.getDataSource();
		RawDataSource datsr = (RawDataSource)dataSource;

		int firstRow = dataSeries.findRowAtTime(lowTime) + 1;
		if (firstRow < 0) {
			firstRow = 0;  // reset if illegal value
		}
		int lastRow = dataSeries.findRowAtTime(highTime);
		return(labelRowRange(dataSeries, var, labelNumber, firstRow, lastRow, newLabel));
	}


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
	public void LabelNameChanged(RawDataEvent evt) {}

	@Override
	public void LabelColorChanged(RawDataEvent evt) {
		updatePlotsForLabels((RawDataSource)evt.getRawDataSource());
	}

	/**
	  *
	  * DataPointsLabeled (RawDataEvent e)
	  * modified by bbush, 10-7-98
	  **/
	@Override
	public void DataPointsLabeled(RawDataEvent evt){
		if(DEBUG){
			System.out.println("DataPointsLabeled: Labeling event");
		}

		Vector vars = evt.getVarObjects();
		boolean found = false;
		for(int i=0;i<varsShown.size();i++){
			Variable var = (Variable) varsShown.elementAt(i);
			if(vars.contains(var)){
				found = true;
				break;
			}
		}

		if(!found){
			return;
		}

		RawDataSource datsr = (RawDataSource)evt.getRawDataSource();
	
		for (int plot = 0; plot < varsShown.size(); plot++) {
			Variable var = (Variable) varsShown.elementAt(plot);
			if(var.getDataSource() instanceof RawDataSource) {
				boolean[][] labels = datsr.getLabelMatrix(var);
				byte[] markers = chart.getMarkerArray(plot);
				labelsToMarkers(labels, markers);
				chart.setMarkerArray(plot, markers);
			}
		}	

		chart.hideSelectionBox();
		chart.repaint(0l);
		chart.validate();
	}


	@Override
	public void LabelOrderChanged(RawDataEvent evt) {
		updatePlotsForLabels((RawDataSource)evt.getRawDataSource());
	} 

	@Override
	public void FormulaListChanged(PreprocessorEvent evt) {} 


	/** Data has changed; remove and re-add dataseries.*/
	@Override
	public void DataChanged(PreprocessorEvent evt)  {
		if(DEBUG) {
			System.out.println("DataChanged: Chart frame received PreprocessorEvent event");
		}

		// check to see if the variable(s) being updated are actually contained in the chart, if not, return.
		boolean found = false;
		Vector dsFromEvent = evt.getDataSeries();
		if(dsFromEvent.isEmpty()){
			return;
		}

		for (int i = 0; i < dsFromEvent.size(); i++) {
			DataSeries ds = (DataSeries)dsFromEvent.elementAt(i);
			for(int j = 0; j < varsShown.size(); j++) {
				Variable v = (Variable)varsShown.elementAt(i);
				if(v.getDataSeries().getName().equals(ds.getName())) {
					found = true;	
					break;
				}
			}
		}

		if(!found){
			return;
		}

		int numVars = varsShown.size();
		Vector variableVector = new Vector(numVars);

		// save all variables displayed
		for (int i = 0; i < numVars; i++) {
			Variable var = (Variable)varsShown.elementAt(i);
			variableVector.addElement(var);
		}

		// remove all data series
		removeAllDataSeries();

		// re-add all variables previously displayed 
		for(int i = 0; i < numVars; i++) {
			Variable var = (Variable)variableVector.elementAt(i);
			addDataSeries(var);
		}
	}

	/** something with labels or labeled data has changed (color, symbol, removed, added etc.), so reset and redraw them. */
	private void updatePlotsForLabels(RawDataSource rawDataSource){
		if(DEBUG) {
			System.out.println("updatePlotsForLabels: Chart frame received RawDataSource event");
		}
		Vector theLabels = theProject.getLabels();
		int labelSize = theLabels.size();
		int baseSize = 6;  // what if chart has been zoomed?
		int highlightSize = 10;

		for (int plot = 0; plot < varsShown.size(); plot++) {
			Variable var = (Variable) varsShown.elementAt(plot);
			if(var.getDataSource() instanceof RawDataSource) {  // labels are only applied to Raw Data series
				boolean[][] labels = rawDataSource.getLabelMatrix(var);
				byte[] markers = chart.getMarkerArray(plot);
				labelsToMarkers(labels, markers);
				chart.setMarkerArray(plot, markers);
				Color plotColor = var.getPlotColor();
				int plotSymbol = var.getPlotSymbol();
				Color highlightColor = null;
				
				MarkerFormat unhighlightedMarker = new MarkerFormat(plotSymbol, plotColor, highlightColor, baseSize, highlightSize);
				MarkerFormat[] markerFormats = new MarkerFormat[labelSize + 1];
				markerFormats[0] = unhighlightedMarker;
				for (int i = 0; i < labelSize; i++) {
					NolLabel label = (NolLabel)theLabels.elementAt(i);
					highlightColor = label.getLabelColor();
					markerFormats[i+1] = new MarkerFormat(plotSymbol, plotColor, highlightColor, baseSize, highlightSize);  
				}
				chart.setMarkerFormats(plot, markerFormats);
			}
		}
		chart.repaint();	
	}


	/** Clear the links in this spreadsheet for garbage collection.*/
	public void clearAll(){
//		super.clearAll();
		removeVarListeners();
		chart = null;
		varsShown.removeAllElements();
		varsShown = null;
		varsFullyQualifiedNameShown.removeAllElements();
		varsFullyQualifiedNameShown = null;
	}						 
	
	public void zoomIn() {
	//	System.out.println("(+)zoomInCounter=" + zoomInCounter);
		if(!zoomOutButton.isEnabled()) 
			zoomOutButton.setEnabled(true);
		zoomInCounter++;
		chart.zoomIn();
	}

	public void zoomOut() {
	//	System.out.println("(-)zoomInCounter=" + zoomInCounter);
		if(zoomInCounter <= 0) 
			zoomOutButton.setEnabled(false);
		zoomInCounter--;
		chart.zoomOut();
	}
/*
	public void keyPressed(KeyEvent e) {
		System.out.println("key pressed = " + e);
		if(e.getKeyCode() == KeyEvent.VK_ALT) {
			altPressed = true;
			if(DEBUG) System.out.println("Alt key pressed");
		}
	}

	public void keyReleased(KeyEvent e) {
		if(e.getKeyCode() == KeyEvent.VK_ALT) {
			altPressed = false;
			if(DEBUG) System.out.println("Alt key pressed");
		}
	}

	public void keyTyped(KeyEvent e) {}
*/

	class ControlAction extends AbstractAction {
		ControlAction() { 
			super("controlAction");
		}

        @Override
		public void actionPerformed(ActionEvent e) {
			String command = e.getActionCommand();
			if(command.equals("Add...")) {
				addAction();
			}
			else if(command.equals("Remove...")) {
				if(popUpVar != null) {
					removeDataSeries(popUpVar);
					popUpVar = null;
				}
			}
			else if(command.equals("Zoom In")) {
				zoomIn();
			}
			else if(command.equals("Zoom Out")) {
				zoomOut();
			}
			else if(command.equals("Change Line Color...")) {
//System.out.println("popUpVar="+popUpVar.getName());
				NolColorChooser colorChooser = new NolColorChooser((JFrame)frame, "Color Chooser");
				colorChooser.setBounds(200,200,300,300);
				colorChooser.setVisible(true);
				Color color = colorChooser.getSelectedColor();
				if(colorChooser.getResult()){
					colorChooser.dispose();		
				}else{
					colorChooser.dispose();	
					setWaitCursor(false);
					return;
				}
				popUpVar.setPlotColor(color);	 //propergate the event gchen 11.18.98
				updatePlotsForColor(popUpVar);
			}
		}	
	}

	/** something with color, so reset and redraw them. */
	private void updatePlotsForColor(Variable var){
		int plot = varsShown.indexOf(var);
		MarkerFormat[] markerFormats = chart.getMarkerFormats(plot);
		MarkerFormat unhighlightedMarker = markerFormats[0];
		Color plotColor = var.getPlotColor();
		unhighlightedMarker.setForegroundColor(plotColor);
		chart.setMarkerFormats(plot, markerFormats);
		LineFormat lineFormat = chart.getLineFormat(plot);
		lineFormat.setColor(plotColor);
		chart.repaint(0l);
		chart.validate();
		Rectangle reg = getBounds();
		setBounds(reg.x,reg.y,reg.width+1,reg.height+1);
		repaint(0l);
		validate();
		setBounds(reg.x,reg.y,reg.width,reg.height);
		repaint(0l);
		validate();
	}

}
