package com.gensym.nols.wksp;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.text.*;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.border.*;

import com.gensym.nols.data.*;
import com.gensym.nols.main.*;

public class NolFileFormatWKSP  extends NolInternalFrame{
    protected static final String FILEFORMAT_NAME = "NameLabel";
    protected static final String FILEFORMAT_COMMENT = "CommentLabel";
    protected static final String FILEFORMAT_DELIMITER = "FileFormat_Delimiter";
    protected static final String FILEFORMAT_COLUMN = "FileFormat_Column";
    protected static final String FILEFORMAT_COLUMNFORMAT = "FileFormat_ColumnFormat";
    protected static final String FILEFORMAT_ROWFORMAT = "FileFormat_RowFormat";
    protected static final String FILEFORMAT_SYMBOLFORMAT = "FileFormat_SymbolFormat";
    protected static final String DELETE = "DeleteLabel";

	private NolMainFrame frame;
	private DataSeriesFileFormat format;
	private JList columnStyleList;
	private DefaultListModel columnStyleModel;
	private JList rowStyleList;
	private DefaultListModel rowStyleModel;
	private JList symbolList;
	private DefaultListModel symbolListModel;
	private JTextField nameField;
	private JTextArea descriptArea;
	private Action actionListener;

	private JLabel delimiterLabel;
	private JLabel columnLabel;

	public NolFileFormatWKSP (NolMainFrame frame,DataSeriesFileFormat format){
		super(frame.getProject().getRawDataSource());
		this.frame = frame;
		this.format = format;
		actionListener = new ControlAction();
		String title = "File Format: "+format.getName();
		setTitle(title);
		initLayout();
		initDataDisplay();
	}

	private void initDataDisplay(){
		nameField.setText(format.getName());
		descriptArea.setText(format.getComment());
		String sep = format.getSeparator();
		if(sep.equals(String.valueOf('\u0009'))){
			delimiterLabel.setText("Tab");
		}else if(sep.equals(";")){
			delimiterLabel.setText("Semicolon");
		}else if(sep.equals(",")){
			delimiterLabel.setText("Comma");
		}else if(sep.equals(String.valueOf('\u0020'))){
			delimiterLabel.setText("Space");
		}else{
			delimiterLabel.setText(sep);
		}
		columnLabel.setText(String.valueOf(format.getColumns()));
		updateRowStyleList();
		updateColumnStyleList();
		updateSymbolStyleList();
		
	}

   	private void updateRowStyleList(){
		getRowStyleListModel().removeAllElements();
		int tagLine = format.getTagLine();
		int nameLine = format.getNameLine();
		int unitLine = format.getUnitLine();
		int[] ignoredRows = format.getIgnoredRows();
		if(tagLine >-1){
			String ss = tagLine +": Tag";
			getRowStyleListModel().addElement(ss);
		}
		if(nameLine >-1){
			String ss = nameLine +": Name";
			getRowStyleListModel().addElement(ss);
		}
		if(unitLine >-1){
			String ss = unitLine +": Unit";
			getRowStyleListModel().addElement(ss);
		}
		if(ignoredRows.length >0){
			for(int i=0;i<ignoredRows.length;i++){
				String ss = ignoredRows[i] +": Ignored";
				getRowStyleListModel().addElement(ss);
			}
		}
	}

	private void updateColumnStyleList(){
		getColumnStyleListModel().removeAllElements();
		int dateTimeColumn = format.getDateTimeColumn();
		int dateColumn = format.getDateColumn();
		int timeColumn = format.getTimeColumn();
		int[] ignoredColumns = format.getIgnoredColumns();
		SimpleDateFormat dateTimeFormat = format.getDateTimeFormat();
		SimpleDateFormat dateFormat = format.getDateFormat();
		SimpleDateFormat timeFormat = format.getTimeFormat();

		if(dateTimeColumn >-1){
			String ss = dateTimeColumn +": Date & Time";
			getColumnStyleListModel().addElement(ss);
			ss = "("+dateTimeFormat.toPattern()+")";
			getColumnStyleListModel().addElement(ss);
		}
		if(dateColumn >-1){
			String ss = dateColumn +": Date";
			getColumnStyleListModel().addElement(ss);
			ss = "("+dateFormat.toPattern()+")";
			getColumnStyleListModel().addElement(ss);
		}
		if(timeColumn >-1){
			String ss = timeColumn +": Time";
			getColumnStyleListModel().addElement(ss);
			ss = "("+timeFormat.toPattern()+")";
			getColumnStyleListModel().addElement(ss);
		}
		if(ignoredColumns.length >0){
			for(int i=0;i<ignoredColumns.length;i++){
				String ss = ignoredColumns[i] +": Ignored";
				getColumnStyleListModel().addElement(ss);
			}
		}
	}

	private void updateSymbolStyleList(){
		getSymbolListModel().removeAllElements();
		Vector symbolStyles = format.getSymbols();
		for(int i=0;i<symbolStyles.size();i++){
			Vector con = (Vector)symbolStyles.elementAt(i);
			String ss = (String)con.elementAt(0) +": " + con.elementAt(1).toString();
			getSymbolListModel().addElement(ss);
		}
	}

