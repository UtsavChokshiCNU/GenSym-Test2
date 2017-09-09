package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gdiConditional extends gdi3PosDataSwitch {
	
	public gdiConditional() {}

	public gdiConditional(java.awt.Frame frame) {
		super(frame);

		equivalenceBand = new SpinOrNoneEditor(0, Double.MAX_VALUE, 1);
		dpanel.placeAttributeEditor(equivalenceBand, EQUIVALENCE_BAND_, 9);

	}
	
	protected SpinOrNoneEditor equivalenceBand;

	protected final static Symbol EQUIVALENCE_BAND_ = 
		Symbol.intern("EQUIVALENCE-BAND");

}