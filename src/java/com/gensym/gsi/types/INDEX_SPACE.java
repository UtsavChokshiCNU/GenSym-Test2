
package com.gensym.gsi.types;

import com.gensym.gsi.*;
import com.gensym.gsi.types.*;
import com.gensym.gsi.messages.*;
import java.io.IOException;

public class INDEX_SPACE implements ICPType {

    public static IndexSpace read(ICPInputStream inputStream) 
	throws IOException {
	return null;
    }
    public static void write(IndexSpace value, ICPOutputStream outputStream)
	throws IOException {
	// outputStream.writeICPInteger(value);
    }

}
