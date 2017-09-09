package com.gensym.nols.dlg;

import java.awt.*;
import java.awt.event.*;
import java.util.*;

import javax.swing.*;
import javax.swing.border.*;

import com.gensym.nols.main.*;
import com.gensym.nols.data.*;
 
public class NolModelValidateChoiceDialog extends JDialog {
	private NolMainFrame frame;
	protected JList choiceList;
	private JButton okButton, cancelButton;
	private boolean isOk;
	private boolean hasValidData;
	private MainAction actionListener;
//	private NolModel2 model;
	private Vector origDataSeries;
	private Vector availableDataSeries;
	private Vector validateChoices;
	private Vector validateDataSeries;
	private JPanel choicePane;
	private boolean nofire = false;
//	private Preprocessor validatePreprocessor;

    
	private static final String INFOR_LABEL = "ModelValidateChoiceDialog_InforLabel";
    private static final String OK_BUTTON_LABEL = "OkButtonLabel";
    private static final String CANCEL_BUTTON_LABEL = "CancelButtonLabel";
	private static final String TRAINFROM = "ModelValidateChoiceDialog_TrainFrom";
	private static final String VALIDATEON = "ModelValidateChoiceDialog_ValidateOn";

	public NolModelValidateChoiceDialog(JFrame dw, String title) {
		super(dw, title, true);
        frame = (NolMainFrame)dw;
		actionListener = new MainAction();
		isOk = false;
		hasValidData = false;
		initializeLayout();
	}
	
	public void setContent(Vector origData, Vector availableData) {
		origDataSeries = origData;
		availableDataSeries = availableData;
		validateChoices = new Vector();
		refreshDialog();
		pack();
	}


	private void initializeLayout(){ 
		JPanel infoPane = new JPanel(new GridLayout());
 		infoPane.setBorder(new EmptyBorder(10,0,10,0));
		String s = frame.getNolResourceString(INFOR_LABEL);
		JTextArea infoLabel = new JTextArea(s);
		infoLabel.setEditable(false);
		infoLabel.setLineWrap(true);
		infoLabel.setWrapStyleWord(true);
		infoLabel.setBackground(infoPane.getBackground());
		infoPane.add(infoLabel);

		choicePane = new JPanel();
		choicePane.setBackground(Color.white);
		JScrollPane listScrollPane = new JScrollPane(choicePane);
		listScrollPane.setBorder(BorderFactory.createLoweredBevelBorder());

		// now put it all together
		JPanel cenPane = new JPanel(new BorderLayout());
 		cenPane.setBorder(new EmptyBorder(10, 10, 10, 10));
		cenPane.add("North", infoPane);
		cenPane.add("Center", listScrollPane);
		getContentPane().setLayout(new BorderLayout());
		getContentPane().add("Center", cenPane);
		getContentPane().add("East", getControlPane());
	}

	private JPanel getControlPane(){
		JPanel control = new JPanel();
		control.setBackground(getContentPane().getBackground());
		control.setLayout(new BoxLayout(control, BoxLayout.Y_AXIS));
		control.setBorder(new EmptyBorder(10, 10, 10, 10));

		JPanel pane0 = new JPanel(new GridLayout(2,1,5,5));
		okButton = new JButton(frame.getNolResourceString(OK_BUTTON_LABEL));
		okButton.setActionCommand("OK");
		cancelButton = new JButton(frame.getNolResourceString(CANCEL_BUTTON_LABEL));
		cancelButton.setActionCommand("Cancel");
		okButton.addActionListener(actionListener);
		cancelButton.addActionListener(actionListener);
		pane0.add(okButton);
		pane0.add(cancelButton);
		control.add(Box.createRigidArea(NolMainFrame.vpad15));
		control.add(pane0);
		control.add(Box.createRigidArea(NolMainFrame.vpad500));
		control.add(Box.createVerticalGlue());
		return control;
	}

	public void refreshDialog() {
		nofire  = true;
		int n = origDataSeries.size();
		choicePane.removeAll();
		choicePane.setLayout(null);
		choicePane.setSize(300,n*20+20);
		BorderedTextField train = new BorderedTextField(frame.getNolResourceString(TRAINFROM));
		train.setBounds(0,0,150,20);
		choicePane.add(train);
		BorderedTextField validate = new BorderedTextField(frame.getNolResourceString(VALIDATEON));
		validate.setBounds(150,0,150,20);
		choicePane.add(validate);
		validateChoices.removeAllElements();

		for(int i=0;i<n;i++){
			DataSeries ds1 = (DataSeries)origDataSeries.elementAt(i);
			BorderedTextField ds1Name = new BorderedTextField(ds1.getName());
			ds1Name.setBounds(0,20*i+20,150,20);
			choicePane.add(ds1Name);
			JComboBox choiceBox = new JComboBox();
			choiceBox.setBounds(150,20*i+20,150,20);
			choiceBox.addActionListener(actionListener);
			validateChoices.addElement(choiceBox);
			choicePane.add(choiceBox);

			Vector avds = (Vector)availableDataSeries.elementAt(i);
			for(int j=0;j<avds.size();j++){
				choiceBox.addItem(avds.elementAt(j).toString());
			}
		}
		nofire = false;
	}

