package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gdiFixedBias extends BlocksDialog {
		
	public gdiFixedBias() {}

	public gdiFixedBias(java.awt.Frame frame) {
		super(frame);

		bias = new SpinEditor();
		dpanel.placeAttributeEditor(bias, BIAS_, 0);

	}
	
	protected SpinEditor bias;

	protected final static Symbol BIAS_ = 
		Symbol.intern("BIAS");

}