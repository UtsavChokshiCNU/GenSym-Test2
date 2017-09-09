
package com.gensym.gsi.types;

import com.gensym.gsi.*;
import com.gensym.gsi.types.*;
import com.gensym.gsi.messages.*;
import java.io.IOException;

public class CORRESPONDING_ICP_OBJECT_INDEX implements ICPType {

    public static int read(ICPInputStream inputStream) 
	throws IOException {
	return inputStream.readICPUnsignedInteger();
    }
    public static void write(int value, ICPOutputStream outputStream)
	throws IOException {
	outputStream.writeICPUnsignedInteger(value);
    }

}
