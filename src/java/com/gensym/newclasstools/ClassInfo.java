package com.gensym.newclasstools;

import java.util.Vector;
import java.io.*;
import java.lang.reflect.Method;
import java.lang.reflect.Constructor;

/** ClassInfo is the top level object that can be  used to store information
* about a class file inside a Java VM.  The ClassInfo object reflects very
* closely the structure defined in Chapter 4 of the "Java Virtual Machine
* Specification" (the Red Book).<p>  
* ClassInfo objects can be used to parse class files into their component parts, 
* to merge different parts of different class files, to create new class files, 
* and finally to emit class files as bytes.<br>
*/
public class ClassInfo implements RuntimeConstants
{
  //************ Properties ******************
  
  /** Magic number.  This is always 0xCAFEBABE in a valid class file */
  private int magic_number;
  public int getMagicNumber() 
  {
    return magic_number;
  }

  /** Minor version of the compiler that produced this class file */
  private int minor_version;
  public int getMinorVersion() 
  {
    return minor_version;
  }

  /** Major version of the compiler that produced this class file */
  private int major_version;
  public int getMajorVersion() 
  {
    return major_version;
  }

  /** The pool of constants for this class */
  private ConstantPool constantPool;
  public ConstantPool getConstantPool() 
  {
    return constantPool;
  }

  /** The access restrictions of this class */
  private InterfaceOrClassAccess access;
  public Access getAccess() 
  {
    return access;
  }

  public void setAccess(InterfaceOrClassAccess access) 
  {
    this.access = access;
  }

  public int getModifiers() {
    return access.getModifiers();
  }

  /** The type object for this class */
  private Type classType;

  public Type getClassType() {
    return classType;
  }

  public void setClassType(Type type) {
    classType = type;
  }

  public String getClassName() 
  {
    return classType.getClassName();
  }

  /** The type of the super class of this class */
  private Type superType;

  public Type getSuperType() {
    return superType;
  }

  public void setSuperType(Type type) {
    superType = type;
  }


  public String getSuperClassName() 
  {
    return superType.getClassName();
  }

  /** An array that summarizes the fields that this class defines */
  private Vector fields = new Vector()
;
  public FieldInfo[] getFields() 
  {
    FieldInfo[] fieldArray = new FieldInfo[fields.size()];
    for(int i = 0 ; i < fields.size() ; i++) {
      fields.copyInto(fieldArray);
    }
    return fieldArray;
  }

  public FieldInfo getField(String name)
  {
    if (fields == null)
      return null;
    else
      {
	int i,size = fields.size();
	for (i=0; i<size ; i++)
	  {
	    FieldInfo fieldInfo = (FieldInfo)fields.elementAt(i);
	    if (fieldInfo.getName().equals(name))
	      return fieldInfo;
	  }
	return null;
      }
  }

  /** An array that summarizes the methods that this class defines.
   * this does not including <init> and <clinit> methods */
  private Vector methods = new Vector();

  public MethodInfo[] getMethods() 
  {
    if (methods == null)
      return new MethodInfo[] { };
    MethodInfo[] methodArray = new MethodInfo[methods.size()];
    methods.copyInto(methodArray);
    return methodArray;
  }

  /** An array that summarized the interfaces that this class defines */
  private Vector interfaces = new Vector();
  public InterfaceInfo[] getInterfaces() 
  {
    InterfaceInfo[] interfaceArray = new InterfaceInfo[interfaces.size()];
    interfaces.copyInto(interfaceArray);
    return interfaceArray; 
  }

  /** An array of the attributes of this class. */
  private Vector attributes = new Vector();
  public Attribute[] getAttributes()
  {
    Attribute[] attributeArray = new Attribute[attributes.size()];
    attributes.copyInto(attributeArray);
    return attributeArray;       
  }

  /** A vector of static initialization blocks and static fields. We need
   * to store these together to keep track of their relative order,
   * since the static field initialization and static block execution
   * must be interleaved.
   */

  private Vector staticInitializers = new Vector();

