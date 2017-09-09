package com.gensym.nols.wksp;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import javax.swing.*;
import javax.swing.table.*;
import javax.swing.event.*;
import javax.swing.border.*;

import com.gensym.nols.data.*;
import com.gensym.nols.main.*;
import com.gensym.nols.util.*;
import com.gensym.nols.dlg.*;

import com.gensym.math.Utilities;

public class NolDataSeriesSimulationWKSP  extends NolInternalFrame{
	private NolMainFrame frame;
	private JTextField simulationName;
	private JTextArea descriptArea;
	private JLabel modelName;
	private JLabel modelType;
	private int simulationIndex;
	private DataSeriesSimulation simulation;
	private Action actionListener;
 	
	private int digits = 5;
	private	JTextField caseName;
	private	JTextField dataName;

	private JList caseList;
	private DefaultListModel caseListModel;
	private Vector testDataSeriesIndex;

	public NolDataSeriesSimulationWKSP (NolMainFrame frame, int simulationIndex){
		super(frame.getProject().getTransformer(0));
		this.frame = frame;
		Project project = frame.getProject();
		project.getTransformer(0).addTransformerListener(this);
		this.simulationIndex = simulationIndex;
		simulation = (DataSeriesSimulation)project.getSimulation(simulationIndex);
		String title = "Simulation:["+simulation.getName()+"]";
		setTitle(title);
		actionListener = new ControlAction();
		initLayout();
		initDataDisplay();
	}

	private void initLayout(){
		JPanel workPane = new JPanel(new BorderLayout());
													    
		JPanel cenPane = new JPanel(new BorderLayout());

		JPanel infoPane = new JPanel(new BorderLayout());
		JPanel namePane = new JPanel(new GridLayout(2,4,10,10));
		namePane.setBorder(new EmptyBorder(12,12,10,12));
		namePane.add(new JLabel("Name:"));
		simulationName = new JTextField();
		namePane.add(simulationName);
		namePane.add(new JPanel());
		namePane.add(new JPanel());
		namePane.add(new JLabel("Model:"));
		modelName = new JLabel();
		namePane.add(modelName);

		namePane.add(new JLabel("Model Type:"));
		modelType = new JLabel();
		namePane.add(modelType);

		
		JPanel descriptPane = new JPanel(new GridLayout());
		descriptPane.setBorder(new TitledBorder(new EmptyBorder(7, 7, 7, 7),               
			"Comment:", TitledBorder.LEFT , TitledBorder.TOP));
		descriptArea = new JTextArea();
		descriptArea.getDocument().addDocumentListener((DocumentListener)actionListener);
		JScrollPane listScrollPane = new JScrollPane(descriptArea);
		listScrollPane.setBorder(BorderFactory.createLoweredBevelBorder());
		listScrollPane.setPreferredSize(NolMainFrame.vpad50); 
		descriptPane.add(listScrollPane);

		infoPane.add("North",namePane);
		infoPane.add("Center",descriptPane);

		JPanel sourcePane = new JPanel(new BorderLayout());
		sourcePane.setBorder(new EmptyBorder(5,5,5,5));

		JPanel caseNamePane = new JPanel(new GridLayout(1,4,5,5));
 		caseNamePane.setBorder(new EmptyBorder(5,5,15,5));
		caseNamePane.add(new JLabel("Preprocessor:"));
		caseName = new JTextField();
		caseName.addActionListener(actionListener);
		caseNamePane.add(caseName);
		caseNamePane.add(new JLabel("Data Series:"));
		dataName = new JTextField();
		dataName.addActionListener(actionListener);
		caseNamePane.add(dataName);

		JPanel listPane = new JPanel(new GridLayout());
		listPane.setBorder(new TitledBorder(new EmptyBorder(1, 1, 1, 1),               
			"Valid Preprocessors:", TitledBorder.LEFT , TitledBorder.TOP));

		caseList = new JList(getCaseListModel());
		caseList.setBackground(Color.white);
		caseList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		caseList.addListSelectionListener((ListSelectionListener)actionListener);
		listScrollPane = new JScrollPane(caseList);
		listScrollPane.setBorder(BorderFactory.createLoweredBevelBorder());
		listPane.add(listScrollPane);

		sourcePane.add("North",caseNamePane);
		sourcePane.add("Center",listPane);

		cenPane.add("North",infoPane);
		cenPane.add("Center",sourcePane);

		
		workPane.add("Center",cenPane);
		workPane.add("East",getControlPanel());
		setContentPane(workPane);

	}

