package com.gensym.nols.wksp;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.io.*;
import javax.swing.*;
import javax.swing.table.*;
import javax.swing.event.*;
import javax.swing.border.*;

import com.gensym.math.datafit.*;
import com.gensym.math.*;
import com.gensym.nols.data.*;
import com.gensym.nols.dlg.*;
import com.gensym.nols.main.*;

import com.gensym.DEBUG;

public class NolRhoModelWKSP  extends NolInternalFrame 
	implements ModelTrainerListener{
	
	protected static final String MODELWKSP_NAME = "NameLabel";
    protected static final String MODELWKSP_COMMENT = "CommentLabel";
    protected static final String MODELWKSP_TYPE= "ModelWKSP_Type";
    protected static final String MODELWKSP_PREPROCESSOR = "ModelWKSP_Preprocessor";
    protected static final String MODELWKSP_TRAINED = "ModelWKSP_Trained";
    protected static final String MODELWKSP_OUTPUTTABLE = "ModelWKSP_OutputTable";
    protected static final String MODELWKSP_VALIDATE = "ModelWKSP_Validate";
    protected static final String MODELWKSP_EXPORT = "ModelWKSP_Export";
    protected static final String MODELWKSP_EXPORTWEIGHTS = "ModelWKSP_ExportWeights";
    protected static final String MODELWKSP_EXPORTSCALEFACTOR = "ModelWKSP_ExportScaleFactor";
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
	private JLabel modelRate;
	private JTextArea descriptArea;
	private JButton exportBut;
	private JButton weightBut;
	private JTextArea modelStructionDesciption;
	
	private	VarClassifyTableModel varClassifyTableModel;
	private	JTable varClassifyTableView;

	private	StatisticsTableModel statisticsTableModel;
	private	JTable statisticsTableView;

	private NolRhoModel model;
	private int delayTimeUnit;
	private Action actionListener;

	private static int TRAINING = 0;
	private static int TESTING = 1;

	private double modelRateValue = 0.0;
    private static final String goodModel = "Good";
    private static final String sosoModel = "OK";
    private static final String badModel = "Need Improvement";

	private Vector globalVariables; 
	private Vector globalRmse; 
	private Vector globalCorrcoef;

	public NolRhoModelWKSP (NolMainFrame frame, NolRhoModel model){
		super(model.getPreprocessor());
		this.frame = frame;
		this.model = model;
		delayTimeUnit = model.getDelayTimeUnit();
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
		detailedTabbedPane.addTab(frame.getNolResourceString(MODELWKSP_STRUCTURE), getStructurePanel());

		workPane.add("Center", detailedTabbedPane);
		workPane.add("East",getControlPanel());
		setContentPane(workPane);

	}

	private JPanel getGeneralPanel(){
		JPanel infoPane = new JPanel(new BorderLayout());
 		infoPane.setBorder(new EmptyBorder(10,10,10,10));
		JPanel namePane = new JPanel(new GridLayout(4,2,10,5));
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

//		namePane.add(new JLabel("Model Rate:"));
//		modelRate = new JLabel();
//		namePane.add(modelRate);

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
		varClassifyTableModel = new VarClassifyTableModel();
		varClassifyTableView = new JTable(varClassifyTableModel);
		varClassifyTableView.setSelectionBackground(Color.white);
		varClassifyTableView.setCellSelectionEnabled(false);
		varClassifyTableView.setSelectionForeground(Color.black);
		JScrollPane listScrollPane = new JScrollPane(varClassifyTableView);
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

	private JPanel getStructurePanel(){
		JPanel strutPane = new JPanel(new GridLayout());
		JPanel infoPane = new JPanel(new GridLayout());
 		infoPane.setBorder(new EtchedBorder(EtchedBorder.LOWERED));
//		infoPane.setBackground(Color.white);
		modelStructionDesciption = new JTextArea();
		modelStructionDesciption.setEditable(false);
//		modelStructionDesciption.setBackground(Color.white);
		infoPane.add(modelStructionDesciption);
		JPanel cenPane = new JPanel(new GridLayout());
 		cenPane.add(infoPane);
		cenPane.setBorder(new EmptyBorder(10,10,10,10));
		strutPane.add(cenPane);
		return strutPane;
	}
	
	private JPanel getControlPanel(){
		JPanel control = new JPanel();
		control.setBackground(getContentPane().getBackground());
		control.setLayout(new BoxLayout(control, BoxLayout.Y_AXIS));
		control.setBorder(new EmptyBorder(10, 10, 10, 10));

//		if(model.getOutputs().size() == 1){
		JPanel pane0 = new JPanel(new GridLayout(4,1,5,5));
		JButton but = new JButton(frame.getNolResourceString(MODELWKSP_OUTPUTTABLE));
		but.setActionCommand("Output Table...");
		but.addActionListener(actionListener);
  		pane0.add(but);
		exportBut = new JButton(frame.getNolResourceString(MODELWKSP_EXPORT));
		exportBut.setActionCommand("Export...");
		exportBut.addActionListener(actionListener);
  		pane0.add(exportBut);
		weightBut = new JButton(frame.getNolResourceString(MODELWKSP_EXPORTWEIGHTS));
		weightBut.setActionCommand("Export Weights...");
		weightBut.addActionListener(actionListener);
  		pane0.add(weightBut);

		if(((NolRbfnModel)model).isNormalizeData()){
			but = new JButton(frame.getNolResourceString(MODELWKSP_EXPORTSCALEFACTOR));
			but.setActionCommand("Export Scaler...");
			but.addActionListener(actionListener);
			pane0.setLayout(new GridLayout(5,1,5,5));
	  		pane0.add(but);
		}

		but = new JButton(frame.getNolResourceString(DELETE));
		but.setActionCommand("Delete");
		but.addActionListener(actionListener);
  		pane0.add(but);
		control.add(Box.createRigidArea(NolMainFrame.vpad15));
		control.add(pane0);
/*		}else{
			JPanel pane0 = new JPanel(new GridLayout(5,1,5,5));
			JButton but = new JButton(frame.getNolResourceString(MODELWKSP_VALIDATE));
			but.setActionCommand("Validate...");
			but.addActionListener(actionListener);
  			pane0.add(but);
			exportBut = new JButton(frame.getNolResourceString(MODELWKSP_EXPORT));
			exportBut.setActionCommand("Export...");
			exportBut.addActionListener(actionListener);
	// 		pane0.add(exportBut); //The first release will not export classic model as java bean.
			weightBut = new JButton(frame.getNolResourceString(MODELWKSP_EXPORTWEIGHTS));
			weightBut.setActionCommand("Export Weights...");
			weightBut.addActionListener(actionListener);
  			pane0.add(weightBut);

			if(((NolRbfnModel)model).isNormalizeData()){
				but = new JButton(frame.getNolResourceString(MODELWKSP_EXPORTSCALEFACTOR));
				but.setActionCommand("Export Scaler...");
				but.addActionListener(actionListener);
				pane0.setLayout(new GridLayout(6,1,5,5));
	  			pane0.add(but);
			}

			but = new JButton(frame.getNolResourceString(MODELWKSP_PREDVSACTUAL));
			but.setActionCommand("Predicted vs Actual...");
			but.addActionListener(actionListener);
  			pane0.add(but);
			
			but = new JButton(frame.getNolResourceString(MODELWKSP_GLOBALSENSITIVITY));
			but.setActionCommand("Global Sensitivity...");
			but.addActionListener(actionListener);
  			pane0.add(but);
			but = new JButton(frame.getNolResourceString(DELETE));
			but.setActionCommand("Delete");
			but.addActionListener(actionListener);
  			pane0.add(but);
			control.add(Box.createRigidArea(NolMainFrame.vpad15));
			control.add(pane0);
		}
*/		control.add(Box.createRigidArea(NolMainFrame.vpad500));
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

	public NolModel2 getModel(){
		return (NolModel2)model;
	}

	private void initDataDisplay(){
		if(frame.isDemoVersion()){
			weightBut.setEnabled(false);
			exportBut.setEnabled(false);
		}else{
			weightBut.setEnabled(true);
			exportBut.setEnabled(true);
		}

		nameField.setText(model.getName());
		caseName.setText(model.getPreprocessor().getName());
		descriptArea.setText(model.getComment());
		typeName.setText("Rho Net");
		
		if(model.isTrained()){
			trainName.setText("Yes");
		}
		else trainName.setText("No");
		Vector names = new Vector();
		Vector delays = new Vector();
		Vector classification = new Vector();

		double divide = 60000;
		if(delayTimeUnit == 1) {
			divide = 3600000;
		}else if(delayTimeUnit == 3) {
			divide = 1000;
		}

		Vector outs = model.getOutputs();
		int nout = outs.size();
		if(nout == 1){
			names.addElement("Probability Density");
			delays.addElement("0");
			classification.addElement("Output");
		}else{
			Vector outDelays = model.getOutputDelays();
			for(int i=0;i<nout;i++){
				names.addElement(outs.elementAt(i));
				delays.addElement("0");
				classification.addElement("Output");
				long[] dls = (long[])outDelays.elementAt(i);
				for(int j=0;j<dls.length;j++){
					if(dls[j]>0){
						names.addElement(outs.elementAt(i));
						double dd = dls[j]/divide;
						delays.addElement(String.valueOf(dd));
						classification.addElement("Input");
					}
				}
			}
		}
		Vector ins = model.getInputs();
		Vector inDelays = model.getInputDelays();
		for(int i=0;i<inDelays.size();i++){
			long[] dls = (long[])inDelays.elementAt(i);
			for(int j=0;j<dls.length;j++){
				double dd = dls[j]/divide;
				delays.addElement(String.valueOf(dd));
				names.addElement(ins.elementAt(i));
				classification.addElement("Input");
			}
		}

		modelStructionDesciption.setText(((ClassicModel)model).getDescription());

		varClassifyTableModel.setContent(names,delays,classification);
		varClassifyTableView.setModel(varClassifyTableModel);
		varClassifyTableView.validate();
		// initialize statistics
		globalVariables = new Vector();
		globalRmse = new Vector();
		globalCorrcoef = new Vector();
		if(model.isTrained()){
			if(nout > 1){
				getModelStatistics(model,globalVariables, globalRmse, globalCorrcoef);
				statisticsTableModel.setContent(globalVariables,globalRmse,globalCorrcoef);
				statisticsTableView.validate();
			}
		}
	}

	private void getModelStatistics(NolRhoModel m, Vector variables, Vector rmse, Vector corrcoef) {
		int digits = 4;
		Vector names = model.getOutputVarNames();
		for(int i=0;i<names.size();i++) {
			variables.addElement(names.elementAt(i));
		}
		int nout = m.getNout();
		modelRateValue =0;
		ClassicValidationParameters VP = null;
		VP = ((NolRbfnModel)m).trainingResults;
		for(int j=0;j<nout;j++) {
			rmse.addElement(Utilities.formatDouble(VP.rmse.get(j), digits));
			corrcoef.addElement(Utilities.formatDouble(VP.corrcoef.get(j), digits));
			modelRateValue = modelRateValue+VP.corrcoef.get(j);
		}
		modelRateValue = modelRateValue/nout;

	}



	@Override
	public void trainingComplete(){
		globalVariables.removeAllElements();
		globalRmse.removeAllElements();
		globalCorrcoef.removeAllElements();
		if(model.isTrained()){
			getModelStatistics(model,globalVariables, globalRmse, globalCorrcoef);
			statisticsTableModel.setContent(globalVariables,globalRmse,globalCorrcoef);
			statisticsTableView.validate();
			trainName.setText("Yes");
			if(modelRateValue>0.75){
				modelRate.setText(goodModel);
			}else if(modelRateValue>0.55){
				modelRate.setText(sosoModel);
			}else{
				modelRate.setText(badModel);
			}
		}
	}

/** The inner control listener class.*/
    class ControlAction extends AbstractAction implements DocumentListener{
		ControlAction() {super("controlAction");}

        @Override
		public void actionPerformed(ActionEvent e) {
			String command = e.getActionCommand();
			if(command.equals("Output Table...")){
				frame.showVariableValueWKSP(model);

			}else if(command.equals("Validate...")){
				if(!model.isTrained()){
					frame.showOKDialog("Cannot validate a untrained model.");
					return;
				}
				frame.showModelValidationWKSP(model);
			}else if(command.equals("Export Scaler...")){
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
				fileChooser.setDialogTitle("Export Normalize Factors");
				NolFileFilter filter1 = new NolFileFilter(
				new String[] {"csv"}, "ASCII Factor File"
				);
				fileChooser.addChoosableFileFilter(filter1);
				fileChooser.setFileFilter(filter1);
				fileChooser.setDialogType(JFileChooser.SAVE_DIALOG);

				fileChooser.setSelectedFile(new File(model.getName()+".csv"));
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

				String path = currentPath.getPath();
				int dotInd = path.indexOf(".");
				if(dotInd == -1){
					path = path+".csv";
				}	

				// try to start writing
				try {
					((NolRbfnModel)model).writeNormalizeFactorToFile(path);
				}catch (Exception evt) {
					frame.showOKDialog("Error in writing the scale factor.");
				}
				Toolkit.getDefaultToolkit().beep();

			}else if(command.equals("Export...")){
				JFileChooser fileChooser = new JFileChooser();
				fileChooser.setDialogTitle("Export Model in XML Format");
				NolFileFilter filter2 = new NolFileFilter(
					new String[] {"xml"}, "Extensible Markup Language File"
				);
				fileChooser.addChoosableFileFilter(filter2);
				fileChooser.setFileFilter(filter2);
				fileChooser.setDialogType(JFileChooser.SAVE_DIALOG);

				File currentDirectory = new File(NolMainFrame.miscDirectory);
				if(currentDirectory.exists()) {
					fileChooser.setCurrentDirectory(currentDirectory);
				}

				fileChooser.setSelectedFile(new File(model.getName()+".xml"));
				fileChooser.setLocation(200,200);			
				int retval = fileChooser.showSaveDialog(frame);

				String defaultExt = ".mod";
				javax.swing.filechooser.FileFilter activeFilter = fileChooser.getFileFilter();
				if (activeFilter != null){
					if (activeFilter.equals(filter2)){
						defaultExt = ".xml";
					}
				}				 
				fileChooser.setFileFilter(null);
				fileChooser.removeChoosableFileFilter(filter2);
				
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
				
				String pName = file;
				int dotInd = file.indexOf(".");
				int type = 1; // mod=0; xml=1. 
				if(dotInd == -1){
					file = file+defaultExt;
					if(defaultExt.equals(".xml")){
						type = 1;
					}else if(defaultExt.equals(".mod")){
						type = 0;
					}
				}else{
					pName = file.substring(0,dotInd);	
					String suff = file.substring(dotInd);
					if(suff.equals(".xml")){
						type = 1;
					}else{
						file = file+".xml";
						type = 1;
					}
				}
				if (type == 1){
					System.out.println("export xml file");
					try {
						NolModelXMLHandler handler = new NolModelXMLHandler();
						handler.setModel(model);
						handler.saveToFile(file, directory);
					} catch (Exception ex) {
						frame.showOKDialog("Cannot save models without a valid software license. Exception = "+ex.getMessage());
					}
				}
				Toolkit.getDefaultToolkit().beep();
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
				fileChooser.setDialogTitle("Export Model Weights");
				NolFileFilter filter1 = new NolFileFilter(
				new String[] {"rho"}, "ASCII Model Weight File"
				);
				fileChooser.addChoosableFileFilter(filter1);
				fileChooser.setFileFilter(filter1);
				fileChooser.setDialogType(JFileChooser.SAVE_DIALOG);

				File currentDirectory = new File(NolMainFrame.miscDirectory);
				if(currentDirectory.exists()) {
					fileChooser.setCurrentDirectory(currentDirectory);
				}

				fileChooser.setSelectedFile(new File(model.getName()+".rho"));
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

				String path = currentPath.getPath();
				int dotInd = path.indexOf(".");
				if(dotInd == -1){
					path = path+".rho";
				}	

				// try to start writing
				try {
					((NolRbfnModel)model).writeRbfnToFile(path);
				}catch (Exception evt) {
					frame.showOKDialog("Error in writing the weights.");
				}
				Toolkit.getDefaultToolkit().beep();
			}else if(command.equals("Local Sensitivity...")){
				if(!model.isTrained()){
					frame.showOKDialog("Cannot calculate sensitivity with a untrained model.");
					return;
				}
				frame.showModelSensitivityWKSP(model,0);
			}else if(command.equals("Global Sensitivity...")){
				if(!model.isTrained()){
					frame.showOKDialog("Cannot calculate sensitivity with a untrained model.");
					return;
				}
				frame.showModelSensitivityWKSP(model,1);
			}else if(command.equals("Delete")){
				if(DEBUG.debugFlag) {
					System.out.println("Delete modelWKSP");
				}
				frame.removeModel(model);
			}else if(command.equals("Predicted vs Actual...")){
				if(!model.isTrained()){
					frame.showOKDialog("Cannot calculate prediction with a untrained model.");
					return;
				}
				setWaitCursor(true);  // launch could take a while, so indicate with hourglass
				frame.showClassicModelPredVsActWKSP(model);
				setWaitCursor(false);
			}else if(e.getSource().equals(nameField)){
				String nm = nameField.getText();
				if(nm.length() > 0){
					model.setName(nm);
					String title = "Model:["+model.getName()+"]";
					setTitle(title);
					frame.getProjectTree().changeRhoModelName((NolRhoModel)model,true);
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


	class VarClassifyTableModel extends AbstractTableModel{
		private int row,col;
		private Vector names, delays, classification;

		private String[] colHd = {frame.getNolResourceString(MODELWKSP_VARIABLES),
			frame.getNolResourceString(MODELWKSP_CLASSIFICATION),
			frame.getNolResourceString(MODELWKSP_DELAY)
		};
		public VarClassifyTableModel(){
			row = 0;
			col = 3;
		}

		public void setContent(Vector names, Vector delays, Vector classification){
			this.names = names;
			this.delays = delays;
			this.classification = classification;
			row = names.size();
/*			System.out.println("row="+row);
			System.out.println("row delays="+delays.size());
			for(int i=0;i<row;i++){
			System.out.println("names="+names.elementAt(i));
			}
			for(int i=0;i<delays.size();i++){
			System.out.println("delays="+delays.elementAt(i));
			}
*/		}
		@Override
		public int getColumnCount() { return col; }
		@Override
		public int getRowCount() { return row;}
		@Override
		public Object getValueAt(int r, int c){
			if(c == 0) {
				return names.elementAt(r);
			}else if(c == 1) {
				return classification.elementAt(r);
			}else if(c == 2) {
				return delays.elementAt(r);  // MK switched delay to last col
			}
			return "";
		}
         
		@Override
		public String getColumnName(int c) {
			if(c == 2){
				String hd = colHd[c]+"(Minute)";
				if(delayTimeUnit == 1)
					hd = colHd[c]+"(Hour)";
				else if(delayTimeUnit == 3)
					hd = colHd[c]+"(Second)";
				return hd;
			}
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
		private Vector variables;
		private Vector rmse;
		private Vector corrcoef;
		private String[] colHd = {frame.getNolResourceString(MODELWKSP_VARIABLES),
			frame.getNolResourceString(MODELWKSP_RMSE),
			frame.getNolResourceString(MODELWKSP_CORRCOEF)
		};
		public StatisticsTableModel(){
			row = 0;
			col = 3;
		}

		public void setContent(Vector variables, Vector rmse, Vector corrcoef){
			this.variables = variables;
			this.rmse = rmse;
			this.corrcoef = corrcoef;
			row = variables.size();
		}
		@Override
		public int getColumnCount() { return col; }
		@Override
		public int getRowCount() { return row;}
		@Override
		public Object getValueAt(int r, int c){
			if(c == 0){
				return variables.elementAt(r);
			}else if(c == 1){
				return rmse.elementAt(r);
			}else if(c==2){
				return corrcoef.elementAt(r);
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

