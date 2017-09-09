
package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gdiConclusion extends gdiInferenceOutputAction{


	public gdiConclusion() {}

	public gdiConclusion(java.awt.Frame frame) {
		super(frame);
		
		hysteresisWhen= new StatusComboBoxEditor();
		hysteresisWhen.setType(StatusComboBoxEditor.ALWAYS);
		dpanel.placeAttributeEditor(hysteresisWhen,
			HYSTERESIS_WHEN_, 15);
		
	}


	protected StatusComboBoxEditor hysteresisWhen;

	protected final static Symbol HYSTERESIS_WHEN_ = Symbol.intern("HYSTERESIS-WHEN");

}