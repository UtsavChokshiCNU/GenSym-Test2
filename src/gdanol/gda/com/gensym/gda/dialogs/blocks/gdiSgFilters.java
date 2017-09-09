package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.beansruntime.StringVector;

import com.gensym.gda.controls.*;

public class gdiSgFilters extends gdiQuantization {
	
	public gdiSgFilters() {}

	public gdiSgFilters(java.awt.Frame frame) {
		super(frame);

		sampleSize = new RadioBoxEditor();
		sampleSize.setLabels(new StringVector());
		sampleSize.setMembers(new StringVector(new String[]{"5", "7"}));
		sampleSize.setRowsAndColumns(1, 2);
		dpanel.placeAttributeEditor(sampleSize,
			SAMPLE_SIZE_, dpanel.integerFieldType, 5);
		
		eraseHistoryWhenReset = CheckBoxEditor.createYesNoCheckBox();
		dpanel.placeAttributeEditor(eraseHistoryWhenReset,
			ERASE_HISTORY_WHEN_RESET_, dpanel.integerFieldType, 15);
		
	}

	protected RadioBoxEditor sampleSize;
	protected CheckBoxEditor eraseHistoryWhenReset;

	protected final static Symbol  SAMPLE_SIZE_= Symbol.intern("SAMPLE-SIZE");
	protected final static Symbol  ERASE_HISTORY_WHEN_RESET_= 
		Symbol.intern("ERASE-HISTORY-WHEN-RESET");

}