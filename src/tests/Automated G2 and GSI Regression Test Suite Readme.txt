G2 and GSI Automated Regression Test Suite.

1)	Checkout the G2 regression testkbs from https://trilogy-svn.cvsdude.com/gensym/trunk/tests/ to the testing machine.

2)	Make sure that path to the test folder doesn’t contain any space and also don’t move any files or folders from the tests folder.

3)	Compile “RegressionTests.java” [Hint: You need JDK 1.5 or above version].

4)	If needed edit the testkbs_list.txt for removing or adding any test to the Automated Regression Test Suite 

5)	GSI Regression test is conducted by default, so there is no need to mention the “gsi-suite.kb” in the testkbs_list.txt.

6)	If you dont intend to perform GSI regression test , then pass “-gsi” as a second argument to the test suite. Example: Java RegressionTest “C:\Program Files\Gensym\g2-8.3r1” -gsi

7)	Help for using the Suite can be obtained by running “java RegressionTests” or “java RegressionTests –help” or “java RegressionTests /?”.

8)	Run >java RegressionTests “<g2 path>” Note: Excluding last ‘g2’ 

Example : java RegressionTests C:\Program Files\Gensym\g2-8.3r1” , if you have installed G2 on your machine.
          
		  If you want to run this tests on VM image then goto C:\G2\src\scripts\nt then create a new folder named G2 and copy startserver.bat
		  from C:\G2\src\scripts\nt to C:\G2\src\scripts\nt\g2 directory. Now execute the below command
		  
		  java -classpath . RegressionTests C:\G2\src\scripts\nt  , it will start G2 and run the test KB present in tests folder
		   

9)	Result’s can be found in “C:\results” by default but can me modified by editing  settings.txt (resides in tests folder).

10)	Detailed output of the tests will be in file  <results>\ test-results-log.rg”

11)	Brief Summary of the tests will be in <results> Regr-test-summary.log”


Notes: You might encounter  Exception in thread "main" java.lang.NoClassDefFoundError: RegressionTest error then use below command to execute RegressionTest class
 Open CMD Prompt , Goto test folder on filesystem then execute : java -classpath . RegressionTest
 
 