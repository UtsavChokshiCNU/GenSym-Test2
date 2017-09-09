package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gdiRangeObservation extends gdiConclusion {


	public gdiRangeObservation () {}

	public gdiRangeObservation (java.awt.Frame frame) {
		super(frame);

		UncertaintyBoundPanel ubound = 
			UncertaintyBoundPanel.createThresholdUncertaintyPanel(this);
		dpanel.addPanel(ubound, null, 2);
		
	}


}