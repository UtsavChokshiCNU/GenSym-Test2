package com.gensym.beanbuilder;

import java.beans.*;
import java.lang.reflect.*;
import java.nio.charset.Charset;
import java.io.*;
import java.util.Vector;
import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.classes.G2_ItemWrapper;

/**
 * This Class will create a Bean class that wraps a downloaded G2 Item Bean.
 * The Bean is created as a subclass of Component , and therefore can be
 * loaded into bean builders. The wrapping code also takes into
 * account requirements for the ActiveX Bean Bridge...Where listeners
 * will be added/removed even when the G2 Item has not been downloaded.
 *
 *@author M.D.Gribble
 */
public class ItemBeanCreator {

  private String javaClassName;
  private String g2ClassName;
  private String originalJavaClassName;
  private String javaPackageName;
  private Class beanClass;
  private Class clazz;
  private BeanInfo beanInfo;
  private String itemWrapperName = "Bean";
  private Vector ListenerCodeList = new Vector();
  private PrintWriter output;
  private String outputDirectory = "";
  private Method[] superiorMethods;
  private Method []superiorItemMethodsToHide;
  private Vector iconData;
  private int[] iconDataArray;
  private MethodDescriptor[] methods = null;


  public ItemBeanCreator(Class clazz, String outputDirectory, int[] iconData) throws Exception{

    setup(clazz, outputDirectory, iconData);
  }

  public ItemBeanCreator(String className, String outputDirectory, int[] iconData) throws Exception {

    Class beanClassLocal = null;
    Class itemclazz = null;

    try {

      beanClassLocal = Class.forName(className);

    } catch (Exception e) {
      System.out.println(e.toString());
    }

    this.setup(beanClassLocal, outputDirectory, iconData);

  }

  private void setup(Class clazz, String outputDirectory, int[] iconData) throws Exception {

    this.clazz = clazz;
    originalJavaClassName = clazz.getName();

    // This really is a hack, but we dont want implementation bean names
    javaClassName = originalJavaClassName;
    if (originalJavaClassName.endsWith("Impl"))
      javaClassName = originalJavaClassName.substring(0, originalJavaClassName.lastIndexOf("Impl"));

    javaPackageName = javaClassName.substring(0, javaClassName.lastIndexOf("."));
    javaClassName = javaClassName.substring(javaClassName.lastIndexOf(".")+1);
    g2ClassName = G2ClassTranslator.createG2ClassNameFromJavaClassName(javaClassName).toString();

    Class rootclazz = com.gensym.classes.RootImpl.class;

    if (rootclazz.isAssignableFrom(clazz))
      beanInfo = Introspector.getBeanInfo(clazz, rootclazz);
    else if (java.lang.Object.class.isAssignableFrom(clazz))
      beanInfo = Introspector.getBeanInfo(clazz, java.lang.Object.class);
    else
      beanInfo = Introspector.getBeanInfo(clazz);

    this.outputDirectory = (outputDirectory != null ? outputDirectory : "");

    superiorMethods = G2_ItemWrapper.class.getMethods();
    collectSuperiorItemMethodsToHide();

    this.iconDataArray = iconData;
  }

