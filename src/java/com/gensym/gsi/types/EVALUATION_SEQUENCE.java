
package com.gensym.gsi.types;

import com.gensym.gsi.*;
import com.gensym.gsi.types.*;
import com.gensym.gsi.messages.*;
import java.io.IOException;
import com.gensym.util.Sequence;

public class EVALUATION_SEQUENCE implements ICPType, ICPTypeTags {

    public static Sequence read(ICPInputStream inputStream)
	throws IOException {
	boolean typed = ICPBYTE.read(inputStream) == GSI_TYPED_SEQUENCE_TYPE_TAG;
	int typetag = typed ? ICPBYTE.read(inputStream) : GSI_VALUE_TYPE_TAG;
	int size = INTEGER.read(inputStream);
	Sequence result = new Sequence(size);
	for (int i = 0; i<size; i++)
	    result.addElement((typetag == GSI_VALUE_TYPE_TAG) ?
			      REMOTE_VALUE.read(inputStream) :
			      REMOTE_VALUE.read(inputStream, typetag));
	return result;
    }

    public static void write(Sequence value, ICPOutputStream outputStream)
	throws IOException {
	ICPBYTE.write(GSI_SEQUENCE_TYPE_TAG, outputStream);
	int size = value.size();
	INTEGER.write(size, outputStream);
	for (int i = 0; i<size; i++)
	    REMOTE_VALUE.write(value.elementAt(i), outputStream);
    }

}
