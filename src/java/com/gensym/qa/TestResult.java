package com.gensym.qa;

import java.util.Vector;
import java.util.Enumeration;

import com.gensym.util.Symbol;
import com.gensym.util.UnexpectedException;

/** Encapsulates the results of a test. Allows for nesting of
 * test results. An instance of Testable should maintain an instance
 * of TestResult and <code>add</code> subtest results to it.
 */

public class TestResult extends java.util.EventObject implements TestConstants{
  private Vector subTests = new Vector();
  private Symbol status = PASSED_;
  private String message;
  private String testName;
  private Exception exception;
  private Throwable caughtException;
  private boolean printStackTrace = true;

  /** Typically used for non-leaf tests (e.g., the "top-level" TestResult
   * that will be returned by a Testable).
   */
  public TestResult(Testable source) {
    super(source);
    exception = new Exception();
    testName = source.getName();
  }

  /** Typically used by "leaf" tests (e.g., and individual test within
   * a Testable.
   * @param source the actual test object that created this result.
   * @param the name assigned to this specific TestResult.
   * @param status one of the constants from com.gensym.qa.TestConstants
   * @param message in the case of failure, this description should
   * describe the nature of the failure.
   */
  public TestResult(Testable source, String testName,
		    Symbol status, String message) {
    this(source);
    this.status = status;
    this.message = message;
    if (testName != null) {
      this.testName = testName;
    }
  }
  
  /** Typically used by "leaf" tests (e.g., and individual test within
   * a Testable) for a PASSED_ result.
   * @param source the actual test object that created this result.
   * @param the name assigned to this specific TestResult.
   * @param status one of the constants from com.gensym.qa.TestConstants
   */
  public TestResult(Testable source, String testName,
		    Symbol status) {
    this(source, testName, status, null);
  }

  /** Typically used by leaf tests in the case of failures that
   * involve an exception being thrown.
   * @param source the actual test object that created this result.
   * @param the name assigned to this specific TestResult.
   * @param status one of the constants from com.gensym.qa.TestConstants
   * @param message in the case of failure, this description should
   * describe the nature of the failure.
   * @param caughtException if the failure was an exception, this stores the
   * exception.
   */
  public TestResult(Testable source, String testName, Symbol status,
		    String message, Throwable caughtException) {
    this(source, testName, status, message);
    this.caughtException = caughtException;
    if (printStackTrace) {
      caughtException.printStackTrace();
    }
  }
  
  public boolean passed() {
    return PASSED_.equals(status);
  }

  /** Adds the test result to the list of subtests. If the subtest did not
   * return the status PASSED_, this TestResult is set to FAILED_.
   */
  public void add(TestResult result) {
    subTests.addElement(result);
    if (!result.passed()) {
      status = FAILED_;
    }
  }

  /** Adds the test result to the list of subtests, but does not affect
   * the overall result of the test.
   */
  public void note(TestResult result) {
    subTests.addElement(result);
  }

  /** Enumerates over the subtests.
   */
  public Enumeration getSubTestResults() {
    return subTests.elements();
  }

  private static String indenter = "  ";

  /** Returns an indented string of one line per subtest.
   * Can be arbitrarily nested. The top-level test is reported first.
   */
  public String pprint(String indenter) {
    testName = (testName == null ? ((Testable)source).getName() : testName);
    StringBuffer buf = new StringBuffer(indenter);
    buf.append(testName);
    buf.append(": ");
    buf.append(status.toString());
    if (message != null) {
      buf.append(": ");
      buf.append(message);
    }
    if (caughtException != null) {
      buf.append("; EXCEPTION: ");
      buf.append(caughtException.toString());
    }
    if (!subTests.isEmpty()) {
      buf.append("\n");
      
      for (Enumeration en = subTests.elements(); en.hasMoreElements();) {
	TestResult next = (TestResult)en.nextElement();
	buf.append(indenter);
	buf.append(next.pprint(this.indenter));
	buf.append("\n");
      }
    }

    return buf.toString();    
  }

  /** This method can only change the result if the result is currently
   * <code>null</code> or <code>PASSED_</code>.
   */
  public void setStatus(Symbol newStatus) {
    if (status == null || PASSED_.equals(status)) {
      status = newStatus;
    }
  }

  public Symbol getStatus() {
    return status;
  }

  /** This would typically be set just prior to returning the TestResult
   * in the case of non-leaf tests.
   */
  public void setMessage(String message) {
    this.message = message;
  }

  /** It is usually better to add a test result than to
   * append a message.
   */
  public void appendMessage(String message) {
    this.message = this.message + "; " + message;
  }

  /** The name given to this TestResult.
   */
  public String getName() {
    return (testName == null ? ((Testable)getSource()).getName() :
	    testName);
  }

  /** This is guaranteed to return an exception that was 
   * created when the test result was created. It can be used to
   * more quickly identify the exact line of code relating to the
   * failure.
   */
  public Exception getException() {
    return exception;
  }

  /** @return Throwable If the test result was created as the result of
   * catching an Exception, this will return the exception that was
   * caught.
   */
  public Throwable getCaughtException() {
    return caughtException;
  }
}