  /** A vector of instance initialization blocks and instance fields. We need
   * to store these together to keep track of their relative order,
   * since the field initialization and instance initializer block execution
   * must be interleaved.
   */

  private Vector initializers = new Vector();

  Vector getInitializers() {
    return initializers;
  }

  private MethodInfo staticInitMethod = null;

  public MethodInfo getStaticInitMethod() throws ClassException {
    if (staticInitMethod == null)
      return computeStaticInitMethod();
    else
      return staticInitMethod;
  }

  private MethodInfo computeStaticInitMethod() throws ClassException {
    Block block = new Block();
    for (int i = 0; i < staticInitializers.size(); i++) {
      Object initializer = staticInitializers.elementAt(i);
      if (initializer instanceof FieldInfo) {
	FieldInfo fieldInfo = (FieldInfo)initializer;
	if (fieldInfo.isStatic() &&
	    (fieldInfo.getInitialValue() != null)) 
	  block.add(fieldInfo.getFieldInitializer(this));
      }
      if (initializer instanceof Block) {
	block.add((Block)initializer);
      }
      // Could add case here to handle <clinit>, too.
    }
    if (block.isEmpty())
      return null;
    return new MethodInfo(new Access(ACC_STATIC),
			  "<clinit>",
			  Type.VOID_TYPE,
			  new Type[]{},
			  block,
			  new String[]{},
			  new Type[]{});
  }

  /** A vector of Constructors */
  
  private Vector constructors = new Vector();
  public ConstructorInfo[] getConstructors()
  {
    ConstructorInfo[] constructorArray = new ConstructorInfo[constructors.size()];
    constructors.copyInto(constructorArray);
    return constructorArray;       
  }

  /** Boolean that designates whether this class Info object is valid, whether it
   * is complete enough to be emitted as a class file */
  private boolean isValidClass = true;
  public boolean isValidClass()
  {
    return isValidClass;
  }

  private byte[] bytes;

  private static final boolean trace = false;



  // ************** Constructors ***********************
  
  /** Creates a ClassInfo by parsing an input stream.  If the input stream
  * does not in valid .class format then this will throw a ClassException
  *
  * @exception ClassException
  *       Failure during parsing of the class from the input stream
  **/
  public ClassInfo(InputStream in)
       throws ClassException
  {
    try {
      readInput(in);
    } catch (Exception e)
      {
	isValidClass = false;
      }
    if (isValidClass)
      parseClassFile();
  }

  /** Creates a ClassInfo by parsing a buffer of bytes.  If the buffer is not in
  * valid .class format then this will throw a ClassException
  *
  * @exception ClassException
  *       Failure during parsing of the class from the byte buffer
  */
  public ClassInfo(byte[] buffer)
       throws ClassException
  {
    bytes = buffer;
    parseClassFile();
  }

  /** Creates a blank ClassInfo object with the bare minimum contents.
  * Note class names must be fully qualified with
  * package information. Note that this will not generate a constructor
  * method.<p>
  *
  * Example - to create a ClassInfo to represent:
  * <pre><code>
  *  package com.gensym.tests;
  * 
  *  public final class Foo extends Bar {
  *      }
  * </code>
  * use:
  *<code>
  * // Creating the empty ClassInfo object
  * ClassInfo ci = new ClassInfo(new ClassAccess(ACC_PUBLIC & ACC_FINAL),
  *                              new Type("com.gensym.classtools.Foo"),
  *                              new Type("com.gensym.classtools.Bar"),
  *                              true);
  * </code>
  * </pre>
  * This last argument indicates that you want an empty constructor method
  * to be specified.
  */
  public ClassInfo (InterfaceOrClassAccess flags,
		    Type thiscl,
		    Type supercl,
		    boolean createZeroArgConstructor)
       throws ClassException
  {
    if (flags instanceof InterfaceAccess) {
      initialize(flags,thiscl,Type.OBJECT_TYPE,createZeroArgConstructor);       
      if (supercl != null)
	add(new InterfaceInfo(supercl));
    }
    else initialize(flags,thiscl,supercl,createZeroArgConstructor); 
  }

