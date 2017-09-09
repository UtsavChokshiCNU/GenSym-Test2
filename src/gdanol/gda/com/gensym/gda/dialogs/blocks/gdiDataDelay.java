package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;

import com.gensym.gda.controls.IntervalEditor;
import com.gensym.gda.controls.MIRadioEditor;

public class gdiDataDelay extends BlocksDialog {
	protected IntervalEditor delay;
	protected MIRadioEditor multipleInvocations;
	    
    protected final static Symbol DELAY_ = Symbol.intern("DELAY");
    protected final static Symbol MULTIPLE_INVOCATIONS_ = Symbol.intern("MULTIPLE-INVOCATIONS");
    
    public gdiDataDelay() {}

    public gdiDataDelay(java.awt.Frame frame) {
        super(frame);

        delay = new IntervalEditor();
        dpanel.placeAttributeEditor(delay, DELAY_, 10);

        multipleInvocations = new MIRadioEditor(true);
        dpanel.placeAttributeEditor(multipleInvocations, 
            MULTIPLE_INVOCATIONS_, 20);

    }

}