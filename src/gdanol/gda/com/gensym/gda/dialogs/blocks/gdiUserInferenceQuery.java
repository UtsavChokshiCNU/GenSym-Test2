
package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gdiUserInferenceQuery extends gdiInferenceOutputAction{


	public gdiUserInferenceQuery () {}

	public gdiUserInferenceQuery (java.awt.Frame frame) {
		super(frame);

		displayRouting = new ComboBoxEditor();
		dpanel.placeAttributeEditor(displayRouting,
			DISPLAY_ROUTING_, dpanel.symbolFieldType, 15);
	}



	protected ComboBoxEditor displayRouting;

	protected final static Symbol DISPLAY_ROUTING_ = Symbol.intern("DISPLAY-ROUTING");

	
}