package com.gensym.tests;

import com.gensym.classes.G2__BaseImpl;
import java.util.Vector;
import java.lang.Object;

class individual_datum extends Object{    
    String datum;
    long timestamp;
    String directions; 
    individual_datum (String item, String direction){
	datum = item;
	timestamp = System.currentTimeMillis() ;
	directions = direction + " " + Thread.currentThread().toString();
    }
}

public class Debug3Tier {
    static Vector data = new Vector ();
    public static void add_data (String direction,G2__BaseImpl object){
	data.addElement (new individual_datum (object.toString (), direction));
    }
    public static void add_data (String direction,String text){
	data.addElement (new individual_datum (text, direction));
    }


    public static void dump (){
	int iterator;
	individual_datum datum;
	for (iterator = 0; iterator < data.size (); iterator++) {
	    datum =(individual_datum) data.elementAt (iterator);
	    System.out.print(datum.timestamp);
	    System.out.print (": (");
	    System.out.print(datum.directions);
	    System.out.print (") ");
	    System.out.println (datum.datum);
	}
    }



  /*
  static PrintWriter myfile = null;

  public static void debugline(String s) {
    if (myfile == null)
      try {
	myfile = new PrintWriter(new FileOutputStream("c:\\bt\\yduj\\java\\javaerrors.txt", true));
      } catch (java.io.IOException e){
	System.out.println ("an error occurred:  " +
			    e.toString());
      }
    myfile.println(s);
    myfile.flush();
  }
  */
}
