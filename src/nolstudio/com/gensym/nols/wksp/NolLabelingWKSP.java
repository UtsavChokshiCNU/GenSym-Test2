package com.gensym.nols.wksp;

import java.awt.*;
import java.awt.event.*;
import java.text.*;
import java.util.*;
import java.net.URL;

import javax.swing.*;
import javax.swing.border.*;

import com.gensym.nols.data.*;
import com.gensym.nols.main.*;
import com.gensym.math.MathException;

public class NolLabelingWKSP extends NolInternalFrame {
	private JTextField xGreater;
	private JTextField xLess;
	private JTextField yGreater;
	private JTextField yLess;
	private JTextField symbolForLabel;

	private JComboBox dsSelection;
	private JComboBox varSelection;
	private JComboBox labelSelection;
	private JCheckBox xGreaterEqual;
	private JCheckBox xLessEqual;
	private JCheckBox yGreaterEqual;
	private JCheckBox yLessEqual;
	private JButton applyLabel;
	private JButton removeLabel;
	private ControlAction actionListener;
	private boolean labelMethodFlag; //false: range; true: symbol.
	private boolean isNaNChoice; //false: symbol; true: Nan.
	private boolean modeFlag; //false: row; true: time.
	private boolean xHasEquals1;
	private boolean xHasEquals2;
	private boolean yHasEquals1;
	private boolean yHasEquals2;
	private SimpleDateFormat dateFormat;
	private int buttonSelectedIndex;

	private NolMainFrame frame;
	private Vector rawDataSeries;
	private DataSeries currentDataSeries;
	private	RawDataSource rawData;
	
 	private static String  rangeImage = "labelrange";
    private static final Dimension vpad10 = new Dimension(1,10);
    private static final Dimension vpad5 = new Dimension(1,5);

    private static final String NOLLABELINGWKSP_NAME = "NameLabel";
    private static final String NOLLABELINGWKSP_COMMENT = "CommentLabel";
    private static final String NOLLABELINGWKSP_DATASERIES = "NolLabelingWKSP_DataSeries";
    private static final String NOLLABELINGWKSP_VARIABLE = "NolLabelingWKSP_Variable";
    private static final String NOLLABELINGWKSP_LABEL = "NolLabelingWKSP_Label";
    private static final String NOLLABELINGWKSP_LOWERBOUND = "NolLabelingWKSP_LowerBound";
    private static final String NOLLABELINGWKSP_UPPERBOUND = "NolLabelingWKSP_UpperBound";
    private static final String NOLLABELINGWKSP_ROW = "NolLabelingWKSP_Row";
    private static final String NOLLABELINGWKSP_TIME = "NolLabelingWKSP_Time";
    private static final String NOLLABELINGWKSP_UNLABEL = "NolLabelingWKSP_UnLabel";
    private static final String NOLLABELINGWKSP_RANGE = "NolLabelingWKSP_Range";
    private static final String NOLLABELINGWKSP_LABELMODE = "NolLabelingWKSP_LabelMode";
    private static final String NOLLABELINGWKSP_ALLVARIABLES = "NolLabelingWKSP_AllVariables";
    private static final String NOLLABELINGWKSP_YVALUE = "NolLabelingWKSP_YValue";
    private static final String NOLLABELINGWKSP_YNAN = "NolLabelingWKSP_YNaN";
    private static final String NOLLABELINGWKSP_ERRORCONVERTSTRING = "NolLabelingWKSP_ErrorConverString";
    private static final String NOLLABELINGWKSP_UPPERISLOWER = "NolLabelingWKSP_UpperIsLower";


	public NolLabelingWKSP(){
		super();
	}

	public NolLabelingWKSP(NolMainFrame frame){

		this.frame = frame;
		String title = "Label Raw Data";
		setTitle(title);
		actionListener = new ControlAction();
		JPanel workPane = initializeLayout();
		this.setContentPane(workPane);
		modeFlag = false;
		labelMethodFlag = false;
		isNaNChoice = true;
		xHasEquals1 = false;
		xHasEquals2 = false;
		yHasEquals1 = false;
		yHasEquals2 = false;
		buttonSelectedIndex = 15;
		dateFormat = new SimpleDateFormat("MM/dd/yy hh:mm");
		updateChoiceBox();

	}

	private ImageIcon[] getImageIcons(){
		ImageIcon[] icons = new ImageIcon[16];
		for(int i=0;i<16;i++){
			String location = rangeImage+(i+1)+".gif";
			URL url = this.getClass().getResource(location);
			icons[i] = new ImageIcon(url);
		}
		return icons;
	}

