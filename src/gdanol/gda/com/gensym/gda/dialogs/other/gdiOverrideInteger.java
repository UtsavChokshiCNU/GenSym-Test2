package com.gensym.gda.dialogs.other;

import com.gensym.util.Symbol;

import com.gensym.gda.controls.*;

public class gdiOverrideInteger extends overrideDialog {
    
    public gdiOverrideInteger() {}

    public gdiOverrideInteger(java.awt.Frame frame) {
        super(frame);
	editor = new SpinEditor(0, Integer.MAX_VALUE, 1);
        dpanel.placeAttributeEditor(editor, OVERRIDE_VALUE_, dpanel.integerFieldType, 1);
    }
}
