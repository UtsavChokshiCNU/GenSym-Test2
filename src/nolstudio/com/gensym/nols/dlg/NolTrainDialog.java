package com.gensym.nols.dlg;

import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.util.*;
import java.net.*;

import javax.swing.text.*;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.border.*;

import com.gensym.math.datafit.*;
import com.gensym.math.matrix.*;
import com.gensym.math.*;
 
import com.gensym.nols.wksp.*;
import com.gensym.nols.main.*;
import com.gensym.nols.data.*;

import com.gensym.DEBUG;

public class NolTrainDialog extends JDialog implements ModelTrainerListener{
	private NolMainFrame frame;
	private NolModel2 model;
	private ControlAction actionListener;
	private JPanel autoStruct0;
	private JPanel autoStruct1;
	private JPanel autoStruct2;
	private JPanel cenPane;
	private JTextField trainTime0;
	private JTextField trainTime1;
	private JTextField trainTime2;
	private JButton trainButton;
	private JLabel modelName;
	private JPanel modelNamePane;
	private JPanel modelTabbedPane;
	private JCheckBox autoStopCheckBox0;
	private JCheckBox autoStopCheckBox1;
	private JCheckBox autoStopCheckBox2;
	private JCheckBox singlePLSCheckBox0;
	private NolConsoleFrame consoleFrame;
	private boolean nofire = false;

	private Matrix X;
	private Matrix Y;
	private Matrix I;
	private Matrix D;
	private NolModelTrainThread trainerThread;
	
	private static final String OUTPUTMODEL = "TrainDialog_OutputModel";
    private static final String STATEMODEL = "TrainDialog_StateModel";
    private static final String INFO= "TrainDialog_Info";
    public static final String  MAXTIME= "TrainDialog_MaxTime";
    private static final String  ONEMIN= "TrainDialog_1min";
    private static final String  FIVEMIN= "TrainDialog_5min";
    private static final String  THIRTYMIN= "TrainDialog_30min";
    private static final String  OTHERMIN= "TrainDialog_OtherMin";
    public static final String  AUTOMATICSTOP= "TrainDialog_AutomaticStop";
    private static final String  MODELNAME= "TrainDialog_ModelName";

    private static final String  TRAIN= "TrainDialog_Train";
    private static final String  CANCEL= "CancelButtonLabel";

    
	private static final String ERRORINTIME = "TrainDialog_ErrorInTime";
    private static final String NODATAFORTRAINING = "TrainDialog_NoDataForTraining";

    public static final String SINGLEPLSMODEL = "TrainDialog_SinglePLSModel";

	public NolTrainDialog(JFrame dw, String title) {
		super(dw, title, true);
        frame = (NolMainFrame)dw;
		actionListener = new ControlAction();
		initializeLayout();
	}
	
	public NolTrainDialog(JFrame dw, String title,  NolModel2 model) {
		this(dw,title);
		this.model = model;
	}

	public void setModel(NolModel2 model) {
		this.model = model;
		modelName.setText(model.getName());
		reinitLayout();
	}



