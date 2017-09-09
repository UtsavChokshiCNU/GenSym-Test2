package com.gensym.nols.main;

import java.awt.*;
import java.awt.event.*;
import java.util.*;

import javax.swing.*;
import javax.swing.border.*;
import java.text.SimpleDateFormat;

import com.gensym.math.*;
import com.gensym.math.datafit.*;
import com.gensym.math.stats.*;
import com.gensym.math.matrix.*;

import com.gensym.nols.data.*;
import com.gensym.nols.dlg.*;
import com.gensym.nols.chart.line.*;
import com.gensym.nols.chart.scatter.*;

public class NolClassicConsoleFrame extends JFrame implements ClassicModelTrainerListener,
	ActionListener {
	private JTextArea consoleOutput_1;
	private int vCache;	 
	private int numElementsInGraph;
	private int numModelsUpdated;
	private int lastModelAdded_1;

	private JPanel chartPaneOneHolder;
	private JPanel chartPaneTwoHolder;
	private ConsoleLineChart chartOne;
	private ScatChart ensembleModelPredActChart_1;

	private Matrix Y;
	private Matrix X;
	private Matrix YPred;
	private ClassicModel theModel;
	private DataSeries data;

	private JTabbedPane modelViewTabbedPane;
	private JButton stopButton;
	private JTextField modelCountField_1;
	private JTextField lastModelCountField_1;
	private JComboBox varChoiceY_1; 

	private Thread outputModelTrainingThread;

	private double[] essembleTmes_1;
	private int outputVariable1;

	private Project2 project;
	private boolean neverPopUpStateModelPane;
	private boolean chartDirty;
	private int numLinesToKill;
	private Matrix B1;
	private Matrix temp1;
	private Matrix temp2;

	private boolean noFire;
	private boolean newModelUpdated;
	private NolMainFrame frame;


	/** The Console Frame */
	public NolClassicConsoleFrame(Project2 p, NolMainFrame frame) {
		super();
		this.frame = frame;
		project = p;
		setTitle("NOL Console");
		setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);

        WindowListener wl = new WindowAdapter() {
            @Override
			public void windowClosing(WindowEvent e) {
				if(closeWindow()) 
					dispose();
			}
        };
        this.addWindowListener(wl);
		ImageIcon consoleLogo = new ImageIcon(this.getClass().getResource("console.gif"));
		setIconImage(consoleLogo.getImage());
		vCache = 40;
		numElementsInGraph = 20;
		numModelsUpdated = 0;
		lastModelAdded_1 = 0;
		numLinesToKill = 5;  // lines to kill in console cache
		outputVariable1 = 0;
		neverPopUpStateModelPane = true;
		chartDirty = false;
		noFire = false;
		newModelUpdated = false;
		Y = Matlib.createMatrix();
		X = Matlib.createMatrix();
		YPred = Matlib.createMatrix();
		temp1 = Matlib.createMatrix();
		temp2 = Matlib.createMatrix();

		chartPaneOneHolder = getChartPanelOne();

		modelViewTabbedPane = new JTabbedPane();
		modelViewTabbedPane.addTab("Output Model",chartPaneOneHolder);   // model 1 tabbed pane
		modelViewTabbedPane.setSelectedIndex(0);

		getContentPane().setLayout(new BorderLayout());
		getContentPane().add("Center", modelViewTabbedPane);    
		getContentPane().add("East", getControlPanel());  
	}

	private JPanel getErrorChartPane_1(){

		JPanel ePane = new JPanel(new GridLayout());
		ePane.setBorder(BorderFactory.createTitledBorder("Model Predictive Mean Error Chart:"));
		chartOne = new ConsoleLineChart("ERRORChart1",new long[1],new double[1]);		
		
		ePane.add(chartOne);
		setChartOneData(new double[1]);
		return ePane;
	}

	private JPanel getPredActChartPane_1() {
		JPanel ePane = new JPanel(new GridLayout());
		ePane.setBorder(BorderFactory.createTitledBorder("Predicted(Y) vs. Actual(X) Chart:"));
		ensembleModelPredActChart_1 = new ScatChart(false,getBackground());
		ePane.add(ensembleModelPredActChart_1.getChart());
		return ePane;
	}

	private JPanel getChartPanelOne() {
		JPanel centerPane = new JPanel(new BorderLayout());
		JPanel chartPaneOne = new JPanel(new GridLayout(1,2,0,0));
		chartPaneOne.setBorder(BorderFactory.createLoweredBevelBorder());
		chartPaneOne.setBackground(Color.white);
		chartPaneOne.add(getErrorChartPane_1());		
		chartPaneOne.add(getPredActChartPane_1());		

		JPanel updatePane = new JPanel(new GridLayout(1,6,5,5));
		updatePane.setBorder(new EmptyBorder(10,10,10,10));

		modelCountField_1 = new JTextField(String.valueOf(numModelsUpdated));
		modelCountField_1.setEditable(false);

		lastModelCountField_1 = new JTextField(String.valueOf(lastModelAdded_1));
		lastModelCountField_1.setEditable(false);

		varChoiceY_1 = new JComboBox();
		varChoiceY_1.addActionListener(this);
		
		updatePane.add(new JLabel("Updated Times:", SwingConstants.RIGHT));
 		updatePane.add(modelCountField_1);
		updatePane.add(new JLabel("Last Update Time:", SwingConstants.RIGHT));
 		updatePane.add(lastModelCountField_1);
		updatePane.add(new JLabel("Variable:", SwingConstants.RIGHT));
 		updatePane.add(varChoiceY_1);

		JPanel pane0 = new JPanel(new BorderLayout());
		pane0.add("North",updatePane);
		pane0.add("Center",getConsolePanel_1());

 		centerPane.add("Center",chartPaneOne);    	
 		centerPane.add("South",pane0);  
				
		return centerPane;
	}


	private JScrollPane getConsoleTextArea_1(){
		consoleOutput_1 = new JTextArea();
		consoleOutput_1.setEditable(false);
		JScrollPane outputScrollPane = new JScrollPane(consoleOutput_1){
				@Override
				public Dimension getPreferredSize() { return new Dimension(500,50); }
			};
		outputScrollPane.setBorder(BorderFactory.createLoweredBevelBorder());
		return outputScrollPane;
	}

	private JPanel getConsolePanel_1(){
		JPanel pane = new JPanel(new GridLayout());
		pane.add(getConsoleTextArea_1());
		pane.setBorder(new EmptyBorder(10,10,10,10));
		return pane;
	}

	private JPanel getControlPanel(){
 		JPanel control = new JPanel();
		control.setBackground(getContentPane().getBackground());
		control.setLayout(new BoxLayout(control, BoxLayout.Y_AXIS));
		control.setBorder(new EmptyBorder(10, 10, 10, 10));

//		stopButton = new JButton("Stop",stopIcon);
		stopButton = new JButton("Stop");
		stopButton.setActionCommand("Stop");
		stopButton.addActionListener(this);
		stopButton.setEnabled(false);

		control.add(Box.createRigidArea(new Dimension(1,20)));
		control.add(stopButton);
		control.add(Box.createRigidArea(new Dimension(1,500)));
		control.add(Box.createVerticalGlue());
		return control;
	}

	private void setChartOneData(double[] y){
		long[] t = new long[numElementsInGraph];
		double [] newY = new double [numElementsInGraph];

		for(int i = 0; i < numElementsInGraph; i++) {
			if(i < y.length) 
				newY[i] = y[i];
			else 
				newY[i] = Double.NaN;
		}
		chartOne.setData(t, newY);
	}

	private void refreshPredActDisplay_1(){
		if(!newModelUpdated){
			return;
		}
		if(Y.getRows() == 0 || YPred.getRows() == 0) {
			return;
		}
		if(Y.getRows() != YPred.getRows()) {
			return;
		}

		try{
			if(Y.getRows() > 1000){
				if(B1==null || B1.getRows() != Y.getRows()){
					B1 = Matlib.createMatrix(Y.getRows(),1);
					Stats.randomSplit(Y.getRows(),1000,B1);
				}
				Matlib.getRows(Y,B1,temp1);
				Matlib.getRows(YPred,B1,temp2);
				Matlib.transpose(temp1,temp1);
				Matlib.transpose(temp2,temp2);
			}else{
				Matlib.transpose(Y,temp1);		
				Matlib.transpose(YPred,temp2);		
			}
		}catch(MathException evt){
			System.err.println("Non-Fatal exception: " + evt.getMessage());
			evt.printStackTrace();
		}

		double[][] yy = Matlib.create2DArray(temp1);
		double[] y = yy[outputVariable1];

		double[][] yypp = Matlib.create2DArray(temp2);
		double[] yp = yypp[outputVariable1];		
		ensembleModelPredActChart_1.setData(y, yp);
	}

	
	public void appendTextLine(String s, boolean first) {
		int currentPos;

		int numLines_1 = consoleOutput_1.getLineCount();
		if(numLines_1 < vCache){
			consoleOutput_1.append(s);
		} else { // the console output has more than vCache lines, remove some before appending
			currentPos = consoleOutput_1.getText().indexOf('\n') + 1;
			for(int i = 0; i<numLinesToKill-1; i++) {
				currentPos = consoleOutput_1.getText().indexOf('\n', currentPos)+1;
				}
		consoleOutput_1.select(0,currentPos); // modified by bbush on 8-11-98
		consoleOutput_1.cut();
		consoleOutput_1.append(s);
		consoleOutput_1.select(consoleOutput_1.getText().length(), consoleOutput_1.getText().length());
		}

	}

	// if the user tries to close the window using the "X" the window listener calls this method
	public boolean closeWindow() {
		boolean result = false; // assume all are dead
		if(outputModelTrainingThread != null) {
			if(!outputModelTrainingThread.isAlive()) {
				result = true;
			}
		}
		if(result){
			return true; // if not training return
		}
		String[] buttonLabels = {"Yes","No"};
		NolConfirmDialog confirmDialog = new NolConfirmDialog(this,"Training",buttonLabels, "Do you want to stop training?", "question.gif");
		confirmDialog.setFocus(2);
		confirmDialog.setVisible(true);
		if(confirmDialog.getResult() == 1) {
			outputModelTrainingThread.interrupt();
			stopButton.setEnabled(false);	
			return true;
		} else {
			return false;
		}
	}

