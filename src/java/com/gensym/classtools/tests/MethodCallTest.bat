del TestMethodCall.class
java -verify com.gensym.classtools.tests.MethodCallTest 
java -verify com.gensym.classtools.ClassInfo report TestMethodCall.class > TestMethodCall.ins
call jad -o TestMethodCall.class 