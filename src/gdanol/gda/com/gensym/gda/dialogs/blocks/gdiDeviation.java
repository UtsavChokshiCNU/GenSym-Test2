package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gdiDeviation extends gdiValueObservation {
	
	
	public gdiDeviation() {}

	public gdiDeviation(java.awt.Frame frame) {
		super(frame);

		referenceValue = new SpinEditor();
		dpanel.placeAttributeEditor(referenceValue, REFERENCE_VALUE_,  5);
			
	}

	protected SpinEditor referenceValue;

	protected final static Symbol  REFERENCE_VALUE_= 
		Symbol.intern("REFERENCE-VALUE");

}