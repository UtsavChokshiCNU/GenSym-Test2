
package com.gensym.tests;

import com.gensym.jgi.G2Access;
import com.gensym.jgi.G2Gateway;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.ConnectionTimedOutException;
import com.gensym.classes.Procedure;
import com.gensym.util.Symbol;
import com.gensym.util.Structure;
import com.gensym.classes.Definition;
import com.gensym.util.DefinitionListener;
import com.gensym.util.DefinitionEvent;
import com.gensym.message.Trace;
import com.gensym.message.TraceOut;

public class ClassAttributeAccessTest {

  private static TraceOut traceListener = new TraceOut();

  private static final Symbol PROCEDURE_ = Symbol.intern ("PROCEDURE"),
  DA_DA_DA_  = Symbol.intern ("DA-DA-DA"),
    ITEM_      = Symbol.intern ("ITEM"),
    BA_BA_BA_  = Symbol.intern ("BA-BA-BA");

  public static void main (String[] args) throws ConnectionTimedOutException, G2AccessException {
    String host = "bombay";
    String port = "1111";
    G2Access context = G2Gateway.getOrMakeConnection (host, port);
    Structure iconDescription;

    /*
      Procedure p = (Procedure) context.getUniqueNamedItem (PROCEDURE_, DA_DA_DA_);
      iconDescription = p.getIconDescriptionForClass ();
      System.out.println ("The icon description of the procedure named DA-DA-DA is -> " + iconDescription);


    Trace.setTraceOn(true);
    traceListener.initialize("com.gensym.util.stubs", Trace.ALL_LEVELS, null);
    traceListener.setShowMessageLookup (true);
      */

    com.gensym.classes.Object x = (com.gensym.classes.Object) context.getUniqueNamedItem (ITEM_, BA_BA_BA_);
    iconDescription = x.getIconDescriptionForClass ();
    System.out.println ("The icon description of the object named BA-BA-BA is -> " + iconDescription);

    Definition d = (Definition)x.getDefinition ();
    d.addDefinitionListener (new TestClassListener ());
  }

}


class TestClassListener implements DefinitionListener {

  
  @Override
  public void staticAttributeChanged (DefinitionEvent e) {System.out.println ("Class Attribute Changed : " + e);}

  @Override
  public void classNameChanged (DefinitionEvent e) {System.out.println ("Class Name Changed : " + e);}
  
  @Override
  public void directSuperiorClassesChanged (DefinitionEvent e) {System.out.println ("Class Superiors Changed : " + e);}

  @Override
  public void deleted (DefinitionEvent e) {System.out.println ("Class Deleted : " + e);}

  @Override
  public void classInheritancePathChanged (DefinitionEvent e) {System.out.println ("Class Inh Path Changed : " + e);}

  @Override
  public void classSpecificAttributesChanged (DefinitionEvent e) {System.out.println ("Class Specific Attribute Changed : " + e);}

}
