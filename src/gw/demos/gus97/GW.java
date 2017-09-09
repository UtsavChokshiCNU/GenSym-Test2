// package -- in the nameless package

// GW is a class used to help manage communication between
// G2 and an Applet via WebLink.  It provides a way that a
// text retreived from G2 maybe parsed and placed into a
// tiny database.  The Applet may then query that database
// for information.  In general the Applet will use this
// by creating an instance of the GW class, and then making
// one or more queries back to G2 to populate the database.
// It then uses that info to display information to the 
// the user.  As the user interacts with the Applet the
// Applet makes calls back to G2 to notify it, and G2 returns
// updates to the database, which the Applet uses to
// revise what is being displayed.

// That all amounts to a little pipeline:
//   User <-> Applet <-> database <-> WebLink <-> G2
// and this class implements that database.

import java.lang.*;
import java.net.*;
import java.io.*;

class GW {

  private URL baseURL;  // Something we can use to find our way home.

  GW(URL URLfromWebLink){
    baseURL = URLfromWebLink;
  }

  boolean traceFlag = true; // Something to enable tracing if we want it.

  private void trace(String text) {
    if (traceFlag) {
      System.out.println("GW:"+text);
    }
  }


  // Ask G2 something, and get a stream on his reply.
  InputStream QueryInputStream(String urlName){
      URL url;
      try {
	try { 
	  url = new URL(baseURL,urlName);
	  URLConnection connection = url.openConnection();
	  connection.setUseCaches(false);
	  return connection.getInputStream();
	} catch ( MalformedURLException e ) { return null; };
      } catch ( IOException e ) { return null; };
  }

  // Ask G2 something, and get the reply back as a string.
  String QueryText(String urlName){
    String result = "";
    DataInputStream input;
    input = new DataInputStream(QueryInputStream(urlName));

    // Accumlate the text of the reply.  (ought to use a string buffer).
    try {
      String line;
      while ((line = input.readLine()) != null) {
	result = result + line + "\n";
      }
    } catch (java.io.IOException e) {
      return result;
    }
    
    // That's all folks.
    try {
      input.close();
    } catch (java.io.IOException e) {
      return result;
    }
    return result;
  }

  final int maxTuples = 100;
  Object[][] tuples = new Object[maxTuples][3];
  private int tuplePointer = 0;

  String describeAllTuples(){
    StringBuffer sb = new StringBuffer();
    int cnt = 1;
    for(int i = 0; i<maxTuples;i++){
      if(null!=tuples[i][0]){
	sb.append(cnt++);
	sb.append(": ");
	sb.append(tuples[i][0]);
	sb.append(", ");
	sb.append(tuples[i][1]);
	sb.append(", ");
	sb.append(tuples[i][2]);
	sb.append("\n");
      }
    }
    return sb.toString();
  }

  private void assertTuple(Object a, Object b, Object c){
    trace("assert: " + a + ", " + b + ", " + c );
    Object availableTuple[] = null;
    for(int i=0;i<maxTuples;i++){
      Object tuple[] = tuples[i];
      if ( a.equals(tuple[0])
	   && b.equals(tuple[1])
	   && c.equals(tuple[2]) ) {
	return;
      } else if ( null == tuple[0] ) {
	availableTuple = tuple;
      }
    }
    availableTuple[0] = a;
    availableTuple[1] = b;
    availableTuple[2] = c;
  }

