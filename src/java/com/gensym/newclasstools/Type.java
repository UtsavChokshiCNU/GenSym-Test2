package com.gensym.newclasstools;

import java.util.StringTokenizer;
import java.util.Vector;
import java.util.Enumeration;
import java.util.Hashtable;
import java.lang.reflect.Method;

/**
 * Type is used for to define the type of an expression
 */
public class Type implements RuntimeConstants, ExprOpCodes {

  private int typeCode;

  private int arrayRank;
  // className is the fully qualified name of the base type, or null if
  // the base type is primitive.
  private String className;
  // for primitive types and primitive-based arrays, we store a
  // descriptor instead of a class name.
  private String descriptor;
  private static Hashtable internedTypes = new Hashtable();
  private static final boolean trace = false;
  

  //************** Constructors **************

  // Constructors are private so that all types can be guaranteed to be
  // interned.

  private Type(int type, int rank, String descriptor) {
    typeCode = type;
    arrayRank = rank;
    this.descriptor = descriptor;
  }

  private Type(String className, int rank) {	
    // System.out.println("Creating new type; args are + className  + ", and " + rank);
    typeCode = P_REFERENCE;
    this.className = className;
    arrayRank = rank;
  }

  public String getClassName() {
    if (arrayRank == 0 && className != null) {
      return className;
    } else {
      return descriptor();
    }
  }

  public String getInternalizedClassName() {
    if (arrayRank == 0 && className != null) {
      return Type.internalize(className);
    } else {
      return descriptor();
    }
  }

  public int getTypeCode() {
    if (arrayRank == 0)
      return typeCode;
    else
      return P_REFERENCE;
  }

  public int getArrayRank() {
    return arrayRank;
  }

  private static Type makeType(String hashCode, String className,
			       int typeCode, int rank) { 
    Vector typeVector = (Vector)internedTypes.get(hashCode);
    if (typeVector == null) {
      if (trace) 
	System.out.println("null Type Vector");
      typeVector = new Vector(rank);
      internedTypes.put(hashCode, typeVector);
    }
    Type foundType = null;
    if (rank < typeVector.size()) {
      foundType = (Type)typeVector.elementAt(rank);
    }
    if (trace) 
      System.out.println("Found Type is" + foundType);
    if (foundType == null) {
      if (className == null) {
	foundType = new Type(typeCode, rank, hashCode);
      } else {
	foundType = new Type(className, rank);
      }
      if (typeVector.size() <= rank) {
	if (trace) 
	  System.out.println("setting vector size to " + rank);
	typeVector.setSize(rank + 1);
      }
      if (trace) 
	System.out.println("Adding type " + foundType + " at array index " + rank);
      if (trace) 
	System.out.println("Type vector before add is " + typeVector);
      typeVector.set(rank, foundType);
      if (trace) 
	System.out.println("Type vector after add is " + typeVector);
    }
    return foundType;
  }

  public static Type makeType(String className, int rank) { 
    return makeType(className, className, P_REFERENCE, rank);
      }

  public static Type makeType(String className) { 
    return makeType(className, className, P_REFERENCE, 0);
      }

  public static Type makeType(Type baseType, int rank) { 
    return makeType((baseType.className == null)? 
		    baseType.descriptor : baseType.className,
		    baseType.className,
		    baseType.getTypeCode(),
		    baseType.getArrayRank() + rank);
      }

  // Note; getArrayElementType on [[I returns [I;
  //  getArrayBaseElementType on [[I returns I.

  public Type getArrayBaseElementType() {
    return makeType((className == null) ? descriptor : className,
		    className,
		    getTypeCode(),
		    0);
  }

  public Type getArrayElementType() throws ClassException {
    if (! isArrayType())
      throw new ClassException("Not an array type");
    return makeType((className == null) ? descriptor : className,
		    className,
		    getTypeCode(),
		    getArrayRank() - 1);
  }

  // ******* Parsing a Type from a descriptor string **************
  
  public static Type parseType(String desc) throws ClassException

  {
    TypeParser tp = new TypeParser(desc, 0);
    return tp.getType();
  }

