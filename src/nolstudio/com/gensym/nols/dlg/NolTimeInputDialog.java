package com.gensym.nols.dlg;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.text.*;

import javax.swing.text.*;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.border.*;

import com.gensym.nols.main.NolMainFrame;

public class NolTimeInputDialog  extends JDialog{
    protected static final String OK_BUTTON_LABEL = "OkButtonLabel";
    protected static final String CANCEL_BUTTON_LABEL = "CancelButtonLabel";
	protected static final String TIME_SETTING_LABEL = "TimeInputDialog_TimeSettingLabel";

	protected static final String SECOND_LABEL = "SecondLabel";
	protected static final String MINUTE_LABEL = "MinuteLabel";
	protected static final String HOUR_LABEL = "HourLabel";
	protected static final String DAY_LABEL = "DayLabel";
	protected static final String MONTH_LABEL = "MonthLabel";
	protected static final String YEAR_LABEL = "YearLabel";
	
	private JFrame parent;
	private JComboBox inputYear;
	private JComboBox inputMonth;
	private JComboBox inputDay;
	private JComboBox inputHour;
	private JComboBox inputMin;
	private JComboBox inputSec;
	private JTextField timeSetting;
	private boolean isOk;
	private ControlAction actionListener;
	private long resultTime;
	private SimpleDateFormat dateTimeFormat;	

	public NolTimeInputDialog (JFrame dw, String title) {
		super(dw, title, true);
		parent = dw;
		JPanel workSpace = new JPanel();
		setContentPane(workSpace);    
		workSpace.setLayout(new BorderLayout());
		actionListener = new ControlAction();

		JPanel dataPane = new JPanel(new GridLayout(3,3,20,20));
		dataPane.setBorder(BorderFactory.createTitledBorder(""));

		JPanel pane = new JPanel(new GridLayout());
		pane.setBorder(new TitledBorder(new EmptyBorder(1, 1, 1, 1),               
				((NolMainFrame)parent).getNolResourceString(YEAR_LABEL) + ":", TitledBorder.LEFT , TitledBorder.TOP));
		inputYear =  new JComboBox();
		pane.add(inputYear);
		dataPane.add(pane);

		pane = new JPanel(new GridLayout());
		pane.setBorder(new TitledBorder(new EmptyBorder(1, 1, 1, 1),               
				((NolMainFrame)parent).getNolResourceString(MONTH_LABEL) + ":", TitledBorder.LEFT , TitledBorder.TOP));
		inputMonth =  new JComboBox();
		pane.add(inputMonth);
		dataPane.add(pane);

		pane = new JPanel(new GridLayout());
		pane.setBorder(new TitledBorder(new EmptyBorder(1, 1, 1, 1),               
				((NolMainFrame)parent).getNolResourceString(DAY_LABEL) + ":", TitledBorder.LEFT , TitledBorder.TOP));
		inputDay =  new JComboBox();
		pane.add(inputDay);
		dataPane.add(pane);

		pane = new JPanel(new GridLayout());
		pane.setBorder(new TitledBorder(new EmptyBorder(1, 1, 1, 1),               
			((NolMainFrame)parent).getNolResourceString(HOUR_LABEL) + ":", TitledBorder.LEFT , TitledBorder.TOP));
		inputHour =  new JComboBox();
		pane.add(inputHour);
		dataPane.add(pane);

		pane = new JPanel(new GridLayout());
		pane.setBorder(new TitledBorder(new EmptyBorder(1, 1, 1, 1),               
				((NolMainFrame)parent).getNolResourceString(MINUTE_LABEL) + ":", TitledBorder.LEFT , TitledBorder.TOP));
		inputMin =  new JComboBox();
		pane.add(inputMin);
		dataPane.add(pane);

		pane = new JPanel(new GridLayout());
		pane.setBorder(new TitledBorder(new EmptyBorder(1, 1, 1, 1),               
				((NolMainFrame)parent).getNolResourceString(SECOND_LABEL) + ":", TitledBorder.LEFT , TitledBorder.TOP));
		inputSec =  new JComboBox();
		pane.add(inputSec);
		dataPane.add(pane);
		
		JPanel cenPane = new JPanel(new BorderLayout());
		cenPane.add("Center",dataPane);

		pane = new JPanel(new GridLayout());
		pane.setBorder(new TitledBorder(new EmptyBorder(1, 1, 1, 1),               
				((NolMainFrame)parent).getNolResourceString(TIME_SETTING_LABEL) +  ":", TitledBorder.LEFT , TitledBorder.TOP));
		timeSetting =  new JTextField();
		pane.add(timeSetting);

		cenPane.add("South",pane);

		workSpace.add("Center",dataPane);
		workSpace.add("East",getControlPane());
		initializeChoice();
		setTime(System.currentTimeMillis());
		pack();

	}