/** Set the project of this project frame and refresh the display.*/
	public void setProject(Project p){

	}

	public void setOutputModelTrainingThread(Thread t){
		outputModelTrainingThread = t;
	}

	public void setModel(ClassicModel m) {
		theModel = m;
		Vector outs = theModel.getOutputVarNames();
		int numOut_1 = outs.size();
		varChoiceY_1.removeAllItems();
		for(int j=0; j < numOut_1; j++){
			String name = outs.elementAt(j).toString();
			varChoiceY_1.addItem(name);			
		}
		noFire = true;
		varChoiceY_1.setSelectedIndex(0);
		noFire = false;

	}

	public void setModel1TrainInput(Matrix M){
		if(X != null)
			Matlib.clear(X);
		X = M;
	}
	public void setModel1TrainOutput(Matrix M){
		if(Y != null)
			Matlib.clear(Y);
		Y = M;
		if(YPred != null)
			YPred.redimension(Y.getRows(),Y.getCols());
		else
			YPred = Matlib.zeros(Y.getRows(),Y.getCols());
	}

	@Override
	public void error(String message){
		stopButton.setEnabled(false);
		frame.showOKDialog("Found Error: "+message);
	}
	@Override
	public void modelUpdated(){
//System.out.println("modelUpdated");
		newModelUpdated = true;
		numModelsUpdated++;
		modelCountField_1.setText(String.valueOf(numModelsUpdated));
		long timemil = System.currentTimeMillis();
		Date date = new Date(timemil);
		SimpleDateFormat formatter = new SimpleDateFormat ("hh:mm:ss MM.dd ");
		lastModelCountField_1.setText(formatter.format(date));
		try {
			theModel.evaluate(X,YPred);
		} catch (MathException me) {
			System.err.println("Non-Fatal exception: "+ me.getMessage());
			me.printStackTrace();
		}
		refreshPredActDisplay_1();
		double mpe = theModel.getRMSE();
		if(essembleTmes_1 == null){
			essembleTmes_1 = new double[2];
			essembleTmes_1[0] = mpe;
			essembleTmes_1[1] = mpe;
		}else{
			double[] tmes = essembleTmes_1;
			if(essembleTmes_1.length >= numElementsInGraph-1) {  
				// added by bbush on 8-10-98 to roll buffer, FIFO
				essembleTmes_1 = new double[tmes.length]; 
				for(int i = 1; i < tmes.length; i++) // save current array, except for 1st element [i] -> [i-1]
					essembleTmes_1[i-1] = tmes[i];
				essembleTmes_1[tmes.length-1] = mpe;
				tmes = null;
			}else {
				essembleTmes_1 = new double[tmes.length+1];
				for(int i = 0;i < tmes.length; i++) // save current array, all elements
					essembleTmes_1[i] = tmes[i];
				essembleTmes_1[tmes.length] = mpe;
				tmes = null;
			}
		}
		setChartOneData(essembleTmes_1);
		String s = "Model mean squared error: "+mpe +"\n";
		appendTextLine(s, true); // add string s to console
	}

	
	@Override
	public void trainingComplete(){
//System.out.println("trainingComplete");
		newModelUpdated = true;
		modelUpdated();
		stopButton.setEnabled(false);
		frame.showOKDialog("Finished training "+theModel.getName()+" !");
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		if(noFire){
			return;		
		}
		if (e.getSource().equals(stopButton)){
			outputModelTrainingThread.interrupt();
			stopButton.setEnabled(false);
		}else if(e.getSource().equals(varChoiceY_1)) { 
			int index = varChoiceY_1.getSelectedIndex();
			outputVariable1 = index;
			refreshPredActDisplay_1();
			chartOne.validate();
			chartOne.repaint(0l);
		}
	}

	/**
     * ScatChart implementation
     */
    class ScatChart extends Object{
		private ScatterChart chart;
		ScatChart(boolean connectors,Color back){
			chart = new ScatterChart(back);
			if(connectors) {
				chart.setConnectorsState(true);
			}
		
			double [] y = new double[1];
			y[0] = Double.NaN;
			double [] ypred = new double[1];
			ypred[0] = Double.NaN;

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
			highlightColor = null;
			markerFormats[1] = new MarkerFormat
					(plotSymbol, plotColor, highlightColor, baseSize, highlightSize);  
			chart.addDataSeries("1p/2p", y, ypred, markerFormats, markers); 

			chart.setAxisColor(Color.black);
			chart.setBackground(Color.lightGray);
			chart.setFortyFiveDegreeLine(true);
		}

		public void setData(double[] y, double[] ypred) {
			int nData = y.length;
			byte[] markers = new byte[nData];
			chart.setDataSeries("1p/2p", y, ypred, markers); 
		}

		public ScatterChart getChart(){
			return chart;
		}
	}
}

