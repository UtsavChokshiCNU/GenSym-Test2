package com.gensym.tests.jgi;

import com.gensym.jgi.*;
import com.gensym.util.Symbol;
import com.gensym.util.CmdLineArgHandler;

public class MultiConnectionTest {

  G2Connection con;
  private static Symbol _javaCallG2ProcNameSymbol = Symbol.intern("MULTI-CONNECTION-PROCEDURE");
  private static Symbol _G2CallJavaConnectionMethodSymbol = Symbol.intern("JAVA-CONNECTION-METHOD");

  public MultiConnectionTest(G2Connection connection) {
    
    con = connection;
  }

  public int callG2MultiConnectionProc(String str) throws G2AccessException  {

    // Set params up call to 
    // JAVA-CALL(integer, text, symbol, float, truth-value, class item) = ( integer)
    Object args[] = new Object[] {str};

    Object retval = con.callRPC(_javaCallG2ProcNameSymbol, args, 0);
    return ((Integer)retval).intValue();
  }

  public boolean runCallTest(String str, int testnum) throws G2AccessException {
    int retnum = callG2MultiConnectionProc(str);
    if (retnum == testnum) {
      System.out.println(str  + "...passed");
      return true;
    } else {
      System.out.println(str  + "...failed");
      return false;
    }
  }

  public int javaMethod1(String str) {
    System.out.println("In Java Method 1..." + str);
    return 1;
  }

  public int javaMethod2(String str) {
    System.out.println("In Java Method 2..." + str);
    return 2;
  }

  public int javaMethod3(String str) {
    System.out.println("In Java Method 3..." + str);
    return 3;
  } 

  public int javaMethod4(String str) {
    System.out.println("In Java Method 4..." + str);
    return 4;
  }

  public int javaMethod5(String str) {
    System.out.println("In Java Method 5..." + str);
    return 5;
  } 


  public static void redefinitionMethodTest(G2Connection con1,
				     G2Connection con2,
				     G2Connection con3,
				     boolean closeConnections) throws G2AccessException {

      MultiConnectionTest mt1 = new MultiConnectionTest(con1);
      con1.registerJavaMethod(mt1, "JavaMethod1", _G2CallJavaConnectionMethodSymbol);
      mt1.runCallTest("Test 1", 1);
      if (closeConnections) con1.closeConnection();

      MultiConnectionTest mt2 = new MultiConnectionTest(con2);
      con2.registerJavaMethod(mt2, "JavaMethod2", _G2CallJavaConnectionMethodSymbol);
      mt2.runCallTest("Test 2", 2);
      if (closeConnections) con2.closeConnection();

      MultiConnectionTest mt3 = new MultiConnectionTest(con3);
      con3.registerJavaMethod(mt3, "JavaMethod3", _G2CallJavaConnectionMethodSymbol);
      mt3.runCallTest("Test 3", 3);
      if (closeConnections) con3.closeConnection();

  }

  public static boolean registerMethodTest(G2Connection con1,
					    String javaMethodToCall,
					    String testName,
					    int returnExpected)
                                            throws G2AccessException {

      MultiConnectionTest mt1 = new MultiConnectionTest(con1);
      System.out.println(mt1 + " " + con1);
      con1.registerJavaMethod(mt1, javaMethodToCall, _G2CallJavaConnectionMethodSymbol);
      return mt1.runCallTest(testName, returnExpected);
  }

  public static boolean testForcedConnections(String host, String port) throws Exception {
    G2ConnectionInfo ci = new G2ConnectionInfo(null, host, port, true , true);
                                            // URL               forceNew, sharable
    G2Connection con1 = G2Gateway.getOrMakeConnection(ci);
    con1.returnMessage("Hi there from  " + con1);

    G2Connection con2 = G2Gateway.getOrMakeConnection(ci);
    con2.returnMessage("Hi there from  " + con2);

    G2Connection con3 = G2Gateway.getOrMakeConnection(ci);
    con3.returnMessage("Hi there from  " + con3);

    con1.closeConnection();
    con2.closeConnection();
    con3.closeConnection();
    
    // new connections should have been made here
    if (con1 == con2) return false;
    if (con1 == con3) return false;
    if (con2 == con3) return false;
    return true;
  }

  public static boolean testSharedConnection(String host, String port) throws Exception {

  //default sharable, not forced
    G2Connection con1 = G2Gateway.getOrMakeConnection(host, port);
    con1.returnMessage("Hi there from  " + con1);

    G2Connection con2 = G2Gateway.getOrMakeConnection(host, port);
    con2.returnMessage("Hi there from  " + con2);

    G2Connection con3 = G2Gateway.getOrMakeConnection(host, port);
    con3.returnMessage("Hi there from  " + con3);

    con1.closeConnection();

    if (con1 == con2 && con1 == con3) return true;

    return false;

  }