  private void collectSuperiorItemMethodsToHide() {

    superiorItemMethodsToHide = new Method[] {

      getMethod(clazz,"isByHandle", new Class[] {} ),
      getMethod(clazz,"isItemLocal", new Class[] {} ),
      getMethod(clazz,"getRepresentationType", new Class[] {} ),
      getMethod(clazz,"getAttributeDescriptions", new Class[] {com.gensym.util.Sequence.class} ),
      getMethod(clazz,"getAttributeDescriptions", new Class[] {} ),
      getMethod(clazz,"processItemEvent", new Class[] { com.gensym.util.ItemEvent.class} ),
      getMethod(clazz,"updateItemForWorkspaceEvent", new Class[] {com.gensym.util.WorkspaceEvent.class} ),
      getMethod(clazz,"getDefinition", new Class[] {} ),
      getMethod(clazz,"getAttributeDisplayItems", new Class[] {} ),
      getMethod(clazz,"getNameBoxItem", new Class[] {} ),
      getMethod(clazz,"setIconVariables", new Class[] {com.gensym.util.Structure.class} ),
      getMethod(clazz,"getIconVariables", new Class[] {} ),
      getMethod(clazz,"setCurrentAttributeDisplays", new Class[] {com.gensym.util.Sequence.class}),
      getMethod(clazz,"getCurrentAttributeDisplays", new Class[] {} ),
      getMethod(clazz,"setNameBox", new Class[] {com.gensym.util.Structure.class} ),
      getMethod(clazz,"getNameBox", new Class[] {} ),
      getMethod(clazz,"getLayerPosition", new Class[] {} ),
      getMethod(clazz,"setClassSpecificAttributesForClass", new Class[] {com.gensym.util.Sequence.class} ),
      getMethod(clazz,"setDirectSuperiorClassesForClass", new Class[] {com.gensym.util.Sequence.class} ),
      getMethod(clazz,"getInstantiateForClass", new Class[] {} )
    };

  }


  private Method getMethod(Class clazz, String methodName, Class[] argClasses) {
    try {
      return clazz.getMethod(methodName, argClasses );
    } catch (NoSuchMethodException e) {
      System.err.println("Tried to lookup Method, " + methodName + " from Item, but it was not found !");
      return null;
    }
  }



  public static void main(String args[]) {

    if (args.length == 0) {
      System.out.println("usage: [outputdirectory] fully_qualified_class_name");
      System.out.println("example: ../output com.gensym.user.MyClass");
      System.exit(0);
    }

    String className = args[0];
    String outputdirectory = "";

    if (args.length > 1) {
      outputdirectory = args[0];
      className = args[1];
    }

    try {

      int[] icon = getSerializedImage(loadImage(args[2]));

      ItemBeanCreator bc = new ItemBeanCreator(className, outputdirectory, icon);

      bc.generateBean();
      bc.generateBeanInfo();
    } catch (Exception e) {
      e.printStackTrace();
      System.out.println(e.toString());
    }
    System.exit(0);
  }

  public void generateBean () throws Exception {

    System.out.println ("Beanifying " + javaClassName);
    File f = new File (outputDirectory, javaClassName + "Bean.java");
    FileOutputStream fos = new FileOutputStream (f);
    output = new PrintWriter (new OutputStreamWriter(fos, Charset.defaultCharset()), true);
    emitClass ();
    output.close ();
    SourceCompiler.Compile (f.getPath ());
  }

