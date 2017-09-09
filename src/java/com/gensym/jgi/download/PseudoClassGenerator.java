package com.gensym.jgi.download;

import java.io.FileOutputStream;
import java.lang.reflect.Method;
import java.util.Hashtable;
import java.util.Vector;

import com.gensym.classtools.*;
import com.gensym.message.Resource;

/**
 * Uses classtools to generate the bytes for "pseudo classes".
 * A "pseudo class" is one that is used during a "thin load" when
 * the G2 class of the item being downloaded includes inheritance from two
 * separate G2 classes, each of which has a downloaded interface.
 * #see com.gensym.jgi.download.StubClassLoader#findAlternateClass
 * <p>
 * The algorithm is as follows:
 * There is class to extend (superClass) and an array of classes
 * to encapsulate (implementationClass[]). The generated class
 * must implement all the interfaces implemented by superClass
 * and implementedClasses[].
 * 1. all the interfaces implemented by superClass are filtered out,
 * as those come for free.
 * 2. for each implementationClass, a delegate is created.
 * 3. For each delegate/implementationClass, all the interfaces
 * implemented by implementationClass, and not by superClass, or by any
 * preceding implementationClass is implemented 
 * in the pseudo class by delegating the call to the delegate.
 */
class PseudoClassGenerator implements RuntimeConstants {
  private static final boolean trace = false;
  private static final Resource i18n =
  Resource.getBundle("com.gensym.jgi.download.Messages");

  PseudoClassGenerator () {}

  /*
   * Create a .class file for the following piece of Java code
   * 
   * public final class GsiDataService____IntegerVariableImpl {
   *	TestRemote o;
   *
   *   public GsiDataService____IntegerVariableImpl() {
   *   }
   *
   */

  private static final int PACKAGE_PREFIX_LENGTH = 19;
  private static final String G2_ACCESS_DESCRIPTOR =
  "Lcom/gensym/jgi/G2Access;";
  private static final String STRUCTURE_DESCRIPTOR = "Lcom/gensym/util/Structure;";

  private String stubClassName;
  private String superClassName;
  private Class superClass;
  private String[] implementationClassNames;
  private Class[] implementationClasses;
  private PseudoClassDelegateInfo[] delegateInfos;
  // a marker
  private Object superDelegateMarker = new Object();
  private ClassOverrides[] overridesArray;
  private Hashtable methodsAlreadyAssigned = new Hashtable();
  // this table has all PseudoClassDelegateInfo's except for
  // the superDelegateMarker
  private Hashtable interfacesProcessed = new Hashtable();

  private FieldRef[] delegateRefs;

  private ClassInfo classInfo;

  public PseudoClassGenerator(String stubClassName,
			      Class superClass,
			      Class[] implementationClasses) {
    this.stubClassName = stubClassName;
    this.superClass = superClass;
    superClassName = superClass.getName();
    this.implementationClasses = implementationClasses;
  }

  private void buildStub () throws ClassException {
    classInfo = createStubClassInfo();
    filterOutInterfacesOfSuperclass();
    initializeDelegates();
    // todo: no-arg constructor can go here. classtools
    // currently makes one automatically.
    // makeNoArgConstructor();
    createConstructor(3);
    createConstructor(5);
    createDelegationMethods();
  }

  private ClassInfo createStubClassInfo()
  throws ClassException {
    String[] interfaceNamesToImplement = getInterfaceNamesToImplement();
    ClassInfo ci =  new ClassInfo(new ClassAccess(ACC_PUBLIC |
						  ACC_SUPER),
				  stubClassName,
				  superClassName,
				  true);
    
    // *** Adding the interfaces ***
    for (int i = 0; i < interfaceNamesToImplement.length; i++)
      ci.add(new InterfaceInfo(interfaceNamesToImplement[i]));

    return ci;	
  }

  private void initializeDelegates() throws ClassException {
    int implementationClassCount = implementationClasses.length;
    // for each implementationClass there is a delegate
    delegateInfos = new PseudoClassDelegateInfo[implementationClassCount];
    delegateRefs = new FieldRef[implementationClassCount];
    for (int i = 0; i < implementationClassCount; i++) {
      PseudoClassDelegateInfo currentInfo =
	new PseudoClassDelegateInfo(classInfo, implementationClasses[i]);
      delegateInfos[i] = currentInfo;
      delegateRefs[i] = addDelegate(currentInfo);
      currentInfo.setFieldRef(delegateRefs[i]);
    }
    assignMethodsToDelegates();
  }

