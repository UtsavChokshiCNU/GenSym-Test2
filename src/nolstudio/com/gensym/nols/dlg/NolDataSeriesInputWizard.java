package com.gensym.nols.dlg;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.io.*;
import java.net.URL;
import java.nio.charset.Charset;
import java.text.*;

import javax.swing.*;
import javax.swing.event.*;
import javax.swing.border.*;
import javax.swing.table.*;

import com.gensym.nols.data.*;
import com.gensym.nols.util.Parser;
import com.gensym.DEBUG;

import com.gensym.nols.main.NolMainFrame;
import com.gensym.nols.main.NolSettings;

public class NolDataSeriesInputWizard extends NolWizardDialog {
    private static final String FORMAT_LABEL = "DataSeriesInputWizard_FormatString";
	private static final String IMPORT_LABEL = "DataSeriesInputWizard_ImportAnASCIIFile";
    private static final String NAME_DS_LABEL = "DataSeriesInputWizard_NameDataSeriesLabel";
	private static final String NAME_FF_LABEL = "DataSeriesInputWizard_NameFileFormat";
    private static final String COMMENT_DS_LABEL = "DataSeriesInputWizard_CommentForDS";
	private static final String COMMENT_FF_LABEL = "DataSeriesInputWizard_CommentForFormat";
	private static final String WHAT_IS_DELIMITERS_LABEL = "DataSeriesInputWizard_WhatISDelimiters";
	
	// general labels
	private static final String DELIMITERS_LABEL = "DataSeriesInputWizard_DelimitersLabel";
	private static final String SPACE_LABEL = "DataSeriesInputWizard_SpaceLabel";
	private static final String SEMICOLON_LABEL = "DataSeriesInputWizard_SemicolonLabel";
	private static final String OTHER_LABEL = "DataSeriesInputWizard_OtherLabel";
	private static final String COMMA_LABEL = "DataSeriesInputWizard_CommaLabel";
	private static final String TAB_LABEL = "DataSeriesInputWizard_TabLabel";

	private static final String COLUMN_FORMAT_TEXT = "DataSeriesInputWizard_ColumnFormatPaneText";
	private static final String ROW_FORMAT_TEXT = "DataSeriesInputWizard_RowFormatPaneText";
	private static final String SYMBOL_PANE_TEXT = "DataSeriesInputWizard_SymbolPaneText";
	private static final String NUMBER_LABEL = "DataSeriesInputWizard_NumberLabel";
	private static final String SET_LABEL = "DataSeriesInputWizard_SetLabel";
	private static final String REMOVE_LABEL = "DataSeriesInputWizard_RemoveLabel";
	private static final String IGNORE_ROW_LABEL = "DataSeriesInputWizard_IgnoreRowLabel";
	private static final String TEXT_CONVERSION_LABEL = "DataSeriesInputWizard_TextConversionLabel";
	private static final String COLUMN_FORMAT_TITLE = "DataSeriesInputWizard_ColumnFormatTitle";
	private static final String DATE_TIME_LABEL = "DataSeriesInputWizard_DateTimeLabel";
	private static final String TIME_LABEL = "DataSeriesInputWizard_TimeLabel";
	private static final String DATE_LABEL = "DataSeriesInputWizard_DateLabel";
	private static final String IGNORED_LABEL = "DataSeriesInputWizard_IgnoredLabel";
	private static final String COLUMN_LABEL = "DataSeriesInputWizard_ColumnLabel";
	private static final String DATA_PREVIEW = "DataSeriesInputWizard_DataPreview";
	private static final String CUSTOM_FORMAT = "DataSeriesInputWizard_CustomFormat";
	
	private static final String TAGS = "DataSeriesInputWizard_Tags";
	private static final String UNITS = "DataSeriesInputWizard_Units";
	private static final String NAMES = "DataSeriesInputWizard_Names";
	private static final String NAN = "DataSeriesInputWizard_NaN";
	private static final String SYMBOL = "DataSeriesInputWizard_Symbol";
	private static final String ROW = "DataSeriesInputWizard_Row";
	private static final String ROW_FORMAT_TITLE = "DataSeriesInputWizard_RowDataFormat";
	
	private static final String FORMAT_PANE_TEXT = "DataSeriesInputWizard_formatPaneText";
	private static final String FORMAT_CHOICE = "DataSeriesInputWizard_formatChoice";
	private static final String ENGLISH = "DataSeriesInputWizard_English";
	private static final String FRENCH = "DataSeriesInputWizard_French";
	private static final String GERMAN = "DataSeriesInputWizard_German";
	private static final String ITALIAN = "DataSeriesInputWizard_Italian";

	private static final String REDUNDENT = "DataSeriesInputWizard_Redundent";

	private JTextField dataSeriesName;
	private JTextField fileFormatName;
	private JTextArea dataSeriesDescript;
	private JTextArea fileFormatDescript;
	private JTextField otherDelimiter;
	private ControlAction actionListener;
	private boolean isOk;
	private boolean noFire;

	private JPanel viewArea1;
	private JPanel viewArea2;
	private JPanel viewArea3;
	private JPanel viewArea4;
/*	private JScrollPane areaScrollPane1;
	private JScrollPane areaScrollPane2;
	private JScrollPane areaScrollPane3;
	private JScrollPane areaScrollPane4;
*/
	
	private JComboBox dateStyle;
	private JRadioButton spaceCheck;
	private JRadioButton dateTimeRadio;
	private JRadioButton dateRadio;
	private JRadioButton timeRadio;
	private JRadioButton tagRadio;
	private JRadioButton nanRadio;
	private JComboBox timeStyle;
	private JComboBox dateTimeStyle;
	private DefaultListModel columnStyleListModel;
	private DefaultListModel rowStyleListModel;
	private DefaultListModel conversionListModel;
	private JList columnStyleList;
	private JList rowStyleList;
	private JList conversionList;
	private JTextField columnInput;
	private JTextField rowInput;
	private JTextField symbolInput;
	private JTextField numberInput;
	private String file;
	private String directory;

	private URL url;


	private int rows;
	private int columns;
	private Vector dataPreviewStrings;
	private String separateString;
	private Vector previewColumns;
	private int[] maxStrLengths;
	
	private NolMainFrame frame;
	private int rowFormatIndex; // 0:tag; 1:unit; 2:skip
	private int columnFormatIndex; // 0:date&time,1:date,2:time,3:ignore
	private int symbolFormatIndex; // 0:number; 1:NaN; 2:ignore row
	private Vector columnStyles;
	private Vector rowStyles;
	private Vector symbolStyles;

	private Vector dateFormatVector;
	private Vector timeFormatVector;
	private Vector dateTimeFormatVector;

 	private	DataStringTableModel delimiterTableModel;
 	private	DataStringTableModel rowTableModel;
 	private	DataStringTableModel columnTableModel;
 	private	DataStringTableModel symbolTableModel;
 	private	JTable delimiterTableView;
 	private	JTable rowTableView;
 	private	JTable columnTableView;
 	private	JTable symbolTableView;

	private static String[] dateFormat = 
			{"M/d/y", 
			"d/M/y",
			"M/d",
			"d/M",
			"M/y",
			"dd-MM-yy",
			"MM-yy"
	};

 	private static String[] timeFormat = 
			{"H:m:s", 
			"H:m",
			"m:s",
			"h:m a",
			"m:s a",
			"h:m:s a",
			"HH:mm:ss"
	};

 	private static String[] dateTimeFormat = 
			{"M/d/y h:m:s a", 
			"M/d/y H:m:s",
			"M/d/y h:m a",
			"M/d/y H:m",
			"d/M/y h:m:s a",
			"d/M/y H:m:s",
			"d/M/y h:m a",
			"d/M/y H:m",
			"M/d h:m:s a",
			"M/d H:m:s",
			"M/d h:m a",
			"M/d H:m",
			"dd-MMM-yy HH:mm:ss"
	};

	private String[] columnStyleText;
	private String[] rowStyleText;
	private DataSeriesFileFormat format;

	public NolDataSeriesInputWizard (JFrame dw, String title) {
		super(dw, title, true, 6);
		frame = (NolMainFrame)dw;
		actionListener = new ControlAction();
		format = new DataSeriesFileFormat();
		noFire = false;

		dateFormatVector = new Vector();
		timeFormatVector = new Vector();
		dateTimeFormatVector = new Vector();
		Vector holdVector = new Vector();
		
		//add custom formats, if they exist, first
		holdVector = NolSettings.getSettings().getCustomDateFormatsVector();
		if (holdVector != null && !holdVector.isEmpty()){
		  for (int i=0; i<holdVector.size();i++)
		    dateFormatVector.addElement(holdVector.elementAt(i));
		}
		for(int i=0;i<dateFormat.length;i++)
			dateFormatVector.addElement(dateFormat[i]);
		  
		holdVector = NolSettings.getSettings().getCustomTimeFormatsVector();
		if (holdVector != null && !holdVector.isEmpty()){
		  for (int i=0; i<holdVector.size();i++)
		    timeFormatVector.addElement(holdVector.elementAt(i));
		}
		for(int i=0;i<timeFormat.length;i++)
			timeFormatVector.addElement(timeFormat[i]);

		holdVector = NolSettings.getSettings().getCustomDateTimeFormatsVector();
		if(holdVector != null && !holdVector.isEmpty()){
		  for (int i=0; i<holdVector.size();i++)
		    dateTimeFormatVector.addElement(holdVector.elementAt(i));
		}
		for(int i=0;i<dateTimeFormat.length;i++)
			dateTimeFormatVector.addElement(dateTimeFormat[i]);

		initializeLayout();
		initializeData();
	}

