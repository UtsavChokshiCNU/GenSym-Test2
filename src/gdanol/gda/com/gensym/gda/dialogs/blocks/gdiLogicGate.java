
package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gdiLogicGate extends gdi3PosInferenceSwitch {
	
	public gdiLogicGate() {}

	public gdiLogicGate(java.awt.Frame frame) {
		super(frame);

		logic = new CheckBoxEditor();
		logic.setOnvalue(FUZZY_);
		logic.setOffvalue(DISCRETE_);
		logic.getCheckBox().setText(localize("Fuzzy"));
		dpanel.placeAttributeEditor(logic, LOGIC_, 7);

		outputUncertainty = new SpinOrNoneEditor(0.0, 1.0, 0.1);
		dpanel.placeAttributeEditor(outputUncertainty, 
			OUTPUT_UNCERTAINTY_, dpanel.quantityFieldType, 20);


	}
	
	
	protected CheckBoxEditor logic;
	protected SpinOrNoneEditor outputUncertainty;

	protected final static Symbol LOGIC_ = Symbol.intern("LOGIC");
	protected final static Symbol FUZZY_= Symbol.intern("FUZZY");
	protected final static Symbol DISCRETE_= Symbol.intern("DISCRETE");
	protected final static Symbol OUTPUT_UNCERTAINTY_= Symbol.intern("OUTPUT-UNCERTAINTY");

}