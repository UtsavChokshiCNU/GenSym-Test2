package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gdiRangePattern extends gdiRangeObservation {


	public gdiRangePattern () {}

	public gdiRangePattern (java.awt.Frame frame) {
		super(frame);

		sampleBox = new TypeSizePanel(this,
			TypeSizePanel.sampleType, false, 1);
		dpanel.addPanel(sampleBox, null, 0);
		
		eraseHistoryWhenReset = CheckBoxEditor.createYesNoCheckBox();
		dpanel.placeAttributeEditor(eraseHistoryWhenReset,
			ERASE_HISTORY_WHEN_RESET_, 4);
			
		triggerCount = new SpinEditor(1,Integer.MAX_VALUE, 1);
		dpanel.placeAttributeEditor(triggerCount,
			TRIGGER_COUNT_, dpanel.integerFieldType, 6);
		
	}

	protected TypeSizePanel sampleBox;
	protected CheckBoxEditor eraseHistoryWhenReset;
	protected SpinEditor triggerCount;

	protected final static Symbol  ERASE_HISTORY_WHEN_RESET_= 
		Symbol.intern("ERASE-HISTORY-WHEN-RESET");
	protected final static Symbol  TRIGGER_COUNT_= 
		Symbol.intern("TRIGGER-COUNT");

}