	public NolDataSeriesInputWizard (JFrame dw, String title, String fileName, String dir) {
		this(dw, title);
		this.file = fileName;
		this.directory = dir;
		if(dir == null) {
			dataPreviewStrings = readFromFile(file);
		}else{
			dataPreviewStrings = readFromFile(directory, file);
		}
		if(dataPreviewStrings.isEmpty()) {
			// did not find the file, or it was empty
			isOK = false;
			dispose();
			return;
		}
		updatePreviewDisplay();
		String fn = displayName(fileName);
		dataSeriesName.setText(fn);
		String cName = fn + frame.getNolResourceString(FORMAT_LABEL);
		fileFormatName.setText(cName);
		format = new DataSeriesFileFormat(cName);
	}

	private void initializeData(){
		rows = 0;
		columns = 0;
		separateString = String.valueOf('\u0020');
		previewColumns =new Vector();
		columnFormatIndex = 0;
		rowFormatIndex = 0;
		symbolFormatIndex = 0;
		columnStyles  =new Vector();
		rowStyles  =new Vector();
		symbolStyles  =new Vector();
		noFire = true;
		spaceCheck.setSelected(true);
		tagRadio.setSelected(true);
		dateTimeRadio.setSelected(true);
		nanRadio.setSelected(true);
		noFire = false;
		dataSeriesDescript.setText("");
		fileFormatDescript.setText("");
		otherDelimiter.setText("");
		columnInput.setText("");
		rowInput.setText("");
		symbolInput.setText("");
		numberInput.setText("");
		getColumnStyleListModel().removeAllElements();
		getRowStyleListModel().removeAllElements();
		getConversionListModel().removeAllElements();
		isOK = false;

		columnStyleText = new String[4];
		columnStyleText[0] = frame.getNolResourceString(DATE_TIME_LABEL);
		columnStyleText[1] = frame.getNolResourceString(DATE_LABEL);
		columnStyleText[2] = frame.getNolResourceString(TIME_LABEL);
		columnStyleText[3] = frame.getNolResourceString(IGNORED_LABEL);

		rowStyleText = new String[4];
		rowStyleText[0] = frame.getNolResourceString(TAGS);
		rowStyleText[1] = frame.getNolResourceString(UNITS);
		rowStyleText[2] = frame.getNolResourceString(NAMES);
		rowStyleText[3] = frame.getNolResourceString(IGNORE_ROW_LABEL);
	}
	
	private void initializeLayout(){
		stepPanes.setElementAt(getGeneralPanel(),0);
		stepPanes.setElementAt(getDelimiterPanel(),1);
		stepPanes.setElementAt(getColumnFormatPane(),2);
		stepPanes.setElementAt(getRowFormatPane(),3);
		stepPanes.setElementAt(getSymbolPane(),4);
		stepPanes.setElementAt(getNumberFormatPane(),5);
	}


	public void setFile(String dir, String fileName) {
		this.file = fileName;
		this.directory = dir;
		if(dir == null){
			dataPreviewStrings = readFromFile(file);
		}else {
			dataPreviewStrings = readFromFile(directory, file);
		}
		if(dataPreviewStrings.isEmpty()) {
			// did not find the file, or it was empty
			isOK = false;
			dispose();
			return;
		}
		updatePreviewDisplay();
		String fn = displayName(fileName);
		dataSeriesName.setText(fn);
		String cName = fn + frame.getNolResourceString(FORMAT_LABEL);
		fileFormatName.setText(cName);
		format = new DataSeriesFileFormat(cName);
	}

	public void setURL(URL url) {
		this.url = url;
		dataPreviewStrings = readFromFile(url);
		if(dataPreviewStrings.isEmpty()) {
			// did not find the file, or it was empty
			isOK = false;
			dispose();
			return;
		}
		this.file = url.getFile();
		this.directory = null;
		updatePreviewDisplay();
		String fn = displayName(url.getFile());
		dataSeriesName.setText(fn);
		String cName = fn + frame.getNolResourceString(FORMAT_LABEL);
		fileFormatName.setText(cName);
		format = new DataSeriesFileFormat(cName);
	}

	public DataSeriesFileFormat getDataSeriesFileFormat(){
		return format;
	}

 	public String getDataSeriesFileFormatComment(){
		return fileFormatDescript.getText();
	}


	public String getDataSeriesName(){
		return dataSeriesName.getText();
	}

	public String getDataSeriesComment(){
		return dataSeriesDescript.getText();
	}

	private JPanel getGeneralPanel(){
		JPanel genPane = new JPanel(new BorderLayout());
		URL imageUrl = this.getClass().getResource("largeimport.gif");
		ImageIcon importIcon = new ImageIcon(imageUrl);

		JPanel infoPane = new JPanel(new BorderLayout());
 		infoPane.setBorder(new EmptyBorder(10,10,10,10));

		JTextArea infoLabel = new JTextArea(frame.getNolResourceString(IMPORT_LABEL));
		infoLabel.setEditable(false);
		infoLabel.setLineWrap(true);
		infoLabel.setWrapStyleWord(true);
		infoLabel.setBackground(infoPane.getBackground());
		infoPane.add("Center",infoLabel);
		infoPane.add("West",new JLabel(importIcon));

		genPane.add("North",infoPane);

		JPanel cenPane = new JPanel(new BorderLayout());
		JPanel namePane = new JPanel(new GridLayout(3,2,10,5));
 		namePane.setBorder(new EmptyBorder(10,10,10,10));
		namePane.add(new JLabel(frame.getNolResourceString(NAME_DS_LABEL) + ":"));
		namePane.add(new JLabel(frame.getNolResourceString(NAME_FF_LABEL) + ":"));
		dataSeriesName = new JTextField();
		namePane.add(dataSeriesName);
		fileFormatName = new JTextField();
		namePane.add(fileFormatName);
		namePane.add(new JLabel(frame.getNolResourceString(COMMENT_DS_LABEL) + ":"));
		namePane.add(new JLabel(frame.getNolResourceString(COMMENT_FF_LABEL) + ":"));
 		cenPane.add("North",namePane);

		JPanel descripPane = new JPanel(new GridLayout(1,2,10,5));
 		descripPane.setBorder(new EmptyBorder(0,10,10,10));
		dataSeriesDescript = new JTextArea();		
		JScrollPane listScrollPane = new JScrollPane(dataSeriesDescript);
		listScrollPane.setBorder(BorderFactory.createLoweredBevelBorder());
		descripPane.add(listScrollPane);
		fileFormatDescript = new JTextArea();
		listScrollPane = new JScrollPane(fileFormatDescript);
		listScrollPane.setBorder(BorderFactory.createLoweredBevelBorder());
		descripPane.add(listScrollPane);
 		cenPane.add("Center",descripPane);

 		genPane.add("Center",cenPane);
		return genPane;
	}

	private JPanel getDelimiterPanel(){
		JPanel delimiterPane = new JPanel(new BorderLayout());
		JPanel infoPane = new JPanel(new GridLayout());
 		infoPane.setBorder(new EmptyBorder(10,10,10,10));
		JTextArea infoLabel = new JTextArea(frame.getNolResourceString(WHAT_IS_DELIMITERS_LABEL));
		infoLabel.setEditable(false);
		infoLabel.setLineWrap(true);
		infoLabel.setWrapStyleWord(true);
		infoLabel.setBackground(infoPane.getBackground());
		infoPane.add(infoLabel);
		delimiterPane.add("North",infoPane);

		JPanel cenPane = new JPanel(new BorderLayout());		
 		cenPane.setBorder(new EmptyBorder(10,10,10,10));

		JPanel delPane = new JPanel();
		delPane.setLayout(new GridLayout(2,3,5,5));
		delPane.setBorder(BorderFactory.createTitledBorder(frame.getNolResourceString(DELIMITERS_LABEL)));
		ButtonGroup group = new ButtonGroup();
		spaceCheck = new JRadioButton(frame.getNolResourceString(SPACE_LABEL),true);
		spaceCheck.setActionCommand("Space");
		spaceCheck.addActionListener(actionListener);
		group.add(spaceCheck);
		delPane.add(spaceCheck);
		JRadioButton check = new JRadioButton(frame.getNolResourceString(SEMICOLON_LABEL));
		check.setActionCommand("Semicolon");
		check.addActionListener(actionListener);
		group.add(check);
		delPane.add(check);
		check = new JRadioButton(frame.getNolResourceString(OTHER_LABEL));
		check.setActionCommand("Other");
		check.addActionListener(actionListener);
		group.add(check);
		delPane.add(check);
		check = new JRadioButton(frame.getNolResourceString(COMMA_LABEL));
		check.setActionCommand("Comma");
		check.addActionListener(actionListener);
		group.add(check);
		delPane.add(check);
		check = new JRadioButton(frame.getNolResourceString(TAB_LABEL));
		check.setActionCommand("Tab");
		check.addActionListener(actionListener);
		group.add(check);
		delPane.add(check);
		otherDelimiter = new JTextField();
		otherDelimiter.addActionListener(actionListener);
 		delPane.add(otherDelimiter);

		cenPane.add("North",delPane);

		cenPane.add("Center",getDataPreviewPanel(1));

		delimiterPane.add("Center",cenPane);
		return delimiterPane;

	}

