package com.gensym.classtools;

import java.util.StringTokenizer;
import java.util.Vector;
import java.util.Enumeration;
import java.util.Hashtable;

/**
 * Type is used for to define the type of an expression
 */
public class Type implements RuntimeConstants {
  private int typeFlags;
  private int arrayDimensions;
  // Note that while this string calls itself a class name, it is actually
  // a class descriptor for the "base class" of this type. That is, if
  // the class is an array type, this is the ultimate element type. This
  // is null if this is a primitive type, or an array of a primitive type.
  String className;
  private Vector argumentTypes;
  private boolean simple = true;
  boolean interned = false;
  private static volatile Hashtable internedTypes = new Hashtable();
  private static final boolean trace = false;


  //************** Constructors **************

  public Type(int type) {
    typeFlags = type;
    addNumericFlags();
  }

  Type(int type, Vector args, String className, int dimensions) {	
    // System.out.println("Creating new type; args are " + type + ", " + args + ", " + className  + ", and " + dimensions);
    typeFlags = type;
    argumentTypes = args;
    this.className = className;
    arrayDimensions = dimensions;
    addNumericFlags();
    if (args != null)
      simple = false;
  }


  // temporary; for debugging only.
  public String getClassName() {
    return className;
  }

  private void addNumericFlags() {
    if (isIntegerBasedType() || isShortBasedType() || isByteBasedType() || isCharBasedType())
      typeFlags |= (T_INTEGRAL | T_NUMERIC | T_SMALL_INTEGRAL);
    else if (isBooleanBasedType())
      typeFlags |= (T_INTEGRAL | T_SMALL_INTEGRAL);
    else if (isDoubleBasedType() || isFloatBasedType())
      typeFlags |= T_NUMERIC;
    else if (isLongBasedType())
      typeFlags |= (T_INTEGRAL | T_NUMERIC);
  }

  //***************** Predicates ***********************

  // NB isIntegerType() means only an integer type.
  // isIntegerBasedType() includes arrays of (arrays of...) integer types.
  // These concepts were previously confounded, and both called
  // isIntegerType. This predicate name is no longer used, to avoid confusion.
  // Similarly for all the other IsFooType predicates.

  public boolean isIntegerBasedType() {
    return ((typeFlags & T_INT) > 0);
  }

  public boolean isShortBasedType() {
    return ((typeFlags & T_SHORT) > 0);
  }

  public boolean isBooleanBasedType() {
    return ((typeFlags & T_BOOLEAN) > 0);
  }

  public boolean isByteBasedType() {
    return ((typeFlags & T_BYTE) > 0);
  }

  public boolean isFloatBasedType() {
    return ((typeFlags & T_FLOAT) > 0);
  }

  public boolean isDoubleBasedType() {
    return ((typeFlags & T_DOUBLE) > 0);
  }

  public boolean isCharBasedType() {
    return ((typeFlags & T_CHAR) > 0);
  }

  public boolean isVoidBasedType() {
    return ((typeFlags & T_VOID) > 0);
  }

  public boolean isLongBasedType() {
    return ((typeFlags & T_LONG) > 0);
  }

  public boolean isArrayBasedType() {
    return ((typeFlags & T_ARRAY) > 0);
  }

  public boolean isJavaLangObjectBasedType() {
    return (((typeFlags & T_CLASS) > 0) &&
	    className.equals(OBJECT_DESC));
  }

  public boolean isClassBasedType() {
    return ((typeFlags & T_CLASS) > 0);
  }

  public int getArrayDimensions() {
    return arrayDimensions;
  }

  // Note; getArrayElementType on [[I returns [I;
  //  getArrayBaseElementType on [[I returns I.

  public Type getArrayElementType() throws ClassException {
    // System.out.println("Creating new type in getArrayElementType");
    if (!isArrayType())
      throw new ClassException("Not an array type");
    if (arrayDimensions == 1) {
      if (isClassBasedType()) {
	return Type.parseType(className);
      }
      else return new Type(typeFlags ^ T_ARRAY);
    } else {
      return new Type(typeFlags, argumentTypes, className, arrayDimensions - 1);	 
    }
  }

