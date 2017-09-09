package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gdiBlockDataSeek extends BlocksDialog {
	
	public gdiBlockDataSeek() {}

	public gdiBlockDataSeek(java.awt.Frame frame) {
		super(frame);
				
		dataSeekTimeout = new IntervalOrNoneEditor();
		dpanel.placeAttributeEditor(dataSeekTimeout, DATA_SEEK_TIMEOUT_, 0);
		
		attribute = new TextOrNoneEditor();
		dpanel.placeAttributeEditor(attribute, 
			ATTRIBUTE_, dpanel.symbolFieldType, 1);

	}
	
	protected IntervalOrNoneEditor dataSeekTimeout;
	protected TextOrNoneEditor attribute;
	
	protected final static Symbol DATA_SEEK_TIMEOUT_= Symbol.intern("DATA-SEEK-TIMEOUT");
	protected final static Symbol ATTRIBUTE_= Symbol.intern("ATTRIBUTE");

}