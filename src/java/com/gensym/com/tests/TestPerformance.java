package com.gensym.com.tests;

import com.gensym.com.Variant;

import java.util.Vector;

public class TestPerformance {

  private static native void empty_c_method();
  
  private static native void vector_method(Vector vector);
  private static native void variant_method(Variant variant);
  private static native void double_method(double mydouble);
  private static native void integer_method(int myint);
  private static native void string_method(String myString);
    
  private static native void variant_get_class_method(Variant variant);
  private static native void variant_get_variant_value(Variant variant);

  private static native void vector_get_values(Vector vector);

  private static native void convert_string(String str);
  private static native void convert_string_then_free(String str);
  private static native void convert_string_no_sysalloc(String str);

  private static native void start_up();

  private static native void callback_cost(Variant var, int times);

  private static Class varClass; 
  private static Class vectClass; 
  private static boolean libraryIsLoaded = false;
  static {
    loadLibrary(true);
  }


  public static boolean loadLibrary (boolean definitely) {
    if (libraryIsLoaded && !definitely)
      return true;
    try {
      System.loadLibrary("JavaPerformance");
      System.out.println("com.gensym.com: Loaded JavaPerformance.");
      libraryIsLoaded = true;
      return true;
    } catch (UnsatisfiedLinkError e) {
      System.out.println("com.gensym.com: Error! Could not load JavaPerformance.");
      return false;
    }
  }

  private static void printResult(String type, 
                             String descriptor,
                             long end,
                             long start,
                             long scale) 
  { 
    long diff;
    double average, persecond;

    diff = (end - start);
    average = (diff / (scale + 0.0));
    persecond = (1000 / average);

    System.out.println("Total " +type + " " + descriptor + 
      " " +diff + " (millis)");
    System.out.println("Average " + type + " " + descriptor +
      " " +average + " (millis)");
    System.out.println("Number per second " + type + " " + descriptor + " " +
      persecond+ "\n");
  }