	private JPanel initializeLayout(){
		JPanel workPane = new JPanel();
		workPane.setLayout(new BorderLayout());
		
		JPanel selectDsPane = new JPanel();
		selectDsPane.setBorder(new TitledBorder(new EmptyBorder(1, 1, 1, 1),               
				frame.getNolResourceString(NOLLABELINGWKSP_DATASERIES)+":", TitledBorder.LEFT , TitledBorder.TOP));
		dsSelection = new JComboBox();
		dsSelection.addActionListener(actionListener);
		selectDsPane.setLayout(new GridLayout());
		selectDsPane.add(dsSelection);

		JPanel selectVarPane = new JPanel();
		selectVarPane.setBorder(new TitledBorder(new EmptyBorder(1, 1, 1, 1),               
				frame.getNolResourceString(NOLLABELINGWKSP_VARIABLE)+":", TitledBorder.LEFT , TitledBorder.TOP));
		varSelection = new JComboBox();
		selectVarPane.setLayout(new GridLayout());
		selectVarPane.add(varSelection);

		JPanel selectLabelPane = new JPanel();
		selectLabelPane.setBorder(new TitledBorder(new EmptyBorder(1, 1, 1, 1),               
				frame.getNolResourceString(NOLLABELINGWKSP_LABEL)+":", TitledBorder.LEFT , TitledBorder.TOP));
		labelSelection = new JComboBox();
		selectLabelPane.setLayout(new GridLayout());
		selectLabelPane.add(labelSelection);

		JPanel topPane = new JPanel();
 		topPane.setLayout(new GridLayout(1,3));
		topPane.add(selectDsPane);
		topPane.add(selectVarPane);
		topPane.add(selectLabelPane);


		JPanel rangePane0 = new JPanel();
		rangePane0.setBorder(new EmptyBorder(10,10,10,10));
		rangePane0.setLayout(new BoxLayout(rangePane0, BoxLayout.Y_AXIS));

		JPanel rangeImagePane = new JPanel();
		rangeImagePane.setLayout(new GridLayout(2,8,10,10));
		ImageIcon[] icons = getImageIcons();
		ButtonGroup group = new ButtonGroup();
		for(int i=0;i<icons.length;i++){
			String command = "buttonIndex"+i;
			JToggleButton butt = new JToggleButton(icons[i]);
			group.add(butt);
			rangeImagePane.add(butt);
			butt.setActionCommand(command);
			butt.addActionListener(actionListener);
			if(i== icons.length-1){
				butt.setSelected(true);
			}
		}

		rangePane0.add(rangeImagePane);

		JPanel rangePane = new JPanel();
		rangePane.setLayout(new GridLayout(3,6,10,10));

		rangePane.add(new JLabel(frame.getNolResourceString(NOLLABELINGWKSP_LOWERBOUND)));
		rangePane.add(new JPanel());
		rangePane.add(new JPanel());
		rangePane.add(new JPanel());
		rangePane.add(new JPanel());
		rangePane.add(new JLabel(frame.getNolResourceString(NOLLABELINGWKSP_UPPERBOUND)));

		xGreater = new JTextField();
		xGreater.setEnabled(false);
		xGreater.addActionListener(actionListener);
		rangePane.add(xGreater);

		xGreaterEqual = new JCheckBox("<=");
		xGreaterEqual.setActionCommand("xgreaterequal");
		xGreaterEqual.addActionListener(actionListener);
		xGreaterEqual.setEnabled(false);
		rangePane.add(xGreaterEqual);

		ButtonGroup group1 = new ButtonGroup();
		JRadioButton radio1 = new JRadioButton(frame.getNolResourceString(NOLLABELINGWKSP_ROW), true);
		radio1.setActionCommand("Row Mode");
		radio1.addActionListener(actionListener);
		group1.add(radio1);
		rangePane.add(radio1);
		
		radio1 = new JRadioButton(frame.getNolResourceString(NOLLABELINGWKSP_TIME));
		radio1.setActionCommand("Time Mode");
		radio1.addActionListener(actionListener);
		group1.add(radio1);
		rangePane.add(radio1);

		JPanel tempPane = new JPanel();
		tempPane.setLayout(new BoxLayout(tempPane, BoxLayout.X_AXIS));
		tempPane.add(Box.createHorizontalGlue());
		xLessEqual = new JCheckBox("<=");
		xLessEqual.setActionCommand("xlessequal");
		xLessEqual.addActionListener(actionListener);
		xLessEqual.setEnabled(false);
		tempPane.add(xLessEqual);
		rangePane.add(tempPane);

		xLess = new JTextField();
		xLess.setEnabled(false);
		xLess.addActionListener(actionListener);
		rangePane.add(xLess);

		yGreater = new JTextField();
		yGreater.setEnabled(false);
		yGreater.addActionListener(actionListener);
		rangePane.add(yGreater);

		yGreaterEqual = new JCheckBox("<=");
		yGreaterEqual.setActionCommand("ygreaterequal");
		yGreaterEqual.addActionListener(actionListener);
		yGreaterEqual.setEnabled(false);
		rangePane.add(yGreaterEqual);

		ButtonGroup group2 = new ButtonGroup();
		JRadioButton radio2 = new JRadioButton(frame.getNolResourceString(NOLLABELINGWKSP_YVALUE), true);
		radio2.setActionCommand("Value");
		radio2.addActionListener(actionListener);
		group2.add(radio2);
		rangePane.add(radio2);
		
		radio2 = new JRadioButton(frame.getNolResourceString(NOLLABELINGWKSP_YNAN));
		radio2.setActionCommand("NaN");
		radio2.addActionListener(actionListener);
		group2.add(radio2);
		rangePane.add(radio2);
		
		tempPane = new JPanel();
		tempPane.setLayout(new BoxLayout(tempPane, BoxLayout.X_AXIS));
		tempPane.add(Box.createHorizontalGlue());
		yLessEqual = new JCheckBox("<=");
		yLessEqual.setActionCommand("ylessequal");
		yLessEqual.addActionListener(actionListener);
		yLessEqual.setEnabled(false);
		tempPane.add(yLessEqual);
 		rangePane.add(tempPane);

		yLess = new JTextField();
		yLess.setEnabled(false);
		yLess.addActionListener(actionListener);
		rangePane.add(yLess);

		rangePane0.add(Box.createRigidArea(vpad10));
		rangePane0.add(rangePane);
		rangePane0.add(Box.createRigidArea(vpad5));

 		JPanel control = new JPanel();
		control.setBackground(getContentPane().getBackground());
		control.setLayout(new BoxLayout(control, BoxLayout.Y_AXIS));
		control.setBorder(new TitledBorder(new EmptyBorder(1, 1, 1, 1),               
				"", TitledBorder.LEFT , TitledBorder.TOP));

		JPanel pane0 = new JPanel(new GridLayout(3,1,5,5));
		applyLabel = new JButton(frame.getNolResourceString(NOLLABELINGWKSP_LABEL));
		applyLabel.setActionCommand("labeling");
		applyLabel.addActionListener(actionListener);
		removeLabel = new JButton(frame.getNolResourceString(NOLLABELINGWKSP_UNLABEL));
		removeLabel.setActionCommand("labeling");
		removeLabel.addActionListener(actionListener);
 		pane0.add(applyLabel);
		pane0.add(removeLabel);

		control.add(Box.createRigidArea(new Dimension(1,20)));
		control.add(pane0);
		control.add(Box.createRigidArea(new Dimension(1,500)));
		control.add(Box.createVerticalGlue());

		pane0 = new JPanel(new BorderLayout());
		pane0.add("North", topPane);

		pane0.add("Center", rangePane0);
		workPane.add("Center", pane0);
		workPane.add("East", control);
		
		return workPane;
	}

