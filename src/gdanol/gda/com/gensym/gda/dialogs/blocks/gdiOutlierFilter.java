package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gdiOutlierFilter extends gdiChangebandFilter {
	

	public gdiOutlierFilter() {}

	public gdiOutlierFilter(java.awt.Frame frame) {
		super(frame);

		outlierReplacement = CheckBoxEditor.createYesNoCheckBox();
		dpanel.placeAttributeEditor(outlierReplacement,
			OUTLIER_REPLACEMENT_, 13);
		
	}

	protected CheckBoxEditor outlierReplacement;

	protected final static Symbol  OUTLIER_REPLACEMENT_= 
		Symbol.intern("OUTLIER-REPLACEMENT");

}