  public Type getArrayBaseElementType() throws ClassException {
    // System.out.println("Creating new type in getArrayBaseElementType");
    if (! isArrayType())
      throw new ClassException("Not an array type");
    else {
      if (isClassBasedType()) {
	return Type.parseType(className);
      }
      else return new Type(typeFlags ^ T_ARRAY);
    }
  }



  public boolean isIntegralBasedType() {
    return
      ((typeFlags & T_INTEGRAL) > 0);
  }

  public boolean isSmallIntegralBasedType() {
    return ((typeFlags & T_SMALL_INTEGRAL) > 0);
  }

  public boolean isNumericBasedType() {
    return
      ((typeFlags & T_NUMERIC) > 0);
  }


  // Predicates for the combo-types that are often allowable arguments to expressions 
  private boolean isAnyBasedType() {
    return
      ((typeFlags & T_ANY) > 0);
  }

  private boolean isSpecificallyIntegral() {
    return
      ((typeFlags ^ T_INTEGRAL) == 0);
  }

  private boolean isSpecificallyNumeric() {
    return
      ((typeFlags ^ T_NUMERIC) == 0);
  }


  public boolean isIntegerType() {
    return ((typeFlags & T_INT) > 0 && ((typeFlags & T_ARRAY) == 0));
  }

  public boolean isShortType() {
    return ((typeFlags & T_SHORT) > 0) && ((typeFlags & T_ARRAY) == 0);
  }

  public boolean isBooleanType() {
    return ((typeFlags & T_BOOLEAN) > 0) && ((typeFlags & T_ARRAY) == 0);
  }

  public boolean isByteType() {
    return ((typeFlags & T_BYTE) > 0) && ((typeFlags & T_ARRAY) == 0);
  }

  public boolean isFloatType() {
    return ((typeFlags & T_FLOAT) > 0) && ((typeFlags & T_ARRAY) == 0);
  }

  public boolean isDoubleType() {
    return ((typeFlags & T_DOUBLE) > 0) && ((typeFlags & T_ARRAY) == 0);
  }

  public boolean isCharType() {
    return ((typeFlags & T_CHAR) > 0) && ((typeFlags & T_ARRAY) == 0);
  }

  public boolean isVoidType() {
    return ((typeFlags & T_VOID) > 0) && ((typeFlags & T_ARRAY) == 0);
  }

  public boolean isLongType() {
    return ((typeFlags & T_LONG) > 0) && ((typeFlags & T_ARRAY) == 0);
  }

  public boolean isArrayType() {
    return ((typeFlags & T_ARRAY) > 0);
  }

  public boolean isJavaLangObjectType() {
    return (((typeFlags & T_CLASS) > 0)
	    && (className.equals(OBJECT_DESC))
	    && ((typeFlags & T_ARRAY) == 0));
  }

  public boolean isClassType() {
    return ((typeFlags & T_CLASS) > 0) && ((typeFlags & T_ARRAY) == 0);
  }

  public boolean isReferenceType() {
    return ((typeFlags & T_CLASS) > 0) || ((typeFlags & T_ARRAY) > 0);
  }

  public boolean isSimpleType() {
    return simple;
  }

  public boolean isIntegralType() {
    return
      ((typeFlags & T_INTEGRAL) > 0) && ((typeFlags & T_ARRAY) == 0);
  }

  public boolean isSmallIntegralType() {
    return ((typeFlags & T_SMALL_INTEGRAL) > 0);
  }

  public boolean isNumericType() {
    return
      ((typeFlags & T_NUMERIC) > 0) && ((typeFlags & T_ARRAY) == 0);
  }

  // Predicates for the combo-types that are often allowable arguments to expressions 
  private boolean isAnyType() {
    return
      ((typeFlags & T_ANY) > 0) && ((typeFlags & T_ARRAY) == 0);
  }


  //******* Get method on type information ********
	
  public int getReturnType() {
    return typeFlags;
  }

