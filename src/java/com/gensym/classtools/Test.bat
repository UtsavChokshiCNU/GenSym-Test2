cd %SRCBOX%\java\com\gensym\classtools
rm *.class
javac *.java
cd examples\EmitSimpleClass
javac *.java
java -verify com.gensym.classtools.examples.EmitSimpleClass.SimpleClass
cd ..\..\examples\EmitInterface
javac EmitInterface.java
call EmitInterface.bat
cd ..\..\examples\EmitMultiInterfaces
javac EmitMultiInterfaces.java
call EmitMultiInterfaces.bat
cd ..\..\examples\EmitProxy
javac EmitProxy.java
call EmitProxy.bat
cd ..\..\examples\EmitNativeStubs
javac EmitNativeStubs.java
java com.gensym.classtools.examples.EmitNativeStubs.EmitNativeStubs
cd ..\..\examples\MergeClassLoader
javac *.java
call MergeClassLoader.bat
cd ..\..
cd tests
javac ExpressionTest.java StatementTest.java MethodCallTest.java TryTest.java
javac SourceFileAttributeTest.java LineNumberTableTest.java 
javac ReferenceTest.java TryExpressionTest.java
javac InstanceOfTest.java SynchronizedTest.java
call ExpressionTest.bat
call StatementTest.bat
call MethodCallTest.bat
call TryTest.bat
call SourceFileAttributeTest.bat
call LineNumberTableTest.bat
call ReferenceTest,bat
call TryExpressionTest.bat
call InstanceOfTest.bat
call SynchronizedTest.bat