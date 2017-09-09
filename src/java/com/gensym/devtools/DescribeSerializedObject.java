
package com.gensym.devtools;

import java.util.Vector;
import com.gensym.core.*;
import com.gensym.util.*;

public class DescribeSerializedObject {
  public static void main (String[] args) throws Exception {
    int numObjects = 0;
    if (args.length != 1)
      numObjects = Integer.parseInt (args[1]);
    Object[] objs = DebugUtil.readFromFile (args[0], numObjects);
    for (int i=0; i<objs.length; i++) {
      Object o = objs[i];
      System.out.println (i + " " + o.getClass ());
      System.out.println ("  " + o);
      if (o instanceof Sequence)
	((Sequence)o).print ();
      else if (o instanceof Vector) {
	Vector v = (Vector)o;
	System.out.println (o + " Is a vector of size " + v.size ());
	for (int j=0; j<v.size (); j++)
	  System.out.println ("#" + j + " = " + v.elementAt (j));
      }
      if (o instanceof com.gensym.beaneditor.Wrapper)
	System.out.println ("  Bean = " + ((com.gensym.beaneditor.Wrapper)o).bean);
    }
    System.exit (0);
  }
}
