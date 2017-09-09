package com.gensym.gda.dialogs.other;

import com.gensym.util.Symbol;

import com.gensym.gda.controls.*;

public class gdiOverrideQuantity extends overrideDialog {
    
    public gdiOverrideQuantity() {}

    public gdiOverrideQuantity(java.awt.Frame frame) {
        super(frame);
        
        editor = new SpinEditor(-Double.MAX_VALUE, Double.MAX_VALUE, 1.0);
        dpanel.placeAttributeEditor(editor, OVERRIDE_VALUE_, dpanel.quantityFieldType, 1);

    }
        
}