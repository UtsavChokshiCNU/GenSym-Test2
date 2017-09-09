package com.gensym.gda.dialogs.other;

import com.gensym.util.Symbol;

import com.gensym.gda.controls.*;

public class gdiOverrideSymbol extends overrideDialog {
    
    public gdiOverrideSymbol() {}

    public gdiOverrideSymbol(java.awt.Frame frame) {
        super(frame);
        
        editor = new TextFieldEditor();
        dpanel.placeAttributeEditor(editor, OVERRIDE_VALUE_, dpanel.symbolFieldType, 1);

    }
        
}