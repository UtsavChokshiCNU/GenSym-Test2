package com.gensym.nols.dlg;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.text.*;

import javax.swing.*;
import javax.swing.border.*;

import com.gensym.nols.main.*;

public class NolPreferenceDialog extends NolDialog{
	private NolMainFrame frame;

	private boolean isOK;
	private JButton cancelButton;
	private JButton okButton;
	private JButton testButton;
	private JButton helpButton;
	private ControlAction actionListener;

  	private JTextField dateInputField;
  	private JTextField timeInputField;
  	private JTextField nmaxField;
  	private JLabel currentTimeLabel;

	private DefaultListModel dateKeysModel;
	private DefaultListModel timeKeysModel;
	private NolList dateKeysContents;
	private NolList timeKeysContents;

	private long currentTime;
	private SimpleDateFormat dateFormat;		
	private SimpleDateFormat timeFormat;
	private int NMAX;

	private static String[] timeFormats = {
	"h       hour in am/pm (1-12)",
	"H       hour in day (0-23)",
	"k       hour in day (1-24)",
	"K       hour in am/pm (0-11)",
	"m       minute in hour",
	"s       second in minute",
	"S       millisecond",
	"a       am/pm marker",
	"z       time zone"
	};
	private static String[] dateFormats = {
	"G       era designator",
	"y       year (number)",
	"M       month in year (text or number)",
	"D       day in year (number)",
	"d       day in month (number)",
	"E       day in week (text)",
	"F       day of week in month (number)",
	"w       week in year (number)",
	"W       week in month (number)"};

	private static Vector timeFormatsVector,dateFormatsVector;
	static {
		timeFormatsVector = new Vector();
		for (int i=0; i<timeFormats.length; i++){
		  timeFormatsVector.addElement(timeFormats[i]);
		}
		dateFormatsVector = new Vector();
		for (int i=0; i<dateFormats.length; i++){
		  dateFormatsVector.addElement(dateFormats[i]);
		}
	}
   
	private static final String CANCEL_BUTTON_LABEL = "CancelButtonLabel";
    private static final String OK_BUTTON_LABEL = "OkButtonLabel";
    private static final String TEST_BUTTON_LABEL = "PreferenceDialog_Test";
	

    private static final String DATEFORMAT = "PreferenceDialog_DateFormat";
    private static final String TIMEFORMAT = "PreferenceDialog_TimeFormat";
    private static final String DATEFORMATPATTERN = "PreferenceDialog_DateFormatPattern";
    private static final String TIMEFORMATPATTERN = "PreferenceDialog_TimeFormatPattern";
    private static final String DATEFORMATKEYS = "PreferenceDialog_DateFormatKeys";
    private static final String TIMEFORMATKEYS = "PreferenceDialog_TimeFormatKeys";
    private static final String CURRENTTIME = "PreferenceDialog_CurrentTime";
    private static final String WRONGDATEFORMAT = "PreferenceDialog_WrongDateFormat";
    private static final String WRONGTIMEFORMAT = "PreferenceDialog_WrongTimeFormat";
    private static final String ENTERNEWNMAX = "PreferenceDialog_EnterNewNMAX";
    private static final String ENTER = "PreferenceDialog_Enter";
    private static final String OPTIMIZATION = "PreferenceDialog_Optimization";
	
	
	public NolPreferenceDialog(JFrame dw, String title) {

		super(dw, title, true);
        frame = (NolMainFrame)dw;	 
		actionListener = new ControlAction();	
		dateKeysModel = new DefaultListModel();
		timeKeysModel = new DefaultListModel();
		initLayout();
        setBounds(150,150,500,350);
	}