	private void initializeLayout(){ 
		JPanel genPane = new JPanel(new BorderLayout());
		URL url = this.getClass().getResource("defaulticon.gif");
		ImageIcon importIcon = new ImageIcon(url);

		JPanel infoPane = new JPanel(new BorderLayout());
 		infoPane.setBorder(new EmptyBorder(10,10,10,10));

		String s = frame.getNolResourceString(INFO);

		JTextArea infoLabel = new JTextArea(s);
		infoLabel.setEditable(false);
		infoLabel.setLineWrap(true);
		infoLabel.setWrapStyleWord(true);
		infoLabel.setBackground(infoPane.getBackground());
		infoPane.add("Center",infoLabel);
		infoPane.add("West",new JLabel(importIcon));

													    
		autoStruct0 = new JPanel(new GridLayout(7,1,5,5));
		autoStruct0.setBorder(new TitledBorder(frame.getNolResourceString(MAXTIME)+":"));               
//		autoStruct0.setBorder(new TitledBorder("Maximum Training Time:"));               
		ButtonGroup group = new ButtonGroup();
		JRadioButton time2 = new JRadioButton(frame.getNolResourceString(ONEMIN));
//		JRadioButton time2 = new JRadioButton("Get Coffee (1 min)");
		time2.setActionCommand("Get Coffee (1 min) 0");
		time2.addActionListener(actionListener);
		group.add(time2); 
		autoStruct0.add(time2);
		JRadioButton time3 = new JRadioButton(frame.getNolResourceString(FIVEMIN));
//		JRadioButton time3 = new JRadioButton("Check Email (5 min)");
		time3.setActionCommand("Check Email (5 min) 0");
		time3.addActionListener(actionListener);
		group.add(time3); 
		autoStruct0.add(time3);
		JRadioButton time4 = new JRadioButton(frame.getNolResourceString(THIRTYMIN));
//		JRadioButton time4 = new JRadioButton("Eat Lunch (30 min)");
		time4.setActionCommand("Eat Lunch (30 min) 0");
		time4.addActionListener(actionListener);
		group.add(time4); 
		autoStruct0.add(time4);
		JRadioButton otherTime = new JRadioButton(frame.getNolResourceString(OTHERMIN));
//		JRadioButton otherTime = new JRadioButton("Other (min):");
		otherTime.setActionCommand("Other (min): 0");
		otherTime.addActionListener(actionListener);
		group.add(otherTime); 
		autoStruct0.add(otherTime);
		trainTime0 = new JTextField("1.0");
		trainTime0.setEnabled(false);
		autoStruct0.add(trainTime0);
		time2.setSelected(true);

		autoStopCheckBox0 = new JCheckBox(frame.getNolResourceString(AUTOMATICSTOP));
//		autoStopCheckBox0 = new JCheckBox("Use automatic stopping");
		autoStopCheckBox0.setSelected(true);
		autoStruct0.add(autoStopCheckBox0);



		singlePLSCheckBox0 = new JCheckBox(frame.getNolResourceString(SINGLEPLSMODEL));
		singlePLSCheckBox0.setSelected(false);
		autoStruct0.add(singlePLSCheckBox0);
		

		autoStruct1 = new JPanel(new GridLayout(6,1,5,5));
//		autoStruct1.setBorder(new TitledBorder("Maximum Training Time:"));               
		group = new ButtonGroup();
		time2 = new JRadioButton(frame.getNolResourceString(ONEMIN));
		time2.setActionCommand("Get Coffee (1 min) 1");
		time2.addActionListener(actionListener);
		group.add(time2); 
		autoStruct1.add(time2);
		time3 = new JRadioButton(frame.getNolResourceString(FIVEMIN));
		time3.setActionCommand("Check Email (5 min) 1");
		time3.addActionListener(actionListener);
		group.add(time3); 
		autoStruct1.add(time3);
		time4 = new JRadioButton(frame.getNolResourceString(THIRTYMIN));
		time4.setActionCommand("Eat Lunch (30 min) 1");
		time4.addActionListener(actionListener);
		group.add(time4); 
		autoStruct1.add(time4);
		otherTime = new JRadioButton(frame.getNolResourceString(OTHERMIN));
		otherTime.setActionCommand("Other (min): 1");
		otherTime.addActionListener(actionListener);
		group.add(otherTime); 
		autoStruct1.add(otherTime);
		trainTime1 = new JTextField("1.0");
		trainTime1.setEnabled(false);
		autoStruct1.add(trainTime1);
		time2.setSelected(true);

		autoStopCheckBox1 = new JCheckBox(frame.getNolResourceString(AUTOMATICSTOP));
		autoStopCheckBox1.setSelected(true);
		autoStruct1.add(autoStopCheckBox1);

		autoStruct2 = new JPanel(new GridLayout(6,1,5,5));
//		autoStruct2.setBorder(new TitledBorder("Maximum Training Time:"));               
		group = new ButtonGroup();
		time2 = new JRadioButton(frame.getNolResourceString(ONEMIN));
		time2.setActionCommand("Get Coffee (1 min) 2");
		time2.addActionListener(actionListener);
		group.add(time2); 
		autoStruct2.add(time2);
		time3 = new JRadioButton(frame.getNolResourceString(FIVEMIN));
		time3.setActionCommand("Check Email (5 min) 2");
		time3.addActionListener(actionListener);
		group.add(time3); 
		autoStruct2.add(time3);
		time4 = new JRadioButton(frame.getNolResourceString(THIRTYMIN));
		time4.setActionCommand("Eat Lunch (30 min) 2");
		time4.addActionListener(actionListener);
		group.add(time4); 
		autoStruct2.add(time4);
		otherTime = new JRadioButton(frame.getNolResourceString(OTHERMIN));
		otherTime.setActionCommand("Other (min): 2");
		otherTime.addActionListener(actionListener);
		group.add(otherTime); 
		autoStruct2.add(otherTime);
		trainTime2 = new JTextField("1.0");
		trainTime2.setEnabled(false);
		autoStruct2.add(trainTime2);
		time2.setSelected(true);

		autoStopCheckBox2 = new JCheckBox(frame.getNolResourceString(AUTOMATICSTOP));
		autoStopCheckBox2.setSelected(true);
		autoStruct2.add(autoStopCheckBox2);

		modelTabbedPane = new JPanel(new GridLayout());
		modelTabbedPane.setBorder(new TitledBorder("Maximum Training Time:"));               
		JTabbedPane tabbedPane = new JTabbedPane();
		tabbedPane.addTab(frame.getNolResourceString(OUTPUTMODEL), autoStruct1);
		tabbedPane.setSelectedIndex(0);
		tabbedPane.addTab(frame.getNolResourceString(STATEMODEL), autoStruct2);
		modelTabbedPane.add(tabbedPane);

		cenPane = new JPanel(new BorderLayout());
		cenPane.setBorder(new EmptyBorder(10,50,10,10));

		modelNamePane = new JPanel(new GridLayout(1,2,5,5));
		modelNamePane.setBorder(new EmptyBorder(0,0,10,0));
		modelNamePane.add(new JLabel(frame.getNolResourceString(MODELNAME)+":"));
//		modelNamePane.add(new JLabel("Model Name:"));
		modelName = new JLabel();
		modelNamePane.add(modelName);

		genPane.add("North",infoPane);
		genPane.add("Center",cenPane);
		genPane.add("East",getControlPane());
		setContentPane(genPane);
	}