	private DefaultListModel getColumnStyleListModel() {
		if (columnStyleModel == null) {
			columnStyleModel = new DefaultListModel();
		}	
		return columnStyleModel;
	}
	private DefaultListModel getRowStyleListModel() {
		if (rowStyleModel == null) {
			rowStyleModel = new DefaultListModel();
		}	
		return rowStyleModel;
	}
	private DefaultListModel getSymbolListModel() {
		if (symbolListModel == null) {
			symbolListModel = new DefaultListModel();
		}	
		return symbolListModel;
	}
	private void initLayout(){
		JPanel workPane = new JPanel(new BorderLayout());
													    
		JPanel cenPane = new JPanel(new BorderLayout());
		cenPane.setBorder(new EmptyBorder(10,10,10,10));

		JPanel infoPane = new JPanel(new BorderLayout());
		JPanel namePane = new JPanel(new GridLayout(2,1,5,5));
		namePane.setBorder(new EmptyBorder(10,10,10,10));
		JPanel namePane1 = new JPanel(new GridLayout(1,2,5,5));

		namePane1.add(new JLabel(frame.getNolResourceString(FILEFORMAT_NAME)+":"));
		nameField = new JTextField();
		nameField.addActionListener(actionListener);
		namePane1.add(nameField);
		JPanel namePane2 = new JPanel(new GridLayout(1,4,5,5));
		namePane2.add(new JLabel(frame.getNolResourceString(FILEFORMAT_DELIMITER)+":"));
		delimiterLabel = new JLabel();
		namePane2.add(delimiterLabel);
		namePane2.add(new JLabel(frame.getNolResourceString(FILEFORMAT_COLUMN)+":"));
		columnLabel = new JLabel();
		namePane2.add(columnLabel);
		namePane.add(namePane1);
		namePane.add(namePane2);

		JPanel descriptPane = new JPanel(new GridLayout());
		descriptPane.setBorder(new TitledBorder(new EmptyBorder(1, 1, 1, 1),               
			frame.getNolResourceString(FILEFORMAT_COMMENT)+":", TitledBorder.LEFT , TitledBorder.TOP));
		descriptArea = new JTextArea();
		descriptArea.getDocument().addDocumentListener((DocumentListener)actionListener);
 		JScrollPane listScrollPane = new JScrollPane(descriptArea);
		listScrollPane.setBorder(BorderFactory.createLoweredBevelBorder());
		listScrollPane.setPreferredSize(NolMainFrame.vpad40); 

		descriptPane.add(listScrollPane);

		infoPane.add("North",namePane);
		infoPane.add("Center",descriptPane);

		cenPane.add("North",infoPane);


		JPanel listPane = new JPanel(new GridLayout(1,3,5,5));
		JPanel collistPane = new JPanel(new GridLayout());
		collistPane.setBorder(new TitledBorder(new EmptyBorder(1, 1, 1, 1),               
			frame.getNolResourceString(FILEFORMAT_COLUMNFORMAT)+":", TitledBorder.LEFT , TitledBorder.TOP));
  		columnStyleList = new JList(getColumnStyleListModel());
//		columnStyleList.setBackground(Color.white);
		columnStyleList.setSelectionForeground(columnStyleList.getForeground());
		columnStyleList.setSelectionBackground(columnStyleList.getBackground());
		listScrollPane = new JScrollPane(columnStyleList);
		listScrollPane.setBorder(BorderFactory.createLoweredBevelBorder());
		collistPane.add(listScrollPane);

		JPanel rowlistPane = new JPanel(new GridLayout());
		rowlistPane.setBorder(new TitledBorder(new EmptyBorder(1, 1, 1, 1),               
			frame.getNolResourceString(FILEFORMAT_ROWFORMAT)+":", TitledBorder.LEFT , TitledBorder.TOP));
  		rowStyleList = new JList(getRowStyleListModel());
//		rowStyleList.setBackground(Color.white);
		rowStyleList.setSelectionForeground(rowStyleList.getForeground());
		rowStyleList.setSelectionBackground(rowStyleList.getBackground());
		listScrollPane = new JScrollPane(rowStyleList);
		listScrollPane.setBorder(BorderFactory.createLoweredBevelBorder());
		rowlistPane.add(listScrollPane);

		JPanel symbollistPane = new JPanel(new GridLayout());
		symbollistPane.setBorder(new TitledBorder(new EmptyBorder(1, 1, 1, 1),               
			frame.getNolResourceString(FILEFORMAT_SYMBOLFORMAT)+":", TitledBorder.LEFT , TitledBorder.TOP));
  		symbolList = new JList(getSymbolListModel());
//		symbolList.setBackground(Color.white);
		symbolList.setSelectionForeground(symbolList.getForeground());
		symbolList.setSelectionBackground(symbolList.getBackground());
		listScrollPane = new JScrollPane(symbolList);
		listScrollPane.setBorder(BorderFactory.createLoweredBevelBorder());
		symbollistPane.add(listScrollPane);

		listPane.add(collistPane);
		listPane.add(rowlistPane);
		listPane.add(symbollistPane);

		cenPane.add("Center",listPane);

		workPane.add("Center",cenPane);
		workPane.add("East",getControlPanel());
		setContentPane(workPane);

	}

	private JPanel getControlPanel(){
		JPanel control = new JPanel();
		control.setBackground(getContentPane().getBackground());
		control.setLayout(new BoxLayout(control, BoxLayout.Y_AXIS));
		control.setBorder(new EmptyBorder(10, 10, 10, 10));

		JPanel pane0 = new JPanel(new GridLayout(1,1,5,5));
		JButton but = new JButton(frame.getNolResourceString(DELETE));
		but.setActionCommand("Delete");
		but.addActionListener(actionListener);
 		pane0.add(but);
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

	public DataSeriesFileFormat getDataFormat(){
		return format;
	}

/** The inner control listener class.*/
    class ControlAction extends AbstractAction implements DocumentListener{
		ControlAction() {super("controlAction");}

        @Override
		public void actionPerformed(ActionEvent e) {
			String command = e.getActionCommand();
			if(command.equals("Delete")){
				frame.removeFileFormat(format);
			}
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
			format.setComment(com);
		}
	}
}

