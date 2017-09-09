package com.gensym.gda.controls;

import com.gensym.controls.FieldType;

/**
*A class for entering an arbitrary number or NONE
*/
public class SpinOrNoneEditor extends FieldOrCheckEditor implements Boundary{

    /**
    *Construct the class with default SpinField and
    *NONE checkbox placed below it.
    */
	public SpinOrNoneEditor() {
		super(new G2SpinField());
    }
    
    
    /**
    *Construct the class with default SpinField and
    *NONE checkbox placed below it and sets the Spin parameters.
    *@param min minimum spin value
    *@param max maximum spin value
    *@param increment spin increment
    */
	public SpinOrNoneEditor(double min, double max, double increment) {
		super(new G2SpinField(min, max, increment));
    }

    /**
    *Construct the class with
    *NONE checkbox placed below the field.
    *@param field should be of class G2SpinField
    */
	public SpinOrNoneEditor(G2SpinField field) {
		super(field);
    }
    
    /**
    *Construct the class
    *@param field should be of class G2SpinField
    *@param placeCheckBelow <i>true</i> to place the checkbox below the field 
    *                   and <i>false</i> to place it to the right of the field.
    */    
    public SpinOrNoneEditor(G2SpinField field, boolean placeCheckBelow) {
        super(field, placeCheckBelow);
    }

    
    protected G2textfield[] getG2textfields(){
        return new G2textfield[] {(G2textfield)((G2SpinField)getAttributeEditor()).getTextField()};
    }
    
    public void setFieldType(FieldType type){
        ((G2SpinField)getAttributeEditor()).setFieldType(type);
    }
    
    public FieldType getFieldType(){
        return ((G2SpinField)getAttributeEditor()).getFieldType();
    }

	public boolean isValid() {
		return ((G2SpinField)getAttributeEditor()).getTextField().isValid();
	}

    public void setValid(boolean valid) {((G2SpinField)getAttributeEditor()).getTextField().setValid(valid);}

	public void setMinValue(double minvalue) {
		((G2SpinField)getAttributeEditor()).setMinValue(minvalue);
	}

	public void setMaxValue(double maxvalue) {
		((G2SpinField)getAttributeEditor()).setMaxValue(maxvalue);
	}

	public double getMinValue() {return ((G2SpinField)getAttributeEditor()).getMinValue();}

	public double getMaxValue() {return ((G2SpinField)getAttributeEditor()).getMaxValue();}

	public void setIncrement(double increment) {
		((G2SpinField)getAttributeEditor()).setIncrement(increment);
	}

}