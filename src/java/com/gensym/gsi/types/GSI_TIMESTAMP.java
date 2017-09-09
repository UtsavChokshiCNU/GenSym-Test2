
package com.gensym.gsi.types;

import com.gensym.gsi.*;
import com.gensym.gsi.types.*;
import com.gensym.gsi.messages.*;
import java.io.IOException;

public class GSI_TIMESTAMP implements ICPType {

    public static double read(ICPInputStream inputStream) 
	throws IOException {
	return DOUBLE.read(inputStream);
    }
    public static void write(double value, ICPOutputStream outputStream)
	throws IOException {
	DOUBLE.write(value, outputStream);
    }

}
