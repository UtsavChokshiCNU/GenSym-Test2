    
package com.gensym.gda.controls;

import com.gensym.controls.FieldType;

/**
*A class for entering an arbitrary text or NONE
*/
public class TextOrNoneEditor extends FieldOrCheckEditor{

    /**
    *Construct the class with {@link G2textfield} and
    *NONE checkbox placed below it.
    */
    public TextOrNoneEditor() {
    	this (new G2textfield(), true);
    }

    public TextOrNoneEditor(G2textfield field, boolean placeCheckBelow) {
        super(field, placeCheckBelow);
    }

    
    protected G2textfield[] getG2textfields(){
        return new G2textfield[] {(G2textfield)getAttributeEditor()};
    }
    
    public void setFieldType(FieldType type){
        ((G2textfield)getAttributeEditor()).setFieldType(type);
    }
    
    public FieldType getFieldType(){
        return ((G2textfield)getAttributeEditor()).getFieldType();
    }
    
    public boolean isValid() {
		return ((G2textfield)getAttributeEditor()).isValid();
	}

    public void setValid(boolean valid) {((G2textfield)getAttributeEditor()).setValid(valid);}

}