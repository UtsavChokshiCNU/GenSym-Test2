
package com.gensym.jgi;

import java.io.*;
import java.lang.reflect.*;
import java.util.Vector;
import java.util.Hashtable;
import com.gensym.core.GensymApplication;
import com.gensym.util.*;
import com.gensym.classes.Item;
import com.gensym.classes.G2Definition;
import com.gensym.classes.Definition;
/**
 * This class is responsible for creating an Interface adapter that will be used for 
 * a G2 item that wishes to implement Java interfaces. The resulting adapter can 
 * be returned and accepted to Java (in place of the G2 item) as it will 
 * fully implement the correct Java Interfaces. 
 * The actual adapter will (for each Interface method pass the Java call to the appropriate G2
 * method on the original G2 Item
 */
public class G2JavaStubInterfaceGenerator {

  private PrintWriter output;
  private Class interfaceClass;
  private String adapterClassName;
  private Vector interfacesToImplement;
  protected static String adapterPrefix = "G2JavaProxyAdapter_";
  protected static String adapterPackageName = "g2proxyadapter";
  protected static volatile String adapterRepositoryDir = "";
  protected static String g2ProxyVarName = "g2InterfaceProxy";


  protected G2JavaStubInterfaceGenerator(Vector interfacesToImplement, 
			       String adapterClassName) {
    this.interfacesToImplement = interfacesToImplement;
    this.adapterClassName = adapterClassName;
  }

  private static Hashtable adapters = new Hashtable();
  protected static Class[] constructorParams = 
                 new Class[] {G2JavaStubController.class, G2Access.class, Item.class};

  protected static Constructor getAdapterConstructor(DownLoad downloader, 
					   Vector interfacesToImplement,
					   G2Access context,
					   Symbol g2ClassName)
       throws NoSuchMethodException,
              ClassNotFoundException,
              G2AccessException {
    try {
      G2Definition def = context.getClassManager().getDefinition(g2ClassName);
      String moduleName = "system";
      if (def instanceof Definition) {
	Symbol moduleNameSym = ((Definition)def).getContainingModule();
	moduleName = G2ClassTranslator.createJavaNameFromG2Name(moduleNameSym);
      }
      String userPackageStart = System.getProperty ("com.gensym.class.user.package");
      String proxyJavaName = G2ClassTranslator.createJavaNameFromG2Name(g2ClassName);
      String adapterClassName = userPackageStart.replace('.','_') + "_" + 
	                        moduleName + "_" + proxyJavaName + "_adapter";

      Class adapterClass = getAdapterClass(downloader, 
					   adapterClassName,
					   new G2JavaStubInterfaceGenerator(interfacesToImplement, 
									    adapterClassName));
      Constructor cons = adapterClass.getConstructor(constructorParams);
      return cons;
    } catch (JavaClassCompilerException e) {
      throw new RuntimeException(e.toString());
    }
  }

  static Object createAdapter(Constructor cons, 
			      G2JavaStubController controller, 
			      G2Access connection, 
			      Item g2Proxy)
    throws InstantiationException,
           InvocationTargetException, 
           IllegalAccessException {
 
	try { // This is here due to a strange problem with the JDK1.1.6 JIT
	  // The use of the Constructor with args, later on would fail, if we dont
	  // create a dummy instance here !
	  cons.getDeclaringClass().newInstance ();
	} catch (Exception e) {
	  com.gensym.message.Trace.exception (e);
	} 
    return cons.newInstance(new Object[] {controller, connection, g2Proxy});
  }