  public static void main(String[] args) {
    String scale = args[0];
    int scaleInt = Integer.parseInt(scale);

    start_up();
    String preloadClasses = args[1];
    boolean mustPreLoad = false;
    if (preloadClasses.equals("true")) 
      mustPreLoad = true;

    if (mustPreLoad) {
      try {
        varClass = Class.forName("com.gensym.com.Variant");
        vectClass = Class.forName("java.util.Vector");
        
      }
      catch(ClassNotFoundException e)
      {}
    }
    
    System.out.println("\nTime taken for " + scaleInt + " JNI calls");
    System.out.println("----------------------------------------\n");

    if (mustPreLoad)
      System.out.println("PreLoading Variant and Vector");

    long endtime; 
    long starttime = System.currentTimeMillis();

    // Raw cost of empty JNI call
    for (int i = 0; i < scaleInt; i ++)
      empty_c_method();

    endtime = System.currentTimeMillis();

    printResult("static","()V",endtime,starttime,scaleInt);
      

    //***** Tests for effect of JNI on our marshalling ***

    // (com/gensym/com/Variant;)V

    starttime = System.currentTimeMillis();
    for (int i = 0; i < scaleInt; i ++)
      variant_method(new Variant(1));

    endtime = System.currentTimeMillis();

    printResult("static","(com/gensym/com/Variant;)V",endtime,starttime,scaleInt);

    starttime = System.currentTimeMillis();
    for (int i = 0; i < scaleInt; i ++) {
       Variant myvar = new Variant(1);
    }

    endtime = System.currentTimeMillis();

    printResult("","Just creating variants",endtime,starttime,scaleInt);

    // (java/util/Vector;)V

    starttime = System.currentTimeMillis();
    for (int i = 0; i < scaleInt; i ++)
      vector_method(new Vector(0));

    endtime = System.currentTimeMillis();

    printResult("static","(com/gensym/com/Vector;)V",endtime,starttime,scaleInt);

    starttime = System.currentTimeMillis();
    for (int i = 0; i < scaleInt; i ++) {
       Vector myvector = new Vector(0);
    }

    endtime = System.currentTimeMillis();

    printResult("","Just creating empty vectors",endtime,starttime,scaleInt);

    // (D)V
    
    starttime = System.currentTimeMillis();
    for (int i = 0; i < scaleInt; i ++)
      double_method(30.0);

    endtime = System.currentTimeMillis();

    printResult("static","(D)V",endtime,starttime,scaleInt);

    // (I)V

    starttime = System.currentTimeMillis();
    for (int i = 0; i < scaleInt; i ++)
      integer_method(100);

    endtime = System.currentTimeMillis();

    printResult("static","(I)V",endtime,starttime,scaleInt);


    // (java/lang/String)V

    starttime = System.currentTimeMillis();
    for (int i = 0; i < scaleInt; i ++)
      string_method("foobarandawholebigshakeofcheesedoodles");

    endtime = System.currentTimeMillis();

    printResult("static","(java/lang/String;)V",endtime,starttime,scaleInt);
    

    // Cost of getting the class out of variant
    starttime = System.currentTimeMillis();
    for (int i = 0; i < scaleInt; i ++)
      variant_get_class_method(new Variant(1));

    endtime = System.currentTimeMillis();

    printResult("static","(com/gensym/com/Variant;)V getclass",endtime,starttime,scaleInt);


    // Cost of getting a value out of a Variant
    // int
    starttime = System.currentTimeMillis();
    for (int i = 0; i < scaleInt; i ++)
      variant_get_variant_value(new Variant(1));

    endtime = System.currentTimeMillis();

    printResult("static","(com/gensym/com/Variant;)V getvalue of integer",endtime,starttime,scaleInt);

    // double
    starttime = System.currentTimeMillis();
    for (int i = 0; i < scaleInt; i ++)
      variant_get_variant_value(new Variant(50.0));

    endtime = System.currentTimeMillis();

    printResult("static","(com/gensym/com/Variant;)V getvalue of double",endtime,starttime,scaleInt);

    // String
    starttime = System.currentTimeMillis();
    for (int i = 0; i < scaleInt; i ++)
      variant_get_variant_value(new Variant("foobarandawholebigshakeofcheesedoodles"));

    endtime = System.currentTimeMillis();

    printResult("static","(com/gensym/com/Variant;)V getvalue of String",endtime,starttime,scaleInt);


    // Cost of getting value out of Vector of Variants
    // empty vector
    starttime = System.currentTimeMillis();
    for (int i = 0; i < scaleInt; i ++)
      vector_get_values(new Vector(0));

    endtime = System.currentTimeMillis();
    printResult("static","(com/gensym/com/Vector;)V get args empty vector",endtime,starttime,scaleInt);

    // null rather than vector
    starttime = System.currentTimeMillis();
    for (int i = 0; i < scaleInt; i ++)
      vector_get_values(null);

    endtime = System.currentTimeMillis();
    printResult("static","(com/gensym/com/Vector;)V get args on null",endtime,starttime,scaleInt);
          
    // 1 Integer
    starttime = System.currentTimeMillis();
    for (int i = 0; i < scaleInt; i ++)  {
      Vector moreargs = new Vector(0);
      moreargs.addElement(new Variant(40));
      vector_get_values(moreargs);
    }
    endtime = System.currentTimeMillis();

    printResult("static","(com/gensym/com/Vector;)V get args 1 int variant",endtime,starttime,scaleInt);

    // 1 Double
    starttime = System.currentTimeMillis();
    for (int i = 0; i < scaleInt; i ++)  {
      Vector moreargs = new Vector(0);
      moreargs.addElement(new Variant(40.0));
      vector_get_values(moreargs);
    }
    endtime = System.currentTimeMillis();

    printResult("static","(com/gensym/com/Vector;)V get args 1 double variant",endtime,starttime,scaleInt);

    // 1 String
    starttime = System.currentTimeMillis();
    for (int i = 0; i < scaleInt; i ++)  {
      Vector moreargs = new Vector(0);
      moreargs.addElement(new Variant("foobarandawholebigshakeofcheesedoodles"));
      vector_get_values(moreargs);
    }
    endtime = System.currentTimeMillis();

    starttime = System.currentTimeMillis();
    for (int i = 0; i < scaleInt; i ++)  {
      convert_string_then_free("foobar");
    }
    endtime = System.currentTimeMillis();

    printResult("","just converting 1 short string SysAlloc&SysFree",endtime,starttime,scaleInt);

    starttime = System.currentTimeMillis();
    for (int i = 0; i < scaleInt; i ++)  {
      convert_string("foobarandawholebigshakeofcheesedoodles");
    }
    endtime = System.currentTimeMillis();

    printResult("","just converting 1 long string",endtime,starttime,scaleInt);


    starttime = System.currentTimeMillis();
    for (int i = 0; i < scaleInt; i ++)  {
      convert_string("foobar");
    }
    endtime = System.currentTimeMillis();

    printResult("","just converting 1 short string",endtime,starttime,scaleInt);


    starttime = System.currentTimeMillis();
    for (int i = 0; i < scaleInt; i ++)  {
      convert_string_no_sysalloc("foobar");
    }
    endtime = System.currentTimeMillis();

    printResult("","just converting 1 short string no SysAlloc",endtime,starttime,scaleInt);

    // Cost of callbacks into java
    starttime = System.currentTimeMillis();
    callback_cost(new Variant(1), scaleInt);
    endtime = System.currentTimeMillis();

    printResult("static","(Lcom/gensym/com/Variant;I)V callback to getIntegerValue()",endtime,starttime,scaleInt);


  }

}