  public static boolean testNonSharedConnections(String host, String port) throws Exception {

    G2ConnectionInfo cif = new G2ConnectionInfo(null, host, port, true , true);
                                            // URL               forceNew, sharable
    G2Connection conf = G2Gateway.getOrMakeConnection(cif);
    conf.returnMessage("Hi there from  " + conf);

    G2ConnectionInfo cid = new G2ConnectionInfo(null, host, port);  //default sharable, not forced
    G2Connection cond = G2Gateway.getOrMakeConnection(cid);
    cond.returnMessage("Hi there from  " + cond);

    G2ConnectionInfo ci = new G2ConnectionInfo(null, host, port, false , false);
                                            // URL               not forceNew, not sharable
    G2Connection con1 = G2Gateway.getOrMakeConnection(ci);
    con1.returnMessage("Hi there from  " + con1);

    G2Connection con2 = G2Gateway.getOrMakeConnection(ci);
    con2.returnMessage("Hi there from  " + con2);

    G2Connection con3 = G2Gateway.getOrMakeConnection(ci);
    con3.returnMessage("Hi there from  " + con3);

    con1.closeConnection();
    con2.closeConnection();
    con3.closeConnection();
    conf.closeConnection();

    // new connections should have been made
    if (con1 == conf || con2 == conf || con3 == conf) return false;
    if (con1 == cond || con2 == cond || con3 == cond) return false;

    if (con1 == con2) return false;
    if (con1 == con3) return false;
    if (con2 == con3) return false;
    return true;
  }

  public static boolean testRegisteredMethodsToSameConnection(G2Connection con1) throws Exception {
    boolean res1 = registerMethodTest(con1, "javaMethod1", "SameConnection Test 1", 1);
    boolean res2 = registerMethodTest(con1, "javaMethod2", "SameConnection Test 2", 2);
    boolean res3 = registerMethodTest(con1, "javaMethod3", "SameConnection Test 3", 3);
    return (res1 && res2 && res3);
  }

  public static boolean testRegisteredMethodsToDifferentConnections(G2Connection con1, 
					       G2Connection con2, 
					       G2Connection con3) throws Exception {

    boolean res1 = registerMethodTest(con1, "javaMethod1", "DifferentConnection Test 1", 1);
    boolean res2 = registerMethodTest(con2, "javaMethod2", "DifferentConnection Test 2", 2);
    boolean res3 = registerMethodTest(con3, "javaMethod3", "DifferentConnection Test 3", 3);
    return (res1 && res2 && res3);
  }

  public static boolean testRegisteredMethodsToNewConnections(String host, String port) throws Exception {

    G2Connection con1 = G2Gateway.getOrMakeConnection(host, port);
    boolean res1 = registerMethodTest(con1, "javaMethod1", "NewConnection Test 1", 1);
    con1.closeConnection();
    G2Connection con2 = G2Gateway.getOrMakeConnection(host, port);
    if (con2 == con1) return false;
    boolean res2 = registerMethodTest(con2, "javaMethod4", "NewConnection Test 2", 4);
    con2.closeConnection();
    G2Connection con3 = G2Gateway.getOrMakeConnection(host, port);
    if (con3 == con1) return false;
    boolean res3 = registerMethodTest(con3, "javaMethod5", "NewConnection Test 3", 5);
    con3.closeConnection();

    return (res1 && res2 && res3);
  }

  public static void main(String args[]) {
    CmdLineArgHandler cmdline = new CmdLineArgHandler(args);

    String host = cmdline.getOptionValue("-g2host");
    String port = cmdline.getOptionValue("-g2port");
    host = (host == null ? "localhost" : host);
    port = (port == null ? "1111" : port);

    try {
      
      System.out.println("Forced Connection Test: " + testForcedConnections(host, port));
      System.out.println("Non Shared Connection Test: " + testNonSharedConnections(host, port));
      System.out.println("Shared Connection Test: " + testSharedConnection(host, port));

      G2Connection con1 = G2Gateway.getOrMakeConnection(host, port);
      System.out.println("Registered Methods to same connection test: " + 
			 testRegisteredMethodsToSameConnection(con1));

      G2ConnectionInfo cif = new G2ConnectionInfo(null, host, port, true , true);
                                            // URL               forceNew, sharable
      G2Connection con2 = G2Gateway.getOrMakeConnection(cif);
      G2Connection con3 = G2Gateway.getOrMakeConnection(cif);
      System.out.println("Registered Methods to same connection test: " + 
			 testRegisteredMethodsToDifferentConnections(con1, con2, con3));

      con1.closeConnection();
      con2.closeConnection();
      con3.closeConnection();

      System.out.println("Registered Methods to new connection test: " + 
			 testRegisteredMethodsToNewConnections(host, port));

      Thread.sleep(1000);
      System.gc();

    } catch (Exception e) {
      System.out.println(e.toString());
    }
    System.out.println("Test end");
  }

  @Override
  public void finalize() {
    System.out.println("Bye Bye " + this);
  }

}

    
