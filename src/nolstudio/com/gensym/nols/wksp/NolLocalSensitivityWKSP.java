package com.gensym.nols.wksp;

import java.awt.*;
import java.awt.event.*;
import java.util.*;

import javax.swing.*;
import javax.swing.table.*;
import javax.swing.border.*;

import com.gensym.math.Utilities;
import com.gensym.math.MathException;
import com.gensym.math.matrix.*;
import com.gensym.math.datafit.*;

import com.gensym.nols.main.*;
import com.gensym.nols.data.*;
import com.gensym.nols.util.*;

public class NolLocalSensitivityWKSP extends NolInternalFrame {

	private NolMainFrame frame;

	private JPanel varListPane;
	private JButton calculateBut;
	private JButton stopBut;
	private ControlAction actionListener;
	private boolean noFire;
	private boolean isCalculated;

	private NolModel2 model;
	private Vector inputVars;
	private Vector outputVars;
	private Vector varContentInPane;

 	private	SensitivityTableModel sensitivityTableModel;
 	private	SensitivityColorTableModel sensitivityColorTableModel;
	private	JTable sensitivityTableView;

	private Thread senThread;

	private Matrix sensitivityValues;
	private Matrix scaledSensitivityValues;
	private Matrix inputValues;

	private int sigDigits = 8;
	
	public NolLocalSensitivityWKSP (NolMainFrame frame, NolModel2 model){ //for demo only
		super(model.getPreprocessor());
		setTitle("Sensitivity for model ["+model.getName()+"]");

		this.frame = frame;
		this.model = model;
		actionListener = new ControlAction();
		inputVars = model.getInputs();
		outputVars = model.getOutputs();	
		isCalculated = false;
		noFire = false;
		initialLayout();
		initDataDisplay();

	}

	private void initialLayout(){
		getContentPane().setLayout(new BorderLayout());  		
		JPanel centerPane = new JPanel(new BorderLayout());
		centerPane.add("Center",getVarPanel());    
		centerPane.add("North", getModelNamePanel());
		getContentPane().add("Center",centerPane);
		getContentPane().add("East",getControlPanel());	
	}

	private JPanel getModelNamePanel(){

		JPanel namePanel = new JPanel(new GridLayout(1,4,5,5));
		namePanel.setBorder(new EmptyBorder(10, 10, 10, 10));               
		namePanel.add(new JLabel("Model Name:"));
		namePanel.add(new JLabel(model.getName()));
		namePanel.add(new JLabel("Preprocessor:"));
		namePanel.add(new JLabel(model.getPreprocessor().getName()));
		return namePanel;
	}

	private JTabbedPane getVarPanel(){
		
		JTabbedPane detailedTabbedPane = new JTabbedPane();

		sensitivityTableModel = new SensitivityTableModel();
		sensitivityColorTableModel = new SensitivityColorTableModel();
		sensitivityTableView = new JTable(sensitivityTableModel);
		sensitivityTableView.setDefaultRenderer(ColoredBar.class, 
			new SensitivityTableRenderer());
		sensitivityTableView.setSelectionMode(0);
		sensitivityTableView.setCellSelectionEnabled(true);
		JScrollPane listScrollPane = new JScrollPane(sensitivityTableView);
		listScrollPane.setBackground(Color.white);
		listScrollPane.setPreferredSize(NolMainFrame.vpad40);
		detailedTabbedPane.addTab("Sensitivities", listScrollPane);

		varListPane = new JPanel();
		varListPane.setLayout(new BoxLayout(varListPane, BoxLayout.Y_AXIS));
		varListPane.setBackground(Color.white);
 		
		listScrollPane = new JScrollPane(varListPane);
		listScrollPane.setBorder(BorderFactory.createLoweredBevelBorder());
 		listScrollPane.setColumnHeaderView(new VarContentHeaderPane());
		detailedTabbedPane.addTab("Input Values", listScrollPane);

		detailedTabbedPane.setSelectedIndex(0);

		return detailedTabbedPane;
	}


