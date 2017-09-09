
package com.gensym.gsi.types;

import com.gensym.gsi.*;
import com.gensym.gsi.types.*;
import com.gensym.gsi.messages.*;
import java.io.IOException;
import java.util.Map;

public class NUMBER_OF_ICP_BYTES_OF_FILL implements ICPType {
    public static Map read(ICPInputStream inputStream) 
	throws IOException {
	int number_of_bytes = ICP_BYTE.read(inputStream);
	int first_byte = ICP_BYTE.read(inputStream);
	if (first_byte == 0) {
	    for (int i=1; i<number_of_bytes; i++)
		ICP_BYTE.read(inputStream);
	    return null;
	} else {
	    int type_and_size = first_byte;
	    Map result = new HashMap();
	    while (type_and_size != 0) {
		int type_code = type_and_size >> 10;
		int size = type_and_size & ((1<<10)-1);
		int mode = 0;
		NUMBER_OF_ICP_BYTES_OF_FILL.
		    readElement(result,type_code, size, mode, inputStream);
	    }
	    return result;
	}
    }
    public static void readElement(Map map, int type_code, int size, int mode, ICPInputStream inputStream) 
	throws IOException {
	Symbol name = NUMBER_OF_ICP_BYTES_OF_FILL.get_name_for_code(type_code, mode);
	int type = NUMBER_OF_ICP_BYTES_OF_FILL.get_type_for_code(type_code, mode);
	Object value;
	switch (type) {
	case NULL_TYPE: 
	    value = null; 
	    break;
	case FIXNUM_TYPE: 
	    value = FIXNUM.read(inputStream);
	    break;
	case GENSYM_STRING_TYPE:
	    value = GENSYM_STRING.read(inputStream);
	    break;
	case WIDE_STRING_TYPE:
	    value = TEXT_STRING.read(inputStream);
	    break;
	case SYMBOL_TYPE:
	    value = Symbol.intern(GENSYM_STRING.read(inputStream));
	    break;
	default: 
	    for (int i=1; i<size; i++)
		ICP_BYTE.read(inputStream);
	    return null;
	}
	map.put(name, value);
    }
    public static void write(Map value, ICPOutputStream outputStream)
	throws IOException {
	ICP_BYTE.write(0, outputStream);
    }
}
