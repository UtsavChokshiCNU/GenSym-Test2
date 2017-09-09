/*
 * @(#)WrapperclassGenerator.java	1.0 97/10/22
 * 
 * Copyright (c) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 
 */


package com.gensym.devtools;

import java.lang.reflect.*;
import java.io.PrintStream;

import com.gensym.core.CmdLineArgHandler;

/** Generates a wrapperclass of the given class by adding additional code
 * before the call to <code>super</code> in each method. This class was created
 * to automatically generate a wrapperclass of com.gensym.ntw.rmi.TwRMIClientImpl
 * that will call the netscape.security.PrivilegeManager before each RMI call.
 */
public class WrapperclassGenerator {

  public static final int DEFAULT_INDENT_DELTA = 2;
  
  PrintStream out;
  Class wrappedClass;
  String wrapperclassName;
  String superclassName;
  protected int indentDelta = DEFAULT_INDENT_DELTA;

  public WrapperclassGenerator() {
    this(System.out);
  }

  public WrapperclassGenerator(PrintStream out) {
    this.out = out;
  }

  public void generateWrapperclass(String packageName,
				   String wrapperclassName,
				   String superclassName,
				   Class wrappedClass) {
    this.wrappedClass = wrappedClass;
    this.wrapperclassName = wrapperclassName;
    this.superclassName = superclassName;
    
    generatePackageDeclaration(packageName);
    out.println();
    generateImports();
    out.println();
    generateClassDeclaration();
    increaseIndent(indentDelta);
    generateVariables();
    out.println();
    generateConstructors();
    out.println();
    generateMethods();
    out.println("}");
  }

  public void generateImports() {
    printImports(getImports());
  }

  public void printImports(String[] imports) {
    if (imports == null)
      return;
    int len = imports.length;
    for (int i = 0; i < len; i++) {
      iprint("import ");
      iprint(imports[i]);
      iprintln(";");
    }
  }

  public String[] getImports() {
    return null;
  }

  public void generatePackageDeclaration(String packageName) {
    out.print("package ");
    out.print(packageName);
    out.println(";");
  }

  public void generateClassDeclaration() {
    out.print("public class ");
    out.print(wrapperclassName);
    out.print(" extends ");
    out.print(superclassName);
    out.println("{");
  }

  /**
   */
  public void generateVariables() {
    String wrappedName = wrappedClass.getName();
    increaseIndent(indentDelta);
    out.print("private " + wrappedName + " wrapped " +
	      "= new " + wrappedName + "();");
  }

  /** NOTE for PrivilegeManager calling:
   * If the constructor calls a private method that requires the Privilege
   * manager, then this generated class will still have problems with
   * Netscape security.
   */
  public void generateConstructors() {
    Constructor[] constructors = wrappedClass.getDeclaredConstructors();
    int length = constructors.length;

    for (int i = 0; i < length; i++) {
      Constructor constructor = constructors[i];
      int mods = constructor.getModifiers();
      if(Modifier.isFinal(mods)) {
	continue;
      }
      
      if(Modifier.isProtected(mods)) {
	iprint("protected ");
      } else if (Modifier.isPublic(mods)) {
	iprint("public ");
      } else {
	// fix this: may want to allow for package-private
	continue;
      }

      out.print(wrapperclassName);
      printArgs(constructor);
      printThrows(constructor);
      out.println("{");
      increaseIndent(indentDelta);
      printConstructorBody(constructor);
      decreaseIndent(indentDelta);
      iprintln("}");
      out.println();
    }
  }

  protected void printArgs(Constructor constructor) {
    out.print("(");
    
    Class[] args = constructor.getParameterTypes();
    int len = args.length;

    for (int i = 0; i < len; i++) {
      Class clazz = args[i];
      out.print(clazz.getName());
      if (clazz.isArray()) {
	out.print("[]");
      }

      out.print(" ");
      printArgName(clazz, i);
      if (i < len -1)
	out.print(", ");
    }
    out.print(")");
  }

  public void printArgName(Class clazz, int argPos) {
    if (clazz.isArray())
      clazz = clazz.getComponentType();
    
    String name = clazz.getName();
    int separatorPos = name.lastIndexOf('.');
    // NOTE: this also works when charAt() returns -1.
    out.print(Character.toLowerCase(name.charAt(separatorPos + 1)));
    out.print(name.substring(separatorPos + 2));
    out.print(argPos);
  }

  protected void printThrows(Constructor constructor) {
    Class[] exceptions = constructor.getExceptionTypes();

    printThrowsAux(exceptions);
  }

  public void printThrowsAux(Class[] exceptions) {
    if (exceptions.length == 0)
      return;
    
    out.println();
    iprint("throws ");
    int len = exceptions.length;

    for (int i = 0; i < len; i++) {
      out.print(exceptions[i].getName());
      if (i < len - 1)
	out.print(", ");
    }
  }

  /** This method should be overridden, not hidden.
   */
  protected void printConstructorBody(Constructor constructor) {
    out.print("wrapped " +
		"= new " + wrappedClass.getName());
    Class[] args = constructor.getParameterTypes();
    printCallParameters(args);
    out.println( ";");
  }

  public boolean isVoid(Class clazz) {
    return (java.lang.Void.TYPE.equals(clazz));
  }

