package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gdiVariance extends gdiHistoricalBlock {
	
	public gdiVariance() {}

	public gdiVariance(java.awt.Frame frame) {
		super(frame);

		outputAsStdDeviation = CheckBoxEditor.createYesNoCheckBox();
		dpanel.placeAttributeEditor(outputAsStdDeviation,
			OUTPUT_AS_STD_DEVIATION_,2);
		
	}

	protected CheckBoxEditor outputAsStdDeviation;

		protected final static Symbol OUTPUT_AS_STD_DEVIATION_ = 
		Symbol.intern("OUTPUT-AS-STD-DEVIATION");


}