  /**
   * A shortcut for when the super class is java.lang.Object.
   */
  public ClassInfo (InterfaceOrClassAccess flags,
		    Type thiscl,
		    boolean createZeroArgConstructor)
       throws ClassException
  {
    initialize(flags,thiscl,Type.OBJECT_TYPE,createZeroArgConstructor);
  }

  /* 
  * Constructor for dedicated use in specifying interfaces. Since 
  * interfaces can "extend" multiple interfaces the super interfaces 
  * can be specified in an array.  This is a convenience only, the
  * same can be achieved by specifying an interface class that is
  * a subclass of java.lang.Object and adding InterfaceInfo objects to
  * the ClassInfo object.
  */
  public ClassInfo(InterfaceAccess flags,
                   Type thiscl,
                   Type[] superInterfaces) 
       throws ClassException
  {
    initialize(flags,thiscl,Type.OBJECT_TYPE,false);
    if (superInterfaces != null) {
      int size = superInterfaces.length;
      for (int i = 0; i < size; i++)
        add(new InterfaceInfo(superInterfaces[i]));
    }
  }

  private void initialize (InterfaceOrClassAccess flags,Type thiscl,Type supercl, boolean zargp)
       throws ClassException
  {
    
    if (null == thiscl)
      throw new ClassException("Null classType passed to ClassInfo constructor");
    if (null == flags) 
        throw new ClassException("Null access flags passed to ClassInfo constructor");
    if (supercl == null)
      supercl = Type.OBJECT_TYPE;
    
    if(thiscl.equals(supercl)) 
      throw new ClassException("Class cannot extend itself: " + thiscl);
    
    if (zargp & (flags instanceof InterfaceAccess))
      throw new ClassException("An interface cannot contain a constructor");
    
    magic_number = JAVA_MAGIC;
    major_version = JAVA_VERSION;
    minor_version = JAVA_MINOR_VERSION;
    flags.addSuper();
    access = flags;
    classType = thiscl;
    superType = supercl;
    constantPool = new ConstantPool();
    if (zargp) {
      add(new ConstructorInfo(new Access(ACC_PUBLIC),
			      null,
			      new Block(),
			      null,
			      null));
      isValidClass = true;
    } else {
      // Not valid until it has a constructor
      isValidClass = false;
    }
  }

  // **************** Output tools **********************

  /** Returns the cached bytes for this class. 
  */
  public byte[] getBytes() {
    return bytes;
  }

  /** Depending upon whether the argument is true or not, this will
   * force the re-emitting of the bytes for this ClassInfo.  This
   * involves emitting at every level of the ClassInfo  object.
   */
  public byte[] getBytes(boolean re_emit) throws ClassException {
    if (! re_emit) 
      return bytes;
    else {
      emit();
      return bytes;
    }
  }

  /** toFile() will write the bytes that represent this ClassInfo object to a file.
   * The second argument specifies whether emitting should take place before this, or
   * whether cached bytes are used.
   */
  public void toFile(String fileName, boolean re_emit) throws IOException, ClassException {
    FileOutputStream fileOutStream = new FileOutputStream(fileName);
    fileOutStream.write(getBytes(re_emit));
    fileOutStream.close();
  }

  /** Produces a summary of the ClassInfo object as a string.
   */
  @Override
  public String toString() {
    return "ClassInfo for" + getClassName();
  }

  /** Write a report on this class info object to standard output.  
   */
  public void toStdout() {
    System.out.println("Summary of ClassInfo");
    System.out.println("--------------------");
    System.out.println("");
    System.out.println("Magic number: " + magic_number);
    System.out.println("Minor version: " + minor_version);
    System.out.println("Major version: " + major_version);
    System.out.println("");
    System.out.println("Class name: " + ((classType == null) ? "undefined" : getClassName()));
    System.out.println("Super Class name: " + ((superType  == null) ? "undefined" : getSuperClassName()));
    System.out.println("");
    if (isValidClass)
      System.out.println("This class is a valid Java class");
    else System.out.println("This class is not a valid Java class");
    System.out.println("");
    access.toStdout();
    System.out.println("");
    constantPool.toStdout();
    System.out.println("");
    FieldInfo.toStdout(fields);
    System.out.println("");
    MethodInfo.toStdout(methods);
    System.out.println("");
    InterfaceInfo.toStdout(interfaces);
    System.out.println("");
    Attribute.toStdout(attributes,"");
    System.out.println("");
    ConstructorInfo.toStdout(constructors, this);
    System.out.println("");
  }

