/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 *          com.gensym.com.IntSafeArrayTest.java
 *
 *   Author: Stephen Flores
 */
package com.gensym.com;

public class IntSafeArrayTest {

  public static void main(String[] args) {
    int cubeLBounds[] = {0, 0, 0};
    int cubeUBounds[] = {2, 2, 2};
    int cubeIndexes[] = {1, 2, 2};
    int cubeData[] = {99, 100};

    IntSafeArray cubeArray = new IntSafeArray(cubeLBounds, cubeUBounds);
    cubeArray.setInts(cubeIndexes, cubeData);
    System.out.println("cubeArray = " + cubeArray);

    int testInts[] = {0, 1, 2, 3, 4, 5};
    IntSafeArray array;
    IntSafeArray clone;
    int lBounds[] = {0};
    int uBounds[] = {5};

    int i = 0;
    int size = 0;
    int dimensions = 0;

    array = new IntSafeArray(testInts);

    if (!array.isValid()) {
      System.out.println("array is not valid");
      return;
    } else {
      System.out.println("array is valid");
    }

    System.out.println("isOwner = " + array.isOwner());
    array.giveUpOwnership();
    System.out.println("after giveUpOwnership isOwner = " + array.isOwner());
    array.takeOwnership();
    System.out.println("after takeOwnership isOwner = " + array.isOwner());

    dimensions = array.getDimensions();
    System.out.println("dimensions = " + dimensions);
   
    size = array.getUBound(1) - array.getLBound(1) + 1;
    System.out.println("size = " + size);

    print(array);

    clone = (IntSafeArray)array.clone();

    print("clone", clone);

    System.out.println("");

    array.setInt(0, 9);
    if (array.getInt(0) == 9)
      System.out.println("Put 1 element and get 1 element worked.");

    System.out.println("array.lock()");
    array.lock();
    
    System.out.println("array.dispose() = " + array.dispose());

    System.out.println("array.unlock()");
    array.unlock();

    System.out.println("array.dispose() = " + array.dispose());
    System.out.println("array.isValid() = " + array.isValid());

    clone = null;
    System.gc();

    array = new IntSafeArray(lBounds, uBounds);
    fillAndPrint(array, testInts);

    array = new IntSafeArray(6);
    fillAndPrint(array, testInts);

    lBounds[0] = -5;
    array = new IntSafeArray(lBounds, uBounds);
    array.setInt(0, 99);
    System.out.println("array = " + array);

    lBounds[0] = -11;
    uBounds[0] = -1;
    array = new IntSafeArray(lBounds, uBounds);
    array.setInt(-6, 99);
    System.out.println("array = " + array);

    lBounds[0] = 1;
    uBounds[0] = 11;
    array = new IntSafeArray(lBounds, uBounds);
    array.setInt(6, 99);
    System.out.println("array = " + array);

    System.out.println("\nPress Enter to continue...");
    try {
      System.in.read();
    } catch (Throwable e) {}
  }

  static void fillAndPrint(IntSafeArray array, int values[]) {
    int indexes[] = {0};

    array.setInts(indexes, values);
    print(array);
  }

  static void print(IntSafeArray array) {
    print("array", array);
  }

  static void print(String name, IntSafeArray array) {
    int ints[];
    int i;

    ints = array.getAllInts();
    if (ints == null) {
      System.out.println("Could not get any elements to print.");
      return;
    }

    for (i = 0; i < ints.length ; i++)
      System.out.println(name + "[" + i + "] = " + ints[i]);
  }
}
