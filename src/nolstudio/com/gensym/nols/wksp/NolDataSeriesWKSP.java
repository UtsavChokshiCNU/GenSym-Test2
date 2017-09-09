package com.gensym.nols.wksp;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.text.*;
import java.io.*;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.border.*;

import com.gensym.math.matrix.*;
import com.gensym.nols.data.*;
import com.gensym.nols.main.*;
import com.gensym.nols.dlg.*;

import com.gensym.DEBUG;

public class NolDataSeriesWKSP  extends NolInternalFrame{
    protected static final String DATASERIES_NAME = "NameLabel";
    protected static final String DATASERIES_COMMENT = "CommentLabel";
    protected static final String DATASERIES_SOURCE = "DataSeries_Source";
    protected static final String VARIABLES = "VariableLabel";
    protected static final String VARIABLESTATISTICS = "DataSeries_Variable_Statistics";
    protected static final String VARIABLEPROPERTY = "DataSeries_Variable_Property";
    protected static final String SPREADSHEET = "spreadsheet";
    protected static final String PROJECTPLOT = "projectplot";
    protected static final String XYPLOT = "xyplot";
    protected static final String LINECHART = "DataSeries_Line_Chart";	
    protected static final String EXPORT = "DataSeries_Export";
    protected static final String EXPORTSCALED = "DataSeries_ExportScale";
    protected static final String APPEND = "DataSeries_Append";
    protected static final String ADDTIMESTAMPS = "DataSeries_Addtimestamps";
    protected static final String DELETE = "DeleteLabel";
    protected static final String STARTTIME = "DataSeries_Starttime";
    protected static final String ENDTIME = "DataSeries_Endtime";
    protected static final String INTERVAL = "DataSeries_Interval";
    protected static final String SAMPLES = "DataSeries_Samples";
    protected static final String VALID = "DataSeries_Valid";

	private NolMainFrame frame;
	private DataSource dataSource;
	private DataSeries dataSeries;
	private NolList varList;
	private DefaultListModel varListModel;
	private JTextField nameField;
	private JLabel sourceLabel;
	private JTextArea descriptArea;
	private Action actionListener;
	private JPanel dataPane;
	private JLabel startTime;
	private JLabel endTime;
	private JLabel interval;
	private JLabel varCount;
	private JLabel sampleCount;
	private JLabel validCount;
	private JButton xybut;
	private JButton linebut;
	private JButton deleteBut;
	private JButton projectBut;
	private JButton addTimeBut;
	private JButton appendBut;
	private JButton propertyButton;
	private NolXYSingleChoiceDialog	xychoice;

	public NolDataSeriesWKSP (NolMainFrame frame,DataSeries ds){
		super(ds.getDataSource());
		this.frame = frame;
		actionListener = new ControlAction();
		dataSeries = ds;
		dataSource = ds.getDataSource();
		String title = dataSource.getName()+"."+ds.getName();
		setTitle(title);
		initLayout();
		initDataDisplay();
		updateDataPane();
	}

	public void initDataDisplay() {
		if(dataSeries.getDataSource() instanceof RawDataSource){
			deleteBut.setEnabled(true);
			appendBut.setEnabled(true);
		}else{
			deleteBut.setEnabled(false); //Temp Gchen 9/9/98
			appendBut.setEnabled(false);
		}
		nameField.setText(dataSeries.getName());
		sourceLabel.setText(dataSource.getName());
		descriptArea.setText(dataSeries.getComment());
		Vector varObjs = dataSeries.getVarObjects();
		int c = dataSeries.getColumn();
		if(c<2){
			xybut.setEnabled(false);
			projectBut.setEnabled(false);
		}else{
			xybut.setEnabled(true);
			projectBut.setEnabled(true);
		}
		
		if(DEBUG.debugFlag){
			System.out.println("datawksp init disp varobjs size="+varObjs.size());
		}
		getVarListModel().removeAllElements();
		varList.addElements(varObjs);
	}
	
	public void refreshNameField(){
		String title = dataSource.getName()+"."+dataSeries.getName();
			setTitle(title);
		nameField.setText(dataSeries.getName());
	}


	public void refreshVarTable(){
		varList.validate();
		varList.repaint(0l);
	}
	
