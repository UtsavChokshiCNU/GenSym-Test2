package com.gensym.classtools.examples.MergeClassLoader;

import com.gensym.classtools.*;

/** Y is a class that is used purely in testing of the 
* classtools package.
*/
public class Y extends V {
	protected int count = 10;

      protected static int famous = 12;

      protected static int famous2 = 12;

      protected static String famous3 = "I am a single String";

      static {
          famous2 = 3;
          try {
              Thread.sleep(1);
          }
          catch(Exception e)
          {
              e.printStackTrace();
          }
      }

	public Y() {
		super();
	}

	@Override
	public int dootherStuff() throws ClassMergeException  {
		 System.out.println("A String in common");
             if (count > supercount)
			return count + famous + famous2;
		 else throw new ClassMergeException();
	}

}