	public void updateChoiceBox(){
		Project proj = frame.getProject();
		rawData = proj.getRawDataSource(); // SOURCE LEVEL - only one data source		
		int nds =  rawData.getNumberOfDataSeries();
		if(nds==0) {
			return;
		}

		if(rawDataSeries == null){
			rawDataSeries = new Vector();
		}else{
			rawDataSeries.removeAllElements();
		}
		dsSelection.removeAllItems();
		for(int j = 0; j <nds; j++) { // SERIES level
			DataSeries ds = rawData.getDataSeries(j);
			rawDataSeries.addElement(ds);
			dsSelection.addItem(ds.toString());
		}
		currentDataSeries =  (DataSeries)rawDataSeries.elementAt(0);
		int nv = currentDataSeries.getColumn();
		varSelection.removeAllItems();
		for(int i=0;i<nv;i++){
			varSelection.addItem(currentDataSeries.getVarByIndex(i).getName());
		}
		varSelection.addItem(frame.getNolResourceString(NOLLABELINGWKSP_ALLVARIABLES));
		varSelection.setSelectedIndex(0);
		varSelection.validate();

		int nl = proj.getNumberOfLabels();
		labelSelection.removeAllItems();
		for(int i=0;i<nl;i++)
			labelSelection.addItem(proj.getLabel(i).getName());
		labelSelection.validate();
	}

	private void disableButtons(){
		xGreaterEqual.setEnabled(false);
		xGreater.setEnabled(false);
		xLessEqual.setEnabled(false);
		xLess.setEnabled(false);
		yGreaterEqual.setEnabled(false);
		yGreater.setEnabled(false);
		yLessEqual.setEnabled(false);
		yLess.setEnabled(false);
		xGreater.setText("");
		xLess.setText("");
		yGreater.setText("");
		yLess.setText("");
	}	   
	
	private int getxhigh(int rows, JTextField xless){
		int rowLess =  -1;
		try{
			String xls = xless.getText();
			if(modeFlag){
 				long timelow = dateFormat.parse(xls).getTime();
				rowLess = currentDataSeries.findRowAtTime(timelow);
			}else{
 				rowLess = Integer.valueOf(xls).intValue();
			}
			if(rowLess>=0){
				if(xHasEquals2){
					rowLess = rowLess+1;
				}
			}
		} catch(ParseException evt){
			frame.showOKDialog(frame.getNolResourceString(NOLLABELINGWKSP_ERRORCONVERTSTRING));
			xless.setText("");
			rowLess = -1;
		} catch(RuntimeException evt){
			frame.showOKDialog(frame.getNolResourceString(NOLLABELINGWKSP_ERRORCONVERTSTRING));
			xless.setText("");
			rowLess = -1;
		}
		if(rowLess>rows) {
			rowLess = rows;
		}
		if(rowLess<0){
			rowLess = -1;
		}
		return rowLess;
	}

 	private int getxlow(int rows,  JTextField xgreat){
		int rowGreat =  0;
		try{
			String xgs = xgreat.getText();
			if(modeFlag){
 				long timelow = dateFormat.parse(xgs).getTime();
				rowGreat = currentDataSeries.findRowAtTime(timelow);
			}else{
 				rowGreat = Integer.valueOf(xgs).intValue();
			}
			if(rowGreat>=0){
				if(!xHasEquals1){
					rowGreat = rowGreat+1;
				}
			}
		} catch(ParseException  evt){
			frame.showOKDialog(frame.getNolResourceString(NOLLABELINGWKSP_ERRORCONVERTSTRING));
			xgreat.setText("");
		} catch(RuntimeException  evt){
			frame.showOKDialog(frame.getNolResourceString(NOLLABELINGWKSP_ERRORCONVERTSTRING));
			xgreat.setText("");
		}
		
		if(rowGreat>rows) {
			rowGreat = rows;
		}
		if(rowGreat<0) {
			rowGreat = 0;
		}
		return rowGreat;
	}

	private double getDoubleFromText(JTextField textField){
		double value = Double.NaN;
		try{
			String text =  textField.getText();
			value = Double.valueOf(text).doubleValue(); 
		}catch(Exception evt){
			frame.showOKDialog(frame.getNolResourceString(NOLLABELINGWKSP_ERRORCONVERTSTRING));
			value = Double.NaN;
		}
		return value;
	}

	private double[] getDoubleFromText(JTextField lowerField,JTextField upperField){
		double[] value = new double[2];
		value[0] = getDoubleFromText(lowerField);
		if(Double.isNaN(value[0])){
			return value;
		}
		value[1] = getDoubleFromText(upperField);
		if(Double.isNaN(value[0])){
			value[0] = Double.NaN;
			return value;
		}
		if(value[1]<value[0]){
			frame.showOKDialog(frame.getNolResourceString(NOLLABELINGWKSP_UPPERISLOWER));
			value[0] = Double.NaN;
			return value;
		}
		return value;
	}

   class ControlAction extends AbstractAction {

		ControlAction() {
			super("controlAction");
		}

