cd %DST_BOX%\com\gensym\g2script
del *.class
javac *.java
cd tests
echo "<<< TESTING ARITHMETIC FUNCTIONS"
java com.gensym.g2script.tests.FunctionTest
echo ">>> END ARITHMETIC TESTS"
cd..

