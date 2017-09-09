/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 Sorter.java
 *
 */

package com.gensym.util;

import java.lang.reflect.Array;
import java.lang.reflect.Method;
import com.gensym.message.Resource;
/**
 *  This class sorts a given array of elements.  The array of elements must be
 *  a homogeneous list, i.e., all elements in the array must be of the same type.  
 *  The array elements may be primitive types or Objects, but may not be null.
 *  The comparison method used to compare elements may be provided via a parameter 
 *  to the sort method or via setDefaultCompareMethod(Class, Method) in 
 *  SorterSupporter.
 * <p>
 *  If the comparison method is provided via a parameter to the method call, then 
 *  the comparison method must be public and static, and take two parameters. 
 *  The two parameters must be the same type as the array.
 * </p>
 *  A method provided as a parameter always overrides one set in SorterSupport.
 *  @see com.gensym.util.SorterSupport
 */ 

public class Sorter{

  public static final int ASCENDING = 0;
  public static final int DESCENDING = 1;

  private static final Resource i18n = Resource.getBundle("com/gensym/util/Messages");

  /** Sort <code>array</code> by the given sort order, either ASCENDING or 
   *  DESCENDING. A comparison method for the type of array must have already
   *  been registered with SorterSupport.
   *  <p>
   *  This method returns true if any elements changed position during sorting.
   *  </p>
   *  @see com.gensym.util.SorterSupport
   */
  public static boolean sort(Object array, int sortOrder){
    return sort(array, null, sortOrder, (Method)null);
  }

  /** Sort <code>array</code> by the given sort order, either ASCENDING or 
   *  DESCENDING.  A comparison method for the type of array must have already
   *  been registered with SorterSupport.
   *  In addition, the array(s) in auxillaryLists are sorted in conjunction with 
   *  <code>array</code>, so that the item at the ith position of an auxillary 
   *  list and the item at the ith position of the array end up at the same 
   *  position after sorting is complete. To sort multiple auxillary arrays,
   *  pass in an array of arrays for <code>auxillaryLists</code>.
   * <p>
   *  This method returns true if any elements changed position during sorting.
   *  </p>
   */
  public static boolean sort(Object array, Object[] auxillaryLists, int sortOrder){
    return sort(array, auxillaryLists, sortOrder, (Method)null);
  }

  /** Sort <code>array</code> by the given sort order, either ASCENDING or 
   *  DESCENDING, using the given comparison method. 
   *  <p>
   *  This method returns true if any elements changed position during sorting.
   *  </p>
   */
  public static boolean sort(Object array, int sortOrder, Method compareMethod){
    return sort(array, null, sortOrder, compareMethod);
  }

  /** Sort <code>array</code> by the given sort order, either ASCENDING or 
   *  DESCENDING, using the given comparison method. In addition, the array(s) 
   *  in auxillaryLists are sorted in conjunction with 
   *  <code>array</code>, so that the item at the ith position of an auxillary 
   *  list and the item at the ith position of the array end up at the same 
   *  position after sorting is complete. To sort multiple auxillary arrays,
   *  pass in an array of arrays for <code>auxillaryLists</code>.
   *  <p>
   *  This method returns true if any elements changed position during sorting.
   *  </p>
   */
  public static boolean sort(final Object array, final Object[] auxillaryLists, final int sortOrder, 
		  final Method compareMethod){ 
    //check array
	Method method = compareMethod;
    if (!array.getClass().isArray())
      throw new IllegalArgumentException(i18n.getString("illegalArrayArgument"));
    int length = Array.getLength(array);
    if (length == 0){
    	return false;
    }
    //check comparison method
    if (method != null){ 
      if (!(SorterSupport.verifyMethod(method, array.getClass().getComponentType(), false))) {
    	  throw new IllegalArgumentException(i18n.getString("illegalComparisonMethod"));
      }
    }
    else {
      method = SorterSupport.getDefaultCompareMethod(array.getClass());
      if (method == null)
	throw new IllegalArgumentException(i18n.getString("nullComparisonMethod"));
    }
    //check lengths of auxillary array(s)
    boolean multipleAuxArrays = false;
    if (auxillaryLists != null) {
      if ((auxillaryLists[0] != null) && (auxillaryLists[0].getClass().isArray())){
	multipleAuxArrays = true;
	for (int index=0; index<auxillaryLists.length; index++){
	  Object auxArray = auxillaryLists[index];
	  if (!(auxArray.getClass().isArray()))
	    throw new IllegalArgumentException();
	  if (length != Array.getLength(auxArray)) 
	    throw new IllegalArgumentException(i18n.getString("arrayLengthsMustBeEqual"));
	}
      }
      else if (length != auxillaryLists.length)
	throw new IllegalArgumentException(i18n.getString("arrayLengthsMustBeEqual"));
    }
    //sort
    return bubbleSort(array, auxillaryLists, sortOrder, method, multipleAuxArrays);
  }

  private static void swap(int i, int j, Object array, Object[] auxillaryLists,
			   boolean multipleAuxArrays){
    Object temp = Array.get(array, i);
    Array.set(array, i, Array.get(array, j));
    Array.set(array, j, temp);
    if (auxillaryLists != null){
      if (multipleAuxArrays){
	for (int index=0; index<auxillaryLists.length; index++){
	  Object auxArray = auxillaryLists[index];
	  Object auxTemp = Array.get(auxArray, i);
	  Array.set(auxArray, i, Array.get(auxArray, j));
	  Array.set(auxArray, j, auxTemp);
	}
      }
      else{
	Object auxTemp = auxillaryLists[i];
	auxillaryLists[i] = auxillaryLists[j];
	auxillaryLists[j] = auxTemp;
      }
    }
  }

  private static boolean bubbleSort(Object array, Object[] auxillaryList, 
				    int sortOrder, Method compareMethod, 
				    boolean multipleAuxArrays){
    boolean bubbled = false;
    int length = Array.getLength(array);
    Object[] comparisonArray = new Object[2];
    for (int i=0; i<length; i++){
      for (int j=length-1; j>i; j--){
	comparisonArray[0] = Array.get(array, j);
	comparisonArray[1] = Array.get(array, j-1);
	int comparison;
	try{
	   Integer result = (Integer)compareMethod.invoke(null, comparisonArray);
	   comparison = result.intValue();
	   if (((comparison < 0)&&(sortOrder == ASCENDING)) ||
	       ((comparison > 0)&&(sortOrder == DESCENDING))){ 
	     bubbled = true;
	     swap(j, j-1, array, auxillaryList, multipleAuxArrays);
	   }
	}
	catch (Exception ex){
	  throw new UnexpectedException(ex, ex.toString());
	}
      }
    }
    return bubbled;
  }

}