	private JPanel getControlPanel(){
		JPanel control = new JPanel();
		control.setBackground(getContentPane().getBackground());
		control.setLayout(new BoxLayout(control, BoxLayout.Y_AXIS));
		control.setBorder(new EmptyBorder(10, 10, 10, 10));

		JPanel controlButtonPane = new JPanel(new GridLayout(2,1,5,5));
		calculateBut = new JButton("Calculate");
		calculateBut.addActionListener(actionListener);
  		controlButtonPane.add(calculateBut);
		JButton but = new JButton("Report...");
		but.addActionListener(actionListener);
 //		controlButtonPane.add(but);

		JPanel radioButtonPane = new JPanel(new GridLayout(2,1,5,5));
		radioButtonPane.setBorder(new TitledBorder("Show"));
		ButtonGroup group = new ButtonGroup();
		JRadioButton radio = new JRadioButton("Number",true);
		radio.setActionCommand("Number");
		radio.addActionListener(actionListener);
		group.add(radio);
 		radioButtonPane.add(radio);
		radio = new JRadioButton("Chart");
		radio.setActionCommand("Chart");
		radio.addActionListener(actionListener);
		group.add(radio);
 		radioButtonPane.add(radio);

		control.add(Box.createRigidArea(NolMainFrame.vpad15));
		control.add(controlButtonPane);
		control.add(radioButtonPane);
		control.add(Box.createRigidArea(NolMainFrame.vpad500));
		control.add(Box.createVerticalGlue());
		return control;
	}
	
	private void initDataDisplay(){
		
		varContentInPane = new Vector();		
		int ni = inputVars.size();
		int no = outputVars.size();
		inputValues = Matlib.createMatrix(1,ni);
		sensitivityValues = Matlib.createMatrix(ni,no);
		scaledSensitivityValues = Matlib.createMatrix(ni,no);
		for(int c=0;c<no;c++){
			for(int r=0;r<ni;r++){
				sensitivityValues.set(r,c,Double.NaN);
			}
		}

		Matlib.copy(sensitivityValues,scaledSensitivityValues);

		Preprocessor prep = model.getPreprocessor();
		
		varListPane.removeAll();
		varContentInPane.removeAllElements();

		for(int i=0;i<ni;i++){
			String varName = (String)inputVars.elementAt(i);
			Variable colObj = prep.getVariableFromVariableName(varName);
			inputValues.set(0,i,colObj.getMeanValue());
			VarContentPane contentPane = new VarContentPane
				(varName,colObj.getMeanValue(),colObj.getMinValue(),colObj.getMaxValue());
			varListPane.add(contentPane);
			varContentInPane.addElement(contentPane);
		}
		varListPane.add(Box.createVerticalGlue());
		varListPane.repaint(0l);
		varListPane.validate();	
		
		if(isCalculated){
			refreshSensitivityDataDisplay();
			calculateBut.setEnabled(false);
		}
	}

	private void refreshSensitivityDataDisplay(){
		if(!isCalculated)
			calculateSensitivities();
		calculateBut.setEnabled(false);
		sensitivityTableView.repaint(0l);
		sensitivityTableView.validate();
	}
	
	public NolModel2 getModel(){
		return model;
	}

	private void calculateSensitivities(){
		EnsembleModel ensemble = (EnsembleModel)model.getModel();
		int no = sensitivityValues.getCols();
		int ni = sensitivityValues.getRows();
		Preprocessor prep = model.getPreprocessor();
		Matrix pX = Matlib.createMatrix(1,ni);
		Matrix nX = Matlib.createMatrix(1,ni);
		Matrix pY = Matlib.createMatrix(1,no);
		Matrix nY = Matlib.createMatrix(1,no);
		Matrix singleY = Matlib.createMatrix(1,no);
		for(int i=0;i<ni;i++){
			String varName = (String)inputVars.elementAt(i);
			Variable colObj = prep.getVariableFromVariableName(varName);
			double delta = colObj.getRange()/1000;
			double var = colObj.getVariance();
			Matlib.copy(inputValues,pX);
			Matlib.copy(inputValues,nX);
			pX.set(0,i,inputValues.get(0,i)+delta);
			nX.set(0,i,inputValues.get(0,i)-delta);
			try {
				ensemble.evaluate(pX,pY);
				ensemble.evaluate(nX,nY);
				Matlib.subtract(pY,nY,singleY);
				Matlib.divide(singleY,delta*2,singleY);
				Matlib.divide(singleY,var,singleY);
				
			} catch (MathException me) {
				System.err.println("Non-Fatal exception: "+ me.getMessage());
				me.printStackTrace();
			}			
			for(int c=0;c<no;c++){
				sensitivityValues.set(i,c,singleY.get(0,c));
			}
		}
		Matlib.clear(pX);
		Matlib.clear(nX);
		Matlib.clear(pY);
		Matlib.clear(nY);
		Matlib.clear(singleY);
		isCalculated = true;
		Matlib.copy(sensitivityValues,scaledSensitivityValues);
		double[] maxAbsValue = new double[no];
		for(int c=0;c<no;c++){
			maxAbsValue[c] = 0;
			for(int r=0;r<ni;r++){
				double v = Math.abs(sensitivityValues.get(r,c));
				if(v>maxAbsValue[c])
					maxAbsValue[c] = v;
			}
		}
		for(int c=0;c<no;c++){
			if(maxAbsValue[c] >0){
				double scalor = 1.0/maxAbsValue[c];
				for(int r=0;r<ni;r++){
					scaledSensitivityValues.set(r,c,scaledSensitivityValues.get(r,c)*scalor);
				}
			}
		}
		sensitivityColorTableModel.setValues();
	}