  // ***************** Operations on this class ***********************

   /** Adds an InterfaceInfo object to this ClassInfo object
   *
   * @exception  ClassException
   *         A failure during addition into this ClassInfo object.
   */
  public void add(InterfaceInfo interfaceInfo)
    throws ClassException
  {
    // Is there an interface with the same name already in this
    // class. If so throw a ClassException.  More forgiving
    // approaches can be imagined
    if (interfaces != null)
      {
	for (int i =0; i < interfaces.size(); i++) {
	  if(interfaceInfo.equals((InterfaceInfo) interfaces.elementAt(i))) {
            throw new ClassException("Interface already defined " + 
				     interfaceInfo.getName());
	  }
	}
      }
    
    if (interfaces== null) {
      interfaces = new Vector();
    }
    interfaces.addElement(interfaceInfo);
  }


   /** Remove an InterfaceInfo object from this ClassInfo object
   *
   */
  public void remove(InterfaceInfo interfaceInfo)
  {
    if (interfaces != null) {
      interfaces.remove(interfaceInfo);
    }
  }

  /** Adds a field to this ClassInfo object
   *
   * @exception  ClassException
   *         A failure during merging into this ClassInfo object.
   */
  public void add(FieldInfo fieldInfo)
       throws ClassException
  { 

    // Is there a field of the same name and type already in this
    // class. If so throw a ClassException. 
    FieldInfo fieldInfo2;
    for (int i =0; i < fields.size(); i++) {
      fieldInfo2 = (FieldInfo) fields.elementAt(i);
      if(fieldInfo.getName().equals(fieldInfo2.getName())
	 && !(fieldInfo.getAccess().isPrivate() &&
	      fieldInfo2.getAccess().isPrivate()))
	throw new ClassException("Field name already defined" + fieldInfo.getName() + " " +
				 fieldInfo.getType().descriptor());
    }

  fields.addElement(fieldInfo);
  if(fieldInfo.isStatic())
    staticInitializers.addElement(fieldInfo);
  else
    initializers.addElement(fieldInfo);
  } 

  public void deleteField(String fieldName)
  {
    int i,size = fields.size();
    for (i=0; i<size ; i++) {
      FieldInfo fieldInfo = (FieldInfo)fields.elementAt(i);
      if (fieldInfo.getName().equals(fieldName)) {
	fields.remove(fieldInfo);
	if(fieldInfo.isStatic())
	  staticInitializers.remove(fieldInfo);
	else
	  initializers.remove(fieldInfo);
	return;
      } 
    }
    System.out.println("Field " + fieldName + " not found");
  }


  public void remove(FieldInfo field)
  {
    fields.remove(field);
    if(field.isStatic())
      staticInitializers.remove(field);
    else
      initializers.remove(field);
  } 

  /** Adds a method to this ClassInfo object
   *
   * @exception  ClassException
   *         A failure during adding into this ClassInfo object.
   */
  public void add(MethodInfo methodInfo)  throws ClassException {
    // Is there a method of the same descriptor already in this
    // class. If so throw a ClassException. 
    MethodInfo methodInfo2;	
    for (int i =0; i < methods.size(); i++) {
      methodInfo2  = (MethodInfo) methods.elementAt(i);
      if(methodInfo.getName().equals(methodInfo2.getName()) &&
	 methodInfo.getDescriptor().equals(methodInfo2.getDescriptor()))
	throw new ClassException("Method name and type already defined" + methodInfo.getName() +
				 " " + methodInfo.getDescriptor());
    }
    // Add in the method to the end of the methods vector
    methods.addElement(methodInfo);
  }

