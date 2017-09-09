   
package com.gensym.gda.controls;

import com.gensym.controls.FieldType;

/**
*A class for entering an arbitrary interval or NONE
*/
public class IntervalOrNoneEditor extends FieldOrCheckEditor implements Boundary{
    
    /**
    *Construct the class with default IntervalField and
    *NONE checkbox placed below it.
    */
    public IntervalOrNoneEditor() {
        super(new IntervalField(), true);
    }
    
    /**
    *Construct the class with
    *NONE checkbox placed below the field.
    *@param field should be of class IntervalField
    */
    public IntervalOrNoneEditor(IntervalField field) {
        super(field);
    }
    
    /**
    *Construct the class
    *@param field should be of class IntervalField
    *@param placeCheckBelow <i>true</i> to place the checkbox below the field 
    *                  and <i>false</i> to place it to the right of the field.
    */
    public IntervalOrNoneEditor(IntervalField field, boolean placeCheckBelow) {
        super(field, placeCheckBelow);
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