	public void updateDataPane(){
		dataPane.removeAll();
		if(dataSeries.getHasTimeStamps()){
			dataPane.setLayout(new GridLayout(6,2,5,5));
			
			dataPane.add(new JLabel(frame.getNolResourceString(STARTTIME)+":"));
//			dataPane.add(new JLabel("Start time:"));
			startTime = new JLabel();
			dataPane.add(startTime);
			dataPane.add(new JLabel(frame.getNolResourceString(ENDTIME)+":"));
			endTime = new JLabel();
			dataPane.add(endTime);
			dataPane.add(new JLabel(frame.getNolResourceString(INTERVAL)+":"));
			interval = new JLabel();
			dataPane.add(interval);
		} else dataPane.setLayout(new GridLayout(3,2,5,5));
		dataPane.add(new JLabel(frame.getNolResourceString(VARIABLES)+":"));
		varCount = new JLabel();
		dataPane.add(varCount);
		dataPane.add(new JLabel(frame.getNolResourceString(SAMPLES)+":"));
		sampleCount = new JLabel();
		dataPane.add(sampleCount);
		dataPane.add(new JLabel(frame.getNolResourceString(VALID)+":"));
		validCount = new JLabel();
		dataPane.add(validCount);
		
		if(dataSeries.getHasTimeStamps()){
			long[] timeStamps = dataSeries.getTimeStamps();
			SimpleDateFormat timeFormat = new SimpleDateFormat("MM/dd/yyyy H:mm:ss");
			String s = timeFormat.format(new Date(timeStamps[0]));
//	 System.out.println("start="+s);
			startTime.setText(s);
			s = timeFormat.format(new Date(timeStamps[timeStamps.length-1]));
			endTime.setText(s);
//	 System.out.println("end="+s);
			if(timeStamps.length>1){
				long interv = (timeStamps[timeStamps.length-1]-timeStamps[0])/(timeStamps.length-1);
//	 System.out.println("timeStamps.length="+timeStamps.length);
				long h = (long)interv/3600000;
				if(h>0){
					s = String.valueOf(h)+":";
					interv = interv - h*3600000;
				}else{ 
					s ="0:";
				}
				long m = (long)interv/60000;
 				if(m>0){
					s = s+m+":";
					interv = interv - m*60000;
				}else{
					if(!s.equals(""))
						s =s+"00:";
				}
				long se = (long)interv/1000;
 				if(se>0){
					s = s+se+":";
					interv = interv - se*1000;
				}else{
					if(!s.equals(""))
						s =s+"00:";
				}
 				if(interv>0){
					s = s+interv;
				}else{
					s =s+"0";
				}
				interval.setText(s);
			}else{
				interval.setText("");
			}
			addTimeBut.setText(frame.getNolResourceString("DataSeries_Resampling"));
			addTimeBut.setActionCommand("Resampling...");
	//		addTimeBut.setEnabled(false);
		}else{
			if(dataSource instanceof RawDataSource){
				addTimeBut.setEnabled(true);
			}else{
				addTimeBut.setEnabled(false);
			}
		}
		int c = dataSeries.getColumn();
		varCount.setText(String.valueOf(c));
		int r = dataSeries.getRow();
		sampleCount.setText(String.valueOf(r));
		Matrix X = dataSeries.getDataMatrix();
		Matrix temp = Matlib.createMatrix(r,1);
		Matlib.findFiniteRows(X,temp);
		int validr = 0;
		for(int i=0;i<r;i++){
			if(temp.get(i,0)>0)
				validr++;
		}
		Matlib.clear(temp); // memory leak if not cleared; added by Brian O. Bush, Feb 5, 1998

		validCount.setText(String.valueOf(validr));	//Temp gchen 9/9/98
		if(DEBUG.debugFlag){
			System.out.println("updateDataPane dataSeries.getColumn()="+c);
			System.out.println("updateDataPane dataSeries.getRow()="+r);
		}
		this.validate();
		this.repaint(0l);
	}

	private DefaultListModel getVarListModel() {
		if (varListModel == null) {
			varListModel = new DefaultListModel();
		}	
		return varListModel;
	}
	
