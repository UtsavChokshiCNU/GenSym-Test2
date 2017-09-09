
package com.gensym.gsi.types;

import com.gensym.gsi.*;
import com.gensym.gsi.types.*;
import com.gensym.gsi.messages.*;
import java.io.IOException;

public class UNSIGNED_INTEGER_OR_NIL implements ICPType {

    public static Integer read(ICPInputStream inputStream) 
	throws IOException {
	int value = inputStream.readICPInteger();
	return (value < 0) ? null : new Integer(value);
    }
    public static void write(Integer value, ICPOutputStream outputStream)
	throws IOException {
	outputStream.writeICPInteger((value==null)?-1:value.intValue());
    }

}
