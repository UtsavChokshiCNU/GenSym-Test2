package com.gensym.nols.wksp;

import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.util.*;
import java.net.*;
import java.util.zip.*;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.border.*;

import com.gensym.nols.data.*;
import com.gensym.nols.main.*;
import com.gensym.nols.dlg.*;
import com.gensym.nols.data.function.*;
import com.gensym.math.MathException;

public class NolPreprocessorWKSP  extends NolInternalFrame 
implements PreprocessorListener,InternalFrameListener {

	private NolMainFrame frame;
	private JList varNameList;
	private JTextField nameField;
	private JTextArea descriptArea;
	private JTextArea filterArea;
	private Action actionListener;
	private Action formulaActionListener;


/*	private	SpikeTableModel spikeTableModel;
	private	JTable spikeTableView;
	private	DeadSignalTableModel deadSignalTableModel;
	private	JTable deadSignalTableView;
	private	SmoothTableModel smoothTableModel;
	private	JTable smoothTableView;
  */

//	private JComboBox dataSeriesDisplayChoice;
	private JComboBox varDisplayChoice;
	private JComboBox locationDisplayChoice;
	private JList formulaList;
	private DefaultListModel formulaListModel;
	private FormulasListCellRenderer formulasListCellRenderer;
	private FormulaConstructor formulaConst;
	private JButton newVarBut;
	private boolean noFire;
//	private int dataSeriesIndex;
	private int currentPosition;
	private Formula2 currentFormula = null;   // the formula being edited
	private int funcMode;  // 0=drag enabled, 1=modify, 3=add formula
	private int moveFrom;
	private int moveTo;
	private Vector varFormulaIndex = null;
	private String currentVariable;

	// Layout constants of formula constructor
	private static int INPUT_FIELD_WIDTH = 30000;
	private static int VGAP = 10;  // typical vertical spacing between components
	private static int H0 = 25;  // height of text and label fields, full-sized buttons
	private static int H1 = 17;  // height of short buttons (New var, etc.)
	private static int H2 = 42;  // height of viewport of input field
	private static int H3 =	150; // height of list boxes and numerical entry
	private static int H4 = 50;  // height of help field (allows 2 lines)

	private static int Y0 = VGAP;        // top of output field 
	private static int Y1 = Y0+H0+VGAP;  // top of input field 
	private static int Y2 = Y1+H2+VGAP;  // top of button row 
	private static int Y3 = Y2+H1+VGAP;	 // top of list boxes and numerical buttons
	private static int Y4 = Y3+H3+VGAP;	 // top of help text field
	private static int Y5 = Y4+H4+VGAP;  // total height of dialog

	private static int WGAP = 10;  // horizontal spacing between components
	private static int W0 = 60;	// width of text-field labels
	private static int W1 = 530;   // width of input/output text fields
	private static int W2 = 190;  // width of list boxes, number entry pane
	private static int W3 = 80;  // width of full-sized buttons (OK, cancel)
	private static int W4 = 160; // width of arrow-button set

	private static int X0 = WGAP;
	private static int X1 = X0+W0;		// left edge of text fields
	private static int X2 = X0+W2+WGAP;  // left edge of formula pane
	private static int X3 = X2+W2+WGAP;  // left edge of number pane
	private static int X4 = X1+W1+WGAP;  // left edge of OK, Cancel buttons
	private static int X5 = X4+W3+WGAP;  // total width of dialog
	private static int X6 = X1+W4+WGAP;  // left edge of label button set (undo, redo, etc.)


    private static final String NAME = "NameLabel";
    private static final String GENERAL = "GeneralLabel";
    private static final String COMMENT = "CommentLabel";
    private static final String FILTER = "PreprocessorWKSP_Filter";
    private static final String VARIABLES = "VariableLabel";
    private static final String DELETE = "DeleteLabel";
    private static final String REAPPLY = "PreprocessorWKSP_Reapply";
    private static final String FORMULAS = "PreprocessorWKSP_Formulas";
    private static final String VIEW = "PreprocessorWKSP_View";
    private static final String LOCATION = "PreprocessorWKSP_Location";
    private static final String APPLY = "PreprocessorWKSP_Apply";
    private static final String EXPORT = "PreprocessorWKSP_Export";
    private static final String IMPORT = "PreprocessorWKSP_Import";
    private static final String INSERT = "PreprocessorWKSP_Insert";
    private static final String MODIFY = "PreprocessorWKSP_Modify";
    private static final String REMOVE = "PreprocessorWKSP_Remove";
    private static final String NEWFORMULALABEL = "PreprocessorWKSP_NewFormulaLabel";
    private static final String ANYVARIABLES = "PreprocessorWKSP_AnyVariables";
    private static final String ANYWHERE = "PreprocessorWKSP_AnyWhere";
    private static final String INPUTS = "PreprocessorWKSP_Inputs";
    private static final String OUTPUTS = "PreprocessorWKSP_Outputs";

    private static final String FORMULA = "PreprocessorWKSP_Formula";
    private static final String NEW = "PreprocessorWKSP_New";
    private static final String OK = "OkButtonLabel";
    private static final String CANCEL = "CancelButtonLabel";
    private static final String FUNCTIONS = "PreprocessorWKSP_Functions";
    private static final String NUMERICALINPUTS = "PreprocessorWKSP_NumericalInputs";
    private static final String UNDO = "PreprocessorWKSP_Undo";
    private static final String REDO = "PreprocessorWKSP_Redo";
    private static final String ADDARG = "PreprocessorWKSP_AddArg";
    private static final String DELARG = "PreprocessorWKSP_DelArg";
    
	private static final String SOURCE = "PreprocessorWKSP_Source";
    private static final String FROMPREPROCESSOR = "PreprocessorWKSP_FromPreprocessor";
    private static final String FROMFILE = "PreprocessorWKSP_FromFile";
    private static final String FILE = "PreprocessorWKSP_File";

	public NolPreprocessorWKSP (NolMainFrame frame, Preprocessor prep){
		super(prep);
		this.frame = frame;
		String title = "Preprocessor:["+prep.getName()+"]";
		setTitle(title);

		noFire = true;
		actionListener = new ControlAction();
		formulaActionListener = new FormulaControlAction();

		initLayout();
		initDataDisplay();

		prep.addListener(this);
//		dataSeriesIndex = 0;
		initializeFormulaDataDisplay();		
		addInternalFrameListener(this);
		noFire = false;
	}

 	private void initDataDisplay(){
		nameField.setText(dataSource.getName());
		String s = getQueryText((Preprocessor)dataSource);
		filterArea.setText(s);
		s = dataSource.getComment();
		descriptArea.setText(s);
		Vector vs = ((Preprocessor)dataSource).getVariableNames();
		varNameList.setListData(vs);
/*		spikeTableModel.setContent(vs);
		deadSignalTableModel.setContent(vs);
		smoothTableModel.setContent(vs);
*/	}
	
	private String getQueryText(Preprocessor prep){
		String s = "";
		ViewFilter vfr = prep.getViewFilter();
		LabelPattern[] showPatterns = vfr.getPatternsToShow();
		LabelPattern[] hidePatterns = vfr.getPatternsToHide();
		s = s+"Label Query:\n";
		s = s+"    " + "Include:\n";
		if(showPatterns.length==0){
			s = s+"        " + "All data points.\n";
		}else{
			for(int i=0;i<showPatterns.length;i++){
				Vector labelPresent = showPatterns[i].getLabelsPresent();
				Vector labelAbsent = showPatterns[i].getLabelsAbsent();
				if(labelPresent.isEmpty() || !labelAbsent.isEmpty()){
					s = s+"        " + "Any point unlabeled";
				}else if(labelPresent.size() ==1){
					s = s+"        " + "Any point labeled with "+
					labelPresent.elementAt(0) + "\n";
				}else{
					s = s+"        " + "Any point labeled with ";
					for(int j=0;j<labelPresent.size()-1;j++)
						s = s+labelPresent.elementAt(j)+" and ";
					s = s+labelPresent.elementAt(labelPresent.size()-1)+"\n";
				}
			}
		}
		if(hidePatterns.length>0){
			s = s+"    " + "Exclude:\n";
			for(int i=0;i<hidePatterns.length;i++){
				Vector labelPresent = hidePatterns[i].getLabelsPresent();
				Vector labelAbsent = hidePatterns[i].getLabelsAbsent();
				if(labelPresent.isEmpty() || !labelAbsent.isEmpty())
					s = s+"        " + "Any point unlabeled";
				else if(labelPresent.size() ==1)
					s = s+"        " + "Any point labeled with "+
					labelPresent.elementAt(0) + "\n";
				else{
					s = s+"        " + "Any point labeled with ";
					for(int j=0;j<labelPresent.size()-1;j++)
						s = s+labelPresent.elementAt(j)+" and ";
					s = s+labelPresent.elementAt(labelPresent.size()-1)+"\n";
				}
			}
		}			

		return s;
	}

	private void initLayout(){
		JPanel workPane = new JPanel(new BorderLayout());

		JTabbedPane cenPane = new JTabbedPane();
		cenPane.addTab("General", getGeneralPanel());
//		cenPane.addTab("Spike Detection", getSpikePanel());
//		cenPane.addTab("Dead Signal Detection", getDeadPanel());
//		cenPane.addTab("Smooth", getSmoothPanel());
		cenPane.addTab("Formulas", getFormulaPanel());
		
		cenPane.setSelectedIndex(0);
		workPane.add("Center",cenPane);

//		workPane.add("Center",getGeneralPanel());
//		workPane.add("East",getControlPanel());
		setContentPane(workPane);
	}

	private JPanel getGeneralPanel(){
		JPanel genPane = new JPanel(new BorderLayout());
 		genPane.setBorder(new EmptyBorder(10,10,10,10));

		JPanel infoPane = new JPanel(new BorderLayout());
		JPanel namePane = new JPanel(new GridLayout(1,2,5,5));
		namePane.add(new JLabel(frame.getNolResourceString(NAME)+":"));
		nameField = new JTextField();
		nameField.addActionListener(actionListener);
		namePane.add(nameField);

 		JPanel descriptPane = new JPanel(new GridLayout());
		descriptPane.setBorder(new TitledBorder(new EmptyBorder(1, 1, 1, 1),               
			frame.getNolResourceString(COMMENT)+":", TitledBorder.LEFT , TitledBorder.TOP));
		descriptArea = new JTextArea();
		descriptArea.getDocument().addDocumentListener((DocumentListener)actionListener);
		JScrollPane listScrollPane = new JScrollPane(descriptArea);
		listScrollPane.setBorder(BorderFactory.createLoweredBevelBorder());
		listScrollPane.setPreferredSize(NolMainFrame.vpad40); 

		descriptPane.add(listScrollPane);

		JPanel filterPane = new JPanel(new GridLayout());
		filterPane.setBorder(new TitledBorder(new EmptyBorder(1, 1, 1, 1),               
			frame.getNolResourceString(FILTER)+":", TitledBorder.LEFT , TitledBorder.TOP));
		filterArea = new JTextArea();
		filterArea.setEditable(false);
		listScrollPane = new JScrollPane(filterArea);
		listScrollPane.setBorder(BorderFactory.createLoweredBevelBorder());
		listScrollPane.setPreferredSize(NolMainFrame.vpad50); 

		filterPane.add(listScrollPane);

		infoPane.add("North",namePane);
		JPanel pane = new JPanel(new GridLayout(2,1,5,5));
		pane.add(descriptPane);
		pane.add(filterPane);
		infoPane.add("Center",pane);

		JPanel listPane = new JPanel(new GridLayout());
		listPane.setBorder(new TitledBorder(new EmptyBorder(1, 1, 1, 1),               
			frame.getNolResourceString(VARIABLES)+":", TitledBorder.LEFT , TitledBorder.TOP));
  		varNameList = new JList();
//		varNameList.setBackground(Color.white);
		varNameList.addMouseListener((MouseListener)actionListener);
		listScrollPane = new JScrollPane(varNameList);
		listScrollPane.setBorder(BorderFactory.createLoweredBevelBorder());
		listPane.add(listScrollPane);

		JPanel cenPane = new JPanel(new BorderLayout());
		cenPane.add("North",infoPane);
		cenPane.add("Center",listPane);
		genPane.add("Center",cenPane);
		genPane.add("East",getControlPanel());
		return genPane;
	}


	private JPanel getControlPanel(){
		JPanel control = new JPanel();
		control.setBackground(getContentPane().getBackground());
		control.setLayout(new BoxLayout(control, BoxLayout.Y_AXIS));
		control.setBorder(new EmptyBorder(10, 10, 10, 10));

		JPanel pane0 = new JPanel(new GridLayout(2,1,5,5));
		JButton but = new JButton(frame.getNolResourceString(REAPPLY));
		but.setActionCommand("Reapply Preprocessor");
		but.addActionListener(actionListener);
		but.setEnabled(true); //Gchen Temp 1/27/99 -- MK 2/6/99 turned back on, we have to make it work
  		pane0.add(but);

/*		but = new JButton("Apply to New Data");
		but.addActionListener(actionListener);
		but.setEnabled(false); //Gchen Temp 1/27/99
  		pane0.add(but);
  */
		but = new JButton(frame.getNolResourceString(DELETE));
		but.setActionCommand("Delete");
		but.addActionListener(actionListener);
  		pane0.add(but);
		control.add(Box.createRigidArea(NolMainFrame.vpad15));
		control.add(pane0);
		control.add(Box.createRigidArea(NolMainFrame.vpad500));
		control.add(Box.createVerticalGlue());
		return control;
	}

	public Preprocessor getPreprocessor(){
		return (Preprocessor)dataSource;
	}

	private void refreshDisplay(){
		Rectangle rv = this.getBounds();
		this.setBounds(rv.x,rv.y,rv.width+1,rv.height);
		this.paintImmediately(rv.x,rv.y,rv.width+1,rv.height);
		this.validate();
		this.setBounds(rv.x,rv.y,rv.width,rv.height);
		this.validate();
	}

/** The inner control listener class.*/
    class ControlAction extends AbstractAction implements DocumentListener, MouseListener, Runnable {
		String command;
		Object source;
		ControlAction() {super("controlAction");}
		@Override
		public void actionPerformed(ActionEvent e) {
			command = e.getActionCommand ();
			source = e.getSource ();
			new Thread (this).start();
		}
        @Override
		public void run() {
			setWaitCursor(true);
			if(command.equals("Formulas")){
				frame.showFormulaListWKSP((Preprocessor)dataSource);
			}else if(source.equals(nameField)){
				String caseName = nameField.getText();
				if(caseName.length() > 0){
					dataSource.setName(caseName); //Need to generate event
					String title = "Preprocessor:["+caseName+"]";
					setTitle(title);
					frame.getProjectTree().changePreprocessorName((Preprocessor)dataSource,true);
					refreshDisplay();
				}else{
					caseName = dataSource.getName();
					nameField.setText(caseName);
				}
			}else if(command.equals("Apply to New Data")){
			}else if(command.equals("Reapply Preprocessor")){
				try {
					((Preprocessor)dataSource).reapplyPreprocessor();
				} catch (FormulaException e) {
					frame.showOKDialog(e.getMessage());
				} catch (MathException e) {
					frame.showOKDialog(e.getMessage());
				} catch (Exception e) {
					System.err.println("Error applying formula: " + e.getMessage());
					e.printStackTrace();
				}
			}else if(command.equals("Delete")){
				frame.removePreprocessor((Preprocessor)dataSource);
			}
			setWaitCursor(false);
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
			dataSource.setComment(com);
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
			int clickCount =  m.getClickCount();
			if(clickCount != 2){
				return;
			}
			int index = varNameList.getSelectedIndex();
			Vector vs = ((Preprocessor)dataSource).getVariableNames();
			String varName = (String)vs.elementAt(index);
			Variable varObj = ((Preprocessor)dataSource).getVariableFromVariableName(varName);
			frame.showVariableWKSP(varObj);
		}
    }


/** initializeFormulaLayout. */
	private JPanel getFormulaPanel(){
		JPanel formulaPane = new JPanel(new BorderLayout());
  		formulaPane.setBorder(new EmptyBorder(10,10,10,10));

		formulaPane.setBackground(getContentPane().getBackground());

		JPanel varChoicePane = new JPanel();
		varChoicePane.setBorder(new TitledBorder(new EmptyBorder(1, 1, 1, 1),               
					frame.getNolResourceString(VARIABLES)+":", TitledBorder.LEFT , TitledBorder.TOP));
		varChoicePane.setLayout(new GridLayout());
		varDisplayChoice = new JComboBox ();
		varDisplayChoice.addItemListener((ItemListener)formulaActionListener);
		varChoicePane.add(varDisplayChoice);

		JPanel locationPane = new JPanel();
		locationPane.setBorder(new TitledBorder(new EmptyBorder(1, 1, 1, 1),               
					frame.getNolResourceString(LOCATION)+":", TitledBorder.LEFT , TitledBorder.TOP));
		locationPane.setLayout(new GridLayout());
		locationDisplayChoice = new JComboBox ();
 		locationDisplayChoice.addItemListener((ItemListener)formulaActionListener);
		locationPane.add(locationDisplayChoice);
		locationDisplayChoice.addItem(frame.getNolResourceString(ANYWHERE));
		locationDisplayChoice.addItem(frame.getNolResourceString(OUTPUTS));
		locationDisplayChoice.addItem(frame.getNolResourceString(INPUTS));

		JPanel tranListPane = new JPanel();
		tranListPane.setBorder(new TitledBorder(new EmptyBorder(1, 1, 1, 1),               
					frame.getNolResourceString(FORMULAS)+":", TitledBorder.LEFT , TitledBorder.TOP));
		tranListPane.setLayout(new GridLayout());
		formulaList = new JList(getFormulasListModel());
		formulaList.setBackground(Color.white);
		formulaList.addListSelectionListener((ListSelectionListener)formulaActionListener);
		formulaList.addMouseListener((MouseListener)formulaActionListener);
		formulaList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);  // new 2/26/99 -- method add, remove, move weren't able to handle multiple selection
		JScrollPane listScrollPane = new JScrollPane(formulaList);
		tranListPane.add(listScrollPane);

		JPanel pane0 = new JPanel(new GridLayout(1,3,5,5));
		pane0.setBorder(new TitledBorder(frame.getNolResourceString(VIEW)+":"));
		pane0.add(varChoicePane);
		pane0.add(locationPane);

		JPanel pane1 = new JPanel();
		pane1.setLayout(new BorderLayout());
		pane1.add("North",pane0);
		pane1.add("Center",tranListPane);

		formulaPane.add("Center",pane1);
		formulaPane.add("East",getFormulaControlPanel());

		formulaList.setCellRenderer(getFormulasListCellRenderer());

		return formulaPane;
	}

	private JPanel getFormulaControlPanel(){
		JPanel control = new JPanel();
		control.setBackground(getContentPane().getBackground());
		control.setLayout(new BoxLayout(control, BoxLayout.Y_AXIS));
		control.setBorder(new EmptyBorder(10, 10, 10, 10));

		JPanel pane0 = new JPanel(new GridLayout(7,1,5,5));
		JButton but = new JButton(frame.getNolResourceString(APPLY));
		but.setActionCommand("Apply");
		but.addActionListener(formulaActionListener);
  		pane0.add(but);
  		pane0.add(new JPanel());

		but = new JButton(frame.getNolResourceString(INSERT));
		but.setActionCommand("Insert...");
		but.addActionListener(formulaActionListener);
  		pane0.add(but);

		but = new JButton(frame.getNolResourceString(MODIFY));
		but.setActionCommand("Modify...");
		but.addActionListener(formulaActionListener);
  		pane0.add(but);

		but = new JButton(frame.getNolResourceString(IMPORT));
		but.setActionCommand("Import...");
		but.addActionListener(formulaActionListener);
  		pane0.add(but);

		but = new JButton(frame.getNolResourceString(EXPORT));
		but.setActionCommand("Export...");
		but.addActionListener(formulaActionListener);
  		pane0.add(but);
		
		but = new JButton(frame.getNolResourceString(REMOVE));
		but.setActionCommand("Remove...");
		but.addActionListener(formulaActionListener);
  		pane0.add(but);

		control.add(Box.createRigidArea(NolMainFrame.vpad15));
		control.add(pane0);
		control.add(Box.createRigidArea(NolMainFrame.vpad500));
		control.add(Box.createVerticalGlue());
		return control;
	}

	private void initializeFormulaDataDisplay(){
		currentVariable = "Any Variables";
		varFormulaIndex = new Vector();
 		displayVarDisplayChoice();
		displayFormulaList(currentVariable);
		getFormulaConst().displayFormulaChoice();
		getFormulaConst().displayVarListChoice();
		currentPosition = getFormulasListModel().getSize()-1;
		formulaList.setSelectedIndex(currentPosition);
		formulaList.validate();
	}

	private FormulasListCellRenderer getFormulasListCellRenderer() {
		if (formulasListCellRenderer == null) {
			formulasListCellRenderer = new FormulasListCellRenderer(formulaList, new Vector());
		}
		return formulasListCellRenderer;
	}

	private DefaultListModel getFormulasListModel() {
		if (formulaListModel == null) {
			formulaListModel = new DefaultListModel();
		}
		return formulaListModel;
	}

	private FormulaConstructor getFormulaConst(){
		if (formulaConst == null) {
			formulaConst = new FormulaConstructor(frame);
		}
		return formulaConst;
	}
