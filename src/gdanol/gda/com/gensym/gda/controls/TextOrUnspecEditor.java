package com.gensym.gda.controls;

import com.gensym.util.Symbol;

import com.gensym.controls.FieldType;

/**
*A class for entering an arbitrary text or UNSPECIFIED symbol
*/
public class TextOrUnspecEditor extends FieldOrCheckEditor{

    protected static final Symbol UNSPECIFIED_ = Symbol.intern("UNSPECIFIED");
    
    /**
    *Constructs the class with default SpinField and
    *UNSPECIFIED checkbox placed below it.
    */
    public TextOrUnspecEditor() {
        this(new G2textfield(), true);
    }
    
    /**
    *Constructs the class
    *@param field should be of class G2textfield
    *@param placeCheckBelow <i>true</i> to place the checkbox below the field 
    *                   and <i>false</i> to place it to the right of the field.
    */    
    public TextOrUnspecEditor(G2textfield field, boolean placeCheckBelow) {
        super(field, UNSPECIFIED_, placeCheckBelow);
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

}