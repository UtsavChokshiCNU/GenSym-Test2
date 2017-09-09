/** com.gensym.util.ClassConstants.java
 *  Defines references to the names and VM descriptors of common classes.
**/

package com.gensym.util;

public interface ClassConstants {
  public static final String OBJECT_ARRAY_DESC = "[Ljava/lang/Object;";
  public static final String SYMBOL_CLASS_NAME = "com.gensym.util.Symbol";
  public static final String SYMBOL_CLASS_DESC = "Lcom/gensym/util/Symbol;";
  public static final String SYMBOL_ARRAY_CLASS_DESC = "[Lcom/gensym/util/Symbol;";
  public static final String SEQUENCE_DESC = "Lcom/gensym/util/Sequence;";
  public static final String SEQUENCE_ARRAY_DESC = "[" + SEQUENCE_DESC;
  public static final String STRUCTURE_DESC = "Lcom/gensym/util/Structure;";
  public static final String STRUCTURE_ARRAY_DESC = "[" + STRUCTURE_DESC;
  public static final String G2_ACCESS_EXCEPTION_CLASS_NAME = "com.gensym.jgi.G2AccessException";
  public static final String G2_ACCESS_EXCEPTION_CLASS_DESC = "Lcom/gensym/jgi/G2AccessException;";
  public static final String CONTEXT_CLASS_NAME = "com.gensym.jgi.G2Access";
  public static final String CONTEXT_CLASS_DESC = "Lcom/gensym/jgi/G2Access;";
  public static final String NUMBER_CLASS_NAME = "java.lang.Number";
  public static final String NUMBER_CLASS_DESC = "Ljava/lang/Number;";
}
