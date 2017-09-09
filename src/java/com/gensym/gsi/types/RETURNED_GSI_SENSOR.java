
package com.gensym.gsi.types;

import com.gensym.gsi.*;
import com.gensym.gsi.types.*;
import com.gensym.gsi.messages.*;
import java.io.IOException;

public class RETURNED_GSI_SENSOR implements ICPType, ICPTypeTags {

    public static int read(ICPInputStream inputStream)
	throws IOException {
	// Not read by GSI
	return 0;
    }
    public static void write(int value, ICPOutputStream outputStream)
	throws IOException {
	ICPBYTE.write(GSI_INTEGER_TYPE_TAG, outputStream);
	CORRESPONDING_ICP_OBJECT_INDEX.write(value, outputStream);
    }
    public static void write(Object value, ICPOutputStream outputStream)
	throws IOException {
	ITEM_REFERENCE.write(value, outputStream);
    }

}
