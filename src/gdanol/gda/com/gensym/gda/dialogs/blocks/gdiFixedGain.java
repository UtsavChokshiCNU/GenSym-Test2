package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gdiFixedGain extends BlocksDialog {
		
	public gdiFixedGain() {}

	public gdiFixedGain(java.awt.Frame frame) {
		super(frame);

		gain = new SpinEditor();
		dpanel.placeAttributeEditor(gain, GAIN_, 0);

	}
	
	protected SpinEditor gain;

	protected final static Symbol GAIN_ = Symbol.intern("GAIN");

}