	private void initLayout(){
		JPanel workPane = new JPanel(new BorderLayout());
													    
		JPanel cenPane = new JPanel(new BorderLayout());
		cenPane.setBorder(new EmptyBorder(10,10,10,10));

		JPanel infoPane = new JPanel(new BorderLayout());
		JPanel namePane = new JPanel(new GridLayout(1,4,5,5));
		namePane.setBorder(new EmptyBorder(10,10,10,10));
		namePane.add(new JLabel(frame.getNolResourceString(DATASERIES_NAME)+":"));
		nameField = new JTextField();
		nameField.addActionListener(actionListener);
		namePane.add(nameField);
		namePane.add(new JLabel(frame.getNolResourceString(DATASERIES_SOURCE)+":"));
		sourceLabel = new JLabel();
		namePane.add(sourceLabel);

		JPanel descriptPane = new JPanel(new GridLayout());
		descriptPane.setBorder(new TitledBorder(new EmptyBorder(1, 1, 1, 1),               
			frame.getNolResourceString(DATASERIES_COMMENT)+":", TitledBorder.LEFT , TitledBorder.TOP));
		descriptArea = new JTextArea();
		descriptArea.getDocument().addDocumentListener((DocumentListener)actionListener);
 		JScrollPane listScrollPane = new JScrollPane(descriptArea);
		listScrollPane.setBorder(BorderFactory.createLoweredBevelBorder());
		listScrollPane.setPreferredSize(NolMainFrame.vpad40); 

		descriptPane.add(listScrollPane);

		infoPane.add("North",namePane);
		infoPane.add("Center",descriptPane);

		cenPane.add("North",infoPane);

		JPanel listPane = new JPanel(new GridLayout());
		listPane.setBorder(new TitledBorder(new EmptyBorder(1, 1, 1, 1),               
			frame.getNolResourceString(VARIABLES)+":", TitledBorder.LEFT , TitledBorder.TOP));
  		varList = new NolList(getVarListModel());
		varList.addMouseListener((MouseListener)actionListener);
//		varList.setBackground(Color.white);
		listScrollPane = new JScrollPane(varList);
		listScrollPane.setBorder(BorderFactory.createLoweredBevelBorder());
		listPane.add(listScrollPane);
		cenPane.add("Center",listPane);

		dataPane = new JPanel(new GridLayout());
		dataPane.setBorder(new EmptyBorder(10, 10, 10, 10));  			
		cenPane.add("South",dataPane);

		workPane.add("Center",cenPane);
		workPane.add("East",getControlPanel());
		setContentPane(workPane);
	}

	private JPanel getControlPanel(){
		JPanel control = new JPanel();
		control.setBackground(getContentPane().getBackground());
		control.setLayout(new BoxLayout(control, BoxLayout.Y_AXIS));
		control.setBorder(new EmptyBorder(10, 10, 10, 10));

		JPanel pane0 = new JPanel(new GridLayout(10,1,5,5));
		JButton but = new JButton(frame.getNolResourceString(SPREADSHEET));
		but.setActionCommand("Spreadsheet");
		but.addActionListener(actionListener);
  		pane0.add(but);
		projectBut = new JButton(frame.getNolResourceString(PROJECTPLOT));
		projectBut.setActionCommand("Projection Plot");
		projectBut.addActionListener(actionListener);
  		pane0.add(projectBut);
		xybut = new JButton(frame.getNolResourceString(XYPLOT));
		xybut.setActionCommand("X-Y Plot...");
		xybut.addActionListener(actionListener);
  		pane0.add(xybut);

		linebut = new JButton(frame.getNolResourceString(LINECHART));
		linebut.setActionCommand("Line Chart...");
		linebut.addActionListener(actionListener);
		linebut.setEnabled(false);
  		pane0.add(linebut);

		but = new JButton(frame.getNolResourceString(EXPORT));
		but.setActionCommand("Export...");
		but.addActionListener(actionListener);
  		pane0.add(but);

		//This feature is for version 4.3		
/*		but = new JButton(frame.getNolResourceString(EXPORTSCALED));
		but.setActionCommand("Export Scaled Data");
		but.addActionListener(actionListener);
  		pane0.add(but);
  */ 
		appendBut = new JButton(frame.getNolResourceString(APPEND));
		appendBut.setActionCommand("Append...");
		appendBut.addActionListener(actionListener);
  		pane0.add(appendBut);
		addTimeBut = new JButton(frame.getNolResourceString(ADDTIMESTAMPS));
		addTimeBut.setActionCommand("Add Time Stamps...");
		addTimeBut.addActionListener(actionListener);
  		pane0.add(addTimeBut);
		

//		if(DEBUG.more){
		but = new JButton(frame.getNolResourceString(VARIABLESTATISTICS));
		but.setActionCommand("Variable Statistics...");
		but.addActionListener(actionListener);
		pane0.add(but);
		propertyButton = new JButton(frame.getNolResourceString(VARIABLEPROPERTY));
		propertyButton.setActionCommand("Variable Property...");
		propertyButton.addActionListener(actionListener);
		propertyButton.setEnabled(false);
		pane0.add(propertyButton);
//		}

		deleteBut = new JButton(frame.getNolResourceString(DELETE));
		deleteBut.setActionCommand("Delete");
		deleteBut.addActionListener(actionListener);
 		pane0.add(deleteBut);
		control.add(Box.createRigidArea(NolMainFrame.vpad15));
		control.add(pane0);
		control.add(Box.createRigidArea(NolMainFrame.vpad500));
		control.add(Box.createVerticalGlue());
		return control;
	}

