package com.gensym.util;

import java.lang.reflect.*;
import java.nio.charset.Charset;
import java.util.Hashtable;
import java.io.*;

/**
 * This class provides generic methods for conversion of G2 proxy classes to and from Java classes.
 * The Class provides the following functionality;
 *. generate a G2 name or Class name from a Java name or class name.
 *. generate a Java name or Class name from a G2 name or Class name.
 *. Provide mapping hashtables for G2 to Java classes and Java to G2.
 *. methods to generate G2 source that can be used to generate G2 proxy classes and
 *  stubs that represent java classes from G2 (used by JavaLink module KB).
 */
public class G2ClassTranslator  {

  // Lookup for G2 Type from Java Class
  private static Hashtable G2TypeFromJavaClassHashtable = null;
  // lookup for G2 return types from Java Classes
  private static Hashtable G2ReturnTypeFromJavaClassHashTable = null;

  // lookup for remapping Java Attributes to G2 attributes
  private static Hashtable ConflictingJavaG2AttributeNamesHashTable = null;

  // lookup to avoid clashing with G2 reserved symbols
  private static Hashtable G2ReservedSymbolsHashTable = null;

  private static Class IntegerClass;
  private static Class FloatClass;
  private static Class BooleanClass;
  private static Class DoubleClass;
  private static Class MethodClass;
  private static Class FieldClass;
  private static Class LongClass;
  private static Class ByteClass;
  private static Class ShortClass;
  private static Class CharacterClass;
  //private static Class G2ItemProxyClass;

  private static Symbol JAVA_LANG_INTEGER_TYPE_     = Symbol.intern("JAVA.LANG.INTEGER.TYPE");
  private static Symbol JAVA_LANG_FLOAT_TYPE_       = Symbol.intern("JAVA.LANG.FLOAT.TYPE");
  private static Symbol JAVA_LANG_DOUBLE_TYPE_      = Symbol.intern("JAVA.LANG.DOUBLE.TYPE");
  private static Symbol JAVA_LANG_BYTE_TYPE_        = Symbol.intern("JAVA.LANG.BYTE.TYPE");
  private static Symbol JAVA_LANG_CHARACTER_TYPE_   = Symbol.intern("JAVA.LANG.CHARACTER.TYPE");
  private static Symbol JAVA_LANG_SHORT_TYPE_       = Symbol.intern("JAVA.LANG.SHORT.TYPE");
  private static Symbol JAVA_LANG_LONG_TYPE_        = Symbol.intern("JAVA.LANG.LONG.TYPE");
  private static Symbol JAVA_LANG_BOOLEAN_TYPE_     = Symbol.intern("JAVA.LANG.BOOLEAN.TYPE");
  private static Symbol JAVA_LANG_INTEGER_          = Symbol.intern("JAVA.LANG.INTEGER");
  private static Symbol JAVA_LANG_FLOAT_            = Symbol.intern("JAVA.LANG.FLOAT");
  private static Symbol JAVA_LANG_DOUBLE_           = Symbol.intern("JAVA.LANG.DOUBLE");
  private static Symbol JAVA_LANG_BYTE_             = Symbol.intern("JAVA.LANG.BYTE");
  private static Symbol JAVA_LANG_CHARACTER_        = Symbol.intern("JAVA.LANG.CHARACTER");
  private static Symbol JAVA_LANG_SHORT_            = Symbol.intern("JAVA.LANG.SHORT");
  private static Symbol JAVA_LANG_LONG_             = Symbol.intern("JAVA.LANG.LONG");
  private static Symbol JAVA_LANG_BOOLEAN_          = Symbol.intern("JAVA.LANG.BOOLEAN");
  private static Symbol JAVA_LANG_STRING_           = Symbol.intern("JAVA.LANG.STRING");

