
package com.gensym.gda.dialogs.blocks;


import java.awt.GridBagConstraints;
import javax.swing.JLabel;

import com.gensym.dlgevent.*;
import com.gensym.util.Symbol;
import com.gensym.util.Structure;
import com.gensym.beansruntime.StringVector;
import com.gensym.dlg.WarningDialog;

import com.gensym.gda.controls.*;

/**
UncertaintyBoundPanel contains four controls:
minimum value, maximum value, 
minimum uncertainty value and maximum uncertainty value.
*/
public class UncertaintyBoundPanel extends BoundPanel {


	public UncertaintyBoundPanel(BlocksDialog d) {
    	super(d);
    	minUEditor = null;
    	maxUEditor = null;	
    	createLabels();    	
	}

	public void placeEditors(AbstractAttributeEditor max,
							AbstractAttributeEditor min,
							AbstractAttributeEditor maxU,
							AbstractAttributeEditor minU,
							String title,
							String uncertainty,
							String upper,
							String lower) {
		maxEditor = max;
		minEditor = min;
		maxUEditor = maxU;
		minUEditor = minU;
		titleLabel.setText(title);
		uncertaintyLabel.setText(uncertainty);
		upperLabel.setText(upper);
		lowerLabel.setText(lower);
		
		registerEditor(minEditor);
		registerEditor(minUEditor);
		registerEditor(maxUEditor);
		registerEditor(maxEditor);
		
		setDefaultConstraints();
	    gridBagConstraints.weightx = 1.0;
	    gridBagConstraints.weighty = 1.0;
	    gridBagConstraints.fill = attributeEditorFillConstraint;
	    gridBagConstraints.gridy=1;
	    gridBagConstraints.gridx=1;
	    
	    gridBagLayout.setConstraints(minEditor, gridBagConstraints);
		add(minEditor);
		
	    gridBagConstraints.gridy=2;
	    gridBagLayout.setConstraints(minUEditor, gridBagConstraints);
		add(minUEditor);
		
	    gridBagConstraints.gridx=2;
	    gridBagLayout.setConstraints(maxUEditor, gridBagConstraints);
		add(maxUEditor);
	    
	    gridBagConstraints.gridy=1;
	    gridBagLayout.setConstraints(maxEditor, gridBagConstraints);
		add(maxEditor);		
		
	}

	public void setMinUncertaintyEditor(AbstractAttributeEditor min) {minUEditor = min;}
	public void setMaxUncertaintyEditor(AbstractAttributeEditor max) {maxUEditor = max;}

	public AbstractAttributeEditor getMinUncertaintyEditor() {return minUEditor;}
	public AbstractAttributeEditor getMaxUncertaintyEditor() {return maxUEditor;}

	public void objectUpdated(ObjectUpdateEvent e) {
		if (minUEditor == null || maxUEditor == null)
			return;// *** throw exception? !!!
			
		values.put(minUEditor, e.getUpdatedValue(minUEditor.getAttribute()));
		values.put(maxUEditor, e.getUpdatedValue(maxUEditor.getAttribute()));

		super.objectUpdated(e);
	}

	protected boolean checkNewValue(AbstractAttributeEditor editor, Object value) {
		
		Object oldvalue = values.get(editor);
		values.put(editor, value);

		boolean result = checkNewValue();

		values.put(editor, oldvalue);
		return result;
	}

    protected boolean checkNewValue() {
        
        if (!super.checkNewValue())
			return false;

		double min = ((Number) values.get(minEditor)).doubleValue();
		double max = ((Number) values.get(maxEditor)).doubleValue();
		boolean minuexists;
		double minu;
		boolean maxuexists;
		double maxu;
		
		if (values.get(minUEditor) instanceof Number) {
			minu = ((Number) values.get(minUEditor)).doubleValue();
			minuexists=true;
		} else {
			minu=0;
			minuexists=false;
		}
		if (values.get(maxUEditor) instanceof Number) {
			maxu = ((Number) values.get(maxUEditor)).doubleValue();
			maxuexists=true;
		} else {
			maxu=0;
			maxuexists=false;
		}
		
		double bandwidth = max - min;
		double ubandwidth = maxu + minu;
		if (0.5*ubandwidth>bandwidth) {
			if(!maxuexists) {
				warningDialog(localize("MinUncertaintyInvalid"));
				return false;
			 } else if (!minuexists) {
				warningDialog(localize("MaxUncertaintyInvalid"));
				return false;
			 } else {
				warningDialog(localize("UncertaintiesInvalid"));
				return false;
			 }
		}
		((Boundary)minUEditor).setMaxValue(2*bandwidth-maxu);
		((Boundary)maxUEditor).setMaxValue(2*bandwidth-minu);

		((Boundary)minEditor).setMaxValue(max - 0.5*ubandwidth);
		((Boundary)maxEditor).setMinValue(min + 0.5*ubandwidth);

		return true;        
    }

