   
package com.gensym.gda.controls;

import com.gensym.controls.FieldType;
import com.gensym.util.Symbol;

/**
*A class for entering an arbitrary text or one of the predefined values
*/
public class TextOrRadioEditor extends FieldOrRadioEditor{
    
    public TextOrRadioEditor() {
        this(new Symbol[] {Symbol.intern("Radio0")});
    }

    public TextOrRadioEditor(Symbol[] values) {
        super(new G2textfield(), values);
    }
    
    public TextOrRadioEditor(G2textfield field, Symbol[] values) {
        super(field, values);
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