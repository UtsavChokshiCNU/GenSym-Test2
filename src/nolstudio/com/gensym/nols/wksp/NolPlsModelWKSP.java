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
import com.gensym.math.matrix.*;
import com.gensym.math.*;
import com.gensym.nols.data.*;
import com.gensym.nols.dlg.*;
import com.gensym.nols.main.*;

import com.gensym.DEBUG;

public class NolPlsModelWKSP  extends NolInternalFrame 
	implements ModelTrainerListener{
	
	protected static final String MODELWKSP_NAME = "NameLabel";
    protected static final String MODELWKSP_COMMENT = "CommentLabel";
    protected static final String MODELWKSP_TYPE= "ModelWKSP_Type";
    protected static final String MODELWKSP_PREPROCESSOR = "ModelWKSP_Preprocessor";
    protected static final String MODELWKSP_TRAINED = "ModelWKSP_Trained";
    protected static final String MODELWKSP_VALIDATE = "ModelWKSP_Validate";
    protected static final String MODELWKSP_EXPORT = "ModelWKSP_Export";
    protected static final String MODELWKSP_EXPORTWEIGHTS = "ModelWKSP_ExportWeights";
    protected static final String MODELWKSP_EXPORTDATA = "ModelWKSP_ExportData";
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
	private JButton dataBut;
	private JTextArea modelStructionDesciption;
	
	private	VarClassifyTableModel varClassifyTableModel;
	private	JTable varClassifyTableView;

	private	StatisticsTableModel statisticsTableModel;
	private	JTable statisticsTableView;

	
	private NolPlsModel model;
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

	public NolPlsModelWKSP (NolMainFrame frame, NolPlsModel model){
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

		namePane.add(new JLabel("Model Rate:"));
		modelRate = new JLabel();
		namePane.add(modelRate);

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

		JPanel pane0 = new JPanel(new GridLayout(6,1,5,5));
		JButton but = new JButton(frame.getNolResourceString(MODELWKSP_VALIDATE));
		but.setActionCommand("Validate...");
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
/*		dataBut = new JButton(frame.getNolResourceString(MODELWKSP_EXPORTDATA));
		dataBut.setActionCommand("Export Training Data...");
		dataBut.addActionListener(actionListener);
  		pane0.add(dataBut);
*/
		but = new JButton(frame.getNolResourceString(MODELWKSP_PREDVSACTUAL));
		but.setActionCommand("Predicted vs Actual...");
		but.addActionListener(actionListener);
  		pane0.add(but);
		
//		if(DEBUG.more){
//		but = new JButton(frame.getNolResourceString(MODELWKSP_LOCALSENSITIVITY));
//		but.setActionCommand("Local Sensitivity...");
//		but.addActionListener(actionListener);
//		pane0.add(but);
		but = new JButton(frame.getNolResourceString("NolPlsModelWKSP_Ratio"));
		but.setActionCommand("Global Sensitivity...");
		but.addActionListener(actionListener);
  		pane0.add(but);
//		}
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

	public NolPlsModel getModel(){
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
		typeName.setText("PLS Model");
		
		if(model.isTrained()){
			trainName.setText("Yes");
		}
		else trainName.setText("No");
		Vector names = new Vector();
		Vector delays = new Vector();
		Vector classification = new Vector();

		double divide = 60000;
		if(delayTimeUnit == 1){
			divide = 3600000;
		}else if(delayTimeUnit == 3){
			divide = 1000;
		}

		Pls net = (Pls) model.getModel();
		Vector outs = model.getOutputs();
		int nout = outs.size();
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
		modelStructionDesciption.setText(net.getDescription());
		varClassifyTableModel.setContent(names,delays,classification);
		varClassifyTableView.setModel(varClassifyTableModel);
		varClassifyTableView.validate();
		// initialize statistics
		globalVariables = new Vector();
		globalRmse = new Vector();
		globalCorrcoef = new Vector();
		if(model.isTrained()){
			getModelStatistics(globalVariables, globalRmse, globalCorrcoef);
			if(modelRateValue>0.75){
				modelRate.setText(goodModel);
			}else if(modelRateValue>0.55){
				modelRate.setText(sosoModel);
			}else{
				modelRate.setText(badModel);
			}
		}
		statisticsTableModel.setContent(globalVariables,globalRmse,globalCorrcoef);
		statisticsTableView.validate();
	}

	private void getModelStatistics(Vector variables, Vector rmse, Vector corrcoef) {
		variables.addElement("TRAINING:");
		rmse.addElement(" ");
		corrcoef.addElement(" ");
		getModelStatistics(variables, rmse, corrcoef, TRAINING);
		variables.addElement(" ");
		rmse.addElement(" ");
		corrcoef.addElement(" ");
		variables.addElement("TESTING:");
		rmse.addElement(" ");
		corrcoef.addElement(" ");
		getModelStatistics(variables, rmse, corrcoef, TESTING);
	}

	private void getModelStatistics(Vector variables, Vector rmse, Vector corrcoef, int type) {
		Pls net = (Pls) model.getModel();
		getModelStatistics(net, rmse, corrcoef, type);
		Vector names = model.getOutputVarNames();
		for(int i=0;i<names.size();i++){
			variables.addElement(names.elementAt(i));
		}
	}

	private void getModelStatistics(Pls net, Vector rmse, Vector corrcoef, int type) {
		int digits = 4;
		int nout = net.getNout();
		double[] rmseAve = new double[nout];
		double[] corrAve = new double[nout];
		modelRateValue =0;
		for(int j=0;j<nout;j++) {
			rmseAve[j] = 0.0;
			corrAve[j] = 0.0;
			ValidationParameters VP = null;
			if(type==TESTING) {
				VP = net.testingResults;
			}else {
				VP = net.trainingResults;
			}
			rmseAve[j] += VP.rmse.get(j);
			corrAve[j] += VP.corrcoef.get(j);
		}
		for(int i=0;i<nout;i++) {
			rmse.addElement(Utilities.formatDouble(rmseAve[i], digits));
			corrcoef.addElement(Utilities.formatDouble(corrAve[i], digits));
			modelRateValue = modelRateValue+corrAve[i];
		}
		modelRateValue = modelRateValue/nout;
	}


	@Override
	public void trainingComplete(){
		globalVariables.removeAllElements();
		globalRmse.removeAllElements();
		globalCorrcoef.removeAllElements();
		if(model.isTrained()){
			getModelStatistics(globalVariables,globalRmse,globalCorrcoef);
			trainName.setText("Yes");
			if(modelRateValue>0.75){
				modelRate.setText(goodModel);
			}else if(modelRateValue>0.55){
				modelRate.setText(sosoModel);
			}else{
				modelRate.setText(badModel);
			}
		}
		statisticsTableModel.setContent(globalVariables,globalRmse,globalCorrcoef);
		statisticsTableView.repaint(0l);
		statisticsTableView.validate();
	}

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
				frame.showModelValidationWKSP(model);
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
				fileChooser.setDialogTitle("Export PLS Model Weights");
				NolFileFilter filter1 = new NolFileFilter(
				new String[] {"pls"}, "ASCII Model Weight File"
				);
				fileChooser.addChoosableFileFilter(filter1);
				fileChooser.setFileFilter(filter1);
				fileChooser.setDialogType(JFileChooser.SAVE_DIALOG);

				File currentDirectory = new File(NolMainFrame.miscDirectory);
				if(currentDirectory.exists()) {
					fileChooser.setCurrentDirectory(currentDirectory);
				}

				fileChooser.setSelectedFile(new File(model.getName()+".pls"));
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
					file = file+".pls";
				}

				try {
					model.writePLSWeightFile(directory,file);
				}catch (Exception evt) {
					frame.showOKDialog("Error in writing the weights.");
				}
				Toolkit.getDefaultToolkit().beep();
			} else if(command.equals("Export Training Data...")){
					try{
						long[] outputTime = null;
						Matrix Y = Matlib.createMatrix();
						Matrix X = Matlib.createMatrix();
						try{
							outputTime = model.prepareTrainingSet(X, Y);
						}catch (MathException evt){
							System.err.println("Non-Fatal exception: " + evt.getMessage());
							evt.printStackTrace();	
						}
						if(outputTime == null){
							// create fake times for plotting
							outputTime = new long[Y.getRows()];
							for(int r=0;r<outputTime.length;r++){
								outputTime[r] = (long)r*1000;
							}
						}
						if(X.getRows() <10){
							frame.showOKDialog("There is not enough data for training!");
							return;
						}
						Matlib.appendColumns(X,Y,X);
 						DataSeries ds = new DataSeries(X);
						ds.setName(model.getName());
						if(model.getHasTimeStamps()){
							ds.setTimeStamps(outputTime);
						}
						
						Preprocessor prep = model.getPreprocessor();
						Vector ins = model.getInputs();
						Vector inputDelays = model.getInputDelays();
						Vector outputDelays = model.getOutputDelays();
						Vector outs = model.getOutputs();
						int col = 0;

						for(int i=0;i<outs.size();i++){
							String varName = (String) outs.elementAt(i);
							Variable varObj = prep.getVariableFromVariableName(varName);
							String varTag = varObj.getTag();
							long[] delays = (long[]) outputDelays.elementAt(i);
							if(delays.length >= 1){
								for(int j=0;j<delays.length;j++){
									if(delays[j] > 0){
										String newVarName = varName + "_("+delays[j]+")";
										String newVarTag = varTag + "_("+delays[j]+")";
										ds.setVariableParameters(col,newVarTag,newVarName,"None");
										col++;
									}
								}
							}
						}
						for(int i=0;i<ins.size();i++){
							String varName = (String) ins.elementAt(i);
							Variable varObj = prep.getVariableFromVariableName(varName);
							String varTag = varObj.getTag();
							long[] delays = (long[]) inputDelays.elementAt(i);
							if(delays.length == 0){
								ds.setVariableParameters(col,varTag,varName,"None");
								col++;
							}else if(delays.length == 1){
								if(delays[0] >0){
									String newVarName = varName + "_("+delays[0]+")";
									String newVarTag = varTag + "_("+delays[0]+")";
									ds.setVariableParameters(col,newVarTag,newVarName,"None");
									col++;
								}else{
									ds.setVariableParameters(col,varTag,varName,"None");
									col++;
								}
							}else {
								for(int j=0;j<delays.length;j++){
									String newVarName = varName + "_("+delays[j]+")";
									String newVarTag = varTag + "_("+delays[j]+")";
									ds.setVariableParameters(col,newVarTag,newVarName,"None");
									col++;
								}
							}
						}
						for(int c=0;c<outs.size();c++){
							String varName = (String) outs.elementAt(c);
							Variable varObj = prep.getVariableFromVariableName(varName);
							String varTag = varObj.getTag();
							ds.setVariableParameters(col,varTag,varName,"None");
							col++;
						}
						frame.exportActionPerformed(ds);
						ds.clearMemory();  // this clears YPAll
						ds = null; 
   					}catch(MathException evt){
						evt.printStackTrace();
						Toolkit.getDefaultToolkit().beep();
						frame.showOKDialog("Error in saving data.");
						return;
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
				showLoadingChart();
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
					frame.getProjectTree().changePlsModelName(model,true);
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
	
	private void showLoadingChart(){
		try {
			NolInternalFrame activeInternalFrame = new NolPlsLoadingChartFrame(frame,model); 
			showChart(activeInternalFrame);
		} catch (MathException pe) {
			frame.showOKDialog(pe.getMessage());
		}
	}

	private void showChart(NolInternalFrame activeInternalFrame){
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
			}else if(c == 2){
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
//		private String[] colHd = {"Variable","RMSE","CORRCOEF"};
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

