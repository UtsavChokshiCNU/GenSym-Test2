package com.gensym.classtools;

import java.util.Vector;
import java.io.*;

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

  /** The name of the super class of this class */
  private String className;
  public String getClassName() 
  {
    return className;
  }

  /** The name of the super class of this class */
  private String superName;
  public String getSuperClassName() 
  {
    return superName;
  }

  /** An array that summarizes the fields that this class defines */
  private Vector fields;
  public FieldInfo[] getFields() 
  {
    if (fields == null)
      return new FieldInfo[] { };
    FieldInfo[] fieldArray = new FieldInfo[fields.size()];
    fields.copyInto(fieldArray);
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
	    if (fieldInfo.name.equals(name))
	      return fieldInfo;
	  }
	return null;
      }
  }

  /** An array that summarizes the methods that this class defines */
  private Vector methods;
  public MethodInfo[] getMethods() 
  {
    if (methods == null)
      return new MethodInfo[] { };
    MethodInfo[] methodArray = new MethodInfo[methods.size()];
    methods.copyInto(methodArray);
    return methodArray;
  }

  /** An array that summarized the interfaces that this class defines */
  private Vector interfaces;
  public InterfaceInfo[] getInterfaces() 
  {
    if (interfaces == null)
      return new InterfaceInfo[] { };
    InterfaceInfo[] interfaceArray = new InterfaceInfo[interfaces.size()];
    interfaces.copyInto(interfaceArray);
    return interfaceArray; 
  }

  /** An array of the attributes of this class. */
  private Vector attributes;
  public Attribute[] getAttributes()
  {
    if (attributes == null)
      return new Attribute[] { };
    Attribute[] attributeArray = new Attribute[attributes.size()];
    attributes.copyInto(attributeArray);
    return attributeArray;       
  }

  /** Boolean that designates whether this class Info object is valid, whether it
   * is complete enough to be emitted as a class file */
  private boolean isValidClass = true;
  public boolean isValidClass()
  {
    return isValidClass;
  }

  private boolean hasConstructor = false;
  public boolean hasConstructor()
  {
    return hasConstructor;
  }
  
  private byte[] bytes;
  private int classIndex;
  private int superIndex;
  private Vector bufferedClinits =  new Vector();

  private static MergeSession defaultMergeSession =
    new MergeSession(new ClassInfo[] {}, 
                     MergeSession.MERGE_EXCEPTION_ON_CONFLICT);

  private static MergeSession replaceMergeSession =
    new MergeSession(new ClassInfo[] {}, 
                     MergeSession.MERGE_REPLACE_ON_CONFLICT);

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
  *                              "com/gensym/classtools/Foo",
  *                              "com/gensym/classtools/Bar",
  *                              true);
  * </code>
  * </pre>
  * This last argument indicates that you want an empty constructor method
  * to be specified.
  */
  public ClassInfo (InterfaceOrClassAccess flags,
		    String thiscl,
		    String supercl,
		    boolean createZeroArgConstructor)
       throws ClassException
  {
    if (flags instanceof InterfaceAccess) {
      initialize(flags,thiscl,OBJECT_STR,createZeroArgConstructor);       
      if (supercl != null)
	add(new InterfaceInfo(supercl));
    }
    else initialize(flags,thiscl,supercl,createZeroArgConstructor); 
  }

  /**
   * A shortcut for when the super class is java.lang.Object.
   */
  public ClassInfo (InterfaceOrClassAccess flags,
		    String thiscl,
		    boolean createZeroArgConstructor)
       throws ClassException
  {
    initialize(flags,thiscl,OBJECT_STR,createZeroArgConstructor);
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
                   String thiscl,
                   String[] superInterfaces) 
       throws ClassException
  {
    initialize(flags,thiscl,OBJECT_STR,false);
    if (superInterfaces != null) {
      int size = superInterfaces.length;
      for (int i = 0; i < size; i++)
        add(new InterfaceInfo(superInterfaces[i]));
    }
  }

  private void initialize (InterfaceOrClassAccess flags,String thiscl,String supercl, boolean zargp)
       throws ClassException
  {
    
    if (null == thiscl)
      throw new ClassException("Null className passed to ClassInfo constructor");
    if (null == flags) 
        throw new ClassException("Null access flags passed to ClassInfo constructor");
    if (supercl == null)
      throw new ClassException("Null super class name passed to ClassInfo constructor");
    
    if(thiscl.equals(supercl)) 
      throw new ClassException("Class cannot extend itself: " + thiscl);
    
    if (zargp && (flags instanceof InterfaceAccess))
      throw new ClassException("An interface cannot contain a constructor");
    
    magic_number = JAVA_MAGIC;
    major_version = JAVA_VERSION;
    minor_version = JAVA_MINOR_VERSION;
    flags.addSuper();
    access = flags;
    className = thiscl;
    superName = supercl;
    constantPool = new ConstantPool();
    classIndex = constantPool.add(new ClassConstant(constantPool,className),true);
    superIndex = constantPool.add(new ClassConstant(constantPool,superName),true);
    if (zargp) {
      // Create 0 arg constructor method 
      MethodRef methodRef = new MethodRef(thiscl,
					  "<init>",
					  "()V");
	   // Call superior constructor
      MethodRef methodRef1 = new MethodRef(supercl,
					   "<init>",
					   "()V");
      MethodCall methodCall = new MethodCall(methodRef1,MTH_CALL_SPECIAL);
      Return rtrn = new Return();		
      Block block = new Block();	
      // Add statements to the block
      block.add(methodCall);
      block.add(rtrn);
      // Add block to MethodInfo
      MethodInfo methodInfo = new MethodInfo(new Access(ACC_PUBLIC),
					     methodRef,
					     null,
					     block);
      // Add  0 arg constructor to the class
	   add(methodInfo);
	   isValidClass = true;
    } 
    else {
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
  public byte[] getBytes(boolean re_emit) {
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
  public void toFile(String fileName, boolean re_emit) throws IOException {
    FileOutputStream fileOutStream = new FileOutputStream(fileName);
    fileOutStream.write(getBytes(re_emit));
    fileOutStream.close();
  }

  /** Produces a summary of the ClassInfo object as a string.
   */
  @Override
  public String toString() {
    return "ClassInfo for" + className;
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
    System.out.println("Class name: " + ((className == null) ? "undefined" : className));
    System.out.println("Super Class name: " + ((superName  == null) ? "undefined" : superName));
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
  }

  // ***************** Operations on this class ***********************

   /** Adds an InterfaceInfo object to this ClassInfo object
   *
   * @exception  ClassException
   *         A failure during merging into this ClassInfo object.
   */
  public void add(InterfaceInfo infceInfo)
    throws ClassException
  {
      add0(infceInfo, defaultMergeSession);
  }

  public void add0(InterfaceInfo infceInfo,
                   MergeSession session)                
                   throws ClassException
  {
    short mergePolicy = session.getMergePolicy();

    if ( ! infceInfo.normalized) {
      infceInfo.normalize();
    }
    
    // Is there an interface with the same name already in this
    // class. If so throw a ClassMergeException.  More forgiving
    // approaches can be imagined
    if (interfaces != null)
      {
	for (int i =0; i < interfaces.size(); i++) {
	  if(infceInfo.equals((InterfaceInfo) interfaces.elementAt(i)))
	    {
	      switch(mergePolicy)
		{
		case MergeSession.MERGE_EXCEPTION_ON_CONFLICT:   
            throw new ClassMergeException("Interface already defined " + 
					  infceInfo.name);
		case MergeSession.MERGE_IGNORE_ON_CONFLICT: 
		  return;
		case MergeSession.MERGE_BUFFER_CONFLICTS:
		  {
              // Need to add a MergeConflict to this session
		    
              return;
		  }
		case MergeSession.MERGE_REPLACE_ON_CONFLICT:
		  {
		    // Add in each new constant to the constantpool
		    constantPool.add(infceInfo.normalizedConstants);
		    
		    // Localize the interface to the newpool
		    infceInfo.localize(constantPool);
		    
		    // In this case replace the existing method with
              // the same name and the same descriptor
		    interfaces.setElementAt(infceInfo, i);                             
                   
		    return;
		  }
		default:
		}
	    }
	}
      }
    
    // Add in each new constant to the constantpool
    constantPool.add(infceInfo.normalizedConstants);
    
    // Localize the interface to the newpool
    infceInfo.localize(constantPool);
    
    if (interfaces!= null) {
      interfaces.addElement(infceInfo);
    }
    else {
      interfaces = new Vector();
      interfaces.addElement(infceInfo);
    } 
  }
    
  private void add0(MethodInfo methodInfo, 
                    boolean bufferClinits,
                    MergeSession mergeSession)
       throws ClassException
  {  
    boolean present;
    ConstantPool newpool;
    int added, lgth;
    short mergePolicy = mergeSession.getMergePolicy();
    
    // Check that the method has been normalized()
    if ( ! methodInfo.normalized) 
      methodInfo.normalize();
    
    // If the method is a "<clinit>" method then collect these separately.
    // When it comes to emit the class these are combined along with a all
    // field initial value expressions to produce a single "<clinit>" method
    if (methodInfo.name.equals("<clinit>") && bufferClinits) {
      bufferedClinits.addElement(methodInfo);
      methodInfo.setClassName(getClassName());
      return;
    }
    else {
      // Is there a method of the same descriptor already in this
      // class. If so throw a ClassMergeException. 
      if(methods != null) { 
	MethodInfo methodInfo2;	
	for (int i =0; i < methods.size(); i++) {
	  methodInfo2  = (MethodInfo) methods.elementAt(i);
	  if(methodInfo.name.equals(methodInfo2.name) &&
	     methodInfo.getDescriptor().equals(methodInfo2.getDescriptor()))
	    switch(mergePolicy)
	      {
	      case MergeSession.MERGE_EXCEPTION_ON_CONFLICT:   
                throw new ClassMergeException("Method name and type already defined" + methodInfo.name +
					      " " + methodInfo.getDescriptor());
              case MergeSession.MERGE_IGNORE_ON_CONFLICT: 
		return;
              case MergeSession.MERGE_BUFFER_CONFLICTS:
              {
                // Need to add a MergeConflict to this session
		
                return;
              }
              case MergeSession.MERGE_REPLACE_ON_CONFLICT:
		{
		  constantPool.add(methodInfo.normalizedConstants);
		  
                // Localize the method to the new constantpool
		  methodInfo.localize(constantPool);
		  
		  // In this case replace the existing method with
		  // the same name and the same descriptor
		  methods.setElementAt(methodInfo, i);
		  
		  return;
		}
		 default:
	      }
	}
      }
      
      // Change the class that the method refers to
      // NB - destructive operation.
      methodInfo.setClassName(getClassName());
      
      constantPool.add(methodInfo.normalizedConstants);
      
      // Localize the method to the new constantpool
      methodInfo.localize(constantPool);
      
      // Add in the method to the end of the methods vector
      if (methods == null) 
	methods = new Vector();	
      methods.addElement(methodInfo);
      
      // Should ensure that this is always true.
      if(! methodInfo.hasMethodRefConstant()) { 
	// Add the CONSTANT_Method and CONSTANT_NameAndType_info so that
	// the method can be located and understood.
	NameAndTypeConstant nametc = 
	  new NameAndTypeConstant(constantPool,
				  methodInfo.nameIndex,
				  methodInfo.getTypeIndex());
	int nametcindex = nametc.getWhere();
	MethodRefConstant methc =
	  new MethodRefConstant(constantPool,classIndex,nametcindex);
      }
      
      // If the method that was just added was a constructor method, and this class
      // did not have a constructor before then hasConstructor true.
      
      if (methodInfo.name.equals("<init>") && (hasConstructor == false))
	hasConstructor = true;  
    }
  }
  
  /** Adds a method to this ClassInfo object
   *
   * @exception  ClassException
   *         A failure during merging into this ClassInfo object.
   */
  public void add(MethodInfo methodInfo)  throws ClassException {
    add0(methodInfo,true, defaultMergeSession);	 
  }

  /** Adds a field to this ClassInfo object
   *
   * @exception  ClassException
   *         A failure during merging into this ClassInfo object.
   */
  public void add(FieldInfo fieldInfo)
       throws ClassException
  { 
    add0(fieldInfo, defaultMergeSession);
  }
  
  private void add0(FieldInfo fieldInfo, MergeSession session)
       throws ClassException
  {
    if (! fieldInfo.normalized)
      fieldInfo.normalize();
    
    short mergePolicy = session.getMergePolicy();

    // Is there a field of the same name and type already in this
    // class. If so throw a ClassMergeException. 
    if(fields != null) { 
      FieldInfo fieldInfo2;
      for (int i =0; i < fields.size(); i++) {
        fieldInfo2 = (FieldInfo) fields.elementAt(i);
        if(fieldInfo.getDescriptor().equals(fieldInfo2.getDescriptor()) &&
          fieldInfo.name.equals(fieldInfo2.name))
          switch(mergePolicy)
          {
          case MergeSession.MERGE_EXCEPTION_ON_CONFLICT:
            throw new ClassMergeException("Field name and type already defined" + fieldInfo.name + " " +
              fieldInfo.getDescriptor());

          case MergeSession.MERGE_IGNORE_ON_CONFLICT:
          case MergeSession.MERGE_BUFFER_CONFLICTS:
            // Need to add a MergeConflict to this session
            return;

          case MergeSession.MERGE_REPLACE_ON_CONFLICT:
            {
              constantPool.add(fieldInfo.normalizedConstants);
              fieldInfo.localize(constantPool);		
	      
	      
              // In this case replace the existing method with
              // the same name and the same descriptor
              fields.setElementAt(fieldInfo, i);              
              return; 
            }
          default:
	  }
      }
    }
    
    constantPool.add(fieldInfo.normalizedConstants);
    fieldInfo.localize(constantPool);		
    
    if (fields == null) {
      fields = new Vector();
      fields.addElement(fieldInfo);
    }
    else {
      fields.addElement(fieldInfo);
    }
  } 

  /** Adds an attribute to this ClassInfo object
   *
   * @exception  ClassException
   *         A failure during merging into this ClassInfo object.
   */
  public void add(Attribute attr)
       throws ClassException
  {
    attr.localize(constantPool,attr.getConstantPool());
    if (attributes == null)
      attributes = new Vector();
    attributes.addElement(attr);
  }
  
  /** Conduct a class merge.  The MergeSession defines which ClassInfo's
   * will be merged into this one, and how conflicts will be handled during 
   * the merge
   */
  public void merge(MergeSession mergeSession)
			throws ClassException
  {
    ClassInfo[] classes;
    MethodInfo methodInfo;
    FieldInfo fieldInfo;
    ClassInfo clinfo;
    
    classes = mergeSession.getClasses();
    
    // Check that the classes are adequate for a successful merge
    
    for (int j = 0; j < classes.length; j++)
      {
	clinfo = classes[j];
	
	// Add every method -  but not the constructor or class init methods 
	for(int i = 0; i < clinfo.methods.size(); i++) {
	  methodInfo = (MethodInfo) clinfo.methods.elementAt(i);
	  String name = methodInfo.name;
	  if (!(name.equals("<init>")))
	    add0(methodInfo, true, mergeSession);
	}
	
	// Add every field
	for(int i = 0; i < clinfo.fields.size(); i++) {
	  fieldInfo = (FieldInfo) clinfo.fields.elementAt(i);
	  add0(fieldInfo, mergeSession);
	}
	
	// Add every interface 
	for(int i = 0; i < clinfo.interfaces.size(); i++) {
	  add0((InterfaceInfo) clinfo.interfaces.elementAt(i), 
	       mergeSession);
	}
      }
    
    // Re-emit the bytes from component parts - or in the minimal necessary
    // change kind of a way
    getBytes(true);  
  } 
  
  
  /** Merge another ClassInfo object into this one.  If successful
   *  this operation will desctructively change this class.  
   * 
   * @exception  ClassException
   *         A failure during merging into this ClassInfo object.
   */
  
  public void merge(ClassInfo clinfo) 
       throws ClassException
  {
    merge(new MergeSession(new ClassInfo[] {clinfo},
    MergeSession.MERGE_REPLACE_ON_CONFLICT));
  }
  
  /** Emit the bytes for this class, bind the result to bytes
   */
  public void emit() {
    
    // New output stream is by default the size of the original one if we have one,
    // Otherwize make it some reasonable large size that is the default for ClassOutput
    ClassOutput newclass;	
    MethodInfo methodInfo;
    if(bytes == null) 
      newclass = new ClassOutput();
    else newclass = new ClassOutput(bytes.length);
    
    try {
      
      // For each field collect all static initialization expressions
      // in a block
      Block block = new Block();
      FieldInfo fieldInfo;

      if (fields != null) 
	for (int i = 0; i < fields.size(); i++)
      {
        fieldInfo = (FieldInfo) fields.elementAt(i);
	  if (fieldInfo.getAccess().isStatic() &&
            (fieldInfo.getInitialValue() != null)) 
            block.add((Call) ((FieldInfo) fields.elementAt(i)).getInitialValue());
      }
      
      // If there are multiple "<clinit>" methods then collect these
      // in the same block
      Block contents;
      
      if (!bufferedClinits.isEmpty())
      {
        if (methods != null) 
	  for (int i = 0; i < methods.size(); i++) { 
	    methodInfo = (MethodInfo) methods.elementAt(i);
	    if (methodInfo.name.equals("<clinit>"))
             if ((contents = methodInfo.getContents()) == null)
	       { 
		 if (! methodInfo.normalized)
		   {
		     methodInfo.normalize(); 
             }
		 block.add(new InlineMethodCall(methodInfo, null));
	       }
	     else block.add(contents);
	  }
	
        for (int i = 0; i < bufferedClinits.size(); i++)
	  {
	    methodInfo = (MethodInfo) bufferedClinits.elementAt(i);
	    if (methodInfo.name.equals("<clinit>"))
	      {
		if ((contents = methodInfo.getContents()) == null)
		  {
		    if (! methodInfo.normalized)
		      {
			methodInfo.normalize();
		      }
		    block.add(new InlineMethodCall(methodInfo, null));
		  }
		else block.add(contents);
	      }
	  }
      }
      bufferedClinits.setSize(0);
      
      if (! block.isEmpty()) {
	block.add(new Return());
	
	// Create a Method with the results.
	methodInfo = new MethodInfo(new Access(ACC_STATIC),
				    new MethodRef(className,"<clinit>","()V"),
				    block,
				    false);

	add0(methodInfo,false, replaceMergeSession);
      }
      
      // Emit magic_number
      newclass.out.writeInt(magic_number);
      
      // Emit minor_version
      newclass.out.writeShort(minor_version);
      
      // Emit major_version
      newclass.out.writeShort(major_version);
      
      // Emit the constant pool *
      constantPool.emit(newclass.out);

      // Emit the access_flags
      access.emit(newclass.out);
      
      // Emit this class
      newclass.out.writeShort(classIndex);

      // Emit the superclass
      newclass.out.writeShort(superIndex);

      // Emit the interfaces *
      // Consider having interfaces as separate class with normalization/localization
      // protocol
      if(trace)
	System.out.println("Emitting Interfaces" + interfaces);
      InterfaceInfo.emit(interfaces,newclass.out);
      
      if (trace)
	System.out.println("Emitting " + fields);
      // Emit the fields *
      FieldInfo.emit(fields,newclass.out);
      
      // Emit the methods *
      MethodInfo.emit(methods,newclass.out);
      
      // Emit the attributes *  
      if (trace)
	System.out.println("Emitting " + attributes);
      Attribute.emit(attributes,newclass.out);
      
    }
    catch (IOException e) {
      System.out.println("Failure during emit. " + e.getMessage());
      e.printStackTrace();
    }catch (ClassException e) {
      System.out.println("Failure during emit. " + e.getMessage());
      e.printStackTrace();
    }catch (RuntimeException e) {
      System.out.println("Failure during emit. " + e.getMessage());
      e.printStackTrace();
    }
    
    // Get the buffer from the stream and assign them to bytes
    bytes = new byte[newclass.bytes.size()];

    System.arraycopy(newclass.bytes.toByteArray(),0,bytes,0,newclass.bytes.size());
    
    // If we can successfully emit the class we assume that it is valid
    isValidClass = true;
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
  
  private void readInput(InputStream dataIn) throws IOException
  {
    int bufferSize = 2048;
    byte[] input = new byte[bufferSize];
    
    int inputUsed = 0, n;
    while((n = dataIn.read(input, inputUsed, input.length - inputUsed)) >= 0)
      {
	inputUsed += n;
	if(inputUsed == input.length) {
	  byte newinput[] = new byte[inputUsed + bufferSize];
	  System.arraycopy(input, 0, newinput, 0, inputUsed);
	  input = newinput;
	}
      }
    byte newinput[] = new byte[inputUsed];
    System.arraycopy(input, 0, newinput, 0, inputUsed);
    bytes = newinput;
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
    
    int offset = 10;
    
    int constantPoolCount;
    
    try {
      constantPoolCount = readU2(8);
      constantPool = new ConstantPool(constantPoolCount);
      offset = Constant.fillConstantPool(constantPool,bytes,offset,constantPoolCount);
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
    
    try {
      classIndex = readU2(offset);
      if (constantPool.getPool(classIndex) == null ||
	  constantPool.getPool(classIndex).getType() != CONSTANT_CLASS)
	throw new ClassException("thisClass record corrupt: " + offset + " Index " + classIndex);
      if (trace)
        System.out.println("Class Name Index = " + classIndex);
      className = constantPool.getPool(classIndex).getClassName();
      offset += 2;
    }
    catch (ArrayIndexOutOfBoundsException e) {
      throw new ClassException("thisClass record corrupt: " + offset + " Index " + classIndex);
    }
    if (trace)
      System.out.println("Class Name Index: " + classIndex);
    
    // super class name
    
    superName = OBJECT_STR;
    try {
      superIndex = readU2(offset);
      if (superIndex != 0 && 
	  (constantPool.getPool(superIndex) == null ||
	   constantPool.getPool(superIndex).getType() != CONSTANT_CLASS))
	throw new ClassException("superClass record corrupt: " + offset);
      
      if (superIndex != 0)
	superName = constantPool.getPool(superIndex).getClassName();
      offset += 2;
    }
    catch(ArrayIndexOutOfBoundsException e) {
      throw new ClassException("superClass record corrupt: " + offset);
    }
    
    if (trace)
      System.out.println("cname ="+className+" super= "+superName);
    
    // interfaces
    
    try {
      int interfaceCount = readU2(offset);
      offset += 2;
      interfaces = new Vector();
      if(interfaceCount > 0) {
	for(int i = 0; i < interfaceCount; i++) {
	  int index = readU2(offset);
	  Constant constant = constantPool.getPool(index);
	  if(constant != null && constant.getType() == CONSTANT_CLASS)
	    {
	      interfaces.addElement(new InterfaceInfo(index,constantPool));
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
      if(fieldCount > 0) {
	for(int i = 0; i < fieldCount; i++) 
	  {
	    fields.addElement(new FieldInfo(readU2(offset),  // Acceess
					    constantPool,
					    readU2(offset+2), // name index
					    readU2(offset+4))); // descriptor index
	    int attributeCount = readU2(offset+6);
	    if (trace)
	      System.out.println("Read Attributes :" + attributeCount);
	    offset += 8;
	    Vector tempAttributes = new Vector(attributeCount);
	    for (int j = 0 ; j<attributeCount ; j++)
	      {
		tempAttributes.addElement(Attribute.readAttribute(constantPool,bytes,offset));
	      offset += (((Attribute) tempAttributes.elementAt(j)).length + 6);
	      }
	    ((FieldInfo) fields.elementAt(i)).attributes = tempAttributes; 
	  }
      }
    } catch(ArrayIndexOutOfBoundsException e) {
      throw new ClassException("Field record corrupt: " + offset);
    }
    
    
    // methods
    
    try {
      int methodCount = readU2(offset);
      offset += 2;
      methods = new Vector();
      if(methodCount > 0) {
	MethodInfo method;
	for(int i = 0; i < methodCount; i++) 
	  {
	    //Should do all this work in MethodInfo() itself.
	    method = new MethodInfo(readU2(offset),  // Access
				    constantPool,
				    readU2(offset+2), // name index
				    readU2(offset+4)); // descriptor index
	    
	    methods.addElement(method);
	    int attributeCount = readU2(offset+6);
	    offset += 8;
	    Vector tempAttributes = new Vector(attributeCount);
	    for (int j = 0 ; j<attributeCount ; j++)
	      {
		tempAttributes.addElement(Attribute.readAttribute(constantPool,bytes,offset));
		offset += (((Attribute) tempAttributes.elementAt(j)).length + 6);
	      }
	    ((MethodInfo) methods.elementAt(i)).attributes = tempAttributes;
	    ((MethodInfo) methods.elementAt(i)).setClassName(getClassName());
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
  
  // Command line interface.
  
  private static final void reportUsage() {
    System.out.println("usage: java ClassInfo [report <classfile> ... | merge <classfile1> <classfile2> <outputfile>]");
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
	if (args.length < 4) 
	  reportUsage();
	FileInputStream fileStream = new FileInputStream(args[1]);
	classInfo = new ClassInfo(fileStream);
	fileStream.close();
	
	fileStream = new FileInputStream(args[2]);
	classInfo2 = new ClassInfo(fileStream);
	fileStream.close();
	
	for(int i = 1; i < classInfo2.methods.size(); i++) {
	  ((MethodInfo) classInfo2.methods.elementAt(i)).normalize();
	}
	classInfo.merge(classInfo2);

	FileOutputStream fileOutStream = new FileOutputStream(args[3]);
	fileOutStream.write(classInfo.getBytes(true));
	fileOutStream.close();

	fileStream = new FileInputStream(args[3]);
	classInfo3 = new ClassInfo(fileStream);
	fileStream.close();
      } 
    }
    catch (Exception e)
      {
	System.out.println("ClassInfo operation failed");
	e.printStackTrace();
      }
  }
}
