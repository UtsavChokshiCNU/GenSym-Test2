package com.gensym.nols.dlg;

import java.awt.*;
import java.awt.event.*;
import java.net.URL;
import java.util.*;

import javax.swing.*;
import javax.swing.border.*;

import com.gensym.nols.main.NolMainFrame;
import com.gensym.DEBUG;

public class NolWizardDialog extends NolDialog {
    protected static final String CANCEL_BUTTON_LABEL = "CancelButtonLabel";
    protected static final String BACK_BUTTON_LABEL = "WizardDialog_BackLabel";
    protected static final String NEXT_BUTTON_LABEL = "WizardDialog_NextLabel";
    protected static final String FINISH_BUTTON_LABEL = "WizardDialog_FinishLabel";

	private JFrame parent;
	protected boolean isOK;
	protected JButton cancelButton;
	protected JButton backButton;
	protected JButton nextButton;
	protected JButton finishButton;
	protected JButton helpButton;
	protected int stepCount;
	protected int currentStep;
	protected Vector stepPanes;
	protected JPanel stepPane;
	protected boolean enableNext;
	protected boolean enableFinish;

	private ControlAction actionListener;

	public NolWizardDialog (JFrame dw, String title, boolean modal, int steps) {
		super(dw, title, modal);
		parent = dw;
		actionListener = new ControlAction();	
		isOK = false;
		enableNext = true;
		enableFinish = true;
		stepCount = steps;
		if(stepCount <1) {
			stepCount = 1;
		}
		currentStep = 1;
		initializeLayout();
	}

	private void initializeLayout(){
		cancelButton = new JButton(((NolMainFrame)parent).getNolResourceString(CANCEL_BUTTON_LABEL));
		backButton = new JButton(((NolMainFrame)parent).getNolResourceString(BACK_BUTTON_LABEL));
		backButton.setEnabled(false);
		nextButton = new JButton(((NolMainFrame)parent).getNolResourceString(NEXT_BUTTON_LABEL));
		finishButton = new JButton(((NolMainFrame)parent).getNolResourceString(FINISH_BUTTON_LABEL));
		cancelButton.addActionListener(actionListener);
		backButton.addActionListener(actionListener);
		nextButton.addActionListener(actionListener);
		finishButton.addActionListener(actionListener);
		URL url = this.getClass().getResource("help.gif");
		helpButton = new JButton(new ImageIcon(url));
		helpButton.addActionListener(actionListener);
		getContentPane().setLayout(new BorderLayout());

		JPanel controlPane = new JPanel(new GridLayout(1,4,5,5));
		controlPane.add(cancelButton);
		
		if(stepCount>1){
			controlPane.add(backButton);
			controlPane.add(nextButton);
		}
		controlPane.add(finishButton);

		JPanel southPane = new JPanel(new BorderLayout());
		southPane.setBorder(new EmptyBorder(10,10,10,10));
//		southPane.add("West",helpButton);
//		southPane.add("Center",new JPanel());
		southPane.add("East",controlPane);

		stepPanes = new Vector(stepCount);
		for(int i=0;i<stepCount;i++){
			JPanel pane = new JPanel();
			stepPanes.addElement(pane);
		}

		stepPane = new JPanel(new GridLayout());

		getContentPane().setLayout(new BorderLayout());
		getContentPane().add("South",southPane);
		getContentPane().add("Center",stepPane);
		
	}

	public void setButtonFocus(){
		if(stepCount>1){
			nextButton.requestFocus();
		}else{
			if(DEBUG.debugFlag){
				System.out.println("finish focus");
			}
			finishButton.requestFocus();
		}
	}

	protected String setTitleForStep(int step){
		String s = "Step "+currentStep+" of " + stepCount;
		return s;
	}

	protected boolean finishAction(){
		return true;
	}

	protected void setEnableNext(boolean e){
		enableNext = e;
	}

	protected void setEnableFinish(boolean e){
		enableFinish = e;
	}


	protected void modifyStep(boolean isNext){
		if(isNext)
			currentStep++;
		else
			currentStep--;
		if(currentStep>= stepCount){
			currentStep = stepCount;
			nextButton.setEnabled(false);
			finishButton.requestFocus();
		}else{
			if(enableNext){
				nextButton.setEnabled(true);
				nextButton.requestFocus();
			} else{
				nextButton.setEnabled(false);
			}
		}
		if(enableFinish){
			finishButton.setEnabled(true);
		}else{
			finishButton.setEnabled(false);
		}

		if(currentStep <= 1){
			currentStep = 1;
			backButton.setEnabled(false);
			nextButton.requestFocus();
		}else{
			backButton.setEnabled(true);
		}

		stepPane.removeAll();
		stepPane.add((JPanel)stepPanes.elementAt(currentStep-1));
		stepPane.validate();
		stepPane.repaint(0l);
	}

	public boolean isOK(){
		return isOK;
	}

	class ControlAction extends AbstractAction {

		ControlAction() { super("controlAction");}

        @Override
		public void actionPerformed(ActionEvent e) {
			if(e.getSource().equals(cancelButton)) {
				setWaitCursor(true);
				isOK = false;
				setVisible(false);
				setWaitCursor(false);
			}else if(e.getSource().equals(backButton)) {
				setWaitCursor(true);
				modifyStep(false);
				setWaitCursor(false);
			}else if(e.getSource().equals(nextButton)) {
				setWaitCursor(true);
				modifyStep(true);
				setWaitCursor(false);
			}else if(e.getSource().equals(finishButton)) {
				setWaitCursor(true);
				isOK = finishAction();
				if(isOK) {
					setVisible(false);
				}
				setWaitCursor(false);
			}
		}
	}
}