  static
  {
    try {

      // compiled from the G2 documentation guide see reserved words
      G2ReservedSymbolsHashTable = new Hashtable();
      G2ReservedSymbolsHashTable.put("a","_a" ) ;
      G2ReservedSymbolsHashTable.put("above","_above" ) ;
      G2ReservedSymbolsHashTable.put("across","_across" ) ;
      G2ReservedSymbolsHashTable.put("ago","_ago" ) ;
      G2ReservedSymbolsHashTable.put("all","_all" ) ;
      G2ReservedSymbolsHashTable.put("an","_an" ) ;
      G2ReservedSymbolsHashTable.put("and","_and" ) ;
      G2ReservedSymbolsHashTable.put("any","_any" ) ;
      G2ReservedSymbolsHashTable.put("at","_at" ) ;
      //G2ReservedSymbolsHashTable.put("available-frame-vector","_available-frame-vector" ) ;
      G2ReservedSymbolsHashTable.put("average","_average" ) ;
      G2ReservedSymbolsHashTable.put("be","_be" ) ;
      G2ReservedSymbolsHashTable.put("becomes","_becomes" ) ;
      G2ReservedSymbolsHashTable.put("begin","_begin" ) ;
      G2ReservedSymbolsHashTable.put("below","_below" ) ;
      G2ReservedSymbolsHashTable.put("between","_between" ) ;
      G2ReservedSymbolsHashTable.put("by","_by" ) ;
      G2ReservedSymbolsHashTable.put("call","_call" ) ;
      G2ReservedSymbolsHashTable.put("case","_case" ) ;
      G2ReservedSymbolsHashTable.put("change","_change" ) ;
      G2ReservedSymbolsHashTable.put("checking","_checking" ) ;
      G2ReservedSymbolsHashTable.put("collection","_collection" ) ;
      //G2ReservedSymbolsHashTable.put("color-pattern","_color-pattern" ) ;
      G2ReservedSymbolsHashTable.put("conclude","_conclude" ) ;
      G2ReservedSymbolsHashTable.put("connected","_connected" ) ;
      G2ReservedSymbolsHashTable.put("could","_could" ) ;
      G2ReservedSymbolsHashTable.put("count","_count" ) ;
      G2ReservedSymbolsHashTable.put("current","_current" ) ;
      G2ReservedSymbolsHashTable.put("day","_day" ) ;
      G2ReservedSymbolsHashTable.put("days","_days" ) ;
      G2ReservedSymbolsHashTable.put("deviation","_deviation" ) ;
      G2ReservedSymbolsHashTable.put("do","_do" ) ;
      G2ReservedSymbolsHashTable.put("down","_down" ) ;
      G2ReservedSymbolsHashTable.put("during","_during" ) ;
      G2ReservedSymbolsHashTable.put("else","_else" ) ;
      G2ReservedSymbolsHashTable.put("end","_end" ) ;
      G2ReservedSymbolsHashTable.put("every","_every" ) ;
      G2ReservedSymbolsHashTable.put("everything","_everything" ) ;
      G2ReservedSymbolsHashTable.put("exists","_exists" ) ;
      G2ReservedSymbolsHashTable.put("exit","_exit" ) ;
      G2ReservedSymbolsHashTable.put("expiration","_expiration" ) ;
      G2ReservedSymbolsHashTable.put("false","_false" ) ;
      G2ReservedSymbolsHashTable.put("first","_first" ) ;
      G2ReservedSymbolsHashTable.put("focus","_focus" ) ;
      G2ReservedSymbolsHashTable.put("for","_for" ) ;
      G2ReservedSymbolsHashTable.put("format","_format" ) ;
      G2ReservedSymbolsHashTable.put("giving","_giving" ) ;
      G2ReservedSymbolsHashTable.put("go","_go" ) ;
      G2ReservedSymbolsHashTable.put("has","_has" ) ;
      G2ReservedSymbolsHashTable.put("hour","_hour" ) ;
      G2ReservedSymbolsHashTable.put("hours","_hours" ) ;
      G2ReservedSymbolsHashTable.put("if","_if" ) ;
      G2ReservedSymbolsHashTable.put("in","_in" ) ;
      G2ReservedSymbolsHashTable.put("infer","_infer" ) ;
      G2ReservedSymbolsHashTable.put("input","_input" ) ;
      G2ReservedSymbolsHashTable.put("integral","_integral" ) ;
      G2ReservedSymbolsHashTable.put("interpolated","_interpolated" ) ;
      G2ReservedSymbolsHashTable.put("invoke","_invoke" ) ;
      G2ReservedSymbolsHashTable.put("is","_is" ) ;
      G2ReservedSymbolsHashTable.put("last","_last" ) ;
      G2ReservedSymbolsHashTable.put("maximum","_maximum" ) ;
      G2ReservedSymbolsHashTable.put("minimum","_minimum" ) ;
      G2ReservedSymbolsHashTable.put("minute","_minute" ) ;
      G2ReservedSymbolsHashTable.put("minutes","_minutes" ) ;
      G2ReservedSymbolsHashTable.put("moved","_moved" ) ;
      G2ReservedSymbolsHashTable.put("name","_name" ) ;
      G2ReservedSymbolsHashTable.put("named","_named" ) ;
      G2ReservedSymbolsHashTable.put("nearest","_nearest" ) ;
      G2ReservedSymbolsHashTable.put("no","_no" ) ;
      G2ReservedSymbolsHashTable.put("none","_none" ) ;
      G2ReservedSymbolsHashTable.put("not","_not" ) ;
      G2ReservedSymbolsHashTable.put("nothing","_nothing" ) ;
      G2ReservedSymbolsHashTable.put("of","_of" ) ;
      G2ReservedSymbolsHashTable.put("on","_on" ) ;
      G2ReservedSymbolsHashTable.put("one","_one" ) ;
      G2ReservedSymbolsHashTable.put("or","_or" ) ;
      G2ReservedSymbolsHashTable.put("output","_output" ) ;
      G2ReservedSymbolsHashTable.put("over","_over" ) ;
      G2ReservedSymbolsHashTable.put("past","_past" ) ;
      G2ReservedSymbolsHashTable.put("per","_per" ) ;
      G2ReservedSymbolsHashTable.put("product","_product" ) ;
      G2ReservedSymbolsHashTable.put("rate","_rate" ) ;
      G2ReservedSymbolsHashTable.put("repeat","_repeat" ) ;
      G2ReservedSymbolsHashTable.put("return","_return" ) ;
      G2ReservedSymbolsHashTable.put("rules","_rules" ) ;
      G2ReservedSymbolsHashTable.put("same","_same" ) ;
      G2ReservedSymbolsHashTable.put("second","_second" ) ;
      G2ReservedSymbolsHashTable.put("seconds","_seconds" ) ;
      G2ReservedSymbolsHashTable.put("send","_send" ) ;
      G2ReservedSymbolsHashTable.put("sequence","_sequence" ) ;
      G2ReservedSymbolsHashTable.put("set","_set" ) ;
      G2ReservedSymbolsHashTable.put("should","_should" ) ;
      G2ReservedSymbolsHashTable.put("simulated","_simulated" ) ;
      G2ReservedSymbolsHashTable.put("standard","_standard" ) ;
      G2ReservedSymbolsHashTable.put("start","_start" ) ;
      G2ReservedSymbolsHashTable.put("structure","_structure" ) ;
      G2ReservedSymbolsHashTable.put("subworkspace","_subworkspace" ) ;
      G2ReservedSymbolsHashTable.put("sum","_sum" ) ;
      G2ReservedSymbolsHashTable.put("symbol","_symbol" ) ;
      G2ReservedSymbolsHashTable.put("that","_that" ) ;
      G2ReservedSymbolsHashTable.put("the","_the" ) ;
      G2ReservedSymbolsHashTable.put("then","_then" ) ;
      G2ReservedSymbolsHashTable.put("there","_there" ) ;
      G2ReservedSymbolsHashTable.put("this","_this" ) ;
      G2ReservedSymbolsHashTable.put("to","_to" ) ;
      G2ReservedSymbolsHashTable.put("true","_true" ) ;
      G2ReservedSymbolsHashTable.put("undefined","_undefined" ) ;
      G2ReservedSymbolsHashTable.put("unspecified","_unspecified" ) ;
      G2ReservedSymbolsHashTable.put("until","_until" ) ;
      G2ReservedSymbolsHashTable.put("upon","_upon" ) ;
      G2ReservedSymbolsHashTable.put("value","_value" ) ;
      G2ReservedSymbolsHashTable.put("values","_values" ) ;
      G2ReservedSymbolsHashTable.put("via","_via" ) ;
      G2ReservedSymbolsHashTable.put("wait","_wait" ) ;
      G2ReservedSymbolsHashTable.put("was","_was" ) ;
      G2ReservedSymbolsHashTable.put("week","_week" ) ;
      G2ReservedSymbolsHashTable.put("weeks","_weeks" ) ;
      G2ReservedSymbolsHashTable.put("were","_were" ) ;
      G2ReservedSymbolsHashTable.put("when","_when" ) ;
      G2ReservedSymbolsHashTable.put("will","_will" ) ;
      G2ReservedSymbolsHashTable.put("with","_with" ) ;
      G2ReservedSymbolsHashTable.put("workspace","_workspace" ) ;
      G2ReservedSymbolsHashTable.put("yes","_yes" ) ;

      ConflictingJavaG2AttributeNamesHashTable = new Hashtable();
      ConflictingJavaG2AttributeNamesHashTable.put("notes","_notes");
      ConflictingJavaG2AttributeNamesHashTable.put("authors","_authors");
      ConflictingJavaG2AttributeNamesHashTable.put("instantiate","_instantiate");
      ConflictingJavaG2AttributeNamesHashTable.put("names","_names");
      ConflictingJavaG2AttributeNamesHashTable.put("class","_class");


      // Pre Load Class Lookup information
      // Entries should only be put in this table if there is a type or class already
      // in G2 that will support the data type /class

      IntegerClass = Integer.class;
      LongClass = Long.class;
      ByteClass = Byte.class;
      ShortClass = Short.class;
      FloatClass = Float.class;
      DoubleClass = Double.class;
      BooleanClass = Boolean.class;
      CharacterClass = Character.class;
      MethodClass = Method.class;
      FieldClass = Field.class;

      G2TypeFromJavaClassHashtable = new Hashtable();
      G2TypeFromJavaClassHashtable.put(Integer.TYPE, "INTEGER");
      G2TypeFromJavaClassHashtable.put(Boolean.TYPE, "TRUTH-VALUE");
      G2TypeFromJavaClassHashtable.put(Double.TYPE,  "FLOAT");

      G2TypeFromJavaClassHashtable.put(Sequence.class, "SEQUENCE");
      G2TypeFromJavaClassHashtable.put(Structure.class, "STRUCTURE");
      G2TypeFromJavaClassHashtable.put(String.class, "TEXT");
      G2TypeFromJavaClassHashtable.put(Symbol.class, "SYMBOL");
      G2TypeFromJavaClassHashtable.put(Number.class, "QUANTITY");
      G2TypeFromJavaClassHashtable.put(Void.TYPE, "");

      // Get at Class for arrays, so create dummy ones (anybody know different ?)
      // vkp - 08/27/97 - You can try Class.forName ("[Ljava.lang.Integer;") etc.
      Class arr_int_class = (new int[0]).getClass();
      Class arr_double_class  = (new double[0]).getClass();
      Class arr_float_class   = (new float[0]).getClass();
      Class arr_boolean_class = (new boolean[0]).getClass();
      Class arr_byte_class    = (new byte[0]).getClass();
      Class arr_char_class    = (new char[0]).getClass();
      Class arr_short_class   = (new short[0]).getClass();
      Class arr_long_class    = (new long[0]).getClass();
      // Special classes are required for Java Raw array types
      G2TypeFromJavaClassHashtable.put(arr_char_class,   "CLASS JAVA.LANG.CHARACTER.TYPE@[@]");
      G2TypeFromJavaClassHashtable.put(arr_byte_class,   "CLASS JAVA.LANG.BYTE.TYPE@[@]");
      G2TypeFromJavaClassHashtable.put(arr_int_class,    "CLASS JAVA.LANG.INTEGER.TYPE@[@]");
      G2TypeFromJavaClassHashtable.put(arr_double_class, "CLASS JAVA.LANG.DOUBLE.TYPE@[@]");
      G2TypeFromJavaClassHashtable.put(arr_boolean_class, "CLASS JAVA.LANG.BOOLEAN.TYPE@[@]");
      G2TypeFromJavaClassHashtable.put(arr_float_class,   "CLASS JAVA.LANG.FLOAT.TYPE@[@]");
      G2TypeFromJavaClassHashtable.put(arr_short_class,   "CLASS JAVA.LANG.SHORT.TYPE@[@]");
      G2TypeFromJavaClassHashtable.put(arr_long_class,   "CLASS JAVA.LANG.LONG.TYPE@[@]");

      G2TypeFromJavaClassHashtable.put(Long.TYPE,      "CLASS " + JAVA_LANG_LONG_TYPE_.getPrintValue());
      G2TypeFromJavaClassHashtable.put(Byte.TYPE,      "CLASS " + JAVA_LANG_BYTE_TYPE_.getPrintValue());
      G2TypeFromJavaClassHashtable.put(Short.TYPE,     "CLASS " + JAVA_LANG_SHORT_TYPE_.getPrintValue());
      G2TypeFromJavaClassHashtable.put(Character.TYPE, "CLASS " + JAVA_LANG_CHARACTER_TYPE_.getPrintValue());
      G2TypeFromJavaClassHashtable.put(Float.TYPE,     "CLASS " + JAVA_LANG_FLOAT_TYPE_.getPrintValue());
      G2TypeFromJavaClassHashtable.put(Object.class,   "ITEM-OR-VALUE");

      G2ReturnTypeFromJavaClassHashTable = (Hashtable)G2TypeFromJavaClassHashtable.clone();

      // JavaLink will convert native warpper classes and types to the same G2 return types
      // i.e. Integer and int is an INTEGER when returned to G2
      G2ReturnTypeFromJavaClassHashTable.put(LongClass,    "CLASS " + JAVA_LANG_LONG_TYPE_.getPrintValue());
      G2ReturnTypeFromJavaClassHashTable.put(IntegerClass, "INTEGER");
      G2ReturnTypeFromJavaClassHashTable.put(BooleanClass, "TRUTH-VALUE");
      G2ReturnTypeFromJavaClassHashTable.put(DoubleClass,  "FLOAT");
      G2ReturnTypeFromJavaClassHashTable.put(ByteClass,    "INTEGER");
      G2ReturnTypeFromJavaClassHashTable.put(ShortClass,   "INTEGER" );
      G2ReturnTypeFromJavaClassHashTable.put(CharacterClass, "TEXT" );
      G2ReturnTypeFromJavaClassHashTable.put(FloatClass,    "FLOAT");

      G2ReturnTypeFromJavaClassHashTable.put(Integer.TYPE, "INTEGER");
      G2ReturnTypeFromJavaClassHashTable.put(Boolean.TYPE, "TRUTH-VALUE");
      G2ReturnTypeFromJavaClassHashTable.put(Double.TYPE,  "FLOAT");
      G2ReturnTypeFromJavaClassHashTable.put(Byte.TYPE,    "INTEGER");
      G2ReturnTypeFromJavaClassHashTable.put(Short.TYPE,   "INTEGER" );
      G2ReturnTypeFromJavaClassHashTable.put(Character.TYPE, "TEXT" );
      G2ReturnTypeFromJavaClassHashTable.put(Float.TYPE,    "FLOAT");



    } catch (Exception E) { System.err.println(E.toString()); }
  }

