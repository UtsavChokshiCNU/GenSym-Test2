package com.gensym.classtools.examples.MergeClassLoader;

import com.gensym.classtools.ClassException;

/** Z is a class used only in testing of the classtools
* package.
*/
public class Z implements U {

public static int reference = 5;
public static int reference2 = 5;

static {
    reference2 = 6;
}

public Z() {
}

@Override
public int dostuff(int i, int j) 
  throws ClassException 
{
 if (i > j) {
   try{
     System.out.println("About to throw a ClassException");
     throw new ClassException();
    }
    catch (Exception e)
    {
       System.out.println("A String in common");
    }
 }
 return i + j + reference + reference2;
}

}
