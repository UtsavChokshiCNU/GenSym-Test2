
package com.gensym.gsi.types;

import com.gensym.gsi.*;
import com.gensym.gsi.types.*;
import com.gensym.gsi.messages.*;
import java.io.IOException;

import com.gensym.util.Symbol;

public class GSI_ICP_INTERFACE implements ICPType {

    public static ICPSocket read(ICPInputStream inputStream) 
	throws IOException {
	CORRESPONDING_ICP_OBJECT_INDEX.read(inputStream);
	return inputStream.sck;
    }
    public static void initialWrite(ICPSocket value, ICPOutputStream outputStream)
	throws IOException {
	// never written by GSI
    }
    public static void write(Symbol value, ICPOutputStream outputStream)
	throws IOException {
	// never written by GSI
    }

}
