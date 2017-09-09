package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gdiControlCounter extends BlocksDialog {
	
	public gdiControlCounter() {}

	public gdiControlCounter(java.awt.Frame frame) {
		super(frame);
	
		valueOnInitialization = new SpinEditor(0, Integer.MAX_VALUE, 1);
		dpanel.placeAttributeEditor(valueOnInitialization, 
			VALUE_ON_INITIALIZATION_, dpanel.integerFieldType, 1);
			
		multipleInvocations = new MIRadioEditor(false);
		dpanel.placeAttributeEditor(multipleInvocations, MULTIPLE_INVOCATIONS_, 0);
		
	}

	protected SpinEditor valueOnInitialization;
	protected MIRadioEditor multipleInvocations;
	
	protected final static Symbol VALUE_ON_INITIALIZATION_ = 
		Symbol.intern("VALUE-ON-INITIALIZATION");
	protected final static Symbol MULTIPLE_INVOCATIONS_ = 
		Symbol.intern("MULTIPLE-INVOCATIONS");

}