   /** Remove a MethodInfo object from this ClassInfo object
   *
   */
  public void remove(MethodInfo methodInfo)
  {
    methods.remove(methodInfo);
  }

  /** Adds an attribute to this ClassInfo object
   *
   * @exception  ClassException
   *         A failure during merging into this ClassInfo object.
   */
  public void add(Attribute attr)
       throws ClassException
  {
    attributes.addElement(attr);
  }

   /** Remove a Attribute object from this ClassInfo object
   *
   */
  public void remove(Attribute attribute)
  {
    attributes.remove(attribute);
  }

  /** Adds a constructor to this ClassInfo object
   *
   */

  public void add(ConstructorInfo constructor) {
    constructors.addElement(constructor);
    isValidClass = true;
  }


   /** Remove a Constructor object from this ClassInfo object
   *
   */
  public void remove(ConstructorInfo constructorInfo)
  {
    constructors.remove(constructorInfo);
    if (constructors.size() == 0)
      isValidClass = false;
  }

  /** Add an instance or class initialization block to this ClassInfo Object.
   *
   */
  public void add(Block initializer, boolean staticp) {
    if(staticp)
      staticInitializers.add(initializer);
    else
      initializers.add(initializer);
  }

  /** Remove an instance or class initialization block to this ClassInfo Object.
   *
   */
  public void remove(Block initializer, boolean staticp) {
    if(staticp)
      staticInitializers.remove(initializer);
    else
      initializers.remove(initializer);
  }

  public void emit() throws ClassException {
    
    // New output stream is by default the size of the original one if we have one,
    // Otherwize make it some reasonable large size that is the default for ClassOutput
    ClassOutput newclass;	
    MethodInfo methodInfo;
    if(bytes == null) 
      newclass = new ClassOutput();
    else newclass = new ClassOutput(bytes.length);
    ClassOutput newclass2 = new ClassOutput();

    try {
      constantPool = new ConstantPool();

      // Emit the access_flags
      access.emit(newclass.out);
      
      // Emit this class
      newclass.out.writeShort(constantPool.getIndex(new ClassConstant(classType)));

      // Emit the superclass
      newclass.out.writeShort(constantPool.getIndex(new ClassConstant(superType)));

      // Emit the interfaces *
      // Consider having interfaces as separate class with normalization/localization
      // protocol
      if(trace)
	System.out.println("Emitting Interfaces" + interfaces);
      InterfaceInfo.emit(interfaces,newclass.out, constantPool);
      
      if (trace)
	System.out.println("Emitting " + fields);
      // Emit the fields *
      FieldInfo.emit(fields,newclass.out, constantPool);
      
      // Emit the methods *
      Vector allmethods = (Vector)methods.clone();
      MethodInfo staticInit = computeStaticInitMethod();
      if (staticInit != null)
	allmethods.addElement(staticInit);
      for(int i = 0; i < constructors.size(); i++) {
	allmethods.addElement(((ConstructorInfo)constructors.elementAt(i)).computeConstructorMethod(this));
      }
	
      MethodInfo.emit(allmethods,newclass.out, classType, constantPool);
      
      // Emit the attributes *  
      if (trace)
	System.out.println("Emitting " + attributes);
      Attribute.emit(attributes,newclass.out, constantPool);
    
    // Now that all of these have been emitted, the constant pool has
    // all required entries, and we can emit that.

    // Emit magic_number
    newclass2.out.writeInt(magic_number);
    
    // Emit minor_version
    newclass2.out.writeShort(minor_version);
    
    // Emit major_version
    newclass2.out.writeShort(major_version);
    
    // Emit the constant pool *
    constantPool.emit(newclass2.out);
    }
    catch (Exception e) {
      System.out.println("Failure during emit");
      e.printStackTrace();
    }
    
    // Get the buffer from the stream and assign them to bytes
    bytes = new byte[newclass.bytes.size() + newclass2.bytes.size()];

    System.arraycopy(newclass2.bytes.toByteArray(),0,bytes,0,newclass2.bytes.size());

    System.arraycopy(newclass.bytes.toByteArray(),0,bytes,newclass2.bytes.size(),
		     newclass.bytes.size());
  }
  
