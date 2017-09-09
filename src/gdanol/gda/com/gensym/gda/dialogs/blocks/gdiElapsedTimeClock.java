package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gdiElapsedTimeClock extends gdiRealTimeClock {
	
	public gdiElapsedTimeClock() {}

	public gdiElapsedTimeClock(java.awt.Frame frame) {
		super(frame);

		autoResetPeriod= new IntervalEditor();
		dpanel.placeAttributeEditor(autoResetPeriod,
			AUTO_RESET_PERIOD_,  15);
		
	}

	protected IntervalEditor autoResetPeriod;
	protected final static Symbol AUTO_RESET_PERIOD_= 
		Symbol.intern("AUTO-RESET-PERIOD");

}