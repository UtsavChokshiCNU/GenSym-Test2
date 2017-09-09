
package com.gensym.gda.dialogs.blocks;

import com.gensym.gda.controls.StatusComboBoxEditor;
import com.gensym.util.Symbol;

public class gdiPersistenceGate extends Delay {
	protected StatusComboBoxEditor triggerOn;
	
    protected final static Symbol TRIGGER_ON_ = Symbol.intern("TRIGGER-ON");

    public gdiPersistenceGate() {}

    public gdiPersistenceGate(java.awt.Frame frame) {
        super(frame);

        triggerOn = new StatusComboBoxEditor(StatusComboBoxEditor.ALWAYS_UNKNOWN);

        dpanel.placeAttributeEditor(triggerOn, 
            TRIGGER_ON_, 5);
        
    }
}