package com.gensym.nols.wksp;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.io.*;
import java.lang.reflect.*;
import javax.swing.*;
import javax.swing.table.*;
import javax.swing.event.*;
import javax.swing.border.*;

import com.gensym.math.datafit.*;
import com.gensym.math.matrix.*;
import com.gensym.math.*;
import com.gensym.nols.data.*;
import com.gensym.nols.dlg.*;
import com.gensym.nols.deploy.*;
import com.gensym.nols.main.*;

import com.gensym.DEBUG;

public class NolModelWKSP  extends NolInternalFrame 
	implements ModelTrainerListener{
	
	protected static final String MODELWKSP_NAME = "NameLabel";
    protected static final String MODELWKSP_COMMENT = "CommentLabel";
    protected static final String MODELWKSP_TYPE= "ModelWKSP_Type";
    protected static final String MODELWKSP_PREPROCESSOR = "ModelWKSP_Preprocessor";
    protected static final String MODELWKSP_TRAINED = "ModelWKSP_Trained";
    protected static final String MODELWKSP_CONTINUETRAINING = "ModelWKSP_ContinueTraining";
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

	
	private NolModel2 model;
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

	public NolModelWKSP (NolMainFrame frame, NolModel2 model){
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

		JPanel pane0 = new JPanel(new GridLayout(8,1,5,5));
		JButton but = new JButton(frame.getNolResourceString(MODELWKSP_CONTINUETRAINING));
		but.setActionCommand("Continue Training...");
		but.addActionListener(actionListener);
  		pane0.add(but);
		but = new JButton(frame.getNolResourceString(MODELWKSP_VALIDATE));
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
		dataBut = new JButton(frame.getNolResourceString(MODELWKSP_EXPORTDATA));
		dataBut.setActionCommand("Export Training Data...");
		dataBut.addActionListener(actionListener);
  		pane0.add(dataBut);
		but = new JButton(frame.getNolResourceString(MODELWKSP_PREDVSACTUAL));
		but.setActionCommand("Predicted vs Actual...");
		but.addActionListener(actionListener);
  		pane0.add(but);
		
//		if(DEBUG.more){
//		but = new JButton(frame.getNolResourceString(MODELWKSP_LOCALSENSITIVITY));
//		but.setActionCommand("Local Sensitivity...");
//		but.addActionListener(actionListener);
//		pane0.add(but);
		but = new JButton(frame.getNolResourceString(MODELWKSP_GLOBALSENSITIVITY));
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

	public NolModel2 getModel(){
		return model;
	}

	public void initDataDisplay(){
		nameField.setText(model.getName());
		caseName.setText(model.getPreprocessor().getName());
		descriptArea.setText(model.getComment());
		if(model instanceof NolOptimizeModel){
			typeName.setText("Optimization Model");
			weightBut.setEnabled(false);
			exportBut.setEnabled(false);
		}else{
			typeName.setText("Predictive Model");
			weightBut.setEnabled(true);
			exportBut.setEnabled(true);
		}
		if(frame.isDemoVersion()){
			weightBut.setEnabled(false);
			exportBut.setEnabled(false);
		}		
		if(model.isTrained()){
			trainName.setText("Yes");
		}else{
			trainName.setText("No");
		}
		Vector names = new Vector();
		Vector delays = new Vector();
		Vector classification = new Vector();

		double divide = 60000;
		if(delayTimeUnit == 1){
			divide = 3600000;
		}else if(delayTimeUnit == 3){
			divide = 1000;
		}

		boolean hasTwoEnsambles = false;
		EnsembleModel ensemble = (EnsembleModel) model.getModel();
		if(model instanceof NolOptimizeModel){
			if(((NolOptimizeModel)model).getStateModel() != null){
				hasTwoEnsambles = true;
			}
			NolOptimizeModel optModel = (NolOptimizeModel) model;
			names.addElement("Output Model:");
			classification.addElement(" ");
			delays.addElement(" ");

			Vector outs = model.getOutputs();
			int nout = outs.size();
			Vector outDelays = model.getOutputDelays();
			Vector ins = model.getInputs();
			Vector inDelays = model.getInputDelays();
			
			Vector states = optModel.getState();
			Vector manis = optModel.getManipulate();			
			Vector exogs = optModel.getExogenous();

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
			for(int i=0;i<inDelays.size();i++){
				long[] dls = (long[])inDelays.elementAt(i);
				for(int j=0;j<dls.length;j++){
					double dd = dls[j]/divide;
					delays.addElement(String.valueOf(dd));
					String name = (String)ins.elementAt(i);
					names.addElement(name);
					if(states.contains(name)){
						classification.addElement("State");
					}else if(manis.contains(name)){
						classification.addElement("Manipulate");
					}else if(exogs.contains(name)){
						classification.addElement("Exogenous");
					}
				}
			}
			
			if(hasTwoEnsambles){
				names.addElement(" ");  // add empty row
				classification.addElement(" ");
				delays.addElement(" ");
				names.addElement("State Model:");
				classification.addElement(" ");
				delays.addElement(" ");

				Vector stateModelDelays = new Vector(0,10);
				Vector stateDelays = optModel.getStateDelays();
				
				Vector stateins = optModel.getStateInput();
 				Vector stateInputDelays = optModel.getStateInputDelays();

				for(int i=0;i<states.size();i++){
					names.addElement(states.elementAt(i));
					classification.addElement("State");
					long[] dls = (long[])stateDelays.elementAt(i);
	//			System.out.println("dls.length="+dls.length);

					if(dls.length == 0){
							delays.addElement("0");
					}else{
						for(int j=0;j<dls.length;j++){
							double dd = dls[j]/divide; 
							delays.addElement(String.valueOf(dd));
						}
					}
				}

				for (int i = 0; i < stateins.size(); i++) {
					String name = (String) stateins.elementAt(i);
					String classificationString = "";
					if (manis.contains(name)) {
						classificationString = "Manipulate";
					} else if(exogs.contains(name)) {
						classificationString = "Exogenous";
					}
					long[] dls = (long[]) stateInputDelays.elementAt(i);
					for (int j = 0; j < dls.length; j++) {
						names.addElement(name);
						classification.addElement(classificationString);
						double dd = dls[j] / divide;
						delays.addElement(String.valueOf(dd));
					}
				}
				EnsembleModel ensemble2 = (EnsembleModel)optModel.getStateModel();
				if(model.isTrained() && ensemble2!=null){
					String description = "OUTPUT MODEL:\n"+ensemble.getDescription();
					if(ensemble2 != null){
						description = description+"\nSTATE MODEL:\n"+ensemble2.getDescription();
					}
					modelStructionDesciption.setText(description);
				}
			}else{
				modelStructionDesciption.setText(ensemble.getDescription());
			}
		}else{
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
			modelStructionDesciption.setText(ensemble.getDescription());
		}
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
		EnsembleModel ensemble = (EnsembleModel) model.getModel();
		getModelStatistics(ensemble, rmse, corrcoef, type);
		Vector names = model.getOutputVarNames();
		for(int i=0;i<names.size();i++) {
			variables.addElement(names.elementAt(i));
		}
		if(model instanceof NolOptimizeModel) {
			NolOptimizeModel optModel = (NolOptimizeModel) model;
			ensemble =  (EnsembleModel) optModel.getStateModel();
			if(ensemble != null) {
				getModelStatistics(ensemble, rmse, corrcoef, type);
				names = optModel.getState();
				for(int i=0;i<names.size();i++) {
					variables.addElement(names.elementAt(i));
				}
			}
		}
	}

	private void getModelStatistics(EnsembleModel ensemble, Vector rmse, Vector corrcoef, int type) {
		int digits = 4;
		int ensembleSize = ensemble.size();
		int nout = ensemble.getNout();
		double[] rmseAve = new double[nout];
		double[] corrAve = new double[nout];
		modelRateValue =0;
		for(int j=0;j<nout;j++) {
			rmseAve[j] = 0.0;
			corrAve[j] = 0.0;
			for (int i = 0; i < ensembleSize; i++) {
				TrainableModel submodel = (TrainableModel) ensemble.getModel(i);
				ValidationParameters VP = null;
				if(type==TESTING) {
					VP = submodel.testingResults;
				}else {
					VP = submodel.trainingResults;
				}
				rmseAve[j] += VP.rmse.get(j);
				corrAve[j] += VP.corrcoef.get(j);
			}
			rmseAve[j] /= ensembleSize;
			corrAve[j] /= ensembleSize; 
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
			if(command.equals("Continue Training...")){
				frame.getTrainDialog().setModel(model);
				frame.getTrainDialog().setVisible(true);				
			}else if(command.equals("Validate...")){
				if(!model.isTrained()){
					frame.showOKDialog("Cannot validate a untrained model.");
					return;
				}
				frame.showModelValidationWKSP(model);
			}else if(command.equals("Export...")){
				if(!model.isTrained()){
					frame.showOKDialog("Cannot export a untrained model.");
					return;
				}

				JFileChooser fileChooser = new JFileChooser();
				fileChooser.setDialogTitle("Export Model");
				NolFileFilter filter1 = new NolFileFilter(
					new String[] {"mod"}, "Binary Model File"
				);
				fileChooser.addChoosableFileFilter(filter1);
				NolFileFilter filter2 = new NolFileFilter(
					new String[] {"xml"}, "Extensible Markup Language File"
				);
				fileChooser.addChoosableFileFilter(filter2);
				
				fileChooser.setFileFilter(filter1);
				fileChooser.setDialogType(JFileChooser.SAVE_DIALOG);

				File currentDirectory = new File(NolMainFrame.miscDirectory);
				if(currentDirectory.exists()) {
					fileChooser.setCurrentDirectory(currentDirectory);
				}

				fileChooser.setSelectedFile(new File(model.getName()+".mod"));
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
				fileChooser.removeChoosableFileFilter(filter1);
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
				int type = 0; // mod=0; xml=1. 
				
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
					}else if(suff.equals(".mod")){
						type = 0;
					}
				}
				
				if(type == 0){
					OnlineProcessor processor = null;
					try{
						if(model.isAutoRecursiveModel()){
							processor = new OnlineAutoRecusiveProcessor(pName,model.getPreprocessor(),model);
						}else{
							processor = new OnlineProcessor(pName,model.getPreprocessor(),model);
						}
					}catch(MathException evt){
						Toolkit.getDefaultToolkit().beep();
						frame.showOKDialog("Error in making the online processor.");
						return;
					}
					try {
						Class versionManagerClass = Class.forName("com.gensym.nols.data.VersionManagerForOnlineProcessor");
						Object versionManager = versionManagerClass.newInstance();
						Method method = versionManagerClass.getMethod("setProcessor",new Class[] {Class.forName("com.gensym.nols.deploy.OnlineProcessor")});
						method.invoke(versionManager,new Object[] {processor});
						method = versionManagerClass.getMethod("saveToFile",new Class[] {directory.getClass(), file.getClass()});
						method.invoke(versionManager,new Object[] {directory, file});
					} catch (Exception ex) {
						frame.showOKDialog("Cannot save models without a valid software license. Exception = "+ex.getMessage());
					}
				}else if (type == 1){
//					System.out.println("export xml file");
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
				} catch (ClassNotFoundException ex) {
					frame.showOKDialog("Cannot save models without a valid software license.");
					return;
				} catch (RuntimeException ex) {
					frame.showOKDialog("Cannot save models without a valid software license.");
					return;
				}
 				JFileChooser fileChooser = new JFileChooser();
				fileChooser.setDialogTitle("Export Model Weights");
				NolFileFilter filter1 = new NolFileFilter(
				new String[] {"wgt"}, "ASCII Model Weight File"
				);
				fileChooser.addChoosableFileFilter(filter1);
				fileChooser.setFileFilter(filter1);
				NolFileFilter filter2 = new NolFileFilter(
					new String[] {"pls"}, "Partial Least Square Weight File"
				);
//				fileChooser.addChoosableFileFilter(filter2);
				fileChooser.setDialogType(JFileChooser.SAVE_DIALOG);

				File currentDirectory = new File(NolMainFrame.miscDirectory);
				if(currentDirectory.exists()) {
					fileChooser.setCurrentDirectory(currentDirectory);
				}

				fileChooser.setSelectedFile(new File(model.getName()+".wgt"));
				fileChooser.setLocation(200,200);			
				int retval = fileChooser.showSaveDialog(frame);

				String defaultExt = ".wgt";
				javax.swing.filechooser.FileFilter activeFilter = fileChooser.getFileFilter();
				if (activeFilter != null){
					if (activeFilter.equals(filter2)){
						defaultExt = ".pls";
					}
				}				 
				
				if(retval == JFileChooser.CANCEL_OPTION){
					return;
				}
				File currentPath = fileChooser.getSelectedFile();
				if(currentPath == null){
					return;
				}

				fileChooser.setFileFilter(null);
				fileChooser.removeChoosableFileFilter(filter1);
//				fileChooser.removeChoosableFileFilter(filter2);


				String file = currentPath.getName();
				String directory = currentPath.getParent();

				// try to start writing
				int dotInd = file.indexOf(".");
				int type = 0; // normal weight=0; pls weights =1; 

				if(dotInd == -1){
					file = file+defaultExt;
					if(defaultExt.equals(".pls")){
						type = 1;
					}else if(defaultExt.equals(".wgt")){
						type = 0;
					}
				}else{
					String suff = file.substring(dotInd);
					if(suff.equals(".pls")){
						type = 1;
					}else if(suff.equals(".wgt")){
						type = 0;
					}
				}

				EnsembleModel ensemble = (EnsembleModel)model.getModel();
				try {
					if(type == 0 ){
						ensemble.writeWeightFile(directory,file);
					}else if(type == 1 ){
						ensemble.writePLSWeightFile(directory,file);
					}
				} catch (IOException evt) {
					frame.showOKDialog("Error in writing the weights.");
				}  catch (MathException evt) {
					frame.showOKDialog("Error in writing the weights.");
				}  catch (RuntimeException evt) {
					frame.showOKDialog("Error in writing the weights.");
				}
				Toolkit.getDefaultToolkit().beep();
			} else if(command.equals("Export Training Data...")){
				if(model instanceof NolOptimizeModel) {
/*					NolOptimizeModel optModel = (NolOptimizeModel) model;
					if(Y != null)
						Matlib.clear(Y);
					if(X != null)
						Matlib.clear(X);
					Y = Matlib.createMatrix();
					X = Matlib.createMatrix();
					if(D != null)
						Matlib.clear(D);
					if(I != null)
						Matlib.clear(I);
					D = Matlib.createMatrix();
					I = Matlib.createMatrix();
					try{
						model.prepareTrainingSet(X, Y);
						if(DEBUG.debug){
							System.out.println("X.getCols="+X.getCols());
							System.out.println("Y.getCols="+Y.getCols());
						}
					} catch(MathException evt){
						System.err.println("Non-fatal exception preparing training data: "+evt.getMessage());
						evt.printStackTrace();
						return false;
					}

					if(X.getRows() <10){
						frame.showOKDialog(frame.getNolResourceString(NODATAFORTRAINING));
		//				frame.showOKDialog("There is not enough data for training.");
						return false;
					}	
					double minutes = 30.0;
					try{
						if(optModel.getStateModel() != null){
							minutes = Double.valueOf(trainTime1.getText()).doubleValue();
						}else{
							minutes = Double.valueOf(trainTime0.getText()).doubleValue();
						}
					}catch (NumberFormatException evt){
						frame.showOKDialog(frame.getNolResourceString(ERRORINTIME));
		//				frame.showOKDialog("Error in time value");
						return false;
					}

					int timeInMilli = (int)(minutes*60000.0); 
					EnsembleModel net1 = (EnsembleModel) optModel.getModel();
					net1.setTrainingTime(timeInMilli);  // convert minutes to milliseconds
					if(optModel.getStateModel() != null){
						net1.useAutomaticStopping(autoStopCheckBox1.isSelected());
					}else{
						net1.useAutomaticStopping(autoStopCheckBox0.isSelected());
					}
					net1.removeAllListeners();
					net1.addListener(consoleFrame);
					consoleFrame.setModel(model);
					consoleFrame.setModel1TrainInput(X);
					consoleFrame.setModel1TrainOutput(Y);
					if(trainerThread == null){
						trainerThread = new NolModelTrainThread(net1);
						trainerThread.addListener(this);
					}else{ 
						trainerThread.setEnsembleModel1(net1);
						trainerThread.removeListener(this);
						trainerThread.addListener(this);
					}
					trainerThread.setInput1(X);
					trainerThread.setOutput1(Y);
					
					if(optModel.getStateModel() != null){
						try{
							optModel.prepareTrainingSet2(I, D);
						} catch(MathException evt){
							System.err.println("Non-fatal exception preparing training data: "+evt.getMessage());
							evt.printStackTrace();
							return false;
						}
						if(D.getRows()<10){
							frame.showOKDialog(frame.getNolResourceString(NODATAFORTRAINING));
		//					frame.showOKDialog("There is not enough data for training.");
							return false;
						}
						EnsembleModel net2 = (EnsembleModel) optModel.getStateModel();
						try{
							minutes = Double.valueOf(trainTime2.getText()).doubleValue();
						}catch (NumberFormatException evt){
		//					frame.showOKDialog("Error in time value");
							frame.showOKDialog(frame.getNolResourceString(ERRORINTIME));
							return false;
						}
						timeInMilli = (int)(minutes*60000.0); 
						net2.setTrainingTime(timeInMilli);  // convert minutes to milliseconds
						net2.useAutomaticStopping(autoStopCheckBox2.isSelected());
						net2.removeAllListeners();
						net2.addListener(consoleFrame);
						consoleFrame.setModel2TrainInput(I);
						consoleFrame.setModel2TrainOutput(D);
						trainerThread.setEnsembleModel2(net2);
						trainerThread.setInput2(I);
						trainerThread.setOutput2(D);			
					}
					Thread trainingthread = new Thread(trainerThread);
					consoleFrame.setOutputModelTrainingThread(trainingthread);
					int prior = trainingthread.getPriority()-3;
					if(prior <Thread.MIN_PRIORITY) prior = Thread.MIN_PRIORITY;
					trainingthread.setPriority(prior);
					trainingthread.start();
*/
				}else{	
					try{
						long[] outputTime = null;
						Matrix Y = Matlib.createMatrix();
						Matrix X = Matlib.createMatrix();
						try{
							outputTime = model.prepareTrainingSet(X, Y, false);
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
				if(DEBUG.debugFlag){
					System.out.println("Delete modelWKSP");
				}
				frame.removeModel(model);
			}else if(command.equals("Predicted vs Actual...")){
				if(!model.isTrained()){
					frame.showOKDialog("Cannot calculate prediction with a untrained model.");
					return;
				}
				setWaitCursor(true);  // launch could take a while, so indicate with hourglass
				if(model.isAutoRecursiveModel()){
//System.out.println("show auto recursive wksp");
					frame.showRecursivePredVsActWKSP(model);
				}else{
					frame.showModelPredVsActWKSP(model);
				}
				setWaitCursor(false);
			}else if(e.getSource().equals(nameField)){
				String nm = nameField.getText();
				if(nm.length() > 0){
					model.setName(nm);
					String title = "Model:["+model.getName()+"]";
					setTitle(title);
					if(model instanceof NolOptimizeModel){
						frame.getProjectTree().changeOptimizationModelName((NolOptimizeModel)model,true);
					}else{
						frame.getProjectTree().changePredictiveModelName(model,true);
					}
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


	class VarClassifyTableModel extends AbstractTableModel {
		private int row,col;
		private Vector names, delays, classification;

		private String[] colHd = {
				frame.getNolResourceString(MODELWKSP_VARIABLES),
				frame.getNolResourceString(MODELWKSP_CLASSIFICATION),
				frame.getNolResourceString(MODELWKSP_DELAY)};
		
		public VarClassifyTableModel() {
			row = 0;
			col = 3;
		}

		public void setContent(Vector names, Vector delays,
				Vector classification) {
			this.names = names;
			this.delays = delays;
			this.classification = classification;
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

	public VarClassifyTableModel getVarClassifyTableModel() {
		return varClassifyTableModel;
	}
}