  // * - must emit size then iteratively emit each info type
  

  //*************** Utilities private to this class ********************
  
  
  private int readU2(int index)
       throws ArrayIndexOutOfBoundsException
  {
    return ((bytes[index] & 0xFF) << 8) + (bytes[index + 1] & 0xFF);
  }
  
  private int readS2(int index) 
       throws ArrayIndexOutOfBoundsException
  {
    return ((int)bytes[index] << 8) + (bytes[index + 1] & 0xFF);
  }
  
  private int readU4(int index) 
       throws ArrayIndexOutOfBoundsException 
  {
    int high = readU2(index);
    int low = readU2(index + 2);
    return (high << 16) + low;
  }
  
  private int readS4(int index) 
       throws ArrayIndexOutOfBoundsException 
  {
    return readU4(index);
  }
  
  private long readU8(int index)
       throws ArrayIndexOutOfBoundsException
  {
    long high = readU4(index);
    long low = readU4(index + 4);
    return (high << 32L) + low;
  }
  
  private void readInput(InputStream dataIn) throws IOException {

    int bufferSize = 2048;
    byte[] input = new byte[bufferSize];

    Vector inputs = new Vector();
    int inputUsed = 0;
    int totalBytes = 0;
    int n;
    while((n = dataIn.read(input, inputUsed, input.length - inputUsed)) >= 0)
      {
	inputUsed += n;
	totalBytes += n;
	if(inputUsed == input.length) {
	  inputs.addElement(input);
	  input = new byte[bufferSize];
	  inputUsed = 0;
	}
      }
    if (inputs.size() == 0) {
      bytes = input;
    } else {
      byte newinput[] = new byte[totalBytes];
      int index = 0;
      for(int i = 0; i < inputs.size(); i++) {
	int size = ((byte[])inputs.elementAt(i)).length;
	System.arraycopy((byte[])inputs.elementAt(i), 0, newinput, index, size);
	index += size;
    }
      System.arraycopy(input, 0, newinput, index, inputUsed);
      bytes = newinput;
    }
  }
  