  public static Type parseReturnType(String desc) 
      throws ClassException
  {
    TypeParser tp = new TypeParser(desc, desc.indexOf(')') + 1);
    return tp.getType();
  }

  public static Vector parseArgumentTypes(String desc) throws ClassException {
    Vector result = new Vector();
    TypeParser tp = new TypeParser(desc, 1); // Skip the initial '('
    while (tp.currentChar() != ')') {
      result.add(tp.getType());
    }
    return result;
  }

  static Type[] makeTypeArray(Vector v) {
    Type[] result = new Type[v.size()];
    for(int i = 0; i < v.size(); i++) {
      result[i] = (Type)v.elementAt(i);
    }
    return result;
  }

  private static Type makePrimitiveType(int typeCode, String descriptor) {
    return makeType(descriptor, null, typeCode, 0);
  }

  public final static Type NULL_TYPE = makePrimitiveType(P_NULL, "null");
  public final static Type INT_TYPE = makePrimitiveType(P_INT, "I");
  public final static Type VOID_TYPE = makePrimitiveType(P_VOID, "V");
  public final static Type BOOLEAN_TYPE = makePrimitiveType(P_BOOLEAN, "Z");
  public final static Type BYTE_TYPE = makePrimitiveType(P_BYTE, "B");
  public final static Type CHAR_TYPE = makePrimitiveType(P_CHAR, "C");
  public final static Type SHORT_TYPE = makePrimitiveType(P_SHORT, "S");
  public final static Type LONG_TYPE = makePrimitiveType(P_LONG, "J");
  public final static Type FLOAT_TYPE = makePrimitiveType(P_FLOAT, "F");  
  public final static Type DOUBLE_TYPE = makePrimitiveType(P_DOUBLE, "D");  

  public final static Type OBJECT_TYPE = makeType("java.lang.Object");
  public final static Type STRING_TYPE = makeType("java.lang.String");
  public final static Type STRING_BUFFER_TYPE = makeType("java.lang.StringBuffer");
  public final static Type CLONEABLE_TYPE = makeType("java.lang.Cloneable");
  public final static Type SERIALIZABLE_TYPE = makeType("java.io.Serializable");

  private final static Type[] typeCodeToType = {
    null,  // Illegal
    NULL_TYPE,
    BOOLEAN_TYPE,
    CHAR_TYPE,
    BYTE_TYPE,
    SHORT_TYPE,
    INT_TYPE,
    LONG_TYPE,
    FLOAT_TYPE,
    DOUBLE_TYPE,
    STRING_TYPE,
    null,    // Reference type
    null     // Void type.
  };

  static { STRING_TYPE.typeCode = P_STRING;}


  //***************** Predicates ***********************

  // NB isIntegerType() means only an integer type.
  // isIntegerBasedType() includes arrays of (arrays of...) integer types.
  // These concepts were previously confounded, and both called
  // isIntegerType. This predicate name is no longer used, to avoid confusion.
  // Similarly for all the other IsFooType predicates.

  public boolean isIntegerBasedType() {
    return (typeCode == P_INT);
  }

  public boolean isShortBasedType() {
    return (typeCode == P_SHORT);
  }

  public boolean isBooleanBasedType() {
    return (typeCode == P_BOOLEAN);
  }

  public boolean isByteBasedType() {
    return (typeCode == P_BYTE);
  }

  public boolean isFloatBasedType() {
    return (typeCode == P_FLOAT);
  }

  public boolean isDoubleBasedType() {
    return (typeCode == P_DOUBLE);
  }

  public boolean isCharBasedType() {
    return (typeCode == P_CHAR);
  }

  public boolean isLongBasedType() {
    return (typeCode == P_LONG);
  }

  public boolean isArrayType() {
    return (arrayRank > 0);
  }

  public boolean isJavaLangObjectBasedType() {
    return (getArrayBaseElementType() == OBJECT_TYPE);
  }

  public boolean isClassBasedType() {
    return (typeCode >= P_STRING || this == NULL_TYPE);
  }

  public boolean isIntegralBasedType() {
    return (typeCode >= P_CHAR && typeCode <= P_LONG);
  }

  public boolean isSmallIntegralBasedType() {
    return (typeCode >= P_CHAR && typeCode <= P_INT);
  }

