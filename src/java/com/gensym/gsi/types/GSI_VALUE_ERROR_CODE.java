
package com.gensym.gsi.types;

import com.gensym.gsi.*;
import com.gensym.gsi.types.*;
import com.gensym.gsi.messages.*;
import java.io.IOException;

public class GSI_VALUE_ERROR_CODE implements ICPType {

    public static int read(ICPInputStream inputStream) 
	throws IOException {
	return UNSIGNED_INTEGER.read(inputStream);
    }
    public static void write(int value, ICPOutputStream outputStream)
	throws IOException {
	UNSIGNED_INTEGER.write(value, outputStream);
    }

}
