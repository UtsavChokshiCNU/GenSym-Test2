package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gdiStationaryDisturbance extends gdiMovingDisturbance {
	
	public gdiStationaryDisturbance() {}
	
	public gdiStationaryDisturbance(java.awt.Frame frame) {
		super(frame);

		processMean = new SpinEditor();
		dpanel.placeAttributeEditor(processMean, PROCESS_MEAN_, 5);	
	
	}

	protected SpinEditor processMean;
	protected final static Symbol  PROCESS_MEAN_= Symbol.intern("PROCESS-MEAN");

}