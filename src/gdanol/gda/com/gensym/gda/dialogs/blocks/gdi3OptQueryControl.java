package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gdi3OptQueryControl extends gdi2OptQueryControl {
	
	public gdi3OptQueryControl() {}

	public gdi3OptQueryControl(java.awt.Frame frame) {
		super(frame);

		option3Description = new TextAreaEditor();
		dpanel.placeAttributeEditor(option3Description,OPTION_3_DESCRIPTION_, 3);

		defaultOption.getSpinField().setMaxValue(3);

	}

	
	protected TextAreaEditor option3Description;

	protected final static Symbol OPTION_3_DESCRIPTION_= 
		Symbol.intern("OPTION-3-DESCRIPTION");

}