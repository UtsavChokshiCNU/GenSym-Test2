
package com.gensym.gsi.types;

import com.gensym.gsi.*;
import com.gensym.gsi.types.*;
import com.gensym.gsi.messages.*;
import java.io.IOException;

import com.gensym.util.Symbol;

public class REMOTE_PROCEDURE_NAME implements ICPType {

    public static Symbol read(ICPInputStream inputStream) 
	throws IOException {
	Integer icpindex = new Integer(CORRESPONDING_ICP_OBJECT_INDEX.read(inputStream));
	return (Symbol)(inputStream.standardIndexSpace.lookupObjectForIndex(icpindex.intValue()));
    }
    public static void initialWrite(Symbol value, ICPOutputStream outputStream)
	throws IOException {
	Integer icpindex = (Integer)(outputStream.standardIndexSpace.lookupIndexForObject(value));
	if (null != icpindex) return;
	icpindex = new Integer(outputStream.standardIndexSpace.getIndexForObject(value));
	(new define_remote_procedure_name (icpindex.intValue(), value)).write(outputStream);
    }
    public static void write(Symbol value, ICPOutputStream outputStream)
	throws IOException {
	Integer icpindex = (Integer)(outputStream.standardIndexSpace.lookupIndexForObject(value));
	CORRESPONDING_ICP_OBJECT_INDEX.write(icpindex.intValue(), outputStream);
    }

}

