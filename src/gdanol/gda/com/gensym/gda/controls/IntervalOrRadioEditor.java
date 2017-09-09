   
package com.gensym.gda.controls;

import com.gensym.controls.FieldType;
import com.gensym.util.Symbol;

/**
*A class for entering an arbitrary interval or one of the predefined values
*/
public class IntervalOrRadioEditor extends FieldOrRadioEditor implements Boundary{
    
    public IntervalOrRadioEditor() {
        this(new Symbol[] {Symbol.intern("Radio0")});
    }

    /**
    *Construct the class with default IntervalField.
    *@param values an array of predefined symbols
    */
    public IntervalOrRadioEditor(Symbol[] values) {
        super(new IntervalField(), values);
    }

    /**
    *@param field should be of class IntervalField
    *@param values an array of predefined symbols
    */
    public IntervalOrRadioEditor(IntervalField field, Symbol[] values) {
        super(field, values);
    }

    
    protected G2textfield[] getG2textfields(){
        return ((IntervalField)getAttributeEditor()).getFields();
    }
    
    public void setFieldType(FieldType type){
        ((IntervalField)getAttributeEditor()).setFieldType(type);
    }
    
    public FieldType getFieldType(){
        return ((IntervalField)getAttributeEditor()).getFieldType();
    }
    
	public boolean isValid() {
		return ((IntervalField)getAttributeEditor()).isValid();
	}
	
    public void setValid(boolean valid) {((IntervalField)getAttributeEditor()).setValid(valid);}

	public void setMinValue(double minvalue) {
		((IntervalField)getAttributeEditor()).setMinValue(minvalue);
	}

	public void setMaxValue(double maxvalue) {
		((IntervalField)getAttributeEditor()).setMaxValue(maxvalue);
	}

	public double getMinValue() {return ((IntervalField)getAttributeEditor()).getMinValue();}

	public double getMaxValue() {return ((IntervalField)getAttributeEditor()).getMaxValue();}


}