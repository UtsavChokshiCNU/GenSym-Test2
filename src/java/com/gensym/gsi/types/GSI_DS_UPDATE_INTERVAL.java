
package com.gensym.gsi.types;

import com.gensym.gsi.*;
import com.gensym.gsi.types.*;
import com.gensym.gsi.messages.*;
import java.io.IOException;

public class GSI_DS_UPDATE_INTERVAL implements ICPType {

    public static double read(ICPInputStream inputStream) 
	throws IOException {
	return inputStream.readICPDouble();
    }
    public static void write(double value, ICPOutputStream outputStream)
	throws IOException {
	outputStream.writeICPDouble(value);
    }

}