  public boolean isNumericBasedType() {
    return (typeCode >= P_CHAR && typeCode <= P_DOUBLE);
  }

  public boolean isIntegerType() {
    return (getTypeCode() == P_INT);
  }

  public boolean isShortType() {
    return (getTypeCode() == P_SHORT);
  }

  public boolean isBooleanType() {
    return (getTypeCode() == P_BOOLEAN);
  }

  public boolean isByteType() {
    return (getTypeCode() == P_BYTE);
  }

  public boolean isFloatType() {
    return (getTypeCode() == P_FLOAT);
  }

  public boolean isDoubleType() {
    return (getTypeCode() == P_DOUBLE);
  }

  public boolean isCharType() {
    return (getTypeCode() == P_CHAR);
  }

  public boolean isVoidType() {
    return (getTypeCode() == P_VOID);
  }

  public boolean isLongType() {
    return (getTypeCode() == P_LONG);
  }

  public boolean isJavaLangObjectType() {
    return (this == OBJECT_TYPE);
  }

  public boolean isClassType() {
    return ((getTypeCode() >= P_STRING && getTypeCode() <= P_REFERENCE &&
	     arrayRank == 0) || isNullType());
  }

  public boolean isNullType() {
    return this == NULL_TYPE;
      }

  public boolean isReferenceType() {
    return ((getTypeCode() >= P_STRING && getTypeCode() <= P_REFERENCE) ||
	    arrayRank > 0 || this == NULL_TYPE);
  }

  public boolean isIntegralType() {
    return (getTypeCode() >= P_CHAR && getTypeCode() <= P_LONG);
  }

  public boolean isSmallIntegralType() {
    return (getTypeCode() >= P_CHAR && getTypeCode() <= P_INT);
  }

  public boolean isNumericType() {
    return (getTypeCode() >= P_CHAR && getTypeCode() <= P_DOUBLE);
  }

  //********** Boolean Predicates on Two types *********************

  /**
   * Types are interned, so no need for equals
   */
  @Override
  public boolean equals(Object tpe) {
    return (this == tpe);
  }

  // Used for argument lists; 
  public static int hashTypeArray(Type[] array) {
    int hashCode = 1;
    for (int i = 0; i < array.length; i++) {
      Type type = array[i];
      hashCode = 31 * hashCode + ((type == null) ? 0 : type.hashCode());
    }
    return hashCode;
  }
	
  // Denigrated - used only in OperatorCall type checking, may want to use
  // something else there as well
  boolean potentialSubType(Type tpe) 
  {
    return
      (isNumericType() && tpe.isNumericType()) ||
      (isIntegralType() && tpe.isIntegralType()) ||	
      (isArrayType() ? (arrayRank == tpe.getArrayRank())
       && (getArrayBaseElementType().potentialSubType(tpe.getArrayBaseElementType())): false) ||
      (isJavaLangObjectType() && tpe.isReferenceType()) ||
      (isClassType() ? tpe.isClassType() : true);
  }

  /**
   * Check if an expression is assignment compatable with this type.
   * Note that this predicate requires access to the node because there is a special rule 
   * surrounding whether the expression being assigned is a constant integer of a certain
   * size.  See "The Java Virtual Machine Specification" pages 17 and 18 for a full discussion
   * of assignment conversion.
   * 
   */
  
  public boolean potentialAssignmentConversion(Type tpe) {
    return potentialConversion(tpe, null, true);
  }


