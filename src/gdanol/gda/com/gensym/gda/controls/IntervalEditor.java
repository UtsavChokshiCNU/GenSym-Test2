
package com.gensym.gda.controls;

import com.gensym.dlgevent.ObjectUpdateEvent;
import com.gensym.controls.FieldType;
import com.gensym.types.G2SyntaxException;

import java.awt.BorderLayout;

/**
IntervalEditor uses {@link IntervalField} as AttributeEditor.
@see com.gensym.gda.controls.IntervalField
*/
public class IntervalEditor extends AbstractAttributeEditor  implements Boundary{

    public IntervalEditor () {
        intervalField = new IntervalField();
        add(intervalField, BorderLayout.CENTER);        
        setAttributeEditor(intervalField);
        setBorder(intervalField.getBorder());
        intervalField.setBorder(null);
    }

    public void setFieldType(FieldType type) {intervalField.setFieldType(type);}

    public FieldType getFieldType() { return intervalField.getFieldType();}

    public void setEnabled(boolean enabled) {
        super.setEnabled(enabled);
        intervalField.setEnabled(enabled);
    }

    public void requestFocus(){
        intervalField.requestFocus();
    }
    
	public boolean isValid() {
		return intervalField.isValid();
	}

    public void setValid(boolean valid) {intervalField.setValid(valid);}

    public IntervalField getIntervalField(){
        return intervalField;
    }

	public void setMinValue(double minvalue) {
		intervalField.setMinValue(minvalue);
	}

	public void setMaxValue(double maxvalue) {
		intervalField.setMaxValue(maxvalue);
	}

	public double getMinValue() {return intervalField.getMinValue();}

	public double getMaxValue() {return intervalField.getMaxValue();}


  private IntervalField intervalField;

}