  private static Hashtable knownG2TypeClasses = new Hashtable(201);
  private static Hashtable knownPrimitiveTypes = new Hashtable(201);
  private static Hashtable javaClassesThatAreConvertedOnReturnToG2Table = new Hashtable(201);

  static {
    // lookup for Java TYPE object for associated g2 classes acting as java Types
    knownG2TypeClasses.put(JAVA_LANG_INTEGER_TYPE_,   Integer.TYPE);
    knownG2TypeClasses.put(JAVA_LANG_FLOAT_TYPE_,     Float.TYPE);
    knownG2TypeClasses.put(JAVA_LANG_DOUBLE_TYPE_,    Double.TYPE);
    knownG2TypeClasses.put(JAVA_LANG_BYTE_TYPE_,      Byte.TYPE);
    knownG2TypeClasses.put(JAVA_LANG_CHARACTER_TYPE_, Character.TYPE);
    knownG2TypeClasses.put(JAVA_LANG_SHORT_TYPE_,     Short.TYPE);
    knownG2TypeClasses.put(JAVA_LANG_LONG_TYPE_,      Long.TYPE);
    knownG2TypeClasses.put(JAVA_LANG_BOOLEAN_TYPE_,   Boolean.TYPE);

    // lookup for wrapping that occurs, when data received from G2
    knownPrimitiveTypes.put(Integer.class, Integer.TYPE);
    knownPrimitiveTypes.put(Double.class, Double.TYPE);
    knownPrimitiveTypes.put(Boolean.class, Boolean.TYPE);

    // lookup for any Java classes that will get converted by javalink on return to G2
    javaClassesThatAreConvertedOnReturnToG2Table.put(Integer.class,   "INTEGER");
    javaClassesThatAreConvertedOnReturnToG2Table.put(Integer.TYPE,    "INTEGER");
    javaClassesThatAreConvertedOnReturnToG2Table.put(Byte.class,      "INTEGER");
    javaClassesThatAreConvertedOnReturnToG2Table.put(Byte.class,      "INTEGER");
    javaClassesThatAreConvertedOnReturnToG2Table.put(Short.class,     "INTEGER");
    javaClassesThatAreConvertedOnReturnToG2Table.put(Short.TYPE,      "INTEGER");
    javaClassesThatAreConvertedOnReturnToG2Table.put(Float.class,     "FLOAT");
    javaClassesThatAreConvertedOnReturnToG2Table.put(Float.TYPE,      "FLOAT");
    javaClassesThatAreConvertedOnReturnToG2Table.put(Long.class,      "CLASS " + JAVA_LANG_LONG_TYPE_.getPrintValue());
    javaClassesThatAreConvertedOnReturnToG2Table.put(Long.TYPE,       "CLASS " + JAVA_LANG_LONG_TYPE_.getPrintValue());
    javaClassesThatAreConvertedOnReturnToG2Table.put(Double.class,    "FLOAT");
    javaClassesThatAreConvertedOnReturnToG2Table.put(Double.TYPE,     "FLOAT");
    javaClassesThatAreConvertedOnReturnToG2Table.put(Boolean.class,   "TRUTH-VALUE");
    javaClassesThatAreConvertedOnReturnToG2Table.put(Boolean.TYPE,    "TRUTH-VALUE");
    javaClassesThatAreConvertedOnReturnToG2Table.put(String.class,    "TEXT");
    javaClassesThatAreConvertedOnReturnToG2Table.put(Symbol.class,    "SYMBOL");
    javaClassesThatAreConvertedOnReturnToG2Table.put(Sequence.class,  "SEQUENCE");
    javaClassesThatAreConvertedOnReturnToG2Table.put(Structure.class, "STRUCTURE");
  }

