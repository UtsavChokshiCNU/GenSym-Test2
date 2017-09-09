package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gdiValueObservation extends gdiConclusion {
	
	
	public gdiValueObservation() {}

	public gdiValueObservation(java.awt.Frame frame) {
		super(frame);

		threshold=new SpinEditor();
		dpanel.placeAttributeEditor(threshold, THRESHOLD_, 1);

		thresholdUncertainty=new SpinOrNoneEditor(0, 1, 0.1);
		dpanel.placeAttributeEditor(thresholdUncertainty, 
			THRESHOLD_UNCERTAINTY_,dpanel.quantityFieldType, 2);
	}

	protected SpinEditor threshold;
	protected SpinOrNoneEditor thresholdUncertainty;

	protected final static Symbol THRESHOLD_ = Symbol.intern("THRESHOLD");
	protected final static Symbol THRESHOLD_UNCERTAINTY_ = Symbol.intern("THRESHOLD-UNCERTAINTY");

}