	private void initLayout(){

		cancelButton = new JButton(frame.getNolResourceString(CANCEL_BUTTON_LABEL));
		okButton = new JButton(frame.getNolResourceString(OK_BUTTON_LABEL));
		cancelButton.addActionListener(actionListener);
		okButton.addActionListener(actionListener);

		JPanel controlPane = new JPanel(new GridLayout(1,2,5,5));
		controlPane.add(cancelButton);
//		controlPane.add(testButton);
		controlPane.add(okButton);

		JPanel southPane = new JPanel(new BorderLayout());
		southPane.setBorder(new EmptyBorder(10,10,10,10));
		southPane.add("East",controlPane);

														 
		getContentPane().setLayout(new BorderLayout());

		
		JTabbedPane cenPane = new JTabbedPane();
		cenPane.addTab(frame.getNolResourceString(TIMEFORMAT), getTimeFormatPanel());
		cenPane.addTab(frame.getNolResourceString(OPTIMIZATION), getOptimizationPanel());

		getContentPane().add("South",southPane);
		getContentPane().add("Center",cenPane);
		
	}

	private JPanel getTimeFormatPanel(){
		JPanel timeDateFormatPane = new JPanel(new BorderLayout());

		JPanel dateFormatPane = new JPanel(new BorderLayout());
		dateFormatPane.setBorder(BorderFactory.
			  createTitledBorder(frame.getNolResourceString(DATEFORMAT)+":"));

		JPanel datePattenPane = new JPanel(new GridLayout());
		datePattenPane.setBorder(new TitledBorder(new EmptyBorder(1, 1, 1, 1),               
			frame.getNolResourceString(DATEFORMATPATTERN)+":", TitledBorder.LEFT , TitledBorder.TOP));
		dateInputField = new JTextField();
		datePattenPane.add(dateInputField);


	  	dateKeysContents = new NolList(dateKeysModel);
		dateKeysContents.addElements(dateFormatsVector);

		JPanel dateKeysPane = new JPanel(new GridLayout());
		dateKeysPane.setBorder(new TitledBorder(new EmptyBorder(1, 1, 1, 1),               
			frame.getNolResourceString(DATEFORMATKEYS)+":", TitledBorder.LEFT , TitledBorder.TOP));
		JScrollPane dateKeysScrollPane = new JScrollPane(dateKeysContents);
		dateKeysPane.add(dateKeysScrollPane);

		dateFormatPane.add("North",datePattenPane);
		dateFormatPane.add("Center",dateKeysPane);
		
		JPanel timeFormatPane = new JPanel(new BorderLayout());
 		timeFormatPane.setBorder(BorderFactory.
			  createTitledBorder(frame.getNolResourceString(TIMEFORMAT)+":"));

		JPanel timePattenPane = new JPanel(new GridLayout());
		timePattenPane.setBorder(new TitledBorder(new EmptyBorder(1, 1, 1, 1),               
			frame.getNolResourceString(TIMEFORMATPATTERN)+":", TitledBorder.LEFT , TitledBorder.TOP));
		timeInputField = new JTextField();
		timePattenPane.add(timeInputField);

		timeKeysContents = new NolList(timeKeysModel);
		timeKeysContents.addElements(timeFormatsVector);

		JPanel timeKeysPane = new JPanel(new GridLayout());
		timeKeysPane.setBorder(new TitledBorder(new EmptyBorder(1, 1, 1, 1),         
			frame.getNolResourceString(TIMEFORMATKEYS)+":", TitledBorder.LEFT , TitledBorder.TOP));

		JScrollPane timeKeysScrollPane = new JScrollPane(timeKeysContents);
		timeKeysPane.add(timeKeysScrollPane);

		timeFormatPane.add("North",timePattenPane);
		timeFormatPane.add("Center",timeKeysPane);
		
		
		JPanel convertionPane = new JPanel(new BorderLayout());
		convertionPane.setBorder(BorderFactory.
			  createTitledBorder(frame.getNolResourceString(CURRENTTIME)+":"));
		currentTimeLabel  = new JLabel();
		testButton = new JButton(frame.getNolResourceString(TEST_BUTTON_LABEL));
		testButton.addActionListener(actionListener);
		convertionPane.add("Center",currentTimeLabel);
		convertionPane.add("East",testButton);

		JPanel cPane = new JPanel(new GridLayout(1,2,5,5));
		cPane.add(dateFormatPane);
		cPane.add(timeFormatPane);
		timeDateFormatPane.add("South",convertionPane);
		timeDateFormatPane.add("Center",cPane);
		return timeDateFormatPane;

	}

