
package com.gensym.gsi.types;

import com.gensym.gsi.*;
import com.gensym.gsi.types.*;
import com.gensym.gsi.messages.*;
import java.io.IOException;

public class GSI_PERMANENT_REMOTE_VALUE implements ICPType {

    public static Object read(ICPInputStream inputStream) 
	throws IOException {
	return REMOTE_VALUE.read(inputStream);
    }
    public static void write(Object value, ICPOutputStream outputStream)
	throws IOException {
	REMOTE_VALUE.write(value, outputStream);
    }

}