  public boolean potentialAssignmentConversion(Expression exp) {
    return potentialConversion(exp.getExpressionType(), exp, true);
  }

  
  private boolean potentialConversion(Type tpe, Expression exp,
				      boolean allowWideningPrimitiveConversion)
  {
    // System.out.println("Comparing Types: " + this + " and " + tpe);
    // System.out.println("Typecodes are: " + this.getTypeCode() + " and " + tpe.getTypeCode());
    if (tpe == NULL_TYPE) {
      // System.out.println("Null Type case");
      return isReferenceType();
    }
    if (tpe.isClassType()) {
      // System.out.println("Class Type case");
      if ((exp != null) && exp instanceof Value && ((Value)exp).isNull())
	return isReferenceType();
      else
	return isClassType();
    }
    if (tpe.isArrayType()) {
      // System.out.println("Array Type case");
      if (getArrayRank() == tpe.getArrayRank())
	return getArrayBaseElementType().potentialConversion(tpe.getArrayBaseElementType(), null, false);
      if (getArrayRank() > tpe.getArrayRank())
	return false;
      // getArrayRank() < tpe.getArrayRank()
      Type baseType = getArrayBaseElementType();
      return (baseType.isJavaLangObjectType() || baseType == CLONEABLE_TYPE || baseType == SERIALIZABLE_TYPE);
    }
    // tpe is primitive type.
    if (isReferenceType()) {
      // System.out.println("Second Type is reference type");
      return false;
    }
    // two primitive types.
    if (tpe.isBooleanType()) {
      // System.out.println("Boolean Type case");
      return isBooleanType();
    }
    if (isBooleanType()) {
      // System.out.println("Second Type is boolean type");
      return false;
    }
    // two numeric types.
    // System.out.println("Comparing 2 numeric Types: " + this + " and " + tpe);
    if (requiresNarrowingPrimitiveConversion(tpe)) 
      if (allowWideningPrimitiveConversion
	  && (isShortType() | isByteType() | isCharType()) 
	  && tpe.isIntegerType() 
	  && (exp instanceof Value)
	  && ((Value) exp).canFitInSingleByte())
	return true;
      else return false;
    else return true;			
  }

  public boolean potentialMethodArgumentConversion(Expression exp) { 
    return potentialConversion(exp.getExpressionType(), exp, false);
  }

  public boolean potentialMethodArgumentConversion(Type tpe) { 
    return potentialConversion(tpe, null, false);
  }
   
 
  // pp15-16
  boolean requiresNarrowingPrimitiveConversion(Type tpe) {
    if (tpe.isIntegerType())	
      return (isByteType() | isShortType() | isCharType());
    if (tpe.isByteType())
      return isCharType();
    if (tpe.isLongType())
      return (isByteType() | isShortType() | isCharType() | isIntegerType());
    if (tpe.isDoubleType())
      return (isByteType() | isShortType() | isCharType() |
	      isIntegerType() | isFloatType());
    if (tpe.isShortType())
      return isByteType() | isCharType();
    if (tpe.isFloatType())
      return (isByteType() | isShortType() | isCharType() | isIntegerType());
    return false;
  }

