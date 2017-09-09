package com.gensym.gda.dialogs.blocks;

import javax.swing.BoxLayout;
import com.gensym.util.Symbol;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.dlgevent.ObjectChangeListener;
import com.gensym.dlgevent.ObjectChangeEvent;
import com.gensym.dlgevent.ObjectUpdateEvent;

import javax.swing.JPanel;
import com.gensym.gda.controls.*;
import com.gensym.gda.util.GfrCommunicationManager;

public class gdiMSObservation extends BlocksDialog {
	
	public gdiMSObservation() {}

	public gdiMSObservation(java.awt.Frame frame) {
		super(frame);
		topPanel=new BlocksPanel(this);
		bottomPanel=new BlocksPanel(this);

		dpanel.setLayout(new BoxLayout(dpanel, BoxLayout.Y_AXIS));
		dpanel.setMinimumPanelWidth(450);
		dpanel.add(topPanel);
		dpanel.add(bottomPanel);
		bottomPanel.setLayout(new BoxLayout(bottomPanel, BoxLayout.X_AXIS));
		
		numberOfStates = new SpinEditor(2, Integer.MAX_VALUE, 1);
		topPanel.placeAttributeEditor(numberOfStates, 
			NUMBER_OF_STATES_, BlocksPanel.integerFieldType, 0);
		numberOfStates.addObjectChangeListener(new numberOfStatesChangeListener());
			
		outputUncertainty = new SpinEditor(0.0, 1.0, 0.1);
		topPanel.placeAttributeEditor(outputUncertainty, 
			OUTPUT_UNCERTAINTY_, BlocksPanel.quantityFieldType, 1);

		logic=new LogicEditor();
		topPanel.placeAttributeEditor(logic, LOGIC_, BlocksPanel.symbolFieldType, 2);
		logic.addObjectChangeListener(new logicChangeListener());
		
		inputType=new InputTypeEditor();
		topPanel.placeAttributeEditor(inputType, INPUT_TYPE_, BlocksPanel.symbolFieldType, 3);
		inputType.addObjectChangeListener(new inputTypeChangeListener());
		javax.swing.JLabel label = new javax.swing.JLabel(localize("ThreholdsNotificationMessage"));
		java.awt.GridBagConstraints c=new java.awt.GridBagConstraints();
		c.gridy=4;
		c.gridwidth=c.REMAINDER;
		((java.awt.GridBagLayout)topPanel.getLayout()).setConstraints(label, c);
		topPanel.add(label);
		
		thresholds = new EditableListEditor(localize(MS_UPPER_THRESHOLD_));
		thresholds.setDisableIfNotUpdated(false);
		thresholds.setAttribute(MS_UPPER_THRESHOLD_);
		thresholds.setFieldType(BlocksPanel.floatFieldType);
		bottomPanel.registerEditor(thresholds);
		bottomPanel.add(thresholds);

		categories = new EditableListEditor(localize(MS_CATEGORIES_));
		categories.setDisableIfNotUpdated(false);
		categories.setAttribute(MS_CATEGORIES_);
		bottomPanel.registerEditor(categories);
		bottomPanel.add(categories);

		thresholdsUncertainty = new EditableListEditor(localize(MS_UPPER_THRESHOLD_UNCERTAINTY_));
		thresholdsUncertainty.setDisableIfNotUpdated(false);
		thresholdsUncertainty.setAttribute(MS_UPPER_THRESHOLD_UNCERTAINTY_);
		thresholdsUncertainty.setFieldType(BlocksPanel.floatFieldType);
		bottomPanel.registerEditor(thresholdsUncertainty);
		bottomPanel.add(thresholdsUncertainty);

		explanation = new EditableListEditor(localize(MS_EXPLANATION_));
		explanation.setDisableIfNotUpdated(false);
		explanation.setAttribute(MS_EXPLANATION_);
		bottomPanel.registerEditor(explanation);
		bottomPanel.add(explanation);

	}

