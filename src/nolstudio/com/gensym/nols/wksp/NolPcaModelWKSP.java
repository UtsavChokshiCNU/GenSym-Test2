package com.gensym.nols.wksp;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.io.*;
import java.nio.charset.Charset;

import javax.swing.*;
import javax.swing.table.*;
import javax.swing.event.*;
import javax.swing.border.*;

import com.gensym.math.matrix.*;
import com.gensym.math.*;
import com.gensym.nols.data.*;
import com.gensym.nols.dlg.*;
import com.gensym.nols.main.*;

import com.gensym.DEBUG;

public class NolPcaModelWKSP  extends NolInternalFrame 
	implements ModelTrainerListener{
	
	protected static final String MODELWKSP_NAME = "NameLabel";
    protected static final String MODELWKSP_COMMENT = "CommentLabel";
    protected static final String MODELWKSP_TYPE= "ModelWKSP_Type";
    protected static final String MODELWKSP_PREPROCESSOR = "ModelWKSP_Preprocessor";
    protected static final String MODELWKSP_TRAINED = "ModelWKSP_Trained";
    protected static final String MODELWKSP_VALIDATE = "ModelWKSP_Validate";
    protected static final String MODELWKSP_EXPORT = "ModelWKSP_Export";
    protected static final String MODELWKSP_EXPORTWEIGHTS = "ModelWKSP_ExportWeights";
    protected static final String MODELWKSP_PREDVSACTUAL = "ModelWKSP_PredVsActual";
    protected static final String MODELWKSP_LOCALSENSITIVITY = "ModelWKSP_LocalSensitivity";
    protected static final String MODELWKSP_GLOBALSENSITIVITY = "ModelWKSP_GlobalSensitivity";
    protected static final String DELETE = "DeleteLabel";
														   
    protected static final String MODELWKSP_GENERAL = "GeneralLabel";
    protected static final String MODELWKSP_VARIABLES = "VariableLabel";
    protected static final String MODELWKSP_STATISTICS = "ModelWKSP_Statistics";
    protected static final String MODELWKSP_STRUCTURE = "ModelWKSP_Structure";

    protected static final String MODELWKSP_DELAY = "ModelWKSP_Delay";
    protected static final String MODELWKSP_CLASSIFICATION = "ModelWKSP_Classification";
    protected static final String MODELWKSP_VALUE = "ModelWKSP_Value";
    protected static final String MODELWKSP_RMSE = "ModelWKSP_RMSE";
    protected static final String MODELWKSP_CORRCOEF = "ModelWKSP_CORRCOEF";
//    protected static final String MODELWKSP_STRUCTURE = "ModelWKSP_";

	private NolMainFrame frame;
	private JTextField nameField;
	private JLabel caseName;
	private JLabel typeName;
	private JLabel trainName;
	private JTextField factorNumber;
	
	private JTextArea descriptArea;
	private JButton weightBut;
	private JButton dataBut;
	private JTextArea modelStructionDesciption;
	
	private	VarTableModel varTableModel;
	private	JTable varTableView;

	private	StatisticsTableModel statisticsTableModel;
	private	JTable statisticsTableView;

	private NolPcaModel model;
	private Action actionListener;

	public NolPcaModelWKSP (NolMainFrame frame, NolPcaModel model){
		super(model.getPreprocessor());
		this.frame = frame;
		this.model = model;
		String title = "Model:["+model.getName()+"]";
		setTitle(title);
		actionListener = new ControlAction();
		initLayout();
		initDataDisplay();
	}

	private void initLayout(){
		JPanel workPane = new JPanel(new BorderLayout());
													    
		JTabbedPane detailedTabbedPane = new JTabbedPane();
		detailedTabbedPane.addTab(frame.getNolResourceString(MODELWKSP_GENERAL), getGeneralPanel());
		detailedTabbedPane.setSelectedIndex(0);
		detailedTabbedPane.addTab(frame.getNolResourceString(MODELWKSP_VARIABLES), getVariablePanel());
		detailedTabbedPane.addTab(frame.getNolResourceString(MODELWKSP_STATISTICS), getStatisticPanel());

		workPane.add("Center", detailedTabbedPane);
		workPane.add("East",getControlPanel());
		setContentPane(workPane);

	}

	private JPanel getGeneralPanel(){
		JPanel infoPane = new JPanel(new BorderLayout());
 		infoPane.setBorder(new EmptyBorder(10,10,10,10));
		JPanel namePane = new JPanel(new GridLayout(5,2,10,5));
		namePane.setBorder(new EmptyBorder(10,10,10,10));
		namePane.add(new JLabel(frame.getNolResourceString(MODELWKSP_NAME)+":"));
		nameField = new JTextField();
		nameField.addActionListener(actionListener);
		namePane.add(nameField);
		namePane.add(new JLabel(frame.getNolResourceString(MODELWKSP_TYPE)+":"));
		typeName = new JLabel();
		namePane.add(typeName);

		namePane.add(new JLabel(frame.getNolResourceString(MODELWKSP_PREPROCESSOR)+":"));
		caseName = new JLabel();
		namePane.add(caseName);

		namePane.add(new JLabel(frame.getNolResourceString(MODELWKSP_TRAINED)+"?"));
		trainName = new JLabel();
		namePane.add(trainName);

		namePane.add(new JLabel(frame.getNolResourceString("NolPcaModelWKSP_Retained_Factor")+":"));
		factorNumber = new JTextField();
		factorNumber.addActionListener(actionListener);
		namePane.add(factorNumber);

		JPanel descriptPane = new JPanel(new GridLayout());
		descriptPane.setBorder(new TitledBorder(new EmptyBorder(1, 1, 1, 1),               
			frame.getNolResourceString(MODELWKSP_COMMENT)+":", TitledBorder.LEFT , TitledBorder.TOP));
		descriptArea = new JTextArea();
		descriptArea.getDocument().addDocumentListener((DocumentListener)actionListener);
		JScrollPane listScrollPane = new JScrollPane(descriptArea);
		listScrollPane.setBorder(BorderFactory.createLoweredBevelBorder());
		listScrollPane.setPreferredSize(NolMainFrame.vpad40); 
		descriptPane.add(listScrollPane);
		infoPane.add("North",namePane);
		infoPane.add("Center",descriptPane);
		return infoPane;
	}

	private JPanel getVariablePanel(){
		JPanel varPane = new JPanel(new GridLayout());
		JPanel cenPane = new JPanel(new GridLayout());
  		cenPane.setBorder(new EmptyBorder(10,10,10,10));
		varTableModel = new VarTableModel();
		varTableView = new JTable(varTableModel);
		varTableView.setSelectionBackground(Color.white);
		varTableView.setCellSelectionEnabled(false);
		varTableView.setSelectionForeground(Color.black);
		JScrollPane listScrollPane = new JScrollPane(varTableView);
		listScrollPane.setBackground(Color.white);
		cenPane.add(listScrollPane);
		varPane.add(cenPane);
		return varPane;
	}


	
	private JPanel getStatisticPanel(){
		JPanel statPane = new JPanel(new GridLayout());
		JPanel cenPane = new JPanel(new GridLayout());
  		cenPane.setBorder(new EmptyBorder(10,10,10,10));
		statisticsTableModel = new StatisticsTableModel();
		statisticsTableView = new JTable(statisticsTableModel);
		statisticsTableView.setSelectionBackground(Color.white);
		statisticsTableView.setCellSelectionEnabled(false);
		statisticsTableView.setSelectionForeground(Color.black);
		JScrollPane listScrollPane = new JScrollPane(statisticsTableView);
		listScrollPane.setBackground(Color.white);
		cenPane.add(listScrollPane);
		statPane.add(cenPane);
		return statPane;
	}

	private JPanel getControlPanel(){
		JPanel control = new JPanel();
		control.setBackground(getContentPane().getBackground());
		control.setLayout(new BoxLayout(control, BoxLayout.Y_AXIS));
		control.setBorder(new EmptyBorder(10, 10, 10, 10));

		JPanel pane0 = new JPanel(new GridLayout(8,1,5,5));
		JButton but = new JButton(frame.getNolResourceString(MODELWKSP_VALIDATE));
		but.setActionCommand("Validate...");
		but.addActionListener(actionListener);
  		pane0.add(but);
		weightBut = new JButton(frame.getNolResourceString(MODELWKSP_EXPORTWEIGHTS));
		weightBut.setActionCommand("Export Weights...");
		weightBut.addActionListener(actionListener);
  		pane0.add(weightBut);
		JButton scoreBut = new JButton(frame.getNolResourceString("ModelWKSP_ExportScore"));
		scoreBut.setActionCommand("Export Scores...");
		scoreBut.addActionListener(actionListener);
  		pane0.add(scoreBut);
		dataBut = new JButton(frame.getNolResourceString("ModelWKSP_Residual"));
		dataBut.setActionCommand("Residual Chart...");
		dataBut.addActionListener(actionListener);
  		pane0.add(dataBut);
		but = new JButton("Loading Chart");
		but.setActionCommand("Loading Chart");
		but.addActionListener(actionListener);
  		pane0.add(but);
		but = new JButton("Single Score Chart");
		but.setActionCommand("Single Score Chart");
		but.addActionListener(actionListener);
  		pane0.add(but);
		
		but = new JButton("2D Score Chart");
		but.setActionCommand("2D Score Chart");
		but.addActionListener(actionListener);
  		pane0.add(but);

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

	private void refreshDisplay(){
		Rectangle rv = this.getBounds();
		this.setBounds(rv.x,rv.y,rv.width+20,rv.height);
		this.paintImmediately(rv.x,rv.y,rv.width+20,rv.height);
		this.validate();
		this.setBounds(rv.x,rv.y,rv.width,rv.height);
		this.validate();
	}

	public NolPcaModel getModel(){
		return model;
	}

	private void initDataDisplay(){
		if(frame.isDemoVersion()){
			weightBut.setEnabled(false);
		}else{
			weightBut.setEnabled(true);
		}

		nameField.setText(model.getName());
		caseName.setText(model.getPreprocessor().getName());
		descriptArea.setText(model.getComment());
		typeName.setText("PCA Model");
		factorNumber.setText(""+model.getRetainedFactorNumber());
		
		if(model.isTrained()){
			trainName.setText("Yes");
		}else {
			trainName.setText("No");
		}
		Vector names = model.getInputs();
		varTableModel.setContent(names);
		varTableView.setModel(varTableModel);
		varTableView.validate();
		Vector params = new Vector();
		Vector vals = new Vector();
		Matrix pclims = model.getScoreLimits();
		int nm = names.size();
		params.addElement("SPE 95% Limit (Q value)");
		vals.addElement(new Double(model.getQ()));
		for (int i=0;i<nm;i++){
			params.addElement("PC "+(i+1)+" 95% Limit");
			vals.addElement(new Double(pclims.get(i)));
		}
		statisticsTableModel.setContent(params,vals);
		statisticsTableView.validate();
	}


	@Override
	public void trainingComplete(){}

/** The inner control listener class.*/
    class ControlAction extends AbstractAction implements DocumentListener{
		ControlAction() {super("controlAction");}

        @Override
		public void actionPerformed(ActionEvent e) {
			String command = e.getActionCommand();
			if(command.equals("Validate...")){
				if(!model.isTrained()){
					frame.showOKDialog("Cannot validate a untrained model.");
					return;
				}
				showModelValidationWKSP();
			} else if(command.equals("Export Weights...")){
				if(!model.isTrained()){
					frame.showOKDialog("Cannot export a untrained model.");
					return;
				}
				try {  // just see if this is a licensed copy
					Class versionManagerClass = Class.forName("com.gensym.nols.data.VersionManagerForOnlineProcessor");
				} catch (Exception ex) {
					frame.showOKDialog("Cannot save models without a valid software license.");
					return;
				}
 				JFileChooser fileChooser = new JFileChooser();
				fileChooser.setDialogTitle("Export PCA Parameters");
				NolFileFilter filter1 = new NolFileFilter(
				new String[] {"pca"}, "ASCII PCA Parameter File"
				);
				fileChooser.addChoosableFileFilter(filter1);
				fileChooser.setFileFilter(filter1);
				fileChooser.setDialogType(JFileChooser.SAVE_DIALOG);

				File currentDirectory = new File(NolMainFrame.miscDirectory);
				if(currentDirectory.exists()) {
					fileChooser.setCurrentDirectory(currentDirectory);
				}

				fileChooser.setSelectedFile(new File(model.getName()+".pca"));
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

				// try to start writing
				int dotInd = file.indexOf(".");
				if(dotInd == -1){
					file = file+".pca";
				}	
				try{
					exportPCAParameters(directory, file);
				}catch(Exception evt){
					evt.printStackTrace();
				}
				Toolkit.getDefaultToolkit().beep();				
			} else if(command.equals("Export Scores...")){
				if(!model.isTrained()){
					frame.showOKDialog("Cannot export a untrained model.");
					return;
				}
				try {  // just see if this is a licensed copy
					Class versionManagerClass = Class.forName("com.gensym.nols.data.VersionManagerForOnlineProcessor");
				} catch (Exception ex) {
					frame.showOKDialog("Cannot save models without a valid software license.");
					return;
				}
 				JFileChooser fileChooser = new JFileChooser();
				fileChooser.setDialogTitle("Export PCA Scores");
				NolFileFilter filter1 = new NolFileFilter(
				new String[] {"pca"}, "ASCII PCA Scores File"
				);
				fileChooser.addChoosableFileFilter(filter1);
				fileChooser.setFileFilter(filter1);
				fileChooser.setDialogType(JFileChooser.SAVE_DIALOG);

				File currentDirectory = new File(NolMainFrame.miscDirectory);
				if(currentDirectory.exists()) {
					fileChooser.setCurrentDirectory(currentDirectory);
				}

				fileChooser.setSelectedFile(new File(model.getName()+".sco"));
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

				// try to start writing
				int dotInd = file.indexOf(".");
				if(dotInd == -1){
					file = file+".sco";
				}	
				try{
					exportPCAScores(directory, file);
				}catch(Exception evt){
					evt.printStackTrace();
				}
				Toolkit.getDefaultToolkit().beep();				
			} else if(command.equals("Residual Chart...")){
				showResidualChart();
				Toolkit.getDefaultToolkit().beep();
			}else if(command.equals("2D Score Chart")){
				show2DScoreChart();
			}else if(command.equals("Single Score Chart")){
				showSingleScoreChart();
			}else if(command.equals("Loading Chart")){
				showLoadingChart();
			}else if(command.equals("Delete")){
				if(DEBUG.debugFlag) {
					System.out.println("Delete modelWKSP");
				}
				frame.removeModel(model);
			}else if(e.getSource().equals(nameField)){
				String nm = nameField.getText();
				if(nm.length() > 0){
					model.setName(nm);
					String title = "Model:["+model.getName()+"]";
					setTitle(title);
					frame.getProjectTree().changePredictiveModelName(model,true);
				}else{
					nm = model.getName();
					nameField.setText(nm);
				}
			}
		}
		@Override
		public void changedUpdate(DocumentEvent e){}
		@Override
		public void insertUpdate(DocumentEvent e){
			String com = descriptArea.getText();
			model.setComment(com);
		}
		@Override
		public void removeUpdate(DocumentEvent e){
			String com = descriptArea.getText();
			model.setComment(com);
		}
    }

	protected void exportPCAParameters(String directory, String file) throws IOException{
		
		FileOutputStream outStream = null;
	    Writer writer = null;
	    BufferedWriter Source = null;
	    try {
			File SourceFile = new File(directory,file);
			outStream = new FileOutputStream(SourceFile);
			writer = new OutputStreamWriter(outStream, Charset.defaultCharset());
			Source = new BufferedWriter(writer);
			model.saveParameters(Source);
	    }finally {
	    	closeSilently(Source);
	    	closeSilently(writer);
	    	closeSilently(outStream);
	    }
	}

	protected void exportPCAScores(String directory, String file) throws IOException, MathException{
		FileOutputStream outStream = null;
	    Writer writer = null;
	    BufferedWriter Source = null;
	    try {
			File SourceFile = new File(directory,file);
			outStream = new FileOutputStream(SourceFile);
			writer = new OutputStreamWriter(outStream, Charset.defaultCharset());
			Source = new BufferedWriter(writer);
			model.saveScores(Source);
	    }finally {
	    	closeSilently(Source);
	    	closeSilently(writer);
	    	closeSilently(outStream);
	    }
	}

	private void showModelValidationWKSP(){
		DataSeries ds = getValidateDataSeries();
		if(ds == null){
			return;
		}
		try{
			NolValidatePcaWKSP validateWKSP = new NolValidatePcaWKSP(frame,model,ds);
			showInternalFrame(validateWKSP);
		}catch(MathException evt){
			System.out.println("evt="+evt.getMessage());		
		}
	}

	private DataSeries getValidateDataSeries(){
		Vector inputVarNames = new Vector();
		Vector inputVars = new Vector();
		Vector ins = model.getInputs();
		for(int i=0;i<ins.size();i++){
			inputVarNames.addElement(ins.elementAt(i));
		}
		Preprocessor prep = model.getPreprocessor();
		for(int i=0;i<inputVarNames.size();i++){
			String varName = (String)inputVarNames.elementAt(i);
			Variable varObj = prep.getVariableFromVariableName(varName);
			inputVars.addElement(varObj);
		}

		Vector ddss = new Vector();
		for(int i=0;i<inputVars.size();i++){
			Variable varObj = (Variable)inputVars.elementAt(i);
			DataSeries ds = varObj.getDataSeries();
			if(!ddss.contains(ds)){
				ddss.addElement(ds);
			}
		}
		int n = ddss.size();
		Project2 project = frame.getProject();
		RawDataSource rawData = project.getRawDataSource();
		Vector rawDss = rawData.getDataSeries();
		boolean hasValidateData = false;
		Vector availableDs = new Vector(n);
		for(int i=0;i<n;i++){
			int c=0;
			DataSeries ds1 = (DataSeries)ddss.elementAt(i);
			Vector avaiDs = new Vector();
			for(int j=0;j<rawDss.size();j++){
				DataSeries rds = (DataSeries)rawDss.elementAt(j);
				if(ds1.getName().equals(rds.getName())){
					avaiDs.addElement(rds);
				}else{
					if(ds1.getHasTimeStamps() == rds.getHasTimeStamps()){
						Vector varObjs1 = ds1.getVarObjects();
						Vector varObjs2 = rds.getVarObjects();
						boolean match = true;
						for(int k=0;k<varObjs1.size();k++){							
							Variable varObj = (Variable)varObjs1.elementAt(k);
							String varName1 = varObj.toString();
							if(inputVars.contains(varObj)){
								boolean found = false;
								for(int l=0;l<varObjs2.size();l++){
 									String varName2 = varObjs2.elementAt(l).toString();
									if(varName1.equals(varName2)){
									   found = true;
									   break;
									}
								}
								if(!found){
								   match = false;
								   break;
								}
							}
						}
						if(match){
							avaiDs.addElement(rds);
							hasValidateData = true;
						}
					}
				}
			}
			availableDs.addElement(avaiDs);
		}
		if(!hasValidateData){
			frame.showOKDialog(frame.getNolResourceString("MainFrame_NoDataMatchModel"));
			return null;
		}

		NolModelValidateChoiceDialog modelValidateChoiceDialog = new NolModelValidateChoiceDialog(frame,"Choose the validation data series");
		modelValidateChoiceDialog.setContent(ddss,availableDs);
		modelValidateChoiceDialog.setBounds(200, 200, 420, 300);
		modelValidateChoiceDialog.setVisible(true);
		
		if(!modelValidateChoiceDialog.getResult()){
			return null;
		}

		if(!modelValidateChoiceDialog.hasValidData()){
			frame.showOKDialog(frame.getNolResourceString("MainFrame_InvalidDataChoice"));
			return null;
		}
		Vector vds = modelValidateChoiceDialog.getValidateDataSeries();
		if (vds.isEmpty()) 
			return null;
		DataSeries ds = (DataSeries)vds.elementAt(0);
		return ds;
	}

	private void show2DScoreChart(){
		try {
			NolInternalFrame activeInternalFrame = new Nol2DScoreChartFrame(frame,model); 
			showInternalFrame(activeInternalFrame);
		} catch (MathException pe) {
			frame.showOKDialog(pe.getMessage());
		}
	}
	private void showSingleScoreChart(){
		try {
			NolInternalFrame activeInternalFrame = new NolSingleScoreChartFrame(frame,model); 
			showInternalFrame(activeInternalFrame);
		} catch (MathException pe) {
			frame.showOKDialog(pe.getMessage());
		}
	}


	private void showLoadingChart(){
		try {
			NolInternalFrame activeInternalFrame = new NolPcaLoadingChartFrame(frame,model); 
			showInternalFrame(activeInternalFrame);
		} catch (MathException pe) {
			frame.showOKDialog(pe.getMessage());
		}
	}
	private void showResidualChart(){
		try {
			NolInternalFrame activeInternalFrame = new NolResidualChartFrame(frame,model); 
			showInternalFrame(activeInternalFrame);
		} catch (MathException pe) {
			frame.showOKDialog(pe.getMessage());
		}
	}
 
	private void showInternalFrame(NolInternalFrame activeInternalFrame){
		activeInternalFrame.setClosable(true);
		activeInternalFrame.setMaximizable(false);
		activeInternalFrame.setIconifiable(true);
		activeInternalFrame.setResizable(true);
		frame.getEditor().add(activeInternalFrame, JLayeredPane.DEFAULT_LAYER);
		activeInternalFrame.setBounds(50, 10, 640,440);
		try { 
			activeInternalFrame.setSelected(true); 
		} catch (java.beans.PropertyVetoException e2) {
			System.err.println("Non-Fatal exception: " + e2.getMessage());
			e2.printStackTrace();		
		}
		frame.getEditor().moveToFront(activeInternalFrame);
		activeInternalFrame.setBounds(50, 10, 660,480);
		activeInternalFrame.validate();
		frame.addWindowMenuItem(activeInternalFrame);
	}

	class VarTableModel extends AbstractTableModel{
		private int row,col;
		private Vector names;

		private String[] colHd = {frame.getNolResourceString(MODELWKSP_VARIABLES)};
		public VarTableModel(){
			row = 0;
			col = 1;
		}

		public void setContent(Vector names){
			this.names = names;
			row = names.size();
		}
		@Override
		public int getColumnCount() { return col; }
		@Override
		public int getRowCount() { return row;}
		@Override
		public Object getValueAt(int r, int c){
			if(c == 0) {
				return names.elementAt(r);
			}
			return "";
		}
         
		@Override
		public String getColumnName(int c) {
			return colHd[c];
		}
           
		@Override
		public Class getColumnClass(int c) {
			return getValueAt(0, c).getClass();
		}

		@Override
		public boolean isCellEditable(int r, int c) {
			return false;
		}	
	}

	class StatisticsTableModel extends AbstractTableModel{
		private int row,col;
		private Vector params;
		private Vector vals;
		private String[] colHd = {"Parameters","Values"};
		public StatisticsTableModel(){
			row = 0;
			col = 2;
		}

		public void setContent(Vector params, Vector vals){
			this.params = params;
			this.vals = vals;
			row = params.size();
		}
		@Override
		public int getColumnCount() { return col; }
		@Override
		public int getRowCount() { return row;}
		@Override
		public Object getValueAt(int r, int c){
			if(c == 0){
				return params.elementAt(r);
			}else if(c == 1){
				return vals.elementAt(r).toString();
			}
			return "";
		}
         
		@Override
		public String getColumnName(int c) {
			return colHd[c];
		}
           
		@Override
		public Class getColumnClass(int c) {
			return getValueAt(0, c).getClass();
		}

		@Override
		public boolean isCellEditable(int r, int c) {
			return false;
		}
		
		@Override
		public void setValueAt(Object aValue, int r, int c) {
		}
	}
}