  static private int computePromotion(int opCode, Type type1, Type type2) {
    int typecode1 = type1.getTypeCode();
    if (type2 != null) {
      int typecode2 = type2.getTypeCode();
      // 
      switch (opCode) {
      case MINUS_:
      case STAR_:
      case MOD_:
      case DIV_:
	// only numeric types are OK
	if ((typecode1 > P_DOUBLE) || (typecode2 > P_DOUBLE)) return P_ILLEGAL;
      case PLUS_:
	// Binary Numeric Promotion, p. 74
	// Note that any binary op performed on types shorter than int
	// (including char) will be promoted to integer, even when both the 
	// types are the same. For example:
	//    byte x = (byte)100;
	//    char y = 'a';     // ASCII is 97
	//    System.out.println("FOO " + (x + x + x)    );
	//    System.out.println("FOO " + (y + y + y)    );
	// produces:
	//    FOO 300
	//    Foo 291
	if ((typecode1 == P_STRING) || (typecode2 == P_STRING)) return P_STRING;
	if ((typecode1 < P_CHAR) || (typecode2 < P_CHAR)) return P_ILLEGAL;
	if ((typecode1 > P_STRING) || (typecode2 > P_STRING)) return P_ILLEGAL;
	return Math.max(Math.max(typecode1, typecode2),P_INT);
      case SR_:
      case BSR_:
      case SL_:
	if ((typecode1 < P_CHAR) || (typecode2 < P_CHAR)) return P_ILLEGAL;  // Can floats be shifted??
	if ((typecode1 > P_DOUBLE) || (typecode2 > P_DOUBLE)) return P_ILLEGAL;
	// Unary Numeric promotion: p. 73
	return Math.max(typecode1,P_INT);
      case EQUAL_:
      case NOT_EQUAL_:
	// See p. 363 for == and != spec.
	// Both reference, both String, both boolean, both nueric are allowed.
	// Reference equaility needs compile time compatibility checking. ??
	if (((typecode1 == P_REFERENCE) || (typecode1 == P_NULL) || (typecode1 == P_STRING)) && 
	    ((typecode2 == P_REFERENCE)) || (typecode2 == P_NULL) || (typecode2 == P_STRING))
	  return P_BOOLEAN;
	if ((typecode1 == P_BOOLEAN) && (typecode2 == P_BOOLEAN)) return P_BOOLEAN;
      case GE_:
      case GT_:
      case LE_:
      case LT_:
	// See p. 360. Both must be numeric. Use binary promotion.
	if ((typecode1 < P_CHAR) || (typecode1 > P_DOUBLE) ||
	    (typecode2 < P_CHAR) || (typecode2 > P_DOUBLE)) return P_ILLEGAL;
	return P_BOOLEAN;
      case BXOR_:
      case BOR_:
      case BAND_:
	// p. 365. Either boolean to boolean, or integral bitwise.
	if ((typecode1 == P_BOOLEAN) && (typecode2 == P_BOOLEAN)) return P_BOOLEAN;
	if ((typecode1 < P_CHAR) || (typecode1 > P_LONG) ||
	    (typecode2 < P_CHAR) || (typecode2 > P_LONG)) return P_ILLEGAL;
	return Math.max(Math.max(typecode1, typecode2),P_INT);     
      case LOR_:
      case LAND_:
	if ((typecode1 == P_BOOLEAN) && (typecode2 == P_BOOLEAN)) return P_BOOLEAN;
	return P_ILLEGAL;
      case QUESTION_:
	// See page 368;
	// This code fails to fully implement that spec because no machinery for
	// for compile time evaluation of constants has been implemented.
	// Thus, for example:  "char ch2 = bool1 ? ch1 : 77;" will not compile.
	// The user will have to write: "char ch2 = bool1 ? ch1 : (char)77;"   ??
	if (typecode1 == typecode2) return typecode1;
	if (((typecode1 == P_SHORT) && (typecode2 == P_BYTE)) ||
	    ((typecode2 == P_SHORT) && (typecode1 == P_BYTE))) return P_SHORT;
	if (((typecode1 == P_REFERENCE) || (typecode1 == P_NULL) || (typecode1 == P_STRING)) && 
	    ((typecode2 == P_REFERENCE)) || (typecode2 == P_NULL) || (typecode2 == P_STRING))
	  return P_REFERENCE;
	if ((typecode1 < P_CHAR) || (typecode1 > P_DOUBLE) ||
	    (typecode2 < P_CHAR) || (typecode2 > P_DOUBLE)) return P_ILLEGAL;
	return Math.max(Math.max(typecode1, typecode2),P_INT);

      case PLUS_ASSIGN_:
	// 
	if (typecode1 == P_STRING || typecode2 == P_STRING ||
	    (typecode1 > P_BOOLEAN && typecode2 > P_BOOLEAN && typecode1 < P_STRING && typecode2 < P_STRING))
	  return typecode1; else return P_ILLEGAL; 

      case ASSIGN_:
	if ((typecode1 > P_BOOLEAN && typecode2 > P_BOOLEAN && typecode1 < P_STRING && typecode2 < P_STRING) ||
	    (typecode1 == typecode2) ||
	    ((typecode1 == P_STRING && typecode2 == P_REFERENCE) && 
	     typecode2 == P_NULL) ||
	    (typecode1 == P_REFERENCE && typecode2 == P_STRING))

	  return typecode1; else return P_ILLEGAL; 
      case DIV_ASSIGN_:
      case MINUS_ASSIGN_:
      case STAR_ASSIGN_:
      case MOD_ASSIGN_:
      case SR_ASSIGN_:
      case BSR_ASSIGN_:
      case SL_ASSIGN_:
	if (typecode1 > P_BOOLEAN && typecode2 > P_BOOLEAN && typecode1 < P_STRING && typecode2 < P_STRING)
	  return typecode1; else return P_ILLEGAL; 

      case BXOR_ASSIGN_:
      case BOR_ASSIGN_:
      case BAND_ASSIGN_:
	if (typecode1 < P_STRING && typecode2 < P_STRING)
	  return typecode1; else return P_ILLEGAL; 
      case POST_INC:
      case POST_DEC:
      case PRE_INC:
      case PRE_DEC:
	if ((typecode1 < P_CHAR) || (typecode1 > P_DOUBLE)) return P_ILLEGAL;
	return typecode1;
      }  // end switch
      return P_ILLEGAL;  // Bad opCode (or to make Javac happy)
      
    } else {  // op is unary from here on
      switch (opCode) {
      case INSTANCEOF:
	// instanceof is binary, but the second argument has null type
	// (since there is no type to represent a class name)
	// so we end up here.
	return P_BOOLEAN;
      case LNOT_:
	if (typecode1 == P_BOOLEAN) return P_BOOLEAN; else return P_ILLEGAL;
      case BNOT_:
	// p. 349. The arg. must be an integral type. Use unary promotion.
	if ((typecode1 < P_CHAR) || (typecode1 > P_LONG)) return P_ILLEGAL;
	return Math.max(typecode1,P_INT);
      case UNARY_PLUS_:
      case UNARY_MINUS_:
	// pp. 348-349
	// The args must be numeric. Use unary promotion. 
	if ((typecode1 < P_CHAR) || (typecode1 > P_DOUBLE)) return P_ILLEGAL;
	return Math.max(typecode1,P_INT);  
      } 
      return P_ILLEGAL;  // Bad opCode (or to make Javac happy)
    }    
  } // end computePromotion