  protected static Class getAdapterClass(DownLoad downloader,
					 String adapterClassName,
					 G2JavaStubInterfaceGenerator generator)
       throws JavaClassCompilerException, 
              ClassNotFoundException {
    String fullAdapterClassName = adapterPackageName + "." + adapterClassName; 
    adapterRepositoryDir = System.getProperty ("com.gensym.class.user.repository") +
                           System.getProperty ("file.separator") +
                           adapterPackageName.replace('.', '/') +
                           System.getProperty ("file.separator");
    Class adapterClass = null;
    try {
      adapterClass = downloader.lookupClass(fullAdapterClassName);
    } catch (ClassNotFoundException e) {
      // Not found create the adapter
      String adapterSource = generator.emitInterfaceAdapter();
      File adapterRepositoryDirFile = new File(adapterRepositoryDir);
      if (!adapterRepositoryDirFile.exists()) 
	adapterRepositoryDirFile.mkdirs();
      downloader.loadJavaClass(adapterRepositoryDir, fullAdapterClassName, adapterSource);
      adapterClass = downloader.lookupClass(fullAdapterClassName);
    }
    adapters.put(fullAdapterClassName, adapterClass);
    return adapterClass;
  }

  protected static G2JavaStubInterfaceGenerator getAdapterGenerator(Vector interfacesToImplement, 
								  String adapterClassName) {
   return  new G2JavaStubInterfaceGenerator(interfacesToImplement, 
					    adapterClassName);
  }


  protected String emitInterfaceAdapter() {
    StringWriter strWriter = new StringWriter();
    output = new PrintWriter (strWriter, true);

    emitClass();
    output.close ();
    return strWriter.toString();
  }

  protected void emitHeader() {

    iprintln("/*");
    iprintln(" *  Copyright (c) " +"1998 " + G2ClassTranslator.companyName + ".");
    iprintln(" *  All Rights Reserved.");
    iprintln(" *");
    iprintln(" *      " + adapterClassName + ".java");
	iprintln(" *");
	iprintln(" *   Description: Generated G2 Java Proxy Interface Adpater. Do not edit!");
	iprintln(" *");
	iprintln(" *        Author: Gensym Corp.");
	iprintln(" *");
	iprintln(" *       Version: 5.1");
	iprintln(" *");
	iprintln(" *          Date: " + new java.util.Date());
	iprintln(" *");
	iprintln(" */\n\n");

    iprintln ("package " + adapterPackageName + ";");
    iprintln ("");
    iprintln ("import com.gensym.util.*;");
    iprintln ("import com.gensym.jgi.*;");
    iprintln ("import com.gensym.classes.Item;");
    iprintln ("");
  }

  protected void emitClass() {

    emitHeader();

    iprint ("public class " + adapterClassName + " implements java.io.Serializable");
    for (int i = 0; i<interfacesToImplement.size(); i++) {
      String interfaceName = ((Class)interfacesToImplement.elementAt(i)).getName();
      iprint("," + interfaceName);
    }
    iprintln("{");
    iprintln("");
    increaseIndent(2);

    // Fields
    iprintln ("");
    iprintln ("static final long serialVersionUID = -441189241920989898L;");
    iprintln ("private G2JavaStubController controller;");
    iprintln ("private Item " + g2ProxyVarName + ";");
    iprintln ("private G2Access context;");
    iprintln ("");

    // Constructor
    iprintln("// Do not use, here due to JIT problems");
    iprintln("public " + adapterClassName + "() {}");
    iprintln("");

    iprintln("public " + adapterClassName + 
	     "(G2JavaStubController controller, G2Access context, Item g2Proxy) { ");
    increaseIndent(2);
    iprintln("this.controller = controller;");
    iprintln("this." + g2ProxyVarName + " = g2Proxy;");
    iprintln("this.context = context;");
    decreaseIndent(2);
    iprintln("}");

    // Interface implementation
    emitImplementation();
    iprintln ("");
    decreaseIndent(2);
    iprintln ("}");
  }


  protected void emitImplementation() {
    Vector generatedMethods = new Vector(41);
    for (int i = 0; i<interfacesToImplement.size(); i++) {
      Class interfaceCls = (Class)interfacesToImplement.elementAt(i);
      Method[] methods = interfaceCls.getMethods();
      generatedSymbols = new Vector();
      // Output implementation
      for (int y=0; y<methods.length; y++) {
	Method method = methods[y];
	if (!isMethodConflict(generatedMethods,method)) {
	  iprintln("");
	  generateWrapperMethod(method);
	  generatedMethods.addElement(method);
	}
      }
    }
  }

