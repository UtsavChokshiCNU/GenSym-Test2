package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gdiInferenceInhibit extends gdi3PosInferenceSwitch {

	public gdiInferenceInhibit() {}
	
	public gdiInferenceInhibit(java.awt.Frame frame) {
		super(frame);
		
		triggerOn = new StatusComboBoxEditor(StatusComboBoxEditor.SMALL_UNKNOWN);
		dpanel.placeAttributeEditor(triggerOn, TRIGGER_ON_, 15);

	}

	protected StatusComboBoxEditor triggerOn;

	protected final static Symbol TRIGGER_ON_ = 
		Symbol.intern("TRIGGER-ON");

}