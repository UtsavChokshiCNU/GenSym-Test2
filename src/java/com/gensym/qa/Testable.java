package com.gensym.qa;

import com.gensym.jgi.G2ConnectionInfo;

/** Defines an interface that an automatable java test must implement.
 * A test should have a main method that (possibly with the help of
 * command-line arguments such as host and port) will allow the test
 * to be run from the command-line. Most of the interesting initialization
 * should not be in the main, but should instead be in the initialize()
 * methods. An example main for an ItemRetriever test might be:
 * <blockquote>
 * <pre>
 * \/** takes -url, -host, -port, -item1, -class1, -item2, and -class2.
 *   * The latter are names
 *   * of G2 items. The G2 should be running, and if items and
 *   * classes are not specified, G2 should have foo.kb loaded. *\/
 * public static void main(String[] args) {
 *    CmdLineArgHandler cmdLine = new CmdLineArgHandler (args);
 *    String url  = cmdLine.getOptionValue ("-url");
 *    String host  = cmdLine.getOptionValue ("-host");
 *    String port  = cmdLine.getOptionValue ("-port");
 *
 *    G2ConnectionInfo connectionInfo = new G2ConnectionInfo(url, host, port);
 *
 *    MyItemRetrieverTest test = new MyItemRetrieverTest();
 *    test.initializeConnectionInfo(G2ConnectionInfo(connectionInfo));
 *    String item1 = cmdLine.getOptionValue ("-item1");
 *    String item2 = cmdLine.getOptionValue ("-item2");
 *    String class1 = cmdLine.getOptionValue ("-class1");
 *    String class2 = cmdLine.getOptionValue ("-class2");
 *    test.initialize(new Object[] {item1, class1, item2, class2});
 *
 *    try {
 *      test.runtTest();
 *    } catch (Exception ex) {
 *      ex.printStackTrace();
 *    }
 * </pre>
 * </blockquote>
 *   
 */

public interface Testable extends TestConstants{

  /** To allow the test to be configured to talk to a specific G2.
   * If part of the purpose of the test is testing if it can connect
   * to G2, then the actual call to G2Gateway.getOrMakeConnection should
   * be left until the runTest(), otherwise it should be called inside
   * initialize(Object[]).
   */
  public void initializeConnectionInfo(G2ConnectionInfo connectionInfo);

  /** Initialize the test without the help of outside data.
   * Should call <code>initialize(Object[])</code>.
   * @see #initialize(Object[])
   */
  public void initialize();

  /** Initialize the test with an array of data. Implementations must
   * document the order and size of the array, if those things matter
   * to the initialization of the test.
   * @param name Allow the caller to specify a name for this instance
   * of Testable
   * @param args Initialization parameters.
   */
  public void initialize(String name, Object[] args);

  /** What is the name of the test. This can be implemented internally
   * to return a name that depends on its initialization array, though
   * it should return the name given to the instance if one was specified.
   */
  public String getName();

  /** The description should enable readers of the test results to
   * interpret the meaning of the PASS or FAIL of the test.
   */
  public String getDescription();

  /** An EventObject that describes the result of the test. It is recommended
   * that implementors maintain an internal <code>TestResult</code>
   * variable that
   * would indicate the current stage of the test, so that an unexpected
   * exception that aborts <code>runTest()</code> will still allow the
   * test harness to
   * obtain a meaningful return value from this method.
   */
  public TestResult getResult();

  /** This is synchronous to make test running and monitoring easier.
   * The implementor should catch only the Exceptions that they feel
   * they can adequately interpret. The test harness will catch any
   * unexpected exceptions, and interpret such as failure of the test.
   * @exception Throwable an exception was thrown that the writer of
   * this Testable did not catch, because they had no specific interpretation
   * to give to such an exception.
   */
  public void runTest() throws Throwable;
}