 	private JPanel getColumnFormatPane(){
		JPanel colPane = new JPanel(new BorderLayout());
		JPanel infoPane = new JPanel(new GridLayout());
 		infoPane.setBorder(new EmptyBorder(10,10,5,10));
		JTextArea infoLabel = new JTextArea(frame.getNolResourceString(COLUMN_FORMAT_TEXT));
		infoLabel.setLineWrap(true);
		infoLabel.setWrapStyleWord(true);
		infoLabel.setEditable(false);
		infoLabel.setBackground(infoPane.getBackground());
		infoPane.add(infoLabel);
		colPane.add("North",infoPane);


		JPanel cenPane = new JPanel(new BorderLayout());		
 		cenPane.setBorder(new EmptyBorder(0,10,10,10));

		JPanel formatPane = new JPanel(new BorderLayout());
		formatPane.setBorder(BorderFactory.createTitledBorder(frame.getNolResourceString(COLUMN_FORMAT_TITLE)));

		JPanel formatSetPane = new JPanel();
 		formatSetPane.setBorder(new EmptyBorder(0,10,0,0));
		formatSetPane.setLayout(new BoxLayout(formatSetPane, BoxLayout.X_AXIS));

		JPanel pane1 = new JPanel(new GridLayout(4,1,5,5));
		//eg - rearrange layout
		
		dateTimeStyle = new JComboBox();
		for(int i=0;i<dateTimeFormatVector.size();i++)
			dateTimeStyle.addItem(dateTimeFormatVector.elementAt(i));
		dateTimeStyle.addActionListener(actionListener);
		pane1.add(dateTimeStyle);
		
		dateStyle = new JComboBox();
		for(int i=0;i<dateFormatVector.size();i++)
			dateStyle.addItem(dateFormatVector.elementAt(i));
		dateStyle.addActionListener(actionListener);
		pane1.add(dateStyle);

		timeStyle = new JComboBox();
		for(int i=0;i<timeFormatVector.size();i++)
			timeStyle.addItem(timeFormatVector.elementAt(i));
 		timeStyle.addActionListener(actionListener);
		pane1.add(timeStyle);
		
		formatSetPane.add(pane1);
		
		pane1 = new JPanel(new GridLayout(4,1,5,5));
		pane1.setBorder(new EmptyBorder(0,5,0,0));
		
		ButtonGroup group = new ButtonGroup();
		dateTimeRadio = new JRadioButton(frame.getNolResourceString(DATE_TIME_LABEL),true);
		dateTimeRadio.setActionCommand("Date&Time");
		dateTimeRadio.addActionListener(actionListener);
		pane1.add(dateTimeRadio);
		group.add(dateTimeRadio);

		dateRadio = new JRadioButton(frame.getNolResourceString(DATE_LABEL), true);
		dateRadio.setActionCommand("Date");
		dateRadio.addActionListener(actionListener);
		pane1.add(dateRadio);
		group.add(dateRadio);

		timeRadio = new JRadioButton(frame.getNolResourceString(TIME_LABEL));
		timeRadio.setActionCommand("Time");
		timeRadio.addActionListener(actionListener);
		pane1.add(timeRadio);
		group.add(timeRadio);

		JRadioButton radio = new JRadioButton(frame.getNolResourceString(IGNORED_LABEL));
		radio.setActionCommand("columnIgnore");
		radio.addActionListener(actionListener);
		pane1.add(radio);
		group.add(radio);

		formatSetPane.add(pane1);

		pane1 = new JPanel(new GridLayout(4,1,5,5));
		pane1.setBorder(new EmptyBorder(0,20,0,0));

		JButton butt = new JButton(frame.getNolResourceString(SET_LABEL));
		butt.setActionCommand("columnSet");
		butt.addActionListener(actionListener);
		pane1.add(butt);

		butt = new JButton(frame.getNolResourceString(REMOVE_LABEL));
		butt.setActionCommand("columnRemove");
		butt.addActionListener(actionListener);
 		pane1.add(butt);
		
		//eg - custom formats
		butt = new JButton (frame.getNolResourceString(CUSTOM_FORMAT));
		butt.setActionCommand("custFormat");
		butt.addActionListener(actionListener);
		pane1.add(butt);
		
 		formatSetPane.add(pane1);

 		columnStyleList = new JList(getColumnStyleListModel());
		columnStyleList.setBackground(Color.white);
		JScrollPane listScrollPane = new JScrollPane(columnStyleList);
		listScrollPane.setBorder(BorderFactory.createLoweredBevelBorder());
		listScrollPane.setPreferredSize(NolMainFrame.vpad20);
		
		pane1 = new JPanel(new BorderLayout());
		JPanel pane0 = new JPanel(new GridLayout(1,2,2,2));
		pane0.add(new JLabel(frame.getNolResourceString(COLUMN_LABEL) + ":"));
		columnInput = new JTextField();
		pane0.add(columnInput);
		pane1.add("North",pane0);
		pane1.add("Center",listScrollPane);

		formatPane.add("East", formatSetPane);
		formatPane.add("Center", pane1);
		cenPane.add("North",formatPane);
		cenPane.add("Center",getDataPreviewPanel(2));
		colPane.add("Center",cenPane);

		return colPane;
	}
 	private JPanel getRowFormatPane(){
		JPanel rowPane = new JPanel(new BorderLayout());
		JPanel infoPane = new JPanel(new GridLayout());
 		infoPane.setBorder(new EmptyBorder(10,10,5,10));
		JTextArea infoLabel = new JTextArea(frame.getNolResourceString(ROW_FORMAT_TEXT));
		infoLabel.setEditable(false);
		infoLabel.setLineWrap(true);
		infoLabel.setWrapStyleWord(true);
		infoLabel.setBackground(infoPane.getBackground());
		infoPane.add(infoLabel);
		rowPane.add("North",infoPane);

		JPanel cenPane = new JPanel(new BorderLayout());		
 		cenPane.setBorder(new EmptyBorder(0,10,10,10));

		JPanel formatPane = new JPanel(new GridLayout(1,2,20,20));
		formatPane.setBorder(BorderFactory.createTitledBorder(
			frame.getNolResourceString(ROW_FORMAT_TITLE)));

		JPanel formatSetPane = new JPanel(new GridLayout(2,3,10,5));
 		formatSetPane.setBorder(new EmptyBorder(15,0,0,0));

		
		tagRadio = new JRadioButton(frame.getNolResourceString(TAGS),true);
		tagRadio.setActionCommand("Tags");
		tagRadio.addActionListener(actionListener);
		ButtonGroup group = new ButtonGroup();
		group.add(tagRadio);
		formatSetPane.add(tagRadio);

 		JRadioButton radio = new JRadioButton(frame.getNolResourceString(UNITS));
		radio.setActionCommand("Units");
		radio.addActionListener(actionListener);
		group.add(radio);
		formatSetPane.add(radio);

		JButton butt = new JButton(frame.getNolResourceString(SET_LABEL));
		butt.setActionCommand("rowSet");
		butt.addActionListener(actionListener);
		formatSetPane.add(butt);

		radio = new JRadioButton(frame.getNolResourceString(NAMES));
		radio.setActionCommand("Names");
		radio.addActionListener(actionListener);
		group.add(radio);
		formatSetPane.add(radio);

		radio = new JRadioButton(frame.getNolResourceString(IGNORE_ROW_LABEL));
		radio.setActionCommand("rowIgnore");
		radio.addActionListener(actionListener);
		group.add(radio);
		formatSetPane.add(radio);

		butt = new JButton(frame.getNolResourceString(REMOVE_LABEL));
		butt.setActionCommand("rowRemove");
		butt.addActionListener(actionListener);
		formatSetPane.add(butt);

 		rowStyleList = new JList(getRowStyleListModel());
		rowStyleList.setBackground(Color.white);
		JScrollPane listScrollPane = new JScrollPane(rowStyleList);
		listScrollPane.setBorder(BorderFactory.createLoweredBevelBorder());
		listScrollPane.setPreferredSize(NolMainFrame.pad5020);
		
		JPanel pane1 = new JPanel(new BorderLayout());
		JPanel pane0 = new JPanel(new GridLayout(1,2,2,2));
		pane0.add(new JLabel(frame.getNolResourceString(ROW)+":"));
		rowInput = new JTextField();
		pane0.add(rowInput);
		pane1.add("North",pane0);
		pane1.add("Center",listScrollPane);

		formatPane.add(pane1);
		formatPane.add(formatSetPane);
		cenPane.add("North",formatPane);
		cenPane.add("Center",getDataPreviewPanel(3));
		rowPane.add("Center",cenPane);

		return rowPane;
	}

	private JPanel getSymbolPane(){
		JPanel symPane = new JPanel(new BorderLayout());
		JPanel infoPane = new JPanel(new GridLayout());
 		infoPane.setBorder(new EmptyBorder(10,10,2,10));
		JTextArea infoLabel = new JTextArea(frame.getNolResourceString(SYMBOL_PANE_TEXT));
		infoLabel.setEditable(false);
		infoLabel.setLineWrap(true);
		infoLabel.setWrapStyleWord(true);
		infoLabel.setBackground(infoPane.getBackground());
		infoPane.add(infoLabel);
		symPane.add("North",infoPane);

		JPanel cenPane = new JPanel(new BorderLayout());		
 		cenPane.setBorder(new EmptyBorder(0,10,10,10));

		JPanel formatPane = new JPanel(new GridLayout(1,2,20,20));
		formatPane.setBorder(BorderFactory.createTitledBorder(frame.getNolResourceString(TEXT_CONVERSION_LABEL)));

		JPanel formatSetPane = new JPanel(new GridLayout(2,3,10,5));
 		formatSetPane.setBorder(new EmptyBorder(15,0,0,0));
		
		nanRadio = new JRadioButton(frame.getNolResourceString(NAN),true);
		nanRadio.setActionCommand("NaN");
		ButtonGroup group = new ButtonGroup();
		nanRadio.addActionListener(actionListener);
		group.add(nanRadio);
		formatSetPane.add(nanRadio);

		JRadioButton radio = new JRadioButton(frame.getNolResourceString(IGNORE_ROW_LABEL));
		radio.setActionCommand("Ignore Row");
		radio.addActionListener(actionListener);
		group.add(radio);
		formatSetPane.add(radio);


		JButton butt = new JButton(frame.getNolResourceString(SET_LABEL));
		butt.setActionCommand("SymbolSet");
		butt.addActionListener(actionListener);
		formatSetPane.add(butt);

		radio  = new JRadioButton(frame.getNolResourceString(NUMBER_LABEL)+ ":");
		radio.setActionCommand("Number:");
		radio.addActionListener(actionListener);
		group.add(radio);
		formatSetPane.add(radio);

		numberInput = new JTextField();
		formatSetPane.add(numberInput);


		butt = new JButton(frame.getNolResourceString(REMOVE_LABEL));
		butt.setActionCommand("symbolRemove");
		butt.addActionListener(actionListener);
		formatSetPane.add(butt);


 		conversionList = new JList(getConversionListModel());
		conversionList.setBackground(Color.white);
		JScrollPane listScrollPane = new JScrollPane(conversionList);
		listScrollPane.setBorder(BorderFactory.createLoweredBevelBorder());
		listScrollPane.setPreferredSize(NolMainFrame.pad5020);
		
		JPanel pane1 = new JPanel(new BorderLayout());
		JPanel pane0 = new JPanel(new GridLayout(1,2,2,2));
		pane0.add(new JLabel(frame.getNolResourceString(SYMBOL)+":"));
		symbolInput = new JTextField();
		pane0.add(symbolInput);
		pane1.add("North",pane0);
		pane1.add("Center",listScrollPane);

		formatPane.add(pane1);
		formatPane.add(formatSetPane);
		cenPane.add("North",formatPane);
		cenPane.add("Center",getDataPreviewPanel(4));
		symPane.add("Center",cenPane);

		return symPane;
	}


