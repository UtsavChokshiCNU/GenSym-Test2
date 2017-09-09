/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 *          com.gensym.com.DateSafeArrayTest.java
 *
 *   Author: Stephen Flores
 */
package com.gensym.com;

import java.util.*;

public class DateSafeArrayTest {

  public static void main(String[] args) {
    Date testDates[] = {
      (new GregorianCalendar( 1999, 7, 1 )).getTime(),
      (new GregorianCalendar( 1999, 7, 2 )).getTime(),
      (new GregorianCalendar( 1999, 7, 3 )).getTime(),
      (new GregorianCalendar( 1999, 7, 4 )).getTime(),
      (new GregorianCalendar( 1999, 7, 5 )).getTime(),
      (new GregorianCalendar( 1999, 7, 6 )).getTime()
    };
    DateSafeArray array;
    int lBounds[] = {0};
    int uBounds[] = {testDates.length - 1};

    int i = 0;
    int size = 0;
    int dimensions = 0;

    array = new DateSafeArray(testDates);

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

    array.setDate(0, new Date(0));
    if (array.getDate(0).equals(new Date(0)))
      System.out.println("Put 1 element and get 1 element worked.");

    System.out.println("array.lock()");
    array.lock();
    
    System.out.println("array.dispose() = " + array.dispose());

    System.out.println("array.unlock()");
    array.unlock();

    System.out.println("array.dispose() = " + array.dispose());
    System.out.println("array.isValid() = " + array.isValid());

    array = new DateSafeArray(lBounds, uBounds);
    fillAndPrint(array, testDates);

    array = new DateSafeArray(6);
    fillAndPrint(array, testDates);

    System.out.println("\nPress Enter to continue...");
    try {
      System.in.read();
    } catch (Throwable e) {}
  }

  static void fillAndPrint(DateSafeArray array, Date values[]) {
    int indexes[] = {0};

    array.setDates(indexes, values);
    print(array);
  }

  static void print(DateSafeArray array) {
    print("array", array);
  }

  static void print(String name, DateSafeArray array) {
    Date dates[];
    int i;

    dates = array.getAllDates();
    if (dates == null) {
      System.out.println("Could not get any elements to print.");
      return;
    }

    for (i = 0; i < dates.length ; i++)
      System.out.println(name + "[" + i + "] = " + dates[i]);
  }
}
