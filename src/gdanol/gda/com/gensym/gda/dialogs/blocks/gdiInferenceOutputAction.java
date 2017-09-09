
package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gdiInferenceOutputAction extends gdi3PosInferenceSwitch {
	
	public gdiInferenceOutputAction() {}

	public gdiInferenceOutputAction(java.awt.Frame frame) {
		super(frame);
		createDescriptionsTab();
		
		outputUncertainty = new SpinOrNoneEditor(
			new G2SpinField(0, 1, 0.1));
		dpanel.placeAttributeEditor(outputUncertainty,
			OUTPUT_UNCERTAINTY_, dpanel.quantityFieldType, 20);
		
	}
	
	
	protected SpinOrNoneEditor outputUncertainty;
	protected final static Symbol OUTPUT_UNCERTAINTY_ = 
		Symbol.intern("OUTPUT-UNCERTAINTY");

}