	private JPanel getNumberFormatPane(){
		JPanel formatPane = new JPanel(new BorderLayout());
		JPanel infoPane = new JPanel(new GridLayout());
 		infoPane.setBorder(new EmptyBorder(10,10,2,10));
		JTextArea infoLabel = new JTextArea(frame.getNolResourceString(FORMAT_PANE_TEXT));
		infoLabel.setEditable(false);
		infoLabel.setLineWrap(true);
		infoLabel.setWrapStyleWord(true);
		infoLabel.setBackground(infoPane.getBackground());
		infoPane.add(infoLabel);
		formatPane.add("North",infoPane);

		JPanel cenPane = new JPanel(new GridLayout(4,1,10,10));		
		cenPane.setBorder(BorderFactory.createTitledBorder(
			frame.getNolResourceString(FORMAT_CHOICE)));
		
		JRadioButton radio = new JRadioButton(frame.getNolResourceString(ENGLISH),true);
		radio.setActionCommand("English");
		ButtonGroup group = new ButtonGroup();
		radio.addActionListener(actionListener);
		group.add(radio);
		cenPane.add(radio);

		radio = new JRadioButton(frame.getNolResourceString(FRENCH));
		radio.setActionCommand("French");
		radio.addActionListener(actionListener);
		group.add(radio);
		cenPane.add(radio);

		radio = new JRadioButton(frame.getNolResourceString(GERMAN));
		radio.setActionCommand("German");
		radio.addActionListener(actionListener);
		group.add(radio);
		cenPane.add(radio);
		
/*		radio = new JRadioButton(frame.getNolResourceString(ITALIAN));
		radio.setActionCommand("Italian");
		radio.addActionListener(actionListener);
		group.add(radio);
		cenPane.add(radio);
*/	
		formatPane.add("Center",cenPane);

		return formatPane;
	}

	private DefaultListModel getColumnStyleListModel() {
		if (columnStyleListModel == null) {
			columnStyleListModel = new DefaultListModel();
		}	
		return columnStyleListModel;
	}	

	private DefaultListModel getRowStyleListModel() {
		if (rowStyleListModel == null) {
			rowStyleListModel = new DefaultListModel();
		}	
		return rowStyleListModel;
	}	

	private DefaultListModel getConversionListModel() {
		if (conversionListModel == null) {
			conversionListModel = new DefaultListModel();
		}	
		return conversionListModel;
	}	

	private JPanel getDataPreviewPanel(int viewIndex){

		if(viewIndex == 1){
			JPanel dataPreview = new JPanel();
			dataPreview.setLayout(new GridLayout());
			dataPreview.setBorder(BorderFactory.createTitledBorder(
				frame.getNolResourceString(DATA_PREVIEW)+":"));
			
			JPanel tablePane = new JPanel(new GridLayout());
			delimiterTableView = new JTable();
			delimiterTableView.setCellSelectionEnabled(false);
			delimiterTableView.setColumnSelectionAllowed(false);
			delimiterTableView.setRowSelectionAllowed(false);
			JScrollPane listScrollPane = new JScrollPane(delimiterTableView);
			listScrollPane.setBackground(Color.white);
			tablePane.add(listScrollPane);
			dataPreview.add(tablePane);
			return dataPreview;
		}else if(viewIndex == 2){
			JPanel dataPreview = new JPanel();
			dataPreview.setLayout(new GridLayout());
			dataPreview.setBorder(BorderFactory.createTitledBorder(
				frame.getNolResourceString(DATA_PREVIEW)+":"));

			JPanel tablePane = new JPanel(new GridLayout());
			columnTableView = new JTable();
			columnTableView.setSelectionMode(0);
			columnTableView.setCellSelectionEnabled(false);
			columnTableView.setColumnSelectionAllowed(true);
			columnTableView.setRowSelectionAllowed(false);
			columnTableView.getTableHeader().setReorderingAllowed(false);
			columnTableView.getSelectionModel().addListSelectionListener((ListSelectionListener)actionListener);
			columnTableView.getColumnModel().getSelectionModel().addListSelectionListener((ListSelectionListener)actionListener);			
			JScrollPane listScrollPane = new JScrollPane(columnTableView);
			listScrollPane.setBackground(Color.white);
			tablePane.add(listScrollPane);
			dataPreview.add(tablePane);
			return dataPreview;
		}else if(viewIndex == 3){
			JPanel dataPreview = new JPanel();
			dataPreview.setLayout(new GridLayout());
			dataPreview.setBorder(BorderFactory.createTitledBorder(
				frame.getNolResourceString(DATA_PREVIEW)+":"));
			
			JPanel tablePane = new JPanel(new GridLayout());
			rowTableView = new JTable();
			rowTableView.setSelectionMode(0);
			rowTableView.setCellSelectionEnabled(false);
			rowTableView.setColumnSelectionAllowed(false);
			rowTableView.setRowSelectionAllowed(true);
			rowTableView.getSelectionModel().addListSelectionListener((ListSelectionListener)actionListener);
			JScrollPane listScrollPane = new JScrollPane(rowTableView);
			listScrollPane.setBackground(Color.white);
			tablePane.add(listScrollPane);
			dataPreview.add(tablePane);
	
			return dataPreview;
		}else {
			JPanel dataPreview = new JPanel();
			dataPreview.setLayout(new GridLayout());
			dataPreview.setBorder(BorderFactory.createTitledBorder(
				frame.getNolResourceString(DATA_PREVIEW)+":"));
			
			JPanel tablePane = new JPanel(new GridLayout());
			symbolTableView = new JTable();
			symbolTableView.setSelectionMode(0);
			symbolTableView.setCellSelectionEnabled(false);
			symbolTableView.setColumnSelectionAllowed(false);
			symbolTableView.setRowSelectionAllowed(false);
			JScrollPane listScrollPane = new JScrollPane(symbolTableView);
			listScrollPane.setBackground(Color.white);
			tablePane.add(listScrollPane);
			dataPreview.add(tablePane);

			return dataPreview;
		}

	}

	@Override
	public void setVisible(boolean v){
 		stepPane.removeAll();
		stepPane.add((JPanel)stepPanes.elementAt(0));
		stepPane.validate();
		stepPane.repaint(0l);
		currentStep = 0;
		modifyStep(true);
		String title = "Import Data Series - "+setTitleForStep(currentStep);
		title = title + " - General";
		setTitle(title);
		super.setVisible(v);
	}

	public void resetData(){
		initializeData();
	}

	@Override
	protected void modifyStep(boolean isNext){
		super.modifyStep(isNext);
		String title = "Import Data Series - "+setTitleForStep(currentStep);
		if(currentStep == 1){
			title = title + " - General";
		}else if(currentStep == 2){
			title = title + " - Delimiter";
		}else if(currentStep == 3){
			title = title + " - Column";
		}else if(currentStep == 4){
			title = title + " - Row";
		}else if(currentStep == 5){
			title = title + " - Symbol";
		}else if(currentStep == 6){
			title = title + " - Decimal Format";
		}		
		if(DEBUG.debugFlag){
				System.out.println(title);
		}
		setTitle(title);
	}

	private Vector readFromFile(String fileName){
		return readFromFile(null, fileName);
	}

	private Vector readFromFile(String directory, String fileName) {	
		File SourceFile;
		if(directory == null){
			SourceFile = new File(fileName);
		}else {
			SourceFile = new File(directory,fileName);
		}
		BufferedReader Source = null;
		Vector dataString = new Vector();
		if (!SourceFile.exists() || !SourceFile.isFile() || !SourceFile.canRead()) 
			return dataString;  // returning empty vector to signify failure
		
		FileInputStream inStream = null;
		Reader streamReader = null;
        try{
        	inStream= new FileInputStream(SourceFile);
        	streamReader = new InputStreamReader(inStream, Charset.defaultCharset());
			Source = new BufferedReader(streamReader);
			rows = 0;
			while(rows <21) {
				String lineStr = Source.readLine();	
				if (lineStr == null){
					break;
				}
				dataString.addElement(lineStr); 
				rows++;
			}
		} catch (EOFException e){
			System.err.println("Non-Fatal exception: " + e.getMessage());
			e.printStackTrace();
		} catch (IOException e){
			System.err.println("Non-Fatal exception: " + e.getMessage());
			e.printStackTrace();
		} finally {
			closeSilently(Source);
			closeSilently(streamReader);
			closeSilently(inStream);
        }
		return dataString;
	}
	
