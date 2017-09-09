
package com.gensym.gda.controls;

import java.awt.BorderLayout;

import com.gensym.controls.FieldType;
import com.gensym.jcontrols.G2TextField;

/**
SpinEditor uses {@link G2SpinField} as AttributeEditor.
@see G2SpinField
*/
public class SpinEditor extends AbstractAttributeEditor implements Boundary {

    public SpinEditor() {
		spinfield = new G2SpinField();
		add(spinfield, BorderLayout.CENTER);		
		setAttributeEditor(spinfield);
		G2TextField field = (G2TextField)spinfield.getTextField();
	}


    public SpinEditor(double minvalue, double maxvalue, double increment) {
		this();
		spinfield.setMinValue(minvalue);
		spinfield.setMaxValue(maxvalue);
		spinfield.setIncrement(increment);
	}

	public G2SpinField getSpinField() {return spinfield;}

    public void setFieldType(FieldType type) {spinfield.setFieldType(type);}

	public FieldType getFieldType() { return spinfield.getFieldType();}

	public void setEnabled(boolean enabled) {
		super.setEnabled(enabled);
		spinfield.setEnabled(enabled);
	}

	public boolean isValid() {return spinfield.getTextField().isValid();}

    public void setValid(boolean valid) {spinfield.getTextField().setValid(valid);}

	public void setMinValue(double minvalue) {
		spinfield.setMinValue(minvalue);
	}

	public void setMaxValue(double maxvalue) {
		spinfield.setMaxValue(maxvalue);
	}

	public double getMinValue() {return spinfield.getMinValue();}

	public double getMaxValue() {return spinfield.getMaxValue();}
	
	public void setIncrement(double increment) {
		spinfield.setIncrement(increment);
	}

	private G2SpinField spinfield;

}