  private Vector generatedSymbols;

  protected void generateWrapperMethod(Method m) {

    Class[] exceptionTypes = m.getExceptionTypes();
    String name = m.getName();
    Class[] parameterTypes = m.getParameterTypes();
    Class returnType = m.getReturnType();
    // As we may be an interface signature, loose ABSTRACT
    int modifiers = m.getModifiers() &  ~(Modifier.ABSTRACT);

    // Ignore all statics
    if (Modifier.isStatic(modifiers)) {
    	return;
    }

    Symbol g2MethodName = G2ClassTranslator.createG2NameFromJavaName(name);
    String javaG2MethodName = g2MethodName.toString().replace('-','_') + "_";
    if (!generatedSymbols.contains(javaG2MethodName)) {
      iprintln("private static Symbol " + javaG2MethodName + " = Symbol.intern(\"" + g2MethodName + "\");");
      generatedSymbols.addElement(javaG2MethodName);
    }
    iprintln("");
    iprint(Modifier.toString(modifiers));
    print(" " + getJavaTypeString(returnType));
    print(" " + name + " (");

    for (int i=0; i<parameterTypes.length; i++) {
      if (i>0){
    	  print(",");
      }
      print(getJavaTypeString(parameterTypes[i]) + " arg" + i );
    }

    if (exceptionTypes.length >0) {
      println(")");
      for (int i=0; i<exceptionTypes.length; i++) {
	if (i==0){
		iprint(" throws ");
	}
	if (i>0){
		print(",");
	}
	print(exceptionTypes[i].getName() );
      }
      println(" {");
    } else {
      println(") {");
    }               
    increaseIndent(2);
     
    iprintln("try {");
    increaseIndent(2);
    
    // resolve arguments
    for (int i=0; i<parameterTypes.length; i++) {
      if (parameterTypes[i].isPrimitive()) 
	iprintln("Object g2arg" + i + "= " + typeConvTable.get(parameterTypes[i]) + "arg" + i + ");");
      else
	iprintln("Object g2arg" + i + "= arg" + i + ";");
    }

    // The wrapper call
    if (!returnType.getName().equals("void"))
       iprint("Object retval =");
    else
      iprint("");

    emitMethodAdapterCall(m, javaG2MethodName);

    for (int i=0; i<parameterTypes.length; i++) {
      if (i>0) {
    	  print(",");
      }
	print( "g2arg" + i );
    }
    
    println("});");

    if (!returnType.getName().equals("void")) {
      if (!returnType.isPrimitive()) {
	iprintln("return (" + getJavaTypeString(returnType) + ")retval;");
      } else
	iprintln("return " + returnTypeConvTable.get(returnType));
    }
    decreaseIndent(2);
    iprintln("} catch (G2AccessException e) {");
    increaseIndent(2);
    iprintln("throw new RuntimeException(e.toString());");
    decreaseIndent(2);
    iprintln("}");
    decreaseIndent(2);

    iprintln("}");

  }

  protected void emitMethodAdapterCall(Method m, String javaG2MethodName) {
      println("controller." +
	      G2JavaStubController.callG2ProxyFromJava_MethodName + "(");
      iprintln("    context, " + javaG2MethodName + ", new Object[] {" + g2ProxyVarName + ",");
  }