	private void closeSilently(Closeable obj){
	  try {
	      if (obj != null) 
	    	  obj.close();
      } catch (IOException e) {
    	  System.err.println("Non-Fatal exception: Error while closing stream : " + e.toString());
    	  e.printStackTrace();
      } 
	}

	private Vector readFromFile(URL url) {	
		BufferedReader Source = null;
		Vector dataString = new Vector();
		Reader streamReader = null;
        try{
        	streamReader = new InputStreamReader(url.openStream(), Charset.defaultCharset());
			Source = new BufferedReader(streamReader);
			rows = 0;
			while(rows <21) {
				String lineStr = Source.readLine();	
				if (lineStr == null) {
					break;
				}
				dataString.addElement(lineStr); 
				rows++;
			}
		} catch (EOFException e){
			System.err.println("Non-Fatal exception: " + e.getMessage());
			e.printStackTrace();
			return dataString;  // returning empty vector to signify failure
		} catch (IOException e){
			System.err.println("Non-Fatal exception: " + e.getMessage());
			e.printStackTrace();
			return dataString;  // returning empty vector to signify failure
		} finally {
            closeSilently(Source);
            closeSilently(streamReader);
        }
		return dataString;
	}

 	private void updatePreviewDisplay(){
//		System.out.println("updatePreviewDisplay");
		convertStringWithDelimiter(separateString);

		delimiterTableModel = new DataStringTableModel();
		rowTableModel = new DataStringTableModel();
		columnTableModel = new DataStringTableModel();
		symbolTableModel = new DataStringTableModel();

		delimiterTableModel.resetTable();
		rowTableModel.resetTable();
		columnTableModel.resetTable();
		symbolTableModel.resetTable();

		delimiterTableView.setModel(delimiterTableModel);
		rowTableView.setModel(rowTableModel);
		columnTableView.setModel(columnTableModel);
		symbolTableView.setModel(symbolTableModel);

		delimiterTableView.getTableHeader().setReorderingAllowed(false);
		rowTableView.getTableHeader().setReorderingAllowed(false);
		columnTableView.getTableHeader().setReorderingAllowed(false);
		symbolTableView.getTableHeader().setReorderingAllowed(false);

		int colCount = previewColumns.size();
		if(colCount<5 && colCount>0){
			delimiterTableView.setAutoResizeMode(JTable.AUTO_RESIZE_ALL_COLUMNS);
			rowTableView.setAutoResizeMode(JTable.AUTO_RESIZE_ALL_COLUMNS);
			columnTableView.setAutoResizeMode(JTable.AUTO_RESIZE_ALL_COLUMNS);
			symbolTableView.setAutoResizeMode(JTable.AUTO_RESIZE_ALL_COLUMNS);
			delimiterTableView.sizeColumnsToFit(-1);
			rowTableView.sizeColumnsToFit(-1);
			columnTableView.sizeColumnsToFit(-1);
			symbolTableView.sizeColumnsToFit(-1);
		}else{
			delimiterTableView.setAutoResizeMode(JTable.AUTO_RESIZE_OFF);
			rowTableView.setAutoResizeMode(JTable.AUTO_RESIZE_OFF);
			columnTableView.setAutoResizeMode(JTable.AUTO_RESIZE_OFF);
			symbolTableView.setAutoResizeMode(JTable.AUTO_RESIZE_OFF);
			TableColumnModel cm1 = delimiterTableView.getColumnModel();
			TableColumnModel cm2 = rowTableView.getColumnModel();
			TableColumnModel cm3 = columnTableView.getColumnModel();
			TableColumnModel cm4 = symbolTableView.getColumnModel();
			cm1.getColumn(0).setWidth(30);
			cm2.getColumn(0).setWidth(30);
			cm3.getColumn(0).setWidth(30);
			cm4.getColumn(0).setWidth(30);
		}

/*		TableColumnModel cm1 = delimiterTableView.getColumnModel();
		TableColumnModel cm2 = rowTableView.getColumnModel();
		TableColumnModel cm3 = columnTableView.getColumnModel();
		TableColumnModel cm4 = symbolTableView.getColumnModel();
		cm1.getColumn(0).setWidth(30);
		cm2.getColumn(0).setWidth(30);
		cm3.getColumn(0).setWidth(30);
		cm4.getColumn(0).setWidth(30);
 		if(colCount<5 && colCount>0){
			for(int i=0;i<colCount;i++){
				int w = 500/colCount; 
				cm1.getColumn(i+1).setWidth(w);
				cm2.getColumn(i+1).setWidth(w);
				cm3.getColumn(i+1).setWidth(w);
				cm4.getColumn(i+1).setWidth(w);
			}
		}
		/*  MK removed as extra code, not needed.
		if(currentStep==2) delimiterTableView.validate();
		else if (currentStep==3) columnTableView.validate();
		else if (currentStep==4) rowTableView.validate();
		else if (currentStep==5) symbolTableView.validate(); */
	}

	private String displayName(String fileName){
		int dotInd = fileName.indexOf(".");
		String fn = new String(fileName);
		if(dotInd != -1){
			fn = fileName.substring(0,dotInd);
		}
		return fn;
	}

   	private void updateRowStyleList(){
		int c = rowStyles.size();
		getRowStyleListModel().removeAllElements();
		for(int i=0;i<c;i++){
			int[] styleIndex = (int[])rowStyles.elementAt(i);
			String ss = styleIndex[0] +": " + rowStyleText[styleIndex[1]];
			getRowStyleListModel().addElement(ss);
		}
	}

	private void updateColumnStyleList(){
		int c = columnStyles.size();
		getColumnStyleListModel().removeAllElements();
		for(int i=0;i<c;i++){
			int[] styleIndex = (int[])columnStyles.elementAt(i);
			String ss = styleIndex[0] +": " + columnStyleText[styleIndex[1]];
			getColumnStyleListModel().addElement(ss);
		}
	}

	private void updateSymbolStyleList(){
		int c = symbolStyles.size();
		getConversionListModel().removeAllElements();
		for(int i=0;i<c;i++){
			Vector con = (Vector)symbolStyles.elementAt(i);
			String ss = (String)con.elementAt(0) +": " + con.elementAt(1).toString();
			getConversionListModel().addElement(ss);
		}
	}

	private void convertStringWithDelimiter(String sep){
		// parse rows to determine the number of columns (store results for later)
		int nrows = dataPreviewStrings.size();
		Vector parsedRows = new Vector(0,nrows);
		int maxCols = 0;
		for(int i=0;i<nrows;i++){
			String s = (String) dataPreviewStrings.elementAt(i);
			Vector ss = Parser.string2Strings(s,sep);
			parsedRows.addElement(ss);
			maxCols = Math.max(maxCols, ss.size());
		}
		columns = maxCols;
		// find maximum string length in each column
		maxStrLengths = new int[columns];
		for(int i=0;i<nrows;i++){
			Vector ss = (Vector) parsedRows.elementAt(i);
			int sn = ss.size();
			for(int j=0;j<sn;j++){
				maxStrLengths[j] = Math.max(sn, maxStrLengths[j]);
			}
		}
		// update the preview columns
		previewColumns.removeAllElements();
		for(int j=0;j<columns;j++) {
			previewColumns.addElement(new Vector(0,nrows));
		}
		for(int i=0;i<nrows;i++){
			Vector ss = (Vector) parsedRows.elementAt(i);
			int sn = ss.size();
			for(int j=0;j<columns;j++){
				if(j<sn){
					String subs = (String) ss.elementAt(j);
					((Vector) previewColumns.elementAt(j)).addElement(subs);
				} else {
					((Vector) previewColumns.elementAt(j)).addElement("");
				}
			}
		}
	}

  	private void selectRow(int row){
		Component[] objs3 = viewArea3.getComponents();
		int on = objs3.length;
		for(int i=0;i<on;i++){
			if(objs3[i] instanceof PreviewColumn){
				objs3[i].setBackground(Color.white);
				((PreviewColumn)objs3[i]).setSelectedRow(row);
			}
		}
		rowInput.setText(String.valueOf(row));
 		viewArea3.repaint();
		viewArea3.validate();

	}
	private void selectColumn(int column){
		Component[] objs2 = viewArea2.getComponents();
		int on = objs2.length;
		for(int i=0;i<on;i++){
			if(objs2[i] instanceof PreviewColumn){
				if(i==column) {
					objs2[i].setBackground(Color.lightGray);
				}else {
					objs2[i].setBackground(Color.white);
				}
				((PreviewColumn)objs2[i]).setSelectedRow(-1);
			}
		}
		columnInput.setText(String.valueOf(column));
 		viewArea2.repaint();
		viewArea2.validate();
	}

