package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gdiFuzzyEvidenceGate extends outputUncertainty {
	
	public gdiFuzzyEvidenceGate() {}

	public gdiFuzzyEvidenceGate(java.awt.Frame frame) {
		super(frame);
				
		implicationThreshold = new SpinEditor(0, 1, 0.1);
		dpanel.placeAttributeEditor(implicationThreshold, 
			IMPLICATION_THRESHOLD_, 0);

		useExpiredInputs= CheckBoxEditor.createYesNoCheckBox();
		dpanel.placeAttributeEditor(useExpiredInputs, USE_EXPIRED_INPUTS_, 1);
		
	}

	protected CheckBoxEditor useExpiredInputs;
	protected SpinEditor implicationThreshold;

	protected final static Symbol IMPLICATION_THRESHOLD_= 
		Symbol.intern("IMPLICATION-THRESHOLD");

}