package com.gensym.nols.wksp;

import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.net.*;
import java.util.*;

import javax.swing.text.*;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.border.*;

import com.gensym.nols.main.*;
import com.gensym.nols.data.*;
import com.gensym.nols.dlg.*;
/**
 * 
 */
public class NolFormulaListWKSP extends NolInternalFrame implements 
ActionListener, ItemListener, PreprocessorListener,ListSelectionListener {
	private JButton ivjAddTransform = null;
	private JButton ivjModifyTransform = null;
	private JButton ivjMergeTransform = null;
	private JButton ivjImportTransform = null;
	private JButton ivjExportTransform = null;
	private JButton ivjRemoveTransform = null;
	private JButton ivjUpdateData = null;
	private JComboBox  ivjVarListChoice = null;
	private JComboBox  ivjDataSeriesChoice = null;
	private JComboBox  ivjArgLocation = null;
	private JList ivjTransformList = null;
	private JPanel ivjPanel1 = null;
	private JPanel mainPanel = null;
	private GridLayout ivjPanel1GridLayout = null;
	private JPanel ivjPanel2 = null;
	private JDialog ivjTransformConst = null;

	private g2TextField ivjOutputField = null;
	private g2TextField ivjInputField = null;
	private Font ivjInputFieldFont = null;
	private FontMetrics ivjInputFieldFontMetrics = null;
	private Font ivjOutputFieldFont = null;
	private FontMetrics ivjOutputFieldFontMetrics = null;
	private JPanel ivjPanel3 = null;
	private JPanel ivjPanel4 = null;
	private JPanel ivjPanel5 = null;
	private JButton ivjNumber0 = null;
	private JButton ivjNumber1 = null;
	private JButton ivjNumber2 = null;
	private JButton ivjNumber3 = null;
	private JButton ivjNumber4 = null;
	private JButton ivjNumber5 = null;
	private JButton ivjNumber6 = null;
	private JButton ivjNumber7 = null;
	private JButton ivjNumber8 = null;
	private JButton ivjNumber9 = null;
	private JButton ivjNumberBack = null;
	private JButton ivjNumberDot = null;
	private JButton ivjNumberE = null;
	private JButton ivjNumberPi = null;
	private JButton ivjNumberSign = null;
	private JLabel ivjConstructLabel0 = null;
	private JLabel ivjConstructLabel1 = null;
	private JList ivjTransformChoice = null;
	private JList ivjVariableChoice = null;
    private DefaultListModel transformChoiceModel = null;
    private DefaultListModel variableChoiceModel = null;
	private JButton ivjCreateNewVar = null;
	private JButton ivjTransformProperty = null;
	private JButton ivjAddArg = null;
	private JButton ivjDeleteArg = null;
	private JButton ivjDone1 = null;
	private JButton ivjCancel1 = null;

	private JButton ivjDown = null;
	private JButton ivjLeft = null;
	private JButton ivjRight = null;
	private JButton ivjUp = null;

//	The public field for data series.
	private int dataSeriesIndex = 0;
	private Formula2 currentFormula = null;
	private int currentPosition = -1;
	private String currentVariable = "";
	protected int moveFrom = -1;
	protected int moveTo = -1;
	protected boolean isInOrOut = false;
	private g2FocusAdapter g2focusListener = null;
	private g2MouseAdapter g2mouseListener = null;
	private g2KeyAdapter g2keyListener = null;
	private g2WindowAdapter g2windowListener = null;
	private Vector varTransformIndex = null;
	private int funcMode = 0;// 0: waiting; 1: modify;  2:move 3: add;
	private Vector editedInputIndex = null;
	private int editedOutputIndex = 0;
	private int editedInputStart = 0;
	private int editedInputEnd = 0;
	private int displayMode = 0;// 0: output;  1:input 2: anywhere
	private String numberInput = "";
	private boolean findClick = false;
    private DefaultListModel NolFormulaListWKSPModel = null;
    private JScrollPane listScrollPane;
	private TransformListCellRenderer transformListCellRenderer = null;
	private boolean noFireAction = true;
	private boolean oneTransformDialogOut = false;

	private NolMainFrame frame = null;

/**
 * NolFormulaListWKSP constructor comment.
 * @param title OfflineOfflineTransformer
 */
public NolFormulaListWKSP(NolMainFrame frame,Preprocessor prep){
	super(prep);
	this.frame = frame;
	this.dataSeriesIndex = 0;
	initialize();
	initConnections();
	String title = "Formula List: [" + prep.getName()+"]";
	this.setTitle(title);
	this.currentVariable = "All Variables";
	noFireAction = true;
	displayVarChoice();
	displayTransformChoice();
	displayDataSeriesChoice();
	displayTransList("All Variables");
	this.currentPosition = getTransformListModel().getSize()-1;
//	System.out.println("con currentPosition 1= "+currentPosition); 
	getTransformList().setSelectedIndex(this.currentPosition);
//	System.out.println("con currentPosition 2= "+currentPosition); 
	getListScrollPane().validate();
	this.transformer.addTransformerListener(this);
	noFireAction = false;
}

public void setTransformer(OfflineTransformer tf){
	this.transformer.removeTransformerListener(this);
	this.transformer = tf;
	this.dataSeriesIndex = 0;
	initializeAttribute();
	noFireAction = true;
	displayVarChoice();
	displayTransformChoice();
	displayDataSeriesChoice();
	displayTransList("All Variables");
	this.currentPosition = getTransformListModel().getSize()-1;
	getTransformList().setSelectedIndex(this.currentPosition);
	getListScrollPane().validate();
	this.transformer.addTransformerListener(this);
	noFireAction = false;
}

/**
 * conn1:  (AddTransform.action.actionPerformed(ActionEvent) --> TransformConst.show())
 * @param arg1 ActionEvent
 */
private void conn1(ActionEvent arg1) {
//	System.out.println("in conn1");
	if(noFireAction){
//		System.out.println("in conn1 noFireAction");
		return;
	}
	if(dataSeriesIndex>=this.transformer.getNumberOfDataSeries()) return;
//	try {
        
		funcMode = 3;
		noFireAction = true;
//		System.out.println("conn1 get 1");
		getTransformListModel().removeElement(new Integer(0));
//		System.out.println("conn1 get 2 currentPosition="+currentPosition);
	  	getTransformListModel().insertElementAt(new Integer(0),this.currentPosition);
//		System.out.println("conn1 get 3");
		getListScrollPane().validate();
//		System.out.println("conn1 get 4");
	 	getTransformList().setSelectedIndex(this.currentPosition);	
//		System.out.println("conn1 get 5");
		refreshcurrentFormula();

		this.isInOrOut = false;
//		this.setEnabled(false);
//		System.out.println("conn1 current transform = "+ currentFormula.toString());
//		System.out.println("conn1 current ds# in the transform = "+ currentFormula.getDataSeriesIndex());
		getTransformConst().pack();  
		getTransformConst().setBounds(200,200,720,260);  
		getTransformConst().setVisible(true); 
		showInputField();
		showOutputField();
		noFireAction = false;
//		System.out.println("conn1 current transform = "+ currentFormula.toString());

//	} catch (Throwable ivjExc) {
//		System.out.println("no after show"+ivjExc.toString());
//		handleException(ivjExc);
//	}
}

/**
 * conn2:  (ModifyTransform.action.actionPerformed(ActionEvent) --> TransformConst.show())
 * @param arg1 ActionEvent
 */
private void conn2(ActionEvent arg1) {
//	System.out.println("in conn2");
	if(noFireAction) return;
	if(dataSeriesIndex>=this.transformer.getNumberOfDataSeries()) return;
//	try {
		noFireAction = true;        
		getTransformConst().pack();  
		getTransformConst().setBounds(200,200,720,260);  
		getTransformConst().setVisible(true); 
		funcMode = 1;
		Integer posit = (Integer)getTransformListModel().elementAt(this.currentPosition);
		if(posit.intValue() == 0){
			currentFormula = new Transform(dataSeriesIndex);
			editedOutputIndex = 0;
			currentFormula.getOutputs().addElement(new String("???"));
		}else{
			editedOutputIndex = 0;
			Vector tfl = this.transformer.getTransforms();
			currentFormula = (Transform)tfl.elementAt(posit.intValue()-1);
		}
		//Inputs:
		editedInputIndex.removeAllElements();
		editedInputIndex.addElement(currentFormula);
		this.numberInput = new String();

		this.isInOrOut = false;
		showInputField();
		showOutputField();
		noFireAction = false;
//	} catch (Throwable ivjExc) {
//		System.out.println("no after show"+ivjExc.toString());
//		handleException(ivjExc);
//	}
}
/**
 * conn3:  (RemoveTransform.action.actionPerformed(ActionEvent) --> TransformConst.show())
 * @param arg1 ActionEvent
 */
private void conn3(ActionEvent arg1) {
//		System.out.println("in conn3");
	if(noFireAction) return;
//	try {
		int position = getCurrentPosition(this.currentPosition);
		if(position <= -1) return;
		if(position <= this.transformer.getTransforms().size()-1){
			this.transformer.removeTransform(position);
			if(this.currentPosition > this.varTransformIndex.size()-1){
				this.currentPosition = this.varTransformIndex.size()-1;
				if(this.currentPosition<0) this.currentPosition=0;
			}
		}

//	} catch (Throwable ivjExc) {
//		handleException(ivjExc);
//	}
}
/**
 * conn4:  (UpdateTransform.action.actionPerformed(ActionEvent) --> TransformConst.show())
 * @param arg1 ActionEvent
 */
private void conn4(ActionEvent arg1) {
	System.out.println("in conn4");
	if(noFireAction) return;
	try {
		this.transformer.updateTransform();
	} catch (NoSuchMethodException ivjExc){
		System.err.println("updateTransform Exception " + ivjExc.getMessage());
		ivjExc.printStackTrace();
	} catch (SecurityException ivjExc){
		System.err.println("updateTransform Exception " + ivjExc.getMessage());
		ivjExc.printStackTrace();
	} catch (InstantiationException ivjExc){
		System.err.println("updateTransform Exception " + ivjExc.getMessage());
		ivjExc.printStackTrace();
	} catch (IllegalAccessException ivjExc) {
		System.err.println("updateTransform Exception " + ivjExc.getMessage());
		ivjExc.printStackTrace();
	}
	Toolkit.getDefaultToolkit().beep();
//	frame.getProjectTree().setoject();
}
/**
 * conn7:  (VarListChoice.item.itemStateChanged(ItemEvent) --> NolFormulaListWKSP.show())
 * @param arg1 ItemEvent
 */
private void conn7(ItemEvent arg1) {
//	System.out.println("in conn7");
	if(noFireAction){
//		System.out.println("no fire conn7");
		return;
	}
//	try {
		noFireAction = true;
		this.currentVariable = (String)getVarListChoice().getSelectedItem();
		if(this.currentVariable == null){
//			System.out.println("no selected string conn7");
//			this.currentVariable = "All
		}
		displayTransList(this.currentVariable);
		this.currentPosition = getTransformListModel().getSize()-1;
		getTransformList().setSelectedIndex(this.currentPosition);
		getListScrollPane().validate();
		noFireAction = false;
//	} catch (Throwable ivjExc) {
//		handleException(ivjExc);
//	}
}

/**
 * conn8:  (ArgLocation.item.itemStateChanged(ItemEvent) --> NolFormulaListWKSP.show())
 * @param arg1 ItemEvent
 */
private void conn8(ItemEvent arg1) {
//	System.out.println("in conn8");
	if(noFireAction) return;
//	try {
		this.displayMode = getArgLocation().getSelectedIndex();
		displayTransList(this.currentVariable);
		this.currentPosition = getTransformListModel().getSize()-1;
		getTransformList().setSelectedIndex(this.currentPosition);
		getListScrollPane().validate();
//	} catch (Throwable ivjExc) {
//		handleException(ivjExc);
//	}
}

/**
 * conn9:  (CreateNewVar.action.actionPerformed(ActionEvent) --> NolFormulaListWKSPV.show())
 * @param arg1 ActionEvent
 */
private void conn9(ActionEvent arg1) {
//	System.out.println("in conn9");
	if(noFireAction) return;
//	try {			
		JFrame frame = getFrame();
		NolTextInput newVar = new NolTextInput(frame, "Input Variable Name","Variable Name:");
		newVar.setBounds(200,200,195,145);
		newVar.setVisible(true);
		String s = newVar.getText();
		if(newVar.getResult()){
			newVar.dispose();		
		}else{
			newVar.dispose();
			return;
		}
		if(getVariableChoiceModel().contains(s)){
			return;
		}else{
			noFireAction = true;
			getVariableChoice().clearSelection();
			String dsName = transformer.getDataSeriesName(dataSeriesIndex);
			Column colObj = new Column(s,dsName,-1);
			this.currentFormula.getOutputs().setElementAt(colObj,editedOutputIndex);
			showOutputField();
			noFireAction = false;
		}
		
//		if(this.isInOrOut) return;
//		String s = getCreateNewVar().getText();
//		getVariableChoice().setSelectedItem(s);
//		if(getVariableChoice().getSelectedItem().equals(s)){
//			return;
//		}else{
//			getVariableChoice().setSelectedItem("");
//			Column colObj = new Column(s,-1);
//			this.currentFormula.getOutputs().setElementAt(colObj,editedOutputIndex);
//			showOutputField();
//		}
//	} catch (Throwable ivjExc) {
//		handleException(ivjExc);
//	}
}
/**
 * conn10:  (NolFormulaListWKSP.item.itemStateChanged(ItemEvent) --> NolFormulaListWKSPV.show())
 * @param arg1 ItemEvent
 */
private void conn10(ListSelectionEvent arg1) {
//	System.out.println("in conn10");
	if(noFireAction) {
//		System.out.println(" not fireing 10");
		return;
	}
//	try {
		if(funcMode != 2){
//			System.out.println(" conn10(currentPosition 1="+currentPosition);
			this.currentPosition = getTransformList().getSelectedIndex();
//			System.out.println(" conn10(currentPosition 2="+currentPosition);
//		}else{//in move mode
//			String s = ""+(getTransformList().getSelectedIndex()+1);
//			getMoveToLine().setText(s);
		}
//	} catch (Throwable ivjExc) {
//		handleException(ivjExc);
//	}
}

/**
 * conn11:  (DataSeriesChoice.item.itemStateChanged(ItemEvent) --> NolFormulaListWKSPV.show())
 * @param arg1 ItemEvent
 */
private void conn11(ItemEvent arg1) {
//	System.out.println("in conn11");
	if(noFireAction) return;
	noFireAction = true;
//	try {
		this.dataSeriesIndex = getDataSeriesChoice().getSelectedIndex();
		if(dataSeriesIndex>=this.transformer.getNumberOfDataSeries()){
			getTransformConst().setVisible(false);
			getAddTransform().setEnabled(false);
			getModifyTransform().setEnabled(false);
			getMergeTransform().requestFocus();
		}else{
			getAddTransform().setEnabled(true);
			getModifyTransform().setEnabled(true);
			getAddTransform().requestFocus();
		}
		displayVarChoice();
		displayTransList(this.currentVariable);
		this.currentPosition = getTransformListModel().getSize()-1;
		getTransformList().setSelectedIndex(this.currentPosition);
		getListScrollPane().validate();
//	} catch (Throwable ivjExc) {
//		handleException(ivjExc);
//	}
	noFireAction = false;
}

/**
 * conn12:  (Done1.action.actionPerformed(ActionEvent) --> TransformConst.dispose())
 * @param arg1 ActionEvent
 */
private void conn12(ActionEvent arg1) {
//	System.out.println("in conn12");
	if(noFireAction) return;
	noFireAction = true;
//	try {
		if(currentFormula.getOutputs().contains("???")) return;
		if(getInputField().getText().indexOf("???") != -1) return;

		if(!this.currentFormula.isValid()) return;

		if(funcMode == 3){
			this.addTransform(this.currentFormula);
		}else if(funcMode == 1){
			this.modifyTransform(this.currentFormula);
		}
		getTransformConst().setVisible(false);
		this.setEnabled(true);
		refreshcurrentFormula();
		funcMode = 0;
		showcurrentFormulaList("conn12");
		
//	} catch (Throwable ivjExc) {
//		handleException(ivjExc);
//	}
	noFireAction = false;
}
/**
 * conn13:  (Cancel1.action.actionPerformed(ActionEvent) --> TransformConst.dispose())
 * @param arg1 ActionEvent
 */
private void conn13(ActionEvent arg1) {
	System.out.println("in conn13");
	if(noFireAction) return;
//	try {
		getTransformConst().setVisible(false); //12/3/97
		System.out.println("get the cancel button");
		if(funcMode == 3){
			getTransformListModel().removeElement(new Integer(0));
			getTransformListModel().addElement(new Integer(0));	
			getListScrollPane().validate();
			this.currentPosition = getTransformListModel().getSize()-1;
			getTransformList().setSelectedIndex(this.currentPosition);	
			getListScrollPane().validate();
		}
		refreshcurrentFormula();
		funcMode = 0;
//	} catch (Throwable ivjExc) {
//		handleException(ivjExc);
//	}
}
/**
 * conn14:  (AddArg.action.actionPerformed(ActionEvent) --> NolFormulaListWKSPV.show())
 * @param arg1 ActionEvent
 */
private void conn14(ActionEvent arg1) {
	System.out.println("in conn14");
	if(noFireAction) return;
//	try {
		if(!this.isInOrOut){
			editedOutputIndex++;
			this.currentFormula.getOutputs().insertElementAt("???",editedOutputIndex); 
			showOutputField();
		}else{
			if(editedInputIndex.lastElement() == this.currentFormula) return;
			Transform trans = (Transform)editedInputIndex.elementAt(editedInputIndex.size()-2);
			int size = trans.getInputs().size();
			for(int i=0;i<size;i++){
				if(trans.getInputs().elementAt(i) == editedInputIndex.lastElement()){
					String s = new String("???");
					trans.getInputs().insertElementAt(s,i+1);
					editedInputIndex.setElementAt(s,editedInputIndex.size()-1);
					break;
				}
			}
			this.numberInput = new String();
			showInputField();
		}
//	} catch (Throwable ivjExc) {
//		handleException(ivjExc);
//	}
}

/**
 * conn15:  (DeleteArg.action.actionPerformed(ActionEvent) --> NolFormulaListWKSPV.show())
 * @param arg1 ActionEvent
 */
private void conn15(ActionEvent arg1) {

	System.out.println("in conn15");
	if(noFireAction) return;
//	try {
		if(!this.isInOrOut){
			if(editedOutputIndex != 0){
				this.currentFormula.getOutputs().removeElementAt(editedOutputIndex); 
				editedOutputIndex--;
			}else if(this.currentFormula.getOutputs().size()>1){
				this.currentFormula.getOutputs().removeElementAt(editedOutputIndex); 
			}else if(!this.currentFormula.getOutputs().elementAt(0).equals("???")){
				this.currentFormula.getOutputs().setElementAt("???",editedOutputIndex); 
			}
			showOutputField();
		}else{
			if(editedInputIndex.lastElement() == this.currentFormula) {
 				currentFormula.setTransform("");
				currentFormula.setTransClass(""); 
				currentFormula.getInputs().removeAllElements();
			}else{
				Transform trans = (Transform)editedInputIndex.elementAt(editedInputIndex.size()-2);
				int size = trans.getInputs().size();
				if(size == 1){
					if(trans.getInputs().elementAt(0).equals("???")) return;
					String s = new String("???");
					trans.getInputs().setElementAt(s,0);
					editedInputIndex.setElementAt(s,editedInputIndex.size()-1);
				}else{
					for(int i=0;i<size;i++){
						if(trans.getInputs().elementAt(i) == editedInputIndex.lastElement()){
							trans.getInputs().removeElementAt(i);
							if(i==size-1){
								editedInputIndex.setElementAt(trans.getInputs().elementAt(i-1),editedInputIndex.size()-1);
							}else{
								editedInputIndex.setElementAt(trans.getInputs().elementAt(i),editedInputIndex.size()-1);
							}
							break;
						}
					}
				}
			}
//			System.out.println("dele out "+editedInputIndex.toString());
			this.numberInput = new String();
			showInputField();
		}
//	} catch (Throwable ivjExc) {
//		handleException(ivjExc);
//	}
}
/**
 * conn16:  (TransformChoice.item.itemStateChanged(ItemEvent) --> InputField.enabled)
 * @param arg1 ItemEvent
 */
private void conn16(ListSelectionEvent arg1) {
	if(noFireAction){
		System.out.println("no fire conn16");
		return;
	}
//	try {
		if(!this.isInOrOut) {
			showOutputField();
			return;
		}
		String m = (String)getTransformChoice().getSelectedValue();
		System.out.println("conn16 getSelectedValue="+m);
		if(m==null) return;
		if(m.equals("More Functions...")){
			JFrame frame = getFrame();
			if(frame != null){
				Project p = transformer.getProject();
				Vector models = p.getPredictiveModels();
				Vector contentsStrings = new Vector(10,10);
				Vector contentInfos = new Vector(10,10);
				for(int i=0;i<TransformMap.transforms.length;i++){
					contentsStrings.addElement(TransformMap.transforms[i]);
				}
				for(int i=0;i<models.size();i++){
					contentsStrings.addElement(((NolModel2)models.elementAt(i)).getTransform());
				}
				for(int i=0;i<TransformMap.transforms.length;i++){
					contentInfos.addElement(TransformMap.transformInfo[i]);
				}
				for(int i=0;i<models.size();i++){
					contentInfos.addElement(((NolModel2)models.elementAt(i)).getTransform());
				}
				if(oneTransformDialogOut) return;
				oneTransformDialogOut = true;
				NolTransformChoiceDialog dg = new NolTransformChoiceDialog
					(frame,"Select Function", 
					"Select the function for this transform.",
					contentsStrings, contentInfos, false);
				dg.setBounds(50, 50, 450, 300);
				dg.show();	
				int tIndex = dg.getSelectedIndex();
				if(dg.getResult()){
					oneTransformDialogOut = false;
					int ind = dg.getSelectedIndex();
					if(ind>=TransformMap.transforms.length){
						m = ((NolModel2)models.elementAt(ind-TransformMap.transforms.length)).getTransform();
					}else{
						m = TransformMap.transforms[ind];
					}
					noFireAction = true;
					if(getTransformChoiceModel().contains(m)){
						getTransformChoice().setSelectedIndex(getTransformChoiceModel().indexOf(m));
					}else{
						getTransformChoiceModel().removeElementAt(5);
						getTransformChoiceModel().insertElementAt(m,0);
						getTransformChoice().setSelectedIndex(0);
					}
					noFireAction = false;
					dg.dispose();		
				}else{
					oneTransformDialogOut = false;
					dg.dispose();	
					return;
				}
			}else{
				return;
			}
		}
			
		Project p = transformer.getProject();
		Object inputObj = editedInputIndex.lastElement();
		int mindex = p.getPredictiveModelIndexByName(m);
		if(currentFormula == inputObj){
			if(currentFormula.getTransform().equals(m)) return;
			if(mindex !=  -1){
				Vector models = p.getPredictiveModels();
				currentFormula = (NolModel2)models.elementAt(mindex);
				showInputField();
				showOutputField();
			}else{
				currentFormula.setTransform(m);
				//modify the property into input vector.
				currentFormula.setTransClass("TransformCalculator");  
				currentFormula.getInputs().removeAllElements();
				currentFormula.getInputs().addElement(new String("???"));
				showInputField();
			}
		}else{
			if(mindex ==  -1){
				InnerTransform newTrans = new InnerTransform();
				newTrans.setTransform(m);
				newTrans.setTransClass("TransformCalculator");
				newTrans.getInputs().addElement(new String("???"));
				modifycurrentFormula((Transform)editedInputIndex.elementAt(editedInputIndex.size()-2), newTrans);
				showInputField();
				this.numberInput = new String();
			}
		}
		System.out.println(currentFormula.toString()); 
		//gchen add the model to the transform list.

//	} catch (Throwable ivjExc) {
//		System.out.println(ivjExc);
//		handleException(ivjExc);
//	}
}

/**
 * conn17:  (VariableChoice.item.itemStateChanged(ItemEvent) --> OutputField.enabled)
 * @param arg1 ItemEvent
 */
private void conn17(ListSelectionEvent arg1) {
	System.out.println("in conn17");
	if(noFireAction){
		System.out.println("no fire conn17");
		return;
	}
	try {
		int index = getVariableChoice().getSelectedIndex();
		if(index == -1 ) return;
		int[] vars = this.transformer.getVariableNumbers(dataSeriesIndex);
		Column colObj = (Column)((Column)this.transformer.getColumnInfo().elementAt(vars[index])).clone();
//		Column colObj = (Column)this.transformer.getColumnInfo().elementAt(vars[index]);
		if(this.isInOrOut){
			Object inputObj = editedInputIndex.lastElement();
			if(inputObj == this.currentFormula) return;
			modifycurrentFormula((Transform)editedInputIndex.elementAt(editedInputIndex.size()-2), colObj);
			showInputField();
			this.numberInput = new String();
		}else{
			this.currentFormula.getOutputs().setElementAt(colObj,editedOutputIndex);
			showOutputField();
		}

	} catch (CloneNotSupportedException ivjExc) {
		handleException(ivjExc);
	}
}
/**
 * conn18:  (getTransformProperty.action.actionPerformed(ActionEvent) --> NolFormulaListWKSPV.show())
 * @param arg1 ActionEvent
 */
private void conn18(ActionEvent arg1) {

	if(noFireAction) return;
	if(!this.isInOrOut) return;
	Object inputObj = editedInputIndex.lastElement();
	if(inputObj instanceof Transform || inputObj instanceof InnerTransform){
		Transform tf = (Transform)inputObj;
		int np = tf.getNumberOfProperties();
		if(np>0){
			JFrame frame = getFrame();
			Vector contents = tf.getPropertyNames();
			Vector defaultInputs = tf.getProperties();
			NolTableDialog dg = new NolTableDialog
				(frame, "Define Formula Properties", 
				tf.getTransform(), contents,defaultInputs);
			dg.pack();
			int w = dg.getSize().width+40;
			if(w<200) w = 200;
			dg.setBounds(200,200,w,dg.getSize().height);
			dg.show();		
			if(dg.getResult()){
				Vector result = dg.getInputs();
				tf.setProperties(result);
				dg.dispose();
			}else{
				dg.dispose();
				return;
			}
		}
	}
}

/**
 * conn20: 
 * @param arg1 ActionEvent
 */
private void conn20(ActionEvent arg1) {
	System.out.println("in conn20");
	if(noFireAction) return;
	JFrame frame = getFrame();
	if(frame == null) return;
	funcMode = 3;
	noFireAction = true;
	getTransformListModel().removeElement(new Integer(0));
	getTransformListModel().insertElementAt(new Integer(0),this.currentPosition);
	getListScrollPane().validate();
	getTransformList().setSelectedIndex(this.currentPosition);	

	Vector varName = new Vector();
	int n = this.transformer.getNumberOfVariables();
	for(int i=0;i<n;i++)
		varName.addElement(this.transformer.getVariableName(i));
		
	NolVarMergeDialog dg = new NolVarMergeDialog (frame, 
			"Create New Data Series by Merging",varName, true);
	dg.show();
	if(dg.getResult()){
		dg.dispose();		
	}else{
		dg.dispose();	
		noFireAction = false;
		return;
	}
	Vector vs = dg.getSelectedItems();
	String dsName = dg.getGivenName();
	long[] T = new long[0];
	if(dg.getTimeStampFlag() == 0){
		String vn = dg.getVarNameForTime(); 
		T = transformer.getTimes(transformer.getVariableNumber(vn));
	}else if(dg.getTimeStampFlag() == 1){
		T = dg.getNewTimeStamps();
	}
	int nvs = vs.size();
	if(nvs==0){
		noFireAction = false;
		return;
	}
	String vname = (String)vs.elementAt(0);
	int nbvs = this.transformer.getVariableNumber(vname);
	int nbds = this.transformer.getDataSeriesNumber(nbvs);
	boolean sameDs = true;
	for(int i=1;i<nvs;i++){
		vname = (String)vs.elementAt(i);
		nbvs = this.transformer.getVariableNumber(vname);
		int newnbds = this.transformer.getDataSeriesNumber(nbvs);
		if(newnbds != nbds){
			sameDs = false;
			break;
		}
	}
	if(sameDs){
		noFireAction = false;
		return;
	}
	if(dsName.equals("DefaultMergedSeries")){
		String newdsName = dsName;
		int count = 1;
		while(true){
			newdsName = dsName + count;
			count++;
			if(this.transformer.getDataSeriesNumber(newdsName) == -1){
				dsName = newdsName;
				break;
			}
		}
	}
	int dss  = this.transformer.getNumberOfDataSeries();
	Vector outs = new Vector(1);
	for(int i=0;i<nvs;i++){
		vname = (String)vs.elementAt(i);
		while(true){
			vname = vname+"_m";
			if(this.transformer.getVariableNumber(vname) == -1){
				Column colObj = new Column(vname,dsName,-1);
				outs.addElement(colObj);
				break;
			}
		}
	}	
	Vector ins = new Vector(nvs);	
	for(int i=0;i<nvs;i++){
		vname = (String)vs.elementAt(i);
		nbvs = 	this.transformer.getVariableNumber(vname);
		String olddsName = this.transformer.getDataSeriesName(this.transformer.getDataSeriesNumber(nbvs));
		Column colObj = new Column(vname,olddsName,nbvs);
		ins.addElement(colObj);
	}
	Transform mergeTransform = new Transform("MERGE",ins,outs,dss);
	Vector prop = new Vector();
	prop.addElement(dsName);
	prop.addElement(new Integer(0));
	prop.addElement(T);
	mergeTransform.setProperties(prop);
	this.addTransform(mergeTransform);
	System.out.println("merge tran = "+mergeTransform.toString());
	this.currentPosition = getTransformListModel().getSize()-1;
	funcMode = 0;
	noFireAction = false;
}

/**
 * conn21: 
 * @param arg1 ActionEvent
 */
private void conn21(ActionEvent arg1) {	
	JFrame frame = getFrame();
	NolImportTransformDialog dg = 
		new NolImportTransformDialog(frame, transformer);			
	dg.setBounds(50, 50, 700, 300);
	dg.show();
	if(dg.getResult()){
		dg.dispose();
	}else{
		dg.dispose();
		return;
	}
	Vector newTransforms = dg.getSelectedTransforms();
	System.out.println("importing Transforms");
	int position = getCurrentPosition(this.currentPosition);
	if(position == -1)
		position = this.transformer.getTransforms().size();	
	if(position >= this.transformer.getTransforms().size()){
		System.out.println("get importing out loop1");
		this.transformer.addTransforms(newTransforms);
	}else{
		System.out.println("get importing out loop2");
		this.transformer.addTransforms(newTransforms,position);
	}

}
/**
 * conn22: 
 * @param arg1 ActionEvent
 */
private void conn22(ActionEvent arg1) {
	JFrame frame = getFrame();
	FileDialog fileDialog = new FileDialog(frame);
	fileDialog.setMode(FileDialog.SAVE);
	fileDialog.setFile("*.tfm");
	fileDialog.setTitle("Export Formula List");
	fileDialog.setLocation(200,200);			
	fileDialog.show();

	String file = fileDialog.getFile();
	if (file == null) return;
	String directory = fileDialog.getDirectory();
	   
	// try to start writing
	
	int dotInd = file.indexOf(".");
	if(dotInd == -1){
		file = file+".tfm";
	}		
	transformer.saveTransformsBinary(directory, file);
	Toolkit.getDefaultToolkit().beep();
}

/**
 * conn23:  (Number1.action.actionPerformed(ActionEvent) --> NolFormulaListWKSPV.show())
 * @param arg1 ActionEvent
 */
private void conn23(ActionEvent arg1) {
	System.out.println("in conn23");
	if(noFireAction) return;
//	try {
		if(!this.isInOrOut) return;
		String str = this.numberInput + 1;
		appendNumberInput(str);
//	} catch (Throwable ivjExc) {
//		handleException(ivjExc);
//	}
}

/**
 * conn24:  (Number2.action.actionPerformed(ActionEvent) --> NolFormulaListWKSPV.show())
 * @param arg1 ActionEvent
 */
private void conn24(ActionEvent arg1) {
//	try {
		if(!this.isInOrOut) return;
		String str = this.numberInput + 2;
		appendNumberInput(str);
//	} catch (Throwable ivjExc) {
//		handleException(ivjExc);
//	}
}

/**
 * conn25:  (Number3.action.actionPerformed(ActionEvent) --> NolFormulaListWKSPV.show())
 * @param arg1 ActionEvent
 */

private void conn25(ActionEvent arg1) {
//	try {
		if(!this.isInOrOut) return;
		String str = this.numberInput + 3;
		appendNumberInput(str);
//	} catch (Throwable ivjExc) {
//		handleException(ivjExc);
//	}
}

/**
 * conn26:  (Number4.action.actionPerformed(ActionEvent) --> NolFormulaListWKSPV.show())
 * @param arg1 ActionEvent
 */

private void conn26(ActionEvent arg1) {
//	try {
		if(!this.isInOrOut) return;
		String str = this.numberInput + 4;
		appendNumberInput(str);
//	} catch (Throwable ivjExc) {
//		handleException(ivjExc);
//	}
}

/**
 * conn27:  (Number5.action.actionPerformed(ActionEvent) --> NolFormulaListWKSPV.show())
 * @param arg1 ActionEvent
 */

private void conn27(ActionEvent arg1) {
//	try {
		if(!this.isInOrOut) return;
		String str = this.numberInput + 5;
		appendNumberInput(str);
//	} catch (Throwable ivjExc) {
//		handleException(ivjExc);
//	}
}

/**
 * conn28:  (Number6.action.actionPerformed(ActionEvent) --> NolFormulaListWKSPV.show())
 * @param arg1 ActionEvent
 */

private void conn28(ActionEvent arg1) {
	try {
		if(!this.isInOrOut) return;
		String str = this.numberInput + 6;
		appendNumberInput(str);
	} catch (Throwable ivjExc) {
		handleException(ivjExc);
	}
}

/**
 * conn29:  (Number7.action.actionPerformed(ActionEvent) --> NolFormulaListWKSPV.show())
 * @param arg1 ActionEvent
 */

private void conn29(ActionEvent arg1) {
//	try {
		if(!this.isInOrOut) return;
		String str = this.numberInput + 7;
		appendNumberInput(str);
//	} catch (Throwable ivjExc) {
//		handleException(ivjExc);
//	}
}

/**
 * conn30:  (Number8.action.actionPerformed(ActionEvent) --> NolFormulaListWKSPV.show())
 * @param arg1 ActionEvent
 */

private void conn30(ActionEvent arg1) {
//	try {
		if(!this.isInOrOut) return;
		String str = this.numberInput + 8;
		appendNumberInput(str);
//	} catch (Throwable ivjExc) {
//		handleException(ivjExc);
//	}
}

/**
 * conn31:  (Number9.action.actionPerformed(ActionEvent) --> NolFormulaListWKSPV.show())
 * @param arg1 ActionEvent
 */

private void conn31(ActionEvent arg1) {
//	try {
		if(!this.isInOrOut) return;
		String str = this.numberInput + 9;
		appendNumberInput(str);
//	} catch (Throwable ivjExc) {
//		handleException(ivjExc);
//	}
}
/**
 * conn32:  (Number0.action.actionPerformed(ActionEvent) --> NolFormulaListWKSPV.show())
 * @param arg1 ActionEvent
 */

private void conn32(ActionEvent arg1) {
//	try {
		if(!this.isInOrOut) return;
		String str = this.numberInput + 0;
		appendNumberInput(str);
//	} catch (Throwable ivjExc) {
//		handleException(ivjExc);
//	}
}
/**
 * conn33:  (NumberDot.action.actionPerformed(ActionEvent) --> NolFormulaListWKSPV.show())
 * @param arg1 ActionEvent
 */

private void conn33(ActionEvent arg1) {
//	try {
		if(!this.isInOrOut) return;
		String str = this.numberInput + ".";
		appendNumberInput(str);
//	} catch (Throwable ivjExc) {
//		handleException(ivjExc);
//	}
}
/**
 * conn34:  (NumberE.action.actionPerformed(ActionEvent) --> NolFormulaListWKSPV.show())
 * @param arg1 ActionEvent
 */

private void conn34(ActionEvent arg1) {
//	try {
		if(!this.isInOrOut) return;
		String str = this.numberInput + "E+0";
		appendNumberInput(str);
//	} catch (Throwable ivjExc) {
//		handleException(ivjExc);
//	}
}
/**
 * conn35:  (NumberPi.action.actionPerformed(ActionEvent) --> NolFormulaListWKSPV.show())
 * @param arg1 ActionEvent
 */

private void conn35(ActionEvent arg1) {
//	try {
		if(!this.isInOrOut) return;
		String str = new String("3.14159265359");
		appendNumberInput(str);
//	} catch (Throwable ivjExc) {
//		handleException(ivjExc);
//	}
}
/**
 * conn37:  (ArgUp.action.actionPerformed(ActionEvent) --> NolFormulaListWKSPV.show())
 * @param arg1 ActionEvent
 */
private void conn37(ActionEvent arg1) {
	if(noFireAction) return;
//	try {
		if(!this.isInOrOut) return;
		int vsize = editedInputIndex.size();
		if(vsize >1){
			editedInputIndex.removeElementAt(vsize-1);
		}
		this.numberInput = new String();
		showInputField();
//	} catch (Throwable ivjExc) {
//		handleException(ivjExc);
//	}
}

/**
 * conn38:  (ArgLeft.action.actionPerformed(ActionEvent) --> NolFormulaListWKSPV.show())
 * @param arg1 ActionEvent
 */
private void conn38(ActionEvent arg1) {
	if(noFireAction) return;
//	try {
		if(!this.isInOrOut && editedOutputIndex != 0){
			editedOutputIndex--;
			showOutputField();
		}
		if(this.isInOrOut){
			int vsize =  editedInputIndex.size();
			if(vsize<=1) return;
			Transform inTran = (Transform)editedInputIndex.elementAt(vsize-2);
			Vector inputObjs = inTran.getInputs();
			int p =0;
			for(int i=0;i<inputObjs.size();i++){
				if(editedInputIndex.lastElement() == inputObjs.elementAt(i)){
					p=i;
					break;
				}
			}
			if(p>0){
				editedInputIndex.removeElementAt(editedInputIndex.size()-1);
				editedInputIndex.addElement(inputObjs.elementAt(p-1));
			}
			this.numberInput = new String();
//			System.out.println(editedInputIndex.lastElement().toString());
			showInputField();
		}
//	} catch (Throwable ivjExc) {
//		handleException(ivjExc);
//	}
}

/**
 * conn39:  (ArgDown.action.actionPerformed(ActionEvent) --> NolFormulaListWKSPV.show())
 * @param arg1 KeyEvent
 */
private void conn39(ActionEvent arg1) {
	if(noFireAction) return;
//	try {
		if(!this.isInOrOut) return;

		Object inputObj = editedInputIndex.lastElement();
//		String objClass = inputObj.getClass().getName();
//		if(objClass.equals("InnerTransform") || objClass.equals("Transform")){
		if(inputObj instanceof InnerTransform ){
			editedInputIndex.addElement(((Transform)inputObj).getInputs().elementAt(0));
		}else if( inputObj instanceof Transform ){
			if(((Transform)inputObj).getInputs().size() ==0) return;
			editedInputIndex.addElement(((Transform)inputObj).getInputs().elementAt(0));
//		 System.out.println(editedInputIndex.lastElement().toString());
		}
		this.numberInput = new String();
		showInputField();
//	} catch (Throwable ivjExc) {
//		handleException(ivjExc);
//	}
} 

/**
 * conn40:  (ArgRight.action.actionPerformed(ActionEvent) --> NolFormulaListWKSPV.show())
 * @param arg1 KeyEvent
 */
private void conn40(ActionEvent arg1) {
	if(noFireAction) return;
//	try {
		if(!this.isInOrOut && editedOutputIndex < this.currentFormula.getOutputs().size()-1){
			editedOutputIndex++;
			showOutputField();
		}
		if(this.isInOrOut){
			int vsize =  editedInputIndex.size();
			if(vsize<=1) return;
			System.out.println("call conn40"+editedInputIndex.lastElement().toString());
			Transform inTran = (Transform)editedInputIndex.elementAt(vsize-2);

//			System.out.println("call conn40 inTran"+inTran.toString());

			Vector inputObjs = inTran.getInputs();
			int p =0;
			for(int i=0;i<inputObjs.size();i++){
				if(editedInputIndex.lastElement() == inputObjs.elementAt(i)){
					p=i;
					break;
				}
			}
//			System.out.println("call conn40 p"+p);
			if(p<inputObjs.size()-1){
				editedInputIndex.removeElementAt(editedInputIndex.size()-1);
				editedInputIndex.addElement(inputObjs.elementAt(p+1));
			}
//			 System.out.println("call conn40 last"+editedInputIndex.lastElement().toString());
			showInputField();
		}
//	} catch (Throwable ivjExc) {
//		handleException(ivjExc);
//	}
}
/**
 * conn41:  (NumberSign.action.actionPerformed(ActionEvent) --> NolFormulaListWKSPV.show())
 * @param arg1 ActionEvent
 */

private void conn41(ActionEvent arg1) {
	if(noFireAction) return;
//	try {
		if(!this.isInOrOut) return;
		String str = "";
		int Ed = this.numberInput.indexOf("E");
		if(Ed==-1){
			if(this.numberInput.substring(0,1).equals("-")){
				str = this.numberInput.substring(1);
			}else{
				str = "-"+this.numberInput;
			}
		}else{
			if(this.numberInput.indexOf("+",Ed) == -1){
				str = this.numberInput.substring(0,Ed+1) + "+" + this.numberInput.substring(Ed+2);
			}else{
				str = this.numberInput.substring(0,Ed+1) + "-" + this.numberInput.substring(Ed+2);
			}
		}
		appendNumberInput(str);
//	} catch (Throwable ivjExc) {
//		handleException(ivjExc);
//	}
}

/**
 * conn42:  (NumberBack.action.actionPerformed(ActionEvent) --> NolFormulaListWKSPV.show())
 * @param arg1 ActionEvent
 */

private void conn42(ActionEvent arg1) {
	if(noFireAction) return;
//	try {
		if(!this.isInOrOut) return;
		if(this.numberInput.length()<=1){
			conn15(arg1);
		}
		String str = "";
		int Ed = this.numberInput.indexOf("E");
		if(Ed==-1){
			str = this.numberInput.substring(0,this.numberInput.length()-1);
		}else{
			System.out.println(	"sub str="+this.numberInput.substring(Ed));
			if(this.numberInput.substring(Ed).length() == 3){
				str = this.numberInput.substring(0,Ed);
			}else{
				str = this.numberInput.substring(0,this.numberInput.length()-1);
			}
		}
		appendNumberInput(str);
//	} catch (Throwable ivjExc) {
//		handleException(ivjExc);
//	}
}
/**
 * Return the AddArg property value.
 * @return JButton
 */
private JButton getAddArg() {
	if (ivjAddArg == null) {
//		try {
			ivjAddArg = new JButton("Add");
			ivjAddArg.setName("AddArg");
//		} catch (Throwable ivjExc) {
//			handleException(ivjExc);
//		}
	};
	return ivjAddArg;
}
/**
 * Return the Button1 property value.
 * @return JButton
 */

private JButton getAddTransform() {
	if (ivjAddTransform == null) {
			ivjAddTransform = new JButton("Add...");
			ivjAddTransform.setName("AddTransform");
	};
	return ivjAddTransform;
}

/**
 * Return the ConstructLabel1 property value.
 * @return JLabel
 */
private JLabel getConstructLabel1() {
	if (ivjConstructLabel1 == null) {
			ivjConstructLabel1 = new JLabel();
			ivjConstructLabel1.setText("Outputs:");
			ivjConstructLabel1.setBounds(10, 10, 60, 25);
	};
	return ivjConstructLabel1;
}
/**
 * Return the ConstructLabel0 property value.
 * @return JLabel
 */
private JLabel getConstructLabel0() {
	if (ivjConstructLabel0 == null) {
//		try {
			ivjConstructLabel0 = new JLabel();
			ivjConstructLabel0.setName("ConstructLabel1");
			ivjConstructLabel0.setText("Formula:");
			ivjConstructLabel0.setBounds(10, 50, 60, 25); 
//		} catch (Throwable ivjExc) {
//			handleException(ivjExc);
//		}
	};
	return ivjConstructLabel0;
}

/**
 * Return the CreateNewVar property value.
 * @return TextField
 */
private JButton getCreateNewVar() {
	if (ivjCreateNewVar == null) {
//		try {
			ivjCreateNewVar = new JButton("New");
			ivjCreateNewVar.setName("CreateNewVar");
			ivjCreateNewVar.setBounds(520, 10, 80, 25);
//		} catch (Throwable ivjExc) {
//			handleException(ivjExc);
//		}
	};
	return ivjCreateNewVar;
}

/**
 * Return the property button.
 * @return JButton
 */
private JButton getTransformProperty() {
	if (ivjTransformProperty == null) {
//		try {
			ivjTransformProperty = new JButton("Property");
			ivjTransformProperty.setName("TransformProperty");
			ivjTransformProperty.setBounds(520, 50, 80, 25);
//		} catch (Throwable ivjExc) {
//			handleException(ivjExc);
//		}
	};
	return ivjTransformProperty;
}

/**
 * Return the DeleteArg property value.
 * @return JButton
 */
private JButton getDeleteArg() {
	if (ivjDeleteArg == null) {
		try {
			ivjDeleteArg = new JButton("Delete");
			ivjDeleteArg.setName("DeleteArg");
//			ivjDeleteArg.setFont(new Font("dialog", 0, 14));
		} catch (Throwable ivjExc) {
			handleException(ivjExc);
		}
	};
	return ivjDeleteArg;
}

/**
 * Return the Down button.
 * @return JButton
 */
private JButton getDown() {
	if (ivjDown == null) {
		try {
			URL url = this.getClass().getResource("transformDown.gif");
			ivjDown = new JButton(new ImageIcon(url));
			ivjDown.setName("Down");
			ivjDown.setBounds(650, 210, 20, 20);
		} catch (Throwable ivjExc) {
			handleException(ivjExc);
		}
	};
	return ivjDown;
}

/**
 * Return the Left button.
 * @return JButton
 */
private JButton getLeft() {
	if (ivjLeft == null) {
		try {
			URL url = this.getClass().getResource("transformLeft.gif");
			ivjLeft = new JButton(new ImageIcon(url));
			ivjLeft.setName("Left");
			ivjLeft.setBounds(630, 190, 20, 20);
		} catch (Throwable ivjExc) {
			handleException(ivjExc);
		}
	};
	return ivjLeft;
}

/**
 * Return the right button.
 * @return JButton
 */
private JButton getRight() {
	if (ivjRight == null) {
		try {
			URL url = this.getClass().getResource("transformRight.gif");
			ivjRight = new JButton(new ImageIcon(url));
			ivjRight.setName("Right");
			ivjRight.setBounds(670, 190, 20, 20);
		} catch (Throwable ivjExc) {
			handleException(ivjExc);
		}
	};
	return ivjRight;
}

/**
 * Return the Up button.
 * @return JButton
 */
private JButton getUp() {
	if (ivjUp == null) {
		try {
			URL url = this.getClass().getResource("transformUp.gif");
			ivjUp = new JButton(new ImageIcon(url));
			ivjUp.setName("Up");
			ivjUp.setBounds(650, 170, 20, 20);
		} catch (Throwable ivjExc) {
			handleException(ivjExc);
		}
	};
	return ivjUp;
}

/**
 * Return the key listener property value.
 * @return g2KeyAdapter
 */
private g2FocusAdapter getFocusListener() {
	if (g2focusListener == null) {
		try {
			g2focusListener = new g2FocusAdapter();
		} catch (Throwable ivjExc) {
			handleException(ivjExc);
		}
	};
	return g2focusListener;
}
/**
 * Return the InputField property value.
 * @return g2TextField
 */
private java.awt.g2TextField getInputField() {
	if (ivjInputField == null) {
		try {
			ivjInputField = new java.awt.g2TextField();
			ivjInputField.setName("InputField");
			ivjInputFieldFont = new Font("dialog", 0, 12);
			ivjInputField.setFont(ivjInputFieldFont);
			ivjInputField.setText("");
			ivjInputField.setBackground(Color.white);
			ivjInputField.setBounds(80, 50, 430, 25); 
			ivjInputField.setEditable(false);
			ivjInputField.setEnabled(true);
		} catch (Throwable ivjExc) {
			System.out.println("wrong with the width()"+ivjExc);
			handleException(ivjExc);
		}
	};
	return ivjInputField;
}
/**
 * Return the InputFieldFontMetrics property value.
 * @return g2TextField
 */
private FontMetrics getInputFieldFontMetrics() {
	if (ivjInputFieldFontMetrics == null) {
		try {
			ivjInputFieldFontMetrics = getInputField().getFontMetrics(ivjInputFieldFont);
		} catch (Throwable ivjExc) {
			handleException(ivjExc);
		}
	};
	return ivjInputFieldFontMetrics;
}
/**
 * Return the OutputFieldFontMetrics property value.
 * @return java.awt.g2TextField
 */
private FontMetrics getOutputFieldFontMetrics() {
	if (ivjOutputFieldFontMetrics == null) {
		try {
			ivjOutputFieldFontMetrics = getOutputField().getFontMetrics(ivjOutputFieldFont);
		} catch (Throwable ivjExc) {
			handleException(ivjExc);
		}
	};
	return ivjOutputFieldFontMetrics;
}
/**
 * Return the key listener property value.
 * @return g2KeyAdapter
 */
private g2KeyAdapter getKeyListener() {
	if (g2keyListener == null) {
		try {
			g2keyListener = new g2KeyAdapter();
		} catch (Throwable ivjExc) {
			handleException(ivjExc);
		}
	};
	return g2keyListener;
}
private g2WindowAdapter getWindowListener() {
	if (g2windowListener == null) {
		try {
			g2windowListener = new g2WindowAdapter();
		} catch (Throwable ivjExc) {
			handleException(ivjExc);
		}
	};
	return g2windowListener;
}
/**
 * Return the Button2 property value.
 * @return JButton
 */
private JButton getModifyTransform() {
	if (ivjModifyTransform == null) {
		try {
			ivjModifyTransform = new JButton("Modify...");
			ivjModifyTransform.setName("ModifyTransform");
		} catch (Throwable ivjExc) {
			// user code begin {2}
			// user code end
			handleException(ivjExc);
		}
	};
	return ivjModifyTransform;
}

/**
 * Return the mouse listener property value.
 * @return g2MouseAdapter
 */
private g2MouseAdapter getMouseListener() {
	if (g2mouseListener == null) {
		try {
			g2mouseListener = new g2MouseAdapter();
		} catch (Throwable ivjExc) {
			handleException(ivjExc);
		}
	};
	return g2mouseListener;
}
/**
 * Return the ivjMergeTransform property value.
 * @return JButton
 */
private JButton getMergeTransform() {
	if (ivjMergeTransform == null) {
		try {
			ivjMergeTransform = new JButton("Merge...");
			ivjMergeTransform.setName("MergeTransform");
		} catch (Throwable ivjExc) {
			handleException(ivjExc);
		}
	};
	return ivjMergeTransform;
}

/**
 * Return the ivjImportTransform property value.
 * @return JButton
 */
private JButton getImportTransform() {
	if (ivjImportTransform == null) {
		try {
			ivjImportTransform = new JButton("Import...");
			ivjImportTransform.setName("ImportTransform");
		} catch (Throwable ivjExc) {
			handleException(ivjExc);
		}
	};
	return ivjImportTransform;
}

/**
 * Return the ivjExportTransform property value.
 * @return JButton
 */
private JButton getExportTransform() {
	if (ivjExportTransform == null) {
		try {
			ivjExportTransform = new JButton("Export...");
			ivjExportTransform.setName("ExportTransform");
		} catch (Throwable ivjExc) {
			handleException(ivjExc);
		}
	};
	return ivjExportTransform;
}
 
 
/**
 * Return the Number0 property value.
 * @return JButton
 */
private JButton getNumber0() {
	if (ivjNumber0 == null) {
		try {
			ivjNumber0 = new JButton("0");
			ivjNumber0.setName("Number0");
		} catch (Throwable ivjExc) {
			handleException(ivjExc);
		}
	};
	return ivjNumber0;
}

/**
 * Return the Number1 property value.
 * @return JButton
 */
private JButton getNumber1() {
	if (ivjNumber1 == null) {
		try {
			ivjNumber1 = new JButton("1");
			ivjNumber1.setName("Number1");
		} catch (Throwable ivjExc) {
			handleException(ivjExc);
		}
	};
	return ivjNumber1;
}

/**
 * Return the Number2 property value.
 * @return JButton
 */

private JButton getNumber2() {
	if (ivjNumber2 == null) {
		try {
			ivjNumber2 = new JButton("2");
			ivjNumber2.setName("Number2");
		} catch (Throwable ivjExc) {
			handleException(ivjExc);
		}
	};
	return ivjNumber2;
}

/**
 * Return the Number3 property value.
 * @return JButton
 */
private JButton getNumber3() {
	if (ivjNumber3 == null) {
		try {
			ivjNumber3 = new JButton("3");
			ivjNumber3.setName("Number3");
		} catch (Throwable ivjExc) {
			handleException(ivjExc);
		}
	};
	return ivjNumber3;
}

/**
 * Return the Number4 property value.
 * @return JButton
 */
private JButton getNumber4() {
	if (ivjNumber4 == null) {
		try {
			ivjNumber4 = new JButton("4");
			ivjNumber4.setName("Number4");
		} catch (Throwable ivjExc) {
			handleException(ivjExc);
		}
	};
	return ivjNumber4;
}

/**
 * Return the Number5 property value.
 * @return JButton
 */
private JButton getNumber5() {
	if (ivjNumber5 == null) {
		try {
			ivjNumber5 = new JButton("5");
			ivjNumber5.setName("Number5");
		} catch (Throwable ivjExc) {
			handleException(ivjExc);
		}
	};
	return ivjNumber5;
}

/**
 * Return the Number6 property value.
 * @return JButton
 */
private JButton getNumber6() {
	if (ivjNumber6 == null) {
		try {
			ivjNumber6 = new JButton("6");
			ivjNumber6.setName("Number6");
		} catch (Throwable ivjExc) {
			handleException(ivjExc);
		}
	};
	return ivjNumber6;
}

/**
 * Return the Number7 property value.
 * @return JButton
 */
private JButton getNumber7() {
	if (ivjNumber7 == null) {
		try {
			ivjNumber7 = new JButton("7");
			ivjNumber7.setName("Number7");
		} catch (Throwable ivjExc) {
			handleException(ivjExc);
		}
	};
	return ivjNumber7;
}

/**
 * Return the Number8 property value.
 * @return JButton
 */
private JButton getNumber8() {
	if (ivjNumber8 == null) {
		try {
			ivjNumber8 = new JButton("8");
			ivjNumber8.setName("Number8");
		} catch (Throwable ivjExc) {
			handleException(ivjExc);
		}
	};
	return ivjNumber8;
}

/**
 * Return the Number9 property value.
 * @return JButton
 */
private JButton getNumber9() {
	if (ivjNumber9 == null) {
		try {
			ivjNumber9 = new JButton("9");
			ivjNumber9.setName("Number9");
		} catch (Throwable ivjExc) {
			handleException(ivjExc);
		}
	};
	return ivjNumber9;
}


/**
 * Return the NumberBack property value.
 * @return JButton
 */
private JButton getNumberBack() {
	if (ivjNumberBack == null) {
		try {
			ivjNumberBack = new JButton("del");
			ivjNumberBack.setName("NumberBack");
			ivjNumberBack.setFont(new Font("dialog", 0, 8));
		} catch (Throwable ivjExc) {
			handleException(ivjExc);
		}
	};
	return ivjNumberBack;
}
/**
 * Return the NumberDot property value.
 * @return JButton
 */
private JButton getNumberDot() {
	if (ivjNumberDot == null) {
		try {
			ivjNumberDot = new JButton(".");
			ivjNumberDot.setName("NumberDot");
		} catch (Throwable ivjExc) {
			handleException(ivjExc);
		}
	};
	return ivjNumberDot;
}


/**
 * Return the NumberE property value.
 * @return JButton
 */
private JButton getNumberE() {
	if (ivjNumberE == null) {
		try {
			ivjNumberE = new JButton("E");
			ivjNumberE.setName("NumberE");
		} catch (Throwable ivjExc) {
			handleException(ivjExc);
		}
	};
	return ivjNumberE;
}

/**
 * Return the NumberPi property value.
 * @return JButton
 */
private JButton getNumberPi() {
	if (ivjNumberPi == null) {
		try {
			ivjNumberPi = new JButton("pi");
			ivjNumberPi.setName("NumberPi");
		} catch (Throwable ivjExc) {
			handleException(ivjExc);
		}
	};
	return ivjNumberPi;
}

/**
 * Return the NumberSign property value.
 * @return JButton
 */
private JButton getNumberSign() {
	if (ivjNumberSign == null) {
		try {
			ivjNumberSign = new JButton("+/-");
			ivjNumberSign.setName("NumberSign");
			ivjNumberSign.setFont(new Font("dialog", 0, 8));
		} catch (Throwable ivjExc) {
			handleException(ivjExc);
		}
	};
	return ivjNumberSign;
}

/**
 * Return the OutputField property value.
 * @return java.awt.g2TextField
 */
private java.awt.g2TextField getOutputField() {
	if (ivjOutputField == null) {
		try {
			ivjOutputField = new java.awt.g2TextField();
			ivjOutputField.setName("OutputField");
			ivjOutputFieldFont = new Font("dialog", 0, 12);
			ivjOutputField.setFont(ivjOutputFieldFont);
			ivjOutputField.setBackground(Color.white);
			ivjOutputField.setBounds(80, 10, 430, 25);
			ivjOutputField.setEditable(false);
			ivjOutputField.setEnabled(true);
		} catch (Throwable ivjExc) {
			handleException(ivjExc);
		}
	};
	return ivjOutputField;
}

/**
 * Return the Button4 property value.
 * @return JButton
 */
private JButton getRemoveTransform() {
	if (ivjRemoveTransform == null) {
		try {
			ivjRemoveTransform = new JButton("Remove");
			ivjRemoveTransform.setName("RemoveTransform");
		} catch (Throwable ivjExc) {
			handleException(ivjExc);
		}
	};
	return ivjRemoveTransform;
}

/**
 * Return the TransformConst property value.
 * @return Frame
 */
private JDialog getTransformConst() {
	if (ivjTransformConst == null) {
		try {
			JFrame frame = getFrame();
			ivjTransformConst = new JDialog(frame);
			JPanel ConstPanel  = new JPanel();
			ivjTransformConst.setContentPane(ConstPanel);
			ivjTransformConst.setName("TransformConst");
			ivjTransformConst.setTitle("Define Formula");
			ivjTransformConst.setResizable(false);

			ConstPanel.setLayout(null);
			ConstPanel.add(getConstructLabel1(), getConstructLabel1().getName());
			ConstPanel.add(getOutputField(), getOutputField().getName());
			ConstPanel.add(getConstructLabel0(), getConstructLabel0().getName());	  
			ConstPanel.add(getInputField(), getInputField().getName());
			ConstPanel.add(getCreateNewVar(), getCreateNewVar().getName());
			ConstPanel.add(getTransformProperty(), getTransformProperty().getName());
			ConstPanel.add(getDone1(), getDone1().getName());
			ConstPanel.add(getCancel1(), getCancel1().getName());

			ConstPanel.add(getPanel2(), getPanel2().getName());
			ConstPanel.add(getPanel3(), getPanel3().getName());
			ConstPanel.add(getPanel4(), getPanel4().getName());
			ConstPanel.add(getPanel5(), getPanel5().getName());

			ConstPanel.add(getUp(), getUp().getName());
			ConstPanel.add(getLeft(), getLeft().getName());
			ConstPanel.add(getDown(), getDown().getName());

						System.out.println("get here getLeft");

			ConstPanel.add(getRight(), getRight().getName());
		} catch (Throwable ivjExc) {
			handleException(ivjExc);
		}
	}
	return ivjTransformConst;
	
}
		
/**
 * Return the Button5 property value.
 * @return JButton
 */
private JButton getUpdateData() {
	if (ivjUpdateData == null) {
//		try {
			ivjUpdateData = new JButton("Apply");
			ivjUpdateData.setName("UpdateData");
//		} catch (Throwable ivjExc) {
//			handleException(ivjExc);
//		}
	};
	return ivjUpdateData;
}

/**
 * Return the Done1 property value.
 * @return JButton
 */
private JButton getDone1() {
	if (ivjDone1 == null) {
//		try {
			ivjDone1 = new JButton("OK");
			ivjDone1.setName("Done1");
			ivjDone1.setBounds(620, 10, 80, 25); 
//		} catch (Throwable ivjExc) {
//			handleException(ivjExc);
//		}
	};
	return ivjDone1;
}
/**
 * Return the Cancel1 property value.
 * @return JButton
 */
private JButton getCancel1() {
	if (ivjCancel1 == null) {
//		try {
			ivjCancel1 = new JButton("Cancel");
			ivjCancel1.setName("Cancel1");
			ivjCancel1.setBounds(620, 50, 80, 25);
//		} catch (Throwable ivjExc) {
//			handleException(ivjExc);
//		}
	};
	return ivjCancel1;
}

/**
 * Return the TransformChoice property value.
 * @return JComboBox
 */
private JList getTransformChoice() {
	if (ivjTransformChoice == null) {
//		try {
			ivjTransformChoice = new JList(getTransformChoiceModel());
			ivjTransformChoice.setName("TransformChoice");
			ivjTransformChoice.setBackground(Color.white);
/*			transformCache.removeAllElements();
			transformCache.addElement("ABS");
			transformCache.addElement("COS");
			transformCache.addElement("LOG");
			transformCache.addElement("MINUS");
			transformCache.addElement("MULTIPLY");
			transformCache.addElement("SIN");
			transformCache.addElement("SUM");
			transformCache.addElement("More Functions...");
			for(int i=0;i<transformCache.size();i++)
				ivjTransformChoice.addItem(transformCache.elementAt(i));
			ivjTransformChoice.addItem("");
			ivjTransformChoice.setEditable(false);
*///		} catch (Throwable ivjExc) {
	//		handleException(ivjExc);
	//	}
	};
	return ivjTransformChoice;
}
/**
 * Return the VariableChoice property value.
 * @return JComboBox
 */
private JList getVariableChoice() {
	if (ivjVariableChoice == null) {
//		try {
			ivjVariableChoice = new JList(getVariableChoiceModel());
			ivjVariableChoice.setBackground(Color.white);
//		} catch (Throwable ivjExc) {
//			handleException(ivjExc);
//		}
	};
	return ivjVariableChoice;
}

/**
 * Return the JComboBox1 property value.
 * @return JComboBox 
 */
private JComboBox  getVarListChoice() {
	if (ivjVarListChoice == null) {
//		try {
			ivjVarListChoice = new JComboBox ();
			ivjVarListChoice.setName("VarListChoice");
			ivjVarListChoice.setBackground(Color.white);
			ivjVarListChoice.setBounds(220, 10, 150, 20);
//		} catch (Throwable ivjExc) {
//			handleException(ivjExc);
//		}
	};
	return ivjVarListChoice;
}

/**
 * Return the JComboBox1 property value.
 * @return JComboBox 
 */
private JComboBox  getDataSeriesChoice() {
	if (ivjDataSeriesChoice == null) {
		try {
			ivjDataSeriesChoice = new JComboBox ();
			ivjDataSeriesChoice.setName("DataSeriesChoice");
			ivjDataSeriesChoice.setBackground(Color.white);
			ivjDataSeriesChoice.setBounds(10, 10, 150, 20);
		} catch (Throwable ivjExc) {
			handleException(ivjExc);
		}
	};
	return ivjDataSeriesChoice;
}

/**
 * Return the JComboBox11 property value.
 * @return JComboBox 
 */
private JComboBox  getArgLocation() {
	if (ivjArgLocation == null) {
		try {
			ivjArgLocation = new JComboBox ();
			ivjArgLocation.setName("JComboBox11");
			ivjArgLocation.setBackground(Color.white);
			ivjArgLocation.setBounds(408, 10, 80, 20);
			ivjArgLocation.addItem("Outputs");
			ivjArgLocation.addItem("Inputs");
			ivjArgLocation.addItem("Anywhere");
		} catch (Throwable ivjExc) {
			handleException(ivjExc);
		}
	};
	return ivjArgLocation;
}


/**
 * Return the List1 property value.
 * @return JList  
 */
private JList getTransformList() {
	if (ivjTransformList == null) {
		try {
			ivjTransformList = new JList(getTransformListModel());
			ivjTransformList.setBackground(Color.white);
		} catch (Throwable ivjExc) {
			handleException(ivjExc);
		}
	};
	return ivjTransformList;
}

private TransformListCellRenderer getTransformListCellRenderer() {
	if (transformListCellRenderer == null) {
		try {
			transformListCellRenderer = 
				new TransformListCellRenderer(getTransformList(), new Vector());
		} catch (Throwable ivjExc) {
			handleException(ivjExc);
		}
	};
	return transformListCellRenderer;
}
private DefaultListModel getTransformListModel() {
	if (NolFormulaListWKSPModel == null) {
		try {
			NolFormulaListWKSPModel = new DefaultListModel();
		} catch (Throwable ivjExc) {
			handleException(ivjExc);
		}
	};
	return NolFormulaListWKSPModel;
}

private DefaultListModel getTransformChoiceModel() {
	if (transformChoiceModel == null) {
		try {
			transformChoiceModel = new DefaultListModel();
		} catch (Throwable ivjExc) {
			handleException(ivjExc);
		}
	};
	return transformChoiceModel;
}

private DefaultListModel getVariableChoiceModel() {
	if (variableChoiceModel == null) {
		try {
			variableChoiceModel = new DefaultListModel();
		} catch (Throwable ivjExc) {
			handleException(ivjExc);
		}
	};
	return variableChoiceModel;
}

private JScrollPane getListScrollPane() {
	if (listScrollPane == null) {
		try {
			listScrollPane = new JScrollPane(getTransformList());
			listScrollPane.setBounds(10, 40, 478, 170);
			listScrollPane.setBorder(BorderFactory.createLoweredBevelBorder());
		} catch (Throwable ivjExc) {
			handleException(ivjExc);
		}
	};
	return listScrollPane;
}

/**
 * Return the mainPanel property value.
 * @return JPanel
 */
private JPanel getMainPanel() {
	if (mainPanel == null) {
		try {
			mainPanel = new JPanel();
			mainPanel.setName("mainPanel");
			mainPanel.setLayout(null);
		} catch (Throwable ivjExc) {
			handleException(ivjExc);
		}
	};
	return mainPanel;
}

/**
 * Return the Panel2 property value.
 * @return JPanel
 */
private JPanel getPanel2() {
	if (ivjPanel2 == null) {
		try {
			ivjPanel2 = new JPanel();
			ivjPanel2.setName("Panel3");
			ivjPanel2.setLayout(new GridLayout());
			ivjPanel2.setBounds(10, 90, 195, 145);
			ivjPanel2.setBorder(new TitledBorder(new EmptyBorder(1, 1, 1, 1),               
				"Variables:", TitledBorder.LEFT , TitledBorder.TOP));
			JScrollPane listScrollPane = new JScrollPane(getVariableChoice());
			listScrollPane.setBorder(BorderFactory.createLoweredBevelBorder());
			ivjPanel2.add(listScrollPane);
		} catch (Throwable ivjExc) {
			handleException(ivjExc);
		}
	};
	return ivjPanel2;
}
/**
 * Return the Panel3 property value.
 * @return JPanel
 */
private JPanel getPanel3() {
	if (ivjPanel3 == null) {
		try {
			ivjPanel3 = new JPanel();
			ivjPanel3.setName("Panel3");
			ivjPanel3.setLayout(new GridLayout());
			ivjPanel3.setBounds(210, 90, 195, 145);
			ivjPanel3.setBorder(new TitledBorder(new EmptyBorder(1, 1, 1, 1),               
				"Formulas:", TitledBorder.LEFT , TitledBorder.TOP));
			JScrollPane listScrollPane = new JScrollPane(getTransformChoice());
			listScrollPane.setBorder(BorderFactory.createLoweredBevelBorder());
			ivjPanel3.add(listScrollPane);
		} catch (Throwable ivjExc) {
			handleException(ivjExc);
		}
	};
	return ivjPanel3;
}

/**
 * Return the Panel4 property value.
 * @return JPanel
 */
private JPanel getPanel4() {
	if (ivjPanel4 == null) {
		try {
			ivjPanel4 = new JPanel();
			ivjPanel4.setName("Panel4");
			ivjPanel4.setLayout(new GridLayout(4,4,5,5));
			ivjPanel4.setBounds(410, 90, 195, 145);
			ivjPanel4.setBorder(BorderFactory.createTitledBorder("Numerical Inputs"));
			ivjPanel4.add(getNumber1(), getNumber1().getName());
			ivjPanel4.add(getNumber2(), getNumber2().getName());
			ivjPanel4.add(getNumber3(), getNumber3().getName());
			ivjPanel4.add(getNumberPi(), getNumberPi().getName());
			ivjPanel4.add(getNumber4(), getNumber4().getName());
			ivjPanel4.add(getNumber5(), getNumber5().getName());
			ivjPanel4.add(getNumber6(), getNumber6().getName());
			ivjPanel4.add(getNumberSign(), getNumberSign().getName());
			ivjPanel4.add(getNumber7(), getNumber7().getName());
			ivjPanel4.add(getNumber8(), getNumber8().getName());
			ivjPanel4.add(getNumber9(), getNumber9().getName());
			ivjPanel4.add(getNumberBack(), getNumberBack().getName());
			ivjPanel4.add(getNumber0(), getNumber0().getName());
			ivjPanel4.add(getNumberDot(), getNumberDot().getName());
			ivjPanel4.add(getNumberE(), getNumberE().getName());
		} catch (Throwable ivjExc) {
			handleException(ivjExc);
		}
	};
	return ivjPanel4;
}

/**
 * Return the Panel5 property value.
 * @return JPanel
 */
private JPanel getPanel5() {
	if (ivjPanel5 == null) {
		try {
			ivjPanel5 = new JPanel();
			ivjPanel5.setName("Panel5");
			ivjPanel5.setLayout(new GridLayout(0,1,5,5));
			ivjPanel5.setBounds(620, 90, 80, 79);
			ivjPanel5.setBorder(BorderFactory.createTitledBorder("Arguments"));
			ivjPanel5.add(getAddArg(), getAddArg().getName());
			ivjPanel5.add(getDeleteArg(), getDeleteArg().getName());
		} catch (Throwable ivjExc) {
			handleException(ivjExc);
		}
	};
	return ivjPanel5;
}

/**
 * Called whenever the part throws an exception.
 * @param exception Throwable
 */
private void handleException(Throwable exception) {
	System.out.println("in handle=" + exception);

	/* Uncomment the following lines to print uncaught exceptions to stdout */
	// System.out.println("--------- UNCAUGHT EXCEPTION ---------");
	// exception.printStackTrace(System.out);
}


/**
 * Initialize class
 */
private void initialize() {
	setName("NolFormulaListWKSP");
	this.setContentPane(getMainPanel());
	getMainPanel().setLayout(new BorderLayout());

	JPanel dataChoicePane = new JPanel();
	dataChoicePane.setBorder(new TitledBorder(new EmptyBorder(1, 1, 1, 1),               
				"Data Series:", TitledBorder.LEFT , TitledBorder.TOP));
	dataChoicePane.setLayout(new GridLayout());
	dataChoicePane.add(getDataSeriesChoice());

	JPanel varChoicePane = new JPanel();
	varChoicePane.setBorder(new TitledBorder(new EmptyBorder(1, 1, 1, 1),               
				"Variables:", TitledBorder.LEFT , TitledBorder.TOP));
	varChoicePane.setLayout(new GridLayout());
	varChoicePane.add(getVarListChoice());

	JPanel locationPane = new JPanel();
	locationPane.setBorder(new TitledBorder(new EmptyBorder(1, 1, 1, 1),               
				"Location:", TitledBorder.LEFT , TitledBorder.TOP));
	locationPane.setLayout(new GridLayout());
	locationPane.add(getArgLocation());

	JPanel tranListPane = new JPanel();
	tranListPane.setBorder(new TitledBorder(new EmptyBorder(1, 1, 1, 1),               
				"Formulas:", TitledBorder.LEFT , TitledBorder.TOP));
	tranListPane.setLayout(new GridLayout());
	tranListPane.add(getListScrollPane());

	JPanel pane0 = new JPanel(new GridLayout(1,3,5,5));
	pane0.setBorder(new TitledBorder("View"));
	pane0.add(dataChoicePane);
	pane0.add(varChoicePane);
	pane0.add(locationPane);

	JPanel pane1 = new JPanel();
	pane1.setLayout(new BorderLayout());
	pane1.add("North",pane0);
	pane1.add("Center",tranListPane);

	getMainPanel().add("Center",pane1);
	
	pane1 = new JPanel(new GridLayout(8,1,5,5));

	pane1.add(getUpdateData(), getUpdateData().getName());
	pane1.add(getImportTransform(), getImportTransform().getName());
	pane1.add(getExportTransform(), getExportTransform().getName());
	pane1.add(new JPanel());
	pane1.add(getAddTransform(), getAddTransform().getName());
	pane1.add(getModifyTransform(), getModifyTransform().getName());
	pane1.add(getMergeTransform(), getMergeTransform().getName());
	pane1.add(getRemoveTransform(), getRemoveTransform().getName());
	
	pane0 = new JPanel();
	pane0.setBorder(new TitledBorder(new EmptyBorder(1, 1, 1, 1),               
				"", TitledBorder.LEFT , TitledBorder.TOP));
	pane0.setLayout(new BoxLayout(pane0, BoxLayout.Y_AXIS));
		
	pane0.add(Box.createRigidArea(vpad10));
	pane0.add(pane1);
	pane0.add(Box.createRigidArea(vpad200));
	pane0.add(Box.createVerticalGlue());

	getMainPanel().add("East",pane0);

	getTransformList().setCellRenderer(getTransformListCellRenderer());
	initializeAttribute();
}
private void initializeAttribute(){
	/* User defined attribute*/
	this.currentFormula = new Transform(dataSeriesIndex);
	this.currentPosition = -1;
	this.moveFrom = -1;
	this.moveTo = -1;
	this.isInOrOut = false;
	this.funcMode = 0;
	this.varTransformIndex = new Vector();
	this.editedInputIndex = new Vector();
	this.editedOutputIndex = 0;
	this.editedInputStart = 0;
	this.editedInputEnd = 0;
	this.numberInput = new String();
	String title = "Formula List: [" + this.transformer.getName()+"]";
	this.setTitle(title);
	this.currentVariable = "All Variables";
//	this.transformCache = new Vector();
}
/**
 * Initialize connection
 */
private void initConnections() {
	getArgLocation().addItemListener(this);
	getAddTransform().addActionListener(this);
	getDone1().addActionListener(this);
	getCancel1().addActionListener(this);
//	getVariableChoice().addItemListener(this);
	getVariableChoice().addListSelectionListener(this);
//	getTransformChoice().addItemListener(this);
	getTransformChoice().addListSelectionListener(this);
//	getInputField().addFocusListener(getFocusListener());
	getInputField().addMouseListener(getMouseListener());
 	getInputField().addKeyListener(getKeyListener());
//	getOutputField().addFocusListener(getFocusListener());
 	getOutputField().addMouseListener(getMouseListener());
	getOutputField().addKeyListener(getKeyListener());
//	getTransformConst().addWindowListener(getWindowListener());
	getDown().addActionListener(this);
	getLeft().addActionListener(this);
	getRight().addActionListener(this);
	getUp().addActionListener(this);
	getAddArg().addActionListener(this);
	getDeleteArg().addActionListener(this);
	getNumber1().addActionListener(this);
	getNumber2().addActionListener(this);
	getNumber3().addActionListener(this);
	getNumber4().addActionListener(this);
	getNumber5().addActionListener(this);
	getNumber6().addActionListener(this);
	getNumber7().addActionListener(this);
	getNumber8().addActionListener(this);
	getNumber9().addActionListener(this);
	getNumber0().addActionListener(this);
	getNumberDot().addActionListener(this);
	getNumberE().addActionListener(this);
	getNumberPi().addActionListener(this);
	getNumberSign().addActionListener(this);
	getNumberBack().addActionListener(this);
	getCreateNewVar().addActionListener(this);
	getTransformProperty().addActionListener(this);
	getVarListChoice().addItemListener(this);
	getDataSeriesChoice().addItemListener(this);
	getTransformList().addListSelectionListener(this);
	getTransformList().addMouseListener(getMouseListener());
	getModifyTransform().addActionListener(this);
	getRemoveTransform().addActionListener(this);
	getUpdateData().addActionListener(this);
	getMergeTransform().addActionListener(this);
	getImportTransform().addActionListener(this);
	getExportTransform().addActionListener(this);
  
/*	getMoveDialogFrame().addWindowListener(this);

	getInputField().addKeyListener(getKeyListener());
 	getOutputField().addMouseListener(getMouseListener());


	getMoveDone().addActionListener(this);
	getMoveFromLine().addActionListener(this);
	getMoveToLine().addActionListener(this);
	getMoveCancel().addActionListener(this);

	getHelp().addActionListener(this);
	getOutputField().addActionListener(this);
	getArgUp().addActionListener(this);
	getArgLeft().addActionListener(this);
	getArgDown().addActionListener(this);
	getArgRight().addActionListener(this);
*/
}
/**
 * Method to handle events for the ItemListener interface.
 * @param e ItemEvent
 */
public void itemStateChanged(ItemEvent e) {
	if ((e.getSource() == getVarListChoice()) ) {
		conn7(e);
	}
	if ((e.getSource() == getArgLocation()) ) {
		conn8(e);
	}
	if ((e.getSource() == getDataSeriesChoice()) ) {
		conn11(e);
	}
/*	if ((e.getSource() == getTransformChoice()) ) {
		conn16(e);
	}
	if ((e.getSource() == getVariableChoice()) ) {
		conn17(e);
	}
*/
}
public void valueChanged(ListSelectionEvent e) {
	if ((e.getSource() == getTransformList()) ) {
		conn10(e);
	}else if((e.getSource() == getTransformChoice()) ){
		conn16(e);
	}else if((e.getSource() == getVariableChoice()) ){
		conn17(e);
	}
}
/**
 * Method to handle events for the gTransformEventListener interface.
 * @param e gTransformEvent
 */
/*	public void transformerMaskChanged(TransformerEvent e){}
	public void transformerVariableAdded(TransformerEvent e){}
	public void transformerVariableRemoved(TransformerEvent e){}
	public void transformerDataChanged(TransformerEvent e){	}
	public void transfomerLabelCategoryAdded(TransformerEvent e) {	}
	public void transfomerLabelCategoryRemoved(TransformerEvent e){	}
	public void transfomerDataPointsLabeled(TransformerEvent e){	}
	public void transformerTransformerChanged(TransformerEvent e){	}
 */

	public void transfomerTransformListChanged(TransformerEvent evt){
		if (this.transformer.equals((Transformer)evt.getTransformer())){
			noFireAction = true;
			System.out.println("transformChanged currentPosition 1 = "+currentPosition);
			if(transformer.getNumberOfDataSeries() != getDataSeriesChoice().getItemCount()-1){
				displayDataSeriesChoice();
			}
			displayTransList(currentVariable);
			System.out.println("transformChanged currentPosition 2= "+currentPosition);
			getTransformList().setSelectedIndex(this.currentPosition );
			
			if(dataSeriesIndex>=this.transformer.getNumberOfDataSeries()){
				if(transformer.getNumberOfVariables() != getVarListChoice().getItemCount()-1)
					displayVarChoice();
			}else{
				int[] vars = transformer.getVariableNumbers(dataSeriesIndex);
				if(vars.length != getVarListChoice().getItemCount()-1)
					displayVarChoice();
			}
			noFireAction = false;
		}
	}
/**
 * Method to handle events for the ActionListener interface.
 * @param e ActionEvent
 */
public void actionPerformed(ActionEvent e) {
	if ((e.getSource() == getAddTransform()) ) {
		conn1(e);
	}
	if ((e.getSource() == getModifyTransform()) ) {
		conn2(e);
	}
	if ((e.getSource() == getRemoveTransform()) ) {
		conn3(e);
	}
	if ((e.getSource() == getUpdateData()) ) {
		conn4(e);
	}
	if ((e.getSource() == getCreateNewVar()) ) {
		conn9(e);
	}
	if ((e.getSource() == getDone1()) ) {
		conn12(e);
	}
	if ((e.getSource() == getCancel1()) ) {
		conn13(e);
	}
	if ((e.getSource() == getAddArg()) ) {
		conn14(e);
	}
	if ((e.getSource() == getDeleteArg()) ) {
		conn15(e);
	}
	if ((e.getSource() == getTransformProperty()) ) {
		conn18(e);
	}
	if ((e.getSource() == getMergeTransform()) ) {
		conn20(e);
	}	
	if ((e.getSource() == getImportTransform()) ) {
		conn21(e);
	}	
	if ((e.getSource() == getExportTransform()) ) {
		conn22(e);
	}	
	if ((e.getSource() == getNumber1()) ) {
		conn23(e);
	}
	if ((e.getSource() == getNumber2()) ) {
		conn24(e);
	}
	if ((e.getSource() == getNumber3()) ) {
		conn25(e);
	}
	if ((e.getSource() == getNumber4()) ) {
		conn26(e);
	}
	if ((e.getSource() == getNumber5()) ) {
		conn27(e);
	}
	if ((e.getSource() == getNumber6()) ) {
		conn28(e);
	}
	if ((e.getSource() == getNumber7()) ) {
		conn29(e);
	}
	if ((e.getSource() == getNumber8()) ) {
		conn30(e);
	}
	if ((e.getSource() == getNumber9()) ) {
		conn31(e);
	}
	if ((e.getSource() == getNumber0()) ) {
		conn32(e);
	}
	if ((e.getSource() == getNumberDot()) ) {
		conn33(e);
	}
	if ((e.getSource() == getNumberE()) ) {
		conn34(e);
	}
	if ((e.getSource() == getNumberPi()) ) {
		conn35(e);
	}
	if ((e.getSource() == getUp()) ) {
		conn37(e);
	}
	if ((e.getSource() == getLeft()) ) {
		conn38(e);
	}
	if ((e.getSource() == getDown()) ) {
		conn39(e);
	}
	if ((e.getSource() == getRight()) ) {
		conn40(e);
	}
	if ((e.getSource() == getNumberSign()) ) {
		conn41(e);
	}
	if ((e.getSource() == getNumberBack()) ) {
		conn42(e);
	}
}

/** Display the new variable Choice items.*/
	public void displayDataSeriesChoice(){
		int dsNumber = this.transformer.getNumberOfDataSeries();
		getDataSeriesChoice().removeAllItems();
		for(int i=0;i<dsNumber;i++){
			String n = this.transformer.getDataSeriesName(i);
			getDataSeriesChoice().addItem(n);
		}
		getDataSeriesChoice().addItem("All");
	}


/** Display the new variable Choice items.*/
	public void displayVarChoice(){
		int nds = this.transformer.getNumberOfDataSeries();
		if(dataSeriesIndex >= 0 && dataSeriesIndex< nds){
			int[] varNumbers = this.transformer.getVariableNumbers(dataSeriesIndex);
			Vector colInfo = this.transformer.getColumnInfo();	
			getVariableChoiceModel().removeAllElements();
			getVarListChoice().removeAllItems();
			getVarListChoice().addItem("All Variables");
			for(int i=0;i<varNumbers.length;i++){
//				String n = new String(((Column)colInfo.elementAt(varNumbers[i])).getTag());
				String n = new String(((Column)colInfo.elementAt(varNumbers[i])).getName());
				getVariableChoiceModel().addElement(n);
				getVarListChoice().addItem(n);	
			}
		}else{
			Vector colInfo = this.transformer.getColumnInfo();	
			getVariableChoiceModel().removeAllElements();
			getVarListChoice().removeAllItems();
			getVarListChoice().addItem("All Variables");
			for(int i=0;i<colInfo.size();i++){
//				String n = new String(((Column)colInfo.elementAt(i)).getTag());
				String n = new String(((Column)colInfo.elementAt(i)).getName());
//				getVariableChoiceModel().addElement(n);
				getVarListChoice().addItem(n);	
			}
		}
//		getVariableChoice().addItem("");

	}

	private void displayTransformChoice(){
		getTransformChoiceModel().removeAllElements();
		getTransformChoiceModel().addElement(TransformMap.transforms[7]);
		for(int i=0;i<5;i++){
			getTransformChoiceModel().addElement(TransformMap.transforms[i]);
		}
		getTransformChoiceModel().addElement("More Functions...");
	}
/** Add the current transform into the transform list of the transformer at
cuurent position.*/
	public void addTransform(Transform tf){
		System.out.println("in addTransform");
		int position = getCurrentPosition(this.currentPosition);
		if(position == -1)
			position = this.transformer.getTransforms().size();	
		if(position >= this.transformer.getTransforms().size()){
			System.out.println("get add out loop1");
			this.transformer.addTransform(tf);
		}else{
			System.out.println("get add out loop2");
			this.transformer.addTransform(tf,position);
		}
	}
/** Add the current transform into the transform list of the OfflineTransformer at
cuurent position.*/
	public void modifyTransform(Transform tf){
		System.out.println("in modifyTransform");
		int position = getCurrentPosition(this.currentPosition);
		System.out.println("in modifyTransform position= " + position);

		if(position > this.transformer.getTransforms().size() || position == -1){
			return;
		}else if(position == this.transformer.getTransforms().size()){
			this.transformer.addTransform(tf);
		}else{
			this.transformer.modifyTransform(tf,position);
		}

	}
 /** Get the index of the current position in the global transform list.*/
	private int getCurrentPosition(int listPosition){

		if(varTransformIndex == null) return listPosition;
		if(varTransformIndex.size() == 0) return listPosition;

		Vector tfl = this.transformer.getTransforms();
		if(listPosition >= this.varTransformIndex.size()){
			Transform tf = (Transform)this.varTransformIndex.lastElement(); 
			for(int i=0;i<tfl.size();i++){
				if(tf == tfl.elementAt(i))
				return i+1;
			}
		}else{
			Transform tf = (Transform)this.varTransformIndex.elementAt(listPosition); 
			for(int i=0;i<tfl.size();i++){
				if(tf == tfl.elementAt(i))
					return i;
			}
		}
		return -1;
	}

/** Appending number to the number input.*/
	private void appendNumberInput(String str){
		System.out.println(str);
		try{
			Double doubleInput = Double.valueOf(str);
			Object inputObj = editedInputIndex.lastElement();
			if(inputObj == this.currentFormula) return;
			modifycurrentFormula((Transform)editedInputIndex.elementAt(editedInputIndex.size()-2), str);
			showInputField();
			this.numberInput = str;
		}catch(NumberFormatException e){	
		}
		System.out.println(numberInput);
	}

/** Display the transform list for current variable.*/
	public void displayTransList(String currentVarSelect){
		
		Vector tfl = this.transformer.getTransforms();
		getTransformListCellRenderer().modifyContent(tfl);
		this.varTransformIndex.removeAllElements();

		if(tfl == null)
			System.out.println("no tfl");

		if(currentVarSelect.equals("All Variables")){
			getTransformListModel().removeAllElements();
			for(int i=0;i<tfl.size();i++){
				Transform tf = (Transform)tfl.elementAt(i);
//				System.out.println("d s #="+ this.transformer.getDataSeriesNumber(tf));
//				System.out.println(" exist d s #="+ dataSeriesIndex);
				if(dataSeriesIndex<this.transformer.getNumberOfDataSeries()){
					if(this.transformer.getDataSeriesNumber(tf) == dataSeriesIndex){
						getTransformListModel().addElement(new Integer(i+1));
						this.varTransformIndex.addElement(tf);
					}
				}else{
					getTransformListModel().addElement(new Integer(i+1));
					this.varTransformIndex.addElement(tf);
				}
			}
			getTransformListModel().addElement(new Integer(0));
		}else{
			getTransformListModel().removeAllElements();
			for(int i=0;i<tfl.size();i++){
				Transform tf = (Transform)tfl.elementAt(i);
				if(displayMode == 0){ 
					if(tf.hasOutput(currentVarSelect)){
						getTransformListModel().addElement(new Integer(i+1));
						this.varTransformIndex.addElement(tf);
					}
				}else if(displayMode == 1){
					if(tf.hasInput(currentVarSelect)){
						getTransformListModel().addElement(new Integer(i+1));
						this.varTransformIndex.addElement(tf);
					}
				}else if(displayMode == 2){
					if(tf.hasVariable(currentVarSelect)){
						getTransformListModel().addElement(new Integer(i+1));
						this.varTransformIndex.addElement(tf);
					}
				}
			}
			getTransformListModel().addElement(new Integer(0));
		}
		getListScrollPane().validate();

	}

/** Display the output field of the transform constructor.*/
	public void showOutputField(){

 		System.out.println("showOutputField current transform = "+ currentFormula.toString());

		if(currentFormula == null){
			currentFormula = new Transform(dataSeriesIndex);
//			getTransformChoice().setSelectedItem("");
			getOutputField().setText(new String("???"));
			if(!this.isInOrOut){
				getOutputField().selectAll();
//				getVariableChoice().setSelectedItem("");
				getOutputField().requestFocus();
				getInputField().select(0,0);
			}else{
				getOutputField().select(0,0);
			}
			return;
		}
		String s ="";
		int startHighLight  = 0;
		int endHighLight  = 0;
		Vector editedOutputs = this.currentFormula.getOutputs();
		for(int i=0;i<editedOutputs.size();i++){
			if(editedOutputIndex == i){
				startHighLight = s.length();
				s = s+editedOutputs.elementAt(i).toString();
				endHighLight = s.length();
			}else{
				s = s+editedOutputs.elementAt(i).toString();
			}
			if(i<editedOutputs.size()-1) s = s+" , ";
		}
		getOutputField().setText(s);
		if(!this.isInOrOut){
			getOutputField().select(startHighLight,endHighLight);
			if(getOutputField().getSelectedText().equals("???"))
//				getVariableChoice().setSelectedItem("");
			getOutputField().requestFocus();
			getInputField().select(0,0);
		}else{
			getOutputField().select(0,0);
		}
	}

/** Display the input field of the transform constructor.*/
	public void showInputField(){

		if(currentFormula == null){
			currentFormula = new Transform(dataSeriesIndex);
//			getTransformChoice().setSelectedItem("");
			getInputField().setText(new String("???"));
			if(this.isInOrOut){
				getInputField().selectAll();
//				getVariableChoice().setSelectedItem("");
				getInputField().requestFocus();
				getOutputField().select(0,0);
			}else{
				getInputField().select(0,0);
			}
			return;
		}
		String m = this.currentFormula.getTransform();
		if(m==""){
//			getTransformChoice().setSelectedItem("");
			getInputField().setText(new String("???"));
			if(this.isInOrOut){
				getInputField().selectAll();
//				getVariableChoice().setSelectedItem("");
				getInputField().requestFocus();
				getOutputField().select(0,0);
			}else{
				getInputField().select(0,0);
			}
			return;
		}
		String s = m+"(";
		Vector editedInputs = currentFormula.getInputs();

		if(editedInputIndex.lastElement() == currentFormula) {
			for(int i=0;i<editedInputs.size();i++){
				s = s+editedInputs.elementAt(i).toString();
				if(i<editedInputs.size()-1) s = s+" , ";
			}
			s = s+")";
			getInputField().setText(s);
			if(this.isInOrOut){
				getInputField().selectAll();
				getInputField().requestFocus();
				getOutputField().select(0,0);
			}else{
				getInputField().select(0,0);
			}

//			System.out.println("called 1 position");
			
			return;
		}
		editedInputStart = 0;
		editedInputEnd = 0;
		for(int i=0;i<editedInputs.size();i++){
			Object inputObj = editedInputs.elementAt(i);
 			if(editedInputEnd !=0 || editedInputStart !=0){
				s = s+inputObj.toString();
			}else if(editedInputIndex.lastElement() == inputObj){
				editedInputStart = s.length();
				s = s+inputObj.toString();
				editedInputEnd = s.length();
			}else if(inputObj instanceof InnerTransform){
				s = findSelectString(s,(InnerTransform)inputObj);
			}else{
				s = s+inputObj.toString();
			}
			if(i<editedInputs.size()-1) s = s+" , ";
		}
		s = s+")";
		getInputField().setText(s);
		if(this.isInOrOut){
			getInputField().select(editedInputStart,editedInputEnd);
			if(getInputField().getSelectedText().equals("???"))
//				getVariableChoice().setSelectedItem("");
			getInputField().requestFocus();
			getOutputField().select(0,0);
		}else{
			getInputField().select(0,0);
		}
	}
/** Convert the inner transform to string and find the selected substring at same time.*/
	private  String findSelectString(String str, InnerTransform trans){
		String calculator = trans.getTransClass();
		String m = trans.getTransform();
		if(calculator.equals("TransformCalculator")){
			str = str + m + "(";
		}else{
			str = str + calculator + "." + m + "(";
		}
		Vector editedInputs = trans.getInputs();
		for(int i=0;i<editedInputs.size();i++){
			Object inputObj = editedInputs.elementAt(i);
 			if(editedInputEnd !=0 || editedInputStart !=0){
				str = str+inputObj.toString();	
			}else if(editedInputIndex.lastElement() == inputObj){
				editedInputStart = str.length();
				str = str+inputObj.toString();
				editedInputEnd = str.length();
			}else if(inputObj instanceof InnerTransform){
				str = findSelectString(str,(InnerTransform)inputObj);
			}else{
				str = str+inputObj.toString();
			}

			if(i<editedInputs.size()-1) str = str+" , ";
		}
		str = str+")";
		return str;
	}
/** Modify current transform.*/
	private void modifycurrentFormula(Transform trans, Object newObj){
		if(newObj == editedInputIndex.lastElement()) return;
		Vector editedInputs = trans.getInputs();
		for(int i=0;i<editedInputs.size();i++){
			Object inputObj = editedInputs.elementAt(i);
			if(editedInputIndex.lastElement() == inputObj){
				editedInputs.setElementAt(newObj, i);
				editedInputIndex.setElementAt(newObj, editedInputIndex.size()-1);
			}else if(inputObj instanceof InnerTransform){
				modifycurrentFormula((InnerTransform)inputObj, newObj);
			}
		}
	}


/** The adapter class for window action of the constructor.*/	
	class g2WindowAdapter extends WindowAdapter{
		public void windowClosing(WindowEvent e) {
			if(e.getSource() == getTransformConst()){
				getTransformConst().setVisible(false);
			}
		}
	}

/** The adapter class for capture the key input actions.*/	
	class g2KeyAdapter extends KeyAdapter{
	
	/**
	 * Method to handle events for the KeyListener interface.
	 * @param e KeyEvent
	*/
	/* WARNING: THIS METHOD WILL BE REGENERATED. */
	public void keyTyped(KeyEvent e) {
		if(e.getSource() == getInputField()){
//			System.out.println("get keyTyped");
			if(String.valueOf(e.getKeyChar()).equals("1")){
				conn23(new ActionEvent(getNumber1(),0,""));
			}	
			if(String.valueOf(e.getKeyChar()).equals("2")){
				conn24(new ActionEvent(getNumber2(),0,""));
			}	
			if(String.valueOf(e.getKeyChar()).equals("3")){
				conn25(new ActionEvent(getNumber3(),0,""));
				}	
			if(String.valueOf(e.getKeyChar()).equals("4")){
				conn26(new ActionEvent(getNumber4(),0,""));
			}	
			if(String.valueOf(e.getKeyChar()).equals("5")){
				conn27(new ActionEvent(getNumber5(),0,""));
			}	
			if(String.valueOf(e.getKeyChar()).equals("6")){
				conn28(new ActionEvent(getNumber6(),0,""));
			}	
			if(String.valueOf(e.getKeyChar()).equals("7")){
				conn29(new ActionEvent(getNumber7(),0,""));
			}	
			if(String.valueOf(e.getKeyChar()).equals("8")){
				conn30(new ActionEvent(getNumber8(),0,""));
			}	
			if(String.valueOf(e.getKeyChar()).equals("9")){
				conn31(new ActionEvent(getNumber9(),0,""));
			}	
			if(String.valueOf(e.getKeyChar()).equals("0")){
				conn32(new ActionEvent(getNumber0(),0,""));
			}	
			if(String.valueOf(e.getKeyChar()).equals("e") || String.valueOf(e.getKeyChar()).equals("E") ){
				conn34(new ActionEvent(getNumberE(),0,""));
			}	
			if(String.valueOf(e.getKeyChar()).equals(".")){
				conn33(new ActionEvent(getNumberDot(),0,""));
			}	
		}
	}
	/**
	 * Method to handle events for the KeyListener interface.
	 * @param e KeyEvent
	*/
	public void keyPressed(KeyEvent e) {
//		System.out.println("get keyPressed");
	
		if(e.getKeyCode() == KeyEvent.VK_BACK_SPACE ){
			conn42(new ActionEvent(getNumberBack(),0,""));
		}
	
		if(e.getKeyCode() == KeyEvent.VK_UP ){
			conn37(new ActionEvent(getUp(),0,""));
		}
		if(e.getKeyCode() == KeyEvent.VK_LEFT){
			conn38(new ActionEvent(getLeft(),0,""));
		}
		if(e.getKeyCode() == KeyEvent.VK_DOWN){
			conn39(new ActionEvent(getDown(),0,""));
		}
		if(e.getKeyCode() == KeyEvent.VK_RIGHT){
			conn40(new ActionEvent(getRight(),0,""));
		}
 
		if(e.getKeyCode() == KeyEvent.VK_INSERT){
			conn14(new ActionEvent(getAddArg(),0,""));
		}
		if(e.getKeyCode() == KeyEvent.VK_DELETE ){
			conn15(new ActionEvent(getDeleteArg(),0,""));
		}
	}
}



/** The adapter class for capture the transform list drag and drop actions.*/	
	class g2MouseAdapter extends MouseAdapter{
 
		public void mousePressed(MouseEvent e){
			if(e.getSource() == getTransformList()){
				if(funcMode == 0){
					int position = e.getY()/16;
					int limit = NolFormulaListWKSP.this.varTransformIndex.size();
					if(position >= limit){
						NolFormulaListWKSP.this.moveFrom = getCurrentPosition(limit-1);
					}else{
						NolFormulaListWKSP.this.moveFrom = getCurrentPosition(position);
					}
				}
				getTransformList().setCursor(new Cursor(Cursor.HAND_CURSOR));
			}
		}

		public void mouseClicked(MouseEvent e){
			if(e.getSource() == getInputField()){
				NolFormulaListWKSP.this.isInOrOut = true;
				String m = NolFormulaListWKSP.this.currentFormula.getTransform();
				if(m == ""){
					showInputField();
					return;
				}
				String s = m+"(";
				int sw = getInputFieldFontMetrics().stringWidth(s);
				if(sw+4 > e.getX()){
//					System.out.println("mark 3");
					editedInputIndex.removeAllElements();
					editedInputIndex.addElement(currentFormula);
					showInputField();
					return;
				}
 				Vector editedInputs = currentFormula.getInputs();
				editedInputIndex.removeAllElements();
				editedInputIndex.addElement(currentFormula);
				findClick = false;
				for(int i=0;i<editedInputs.size();i++){
					Object inputObj = editedInputs.elementAt(i);
					if(inputObj instanceof InnerTransform){
						s = findSelectObj(s,(InnerTransform)inputObj, e.getX());
						if(findClick)break;
					}else{
						s = s+inputObj.toString();
						sw = getInputFieldFontMetrics().stringWidth(s);
						if(sw+4 > e.getX()){
//							System.out.println("mark 4");
							editedInputIndex.addElement(inputObj);
							break;
						}
					}
					if(i<editedInputs.size()-1) s = s+" , ";
				}
				showInputField();
//				System.out.println("X=" +e.getX());			
//				System.out.println("editedInputIndex=" +editedInputIndex.toString());			

			}else if(e.getSource() == getOutputField()){
				NolFormulaListWKSP.this.isInOrOut = false;
				String s ="";
				Vector editedOutputs = NolFormulaListWKSP.this.currentFormula.getOutputs();
				editedOutputIndex = editedOutputs.size()-1;
				for(int i=0;i<editedOutputs.size();i++){
//					if(editedOutputs.elementAt(i) == null) System.out.println("2524 null el=");
					s = s+editedOutputs.elementAt(i).toString();
					int sw = getOutputFieldFontMetrics().stringWidth(s);
	//				System.out.println("sw=" +sw);			
					if(sw+4 > e.getX()){
						editedOutputIndex = i;
						break;
					}
					if(i<editedOutputs.size()-1) s = s+" , ";
				}
				showOutputField();
			}
		}
		public void mouseReleased(MouseEvent e){
			if(e.getSource() == getTransformList()){
			 	if(funcMode == 0 && NolFormulaListWKSP.this.moveFrom != -1){
					noFireAction = true;
					getTransformList().setCursor(new Cursor(Cursor.DEFAULT_CURSOR));
					currentPosition = getTransformList().getSelectedIndex();					
					int limit = NolFormulaListWKSP.this.varTransformIndex.size();
					if(currentPosition >= limit){
						moveTo = getCurrentPosition(currentPosition - 1);
					}else{
						moveTo = getCurrentPosition(currentPosition);
					}
					if(!NolFormulaListWKSP.this.transformer.moveTransform(moveFrom, moveTo))
						Toolkit.getDefaultToolkit().beep();
					noFireAction = false;
				}
			} 
		}	
	}

/** Convert the inner transform to string and find the selected substring at same time.*/
	private  String findSelectObj(String str, InnerTransform trans, int x){
		
		editedInputIndex.addElement(trans);
		
		String calculator = trans.getTransClass();
		String m = trans.getTransform();
		if(calculator.equals("TransformCalculator")){
			str = str + m + "(";
		}else{
			str = str + calculator + "." + m + "(";
		}
		int sw = getInputFieldFontMetrics().stringWidth(str);
		if(sw+4 > x){
//			System.out.println("mark 1");
			findClick = true;
			return str;
		}
		Vector editedInputs = trans.getInputs();
		for(int i=0;i<editedInputs.size();i++){
			Object inputObj = editedInputs.elementAt(i);
			if(inputObj instanceof InnerTransform){
				findSelectObj(str,(InnerTransform)inputObj,x);
				if(findClick) return str;
			}else{
				str = str+inputObj.toString();
				sw = getInputFieldFontMetrics().stringWidth(str);
				if(sw+4 > x){
//					System.out.println("mark 2");
					editedInputIndex.addElement(inputObj);
					findClick = true;
					return str;
				}
			}
			if(i<editedInputs.size()-1) str = str+" , ";
		}
		str = str+")";
		sw = getInputFieldFontMetrics().stringWidth(str);
		if(sw+4 > x){
			findClick = true;
			return str;
		}
		editedInputIndex.removeElementAt(editedInputIndex.size()-1);
		return str;
	}
/** The adapter class for capture the focus of the input fields.*/	
	class g2FocusAdapter extends FocusAdapter{

		public void focusGained(FocusEvent e){
			if(e.getSource() == getOutputField()){
//				getOutputField().setEnabled(false);
				NolFormulaListWKSP.this.isInOrOut = false;
				getInputField().select(0,0);
				showOutputField();
//				getCreateNewVar().setEnabled(true);
//				System.out.println("focus on outputfield");
			}else if(e.getSource() == getInputField()){
//				getInputField().setEnabled(false);
				NolFormulaListWKSP.this.isInOrOut = true;
				NolFormulaListWKSP.this.getOutputField().select(0,0);
				showInputField();
//				System.out.println("focus on inputfield");
			}
		}

		public void focusLost(FocusEvent e){
			if(e.getSource() == getOutputField()){
//				getOutputField().setEnabled(true);
//				getCreateNewVar().setEnabled(false);
//				System.out.println("focus move from outputfield");
			}else if(e.getSource() == getInputField()){
//				getInputField().setEnabled(true);
//				System.out.println("focus move from inputfield");
			}		
		}

	}
    class TransformListCellRenderer extends JLabel implements ListCellRenderer
    {
	JList   listBox;
	Color highlightColor = new Color(0, 0, 128);
	String[] transformString;

		TransformListCellRenderer(JList listBox, Vector transforms) {
			setOpaque(true);
			this.listBox = listBox;
			if(transforms != null){
				this.transformString = new String[transforms.size()+1];
				transformString[0] = "New Formula";
				for(int i=1;i<=transforms.size();i++){
					transformString[i] = transforms.elementAt(i-1).toString();
				}
			}
		}
		public void modifyContent(Vector transforms){
			this.transformString = new String[transforms.size()+1];
			transformString[0] = "New Formula";
			for(int i=1;i<=transforms.size();i++){
				transformString[i] = transforms.elementAt(i-1).toString();
			}
		}
		public Component getListCellRendererComponent(
            JList list, 
            Object value, 
            int index, 
            boolean isSelected, 
            boolean cellHasFocus) 
        {
			int i = ((Integer)value).intValue();
		    if(listBox.isSelectedIndex(index)) {
				setText(transformString[i]);
				setBackground(highlightColor);
				setForeground(Color.white);
			} else {
				setText(transformString[i]);
				setBackground(Color.white);
				setForeground(Color.black);
			}
			return this;
		}
    }

/** Refresh the current transform.*/
	private void refreshcurrentFormula(){

		currentFormula = new Transform(dataSeriesIndex);
		//Outputs:
		editedOutputIndex = 0;
		currentFormula.getOutputs().addElement(new String("???"));
		//Inputs:
		editedInputIndex.removeAllElements();
		editedInputIndex.addElement(currentFormula);
		this.numberInput = new String();
	}

/* debug method*/
	private void showcurrentFormulaList(String local){

		System.out.println(local + " ctf = "+ currentFormula.toString());
		Vector tfl = this.transformer.getTransforms();
		System.out.println("tflsize="+tfl.size());
		for(int i=0;i<tfl.size();i++){
			System.out.println(tfl.elementAt(i).toString());
		}
		Vector cols = this.transformer.getColumnInfo();
		System.out.println("col #="+cols.size());
//		for(int i=0;i<cols.size();i++){
//			System.out.println(cols.elementAt(i).toString());
//		}
	}
}