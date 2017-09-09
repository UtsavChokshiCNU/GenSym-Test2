
package com.gensym.devtools;

import java.util.Properties;
import java.util.Enumeration;
import java.util.Vector;
import com.gensym.util.QuickSorter;

/**
 * Class that can be used to determine what
 * System properties have been set - in
 * alphabetical order
 */
public class DumpProperties {

  public static void main (String[] args) {
    dump ();
  }

  public static void dump () {
    Properties sysProps = System.getProperties ();
    int numEntries = sysProps.size ();
    Enumeration e = sysProps.keys ();
    Vector propKeys = new Vector (numEntries);
    while (e.hasMoreElements ())
      propKeys.addElement (e.nextElement ());
    QuickSorter qs = new QuickSorter () {
	@Override
	public boolean lessThan(Object a, Object b) {
	  return a.toString().toLowerCase().
	    compareTo(b.toString().toLowerCase()) < 0;
	}
    };
    qs.quickSortInPlace (propKeys);
    for (int i=0; i<numEntries; i++)
      System.out.println (i + " : " + propKeys.elementAt (i) + " = " +
			  System.getProperty ((String)propKeys.elementAt (i)));
  }

}