	private void reinitLayout(){

		cenPane.removeAll();
		cenPane.add("North",modelNamePane);
		if(model instanceof NolOptimizeModel){
			if(((NolOptimizeModel)model).getStateModel() != null){
				cenPane.add("Center",modelTabbedPane);
			}else{
				cenPane.add("Center",autoStruct0);
			}
		}else{
			cenPane.add("Center",autoStruct0);
		}
		cenPane.repaint(0L);
		cenPane.validate();
	}

	private JPanel getControlPane(){
		JPanel control = new JPanel();
		control.setBackground(getContentPane().getBackground());
		control.setLayout(new BoxLayout(control, BoxLayout.Y_AXIS));
		control.setBorder(new EmptyBorder(10, 10, 10, 10));

		JPanel pane0 = new JPanel(new GridLayout(2,1,5,5));
		trainButton = new JButton(frame.getNolResourceString(TRAIN));
		trainButton.setActionCommand("Train ");
		trainButton.addActionListener(actionListener);
  		pane0.add(trainButton);
		JButton but = new JButton(frame.getNolResourceString(CANCEL));
		but.setActionCommand("Cancel");
		but.addActionListener(actionListener);
  		pane0.add(but);
		control.add(Box.createRigidArea(NolMainFrame.vpad15));
		control.add(pane0);
		control.add(Box.createRigidArea(NolMainFrame.vpad500));
		control.add(Box.createVerticalGlue());
		return control;
	}

