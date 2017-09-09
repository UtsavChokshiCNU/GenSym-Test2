package com.gensym.nols.deploy;


import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.net.*;
import java.util.*;
import java.util.zip.*;

import javax.swing.*;
import javax.swing.border.*;
import javax.swing.event.*;
import javax.swing.table.*;

import com.gensym.nols.data.*;
import com.gensym.math.datafit.*;
import com.gensym.math.MathException;
/**
 * a class to display model information for nolstudio models
 *
 * @version	1.0 march 27,2003
 * @author Gang Chen
**/
public class ModelReader extends JFrame {

	private JTextPane Textpane;
	private JPanel controlPane;
	private JTextArea errText;
	private JTextField addressText;
	private ControlAction actionListener;
	private boolean confirmed;

	private JLabel nameField;
	private JLabel typeName;
	private JTextArea descriptArea;
	private JTextArea modelStructionDesciption;
	private JTextArea formulaDesciption;
	private int delayTimeUnit;

    private static String motif    = "com.sun.java.swing.plaf.motif.MotifLookAndFeel";
    private static String windows  = "com.sun.java.swing.plaf.windows.WindowsLookAndFeel";
	
	private	VarClassifyTableModel varClassifyTableModel;
	private	JTable varClassifyTableView;
	static final ModelReader reader = new ModelReader("Display Model Information");

	private String file = "";
	private String directory = "";

	private OnlineProcessor processor;
	private OnlineOptimizer optimizer;
	private int modelType = -1; //0: processor; 1: optimizer


	ModelReader(String title) {
		super(title);
		URL url = this.getClass().getResource("framelogo.gif");
		ImageIcon gensymLogo = new ImageIcon(url);
		setIconImage(gensymLogo.getImage());

		Container c = getContentPane();
        c.add("Center", getConsolePanel());
		actionListener = new ControlAction();
		c.add("East", getControlPanel());

		optimizer = new OnlineOptimizer();
		processor = new OnlineProcessor();
	}

	private JPanel getControlPanel(){
		JPanel control = new JPanel();
		control.setBackground(getContentPane().getBackground());
		control.setLayout(new BoxLayout(control, BoxLayout.Y_AXIS));
		control.setBorder(new EmptyBorder(10, 10, 10, 10));

		JPanel pane0 = new JPanel(new GridLayout(8,1,5,5));
		JButton but = new JButton("Browse...");
		but.setActionCommand("Browse...");
		but.addActionListener(actionListener);
  		pane0.add(but);
		but = new JButton("Load");
		but.setActionCommand("Load");
		but.addActionListener(actionListener);
  		pane0.add(but);
		but = new JButton("Exit");
		but.setActionCommand("Exit");
		but.addActionListener(actionListener);
  		pane0.add(but);

		control.add(Box.createRigidArea(new Dimension(1,15)));
		control.add(pane0);
		control.add(Box.createRigidArea(new Dimension(1,500)));
		control.add(Box.createVerticalGlue());
		return control;
	}


	private JPanel getConsolePanel(){
		JPanel centerPane = new JPanel(new BorderLayout());
		JPanel addressPane = new JPanel(new GridLayout());
		addressText = new JTextField();
		addressPane.add(addressText);
		addressPane.setBorder(new TitledBorder("Model Address:"));
		centerPane.add("North", addressPane);
		centerPane.setBorder(new EmptyBorder(10,10,10,10));
		centerPane.add("Center", getModelPanel());
		return centerPane;
	}

	private JTabbedPane getModelPanel(){
		JTabbedPane detailedTabbedPane = new JTabbedPane();
		detailedTabbedPane.addTab("General", getGeneralPanel());
		detailedTabbedPane.setSelectedIndex(0);
		detailedTabbedPane.addTab("Variable", getVariablePanel());
		detailedTabbedPane.addTab("Structure", getStructurePanel());
		detailedTabbedPane.addTab("Formulas", getFormulaPanel());
		return detailedTabbedPane;
	}

