
package com.gensym.gsi.types;

import com.gensym.gsi.*;
import com.gensym.gsi.types.*;
import com.gensym.gsi.messages.*;
import java.io.IOException;

public class TEXT_STRING implements ICPType {
    public static String read(ICPInputStream inputStream) 
	throws IOException {
	return inputStream.readICPString();
    }
    public static void write(String value, ICPOutputStream outputStream)
	throws IOException {
	outputStream.writeICPString(value);
    }
}

