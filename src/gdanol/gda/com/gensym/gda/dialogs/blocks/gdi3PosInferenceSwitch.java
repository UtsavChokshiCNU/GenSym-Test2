package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;

import com.gensym.gda.controls.*;

public class gdi3PosInferenceSwitch extends BlocksDialog {
	
	public gdi3PosInferenceSwitch() {}

	public gdi3PosInferenceSwitch(java.awt.Frame frame) {
		super(frame);
		
		statusOnInitialization = new StatusComboBoxEditor();
		dpanel.placeAttributeEditor(statusOnInitialization,
			STATUS_ON_INITIALIZATION_, 10);

	}

	protected StatusComboBoxEditor statusOnInitialization;

	protected final static Symbol STATUS_ON_INITIALIZATION_ = 
		Symbol.intern("STATUS-ON-INITIALIZATION");

}