	private JPanel getGeneralPanel(){
		JPanel infoPane = new JPanel(new BorderLayout());
		JPanel namePane = new JPanel(new GridLayout(2,2,10,5));
		namePane.setBorder(new EmptyBorder(10,10,10,10));
		namePane.add(new JLabel("Name:"));
		nameField = new JLabel();
		namePane.add(nameField);
		namePane.add(new JLabel("Model Type:"));
		typeName = new JLabel();
		namePane.add(typeName);

		JPanel descriptPane = new JPanel(new GridLayout());
		descriptPane.setBorder(new TitledBorder(new EmptyBorder(1, 1, 1, 1),               
			"Comment:", TitledBorder.LEFT , TitledBorder.TOP));
		descriptArea = new JTextArea();
		descriptArea.getDocument().addDocumentListener((DocumentListener)actionListener);
		JScrollPane listScrollPane = new JScrollPane(descriptArea);
		listScrollPane.setBorder(BorderFactory.createLoweredBevelBorder());
		listScrollPane.setPreferredSize(new Dimension(1,40)); 
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

	private JPanel getStructurePanel(){
		JPanel strutPane = new JPanel(new GridLayout());
		JPanel infoPane = new JPanel(new GridLayout());
 		infoPane.setBorder(new EtchedBorder(EtchedBorder.LOWERED));
		modelStructionDesciption = new JTextArea();
		modelStructionDesciption.setEditable(false);
		infoPane.add(modelStructionDesciption);
		JPanel cenPane = new JPanel(new GridLayout());
 		cenPane.add(infoPane);
		cenPane.setBorder(new EmptyBorder(10,10,10,10));
		strutPane.add(cenPane);
		return strutPane;
	}
	
	private JPanel getFormulaPanel(){
		JPanel formulaPane = new JPanel(new GridLayout());
		JPanel infoPane = new JPanel(new GridLayout());
 		infoPane.setBorder(new EtchedBorder(EtchedBorder.LOWERED));
		formulaDesciption = new JTextArea();
		formulaDesciption.setEditable(false);
		infoPane.add(formulaDesciption);
		JPanel cenPane = new JPanel(new GridLayout());
 		cenPane.add(infoPane);
		cenPane.setBorder(new EmptyBorder(10,10,10,10));
		formulaPane.add(cenPane);
		return formulaPane;
	}
	

	
	private void setDataDisplay(){
		INolModel2 model;
		if(modelType == 0){	
			model = processor.getModel();
		}else if(modelType == 1){
			model = optimizer.getModel();
		}else{
			return;
		}
		
		nameField.setText(model.getName());
		descriptArea.setText(model.getComment());
		if(model instanceof NolOptimizeModel){
			typeName.setText("Optimization Model");
		}else{
			typeName.setText("Predictive Model");
		}
		
		Vector names = new Vector();
		Vector delays = new Vector();
		Vector classification = new Vector();

		double divide = 60000;
		if(delayTimeUnit == 1) {
			divide = 3600000;
		}else if(delayTimeUnit == 3) {
			divide = 1000;
		}

		boolean hasTwoEnsambles = false;
		if(model instanceof NolOptimizeModel){
			if(((NolOptimizeModel)model).getStateModel() != null){
				hasTwoEnsambles = true;
			}
		}

		if(hasTwoEnsambles){
			names.addElement("Output Model:");
			classification.addElement(" ");
			delays.addElement(" ");
		}
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
		EnsembleModel ensemble = (EnsembleModel) model.getModel();
		if(hasTwoEnsambles){
			names.addElement(" ");  // add empty row
			classification.addElement(" ");
			delays.addElement(" ");
			names.addElement("State Model:");
			classification.addElement(" ");
			delays.addElement(" ");

			NolOptimizeModel optModel = (NolOptimizeModel) model;
			Vector states = optModel.getState();
			Vector manis = optModel.getManipulate();			
			Vector exogs = optModel.getExogenous();

			for(int i=0;i<states.size();i++){
				names.addElement(states.elementAt(i));
				classification.addElement("State");
			}
			for(int i=0;i<manis.size();i++){
				names.addElement(manis.elementAt(i));
				classification.addElement("Manipulate");
			}
			for(int i=0;i<exogs.size();i++){
				names.addElement(exogs.elementAt(i));
				classification.addElement("Exogenous");
			}
			Vector stateModelDelays = new Vector(0,10);
			Vector stateDelays = optModel.getStateDelays();
//			System.out.println("stateDelays size="+stateDelays.size());
			for(int i=0;i<stateDelays.size();i++) {
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
			Vector stateInputDelays = optModel.getStateInputDelays();
//			System.out.println("stateInputDelays size="+stateInputDelays.size());
			for(int i=0;i<stateInputDelays.size();i++) {
				long[] dls = (long[])stateInputDelays.elementAt(i);
//			System.out.println("dls.length="+dls.length);
				for(int j=0;j<dls.length;j++){
					double dd = dls[j]/divide;
					delays.addElement(String.valueOf(dd));
				}
			}
			EnsembleModel ensemble2 = (EnsembleModel)optModel.getStateModel();
			if(model.isTrained() && ensemble2!=null){
				String description = "OUTPUT MODEL:\n"+ensemble.getDescription();
				if(ensemble2 != null) {
					description = description+"\nSTATE MODEL:\n"+ensemble2.getDescription();
				}
				modelStructionDesciption.setText(description);
			}
		}else{
			modelStructionDesciption.setText(ensemble.getDescription());
		}
System.out.println("names.length="+names.size());
		varClassifyTableModel.setContent(names,delays,classification);
		varClassifyTableView.setModel(varClassifyTableModel);
		varClassifyTableView.validate();
		varClassifyTableView.repaint(0L);
		if(modelType == 0){ 
			try{
			formulaDesciption.setText(processor.getFormulas());
			}catch (MathException e){}
		}else{
			formulaDesciption.setText("No formula for optimization model.");
		}
		refreshFrame();

/*		// initialize statistics
		Vector variables = new Vector();
		Vector rmse = new Vector();
		Vector corrcoef = new Vector();
		if(model.isTrained()){
			getModelStatistics(variables, rmse, corrcoef);
			if(modelRateValue>0.75){
				modelRate.setText(goodModel);
			}else if(modelRateValue>0.55){
				modelRate.setText(sosoModel);
			}else{
				modelRate.setText(badModel);
			}
		}
		statisticsTableModel.setContent(variables,rmse,corrcoef);
		statisticsTableView.validate();
*/
	}

	private void refreshFrame(){
		Rectangle bs = getBounds();
		setBounds(bs.x, bs.y, bs.width+1,bs.height);
		validate();
		repaint(0L);
		setBounds(bs.x, bs.y, bs.width,bs.height);
		validate();
		repaint(0L);
	}



	class ControlAction extends AbstractAction {
		ControlAction() {
		}

        @Override
		public void actionPerformed(ActionEvent event) {
			String command = event.getActionCommand();
			if(command.equals("Browse...")){
				FileDialog fileDialog = new FileDialog(reader);
				fileDialog.setMode(FileDialog.LOAD);
				fileDialog.setFile("*.mod");
				fileDialog.setLocation(200,200);
				fileDialog.setModal(true);
				fileDialog.setVisible(true);
				fileDialog.toFront();

				file = fileDialog.getFile();
				directory = fileDialog.getDirectory();
				if (file == null){
					return;
				}else{
					addressText.setText(directory+file);
				}
			}else if(command.equals("Exit")){
				System.exit(0);
			}else if(command.equals("Load")){
				if("".equals(file)){
					return;
				}
				try{
					File sourceFile;
					if(directory==null)
						sourceFile = new File(file);	
					else
						sourceFile = new File(directory,file);
					FileInputStream fis = new FileInputStream(sourceFile); 
					GZIPInputStream gzis = new GZIPInputStream(fis);   
					ObjectInputStream in = new ObjectInputStream(gzis);
					Object ver = in.readObject();
					String className = ver.getClass().getName();
					if(className.equals("com.gensym.nols.data.VersionManagerForOnlineProcessor")) {
						OnlineProcessor olp = ((VersionManagerForOnlineProcessor)ver).getProcessor();
						processor.copyToThis(olp);
						modelType = 0;
					}else if (className.equals("com.gensym.nols.data.VersionManagerForOnlineOptimizer")) {
						OnlineOptimizer opt = ((VersionManagerForOnlineOptimizer)ver).getOptimizer();
						optimizer.copyToThis(opt);
						modelType = 1;
					}
					in.close(); 
				}catch (Exception evt) { 
					System.err.println("Non-Fatal exception: " + evt.getMessage());
					evt.printStackTrace();
				}
				setDataDisplay();
			}
		}
    }

	private void showModel(String modelName){

	}

	public static void main(String[] args) {
		String os = System.getProperty("os.name");		
		String currentLF = windows;
		if(os.indexOf("Win") == -1){
			currentLF = motif;
		}
		try {
			UIManager.getLookAndFeel();  // this is to work around some swing problems.
			UIManager.setLookAndFeel(currentLF);
		} catch (Throwable t) {
			System.err.println(t.toString());
			return;
		}

		String vers = System.getProperty("java.version");		
		if (vers.compareTo("1.1.7") < 0) {
			System.out.println("!!!WARNING: Swing must be run with a " +
				"1.1.7 or higher version VM!!!");
		}
		 
		if(args.length == 1){
			reader.showModel(args[0]);
		}
		reader.setBounds(100,100,450,400);
		reader.setVisible(true);
    }
	class VarClassifyTableModel extends AbstractTableModel{
		private int row,col;
		private Vector names, delays, classification;
		private String[] colHd = {"Variable","Classification","Delay"};
		
		public VarClassifyTableModel(){
			row = 0;
			col = 3;
		}

		public void setContent(Vector names, Vector delays, Vector classification){
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
			}else if(c == 1){
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

}