  private static Hashtable knownG2Classes = new Hashtable(201);
  private static Symbol JAVA_LANG_INTEGER_TYPE_ARRAY_     = Symbol.intern("JAVA.LANG.INTEGER.TYPE[]");
  private static Symbol JAVA_LANG_FLOAT_TYPE_ARRAY_       = Symbol.intern("JAVA.LANG.FLOAT.TYPE[]");
  private static Symbol JAVA_LANG_DOUBLE_TYPE_ARRAY_      = Symbol.intern("JAVA.LANG.DOUBLE.TYPE[]");
  private static Symbol JAVA_LANG_BYTE_TYPE_ARRAY_        = Symbol.intern("JAVA.LANG.BYTE.TYPE[]");
  private static Symbol JAVA_LANG_CHARACTER_TYPE_ARRAY_   = Symbol.intern("JAVA.LANG.CHARACTER.TYPE[]");
  private static Symbol JAVA_LANG_SHORT_TYPE_ARRAY_       = Symbol.intern("JAVA.LANG.SHORT.TYPE[]");
  private static Symbol JAVA_LANG_LONG_TYPE_ARRAY_        = Symbol.intern("JAVA.LANG.LONG.TYPE[]");
  private static Symbol JAVA_LANG_BOOLEAN_TYPE_ARRAY_     = Symbol.intern("JAVA.LANG.BOOLEAN.TYPE[]");

