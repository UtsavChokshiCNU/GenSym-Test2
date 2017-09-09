/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 *          com.gensym.com.ShortSafeArrayTest.java
 *
 *   Author: Stephen Flores
 */
package com.gensym.com;

public class ShortSafeArrayTest {

  public static void main(String[] args) {
    ShortSafeArray array;

    int lBounds[] = {-3, -1 , 6};
    int uBounds[] = {-2, 1, 9};
    int indexes[] = new int[3];
    short data[] = new short[1];
    array = new ShortSafeArray(lBounds, uBounds);

    System.out.println("array [" + array.getLBound(1) + " ... " +
                       array.getUBound(1) + "] [" +
                       array.getLBound(2) + " ... " +
                       array.getUBound(2) + "] [" +
                       array.getLBound(3) + " ... " +
                       array.getUBound(3) + "]");
    
    int k, x, y, z;

    /* fill -2 to -3 array with -2, -3 respectively */
    for (k = 0; k < 3; k++) {
      for (x = lBounds[0]; x <= uBounds[0]; x++) {
        for (y = lBounds[1]; y <= uBounds[1]; y++) {
          for (z = lBounds[2]; z <= uBounds[2]; z++) {
            indexes[0] = x;
            indexes[1] = y;
            indexes[2] = z;
            switch (k) {
            case 0:
              data[0] = (short)x;
              break;

            case 1:
              data[0] = (short)y;
              break;

            case 2:
              data[0] = (short)z;
              break;
            }

            array.setShorts(indexes, data);
          } // z
        } // y
      } // x

      System.out.println("array = " + array);
      printMulti(array);
    } // k

    short testShorts[] = {0, 1, 2, 3, 4, 5};
    int lBound[] = {0};
    int uBound[] = {5};

    int i = 0;
    int size = 0;
    int dimensions = 0;

    array = new ShortSafeArray(testShorts);

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

    array.setShort(0, (short)9);
    if (array.getShort(0) == 9)
      System.out.println("Put 1 element and get 1 element worked.");

    System.out.println("array.lock()");
    array.lock();
    
    System.out.println("array.dispose() = " + array.dispose());

    System.out.println("array.unlock()");
    array.unlock();

    System.out.println("array.dispose() = " + array.dispose());
    System.out.println("array.isValid() = " + array.isValid());

    array = new ShortSafeArray(lBound, uBound);
    fillAndPrint(array, testShorts);

    array = new ShortSafeArray(6);
    fillAndPrint(array, testShorts);

    System.out.println("\nPress Enter to continue...");
    try {
      System.in.read();
    } catch (Throwable e) {}
  }

  static void fillAndPrint(ShortSafeArray array, short values[]) {
    int indexes[] = {0};

    array.setShorts(indexes, values);
    print(array);
  }

  static void print(ShortSafeArray array) {
    print("array", array);
  }

  static void print(String name, ShortSafeArray array) {
    short shorts[];
    int i;

    shorts = array.getAllShorts();
    if (shorts == null) {
      System.out.println("Could not get any elements to print.");
      return;
    }

    for (i = 0; i < shorts.length ; i++)
      System.out.println(name + "[" + i + "] = " + shorts[i]);
  }

  static void printMulti(ShortSafeArray array) {
    int dimensions;

    dimensions = array.getDimensions();
    printMulti(array, dimensions, new int[dimensions]);
    System.out.println("************************************");
  }

  static void printMulti(ShortSafeArray array, int dim, int[] indexes) {
    int uBound;
    int lBound;
    int i;
    String output = "{";

    uBound = array.getUBound(dim);
    lBound = array.getLBound(dim);

    if (dim > 1) {
      System.out.println("");

      for (i = lBound; i <= uBound; i++) {
        indexes[dim - 1] = i;
        printMulti(array, dim - 1, indexes);
      }

      return;
    }

    for (i = lBound; i <= uBound; i++) {
      indexes[dim - 1] = i;
      output += array.getShorts(indexes, 1)[0] + " ";
    }

    System.out.println(output + "}");
  }
}
