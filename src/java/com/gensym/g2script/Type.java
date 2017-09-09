package com.gensym.g2script;

import java.lang.reflect.*;
import java.util.Vector;
import java.util.Stack;
import java.util.Enumeration;
import com.gensym.classtools.ClassInfo;
import com.gensym.classtools.InterfaceInfo;

public class Type
{
  Class clazz = null; // if filled means compilation was available
  ClassInfo uncompiledClass = null; // filled otherwise
  Compiler compiler;

  Type(Compiler compiler, Class clazz)
  {
    this.compiler = compiler;
    compiler.knownTypes.put(clazz.getName(),this);
    this.clazz = clazz;
  }

  Type(Compiler compiler, ClassInfo uncompiledClass)
  {
    this.compiler = compiler;
    compiler.knownTypes.put(uncompiledClass.getClassName(),this);
    this.uncompiledClass = uncompiledClass;
  }

  Type()
  {
    // exists only for package-private ArrayType constructor
  }

  @Override
  public String toString() 
  {
    return (isInterface() ? "interface " : (isPrimitive() ? "" : "class "))
            + getName();
  } 

  static Type ensureUncompiledClassIsType(Compiler compiler, ClassInfo uncompiledClass)
  {
    Type type = forName(compiler, uncompiledClass.getClassName());
    if (type == null)
      {
	return new Type(compiler, uncompiledClass);
      }
    else 
      return type;
  }

  public static Type forName(Compiler compiler, String className)
       
  {
    Type type =  (Type) compiler.knownTypes.get(className);
    if (type != null)
      return type;
    else if (compiler.classInfoFactory != null)
      {
	Class newClass = null;
	ClassInfoFactory factory = compiler.classInfoFactory;
	try {
	  newClass = factory.getClassForName(className);
	} catch (ClassNotFoundException cnfe)
	  {
	    // do nothing
	  }
	
	if (newClass != null)
	  {
	    Type newType = new Type(compiler,newClass);
	    compiler.knownTypes.put(className,newType);
	    return newType;
	  }
	else 
	  {
	    ClassInfo classInfo = factory.generateClassInfo(className);
	    if (classInfo != null)
	      return ensureUncompiledClassIsType(compiler,classInfo);
	    else 
	      return null;
	  }
      }
    else
      {
	Class newClass = null;
	try {
	  newClass = Class.forName(className);
	} catch (ClassNotFoundException e)
	  {}
	if (newClass != null)
	  {
	    Type newType = new Type(compiler,newClass);
	    compiler.knownTypes.put(className, newType);
	    return newType;
	  }
	else
	  return null;
      }
  }

  static Type forClass(Compiler compiler, Class clazz)
  {
    if (clazz.isPrimitive())
      {
	String name = null;
	if (clazz == Integer.TYPE)
	  name = "int";
	else if (clazz == Long.TYPE)
	  name = "long";
	else if (clazz == Byte.TYPE)
	  name = "byte";
	else if (clazz == Character.TYPE)
	  name = "char";
	else if (clazz == Short.TYPE)
	  name = "short";
	else if (clazz == Float.TYPE)
	  name = "float";
	else if (clazz == Double.TYPE)
	  name =  "double";
	else if (clazz == Boolean.TYPE)
	  name = "boolean";
	else if (clazz == Void.TYPE)
	  name = "void";
	return Type.forName(compiler,name);
      }
    else
      return Type.forName(compiler,clazz.getName());
  }

  static Type forDescriptor(Compiler compiler, String string)
  {
    char[] chars = string.toCharArray();
    int i, len = chars.length;
    char ch;
    String typeName;
    StringBuffer buffer = null;
    boolean inClassName = false;
    for (i=0, ch = chars[0] ; i<len ; i++, ch = chars[i])
      if (inClassName)
	{
	  if (buffer == null)
	    buffer = new StringBuffer();
	  if (ch == '/')
	    buffer.append('.');
	  else if (ch == ';')
	    {
	      if (i == len - 1)
		return forName(compiler, buffer.toString());
	      else
		throw new IllegalArgumentException("bad descriptor "+string);
	    }
	  else
	    buffer.append(ch);
	}
      else
	switch (ch)
	  {
	  case 'B': 
	    return typeForPrimitiveDescriptor(compiler,"byte",i,len,string);
	  case 'C':
	    return typeForPrimitiveDescriptor(compiler,"char",i,len,string);
	  case 'S':
	    return typeForPrimitiveDescriptor(compiler,"short",i,len,string);
	  case 'I':
	    return typeForPrimitiveDescriptor(compiler,"int",i,len,string);
	  case 'J':
	    return typeForPrimitiveDescriptor(compiler,"long",i,len,string);
	  case 'D':
	    return typeForPrimitiveDescriptor(compiler,"double",i,len,string);
	  case 'F':
	    return typeForPrimitiveDescriptor(compiler,"float",i,len,string);
	  case 'Z':
	    return typeForPrimitiveDescriptor(compiler,"boolean",i,len,string);
	  case 'V':
	    return typeForPrimitiveDescriptor(compiler,"void",i,len,string);
	  case 'L':
	    inClassName = true;
	    break;
	  case '[':
	    throw new RuntimeException("array descriptors NYI");
	  default:
	  }
    throw new IllegalArgumentException("bad descriptor "+string);
  }