   /**
     * Control action implementation
     */
    class ControlAction extends AbstractAction {

		ControlAction(){super("controlAction");}
			
		@Override
		public void actionPerformed(ActionEvent e) {
			if(noFire){
				return;
			}
			String command = e.getActionCommand();
			if(command.equals("Calculate")){
				refreshSensitivityDataDisplay();
			}else if(command.equals("Report...")){

			}else if(command.equals("Number")){
				sensitivityTableView.setModel(sensitivityTableModel);	
				sensitivityTableView.repaint(0l);
				sensitivityTableView.validate();
			}else if(command.equals("Chart")){
				sensitivityTableView.setModel(sensitivityColorTableModel);
				sensitivityTableView.repaint(0l);
				sensitivityTableView.validate();
			}else{
			} 
		}
    }


	class SensitivityTableModel extends AbstractTableModel{
		private int row,col;
		private String[] colHd;
		private String[] rowHd;

		public SensitivityTableModel(){
			row = inputVars.size();
			col = outputVars.size()+1;
			colHd = new String[col];
			rowHd = new String[row];		
			colHd[0] = "";			
			for(int i=1;i<col;i++){
				colHd[i] = outputVars.elementAt(i-1).toString();
			}
			for(int i=0;i<row;i++){
				rowHd[i] = inputVars.elementAt(i).toString();
			}
		}
		@Override
		public int getColumnCount() { return col; }
		@Override
		public int getRowCount() { return row;}

		@Override
		public Object getValueAt(int r, int c){
			if(c == 0){
				return rowHd[r];
			}else {
				if(Double.isNaN(sensitivityValues.get(r,c-1))){
					return "";
				}else{
					return Utilities.formatDouble(sensitivityValues.get(r,c-1), sigDigits);
				}
			}
		}
		@Override
		public String getColumnName(int c) {
			return colHd[c];
		}
		@Override
		public boolean isCellEditable(int r, int c) {
			return false;
		}		
		@Override
		public void setValueAt(Object aValue, int r, int c) {
		}
	}

	class SensitivityColorTableModel extends AbstractTableModel{
		private int row,col;
		private String[] colHd;
		private String[] rowHd;
		private ColoredBar[][] blocks;

		public SensitivityColorTableModel(){
			row = inputVars.size();
			col = outputVars.size()+1;
			colHd = new String[col];
			rowHd = new String[row];		
			colHd[0] = "";			
			for(int i=1;i<col;i++){
				colHd[i] = outputVars.elementAt(i-1).toString();
			}
			for(int i=0;i<row;i++){
				rowHd[i] = inputVars.elementAt(i).toString();
			}
			blocks = new ColoredBar[row][col-1];
			for(int c=0;c<col-1;c++){
				for(int r=0;r<row;r++){
					blocks[r][c] = new ColoredBar(Color.white, true, 1.0, 1);
				}
			}
		}
		@Override
		public int getColumnCount() { return col; }
		@Override
		public int getRowCount() { return row;}

		@Override
		public Object getValueAt(int r, int c){
			if(c == 0){
				return rowHd[r];
			}else {
				return blocks[r][c-1];
			}
		}
		@Override
		public String getColumnName(int c) {
			return colHd[c];
		}
		public void setValues() {
			for(int c=1;c<col;c++){
				boolean neg = false;
				boolean pos = false;
				int flag = 0;
 				for(int r=0;r<row;r++){
					double val = scaledSensitivityValues.get(r,c-1);
					if(val >0){
						pos = true;
					}
					if(val <0){
						neg = true;
					}
				}
 				
 				if (pos && !neg) {
					flag = 1;
 				} else if (neg && !pos) {
					flag = -1;
				}
				
				for(int r=0;r<row;r++){
					double val = scaledSensitivityValues.get(r,c-1);
					if(Double.isNaN(val)){
						blocks[r][c-1].setShowColor(Color.white);
					}else{
						if(val >= 0){
							blocks[r][c-1].setShowColor(new Color(255,0,0));
						}else{
							blocks[r][c-1].setShowColor(new Color(0,0,255));
						}
						blocks[r][c-1].setValue(val);
						blocks[r][c-1].setFlag(flag);
					}
				}
			}
		}