  public boolean doGenerateOverride(Method method) {
    return true;
  }

  /** NOTE for PrivilegeManager calling:
   * If the method calls a private method that requires the Privilege
   * manager, then this generated class will still have problems with
   * Netscape security.
   */
  public void generateMethods() {
    Method[] methods = wrappedClass.getDeclaredMethods();
    int length = methods.length;

    for (int i = 0; i < length; i++) {
      if (!doGenerateOverride(methods[i]))
	continue;
      
      Method method = methods[i];
      int mods = method.getModifiers();
      if(Modifier.isFinal(mods)) {
	continue;
      }
      if(Modifier.isStatic(mods))
	 continue;
      
      if(Modifier.isProtected(mods)) {
	iprint("protected ");
      } else if (Modifier.isPublic(mods)) {
	iprint("public ");
      } else {
	// fix this: may want to allow for package-private
	continue;
      }

      Class returnType = method.getReturnType();
      
      out.print(returnType.getName());
      out.print(" ");

      out.print(method.getName());
      printArgs(method);
      printThrows(method);
      out.println("{");
      increaseIndent(indentDelta);
      printMethodBody(method, returnType);
      decreaseIndent(indentDelta);
      iprintln("}");
      out.println();
    }
  }

  protected void printArgs(Method method) {
    out.print("(");
    
    Class[] args = method.getParameterTypes();
    int len = args.length;

    for (int i = 0; i < len; i++) {
      Class clazz = args[i];
      boolean isArray = clazz.isArray();
      if(isArray) {
	clazz = clazz.getComponentType();
      }
      out.print(clazz.getName());
      if (isArray) {
	out.print("[]");
      }

      out.print(" ");
      printArgName(clazz, i);
      if (i < len -1)
	out.print(", ");
    }
    out.print(")");
  }

  public void printThrows(Method method) {
    Class[] exceptions = method.getExceptionTypes();

    printThrowsAux(exceptions);
  }

  /** This method will typically be hidden, rather than overridden.
   */
  public void printMethodBody(Method method, Class returnType) {
    String varName = getVarName(method, returnType);
    declareResultVar(method, returnType, varName, true);
    setWrappedResult(method, returnType, varName);
    returnWrappedResult(returnType, varName);
  }

  public String getVarName(Method method, Class returnType) {
    return "returnVar";
  }

  public void declareResultVar(Method method, Class returnType, String varName,
			       boolean initializeToDefault) {
    if (!isVoid(returnType)) {
      iprint(returnType.getName());
      out.print(" ");
      out.print(varName);
      if (initializeToDefault) {
	out.print(" = ");
	printInitializationDefault(method, returnType);
      }
      out.println(";");
    }
  }

  public void printInitializationDefault(Method method, Class returnType) {
    if (isVoid(returnType))
      return;

    if(!returnType.isPrimitive()) {
      out.print("null");
    } else if (Boolean.TYPE.isAssignableFrom(returnType)) {
      out.print("false");
    } else {
      out.print("(");
      out.print(returnType.getName());
      out.print(")");
      out.print(0);
    }
  }

  public void setWrappedResult(Method method, Class returnType, String varName) {
    if (!isVoid(returnType)) {
      iprint(varName);
      out.print(" = ");
      out.print("wrapped.");
    } else {
      iprint("wrapped.");
    }
    out.print(method.getName());
    Class[] args = method.getParameterTypes();
    printCallParameters(args);
    out.println(";");
  }

  public void returnWrappedResult(Class returnType, String varName) {
    iprint("return");
    if (!isVoid(returnType)) {
      out.print(" ");
      out.print(varName);
    }
    out.println(";");
  }

  public void printCallParameters(Class[] args) {
    out.print("(");
    
    int len = args.length;

    for (int i = 0; i < len; i++) {
      Class clazz = args[i];
      printArgName(clazz, i);
      if (i < len - 1)
	out.print(", ");
    }
    out.print(")");
  }

  //
  // stolen from com.gensym.util.ClassGenerationContext
  //

  private int indent = 0;
  private String indentString = "";
  private String SPACES = "                ";

  protected synchronized void increaseIndent (int delta) {
    indent += delta;
    indentString = SPACES.substring (0, indent);
  }

  protected synchronized void decreaseIndent (int delta) {
    indent -= delta;
    if (indent < 0)
      indent = 0;
    indentString = SPACES.substring (0, indent);
  }

  protected void iprint (String x) {
    out.print (indentString);
    out.print (x);
  }

  protected void iprintln (String x) {
    iprint (x);
    out.println ();
  }

  public static void main(String[] args) {
    CmdLineArgHandler cmdLine = new CmdLineArgHandler (args);

    String packageName = cmdLine.getOptionValue("-packageName");
    String wrapperclassName = cmdLine.getOptionValue("-wrapperclassName");
    String wrappedclassName = cmdLine.getOptionValue("-wrappedclassName");
    String superclassName = cmdLine.getOptionValue("-superclassName");
    WrapperclassGenerator gen =
      new WrapperclassGenerator(System.out);
    try {
      gen.generateWrapperclass(packageName,
			       wrapperclassName,
			       superclassName,
			       Class.forName(wrappedclassName));
    } catch (Exception ex) {
      System.out.println(ex.getMessage());
      ex.printStackTrace();
    }
  }
}
