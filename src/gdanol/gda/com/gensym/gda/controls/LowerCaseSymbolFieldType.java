
package com.gensym.gda.controls;

import java.io.IOException;
import java.io.EOFException;
import com.gensym.types.SymbolType;
import com.gensym.types.G2TokenizerException;
import com.gensym.types.G2ParserException;
import com.gensym.controls.FieldType;

/**
LowerCaseSymbolFieldType represent symbol values in lower case.
(FieldType represent it in upper case).
*/
public class LowerCaseSymbolFieldType extends FieldType {

  /**
  Constructor creates FieldType with SymbolType.
  */
	public LowerCaseSymbolFieldType() {
		super(new SymbolType());
	}

	/**
	Converts to lower case string which return super method.
	
	*/
	public String objectToString(Object obj) throws IOException {
		String s = super.objectToString(obj);
		return s.toLowerCase();
	}

	/**Converts to uppercase string <i>s</i> and pass it to super method.
	*/
	public Object stringToObject(String s)
		throws G2TokenizerException, G2ParserException, EOFException, IOException {
		
		return super.stringToObject(s.toUpperCase());
	}    
}