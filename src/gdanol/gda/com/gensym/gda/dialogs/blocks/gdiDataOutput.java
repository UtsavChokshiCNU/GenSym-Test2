package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;

import com.gensym.gda.controls.ListEditor;

public class gdiDataOutput extends BlocksDialog {
	
	protected ListEditor targetVariable;
	
    protected final static Symbol TARGET_VARIABLE_ = Symbol.intern("TARGET-VARIABLE");

	public gdiDataOutput() {}

	public gdiDataOutput(java.awt.Frame frame) {
        super(frame);

        targetVariable = new ListEditor();
        dpanel.placeAttributeEditor(targetVariable,
             TARGET_VARIABLE_, dpanel.symbolFieldType, 10);

    }

}