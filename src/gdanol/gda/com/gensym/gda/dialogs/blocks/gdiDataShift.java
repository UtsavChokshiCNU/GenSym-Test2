package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gdiDataShift extends gdi3PosDataSwitch {
	
	public gdiDataShift() {}

	public gdiDataShift(java.awt.Frame frame) {
		super(frame);

		sampleBox = new TypeSizePanel(this, sampleBox.sampleType, false, 1);
		dpanel.addPanel(sampleBox, null, 1);
		
		eraseHistoryWhenReset = CheckBoxEditor.createYesNoCheckBox();
		dpanel.placeAttributeEditor(eraseHistoryWhenReset,
			ERASE_HISTORY_WHEN_RESET_,8);
		
	}

	protected TypeSizePanel sampleBox;
	protected CheckBoxEditor eraseHistoryWhenReset;

		protected final static Symbol ERASE_HISTORY_WHEN_RESET_ = 
		Symbol.intern("ERASE-HISTORY-WHEN-RESET");


}