	private boolean buildModel(){
		Project project = frame.getProject();
		consoleFrame = new NolConsoleFrame(project, frame, model.getName());
		consoleFrame.setBounds(100,100,750,500);
		consoleFrame.setReady(false);
		Matlib.pack() ;
		if(model instanceof NolOptimizeModel) {
			NolOptimizeModel optModel = (NolOptimizeModel) model;
			if(Y != null)
				Matlib.clear(Y);
			if(X != null)
				Matlib.clear(X);
			Y = Matlib.createMatrix();
			X = Matlib.createMatrix();
			if(D != null)
				Matlib.clear(D);
			if(I != null)
				Matlib.clear(I);
			D = Matlib.createMatrix();
			I = Matlib.createMatrix();
			try{
				model.prepareTrainingSet(X, Y);
				if(DEBUG.debugFlag){
					System.out.println("X.getCols="+X.getCols());
					System.out.println("Y.getCols="+Y.getCols());
				}
			} catch(MathException evt){
				System.err.println("Non-fatal exception preparing training data: "+evt.getMessage());
				evt.printStackTrace();
				return false;
			}

			if(X.getRows() <10){
				frame.showOKDialog(frame.getNolResourceString(NODATAFORTRAINING));
//				frame.showOKDialog("There is not enough data for training.");
				return false;
			}	
			double minutes = 30.0;
			try{
				if(optModel.getStateModel() != null){
					minutes = Double.valueOf(trainTime1.getText()).doubleValue();
				}else{
					minutes = Double.valueOf(trainTime0.getText()).doubleValue();
				}
			}catch (NumberFormatException evt){
				frame.showOKDialog(frame.getNolResourceString(ERRORINTIME));
//				frame.showOKDialog("Error in time value");
				return false;
			}

			int timeInMilli = (int)(minutes*60000.0); 
			EnsembleModel net1 = (EnsembleModel) optModel.getModel();
			net1.setTrainingTime(timeInMilli);  // convert minutes to milliseconds
			if(optModel.getStateModel() != null){
				net1.useAutomaticStopping(autoStopCheckBox1.isSelected());
			}else{
				net1.useAutomaticStopping(autoStopCheckBox0.isSelected());
			}
			net1.removeAllListeners();
			net1.addListener(consoleFrame);
			consoleFrame.setModel(model);
			consoleFrame.setModel1TrainInput(X);
			consoleFrame.setModel1TrainOutput(Y);
			if(trainerThread == null){
				trainerThread = new NolModelTrainThread(net1);
				trainerThread.addListener(this);
			}else{ 
				trainerThread.setEnsembleModel1(net1);
				trainerThread.removeListener(this);
				trainerThread.addListener(this);
			}
			trainerThread.setInput1(X);
			trainerThread.setOutput1(Y);
			
			if(optModel.getStateModel() != null){
				try{
					optModel.prepareTrainingSet2(I, D);
				} catch(MathException evt){
					System.err.println("Non-fatal exception preparing training data: "+evt.getMessage());
					evt.printStackTrace();
					return false;
				}
				if(D.getRows()<10){
					frame.showOKDialog(frame.getNolResourceString(NODATAFORTRAINING));
//					frame.showOKDialog("There is not enough data for training.");
					return false;
				}
				EnsembleModel net2 = (EnsembleModel) optModel.getStateModel();
				try{
					minutes = Double.valueOf(trainTime2.getText()).doubleValue();
				}catch (NumberFormatException evt){
//					frame.showOKDialog("Error in time value");
					frame.showOKDialog(frame.getNolResourceString(ERRORINTIME));
					return false;
				}
				timeInMilli = (int)(minutes*60000.0); 
				net2.setTrainingTime(timeInMilli);  // convert minutes to milliseconds
				net2.useAutomaticStopping(autoStopCheckBox2.isSelected());
				net2.removeAllListeners();
				net2.addListener(consoleFrame);
				consoleFrame.setModel2TrainInput(I);
				consoleFrame.setModel2TrainOutput(D);
				trainerThread.setEnsembleModel2(net2);
				trainerThread.setInput2(I);
				trainerThread.setOutput2(D);			
			}
			Thread trainingthread = new Thread(trainerThread);
			consoleFrame.setOutputModelTrainingThread(trainingthread);
			int prior = trainingthread.getPriority()-3;
			if(prior <Thread.MIN_PRIORITY) {
				prior = Thread.MIN_PRIORITY;
			}
			trainingthread.setPriority(prior);
			trainingthread.start();
		}else{			
			if(Y != null)
				Matlib.clear(Y);
			if(X != null)
				Matlib.clear(X);
			X = Matlib.createMatrix();
			Y = Matlib.createMatrix();
			try{
				model.prepareTrainingSet(X, Y);
			}catch (MathException evt){
				System.err.println("Non-Fatal exception: " + evt.getMessage());
				evt.printStackTrace();	
			}

			if(X.getRows() <10){
				frame.showOKDialog(frame.getNolResourceString(NODATAFORTRAINING));
//				frame.showOKDialog("There is not enough data for training.");
				return false;
			}

			double minutes = 30.0;
			try{
				minutes = Double.valueOf(trainTime0.getText()).doubleValue();
			} catch(NumberFormatException evt){
				frame.showOKDialog(frame.getNolResourceString(ERRORINTIME));
				return false;
			}
			
			EnsembleModel ensemble = (EnsembleModel)model.getModel();
			int timeInMilli = (int)(minutes*60000.0); 
			ensemble.setTrainingTime(timeInMilli);  // convert minutes to milliseconds
			ensemble.useAutomaticStopping(autoStopCheckBox0.isSelected());
			ensemble.setSinglePLSModel(singlePLSCheckBox0.isSelected());
			ensemble.removeAllListeners();
			ensemble.addListener(consoleFrame);
			consoleFrame.setModel(model);
			consoleFrame.setModel1TrainInput(X);
			consoleFrame.setModel1TrainOutput(Y);
			if(trainerThread == null){
				trainerThread = new NolModelTrainThread(ensemble);
				trainerThread.addListener(this);
			}else{ 
				trainerThread.setEnsembleModel1(ensemble);
				trainerThread.removeListener(this);
				trainerThread.addListener(this);
			}
			Thread trainingthread = new Thread(trainerThread);
			consoleFrame.setOutputModelTrainingThread(trainingthread);
			int prior = trainingthread.getPriority()-3;
			if(prior <Thread.MIN_PRIORITY) {
				prior = Thread.MIN_PRIORITY;
			}
			trainingthread.setPriority(prior);
			trainerThread.setInput1(X);
			trainerThread.setOutput1(Y);
			trainingthread.start();
		}
		consoleFrame.setTrainingTime(trainerThread.getEnsembleModel1().getTrainingTime());
		consoleFrame.setUseAutomaticStopping(trainerThread.getEnsembleModel1().isUseAutomaticStopping());
		consoleFrame.setSinglePLSModel(trainerThread.getEnsembleModel1().isSinglePLSModel());
		return true;
	}

