package com.gensym.gda.dialogs.blocks;

import javax.swing.BoxLayout;
import com.gensym.util.Symbol;
import com.gensym.util.Sequence;
import com.gensym.dlgevent.ObjectChangeListener;
import com.gensym.dlgevent.ObjectChangeEvent;
import com.gensym.dlgevent.ObjectUpdateEvent;

import javax.swing.JPanel;
import com.gensym.gda.controls.*;

public class gdiMSObservation1 extends gdaDialog {
	
	public gdiMSObservation1() {}

	public gdiMSObservation1(java.awt.Frame frame) {
		super(frame);
		topPanel=new gdaPanel(this);
		bottomPanel=new JPanel();
		leftPanel = new gdaPanel(this);
		leftPanel.setMinimumPanelWidth(0);
		rightPanel = new gdaPanel(this);
		rightPanel.setMinimumPanelWidth(0);
		moreRightPanel= new gdaPanel(this);
		moreRightPanel.setMinimumPanelWidth(0);
		
		dpanel.setLayout(new BoxLayout(dpanel, BoxLayout.Y_AXIS));
		dpanel.setMinimumPanelWidth(450);
		dpanel.add(topPanel);
		dpanel.add(bottomPanel);
		bottomPanel.setLayout(new BoxLayout(bottomPanel, BoxLayout.X_AXIS));
		bottomPanel.add(leftPanel);
		bottomPanel.add(rightPanel);
		bottomPanel.add(moreRightPanel);
		
		numberOfStates = new SpinEditor(2, Integer.MAX_VALUE, 1);
		topPanel.placeAttributeEditor(numberOfStates, 
			NUMBER_OF_STATES_, leftPanel.integerFieldType, 0);
		numberOfStates.addObjectChangeListener(new numberOfStatesChangeListener());
			
		outputUncertainty = new SpinEditor(0.0, 1.0, 0.1);
		topPanel.placeAttributeEditor(outputUncertainty, 
			OUTPUT_UNCERTAINTY_, rightPanel.quantityFieldType, 1);

		logic=new LogicEditor();
		topPanel.placeAttributeEditor(logic, LOGIC_, leftPanel.symbolFieldType, 2);
		logic.addObjectChangeListener(new logicChangeListener());
		
		inputType=new InputTypeEditor();
		topPanel.placeAttributeEditor(inputType, INPUT_TYPE_, rightPanel.symbolFieldType, 3);
		inputType.addObjectChangeListener(new inputTypeChangeListener());
		javax.swing.JLabel label = new javax.swing.JLabel(
			"Enter Thresholds with the highest number on top");
		java.awt.GridBagConstraints c=new java.awt.GridBagConstraints();
		c.gridy=4;
		c.gridwidth=c.REMAINDER;
		((java.awt.GridBagLayout)topPanel.getLayout()).setConstraints(label, c);
		topPanel.add(label);
		
		thresholds = new EditableListEditor(localize(MS_UPPER_THRESHOLD_));
		thresholds.setDisableIfNotUpdated(false);
		leftPanel.placeAttributeEditor(thresholds, null,
			MS_UPPER_THRESHOLD_, leftPanel.floatFieldType, 2);

		categories = new EditableListEditor(localize(MS_CATEGORIES_));
		categories.setDisableIfNotUpdated(false);
		leftPanel.placeAttributeEditor(categories, null, MS_CATEGORIES_, 3);

		thresholdsUncertainty = new EditableListEditor(localize(MS_UPPER_THRESHOLD_UNCERTAINTY_));
		thresholdsUncertainty.setDisableIfNotUpdated(false);
		rightPanel.placeAttributeEditor(thresholdsUncertainty, null,
			MS_UPPER_THRESHOLD_UNCERTAINTY_, rightPanel.floatFieldType, 2);

		explanation = new EditableListEditor(localize(MS_EXPLANATION_));
		explanation.setDisableIfNotUpdated(false);
		moreRightPanel.placeAttributeEditor(explanation, null, MS_EXPLANATION_, 3);

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
			rightPanel.setVisible(isFuzzy);
//			thresholdsUncertainty.setVisible(isFuzzy);
			
		}
	}
	
	protected class inputTypeChangeListener implements ObjectChangeListener {
		public void objectChanged(ObjectChangeEvent e) {
			boolean isNumeric=NUMERIC_.equals(e.getChangedObject());
			thresholds.setVisible(isNumeric);
			categories.setVisible(!isNumeric);
		}
	}

	
	protected gdaPanel topPanel;
	protected JPanel bottomPanel;
	protected gdaPanel leftPanel;
	protected gdaPanel rightPanel;
	protected gdaPanel moreRightPanel;
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

	private final static Double defaultTh= new Double(0.0);
	private final static Double defaultThUn= new Double(0.5);
	private final static String defaultCategory = "user-defined-symbol";
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
			rightPanel.setVisible(isSelected());
//			thresholdsUncertainty.setVisible(isSelected()); //FUZZY_ choice is selected
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