	public boolean getResult(){
		return isOk;
	}

	public Vector getValidateDataSeries(){
		if(hasValidData)
			return validateDataSeries;
		return null;
	}

 	public boolean hasValidData() {
		return hasValidData;
	}

	private boolean okFired() {
		hasValidData = false;
		validateDataSeries  = new Vector();
		for(int i=0;i<validateChoices.size();i++){
			JComboBox choiceBox = (JComboBox)validateChoices.elementAt(i);
			int selIndex = choiceBox.getSelectedIndex();
			Vector avds = (Vector)availableDataSeries.elementAt(i);
			DataSeries ds1 = (DataSeries)avds.elementAt(selIndex);
			DataSeries ds0 = (DataSeries)origDataSeries.elementAt(i);
			if(!ds0.getName().equals(ds1.getName())) {
				hasValidData = true;
			}
			validateDataSeries.addElement(ds1);
		}
		return hasValidData;
	}
/*
		Vector validateVariables = new Vector();
		DataSeries ds = model.getDataSeries();
		Preprocessor prep = (Preprocessor)ds.getDataSource();
		ViewFilter filter0 = prep.getViewFilter();
		ViewFilter filter1 = new ViewFilter();
		LabelPattern[] pshow = filter0.getPatternsToShow();
		LabelPattern[] phide = filter0.getPatternsToHide();
		filter1.setPatternsToShow(pshow);
		filter1.setPatternsToHide(phide);
		Vector origVariables = filter0.getVariables();
		for(int i=0;i<origVariables.size();i++){
			Variable var0 = (Variable)origVariables.elementAt(i);
			DataSeries ds0 = var0.getDataSeries();
//			System.out.println("ds0="+ds0.getName());
			int dsIndex = origDataSeries.indexOf(ds0);
			DataSeries ds1 = (DataSeries)validateDataSeries.elementAt(dsIndex);
			Variable var1 = ds1.getVarByName(var0.getName());
			validateVariables.addElement(var1);
		}
		filter1.setVariables(validateVariables);

		validatePreprocessor = new Preprocessor("ValidatePreprocessor",
			frame.getProject(),filter1,false);

		Vector formulas0 = prep.getFormulas();
		Vector formulas1 = new Vector();
		for(int i=0;i<formulas0.size();i++){
			Formula2 fm = (Formula2)formulas0.elementAt(i);
			if(fm.getName().equals("TIME_MERGE")){

			}else if(fm instanceof NolModel2){

			}else{
				Vector inputs = fm.getInputs();
				Vector outputs = fm.getOutputs();
				Formula2 fm1 = new Formula2();
				fm1.setName(fm.getName());
				fm1.setCalculatorClass("FormulaCalculator");
				for(int j=0;j<outputs.size();j++){
					Variable var0 = (Variable)outputs.elementAt(j);
					DataSeries ds0 = var0.getDataSeries();
					int dsIndex = origDataSeries.indexOf(ds0);
					DataSeries ds1 = (DataSeries)validateDataSeries.elementAt(dsIndex);
					Variable var1 = ds1.getVarByName(var0.getName());
					fm1.getOutputs().addElement(var1);
				}
				for(int j=0;j<inputs.size();j++){
					Object elem0 = inputs.elementAt(j);
					if(elem0 instanceof Variable){
						Variable var0 = (Variable)elem0;
						DataSeries ds0 = var0.getDataSeries();
						int dsIndex = origDataSeries.indexOf(ds0);
						DataSeries ds1 = (DataSeries)validateDataSeries.elementAt(dsIndex);
						Variable var1 = ds1.getVarByName(var0.getName());
						fm1.getInputs().addElement(var1);
					}else if(elem0 instanceof InnerFormula2){
						addInnerFormula(fm1.getInputs(), (InnerFormula2)elem0); 
					}else if(elem0 instanceof java.lang.String){
						fm1.getInputs().addElement(elem0);
					}

				}			
			}
		}
		return okValidate;
*/


    class MainAction extends AbstractAction {
		MainAction() {	super("title");}
        @Override
		public void actionPerformed(ActionEvent event) {
			if(nofire){
				return;
			}
			if (event.getSource().equals(okButton)) {
				okFired();
				isOk = true;
				NolModelValidateChoiceDialog.this.setVisible(false);
			} else if(event.getSource().equals(cancelButton)){
				isOk = false;
				NolModelValidateChoiceDialog.this.setVisible(false);
			}
		}
    }

    class BorderedTextField extends JComponent {
		String text ="";

		public BorderedTextField(String t) {
			this();
			if(t== null) 
				text = "";
			else
				text = t;
		}
		public BorderedTextField() {
			super();
		}

		public void setText(String t){
			if(t== null) 
				text = "";
			else
				text = t;
			repaint(0l);
			validate();
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
			g.drawLine(getWidth()-1, 0, getWidth()-1, getHeight()-1);
			g.drawLine(0, getHeight()-1, getWidth(), getHeight()-1);
		}
    }
}

