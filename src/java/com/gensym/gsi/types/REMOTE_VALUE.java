
package com.gensym.gsi.types;

import com.gensym.gsi.*;
import com.gensym.gsi.types.*;
import com.gensym.gsi.messages.*;
import java.io.IOException;
import com.gensym.util.*;

public class REMOTE_VALUE implements ICPType, ICPTypeTags {

    public static Object read(ICPInputStream inputStream) 
	throws IOException {
	return null;
    }
    public static Object read(ICPInputStream inputStream, int implicitTag) 
	throws IOException {
	return null;
    }
    public static void write(Object value, ICPOutputStream outputStream)
	throws IOException {
	write(value, outputStream, true);
    }
    public static void write(Object value, ICPOutputStream outputStream, boolean writeTag)
	throws IOException {
	if (value == null) {
	    if (writeTag) ICPBYTE.write(GSI_NULL_TYPE_TAG, outputStream);
	} else if (value instanceof Boolean) {
	    if (writeTag) ICPBYTE.write(GSI_LOGICAL_TYPE_TAG, outputStream);
	    INTEGER.write(((Boolean)value).booleanValue()?1000:-1000, outputStream);
	} else if (value instanceof Byte) {
	    if (writeTag) ICPBYTE.write(GSI_INTEGER_TYPE_TAG, outputStream);
	    INTEGER.write(((Byte)value).intValue(), outputStream);
	} else if (value instanceof Short) {
	    if (writeTag) ICPBYTE.write(GSI_INTEGER_TYPE_TAG, outputStream);
	    INTEGER.write(((Short)value).intValue(), outputStream);
	} else if (value instanceof Integer) {
	    if (writeTag) ICPBYTE.write(GSI_INTEGER_TYPE_TAG, outputStream);
	    INTEGER.write(((Integer)value).intValue(), outputStream);
	} else if (value instanceof Long) {
	    REMOTE_VALUE.write(value.toString(), outputStream);
	} else if (value instanceof Symbol) {
	    SYMBOL_AS_VALUE_TYPE.write((Symbol)value, outputStream);
	} else if (value instanceof Float) {
	    if (writeTag) ICPBYTE.write(GSI_64BIT_FLOAT_TYPE_TAG, outputStream);
	    DOUBLE.write(((Float)value).doubleValue(), outputStream);
	} else if (value instanceof Double) {
	    if (writeTag) ICPBYTE.write(GSI_64BIT_FLOAT_TYPE_TAG, outputStream);
	    DOUBLE.write(((Double)value).doubleValue(), outputStream);
	} else if (value instanceof String) {
	    if (writeTag) ICPBYTE.write(GSI_STRING_TYPE_TAG, outputStream);
	    TEXT_STRING.write((String)value, outputStream);
	} else if (value instanceof short[]) {
	    if (writeTag) ICPBYTE.write(GSI_UNSIGNED_SHORT_VECTOR_TYPE_TAG, outputStream);
	    BYTE_ARRAY.write((short[])value, outputStream);
	} else if (value instanceof char[]) {
	    if (writeTag) ICPBYTE.write(GSI_UNSIGNED_SHORT_VECTOR_TYPE_TAG, outputStream);
	    BYTE_ARRAY.writeCharArray((char[])value, outputStream);
	} 
	//	else if (value instanceof Handle) {
	//	    if (writeTag) ICPBYTE.write(RPC_OBJECT_HANDLE_TYPE_TAG, outputStream);
	//	    INTEGER.write(value.index(), outputStream);
	//	} 
	else if (value instanceof Structure) {
	    if (writeTag) ICPBYTE.write(GSI_STRUCTURE_TYPE_TAG, outputStream);
	    EVALUATION_STRUCTURE.write((Structure)value, outputStream);
	} else if (value instanceof Sequence) {
	    EVALUATION_SEQUENCE.write((Sequence)value, outputStream);
	} else if (value instanceof Object) {
	    ITEM.write(value, outputStream);
	} else {
	    if (writeTag) ICPBYTE.write(GSI_NULL_TYPE_TAG, outputStream);
	}
    }

}