  private static final String G2__BASEIMPL_NAME = "com/gensym/classes/G2__BaseImpl";
  private static final String G2__BASEIMPL_DESCRIPTOR = "L" + G2__BASEIMPL_NAME + ";";

/* Note: The following code allows us to print from the generated method
   (assuming we define the printout method; referencing System.out was too
   difficult.)

      MethodRef printerRef = new MethodRef("com/gensym/classes/G2__BaseImpl",
					   "PrintOut",
					   "(Ljava/lang/String;)V");
      MethodCall printerCall =  new MethodCall(printerRef,new Expression[]
					       { new Value("Calling a printer from within a generated method!")},
					       MTH_CALL_STATIC);
      block.add(printerCall);
*/ 

  // ******** Creating constructor method for N args. *******

  private void createConstructor(int nArgs) throws ClassException {
    String argsDescriptor = null;
    String[] argNames = null;
    Expression[] argsInCall = null;

    Variable g2AccessVar = new Variable("context", G2_ACCESS_DESCRIPTOR);
    Variable handleVar = new Variable("handle", "I");
    Variable handleVersionVar = new Variable("handleVersion", "I");
    Variable wrapVar = new Variable("wrap", G2__BASEIMPL_DESCRIPTOR);
    Variable thisRef = new Variable(0, G2__BASEIMPL_DESCRIPTOR);
    Variable attributeVar = new Variable("attributes", STRUCTURE_DESCRIPTOR);

    switch (nArgs) {
    case 3:
      argsDescriptor = "(" + G2_ACCESS_DESCRIPTOR + "I" + STRUCTURE_DESCRIPTOR + ")V";
      argsInCall = new Expression[] {g2AccessVar, handleVar, attributeVar};
      argNames = new String[] {"context", "handle", "attributes"};
      break;
    case 5:
      argsDescriptor = "(" + G2_ACCESS_DESCRIPTOR + "II" + G2__BASEIMPL_DESCRIPTOR + STRUCTURE_DESCRIPTOR + ")V";
      argsInCall = new Expression[] {g2AccessVar, handleVar, handleVersionVar, wrapVar, attributeVar};
      argNames = new String[] {"context", "handle", "handleVersion", "wrap", "attributes"};
      break;
    default:
    }

    // Call superior constructor
    MethodRef superConstructorRef = new MethodRef(superClassName,
						  "<init>",
						  argsDescriptor);
    
    MethodRef constructorRef = new MethodRef(stubClassName,
					     "<init>",
					     argsDescriptor);

    MethodCall superCall = new MethodCall(superConstructorRef,
					  argsInCall,
					  MTH_CALL_SPECIAL);

    Block block = new Block();				
    // Add statements to the block
    block.add(superCall);

    // Use null in supercall for wrapper arg in 5-arg constructor, but for the
    // delegates we want to send "this" as wrapper by first generating 
    // "wrap = this"

    if (nArgs == 5) {
      OperatorCall wrapperAssignment =
	new OperatorCall("=", new Expression[]
			 {wrapVar, thisRef});
      block.add(wrapperAssignment);					
    }


    // initialize delegates
    for (int i = 0; i < delegateInfos.length; i++) {
      PseudoClassDelegateInfo delegateInfo = delegateInfos[i];
      MethodCall constructorCall =
	delegateInfo.makeConstructorCall(argsDescriptor, argsInCall);
      New newCall = new New(constructorCall);
      OperatorCall operatorCall =
	new OperatorCall("=", new Expression[]
			 {delegateInfo.getFieldRef(),
			    newCall});
      block.add(operatorCall);

      //Don't set wrapper in 5-arg constructor; done by constructor!
      if (nArgs == 3) {
	// todo: convert to a call to setWrapper
	FieldRef wrapperRef = new FieldRef(delegateInfo.getFieldRef(),
					   "wrapper",
					   G2__BASEIMPL_DESCRIPTOR);
	OperatorCall wrapperAssignment =
	  new OperatorCall("=", new Expression[]
			   {wrapperRef, thisRef});
	block.add(wrapperAssignment);					
      }
    }

    block.add(new Return());

    // Add block to MethodInfo
    com.gensym.classtools.MethodInfo methodInfo = new com.gensym.classtools.MethodInfo(new Access(ACC_PUBLIC),
					   constructorRef,
                                           argNames,
					   block);

    // Add the constructor MethodInfo to the class
    classInfo.add(methodInfo);
  }

  private void createDelegationMethods() throws ClassException {
    for (int i = 0; i < delegateInfos.length; i++) {
      delegateInfos[i].createDelegationMethods();
    }
  }

  /** Create a FieldRef to refer to the delegate and return it.
   * While you're at it, add the appropriate fieldInfo to the classInfo
   */
  private FieldRef addDelegate(PseudoClassDelegateInfo delegateInfo)
  throws ClassException {

    FieldRef delegate =  new FieldRef(stubClassName,
				      delegateInfo.getDelegateName(),
				      ClassUtils.descriptorForType(delegateInfo.getClassForDelegate()));

    FieldInfo fi =  new FieldInfo(new Access(ACC_PRIVATE),delegate);
    classInfo.add(fi);
    return delegate;
  }