	private void updateListEditor(EditableListEditor editor, int rows, Object defaultValue) {
		editor.removeCellEditor();
		int nowRows = editor.getRowCount();
		if (rows>nowRows) {
			for (int i=0;i< (rows-nowRows);i++) {
				editor.addRow(new Object[]{defaultValue});
			}
		}  else if (rows<nowRows) {
			for (int i=nowRows - 1;i>=rows;i--) {
				editor.removeRow(i);
			}
		}		
	}
	
	protected class numberOfStatesChangeListener implements ObjectChangeListener {
		public void objectChanged(ObjectChangeEvent e) {
			Number nObject = (Number) e.getChangedObject();
			int nValue=nObject.intValue();
			updateListEditor(thresholds, nValue-1, defaultTh);
			updateListEditor(thresholdsUncertainty, nValue-1, defaultThUn);
			updateListEditor(categories, nValue, defaultCategory);
			updateListEditor(explanation, nValue, defaultExplanation);
		}
	}
	
	protected class logicChangeListener implements ObjectChangeListener {
		public void objectChanged(ObjectChangeEvent e) {
			boolean isFuzzy=FUZZY_.equals(e.getChangedObject());
			thresholdsUncertainty.setVisible(isFuzzy);
			
		}
	}
	
	protected class inputTypeChangeListener implements ObjectChangeListener {
		public void objectChanged(ObjectChangeEvent e) {
			boolean isNumeric=NUMERIC_.equals(e.getChangedObject());
			thresholds.setVisible(isNumeric);
			categories.setVisible(!isNumeric);
		}
	}

	
	public boolean editorsAreValid() {
		if (!super.editorsAreValid())
			return false;
			
		Structure threshold = (Structure)changedAttributes.get(MS_UPPER_THRESHOLD_.toString());
		Sequence thresholdValues=null;
		//validatiog threshold
		if (threshold!=null) {
			thresholdValues = (Sequence)threshold.getAttributeValue(ATTRIBUTE_VALUE_, null);
			if (thresholdValues!=null) {// && thresholdValues.size()>1) {
				int size = thresholdValues.size();
				Double lastValue = (Double) thresholdValues.get(0);
				for (int i=1;i<size;i++) {
					Double nextValue = (Double) thresholdValues.get(i);
					if (nextValue.doubleValue()>lastValue.doubleValue()) {
						GfrCommunicationManager.showAlert(localize("ThreholdsNotificationMessage"));
						return false;
					}
					lastValue=nextValue;
				}
			}
		}
		
		//validating threshold uncertainties
		Structure thresholdU = (Structure)changedAttributes.get(MS_UPPER_THRESHOLD_UNCERTAINTY_.toString());
		Sequence thresholdUValues;
		if (thresholdU!=null) {
			//getting threshold values
			if (threshold==null) {
				threshold=(Structure)attributes.get(MS_UPPER_THRESHOLD_.toString());
				thresholdValues=(Sequence)threshold.getAttributeValue(ATTRIBUTE_VALUE_, null);
			}
			thresholdUValues = (Sequence)thresholdU.getAttributeValue(ATTRIBUTE_VALUE_, null);
			if (thresholdUValues!=null) {
				double lastThreshold=((Double) thresholdValues.get(0)).doubleValue();
				double lastThresholdU=((Double) thresholdUValues.get(0)).doubleValue();
				int size = thresholdUValues.size();
				for (int i=1;i<size;i++) {
					double nextValue = ((Double) thresholdValues.get(i)).doubleValue();
					double nextUValue = ((Double) thresholdUValues.get(i)).doubleValue();
					if ((nextUValue+lastThresholdU)/2.0 > lastThreshold-nextValue) {
						GfrCommunicationManager.showAlert(localize("InvalidThresholdUncertainties"));
						return false;
					}
					lastThreshold=nextValue;
					lastThresholdU=nextUValue;
				}
			}			
		}
		
		//validating categories
		Structure s=(Structure)changedAttributes.get(MS_CATEGORIES_.toString());
		if (s!=null) {
			Sequence categoriesValues = (Sequence)s.getAttributeValue(ATTRIBUTE_VALUE_, null);
			int size = categoriesValues.size();
			for (int i=0;i<size;i++) {
				String currentValue = (String) categoriesValues.get(i);
				if (i<size-1) {
					if (currentValue.equals(otherString))
						categoriesValues.set(i, userDefinedSymbolString);
				} else
					categoriesValues.set(i, otherString);
				if (categoriesValues.indexOf(currentValue, i+1)!=-1 &&
					!currentValue.equals(otherString) && !currentValue.equals(userDefinedSymbolString) &&
					!currentValue.equals(emptyString)) {
					GfrCommunicationManager.showAlert(localize("DuplicateCatergories"));
					return false;
				}
			}
		}
		return true;
	}
	
