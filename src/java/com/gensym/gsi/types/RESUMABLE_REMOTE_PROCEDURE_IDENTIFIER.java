
package com.gensym.gsi.types;

import com.gensym.gsi.*;
import com.gensym.gsi.types.*;
import com.gensym.gsi.messages.*;
import java.io.IOException;

public class RESUMABLE_REMOTE_PROCEDURE_IDENTIFIER implements ICPType {

    public static GSIRemoteProcedureIdentifier read(ICPInputStream inputStream) 
	throws IOException {
	int icpindex = CORRESPONDING_ICP_OBJECT_INDEX.read(inputStream);
	return (GSIRemoteProcedureIdentifier)(inputStream.standardIndexSpace.lookupObjectForIndex(icpindex));
    }
    public static void initialWrite(GSIRemoteProcedureIdentifier value, ICPOutputStream outputStream)
	throws IOException {
	Integer icpindex = (Integer)(outputStream.standardIndexSpace.lookupIndexForObject(value));
	if (null != icpindex) return;
	icpindex = new Integer(outputStream.standardIndexSpace.getIndexForObject(value));
	(new define_resumable_remote_procedure_identifier (icpindex.intValue(), 0, value)).write(outputStream);
    }
    public static void write(GSIRemoteProcedureIdentifier value, ICPOutputStream outputStream)
	throws IOException {
	Integer icpindex = (Integer)(outputStream.standardIndexSpace.lookupIndexForObject(value));
	CORRESPONDING_ICP_OBJECT_INDEX.write(icpindex.intValue(), outputStream);
    }

}
