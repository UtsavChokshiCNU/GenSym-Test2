set G2HOST=localhost
set G2PORT=1111
cd %SRCBOX%\java\com\gensym\tests\jgi\testharness
echo OFF
echo JavaLink Testharness starter
echo "Usage runin_sandbox <email address for reports>
echo Ensure /java/products/javalink/kbs/testharness/jgi-th-main.kb is loaded in a G2
echo at %G2HOST% port %G2PORT%

rem If you change the G2HOST name you must also change the interfaces used in the TestHarness KB

cd %SRCBOX%\java\com\gensym\tests\jgi\testharness

echo ...
echo Downloading stubs required for Java Test Harness...
java com.gensym.jgi.download.DownloadInterfaces -force -stubs -classes A-TEST-CLASS GSI-INTEGER-CLASS GSI-FLOAT-CLASS GSI-SYMBOL-CLASS GSI-SYMBOL-CLASS GSI-LOGICAL-CLASS GSI-STRING-CLASS GSI-QUANTITY-CLASS EVENT-SOURCE-CLASS EVENT-SOURCE-EVENT -host %G2HOST% -port %G2PORT% 

echo ...
echo Compiling Test Harness...
javac *.java

echo ...
echo Starting Java Side Test Harness 
start java -nojit -mx110m com.gensym.tests.jgi.testharness.ThGI -mailto %1

echo ...
echo Starting G2 Side Test Harness
echo ...
echo Warning
echo ...The Test Harness WILL generate many files in com/gensym/classes/modules
echo ...you must clear,recheckout and compile com/gensym/classes/modules before
echo ...restarting.
java com.gensym.tests.jgi.testharness.G2Starter -host %G2HOST% -port %G2PORT%





