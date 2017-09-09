package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gdiTabularGates extends outputUncertainty {
	
	public gdiTabularGates() {}

	public gdiTabularGates(java.awt.Frame frame) {
		super(frame);
				
		logic = new CheckBoxEditor();
		logic.setOnvalue(FUZZY_);
		logic.setOffvalue(DISCRETE_);
		logic.getCheckBox().setText(localize("Fuzzy"));
		dpanel.placeAttributeEditor(logic, LOGIC_, 1);

	}


	protected CheckBoxEditor logic;

	protected final static Symbol LOGIC_= Symbol.intern("LOGIC");
	protected final static Symbol FUZZY_= Symbol.intern("FUZZY");
	protected final static Symbol DISCRETE_= Symbol.intern("DISCRETE");
		
}