	protected BlocksPanel topPanel;
	protected BlocksPanel bottomPanel;
	protected LogicEditor logic;
	protected InputTypeEditor inputType;
	protected SpinEditor numberOfStates;
	protected SpinEditor outputUncertainty;
	
	protected EditableListEditor thresholds;
	protected EditableListEditor categories;
	protected EditableListEditor thresholdsUncertainty;
	protected EditableListEditor explanation;

	protected final static Symbol MS_UPPER_THRESHOLD_ = Symbol.intern("MS-UPPER-THRESHOLD");
	protected final static Symbol MS_UPPER_THRESHOLD_UNCERTAINTY_ = Symbol.intern("MS-UPPER-THRESHOLD-UNCERTAINTY");
	protected final static Symbol MS_CATEGORIES_ = Symbol.intern("MS-CATEGORIES");
	protected final static Symbol MS_EXPLANATION_ = Symbol.intern("MS-EXPLANATION");

	protected final static Symbol NUMBER_OF_STATES_ = Symbol.intern("NUM-OF-STATES");
	protected final static Symbol LOGIC_ = Symbol.intern("LOGIC");
	protected final static Symbol OUTPUT_UNCERTAINTY_ = Symbol.intern("OUTPUT-UNCERTAINTY");
	protected final static Symbol INPUT_TYPE_ = Symbol.intern("INPUT-TYPE");
	protected final static Symbol FUZZY_ = Symbol.intern("FUZZY");
	protected final static Symbol DISCRETE_ = Symbol.intern("DISCRETE");
	protected final static Symbol SYMBOLIC_ = Symbol.intern("SYMBOLIC");
	protected final static Symbol NUMERIC_ = Symbol.intern("NUMERIC");
	
	protected final static String emptyString="";
	protected final static String otherString="other";
	protected final static String userDefinedSymbolString="user-defined-symbol";

	private final static Double defaultTh= new Double(0.0);
	private final static Double defaultThUn= new Double(0.5);
	private final static String defaultCategory = userDefinedSymbolString;
	private final static String defaultExplanation= "user-defined-explanation";

	class LogicEditor extends CheckBoxEditor {
		public LogicEditor() {
			setOnvalue(FUZZY_);
			setOffvalue(DISCRETE_);
			setText(localize("Fuzzy"));
		}
		
		public void setDiscrete() {
			if (isSelected()) // if FUZZY_ choice is selected 
				checkbox.doClick();
		}
		
		protected void fireObjectChange(Object value) {
			super.fireObjectChange(value);
			if (FUZZY_.equals(value)) 
				inputType.setNumeric();
		}
		
		public void objectUpdated(ObjectUpdateEvent e) {
			super.objectUpdated(e);
			thresholdsUncertainty.setVisible(isSelected()); //FUZZY_ choice is selected
		}
	}
	
	class InputTypeEditor extends CheckBoxEditor {
		public InputTypeEditor() {
			setOnvalue(NUMERIC_);
			setOffvalue(SYMBOLIC_);
			setText(localize("Numeric"));
		}

		public void setNumeric() {
			if (!isSelected()) // if NUMERIC_ choice is selected 
				checkbox.doClick();
		}
		
		protected void fireObjectChange(Object value) {
			super.fireObjectChange(value);
			if (SYMBOLIC_.equals(value)) 
				logic.setDiscrete();
		}				
		public void objectUpdated(ObjectUpdateEvent e) {
			super.objectUpdated(e);
			thresholds.setVisible(isSelected());
			categories.setVisible(!isSelected());
		}
	}
	
}