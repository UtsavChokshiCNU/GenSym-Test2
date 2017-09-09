package com.gensym.g2script.tests;

import com.gensym.g2script.*;
import java.util.*;

public class FunctionTest {

  static Vector functions;

  /**  Will run through all functions in G2 and test their mapping in java (uses TestG2Script)
  **/
  public static void main(String[] argv) {
    initializeFunctions();
    // Test all functions
    for (Enumeration e = functions.elements(); e.hasMoreElements();) {
      String functionName = (String) e.nextElement();
      TestG2Script.main(new String[] {functionName + ".g2", functionName.toUpperCase()});
    }
  }

  private static void initializeFunctions() {
    functions = new Vector();
    functions.addElement("abs");
    functions.addElement("arctan");
    functions.addElement("average");
    functions.addElement("ceil");
    functions.addElement("cos");
    functions.addElement("exp");
    functions.addElement("expt");
    functions.addElement("floor");
    functions.addElement("ln");
    functions.addElement("log");
    functions.addElement("max");
    functions.addElement("min");
    functions.addElement("quotient");
    functions.addElement("random");
    functions.addElement("remainder");
    functions.addElement("round");
    functions.addElement("sin");
    functions.addElement("sqrt");
    functions.addElement("tan");
    functions.addElement("truncate");
  }
}