  private void emitClass() {

    System.out.println ("Emitting class for " + javaClassName);

    emitHeader();

    iprintln ("public class " + javaClassName + itemWrapperName + " extends G2_ItemWrapper {");

    iprintln("");
    increaseIndent(2);

    // Fields
    iprintln ("");
    iprintln ("private transient " + originalJavaClassName + " " + itemWrapperName + ";");
    iprintln ("static final long serialVersionUID = -4411892419201111111L;");
    iprintln ("");
    outputIconData();
    iprintln ("");

    emitEventDescriptors(output);
    iprintln ("");
    String fetchCode = "";
    String readObjectSetupCode = "";
    String removeCode = "";
    for (int i=0; i<ListenerCodeList.size(); i++) {
    
      ListenerCode lc = (ListenerCode)ListenerCodeList.elementAt(i);
      iprintln(lc.listenerDec);
      readObjectSetupCode = readObjectSetupCode + "\n" + lc.listenerReadObjectSetupCode;
      fetchCode = fetchCode + "\n" + lc.listenerFetchCode;
      removeCode = removeCode + "\n" + lc.listenerRemoveListenerCode;
    }
    iprintln("");
    iprintln("private void readObject(ObjectInputStream stream) throws IOException, G2AccessException {");
    increaseIndent(2);
    iprintln("try {");
    increaseIndent(2);
    iprintln("stream.defaultReadObject();");
    decreaseIndent(2);
    iprintln("} catch (Exception e) { throw new IOException(e.toString()); }");
    //iprintln("//Reinit Transients");
    //iprintMultiLineString(readObjectSetupCode);
    iprintln("");
    iprintln ("if (itemFetched) fetchG2Item();");
    decreaseIndent(2);
    iprintln("}");
    iprintln("");
    iprintln ("protected void fireItemReceived (Item item) throws G2AccessException{");
    increaseIndent(2);
    //iprintln("try {");
    iprintln (itemWrapperName + "=(" + originalJavaClassName + ")item;");
    increaseIndent(2);
    iprintln ("if (" + itemWrapperName + "!= null) {");
    iprintln("okToCallG2();");
    increaseIndent(2);
    iprintMultiLineString (fetchCode);
    decreaseIndent(2);
    iprintln("}");
    iprintln ("super.fireItemReceived (item);");
    decreaseIndent(2);
    //iprintln("} catch (G2AccessException e) {");
    //opInformException();
    //iprintln("}");
    decreaseIndent(2);
    iprintln ("}");
    iprintln ("");

    iprintln ("protected void fireItemRemoved () throws G2AccessException{");
    increaseIndent(2);
    iprintln("try {");
    increaseIndent(2);
    iprintln ("if (" + itemWrapperName + "!= null) {");
    iprintln("okToCallG2();");
    increaseIndent(2);
    iprintMultiLineString (removeCode);
    iprintln ("}");
    decreaseIndent(2);
    //iprintln("} catch (G2AccessException e) {");
    //opInformException();
    iprintln("} finally {");
    iprintln("super.fireItemRemoved ();");
    iprintln(itemWrapperName + "=null;");
    decreaseIndent(2);
    iprintln("}");
    decreaseIndent(2);
    iprintln ("}");
    iprintln ("");
    
    iprintln ("protected String getPrettyClassName() {");
    increaseIndent(2);
    iprintln ("return \"" + g2ClassName + "\";");
    decreaseIndent(2);
    iprintln ("}");

    iprintln ("protected Class getIntendedClass() {");
    increaseIndent(2);
    iprintln ("return " + originalJavaClassName + ".class;");
    decreaseIndent(2);
    iprintln ("}");

    iprintln ("protected Image readIconImage() {");
    increaseIndent(2);
    iprintln ("return _image;");
    decreaseIndent(2);
    iprintln ("}");

    iprintln ("");
    emitMethodDescriptors();

    decreaseIndent(2);
    iprintln ("}");
    iprintln ("");
  }


  public void generateBeanInfo() throws Exception {


    System.out.println ("Creating beanInfo" + javaClassName );
    File bi = new File (outputDirectory, javaClassName + "BeanBeanInfo.java");
    FileOutputStream bifos = new FileOutputStream (bi);
    output = new PrintWriter (new OutputStreamWriter(bifos, Charset.defaultCharset()), true);

    beanClass = Class.forName (javaPackageName + "." + javaClassName + "Bean");

    emitBeanInfo ();

    output.close ();

    System.out.println ("compiling beanInfo" );
    SourceCompiler.Compile (bi.getPath ());

  }

