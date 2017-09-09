package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gdiGenericAction extends BlocksDialog {
	
	public gdiGenericAction() {}

	public gdiGenericAction(java.awt.Frame frame) {
		super(frame);

		userDefinedProcedure = new ComboBoxEditor();
		dpanel.placeAttributeEditor(userDefinedProcedure,
			USER_DEFINED_PROCEDURE_, dpanel.symbolFieldType, 0);

		multipleInvocations = new MIRadioEditor();
		dpanel.placeAttributeEditor(multipleInvocations,MULTIPLE_INVOCATIONS_, 1);

	}
	
	protected ComboBoxEditor userDefinedProcedure;
	protected MIRadioEditor multipleInvocations;

	protected final static Symbol USER_DEFINED_PROCEDURE_= 
		Symbol.intern("USER-DEFINED-PROCEDURE");
	protected final static Symbol MULTIPLE_INVOCATIONS_= 
		Symbol.intern("MULTIPLE-INVOCATIONS");

}