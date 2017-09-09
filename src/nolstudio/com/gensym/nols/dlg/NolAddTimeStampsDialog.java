package com.gensym.nols.dlg;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.net.URL;
import java.text.*;

import javax.swing.text.*;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.border.*;

import com.gensym.nols.main.NolMainFrame;

public class NolAddTimeStampsDialog extends JDialog {
    protected static final String OK_BUTTON_LABEL = "OkButtonLabel";
    protected static final String CANCEL_BUTTON_LABEL = "CancelButtonLabel";
	protected static final String START_TIME_LABEL = "AddTimeStampsDialog_StartTimeLabel";
	protected static final String INTERVAL_LABEL = "AddTimeStampsDialog_IntervalLabel";

	protected static final String SECOND_LABEL = "SecondLabel";
	protected static final String MINUTE_LABEL = "MinuteLabel";
	protected static final String HOUR_LABEL = "HourLabel";
	protected static final String DAY_LABEL = "DayLabel";

	private JFrame frame;
	private JTextField startTime;
	private JTextField interval;
	private JComboBox intervalUnit;
	private boolean isOk;
	private ControlAction actionListener;
	private SimpleDateFormat dateTimeFormat;
	private long startTimeValue;
	private long intervalValue;

	public NolAddTimeStampsDialog (JFrame dw, String title) {
		super(dw, title, true);
		frame = dw ;
		dateTimeFormat = new SimpleDateFormat("MM/dd/yyyy H:mm:s");
		JPanel workSpace = new JPanel();
		setContentPane(workSpace);    
		workSpace.setLayout(new BorderLayout());
		actionListener = new ControlAction();

		JPanel dataPane = new JPanel(new BorderLayout());
		dataPane.setBorder(new EmptyBorder(10,10,10,10));

		JPanel labelPane = new JPanel(new GridLayout(2,1,10,10));
		labelPane.add(new JLabel(((NolMainFrame)frame).getNolResourceString(START_TIME_LABEL)  + ":"));
		labelPane.add(new JLabel(((NolMainFrame)frame).getNolResourceString(INTERVAL_LABEL) + ":"));

		JPanel valuePane = new JPanel(new GridLayout(2,1,10,10));
		valuePane.setBorder(new EmptyBorder(0,5,0,5));
		startTime = new JTextField();
		startTime.setEditable(false);
		valuePane.add(startTime);
		interval = new JTextField();
		valuePane.add(interval);

		JPanel setPane = new JPanel(new GridLayout(2,1,10,10));
		URL url = this.getClass().getResource("pointer.gif");
		JButton timeSet = new JButton(new ImageIcon(url));
		timeSet.setActionCommand("timeFrom");
		timeSet.addActionListener(actionListener);
		JPanel butPane = new JPanel(new GridLayout());
		butPane.setBorder(new EmptyBorder(0,0,0,40));
		butPane.add(timeSet);
		setPane.add(butPane);
		intervalUnit = new JComboBox();
		setPane.add(intervalUnit);

		dataPane.add("West",labelPane);
		dataPane.add("Center",valuePane);
		dataPane.add("East",setPane);

		JPanel control = new JPanel();
		JButton okButton = new JButton(((NolMainFrame)frame).getNolResourceString(OK_BUTTON_LABEL));
		okButton.setActionCommand("OK");
		okButton.addActionListener(actionListener);
		control.add(okButton);
		JButton cancelButton = new JButton(((NolMainFrame)frame).getNolResourceString(CANCEL_BUTTON_LABEL));
		cancelButton.setActionCommand("Cancel");
		cancelButton.addActionListener(actionListener);
		control.add(cancelButton);
		workSpace.add("Center",dataPane);
		workSpace.add("South",control);
		initializeChoice();
		pack();

	}

	private void initializeChoice(){
		intervalUnit.addItem(((NolMainFrame)frame).getNolResourceString(SECOND_LABEL));
		intervalUnit.addItem(((NolMainFrame)frame).getNolResourceString(MINUTE_LABEL));
		intervalUnit.addItem(((NolMainFrame)frame).getNolResourceString(HOUR_LABEL));
		intervalUnit.addItem(((NolMainFrame)frame).getNolResourceString(DAY_LABEL));
		intervalUnit.setSelectedItem(((NolMainFrame)frame).getNolResourceString(MINUTE_LABEL));
	}


	public boolean getResult(){
		return this.isOk;
	}

	public long[] getTimeStampsParameters() throws NumberFormatException{
		long[] tp = new long[2];
		tp[0] = startTimeValue;
		String intStr = interval.getText();
		double intervalDouble = new Double(intStr).doubleValue();
		int unit = intervalUnit.getSelectedIndex();
		if(unit == 0)
			intervalDouble = intervalDouble * 1000;
		else if(unit == 1)
			intervalDouble = intervalDouble * 60000;
		else if(unit == 2)
			intervalDouble = intervalDouble * 3600000;
		else if(unit == 3)
			intervalDouble = intervalDouble * 86400000;
		intervalValue  = (long)intervalDouble; 
		tp[1] = intervalValue;
		return tp;
	}

    /**
     * Control action implementation
     */
    class ControlAction extends AbstractAction {

		ControlAction() {super("controlAction");}

        @Override
		public void actionPerformed(ActionEvent e) {
			String command = e.getActionCommand();
			if(command.equals("OK")){
				isOk = true;
				NolAddTimeStampsDialog.this.dispose();
			}else if(command.equals("Cancel")){
				isOk = false;
				NolAddTimeStampsDialog.this.dispose();
			}else if(command.equals("timeFrom")){
				NolTimeInputDialog ch = new NolTimeInputDialog (frame, 
					"Choose Date and Time");
				ch.setBounds(200,100,300,230);
				ch.setVisible(true);
				if(ch.getResult()){
					startTimeValue = ch.getTime();
					startTime.setText(dateTimeFormat.format(new Date(startTimeValue)));				
				}
			}
		}
    }

}