	private JPanel getControlPane(){
		JPanel control = new JPanel();
		control.setBackground(getContentPane().getBackground());
		control.setLayout(new BoxLayout(control, BoxLayout.Y_AXIS));
		control.setBorder(new EmptyBorder(10, 10, 10, 10));

		JPanel pane0 = new JPanel(new GridLayout(2,1,5,5));
		JButton okButton = new JButton(((NolMainFrame)parent).getNolResourceString(OK_BUTTON_LABEL));
		okButton.setActionCommand("OK");
		JButton cancelButton = new JButton(((NolMainFrame)parent).getNolResourceString(CANCEL_BUTTON_LABEL));
		cancelButton.setActionCommand("Cancel");
		okButton.addActionListener(actionListener);
		cancelButton.addActionListener(actionListener);
		pane0.add(okButton);
		pane0.add(cancelButton);
		control.add(Box.createRigidArea(NolMainFrame.vpad15));
		control.add(pane0);
		control.add(Box.createRigidArea(NolMainFrame.vpad500));
		control.add(Box.createVerticalGlue());
		return control;
	}

	private void initializeChoice(){
		for(int i=0;i<20;i++){
			int y = 1990;
			String Y = ""+(y+i);
			inputYear.addItem(Y);
		}
		for(int i=1;i<=12;i++){
			String M = ""+i;
			inputMonth.addItem(M);
		}
		for(int i=1;i<=31;i++){
			String D = ""+i;
			inputDay.addItem(D);
		}
		for(int i=0;i<24;i++){
			String H = ""+i;
			inputHour.addItem(H);
		}
		for(int i=0;i<60;i++){
			String m = ""+i;
			inputMin.addItem(m);
		}
		for(int i=0;i<60;i++){
			String S = ""+i;
			inputSec.addItem(S);
		}
	}


	public boolean getResult(){
		return this.isOk;
	}

	public void setTime(long t){
		resultTime = t;
		Date date = new Date(t);
		Calendar rightNow = Calendar.getInstance();
		rightNow.setTime(date);
		int y = rightNow.get(Calendar.YEAR);
		if(y>=1990)
			inputYear.setSelectedIndex(y-1990); 
		int m = rightNow.get(Calendar.MONTH);
		if(m>=1)
			inputMonth.setSelectedIndex(m);
//		System.out.println("m="+m);
		int d = rightNow.get(Calendar.DATE);
		if(d>=1)
			inputDay.setSelectedIndex(d-1); 
		int h = rightNow.get(Calendar.HOUR_OF_DAY);
		if(h>=0)
			inputHour.setSelectedIndex(h); 
		int min = rightNow.get(Calendar.MINUTE);
		if(min>=0)
			inputMin.setSelectedIndex(min); 
		int s = rightNow.get(Calendar.SECOND);
 		if(s>=0)
			inputSec.setSelectedIndex(s); 

	}

	public long getTime(){
		Calendar rightNow = Calendar.getInstance();
		rightNow.clear();
		int y = inputYear.getSelectedIndex(); 
		if(y!=-1){
			rightNow.clear(Calendar.YEAR);
			rightNow.set(Calendar.YEAR,y+1990);
		}
		int m = inputMonth.getSelectedIndex(); 
//		System.out.println("getTime m="+m);
		if(m!=-1){
			rightNow.clear(Calendar.MONTH);
			rightNow.set(Calendar.MONTH,m);
		}
		int d = inputDay.getSelectedIndex(); 
		if(d!=-1){
			rightNow.clear(Calendar.DATE);
			rightNow.set(Calendar.DATE,d+1);
		}
		int h = inputHour.getSelectedIndex(); 
		if(h!=-1){
			rightNow.clear(Calendar.HOUR_OF_DAY);
			rightNow.set(Calendar.HOUR_OF_DAY, h);
		}
		int min = inputMin.getSelectedIndex(); 
		if(min!=-1){
			rightNow.clear(Calendar.MINUTE);
			rightNow.set(Calendar.MINUTE,min);
		}
		int s = inputSec.getSelectedIndex(); 
		if(s!=-1) {
			rightNow.clear(Calendar.SECOND);
			rightNow.set(Calendar.SECOND,s);
		}
		Date D = rightNow.getTime();
		return D.getTime();
	}

    /**
     * Control action implementation
     */
    class ControlAction extends AbstractAction {

		ControlAction() {
			super("controlAction");
		}

        @Override
		public void actionPerformed(ActionEvent e) {
				
			String command = e.getActionCommand();
			if(command.equals("OK")){
				isOk = true;
				NolTimeInputDialog.this.dispose();
			}else if(command.equals("Cancel")){
				isOk = false;
				NolTimeInputDialog.this.dispose();
			}
		}
    }

}