  static int operatorToOpCode (String operator) {
    for (int i = 0; i < ExprOpCodes.opNames.length; i++)
      if (ExprOpCodes.opNames[i].equals(operator)) return i;
    return -1;
  }
    
  /** The value is the Type specified in the Java Language Specification as the 
   * value type of an expression governed by a binary operator.
   * 
   * May be used with "?" (QUESTION_) which is a ternary operator. In this case
   * type1 and type2 are the types for the second and third components. (The first
   * must be boolean.)
   *
   * Returns null if the specified types cannot be legally combined with
   * the specified operator.
   *
   * "Every Java expression has a type that can be deduced from the structure
   * of the expression and types of the literals, variables and methods 
   * mentioned in the expression." - The Java Language Specification, p. 51.
   */
  static public Type computeResultType(String operator, Type type1, Type type2) {
    int opcode = operatorToOpCode(operator);
    if (opcode == -1) return null;
    int resultCode = computePromotion(opcode, type1, type2);
    if (resultCode == P_ILLEGAL) return null;
    if (resultCode < P_REFERENCE) return typeCodeToType[resultCode];
    // If result is reference type, it must be the same as the
    // first input reference type.
    return type1;
  }

  static public Type computeResultType(String operator, Type type1) {
    int opcode = operatorToOpCode(operator);
    if (opcode == -1) return null;
    int resultCode = computePromotion(opcode, type1, null);
    if (resultCode == P_ILLEGAL) return null;
    if (resultCode < P_REFERENCE) return typeCodeToType[resultCode];
    // If result is reference type, it must be the same as the
    // input reference type.
    return type1;
  }

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

  public String descriptor() {
    StringBuffer result = new StringBuffer();
    appendDescriptor(result);
    return new String(result);
  }

  public String descriptor(Vector argumentTypes) {
    StringBuffer buffer = new StringBuffer();
    buffer.append('(');
    for (int i = 0; i < argumentTypes.size(); i++) {
      ((Type)argumentTypes.elementAt(i)).appendDescriptor(buffer);
    }
    buffer.append(')');
    appendDescriptor(buffer);
    return new String(buffer);
  }

  public String descriptor(Type[] argumentTypes) {
    // Not the most efficient, but who cares.
    Vector v = new Vector(argumentTypes.length);
    for (int i = 0; i < argumentTypes.length; i++)
    v.addElement(argumentTypes[i]);
    return descriptor(v);
  }

  private void appendDescriptor (StringBuffer buffer) {
    for (int index = 0; index < arrayRank; index++)
      buffer.append('[');
    if (className == null) {
      buffer.append(descriptor);
    } else {
      //System.out.println("className="+className);
      buffer.append('L');
      buffer.append(Type.internalize(className));
      buffer.append(';');
    }
  }

