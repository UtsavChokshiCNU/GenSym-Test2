del TestSynchronized.class
java -verify com.gensym.classtools.tests.SynchronizedTest
java -verify com.gensym.classtools.ClassInfo report TestSynchronized.class > TestSynchronized.ins
call jad -o TestSynchronized.class