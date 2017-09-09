package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;
import com.gensym.ntw.TwAccess;

public class gdiSpcRun extends gdi3PosDataSwitch {
		
	public gdiSpcRun() {}

	public gdiSpcRun(java.awt.Frame frame) {
		super(frame);

        expectedValue = new QuantityOrSymbolOrNoneOrEmbeddedEditor();
		dpanel.placeAttributeEditor(expectedValue, EXPECTED_VALUE_, 11);

	}
	
    public void setConnection(TwAccess connection){
        super.setConnection(connection);
        expectedValue.setConnection(connection);
    }
    
    protected QuantityOrSymbolOrNoneOrEmbeddedEditor expectedValue;

	protected final static Symbol EXPECTED_VALUE_=Symbol.intern("EXPECTED-VALUE");

}