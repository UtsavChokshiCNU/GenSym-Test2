package com.gensym.nols.chart.bar;

import java.awt.*;
import java.awt.event.*;
import java.util.*;

import javax.swing.*;
import javax.swing.border.*;

import com.gensym.nols.main.*;
import com.gensym.nols.data.*;
import com.gensym.nols.wksp.*;

/**
 * NolHistogramFrame
 *
 * @version     1.2 October 9, 1998
 * @author      Brian O. Bush
**/

public class NolHistogramFrame extends NolInternalFrame implements PreprocessorListener, ActionListener {

	private NolMainFrame frame;
	private String title;
	private Variable var;
	private DataSeries dataSeries;
	private DataSource dataSource;
	private double[] values;
	private BarChart histogramChart;
	private JPanel histogramPane;
	private JScrollBar binBar;
	private JComboBox binCountHolder;
	private JTextField minField;
	private JTextField maxField;
	private double [] data;
	private double xMin;  // user set
	private double xMax;  // user set
	private double varMin;  // variable defined
	private double varMax;  // variable defined
	private int numBins;
	private int numData;
	private boolean noFire;
	
	private static final boolean DEBUG = true;

	private static final String SETTINGS = "HistogramFrame_Settings";
	private static final String BINS = "HistogramFrame_Bins";
	private static final String MIN = "HistogramFrame_Min";
	private static final String MAX = "HistogramFrame_Max";

	public NolHistogramFrame(NolMainFrame frame, Variable variable){
		super(variable.getDataSource());
		
		this.frame = frame;
		this.var = variable;
		this.dataSeries = variable.getDataSeries();
		this.dataSource = variable.getDataSource();

		updateTitle();
		numBins = 25;
		numData = 0; // will be set in initializeData()
		noFire = false;
		
		calculateValues();
		initializeData();
		JPanel workPane = initializeLayout();
		this.setContentPane(workPane);    

		Dimension d = new Dimension(450,400);
		this.setMinimumSize(d);		
	}

	public void updateTitle() {
		this.title = "Histogram - " +  var.getDataSource().getName() + "." + var.getDataSeries().getName() + "." + var.getName() + "   ";
		setTitle(title);
	}

	public Vector getVariables() {
		Vector v = new Vector(1);
		v.addElement(var);
		return v;
	}


	private void updateHistogram(int binCount, double low, double high) {	
		double [] minAndMax = new double[2];
		minAndMax[0] = low; 
		minAndMax[1] = high;
		numData = data.length;
		double [] binValues = new double[binCount];
		if(hist(data, minAndMax, binValues)) { 
			histogramChart.setDataSeries(title, binValues, (double)low, (double)high);
		}
		histogramChart.invalidateAll();
		histogramChart.repaint();
	}

	private void calculateValues(){
		values = new double[11];
		double[] stat = var.getStatistics();
		for(int i = 0; i < stat.length; i++) 
			values[i] = stat[i];
		varMin = stat[7]; 
		varMax = stat[8];
		if(Double.compare(varMin, varMax) == 0) {
			// arbitrary but reasonable way to handle variables with no variance
			varMin = varMin - 1.0;
			varMax = varMax + 1.0;
		}
		xMin = varMin;
		xMax = varMax;
	}

	private void initializeData() {  // bbush 7-21-98
		data = dataSeries.getVarArray(var);
		if(data == null){
			return;
		}
		double [] minAndMax = new double[2];
		minAndMax[0] = varMin; 
		minAndMax[1] = varMax;
		numData = data.length;
		double [] binValues = new double[numBins];
		if(hist(data, minAndMax, binValues)) {
			histogramChart = new BarChart(title, binValues, (double)varMin, (double)varMax);
			histogramChart.setBackground(getBackground());
		}
	}