  private static Type typeForPrimitiveDescriptor(Compiler compiler,
						 String typeName, int index, int length,
						 String descriptor)
  {
    if (index == length - 1)
      return Type.forName(compiler,typeName);
    else
      throw new IllegalArgumentException("bad descriptor "+descriptor);
  }

  String makeDescriptor()
  {
    if (this instanceof ArrayType)
      throw new RuntimeException("arrays NYI");
    else if (clazz == null)
      // throw new RuntimeException("uncompiled classes NYI");
      return "L"+uncompiledClass.getClassName().replace('.','/')+";";
    else if (clazz == Integer.TYPE)
      return "I";
    else if (clazz == Long.TYPE)
      return "J";
    else if (clazz == Byte.TYPE)
      return "B";
    else if (clazz == Character.TYPE)
      return "C";
    else if (clazz == Short.TYPE)
      return "S";
    else if (clazz == Float.TYPE)
      return "F";
    else if (clazz == Double.TYPE)
      return "D";
    else if (clazz == Boolean.TYPE)
      return "Z";
    else if (clazz == Void.TYPE)
      return "V";
    else
      return "L"+clazz.getName().replace('.','/')+";";
  }

  boolean isNumeric()
  {
    if (clazz == null)
      return false;
    
    if (clazz.isPrimitive())
      return !(clazz == Void.TYPE || clazz == Boolean.TYPE) ;
    else 
      return false;
  }

  boolean isVoid()
  {
    if (clazz == null)
      return false;
    
    if (clazz.isPrimitive())
      return (clazz == Void.TYPE);
    else 
      return false;
  }

  boolean isCurrentlyDefined()
  {
    return (clazz != null);
  }

  Class getCompiledClass()
  {
    return clazz;
  }

  /** Convenience method to test whether this Type is acceptable as an operand to a bitwise operator
   *  @return true if type is an int, float or boolean, false otherwise
  **/
  boolean isAcceptableForBitwiseOp() {
    String g2Type = g2Name();
    return (g2Type.equals("integer")) || (g2Type.equals("float")) || (g2Type.equals("truth-value")); 
  }

  String g2Name()
  {
	  
    if (this instanceof ArrayType)
      throw new RuntimeException("arrays NYI");
    if (clazz == null)
      throw new RuntimeException("uncompiled classes NYI");
    
    boolean isInteger = clazz == Integer.TYPE || clazz == Long.TYPE || clazz == Byte.TYPE;
    isInteger = isInteger || clazz == Character.TYPE || clazz == Short.TYPE;
    
    if (isInteger)
      return "integer";
    else if (clazz == Float.TYPE || clazz == Double.TYPE)
      return "float";
    else if (clazz == Boolean.TYPE)
      return "truth-value";
    else if (clazz == Void.TYPE)
      return "None";
    else
      return clazz.getName().toLowerCase().replace('.','-');
  }

  // should be called widening reference conversion allowed!
  public boolean isAssignableFrom(Type type)
  {
    try {
      if (clazz != null)
	{
	  if (type.clazz != null)
	    return clazz.isAssignableFrom(type.clazz);
	  else if (type.isInterface())
	    return false;  // this needs a narrowing conversion
	  else
	    return isAssignableFrom(type.getSuperclass());
	}
      else if (this.equals(type))
	return true;
      else
	return isAssignableFrom(type.getSuperclass());
    }
    catch (ClassNotFoundException cnfe)
      {
	System.out.println("Ill-formed type "+type);
	cnfe.printStackTrace();
	throw new RuntimeException("ill-formed type"+type);
      }
  }

  public boolean isInterface()
  {
    if (clazz != null)
      return clazz.isInterface();
    else
      return uncompiledClass.getAccess().isInterface();
  }


  public boolean isArray()
  {
    if (clazz != null)
      clazz.isArray();
    else
      throw new RuntimeException("NYI");
    return false;
  }

  public boolean isPrimitive()
  {
    if (clazz != null)
      return clazz.isPrimitive();
    else
      return false;
  }
  