/** Display the new variable Choice items.*/
	public void displayVarDisplayChoice(){
		int nds = ((Preprocessor)dataSource).getNumberOfDataSeries();
/*		if(dataSeriesIndex >= 0 && dataSeriesIndex< nds){
			DataSeries ds = dataSource.getDataSeries(dataSeriesIndex);
			Vector varObjs = ds.getVarObjects();	
			varDisplayChoice.removeAllItems();
			varDisplayChoice.addItem("Any Variables");
			for(int i=0;i<varObjs.size();i++){
				String n = varObjs.elementAt(i).toString();
				varDisplayChoice.addItem(n);	
			}
		}else{
			Vector dss = dataSource.getDataSeries();
			varDisplayChoice.removeAllItems();
			varDisplayChoice.addItem("Any Variables");
			for(int i=0;i<dss.size();i++){
				Vector varObjs = ((DataSeries)dss.elementAt(i)).getVarObjects();
				for(int j=0;j<varObjs.size();j++){
					String n = varObjs.elementAt(j).toString();
					varDisplayChoice.addItem(n);	
				}
			}
		}
*/
		Vector dss = dataSource.getDataSeries();
		varDisplayChoice.removeAllItems();
		varDisplayChoice.addItem("Any Variables");
		for(int i=0;i<dss.size();i++){
			Vector varObjs = ((DataSeries)dss.elementAt(i)).getVarObjects();
			for(int j=0;j<varObjs.size();j++){
				String n = varObjs.elementAt(j).toString();
				varDisplayChoice.addItem(n);	
			}
		}
	}

/** Display the formula list for current variable.*/
	public void displayFormulaList(String currentVarSelect){
		Vector fms = ((Preprocessor)dataSource).getFormulas();
		getFormulasListCellRenderer().modifyContent(fms);
		varFormulaIndex.removeAllElements();
		getFormulasListModel().removeAllElements();
		int displayMode = locationDisplayChoice.getSelectedIndex();
		if(currentVarSelect.equals("Any Variables")){
			for(int i=0;i<fms.size();i++){
				Formula2 fm = (Formula2)fms.elementAt(i);
				getFormulasListModel().addElement(i+1);
				varFormulaIndex.addElement(fm);
			}
			getFormulasListModel().addElement(0);
				
		}else{
			for(int i=0;i<fms.size();i++){
				Formula2 fm = (Formula2)fms.elementAt(i);
				if(displayMode == 1){ 
					if(fm.hasOutput(currentVarSelect)){
						getFormulasListModel().addElement(i+1);
						varFormulaIndex.addElement(fm);
					}
				}else if(displayMode == 2){
					if(fm.hasInput(currentVarSelect)){
						getFormulasListModel().addElement(i+1);
						varFormulaIndex.addElement(fm);
					}
				}else if(displayMode == 0){
					if(fm.hasVariable(currentVarSelect)){
						getFormulasListModel().addElement(i+1);
						varFormulaIndex.addElement(fm);
					}
				}
			}
			getFormulasListModel().addElement(0);
		}
		formulaList.validate();
	}

/** Add the current Formula into the Formula list of the preprocessor at
cuurent position.*/
	public boolean addFormula(Formula2 tf){
		int position = getCurrentPosition(currentPosition);
		if(position == -1) {
			position = ((Preprocessor)dataSource).getFormulas().size();	
		}
		boolean valid = true;
		if(position >= ((Preprocessor)dataSource).getFormulas().size()){
			valid = ((Preprocessor)dataSource).addFormula(tf);
		}else{
			valid = ((Preprocessor)dataSource).addFormula(tf,position);
		}
		if(!valid) {
			Toolkit.getDefaultToolkit().beep();
			frame.showOKDialog("Could not add formula. It uses variables undefined by previous formulas.");
		}
		return valid;
	}

