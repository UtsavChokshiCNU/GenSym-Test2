/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 *          com.gensym.com.StringSafeArrayTest.java
 *
 *   Author: Stephen Flores
 */
package com.gensym.com;

public class StringSafeArrayTest {

  public static void main(String[] args) {
    String testStrings[] = {"zero", "one", "two", "three", "four", "five"};
    StringSafeArray array;
    int lBounds[] = {0};
    int uBounds[] = {5};

    int i = 0;
    int size = 0;
    int dimensions = 0;

    int cubeLBounds[] = {0, 0, 0};
    int cubeUBounds[] = {2, 2, 2};
    int cubeIndexes[] = {1, 2, 2};
    String cubeData[] = {"second to last", "last"};

    StringSafeArray cubeArray = new StringSafeArray(cubeLBounds, cubeUBounds);
    cubeArray.setStrings(cubeIndexes, cubeData);
    cubeIndexes[2] = -1;
    cubeArray.setStrings(cubeIndexes, cubeData);
    cubeIndexes[2] = 5;
    cubeArray.setStrings(cubeIndexes, cubeData);
    System.out.println("cubeArray = " + cubeArray);

    array = new StringSafeArray(testStrings);

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

    array.setString(0, "nine");
    if (array.getString(0).equals("nine"))
      System.out.println("Put 1 element and get 1 element worked.");

    System.out.println("array.lock()");
    array.lock();
    
    System.out.println("array.dispose() = " + array.dispose());

    System.out.println("array.unlock()");
    array.unlock();

    System.out.println("array.dispose() = " + array.dispose());
    System.out.println("array.isValid() = " + array.isValid());

    array = new StringSafeArray(lBounds, uBounds);
    fillAndPrint(array, testStrings);

    array = new StringSafeArray(6);
    fillAndPrint(array, testStrings);

    System.out.println("\nPress Enter to continue...");
    try {
      System.in.read();
    } catch (Throwable e) {}
  }

  static void fillAndPrint(StringSafeArray array, String values[]) {
    int indexes[] = {0};

    array.setStrings(indexes, values);
    print(array);
  }

  static void print(StringSafeArray array) {
    print("array", array);
  }

  static void print(String name, StringSafeArray array) {
    String strings[];
    int i;

    strings = array.getAllStrings();
    if (strings == null) {
      System.out.println("Could not get any elements to print.");
      return;
    }

    for (i = 0; i < strings.length ; i++)
      System.out.println(name + "[" + i + "] = " + strings[i]);
  }
}
