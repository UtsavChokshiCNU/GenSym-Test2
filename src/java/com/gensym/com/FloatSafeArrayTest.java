/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 *          com.gensym.com.FloatSafeArrayTest.java
 *
 *   Author: Stephen Flores
 */
package com.gensym.com;

public class FloatSafeArrayTest {

  public static void main(String[] args) {
    float testFloats[] = {0, 1, 2, 3, 4, 5};
    FloatSafeArray array;
    int lBounds[] = {0};
    int uBounds[] = {5};

    int i = 0;
    int size = 0;
    int dimensions = 0;

    array = new FloatSafeArray(testFloats);

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

    array.setFloat(0, (float)9);
    if (array.getFloat(0) == 9)
      System.out.println("Put 1 element and get 1 element worked.");

    System.out.println("array.lock()");
    array.lock();
    
    System.out.println("array.dispose() = " + array.dispose());

    System.out.println("array.unlock()");
    array.unlock();

    System.out.println("array.dispose() = " + array.dispose());
    System.out.println("array.isValid() = " + array.isValid());

    array = new FloatSafeArray(lBounds, uBounds);
    fillAndPrint(array, testFloats);

    array = new FloatSafeArray(6);
    fillAndPrint(array, testFloats);

    System.out.println("\nPress Enter to continue...");
    try {
      System.in.read();
    } catch (Throwable e) {}
  }

  static void fillAndPrint(FloatSafeArray array, float values[]) {
    int indexes[] = {0};

    array.setFloats(indexes, values);
    print(array);
  }

  static void print(FloatSafeArray array) {
    print("array", array);
  }

  static void print(String name, FloatSafeArray array) {
    float floats[];
    int i;

    floats = array.getAllFloats();
    if (floats == null) {
      System.out.println("Could not get any elements to print.");
      return;
    }

    for (i = 0; i < floats.length ; i++)
      System.out.println(name + "[" + i + "] = " + floats[i]);
  }
}
