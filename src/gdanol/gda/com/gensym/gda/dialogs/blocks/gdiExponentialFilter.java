package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gdiExponentialFilter extends gdiQuantization {
	
	public gdiExponentialFilter() {}

	public gdiExponentialFilter(java.awt.Frame frame) {
		super(frame);

		filterConstant = new SpinEditor(0, Double.MAX_VALUE, 1);
		dpanel.placeAttributeEditor(filterConstant, FILTER_CONSTANT_, 15);
		
	}

	protected SpinEditor filterConstant;

	protected final static Symbol  FILTER_CONSTANT_= 
		Symbol.intern("FILTER-CONSTANT");

}