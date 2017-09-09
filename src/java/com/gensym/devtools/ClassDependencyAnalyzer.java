
package com.gensym.devtools;

import java.io.InputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.Vector;
import com.gensym.classtools.*;

public class ClassDependencyAnalyzer implements RuntimeConstants {

  private String className;

  private static final String[]
  CONSTANT_TYPES = {"UNDEFINED!",
		    "UTF8",
		    "UNICODE",
		    "INTEGER",
		    "FLOAT",
		    "LONG",
		    "DOUBLE",
		    "CLASS",
		    "STRING",
		    "FIELD_REF",
		    "METHOD_REF",
		    "INERFACE_METHOD_REF",
		    "NAME_AND_TYPE"};

  public static void main (String[] args) throws Exception {
    InputStream in;
    ClassDependencyAnalyzer cda =
      new ClassDependencyAnalyzer (in = new FileInputStream (args[0]));
    // spew out info
    in.close ();
  }

  public ClassDependencyAnalyzer (File root, // directory or jar (NYI)
				  String pkgName,
				  String simpleClassName) throws FileNotFoundException, Exception
  {
    className = pkgName + '.' + simpleClassName;
    InputStream in;
    if (root.isDirectory()) {
      String classFileName =
	root.toString() + File.separatorChar +
	pkgName.replace ('.', File.separatorChar) + File.separatorChar +
	simpleClassName + ".class";
      init (in = new FileInputStream (classFileName));
      in.close();
    } else {
      // write jar case
    }
  }

  public ClassDependencyAnalyzer (InputStream in) throws Exception {
    init (in);
  }

  private Vector types = new Vector();

  private void init (InputStream in) throws Exception {
    ClassInfo ci = new ClassInfo (in);
    className = ci.getClassName();
    ConstantPool cp = ci.getConstantPool();
    //cp.toStdout ();
    Constant[] constants = cp.getPool();
    int constantSize;
    for (int i=1; i<constants.length; i+=constantSize) {
      Constant c = constants[i];
      int type = constants[i].getType();
      constantSize = c.getSlots();
      //System.out.println ("#" + i + " Constant = " + c + "[Size=" + constantSize + "]");
      if (type == CONSTANT_CLASS) {
	String typeName = getTypeFromDescriptor (constants[i].getClassName(), true);
	//System.out.println ("########" + typeName);
	addClassDependency(typeName);
      } else if (type == CONSTANT_FIELD_REF) {
	int classIndex = c.getRawData1();
	int nameAndTypeIndex = c.getRawData2();
	//System.out.println ("########" + constants[classIndex].getClassName());
	addClassDependency(constants[classIndex].getClassName());
	Constant nameType = constants[nameAndTypeIndex];
	int descriptorIndex = nameType.getRawData2();
	//System.out.println ("########" + className);
	addClassDependency (getTypeFromDescriptor (constants[descriptorIndex].getUTF8String(), false));
      } else if (type == CONSTANT_METHOD_REF ||
		 type == CONSTANT_INTERFACE_METHOD_REF) {
	int classIndex = c.getRawData1();
	int nameAndTypeIndex = c.getRawData2();
	//System.out.println ("########" + className);
	addClassDependency (constants[classIndex].getClassName());
	Constant nameType = constants[nameAndTypeIndex];
	int descriptorIndex = nameType.getRawData2();
	String descriptor = constants[descriptorIndex].getUTF8String();
	descriptor = stripMethodChars(descriptor);
	String[] classNames = getTypesFromDescriptor(descriptor);
	//System.out.println ("########" + com.gensym.core.DebugUtil.printArray(classNames));
	addClassDependencies (classNames);
      }	
    }
    FieldInfo[] fields =ci.getFields();
    for (int i=0; i<fields.length; i++) {
      String descriptor = fields[i].getDescriptor();
      //System.out.println ("Field: Type = " + getTypeFromDescriptor(descriptor));
      addClassDependency(getTypeFromDescriptor(descriptor, false));
    }
    MethodInfo[] methods = ci.getMethods ();
    for (int i=0; i<methods.length; i++) {
      String descriptor = methods[i].getDescriptor();
      descriptor = stripMethodChars(descriptor);
      //System.out.println ("Method Type = " + 
      //		  com.gensym.core.DebugUtil.printArray(getTypesFromDescriptor(descriptor)));
      addClassDependencies(getTypesFromDescriptor(descriptor));
    }
  }

  private static String getTypeFromDescriptor (String descriptor, boolean allowUnadornedClassName) {
    char descChar = descriptor.charAt (0);
    if (descriptor.length() == 1) {
      switch (descChar)
	{
	case 'B':
	case 'C':
	case 'D':
	case 'F':
	case 'I':
	case 'J':
	case 'S':
	case 'Z':
	  return descriptor;
	default:
	  throw new RuntimeException ("Unknown type - " + descriptor);
	}
    } else {
      if (descChar == '[')
	return getTypeFromDescriptor (descriptor.substring(1), allowUnadornedClassName);
      else {
	if (descChar != 'L') {
	  if (allowUnadornedClassName)
	    return descriptor;
	  else
	    throw new RuntimeException ("Cannot parse descriptor - " + descriptor);
	}
	int terminalIndex = descriptor.indexOf (';');
	if (terminalIndex != descriptor.length() - 1)
	  throw new RuntimeException ("Malformed descriptor - " + descriptor);
	return descriptor.substring (1, descriptor.length()-1);
      }
    }
  }

  private static String[] getTypesFromDescriptor (String descriptor) {
    int index = 0;
    int descriptorLength = descriptor.length();
    Vector classNames = new Vector ();
  parseLoop: 
    while (index < descriptorLength) {
      char descChar = descriptor.charAt (index);
      
      boolean isValidChar = descChar == 'B' || descChar == 'C' || descChar == 'D' ;
	  isValidChar = isValidChar || descChar == 'F' || descChar == 'I' || descChar == 'J' ;
	  isValidChar = isValidChar || descChar == 'S' || descChar == 'Z' || descChar == 'V' ;
      
	  if (isValidChar) {
		  index++;
		  continue parseLoop;
	  }
	  
	  if (descChar == '[') {
		  index++;
		  continue;
      }
      if (descChar == 'L') {
	int terminalIndex = descriptor.indexOf (';', index);
	String className = descriptor.substring (index + 1, terminalIndex);
	if (!classNames.contains(className))
	  classNames.addElement (className);
	index = terminalIndex+1;
      }
    }
    //System.out.println ("Parse: <" + descriptor + "> = " + types);
    return (String[]) classNames.toArray (new String[classNames.size()]);
  }

  private static String stripMethodChars (String descriptor) {
    int openParenIndex = descriptor.indexOf ('(');
    int closeParenIndex = descriptor.indexOf (')');
    StringBuffer sb = new StringBuffer (descriptor);
    return sb.delete(closeParenIndex, closeParenIndex+1).delete (openParenIndex, openParenIndex+1).toString ();
  }

  private void addClassDependency (final String typeName) {
    String dependency = typeName;
	if (dependency.length() == 1)
      return;
	dependency = dependency.replace('/','.');
    if (!types.contains(dependency)) {
      types.addElement(dependency);
      //System.out.println ("++++<" + typeName + ">");
    }
  }

  private void addClassDependencies (String[] classNames) {
    for (int i=0; i<classNames.length; i++)
      addClassDependency (classNames[i]);
  }

  public String[] getRequiredClassNames () {
    //System.out.println ("Class " + className + " -----> " + types);
    return (String[])types.toArray(new String[types.size()]);
  }

}