  public Class getPrimitive()
  {
    if (clazz != null)
      return (clazz.isPrimitive() ? clazz : null);
    else
      return null;
  }

  public String getName()
  {
    if (clazz != null)
      return clazz.getName();
    else
      return uncompiledClass.getClassName();
  }
 

  public Type getSuperclass()
       throws ClassNotFoundException
  {
    if (clazz != null)
      {
	Class superClass = clazz.getSuperclass();
	return forName(compiler,superClass.getName());
      }
    else
      {
	String parentName = uncompiledClass.getSuperClassName();
	if (parentName.indexOf('/') != -1)
	  throw new RuntimeException("Allan Error encountered "+parentName);
	return forName(compiler,parentName);
      }
  }

  public Type[] getInterfaces()
       throws ClassNotFoundException
  {
    // if java were lisp I could combine the following two cases.
    if (clazz != null)
      {
	Class[] interfaces = clazz.getInterfaces();
	Type[] interfaceTypes = new Type[interfaces.length];
	for (int i = 0; i < interfaces.length; i++)
	  interfaceTypes[i] =
	    forName(compiler,interfaces[i].getName());
	return interfaceTypes;
      }
    else
      {
	InterfaceInfo[] interfaces = uncompiledClass.getInterfaces();
	Type[] interfaceTypes = new Type[interfaces.length];
	for (int i = 0; i < interfaces.length; i++)
	  {
	    String interfaceName = interfaces[i].getName();
	    if (interfaceName.indexOf('/') != -1)
	      throw new RuntimeException("Allan Error encountered "+interfaceName);
	    interfaceTypes[i] = forName(compiler,interfaceName);
	  }
	return interfaceTypes;
      }
  }


  public Type getComponentType()
       throws ClassNotFoundException
  {
    if (clazz != null)
      return forName(compiler,clazz.getComponentType().getName());
    else
      return null;
  }

  public int getModifiers()
  {
    if (clazz != null)
      return clazz.getModifiers();
    else
      return uncompiledClass.getAccess().getModifiers();
  }
 
  public Class getDeclaringClass() {
    return null;                            /* not implemented */
  }

  public Class[] getClasses() {
    return new Class[0];                   
  }

  public Type getMethodReturnType(String methodName, boolean isStatic)
  {
    if (clazz != null)
      {
	Method[] methods = clazz.getMethods();
	for (int i = 0; i<methods.length ; i++)
	  {
	    Method method = methods[i];
	    int modifiers = method.getModifiers();
	    // System.out.println("method "+method+" may equal "+methodName);
	    if (method.getName().equals(methodName) &&
		Modifier.isStatic(modifiers) == isStatic)
	      return forName(compiler,method.getReturnType().getName());
	  }
	return null;
      }
    else
      return null;
  }

  private static com.gensym.util.Dispatcher methodDispatcher = new com.gensym.util.Dispatcher();

  public Method getMethod(String methodName, boolean isStatic, Type[] argTypes)
       throws CompilerException
  {
    Type fault = null;
    Method method = null;
    if (clazz != null)
      {
	Class argClasses[] = new Class[argTypes.length];
	for (int i = 0; i<argTypes.length; i++) 
	  {
	    System.out.println(argTypes.length + " " + i);
	    if (argTypes[i].clazz != null) 
	      {
		System.out.println(i + " " + argTypes[i].clazz.getName());
		argClasses[i] = argTypes[i].clazz;
	      }
	    else 
	      {
		fault = argTypes[i];
		break;
	      }
	  }
	if (fault == null) 
	  {
	    if (!isStatic)
	      method = methodDispatcher.findInstanceMethod(methodName,
							   this.clazz,
							   argClasses);
	    else
	      method = methodDispatcher.findStaticMethod(methodName,
							 this.clazz,
							 argClasses);
	  }
	else
	  throw new CompilerException("Unknown arg Type " + fault + " during lookup for " + methodName +
				      " in " + this);   
      }

    return method;
  }


