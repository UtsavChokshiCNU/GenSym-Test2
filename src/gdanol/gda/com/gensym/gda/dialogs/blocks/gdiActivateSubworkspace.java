package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gdiActivateSubworkspace extends BlocksDialog {

	public gdiActivateSubworkspace() {}
	
	public gdiActivateSubworkspace(java.awt.Frame frame) {
		super(frame);
				
		target = new ListEditor();
		dpanel.placeAttributeEditor(target, TARGET_, dpanel.symbolFieldType, 0);
		
	}
		
	protected ListEditor target;
	
	protected final static Symbol TARGET_= Symbol.intern("TARGET");

}