/** Add the formulas into the Formula list of the preprocessor at
cuurent position.*/
	public boolean addFormulas(Vector fms){
		int position = getCurrentPosition(currentPosition);
		if(position == -1) {
			position = ((Preprocessor)dataSource).getFormulas().size();	
		}
		boolean valid = true;
		if(position >= ((Preprocessor)dataSource).getFormulas().size()){
			valid = ((Preprocessor)dataSource).addFormulas(fms);
		}else{
			valid = ((Preprocessor)dataSource).addFormulas(fms,position);
		}
		if(!valid) {
			Toolkit.getDefaultToolkit().beep();
			frame.showOKDialog("Could not add formulas. It uses variables undefined by previous formulas.");
		}
		return valid;
	}

/** Add the current formula into the Formula list of the OfflineFormulaer at
cuurent position.*/
	public boolean modifyFormula(Formula2 tf){
		int position = getCurrentPosition(currentPosition);
		boolean valid = true;
		if(position > ((Preprocessor)dataSource).getFormulas().size() || position == -1){
			return false;
		}else if(position == ((Preprocessor)dataSource).getFormulas().size()){
			valid = ((Preprocessor)dataSource).addFormula(tf);
		}else{
			valid = ((Preprocessor)dataSource).modifyFormula(tf,position);
		}
		if(!valid) {
			Toolkit.getDefaultToolkit().beep();
			frame.showOKDialog("Could not save modifications.  The formula uses variables undefined by previous formulas.");
		}
		return valid;
	}

 /** Get the index of the current position in the global formula list.*/
	private int getCurrentPosition(int listPosition){

		if(varFormulaIndex == null) 
			return listPosition;
		if(varFormulaIndex.isEmpty()) 
			return listPosition;

		Vector fms = ((Preprocessor)dataSource).getFormulas();
		if(listPosition >= varFormulaIndex.size()){
			Formula2 fm = (Formula2)varFormulaIndex.lastElement(); 
			for(int i=0;i<fms.size();i++){
				if(fm.equals(fms.elementAt(i)))
				return i+1;
			}
		}else{
			Formula2 fm = (Formula2)this.varFormulaIndex.elementAt(listPosition); 
			for(int i=0;i<fms.size();i++){
				if(fm.equals(fms.elementAt(i)))
					return i;
			}
		}
		return -1;
	}