  static {
    knownG2Classes.put(JAVA_LANG_INTEGER_TYPE_ARRAY_,   "[I");
    knownG2Classes.put(JAVA_LANG_FLOAT_TYPE_ARRAY_,     "[F");
    knownG2Classes.put(JAVA_LANG_DOUBLE_TYPE_ARRAY_,    "[D");
    knownG2Classes.put(JAVA_LANG_BYTE_TYPE_ARRAY_,      "[B");
    knownG2Classes.put(JAVA_LANG_CHARACTER_TYPE_ARRAY_, "[C");
    knownG2Classes.put(JAVA_LANG_SHORT_TYPE_ARRAY_,     "[S");
    knownG2Classes.put(JAVA_LANG_LONG_TYPE_ARRAY_,      "[J");
    knownG2Classes.put(JAVA_LANG_BOOLEAN_TYPE_ARRAY_,   "[Z");
    knownG2Classes.put(JAVA_LANG_INTEGER_,              "java.lang.Integer");
    knownG2Classes.put(JAVA_LANG_FLOAT_,                "java.lang.Float");
    knownG2Classes.put(JAVA_LANG_DOUBLE_,               "java.lang.Double");
    knownG2Classes.put(JAVA_LANG_BYTE_,                 "java.lang.Byte");
    knownG2Classes.put(JAVA_LANG_CHARACTER_,            "java.lang.Character");
    knownG2Classes.put(JAVA_LANG_SHORT_,                "java.lang.Short");
    knownG2Classes.put(JAVA_LANG_LONG_,                 "java.lang.Long");
    knownG2Classes.put(JAVA_LANG_BOOLEAN_,              "java.lang.Boolean");
    knownG2Classes.put(JAVA_LANG_STRING_,               "java.lang.String");
  }

  /**
   * Get the Java Type class T for a G2 Class name that represents T, null if no association
   */
  public static Class getJavaTypeForG2Class(Symbol g2ClassName) {
    return (Class)knownG2TypeClasses.get(g2ClassName);
  }
  