  protected boolean isMethodConflict(Vector otherMethods, Method method) {
    boolean conflict = false;
    Class[] methodParamTypes = method.getParameterTypes();
    String methodName = method.getName();
    for (int i = 0; i<otherMethods.size(); i++) {
      Method otherMethod = (Method)otherMethods.elementAt(i);
      if (methodName.equals(otherMethod.getName())) {
	Class[] otherMethodParamTypes = otherMethod.getParameterTypes();
	if (methodParamTypes.length == otherMethodParamTypes.length) {
	  conflict = true;
	  for (int y = 0; y<methodParamTypes.length; y++) 
	    for (int z = 0; z<otherMethodParamTypes.length; z++) 
	      if (methodParamTypes[y] != otherMethodParamTypes[z])
		conflict = false;
	  if (conflict){
		  return true;
	  }
	}
      }
    }
    return false;
  }

  protected String getJavaTypeString(Class clazz) {
    String returnType = clazz.getName();
    if (returnType.endsWith(";")) {
      returnType=returnType.substring(0, returnType.lastIndexOf(";"));
      // Deal with array cases..e.g. [Ljava.lang.Object;
      while (returnType.startsWith("["))
	  returnType=returnType.substring(1) + "[]";

      if (returnType.startsWith("L"))
	  returnType=returnType.substring(1);
    }

    return returnType;
  }

  protected static Hashtable returnTypeConvTable = new Hashtable(10);
  protected static Hashtable typeConvTable = new Hashtable(10);
  static {
    returnTypeConvTable.put(Integer.TYPE, "(int)((Integer)retval).intValue();");
    returnTypeConvTable.put(Double.TYPE, "(double)((Double)retval).doubleValue();");
    returnTypeConvTable.put(Float.TYPE, "(float)((Float)retval).floatValue();");
    returnTypeConvTable.put(Short.TYPE, "(Short)((Short)retval).shortValue();");
    returnTypeConvTable.put(Long.TYPE, "(long)((Long)retval).longValue();");
    returnTypeConvTable.put(Byte.TYPE, "(byte)((Byte)retval).byteValue();");
    returnTypeConvTable.put(Boolean.TYPE, "(boolean)((Boolean)retval).booleanValue();");
    typeConvTable.put(Integer.TYPE, "new Integer(");
    typeConvTable.put(Double.TYPE, "new Double(");
    typeConvTable.put(Float.TYPE, "new Float(");
    typeConvTable.put(Short.TYPE, "new Short(");
    typeConvTable.put(Long.TYPE, "new Long(");
    typeConvTable.put(Byte.TYPE, "new Byte(");
    typeConvTable.put(Boolean.TYPE, "new Boolean(");
  }

  private int indent = 0;
  private volatile String indentString = "";
  private String SPACES = "                ";

  protected void increaseIndent (int delta) {
    indent += delta;
    indentString = SPACES.substring (0, indent);
  }

  protected void decreaseIndent (int delta) {
    indent -= delta;
    if (indent < 0)
      indent = 0;
    indentString = SPACES.substring (0, indent);
  }

  protected void print (String x) {
    output.print (x);
  }

  protected void println (String x) {
    output.println (x);
  }

  protected void println () {
    output.println ();
  }

  protected void iprint (String x) {
    output.print (indentString);
    output.print (x);
  }

  protected void iprintln (String x) {
    iprint (x);
    output.println ();
  }


  protected void iprintMultiLineString (String x) {
    BufferedReader br = new BufferedReader (new StringReader (x));
    String line;
    try {
      while ((line = br.readLine ()) != null)
	iprintln (line);
    } catch (IOException ioe) {
      // Should never happen
      System.err.println (ioe);
    }
  }

  /**
   * @undocumented
   */
  public static void main(String[] args) {

    // Open Gensym Application properties
    GensymApplication.initialize();

    try {
      Class interfaceClass = Class.forName(args[0]);
      //G2JavaStubInterfaceGenerator generator = new G2JavaStubInterfaceGenerator(interfaceClass);
      //System.out.println(generator.emitInterfaceAdapter());
      //System.out.println(getAdapterClass(new DownLoad(), interfaceClass));
    } catch (Exception e) {
      e.printStackTrace();
      System.out.println(e.toString());
    }
  }

    public void setOutput(PrintWriter out) {
        this.output = out;
    }
}   
