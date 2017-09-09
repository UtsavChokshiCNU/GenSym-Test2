package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gdiMovingDisturbance extends gdiRandomWalk {
		
	public gdiMovingDisturbance() {}

	public gdiMovingDisturbance(java.awt.Frame frame) {
		super(frame);

		disturbanceFilterConstant = new SpinEditor(0, 1, 0.1);
		disturbancePanel.placeAttributeEditor(disturbanceFilterConstant, 
			localize("FilterConstant"),
			DISTURBANCE_FILTER_CONSTANT_, dpanel.quantityFieldType, 2);
		
	}

	protected SpinEditor disturbanceFilterConstant;
	protected final static Symbol DISTURBANCE_FILTER_CONSTANT_ = 
		Symbol.intern("DISTURBANCE-FILTER-CONSTANT");
	
}