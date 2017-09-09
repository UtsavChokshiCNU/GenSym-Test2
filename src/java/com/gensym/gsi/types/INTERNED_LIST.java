
package com.gensym.gsi.types;

import com.gensym.gsi.*;
import com.gensym.gsi.types.*;
import com.gensym.gsi.messages.*;
import java.io.IOException;

public class INTERNED_LIST implements ICPType {

    public static InternedList read(ICPInputStream inputStream) 
	throws IOException {
	Integer icpindex = new Integer(CORRESPONDING_ICP_OBJECT_INDEX.read(inputStream));
	return (InternedList)(inputStream.standardIndexSpace.lookupObjectForIndex(icpindex.intValue()));
    }
    public static void initialWrite(InternedList value, ICPOutputStream outputStream)
	throws IOException {
	Integer icpindex = outputStream.standardIndexSpace.lookupIndexForObject(value);
	if (null != icpindex) return;
	icpindex = new Integer(outputStream.standardIndexSpace.getIndexForObject(value));
	(new intern_list (icpindex.intValue(), value)).write(outputStream);
    }
    public static void write(InternedList value, ICPOutputStream outputStream)
	throws IOException {
	Integer icpindex = outputStream.standardIndexSpace.lookupIndexForObject(value);
	CORRESPONDING_ICP_OBJECT_INDEX.write(icpindex.intValue(), outputStream);
    }

}