  public Type[] getArgumentTypes() {
    if (argumentTypes != null) {
      Object[] argts = new Type[argumentTypes.size()];
      argumentTypes.copyInto(argts);
      return (Type[]) argts;
    }
    else  {
      return null;
    }
  }


  //***** Returning as a String **************

  @Override
  public String toString() {
    if (simple) 			
      return getReturnTypeString();
    else return "(" + argsToString(argumentTypes) + ")" + getReturnTypeString();
  }

  private String argsToString(Vector v) {
    StringBuffer buf = new StringBuffer(30);
    for (int i = 0; i < v.size(); i++)
      buf.append(v.elementAt(i));
    return buf.toString();
  }

  /*
  public String oldfangled_getReturnTypeString() {
    if (className != null)
      return className;
    else {
      if (isArrayType()) {
 	StringBuffer buf = new StringBuffer();
 	for (int i = 0; i < arrayDimensions; i++)
 	  buf.append(SIG_ARRAY);
 	buf.append(typeFlagsToString());
 	return buf.toString();
      }
      else return typeFlagsToString();
    }
  }
  */ 

  public String getReturnTypeString() {
    if (isArrayType()) {
      StringBuffer buf = new StringBuffer();	
      for (int i = 0; i < arrayDimensions; i++)
	buf.append(SIG_ARRAY);
      if (className != null)
	buf.append(className);
      else
	buf.append(typeFlagsToString());
      return buf.toString(); 
    } else {
      if (className != null)
	return className;
      else {
	return typeFlagsToString();
      }
    }
  }

  private String typeFlagsToString() {
    if (isIntegerBasedType())
      return SIG_INT;
    if (isFloatBasedType())
      return SIG_FLOAT;
    if (isBooleanBasedType())
      return SIG_BOOLEAN;
    if (isShortBasedType())
      return SIG_SHORT;
    if (isByteBasedType())
      return SIG_BYTE;
    if (isCharBasedType())
      return SIG_CHAR;
    if (isDoubleBasedType())
      return SIG_DOUBLE;
    if (isFloatBasedType())
      return SIG_FLOAT;
    if (isLongBasedType())
      return SIG_LONG;
    if (isVoidBasedType())
      return SIG_VOID;
    if (isSpecificallyNumeric())
      return "<Numerical Type>";
    if (isSpecificallyIntegral())
      return "<Integral Type>";
    if (isAnyBasedType())
      return "<Any Type>";
    return "<Internal type>";
  }


  // *************  Operation on One type *************


  @Override
  public Object clone() {
    // System.out.println("Creating new type in clone");
    return new Type(typeFlags, argumentTypes, className, arrayDimensions);	 
  }

  //********** Boolean Predicates on Two types *********************

