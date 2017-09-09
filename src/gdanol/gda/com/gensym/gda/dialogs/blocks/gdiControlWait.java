package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;

import com.gensym.gda.controls.MIRadioEditor;

public class gdiControlWait extends gdiControlInhibit {
	protected MIRadioEditor multipleInvocations;
    protected final static Symbol MULTIPLE_INVOCATIONS_ = Symbol.intern("MULTIPLE-INVOCATIONS");
    
    public gdiControlWait() {}

    public gdiControlWait(java.awt.Frame frame) {
        super(frame);
        
        multipleInvocations = new MIRadioEditor(true);
        dpanel.placeAttributeEditor(multipleInvocations, 
            MULTIPLE_INVOCATIONS_, 20);
        
    }       
}


        