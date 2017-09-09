
package com.gensym.gda.dialogs.blocks;

import com.gensym.gda.controls.*;

public class gdiTextEntry extends gdiDataPathEntry {
	
	public gdiTextEntry() {}

	public gdiTextEntry(java.awt.Frame frame) {
		super(frame);
		
		valueOnInitialization = new TextOrNoneEditor();
		dpanel.placeAttributeEditor(valueOnInitialization, 
			VALUE_ON_INITIALIZATION_, 3);
		
	}

	protected TextOrNoneEditor valueOnInitialization;

}