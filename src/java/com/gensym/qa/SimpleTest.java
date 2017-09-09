package com.gensym.qa;

import com.gensym.jgi.G2ConnectionInfo;

/** Encapsulates the handling of results and the. When subclassing,
 * initialize the testResult field in all constructors. Similarly,
 * the initialization of testName is left up to the subclass.
 */
public abstract class SimpleTest implements Testable, TestConstants{

  // generic local variables
  protected TestResult testResult;
  protected String testName;

  @Override
  public TestResult getResult() {
    return testResult;
  }

  @Override
  public void initializeConnectionInfo(G2ConnectionInfo info) {
  }

  @Override
  public String getName() {
    if (testName == null) {
      return getClass().getName();
    } else {
      return testName;
    }
  }
}
  
