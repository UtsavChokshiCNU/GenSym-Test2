
package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gdiHistoricalBlock extends gdiDataShift{


	public gdiHistoricalBlock () {}

	public gdiHistoricalBlock (java.awt.Frame frame) {
		super(frame);

		sampleBox.setFixed(true);
		
		updateBox = new TypeSizePanel(this,updateBox.updateType, false, 1);
		dpanel.addPanel(updateBox, null, 0);

		requireFullHistory = CheckBoxEditor.createYesNoCheckBox();
		dpanel.placeAttributeEditor(requireFullHistory,REQUIRE_FULL_HISTORY_, 7);

	}

	protected TypeSizePanel updateBox;
	protected CheckBoxEditor requireFullHistory;

	protected final static Symbol REQUIRE_FULL_HISTORY_ = 
		Symbol.intern("REQUIRE-FULL-HISTORY");

}