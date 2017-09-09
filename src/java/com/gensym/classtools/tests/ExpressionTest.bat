del TestExpression.class
java -verify com.gensym.classtools.tests.ExpressionTest 0 7 0 3 0 2 0 -1
java -verify com.gensym.classtools.ClassInfo report TestExpression.class > TestExpression.ins
call jad -o TestExpression.class 


