package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gdiNetworkNumericEntry extends gdiPathConnectionPost {
	
	public gdiNetworkNumericEntry() {}

	public gdiNetworkNumericEntry(java.awt.Frame frame) {
		super(frame);
		
		valueOnInitialization = new SpinOrNoneEditor();
		dpanel.placeAttributeEditor(valueOnInitialization, 
			VALUE_ON_INITIALIZATION_, 1);
		
		
	}

	protected SpinOrNoneEditor valueOnInitialization;

	protected final static Symbol VALUE_ON_INITIALIZATION_ = 
		Symbol.intern("VALUE-ON-INITIALIZATION");

}