
package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;

import com.gensym.gda.controls.*;

public class gdiDelay extends Delay{

    protected MIRadioEditor multipleInvocations;

    protected final static Symbol MULTIPLE_INVOCATIONS_ = Symbol.intern("MULTIPLE-INVOCATIONS");


	public gdiDelay() {}

	public gdiDelay(java.awt.Frame frame) {
		super(frame);
        		
		multipleInvocations = new MIRadioEditor(false);
		dpanel.placeAttributeEditor(multipleInvocations, 
			MULTIPLE_INVOCATIONS_, 40);
		
	}
		
}