  protected void parseClassFile()
       throws ClassException
  {
    magic_number = readU4(0);
    if(magic_number != 0xCAFEBABE)
      {
	System.out.println("not a class file");
	throw new ClassException();
      }
    
    minor_version = readU2(4);
    major_version = readU2(6);
    
    // constant pool
    
    int offset = 8;
    
    ConstantParser constantParser = new ConstantParser(bytes, offset);
    
    try {
      constantPool =  ConstantPool.readConstantPool(constantParser);
      offset = constantParser.getIndex();
    }
    catch(Exception e) 
      {
	System.out.println("corrupt constant pool");
        e.printStackTrace();
      }
    if (trace)
      constantPool.toStdout();
    
    // access flags
    
    int flags = readU2(offset);
    try {
      access = new ClassAccess(flags);
    }
    catch (Exception e) {
      try {
	access = new InterfaceAccess(flags);
      }
      catch (Exception e2) {
	throw new ClassException("Access flags are invalid");
      }
    }
    offset += 2;

    // class name
    int classIndex = -1;
    try {
      classIndex = readU2(offset);
      if (constantPool.getConstant(classIndex) == null ||
	  constantPool.getConstant(classIndex).getType() != CONSTANT_CLASS)
	throw new ClassException("thisClass record corrupt: " + offset + " Index " + classIndex);
      if (trace)
        System.out.println("Class Name Index = " + classIndex);
      classType = ((ClassConstant)constantPool.getConstant(classIndex)).getMyClass();
      offset += 2;
    }
    catch (ArrayIndexOutOfBoundsException e) {
      throw new ClassException("thisClass record corrupt: " + offset + " Index " + classIndex);
    }
    if (trace)
      System.out.println("Class Type: " + classType);
    
    // super class name
    
    superType = Type.OBJECT_TYPE;
    try {
      int superIndex = readU2(offset);
      if (superIndex != 0 && 
	  (constantPool.getConstant(superIndex) == null ||
	   constantPool.getConstant(superIndex).getType() != CONSTANT_CLASS))
	throw new ClassException("superClass record corrupt: " + offset);
      
      if (superIndex != 0)
	superType = ((ClassConstant)constantPool.getConstant(superIndex)).getMyClass();
      offset += 2;
    }
    catch(ArrayIndexOutOfBoundsException e) {
      throw new ClassException("superClass record corrupt: " + offset);
    }
    
    if (trace)
      System.out.println("cname ="+ getClassName() +" super= "+getSuperClassName());
    
    // interfaces
    
    try {
      int interfaceCount = readU2(offset);
      offset += 2;
      interfaces = new Vector();
      if(interfaceCount > 0) {
	for(int i = 0; i < interfaceCount; i++) {
	  int index = readU2(offset);
	  Constant constant = constantPool.getConstant(index);
	  if(constant != null && constant.getType() == CONSTANT_CLASS)
	    {
	      interfaces.addElement(new InterfaceInfo((ClassConstant)constant));
	    }
	  offset += 2;
	}
      }
    }
    catch(ArrayIndexOutOfBoundsException e) {
      throw new ClassException("Interface record corrupt: " + offset);
    }
    
    

    if (trace)
      for (int itf = 0 ; itf < interfaces.size() ; itf++)
	System.out.println("  implements "+interfaces.elementAt(itf));
    

    
    // fields
    
    try {
      if (trace)
	System.out.println("Before get field count = ");
      int fieldCount = readU2(offset);
      if (trace)
	System.out.println("Field count = " + fieldCount);
      offset += 2;
      fields = new Vector();
      for(int i = 0; i < fieldCount; i++) 
	{
	  Access access = new Access(readU2(offset));
	  fields.addElement
	    (new FieldInfo
	     (access,
	      ((UTF8Constant)constantPool.getConstant(readU2(offset+2))).getString(), // name
	      Type.parseType(((UTF8Constant)constantPool.getConstant(readU2(offset+4))).getString()), // field type.
	      access.isStatic()));
	  int attributeCount = readU2(offset+6);
	  if (trace)
	    System.out.println("Read Attributes :" + attributeCount);
	  offset += 8;
	  Vector attributes = new Vector(attributeCount);
	  for (int j = 0 ; j<attributeCount ; j++)
	    {
	      attributes.addElement(Attribute.readAttribute(constantPool,bytes,offset));
	      offset += (((Attribute) attributes.elementAt(j)).length + 6);
	    }
	  ((FieldInfo) fields.elementAt(i)).attributes = attributes; 
	}
    } catch(ArrayIndexOutOfBoundsException e) {
      throw new ClassException("Field record corrupt: " + offset);
    }
    
    
    // methods
    
    try {
      int methodCount = readU2(offset);
      offset += 2;
      methods = new Vector();
      MethodInfo method;
      for(int i = 0; i < methodCount; i++) 
	{
	  //Should do all this work in MethodInfo() itself.
	  method = new MethodInfo(new Access(readU2(offset)),  // Access
				  (UTF8Constant)constantPool.getConstant(readU2(offset+2)), // name
				  (UTF8Constant)constantPool.getConstant(readU2(offset+4))); // descriptor
	  int attributeCount = readU2(offset+6);
	  offset += 8;
	  Vector attributes = new Vector(attributeCount);
	  for (int j = 0 ; j<attributeCount ; j++)
	    {
	      attributes.addElement(Attribute.readAttribute(constantPool,bytes,offset));
	      offset += (((Attribute) attributes.elementAt(j)).length + 6);
	    }
	  method.attributes = attributes;
	  if (method.getName().equals("<init>")) {
	    constructors.addElement(new ConstructorInfo(method));
	  } else if (method.getName().equals("<clinit>")) {
	    staticInitMethod = method;
	  } else {
	    methods.addElement(method);
	  }
	}
    } catch(ArrayIndexOutOfBoundsException e) {
      e.printStackTrace();
      throw new ClassException("Method record corrupt: " + offset);
    }
    
    // attributes
    
    try {
      int attributeCount = readU2(offset);
      offset += 2;
      attributes = new Vector(attributeCount);
      if(attributeCount > 0) {
	for(int i = 0; i < attributeCount; i++) {
	  attributes.addElement(Attribute.readAttribute(constantPool,bytes,offset));
	  offset += (((Attribute) attributes.elementAt(i)).length + 6);
	}
      }
    } catch(ArrayIndexOutOfBoundsException e) {
      e.printStackTrace();
      throw new ClassException("Attribute record corrupt: " + offset);
    }  
  }