	private JPanel initializeLayout(){
		JPanel workPane = new JPanel(new BorderLayout());
		histogramPane = new JPanel(new GridLayout());
		histogramPane.setBorder(new EmptyBorder(30,10,0,0));

		JPanel controlPane = new JPanel(new GridLayout(3,2,5,5));
		controlPane.setBorder(BorderFactory.createTitledBorder(frame.getNolResourceString(SETTINGS)));
		controlPane.add(new JLabel(frame.getNolResourceString(BINS)+":"));
		JPanel binPane = new JPanel(new BorderLayout());
		
		binCountHolder = new JComboBox();
		Dimension dim = new Dimension(50,20);
		binCountHolder.setPreferredSize(dim);
		binCountHolder.setMinimumSize(dim);
		binCountHolder.setMaximumSize(dim);
		binCountHolder.removeAllItems();
		for(int i=2; i < 51; i++){
			String name = "" + i;
			binCountHolder.addItem(name);
		}
		binCountHolder.setSelectedIndex(numBins-2);
		binCountHolder.addActionListener(this);
		binPane.add("East",binCountHolder);
		binPane.setPreferredSize(dim);
		binPane.setMinimumSize(dim);
		binPane.setMaximumSize(dim);
		controlPane.add(binPane);

		controlPane.add(new JLabel(frame.getNolResourceString(MIN)+":"));
		minField = new JTextField("");
		minField.setPreferredSize(dim);
		minField.setMinimumSize(dim);
		minField.setMaximumSize(dim);
		minField.setText(String.valueOf(varMin));
		minField.addActionListener(this);
		controlPane.add(minField);

		controlPane.add(new JLabel(frame.getNolResourceString(MAX)+":"));
		maxField = new JTextField("");
		maxField.setPreferredSize(dim);
		maxField.setMinimumSize(dim);
		maxField.setMaximumSize(dim);
		maxField.setText(String.valueOf(varMax));
		maxField.addActionListener(this);
		controlPane.add(maxField);

		JPanel control = new JPanel();
		control.setLayout(new BoxLayout(control, BoxLayout.Y_AXIS));
		control.setBorder(new EmptyBorder(10, 10, 10, 10));

		control.add(Box.createRigidArea(NolMainFrame.vpad15));
		control.add(controlPane);
		control.add(Box.createRigidArea(NolMainFrame.vpad500));
		control.add(Box.createVerticalGlue());

		histogramPane.add(histogramChart);
		
		workPane.add("East", control);
		workPane.add("Center",histogramPane); 
		return workPane;
	}

	/** print out the chart **/
	public void doPrint() {

	//	Toolkit toolkit = this.getToolkit();
		PrintJob job = getToolkit().getPrintJob(null, "Brian's Print Job", null);
		if (job != null) {
			Graphics g = job.getGraphics();
			if(g != null) {
				print(g);
				g.dispose();
			}
			// the page is sent to the printer when the graphics object
			// is disposed.
			job.end();
		}
		// else the user canceled out of the print options dialog
	}

	@Override
	public void FormulaListChanged(PreprocessorEvent evt) {} 

	@Override
	public void DataChanged(PreprocessorEvent evt)  {
		calculateValues();
	}

	public void refreshDataSeriesName(DataSeries ds) {
		if(var.getDataSeries().getName().equals(ds.getName())) 
			updateTitle();
	}

	public void refreshVariableName(Variable v) {
		if(v.getName().equals(var.getName())) 
			updateTitle();
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		if(noFire) {
			return;
		}
		//System.out.println("action =" + e.getActionCommand());
		String command = e.getActionCommand();
		if(e.getSource().equals(binCountHolder)){
			int index = binCountHolder.getSelectedIndex();
			numBins = index + 2;
			updateHistogram(numBins, xMin, xMax) ;
		}else if("Print...".equals(command)) {
			doPrint();
		}else if(e.getSource().equals(minField)){
			double tempMin;
			try {
				tempMin = Double.valueOf(minField.getText()).doubleValue();
			} catch (NumberFormatException x) {
				// revert back to previous value
				setMinField(xMin);  
				getToolkit().beep();
				return;
			}
			if(tempMin>=xMax) {
				// user tried to set min greater than current maximum, so reject it
				setMinField(xMin);
				getToolkit().beep();
				return;
			}
			xMin = tempMin;
			updateHistogram(numBins, xMin, xMax);
		}
		else if(e.getSource().equals(maxField)){
			// System.out.println("maxField");
			double tempMax;
			try {
				tempMax = Double.valueOf(maxField.getText()).doubleValue();			
			} catch (NumberFormatException x) {
				// revert back to previous value
				setMaxField(xMax);  
				getToolkit().beep();
				return;
			}
			if(tempMax<=xMin) {
				// user tried to set max <= min, so reject it
				setMaxField(xMax);
				getToolkit().beep();
				return;
			}
			xMax = tempMax;
			updateHistogram(numBins, xMin, xMax);
		}
	}

	public void setMinField(double min) {
		minField.setText(String.valueOf(min));
	}

	public void setMaxField(double max) {
		maxField.setText(String.valueOf(max));
	}

/** Calculate the data for plotting histogram.*/ //gchen 4/8/98
	public static boolean hist(double[] M, double[] minAndMax, double[] binValues){
		if(minAndMax.length != 2){
			return false;
		}
		if(binValues.length ==0) {
			return false;
		}
		int N = binValues.length;	
		double max = minAndMax[1];
		double min = minAndMax[0];
		double binwidth = (max-min)/N;
		int length = M.length;
		double[] xo = new double[N];
		for(int i=0;i<N;i++) {
			xo[i] = min+binwidth*i;
		}
		// loop excludes last bin (MK 2/9/99)
		for(int i=0;i<N-1;i++){
			for(int j=0;j<length;j++){
				if(M[j]>=xo[i] &&  M[j]<xo[i+1]){
					binValues[i]++;
				}
			}
		}
		// calculate the last bin slightly differently, to prevent dropping max point due to roundoff error
		int lastBin = N-1;
		for(int j=0;j<length;j++){
			if(M[j]>=xo[lastBin] &&  M[j]<=max){
				binValues[lastBin]++;
			}
		}
		return true;
	}
}