  // Utility functions for converting names to descriptors and vice versa.

  // Takes a fully-qualified class name, of the sort that is returned by
  // Class.getName(), and returns a class descriptor.
  // Note that for backwards compatibility, class names delimited by / instead
  // of . are supported here.

  public static String internalize (String in) {
    return in.replace('.', '/');
      }

  public static String externalize (String in) {
    return in.replace('/', '.');
      }

  public static String classDescriptor (String classname) {
    String resultstring = (String) primitiveClassNametoDescriptor.get(classname);
    if (resultstring != null) return resultstring;
    StringBuffer result;
    if (classname.startsWith("[")) {
      return Type.internalize(classname);
    } else {
      result = new StringBuffer("L");
      result.append(Type.internalize(classname));
      result.append(";");
      return result.toString();
    }
  }

  public static String className (String classdescriptor) throws ClassException {
    // takes a descriptor, and returns a fully qualified class name, of
    // the sort returned by Class.getName();
    String resultstring = (String) primitiveDescriptortoClassName.get(classdescriptor);
    if (resultstring != null) return resultstring;
    if (classdescriptor.startsWith("["))
      return externalize(classdescriptor);
    else {
      if (classdescriptor.startsWith("L") && classdescriptor.endsWith(";")) {
	return externalize(classdescriptor.substring(1, classdescriptor.length() - 1));
      } else {
	throw new ClassException("Bad class descriptor " + classdescriptor);
      }
    }
  }
  
  @Override
  public String toString() {
    return "<Type " + getClassName() + ">";
  }

  public static Type[] typesFromClasses(Class[] classes)
  {
    Type[] result = new Type[classes.length];
    for (int i = 0; i<classes.length ; i++)
      result[i] = Type.typeForClass(classes[i]);
    return result;
  }

  public static Type[] argTypesForMethod(Method method)
  {
    return typesFromClasses(method.getParameterTypes());
  }

  public static Type typeForClass(Class type)
  {
    if (type == Integer.TYPE)
      return Type.INT_TYPE;
    else if (type == Long.TYPE)
      return Type.LONG_TYPE;
    else if (type == Byte.TYPE)
      return Type.BYTE_TYPE;
    else if (type == Character.TYPE)
      return Type.CHAR_TYPE;
    else if (type == Short.TYPE)
      return Type.SHORT_TYPE;
    else if (type == Float.TYPE)
      return Type.FLOAT_TYPE;
    else if (type == Double.TYPE)
      return Type.DOUBLE_TYPE;
    else if (type == Boolean.TYPE)
      return Type.BOOLEAN_TYPE;
    else if (type == Void.TYPE)
      return Type.VOID_TYPE;
    else if (type.isArray())
      {
	int rank = 0;
	while (type.isArray())
	  {
	    type = type.getComponentType();
	    rank++;
	  }
	Type res =  Type.makeType(typeForClass(type),rank);
	//System.out.println("from class "+type+" got type "+res+
	//" res.descr="+res.descriptor);
	return res;
      }
    else
      return Type.makeType(type.getName());
  }

  public static Type wrappedType(Type rawType) {
    switch (rawType.typeCode) {
    case P_INT: return makeType("java.lang.Integer");
    case P_BOOLEAN: return makeType("java.lang.Boolean");
    case P_BYTE: return makeType("java.lang.Byte");
    case P_CHAR: return makeType("java.lang.Char");
    case P_SHORT: return makeType("java.lang.Short");
    case P_LONG: return makeType("java.lang.Long");
    case P_FLOAT: return makeType("java.lang.Float");
    case P_DOUBLE: return makeType("java.lang.Double");
    }
    return OBJECT_TYPE;
    }