  // New constructor for Joe; given an Interface name, constructs a class that implements
  // that interface (in a completely useless way; it throws a RuntimeException
  // whenever any of its methods are called)

  public ClassInfo (String interfaceName, String newClassName) throws ClassException {
    this(interfaceName,
	 new InterfaceOrClassAccess(ACC_PUBLIC | ACC_SUPER),
	 Type.makeType(newClassName),
	 Type.OBJECT_TYPE);
  }

  public ClassInfo (String interfaceName,
		    InterfaceOrClassAccess flags,
		    Type thiscl,
		    Type supercl) throws ClassException
  {
      this(flags, thiscl, supercl, true);
    try {
      Class theInterface = Class.forName(interfaceName);
      add(new InterfaceInfo(Type.makeType(interfaceName)));
      Method[] methods = theInterface.getMethods();
      int i;
      for (i = 0; i < methods.length; i++) {
	Method method = methods[i];
	Block block = new Block();
	block.add(new Throw(new New(Type.makeType("java.lang.RuntimeException"),
				    new Type[]{Type.STRING_TYPE},
				    new Expression[]
				    {new Value("Method " + method.getName() + " not yet implemented")})));
	add(new MethodInfo(new Access(ACC_PUBLIC),
			   method.getName(),
			   Type.typeForClass(method.getReturnType()),
			   Type.argTypesForMethod(method),
			   block,
			   null,
			   Type.typesFromClasses(method.getExceptionTypes())));
      }
      Constructor[] constructors = theInterface.getConstructors();
      for (i = 0; i < constructors.length; i++) {
	Constructor constructor = constructors[i];
	// Don't signal an error in the constructor, since at least one of them must get called
	// by the subclass constructors. So just do nothing silently.
	// Don't generate the default constructor; we did that already.
	if (constructor.getParameterTypes().length > 0) {
	  Block block = new Block();
	  add(new ConstructorInfo(new Access(ACC_PUBLIC),
				  Type.typesFromClasses(constructor.getParameterTypes()),
				  block,
				  null,
				  Type.typesFromClasses(constructor.getExceptionTypes()),
				  DEFAULT_CONSTRUCTOR_CALL,
				  new Expression[]{}));
	}
      }
    } catch (Exception e) {
      throw new ClassException("error creating default interface implementation for " + 
			       interfaceName + ": " + e);
    }
  }
    

	
				  


  

  // Command line interface.
  
  private static final void reportUsage() {
    System.out.println("usage: java ClassInfo [report <classfile> ... | merge <classfile1> <classfile2> <outputfile>] (But merge is currently not supported)");
    System.exit(-1);
  }

  public static final void main (String[] args)
  {
    ClassInfo classInfo = null;
    ClassInfo classInfo2 = null;
    ClassInfo classInfo3 = null;
    
    try {	
      if ((args == null) || (args.length < 2))
	reportUsage();
      String command = args[0];
      if (command.equals("report")) {
	FileInputStream fileStream = new FileInputStream(args[1]);
	classInfo = new ClassInfo(fileStream);
	fileStream.close();
	classInfo.toStdout();
      }
      if(command.equals("merge")) {	
	System.out.println("merge is currently unsupported; talk to andy if you need it");
      } 
    }
    catch (Exception e)
      {
	System.out.println("ClassInfo operation failed");
	e.printStackTrace();
      }
  }
}