  private void emitBeanInfo () {

    iprintln ("/**");
    iprintln(" *  Copyright (c) " +"1998 " + G2ClassTranslator.companyName + ".");
    iprintln(" *  All Rights Reserved.");
    iprintln("");
    iprintln (" * Generated Bean Info File");
    iprintln (" * Provides support for " + javaClassName +"Bean");
    iprintln (" * which is a Java Bean  around " + javaClassName);
    iprintln (" * which is a Java analogue of the G2 class of the same name");
    iprintln (" */");
    iprintln ("");
    iprintln ("package " + javaPackageName + ";");
    iprintln ("");
    iprintln ("import java.beans.*;");
    iprintln ("import com.gensym.util.BeanImageBuffer;");
    iprintln ("import java.awt.Image;");
    iprintln ("import com.gensym.message.*;");
    iprintln ("import java.util.Vector;");
    iprintln ("");
    iprintln ("");
    iprintln ("public class " + javaClassName + "BeanBeanInfo extends SimpleBeanInfo");
    iprintln (     "implements java.io.Serializable{");
    iprintln ("");
    increaseIndent(2);
    iprintln ("");
    outputIconData();
    iprintln ("");
    iprintln ("public java.awt.Image getIcon(int iconKind) {");
    iprintln ("");
    increaseIndent(2);
    iprintln ("switch(iconKind) {");
    iprintln ("case BeanInfo.ICON_COLOR_16x16: ");
    increaseIndent(2);
    iprintln ("return _imageBuffer.get16x16icon();");
    decreaseIndent(2);
    iprintln ("case BeanInfo.ICON_COLOR_32x32: ");
    increaseIndent(2);
    iprintln ("return _imageBuffer.get32x32icon();");
    decreaseIndent(2);
    iprintln ("case BeanInfo.ICON_MONO_16x16: ");
    increaseIndent(2);
    iprintln ("return _imageBuffer.get16x16icon();");
    decreaseIndent(2);
    iprintln ("case BeanInfo.ICON_MONO_32x32: ");
    increaseIndent(2);
    iprintln ("return _imageBuffer.get32x32icon();");
    decreaseIndent(2);
    iprintln ("default: ");
    increaseIndent(2);
    iprintln ("return _imageBuffer.get32x32icon();");
    decreaseIndent(2);
    iprintln ("}"); // switch
    iprintln ("");
    decreaseIndent(2);
    iprintln ("}"); // method

    iprintln ("public PropertyDescriptor[] getPropertyDescriptors() {");
    increaseIndent(2);
    iprintln ("Vector pdescriptors = new Vector();");

    iprintln ("try {");
    increaseIndent(2);
    writePropertyDescriptors(clazz.getMethods());
    writePropertyDescriptors(G2_ItemWrapper.class.getMethods()); //will be the beans super class
    decreaseIndent(2);
    iprintln ("} catch (IntrospectionException e) {");
    //iprintln (" e.printStackTrace();");
    iprintln (" Trace.exception(e);");
    iprintln ("}");

    iprintln ("PropertyDescriptor[] pda = new PropertyDescriptor[pdescriptors.size()];");
    iprintln ("for (int i=0; i<pdescriptors.size(); i++) {");
    increaseIndent(2);
    iprintln ("pda[i] = (PropertyDescriptor)pdescriptors.elementAt(i);");
    decreaseIndent(2);
    iprintln ("}");

    iprintln ("return pda;");
    decreaseIndent(2);
    iprintln ("}");

    decreaseIndent(2);
    iprintln ("}"); // class
    }

  private static final Vector allowedPropertyClasses = new Vector(11);
  static {
    allowedPropertyClasses.addElement(String.class);
    allowedPropertyClasses.addElement(java.awt.Color.class);
  }

  private void writePropertyDescriptors(Method[] methods) {
    String propertyName = null;
    for (int i=0; i<methods.length; i++) {
      Method method = methods[i];
      String methodName = method.getName();
      propertyName = null;
      if (methodName.startsWith("get") && methodName.length() > 3) {
	propertyName = Character.toUpperCase(methodName.charAt(3)) + methodName.substring(4);
      } else if (methodName.startsWith("is") && methodName.length() > 2) {
	propertyName = Character.toUpperCase(methodName.charAt(2)) + methodName.substring(3);
      }
      if (propertyName != null) {
	Class propertyType = method.getReturnType();
	if  (allowedPropertyClasses.contains(propertyType) || propertyType.isPrimitive()) {
	  writePropertyDescriptor(propertyName);
	}
      }
    }
  }


