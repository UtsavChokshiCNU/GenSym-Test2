
package com.gensym.net.g2;

import java.net.*;
import com.gensym.jgi.G2Gateway;
import com.gensym.util.*;
import com.gensym.classes.Item;
import java.util.*;
import java.io.IOException;
import java.lang.reflect.*;

/**
 * This class is a representation of an open connection to a G2
 * as a result of opening a URL. It can be used to resolve the URL
 * and download its contents. This might not suppport all the generic
 * methods that can be called. (Mostly throws exceptions for
 * getting the InputStream, bytes, or ContentHeaders). The latter
 * might actually be supported if we can actually determine the
 * type of the item that can be retreived as an RPC call.
 */

public class G2Connection extends URLConnection {

  private com.gensym.jgi.G2Connection context;
  private G2URLOperation operation, postGetOperation, postSetOperation;
  private static final Class[] postMethodArgClasses = {Item.class,
						       Sequence.class,
						       Object.class};
  static Method postGetMethod, postSetMethod, _getUniqueNamedItemMethod;
  private static final Class[] guniArgClasses = {Symbol.class,
						 Symbol.class};
  private static final Hashtable argumentNamesMap = new Hashtable (7);
  private static final java.io.PrintStream o = System.out;
  private static final boolean urlXnDebug = false;

  static {
    try {
      Class connectionClass = G2Gateway.class;
      _getUniqueNamedItemMethod = connectionClass.getMethod ("getUniqueNamedItem", guniArgClasses);
      postGetMethod = connectionClass.getMethod ("getValue", postMethodArgClasses);
      postSetMethod = connectionClass.getMethod ("setValue", postMethodArgClasses);
    } catch (NoSuchMethodException nsme) {
      System.err.println ("Unexpected error in G2Connection initializer: " + nsme);
    }
    ArgDescriptor[] _guniArgDesc = {new ArgDescriptor (Symbol.intern ("CLASS"),
					      Symbol.class,
					      true, null),
				    new ArgDescriptor (Symbol.intern ("NAME"),
						       Symbol.class,
						       false, Symbol.intern ("ITEM"))};
    ArgDescriptor[] _postMethArgDesc = {new ArgDescriptor (Symbol.intern ("ITEM"),
					      Item.class,
					      true, null),
					new ArgDescriptor (Symbol.intern ("DENOTATION"),
							   Sequence.class,
							   true, null),
					new ArgDescriptor (Symbol.intern ("DEFAULT-VALUE"),
							   Object.class,
							   false, 21)};
    ArgDescriptor[] _postSetMethArgDesc = {new ArgDescriptor (Symbol.intern ("ITEM"),
							    Item.class,
							    true, null),
					 new ArgDescriptor (Symbol.intern ("DENOTATION"),
							    Sequence.class,
							    true, null),
					 new ArgDescriptor (Symbol.intern ("NEW-VALUE"),
							    Object.class,
							    false, 21)};
    // IMHO, this is pure evil...
    argumentNamesMap.put (_getUniqueNamedItemMethod, _guniArgDesc);
    argumentNamesMap.put (postGetMethod, _postMethArgDesc);
    argumentNamesMap.put (postSetMethod, _postSetMethArgDesc);
  }
  
  G2Connection (com.gensym.jgi.G2Connection context, URL g2url) {
    super (g2url);
    this.context = context;
  }

  @Override
  public String getContentType () {
    if (urlXnDebug)
      o.println ("Returning g2/item-or-value from getContentType()");
    return "g2/data";
  }

  private void resolveURL (URL g2URL) {
    String[] components     = parseURLToComponents (g2URL);
    int queryCharIndex      = components[0].indexOf ('?');
    String actionName       = components[0].substring (0, queryCharIndex);
    String properties       = components[0].substring (queryCharIndex + 1);
    Method method           = mapActionToMethod (actionName);
    Object[] args           = transformParamsToMethodArgs (method, properties);
    operation               = new G2URLOperation (context, method, args, true);
    //Object[] methodArgs     = decomposeParams (parameters, argClasses);
    Object[] postMethodArgs = extractPostMethodArgsFromTrailingURL (components);
    if (postMethodArgs != null) {
      postGetOperation = new G2URLOperation (context, postGetMethod, postMethodArgs, true);
      postSetOperation = new G2URLOperation (context, postSetMethod, postMethodArgs, false);
    }
  }
  
  private String[] parseURLToComponents (URL g2URL) {
    String filePath = g2URL.getFile ();
    if (urlXnDebug)
      o.println ("parsing URL: " + g2URL);
    StringTokenizer tknzr = new StringTokenizer (filePath, "/", false);
    int numComponents = 0;
    Vector cVector = new Vector (3);
    while (tknzr.hasMoreTokens ()) {
      String nextLxme = tknzr.nextToken ();
      if (urlXnDebug)
	o.println ("  :Got token: " + nextLxme);
      cVector.addElement (nextLxme);
      numComponents++;
    }
    String[] components = new String[numComponents];
    cVector.copyInto (components);
    return components;
  }

  private Method mapActionToMethod (String actionName) {
    if (urlXnDebug)
      o.println ("   Trying to find method for-> " + actionName);
    if (actionName.equals ("named-item"))
      return _getUniqueNamedItemMethod;
    throw new RuntimeException ("Unknown operator in URL (" + actionName + ")");
  }

