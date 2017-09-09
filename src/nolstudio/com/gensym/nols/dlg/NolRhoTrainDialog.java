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

public class NolRhoTrainDialog extends JDialog{
	private NolMainFrame frame;
	private NolRhoModel model;
	private ControlAction actionListener;
	private JPanel cenPane;

	private JButton trainButton;
	private JCheckBox scaleCheckBox;
	private NolClassicConsoleFrame consoleFrame;
	private boolean nofire = false;

	private Matrix X;
	private Matrix Y;
	
	private JRadioButton but1;
	private JRadioButton but2;
	
    private static final String  TRAIN= "TrainDialog_Train";
    private static final String  CANCEL= "CancelButtonLabel";
    private static final String NODATAFORTRAINING = "TrainDialog_NoDataForTraining";
    private static final String INFO= "RbfnTrainDialog_Info";

	public NolRhoTrainDialog(JFrame dw, String title) {
		super(dw, title, true);
        frame = (NolMainFrame)dw;
		actionListener = new ControlAction();
		initializeLayout();
	}
	
	public NolRhoTrainDialog(JFrame dw, String title,  NolRhoModel model) {
		this(dw,title);
		this.model = model;
		setTitle("Train a Model: "+model.getName());
	}

	public void setRhoModel(NolRhoModel model) {
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
		
		JPanel methodPane = new JPanel(new GridLayout(2,1,10,10));
		methodPane.setBorder(new TitledBorder("Treatment of Output Data:"));               
		ButtonGroup group = new ButtonGroup();
		but1 = new JRadioButton("Treat Data as Single Class");
		but2 = new JRadioButton("Treat Output as Class Labels");
		but2.setSelected(true);
		group.add(but1);
		group.add(but2);
		methodPane.add(but1);
		methodPane.add(but2);

		JPanel scalePane = new JPanel(new GridLayout(1,1,10,10));
 		scalePane.setBorder(new EmptyBorder(10,10,10,10));
		scaleCheckBox = new JCheckBox("Normalize the data series?");
		scaleCheckBox.setSelected(true);
		scalePane.add(scaleCheckBox);
		
		genPane.add("North",infoPane);
		genPane.add("Center",methodPane);
		genPane.add("East",getControlPane());
		genPane.add("South",scalePane);
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

		int method = 0;
		if(but2.isSelected()){
			method = 1;
		}
		model.setRunningParameter(method);
		try{
			model.setNormalizeData(scaleCheckBox.isSelected());
			model.prepareTrainingSet(X, Y);
		}catch (MathException evt){
			System.err.println("Non-Fatal exception: " + evt.getMessage());
			evt.printStackTrace();	
		}

		if(X.getRows() <10){
			frame.showOKDialog(frame.getNolResourceString(NODATAFORTRAINING));
			return false;
		}
		consoleFrame.setModel1TrainInput(X);
		consoleFrame.setModel1TrainOutput(Y);
		consoleFrame.setModel(model);

		NolClassicModelTrainer modelTrainer = new NolClassicModelTrainer(model);
		modelTrainer.addListener(consoleFrame);
		modelTrainer.setInput(X);
		modelTrainer.setOutput(Y);

		Thread trainingthread = new Thread(modelTrainer);
		consoleFrame.setOutputModelTrainingThread(trainingthread);
		int prior = trainingthread.getPriority()-3;
		if(prior <Thread.MIN_PRIORITY){
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
			if(nofire) {
				return;
			}
			String command = e.getActionCommand();
			if(command.equals("Train ")){
				buildModel();
				setVisible(false);				
			}else if(command.equals("Cancel")){
				setVisible(false);
			}
 		}
    }
}

