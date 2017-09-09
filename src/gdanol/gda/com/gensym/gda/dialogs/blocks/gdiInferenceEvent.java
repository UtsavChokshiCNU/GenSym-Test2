package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gdiInferenceEvent extends gdiConclusion {
	
	public gdiInferenceEvent() {}

	public gdiInferenceEvent(java.awt.Frame frame) {
		super(frame);
	
		triggerOn = new StatusComboBoxEditor(StatusComboBoxEditor.ALWAYS_UNKNOWN);
		dpanel.placeAttributeEditor(triggerOn, TRIGGER_ON_, 3);
		
		holdFor = new IntervalOrNoneEditor();
		dpanel.placeAttributeEditor(holdFor, HOLD_FOR_, 7);
		
	}

	protected StatusComboBoxEditor triggerOn;
	protected IntervalOrNoneEditor holdFor;

	protected final static Symbol  TRIGGER_ON_= Symbol.intern("TRIGGER-ON");
	protected final static Symbol  HOLD_FOR_= Symbol.intern("HOLD-FOR");

}