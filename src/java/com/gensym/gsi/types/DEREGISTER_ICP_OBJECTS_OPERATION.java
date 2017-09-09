
package com.gensym.gsi.types;

import com.gensym.gsi.*;
import com.gensym.gsi.types.*;
import com.gensym.gsi.messages.*;
import java.io.IOException;

public class DEREGISTER_ICP_OBJECTS_OPERATION implements ICPType {

    public static byte read(ICPInputStream inputStream) 
	throws IOException {
	return (byte)(ICPBYTE.read(inputStream));
    }
    public static void write(byte value, ICPOutputStream outputStream)
	throws IOException {
	ICPBYTE.write(value, outputStream);
    }

}
