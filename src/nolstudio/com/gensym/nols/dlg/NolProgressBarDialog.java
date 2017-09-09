package com.gensym.nols.dlg;

import java.awt.*;
import java.awt.event.*;
import java.net.*;

import javax.swing.*;

import com.gensym.nols.main.NolMainFrame;

/**
  *
  * NolProgressBarDialog
  * @author Brian O. Bush
  * @version  1.0 September 8, 1998
  *
  **/

public class NolProgressBarDialog extends JDialog implements ProgressListener {
	private JFrame parent;
	private	JPanel workSpace;
    //private JLabel label;
	private JPanel controlPane;
	private JButton cancelButton;
	private JProgressBar progressBar;
	private boolean isCancel;
	private ButtonAction buttonListener;
	private Font labelFont = new Font("Dialog", Font.BOLD, 14);
	private Thread processThread;
	private String theLabel;
	private int currentProgressValue;
	private int maximumProgressValue;
	private boolean DEBUG = true;

    public static final int INITIAL_WIDTH = 400;
    public static final int INITIAL_HEIGHT = 200;

    private static final String CANCEL_BUTTON_LABEL = "CancelButtonLabel";

	public NolProgressBarDialog(JFrame dw, String title, String labelText, int max) {
		super(dw, title, false);
        this.workSpace = new JPanel();
        parent = dw;	 
		theLabel = labelText;
		isCancel = false;

		// progress bar specific
		currentProgressValue = 0;
		maximumProgressValue = max;

		buttonListener = new ButtonAction();
		initializeLayout();

	}


	private void initializeLayout() {
		
		JPanel progressPanel = new JPanel();
		progressPanel.setLayout(new BoxLayout(progressPanel, BoxLayout.Y_AXIS));

//		Dimension d = new Dimension(100, 20);
		JLabel progressLabel = new JLabel(theLabel);
		progressLabel.setAlignmentX(CENTER_ALIGNMENT);
		URL url = this.getClass().getResource("info.gif");
		ImageIcon butIcon = new ImageIcon(url);
        progressLabel.setIcon(butIcon);
//		progressLabel.setMaximumSize(d);
//		progressLabel.setPreferredSize(d);

		progressBar = new JProgressBar();
		progressLabel.setLabelFor(progressBar);
		progressBar.setAlignmentX(CENTER_ALIGNMENT);
		progressBar.setMinimum(0);
		progressBar.setMaximum(maximumProgressValue);
		progressBar.setValue(0);
//		progressBar.getAccessibleContext().setAccessibleName("Calculating delay ratings");

		progressPanel.add(progressLabel);
		progressPanel.add(Box.createRigidArea(new Dimension(1,20)));
		progressPanel.add(progressBar);

        workSpace.add(progressPanel);
		workSpace.setSize(400,200);
		controlPane = new JPanel();
    
		cancelButton = new JButton(((NolMainFrame)parent).getNolResourceString(CANCEL_BUTTON_LABEL));
		controlPane.add(cancelButton);

		getContentPane().setLayout(new BorderLayout());
//		getContentPane().add("North", label);
		getContentPane().add("Center", workSpace);
		getContentPane().add("South", controlPane);

		// add listener to cancel button
		cancelButton.addActionListener(buttonListener);

        //Initialize this dialog to its preferred size.
        pack();
	}

	public void setThread(Thread t) {
		processThread = t;
	}

	public boolean isCancel(){
		Toolkit.getDefaultToolkit().beep();
		return this.isCancel;
	}

	@Override
	public void valueChanged(ProgressEvent e) {  // change to progressPerformed
		progressBar.setValue(++currentProgressValue);
	//	System.out.println("calculationPerformed Event");
	}

    class ButtonAction extends AbstractAction {

		ButtonAction() {
			super("title");
		}

        @Override
		public void actionPerformed(ActionEvent event) {
			if(event.getSource().equals(cancelButton)){
				isCancel = true;
				processThread.interrupt();
				if(parent!=null && parent instanceof NolMainFrame) {
					NolMainFrame frame = (NolMainFrame) parent;
//					frame.setWaitCursor(false);
				}
				dispose();
			}
		}
    }

}