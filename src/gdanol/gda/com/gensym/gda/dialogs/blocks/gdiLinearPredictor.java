
package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gdiLinearPredictor  extends BlocksDialog{


	public gdiLinearPredictor () {}

	public gdiLinearPredictor (java.awt.Frame frame) {
		super(frame);

		timeHorizon = new IntervalEditor();
		dpanel.placeAttributeEditor(timeHorizon,TIME_HORIZON_, 0);
		
	}

	protected IntervalEditor timeHorizon;

	protected final static Symbol TIME_HORIZON_ = 
	Symbol.intern("TIME-HORIZON");
	
}