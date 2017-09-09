
package com.gensym.gsi.types;

import com.gensym.gsi.*;
import com.gensym.gsi.types.*;
import com.gensym.gsi.messages.*;
import java.io.IOException;

public class ICP_TASK_RESUMABLE_P implements ICPType {

    public static boolean read(ICPInputStream inputStream) 
	throws IOException {
	return BOOLEAN.read(inputStream);
    }
    public static void write(boolean value, ICPOutputStream outputStream)
	throws IOException {
	BOOLEAN.write(value, outputStream);
    }

}
