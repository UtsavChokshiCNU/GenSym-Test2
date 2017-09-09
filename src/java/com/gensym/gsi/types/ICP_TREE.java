
package com.gensym.gsi.types;

import com.gensym.gsi.*;
import com.gensym.gsi.types.*;
import com.gensym.gsi.messages.*;
import java.io.IOException;

import com.gensym.util.Symbol;

public class ICP_TREE implements ICPType, ICPTypeTags {

    public static Object read(ICPInputStream inputStream)
	throws IOException {
	short tag = inputStream.peekICPByte();
	switch (tag) {
	case ICP_STANDARD_INDEX_SPACE_TYPE_TAG: 
	    return SYMBOL_AS_VALUE_TYPE.read(inputStream);
	case ICP_TEMPORARY_INDEX_SPACE_TYPE_TAG:
	    return SYMBOL_AS_VALUE_TYPE.read(inputStream);
	case ICP_NEW_SYMBOL_TYPE_TAG:
	    return SYMBOL_AS_VALUE_TYPE.read(inputStream);
	case ICP_NEW_KEYWORD_SYMBOL_TYPE_TAG:
	    return SYMBOL_AS_VALUE_TYPE.read(inputStream);
	case ICP_NEW_SYMBOL_EXPANDING_INDEX_SPACE_TYPE_TAG:
	    return SYMBOL_AS_VALUE_TYPE.read(inputStream);
	case GSI_NULL_TYPE_TAG:
	    ICPBYTE.read(inputStream);
	    return null;
	case GSI_INTEGER_TYPE_TAG:
	    ICPBYTE.read(inputStream);
	    return INTEGER.read(inputStream);
	case GSI_64BIT_FLOAT_TYPE_TAG:
	    ICPBYTE.read(inputStream);
	    return DOUBLE.read(inputStream);
	case GSI_STRING_TYPE_TAG:
	    ICPBYTE.read(inputStream);
	    return TEXT_STRING.read(inputStream);
	case ICP_TREE_INTERNED_LIST_TYPE_TAG:
	    ICPBYTE.read(inputStream);
	    return INTERNED_LIST_AS_VALUE_TYPE.read(inputStream);
	case ICP_LIST_TYPE_TAG:
	    ICPBYTE.read(inputStream);
	    Object result = new Cons(null, null);
	    Object tail = result;
	    while (true) {
		tail.car = ICP_TREE.read(inputStream);
		tag = inputStream.peekICPByte();
		switch (tag) {
		case ICP_LIST_NON_NIL_TERMINATOR_TYPE_TAG:
		    ICPBYTE.read(inputStream);
		    tail.cdr = ICP_TREE.read(inputStream);
		    return result;
		case ICP_LIST_NIL_TERMINATOR_TYPE_TAG:
		    ICPBYTE.read(inputStream);
		    tail.cdr = null;
		    return result;
		} else {
		    Object next = new Cons(null, null);
		    tail.cdr = next;
		    tail = next;
		}
	    }
	case ICP_CONS_TYPE_TAG:
	    ICPBYTE.read(inputStream);
	    return new Cons(ICP_TREE.read(inputStream),
			    ICP_TREE.read(inputStream));
	}
	return null;
    }

    public static void write(Object value, ICPOutputStream outputStream)
	throws IOException {
	if (value == null) {
	    ICPBYTE.write(GSI_NULL_TYPE_TAG, outputStream);
	} else if (value instanceof Integer) {
	    ICPBYTE.write(GSI_INTEGER_TYPE_TAG, outputStream);
	    INTEGER.write(((Integer)value).intValue(), outputStream);
	} else if (value instanceof Symbol) {
	    SYMBOL_AS_VALUE_TYPE.write((Symbol)value, outputStream);
	} else if (value instanceof Double) {
	    ICPBYTE.write(GSI_64BIT_FLOAT_TYPE_TAG, outputStream);
	    DOUBLE.write(((Double)value).doubleValue(), outputStream);
	} else if (value instanceof String) {
	    ICPBYTE.write(GSI_STRING_TYPE_TAG, outputStream);
	    TEXT_STRING.write((String)value, outputStream);
	} else if (value instanceof InternedList) {
	    ICPBYTE.write(ICP_TREE_INTERNED_LIST_TYPE_TAG, outputStream);
	    INTERNED_LIST_AS_VALUE_TYPE.write((InternedList)value, outputStream);
	} else if (value instanceof Cons) {
	    if (((Cons)value).cdr instanceof Cons) {
		ICPBYTE.write(ICP_LIST_TYPE_TAG, outputStream);
		Object tail = value;
		for (; tail instanceof Cons; tail = ((Cons)tail).get_cdr()) {
		    ICP_TREE.write(((Cons)tail).car, outputStream);
		}
		if (tail == null) {
		    ICPBYTE.write(ICP_LIST_NON_NIL_TERMINATOR_TYPE_TAG, outputStream);
		    ICP_TREE.write(tail, outputStream);
		} else {
		    ICPBYTE.write(ICP_LIST_NIL_TERMINATOR_TYPE_TAG, outputStream);
		}
	    } else {
		ICPBYTE.write(ICP_CONS_TYPE_TAG, outputStream);
		ICP_TREE.write(((Cons)value).car, outputStream);
		ICP_TREE.write(((Cons)value).cdr, outputStream);
	    }
	} else {
	    ICPBYTE.write(GSI_NULL_TYPE_TAG, outputStream);
	}
    }

}
