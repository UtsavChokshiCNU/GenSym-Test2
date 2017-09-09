/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 *          com.gensym.com.ByteSafeArrayTest.java
 *
 *   Author: Stephen Flores
 */
package com.gensym.com;

public class ByteSafeArrayTest {

  public static void main(String[] args) {
    byte testBytes[] = {0, 1, 2, 3, 4, 5};
    ByteSafeArray array;
    int lBounds[] = {0};
    int uBounds[] = {5};

    int i = 0;
    int size = 0;
    int dimensions = 0;

    array = new ByteSafeArray(testBytes);

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

    array.setByte(0, (byte)9);
    if (array.getByte(0) == 9)
      System.out.println("Put 1 element and get 1 element worked.");

    System.out.println("array.lock()");
    array.lock();
    
    System.out.println("array.dispose() = " + array.dispose());

    System.out.println("array.unlock()");
    array.unlock();

    System.out.println("array.dispose() = " + array.dispose());
    System.out.println("array.isValid() = " + array.isValid());

    array = new ByteSafeArray(lBounds, uBounds);
    fillAndPrint(array, testBytes);

    array = new ByteSafeArray(6);
    fillAndPrint(array, testBytes);

    System.out.println("\nPress Enter to continue...");
    try {
      System.in.read();
    } catch (Throwable e) {}
  }

  static void fillAndPrint(ByteSafeArray array, byte values[]) {
    int indexes[] = {0};

    array.setBytes(indexes, values);
    print(array);
  }

  static void print(ByteSafeArray array) {
    print("array", array);
  }

  static void print(String name, ByteSafeArray array) {
    byte bytes[];
    int i;

    bytes = array.getAllBytes();
    if (bytes == null) {
      System.out.println("Could not get any elements to print.");
      return;
    }

    for (i = 0; i < bytes.length ; i++)
      System.out.println(name + "[" + i + "] = " + bytes[i]);
  }
}
