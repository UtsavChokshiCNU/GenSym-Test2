
package com.gensym.gsi.types;

import com.gensym.gsi.*;
import com.gensym.gsi.types.*;
import com.gensym.gsi.messages.*;
import java.io.IOException;

public class INTERNED_LIST_AS_VALUE_TYPE implements ICPType {

    public static Object read(ICPInputStream inputStream)
	throws IOException {
	int icpindex;
	InternedList value;
	short tag = inputStream.peekICPByte();
	switch (tag) {
	case 65535:
	    ICP_BYTE.read(inputStream);
	    icpindex = UNSIGNED_INTEGER.read(inputStream);
	    value = InternedList.intern(ICP_TREE.read(inputStream));
	    inputStream.standardIndexSpace.setObjectForIndex(icpindex,value);
	    break;
	case 65534:
	    ICP_BYTE.read(inputStream);
	    icpindex = UNSIGNED_INTEGER.read(inputStream);
	    value = inputStream.temporaryIndexSpace.lookupObjectForIndex(icpindex);
	    break;
	default:
	    icpindex = UNSIGNED_INTEGER.read(inputStream);
	    value = inputStream.standardIndexSpace.lookupObjectForIndex(icpindex);
	    break;
	}
	return value;
    }

    public static void write(InternedList value, ICPOutputStream outputStream)
	throws IOException {
	Integer icpindex = outputStream.standardIndexSpace.lookupIndexForObject(value);
	if (null != icpindex) {
	    ICPBYTE.write(ICP_STANDARD_INDEX_SPACE_TYPE_TAG, outputStream);
	    UNSIGNED_INTEGER.write(icpindex.intValue(), outputStream);
	    return;
	}
	icpindex = new Integer(outputStream.standardIndexSpace.getIndexForObject(value));
	ICPBYTE.write(65535, outputStream);
	UNSIGNED_INTEGER.write(icpindex.intValue(), outputStream);
	ICP_TREE.write(value.value(), outputStream);
    }
}

