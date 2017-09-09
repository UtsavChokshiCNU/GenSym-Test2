package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gdiRealTimeClock extends BlocksDialog {

	public gdiRealTimeClock() {}
	
	public gdiRealTimeClock(java.awt.Frame frame) {
		super(frame);

		samplePeriod= new IntervalEditor();
		dpanel.placeAttributeEditor(samplePeriod,SAMPLE_PERIOD_, 10);
		
	}

	protected IntervalEditor samplePeriod;
	protected final static Symbol  SAMPLE_PERIOD_= Symbol.intern("SAMPLE-PERIOD");

}