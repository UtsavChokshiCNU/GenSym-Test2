
package com.gensym.gsi.types;

import com.gensym.gsi.*;
import com.gensym.gsi.types.*;
import com.gensym.gsi.messages.*;
import java.io.IOException;
import java.util.*;

public class CORRESPONDING_ICP_OBJECT_INDEX_LIST implements ICPType {

    public static List read(ICPInputStream inputStream) 
	throws IOException {
	LinkedList result = new LinkedList();
	int size = ICPBYTE.read(inputStream);
	for (int i = 0; i<size; i++) 
	    result.addLast(new Integer(CORRESPONDING_ICP_OBJECT_INDEX.read(inputStream)));
	return result;
    }
    public static void write(List value, ICPOutputStream outputStream)
	throws IOException {
	ICPBYTE.write((short)(value.size()), outputStream);
	for (Iterator i = value.listIterator(0); i.hasNext(); )
	    CORRESPONDING_ICP_OBJECT_INDEX.write(((Integer)i.next()).intValue(), outputStream);
    }

}