	private void setFileFormat(){
		format.setName(fileFormatName.getText());
		int dotInd = this.file.indexOf(".");
		if(dotInd == -1) {
			format.setSuffix("");
		}else {
			format.setSuffix(this.file.substring(dotInd));
		}
		format.setSeparator(separateString);
		format.setColumns(columns);
		int c = rowStyles.size();
		int[] igRows = new int[c];
		int count = 0;
		for(int i=0;i<c;i++){
			int[] style = (int[]) rowStyles.elementAt(i);
			if(style[1] == 0) {
				format.setTagLine(style[0]);
			}else if(style[1] == 1){
				format.setUnitLine(style[0]);
			}else if(style[1] == 2) {
				format.setNameLine(style[0]);
			}else if(style[1] == 3){
				igRows[count] = style[0];
				count++;
			}
		}
		int[] igRowsReal = new int[count];
		for(int i=0;i<count;i++) {
			igRowsReal[i] = igRows[i];
		}
		format.setIgnoredRows(igRowsReal);

		c = columnStyles.size();
		int[] igColumns = new int[c];
		count = 0;
		for(int i=0;i<c;i++){
			int[] style = (int[]) columnStyles.elementAt(i);
			if(style[1] == 0){
				format.setDateTimeColumn(style[0]);				
				int dateTimeStyleIndex = dateTimeStyle.getSelectedIndex();
				SimpleDateFormat fmt = 
					new SimpleDateFormat((String)dateTimeFormatVector.elementAt(dateTimeStyleIndex));
				format.setDateTimeFormat(fmt);
			}else if(style[1] == 1){
				format.setDateColumn(style[0]);
				int dateStyleIndex = dateStyle.getSelectedIndex();
				SimpleDateFormat fmt = new SimpleDateFormat((String)dateFormatVector.elementAt(dateStyleIndex));
				format.setDateFormat(fmt);
			}else if(style[1] == 2){
				format.setTimeColumn(style[0]);
				int timeStyleIndex = timeStyle.getSelectedIndex();
				SimpleDateFormat fmt = new SimpleDateFormat((String)timeFormatVector.elementAt(timeStyleIndex));
				format.setTimeFormat(fmt);
			}else if(style[1] == 3){
				igColumns[count] = style[0];
				count++;
			}
		}
		int[] igColumnsReal = new int[count];
		for(int i=0;i<count;i++) {
			igColumnsReal[i] = igColumns[i];
		}
		format.setIgnoredColumns(igColumnsReal);

		format.setSymbols(symbolStyles);
	}


	private Vector hasRedundentVariableNameTag(int row){
		if(row<0) {
			return null;
		}
		Vector resultVec = new Vector();
		int cols = previewColumns.size();
		Vector nameStrs = new Vector(cols);
		for(int c=0;c<cols;c++){
			Vector testCol = (Vector) previewColumns.elementAt(c);
			if(row<testCol.size()){
				nameStrs.addElement(testCol.elementAt(row));
			}
		}
		int ncols = nameStrs.size();
		for(int i=0;i<ncols;i++){
			for(int j=i+1;j<ncols;j++){
				if(nameStrs.elementAt(i).equals(nameStrs.elementAt(j))){
					resultVec.addElement(nameStrs.elementAt(i));
					resultVec.addElement(nameStrs.elementAt(j));
					return resultVec;
				}
			}

		}
		return resultVec;
	}

	@Override
	protected boolean finishAction(){
		setFileFormat();
		return true;
	}

