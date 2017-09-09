package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gdiQuantization extends BlocksDialog {
	
	public gdiQuantization() {}

	public gdiQuantization(java.awt.Frame frame) {
		super(frame);

		quantization = new SpinOrNoneEditor();
		dpanel.placeAttributeEditor(quantization, QUANTIZATION_, 10);	
	
	}

	protected SpinOrNoneEditor quantization;
	protected final static Symbol  QUANTIZATION_= Symbol.intern("QUANTIZATION");

}