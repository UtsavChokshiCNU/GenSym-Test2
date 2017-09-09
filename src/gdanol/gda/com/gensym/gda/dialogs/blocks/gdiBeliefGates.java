package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gdiBeliefGates extends outputUncertainty {
	protected TypeSizePanel sample;
	protected CheckBoxEditor eraseHistoryWhenReset;
	protected CheckBoxEditor requireFullHistory;
	
	public gdiBeliefGates() {}

	public gdiBeliefGates(java.awt.Frame frame) {
		super(frame);
				
				
		sample = new TypeSizePanel(this, sample.sampleType, false, 1);
		dpanel.addPanel(sample, null, 0);

		requireFullHistory= CheckBoxEditor.createYesNoCheckBox();
		dpanel.placeAttributeEditor(requireFullHistory, 
			REQUIRE_FULL_HISTORY_, 1);

		eraseHistoryWhenReset= CheckBoxEditor.createYesNoCheckBox();
		dpanel.placeAttributeEditor(eraseHistoryWhenReset, 
			ERASE_HISTORY_WHEN_RESET_, 2);

	}

	protected CheckBoxEditor useExpiredInputs;
	protected SpinEditor implicationThreshold;

	protected final static Symbol REQUIRE_FULL_HISTORY_= 
		Symbol.intern("REQUIRE-FULL-HISTORY");
	protected final static Symbol ERASE_HISTORY_WHEN_RESET_= 
		Symbol.intern("ERASE-HISTORY-WHEN-RESET");

}