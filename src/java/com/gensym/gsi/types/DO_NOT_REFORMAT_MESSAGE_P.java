
package com.gensym.gsi.types;

import com.gensym.gsi.*;
import com.gensym.gsi.types.*;
import com.gensym.gsi.messages.*;
import java.io.IOException;

public class DO_NOT_REFORMAT_MESSAGE_P implements ICPType {

    public static boolean read(ICPInputStream inputStream) 
	throws IOException {
	return inputStream.readICPBoolean();
    }
    public static void write(boolean value, ICPOutputStream outputStream)
	throws IOException {
	outputStream.writeICPBoolean(value);
    }

}