	private void refreshDisplay(){
		Rectangle rv = this.getBounds();
		this.setBounds(rv.x,rv.y,rv.width+20,rv.height);
		this.paintImmediately(rv.x,rv.y,rv.width+20,rv.height);
		this.validate();
		this.setBounds(rv.x,rv.y,rv.width,rv.height);
		this.validate();
	}

	public DataSeries getDataSeries(){
		return dataSeries;
	}

	@Override
	public DataSource getDataSource(){
		return dataSource;
	}

	public NolXYSingleChoiceDialog	getXYChoice(){
		if(xychoice == null){
			xychoice = new NolXYSingleChoiceDialog(frame,"Select Variables","Variable",
				new Vector(),new Vector(),false);
		}
		return xychoice;
	}

/** The inner control listener class.*/
    class ControlAction extends AbstractAction implements DocumentListener, MouseListener, Runnable {
		private String command;
		private Object source;
		ControlAction() {super("controlAction");}
		@Override
		public void actionPerformed(ActionEvent e) {
			// handle all actions outside of the main UI thread, otherwise the UI hangs
			command = e.getActionCommand ();
			source = e.getSource ();
			new Thread (this).start();
		}
		@Override
		public void run () {
//			setWaitCursor(true);
			if(command.equals("Spreadsheet")) {
				frame.spreadsheetActionPerformed(dataSeries);
			}else if(command.equals("Projection Plot")) {
				frame.projectmapActionPerformed(dataSeries);
			}else if(command.equals("X-Y Plot...")){
				Vector varObjs = dataSeries.getVarObjects();
				getXYChoice().setContent("Select Variables","Variable",varObjs,varObjs,false);
				getXYChoice().pack();
				getXYChoice().setBounds(200, 200, 500, 300);
				getXYChoice().setVisible(true);
				if(getXYChoice().getResult()){
					Variable varx = (Variable)getXYChoice().getSelectedItemX();
					Variable vary = (Variable)getXYChoice().getSelectedItemY();
					frame.xymapActionPerformed(varx,vary);
				}
			}else if(command.equals("Export...")){
				frame.exportActionPerformed(dataSeries);
			}else if(command.equals("Export Scaled Data")){

 				JFileChooser fileChooser = new JFileChooser();
				fileChooser.setDialogTitle("Export Scaled Data");
				NolFileFilter filter1 = new NolFileFilter(
					new String[] {"txt"}, "ASCII file"
				);
				fileChooser.addChoosableFileFilter(filter1);
				fileChooser.setFileFilter(filter1);
				fileChooser.setDialogType(JFileChooser.SAVE_DIALOG);

				fileChooser.setSelectedFile(new File(dataSeries.getName()+".txt"));
				fileChooser.setLocation(200,200);			
				int retval = fileChooser.showSaveDialog(frame);

				fileChooser.setFileFilter(null);
				fileChooser.removeChoosableFileFilter(filter1);

				if(retval == JFileChooser.CANCEL_OPTION){
//					setWaitCursor(false);
					return;
				}
				File currentPath = fileChooser.getSelectedFile();
				if(currentPath == null){
//					setWaitCursor(false);
					return;
				}
				String path = currentPath.getPath();

/*				try{
				}catch(IOException evt){
					System.err.println("Non-Fatal exception: " + evt.getMessage());
					evt.printStackTrace();
				}
*/
				Toolkit.getDefaultToolkit().beep();

				

			}else if(command.equals("Append...")){
				frame.appendDataSeries(dataSeries);
			}else if(command.equals("Add Time Stamps...")){
				NolAddTimeStampsDialog addTimeStampsDialog = 
					new NolAddTimeStampsDialog(frame,"Add Time Stamps to "+dataSeries.getName());
				addTimeStampsDialog.setBounds(200,200,350,140);
				addTimeStampsDialog.setVisible(true);
				if(!addTimeStampsDialog.getResult()){
//					setWaitCursor(false);
					return;
				}
				try{
					long[] tp = addTimeStampsDialog.getTimeStampsParameters();
					dataSeries.setTimeStamps(tp[0],tp[1]);
//					addTimeBut.setEnabled(false);
					addTimeBut.setText(frame.getNolResourceString("DataSeries_Resampling"));
					addTimeBut.setActionCommand("Resampling...");
					updateDataPane();
				} catch(NumberFormatException evt){
					frame.showOKDialog("Error in the text field.");
				}
			}else if(command.equals("Resampling...")){
				NolResamplingDialog resamplingDialog = 
					new NolResamplingDialog(frame,"Resampling Data Series "+dataSeries.getName(), dataSeries);
				resamplingDialog.setBounds(200,200,400,350);
				resamplingDialog.setVisible(true);
				if(!resamplingDialog.getResult()){
//					setWaitCursor(false);
					return;
				}
				String newStartTimeStr = resamplingDialog.getNewStartTimeString();
				String newEndTimeStr = resamplingDialog.getNewEndTimeString();
				String newIntervalTimeStr = resamplingDialog.getNewIntervalTimeString();

				try{
					SimpleDateFormat fmt = new SimpleDateFormat("M/d/y H:m:s");
					Calendar currentCalendar = Calendar.getInstance();
					Date dt= fmt.parse(newStartTimeStr);
					currentCalendar.setTime(dt);
					long t1 = currentCalendar.getTime().getTime();
					dt= fmt.parse(newEndTimeStr);
					currentCalendar.setTime(dt);
					long t2 = currentCalendar.getTime().getTime();
					long t3 = Long.valueOf(newIntervalTimeStr).longValue();
					t3 = t3 * 1000;
					dataSeries.resampleData(t1,t2,t3);
				}catch(java.text.ParseException e){
				}
			}else if(command.equals("Variable Statistics...")){
 				frame.showVariableStatistics(dataSeries);
			}else if(command.equals("Variable Property...")){
				int index = varList.getSelectedIndex();
				if(index == -1){
//					setWaitCursor(false);
					return;
				}
				Vector varObjs = dataSeries.getVarObjects();
				Variable varObj = (Variable)varObjs.elementAt(index);
				frame.showVariableWKSP(varObj);
			}else if(command.equals("Line Chart...")){
				int[] indecs = varList.getSelectedIndices();
				if(indecs.length == 0){
//					setWaitCursor(false);
					return;
				}
				Vector varObjs = dataSeries.getVarObjects();
				Vector varSeletedObjs = new Vector(indecs.length);
				for(int i=0;i<indecs.length;i++){
					varSeletedObjs.addElement(varObjs.elementAt(indecs[i]));
				}
				frame.lineChartActionPerformed(varSeletedObjs);
			}else if(command.equals("Delete")){
				frame.removeRawDataDataSeries(dataSeries);
//				if(frame.removeRawDataDataSeries(dataSeries)){
//					try{
//						setClosed(true);
//					}catch(java.beans.PropertyVetoException evt){}
//				}
			}else if(source.equals(nameField) ){
				if(!(dataSeries.getDataSource() instanceof RawDataSource)){
//					setWaitCursor(false);
					return;
				}
	 			String n = nameField.getText();
				if(n == null || n.equals("")){
//					setWaitCursor(false);
					return;
				}
				Project proj = frame.getProject();
				proj.changeDataSeriesName(dataSeries, n);
				
				dataSeries.setName(n);
				frame.changeDataSeriesName(dataSeries);
			}
//			setWaitCursor(false);
		}