  /**
   * The case of no properties is handled properly
   */
  private static final Object[] transformParamsToMethodArgs (Method method, String properties) {
    if (urlXnDebug)
      o.println ("Entering transformParamsToMethodArgs");
    ArgDescriptor[] argDescs = (ArgDescriptor[])argumentNamesMap.get (method);
    int numArgs              = argDescs.length;
    StringTokenizer tknzr    = new StringTokenizer (properties, "&", false);
    Object[] methodArgs      = new Object[numArgs];
    if (urlXnDebug)
      o.println ("  breaking up param-string " + properties);
    while (tknzr.hasMoreTokens ()) {
      String propStr       = tknzr.nextToken ();
      int assignIndex      = propStr.indexOf ("="); // throw error!
      String propNameStr   = propStr.substring (0, assignIndex);
      String propValueStr  = propStr.substring (assignIndex + 1);
      if (urlXnDebug)
	o.println ("    name = " + propNameStr + " and value = " + propValueStr);
      Symbol propName      = Symbol.intern (propNameStr);
      int argIndex         = getIndexOfArgFromName (propName, argDescs);
      Object propValue     = castMethodArg (propValueStr, argDescs[argIndex]);
      methodArgs[argIndex] = propValue;
    }
    includeDefaultValues (methodArgs, argDescs);
    if (urlXnDebug)
      o.println ("Args for call to " + method);
    for (int i=0;i<numArgs;i++)
      if (urlXnDebug)
	o.println ("Arg " + argDescs[i].argName + " = " + methodArgs[i]);
    if (urlXnDebug)
      o.println ("Exiting transformParamsToMethodArgs");
    return methodArgs;
  }

  private static void includeDefaultValues (Object[] methodArgs, ArgDescriptor[] argDescs) {
    for (int i=0; i<methodArgs.length; i++)
      if (methodArgs[i] == null && argDescs[i].isRequired)
	methodArgs[i] = argDescs[i].defaultValue;
  }

  static int getIndexOfArgFromName (Symbol propName, ArgDescriptor[] argDescs) {
    for (int i=0; i<argDescs.length; i++) {
      if (urlXnDebug)
	o.println ("> Comparing " + propName + "@" + propName.hashCode() + " <=> " + argDescs[i].argName + "@" + argDescs[i].argName.hashCode());
      if (propName.equals(argDescs[i].argName))
	return i;
    }
    throw new RuntimeException ("Unknown param " + propName);
  }

  private static Object castMethodArg (String valueStr, ArgDescriptor argumentDescrpn) {
    Class argClass = argumentDescrpn.classType;
    if (argClass == String.class)
      return valueStr;
    else if (argClass == Symbol.class)
      return Symbol.intern (valueStr);
    else if (argClass == Integer.class || argClass == Object.class)
      return Integer.valueOf (valueStr);
    else
      throw new RuntimeException ("Cannot reconstruct " + argClass + " from string \"" + valueStr + "\"");
  }

  /**
   * First verify that this is a known action
   * Then package up the rest of the args as a Sequence (ugh!)
   * Each component of the path is converted into a structure
   * where each property value is a symbol. (ugh ugh)
   */
  private static Object[] extractPostMethodArgsFromTrailingURL (String[] components) {
    if (components.length == 1)
      return null;
    int queryCharIndex       = components[1].indexOf ('?');
    if (!(components[1].substring (0, queryCharIndex).equals ("value")))
      throw new RuntimeException ("Tell vkp to support a more general URL Specification.");
    String properties        = components[1].substring(queryCharIndex + 1);
    Object[] postMethodArgs  = transformParamsToMethodArgs (postGetMethod, properties);

    int numComponents        = components.length;
    int numTrailingArgs      = numComponents - 2;    /* 0 = orig method call,
							1 = implicit post method */
    Sequence seq        = new Sequence (numTrailingArgs);
    for (int i=2; i<numComponents; i++) {
      Structure s = transformParamsToStructure (components[i]);
      seq.addElement (s);
    }
    int denotationArgIndex = 1;
    postMethodArgs[denotationArgIndex] = seq;
    return postMethodArgs;
  }

  private static Structure transformParamsToStructure (final String properties) {
    Structure newStruct      = new Structure ();
    StringTokenizer tknzr    = new StringTokenizer (properties, "&", false);
    String props = properties;
    while (tknzr.hasMoreTokens ()) {
      String propStr       = tknzr.nextToken ();
      int assignIndex      = propStr.indexOf ("="); // throw error!
      if (assignIndex < 0) {
	    props = "type=attribute&name=" + props;
      }
      String propNameStr   = propStr.substring (0, assignIndex);
      String propValueStr  = propStr.substring (assignIndex + 1);
      Symbol propName      = Symbol.intern (propNameStr);
      Symbol propValue     = Symbol.intern (propValueStr);
      newStruct.setAttributeValue (propName, propValue);
    }
    if (urlXnDebug)
	o.println ("Transformed '" + props + "' into -> " + newStruct);
    return newStruct;
  }

  public com.gensym.jgi.G2Connection getContext () {
    return context;
  }

  public G2URLOperation getOperation () {
    return operation;
  }

  public G2URLOperation getPostGetOperation () {
    return postGetOperation;
  }

  public G2URLOperation getPostSetOperation () {
    return postSetOperation;
  }

  static ArgDescriptor[] getArgumentDescriptionsForMethod (Method method) {
    return (ArgDescriptor[])argumentNamesMap.get (method);
  }

  @Override
  public void connect () throws IOException {
    throw new IOException ("G2 URLs do not support connect");
  }
}


class ArgDescriptor {

  Symbol argName;
  Class classType;
  boolean isRequired;
  Object defaultValue;

  ArgDescriptor (Symbol argName, Class classType, boolean isRequired, Object defaultValue) {
    this.argName = argName;
    this.classType = classType;
    this.isRequired = isRequired;
    this.defaultValue = defaultValue;
  }
}
