package com.gensym.classtools;

import java.lang.reflect.Method;
import java.util.Hashtable;

/**
 * Utilities, typically conversion utilities to simplify the use
 * of classtools classes.
 */

public class ClassUtils implements RuntimeConstants{

  /**
   * convert a type into a descriptor string. <p>
   * E.g.: descriptorForType((new Object[1]{new Object()}).getClass()) => "[Ljava/lang/Object;"
   * @param the type to be converted
   * @returns a valid descriptor for the type.
   */
  public static String descriptorForType(Class type) {
    if (type.isArray())
      return(SIG_ARRAY + descriptorForType(type.getComponentType()));
    if (type == Integer.TYPE)
      return SIG_INT;
    else if (type == Long.TYPE)
      return SIG_LONG;
    else if (type == Byte.TYPE)
      return SIG_BYTE;
    else if (type == Character.TYPE)
      return SIG_CHAR;
    else if (type == Short.TYPE)
      return SIG_SHORT;
    else if (type == Float.TYPE)
      return SIG_FLOAT;
    else if (type == Double.TYPE)
      return SIG_DOUBLE;
    else if (type == Boolean.TYPE)
      return SIG_BOOLEAN;
    else if (type == Void.TYPE)
      return SIG_VOID;
    else
      return
	SIG_CLASS +
	normalizeClassName(type.getName()) +
	SIG_END_CLASS;
  }

  /**
   * @undocumented
   */
  public static String normalizeClassName(String className) {
    return className.replace(SIGC_ALT_PACKAGE, SIGC_PACKAGE);
  }

  private static final Hashtable primitives = new Hashtable();
  static {
    primitives.put("boolean", SIG_BOOLEAN);
    primitives.put("byte", SIG_BYTE);
    primitives.put("short", SIG_SHORT);
    primitives.put("int", SIG_INT);
    primitives.put("char", SIG_CHAR);
    primitives.put("long", SIG_LONG);
    primitives.put("float", SIG_FLOAT);
    primitives.put("double", SIG_DOUBLE);
  }

  /**
   * Converts a type declaration into a descriptor. If the type
   * is the name of a class, it must be class qualified to work.
   * Does not deal with arrays.
   * @undocumented because it is not "clean"
   */
  public static String descriptorForTypeDeclaration (String declaration) {
    String primitive = (String)primitives.get(declaration);

    if (primitive != null)
      return primitive;
    else
      return
	SIG_CLASS +
	declaration.replace(SIGC_ALT_PACKAGE, SIGC_PACKAGE) +
	SIG_END_CLASS;
  }  

  /**
   * Creates a string with method-name + arg descriptor as the key
   * that uniquely identifies a method within a single class (i.e.,
   * no two methods can have the same identifier in a single class
   * and still make a valid class.
   * @undocumented
   */
  public static String makeMethodIdentifier(Method method) {
    return method.getName() + makeArgsDescriptor(method);
  }

  /**
   * Returns the type descriptor for the arguments of <code>method</code>.
   * This does not include the return type.
   */
  public static String makeArgsDescriptor(Method method) {
    StringBuffer buf = new StringBuffer(SIG_METHOD);
    Class[] argTypes = method.getParameterTypes();

    for (int i = 0; i < argTypes.length; i++) {
      buf.append(descriptorForType(argTypes[i]));
    }

    buf.append(SIG_ENDMETHOD);

    return buf.toString();
  }

  

  public static MethodRef makeMethodRef(Method method) throws ClassException {
    String descriptor =
      makeArgsDescriptor(method) + descriptorForType(method.getReturnType());
    return new MethodRef(method.getDeclaringClass().getName(),
			 method.getName(),
			 descriptor);
  }

  // todo: this doesn't make as much sense here, since the variableName
  // have to be consistent with the block.
  public static MethodInfo makeMethodInfo(Method method, MethodRef ref, String[] variableNames,
				   Block block) throws ClassException {

    return new MethodInfo(new Access(method.getModifiers()),
			  ref,
			  block,
			  variableNames,
			  getExceptionClassRefs(method));
  }

  public static ClassRef[] getExceptionClassRefs(Method method) throws ClassException {
    Class[] exceptions = method.getExceptionTypes();
    int length = exceptions.length;
    ClassRef[] exceptionRefs = new ClassRef[length];

    for (int i = 0; i < length; i++)
      exceptionRefs[i] = new ClassRef(exceptions[i].getName());

    return exceptionRefs;
  }

  public static void main(String[] args) {
    System.out.println(descriptorForType((new Object[]{new Object()}).getClass()));
  }
}