  // Returns an expression with the same content as the given expression (which should
  // be of type Object) but of the specified type. Accomplishes this via a cast if the
  // type is a subtype of Object, and via intValue, byteValue, etc. if the type is primitive.
  public static Expression convertToType(Expression exp, Type type) {
    try {
      if (type.isReferenceType())
	return new Cast(type, exp);
      Type wrapped = wrappedType(type);
      String accessor = "";
      switch (type.typeCode) {
      case P_INT: accessor = "intValue"; break;
      case P_BOOLEAN: accessor = "booleanValue"; break;
      case P_BYTE: accessor = "byteValue"; break;
      case P_CHAR: accessor = "charValue"; break;
      case P_SHORT: accessor = "shortValue"; break;
      case P_LONG: accessor = "longValue"; break;
      case P_FLOAT: accessor = "floatValue"; break;
      case P_DOUBLE: accessor = "doubleValue"; break;
      }
      return new MethodCall(accessor,
			    wrapped,
			    new Type[]{},
			    type,
			    new Cast(wrapped, exp),
			    new Expression[]{},
			    MTH_CALL_VIRTUAL);
    } catch (Exception e) {
      return new Value("Unexpected error in convertToType");
    }
  }

  // Given an expression, returns an expression with the same semantic value, whose
  // Type is a subtype of Object, wrapping a boolean as a Boolean, an int as an Integer, etc.
  public static Expression convertToObject(Expression exp) {
    try {
      Type rawType = exp.getExpressionType();
      if (rawType.isReferenceType())
	return exp;
      return new New(wrappedType(rawType), new Type[]{rawType}, new Expression[]{exp});
    } catch (Exception e) {
      return new Value("Unexpected error in convertToObject");
    }
  }

  
  // Given a type object for a type, returns the corresponding Class object.
  public Class classForType() {
    if (isReferenceType())
      try {
      return Class.forName(getClassName());
    } catch (Exception e) {
      return null;
    }
    switch (typeCode) {
    case P_INT: return Integer.TYPE;
    case P_BOOLEAN: return Boolean.TYPE;
    case P_BYTE: return Byte.TYPE;
    case P_CHAR: return Character.TYPE;
    case P_SHORT: return Short.TYPE;
    case P_LONG: return Long.TYPE;
    case P_FLOAT: return Float.TYPE;
    case P_DOUBLE: return Double.TYPE;
    }
    return null;
  }
 
  /*
  public static void main(String[] args)
  {
    try {
      Class c = Class.forName("com.gensym.nm.model.WAN");
      Method[] methods = c.getMethods();
      int i,len = methods.length;
      for (i=0; i<len; i++)
	{
	  Method m = methods[i];
	  if (m.getName().equals("getElementsByIpAddress"))
	    {
	      Type[] types = Type.argTypesForMethod(m);
	    }
	}
    } catch (Exception e)
      {
	e.printStackTrace();
      }
    System.exit(0);
  }
  */

}

class TypeParser implements RuntimeConstants {
  private String str;
  private int index;
  

  private static Type decodeTypeChar (char ch) throws ClassException {
    switch (ch) {
    case SIGC_VOID:
      return Type.VOID_TYPE;
    case SIGC_BOOLEAN:
      return Type.BOOLEAN_TYPE;
    case SIGC_BYTE:
      return Type.BYTE_TYPE;
    case SIGC_CHAR:
      return Type.CHAR_TYPE;
    case SIGC_SHORT:
      return Type.SHORT_TYPE;
    case SIGC_INT:
      return Type.INT_TYPE;
    case SIGC_LONG:
      return Type.LONG_TYPE;
    case SIGC_FLOAT:
      return Type.FLOAT_TYPE;
    case SIGC_DOUBLE:
      return Type.DOUBLE_TYPE;
    default: throw new ClassException("Bad class descriptor '" + ch + "'");
    }
  }

  TypeParser(String str, int index) {
    this.str = str;
    this.index = index;
  }
  
  char currentChar() {
    return str.charAt(index);
  }
  
  Type getType() throws ClassException {
    int rank = 0;
    while (str.charAt(index) == '[') {
      rank++;
      index++;
    }
    if (str.charAt(index) == 'L') {
      int end = str.indexOf(';', index);
      Type result =
	Type.makeType(Type.externalize(str.substring(index+1, end-1)),
		      rank);
      index = end + 1;
      return result;
    }
    Type baseType = decodeTypeChar(str.charAt(index));
    index++;
    return Type.makeType(baseType, rank);
  }
}
