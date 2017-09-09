/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 *          com.gensym.com.VariantSafeArrayTest.java
 *
 *   Author: Stephen Flores
 */
package com.gensym.com;

import java.util.*;

public class VariantSafeArrayTest {

  public static void main(String[] args) {
    VariantSafeArray array;
/*
    int intArray[] = {1,2,3,4};
    Variant testVariants[] = {
      new Variant((short) 0),
      new Variant(1),
      new Variant((float)2.2),
      new Variant(3.3),
      new Variant((new GregorianCalendar( 1999, 7, 5 )).getTime()),
      new Variant("five"),
      new Variant(true),
      new Variant((byte)7),
      new Variant(intArray)
    };
    int lBound[] = {0};
    int uBound[] = {testVariants.length - 1};

    int i = 0;
    int size = 0;
    int dimensions = 0;

    array = new VariantSafeArray(testVariants);

    if (!array.isValid()) {
      System.out.println("array is not valid");
      return;
    } else {
      System.out.println("array is valid");
    }

    dimensions = array.getDimensions();
    System.out.println("dimensions = " + dimensions);
   
    size = array.getUBound(1) - array.getLBound(1) + 1;
    System.out.println("size = " + size);

    print(array);

    System.out.println("");

    array.setVariant(0, new Variant(0));
    if (array.getVariant(0).equals(new Variant(0)))
      System.out.println("Put 1 element and get 1 element worked.");

    System.out.println("array.lock()");
    array.lock();
    
    System.out.println("array.dispose() = " + array.dispose());

    System.out.println("array.unlock()");
    array.unlock();

    System.out.println("array.dispose() = " + array.dispose());
    System.out.println("array.isValid() = " + array.isValid());

    array = new VariantSafeArray(lBound, uBound);
    fillAndPrint(array, testVariants);

    array = new VariantSafeArray(6);
    fillAndPrint(array, testVariants);
*/
    int x;
    int y;
    int lBounds[] = {1, 1};
    int uBounds[] = {5, 7};
    int indexes[] = new int[2];

    array = new VariantSafeArray(lBounds, uBounds);
    System.out.println("array [" + array.getLBound(1) + " ... " +
                       array.getUBound(1) + "] [" +
                       array.getLBound(2) + " ... " +
                       array.getUBound(2) + "]");
    for (x = lBounds[0]; x <= uBounds[0]; x++) {
      for (y = lBounds[1]; y <= uBounds[1]; y++) {
        indexes[0] = x;
        indexes[1] = y;
        array.setVariant(x + ((y - lBounds[1]) *(uBounds[0] - lBounds[0] + 1)),
          new Variant(new IntSafeArray(indexes)));
      }
    }

    System.out.println(array);

    System.out.println("\nPress Enter to continue...");
    try {
      System.in.read();
    } catch (Throwable e) {}
  }

  static void fillAndPrint(VariantSafeArray array, Variant values[]) {
    int indexes[] = {0};

    array.setVariants(indexes, values);
    print(array);
  }

  static void print(VariantSafeArray array) {
    print("array", array);
  }

  static void print(String name, VariantSafeArray array) {
    Variant variants[];
    int i;

    variants = array.getAllVariants();
    if (variants == null) {
      System.out.println("Could not get any elements to print.");
      return;
    }

    for (i = 0; i < variants.length ; i++)
      System.out.println(name + "[" + i + "] = " + variants[i]);
  }
}