  /**
   * Test if the return type of two types are the same.  
   */
  @Override
  public boolean equals(Object obj) {
	if(obj == null || !Type.class.equals(obj.getClass())){
		return false;
	}
	
	Type tpe = (Type) obj; 
    // System.out.println("Comparing " + this + " and " + tpe);
	  boolean areInterned = interned && tpe.interned;
	  boolean areSimpleType = isSimpleType() && tpe.isSimpleType();
	  boolean areNotArrayType = !(isArrayType() || tpe.isArrayType());
    if (areInterned && areSimpleType && areNotArrayType) {
      // System.out.println("Using == test; returning " + (this == tpe));
      return this == tpe;
    }
    if (typeFlags != tpe.getReturnType()) {
      // System.out.println("Type flags don't match; returning false");
      return false;
    }
    if (isArrayType()) {
      if (!tpe.isArrayType() || arrayDimensions != tpe.getArrayDimensions()) {
	// System.out.println("Arrayness doesn't match; returning false");
		    
	return false;
      }
    } else {
      if (tpe.isArrayType()) {
	// System.out.println("Arrayness doesn't match; returning false");
	return false;
      }
    }
    if (className == null) {
      if (tpe.className == null) {
	return true;
      } else { 
	return false;
      }
    } else {
      if (tpe.className == null) {
	return false;
      } else {
	return className.equals(tpe.className);
      }
    }
  }
  
	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result + arrayDimensions;
		result = prime * result + ((className == null) ? 0 : className.hashCode());
		result = prime * result + (interned ? 1231 : 1237);
		result = prime * result + (simple ? 1231 : 1237);
		result = prime * result + typeFlags;
		return result;
	}

  // Denigrated - used only in OperatorCall type checking, may want to use
  // something else there as well
  boolean potentialSubType(Type tpe) 
  {
	boolean arrayTypeCheck = isArrayType() ? arrayDimensions == tpe.getArrayDimensions() : true;
	boolean classTypeCheck = isClassBasedType() ? potentialSubType1(tpe.className,0) : true;
	
	boolean isClassType = typeFlags  == tpe.getReturnType() && arrayTypeCheck && classTypeCheck;
    boolean numericTypeCheck = isSpecificallyNumeric() && tpe.isNumericType();
    boolean integerTypeCheck = isSpecificallyIntegral() && tpe.isIntegralType();
	
    return isAnyType() || numericTypeCheck || integerTypeCheck || isClassType;
  }
  
  
  /**
   * Check if an expression is assignment compatable with this type.
   * Note that this predicate requires access to the node because there is a special rule 
   * surrounding whether the expression being assigned is a constant integer of a certain
   * size.  See "The Java Virtual Machine Specification" pages 17 and 18 for a full discussion
   * of assignment conversion.
   */
  public boolean potentialAssignmentConversion(Expression exp) {
    Type tpe = exp.getExpressionType();
    if (isArrayType()) {
      if (tpe.isArrayType() && arrayDimensions == tpe.getArrayDimensions()){
		  if (isClassBasedType()){
		    return potentialSubType1(tpe.className,0);
		  } else {
			return (! requiresNarrowingPrimitiveConversion(tpe));
		  }
      }
      return false;
    }
    
    if (isClassType()) {
      if (tpe.isClassType()) {
    	  return !requiresNarrowingReferenceConversion(exp);
      } else {
    	  return tpe.isArrayType() && isJavaLangObjectType();
      }
    }
    
    if (requiresNarrowingPrimitiveConversion(tpe)) {
      boolean isPremitiveType = isShortType() || isByteType() || isCharType();
      return isPremitiveType && tpe.isIntegerType() 
    		  && (exp instanceof Value && ((Value) exp).canFitInSingleByte());
    }
  
    return true;			
  }

  public boolean potentialMethodArgumentConversion(Expression exp) { 
    return potentialMethodArgumentConversion(exp, exp.getExpressionType());
  }

  public boolean potentialMethodArgumentConversion(Type tpe) { 
    return potentialMethodArgumentConversion(null, tpe);
  }
   

  private boolean potentialMethodArgumentConversion(Expression e, Type tpe)
  {
    if (isArrayType())
      if (tpe.isArrayType())
	if (arrayDimensions == tpe.getArrayDimensions())
	  if (isClassBasedType())
	    if (e == null)
	      return (! requiresNarrowingReferenceConversion(tpe));
	    else return (! requiresNarrowingReferenceConversion(e));
	  else return (! requiresNarrowingPrimitiveConversion(tpe));
	else return false;
      else return false;
    if (isClassType())
      if (tpe.isClassType())
        if (e == null)
          return (! requiresNarrowingReferenceConversion(tpe));
        else return (! requiresNarrowingReferenceConversion(e));
      else if (isJavaLangObjectType() && tpe.isArrayType())
	return true;
      else
	return false;
    if (requiresNarrowingPrimitiveConversion(tpe)) 
      return false;
    return true;
  }
    
  // pp15-16
  boolean requiresNarrowingPrimitiveConversion(Type tpe) {
	boolean isNumber = isShortType() || isIntegerType() || isFloatType();
    if (tpe.isIntegerType()) {
      return (isByteType() || isShortType() || isCharType());
    }
    if (tpe.isByteType()){
      return isCharType();
    }
    if (tpe.isLongType()){
      return (isByteType() || isShortType() || isCharType() || isIntegerType());
    }
    if (tpe.isDoubleType()) {
      return isByteType() || isCharType() || isNumber;
    }
    if (tpe.isShortType()) {
      return isByteType() || isCharType();
    }
    if (tpe.isFloatType()) {
      return isByteType() || isShortType() || isCharType() || isIntegerType();
    }
    return false;
  }


  boolean requiresNarrowingReferenceConversion(Expression exp) {	
    if (exp instanceof Value) {
      Value val = (Value) exp;
      if (val.isNull())
	return false;
    }
    return requiresNarrowingReferenceConversion(exp.getExpressionType());
  }

  boolean requiresNarrowingReferenceConversion(Type tpe) {	
    return (! potentialSubType1(tpe.getReturnTypeString(),0));
  }
  
  private boolean potentialSubType1(String st, int index) {	
    char c1,c2;
    String type = className;

    // Classes without names match with everything, like
    // wildcards. 
    if ((type == null) || (st == null))
      return true;
    
    if (st.equals(type))
      return true;
    if ((c1 = st.charAt(index)) != (c2 = type.charAt(index))) {
      return false;
    }
    
    // Note we already know that these are in valid syntax
    switch (c1) {
    case SIGC_CLASS: {
      /* classtools should never use information from the VM when evaluating
       * class types.  Class type checking is the responsibility of any facility
       * that uses classtools.
       */
      return true;
    }
    // This is complete garbage; to decide whether [X is a subtype of [Y,
    // we should be seeing if [X is a subtype of [Y; instead, we are checking
    // whether X is a subtype of [Y. Of course, the fundamental brokenness
    // is that we are converting Type objects back into strings and doing
    // string manipulation on them. Why???
    case SIGC_ARRAY: {
      // Remove the [[ at the front then call potentialSubType recursively
      for(int i = 1; (i < st.length()) && (i < type.length()); i++) {
		char ch = st.charAt(i);
		if (!((ch == type.charAt(i)) && (ch == SIGC_ARRAY))) 
		  return potentialSubType1(st,i + 1);
		else 
		  return false;
      }
      return false;
    }
    default: 
      return false;
    }
  }
  
  private static boolean subClass(Class c1,Class c2) {
    return c1.isAssignableFrom(c2);
  }
  
  // ******* Parsing a Type from a descriptor string **************
  
  public static Type parseType(final String desc) 
      throws ClassException
  {
	String descriptor = desc;  
    if (descriptor == null)
      throw new ClassException("Invalid type description " + descriptor);
    descriptor = canonicalizePackageSeparators(descriptor);
    // System.out.println("Looking for Interned type for " + desc);
    Object cachedType = getInterned(descriptor);
    if(cachedType != null) {
      // System.out.println("Interned type found");
      return (Type) cachedType;
    }
    Type newType;
    // Check to see if it is a simple type (not a method or array type)
    if((descriptor.indexOf("(") == -1))
      {
	newType = parseType1(descriptor,0,null);  
	intern(descriptor,newType);
	return newType;
      }
    else {
      String returnType;
      Vector v = new Vector();
      if(descriptor.indexOf(")") == 1) {
	returnType = descriptor.substring(2);
	newType = parseType1(returnType,0,v);
	return newType; 
      }
      StringTokenizer stok = new StringTokenizer(descriptor,"()");
      String first = stok.nextToken();
      parseType2(first,v);
      return parseType1(stok.nextToken(),0,v);
    }
  }
  
  private static Type parseType1(final String tp, final int index, final Vector v) throws ClassException
  {
	int indexLocal = index;
    int flags = 0;
    int dimensions = 0;
    String classNameIfAny = null;
    Type returnTypeForComplex = null;
    // System.out.println("Parsetype1 called on " + tp);
    while (true) {
      if (tp.length() > indexLocal) 
	{
	  char ch = tp.charAt(indexLocal);
	  if (SIG_SIMPLE_TYPES.indexOf(ch) != -1) {
	    if(indexLocal != (tp.length() -1)) 
	      throw new ClassException("Invalid format for simple type: " + tp);    
	    else
	      {
		flags |= decodeTypeChar(ch);
	      }
	    break;
	  }
	  else {
	    if (ch == SIGC_ARRAY) {
	      indexLocal++;
	      dimensions++;
	      flags |= T_ARRAY;
	    }	 
	    else { 
	      if (ch == SIGC_CLASS) {
		classNameIfAny = parseClassReference(tp.substring(indexLocal),true);
		flags |= T_CLASS;
		break;
	      }
	      else throw new ClassException("Descriptor format is corrupt: " + tp);
	    }
	  }
	} 
      else throw new ClassException("Descriptor format is corrupt" + tp);
    }
    // System.out.println("Creating new type in parsetype1");
    Type newType = new Type(flags,v,classNameIfAny,dimensions); 
    /* 
       System.out.println("Returning new Type " + newType);
       if ((flags & T_ARRAY) > 0)
       System.out.println("  which is an array type.");
       else
       System.out.println("  which is not an array type.");
       */

    return newType;
  }
  
  
  private static int decodeTypeChar (char ch) {
    switch (ch) {
    case SIGC_VOID:
      return T_VOID;
    case SIGC_BOOLEAN:
      return T_BOOLEAN;
    case SIGC_BYTE:
      return T_BYTE;
    case SIGC_CHAR:
      return T_CHAR;
    case SIGC_SHORT:
      return T_SHORT;
    case SIGC_INT:
      return T_INT;
    case SIGC_LONG:
      return T_LONG;
    case SIGC_FLOAT:
      return T_FLOAT;
    case SIGC_DOUBLE:
      return T_DOUBLE;
    default: return 0;
    }
  }
  
  private static void parseType2(String tp, Vector v)
      throws ClassException
  {	
    char[] chars = tp.toCharArray();
    char ch;
    for (int i = 0; i < chars.length; i++) {
      ch = chars[i];
      if (SIG_SIMPLE_ARG_TYPES.indexOf(ch) != -1) 
	v.addElement(parseType1(new String(chars,i, 1),0, null));
      else
	if (ch == SIGC_ARRAY) {
	  int before = i;
	  i = parseArrayType(chars,v,i);
	}
	else
	  if (ch == SIGC_CLASS) {
	    StringTokenizer stok
	      = new StringTokenizer(new String(chars).substring(i),SIG_END_CLASS);
	    String next;
	    String className = parseClassReference(next = stok.nextToken(),false);
	    Object cachedType = getInterned(className);
	    if(cachedType != null)
	      v.addElement(cachedType);
	    else {
	      // System.out.println("Creating new type in parsetype2");
	      v.addElement(new Type(T_CLASS,null,className,0));
	    }
	    i += (next.length());
	  }
	  else throw new ClassException("Descriptor format is corrupt " +
					new String(chars,i,1));
    }		
  }
  
  private static int parseArrayType(final char[] chars, final Vector v, final int index)
      throws ClassException 
  {
	int indexLocal = index;  
    String classNameIfAny = null;
    int dimensions = 0;
    int flags = 0;
    while (true) {
      if (indexLocal < chars.length) {
	if (chars[indexLocal] == SIGC_ARRAY) {
	  flags |= T_ARRAY;
	  indexLocal++;
	  dimensions++;
	}
	else
	  {
	    String bigwaste = new String(chars).substring(indexLocal);
	    if (SIG_SIMPLE_ARG_TYPES.indexOf(chars[indexLocal]) != -1) {
	      flags |= decodeTypeChar(chars[indexLocal]);
	      classNameIfAny = "" + chars[indexLocal]; // MACH - to deal with arrays of primitive types
	      break;
	    }
	    if (chars[indexLocal] == SIGC_CLASS) {
	      StringTokenizer stok = new StringTokenizer(bigwaste,"" + SIG_END_CLASS);
	      String next;
	      if(! stok.hasMoreTokens()  )
		throw new ClassException("ClassName format is corrupt");
	      next = stok.nextToken();
	      indexLocal += next.length();				
	      classNameIfAny = bigwaste.substring(0,next.length()+1);
	      break;
	    }
	  }
      }
    }
    // System.out.println("Creating new type in parsearraytype");
    v.addElement(new Type(flags,null,classNameIfAny,dimensions));
    return indexLocal;
  }

  // Avoid; use className or classDescriptor instead.
  private static String parseClassReference (String st, boolean findseparator) 
      throws ClassException 
  {
    StringTokenizer stok = new StringTokenizer(st,SIG_PACKAGE_SEPARATORS);
    StringBuffer results= new StringBuffer(30);
    if (! stok.hasMoreTokens()) 
      throw new ClassException("Invalid class reference" + st);
    String nextToken = stok.nextToken();
    results.append(nextToken);
    while (stok.hasMoreTokens()) {
      results.append(SIGC_PACKAGE);
      results.append(nextToken = stok.nextToken()); 
    }
    
    if ( ! nextToken.endsWith("" + SIG_END_CLASS))
      if (findseparator)
	throw new ClassException("Missing semicolon at end of class name: " + st);
      else results.append(SIGC_END_CLASS);
    return results.toString();
  } 
  
  /*

    // Anything that uses this is seriously broken, and should probably be using
    // className -- ARL
    static String stripClassReference (String st, char packageSeparator)
    { 
    StringTokenizer stok = new StringTokenizer(st,SIG_CLASS_SEPARATORS);
    StringBuffer results= new StringBuffer(30);
    String nextToken = stok.nextToken();
    results.append(nextToken);
    while (stok.hasMoreTokens()) {
    results.append(packageSeparator);
    results.append(nextToken = stok.nextToken()); 
    }
    if (trace)
    System.out.println("Result of stripping classref " + st + " " + results.toString()); 
    return results.toString();
    }

    // Avoid; use className instead. (though note that classname("I") returns
    // "integer", not "I", so care is needed if it is called in a context
    //where primitive descriptors might be involved.
    static String stripClassReference (String className)
    { 
    String nameToUse 
    = className.charAt(0) == SIGC_CLASS ?
    className.substring(1,className.length()-1) :
    className;
    return nameToUse;
    }

    */

  // Avoid; use className or classDescriptor instead.
  static String canonicalizePackageSeparators (String st) { 
    StringTokenizer stok = new StringTokenizer(st,SIG_ALT_PACKAGE);
    StringBuffer results= new StringBuffer(30);
    if (! stok.hasMoreTokens())
      return st;
    String nextToken = stok.nextToken();
    results.append(nextToken);
    while (stok.hasMoreTokens()) {
      results.append(SIGC_PACKAGE);
      results.append(nextToken = stok.nextToken()); 
    }
    return results.toString();
  }

  // For backwards compatibility, functions that take a class name are allowed
  // to delimit the components by / instead of . (/ should only be used
  // in class descriptors, not in class names). This usage is deprecated,
  // but supported. To turn off support, replace this function by the identity.
  static String canonicalizeClassName (String st) {
    return st.replace('/', '.');
  }

  /* 
     // Anything that uses this is seriously broken, and should probably
     // be using classDescriptor instead. -- ARL
     static String adornClassReference (String st) throws ClassException {
     StringTokenizer stok = new StringTokenizer(st,SIG_CLASS_SEPARATORS);
     StringBuffer results= new StringBuffer(30); 
     String nextToken = stok.nextToken();
     if (nextToken.charAt(0) == SIGC_ARRAY) {
     results.append(nextToken);
     results.append(SIG_CLASS);
     if (stok.hasMoreTokens() )
     throw new ClassException("Cannot adorn class reference: " + st);	  
     results.append(stok.nextToken());
     }
     else {
     results.append(SIG_CLASS);
     results.append(nextToken);
     }
     while (stok.hasMoreTokens()) {
     results.append(SIGC_PACKAGE);
     results.append(nextToken = stok.nextToken()); 
     }
     results.append(SIG_END_CLASS);
     if (trace)
     System.out.println("Result of adornment " + results.toString()); 	   
     return results.toString();
     }

     */


  private static Hashtable primitiveClassNametoDescriptor = new Hashtable();
  private static Hashtable primitiveDescriptortoClassName = new Hashtable();

  private static void addPair(String descriptor, String name) {
    primitiveDescriptortoClassName.put(descriptor, name);
    primitiveClassNametoDescriptor.put(name, descriptor);
  }

  static {
    addPair("I", "int");
    addPair("B", "byte");
    addPair("D", "double");
    addPair("F", "float");
    addPair("J", "long");
    addPair("S", "short");
    addPair("Z", "boolean");
  }

  // Takes a fully-qualified class name, of the sort that is returned by
  // Class.getName(), and returns a class descriptor.
  // Note that for backwards compatibility, class names delimited by / instead
  // of . are supported here.
  static String classDescriptor (String classname) {
    String resultstring = (String) primitiveClassNametoDescriptor.get(classname);
    if (resultstring != null){
    	return resultstring;
    }
    StringBuffer result;
    if (classname.startsWith("[")) {
      return classname.replace('.', '/');
    } else {
      result = new StringBuffer("L");
      result.append(classname.replace('.', '/'));
      result.append(";");
      return result.toString();
    }
  }

  static String className (String classdescriptor) throws ClassException {
    // takes a descriptor, and returns a fully qualified class name, of
    // the sort returned by Class.getName();
    String resultstring = (String) primitiveDescriptortoClassName.get(classdescriptor);
    if (resultstring != null) {
    	return resultstring;
    }
    if (classdescriptor.startsWith("["))
      return classdescriptor.replace('/', '.');
    else {
      if (classdescriptor.startsWith("L") && classdescriptor.endsWith(";")) {
	return classdescriptor.substring(1, classdescriptor.length() - 1).replace('/', '.');
      } else {
	throw new ClassException("Bad class descriptor " + classdescriptor);
      }
    }
  }

  // ***************** Interned Type Management *************

  /** Types are interned.  That is there will never be more
   * than one instance of an equal type object in a VM. This 
   * reduces the number of times that an equal descriptor string
   * needs to be parsed. It is up to the user to decide the scope
   * for which interned type persists.  The user has the following 
   * choices:<br>
   * If the user wants type interns not to persist:<br>
   * i) Between compiles keep no pointers to the Class object for Type,
   * and assume the Java VM will unload the type object;<br>
   * ii) Between compiles call Type.resetInternedTypes() to clear out
   * all interned types;<br>
   * If the user wants type interns to persist: <br>
   * i) Between compiles hold on to a pointer to the Class object for Type;<br>
   * ii) Set the -noclassgc option if the VM provides one.<br>
   */ 
  public static void resetInternedTypes() {
    System.out.println("resetting Interned Types");
    // For all previously interned types set the interned flag to false
    Enumeration e = internedTypes.elements();
    while(e.hasMoreElements())
      ((Type) e.nextElement()).interned = false;
    internedTypes = new Hashtable();
  }

  private static void printInternedTypes() {
    Enumeration e1 = internedTypes.elements();
    Enumeration e2 = internedTypes.keys();
    while(e2.hasMoreElements())
      System.out.println(e1.nextElement() + " " + ">>>" + e2.nextElement().hashCode());
  }

  private static void intern(String descriptor, Type tpe) {
    // System.out.println("Interning type " + tpe + " under descriptor " + descriptor);
    internedTypes.put(descriptor,tpe);
    tpe.interned = true;
  }

  private static Object getInterned(String descriptor) {
    // System.out.println("Looking for type for descriptor " + descriptor);
    // System.out.println("Returning " + internedTypes.get(descriptor));
    return internedTypes.get(descriptor);
  }

  //******************  Testing only *****************
   
  public static void main(String[] args) {
    try {
      Type tp = parseType(args[0]);
      Type tp2 = parseType(args[1]);
      System.out.println("Check for potential subtype");
      System.out.println(tp);
      System.out.println(tp2);
      System.out.println("Result = " + tp.potentialSubType(tp2));
      Type tp3 = parseType(args[2]);
      System.out.println("Before stripping class reference " + tp3);
      System.out.println("After stripping class reference " + Type.className(tp3.getReturnTypeString()));
    }
    catch (Exception e) {
      System.out.println("Exception " + e);
      e.printStackTrace();
    }
  }
}

  