  // Warning. n-squared algorithm
  private String[] getInterfaceNamesToImplement() {
    Vector interfaceNames = new Vector();
    for (int i = 0; i < implementationClasses.length; i++) {
      Class clazz = implementationClasses[i];
      Class[] currentInterfaces = clazz.getInterfaces();
      for (int j = 0; j < currentInterfaces.length; j++) {
	String interfaceName = currentInterfaces[j].getName();
	if (!interfaceNames.contains(interfaceName))
	  interfaceNames.addElement(interfaceName);
      }
    }

    String[] interfaces = new String[interfaceNames.size()];
    interfaceNames.copyInto(interfaces);
    return interfaces;
  }

  /**
   * Filter out the interfaces that are implemented by the
   * class being extended.
   */
  private void filterOutInterfacesOfSuperclass() {
    Class[] interfaces = superClass.getInterfaces();
    filterOutInterfaces(interfaces);
  }

  private void filterOutInterfaces(Class[] interfaces) {
    for (int i = 0; i < interfaces.length; i++) {
      interfacesProcessed.put(interfaces[i], superDelegateMarker);
      filterOutInterfaces(interfaces[i].getInterfaces());
    }
  }

  private void assignMethodsToDelegates() {
    for (int i = 0; i < delegateInfos.length; i++) {
      PseudoClassDelegateInfo delegate = delegateInfos[i];
      Class clazz = delegate.getClassForDelegate();
      Class[] interfaces = clazz.getInterfaces();
      assignMethodsToDelegate(delegate, interfaces);
    }
  }

  // NOTE: This would throw security exceptions in Netscape, and
  // perhaps elsewhere. Should perhaps revert to using
  // getMethods() and checking the defining class to help find
  // real conflicts.
  /**
   * recursively examine the interfaces. Since interfaces can be
   * a directed acyclic graph, note each interface as it is
   * examined, so that it doesn't get re-examined if it occurs
   * more than one place in the graph.
   */
  private void assignMethodsToDelegate(PseudoClassDelegateInfo delegateInfo,
				       Class[] interfaces) {
    for (int i = 0; i < interfaces.length; i++) {
      Class currentInterface = interfaces[i];
      if (interfacesProcessed.get(currentInterface) == null) {
	Method[] methods = currentInterface.getDeclaredMethods();
	for (int j = 0; j < methods.length; j++) {
	  Method method = methods[j];
	  int modifiers = method.getModifiers();
	  if ((modifiers & ACC_PUBLIC) != 0) {
	    String identifier = ClassUtils.makeMethodIdentifier(method);
	    Method assignedMethod = (Method)methodsAlreadyAssigned.get(identifier);
	    if (assignedMethod != null) {
	      Class assignedMethodClass = assignedMethod.getDeclaringClass();
	      Class newMethodClass = method.getDeclaringClass();
	      if (!newMethodClass.isAssignableFrom(assignedMethodClass)) {
		String message =
		  i18n.format("pcgConflictingMethod",
			      new Object[] {identifier, newMethodClass, assignedMethodClass});
		throw new ClassFileGenerationException(message);
	      } else {
		continue;
	      }
	    }

	    delegateInfo.addMethod(identifier, method);
	    methodsAlreadyAssigned.put(identifier, method);
	  }
	}
	interfacesProcessed.put(currentInterface, delegateInfo);
	assignMethodsToDelegate(delegateInfo, currentInterface.getInterfaces());
      }
    }
  }

  byte[] getClassBytes() throws ClassException {
    buildStub();
    return classInfo.getBytes(true);
  }

  public static void main (String[] args) {	
    try {
      // Create a ClassInfo to hold the class being created.  This class is
      // named  GsiDataService____IntegerVariableImpl, it has no superior classes and it is public and
      // final.
      String stubClassName = "com/gensym/classes/pseudo/GsiDataService____IntegerVariableImpl";
//       String superClassName = "com/gensym/classes/IntegerVariableImpl";
//       Class[] implementations =
// 	new Class[] {com.gensym.classes.GsiDataServiceImpl.class};

       String superClassName = "com/gensym/classes/GsiDataServiceImpl";
       Class[] implementations =
 	new Class[] {com.gensym.classes.IntegerVariableImpl.class};

      PseudoClassGenerator proxy =
	new PseudoClassGenerator(stubClassName,
				 com.gensym.classes.IntegerVariableImpl.class,
				 implementations);
      FileOutputStream fileOutStream = new FileOutputStream(args[0]);
      fileOutStream.write(proxy.getClassBytes());
      fileOutStream.close();
    }
    catch (Exception e) {
      System.out.println("Failure " + e);
      e.printStackTrace();
    }
  }
}



