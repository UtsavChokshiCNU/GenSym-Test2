package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gdiWeightedEvidenceCombiner extends outputUncertainty {
	

	public gdiWeightedEvidenceCombiner() {}

	public gdiWeightedEvidenceCombiner(java.awt.Frame frame) {
		super(frame);
				
		gain = new SpinOrNoneEditor();
		dpanel.placeAttributeEditor(gain, GAIN_, 0);

		bias = new SpinOrNoneEditor();
		dpanel.placeAttributeEditor(bias, BIAS_, 1);
		
		useExpiredInputs= CheckBoxEditor.createYesNoCheckBox();
		dpanel.placeAttributeEditor(useExpiredInputs, USE_EXPIRED_INPUTS_, 2);

	}

	protected SpinOrNoneEditor gain;
	protected SpinOrNoneEditor bias;
	protected CheckBoxEditor useExpiredInputs;

	protected final static Symbol GAIN_= Symbol.intern("GAIN");
	protected final static Symbol BIAS_= Symbol.intern("BIAS");

}