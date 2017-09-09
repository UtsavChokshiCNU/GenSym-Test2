/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 *          com.gensym.com.DoubleSafeArrayTest.java
 *
 *   Author: Stephen Flores
 */
package com.gensym.com;

public class DoubleSafeArrayTest {

  public static void main(String[] args) {
    double testDoubles[] = {0, 1, 2, 3, 4, 5};
    DoubleSafeArray array;
    int lBounds[] = {0};
    int uBounds[] = {5};

    int i = 0;
    int size = 0;
    int dimensions = 0;

    array = new DoubleSafeArray(testDoubles);

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

    array.setDouble(0, (double)9);
    if (array.getDouble(0) == 9)
      System.out.println("Put 1 element and get 1 element worked.");

    System.out.println("array.lock()");
    array.lock();
    
    System.out.println("array.dispose() = " + array.dispose());

    System.out.println("array.unlock()");
    array.unlock();

    System.out.println("array.dispose() = " + array.dispose());
    System.out.println("array.isValid() = " + array.isValid());

    array = new DoubleSafeArray(lBounds, uBounds);
    fillAndPrint(array, testDoubles);

    array = new DoubleSafeArray(6);
    fillAndPrint(array, testDoubles);

    System.out.println("\nPress Enter to continue...");
    try {
      System.in.read();
    } catch (Throwable e) {}
  }

  static void fillAndPrint(DoubleSafeArray array, double values[]) {
    int indexes[] = {0};

    array.setDoubles(indexes, values);
    print(array);
  }

  static void print(DoubleSafeArray array) {
    print("array", array);
  }

  static void print(String name, DoubleSafeArray array) {
    double doubles[];
    int i;

    doubles = array.getAllDoubles();
    if (doubles == null) {
      System.out.println("Could not get any elements to print.");
      return;
    }

    for (i = 0; i < doubles.length ; i++)
      System.out.println(name + "[" + i + "] = " + doubles[i]);
  }
}