		@Override
		public void changedUpdate(DocumentEvent e){	}
		@Override
		public void insertUpdate(DocumentEvent e){
			changeComment();
		}
		@Override
		public void removeUpdate(DocumentEvent e){
			changeComment();
		}
		private void changeComment(){
			String com = descriptArea.getText();
			dataSeries.setComment(com);
		}
		@Override
		public void mousePressed(MouseEvent m) {}
		@Override
		public void mouseEntered(MouseEvent m) {}
		@Override
		public void mouseExited(MouseEvent m) {}
		@Override
		public void mouseReleased(MouseEvent m) {}
		public void mouseDragged(MouseEvent m) {}
		public void mouseMoved(MouseEvent m) {}
		@Override
		public void mouseClicked(MouseEvent m) {
			int index = varList.getSelectedIndex();
			if(index != -1){
				propertyButton.setEnabled(true);
				linebut.setEnabled(true);
			}else{
				propertyButton.setEnabled(false);
				linebut.setEnabled(false);
			}
			int clickCount =  m.getClickCount();
			if(clickCount != 2) {
				return;
			}
			Vector varObjs = dataSeries.getVarObjects();
			Variable varObj = (Variable)varObjs.elementAt(index);
			frame.showVariableWKSP(varObj);
		}
	}
}

