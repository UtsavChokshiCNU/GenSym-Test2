package com.gensym.nols.deploy;

import java.awt.*;
import java.awt.event.*;
import java.util.*;

import javax.swing.*;
import javax.swing.border.*;

import com.gensym.math.*;
import com.gensym.math.datafit.*;
import com.gensym.math.stats.*;
import com.gensym.math.matrix.*;

import com.gensym.nols.data.*;
import com.gensym.nols.dlg.*;
import com.gensym.nols.chart.line.*;
import com.gensym.nols.chart.scatter.*;

public class NolOnlineConsoleFrame extends JFrame implements EnsembleModelListener,
	ActionListener {
	private JTextArea consoleOutput_1;
	private JTextArea consoleOutput_2;
	private int vCache;	 
	private int numElementsInGraph;
	private int numModelsTrained_1;
	private volatile int lastModelAdded_1;
	private int numModelsTrained_2;
	private volatile int lastModelAdded_2;

	private boolean withTwoModels;

	private JPanel chartPaneOneHolder;
	private JPanel chartPaneTwoHolder;
	private ConsoleLineChart chartOne;
	private ScatChart ensembleModelPredActChart_1;
	private ConsoleLineChart chartTwo;
	private ScatChart ensembleModelPredActChart_2;

	private Matrix Y;
	private Matrix X;
	private Matrix YPred;
	private Matrix D;
	private Matrix I;
	private Matrix DPred;
	private INolModel2 theModel;

	private JTabbedPane modelViewTabbedPane;
	private JButton stopButton;
	private JTextField modelCountField_1;
	private JTextField lastModelCountField_1;
	private JTextField modelCountField_2;
	private JTextField lastModelCountField_2;
	private JComboBox varChoiceY_1; 
	private JComboBox varChoiceY_2; 

	private Thread outputModelTrainingThread;
	private Thread stateModelTrainingThread;

	private double[] essembleTmes_1;
	private double[] essembleTmes_2;
	private int outputVariable1;
	private int outputVariable2;

	private volatile boolean neverPopUpStateModelPane;
	private boolean chartDirty;
	private int numLinesToKill;
	private Matrix B1;
	private Matrix B2;
	private Matrix temp1;
	private Matrix temp2;

	private boolean noFire;
    private String motif    = "com.sun.java.swing.plaf.motif.MotifLookAndFeel";
    private String windows  = "com.sun.java.swing.plaf.windows.WindowsLookAndFeel";

	private OnlineProcessor onlineProcessor;
	private OnlineOptimizer onlineOptimizer;
	private boolean oneSubModel;

	/** The Console Frame */
	public NolOnlineConsoleFrame(OnlineProcessor onlineProcessor) {
		this();
		this.onlineProcessor = onlineProcessor;
		this.onlineOptimizer = null;
	}

	public NolOnlineConsoleFrame(OnlineOptimizer onlineOptimizer) {
		this();
		this.onlineOptimizer = onlineOptimizer;
		this.onlineProcessor = null;
	}
	
	public NolOnlineConsoleFrame() {
		super();

		String os = System.getProperty("os.name");		
		String currentLF = windows;
		if(os.indexOf("Win") == -1){
			currentLF = motif;
		}
		try {
			UIManager.getLookAndFeel();  // this is to work around some swing problems.
			UIManager.setLookAndFeel(currentLF);
		} catch (Throwable t) {
			System.err.println(t.toString());
			return;
		}

		setTitle("NOL Console");
		setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);

        WindowListener wl = new WindowAdapter() {
            @Override
			public void windowClosing(WindowEvent e) {
				if(closeWindow()){ 
					dispose();
				}
			}
        };
        this.addWindowListener(wl);
		ImageIcon consoleLogo = new ImageIcon(this.getClass().getResource("console.gif"));
		setIconImage(consoleLogo.getImage());
		
		vCache = 40;
		numElementsInGraph = 20;
		numModelsTrained_1 = 0;
		lastModelAdded_1 = 0;
		numModelsTrained_2 = 0;
		lastModelAdded_2 = 0;
		numLinesToKill = 5;  // lines to kill in console cache
		outputVariable1 = 0;
		outputVariable2 = 0;
		withTwoModels = false;
		neverPopUpStateModelPane = true;
		chartDirty = false;
		noFire = false;
		Y = Matlib.createMatrix();
		X = Matlib.createMatrix();
		YPred = Matlib.createMatrix();
		D = Matlib.createMatrix();
		I = Matlib.createMatrix();
		DPred = Matlib.createMatrix();
		temp1 = Matlib.createMatrix();
		temp2 = Matlib.createMatrix();

		chartPaneOneHolder = getChartPanelOne();
		chartPaneTwoHolder = getChartPanelTwo();

		modelViewTabbedPane = new JTabbedPane();
		modelViewTabbedPane.addTab("Output Model",chartPaneOneHolder);   // model 1 tabbed pane
		modelViewTabbedPane.setSelectedIndex(0);

		getContentPane().setLayout(new BorderLayout());
		getContentPane().add("Center", modelViewTabbedPane);    
		getContentPane().add("East", getControlPanel());  
	}

	private JPanel getErrorChartPane_1(){

		JPanel ePane = new JPanel(new GridLayout());
		ePane.setBorder(BorderFactory.createTitledBorder("Ensemble Model Predictive Mean Error Chart:"));
		chartOne = new ConsoleLineChart("ERRORChart1",new long[1],new double[1]);		
		
		ePane.add(chartOne);
		setChartOneData(new double[1]);
		return ePane;
	}

	private JPanel getPredActChartPane_1() {
		JPanel ePane = new JPanel(new GridLayout());
		ePane.setBorder(BorderFactory.createTitledBorder("Predicted(Y) vs. Actual(X) Chart:"));
		ensembleModelPredActChart_1 = new ScatChart(false, getBackground());
		ePane.add(ensembleModelPredActChart_1.getChart());
		return ePane;
	}

	private JPanel getErrorChartPane_2(){

		JPanel ePane = new JPanel(new GridLayout());
		ePane.setBorder(BorderFactory.createTitledBorder("Ensemble Model Predictive Mean Error Chart:"));
		chartTwo = new ConsoleLineChart("ERRORChart1",new long[1],new double[1]);		
		
		ePane.add(chartTwo);
		setChartTwoData(new double[1]);
		return ePane;
	}

	private JPanel getPredActChartPane_2() {
		JPanel ePane = new JPanel(new GridLayout());
		ePane.setBorder(BorderFactory.createTitledBorder("Predicted vs. Actual Chart:"));
		ensembleModelPredActChart_2 = new ScatChart(false, getBackground());
		ePane.add(ensembleModelPredActChart_2.getChart());
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

		modelCountField_1 = new JTextField(String.valueOf(numModelsTrained_1));
		modelCountField_1.setEditable(false);

		lastModelCountField_1 = new JTextField(String.valueOf(lastModelAdded_1));
		lastModelCountField_1.setEditable(false);

		varChoiceY_1 = new JComboBox();
		varChoiceY_1.addActionListener(this);
		
		updatePane.add(new JLabel("Models Trained:", SwingConstants.RIGHT));
 		updatePane.add(modelCountField_1);
		updatePane.add(new JLabel("Last Update:", SwingConstants.RIGHT));
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

	private JPanel getChartPanelTwo() {
		JPanel centerPane = new JPanel(new BorderLayout());
		JPanel chartPaneTwo = new JPanel(new GridLayout(1,2,0,0));
		chartPaneTwo.setBorder(BorderFactory.createLoweredBevelBorder());
		chartPaneTwo.setBackground(Color.white);
		chartPaneTwo.add(getErrorChartPane_2());		
		chartPaneTwo.add(getPredActChartPane_2());		

		JPanel updatePane = new JPanel(new GridLayout(1,6,5,5));
		updatePane.setBorder(new EmptyBorder(10,10,10,10));

		modelCountField_2 = new JTextField(String.valueOf(numModelsTrained_2));
		modelCountField_2.setEditable(false);

		lastModelCountField_2 = new JTextField(String.valueOf(lastModelAdded_2));
		lastModelCountField_2.setEditable(false);

		varChoiceY_2 = new JComboBox();
		varChoiceY_2.addActionListener(this);

		updatePane.add(new JLabel("Models Trained:", SwingConstants.RIGHT));
 		updatePane.add(modelCountField_2);
		updatePane.add(new JLabel("Last Update:", SwingConstants.RIGHT));
 		updatePane.add(lastModelCountField_2);
		updatePane.add(new JLabel("Variable:", SwingConstants.RIGHT));
 		updatePane.add(varChoiceY_2);

 		JPanel pane0 = new JPanel(new BorderLayout());
		pane0.add("North",updatePane);
		pane0.add("Center",getConsolePanel_2());

		centerPane.add("Center",chartPaneTwo);    	
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

	private JScrollPane getConsoleTextArea_2(){
		consoleOutput_2 = new JTextArea();
		consoleOutput_2.setEditable(false);
		JScrollPane outputScrollPane = new JScrollPane(consoleOutput_2){
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

	private JPanel getConsolePanel_2(){
		JPanel pane = new JPanel(new GridLayout());
		pane.add(getConsoleTextArea_2());
		pane.setBorder(new EmptyBorder(10,10,10,10));
		return pane;
	}
	
	private JPanel getControlPanel(){
 		JPanel control = new JPanel();
		control.setBackground(getContentPane().getBackground());
		control.setLayout(new BoxLayout(control, BoxLayout.Y_AXIS));
		control.setBorder(new EmptyBorder(10, 10, 10, 10));

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

	private void setChartTwoData(double[] y){
		long[] t = new long[numElementsInGraph];
		double [] newY = new double [numElementsInGraph];

		for(int i = 0; i < numElementsInGraph; i++) {
			if(i < y.length) 
				newY[i] = y[i];
			else 
				newY[i] = Double.NaN;
		}
		
		chartTwo.setData(t, newY);
	}

	private void refreshPredActDisplay_1(){
		if(Y.getRows() == 0 || YPred.getRows() == 0){
			return;
		}
		if(Y.getRows() != YPred.getRows()){
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

	
	
	private void refreshPredActDisplay_2(){
		if(D.getRows() == 0 || DPred.getRows() == 0){
			return;
		}
		if(D.getRows() != DPred.getRows()) {
			return;
		}
		try{
			if(D.getRows() > 1000){
				if(B2==null || B2.getRows() != D.getRows()){
					B2 = Matlib.createMatrix(D.getRows(),1);
					Stats.randomSplit(D.getRows(),1000,B2);
				}
				Matlib.getRows(D,B2,temp1);
				Matlib.getRows(DPred,B2,temp2);
				Matlib.transpose(temp1,temp1);
				Matlib.transpose(temp2,temp2);
			}else{
				Matlib.transpose(D,temp1);
				Matlib.transpose(DPred,temp2);
			}
		}catch(MathException evt){
			System.err.println("Non-Fatal exception: " + evt.getMessage());
			evt.printStackTrace();
		}
		double[][] yy = Matlib.create2DArray(temp1);
		double[] y = yy[outputVariable2];

		double[][] yypp = Matlib.create2DArray(temp2);
		double[] yp = yypp[outputVariable2];
		ensembleModelPredActChart_2.setData(y, yp);
	}

	public void appendTextLine(String s, boolean first) {
		int currentPos;

		if(first) { // FIRST CHART PANE TEXT FIELD
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
		else { // SECOND CHART PANE TEXT FIELD
			int numLines_2 = consoleOutput_2.getLineCount();
			if(numLines_2 < vCache){
				consoleOutput_2.append(s);
			} else { // the console output has more than vCache lines, remove some before appending
				currentPos = consoleOutput_2.getText().indexOf('\n')+1;
				for(int i = 0; i<numLinesToKill-1; i++) {
					currentPos = consoleOutput_2.getText().indexOf('\n', currentPos)+1;
					}
			consoleOutput_2.select(0,currentPos); // modified by bbush on 8-11-98
			consoleOutput_2.cut();
			consoleOutput_2.append(s);
			consoleOutput_2.select(consoleOutput_2.getText().length(), consoleOutput_2.getText().length());
			}
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
		
		if(stateModelTrainingThread != null) {
			if(!stateModelTrainingThread.isAlive()) {
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
			if(withTwoModels && stateModelTrainingThread != null)
				stateModelTrainingThread.interrupt();
			stopButton.setEnabled(false);	
			if(onlineProcessor != null){
				onlineProcessor.completeTraining();
			}else{
				onlineOptimizer.uncompleteTraining();
			}

			return true;
		} else {
			return false;
		}
	}

	public void setStateModelTrainingThread(Thread t){
		stateModelTrainingThread = t;
	}

	public void setOutputModelTrainingThread(Thread t){
		outputModelTrainingThread = t;
	}

	public void setReady(boolean runningInOne){
		if(runningInOne) {
			stopButton.setEnabled(false);
		} else {
			stopButton.setEnabled(true);
		}
	}

	public void setOneModelMode(boolean b){
		oneSubModel = b;
	}

	public void setModel(INolModel2 m) {
		theModel = m;
		if((theModel instanceof NolOptimizeModel) && (((NolOptimizeModel)theModel).getStateModel()!=null)) {
			withTwoModels = true;
			modelViewTabbedPane.addTab("State Model", chartPaneTwoHolder);    // add the State Model tabbed pane
			modelViewTabbedPane.setSelectedIndex(0); // select the Output Model tab
		}else {
			withTwoModels = false;
			if(modelViewTabbedPane.getTabCount() == 2) {
				modelViewTabbedPane.removeTabAt(1); // remove the State Model tab
				modelViewTabbedPane.setSelectedIndex(0); // select the Output Model tab
			}
		}

		Vector outs = theModel.getOutputs();
		int numOut_1 = outs.size();
		varChoiceY_1.removeAllItems();
		for(int j=0; j < numOut_1; j++){
			String name = outs.elementAt(j).toString();
			varChoiceY_1.addItem(name);			
		}
		noFire = true;
		varChoiceY_1.setSelectedIndex(0);
		noFire = false;

		if(withTwoModels) {
			Vector states = ((NolOptimizeModel)theModel).getState();
			if(states.isEmpty()) 
				return;
			// set Y in varChoiceY for State Model Pane
			int numOut_2 = states.size();
			varChoiceY_2.removeAllItems();
			for(int j=0; j < numOut_2; j++){
				String name = states.elementAt(j).toString();
				varChoiceY_2.addItem(name);			
			}
			noFire = true;
			varChoiceY_2.setSelectedIndex(0);
			noFire = false;
		}
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
	}

	public void setModel2TrainInput(Matrix M){
		if(I != null)
			Matlib.clear(I);
		I = M;
	}
	public void setModel2TrainOutput(Matrix M){
		if(D != null)
			Matlib.clear(D);
		D = M;
	}

	
    @Override
	public void modelTrained(EnsembleModelEvent e) {
		//System.out.println("with two models = " + withTwoModels);
		if(withTwoModels) {
			EnsembleModel ensemble = e.getEnsembleModel();
			if(ensemble.equals(theModel.getModel())) { // the event came from the Output Model
				//System.out.println("output model");
				numModelsTrained_1++;
				modelCountField_1.setText(String.valueOf(numModelsTrained_1));
			} else { // the event came from the State Model
				if(neverPopUpStateModelPane){
					modelViewTabbedPane.setSelectedIndex(1); // select the State Model tab				
					neverPopUpStateModelPane = false;
				}
				numModelsTrained_2++;
				modelCountField_2.setText(String.valueOf(numModelsTrained_2));
			}
		}else {
			numModelsTrained_1++;
			modelCountField_1.setText(String.valueOf(numModelsTrained_1));
		}
	}


	@Override
	public synchronized void modelAdded(EnsembleModelEvent e) {
		EnsembleModel ensemble = e.getEnsembleModel();
		double mpe = ensemble.getMeanPredictionError();
		if(ensemble.equals(theModel.getModel())) { // the event came from the Output Model
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
			//System.out.println("X.getCols() = " + X.getCols());
			try {
				ensemble.evaluate(X,YPred);
			} catch (MathException me) {
				System.err.println("Non-Fatal exception: "+ me.getMessage());
				me.printStackTrace();
			}			
			lastModelAdded_1 = numModelsTrained_1; // added by bbush 8-11-98
			lastModelCountField_1.setText(String.valueOf(lastModelAdded_1));

			setChartOneData(essembleTmes_1);

			refreshPredActDisplay_1();
			String s = "Ensemble model mean squared error: "+mpe +"\n";
			appendTextLine(s, true); // add string s to console

		}
		if(withTwoModels){ // with two models
			if(!ensemble.equals(theModel.getModel())) {
				if(neverPopUpStateModelPane){
					modelViewTabbedPane.setSelectedIndex(1); // select the State Model tab				
					neverPopUpStateModelPane = false;
				}
				if(essembleTmes_2 == null){
					essembleTmes_2 = new double[2];
					essembleTmes_2[0] = mpe;
					essembleTmes_2[1] = mpe;
				}else{
					double[] tmes = essembleTmes_2;
					if(essembleTmes_2.length >= numElementsInGraph-1) {  
						// added by bbush on 8-10-98 to roll buffer, FIFO
						essembleTmes_2 = new double[tmes.length]; 
						for(int i = 1; i < tmes.length; i++) // save current array, except for 1st element [i] -> [i-1]
							essembleTmes_2[i-1] = tmes[i];
						essembleTmes_2[tmes.length-1] = mpe;
						tmes = null;
					}else {
						essembleTmes_2 = new double[tmes.length+1];
						for(int i = 0;i < tmes.length; i++) // save current array, all elements
							essembleTmes_2[i] = tmes[i];
						essembleTmes_2[tmes.length] = mpe;
						tmes = null;
					}
				}
				//System.out.println("I.getCols() = " + I.getCols());
				try {
					ensemble.evaluate(I,DPred);
				} catch (MathException me) {
					System.err.println("Non-Fatal exception: "+ me.getMessage());
					me.printStackTrace();
				}			
				lastModelAdded_2 = numModelsTrained_2; // added by bbush, 9-18-98
				lastModelCountField_2.setText(String.valueOf(lastModelAdded_2));
				String s = "Ensemble model mean squared error: "+mpe +"\n";
				appendTextLine(s, false); // add string s to console
				
				setChartTwoData(essembleTmes_2);
				chartTwo.validate();
				chartTwo.repaint(0l);
				refreshPredActDisplay_2();
				theModel.setIsTrained(true);
			}
		}else{
			theModel.setIsTrained(true);
		}
	}
	
	@Override
	public void modelRemoved(EnsembleModelEvent e){}
	@Override
	public void trainingComplete(EnsembleModelEvent e){
		EnsembleModel ensemble = e.getEnsembleModel();
		TrainableModel model = (TrainableModel)e.getModel();
		if(withTwoModels){ 
			if(oneSubModel){
				stopButton.setEnabled(false);
				String[] buttonLabels = {"OK"};
				NolConfirmDialog confirmDialog = new NolConfirmDialog(this,"Information",buttonLabels,"Finished training "+theModel.getName()+" !", "info.gif");
				confirmDialog.setFocus(1);
				confirmDialog.setVisible(true);
			}else{
				if(!ensemble.equals(theModel.getModel())) {
					stopButton.setEnabled(false);
					String[] buttonLabels = {"OK"};
					NolConfirmDialog confirmDialog = new NolConfirmDialog(this,"Information",buttonLabels,"Finished training "+theModel.getName()+" !", "info.gif");
					confirmDialog.setFocus(1);
					confirmDialog.setVisible(true);
				}
			}
		}else{
			stopButton.setEnabled(false);
			String[] buttonLabels = {"OK"};
			NolConfirmDialog confirmDialog = new NolConfirmDialog(this,"Information",buttonLabels,"Finished training "+theModel.getName()+" !", "info.gif");
			confirmDialog.setFocus(1);
			confirmDialog.setVisible(true);
		}
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		if(noFire){
			return;		
		}
		if (e.getSource().equals(stopButton)){
			outputModelTrainingThread.interrupt();
			if(withTwoModels && stateModelTrainingThread != null)
				stateModelTrainingThread.interrupt();
			if(onlineProcessor != null){
				onlineProcessor.completeTraining();
			}else{
				onlineOptimizer.uncompleteTraining();
			}
			stopButton.setEnabled(false);
		}else if(e.getSource().equals(varChoiceY_1)) { 
			int index = varChoiceY_1.getSelectedIndex();
			outputVariable1 = index;
			refreshPredActDisplay_1();
			chartOne.validate();
			chartOne.repaint(0l);
		}else if(e.getSource().equals(varChoiceY_2)) { 
			outputVariable2 = varChoiceY_2.getSelectedIndex();
			refreshPredActDisplay_2();
			chartTwo.validate();
			chartTwo.repaint(0l);
		}
	}

	/**
     * ScatChart implementation
     */
    class ScatChart extends Object{
		private ScatterChart chart;
		ScatChart(boolean connectors, Color back){
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