  public void writePropertyDescriptor(String propertyName) {
    try {
      if (beanClass != null) {// Really fatal!
	PropertyDescriptor pd = new PropertyDescriptor (propertyName, beanClass);
      }
      iprintln ("pdescriptors.addElement(new PropertyDescriptor(\"" + 
		propertyName + "\"," + javaClassName + "Bean.class));");
    } catch (IntrospectionException ie) {
      Trace.exception (ie, "Not generating Property Descriptor for " + propertyName);
      if (com.gensym.core.GensymApplication.getDevOption())
	iprintln ("/*  Property " + propertyName + " : not generated due to IntrospectionException */");
    }
  }

  private void outputIconData() {
    //System.out.println(iconDataArray);
    iprint ("private static int[] _iconData = new int[] {");
    for (int i=0; i<iconDataArray.length; i++) {
      if (i%8==0){
    	  iprintln("");
      }
      if (i>0){
    	  print(",");
      }
      print(iconDataArray[i] + "");
    }
    iprintln ("};");
    iprintln ("private static BeanImageBuffer _imageBuffer = new BeanImageBuffer(_iconData);");
    iprintln ("private static Image _image = _imageBuffer.get32x32icon();");
  }




  private void emitHeader() {

    iprintln("/*");
    iprintln(" *  Copyright (c) " +"1998 " + G2ClassTranslator.companyName + ".");
    iprintln(" *  All Rights Reserved.");
    iprintln(" *");
    iprintln(" *      " + javaClassName + itemWrapperName + ".java");
    iprintln(" *"); 
    iprintln(" *   Description: Generated Item Wrapper file. Do not edit!");
    iprintln(" *"); 
    iprintln(" *        Author: Gensym Corp.");
    iprintln(" *"); 
    iprintln(" *       Version: 5.1 Rev 0");
    iprintln(" *"); 
    iprintln(" *          Date: " + new java.util.Date ());
    iprintln(" *"); 
    iprintln(" */\n\n");

    iprintln ("package " + javaPackageName + ";");
    iprintln ("");
    iprintln ("import java.awt.*;");
    iprintln ("import java.util.Vector;");
    iprintln ("import java.io.*;");
    iprintln ("import com.gensym.util.*;");
    iprintln ("import com.gensym.classes.*;");
    iprintln ("import com.gensym.jgi.G2AccessException;");
    iprintln ("");
  }


  private void emitEventDescriptors(PrintWriter output) {

    EventSetDescriptor[] eventSets = beanInfo.getEventSetDescriptors();

    for (int i=0; i<eventSets.length; i++) {
      EventSetDescriptor eventSet = eventSets[i];

      //System.out.println("Event ..." +  eventSets[i]);
      //System.out.println(eventSets[i].getAddListenerMethod() + " " + eventSets[i].getAddListenerMethod().hashCode());
      //System.out.println(eventSets[i].getRemoveListenerMethod());

      // The activeX Bean bridge is extremely fussy about non standard interfaces
      // i.e. methods within Listener interfaces that dont contain Parameters that are
      // a subclass of java.util.EventObject;
      if (isStandardListenerInterface(eventSet.getListenerType()) &&
	   !isMethodConflict(eventSet.getAddListenerMethod()) &&
	   !isMethodConflict(eventSet.getRemoveListenerMethod())) {

	// As the bean may not be loaded, we keep local copies of Listeners
	ListenerCode lc = new ListenerCode(eventSets[i].getListenerType());
	ListenerCodeList.addElement(lc);

	generateWrapperMethod(eventSet.getAddListenerMethod(), null, lc.listenerAddCode);
	generateWrapperMethod(eventSet.getRemoveListenerMethod(), null, lc.listenerRemoveCode);

      } else {
	System.out.println("Can not add Listener Interface " + eventSets[i].getListenerType().getName() +
			   " as it contains Method parameters that are not subclasses of java.util.EventObject");
      }
    }

  }

