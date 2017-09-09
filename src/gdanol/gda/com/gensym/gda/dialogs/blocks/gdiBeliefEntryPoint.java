
package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gdiBeliefEntryPoint extends gdiDataPathEntry{


	public gdiBeliefEntryPoint () {}

	public gdiBeliefEntryPoint (java.awt.Frame frame) {
		super(frame);
		createDescriptionsTab();
				
		logic = new CheckBoxEditor();
		logic.setOnvalue(FUZZY_);
		logic.setOffvalue(DISCRETE_);
		logic.getCheckBox().setText(localize("Fuzzy"));
		dpanel.placeAttributeEditor(logic, LOGIC_, 3);

		statusOnInitialization = new StatusComboBoxEditor();
		dpanel.placeAttributeEditor(statusOnInitialization, 
			STATUS_ON_INITIALIZATION_, 4);
		

		outputUncertainty = new SpinOrNoneEditor(0.0, 1.0, 0.1);
		dpanel.placeAttributeEditor(outputUncertainty, 
			OUTPUT_UNCERTAINTY_, dpanel.quantityFieldType, 5);
		
	}


	protected CheckBoxEditor logic;		
	protected SpinOrNoneEditor outputUncertainty;		
	protected ComboBoxEditor statusOnInitialization;		

	protected final static Symbol LOGIC_= Symbol.intern("LOGIC");
	protected final static Symbol OUTPUT_UNCERTAINTY_= Symbol.intern("OUTPUT-UNCERTAINTY");
	protected final static Symbol STATUS_ON_INITIALIZATION_ = Symbol.intern("STATUS-ON-INITIALIZATION");

	protected final static Symbol FUZZY_= Symbol.intern("FUZZY");
	protected final static Symbol DISCRETE_= Symbol.intern("DISCRETE");
		
}