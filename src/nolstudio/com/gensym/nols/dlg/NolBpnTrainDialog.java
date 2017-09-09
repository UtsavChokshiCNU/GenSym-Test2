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

public class NolBpnTrainDialog extends JDialog{
	private NolMainFrame frame;
	private NolBpnModel model;
	private ControlAction actionListener;
	private JPanel cenPane;
	private JTextField iterationField;

	private JButton trainButton;
	private JCheckBox pcaCheckBox;
	private NolClassicConsoleFrame consoleFrame;
	private boolean nofire = false;

	private Matrix X;
	private Matrix Y;
	
	private static final String OUTPUTMODEL = "TrainDialog_OutputModel";
    private static final String STATEMODEL = "TrainDialog_StateModel";
    private static final String INFO= "BpnTrainDialog_Info";
    private static final String  MAXTIME= "TrainDialog_MaxTime";
    private static final String  ONEMIN= "TrainDialog_1min";
    private static final String  FIVEMIN= "TrainDialog_5min";
    private static final String  THIRTYMIN= "TrainDialog_30min";
    private static final String  OTHERMIN= "TrainDialog_OtherMin";
    private static final String  AUTOMATICSTOP= "TrainDialog_AutomaticStop";
    private static final String  MODELNAME= "TrainDialog_ModelName";

    private static final String  TRAIN= "TrainDialog_Train";
    private static final String  CANCEL= "CancelButtonLabel";

    
	private static final String ERRORINTIME = "TrainDialog_ErrorInTime";
    private static final String NODATAFORTRAINING = "TrainDialog_NoDataForTraining";

	private JRadioButton but1;
	private JRadioButton but2;
	private JRadioButton but3;
	private JRadioButton but4;
	
	public NolBpnTrainDialog(JFrame dw, String title) {
		super(dw, title, true);
        frame = (NolMainFrame)dw;
		actionListener = new ControlAction();
		initializeLayout();
	}
	
	public NolBpnTrainDialog(JFrame dw, String title,  NolBpnModel model) {
		this(dw,title);
		this.model = model;
		setTitle("Train a Model: "+model.getName());
	}

	public void setBpnModel(NolBpnModel model) {
		this.model = model;
		setTitle("Train a Model: "+model.getName());
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
		
		JPanel numberPane = new JPanel(new GridLayout(1,2,10,10));
		numberPane.add(new JLabel("Maximum iterations:"));
		iterationField = new JTextField("400");
		numberPane.add(iterationField);

		JPanel methodPane = new JPanel(new GridLayout(4,1,10,10));
		methodPane.setBorder(new TitledBorder("Training Method:"));               
		ButtonGroup group = new ButtonGroup();
		but1 = new JRadioButton("Conjugate Gradients(Polak-Ribiere)");
		but2 = new JRadioButton("Conjugate Gradients(Fletcher-Reeves)");
		but3 = new JRadioButton("Second Order(BFGS)");
		but3.setSelected(true);
		but4 = new JRadioButton("Second Order(DFP)");
		group.add(but1);
		group.add(but2);
		group.add(but3);
		group.add(but4);
		methodPane.add(but1);
		methodPane.add(but2);
		methodPane.add(but3);
		methodPane.add(but4);

		JPanel pcaPane = new JPanel();
		pcaPane.add(new JLabel("Accelerate Training by Input Projection?"));
		pcaCheckBox = new JCheckBox();
		pcaPane.add(pcaCheckBox);

		cenPane = new JPanel(new BorderLayout());
		cenPane.setBorder(new EmptyBorder(10,50,10,10));

		cenPane.add("North",numberPane);
		cenPane.add("Center",methodPane);
		cenPane.add("South",pcaPane);


		genPane.add("North",infoPane);
		genPane.add("Center",cenPane);
		genPane.add("East",getControlPane());
		setContentPane(genPane);
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
		Project2 project = frame.getProject();
		consoleFrame = new NolClassicConsoleFrame(project, frame);
		consoleFrame.setBounds(100,100,750,500);
		Matlib.pack() ;
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
			return false;
		}
		int iterations = Integer.valueOf(iterationField.getText()).intValue();
		int method = 2;
		if(but2.isSelected()){
			method = 1;
		}else if(but3.isSelected()){
			method = 3;
		}else if(but4.isSelected()){
			method = 4;
		}
		int pcaFlag = 0;
		if(pcaCheckBox.isSelected()) {
			pcaFlag = 1;
		}

		consoleFrame.setModel1TrainInput(X);
		consoleFrame.setModel1TrainOutput(Y);
		consoleFrame.setModel(model);

		NolClassicModelTrainer modelTrainer = new NolClassicModelTrainer(model);
		modelTrainer.addListener(consoleFrame);
		modelTrainer.setInput(X);
		modelTrainer.setOutput(Y);
		model.setRunningParameter(iterations,method,pcaFlag);

//System.out.println("iterations="+iterations+" method="+method+ " pcaflag="+pcaFlag);
		
		Thread trainingthread = new Thread(modelTrainer);
		consoleFrame.setOutputModelTrainingThread(trainingthread);
		int prior = trainingthread.getPriority()-3;
		if(prior <Thread.MIN_PRIORITY) {
			prior = Thread.MIN_PRIORITY;
		}
		trainingthread.setPriority(prior);
		trainingthread.start();
		return true;
	}

    class ControlAction extends AbstractAction {
		ControlAction() {			super("title");		}

        @Override
		public void actionPerformed(ActionEvent e) {
			if(nofire){
				return;
			}
			String command = e.getActionCommand();
			if(command.equals("Train ")){
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

