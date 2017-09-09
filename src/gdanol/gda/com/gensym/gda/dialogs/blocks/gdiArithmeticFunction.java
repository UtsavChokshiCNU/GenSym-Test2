
package com.gensym.gda.dialogs.blocks;
import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gdiArithmeticFunction extends BlocksDialog {
	
	public gdiArithmeticFunction() {}

	public gdiArithmeticFunction(java.awt.Frame frame) {
		super(frame);
		
		arithmeticFunction = new TextOrNoneEditor();
		dpanel.placeAttributeEditor(arithmeticFunction, 
			ARITHMETIC_FUNCTION_, dpanel.symbolFieldType, 0);
		
	}

	protected TextOrNoneEditor arithmeticFunction;
	protected final static Symbol ARITHMETIC_FUNCTION_ = Symbol.intern("ARITHMETIC-FUNCTION");

}