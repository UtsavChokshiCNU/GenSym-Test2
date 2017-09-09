package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gdiAndOrGates extends gdiTabularGates {
	
	public gdiAndOrGates() {}

	public gdiAndOrGates(java.awt.Frame frame) {
		super(frame);
				
		maximumUnknownInputs = new SpinEditor(0, Integer.MAX_VALUE, 1);
		dpanel.placeAttributeEditor(maximumUnknownInputs, 
			MAXIMUM_UNKNOWN_INPUTS_, dpanel.integerFieldType, 0);

		useExpiredInputs= CheckBoxEditor.createYesNoCheckBox();
		dpanel.placeAttributeEditor(useExpiredInputs, USE_EXPIRED_INPUTS_, 2);
		
	}

	protected CheckBoxEditor useExpiredInputs;
	protected SpinEditor maximumUnknownInputs;

	protected final static Symbol MAXIMUM_UNKNOWN_INPUTS_= 
		Symbol.intern("MAXIMUM-UNKNOWN-INPUTS");

}