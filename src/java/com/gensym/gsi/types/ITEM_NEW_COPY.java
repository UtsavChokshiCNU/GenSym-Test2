
package com.gensym.gsi.types;

import com.gensym.gsi.*;
import com.gensym.gsi.types.*;
import com.gensym.gsi.messages.*;
import java.io.IOException;

public class ITEM_NEW_COPY implements ICPType {

    public Structure read(ICPInputStream inputStream)
	throws IOException {
	Symbol[] properties = (Symbol[])INTERNED_LIST.read(inputStream);
	int size = properties.length;
	Symbol[] returnedProperties = new Symbol[size];
	System.arraycopy (properties, 0, returnedProperties, 0, size);
	Object[] returnedValues = new Object[size];
	for (int i = 0; i<size; i++)
	    returnedValues[i] = REMOTE_VALUE.read(inputStream);
	return new Structure(returnedProperties, returnedValues, size);
    }

    public void write(Structure value, ICPOutputStream outputStream)
	throws IOException {
    }

}