  /**
   * Return the Java Type class for a given wrapped primitive, null
   * if Javalink does not wrap the primitive class
   */
   public static Class getJavaTypeForG2WrappedPrimitive(Class javalinkPrimitiveType) {
    return (Class)knownPrimitiveTypes.get(javalinkPrimitiveType);
  }

  /**
   * Indicate if a java attribute name will conflict with a system attribute slot of
   * a G2 class definition
   *
   */
  public static String checkAndReMapAttributeNames(String javaAttributeName){

    String forbiddenAttributeNameLc = javaAttributeName.toLowerCase();

    // check for clashes between single word java attributes
    // and g2 class definition attributes
    String forbiddenAttributeName = (String)
      ConflictingJavaG2AttributeNamesHashTable.get(forbiddenAttributeNameLc);
    if (forbiddenAttributeName == null)
      forbiddenAttributeName = (String)
	G2ReservedSymbolsHashTable.get(forbiddenAttributeNameLc);
    if (forbiddenAttributeName == null)
      forbiddenAttributeName = javaAttributeName;

    //System.out.println("checking " + javaAttributeName + " , " + forbiddenAttributeName +"\n");

    return forbiddenAttributeName;
  }

  private static Class exportedG2Class = ExportedG2Class.class;

  private static boolean isExportedClass(Class java_class) {
    // Check if that java_class implemented ExportedG2Class
    // ensuring that the assignment check is made with the same classloaders
    try {
      // This also gets around a bug in JDK1.1.8 isAssignableFrom...see JDC BUG 4239879
      ClassLoader loader = java_class.getClassLoader();
      if (loader == null) {
	Class theClass = Class.forName(java_class.getName());
	return exportedG2Class.isAssignableFrom(theClass);
      }
      else {
	Class theClass = loader.loadClass(java_class.getName());
	Class exportedG2ClassAlt = loader.loadClass(exportedG2Class.getName());
	return exportedG2ClassAlt.isAssignableFrom(theClass);
      }
    } catch (ClassNotFoundException e) {
      //e.printStackTrace();
    }
    return false;
  }

  /**
   * Return the G2 Type that G2 would need to pass to JavaLink so that it would
   * create a specified java class
   */
  public static String getG2TypeFromJavaClass(Class java_class) {
    //System.out.println("getG2TypeFromJavaClass\n        ------->" + java_class.toString());
    //System.out.println("        ------->" + getTypeFromHashTable(java_class, G2TypeFromJavaClassHashtable));
    // Exported Items translate directly to G2 items of the same class
    if (isExportedClass(java_class)) {
      String classname = java_class.getName();
      classname = classname.substring(classname.lastIndexOf(".")+1);
      //System.out.println(classname);
      return "CLASS " + createG2ClassNameFromJavaClassName(classname).toString();
    }
    return getTypeFromHashTable(java_class, G2TypeFromJavaClassHashtable);
    //return (String)G2TypeFromJavaClassHashtable.get(java_class);
  }

  /**
   * Return the G2 Type that Javalink would pass to G2 for a given java class
   */
  public static String getG2ReturnTypeFromjavaClass(Class java_class) {
    //System.out.println("getG2ReturnTypeFromJavaClass\n        ------->" + java_class.toString());
    //System.out.println(getTypeFromHashTable(java_class, G2ReturnTypeFromJavaClassHashTable));
    if (isExportedClass(java_class)) {
      String classname = java_class.getName();
      classname = classname.substring(classname.lastIndexOf(".")+1);
      //System.out.println(classname);
      return "CLASS " + createG2ClassNameFromJavaClassName(classname).toString();
    }
    return  getTypeFromHashTable(java_class, G2ReturnTypeFromJavaClassHashTable);
    //return (String)G2ReturnTypeFromJavaClassHashTable.get(java_class);
  }

  /**
   *  Return the G2 Type that G2 would need to pass to JavaLink so that it would
   * create a specified java class (null if not found)
   */
  public static String getG2TypeFromJavaClassOrNull (Class java_class) {
    //System.out.println("getG2TypeFromJavaClassOrNull\n        ------->" + java_class.toString());
    //System.out.println("        ------->" + getTypeFromHashTable(java_class, G2TypeFromJavaClassHashtable));
    if (isExportedClass(java_class)) {
      String classname = java_class.getName();
      classname = classname.substring(classname.lastIndexOf(".")+1);
      //System.out.println(classname);
      return createG2ClassNameFromJavaClassName(classname).toString();
    }
    return getTypeFromHashTable(java_class, G2TypeFromJavaClassHashtable);
    //return (String)G2TypeFromJavaClassHashtable.get(java_class);
  }

  /** 
   * Generic search for a class in a hashtable.
   * Deal with Multi-dimensional arrays, G2 will have one array which can contains other arrays
   */
  private static String getTypeFromHashTable(final Class java_class, Hashtable typeTable) {
    String type = (String)typeTable.get(java_class);
    if (type != null) {
    	return type;
    }

    Class javaClass = java_class;
    while (javaClass.isArray()) {
      Class componentType = javaClass.getComponentType();
      if (componentType == null){
    	  return null;
      }
      type = (String)typeTable.get(javaClass);
      if (type != null){
    	  return type;
      }
      javaClass = componentType;
    }

    return null;
  }

  public static boolean isJavaClassHandledByJavaLinkOnReturnToG2(Class javaClass) {
    return (javaClassesThatAreConvertedOnReturnToG2Table.get(javaClass) == null ? false : true);
  }