	// Action
    class ControlAction extends AbstractAction implements ListSelectionListener, Runnable {
		String command;
		Object source;
		ControlAction() {	super("controlAction");}
        @Override
		public void actionPerformed(ActionEvent e) {
			if(noFire) {
				return;
			}
			command = e.getActionCommand ();
			source = e.getSource ();
			new Thread (this).start();
		}
		@Override
		public void run() {
//			setWaitCursor(true);

//System.out.println("command ="+command);

			if(command.equals("Space")){
				separateString = String.valueOf('\u0020');
				updatePreviewDisplay();
			}else if(command.equals("Tab")){
				separateString = String.valueOf('\u0009');
				updatePreviewDisplay();
			}else if(command.equals("Semicolon")){
				separateString = ";";
				updatePreviewDisplay();
			}else if(command.equals("Comma")){
				separateString = ",";
				updatePreviewDisplay();
			}else if(command.equals("Other") || source.equals(otherDelimiter)){
				String sep = otherDelimiter.getText();
				if(!sep.equals("")) {
					separateString = sep;
					updatePreviewDisplay();
				}
			// Row Formats
			}else if(command.equals("Tags")){
				rowFormatIndex = 0;
			}else if(command.equals("Units")){
				rowFormatIndex = 1;
			}else if(command.equals("Names")){
				rowFormatIndex = 2;
			}else if(command.equals("rowIgnore")){
				rowFormatIndex = 3;
			// Column Formats
			}else if(command.equals("Date&Time")){
				columnFormatIndex = 0;
			}else if(command.equals("Date")){
				columnFormatIndex = 1;
			}else if(command.equals("Time")){
				columnFormatIndex = 2;
			}else if(command.equals("columnIgnore")){
				columnFormatIndex = 3;
			// Symbol Formats
			}else if(command.equals("Number:")){
				symbolFormatIndex = 0;
			}else if(command.equals("NaN")){
				symbolFormatIndex = 1;
			}else if(command.equals("Ignore Row")){
				symbolFormatIndex = 2;
			}else if(command.equals("rowSet")){
				String s = rowInput.getText();
				int r = 0;
				try{
					r = Integer.valueOf(s).intValue();
					if(r<0 || r>=rows){
						rowInput.setText("");
						setWaitCursor(false);
						return;
					}
					if(rowFormatIndex == 0 || rowFormatIndex == 2){
						Vector nstrs = hasRedundentVariableNameTag(r);
						if(nstrs!=null){
							if(nstrs.size()==2){
								String n = "NAME";
								if(rowFormatIndex == 0){
									n = "TAG";
								}
								frame.showOKDialog(frame.getNolResourceString(REDUNDENT)+" "+n+" "+
									nstrs.elementAt(0)+" and "+nstrs.elementAt(1));
								setWaitCursor(false);
								return;
							}
						}
					}
					boolean found = false;
					for(int i=0;i<rowStyles.size();i++){
						int[] old = (int[])rowStyles.elementAt(i);
						if(old[0] == r){
							old[1]= rowFormatIndex;
							rowStyles.setElementAt(old,i);							
							found = true;
							break;
						}
					}
					if(!found){
						int[] rowStyle = new int[2];
						rowStyle[0] = r;
						rowStyle[1] = rowFormatIndex;
						rowStyles.addElement(rowStyle);
					}
					if(rowFormatIndex != 3){
	 					for(int i=0;i<rowStyles.size();i++){
							int[] old = (int[])rowStyles.elementAt(i);
							if(old[1] == rowFormatIndex && old[0] != r){
								rowStyles.removeElementAt(i);							
								break;
							}
						}
					}
					updateRowStyleList();
				}catch(NumberFormatException  evt){
					rowInput.setText("");
				}
			}else if(command.equals("rowRemove")){
				int n = rowStyleList.getSelectedIndex();
				if(n != -1){
					getRowStyleListModel().removeElementAt(n);
					rowStyles.removeElementAt(n);
				}
			}else if(command.equals("columnSet")){
				String s = columnInput.getText();
				int c=-1;
				try {
					c = Integer.valueOf(s).intValue();
					if(c<0 || c>=columns){
						throw new NumberFormatException();
					}
				} catch(NumberFormatException  evt){
					columnInput.setText("");
					setWaitCursor(false);
					getToolkit().beep();
					return;
				}
				// MK added 2/8/99 -- verify proposed date/time formats before committing
				if(columnFormatIndex != 3){
					DateTimeVerifier ver = new DateTimeVerifier(c,columnFormatIndex);
					boolean doIt = false;
					String type="";
					if(columnFormatIndex == 0){
						type = "date/time";
					}else if(columnFormatIndex==1) {
						type = "date";
					}else{
						type = "time";
					}
					if (ver.goodParse) {
						// if here, we could parse, but no guarantee that it is the correct parse.
						// therefore, ask the user for confirmation
						String label = "The "+type+" in row "+ver.trialRow+" has been parsed as\n"+ver.localString+". Is this correct?";
						if(frame.showYesNoDialog(label,1)==1){
							doIt = true;
						}else {
							doIt = false;
						}
					} else { // could not parse
						doIt = false;
						getToolkit().beep();
						frame.showOKDialog("Incorrect "+type+" format.");	
					}
					if(!doIt) {
						setWaitCursor(false);
						return;
					}
				}
				boolean found = false;
				for(int i=0;i<columnStyles.size();i++){
					int[] old = (int[])columnStyles.elementAt(i);
					if(old[0] == c){
						old[1]= columnFormatIndex;
						found = true;
					}
				}
				if(!found){
					int[] columnStyle = new int[2];
					columnStyle[0] = c;
					columnStyle[1] = columnFormatIndex;
					columnStyles.addElement(columnStyle);
				}
				if(columnFormatIndex != 3){
					int dt = -1;
					int d = -1;
					int t = -1;
	 				for(int i=0;i<columnStyles.size();i++){
						int[] old = (int[])columnStyles.elementAt(i);
						if(old[1] == columnFormatIndex && old[0] != c){
							columnStyles.removeElementAt(i);
						}
						if(old[1] == 0){
							dt = i;
						}else if(old[1] == 1){
							d = i;
						}else if(old[1] == 2){
							t = i;
						}
					}
					if(columnFormatIndex == 0){
						if(d != -1 && t != -1){
							if(d>t){
								columnStyles.removeElementAt(d);
								columnStyles.removeElementAt(t);
							}else{
								columnStyles.removeElementAt(t);
 								columnStyles.removeElementAt(d);
							}
						}else if(d != -1){
							columnStyles.removeElementAt(d);
						}else if(t != -1){
							columnStyles.removeElementAt(t);
						}
					} else if(columnFormatIndex==1 || columnFormatIndex==2) {
						if(dt != -1) {
							columnStyles.removeElementAt(dt);
						}
					}
				}
				updateColumnStyleList();
			} else if(command.equals("columnRemove")){
				int n = columnStyleList.getSelectedIndex();
				if(n != -1){
					getColumnStyleListModel().removeElementAt(n);
					columnStyles.removeElementAt(n);
				}
			} // eg - custom date formats
			else if (command.equals("custFormat")){
			  NolCustomDateInput customFormatDG = new
			    NolCustomDateInput (frame,
						"Custom Date and Time Formats");
			  customFormatDG.setBounds(200,100,500,500);
			  customFormatDG.setVisible(true);
			  //If dialog was OKed (getResult=true)
			  boolean result = customFormatDG.getResult();	
			  setWaitCursor(false);
//System.out.println("custFormat 0");
			  if(result){
			    
//System.out.println("custFormat 1");
			    //update format lists (Vectors and ComboBoxes)
			    //update project's custom format lists
			    Vector holdVector = new Vector();
			    holdVector = customFormatDG.getCustomTimeFormats();
			    timeFormatVector.removeAllElements();
			    for(int i=0;i<holdVector.size();i++)
			      timeFormatVector.addElement(holdVector.elementAt(i));
			    for(int i=0;i<timeFormat.length;i++)
			      timeFormatVector.addElement(timeFormat[i]);
			    
			    timeStyle.removeAllItems();
			    for (int i=0;i<timeFormatVector.size();i++)
			      timeStyle.addItem(timeFormatVector.elementAt(i));
			    
			    NolSettings.getSettings().setCustomTimeFormatsVector(holdVector);
			    

			    holdVector = customFormatDG.getCustomDateFormats();
			    dateFormatVector.removeAllElements();
			    for(int i=0;i<holdVector.size();i++)
			      dateFormatVector.addElement(holdVector.elementAt(i));
			    for(int i=0;i<dateFormat.length;i++)
			      dateFormatVector.addElement(dateFormat[i]);
			    dateStyle.removeAllItems();
			    for (int i=0;i<dateFormatVector.size();i++)
			      dateStyle.addItem(dateFormatVector.elementAt(i));
			    
			    NolSettings.getSettings().setCustomDateFormatsVector(holdVector);
			    
			    
			    holdVector = customFormatDG.getCustomDateTimeFormats();
			    dateTimeFormatVector.removeAllElements();
			    for(int i=0;i<holdVector.size();i++)
			      dateTimeFormatVector.addElement(holdVector.elementAt(i));
			    for(int i=0;i<dateTimeFormat.length;i++)
			      dateTimeFormatVector.addElement(dateTimeFormat[i]);
			    dateTimeStyle.removeAllItems();
			    for (int i=0;i<dateTimeFormatVector.size();i++)
			      dateTimeStyle.addItem(dateTimeFormatVector.elementAt(i));
			    
			    NolSettings.getSettings().setCustomDateTimeFormatsVector(holdVector);
			    NolSettings.save();
			  }
			  setWaitCursor(false);			
			} else if(command.equals("SymbolSet")){
				String sym = symbolInput.getText();
				if(sym.equals("")) {
					setWaitCursor(false);
					return;
				}
				Vector conversion = new Vector(2);
				if(symbolFormatIndex == 0){
					try{
						Double number = Double.valueOf(numberInput.getText());
						conversion.addElement(sym);
						conversion.addElement(number);
					} catch(NumberFormatException  evt) {
						// revert number field
						numberInput.setText("");
						setWaitCursor(false);
						getToolkit().beep();
						return;
					}
				} else if(symbolFormatIndex == 1) {
					Double number = new Double(Double.NaN);
					conversion.addElement(sym);
					conversion.addElement(number);
				} else if(symbolFormatIndex == 2) {
					conversion.addElement(sym);
					conversion.addElement("Ignore");
				}
				boolean notFound = true;
				int c= symbolStyles.size();
				for(int i=0;i<c;i++){
					Vector con = (Vector)symbolStyles.elementAt(i);
					String s = (String)con.elementAt(0);
					if(s.equals(sym)){
						symbolStyles.setElementAt(conversion,i);
						notFound = false;
						break;
					}
				}
				if(notFound){
					symbolStyles.addElement(conversion);
				}
				updateSymbolStyleList();
			} else if(command.equals("symbolRemove")){
				int n = conversionList.getSelectedIndex();
				if(n != -1){
					getConversionListModel().removeElementAt(n);
					symbolStyles.removeElementAt(n);
				}
			} else if(source.equals(dateTimeStyle)){
				if(!dateTimeRadio.isSelected()) {
					dateTimeRadio.doClick();
				}
/*				int dateTimeStyleIndex = dateTimeStyle.getSelectedIndex();
				if(dateTimeStyleIndex < dateTimeFormatVector.size()) return;

				noFire = true;
				NolTextInput newFormatDG = new NolTextInput(frame, "Input New Format","Date&Time Format:");
				newFormatDG.setBounds(200,200,220,145);
				newFormatDG.setVisible(true);
				String ff = newFormatDG.getText();
				if(newFormatDG.getResult()){
					newFormatDG.dispose();		
				}else{
					newFormatDG.dispose();
					noFire = false;
					return;
				}
				if(dateTimeFormatVector.contains(ff)){
					noFire = false;
					return;
				}
				dateTimeFormatVector.addElement(ff);
				int index = dateTimeFormatVector.size()-1;
//				dateTimeStyle.removeAllItems();
//				for(int i=0;i<dateTimeFormatVector.size();i++)
//					dateTimeStyle.addItem(dateTimeFormatVector.elementAt(i));
				dateTimeStyle.insertItemAt(ff,index);
				dateTimeStyle.setSelectedItem(ff);
				noFire = false;
*/			}else if(source.equals(dateStyle)){
				if(!dateRadio.isSelected()) {
					dateRadio.doClick();
				}
/*				int dateStyleIndex = dateStyle.getSelectedIndex();
				String fmt = (String)dateFormatVector.elementAt(dateStyleIndex);
				if(!fmt.equals("New")) return;

				noFire = true;
				NolTextInput newFormatDG = new NolTextInput(frame, "Input New Format","Date Format:");
				newFormatDG.setBounds(200,200,220,145);
				newFormatDG.setVisible(true);
				String ff = newFormatDG.getText();
				if(newFormatDG.getResult()){
					newFormatDG.dispose();		
				}else{
					newFormatDG.dispose();
					noFire = false;
					return;
				}
				dateFormatVector.addElement(ff);
				dateStyle.removeAllItems();
				for(int i=0;i<dateFormatVector.size();i++)
					dateStyle.addItem(dateFormatVector.elementAt(i));
				dateStyle.addItem("New");
				dateStyle.setSelectedItem(ff);
				noFire = false;
*/			
			} else if(source.equals(timeStyle)){
				if(!timeRadio.isSelected()) {
					timeRadio.doClick();
				}
/*				int dateStyleIndex = dateStyle.getSelectedIndex();
				String fmt = (String)dateFormatVector.elementAt(dateStyleIndex);
				if(!fmt.equals("New")) return;

				noFire = true;
				NolTextInput newFormatDG = new NolTextInput(frame, "Input New Format","Time Format:");
				newFormatDG.setBounds(200,200,220,145);
				newFormatDG.setVisible(true);
				String ff = newFormatDG.getText();
				if(newFormatDG.getResult()){
					newFormatDG.dispose();		
				}else{
					newFormatDG.dispose();
					noFire = false;
					return;
				}
				noFire = true;
				timeFormatVector.addElement(ff);
				timeStyle.removeAllItems();
				for(int i=0;i<timeFormatVector.size();i++)
					timeStyle.addItem(timeFormatVector.elementAt(i));
				timeStyle.addItem("New");
				timeStyle.setSelectedItem(ff);
				noFire = false;
*/			
			}else if("English".equals(command) || "French".equals(command)
					|| "German".equals(command) || "Italian".equals(command)){
				format.setDecimalFormatLocalString(command);
			}
//System.out.println("custFormat 6");
			setWaitCursor(false);
		}

		public boolean verifyControlActionRun() {
			return null != previewColumns;
		}
		@Override
		public void valueChanged(ListSelectionEvent e){
			if(DEBUG.debugFlag){
				System.out.println("ListSelectionEvent="+e);
			}			
			if(noFire){
				return;
			}
			if(e.getSource().equals(rowTableView.getSelectionModel())){
				rowInput.setText(String.valueOf(rowTableView.getSelectedRow()));
			}else if(e.getSource().equals(columnTableView.getColumnModel().getSelectionModel())
					|| e.getSource().equals(columnTableView.getSelectionModel())){
				int c = columnTableView.getSelectedColumn();
				if(c>0){
					columnInput.setText(String.valueOf(c-1));
				}else{
					columnInput.setText("");
					columnTableView.getSelectionModel().clearSelection();
					columnTableView.clearSelection();
				}
			}		
		}
	}
				
	class PreviewColumn extends JComponent implements MouseListener{
	
	 	private JComponent holder;			// container
		private int column;
		private Dimension displaySize;
		private int defaultCellWidth;
		private int defaultCellHeight;
		private Vector dataString;
		private int selectedRowIndex;
		private int pageNumber;
		private boolean mouseBeenPressed;


/** Constructor for Table Component - arguments are 
	row position in container, col position in container,
	label string and the container */
		public PreviewColumn(int column, int width, 
			JComponent holdPane, Vector dataString, int p) {
			this(column, width, holdPane,p);
			this.dataString = dataString;
			displaySize = new Dimension(defaultCellWidth,defaultCellHeight*(dataString.size()));
		}

		public PreviewColumn(int column, int width, 
			JComponent holdPane, int p) {
			super();
			this.column = column;
			this.holder = holdPane;
			defaultCellWidth = width;
			pageNumber = p;
			defaultCellHeight = 20;
			selectedRowIndex = -1;
			displaySize = new Dimension(defaultCellWidth,defaultCellHeight*21);
			this.addMouseListener(this);
			mouseBeenPressed = false;
		}
	
		@Override
		public boolean isOpaque(){return true;}

		@Override
		public void setPreferredSize(Dimension size){
			super.setPreferredSize(size);
			this.displaySize = size;
		}

