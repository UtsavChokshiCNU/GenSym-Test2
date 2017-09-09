
package com.gensym.tests;

import com.gensym.util.*;
import com.gensym.core.DebugUtil;
import com.gensym.message.*;
import java.util.Enumeration;

public class ClassInfoReader 
       implements com.gensym.util.symbol.AttributeExportSymbols,
                  com.gensym.util.symbol.AttributeTypeSpecificationSymbols {


  private static final Symbol CLASS_ATTRIBUTES_ = Symbol.intern ("CLASS-ATTRIBUTES"),
                              INSTANCE_ATTRIBUTES_ = Symbol.intern ("INSTANCE-ATTRIBUTES"),
                              DIRECT_SUPERIOR_CLASSES_ = Symbol.intern ("DIRECT-SUPERIOR-CLASSES"),
                              CLASS_INHERITANCE_PATH_ = Symbol.intern ("CLASS-INHERITANCE-PATH");
  private static final java.io.PrintStream o = System.out;
  private static final String x = "                     ";
                     
  public static void main (String[] args) {
    if (args.length != 1) {
      System.err.println ("Usage: java com.gensym.tests.ClassInfoReader <filename>");
      System.exit (2);
    }

    Structure classInfo = (Structure)DebugUtil.readFromFile (args[0]);
    try {
      Symbol className_ = (Symbol)classInfo.getAttributeValue (CLASS_NAME_);
      Sequence directSupClasses =
	(Sequence) classInfo.getAttributeValue (DIRECT_SUPERIOR_CLASSES_);
      boolean isSystemDefined = ((Boolean) classInfo.getAttributeValue (IS_SYSTEM_DEFINED_)).booleanValue ();
      Sequence ca = (Sequence) classInfo.getAttributeValue (CLASS_ATTRIBUTES_);
      Sequence ia = (Sequence) classInfo.getAttributeValue (INSTANCE_ATTRIBUTES_);

      o.println ("Class              : " + className_ + " (" +
		 (isSystemDefined ? "system-class" : "user-defined-class") + ")");
      o.print ("Direct Superiors   : ");
      Enumeration e = directSupClasses.elements ();
      while (e.hasMoreElements ())
	o.print ((Symbol)e.nextElement () + " ");
      o.println ();

      o.print ("Class Attributes   : ");
      e = ca.elements ();
      if (e.hasMoreElements ())
	o.println (((Structure)e.nextElement ()).getAttributeValue (ATTRIBUTE_NAME_));
      else
	o.println ();
      while (e.hasMoreElements ()) {
	Structure attrDescpn = (Structure)e.nextElement ();
	o.println (x + attrDescpn.getAttributeValue (ATTRIBUTE_NAME_));
      }

      o.print ("Instance Attributes: ");
      e = ia.elements ();
      if (e.hasMoreElements ())
	o.println (((Structure)e.nextElement ()).getAttributeValue (ATTRIBUTE_NAME_));
      else
	o.println ();
      while (e.hasMoreElements ()) {
	Structure attrDescpn = (Structure)e.nextElement ();
	o.println (x + attrDescpn.getAttributeValue (ATTRIBUTE_NAME_));
      }
    } catch (Exception e) {
      System.err.println (e);
    }
  }


}
