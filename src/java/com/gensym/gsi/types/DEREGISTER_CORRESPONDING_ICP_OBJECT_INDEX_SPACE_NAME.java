
package com.gensym.gsi.types;

import com.gensym.gsi.*;
import com.gensym.gsi.types.*;
import com.gensym.gsi.messages.*;
import java.io.IOException;

import com.gensym.util.Symbol;

public class DEREGISTER_CORRESPONDING_ICP_OBJECT_INDEX_SPACE_NAME implements ICPType {

    public static Symbol read(ICPInputStream inputStream) 
	throws IOException {
	return SYMBOL_AS_VALUE_TYPE.read(inputStream);
    }
    public static void write(Symbol value, ICPOutputStream outputStream)
	throws IOException {
	SYMBOL_AS_VALUE_TYPE.write(value, outputStream);
    }

}
