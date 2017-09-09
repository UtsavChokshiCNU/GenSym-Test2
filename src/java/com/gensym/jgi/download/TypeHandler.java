
package com.gensym.jgi.download;

import java.util.Hashtable;
import java.util.Enumeration;
import com.gensym.util.*;
import com.gensym.util.symbol.*;

class TypeHandler implements G2TypeSymbols, AttributeTypeSpecificationSymbols, MethodExportSymbols, ExtendedTypeSymbols {

  /**
   *
   */

  static boolean isClassType (Symbol typeName_) {
	boolean condition = typeName_ == null;
	condition = condition || SYMBOL_.equals(typeName_) || TEXT_.equals(typeName_) || TRUTH_VALUE_.equals(typeName_);
	condition = condition || STRUCTURE_.equals(typeName_) || SEQUENCE_.equals(typeName_) || FLOAT_.equals(typeName_);
	condition = condition || INTEGER_.equals(typeName_) || QUANTITY_.equals(typeName_) || ITEM_OR_VALUE_.equals(typeName_);
	condition = condition || TRUTH_VALUE_OR_NULL_.equals(typeName_) || INTEGER_OR_NULL_.equals(typeName_) || FLOAT_OR_NULL_.equals(typeName_);
	
    return !condition;
  }

  /**
   * Returns a symbol naming a G2 type or a class-name.
   */
  static Symbol getTypeFromTypeDescription (Structure typeDescrpn) {
    Symbol returnType = null;
    try {
      Symbol type = (Symbol) typeDescrpn.getAttributeValue (TYPE_OR_OPERATOR_);
      
      boolean condition = type == null;
  	  condition = condition || SYMBOL_.equals(type) || TEXT_.equals(type) || TRUTH_VALUE_.equals(type);
  	  condition = condition || STRUCTURE_.equals(type) || SEQUENCE_.equals(type) || FLOAT_.equals(type);
  	  condition = condition || INTEGER_.equals(type) || QUANTITY_.equals(type) || ITEM_OR_VALUE_.equals(type);

      if (condition)
      returnType = type;
      else
	if (type.equals (INTEGER_RANGE_))
	  returnType = INTEGER_;
      else
	if (type.equals (FLOAT_RANGE_))
	  returnType = FLOAT_;
      else
	if (type.equals (QUANTITY_RANGE_))
	  returnType = QUANTITY_;
      else
	if (type.equals (VALUE_))
	  returnType = ITEM_OR_VALUE_;
      else
	if (type.equals (MEMBER_))
	  returnType = SYMBOL_;
      else
	if (type.equals (CLASS_))
	  returnType = (Symbol) typeDescrpn.getAttributeValue (CLASS_NAME_);
      else
	if (type.equals (OR_) || type.equals (AND_)) {
	  Sequence operands =  (Sequence)typeDescrpn.getAttributeValue (OPERANDS_);
	  returnType = mergeTypesInDescription (operands);
	}
      else
	if (type.equals (NOT_))
	  throw new IllegalArgumentException ("Don't know how to handle this type specification : " + typeDescrpn);
    } catch (NoSuchAttributeException nsae) {}
    //System.out.println ("getTypeFromTypeDescription (" + typeDescrpn + ") = " + returnType);
    return returnType;
  }

  private static Symbol mergeTypesInDescription (Sequence typeStructures) {
    Symbol returnType = null;
    for (Enumeration e = typeStructures.elements (); e.hasMoreElements ();) {
      Structure subType = (Structure) e.nextElement ();
      Symbol newType = getTypeFromTypeDescription (subType);
      if (!returnType.equals(newType))
	returnType = findClosestEnclosingType (newType, returnType);
      if (returnType != null && returnType.equals (ITEM_OR_VALUE_))
	break;
//       }
    }
    return returnType;
  }

  /*
   * -vkp, 10/27/97 This can be *MUCH* more intelligent.
   * Consider separating out the type-specification handling into
   * a general utility class with static methods.
   */
  private static Symbol findClosestEnclosingType (Symbol type1, Symbol type2) {
    if (type1 != null && type2 != null)
      return (type1.equals (type2) ? type1 : ITEM_OR_VALUE_);
    else if (type1 != null || type2 != null){
      Symbol nonNullType = (type1 == null ? type2 : type1);
      Symbol wrappingType = (Symbol) wrappingTypesForPrimitives.get (nonNullType);
      if (wrappingType != null)
	nonNullType = wrappingType;
      return nonNullType;
    } else
      return null;
  }


  private static final Hashtable wrappingTypesForPrimitives = new Hashtable (11);

  static {
    wrappingTypesForPrimitives.put (TRUTH_VALUE_, TRUTH_VALUE_OR_NULL_);
    wrappingTypesForPrimitives.put (INTEGER_, INTEGER_OR_NULL_);
    wrappingTypesForPrimitives.put (FLOAT_, FLOAT_OR_NULL_);
  }

}