  void QueryTuples(String urlName){
    int stackPointer = 0;
    Object[] stack = new Object[20];
    InputStream inputStream = QueryInputStream(urlName);
    StreamTokenizer input = new StreamTokenizer(inputStream);
    input.eolIsSignificant(false);
    input.lowerCaseMode(true);
    try { input.nextToken(); } catch (IOException e) {return; }
    boolean finished = false;
    loop: for (int i = 300; i>0; i--){
      switch ( input.ttype ){
      case StreamTokenizer.TT_EOF: 
	finished = true;
	break loop;
      case StreamTokenizer.TT_NUMBER:
	stack[++stackPointer] = new Double(input.nval);
	break;
      case StreamTokenizer.TT_WORD:
	// See if this word is an operator in our little postfix world.
	if( "assert".equals(input.sval) ){ // Less expensive equal?
	  Object c = stack[stackPointer--];
	  Object b = stack[stackPointer--];
	  Object a = stack[stackPointer--];
	  assertTuple(a,b,c);
	} else {
	  // Interning this as string is lame!
	  stack[++stackPointer] = new String(input.sval);
	}
	break;
      case '"':
	stack[++stackPointer] = new String(input.sval);
	break;
      }
      try { input.nextToken(); } catch (IOException e) {return; };
    }
    if ( ! finished ){
      trace("did not finish reading.");
    }
    // That's all folks.
    try {
      inputStream.close();
    } catch (java.io.IOException e) {
      return;
    }
  }


  static Object wildcard = new Object();

  class TesterXXX{ 
      private Object a, b, c;
      TesterXXX(Object x,Object y, Object z){
	a=x; b=y; c=z;
      }
      boolean match(Object x[]){ 
	return true;
      }
    }

    class Tester123 extends TesterXXX{ 
      Tester123(Object x,Object y, Object z){ super(x,y,z); }
      boolean match(Object x[]){ 
	return a.equals(x[0]) && b.equals(x[1]) && c.equals(x[2]);
      }
    }

    class TesterX23 extends TesterXXX{ 
      TesterX23(Object x,Object y, Object z){ super(x,y,z); }
      boolean match(Object x[]){ 
	return b.equals(x[1]) && c.equals(x[2]);
      }
    }

    class Tester1X3 extends TesterXXX{ 
      Tester1X3(Object x,Object y, Object z){ super(x,y,z); }
      boolean match(Object x[]){ 
	return a.equals(x[0]) && c.equals(x[2]);
      }
    }

    class TesterXX3 extends TesterXXX{ 
      TesterXX3(Object x,Object y, Object z){ super(x,y,z); }
      boolean match(Object x[]){ 
	return c.equals(x[2]);
      }
    }


    class Tester12X extends TesterXXX{ 
      Tester12X(Object x,Object y, Object z){ super(x,y,z); }
      boolean match(Object x[]){ 
	return a.equals(x[0]) && b.equals(x[1]);
      }
    }

    class TesterX2X extends TesterXXX{ 
      TesterX2X(Object x,Object y, Object z){ super(x,y,z); }
      boolean match(Object x[]){ 
	return b.equals(x[1]);
      }
    }

    class Tester1XX extends TesterXXX{ 
      Tester1XX(Object x,Object y, Object z){ super(x,y,z); }
      boolean match(Object x[]){ 
	return a.equals(x[0]);
      }
    }

  class generator {
    GW theSpace;
    private Object patternA,patternB,patternC;
    private int pointer = -1;
    TesterXXX tester;


    generator(GW space, Object a, Object b, Object c){
      theSpace = space;
      int pat = 0;
      if ( wildcard.equals(a) ) pat &= 1;
      if ( wildcard.equals(b) ) pat &= 2;
      if ( wildcard.equals(c) ) pat &= 4;
      switch (pat){
      case 0: tester = new Tester123(a,b,c); break;
      case 1: tester = new TesterX23(a,b,c); break;
      case 2: tester = new Tester1X3(a,b,c); break;
      case 3: tester = new TesterXX3(a,b,c); break;
      case 4: tester = new Tester12X(a,b,c); break;
      case 5: tester = new TesterX2X(a,b,c); break;
      case 6: tester = new Tester1XX(a,b,c); break;
      case 7: tester = new TesterXXX(a,b,c); break;
      }
    }

    boolean advance(){
      if(pointer==-2) return false;
      while(++pointer<theSpace.maxTuples){
	if( matchTuple(pointer) ){
	  return true;
	}
      }
      pointer = -2;
      return false;
    }

    boolean matchTuple(int i){
      return tester.match(tuples[i]);
    }


    Object first(){ return theSpace.tuples[pointer][0]; }
    Object second(){ return theSpace.tuples[pointer][0]; }
    Object third(){ return theSpace.tuples[pointer][0]; }

  } // End Generator

}