	@Override
	public void trainingComplete(){
	}

    class ControlAction extends AbstractAction {
		ControlAction() {			super("title");		}

        @Override
		public void actionPerformed(ActionEvent e) {
			if(nofire) {
				return;
			}
			String command = e.getActionCommand();
			if(command.equals("Get Coffee (1 min) 1")){
				trainTime1.setText("1.0");
				trainTime1.setEnabled(false);
			}else if(command.equals("Get Coffee (1 min) 2")){
				trainTime2.setText("1.0");
				trainTime2.setEnabled(false);
			}else if(command.equals("Get Coffee (1 min) 0")){
				trainTime0.setText("1.0");
				trainTime0.setEnabled(false);
			}else if(command.equals("Check Email (5 min) 1")){
				trainTime1.setText("5.0");
				trainTime1.setEnabled(false);
			}else if(command.equals("Check Email (5 min) 2")){
				trainTime2.setText("5.0");
				trainTime2.setEnabled(false);
			}else if(command.equals("Check Email (5 min) 0")){
				trainTime0.setText("5.0");
				trainTime0.setEnabled(false);
			}else if(command.equals("Eat Lunch (30 min) 1")){
				trainTime1.setText("30.0");
				trainTime1.setEnabled(false);
			}else if(command.equals("Eat Lunch (30 min) 2")){
				trainTime2.setText("30.0");
				trainTime2.setEnabled(false);
			}else if(command.equals("Eat Lunch (30 min) 0")){
				trainTime0.setText("30.0");
				trainTime0.setEnabled(false);
			}else if(command.equals("Other (min): 1")){
				trainTime1.setEnabled(true);
			}else if(command.equals("Other (min): 2")){
				trainTime2.setEnabled(true);
			}else if(command.equals("Other (min): 0")){
				trainTime0.setEnabled(true);
			}else if(command.equals("Train ")){
				if(buildModel()){
					setVisible(false);				
					consoleFrame.setVisible(true);
					consoleFrame.toFront();	
				}else{
					setVisible(false);
				}
			}else if(command.equals("Cancel")){
				setVisible(false);
			}
 		}
    }
}