	protected void createLabels () {
		titleLabel = new JLabel("TitleLabel");
    	uncertaintyLabel = new JLabel("Uncertainty");
    	upperLabel = new JLabel("UpperLabel");
    	lowerLabel = new JLabel("LowerLabel");
    	setDefaultConstraints();
    	
    	gridBagConstraints.anchor = GridBagConstraints.WEST;
    	gridBagConstraints.weightx = 0.0;
  	    gridBagConstraints.gridx = 1;
	    gridBagConstraints.gridy = 0;

	    gridBagLayout.setConstraints(lowerLabel, gridBagConstraints);
	    add(lowerLabel);

	    gridBagConstraints.gridx = 2;
	    gridBagLayout.setConstraints(upperLabel, gridBagConstraints);
	    add(upperLabel);

    	gridBagConstraints.anchor = GridBagConstraints.EAST;    	
  	    gridBagConstraints.gridx = 0;
	    gridBagConstraints.gridy = 1;
	    gridBagLayout.setConstraints(titleLabel, gridBagConstraints);
	    add(titleLabel);
	    
	    gridBagConstraints.gridy = 2;
	    gridBagLayout.setConstraints(uncertaintyLabel, gridBagConstraints);
	    add(uncertaintyLabel);
	}


	/**
	creates UnceraintyBoundPanel for editing the next attributes:
	upper-threshold, lower-threshold, 
	upper-threshold-uncertainty, lower-threshold-uncertainty
	*/
	public static UncertaintyBoundPanel createThresholdUncertaintyPanel(
		BlocksDialog d) {
		UncertaintyBoundPanel ubound = new UncertaintyBoundPanel(d);

		SpinEditor upper = new SpinEditor();
		SpinEditor lower = new SpinEditor();
		SpinOrNoneEditor upperU = new SpinOrNoneEditor(0, Double.MAX_VALUE, 1);
		SpinOrNoneEditor lowerU = new SpinOrNoneEditor(0, Double.MAX_VALUE, 1);

		lower.setAttribute(LOWER_THRESHOLD_);
		lowerU.setAttribute(LOWER_THRESHOLD_UNCERTAINTY_);
		upperU.setAttribute(UPPER_THRESHOLD_UNCERTAINTY_);
		upper.setAttribute(UPPER_THRESHOLD_);

		ubound.placeEditors(upper, lower, upperU, lowerU,
			ubound.localize("Threshold"), ubound.localize("Uncertainty"), 
			ubound.localize("Upper"), ubound.localize("Lower"));
		return ubound;
		
	}
	
	/**
	creates UnceraintyBoundPanel for editing the next attributes:
	interval-end, interval-start, 
	interval-end-uncertainty, interval-start-uncertainty
	*/
		public static UncertaintyBoundPanel createIntervalUncertaintyPanel(
		BlocksDialog d) {
		UncertaintyBoundPanel ubound = new UncertaintyBoundPanel(d);

		IntervalEditor upper = new IntervalEditor();
		IntervalEditor lower = new IntervalEditor();
		IntervalOrNoneEditor upperU = new IntervalOrNoneEditor();
		IntervalOrNoneEditor lowerU = new IntervalOrNoneEditor();

		lower.setAttribute(INTERVAL_START_);
		lowerU.setAttribute(INTERVAL_START_UNCERTAINTY_);
		upperU.setAttribute(INTERVAL_END_UNCERTAINTY_);
		upper.setAttribute(INTERVAL_END_);
		
		ubound.placeEditors(upper, lower, upperU, lowerU,
			ubound.localize("Interval"), ubound.localize("Uncertainty"), 
			ubound.localize("End"), ubound.localize("Start"));
		return ubound;
		
	}

	
	protected AbstractAttributeEditor minUEditor;
	protected AbstractAttributeEditor maxUEditor;
	
	protected JLabel titleLabel;
	protected JLabel uncertaintyLabel;
	protected JLabel upperLabel;
	protected JLabel lowerLabel;
	
	
	protected final static Symbol UPPER_THRESHOLD_ = 
		Symbol.intern("UPPER-THRESHOLD");
	protected final static Symbol LOWER_THRESHOLD_ = 
		Symbol.intern("LOWER-THRESHOLD");
	protected final static Symbol UPPER_THRESHOLD_UNCERTAINTY_ = 
		Symbol.intern("UPPER-THRESHOLD-UNCERTAINTY");
	protected final static Symbol LOWER_THRESHOLD_UNCERTAINTY_ = 
		Symbol.intern("LOWER-THRESHOLD-UNCERTAINTY");
		
	protected final static Symbol INTERVAL_START_ = 
		Symbol.intern("INTERVAL-START");
	protected final static Symbol INTERVAL_END_ = 
		Symbol.intern("INTERVAL-END");
	protected final static Symbol INTERVAL_START_UNCERTAINTY_ = 
		Symbol.intern("INTERVAL-START-UNCERTAINTY");
	protected final static Symbol INTERVAL_END_UNCERTAINTY_ = 
		Symbol.intern("INTERVAL-END-UNCERTAINTY");
	

}