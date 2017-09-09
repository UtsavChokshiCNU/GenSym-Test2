package com.gensym.util;

import java.util.Vector;

public class Deserializer extends Object
{
  public static Object makeUnique(Object o)
  {
    if (o instanceof Symbol)
      return Symbol.intern(((Symbol)o).toString());
    else if (o instanceof Structure)
      return ((Structure)o).cloneForDeserializer();
    else if (o instanceof Vector) /* includes sequence */
      {
        Vector s = (Vector)o;
	int size = s.size();
	Vector copy = null;
        if (o instanceof Sequence)
	  copy = new Vector(size);
	else
	  copy = new Sequence(size);

	for (int i = 0; i<size ; i++)
	  copy.addElement(makeUnique(s.elementAt(i)));
        return copy; 
      }
    else 
      return o;
  }

}
