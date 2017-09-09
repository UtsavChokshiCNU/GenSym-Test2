del ClassA.class ClassB.class ClassC.class
java -verify com.gensym.classtools.examples.EmitMultiInterfaces.EmitMultiInterfaces
java -verify com.gensym.classtools.ClassInfo report ClassA.class
java -verify com.gensym.classtools.ClassInfo report ClassB.class
java -verify com.gensym.classtools.ClassInfo report ClassC.class
