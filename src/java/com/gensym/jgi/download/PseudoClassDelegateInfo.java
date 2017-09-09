package com.gensym.jgi.download;

//import java.io.*;
import java.lang.reflect.Method;
import java.util.Hashtable;
import java.util.Vector;

import com.gensym.classtools.*;

class PseudoClassDelegateInfo implements RuntimeConstants {

  Class clazz;
  String delegateName;
  String interfaceName;
  String interfaceShortName;
  String stubClassName;
  Vector methodsToImplement = new Vector();

  ClassInfo classInfo;
  FieldRef fieldRef;

  PseudoClassDelegateInfo(ClassInfo classInfo, Class clazz) {
    this.clazz = clazz;
    this.classInfo = classInfo;
    initialize();
  }

  Class getClassForDelegate() {
    return clazz;
  }

  // remove package qualification.
  private static String getShortName (String className) {
    int startOfClassName = className.lastIndexOf(SIGC_PACKAGE);
    if (startOfClassName == -1)
      startOfClassName = className.lastIndexOf(SIGC_ALT_PACKAGE);
    if (startOfClassName == -1)
      startOfClassName = 0;

    return className.substring(startOfClassName + 1,
			       className.length());
  }

  private void initialize() {
    stubClassName = clazz.getName();
    String stubClassShortName = getShortName(stubClassName);
    // "mv" stands for "member variable"
    delegateName = "mv" + stubClassShortName;
  }

  void setFieldRef(FieldRef fieldRef) {
    this.fieldRef = fieldRef;
  }

  FieldRef getFieldRef() {
    return fieldRef;
  }

  String getDelegateName() {
    return delegateName;
  }

  String getInterfaceName() {
    return interfaceName;
  }

  MethodCall makeConstructorCall (String argsDescriptor, Expression[] args)
  throws ClassException {
    MethodRef constructorRef = new MethodRef(stubClassName,
					    "<init>",
					    argsDescriptor);
    return new MethodCall(constructorRef, args, MTH_CALL_SPECIAL);
  }

  void addMethod(String identifier, Method method) {
    methodsToImplement.addElement(method);
  }

//   MethodRef[] getMethodRefs() throws ClassException {
//     int length = methodsToImplement.size();
//     MethodRef[] refs = new MethodRef[length];
//     for (int i = 0; i < length; i++)
//       refs[i] = ClassUtils.
//     return refs;
//   }

  void createDelegationMethods() throws ClassException {
    int size = methodsToImplement.size();
    for (int i = 0; i < size; i++) {
      Method method = (Method)methodsToImplement.elementAt(i);
      Class[] args = method.getParameterTypes();
      Class returnType = method.getReturnType();
      String fullDescriptor = ClassUtils.makeArgsDescriptor(method) +
	ClassUtils.descriptorForType(returnType);
      String methodName = method.getName();
      //System.out.println("pcdi methodName=" + methodName);
      MethodRef refForCall =
	new MethodRef(ClassUtils.normalizeClassName(clazz.getName()),
		      methodName,
		      fullDescriptor);
      Expression[] vars = generateVariables(args);
      // do this before destructively modified by MethodCall constructor
      String[] variableNames = new String[vars.length];
      for (int j = 0; j < vars.length; j++) {
	variableNames[j] = ((Variable)vars[j]).getVariableName();
      }
      
      //System.out.println("pcdi fullDescriptor=" + fullDescriptor);
      //System.out.println(com.gensym.core.DebugUtil.printArray(vars));
      MethodCall callToDelegate =
	new MethodCall(fieldRef,
		       refForCall,
		       vars,
		       MTH_CALL_VIRTUAL);

      Block block = new Block();

      if(Void.TYPE.equals(returnType)) {
	block.add(callToDelegate);
	block.add(new Return());
      } else {
	block.add(new Return(callToDelegate));
      }
      
      
      MethodRef refForInfo = new MethodRef(stubClassName,
					   methodName,
					   fullDescriptor);

      com.gensym.classtools.MethodInfo methodInfo =
	new com.gensym.classtools.MethodInfo(new Access(ACC_PUBLIC),
					     refForInfo,
					     block,
					     variableNames,
					     ClassUtils.getExceptionClassRefs(method));
      classInfo.add(methodInfo);
    }
  }

  private Expression[] generateVariables(Class[] args) throws ClassException{
    Expression[] vars = new Expression[args.length];
    for (int i = 0; i < vars.length; i++) {
      vars[i] = new Variable("arg" + i, ClassUtils.descriptorForType(args[i]));
    }
    return vars;
  }
}

