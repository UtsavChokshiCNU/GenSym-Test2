package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.StatusComboBoxEditor;

public class gdiControlInhibit extends BlocksDialog {
	protected StatusComboBoxEditor triggerOn;
	
    protected static final Symbol TRIGGER_ON_ = Symbol.intern("TRIGGER-ON");
    
    public gdiControlInhibit(){}

    public gdiControlInhibit(java.awt.Frame frame){
        super(frame);

        triggerOn = new StatusComboBoxEditor(StatusComboBoxEditor.SMALL_UNKNOWN);
        dpanel.placeAttributeEditor(triggerOn, TRIGGER_ON_, dpanel.statusFieldType, 10);
                
    }
    
}