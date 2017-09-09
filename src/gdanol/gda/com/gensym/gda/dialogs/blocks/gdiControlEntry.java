
package com.gensym.gda.dialogs.blocks;

import com.gensym.gda.controls.*;

public class gdiControlEntry extends gdiEntryPoint {
	
	public gdiControlEntry() {}

	public gdiControlEntry(java.awt.Frame frame) {
		super(frame);
		
		valueOnInitialization = new SpinOrNoneEditor(0, Integer.MAX_VALUE, 1);
		dpanel.placeAttributeEditor(valueOnInitialization, 
			VALUE_ON_INITIALIZATION_, dpanel.integerFieldType, 2);

	}

	protected SpinOrNoneEditor valueOnInitialization;

}