	private JPanel getOptimizationPanel(){
		JPanel optPane = new JPanel(new BorderLayout());
		optPane.setBorder(new EmptyBorder(50,10,10,10));
		String s = frame.getNolResourceString(ENTERNEWNMAX);
		JTextArea infoLabel = new JTextArea(s);
		infoLabel.setLineWrap(true);
		infoLabel.setEditable(false);
		infoLabel.setBackground(optPane.getBackground());
		optPane.add("Center",infoLabel);

		JPanel southPane = new JPanel(new GridLayout(1,2,5,5));
		southPane.setBorder(new EmptyBorder(10,20,10,20));
		nmaxField = new JTextField();
		southPane.add(new JLabel(frame.getNolResourceString(ENTER)+":"));
		southPane.add(nmaxField);
		optPane.add("South",southPane);
		return optPane;
	}

	public void resetData(SimpleDateFormat df,SimpleDateFormat tf, int nmax){
		dateFormat = df;
		timeFormat = tf;
		NMAX = nmax;
		initDataDisplay();
	}

	private void initDataDisplay(){
		currentTime = System.currentTimeMillis();
		String s = dateFormat.format(new Date(currentTime)) + " "+
			timeFormat.format(new Date(currentTime));
		currentTimeLabel.setText(s);
		dateInputField.setText(dateFormat.toPattern());
		timeInputField.setText(timeFormat.toPattern());
		nmaxField.setText(NMAX+"");

	}

	private boolean testFormat(){
		boolean valid = true;
		String dstr = "";
		String tstr = "";
  		currentTime = System.currentTimeMillis();
		try{
			SimpleDateFormat df = new SimpleDateFormat(dateInputField.getText());
			dstr = df.format(new Date(currentTime))	;
			dateFormat = df;
		}catch(IllegalArgumentException evt){
			frame.showOKDialog(frame.getNolResourceString(WRONGDATEFORMAT));
			dateInputField.setText(dateFormat.toPattern());
			valid = false;
		}
		try{
			SimpleDateFormat tf = new SimpleDateFormat(timeInputField.getText());
			tstr = tf.format(new Date(currentTime))	;
			timeFormat = tf;
		}catch(IllegalArgumentException evt){
			frame.showOKDialog(frame.getNolResourceString(WRONGTIMEFORMAT));
			timeInputField.setText(timeFormat.toPattern());
			valid = false;
		}
		String s = dateFormat.format(new Date(currentTime)) + " "+
			timeFormat.format(new Date(currentTime));
		currentTimeLabel.setText(s);

  		String ns = nmaxField.getText();
		try{
			int c = Integer.valueOf(ns).intValue();
			if(c>0){
				NMAX = c;
			}else{
				valid = false;
			}
		}catch(NumberFormatException  evt){
				valid = false;
		}
		return valid;
	}
		
	class ControlAction extends AbstractAction {
		ControlAction() { super("controlAction");}

        @Override
		public void actionPerformed(ActionEvent e) {
			if(e.getSource().equals(cancelButton)) {
				isOK = false;
				setVisible(false);
			}else if(e.getSource().equals(testButton)) {
				testFormat();
			}else if(e.getSource().equals(okButton)) {
				if(testFormat()){
					isOK = true;
					setVisible(false);
					NolSettings.getSettings().setDateFormat(dateFormat);
					NolSettings.getSettings().setTimeFormat(timeFormat);
					NolSettings.save();
					frame.setDateTimeFormat(dateFormat,timeFormat);
					frame.setOptimizationNMAX(NMAX);
				}
			}
		}
	}
}

