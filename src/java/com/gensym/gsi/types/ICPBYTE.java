
package com.gensym.gsi.types;

import com.gensym.gsi.*;
import com.gensym.gsi.types.*;
import com.gensym.gsi.messages.*;
import java.io.IOException;

public class ICPBYTE implements ICPType {
    public static short read(ICPInputStream inputStream) 
	throws IOException {
	return inputStream.readICPByte();
    }
    public static void write(short value, ICPOutputStream outputStream)
	throws IOException {
	outputStream.writeICPByte(value);
    }
}

