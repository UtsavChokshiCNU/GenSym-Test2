package com.gensym.gda.dialogs.other;

import com.gensym.util.Symbol;

import com.gensym.gda.controls.*;

public class gdiOverrideBelief extends overrideDialog {
    
    public gdiOverrideBelief() {}

    public gdiOverrideBelief(java.awt.Frame frame) {
        super(frame);
        
        editor = new SpinEditor(0.0, 1.0, 0.1);
        dpanel.placeAttributeEditor(editor, OVERRIDE_VALUE_, dpanel.quantityFieldType, 1);

    }
        
}