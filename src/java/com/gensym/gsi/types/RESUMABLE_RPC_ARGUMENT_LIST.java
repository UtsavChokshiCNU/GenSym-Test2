
package com.gensym.gsi.types;

import com.gensym.gsi.*;
import com.gensym.gsi.types.*;
import com.gensym.gsi.messages.*;
import java.io.IOException;

public class RESUMABLE_RPC_ARGUMENT_LIST implements ICPType {

    public static Object[] read(ICPInputStream inputStream) 
	throws IOException {
	int length = UNSIGNED_INTEGER.read(inputStream);
	Object[] result = new Object[length];
	for (int index=0; index<length; index++) 
	    result[index] = REMOTE_VALUE.read(inputStream);
	return result;
    }
    public static void write(Object[] value, ICPOutputStream outputStream)
	throws IOException {
	UNSIGNED_INTEGER.write(value.length, outputStream);
	for (int index=0; index<value.length; index++) 
	    REMOTE_VALUE.write(value[index], outputStream);	
    }

}
