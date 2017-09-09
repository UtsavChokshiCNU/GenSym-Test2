/** com.gensym.util.ClassConstants.java
 *  Defines references to the names and VM descriptors of common classes.
**/

package com.gensym.jgi.download;

import com.gensym.classtools.*;

public interface ClassConstants extends RuntimeConstants {
  public static final String 
      OBJECT_ARRAY_DESC              = "[Ljava/lang/Object;",
      SYMBOL_CLASS_NAME              = "com.gensym.util.Symbol",
      SYMBOL_CLASS_DESC              = "Lcom/gensym/util/Symbol;",
      SYMBOL_ARRAY_CLASS_DESC        = "[" + SYMBOL_CLASS_DESC,
      SEQUENCE_DESC                  = "Lcom/gensym/util/Sequence;",
      SEQUENCE_ARRAY_DESC            = "[" + SEQUENCE_DESC,
      STRUCTURE_DESC                 = "Lcom/gensym/util/Structure;",
      STRUCTURE_ARRAY_DESC           = "[" + STRUCTURE_DESC,
      G2_ACCESS_EXCEPTION_CLASS_NAME = "com.gensym.jgi.G2AccessException",
      G2_ACCESS_EXCEPTION_CLASS_DESC = "Lcom/gensym/jgi/G2AccessException;",
      CONTEXT_CLASS_NAME             = "com.gensym.jgi.G2Access",
      CONTEXT_CLASS_DESC             = "Lcom/gensym/jgi/G2Access;",
      G2CLASSSYMBOLS_CLASS_NAME      = "com.gensym.util.symbol.G2ClassSymbols",
      G2__BASE_CLASS_NAME            = "com.gensym.g2export.G2__Base",
      G2__BASE_CLASS_DESC            = "Lcom/gensym/g2export/G2__Base;",
      G2__BASEIMPL_CLASS_NAME        = "com.gensym.g2export.G2__BaseImpl",
      G2__BASEIMPL_CLASS_DESC        = "Lcom/gensym/g2export/G2__BaseImpl;";
	
  

  public static final Access 
      PUBLIC_STATIC_FINAL_ACCESS     = new Access (ACC_PUBLIC | ACC_STATIC | ACC_FINAL),
      PUBLIC_ABSTRACT_ACCESS         = new Access (ACC_PUBLIC | ACC_ABSTRACT ),
      PUBLIC_INTERFACE_ACCESS        = new Access (ACC_PUBLIC | ACC_INTERFACE ),
      PUBLIC_ACCESS                  = new Access (ACC_PUBLIC),
      PRIVATE_ACCESS                 = new Access (ACC_PRIVATE),
      STATIC_FINAL_ACCESS            = new Access (ACC_STATIC | ACC_FINAL);
      
      

}