  class ListenerCode {
    String listenerDec;
    String listenerReadObjectSetupCode;
    String listenerAddCode;
    String listenerRemoveCode;
    String listenerFetchCode;
    String listenerRemoveListenerCode;

    ListenerCode(Class listenerClass) {

      String listenerClassName = listenerClass.getName();
      listenerClassName = listenerClassName.substring(listenerClassName.lastIndexOf(".")+1);
      String listenerVectorName = listenerClassName + "_Vector";
      listenerDec = "Vector " + listenerVectorName + "= new Vector(5);";
      listenerReadObjectSetupCode = listenerVectorName + "= new Vector(5);";
      listenerAddCode =    "okToCallG2(); \n" + listenerVectorName + ".addElement(arg0);";
      listenerRemoveCode = "okToCallG2(); \n" +listenerVectorName + ".removeElement(arg0);";
      listenerFetchCode =
        "for (int i=0; i<" + listenerVectorName + ".size(); i++) \n" +
	"    " + itemWrapperName+".add"+ listenerClassName +
	"((" + listenerClass.getName() + ")" +
	listenerVectorName + ".elementAt(i));\n";
	//listenerVectorName + ".removeAllElements();";
      listenerRemoveListenerCode =   
	"for (int i=0; i<" + listenerVectorName + ".size(); i++) \n" +
	"    " + itemWrapperName + ".remove"+ listenerClassName +
	"((" + listenerClass.getName() + ")" +
	listenerVectorName + ".elementAt(i));\n";
	
    }


  }

  private void emitMethodDescriptors() {

    MethodDescriptor[] beanMethods = beanInfo.getMethodDescriptors();

    for (int i=0; i<beanMethods.length; i++) {

      Method method = beanMethods[i].getMethod();
      if (!isMethodConflict(method)) {
	String name = method.getName();

	// Dont generate any Listener methods, done else where
	// Cant simply check for already sent event methods
	// as there may be other add/remove Listener interfaces
	// that are not true Listener interafaces and thus will cause problems
	// with bean builders and ActiveX

	if (!(name.endsWith("Listener") && (name.startsWith("add") || name.startsWith("remove")))) {
	  iprintln("");
	  generateWrapperMethod(method, "throw new ItemNotAvailableException(itemNotAvailableString);", null);
	}
      }
    }
  }


  private void generateWrapperMethod(Method m, String wrapperNullCode, String wrapperPreCode) {

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

    iprint(Modifier.toString(modifiers));
    print(" " + getJavaTypeString(returnType));
    print(" " + name + " (");

    for (int i=0; i<parameterTypes.length; i++) {
      if (i>0){
    	  print(",");
      }
      print(getJavaTypeString(parameterTypes[i]) + " arg" + i );
    }

    println(")");

    boolean callsG2 = false;
    for (int i=0; i<exceptionTypes.length; i++) {
      if (i==0) {
    	  iprint(" throws ");
      }
      if (i>0) {
    	  print(",");
      }
      print(exceptionTypes[i].getName() );
      if (exceptionTypes[i] == com.gensym.jgi.G2AccessException.class)
	callsG2 = true;
    }

    println("{");
    increaseIndent(2);
    
    iprintln ("checkItem (" + itemWrapperName + ");");
    iprintln("try {");
    increaseIndent(2);

    if (wrapperPreCode != null) 
      iprintln(wrapperPreCode);

    // The wrapper call
    if (!returnType.getName().equals("void"))
       iprint("return ");
    else
      iprint("");

    print(itemWrapperName + "." + name + "(");

    for (int i=0; i<parameterTypes.length; i++) {
      if (i>0){
    	  print(",");
      }
      print( "arg" + i );
    }

    println(");");
    decreaseIndent(2);

    String informMess = null;
    for (int i=0; i<exceptionTypes.length; i++) {
      iprintln("} catch (" + exceptionTypes[i].getName() + " e) {" );
      opInformException(informMess);
    }

    /* I'd like to take this next catch out but it reduces the amount
       of tracing we have -- vkp */
    iprintln ("} catch (RuntimeException re) {");
    iprintln ("  informUser (\"Unexpected exception calling " + name + " : \", re);");
    iprintln ("  throw re;");
    
    iprintln("}");
    decreaseIndent(2);
    
    iprintln("}");

  }

