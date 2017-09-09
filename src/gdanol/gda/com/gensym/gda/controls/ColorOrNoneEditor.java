    
package com.gensym.gda.controls;

import com.gensym.controls.FieldType;

/**
*A class for entering an arbitrary text or NONE
*/
public class ColorOrNoneEditor extends FieldOrCheckEditor{

    /**
    *Construct the class with {@link ColorEditor} and
    *NONE checkbox placed below it.
    */
    public ColorOrNoneEditor() {
    	this (new ColorEditor(), true);
    }

    public ColorOrNoneEditor(ColorEditor field, boolean placeCheckBelow) {
        super(field, placeCheckBelow);
    }

    
    protected G2textfield[] getG2textfields(){
        return new G2textfield[0];
    }
    
    public void setFieldType(FieldType type){}
    
    public FieldType getFieldType(){return null;}
    
}