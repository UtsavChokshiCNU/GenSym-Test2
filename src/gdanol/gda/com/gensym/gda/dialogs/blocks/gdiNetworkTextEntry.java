package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gdiNetworkTextEntry extends gdiPathConnectionPost {
	
	public gdiNetworkTextEntry() {}

	public gdiNetworkTextEntry(java.awt.Frame frame) {
		super(frame);
		
		valueOnInitialization = new TextOrNoneEditor();
		dpanel.placeAttributeEditor(valueOnInitialization, 
			VALUE_ON_INITIALIZATION_, 1);
		
		
	}

	protected TextOrNoneEditor valueOnInitialization;

	protected final static Symbol VALUE_ON_INITIALIZATION_ = 
		Symbol.intern("VALUE-ON-INITIALIZATION");

}