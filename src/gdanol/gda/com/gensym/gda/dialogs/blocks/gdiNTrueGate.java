package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gdiNTrueGate extends gdiTabularGates {
	
	public gdiNTrueGate() {}

	public gdiNTrueGate(java.awt.Frame frame) {
		super(frame);
				
		n = new SpinEditor(1, Integer.MAX_VALUE, 1);
		dpanel.placeAttributeEditor(n, 
			N_, dpanel.integerFieldType, 0);

		useExpiredInputs= CheckBoxEditor.createYesNoCheckBox();
		dpanel.placeAttributeEditor(useExpiredInputs, USE_EXPIRED_INPUTS_, 2);
		
	}

	protected CheckBoxEditor useExpiredInputs;
	protected SpinEditor n;

	protected final static Symbol N_= 
		Symbol.intern("N");

}