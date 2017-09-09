
package com.gensym.gsi.types;

import com.gensym.gsi.*;
import com.gensym.gsi.types.*;
import com.gensym.gsi.messages.*;
import java.io.IOException;
import com.gensym.util.Symbol;

public class SYMBOL_AS_VALUE_TYPE implements ICPType, ICPTypeTags {

    public static Symbol read(ICPInputStream inputStream)
	throws IOException {
	Symbol value = null;
	int icpindex;
	switch (inputStream.peekICPByte()) {
	case GSI_NULL_TYPE_TAG:
	    ICPBYTE.read(inputStream);
	    value = Symbol.intern("NIL");
	    break;
	case ICP_TEMPORARY_INDEX_SPACE_TYPE_TAG:
	    ICPBYTE.read(inputStream);
	    icpindex = UNSIGNED_INTEGER.read(inputStream);
	    value = (Symbol)(inputStream.temporaryIndexSpace.lookupObjectForIndex(icpindex));
	    break;
	case ICP_STANDARD_INDEX_SPACE_TYPE_TAG:
	    ICPBYTE.read(inputStream);
	    icpindex = UNSIGNED_INTEGER.read(inputStream);
	    value = (Symbol)(inputStream.standardIndexSpace.lookupObjectForIndex(icpindex));
	    break;
	case ICP_NEW_KEYWORD_SYMBOL_TYPE_TAG:
	    ICPBYTE.read(inputStream);
	    icpindex = UNSIGNED_INTEGER.read(inputStream);
	    value = Symbol.intern(TEXT_STRING.read(inputStream));
	    inputStream.standardIndexSpace.setObjectForIndex(icpindex,value);
	    break;
	case ICP_NEW_SYMBOL_TYPE_TAG:
	    ICPBYTE.read(inputStream);
	    icpindex = UNSIGNED_INTEGER.read(inputStream);
	    value = Symbol.intern(TEXT_STRING.read(inputStream));
	    inputStream.standardIndexSpace.setObjectForIndex(icpindex,value);
	    break;
	default:
	    break;
	}
	return value;
    }
    public static void write(Symbol value, ICPOutputStream outputStream)
	throws IOException {
	// what about NIL?
	Integer icpindex = outputStream.standardIndexSpace.lookupIndexForObject(value);
	if (null != icpindex) {
	    ICPBYTE.write(ICP_STANDARD_INDEX_SPACE_TYPE_TAG, outputStream);
	    UNSIGNED_INTEGER.write(icpindex.intValue(), outputStream);
	    return;
	}
	icpindex = new Integer(outputStream.standardIndexSpace.getIndexForObject(value));
	String string = value.toString();
	if (string.indexOf("::") >= 0) // value.symbol_is_a_keyword()
	    ICPBYTE.write(ICP_NEW_KEYWORD_SYMBOL_TYPE_TAG, outputStream);
	else
	    ICPBYTE.write(ICP_NEW_SYMBOL_TYPE_TAG, outputStream);
	UNSIGNED_INTEGER.write(icpindex.intValue(), outputStream);
	TEXT_STRING.write(string, outputStream);
    }
}

