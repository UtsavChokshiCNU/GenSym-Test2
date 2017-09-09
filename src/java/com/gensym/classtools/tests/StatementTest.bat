del TestStatment.class
java -verify com.gensym.classtools.tests.StatementTest
java -verify com.gensym.classtools.ClassInfo report TestStatement.class > TestStatement.ins
call jad -o TestStatement.class