  String getDescriptorForMethod(Method method) throws CompilerException
  {
    System.out.println("getting descriptor for " + method);
    StringBuffer descriptorBuffer = new StringBuffer("(");
    Class returnClass = method.getReturnType();
    Type returnType = forName(compiler, returnClass.getName());
    Class[] selectedArgClasses = method.getParameterTypes();
    for (int i = 0; i<selectedArgClasses.length; i++)
      {
	System.out.println("argType is  " + selectedArgClasses[i]);
	Type argType = forName(compiler,selectedArgClasses[i].getName());
	if (argType.clazz == null)
	  throw new CompilerException("Unknown arg Type " + argType + " for " + method.getName() +
				      " in " + this);
	descriptorBuffer.append(argType.makeDescriptor());
      }
    if (returnClass == Void.class)
      descriptorBuffer.append(")V");
    else
      descriptorBuffer.append(")" + returnType.makeDescriptor());
    return descriptorBuffer.toString();
  }
       

 
  public Type getFieldType(String fieldName, boolean allFields, boolean isStatic)
  {
    if (clazz != null)
      {
	Field field = null;
	ClassInheritancePath path = new ClassInheritancePath(clazz);
	while (path.hasMoreElements())
	  {
	    Class c = (Class) path.nextElement();
	    Field[] fields = c.getDeclaredFields();
	    for (int i = 0; i<fields.length ; i++)
	      if (fields[i].getName().equals(fieldName))
		field = fields[i];
	  }
	if (field == null)
	  return null;
	int modifiers = field.getModifiers();
	if (allFields || Modifier.isStatic(modifiers) == isStatic)
	  return Type.forName(compiler,field.getType().getName());
	else 
	  return null;
      }
    else
      {
	return null;
      }
  }

  /*
  public Field[] getFields() 
       throws SecurityException
  {
    if (clazz != null)
      return clazz.getFields();
  }
  

  public Method[] getMethods() throws SecurityException {
    checkMemberAccess(Member.PUBLIC);
    return getMethods0(Member.PUBLIC);
  }
  
  public Constructor[] getConstructors() throws SecurityException {
    checkMemberAccess(Member.PUBLIC);
    return getConstructors0(Member.PUBLIC);
  }


    public Field getField(String name)
        throws NoSuchFieldException, SecurityException {
        checkMemberAccess(Member.PUBLIC);
        return getField0(name, Member.PUBLIC);
    }

    public Method getMethod(String name, Class[] parameterTypes)
        throws NoSuchMethodException, SecurityException {
        checkMemberAccess(Member.PUBLIC);
        return getMethod0(name, parameterTypes, Member.PUBLIC);
    }

  public Constructor getConstructor(Class[] parameterTypes)
        throws NoSuchMethodException, SecurityException {
        checkMemberAccess(Member.PUBLIC);
        return getConstructor0(parameterTypes, Member.PUBLIC);
    }

  public Class[] getDeclaredClasses() throws SecurityException 
  {
    checkMemberAccess(Member.DECLARED);
    return new Class[0];                    // not implemented
  }
  */

  /*
  public Field[] getDeclaredFields() throws SecurityException {
        checkMemberAccess(Member.DECLARED);
        return getFields0(Member.DECLARED);
    }
 
    public Method[] getDeclaredMethods() throws SecurityException {
        checkMemberAccess(Member.DECLARED);
        return getMethods0(Member.DECLARED);
    }

    public Constructor[] getDeclaredConstructors() throws SecurityException {
        checkMemberAccess(Member.DECLARED);
        return getConstructors0(Member.DECLARED);
    }

    public Field getDeclaredField(String name)
        throws NoSuchFieldException, SecurityException {
        checkMemberAccess(Member.DECLARED);
        return getField0(name, Member.DECLARED);
    }

    public Method getDeclaredMethod(String name, Class[] parameterTypes)
        throws NoSuchMethodException, SecurityException {
        checkMemberAccess(Member.DECLARED);
        return getMethod0(name, parameterTypes, Member.DECLARED);
    }


    public Constructor getDeclaredConstructor(Class[] parameterTypes)
        throws NoSuchMethodException, SecurityException {
        checkMemberAccess(Member.DECLARED);
        return getConstructor0(parameterTypes, Member.DECLARED);
    }
   */
}


class ClassInheritancePath implements Enumeration
{
  Vector classesVisited= new Vector();
  Stack stack = new Stack();
  
  ClassInheritancePath (Class c)
  {
    super();
    stack.push(c);
  }

  @Override
  public boolean hasMoreElements()
  {
    return ! stack.empty();
  }
  
  @Override
  public Object nextElement()
  {
    Class c = (Class) stack.pop();
    classesVisited.addElement(c);
    if (c != null)
      {
	if (c.isInterface())
	  {
	    Class[] interfaces = c.getInterfaces();
	    for (int i = (interfaces.length - 1) ; i>= 0 ; i--)
	      {
		Class intf = interfaces[i];
		if (!classesVisited.contains(intf))
		  stack.push(intf);
	      }
	  }
	else
	  {
	    Class superClass = c.getSuperclass();
	    if (superClass != null && !classesVisited.contains(superClass))
	      stack.push(superClass);
	  }
      }
    return c;
  }
}
