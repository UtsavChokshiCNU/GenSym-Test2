package com.gensym.gda.dialogs.other;

import com.gensym.util.Symbol;

import com.gensym.gda.controls.*;

public class gdiOverrideText extends overrideDialog {
    
    public gdiOverrideText() {}

    public gdiOverrideText(java.awt.Frame frame) {
        super(frame);
        
        editor = new TextFieldEditor();
        dpanel.placeAttributeEditor(editor, OVERRIDE_VALUE_, dpanel.textFieldType, 1);

    }
        
}