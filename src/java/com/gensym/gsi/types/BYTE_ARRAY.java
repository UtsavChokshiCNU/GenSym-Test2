
package com.gensym.gsi.types;

import com.gensym.gsi.*;
import com.gensym.gsi.types.*;
import com.gensym.gsi.messages.*;
import java.io.IOException;

public class BYTE_ARRAY implements ICPType {
    public static short[] read(ICPInputStream inputStream) 
	throws IOException {
	return inputStream.readICPByteArray();
    }
    public static char[] readCharArray(ICPInputStream inputStream) 
	throws IOException {
	return inputStream.readICPByteArrayAsCharArray();
    }
    public static void write(short[] value, ICPOutputStream outputStream)
	throws IOException {
	outputStream.writeICPByteArray(value);
    }
    public static void writeCharArray(char[] value, ICPOutputStream outputStream)
	throws IOException {
	outputStream.writeICPByteArrayAsCharArray(value);
    }
}

