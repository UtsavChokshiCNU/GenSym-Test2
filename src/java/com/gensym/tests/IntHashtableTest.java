
package com.gensym.tests;

import java.util.Hashtable;
import com.gensym.core.IntHashtable;

public class IntHashtableTest {

  public static void main (String[] args) {
    Hashtable y = new Hashtable (5);
    IntHashtable x = new IntHashtable (5);
    for (int i=100; i-->0;) {
      double d = Math.random ()*100.0;
      double e = Math.random ()*100.0;
      Integer key = new Integer ((int)d),
	    value = new Integer ((int)e);
      x.put (key.intValue (), value);
      y.put (key, value);
    }
    System.out.println (x);
    System.out.println (y + "\n\n");
    for (int i=0; i<100; i+=2) {
      Integer key = new Integer (i);
      x.remove (key.intValue ());
      y.remove (key);
    }
    System.out.println (x);
    System.out.println (y);
  }

}
