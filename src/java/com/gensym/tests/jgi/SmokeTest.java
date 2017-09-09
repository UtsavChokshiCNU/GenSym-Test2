package com.gensym.tests.jgi;
import com.gensym.jgi.*;
import com.gensym.util.*;
 
public class SmokeTest{
  private G2Connection connection = null;
   
  private String hostName = "build";
  private String portNumber = "3030";
   
  private G2ConnectionInfo G2CI = new G2ConnectionInfo(	null, 
							hostName,
							portNumber);
   
  public SmokeTest() {
    super();

    boolean passed = true;
   
    // G2Connection initialization
    try {
      connection = G2Gateway.getOrMakeConnection(G2CI);
      String info = connection.g2GetSoftwareVersion();
      System.out.println (info);
      connection.closeConnection ();
    } catch (Exception ex) {
      System.out.println ("JAVASMOKETEST, TROUBLE, "+ex);
      passed = false;
    }
    if (passed)
      System.out.println ("JAVASMOKETEST, OK, ");
  }
 
	
  public static void main (String args[]){
    SmokeTest mc = new SmokeTest();
    try {
      Thread.sleep (1000);
    } catch (Exception e) {
      System.out.println ("JAVASMOKETEST, TROUBLE, "+e);
    }
    System.out.flush();
    System.exit (0);
  }
}
