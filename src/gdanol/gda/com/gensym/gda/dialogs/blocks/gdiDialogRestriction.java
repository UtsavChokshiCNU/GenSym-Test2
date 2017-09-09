package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gdiDialogRestriction extends BlocksDialog {
	
	public gdiDialogRestriction() {}

	public gdiDialogRestriction(java.awt.Frame frame) {
		super(frame);

		displayRouting = new ComboBoxEditor();
		dpanel.placeAttributeEditor(displayRouting,
			DISPLAY_ROUTING_,dpanel.symbolFieldType, 0);
		
		overrideText = new TextAreaEditor();
		dpanel.placeAttributeEditor(overrideText,OVERRIDE_TEXT_, 1);

		newValuePrompt = new TextAreaEditor();
		dpanel.placeAttributeEditor(newValuePrompt,NEW_VALUE_PROMPT_, 2);

	}

	protected ComboBoxEditor displayRouting;
	protected TextAreaEditor newValuePrompt;
	protected TextAreaEditor overrideText;

	protected final static Symbol DISPLAY_ROUTING_= 
		Symbol.intern("DISPLAY-ROUTING");
	protected final static Symbol OVERRIDE_TEXT_= 
		Symbol.intern("OVERRIDE-TEXT");
	protected final static Symbol NEW_VALUE_PROMPT_= 
		Symbol.intern("NEW-VALUE-PROMPT");
	

}