	private JPanel getControlPanel(){
		JPanel control = new JPanel();
		control.setBackground(getContentPane().getBackground());
		control.setLayout(new BoxLayout(control, BoxLayout.Y_AXIS));
		control.setBorder(new EmptyBorder(10, 10, 10, 10));

		JPanel pane0 = new JPanel(new GridLayout(5,1,5,5));
		JButton but = new JButton("Spreadsheet...");
		but.addActionListener(actionListener);
  		pane0.add(but);
		but = new JButton("Line Chart...");
		but.addActionListener(actionListener);
  		pane0.add(but);
		but = new JButton("Delete");
		but.addActionListener(actionListener);
  		pane0.add(but);
		control.add(Box.createRigidArea(NolMainFrame.vpad15));
		control.add(pane0);
		control.add(Box.createRigidArea(NolMainFrame.vpad500));
		control.add(Box.createVerticalGlue());
		return control;
	}

 	private DefaultListModel getCaseListModel() {
		if (caseListModel == null) {
			caseListModel = new DefaultListModel();
		};	
		return caseListModel;
	}	
		

	private void initDataDisplay(){
		Project project = frame.getProject();
		simulationName.setText(simulation.getName());
		testDataSeriesIndex = new Vector();
		int mType = simulation.getModelType();
		int mIndex = simulation.getModelIndex();
		if(mType == 0){
			modelType.setText("Predictive");
			NolModel2 model = project.getPredictiveModel(mIndex);
			modelName.setText(model.getTransform()); 
		}else{
			modelType.setText("Optimization");
			NolOptimizeModel model = project.getOptimizationModel(mIndex);
			modelName.setText(model.getTransform()); 
		}
		descriptArea.setText(simulation.getComment());
		refreshDataSourceView();
		caseName.setText(simulation.getTransformer().getName());
		dataName.setText(simulation.getDataSeries().getName());
	}

	private void refreshDataSourceView(){
		Project project = frame.getProject();
		testDataSeriesIndex.removeAllElements();
		getCaseListModel().removeAllElements();
		int mType = simulation.getModelType();
		int mIndex = simulation.getModelIndex();

		if(mType == 0){
			NolModel2 model = project.getPredictiveModel(mIndex);
			Vector outs = model.getOutputs();
			Vector ins = model.getInputs();
			OfflineTransformer currentTfr = project.getTransformer(model.getCaseName());
			int dataSeriesIndex = model.getDataSeriesIndex();
			DataSeries ds = currentTfr.getDataSeries(dataSeriesIndex);
			int ntfr = project.getNumberOfTransformers();

			for(int i=1;i<ntfr;i++){
				boolean wrong = false;
				OfflineTransformer tfr = project.getTransformer(i);
				int nds = tfr.getNumberOfDataSeries();
				for(int j=0;j<nds;j++){
					DataSeries ddss = tfr.getDataSeries(j);
					if(model instanceof NolOptimizeModel){
					}else{
						for(int n=0;n<outs.size();n++){
							String na = outs.elementAt(n).toString();
							int vindex = ddss.getVariableNumberFromName(na);
							if(vindex == -1){
								wrong = true;
								break;
							}
						}
						for(int n=0;n<ins.size();n++){
							String na = ins.elementAt(n).toString();
							int vindex = ddss.getVariableNumberFromName(na);
							if(vindex == -1){
								wrong = true;
								break;
							}
						}
					}
					if(!wrong){
						getCaseListModel().addElement(tfr.getName());
						testDataSeriesIndex.addElement(new Integer(j));
						break;
					}
				}
			}
		}else{
			NolModel2 model = (NolModel2)project.getOptimizationModel(mIndex);		 //Gchen need modify if model types are more than two. 9/21/98
		}
	}

	private void refreshDisplay(){
		Rectangle rv = this.getBounds();
		this.setBounds(rv.x,rv.y,rv.width+1,rv.height);
		this.paintImmediately(rv.x,rv.y,rv.width+1,rv.height);
		this.validate();
		this.setBounds(rv.x,rv.y,rv.width,rv.height);
		this.validate();
	}

	public int getSimulationIndex(){
		return simulationIndex;
	}
	
/** The inner control listener class.*/
    class ControlAction extends AbstractAction implements DocumentListener, ListSelectionListener {
		ControlAction() {super("controlAction");}

        @Override
		public void actionPerformed(ActionEvent e) {
			String command = e.getActionCommand();
			if(command.equals("Spreadsheet...")){
				frame.spreadsheetActionPerformed(1, simulationIndex,0);
			}else if(command.equals("Line Chart...")){
			}else if(command.equals("Delete")){
			}
		}
		@Override
		public void changedUpdate(DocumentEvent e){}
		@Override
		public void insertUpdate(DocumentEvent e){
			String com = descriptArea.getText();
			simulation.setComment(com);
			if(NolMainFrame.DEBUG){
				System.out.println("get Document event insertUpdate");
			}
		}
		@Override
		public void removeUpdate(DocumentEvent e){
			String com = descriptArea.getText();
			simulation.setComment(com);
		}
		
		@Override
		public void valueChanged(ListSelectionEvent e){
		}
    }	
}