        @Override
		public void actionPerformed(ActionEvent e) {
			String command = e.getActionCommand();
			if(e.getSource().equals(xGreaterEqual)){
				xHasEquals1 = xGreaterEqual.isSelected();
			}else if(e.getSource().equals(xLessEqual)){
				xHasEquals2 = xLessEqual.isSelected();
			}else if(e.getSource().equals(yGreaterEqual)){
				yHasEquals1 = yGreaterEqual.isSelected();
			}else if(e.getSource().equals(yLessEqual)){
				yHasEquals2 = yLessEqual.isSelected();
			}else if(e.getSource().equals(dsSelection)){
				int vd = dsSelection.getSelectedIndex();
				currentDataSeries =  (DataSeries)rawDataSeries.elementAt(vd);
				int nv = currentDataSeries.getColumn();
				varSelection.removeAllItems();
				for(int i=0;i<nv;i++){
					varSelection.addItem(currentDataSeries.getVarByIndex(i).getName());
				}
				varSelection.addItem(frame.getNolResourceString(NOLLABELINGWKSP_ALLVARIABLES));
				varSelection.setSelectedIndex(0);
				varSelection.validate();
			}else if(command.equals("buttonIndex0")){
				buttonSelectedIndex = 0;
				disableButtons();
				xLessEqual.setEnabled(true);
				xLess.setEnabled(true);
				yGreaterEqual.setEnabled(true);
				yGreater.setEnabled(true);
			}else if(command.equals("buttonIndex1")){
				buttonSelectedIndex = 1;
				disableButtons();
				xLessEqual.setEnabled(true);
				xLess.setEnabled(true);
				yGreaterEqual.setEnabled(true);
				yGreater.setEnabled(true);
				yLessEqual.setEnabled(true);
				yLess.setEnabled(true);
			}else if(command.equals("buttonIndex2")){
				buttonSelectedIndex = 2;
				disableButtons();
				xLessEqual.setEnabled(true);
				xLess.setEnabled(true);
				yLessEqual.setEnabled(true);
				yLess.setEnabled(true);
			}else if(command.equals("buttonIndex3")){
				buttonSelectedIndex = 3;
				disableButtons();
				xLessEqual.setEnabled(true);
				xLess.setEnabled(true);
			}else if(command.equals("buttonIndex4")){
				buttonSelectedIndex = 4;
				disableButtons();
				xLessEqual.setEnabled(true);
				xLess.setEnabled(true);
				xGreaterEqual.setEnabled(true);
				xGreater.setEnabled(true);
				yGreaterEqual.setEnabled(true);
				yGreater.setEnabled(true);
			}else if(command.equals("buttonIndex5")){
				buttonSelectedIndex = 5;
				disableButtons();
				xLessEqual.setEnabled(true);
				xLess.setEnabled(true);
				xGreaterEqual.setEnabled(true);
				xGreater.setEnabled(true);
				yGreaterEqual.setEnabled(true);
				yGreater.setEnabled(true);
				yLessEqual.setEnabled(true);
				yLess.setEnabled(true);
			}else if(command.equals("buttonIndex6")){
				buttonSelectedIndex = 6;
				disableButtons();
				xLessEqual.setEnabled(true);
				xLess.setEnabled(true);
				xGreaterEqual.setEnabled(true);
				xGreater.setEnabled(true);
				yLessEqual.setEnabled(true);
				yLess.setEnabled(true);
			}else if(command.equals("buttonIndex7")){
				buttonSelectedIndex = 7;
				disableButtons();
				xLessEqual.setEnabled(true);
				xLess.setEnabled(true);
				xGreaterEqual.setEnabled(true);
				xGreater.setEnabled(true);
			}else if(command.equals("buttonIndex8")){
				buttonSelectedIndex = 8;
				disableButtons();
				xGreaterEqual.setEnabled(true);
				xGreater.setEnabled(true);
				yGreaterEqual.setEnabled(true);
				yGreater.setEnabled(true);
			}else if(command.equals("buttonIndex9")){
				buttonSelectedIndex = 9;
				disableButtons();
				xGreaterEqual.setEnabled(true);
				xGreater.setEnabled(true);
				yGreaterEqual.setEnabled(true);
				yGreater.setEnabled(true);
				yLessEqual.setEnabled(true);
				yLess.setEnabled(true);
			}else if(command.equals("buttonIndex10")){
				buttonSelectedIndex = 10;
				disableButtons();
				xGreaterEqual.setEnabled(true);
				xGreater.setEnabled(true);
				yLessEqual.setEnabled(true);
				yLess.setEnabled(true);
			}else if(command.equals("buttonIndex11")){
				buttonSelectedIndex = 11;
				disableButtons();
				xGreaterEqual.setEnabled(true);
				xGreater.setEnabled(true);
			}else if(command.equals("buttonIndex12")){
				buttonSelectedIndex = 12;
				disableButtons();
				yGreaterEqual.setEnabled(true);
				yGreater.setEnabled(true);
			}else if(command.equals("buttonIndex13")){
				buttonSelectedIndex = 13;
				disableButtons();
				yGreaterEqual.setEnabled(true);
				yGreater.setEnabled(true);
				yLessEqual.setEnabled(true);
				yLess.setEnabled(true);
			}else if(command.equals("buttonIndex14")){
				buttonSelectedIndex = 14;
				disableButtons();
				yLessEqual.setEnabled(true);
				yLess.setEnabled(true);
			}else if(command.equals("buttonIndex15")){
				buttonSelectedIndex = 15;
				disableButtons();
			}else if(command.equals("Row Mode")){
				modeFlag = false;
			}else if(command.equals("Time Mode")){
				modeFlag = true;
			}else if(command.equals("labeling")){
				boolean newlabel = false;
				if(e.getSource().equals(applyLabel)){
					newlabel = true;
				}
				int labelNumber = labelSelection.getSelectedIndex();
				int vd = varSelection.getSelectedIndex();
				if(labelNumber == -1 || vd == -1){
					return;
				}
				boolean allVar = false;
				if(varSelection.getSelectedItem().equals(frame.getNolResourceString(NOLLABELINGWKSP_ALLVARIABLES))){
					allVar = true;
				}
/*				String xgs = xGreater.getText();
				String xls = xLess.getText();
				String ygs = yGreater.getText();
				String yls = yLess.getText();
*/				int xlow = 0;
				int rows = currentDataSeries.getRow();
				int xhigh = rows;
				if(buttonSelectedIndex==0){
					double ylow = getDoubleFromText(yGreater);
					if(Double.isNaN(ylow)){
						return;
					}
					xhigh = getxhigh(rows,xLess);
					if(xhigh<0) {
						return;
					}
					Vector varObjs = currentDataSeries.getVarObjects();
					int[] possibleRowNumbers = new int[xhigh+1];
					if(allVar){
						int nv = currentDataSeries.getColumn();
						Hashtable hashy = new Hashtable(10);
						for(int c=0;c<nv;c++){
							Variable var = (Variable)varObjs.elementAt(c);
							int selected = 0;
							for(int i = 0; i < xhigh; i++) {  // note loop is inclusive
								try {
									double y = currentDataSeries.getValueAt(i, c);
									if(!Double.isNaN(y)) {
										if(yHasEquals1){
											if(y >= ylow) {
												possibleRowNumbers[selected++] = i;
											}
										}else{
											if(y > ylow){
												possibleRowNumbers[selected++] = i;
											}
										}
									}
								} catch (MathException evt) {
									System.err.println("Fatal Error: Attempted to access data that is not present");
									evt.printStackTrace();
								}
							}
							int[] rowNumbers = new int[selected];
							for(int i = 0; i < selected; i++){
								rowNumbers[i] = possibleRowNumbers[i];
							}
							hashy.put(var, rowNumbers);
						}
						rawData.labelPoints(labelNumber, hashy, newlabel);
					}else{
						Variable var = (Variable)varObjs.elementAt(vd);
						int selected = 0;
						for(int i = 0; i < xhigh; i++) {  // note loop is inclusive
							try {
								double y = currentDataSeries.getValueAt(i, vd);
								if(!Double.isNaN(y)) {
									if(yHasEquals1){
										if(y >= ylow) {
											possibleRowNumbers[selected++] = i;
										}
									}else{
										if(y > ylow){
											possibleRowNumbers[selected++] = i;
										}
									}
								}
							} catch (MathException evt) {
								System.err.println("Fatal Error: Attempted to access data that is not present");
								evt.printStackTrace();
							}
						}
						int[] rowNumbers = new int[selected];
						for(int i = 0; i < selected; i++) {
							rowNumbers[i] = possibleRowNumbers[i];		
						}
						rawData.labelPoints(labelNumber,var,rowNumbers,newlabel);
					}
				}else if(buttonSelectedIndex==1){				
					double[] yy = getDoubleFromText(yLess,yGreater);
					if(Double.isNaN(yy[0])) {
						return;
					}
					double yhigh =  yy[0];
 					double ylow = yy[1];
					xhigh = getxhigh(rows,xLess);
					if(xhigh<0) {
						return;
					}
					Vector varObjs = currentDataSeries.getVarObjects();
					int[] possibleRowNumbers = new int[xhigh+1];
					if(allVar){
						int nv = currentDataSeries.getColumn();
						Hashtable hashy = new Hashtable(10);
						for(int c=0;c<nv;c++){
							Variable var = (Variable)varObjs.elementAt(c);
							int selected = 0;
							for(int i = 0; i < xhigh; i++) {  // note loop is inclusive
								try {
									double y = currentDataSeries.getValueAt(i, c);
									if(!Double.isNaN(y)) {
										if(yHasEquals1&&yHasEquals2){
											if(y >= ylow && y <=yhigh) {
												possibleRowNumbers[selected++] = i;
											}
										}else if((!yHasEquals1)&&yHasEquals2){
											if(y > ylow && y <=yhigh){
												possibleRowNumbers[selected++] = i;
											}
										}else if(yHasEquals1&&(!yHasEquals2)){
											if(y >= ylow && y <yhigh){
												possibleRowNumbers[selected++] = i;
											}
										}else if((!yHasEquals1)&&(!yHasEquals2)){
											if(y > ylow && y <yhigh){
												possibleRowNumbers[selected++] = i;
											}
										}		
									}
								} catch (MathException evt) {
									System.err.println("Fatal Error: Attempted to access data that is not present");
									evt.printStackTrace();
								}
							}
							int[] rowNumbers = new int[selected];
							for(int i = 0; i < selected; i++){
								rowNumbers[i] = possibleRowNumbers[i];
							}
							hashy.put(var, rowNumbers);
						}
						rawData.labelPoints(labelNumber, hashy, newlabel);
					}else{
						Variable var = (Variable)varObjs.elementAt(vd);
						int selected = 0;
						for(int i = 0; i < xhigh; i++) {  // note loop is inclusive
							try {
								double y = currentDataSeries.getValueAt(i, vd);
								if(!Double.isNaN(y)) {
									if(yHasEquals1&&yHasEquals2){
										if(y >= ylow && y <=yhigh) {
											possibleRowNumbers[selected++] = i;
										}
									}else if((!yHasEquals1)&&yHasEquals2){
										if(y > ylow && y <=yhigh){
											possibleRowNumbers[selected++] = i;
										}
									}else if(yHasEquals1&&(!yHasEquals2)){
										if(y >= ylow && y <yhigh){
											possibleRowNumbers[selected++] = i;
										}
									}else if((!yHasEquals1)&&(!yHasEquals2)){
										if(y > ylow && y <yhigh){
											possibleRowNumbers[selected++] = i;
										}
									}
								}
							} catch (MathException evt) {
								System.err.println("Fatal Error: Attempted to access data that is not present");
								evt.printStackTrace();
							}
						}
						int[] rowNumbers = new int[selected];
						for(int i = 0; i < selected; i++){
							rowNumbers[i] = possibleRowNumbers[i];		
						}
						rawData.labelPoints(labelNumber,var,rowNumbers,newlabel);
					}
				}/*
				}else if(buttonSelectedIndex==2){
					if(allVar){
						int n = transformer.getNumberOfVariables();
						for(int c=0;c<n;c++){
							try{
								data = transformer.getData(c);
							}catch(NolProjectException evt){
								return;
							}
							boolean[] flags = new boolean[data.length];
							rows = transformer.getNumberOfRows(c);
							xhigh = rows;
							xhigh = getxhigh(rows,xls,c);
							double yhigh = Double.valueOf(yls).doubleValue(); 
							int count = 0;
							for(int i=xlow;i<xhigh;i++){
								if(yHasEquals2){
									if(data[i] <= yhigh) {
										flags[i] = true;
										count++;
									}
								}else {
									if(data[i] < yhigh){
										flags[i] = true;
										count++;
									}
								}
							} 
							labelPoints(count,rows,flags,ld,c,newlabel,xlow,xhigh);
						}
					}else{
						try{
							data = transformer.getData(vd);
						}catch(NolProjectException evt){
							return;
						}
						boolean[] flags = new boolean[data.length];						
						xhigh = getxhigh(rows,xls,vd);
						double yhigh = Double.valueOf(yls).doubleValue(); 
						int count = 0;
						for(int i=xlow;i<xhigh;i++){
							if(yHasEquals2){
								if(data[i] <= yhigh) {
									flags[i] = true;
									count++;
								}
							}else {
								if(data[i] < yhigh){
									flags[i] = true;
									count++;
								}
							}
						} 
						labelPoints(count,rows,flags,ld,vd,newlabel,xlow,xhigh);
					}
				}else if(buttonSelectedIndex==3){
					if(allVar){
						int n = transformer.getNumberOfVariables();
						for(int c=0;c<n;c++){
							rows = transformer.getNumberOfRows(c);
//							xhigh = rows;
							xhigh = getxhigh(rows,xls,c);
							transformer.labelPoints(ld,c,xlow,c,xhigh-1,newlabel);
						}
					}else{
						xhigh = getxhigh(rows,xls,vd);
						transformer.labelPoints(ld,vd,xlow,vd,xhigh-1,newlabel);
					}
				}else if(buttonSelectedIndex==4){
					if(allVar){
						int n = transformer.getNumberOfVariables();
						for(int c=0;c<n;c++){
							try{
								data = transformer.getData(c);
							}catch(NolProjectException evt){
								return;
							}
							boolean[] flags = new boolean[data.length];
							rows = transformer.getNumberOfRows(c);
							xhigh = rows;
							xlow = getxlow(rows,xgs,c);
							xhigh = getxhigh(rows,xls,c);
							double ylow = Double.valueOf(ygs).doubleValue(); 
							int count = 0;
							for(int i=xlow;i<xhigh;i++){
								if(yHasEquals1){
									if(data[i] >= ylow) {
										flags[i] = true;
										count++;
									}
								}else{
									if(data[i] > ylow){
										flags[i] = true;
										count++;
									}
								}
							} 
							labelPoints(count,rows,flags,ld,c,newlabel,xlow,xhigh);
						}
					}else{
						try{
							data = transformer.getData(vd);
						}catch(NolProjectException evt){
							return;
						}
						boolean[] flags = new boolean[data.length];						
						xlow = getxlow(rows,xgs,vd);
						xhigh = getxhigh(rows,xls,vd);
						double ylow = Double.valueOf(ygs).doubleValue(); 
						int count = 0;
						for(int i=xlow;i<xhigh;i++){
							if(yHasEquals1){
								if(data[i] >= ylow) {
									flags[i] = true;
									count++;
								}
							}else{
								if(data[i] > ylow){
									flags[i] = true;
									count++;
								}
							}
						} 
						labelPoints(count,rows,flags,ld,vd,newlabel,xlow,xhigh);
					}
				}else if(buttonSelectedIndex==5){
					if(allVar){
						int n = transformer.getNumberOfVariables();
						for(int c=0;c<n;c++){
							try{
								data = transformer.getData(c);
							}catch(NolProjectException evt){
								return;
							}
							boolean[] flags = new boolean[data.length];
							rows = transformer.getNumberOfRows(c);
							xhigh = rows;
							xlow = getxlow(rows,xgs,c);
							xhigh = getxhigh(rows,xls,c);
							if(xlow<xhigh) return;
							double ylow = Double.valueOf(ygs).doubleValue(); 
							double yhigh = Double.valueOf(yls).doubleValue(); 
							if(ylow<=yhigh) return;
							int count = 0;
							for(int i=xlow;i<xhigh;i++){
								if(yHasEquals1&&yHasEquals2){
									if(data[i] >= ylow && data[i] <=yhigh) {
										flags[i] = true;
										count++;
									}
								}else if((!yHasEquals1)&&yHasEquals2){
									if(data[i] > ylow && data[i] <=yhigh){
										flags[i] = true;
										count++;
									}
								}else if(yHasEquals1&&(!yHasEquals2)){
									if(data[i] >= ylow && data[i] <yhigh){
										flags[i] = true;
										count++;
									}
								}else if((!yHasEquals1)&&(!yHasEquals2)){
									if(data[i] > ylow && data[i] <yhigh){
										flags[i] = true;
										count++;
									}
								}
							} 
							labelPoints(count,rows,flags,ld,c,newlabel,xlow,xhigh);
						}
					}else{
						try{
							data = transformer.getData(vd);
						}catch(NolProjectException evt){
							return;
						}
						boolean[] flags = new boolean[data.length];						
						xlow = getxlow(rows,xgs,vd);
						xhigh = getxhigh(rows,xls,vd);
						if(xlow<xhigh) return;
						double ylow = Double.valueOf(ygs).doubleValue(); 
						double yhigh = Double.valueOf(yls).doubleValue(); 
						if(ylow<=yhigh) return;
						int count = 0;
						for(int i=xlow;i<xhigh;i++){
							if(yHasEquals1&&yHasEquals2){
								if(data[i] >= ylow && data[i] <=yhigh) {
									flags[i] = true;
									count++;
								}
							}else if((!yHasEquals1)&&yHasEquals2){
								if(data[i] > ylow && data[i] <=yhigh){
									flags[i] = true;
									count++;
								}
							}else if(yHasEquals1&&(!yHasEquals2)){
								if(data[i] >= ylow && data[i] <yhigh){
									flags[i] = true;
									count++;
								}
							}else if((!yHasEquals1)&&(!yHasEquals2)){
								if(data[i] > ylow && data[i] <yhigh){
									flags[i] = true;
									count++;
								}
							}
						} 
						labelPoints(count,rows,flags,ld,vd,newlabel,xlow,xhigh);
					}
				}else if(buttonSelectedIndex==6){
					if(allVar){
						int n = transformer.getNumberOfVariables();
						for(int c=0;c<n;c++){
							try{
								data = transformer.getData(c);
							}catch(NolProjectException evt){
								return;
							}
							boolean[] flags = new boolean[data.length];
							rows = transformer.getNumberOfRows(c);
							xhigh = rows;
							xlow = getxlow(rows,xgs,c);
							xhigh = getxhigh(rows,xls,c);
							if(xlow<xhigh) return;
							double yhigh = Double.valueOf(yls).doubleValue(); 
							int count = 0;
							for(int i=xlow;i<xhigh;i++){
								if(yHasEquals2){
									if(data[i] <=yhigh) {
										flags[i] = true;
										count++;
									}
								}else{
									if(data[i] <yhigh){
										flags[i] = true;
										count++;
									}
								}
							} 
							labelPoints(count,rows,flags,ld,c,newlabel,xlow,xhigh);
						}
					}else{
						try{
							data = transformer.getData(vd);
						}catch(NolProjectException evt){
							return;
						}
						boolean[] flags = new boolean[data.length];						
						xlow = getxlow(rows,xgs,vd);
						xhigh = getxhigh(rows,xls,vd);
						if(xlow<xhigh) return;
						double yhigh = Double.valueOf(yls).doubleValue(); 
						int count = 0;
						for(int i=xlow;i<xhigh;i++){
							if(yHasEquals2){
								if(data[i] <=yhigh) {
									flags[i] = true;
									count++;
								}
							}else{
								if(data[i] <yhigh){
									flags[i] = true;
									count++;
								}
							}
						} 
						labelPoints(count,rows,flags,ld,vd,newlabel,xlow,xhigh);
					}
				}else if(buttonSelectedIndex==7){
					if(allVar){
						int n = transformer.getNumberOfVariables();
						for(int c=0;c<n;c++){
							rows = transformer.getNumberOfRows(c);
							xhigh = rows;
							xlow = getxlow(rows,xgs,c);
							xhigh = getxhigh(rows,xls,c);
							if(xlow<xhigh) return;
							transformer.labelPoints(ld,c,xlow,vd,xhigh-1,newlabel);
						}
					}else{
						xlow = getxlow(rows,xgs,vd);
						xhigh = getxhigh(rows,xls,vd);
						if(xlow<xhigh) return;
						transformer.labelPoints(ld,vd,xlow,vd,xhigh-1,newlabel);
					}
				}else if(buttonSelectedIndex==8){
					if(allVar){
						int n = transformer.getNumberOfVariables();
						for(int c=0;c<n;c++){
							try{
								data = transformer.getData(c);
							}catch(NolProjectException evt){
								return;
							}
							boolean[] flags = new boolean[data.length];
							rows = transformer.getNumberOfRows(c);
							xhigh = rows;
							xlow = getxlow(rows,xgs,c);
							double ylow = Double.valueOf(ygs).doubleValue(); 
							int count = 0;
							for(int i=xlow;i<xhigh;i++){
								if(yHasEquals1){
									if(data[i] >= ylow) {
										flags[i] = true;
										count++;
									}
								}else{
									if(data[i] > ylow ){
										flags[i] = true;
										count++;
									}
								}
							} 
							labelPoints(count,rows,flags,ld,c,newlabel,xlow,xhigh);
						}
					}else{
						try{
							data = transformer.getData(vd);
						}catch(NolProjectException evt){
							return;
						}
						boolean[] flags = new boolean[data.length];
						xlow = getxlow(rows,xgs,vd);
						double ylow = Double.valueOf(ygs).doubleValue(); 
						int count = 0;
						for(int i=xlow;i<xhigh;i++){
							if(yHasEquals1){
								if(data[i] >= ylow) {
									flags[i] = true;
									count++;
								}
							}else{
								if(data[i] > ylow ){
									flags[i] = true;
									count++;
								}
							}
						} 
						labelPoints(count,rows,flags,ld,vd,newlabel,xlow,xhigh);
					}
				}else if(buttonSelectedIndex==9){
					if(allVar){
						int n = transformer.getNumberOfVariables();
						for(int c=0;c<n;c++){
							try{
								data = transformer.getData(c);
							}catch(NolProjectException evt){
								return;
							}
							boolean[] flags = new boolean[data.length];
							rows = transformer.getNumberOfRows(c);
							xhigh = rows;
							xlow = getxlow(rows,xgs,c);
							double ylow = Double.valueOf(ygs).doubleValue(); 
							double yhigh = Double.valueOf(yls).doubleValue(); 
							if(ylow<=yhigh) return;
							int count = 0;
							for(int i=xlow;i<xhigh;i++){
								if(yHasEquals1&&yHasEquals2){
									if(data[i] >= ylow && data[i] <=yhigh) {
										flags[i] = true;
										count++;
									}
								}else if((!yHasEquals1)&&yHasEquals2){
									if(data[i] > ylow && data[i] <=yhigh){
										flags[i] = true;
										count++;
									}
								}else if(yHasEquals1&&(!yHasEquals2)){
									if(data[i] >= ylow && data[i] <yhigh){
										flags[i] = true;
										count++;
									}
								}else if((!yHasEquals1)&&(!yHasEquals2)){
									if(data[i] > ylow && data[i] <yhigh){
										flags[i] = true;
										count++;
									}
								}
							} 
							labelPoints(count,rows,flags,ld,c,newlabel,xlow,xhigh);
						}
					}else{
						try{
							data = transformer.getData(vd);
						}catch(NolProjectException evt){
							return;
						}
						boolean[] flags = new boolean[data.length];
						xlow = getxlow(rows,xgs,vd);
						double ylow = Double.valueOf(ygs).doubleValue(); 
						double yhigh = Double.valueOf(yls).doubleValue(); 
						if(ylow<=yhigh) return;
						int count = 0;
						for(int i=xlow;i<xhigh;i++){
							if(yHasEquals1&&yHasEquals2){
								if(data[i] >= ylow && data[i] <=yhigh) {
									flags[i] = true;
									count++;
								}
							}else if((!yHasEquals1)&&yHasEquals2){
								if(data[i] > ylow && data[i] <=yhigh){
									flags[i] = true;
									count++;
								}
							}else if(yHasEquals1&&(!yHasEquals2)){
								if(data[i] >= ylow && data[i] <yhigh){
									flags[i] = true;
									count++;
								}
							}else if((!yHasEquals1)&&(!yHasEquals2)){
								if(data[i] > ylow && data[i] <yhigh){
									flags[i] = true;
									count++;
								}
							}
						} 
						labelPoints(count,rows,flags,ld,vd,newlabel,xlow,xhigh);
					}
				}else if(buttonSelectedIndex==10){
					if(allVar){
						int n = transformer.getNumberOfVariables();
						for(int c=0;c<n;c++){
							try{
								data = transformer.getData(c);
							}catch(NolProjectException evt){
								return;
							}
							boolean[] flags = new boolean[data.length];
							rows = transformer.getNumberOfRows(c);
							xhigh = rows;
							xlow = getxlow(rows,xgs,c);
							double yhigh = Double.valueOf(yls).doubleValue(); 
							int count = 0;
							for(int i=xlow;i<xhigh;i++){
								if(yHasEquals2){
									if(data[i] <=yhigh) {
										flags[i] = true;
										count++;
									}
								}else{
									if(data[i] <yhigh){
										flags[i] = true;
										count++;
									}
								}
							}
							labelPoints(count,rows,flags,ld,c,newlabel,xlow,xhigh);
						}
					}else{
						try{
							data = transformer.getData(vd);
						}catch(NolProjectException evt){
							return;
						}
						boolean[] flags = new boolean[data.length];
						xlow = getxlow(rows,xgs,vd);
						double yhigh = Double.valueOf(yls).doubleValue(); 
						int count = 0;
						for(int i=xlow;i<xhigh;i++){
							if(yHasEquals2){
								if(data[i] <=yhigh) {
									flags[i] = true;
									count++;
								}
							}else{
								if(data[i] <yhigh){
									flags[i] = true;
									count++;
								}
							}
						}
						labelPoints(count,rows,flags,ld,vd,newlabel,xlow,xhigh);
					}
				}else if(buttonSelectedIndex==11){
					if(allVar){
						int n = transformer.getNumberOfVariables();
						for(int c=0;c<n;c++){
							rows = transformer.getNumberOfRows(c);
							xhigh = rows;
							xlow = getxlow(rows,xgs,c);
							transformer.labelPoints(ld,c,xlow,c,xhigh-1,newlabel);
						}
					}else{
						xlow = getxlow(rows,xgs,vd);
						transformer.labelPoints(ld,vd,xlow,vd,xhigh-1,newlabel);
					}
				}else if(buttonSelectedIndex==12){
					if(allVar){
						int n = transformer.getNumberOfVariables();
						for(int c=0;c<n;c++){
							try{
								data = transformer.getData(c);
							}catch(NolProjectException evt){
								return;
							}
							boolean[] flags = new boolean[data.length];
							rows = transformer.getNumberOfRows(c);
							xhigh = rows;
							double ylow = Double.valueOf(ygs).doubleValue(); 
							int count = 0;
							for(int i=xlow;i<xhigh;i++){
								if(yHasEquals1){
									if(data[i] >= ylow) {
										flags[i] = true;
										count++;
									}
								}else {
									if(data[i] > ylow ){
										flags[i] = true;
										count++;
									}
								}
							} 
							labelPoints(count,rows,flags,ld,c,newlabel,xlow,xhigh);
						}
					}else{
						try{
							data = transformer.getData(vd);
						}catch(NolProjectException evt){
							return;
						}
						boolean[] flags = new boolean[data.length];
						double ylow = Double.valueOf(ygs).doubleValue(); 
						int count = 0;
						for(int i=xlow;i<xhigh;i++){
							if(yHasEquals1){
								if(data[i] >= ylow) {
									flags[i] = true;
									count++;
								}
							}else {
								if(data[i] > ylow ){
									flags[i] = true;
									count++;
								}
							}
						} 
						labelPoints(count,rows,flags,ld,vd,newlabel,xlow,xhigh);
					}
				}else if(buttonSelectedIndex==13){
					if(allVar){
						int n = transformer.getNumberOfVariables();
						for(int c=0;c<n;c++){
							try{
								data = transformer.getData(c);
							}catch(NolProjectException evt){
								return;
							}
							boolean[] flags = new boolean[data.length];
							rows = transformer.getNumberOfRows(c);
							xhigh = rows;
							double ylow = Double.valueOf(ygs).doubleValue(); 
							double yhigh = Double.valueOf(yls).doubleValue(); 
							if(ylow<=yhigh) return;
							int count = 0;
							for(int i=xlow;i<xhigh;i++){
								if(yHasEquals1&&yHasEquals2){
									if(data[i] >= ylow && data[i] <=yhigh) {
										flags[i] = true;
										count++;
									}
								}else if((!yHasEquals1)&&yHasEquals2){
									if(data[i] > ylow && data[i] <=yhigh){
										flags[i] = true;
										count++;
									}
								}else if(yHasEquals1&&(!yHasEquals2)){
									if(data[i] >= ylow && data[i] <yhigh){
										flags[i] = true;
										count++;
									}
								}else if((!yHasEquals1)&&(!yHasEquals2)){
									if(data[i] > ylow && data[i] <yhigh){
										flags[i] = true;
										count++;
									}
								}
							} 
							labelPoints(count,rows,flags,ld,c,newlabel,xlow,xhigh);
						}
					}else{
						try{
							data = transformer.getData(vd);
						}catch(NolProjectException evt){
							return;
						}
						boolean[] flags = new boolean[data.length];
						double ylow = Double.valueOf(ygs).doubleValue(); 
						double yhigh = Double.valueOf(yls).doubleValue(); 
						if(ylow<=yhigh) return;
						int count = 0;
						for(int i=xlow;i<xhigh;i++){
							if(yHasEquals1&&yHasEquals2){
								if(data[i] >= ylow && data[i] <=yhigh) {
									flags[i] = true;
									count++;
								}
							}else if((!yHasEquals1)&&yHasEquals2){
								if(data[i] > ylow && data[i] <=yhigh){
									flags[i] = true;
									count++;
								}
							}else if(yHasEquals1&&(!yHasEquals2)){
								if(data[i] >= ylow && data[i] <yhigh){
									flags[i] = true;
									count++;
								}
							}else if((!yHasEquals1)&&(!yHasEquals2)){
								if(data[i] > ylow && data[i] <yhigh){
									flags[i] = true;
									count++;
								}
							}
						} 
						labelPoints(count,rows,flags,ld,vd,newlabel,xlow,xhigh);
					}
				}else if(buttonSelectedIndex==14){
					if(allVar){
						int n = transformer.getNumberOfVariables();
						for(int c=0;c<n;c++){
							try{
								data = transformer.getData(c);
							}catch(NolProjectException evt){
								return;
							}
							boolean[] flags = new boolean[data.length];
							rows = transformer.getNumberOfRows(c);
							xhigh = rows;
							double yhigh = Double.valueOf(yls).doubleValue(); 
							int count = 0;
							for(int i=xlow;i<xhigh;i++){
								if(yHasEquals2){
									if(data[i] <=yhigh) {
										flags[i] = true;
										count++;
									}
								}else{
									if(data[i] <yhigh){
										flags[i] = true;
										count++;
									}
								}
							} 
							labelPoints(count,rows,flags,ld,c,newlabel,xlow,xhigh);
						}
					}else{
						try{
							data = transformer.getData(vd);
						}catch(NolProjectException evt){
							return;
						}
						boolean[] flags = new boolean[data.length];
						double yhigh = Double.valueOf(yls).doubleValue(); 
						int count = 0;
						for(int i=xlow;i<xhigh;i++){
							if(yHasEquals2){
								if(data[i] <=yhigh) {
									flags[i] = true;
									count++;
								}
							}else{
								if(data[i] <yhigh){
									flags[i] = true;
									count++;
								}
							}
						} 
						labelPoints(count,rows,flags,ld,vd,newlabel,xlow,xhigh);
					}
				}else if(buttonSelectedIndex==15){
					if(allVar){
						int n = transformer.getNumberOfVariables();
						for(int c=0;c<n;c++){
							transformer.labelPoints(ld,c,xlow,vd,xhigh-1,newlabel);
						}
					}else{
						transformer.labelPoints(ld,vd,xlow,vd,xhigh-1,newlabel);
					}
				}
			}else if(e.getSource() == xGreater){
				int vd = varSelection.getSelectedIndex();
				if(vd == -1){
					xGreater.setText("");
					return;
				}
				String xgs = xGreater.getText();
				if(xgs.equals("")) return;
				if(modeFlag){
					try{
						long T = dateFormat.parse(xgs).getTime();
					}catch(ParseException evt){
						xGreater.setText("");
					}
				}else{
					try{
						Integer X = Integer.valueOf(xgs);
					}catch(NumberFormatException evt){
						xGreater.setText("");
					}
				}
			}else if(e.getSource() == xLess){
				int vd = varSelection.getSelectedIndex();
				if(vd == -1){
					xLess.setText("");
					return;
				}
				String xls = xLess.getText();
				if(xls.equals("")) return;
				if(modeFlag){
					try{
						long T = dateFormat.parse(xls).getTime();
					}catch(ParseException evt){
						xLess.setText("");
					}
				}else{
					try{
						Integer X = Integer.valueOf(xls);
					}catch(NumberFormatException evt){
						xLess.setText("");
					}
				}  */

			}
		}  
    }
}

