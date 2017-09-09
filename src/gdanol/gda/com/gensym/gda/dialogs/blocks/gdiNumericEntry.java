package com.gensym.gda.dialogs.blocks;

import com.gensym.gda.controls.*;

public class gdiNumericEntry extends gdiDataPathEntry {
	
	public gdiNumericEntry() {}

	public gdiNumericEntry(java.awt.Frame frame) {
		super(frame);
		
		valueOnInitialization = new SpinOrNoneEditor();
		dpanel.placeAttributeEditor(valueOnInitialization, 
			VALUE_ON_INITIALIZATION_, 3);
	
	
	}

	protected SpinOrNoneEditor valueOnInitialization;

}