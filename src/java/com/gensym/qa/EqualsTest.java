package com.gensym.qa;

import com.gensym.util.CmdLineArgHandler;

/** Tests whether the .equals between n objects satisfies
 * reflexitivity (where n >= 1), symmetry (where n >= 2),
 * transitivity (where n >= 3), and whether the .equals returns
 * the desired value.
 */

public class EqualsTest extends SimpleTest {

  protected Object[] initArray;
  protected boolean compareDesiredValue = false;
  protected boolean desiredValue;

  /** Creates the top-level TestResult object.
   */
  public EqualsTest() {
    testResult = new TestResult(this);
  }

  @Override
  public String getDescription() {
    return "Tests the quality of the .equals() methods of the provided Objects.\nTests for reflexitivity, symmetry and transitivity";
  }

  /** @exception RuntimeException if you call this method.
   */
  @Override
  public void initialize() {
    throw new RuntimeException("cannot run empty");
  }

  /** @param args {<Boolean: desiredValue>, 
   *               <Object obj1>[, <Object obj2>, ...]}.
   * If desiredValue is null, then only the reflexitivity, symmetry,
   * and transitivity are tested. It is presumed that all the .equals
   * should return the same result (this is only interesting when there
   * are more than 2 objects being tested.
   */
  @Override
  public void initialize(String subName, Object[] args) {
    initArray = args;
    testName = "EqualsTest: " + subName;

    if (args.length == 0)
      return;

    if (args[0] != null) {
      compareDesiredValue = true;
      desiredValue = ((Boolean)args[0]).booleanValue();
    }
  }

  @Override
  public void runTest() {
    int length = initArray.length;
    reflexitivity();
    if (length >= 3) {
      symmetry();
      if (compareDesiredValue) {
	if(initArray[1].equals(initArray[2]) == desiredValue) {
	  testResult.add(new TestResult(this, "desiredResult", PASSED_));
	} else {
	  testResult.
	    add(new TestResult(this, "desiredValue", FAILED_,
			       ".equals did not yield desired value: " +
			       desiredValue));
	}
      }
    }
    if (length >= 4)
      transitivity();
  }

  protected void reflexitivity() {
    String subTest = "reflexitivity";
    try {
      boolean result = initArray[1].equals(initArray[1]);
      if (result != true) {
	testResult.add(new TestResult(this, subTest, FAILED_,
				      ".equals must be reflexive"));
      } else {
	testResult.add(new TestResult(this, subTest, PASSED_));
      }
    } catch (Exception ex) {
      testResult.add(new TestResult(this, subTest, FAILED_,
				    ".equals must be robust", ex));
    }
  }

  protected void symmetry() {
    String subTest = "symmetry";
    try {
      boolean result1 = initArray[1].equals(initArray[2]);
      boolean result2 = initArray[2].equals(initArray[1]);

      if (result1 != result2) {
	testResult.add(new TestResult(this, subTest, FAILED_,
				      ".equals must be symmetric"));
      } else {
	testResult.add(new TestResult(this, subTest, PASSED_));
      }
    } catch (Exception ex) {
      testResult.add(new TestResult(this, subTest, FAILED_,
				    ".equals must be robust", ex));
    }
  }

  protected void transitivity() {
    String subTest = "transitivity";

    try {
      boolean result = initArray[1].equals(initArray[2]);
      boolean failed = false;

      for (int i = 3; i < initArray.length; i++) {
	if (result != initArray[i - 1].equals(initArray[i])) {
	  testResult.add(new TestResult(this, subTest, FAILED_,
					"transivity failed at i = " + i +
					"; obj1: " + initArray[i - 1] +
					"; obj2: " + initArray[i]));
	  failed = true;
	  break;
	}
      }
      if (failed != true) {
	testResult.add(new TestResult(this, subTest, PASSED_));
      }
    } catch (Exception ex) {
      testResult.add(new TestResult(this, subTest, FAILED_,
				    ".equals must be robust", ex));
    }
  }

  /** Usage: <command> [-constructed-equals] class1 [class2 ...]
   *Tests all the classes in the command-line to see if instances
   * of the classes on the command-line satisfy the basics of .equals(),
   * namely that equals is reflexive and symmetric.
   * In this case it is also assumed that objects can be created with
   * a no-arg constructor.
   * <p> If -constructed-equals is specifies, a class will fail if two
   * objects created with a no-arg constructor are not .equals()
   * This should be pass for some classes (such as com.gensym.util.Structure),
   * but not necessarily all (it fails for java.lang.Object, for example).
   */
  public static void main (String[] args) {
    CmdLineArgHandler cmdLine = new CmdLineArgHandler (args);

    boolean wantTrue = cmdLine.getSwitchValue("-constructed-equals");
    
    int start = (wantTrue? 1 : 0);

    EqualsTest overallTest = new EqualsTest();
    overallTest.initialize("Overall", new Object[] {});
    TestResult overallTestResult = new TestResult(overallTest);
    for (int i = start; i < args.length; i++) {
      try {
	Class clazz = Class.forName(args[i]);
	Object instance1 = clazz.newInstance();
	Object instance2 = clazz.newInstance();
	EqualsTest test = new EqualsTest();
	test.initialize(args[i], new Object[] {(wantTrue ?
						Boolean.TRUE : null),
						 instance1,
						 instance2});
	test.runTest();
	overallTestResult.add(test.getResult());
      } catch (Throwable ex) {
	overallTestResult.add(new TestResult(overallTest,
					     "constructor", FAILED_,
					     "Class failed", ex));
      }
    }
    System.out.print(overallTestResult.pprint(""));
  }
}
