package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gdiUpdateAndErase extends gdi3PosDataSwitch {
	
	public gdiUpdateAndErase() {}

	public gdiUpdateAndErase(java.awt.Frame frame) {
		super(frame);

		updateBox = new TypeSizePanel(this);
		updateBox.setFixed(false);
		dpanel.addPanel(updateBox, null, 1);
		
		eraseHistoryWhenReset = CheckBoxEditor.createYesNoCheckBox();
		dpanel.placeAttributeEditor(eraseHistoryWhenReset,
			ERASE_HISTORY_WHEN_RESET_,9);
		
	}

	protected TypeSizePanel updateBox;
	protected CheckBoxEditor eraseHistoryWhenReset;

		protected final static Symbol ERASE_HISTORY_WHEN_RESET_ = 
		Symbol.intern("ERASE-HISTORY-WHEN-RESET");


}