		@Override
		public boolean isCellEditable(int r, int c) {
			return false;
		}		
		@Override
		public void setValueAt(Object aValue, int r, int c) {
		}
		@Override
		public Class getColumnClass(int c) {
			return getValueAt(0, c).getClass();
		}

	}

	class SensitivityTableRenderer extends JComponent 
		implements TableCellRenderer, java.io.Serializable{
		@Override
		public Component getTableCellRendererComponent(JTable table,
                                               Object value,
                                               boolean isSelected,
                                               boolean hasFocus,
                                               int row,
                                               int column){
			if(value instanceof ColoredBar){
				ColoredBar block = (ColoredBar)value;
				return 	block;
			}
			return null;
		}
	}


	class VarContentPane extends JPanel implements NolSliderListener{
		protected String varName;
		protected NolSlider varSlider;
		protected JTextField currentValue;
		protected double value;
		protected double min;
		protected double max;
		public VarContentPane(String n, double v, double min, double max){
			varName = n;
			value = v;
			this.min = min;
			this.max = max;
			initialLayout();
		}

		private void initialLayout(){
////			setLayout(new BoxLayout(this, BoxLayout.X_AXIS));
			setLayout(new GridLayout(1,3,0,0));
			BorderedTextField nameLabel = new BorderedTextField(varName);
			nameLabel.setPreferredSize(new Dimension(125,20));
			varSlider = new NolSlider(min,max,value,1);
			varSlider.addNolSliderListener(this);
			varSlider.setPreferredSize(new Dimension(125,20));
			
			currentValue = new JTextField(Utilities.formatDouble(value, sigDigits));
			currentValue.setPreferredSize(new Dimension(125,20));
			
			add(nameLabel);
			add(varSlider);
			add(currentValue);
		}

		@Override
		public void valueChanged(NolSliderEvent evt){
			value = evt.getSetpoint();
			isCalculated = false;
			calculateBut.setEnabled(true);
			int index = inputVars.indexOf(varName);
			inputValues.set(0,index,value);
			currentValue.setText(Utilities.formatDouble(value, sigDigits));
		}
	}

	class VarContentHeaderPane extends JPanel{
		public VarContentHeaderPane(){
			setLayout(new GridLayout(1,3,0,0));
			BorderedLabel col1 = new BorderedLabel("Variable");
			col1.setPreferredSize(new Dimension(100,20));
			BorderedLabel col2 = new BorderedLabel("Value Slider");
			col2.setPreferredSize(new Dimension(100,20));
			BorderedLabel col3 = new BorderedLabel("Value");
			col3.setPreferredSize(new Dimension(100,20));
			col1.setHorizontalAlignment(SwingConstants.CENTER);
			col2.setHorizontalAlignment(SwingConstants.CENTER);
			col3.setHorizontalAlignment(SwingConstants.CENTER);
			add(col1);
			add(col2);
			add(col3);
		}
	}

    class BorderedTextField extends JComponent {
		String text;
		String varName;

		public BorderedTextField(String v) {
			this();
			text = v;
			varName = v;
		}
		public BorderedTextField(String t,String v) {
			this();
			text = t;
			varName = v;
		}
		public BorderedTextField() {
			super();
		}

		public void setText(String t){
			text = t;
			repaint(0l);
			validate();
		}

		public String getVarName(){
			return varName;
		}

		@Override
		public Dimension getPreferredSize() {
			Dimension size = super.getPreferredSize();
			size.height = 20;
			return size;
		}
		@Override
		public Dimension getMaximumSize() {
			return new Dimension(400, 20);
		}
		@Override
		public void paint(Graphics g) {
			super.paint(g);
			g.setColor(Color.black);
//			g.drawRect(1, 1, getWidth()-2, getHeight()-2);
			g.drawString(text,2,15 );
			g.drawRect(0, 0, getWidth(), getHeight());
		}
    }
    
    class BorderedLabel extends JLabel {

		public BorderedLabel(String text) {
			super(text);
		}
		public BorderedLabel() {
			super();
		}
		@Override
		public Dimension getPreferredSize() {
			Dimension size = super.getPreferredSize();
			size.height = 20;
			return size;
		}
		@Override
		public Dimension getMaximumSize() {
			return new Dimension(400, 20);
		}
		@Override
		public void paint(Graphics g) {
			super.paint(g);
			g.setColor(Color.black);
//			g.drawRect(1, 1, getWidth()-2, getHeight()-2);
			g.drawRect(0, 0, getWidth(), getHeight());
		}
    }
}