		@Override
		public void setMinimumSize(Dimension size){
			super.setMinimumSize(size);
				this.displaySize = size;
		}
		@Override
		public Dimension getPreferredSize(){
			return displaySize;
		}
		@Override
		public Dimension getMinimumSize(){
			return displaySize;
		}
		@Override
		public Dimension getMaximumSize(){
			return displaySize;
		}
/** Change the holder to new holder - Table Area */
		public void setHolder(JComponent holderPane) {
			this.holder = holderPane;
		}
	
/**  Get the holder */
		public JComponent getHolder() {
			return this.holder;
		}

		public void setSelectedRow(int r){
			selectedRowIndex = r;
		}

		@Override
		protected void paintComponent(Graphics g) {
			JViewport view = ((JScrollPane)holder).getViewport();	
			Rectangle reg = view.getViewRect();
			int r0 = reg.y/defaultCellHeight;
			int r = reg.height/defaultCellHeight;
			g.clearRect(reg.x,reg.y,reg.width,reg.height);
			for(int rr=r0;rr<r+r0+2;rr++){
				if(rr == selectedRowIndex){ 
					g.setColor(Color.lightGray);
					g.fillRect(0, defaultCellHeight*rr, defaultCellWidth, 
						defaultCellHeight*(rr+1));
				}else{
					g.setColor(this.getBackground());
					g.fillRect(0, defaultCellHeight*rr, defaultCellWidth, 
						defaultCellHeight*(rr+1));
				}
				g.setColor(this.getForeground());
				g.drawLine(0, defaultCellHeight*rr, 
					defaultCellWidth, defaultCellHeight*rr);
				g.setColor(this.getForeground());
				if(column==-1){
					if(rr>=20){
						g.drawString("", 2 ,defaultCellHeight*rr+15 );
					}else{
						g.drawString(String.valueOf(rr), 2 
							,defaultCellHeight*rr+15 );
					}
				}else{
					if(rr>=dataString.size()){
						g.drawString("", 2 ,defaultCellHeight*rr+15 );
					}else{
						g.drawString(dataString.elementAt(rr).toString(), 
							2 ,defaultCellHeight*rr+15 );
					}
				}
			}
			g.setColor(this.getForeground());
			//g.drawLine(0,defaultCellHeight*r0,0,defaultCellHeight*(r+r0+2));
			// draw right edge of column so last column will have a right edge
			g.drawLine(defaultCellWidth-1,defaultCellHeight*r0,defaultCellWidth-1,defaultCellHeight*(r+r0+2));
		}


/** Mouse pressed event ownership is checked by the component and handled */
	 	@Override
		public void mousePressed(MouseEvent m) {
			mouseBeenPressed = true;
		}
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
			if(DEBUG.debugFlag){
				System.out.println("mouseBeenPressed="+mouseBeenPressed);
			}
			if(!mouseBeenPressed){
				return;
			}
			mouseBeenPressed = false;
			int r = m.getY()/defaultCellHeight;
			if(pageNumber == 2){
				if(column!=-1){
					selectColumn(column);
				}
			}else if(pageNumber == 3){
				selectRow(r);
			}
		}
	}


	class PreviewColumnHeader extends JComponent implements MouseListener{

	 	private JComponent holder;			// container
		private int[] widths;
		private int width;
		private Dimension displaySize;
		private int defaultCellHeight;
		private int selectedColumnIndex;
		private int pageNumber;
		private boolean mouseBeenPressed;

		public PreviewColumnHeader(int[] widths, 
			JComponent holdPane, int p) {
			super();
			this.widths = new int[widths.length];
			for(int i=0;i<widths.length;i++)
				this.widths[i] = widths[i];
			this.holder = holdPane;
			pageNumber = p;
			defaultCellHeight = 20;
			selectedColumnIndex = -1;
			width = 0;		
			FontMetrics fm = NolDataSeriesInputWizard.this.getFontMetrics(NolDataSeriesInputWizard.this.getFont());
			int sw = fm.stringWidth("5");
			for(int i=0;i<this.widths.length;i++){
				this.widths[i] = (this.widths[i]+2)*sw;
				this.width += widths[i];
			}
			displaySize = new Dimension(width,defaultCellHeight);
			this.addMouseListener(this);
			setBackground(Color.lightGray);
			mouseBeenPressed = false;
		}


		@Override
		public boolean isOpaque(){
			return true;
		}

		@Override
		public void setPreferredSize(Dimension size){
			super.setPreferredSize(size);
			this.displaySize = size;
		}

		@Override
		public void setMinimumSize(Dimension size){
			super.setMinimumSize(size);
			this.displaySize = size;
		}
		@Override
		public Dimension getPreferredSize(){
			return displaySize;
		}
		@Override
		public Dimension getMinimumSize(){
			return displaySize;
		}
		@Override
		public Dimension getMaximumSize(){
			return displaySize;
		}
/** Change the holder to new holder - Table Area */
		public void setHolder(JComponent holderPane) {
			this.holder = holderPane;
		}

/**  Get the holder */
		public JComponent getHolder() {
			return this.holder;
		}

		public void setSelectedColumn(int c){
			selectedColumnIndex = c;
		}

		@Override
		protected void paintComponent(Graphics g) {
			JViewport view = ((JScrollPane)holder).getViewport();	
			Rectangle reg = view.getViewRect();
//System.out.println("View rect = "+reg.toString());
//System.out.println("Clip 1 = "+g.getClip().toString());
			g.setClip(reg);  // compensate for bug
			g.clearRect(reg.x,reg.y,reg.width,reg.height);
/* fix */	g.setColor(Color.lightGray);
/* fix */	g.fillRect(reg.x,reg.y,reg.width,reg.height);
			int linePosition = 0;
			int adjust = 0;
			for(int cc=0;cc<widths.length;cc++){
				g.setColor(this.getForeground());
				// linePosition-1 aligns separators with columns
				g.drawLine(linePosition-adjust, 0, linePosition-adjust, defaultCellHeight);
				adjust = 1;
				g.setColor(this.getForeground());
				g.drawString(String.valueOf(cc), linePosition+2 ,15 );
				linePosition += widths[cc]; 
			}
			g.setColor(this.getForeground());
			g.drawLine(linePosition, 0, linePosition, defaultCellHeight);
			g.drawLine(0,0,linePosition,0);
			g.drawLine(0,defaultCellHeight,linePosition,defaultCellHeight);
		}

/** Mouse pressed event ownership is checked by the component and handled */
		@Override
		public void mousePressed(MouseEvent m) {
			mouseBeenPressed = true;
		}
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
			if(DEBUG.debugFlag){
				System.out.println("mouseBeenPressed="+mouseBeenPressed);
			}
			if(!mouseBeenPressed) {
				return;
			}
			mouseBeenPressed = false;
			if(pageNumber != 2) {
				return;
			}
			int position = m.getX();
			int forelength = 0;
			boolean find = false;
			for(int i=0;i<widths.length;i++){
				if(forelength <position)
					forelength +=widths[i];
				else{
					selectColumn(i-1);
					find = true;
					break;
				}
			}
			if(!find){
				selectColumn(widths.length-1);
			}
		}
	}	

	class DataStringTableModel extends AbstractTableModel{
		private int row,col;
		public DataStringTableModel(){
			row = 0;
			col = 0;
		}
		public void resetTable(){
			col = previewColumns.size()+1;
			if(col >1){
				row = ((Vector)previewColumns.elementAt(0)).size();
			}else{
				row = 0;
			}
		}
		@Override
		public int getColumnCount() { return col; }
		@Override
		public int getRowCount() { return row;}
		@Override
		public Object getValueAt(int r, int c){
			if(c==0){
				return String.valueOf(r);
			}else if(c <col){
				Vector dataStrings = (Vector)previewColumns.elementAt(c-1);
				if(r<row){
					String dstr = (String)dataStrings.elementAt(r);
					return dstr;
				}
			}
			return "";
		}
		@Override
		public String getColumnName(int c) {
			if(c==0){
				return " ";
			}else if(c <col){
				return String.valueOf(c-1);
			}
			return "";
		}
		@Override
		public boolean isCellEditable(int r, int c) {
			return false;
		}		
		@Override
		public void setValueAt(Object aValue, int r, int c) {
		}
	}

	class DateTimeVerifier {
		protected boolean goodParse;
		protected String trialString;
		protected String localString;
		protected int trialRow;

		public DateTimeVerifier(int col, int flag) {
			goodParse = false;
			trialString="";
			localString="";
			SimpleDateFormat fmt;
			trialRow = -1;
			int index;
			if(flag==0) {
				index = dateTimeStyle.getSelectedIndex();
				fmt = new SimpleDateFormat((String)dateTimeFormatVector.elementAt(index));
			} else if (flag==1) {
				index = dateStyle.getSelectedIndex();
				fmt = new SimpleDateFormat((String)dateFormatVector.elementAt(index));
			} else if (flag==2) {
				index = timeStyle.getSelectedIndex();
				fmt = new SimpleDateFormat((String)timeFormatVector.elementAt(index));
			} else return;
			Vector testCol = (Vector) previewColumns.elementAt(col);
			int row=0;
			Date dt = null;
			// go through rows until we find one with a date/time we can parse
			while(!goodParse && row<testCol.size()) {
				trialString = (String) testCol.elementAt(row); 
				try {
					dt= fmt.parse(trialString);
					goodParse = true;
					trialRow = row;
				} catch(ParseException e) {}
				row++;
			}
			if(!goodParse){
				return;
			}
			// now reconstitute the date/time in long local format
			if(flag==0){
				localString = DateFormat.getDateTimeInstance(DateFormat.LONG,DateFormat.LONG).format(dt);
			}else if (flag==1) {
				localString = DateFormat.getDateInstance(DateFormat.LONG).format(dt);
			}else {
				localString = DateFormat.getTimeInstance(DateFormat.LONG).format(dt);
			}
			//System.out.println("Trial string = "+trialString+", Localized = "+localString);		
		}
	}
	
}
