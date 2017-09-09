/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 *          com.gensym.com.BooleanSafeArrayTest.java
 *
 *   Author: Stephen Flores
 */
package com.gensym.com;

public class BooleanSafeArrayTest {

  public static void main(String[] args) {
    boolean testBooleans[] = {true, false, true, false, true, false};
    BooleanSafeArray array;
    int lBounds[] = {0};
    int uBounds[] = {5};

    int i = 0;
    int size = 0;
    int dimensions = 0;

    array = new BooleanSafeArray(testBooleans);

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

    array.setBoolean(0, true);
    if (array.getBoolean(0) == true)
      System.out.println("Put 1 element and get 1 element worked.");

    System.out.println("array.lock()");
    array.lock();
    
    System.out.println("array.dispose() = " + array.dispose());

    System.out.println("array.unlock()");
    array.unlock();

    System.out.println("array.dispose() = " + array.dispose());
    System.out.println("array.isValid() = " + array.isValid());

    array = new BooleanSafeArray(lBounds, uBounds);
    fillAndPrint(array, testBooleans);

    array = new BooleanSafeArray(6);
    fillAndPrint(array, testBooleans);

    System.out.println("\nPress Enter to continue...");
    try {
      System.in.read();
    } catch (Throwable e) {}
  }

  static void fillAndPrint(BooleanSafeArray array, boolean values[]) {
    int indexes[] = {0};

    array.setBooleans(indexes, values);
    print(array);
  }

  static void print(BooleanSafeArray array) {
    print("array", array);
  }

  static void print(String name, BooleanSafeArray array) {
    boolean booleans[];
    int i;

    booleans = array.getAllBooleans();
    if (booleans == null) {
      System.out.println("Could not get any elements to print.");
      return;
    }

    for (i = 0; i < booleans.length ; i++)
      System.out.println(name + "[" + i + "] = " + booleans[i]);
  }
}
