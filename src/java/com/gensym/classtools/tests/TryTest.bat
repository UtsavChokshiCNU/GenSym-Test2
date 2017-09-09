del TestTry.class
java -verify com.gensym.classtools.tests.TryTest
java -verify com.gensym.classtools.ClassInfo report TestTry.class > TestTry.ins
call jad -o TestTry.class 