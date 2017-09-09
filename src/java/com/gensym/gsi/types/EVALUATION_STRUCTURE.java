
package com.gensym.gsi.types;

import com.gensym.gsi.*;
import com.gensym.gsi.types.*;
import com.gensym.gsi.messages.*;
import java.io.IOException;
import java.util.*;
import com.gensym.util.*;

public class EVALUATION_STRUCTURE implements ICPType {

    public static Structure read(ICPInputStream inputStream)
	throws IOException {
	Object[] properties = (Object [])(INTERNED_LIST.read(inputStream));
	int size = properties.length;
	Symbol[] returnedProperties = new Symbol[size];
	System.arraycopy (properties, 0, returnedProperties, 0, size);
	Object[] returnedValues = new Object[size];
	for (int i = 0; i<size; i++)
	    returnedValues[i] = REMOTE_VALUE.read(inputStream);
	return new Structure(returnedProperties, returnedValues, size);
    }

    public static void write(Structure value, ICPOutputStream outputStream)
	throws IOException {
	synchronized (value) {
	    int count = value.getAttributeCount();
	    Object[] nameArray = new Object[count];
	    int i = 0;
	    Enumeration names = value.getAttributeNames();
	    for (; names.hasMoreElements(); i++)
		nameArray[i] = names.nextElement();
	    INTERNED_LIST.write(nameArray, outputStream);
	    Enumeration values = value.getAttributeValues();
	    for (; values.hasMoreElements();)
		REMOTE_VALUE.write(values.nextElement(), outputStream);
	}
    }

}
