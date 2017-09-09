package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gdiInferenceCounter extends BlocksDialog {
	
	public gdiInferenceCounter() {}

	public gdiInferenceCounter(java.awt.Frame frame) {
		super(frame);
	
		valueOnInitialization = new SpinEditor(Integer.MIN_VALUE, Integer.MAX_VALUE, 1);
		dpanel.placeAttributeEditor(valueOnInitialization, 
			VALUE_ON_INITIALIZATION_, dpanel.integerFieldType, 1);
			
		triggerOn = new StatusComboBoxEditor(StatusComboBoxEditor.ALWAYS_UNKNOWN);
		dpanel.placeAttributeEditor(triggerOn, TRIGGER_ON_, 0);
		
	}

	protected SpinEditor valueOnInitialization;
	protected StatusComboBoxEditor triggerOn;
	
	protected final static Symbol VALUE_ON_INITIALIZATION_ = 
		Symbol.intern("VALUE-ON-INITIALIZATION");
	protected final static Symbol TRIGGER_ON_ = Symbol.intern("TRIGGER-ON");

}