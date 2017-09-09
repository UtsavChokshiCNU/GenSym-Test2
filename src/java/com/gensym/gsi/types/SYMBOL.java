
package com.gensym.gsi.types;

import com.gensym.gsi.*;
import com.gensym.gsi.types.*;
import com.gensym.gsi.messages.*;
import java.io.IOException;

import com.gensym.util.Symbol;

public class SYMBOL implements ICPType {

    public static Symbol read(ICPInputStream inputStream) 
	throws IOException {
	Integer icpindex = new Integer(CORRESPONDING_ICP_OBJECT_INDEX.read(inputStream));
	return (Symbol)(inputStream.standardIndexSpace.lookupObjectForIndex(icpindex.intValue()));
    }
    public static void initialWrite(Symbol value, ICPOutputStream outputStream)
	throws IOException {
	Integer icpindex = outputStream.standardIndexSpace.lookupIndexForObject(value);
	if (null != icpindex) return;
	icpindex = new Integer(outputStream.standardIndexSpace.getIndexForObject(value));
	String string = value.toString();
	if (string.indexOf("::")>=0) // value.symbol_is_a_keyword()
	    (new intern_keyword (icpindex.intValue(), string)).write(outputStream);
	else
	    (new intern (icpindex.intValue(), string)).write(outputStream);
    }
    public static void write(Symbol value, ICPOutputStream outputStream)
	throws IOException {
	Integer icpindex = outputStream.standardIndexSpace.lookupIndexForObject(value);
	CORRESPONDING_ICP_OBJECT_INDEX.write(icpindex.intValue(), outputStream);
    }

}
