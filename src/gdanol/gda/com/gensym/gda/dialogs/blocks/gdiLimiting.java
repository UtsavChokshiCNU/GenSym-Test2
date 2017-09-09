package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gdiLimiting extends gdiInputSelection{


	public gdiLimiting () {}

	public gdiLimiting (java.awt.Frame frame) {
		super(frame);

		limit = new SpinEditor();
		dpanel.placeAttributeEditor(limit, LIMIT_, 0);
			
		
	}
	
	protected SpinEditor limit;

	protected final static Symbol LIMIT_ = Symbol.intern("LIMIT");
	
	
}