  /**
   * General debug method to print out the public fields of an object.
   */
  public static void printFields(Object obj)
  {
    Field []fields = null;

    try {
      fields = obj.getClass().getFields();
	}
    catch (SecurityException E) { /* no class information */ }



    for (int i=0; i<fields.length; i++)
      {

	try {
	      System.out.println("Field Name " + fields[i].getName() + " is " + fields[i].get(obj));
	}
	catch (java.lang.IllegalAccessException E) {}
      }
  }



  /**
   * Create a G2 "-" separated name from a misxed case Java name.
   * A "-" is inserted between each occurrance of a lower/upper case transition
   */
  public static Symbol createG2NameFromJavaName(String java_name)
  {
    char cchar;
    char cchar_p1;
    String field_name;
    StringBuffer g2_name_buffer;
    int length = java_name.length();
    int i;

    g2_name_buffer = new StringBuffer(length);
    for (i=0; i<java_name.length(); i++)
      {
	// Look for each lower/captical compination and insert a "-"
	cchar = java_name.charAt(i);
	g2_name_buffer.append(cchar);
	if ((i+1 < length))
	    {
	      cchar_p1 = java_name.charAt(i+1);
	      boolean condition1 = (Character.isLowerCase(cchar) || Character.isDigit(cchar))
	    		  	&& Character.isUpperCase(cchar_p1);
	      
	      // Also look for cap words before start captialized word
	      // (e.g. ThisFIELDWillWork -> This-FIELD-Will-Work)
	      boolean condition2 = (i+2 < length) && Character.isUpperCase(cchar) && Character.isUpperCase(cchar_p1) 
	    		  			&& Character.isLowerCase(java_name.charAt(i+2));
	      if (condition1 || condition2)
	    	  g2_name_buffer.append("-");
	    }
      }

    return Symbol.intern(g2_name_buffer.toString().toUpperCase());
  }

  /**
   * Create a G2 "-" separated class name from a misxed case Java class name
   * A "-" is inserted between each occurrance of a lower/upper case transition.
   *
   *@param java_class_name The java class name to convert
   */
  public static Symbol createG2ClassNameFromJavaClassName(String java_class_name)
  {
    return createG2NameFromJavaName(java_class_name);
  }

  /**
   * @undocumented
   * Used by G2JavaStubGenerator to get the bean class name in G2
   * for a specific Java class that has been imported.
   */
  public static Symbol getBeanClassNameForG2ProxyClassName (Symbol G2_JavaProxyClassName) {
    return Symbol.intern (G2_JavaProxyClassName.getPrintValue () + "-BEAN");
  }

  /**
   * Create a Java Name from a G2 Name where every "-" is removed
   * and each word is capatilized at the location of the "-" removal.
   * The "?" is replaced with a "Q".
   * -vkp, 9/26/97 Fixed '/' to be treated exactly like a '-' in a name
   *
   *@param g2_name_symbol The g2 name symbol
   */
  public static String createJavaNameFromG2Name(Symbol g2_name_symbol)
  {
    // Remove all "-" and capatlize each word
    String g2_name = g2_name_symbol.toString().toLowerCase();
    int length = g2_name.length();
    StringBuffer java_name_buffer = new StringBuffer(length);
    boolean cap_next_char = false;
    char cchar;
    // This is a sequence of chars not allowed by Java in identifiers
    String notallowedchars = "!@#%^&*()[].,<>+|=`~\"'\\";

    for (int i=0; i<length; i++)
      {
	// Look for each "-", remove and capatlize word
	cchar = g2_name.charAt(i);
	if ((cchar != '-') && (cchar != '/'))
	  {
	    if (cchar == '?')
	      cchar = 'Q';
	    else if (notallowedchars.indexOf(cchar) > -1)
	      cchar = '_';
	    else if (cchar == '$')
	      cap_next_char = true;
	    else if (cap_next_char)
	      {
		cchar = Character.toUpperCase(cchar);
		cap_next_char = false;
	      }

	    java_name_buffer.append(cchar);
	  }
	else
	  cap_next_char = true;
      }

    // G2 allows first char to be a number, not allowed by Java, append an "n"
    if (java_name_buffer.length() > 0 && Character.isDigit(java_name_buffer.charAt(0)))
     java_name_buffer.insert(0, 'n');

    // replace any class qualifier makers :: with _
    return java_name_buffer.toString().replace(':','_');
  }

  /**
   * Create a Java Class Name from a G2 Class Name where every "-" is removed
   * and each word is capatilized at the location of the "-" removal and the
   * first character is capitalized.
   *
   *@param g2_name_symbol The g2 name symbol
   */
  public static String createJavaClassNameFromG2ClassName(Symbol g2_name_symbol)
  {
    if (g2_name_symbol.toString().equals("")){
    	return "";
    }
    StringBuffer java_class_name = new StringBuffer(createJavaNameFromG2Name(g2_name_symbol));
    java_class_name.setCharAt(0, Character.toUpperCase(java_class_name.charAt(0)));

    return java_class_name.toString();
  }