  private void opInformException(String mess) {
    increaseIndent(2);
    if (mess == null)
      iprintln("informUser(null,e);");
    else
      iprintln("informUser(" + "\"" + mess + "\",e);");
    iprintln("throw e;");
    decreaseIndent(2);
  }

  private String getJavaTypeString(Class clazz) {
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

  private boolean isMethodConflict(Method method) {
    if (isMethodConflict(method, superiorMethods))
      return true;
    if (isMethodConflict(method, superiorItemMethodsToHide))
      return true;
    return false;
  }

  private boolean isMethodConflict(Method method, Method []superiorMethods) {
    for (int i=0; i<superiorMethods.length; i++) {
      Method sMethod = superiorMethods[i];
      if (sMethod != null) {
	if (method.getName().equals(sMethod.getName())) {

	  // return types must be the same
	  if (method.getReturnType() != sMethod.getReturnType())
	    return true;

	  // number args different
	  Class[] argTypes = method.getParameterTypes();
	  Class[] sArgTypes = sMethod.getParameterTypes();

	  // Wimp out should check types modifiers and exceptions here
	  // same number of args...not allowed
	  if (argTypes.length == sArgTypes.length)
	    return true;
	}
      }
    }
    return false;
  }

  /**
   * return false  for any Methods within Listener interface that dont contain Parameters that are
   * a subclass of java.util.EventObject
   */
  private boolean isStandardListenerInterface(Class listenerClass) {
    Method[] listenerMethods = listenerClass.getMethods();

    for (int i=0; i<listenerMethods.length; i++) {

      Class[] params = listenerMethods[i].getParameterTypes();

      if (params.length != 1) {
    	  return false;
      }

      for (int y=0; y<params.length; y++) {
	if (!java.util.EventObject.class.isAssignableFrom(params[y]))
	  return false;
      }
    }
    return true;
  }


  private int indent = 0;
  private volatile String indentString = "";
  private String SPACES = "                ";

  synchronized void increaseIndent (int delta) {
    indent += delta;
    indentString = SPACES.substring (0, indent);
  }

  synchronized void decreaseIndent (int delta) {
    indent -= delta;
    if (indent < 0)
      indent = 0;
    indentString = SPACES.substring (0, indent);
  }

  void print (String x) {
    output.print (x);
  }

  void println (String x) {
    output.println (x);
  }

  void println () {
    output.println ();
  }

  void iprint (String x) {
    output.print (indentString);
    output.print (x);
  }

  void iprintln (String x) {
    iprint (x);
    output.println ();
  }


  void iprintMultiLineString (String x) {
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

  private static java.awt.Image loadImage(String resourceName) {

    try {

      java.net.URL url = ItemBeanCreator.class.getResource(resourceName);
      java.awt.Toolkit tk = java.awt.Toolkit.getDefaultToolkit();
      return tk.createImage((java.awt.image.ImageProducer) url.getContent());
    } catch (Exception e) {
      e.printStackTrace();
      System.out.println(e.toString());
      return null;
    }
  }

  private static int[] getSerializedImage(java.awt.Image image) {
    BeanImageBuffer imageBuffer = new BeanImageBuffer();

    System.out.println(image);
    int[] data = imageBuffer.serializeImage(image, new java.awt.Button());
    return data;
  }

}
