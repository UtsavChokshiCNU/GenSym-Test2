package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gdiBeliefTransmitter extends gdiTransmitter {
	
	public gdiBeliefTransmitter() {}

	public gdiBeliefTransmitter(java.awt.Frame frame) {
		super(frame);
				
		outputUncertainty = new SpinOrNoneEditor(0.0, 1.0, 0.1);
		dpanel.placeAttributeEditor(outputUncertainty, OUTPUT_UNCERTAINTY_, 5);
		
	}


	protected SpinOrNoneEditor outputUncertainty;

	protected final static Symbol OUTPUT_UNCERTAINTY_= Symbol.intern("OUTPUT-UNCERTAINTY");

}