/** The inner control listener class.*/
    class FormulaControlAction extends AbstractAction implements 
		MouseListener,ItemListener, ListSelectionListener{
		FormulaControlAction() {super("controlAction");}

        @Override
		public void actionPerformed(ActionEvent e) {
			String command = e.getActionCommand();
			if(command.equals("Apply")){
				applyFormulaAction();
			}else if(command.equals("Export...")){
				exportFormulaAction();
			}else if(command.equals("Import...")){
				importFormulaAction();
			}else if(command.equals("Insert...")){
				addFormulaAction();
			}else if(command.equals("Modify...")){
				modifyFormulaAction();
			}else if(command.equals("Remove...")){
				removeFormulaAction();
			}
		}

		@Override
		public void mousePressed(MouseEvent m) {
			if(m.getSource().equals(formulaList) && funcMode==0){
				if(varFormulaIndex.size() < 2) {
					return;
				}
				int position = m.getY()/16;  // must calculate, nothing selected yet
				int limit = varFormulaIndex.size();
				if(position >= limit) {
					return;  // don't allow user to move the last entry
				}else{
					moveFrom = getCurrentPosition(position);
				}
				formulaList.setCursor(new Cursor(Cursor.HAND_CURSOR));
			}
		}

		@Override
		public void mouseEntered(MouseEvent m) {
			if(m.getSource().equals(formulaList) && funcMode == 0 && moveFrom != -1) {

			}
		}
		@Override
		public void mouseExited(MouseEvent m) {
			if( m.getSource().equals(formulaList) && funcMode == 0 && moveFrom != -1) {


			}
		}
		@Override
		public void mouseReleased(MouseEvent m) {
			if(m.getSource().equals(formulaList) && funcMode == 0 && moveFrom != -1){
				noFire = true;
				formulaList.setCursor(new Cursor(Cursor.DEFAULT_CURSOR));
				// see if the user is selecting a range, if so, no move!
/*				if(formulaList.getMinSelectionIndex()!=formulaList.getMaxSelectionIndex()) {
					noFire = false;
					moveFrom = -1;
					return;
				} */
				currentPosition = formulaList.getSelectedIndex();
				if(currentPosition==moveFrom) {
					noFire = false;
					moveFrom=-1;
					return;
				}
				int limit = varFormulaIndex.size();
				if(currentPosition >= limit){
					moveTo = getCurrentPosition(currentPosition - 1);
				}else {
					moveTo = getCurrentPosition(currentPosition);
				}
				if(!((Preprocessor)dataSource).moveFormula(moveFrom, moveTo)) {
					Toolkit.getDefaultToolkit().beep();
					frame.showOKDialog("Cannot move formula to that position");
				}
				moveFrom=-1;
				noFire = false;
			}
		}
		public void mouseDragged(MouseEvent m) {}
		public void mouseMoved(MouseEvent m) {}
		@Override
		public void mouseClicked(MouseEvent m) {}
		@Override
		public void itemStateChanged(ItemEvent e) {
			if(noFire){
				return;
			}
/*			if (e.getSource() == dataSeriesDisplayChoice) {
				noFire = true;
				dataSeriesIndex = dataSeriesDisplayChoice.getSelectedIndex();
				displayVarDisplayChoice();
				displayFormulaList(currentVariable);
				currentPosition = getFormulasListModel().getSize()-1;
				formulaList.setSelectedIndex(currentPosition);
				formulaList.validate();
				noFire = false;
			}else if (e.getSource() == varDisplayChoice) {
*/			if (e.getSource().equals(varDisplayChoice)) {
				noFire = true;
				currentVariable = (String)varDisplayChoice.getSelectedItem();
				displayFormulaList(currentVariable);
				currentPosition = getFormulasListModel().getSize()-1;
				formulaList.setSelectedIndex(currentPosition);
				formulaList.validate();
				noFire = false;
			}else if (e.getSource().equals(locationDisplayChoice)) {
				displayFormulaList(currentVariable);
				currentPosition = getFormulasListModel().getSize()-1;
				formulaList.setSelectedIndex(currentPosition);
				formulaList.validate();
			}
		}

		@Override
		public void valueChanged(ListSelectionEvent e) {
			if(noFire){
				return;
			}
			if (e.getSource().equals(formulaList)) 
				currentPosition = formulaList.getSelectedIndex();
		}

    }
	@Override
	public void FormulaListChanged(PreprocessorEvent evt) {
		if (!dataSource.equals((Preprocessor)evt.getPreprocessor())) 
			return;
		noFire = true;
		displayFormulaList(currentVariable);
		formulaList.setSelectedIndex(currentPosition);

/*		Vector dss = dataSource.getDataSeries();
		int vc = 0;
		for(int i=0;i<dss.size();i++){
			Vector varObjs = ((DataSeries)dss.elementAt(i)).getVarObjects();
			vc = vc+varObjs.size();
		}
//		System.out.println("vc="+vc);
//		System.out.println("varDisplayChoice.getItemCount()-1="+varDisplayChoice.getItemCount());
		if(vc != varDisplayChoice.getItemCount()-1){
			displayVarDisplayChoice();
			getFormulaConst().displayVarListChoice();
		}

/*		if(dataSeriesIndex < dataSource.getNumberOfDataSeries()){
			DataSeries ds = dataSource.getDataSeries(dataSeriesIndex);
			int vc = ds.getVarObjects().size();
			if(vc != varDisplayChoice.getItemCount()-1){
				displayVarDisplayChoice();
				getFormulaConst().displayVarListChoice();
			}
		}
*/		noFire = false;
	}

	@Override
	public void DataChanged(PreprocessorEvent e) {
		noFire = true;
		Vector dss = dataSource.getDataSeries();
		int vc = 0;
		for(int i=0;i<dss.size();i++){
			Vector varObjs = ((DataSeries)dss.elementAt(i)).getVarObjects();
			vc = vc+varObjs.size();
		}
//		System.out.println("vc="+vc);
//		System.out.println("varDisplayChoice.getItemCount()-1="+varDisplayChoice.getItemCount());
		if(vc != varDisplayChoice.getItemCount()-1){
			displayVarDisplayChoice();
			getFormulaConst().displayVarListChoice();
		}
		noFire = false;
	
	}

	@Override
	public void internalFrameOpened(InternalFrameEvent e){}
	@Override
	public void internalFrameClosing(InternalFrameEvent e){}
	@Override
	public void internalFrameClosed(InternalFrameEvent e){applyFormulaAction();}
	@Override
	public void internalFrameIconified(InternalFrameEvent e){}
	@Override
	public void internalFrameDeiconified(InternalFrameEvent e){}
	@Override
	public void internalFrameActivated(InternalFrameEvent e){}
	@Override
	public void internalFrameDeactivated(InternalFrameEvent e){}

	private void applyFormulaAction() {
		if(noFire) {
			return;
		}
		try {
			((Preprocessor)dataSource).updateFormulas();
		} catch (FormulaException e) {
			frame.showOKDialog(e.getMessage());
		} catch (MathException e) {
			frame.showOKDialog(e.getMessage());
		} catch (Exception e) {
			System.err.println("Error applying formula: " + e.getMessage());
			e.printStackTrace();
		}
		Toolkit.getDefaultToolkit().beep();
//		frame.getProjectTree().setroject();
	}

	private void exportFormulaAction() {
		if(noFire) {
			return;
		}
		Preprocessor prep = (Preprocessor)dataSource;
		if(prep.getNumberOfFormulas() == 0){
			return;
		}

		JFileChooser fileChooser = new JFileChooser();
		fileChooser.setDialogTitle("Export Formula List");
		NolFileFilter filter1 = new NolFileFilter(
		new String[] {"tfm"}, "Binary Formula File"
		);
		fileChooser.addChoosableFileFilter(filter1);
		fileChooser.setFileFilter(filter1);
		fileChooser.setDialogType(JFileChooser.SAVE_DIALOG);

		fileChooser.setSelectedFile(new File(prep.getName()+".tfm"));
		fileChooser.setLocation(200,200);			
		int retval = fileChooser.showSaveDialog(frame);

		fileChooser.setFileFilter(null);
		fileChooser.removeChoosableFileFilter(filter1);

		if(retval == JFileChooser.CANCEL_OPTION){
			return;
		}
		File currentPath = fileChooser.getSelectedFile();
		if(currentPath == null){
			return;
		}

		String file = currentPath.getName();
		String directory = currentPath.getParent();
		
/*		FileDialog fileDialog = new FileDialog((Frame)frame);
		fileDialog.setMode(FileDialog.SAVE);
		fileDialog.setFile(prep.getName()+".tfm");
		fileDialog.setTitle("Export Formula List");
		fileDialog.setLocation(200,200);			
		fileDialog.show();

		String file = fileDialog.getFile();
		if (file == null) return;
		String directory = fileDialog.getDirectory();
*/
		
		// try to start writing		
		int dotInd = file.indexOf(".");
		if(dotInd == -1){
			file = file+".tfm";		
		}
		prep.saveFormulasBinary(directory, file);
		Toolkit.getDefaultToolkit().beep();
	}

	private void importFormulaAction() {
		if(noFire) {
			return;
		}
		Preprocessor prep = (Preprocessor)dataSource;
		NolImportFormulaDialog dg = 
			new NolImportFormulaDialog(frame, prep);			
		dg.setBounds(50, 50, 700, 300);
		dg.setVisible(true);
	}

	private void addFormulaAction() {
		if(noFire){
			return;
		}
//		if(dataSeriesIndex>=dataSource.getNumberOfDataSeries()) return;
		funcMode = 3;
		noFire = true;
		//getFormulasListModel().removeElement(new Integer(0));
		//getFormulasListModel().insertElementAt(new Integer(0),currentPosition);
		//formulaList.validate();   // is this necessary here?  I thought it was already validated...
		//formulaList.setSelectedIndex(currentPosition);
		currentFormula = new Formula2();
		FormulaConstructor fc = getFormulaConst();
		fc.initializeEditContext(); 
		fc.setBounds(200,200,X5,Y5);
		fc.setVisible(true); 
		noFire = false;
	}

 /**  */
	private void modifyFormulaAction() {
		if(noFire) {
			return;
		}
//		if(dataSeriesIndex>=dataSource.getNumberOfDataSeries()) return;
		noFire = true;        
		funcMode = 1;
		Integer posit = (Integer)getFormulasListModel().elementAt(currentPosition);
		if(posit.intValue() == 0){
			currentFormula = new Formula2();
		}else{
			Formula2 originalFormula = (Formula2) ((Preprocessor)dataSource).getFormulas().elementAt(posit.intValue()-1);
			currentFormula = new Formula2(originalFormula);  // returns a clone
		}
		FormulaConstructor fc = getFormulaConst();
		fc.initializeEditContext();
		fc.setBounds(200,200,X5,Y5);  
		fc.setVisible(true); 
		noFire = false;
	}
	/**RemoveFormula.action.*/
	private void removeFormulaAction() {
		if(noFire) {
			return;
		}
		int position = getCurrentPosition(currentPosition);
		if(position <= -1) {
			return;
		}
		if(position <= ((Preprocessor)dataSource).getFormulas().size()-1){
			((Preprocessor)dataSource).removeFormula(position);
			if(currentPosition > varFormulaIndex.size()-1){
				currentPosition = varFormulaIndex.size()-1;
				if(currentPosition<0) {
					currentPosition=0;
				}
			}
		}
	}

	class FormulasListCellRenderer extends JLabel implements ListCellRenderer {
		JList   listBox;
		Color highlightColor = new Color(0, 0, 128);
		String[] formulaStrings;

		FormulasListCellRenderer(JList listBox, Vector formulas) {
			setOpaque(true);
			this.listBox = listBox;
			if(formulas != null){
				this.formulaStrings = new String[formulas.size()+1];
				formulaStrings[0] = frame.getNolResourceString(NEWFORMULALABEL);
				for(int i=1;i<=formulas.size();i++){
					formulaStrings[i] = formulas.elementAt(i-1).toString();
				}
			}
		}
		public void modifyContent(Vector formulas){
			this.formulaStrings = new String[formulas.size()+1];
			formulaStrings[0] = frame.getNolResourceString(NEWFORMULALABEL);
//			formulaStrings[0] = "Insert before selected item";
			for(int i=1;i<=formulas.size();i++){
				formulaStrings[i] = formulas.elementAt(i-1).toString();
			}
		}
		@Override
		public Component getListCellRendererComponent(
            JList list, 
            Object value, 
            int index, 
            boolean isSelected, 
            boolean cellHasFocus) 
        {
			int i = ((Integer)value).intValue();
		    if(listBox.isSelectedIndex(index)) {
				setText(formulaStrings[i]);
				setBackground(highlightColor);
				setForeground(Color.white);
			} else {
				setText(formulaStrings[i]);
				setBackground(Color.white);
				setForeground(Color.black);
			}
			return this;
		}
    }

    class FormulaConstructor extends JDialog {
		protected JTextField outputField;
		protected volatile JTextField inputField;
		protected Font fieldFont;
		protected NolList varListChoice;
		protected DefaultListModel varListChoiceModel;
		protected NolList formulaListChoice;
		protected DefaultListModel formulaListChoiceModel;
		protected FontMetrics inputFieldFontMetrics;
		protected FontMetrics outputFieldFontMetrics;
		protected boolean findClick;
		private Action constActionListener;
		private JButton addArgButt;
		private JButton deleteArgButt;
		private JButton undoButt;
		private JButton redoButt;
		private JTextArea helpText;
		private JScrollBar inputFieldScrollbar;
		private FormulaListKeyAdapter keyListener;
		private FormulaListMouseAdapter mouseListener;
		/*** part of EditState ***/
/***/	private volatile int	selectStart;
/***/	private volatile int	selectEnd;
/***/	private int editedOutputIndex;
/***/	private Vector editedInputIndex;
/***/	private String numberInput;
/***/	private boolean inputFieldHasFocus;
		/*** undo/redo fields ***/
		private Vector formulaUndo;
		private Vector editStateUndo;
		private int undoBufferLength;
		private int undoPointer;
		private int redoCount;
		private boolean undoLock;

		FormulaConstructor(JFrame frame) {
			super(frame);
			setTitle("Define Formula");
			setResizable(false);
			constActionListener = new ConstControlAction();
			formulaUndo = new Vector(0,undoBufferLength+10);
			editStateUndo = new Vector(0,undoBufferLength+10);
			redoCount = 0;
			undoBufferLength = 40;
			undoLock = false;
			initLayout();
		}

		private void initLayout(){
			JPanel workPane = new JPanel();
			workPane.setLayout(null);
			JLabel label1 = new JLabel(frame.getNolResourceString(OUTPUTS)+":");
			label1.setBounds(X0, Y0, W0, H0);
			workPane.add(label1);
			fieldFont = new Font("dialog", 0, 12);
			JLabel label2 = new JLabel(frame.getNolResourceString(FORMULA)+":");
			label2.setBounds(X0, Y1, W0, H0);
			workPane.add(label2);
			newVarBut = new JButton(frame.getNolResourceString(NEW));
			newVarBut.setActionCommand("New...");
			newVarBut.addActionListener(constActionListener);
			newVarBut.setBounds(X0 + 80, Y3, W3, H1);
			workPane.add(newVarBut);
			JButton okBut = new JButton(frame.getNolResourceString(OK));
			okBut.setActionCommand("OK");
			okBut.addActionListener(constActionListener);
			okBut.setBounds(X4, Y0, W3, H0); 
			workPane.add(okBut);
			JButton cancelBut = new JButton(frame.getNolResourceString(CANCEL));
			cancelBut.setActionCommand("Cancel");
			cancelBut.addActionListener(constActionListener);
			cancelBut.setBounds(X4, Y1, W3, H0); 
			workPane.add(cancelBut);
			JPanel pane = new JPanel(new GridLayout());
			pane.setBounds(X0, Y3, W2, H3);
			pane.setBorder(new TitledBorder(new EmptyBorder(1, 1, 1, 1),               
				frame.getNolResourceString(VARIABLES)+":", TitledBorder.LEFT , TitledBorder.TOP));
			varListChoice = new NolList(getVarListChoiceModel());
			varListChoice.addListSelectionListener((ListSelectionListener)constActionListener);
//			varListChoice.setBackground(Color.white);
			varListChoice.setSelectionBackground(Color.lightGray);
			varListChoice.setSelectionForeground(Color.black);
			varListChoice.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
			JScrollPane listScrollPane = new JScrollPane(varListChoice);
			listScrollPane.setBorder(BorderFactory.createLoweredBevelBorder());
			pane.add(listScrollPane);
			workPane.add(pane);
			pane = new JPanel(new GridLayout());
			pane.setBounds(X2, Y3, W2, H3);
			pane.setBorder(new TitledBorder(new EmptyBorder(1, 1, 1, 1),               
				frame.getNolResourceString(FUNCTIONS)+":", TitledBorder.LEFT , TitledBorder.TOP));
			formulaListChoice = new NolList(getFormulaListChoiceModel());
//			formulaListChoice.setBackground(Color.white);
			formulaListChoice.setSelectionBackground(Color.lightGray);
			formulaListChoice.setSelectionForeground(Color.black);
			formulaListChoice.addListSelectionListener((ListSelectionListener)constActionListener);
			formulaListChoice.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
			listScrollPane = new JScrollPane(formulaListChoice);
			listScrollPane.setBorder(BorderFactory.createLoweredBevelBorder());
			pane.add(listScrollPane);
			workPane.add(pane);
			
			inputField = getInputField();
			inputField.setPreferredSize(new Dimension(INPUT_FIELD_WIDTH,H0));
//			inputField.setPreferredScrollableViewportSize(new Dimension(W1,H2));
			JScrollPane scrollpane = new JScrollPane(inputField, ScrollPaneConstants.VERTICAL_SCROLLBAR_NEVER, ScrollPaneConstants.HORIZONTAL_SCROLLBAR_ALWAYS );
			scrollpane.setBorder(BorderFactory.createLoweredBevelBorder());
			scrollpane.setBounds(X1,Y1,W1,H2); 
			workPane.add(scrollpane);
			
			synchronized (this) {
				inputFieldScrollbar = scrollpane.getHorizontalScrollBar();
			}
			
			workPane.add(getOutputField());
			pane = new JPanel(new GridLayout(4,4,5,5));
			pane.setBounds(X3, Y3, W2, H3);
			pane.setBorder(BorderFactory.createTitledBorder(frame.getNolResourceString(NUMERICALINPUTS)));
			JButton but = new JButton("1");
			but.setMargin(new Insets(0,0,0,0));
			but.addActionListener(constActionListener);
			pane.add(but);
			but = new JButton("2"); 
			but.setMargin(new Insets(0,0,0,0));
			but.addActionListener(constActionListener);
			pane.add(but);
			but = new JButton("3"); 
			but.setMargin(new Insets(0,0,0,0));
			but.addActionListener(constActionListener);
			pane.add(but);
			but = new JButton("pi"); 
			but.setMargin(new Insets(0,0,0,0));
			but.addActionListener(constActionListener);
			pane.add(but);
			but = new JButton("4"); 
			but.setMargin(new Insets(0,0,0,0));
			but.addActionListener(constActionListener);
			pane.add(but);
			but = new JButton("5"); 
			but.setMargin(new Insets(0,0,0,0));
			but.addActionListener(constActionListener);
			pane.add(but);
			but = new JButton("6"); 
			but.setMargin(new Insets(0,0,0,0));
			but.addActionListener(constActionListener);
			pane.add(but);
			but = new JButton("+/-"); 
			but.setMargin(new Insets(0,0,0,0));
			but.addActionListener(constActionListener);
			pane.add(but);
			but = new JButton("7"); 
			but.setMargin(new Insets(0,0,0,0));
			but.addActionListener(constActionListener);
			pane.add(but);
			but = new JButton("8"); 
			but.setMargin(new Insets(0,0,0,0));
			but.addActionListener(constActionListener);
			pane.add(but);
			but = new JButton("9"); 
			but.setMargin(new Insets(0,0,0,0));
			but.addActionListener(constActionListener);
			pane.add(but);
			but = new JButton("del"); 
			but.setMargin(new Insets(0,0,0,0));
			but.addActionListener(constActionListener);
			pane.add(but);
			but = new JButton("0"); 
			but.setMargin(new Insets(0,0,0,0));
			but.addActionListener(constActionListener);
			pane.add(but);
			but = new JButton("."); 
			but.setMargin(new Insets(0,0,0,0));
			but.addActionListener(constActionListener);
			pane.add(but);
			but = new JButton("E"); 
			but.setMargin(new Insets(0,0,0,0));
			but.addActionListener(constActionListener);
			pane.add(but);
			workPane.add(pane);
			pane = new JPanel(new GridLayout(1,4,5,0));
			pane.setBounds(X1, Y2, W4, H1); 
			URL url = this.getClass().getResource("transformLeft.gif");
			but = new JButton(new ImageIcon(url));
			but.setActionCommand("formulaLeft");
			but.addActionListener(constActionListener); 
			pane.add(but);
			url = this.getClass().getResource("transformRight.gif");
			but = new JButton(new ImageIcon(url));
			but.setActionCommand("formulaRight");
			but.addActionListener(constActionListener);
			pane.add(but);
			url = this.getClass().getResource("transformUp.gif");
			but = new JButton(new ImageIcon(url));
			but.setActionCommand("formulaUp");
			but.addActionListener(constActionListener);
			pane.add(but);
			url = this.getClass().getResource("transformDown.gif");
			but = new JButton(new ImageIcon(url));
			but.setActionCommand("formulaDown");
			but.addActionListener(constActionListener);
			pane.add(but);
			workPane.add(pane);

			pane = new JPanel(new GridLayout(1,4,5,0));
			pane.setBounds(X6, Y2,(X4-WGAP)-X6, H1); 

			undoButt = new JButton(frame.getNolResourceString(UNDO)); 
			undoButt.setActionCommand("Undo");
			undoButt.addActionListener(constActionListener);
			pane.add(undoButt);

			redoButt = new JButton(frame.getNolResourceString(REDO)); 
			redoButt.setActionCommand("Redo");
			redoButt.addActionListener(constActionListener);
			pane.add(redoButt);

			addArgButt = new JButton(frame.getNolResourceString(ADDARG)); 
			addArgButt.setActionCommand("Add Arg");
			addArgButt.addActionListener(constActionListener);
			pane.add(addArgButt);

			deleteArgButt = new JButton(frame.getNolResourceString(DELARG)); 
			deleteArgButt.setActionCommand("Del Arg");
			deleteArgButt.addActionListener(constActionListener);
			pane.add(deleteArgButt);
			workPane.add(pane);
			helpText = new JTextArea();
			helpText.setBounds(X0,Y4,W0+W1+WGAP+W3,H4);  // width goes all the way across 
			helpText.setLineWrap(true);
			helpText.setWrapStyleWord(true);
			helpText.setEditable(false);
			helpText.setFont(fieldFont);
			helpText.setBackground(workPane.getBackground());
			helpText.setDisabledTextColor(Color.black);
			helpText.setEnabled(false);
			workPane.add(helpText);
			setContentPane(workPane);
		}

		private DefaultListModel getVarListChoiceModel() {
			if (varListChoiceModel == null) {
				varListChoiceModel = new DefaultListModel();
			}
			return varListChoiceModel;
		}

		private DefaultListModel getFormulaListChoiceModel() {
			if (formulaListChoiceModel == null) {
				formulaListChoiceModel = new DefaultListModel();
			}
			return formulaListChoiceModel;
		}

		private JTextField getOutputField() {
			if (outputField == null) {
				outputField = new JTextField("test");
				outputField.setFont(fieldFont);
				outputField.setBackground(Color.white);
				outputField.setBounds(X1, Y0, W1, 25);
				outputField.setEditable(true);
				outputField.setEnabled(true);
				outputField.addMouseListener(getMouseListener());
				outputField.addKeyListener(getKeyListener());
				outputField.setOpaque(true);
				outputField.setSelectionColor(Color.lightGray);
				outputField.selectAll();
			}
			return outputField;
		}

		private JTextField getInputField() {
			if (inputField == null) {
/*				InputDocument inputDoc = new InputDocument();
				String str = "";
				int cols = 300;
				inputField = new JTextField(inputDoc,str,cols);
*/
				inputField = new JTextField();
				inputField.setFont(fieldFont);
				inputField.setBackground(Color.white);
				inputField.setEditable(false);
				inputField.setOpaque(true);
				inputField.setEnabled(true);
				inputField.addMouseListener(getMouseListener());
				inputField.addKeyListener(getKeyListener());
				inputField.setSelectionColor(Color.lightGray);

			}
			return inputField;
		}

		private FormulaListMouseAdapter getMouseListener() {
			if (mouseListener == null) {
				mouseListener = new FormulaListMouseAdapter();
			}
			return mouseListener;
		}

		private FormulaListKeyAdapter getKeyListener() {
			if ( keyListener == null) {
				keyListener = new FormulaListKeyAdapter();
			}
			return keyListener;
		}

		private FontMetrics getInputFieldFontMetrics() {
			if (inputFieldFontMetrics == null) {
				inputFieldFontMetrics = getInputField().getFontMetrics(fieldFont);
			}
			return inputFieldFontMetrics;
		}
		private FontMetrics getOutputFieldFontMetrics() {
			if (outputFieldFontMetrics == null) {
				outputFieldFontMetrics = outputField.getFontMetrics(fieldFont);
			}
			return outputFieldFontMetrics;
		}

		protected void initializeEditContext() {
			editedOutputIndex = 0;
			selectStart = 0;
			selectEnd = 0;
			numberInput = new String();
			inputFieldHasFocus = false;
			if(editedInputIndex==null) {
				editedInputIndex = new Vector();
			}else {
				editedInputIndex.removeAllElements();
			}
			if(currentFormula==null) {
				currentFormula = new Formula2();
			}
			displayVarListChoice();
			if(currentFormula.getOutputs().isEmpty()) {
				currentFormula.addOutput("???");
			}
			setText(inputField,new String(""));  // necessary so undo/redo always catches "???" as first state
			setText(outputField,new String(""));
			clearUndoRedo(); 
			showInputField();
			showOutputField();
			manageControls();
		}

		@Override
		public void setVisible(boolean visible){
			super.setVisible(visible);
			manageLists();
		}

/** Display the output field of the formula constructor.*/
		public void showOutputField(){
			String s ="";
			int startHighLight  = 0;
			int endHighLight  = 0;
			Vector editedOutputs = currentFormula.getOutputs();
			for(int i=0;i<editedOutputs.size();i++){
				if(editedOutputIndex == i){
					startHighLight = s.length();
					s = s+editedOutputs.elementAt(i).toString();
					endHighLight = s.length();
				}else{
					s = s+editedOutputs.elementAt(i).toString();
				}
				if(i<editedOutputs.size()-1) {
					s = s+", ";
				}
			}
			setText(outputField, s);
			if(!inputFieldHasFocus){
				outputField.select(startHighLight,endHighLight);
				inputField.select(0,0);
			}else{
				outputField.select(0,0);
			}
			setFocus();
		}

/** Display the input field */
		public synchronized void showInputField() {
			String m = currentFormula.getName();
			if(m.equals("")) {
				setText(inputField,new String("???"));
				if(inputFieldHasFocus){
					getInputField().selectAll();
					outputField.select(0,0);
					inputFieldScrollbar.setValue(0);
				}else{
					inputField.select(0,0);
				}
				setDescription();
				setFocus();
				setListEnabled(varListChoice,false); // special case, no input yet, must be function
				return;
			}
			String s = m+"(";
			Vector editedInputs = currentFormula.getInputs();
			if(editedInputIndex.isEmpty()) {
				for(int i=0;i<editedInputs.size();i++){
					s = s+editedInputs.elementAt(i).toString();
					if(i<editedInputs.size()-1) {
						s = s+", ";
					}
				}
				s = s+")";
				setText(inputField,s);
				if(inputFieldHasFocus){
					inputField.selectAll();
					outputField.select(0,0);
					inputFieldScrollbar.setValue(0);
				}else{
					inputField.select(0,0);
				}
				setDescription();
				setFocus();
				setListEnabled(varListChoice,false);
				return;
			}
			selectStart = 0;
			selectEnd = 0;
			Object editedObj = currentFormula.getInput(editedInputIndex);
			for(int i=0;i<editedInputs.size();i++){
				Object inputObj = editedInputs.elementAt(i);
				//System.out.println("edited inputs "+i+" = "+inputObj.toString());
 				if(selectEnd !=0 || selectStart !=0){
					s = s+inputObj.toString();
				}else { 
					if(editedObj.equals(inputObj)){
						selectStart = s.length();
						s = s+inputObj.toString();
						selectEnd = s.length();
					}else if(inputObj instanceof InnerFormula2){
						s = findSelectString(s,(InnerFormula2)inputObj);
						//System.out.println("findSelectString returned s = "+s);
					}else{
						s = s+inputObj.toString();
					}
				}
 				
				if(i<editedInputs.size()-1) 
					s = s+", ";
			}
			s = s+")";
					// System.out.println("s="+s+ "  selectStart="+selectStart+"  selectEnd="+selectEnd );
			setText(inputField,s);
			if(inputFieldHasFocus){
				inputField.select(selectStart,selectEnd);
				// Figure out best place for scrollbar
				int currentStart = inputFieldScrollbar.getValue();
				int currentEnd = currentStart + inputFieldScrollbar.getVisibleAmount();
				int editStartPixel = getInputFieldFontMetrics().stringWidth(s.substring(0,selectStart));
				int editEndPixel = getInputFieldFontMetrics().stringWidth(s.substring(0,selectEnd));
					//System.out.println("curr start = "+currentStart+" curr end = "+currentEnd+" vis = "+inputFieldScrollbar.getVisibleAmount());
					//System.out.println("in chars, selection starts at "+selectStart+" ends at "+selectEnd);
					//System.out.println("in pixels, selection starts at "+editStartPixel+" ends at "+editEndPixel);
				if(!(currentStart > editEndPixel) && (currentEnd < editStartPixel || (editEndPixel > currentEnd && editStartPixel > currentStart))) 
					inputFieldScrollbar.setValue(editEndPixel - inputFieldScrollbar.getVisibleAmount());
				else if(currentStart > editEndPixel || (editStartPixel < currentStart && editEndPixel < currentEnd)) 
					inputFieldScrollbar.setValue(editStartPixel);
				
				outputField.select(0,0);
			}else{
				inputField.select(0,0);
			}
			setDescription();
			setFocus();
			setListEnabled(varListChoice,true);
		}

		private void setFocus() {
			if(inputFieldHasFocus) {
				inputField.requestFocus();
			}else {
				outputField.requestFocus();
				setListEnabled(varListChoice,true);
			}
		}

		private void setListEnabled(JList list, boolean enabled) {
			if(enabled) {
				list.setEnabled(true);
				list.setBackground(Color.white);
				list.repaint();
			} else {
				list.setEnabled(false);
				list.setBackground(Color.lightGray);
				list.repaint();
			}
		}


/** Convert the inner formula to string and find the selected substring at same time.*/
		private  String findSelectString(final String str, final InnerFormula2 trans) {
			String m = trans.getName();
			String formulaString = str + m + "(";
			Vector editedInputs = trans.getInputs();
			Object editedObj = currentFormula.getInput(editedInputIndex);
			for(int i=0;i<editedInputs.size();i++){
				Object inputObj = editedInputs.elementAt(i);
 				if(selectEnd !=0 || selectStart !=0){
					formulaString = formulaString+inputObj.toString();	
				}else{
					if (editedObj.equals(inputObj)){
						selectStart = formulaString.length();
						formulaString = formulaString+inputObj.toString();
						selectEnd = formulaString.length();
					}else if(inputObj instanceof InnerFormula2){
						formulaString = findSelectString(formulaString,(InnerFormula2)inputObj);
					}else {
						formulaString = formulaString+inputObj.toString();
					}
				}

				if(i<editedInputs.size()-1) 
					formulaString = formulaString+", ";
			}
			formulaString = formulaString+")";
			return formulaString;
		}

/** Convert the inner Formula to string and find the selected substring at same time.*/
		private  String findSelectObj(final String str, final int level, final int x) {
			editedInputIndex.addElement(level);
			Formula2 formula = (Formula2) currentFormula.getInput(editedInputIndex);
			String m = formula.getName();
			String formulaString = str + m + "(";
			int sw = getInputFieldFontMetrics().stringWidth(formulaString);
			int realX = x + inputField.getScrollOffset();
			if(sw+4 > realX){
				findClick = true;
				return formulaString;
			}
			Vector editedInputs = formula.getInputs();
			for(int i=0;i<editedInputs.size();i++){
				Object inputObj = editedInputs.elementAt(i);
				if(inputObj instanceof InnerFormula2){
					formulaString = findSelectObj(formulaString,i,x);
					if(findClick) {
						return formulaString;
					}
				}else{
					formulaString = formulaString+inputObj.toString();
					sw = getInputFieldFontMetrics().stringWidth(formulaString);
					if(sw+4 > realX){
						editedInputIndex.addElement(i);
						findClick = true;
						return formulaString;
					}
				}
				if(i<editedInputs.size()-1) {
					formulaString = formulaString+", ";
				}
			}
			formulaString = formulaString+")";
			sw = getInputFieldFontMetrics().stringWidth(formulaString);
			if(sw+4 > realX){
				findClick = true;
				return formulaString;
			}
			editedInputIndex.removeElementAt(editedInputIndex.size()-1);  // popping up, remove last element
			return formulaString;
		}

/** The display the formula choice.*/
		private void displayFormulaChoice(){
			getFormulaListChoiceModel().removeAllElements();
			boolean hasTimeStamps = ((Preprocessor)dataSource).getHasTimeStamps();
			// can potentially speed this up by passing vector to the NolList
			if(hasTimeStamps) {
				int c = FormulaMap.timeFunctions.length;
				for(int i=0;i<c;i++){
					getFormulaListChoiceModel().addElement(FormulaMap.timeFunctions[i]);
				}
			} else {
				int c = FormulaMap.rowFunctions.length;
				for(int i=0;i<c;i++) {
					getFormulaListChoiceModel().addElement(FormulaMap.rowFunctions[i]);
				}
			}
			Project p = frame.getProject();
			Vector models1 = p.getPredictiveModels();
			Vector models2 = p.getOptimizationModels();
			for(int i=0;i<models1.size();i++){
				NolModel2 model = (NolModel2)models1.elementAt(i);
				if(hasTimeStamps == model.getHasTimeStamps()){
					getFormulaListChoiceModel().addElement(model.getName());
				}
			}
			for(int i=0;i<models2.size();i++){
				NolModel2 model = (NolModel2)models2.elementAt(i);
				if(hasTimeStamps == model.getHasTimeStamps()){
					getFormulaListChoiceModel().addElement(model.getName());
				}
			}
		}

/** The display the formula choice.*/
		private void displayVarListChoice(){
			// MK 2/23/99 include all variables since formulas can cut across data series
			getVarListChoiceModel().removeAllElements();
			Preprocessor prep = getPreprocessor();
			Vector varNames = prep.getVariableNames();
			varListChoice.addElements(prep.getOriginalVarNames(varNames));
			varListChoice.addElements(prep.getDerivedVariableNames());
		}

		
		// UNDO/REDO STUFF
		private void setText(JTextField field, String newText) {
			// store the edit state in the undo buffer
			String currentText = field.getText();
			if(newText.equals(currentText)) {
				return;  // make sure setting the same text twice does screw up the undo facility
			}
			// shrink if possible, but always allow the required number of undos
			while(undoPointer>undoBufferLength) {
				formulaUndo.removeElementAt(0);
				editStateUndo.removeElementAt(0);
				undoPointer--;	
			}
			// add current instance, text and selection to Undo
			//System.out.println("Adding to undo buffer "+newText);
			formulaUndo.addElement(new Formula2(currentFormula));
			editStateUndo.addElement(new EditState());
			// normally move pointer to end of undo buffer and reset the redo count
			if(!undoLock) {
				undoPointer = formulaUndo.size()-1; 
				redoCount = 0;
			}
//System.out.println("aactually set texxt = "+newText);
			field.setText(newText);
			if(canUndo()) {
				undoButt.setEnabled(true);
			}
			//System.out.println("After set state, Undo pointer is at "+undoPointer+" redo count = "+redoCount+" buffer length = "+(formulaUndo.size()-1));
		}

		private void undo() {
			//System.out.println("Got undo request, can do it = "+canUndo());
			if(!canUndo()) {
				Toolkit.getDefaultToolkit().beep();
				return;
			}
			undoPointer--;
			redoCount++;
			// keep the pointers for further undo or redos
			undoLock = true;
			restoreEditState();
			undoLock = false;
			manageControls();
			//System.out.println("After undo, Undo pointer is at "+undoPointer+" redo count = "+redoCount+" buffer length = "+(formulaUndo.size()-1));
		}

		private void redo() {
			//System.out.println("Got redo request, can do it = "+canRedo());
			if(!canRedo()) {
				Toolkit.getDefaultToolkit().beep();
				return;
			}
			undoPointer++;
			redoCount--;
			undoLock = true;
			restoreEditState();
			undoLock = false;
			manageControls();
			//System.out.println("After redo, Undo pointer is at "+undoPointer+" redo count = "+redoCount+" buffer length = "+(formulaUndo.size()-1));
		}

		// sets the edit state
		private void restoreEditState() {
			//System.out.println("Restoring to state "+undoPointer);
			Formula2 formula = (Formula2) formulaUndo.elementAt(undoPointer);
			EditState state = (EditState) editStateUndo.elementAt(undoPointer);
			currentFormula = new Formula2(formula);  // copy the formula in the undo buffer
			state.restoreState();
			showInputField();
			showOutputField();
		}

		// Used for determining button states
		private boolean canUndo() {
			if(undoPointer>1) {
				return true; // always keep 2 states in the undo buffer (1 for each text field - at least initially)
			}else{
				return false;
			}
		}

		private boolean canRedo() {
			if(redoCount>0){
				return true;
			}else{
				return false;
			}
		}

		// This must be called when unmanaging formula constructor dialog
		private void clearUndoRedo() {
			formulaUndo.removeAllElements();
			editStateUndo.removeAllElements();
			undoPointer = -1;
			redoCount = 0;
			undoLock = false;
		}

		class EditState {
			private int	xselectStart;
			private int	xselectEnd;
			private int xeditedOutputIndex;
			private Vector xeditedInputIndex;
			private String xnumberInput;
			private boolean xinputFieldHasFocus;
			EditState() {
				xselectStart = selectStart;
				xselectEnd = selectEnd;
				xeditedOutputIndex = editedOutputIndex;
				xeditedInputIndex = (Vector) editedInputIndex.clone();
				xnumberInput = numberInput;
				xinputFieldHasFocus = inputFieldHasFocus;
			}
			private void restoreState() {
				selectStart = xselectStart;
				selectEnd = xselectEnd;
				editedOutputIndex = xeditedOutputIndex;
				editedInputIndex = xeditedInputIndex;
				numberInput = xnumberInput;
				inputFieldHasFocus = xinputFieldHasFocus;
			}
		}


/** The inner control listener class.*/
		class ConstControlAction extends AbstractAction implements ListSelectionListener{
			ConstControlAction() {super("");}
			@Override
			public void actionPerformed(ActionEvent e) {
				String command = e.getActionCommand();
				
				boolean isCommandDigit = "1".equals(command) || "2".equals(command) || "3".equals(command);
				isCommandDigit = isCommandDigit || "4".equals(command) || "5".equals(command) || "6".equals(command);
				isCommandDigit = isCommandDigit || "7".equals(command) || "8".equals(command) || "9".equals(command);
				isCommandDigit = isCommandDigit || "0".equals(command) || ".".equals(command);
				
				if(command.equals("New...")){
					addVarAction();
				}else if(command.equals("Add Arg")){
					addArgument();
				}else if(command.equals("Del Arg")){
					deleteArgument();
				}else if(command.equals("formulaDown")){
					argumentDown();
				}else if(command.equals("formulaLeft")){
					argumentLeft();
				}else if(command.equals("formulaRight")){
					argumentRight();
				}else if(command.equals("formulaUp")){
					argumentUp();
				}else if(command.equals("Undo")){
					undo();
				}else if(command.equals("Redo")){
					redo();
				}else if(isCommandDigit){
					addNumberInputAction(command);
				}else if(command.equals("E")||command.equals("e")){
					addNumberInputAction("E+0");
				}else if(command.equals("pi")){
					addNumberPiAction();
				}else if(command.equals("del")){
					backspaceAction();
				}else if(command.equals("+/-")){
					addNumberSignAction();
				}else if(command.equals("OK")){
					constOkAction();
				}else if(command.equals("Cancel")){
					constCancelAction();
				} 
			}

			@Override
			public void valueChanged(ListSelectionEvent e) {
				if(noFire) {
					return;
				}
				try {
					if (e.getSource().equals(varListChoice)) {
						if(varListChoice.getValueIsAdjusting()) {
							return;  // very important! or we get spurious events, and undo/redo doesn't work correctly!
						}
						varListChoice.transferFocus();
						formulaListChoice.transferFocus();
						selectVarListChoice();
					} else if (e.getSource().equals(formulaListChoice)) {
						if(formulaListChoice.getValueIsAdjusting()) {
							return;  // very important! or we get spurious events, and undo/redo doesn't work correctly!
						}
						formulaListChoice.transferFocus();
						selectFormulaListChoice();
						clearNumberInput();
					}
				} catch (Exception ex) {
					System.err.println("Exception: " + ex.getMessage());
					ex.printStackTrace();
				}
			}

		}

		private void manageControls() {
			manageAddDeleteButtons();
			manageUndoRedoButtons();
			manageLists();
		}

		private void manageLists() {
			if(!inputFieldHasFocus){
				newVarBut.setEnabled(true);
				setListEnabled(formulaListChoice,false);
				setListEnabled(varListChoice,true);
			}else{
				if(inputField.getText().equals("???")) {
					setListEnabled(varListChoice,false);
				}else {
					setListEnabled(varListChoice,true);
				}
				newVarBut.setEnabled(false);
				setListEnabled(formulaListChoice,true);
			}

		}

		private void manageUndoRedoButtons() {
			// manage undo/redo buttons
			if(canUndo()) {
				undoButt.setEnabled(true);
			}else {
				undoButt.setEnabled(false);
			}
			if(canRedo()) {
				redoButt.setEnabled(true);
			}else {
				redoButt.setEnabled(false);
			}
		}

		private void manageAddDeleteButtons() {
			// manage add arg and del arg buttons
			if(!inputFieldHasFocus) {
				addArgButt.setEnabled(true);
				if(currentFormula.getOutputs().size()>1) {
					deleteArgButt.setEnabled(true);
				}else {
					deleteArgButt.setEnabled(false);
				}
				return;
			}
			if(editedInputIndex.isEmpty()) {
				addArgButt.setEnabled(false);
				deleteArgButt.setEnabled(false);
				return;
			}
			// must be at level below a function (i.e. in the function's arguments) to add or delete
			int index = editedInputIndex.size() - 1;
			Formula2 formula = (Formula2) currentFormula.getInput(editedInputIndex,index);
			FunctionInterface func = formula.getFunction();
			if(func==null) {
				addArgButt.setEnabled(false);
				deleteArgButt.setEnabled(false);
				return;	
			}
			int size = formula.getInputs().size();
			int maxIn = func.getMaximumInputs();
			int minIn = func.getMinimumInputs();
			if(maxIn > size) {
				addArgButt.setEnabled(true);
			}else {
				addArgButt.setEnabled(false);
			}
			if(minIn < size) {
				deleteArgButt.setEnabled(true);
			}else {
				deleteArgButt.setEnabled(false);
			}
		}


	/**OK.action.*/
		private void constOkAction() {
			boolean isValid = true;
			if(noFire) {
				return;
			}
			noFire = true;
			if(currentFormula.getOutputs().contains("???")) {
				noFire = false;
				isValid = false;
			}
			if(inputField.getText().indexOf("???") != -1) {
				noFire = false;
				isValid = false;
			}
			if(!isValid) {
				frame.showOKDialog("This formula is incomplete");
				noFire = false;
				return;
			}
			if(funcMode == 3){
				isValid = addFormula(currentFormula);
			}else if(funcMode == 1){
				isValid = modifyFormula(currentFormula);
			}
			// leave formula constructor only if formula was valid
			// otherwise, stick around for more tries, or until the user cancels
			if(isValid) {
				setVisible(false);
				clearUndoRedo();
				funcMode = 0;
			}
			noFire = false;
		}

		private void constCancelAction() {
			if(noFire) {
				return;
			}
			setVisible(false);
			clearUndoRedo();
			funcMode = 0;
		}

		private void addNumberInputAction(String command) {
			if(noFire) {
				return;
			}
			if(!inputFieldHasFocus) {
				return;
			}
			appendNumberInput(command);
		}

		private void addNumberPiAction() {
			if(noFire) {
				return;
			}
			if(!inputFieldHasFocus) {
				return;
			}
			String str = new String("3.14159265359");
			setNumberInput(str);
		}

		private void backspaceAction() {
			if(noFire) {
				return;
			}
			if(inputFieldHasFocus) {
				if(numberInput.length()<=1) {
					Object obj = currentFormula.getInput(editedInputIndex);
					if(obj instanceof String && ((String) obj).equals("???")) {
						if(deleteArgButt.isEnabled()) {
							deleteArgument();
						}
					} else if (!editedInputIndex.isEmpty()) {
						modifyCurrentFormula(new String("???"));
						clearNumberInput();
					} else clearInputField();
				}else if((numberInput.length()==2) &&(numberInput.substring(0,1).equals("-"))){
					modifyCurrentFormula(new String("???"));
					clearNumberInput();
				} else {  // 
					String str = "";
					int Ed = numberInput.indexOf("E");
					if(Ed==-1){
						str = numberInput.substring(0,numberInput.length()-1);
					} else {
						if(numberInput.substring(Ed).length() == 3) {
							str = numberInput.substring(0,Ed);
						}else {
							str = numberInput.substring(0,numberInput.length()-1);
						}
					}
					setNumberInput(str);
				}
				showInputField();
				manageControls();	
			} else {
				Vector editedOutputs = currentFormula.getOutputs();
				String s = (String) editedOutputs.elementAt(editedOutputIndex);
				if(s.equals("???") && editedOutputs.size() > 1) {
					// remove the output
					editedOutputs.removeElementAt(editedOutputIndex);
					editedOutputIndex--;
					if(editedOutputIndex<0) {
						editedOutputIndex=0;
					}
				} else {
					editedOutputs.setElementAt(new String("???"),editedOutputIndex);
				}
				showOutputField();
			}

		}

		private void clearInputField() {
			currentFormula = new Formula2();
			editedInputIndex.removeAllElements();
			clearNumberInput();
			showInputField();
			manageControls();
		}

		private void addNumberSignAction() {
			if(noFire) {
				return;
			}
			if(!inputFieldHasFocus) {
				return;
			}
			if(numberInput.length()<1){
				numberInput="-";
				return;
			}else if((numberInput.length()==1)&&(numberInput.substring(0,1).equals("-"))){
				numberInput = "";
				return;
			}

			String str = "";
			int Ed = numberInput.indexOf("E");
			if(Ed==-1){
				if(numberInput.substring(0,1).equals("-")){
					str = numberInput.substring(1);
				}else{
					str = "-"+numberInput;
				}
			}else{
				if(numberInput.indexOf("+",Ed) == -1){
					str = numberInput.substring(0,Ed+1) + "+" + numberInput.substring(Ed+2);
				}else{
					str = numberInput.substring(0,Ed+1) + "-" + numberInput.substring(Ed+2);
				}
			}
			setNumberInput(str);
		}

	/** Appending number to the number input.*/
		private void appendNumberInput(String str){
			if(numberInput.endsWith("E+0")||numberInput.endsWith("E-0")
				||numberInput.endsWith("e+0")||numberInput.endsWith("e-0")) {
				setNumberInput(numberInput.substring(0,numberInput.length()-1) + str);
			} else setNumberInput(numberInput+str);
		}

		private void setNumberInput(String str) {
			if(editedInputIndex.isEmpty()) {
				return;
			}
			try {
				Double doubleInput = Double.valueOf(str);
				modifyCurrentFormula(doubleInput);
			} catch(NumberFormatException e) {
				Toolkit.getDefaultToolkit().beep();
				return;  // do nothing
			}
//System.out.println("setNumberInput str ="+ str);
			showInputField();
			numberInput = str;
		}

		/**ArgUp.action.*/
		private void argumentUp() {
			if(noFire) {
				return;
			}
			if(!inputFieldHasFocus) {
				return;
			}
			int vsize = editedInputIndex.size();
			if(vsize>0) {
				editedInputIndex.removeElementAt(vsize-1);
			}
			clearNumberInput();
			showInputField();
			manageControls();
		}

		/**ArgLeft.action.*/
		private void argumentLeft() {
			if(noFire) {
				return;
			}
			if(!inputFieldHasFocus && editedOutputIndex > 0){
				editedOutputIndex--;
				showOutputField();
				return;
			}
			if(inputFieldHasFocus) {
				int n = editedInputIndex.size();
				if(n==0) {
					return;
				}
				int argNum = ((Integer) editedInputIndex.lastElement()).intValue();
				if(argNum==0) {
					return;  // can't go further left
				}
				editedInputIndex.setElementAt(argNum-1, n-1);
				clearNumberInput();
				showInputField();
				manageControls();
			}
		}

		/**ArgRight action.*/
		private void argumentRight() {
			if(noFire) {
				return;
			}
			if(!inputFieldHasFocus){
				if(editedOutputIndex==currentFormula.getOutputs().size()-1){
					return;  // already at last arg
				}
				editedOutputIndex++;
				showOutputField();
				return;
			}
			if(inputFieldHasFocus) {
				int n = editedInputIndex.size();
				if(n==0){
					return;
				}
				int argNum = ((Integer) editedInputIndex.lastElement()).intValue();
				Formula2 formula = (Formula2) currentFormula.getInput(editedInputIndex,n-1);  // one level up
				if(argNum==formula.getInputs().size()-1){
					return;  // on last arg already
				}
				editedInputIndex.setElementAt(argNum+1, n-1);
				clearNumberInput();
				showInputField();
				manageControls();
			}
		}

		/**ArgDown.action.*/
		private void argumentDown() {
			if(noFire || !inputFieldHasFocus) {
				return;
			}
			Object inputObj = currentFormula.getInput(editedInputIndex);
			if(inputObj instanceof Formula2){
				Formula2 innerFormula = (Formula2) inputObj;
				if(!innerFormula.getInputs().isEmpty()) {
					editedInputIndex.addElement(0);
				} else return;
			} else return;
			clearNumberInput();
			showInputField();
			manageControls();
		} 

		/**Add Arg action.*/
		private void addArgument() {
			if(noFire) {
				return;
			}
			if(!inputFieldHasFocus){
				editedOutputIndex++;
				currentFormula.getOutputs().insertElementAt(new String("???"),editedOutputIndex); 
				showOutputField();
				manageControls();
			} else {
				if(editedInputIndex.isEmpty()) {
					return;
				}
				int level = editedInputIndex.size();
				Formula2 formula = (Formula2) currentFormula.getInput(editedInputIndex,level-1);
				int argNum = ((Integer) editedInputIndex.lastElement()).intValue();
				formula.getInputs().insertElementAt(new String("???"),argNum);
				editedInputIndex.setElementAt(argNum+1, level-1);
				clearNumberInput();
				showInputField();
				manageControls();
			}
		}

		private void deleteArgument() {
			if(noFire){
				return;  
			}
			if(!inputFieldHasFocus){
				if(editedOutputIndex != 0){
					currentFormula.getOutputs().removeElementAt(editedOutputIndex); 
					editedOutputIndex--;
				}else if(currentFormula.getOutputs().size()>1){
					currentFormula.getOutputs().removeElementAt(editedOutputIndex); 
				}else if(!currentFormula.getOutputs().elementAt(0).equals("???")){
					currentFormula.getOutputs().setElementAt(new String("???"),editedOutputIndex); 
				}
				showOutputField();
			}else{
				if(editedInputIndex.isEmpty()) {
					return; // can't delete top level arg
				}
				int level = editedInputIndex.size();
				Formula2 formula = (Formula2) currentFormula.getInput(editedInputIndex,level-1);
				int size = formula.getInputs().size();
				if(size==0) {
					return;  // no arguments to delete
				}
				int currentArg = ((Integer) editedInputIndex.lastElement()).intValue();
				formula.getInputs().removeElementAt(currentArg);
				currentArg--;
				if(currentArg<0) {
					editedInputIndex.removeElementAt(level-1); // no arguments left, pop up a level
				}else {
					editedInputIndex.setElementAt(currentArg, level-1);
				}
				clearNumberInput();
				showInputField();
				manageControls();
			}
		}

 		private void addVarAction() {
			if(noFire) {
				return;
			}
			NolTextInput newVar = new NolTextInput(frame, "New Derived Variable","Variable Name:");
			newVar.setBounds(200,200,195,145);
			newVar.setVisible(true);
			newVar.setFocus();
			String s = newVar.getText();
			if(newVar.getResult()) {
				newVar.dispose();		
			}else {
				newVar.dispose();
				return;
			}
			if(getVarListChoiceModel().contains(s)) {
				frame.showOKDialog("The name "+s+" is already in use");
				return;
			}else if((s.trim()).equals("")) {
				return;
			}
			noFire = true;
			currentFormula.getOutputs().setElementAt(s,editedOutputIndex);
			showOutputField();
			noFire = false;
		}

		private void selectFormulaListChoice() throws ClassNotFoundException, IllegalAccessException, InstantiationException  {
			if(noFire) {
				return;
			}
			if(!inputFieldHasFocus) {
				showOutputField();
				return;
			}
			String m = (String)formulaListChoice.getSelectedValue();
			if(m==null) {
				return;
			}
			Project p = frame.getProject();
			Object inputObj = currentFormula.getInput(editedInputIndex);
			int pindex = p.getPredictiveModelIndexByName(m);
			int oindex = p.getOptimizationModelIndexByName(m);
			if(currentFormula.equals(inputObj)){
				if(currentFormula.getName().equals(m)) {
					return;
				}
				if(pindex !=  -1){
					Vector models = p.getPredictiveModels();
					NolModel2 md = (NolModel2)models.elementAt(pindex);
					try{
						NolModel2 fm = (NolModel2)md.clone();
						currentFormula.setFunction(fm);
						showInputField();
						showOutputField();
					}catch(Exception evt){
						System.err.println("Non-Fatal exception: " + evt.getMessage());
						evt.printStackTrace();
					}
				}else if(oindex !=  -1){
					Vector models = p.getOptimizationModels();
					NolModel2 md = (NolModel2)models.elementAt(oindex);
					try{
						NolModel2 fm = (NolModel2)md.clone();
						currentFormula.setFunction(fm);
						showInputField();
						showOutputField();
					}catch(Exception evt){
						System.err.println("Non-Fatal exception: " + evt.getMessage());
						evt.printStackTrace();
					}
				}else{
					currentFormula.setFunction(m);
					FunctionInterface func = currentFormula.getFunction();
					currentFormula.getInputs().removeAllElements();
					int nin = func.getMinimumInputs();
					for(int j=0;j<nin;j++) {
						currentFormula.getInputs().addElement(new String("???"));
					}
					showInputField();
					manageControls();
				}
				clearNumberInput();
			}else if(pindex ==  -1 && oindex == -1){
				InnerFormula2 newformula = new InnerFormula2();
				newformula.setFunction(m);
				FunctionInterface func = newformula.getFunction();
				int nin = func.getMinimumInputs();
				// change following to use actual variable names!
				for(int j=0;j<nin;j++) {
					newformula.getInputs().addElement(new String("???"));
				}
				modifyCurrentFormula(newformula);
				showInputField();
				manageControls();
				clearNumberInput();
			}
		}

		private void selectVarListChoice() {
			Object obj = varListChoice.getSelectedValue();
			if(obj==null) {
				return;
			}
			if(inputFieldHasFocus){
				if(editedInputIndex.isEmpty()) {
					return;
				}
				modifyCurrentFormula(new String(obj.toString()));
				showInputField();
				clearNumberInput();
			} else {
				currentFormula.getOutputs().setElementAt(new String(obj.toString()), editedOutputIndex);
				showOutputField();
			}
		}

		private void setDescription() {
			Object selectedObj = currentFormula.getInput(editedInputIndex);
			if(selectedObj instanceof Formula2){
				Formula2 fm = (Formula2) selectedObj;
				FunctionInterface func = fm.getFunction();
				if(func!=null) {
					helpText.setText(func.getDescription());
				}
				else helpText.setText("");
			} else { // if we are focused on an argument, still show the description of the parent function
				int level = editedInputIndex.size();
				if(level==0) {
					helpText.setText("");
					return;
				}
				Formula2 fm = (Formula2) currentFormula.getInput(editedInputIndex,level-1);
				FunctionInterface func = fm.getFunction();
				if(func!=null){
					helpText.setText(func.getDescription());
				}else {
					helpText.setText("");
				}
			}
		}

		/** Modify Current Formula.  Replaces the argument at the position indicated by
		the editedInputIndex vector with newObj */
		private void modifyCurrentFormula(Object newObj){
			int level = editedInputIndex.size();
			Formula2 formula = (Formula2) currentFormula.getInput(editedInputIndex,level-1);
			Vector editedInputs = formula.getInputs();
			int arg = ((Integer) editedInputIndex.elementAt(level-1)).intValue();
			editedInputs.setElementAt(newObj,arg);
		}

		private void clearNumberInput() {
			if(!numberInput.equals("")) {
				numberInput = new String("");
			}
		}
	
/** The adapter class for capture the key input actions.*/	
		class FormulaListKeyAdapter extends KeyAdapter{	
			@Override
			public void keyTyped(KeyEvent e) {
				if(e.getSource().equals(inputField)){
//System.out.println(" FormulaListKeyAdapter String.valueOf(e.getKeyChar()) ="+String.valueOf(e.getKeyChar()));
					if(String.valueOf(e.getKeyChar()).equals("1")){
						addNumberInputAction("1");
					}else if(String.valueOf(e.getKeyChar()).equals("2")){
						addNumberInputAction("2");
					}else if(String.valueOf(e.getKeyChar()).equals("3")){
						addNumberInputAction("3");
					}else if(String.valueOf(e.getKeyChar()).equals("4")){
						addNumberInputAction("4");
					}else if(String.valueOf(e.getKeyChar()).equals("5")){
						addNumberInputAction("5");
					}else if(String.valueOf(e.getKeyChar()).equals("6")){
						addNumberInputAction("6");
					}else if(String.valueOf(e.getKeyChar()).equals("7")){
						addNumberInputAction("7");
					}else if(String.valueOf(e.getKeyChar()).equals("8")){
						addNumberInputAction("8");
					}else if(String.valueOf(e.getKeyChar()).equals("9")){
						addNumberInputAction("9");
					}else if(String.valueOf(e.getKeyChar()).equals("0")){
						addNumberInputAction("0");
					}else if(String.valueOf(e.getKeyChar()).equals("e") || String.valueOf(e.getKeyChar()).equals("E") ){
						addNumberInputAction("E+0");
					}else if(String.valueOf(e.getKeyChar()).equals(".")){
						addNumberInputAction(".");
					}	
				}else if(e.getKeyCode()==KeyEvent.VK_BACK_SPACE || e.getKeyCode()==KeyEvent.VK_DELETE){
					backspaceAction();
				}else if(e.getKeyCode() == KeyEvent.VK_UP ){
					argumentUp();
				}else if(e.getKeyCode() == KeyEvent.VK_LEFT ){
					argumentLeft();
				}else if(e.getKeyCode() == KeyEvent.VK_DOWN ){
					argumentDown();
				}else if(e.getKeyCode() == KeyEvent.VK_RIGHT ){
					argumentRight();
				}else if(e.getKeyCode() == KeyEvent.VK_INSERT ){
					if(addArgButt.isEnabled()){
						addArgument();
					}
				}
			}

	/**Method to handle events for the KeyListener interface.*/
			@Override
			public void keyPressed(KeyEvent e) {
				//System.out.println("in keyPressed e.getKeyCode()="+e.getKeyCode());
				if(e.getKeyCode() == KeyEvent.VK_BACK_SPACE || e.getKeyCode()==KeyEvent.VK_DELETE){
					backspaceAction();
				}else if(e.getKeyCode() == KeyEvent.VK_UP ){
					argumentUp();
				}else if(e.getKeyCode() == KeyEvent.VK_LEFT ){
					argumentLeft();
				}else if(e.getKeyCode() == KeyEvent.VK_DOWN ){
					argumentDown();
				}else if(e.getKeyCode() == KeyEvent.VK_RIGHT ){
					argumentRight();
				}else if(e.getKeyCode() == KeyEvent.VK_INSERT ){
					if(addArgButt.isEnabled()) {
						addArgument();
					}
				}
			}
		}
			
/** The adapter class for capture the formula list drag and drop actions.*/	
		class FormulaListMouseAdapter extends MouseAdapter{
 			@Override
			public void mouseClicked(MouseEvent e){
				if(e.getSource().equals(inputField)){
					inputFieldHasFocus = true;
					inputField.requestFocus();
					//newVarBut.setEnabled(false);
					//setListEnabled(formulaListChoice,true);
					//setListEnabled(varListChoice,true);
					String m=currentFormula.getName();
					if(m.equals("")){
						showInputField();
						setDescription();
						manageControls();
						clearNumberInput();
						return;
					}
					String s = m+"(";
					int sw = getInputFieldFontMetrics().stringWidth(s);
					int realX = e.getX() + inputField.getScrollOffset();
					if(sw+4 > realX){
						editedInputIndex.removeAllElements();
						showInputField();
						manageControls();
						clearNumberInput();
						return;
					}
 					Vector editedInputs = currentFormula.getInputs();
					editedInputIndex.removeAllElements();
					findClick = false;
					for(int i=0;i<editedInputs.size();i++){
						Object inputObj = editedInputs.elementAt(i);
						if(inputObj instanceof InnerFormula2){
							s = findSelectObj(s,i,e.getX());
							//System.out.println("Final string = "+s);
							//System.out.println("Final indices = "+editedInputIndex.toString());
							if(findClick){
								break;
							}
						}else{
							s = s+inputObj.toString();
							sw = getInputFieldFontMetrics().stringWidth(s);
							if(sw+4 > realX){
								editedInputIndex.addElement(i);
								//System.out.println("Final string = "+s);
								//System.out.println("Final indices = "+editedInputIndex.toString());
								break;
							}
						}
						if(i<editedInputs.size()-1) {
							s = s+", ";
						}
					}
					showInputField();
					manageControls();
					clearNumberInput();
				}else if(e.getSource().equals(outputField)){
					inputFieldHasFocus = false;
					inputField.transferFocus();  // goes to output field, due to ordering of components
					setDescription();
					String s ="";
					Vector editedOutputs = currentFormula.getOutputs();
					editedOutputIndex = editedOutputs.size()-1;
					int realX = e.getX() + outputField.getScrollOffset();
					for(int i=0;i<editedOutputs.size();i++){
						s = s+editedOutputs.elementAt(i).toString();
						int sw = getOutputFieldFontMetrics().stringWidth(s);
						if(sw+4 > realX){
							editedOutputIndex = i;
							break;
						}
						if(i<editedOutputs.size()-1) {
							s = s+", ";
						}
					}
					//newVarBut.setEnabled(true);
					//setListEnabled(formulaListChoice,false);
					//setListEnabled(varListChoice,true);
					manageControls();
					showOutputField();
				}
			}
		}
	}

	public class NolImportFormulaDialog  extends JDialog {
		private NolMainFrame frame = null;

		private NolSelectPanel importFormulaPanel;
		private JComboBox preprocessorChoice;
		private JButton fileImportBut;
		private ImportControlAction importActionListener;
		private Vector selectedFormulas;
		private Vector availableFormulas;
		private Vector availablePreprocessors;
		private boolean fromFileFlag; //false : from existing preprocessor; true: from a file.
		

		public NolImportFormulaDialog (NolMainFrame frame, Preprocessor p){
			super(frame, "Import formulas", true);
			this.frame = frame;
			selectedFormulas = new Vector();
			availableFormulas = new Vector();
			availablePreprocessors = new Vector();
			getContentPane().setLayout(new BorderLayout());
			importActionListener = new ImportControlAction();
			JPanel workPane = new JPanel(new BorderLayout());
			
			importFormulaPanel = new NolSelectPanel(frame.getNolResourceString(FORMULAS)+":");

			workPane.add("North",getSourcePanel());
			workPane.add("Center",importFormulaPanel);
			getContentPane().add("Center",workPane);
			getContentPane().add("East",getControlPanel());
			initList(p);
			fromFileFlag = false;
		}

		private JPanel getSourcePanel(){

			JPanel sourcePanel = new JPanel(new GridLayout(1,2,50,50));
			sourcePanel.setBackground(getContentPane().getBackground());
			sourcePanel.setBorder(BorderFactory.createTitledBorder(frame.getNolResourceString(SOURCE)+":"));

			JPanel pane1 = new JPanel(new GridLayout(1,2,5,5));
			JRadioButton radio = new JRadioButton(frame.getNolResourceString(FROMPREPROCESSOR)+":",true);
			radio.setActionCommand("From Preprocessor:");
			radio.addActionListener(importActionListener);
			ButtonGroup group = new ButtonGroup();
			group.add(radio);
			pane1.add(radio);

			preprocessorChoice = new JComboBox();
			preprocessorChoice.addActionListener(importActionListener);
			pane1.add(preprocessorChoice);

			JPanel pane2 = new JPanel(new GridLayout(1,2,5,5));
			radio = new JRadioButton(frame.getNolResourceString(FROMFILE)+":");
			radio.setActionCommand("From File:");
			radio.addActionListener(importActionListener);
			group.add(radio);
			pane2.add(radio);

			fileImportBut = new JButton(frame.getNolResourceString(FILE));
			fileImportBut.setActionCommand("File...");
			fileImportBut.addActionListener(importActionListener);
			fileImportBut.setEnabled(false);
			pane2.add(fileImportBut);
			sourcePanel.add(pane1);
			sourcePanel.add(pane2);
			return sourcePanel;
		}

		private JPanel getControlPanel(){
			JPanel control = new JPanel();
			control.setBackground(getContentPane().getBackground());
			control.setLayout(new BoxLayout(control, BoxLayout.Y_AXIS));
			control.setBorder(new TitledBorder(new EmptyBorder(1, 1, 1, 1),               
					"", TitledBorder.LEFT , TitledBorder.TOP));

			JPanel pane0 = new JPanel(new GridLayout(2,1,5,5));
			JButton okButton = new JButton(frame.getNolResourceString(OK));
			okButton.setActionCommand("OK");
			JButton cancelButton = new JButton(frame.getNolResourceString(CANCEL));
  			cancelButton.setActionCommand("Cancel");
			pane0.add(okButton);
  			pane0.add(cancelButton);
			okButton.addActionListener(importActionListener);
			cancelButton.addActionListener(importActionListener);
			control.add(Box.createRigidArea(NolMainFrame.vpad15));
			control.add(pane0);
			control.add(Box.createRigidArea(NolMainFrame.vpad300));
			control.add(Box.createVerticalGlue());
			return control;
		}

		private void initList(Preprocessor p){
			Project project = frame.getProject();
			int n = project.getNumberOfPreprocessors();
			boolean found = false;
			int firstIndex = 1;
			for(int i=0;i<n;i++){
				Preprocessor prep = project.getPreprocessorByIndex(i);
				if(!p.equals(prep)){
					availablePreprocessors.addElement(prep);
					preprocessorChoice.addItem(prep.getName());
				}
			}
			if(!availablePreprocessors.isEmpty()){
  				Preprocessor prep = (Preprocessor)availablePreprocessors.elementAt(0);
				availableFormulas = prep.getFormulas();
				n = availableFormulas.size();
				Vector selected  = (Vector)availableFormulas.clone();
				importFormulaPanel.setContents(availableFormulas,selected);
			}
		}
		
	   /**Control action implementation  */
		class ImportControlAction extends AbstractAction{
			ImportControlAction() {super("ImportControlAction");}
			@Override
			public void actionPerformed(ActionEvent e) {
				String command = e.getActionCommand();
				if(command.equals("OK")){
					selectedFormulas.removeAllElements();
					
					importFormulaPanel.getSelectedListModel(); 
					int sfmc = importFormulaPanel.getSelectedListModel().size();
 					for(int i=0;i<sfmc;i++){
  						selectedFormulas.addElement(
							importFormulaPanel.getSelectedListModel().elementAt(i)); 
					}			
					boolean isValid = true;
					isValid = addFormulas(selectedFormulas);
					// leave import formula dialog only if formula was valid
					// otherwise, stick around for more tries, or until the user cancels
					if(isValid) {
						funcMode = 0;
						Toolkit.getDefaultToolkit().beep();
						NolImportFormulaDialog.this.dispose();
					}
				}else if(command.equals("From Preprocessor:")){
					fromFileFlag = false;
					
					int index = preprocessorChoice.getSelectedIndex();
					if(index == -1 || availablePreprocessors.isEmpty()){
						importFormulaPanel.setContents(new Vector(),new Vector());
					}else{
  						Preprocessor prep = (Preprocessor)availablePreprocessors.elementAt(index);
						availableFormulas = prep.getFormulas();
						Vector selected  = (Vector)availableFormulas.clone();
						importFormulaPanel.setContents(availableFormulas,selected);
					}
					fileImportBut.setEnabled(false);
				}else if(command.equals("From File:")){
					fromFileFlag = true;
					importFormulaPanel.setContents(new Vector(),new Vector());
					fileImportBut.setEnabled(true);
				}else if(command.equals("File...")){
					if(!fromFileFlag) {
						return;
					}
					FileDialog fileDialog = new FileDialog(NolImportFormulaDialog.this.frame);
					fileDialog.setMode(FileDialog.LOAD);
					fileDialog.setFile("*.tfm");
					fileDialog.setTitle("Import Formulas");
					fileDialog.setLocation(200,200);			
					fileDialog.setVisible(true);

					String file = fileDialog.getFile();
					if (file == null) {
						return;
					}
					String directory = fileDialog.getDirectory();
			// Create necessary input streams
					try{		
						File sourceFile;
						if(directory==null)
							sourceFile = new File(file);	
						else
							sourceFile = new File(directory,file);
						FileInputStream fis = new FileInputStream(sourceFile); // Read from file
						GZIPInputStream gzis = new GZIPInputStream(fis);     // Uncompress
						ObjectInputStream in = new ObjectInputStream(gzis);  // Read objects
			// Read in an object.  It should be a vector of transforms
						availableFormulas = (Vector)in.readObject();
						in.close(); // Close the stream.
					}catch (Exception evt) { System.out.println(evt); }
					int n = availableFormulas.size();
					Vector selected  = (Vector)availableFormulas.clone();
					importFormulaPanel.setContents(availableFormulas,selected);
				}else if(command.equals("Cancel")){
					NolImportFormulaDialog.this.dispose();
				} else if(e.getSource().equals(preprocessorChoice)){
					if(fromFileFlag) {
						return;
					}
					int index = preprocessorChoice.getSelectedIndex();
  					Preprocessor prep = (Preprocessor)availablePreprocessors.elementAt(index);
					availableFormulas = prep.getFormulas();
					Vector selected  = (Vector)availableFormulas.clone();
					importFormulaPanel.setContents(availableFormulas,selected);
				}
			}
		}
	}
}
