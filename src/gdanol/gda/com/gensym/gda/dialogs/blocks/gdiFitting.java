package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gdiFitting extends gdiHistoricalBlock {
	
	public gdiFitting() {}

	public gdiFitting(java.awt.Frame frame) {
		super(frame);

		scaleFactor = new SpinEditor();
		dpanel.placeAttributeEditor(scaleFactor,SCALE_FACTOR_, 9);
		
	}

	protected SpinEditor scaleFactor;

	protected final static Symbol SCALE_FACTOR_ = 
		Symbol.intern("SCALE-FACTOR");

}