  //test
  /*
  public static void main(String []args)
  {
    CmdLineArgHandler cmdline = new CmdLineArgHandler(args);

    try
      {
	String javafieldname = cmdline.getOptionValue("-javafieldname");
	String g2attname = cmdline.getOptionValue("-g2attname");
	if (javafieldname != null)
	  {
	    System.out.println("G2 Att Name for Java Field Name is " +
			       createG2NameFromJavaName(javafieldname));
	  }
	if (g2attname != null)
	  {
	    System.out.println("Java Field Name for G2 Att Name is " +
			       createJavaNameFromG2Name(Symbol.intern(g2attname)));
	  }
      } catch (Exception E) { System.out.println(E.toString());}

  }
  */

  public static final String companyName = "Gensym Corporation";
  // fix this: dates are hardcoded for now
  //  private static dateFormat = DateFormat.getInstance();

  /** Given an array of <code>String</code>s that represent the slot-names
   * of a G2 class, this method will write an initial Java class file
   * has placeholders for all the slots. Does very little in the way
   * of pretty-printing. */
  public static void generateJavaBeanFile(String className, String packageName,
					  OutputStream stream,
					  String[] imports,
					  String[] slotNames,
					  String[] slotTypes)
  throws IOException
  {
    PrintWriter output = new PrintWriter(new OutputStreamWriter(stream, Charset.defaultCharset()), true);
    //    Date now = new Date();

    output.println("/*");
    output.println(" *  Copyright (c) " +"1997 " + companyName +
		   ".All Rights Reserved.");
    output.println(" *");
    output.println(" *      " + className + ".java");
    output.println(" *"); 
    output.println(" * Description:");
    output.println(" *"); 
    output.println(" *      Author:");
    output.println(" *"); 
    output.println(" * Modifications:");
    output.println(" *"); 
    output.println(" */");

    output.println("package " + packageName +";"); 
    output.println("");

    //imports, java first.
    output.println("import java.util.Locale;");
    output.println("import java.io.Serializable;");
    for (int i = 0; i < imports.length; i++) {
      if(imports[i] != null && !(imports[i]).equals(""))
	output.println("import " + imports[i] + ";");
      else
	output.println("");
    }

    output.println("import com.gensym.util.*;");
    output.println("");

    output.println("public class " + className + " implements Serializable {");
    output.println("");

    output.println("  private static Resource i18n =");
    output.println("  new Resource(\"" + packageName +
		   ".Messages\", Locale.getDefault());");
    output.println("  private static MessageKey traceKey = ");
    output.println("  Trace.registerMessageKey(\"" + packageName + "\", " +
		   className + ".class);");
    output.println("");

    String[] jSlotNames = new String[slotNames.length];
    for(int i = 0; i < slotNames.length; i++) {
      jSlotNames[i] = slotNameFromG2Slot(slotNames[i]);
    }

    // member variables
    generateMemberVariables(output, slotTypes, jSlotNames, className);

    output.println("");

    generateConstructors(output, slotTypes, jSlotNames, className);

    output.println("");

    generatePropertyAccessors(output, slotTypes, jSlotNames, className);

    output.println("}");
  }

  protected static void generateMemberVariables(PrintWriter output,
						String[] slotTypes,
						String[] jSlotNames,
						String className) {
    for(int i = 0; i < jSlotNames.length; i++) {
      output.println("  private " + slotTypes[i] + " " + jSlotNames[i] + ";");
    }
  }

  protected static void generateConstructors(PrintWriter output,
					     String[] slotTypes,
					     String[] jSlotNames,
					     String className) {
    // null arg constructor
    // Why does this take slotTypes and names??? - vkp 9/12/97
    output.println("  public " + className + "() {");
    output.println("    super();");
    output.println("  }");
  }

  protected static void generateSetBody(PrintWriter output,
					String currentType,
					String currentSlot,
					String className) {
    output.println("    this." + currentSlot + " = " + currentSlot + ";");
  }

  protected static void generateGetBody(PrintWriter output,
					String currentType,
					String currentSlot,
					String className) {
    output.println("    return " + currentSlot + ";");
  }

  protected static void generatePropertyAccessors(PrintWriter output,
						  String[] slotTypes,
						  String[] jSlotNames,
						  String className) {
    // slot accessors
    for(int i = 0; i < jSlotNames.length; i++) {
      String currentSlot = jSlotNames[i];
      String currentType = slotTypes[i];
      output.println("  public void set" + initCap(currentSlot) +
		     "(" + currentType + " " + currentSlot + ") {");
      generateSetBody(output, currentType, currentSlot, className);
      output.println("  }"); 
      output.println("");

      output.println("  public " + currentType + " get" +
		     initCap(currentSlot) + "() {");
      generateGetBody(output, currentType, currentSlot, className);
      output.println("  }"); 
      output.println("");
    }
  }

  /** really just drops the terminating "Q" from names that have them */
  public static String slotNameFromG2Slot(String g2Slot) {
    String jSlot = createJavaNameFromG2Name(Symbol.intern(g2Slot));
    if (jSlot.endsWith("Q"))
      return jSlot.substring(0, jSlot.length() - 1);
    else
      return jSlot;
  }

  public static String initCap(String in) {
    StringBuffer buf = new StringBuffer(in);
    buf.setCharAt(0, Character.toUpperCase(in.charAt(0)));
    return buf.toString();
  }

  public static String dotPackageFromSlashPackage (String slashPackage) {
    StringBuffer sb = new StringBuffer (slashPackage);
     for (int i=0; i<sb.length (); i++)
       if (sb.charAt (i) == '/')
	 sb.setCharAt (i, '.');
     return sb.toString ();
  }
}

