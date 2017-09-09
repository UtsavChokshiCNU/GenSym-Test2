
package com.gensym.gda.controls;

import java.io.IOException;
import java.io.EOFException;

import com.gensym.types.G2TokenizerException;
import com.gensym.types.G2ParserException;


/**StatusFieldType converts .FALSE and .TRUE symbols to strings
false and true and vise versa
*/
public class StatusFieldType extends LowerCaseSymbolFieldType {

    public StatusFieldType() {
		super();
    }



    public String objectToString(Object obj) throws IOException {
		String s = super.objectToString(obj);
		if (s.equalsIgnoreCase(_FALSE)) return FALSE;
		if (s.equalsIgnoreCase(_TRUE)) return TRUE;
        return s;
    }

    public Object stringToObject(String s)
        throws G2TokenizerException, G2ParserException, EOFException, IOException {
		if (s.equals(FALSE))
			s = _FALSE;
		else if (s.equals(TRUE))
			s = _TRUE;

		return super.stringToObject(s);
    }
    
    private final static String _FALSE = ".FALSE";
    private final static String _TRUE = ".TRUE";
		private final static String FALSE = "false";
		private final static String TRUE = "true";
}