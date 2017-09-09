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
import com.gensym.nols.data.*;

public class NolResamplingDialog extends JDialog {
	private static final String SAMPLE_LABEL = "NolResamplingDialog_SampleLabel";

	private JFrame frame;

	private boolean isOk;
	private ControlAction actionListener;
	private SimpleDateFormat dateTimeFormat;

	private JTextField oldStartTime ;
	private JTextField oldEndTime ;
	private JTextField newStartTime ;
	private JTextField newEndTime ;
	private JTextField newIntervalTime;
	private Vector resamplers;
	private Preprocessor preprocessor;

	private long endTimeValue;
	private long startTimeValue;
	private long intervalValue;

	private DataSeries dataSeries;

	public NolResamplingDialog (JFrame dw, String title,DataSeries ds) {
		super(dw, title, true);
		frame = dw ;
		dateTimeFormat = new SimpleDateFormat("MM/dd/yyyy H:mm:s");
		actionListener = new ControlAction();
		setContentPane(getResamplePane());    
		dataSeries = ds;
		refreshResamplePanel();
		pack();
	}

	private JPanel getResamplePane(){
		JPanel resamplePane = new JPanel(new BorderLayout());
		JPanel infoPane = new JPanel(new GridLayout());
 		infoPane.setBorder(new EmptyBorder(10,10,10,10));
		String s = ((NolMainFrame)frame).getNolResourceString(SAMPLE_LABEL);
		JTextArea infoLabel = new JTextArea(s);
		infoLabel.setEditable(false);
		infoLabel.setLineWrap(true);
		infoLabel.setWrapStyleWord(true);
		infoLabel.setBackground(infoPane.getBackground());
		infoPane.add(infoLabel);
		resamplePane.add("North",infoPane);

		JPanel selectPane = new JPanel(new GridLayout(5,2,5,5));
 		selectPane.setBorder(new EmptyBorder(10,10,10,10));
		
		selectPane.add(new JLabel("Existing start time:"));
		oldStartTime = new JTextField();
		selectPane.add(oldStartTime);
		
		selectPane.add(new JLabel("Existing end time:"));
		oldEndTime = new JTextField();
		selectPane.add(oldEndTime);

		selectPane.add(new JLabel("New start time:"));
		
		JPanel timePane = new JPanel(new BorderLayout());
		URL url = this.getClass().getResource("pointer.gif");
		JButton timeSet = new JButton(new ImageIcon(url));
		timeSet.setActionCommand("timeFrom");
		timeSet.addActionListener(actionListener);

		newStartTime = new JTextField();
		timePane.add("Center",newStartTime);
		timePane.add("East",timeSet);
		selectPane.add(timePane);

		selectPane.add(new JLabel("New end time:"));

		timePane = new JPanel(new BorderLayout());
		timeSet = new JButton(new ImageIcon(url));
		timeSet.setActionCommand("timeEnd");
		timeSet.addActionListener(actionListener);
		newEndTime = new JTextField();
		timePane.add("Center",newEndTime);
		timePane.add("East",timeSet);
		selectPane.add(timePane);

		selectPane.add(new JLabel("New interval (Second):"));
		newIntervalTime = new JTextField();
		selectPane.add(newIntervalTime);

		resamplePane.add("Center",selectPane);


		JPanel control = new JPanel();
		JButton okButton = new JButton(((NolMainFrame)frame).getNolResourceString("OkButtonLabel"));
		okButton.setActionCommand("OK");
		okButton.addActionListener(actionListener);
		control.add(okButton);
		JButton cancelButton = new JButton(((NolMainFrame)frame).getNolResourceString("CancelButtonLabel"));
		cancelButton.setActionCommand("Cancel");
		cancelButton.addActionListener(actionListener);
		control.add(cancelButton);
		resamplePane.add("South",control);
		
		return resamplePane;
	}

	private void refreshResamplePanel(){
		long[] ts = dataSeries.getTimeStamps();
		SimpleDateFormat fmt = new SimpleDateFormat("M/d/y H:m:s");
		oldStartTime.setText(fmt.format(new Date(ts[0])));
		oldEndTime.setText(fmt.format(new Date(ts[ts.length-1])));
		newStartTime.setText(fmt.format(new Date(ts[0])));
		newEndTime.setText(fmt.format(new Date(ts[ts.length-1])));
		startTimeValue = ts[0]; 
		endTimeValue = ts[ts.length-1];
		long interval = 0;
		if (ts.length > 1) {
			interval = (endTimeValue - startTimeValue) / (ts.length -1) /1000;
		}
		newIntervalTime.setText(""+interval);
	}

	public boolean getResult(){
		return this.isOk;
	}
	public String getNewStartTimeString(){
		return newStartTime.getText();
	}
	public String getNewEndTimeString(){
		return newEndTime.getText();
	}
	public String getNewIntervalTimeString(){
		return newIntervalTime.getText();
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
				NolResamplingDialog.this.dispose();
			}else if(command.equals("Cancel")){
				isOk = false;
				NolResamplingDialog.this.dispose();
			}else if(command.equals("timeFrom")){
				NolTimeInputDialog ch = new NolTimeInputDialog (frame, 
					"Choose Date and Time");
				ch.setBounds(200,100,300,230);
				ch.setTime(startTimeValue);
				ch.setVisible(true);
				if(ch.getResult()){
					startTimeValue = ch.getTime();
					newStartTime.setText(dateTimeFormat.format(new Date(startTimeValue)));				
				}
			}else if(command.equals("timeEnd")){
				NolTimeInputDialog ch = new NolTimeInputDialog (frame, 
					"Choose Date and Time");
				ch.setBounds(200,100,300,230);
				ch.setTime(endTimeValue);
				ch.setVisible(true);
				if(ch.getResult()){
					endTimeValue = ch.getTime();
					newEndTime.setText(dateTimeFormat.format(new Date(startTimeValue)));				
				}
			}
		}
    }

}

