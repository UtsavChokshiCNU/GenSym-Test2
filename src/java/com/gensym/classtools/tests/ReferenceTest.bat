del TestReference.class
java -verify com.gensym.classtools.tests.ReferenceTest
java -verify com.gensym.classtools.ClassInfo report TestReference.class > TestReference.ins
call jad -o TestReference.class