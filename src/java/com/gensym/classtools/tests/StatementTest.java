package com.gensym.classtools.tests;

import com.gensym.classtools.*;
import java.util.*;
import java.io.*;

public class StatementTest implements RuntimeConstants {


public static void main (String[] args) {	
  try {
    
    String className = "com/gensym/classtools/tests/TestStatement";
    // Create a ClassInfo to hold the class being created.  This class is named
    // TestProxy, it has no superior classes and it is public and final.
    ClassInfo ci =  new ClassInfo(new ClassAccess(ACC_PUBLIC |
      ACC_FINAL  |
      ACC_SUPER),
      className,
      true);
    
    // *** Adding an Interface ***
    InterfaceInfo intinf = new InterfaceInfo("com/gensym/classtools/tests/TestExpressionInterface");
    ci.add(intinf);
    
    
    // An instance method 
    
    MethodRef mr = new MethodRef("com/gensym/classtools/tests/TestExpression",
      "test",
      "()V");			
    Block b = new Block();
    
    
    b.add(new VariableDeclaration("myboo","Z",new Value(false)));
    b.add(new VariableDeclaration("myboo2","Z",new Value(false)));
    Variable var = new Variable("myboo","Z");
    Variable var2 = new Variable("myboo2","Z");
    b.add(new VariableDeclaration("myint","I",new Value(10)));
    b.add(new VariableDeclaration("myint2","I",new Value(20)));
    Variable var3 = new Variable("myint","I");
    Variable var4 = new Variable("myint2","I");

  
    // If statements

    // Simple If statements 
    
    b.add(new If(var,
            new StatementExpression(new OperatorCall("=",new Expression[] {var, new Value(true)}))));


    b.add(new If(var2,
      new StatementExpression(new OperatorCall("=",new Expression[] {var, new Value(true)})),
      new StatementExpression(new OperatorCall("=",new Expression[] {var, new Value(false)}))));

    /* ! */

    b.add(new OperatorCall("=",
      new Expression[] {var, new OperatorCall("!",new Expression[] {var})}));

    b.add(new OperatorCall("=",
      new Expression[] {var, new OperatorCall ("?:", new Expression[] {
                                            new OperatorCall("!",new Expression[] {var}),
                                            var,
                                            var2})}));

    b.add(new If(new OperatorCall("!",new Expression[] {var}),
                 new StatementExpression(new OperatorCall("=",new Expression[] {var, new Value(true)}))));
    
       
    b.add(new If(new OperatorCall("!",new Expression[] {var}),
                 new StatementExpression(new OperatorCall("=",new Expression[] {var, new Value(true)})),
                 new StatementExpression(new OperatorCall("=",new Expression[] {var, new Value(false)}))));



    /* || */
    
    b.add(new OperatorCall("=",new Expression[] {var, 
      new OperatorCall("||", new Expression[] {var, var2})})); 

    b.add(new OperatorCall("=",
      new Expression[] {var, new OperatorCall ("?:", new Expression[] {
                                            new OperatorCall("||",new Expression[] {var, var2}),
                                            var,
                                            var2})}));

    b.add(new If(new OperatorCall("||",new Expression[] {var, var2}),
                 new StatementExpression(new OperatorCall("=",new Expression[] {var, new Value(true)}))));

    b.add(new If(new OperatorCall("||", new Expression[] {var, var2}),
      new StatementExpression(new OperatorCall("=",new Expression[] {var, new Value(true)})),
      new StatementExpression(new OperatorCall("=",new Expression[] {var, new Value(false)}))));

    /* && */

    b.add(new OperatorCall("=",new Expression[] {var2, 
      new OperatorCall("&&", new Expression[] {var, var2})}));

    b.add(new OperatorCall("=",
      new Expression[] {var, new OperatorCall ("?:", new Expression[] {
                                            new OperatorCall("&&",new Expression[] {var, var2}),
                                            var,
                                            var2})}));

    b.add(new If(new OperatorCall("&&",new Expression[] {var, var2}),
                 new StatementExpression(new OperatorCall("=",new Expression[] {var, new Value(true)}))));

    b.add(new If(new OperatorCall("&&", new Expression[] {var, var2}),
                 new StatementExpression(new OperatorCall("=",new Expression[] {var, new Value(true)})),
                 new StatementExpression(new OperatorCall("=",new Expression[] {var, new Value(false)}))));
         
    /* | */
    
    b.add(new OperatorCall("=",new Expression[] {var, 
      new OperatorCall("|", new Expression[] {var, var2})})); 

    b.add(new OperatorCall("=",
      new Expression[] {var, new OperatorCall ("?:", new Expression[] {
                                            new OperatorCall("|",new Expression[] {var, var2}),
                                            var,
                                            var2})}));

    b.add(new If(new OperatorCall("|",new Expression[] {var, var2}),
                 new StatementExpression(new OperatorCall("=",new Expression[] {var, new Value(true)}))));

    b.add(new If(new OperatorCall("|", new Expression[] {var, var2}),
      new StatementExpression(new OperatorCall("=",new Expression[] {var, new Value(true)})),
      new StatementExpression(new OperatorCall("=",new Expression[] {var, new Value(false)}))));


    /* & */
    
    b.add(new OperatorCall("=",new Expression[] {var, 
      new OperatorCall("&", new Expression[] {var, var2})})); 

    b.add(new OperatorCall("=",
      new Expression[] {var, new OperatorCall ("?:", new Expression[] {
                                            new OperatorCall("&",new Expression[] {var, var2}),
                                            var,
                                            var2})}));

    b.add(new If(new OperatorCall("&",new Expression[] {var, var2}),
                 new StatementExpression(new OperatorCall("=",new Expression[] {var, new Value(true)}))));

    b.add(new If(new OperatorCall("&", new Expression[] {var, var2}),
      new StatementExpression(new OperatorCall("=",new Expression[] {var, new Value(true)})),
      new StatementExpression(new OperatorCall("=",new Expression[] {var, new Value(false)}))));


    /* ^ */
    
    b.add(new OperatorCall("=",new Expression[] {var, 
      new OperatorCall("^", new Expression[] {var, var2})})); 

    b.add(new OperatorCall("=",
      new Expression[] {var, new OperatorCall ("?:", new Expression[] {
                                            new OperatorCall("^",new Expression[] {var, var2}),
                                            var,
                                            var2})}));

    b.add(new If(new OperatorCall("^",new Expression[] {var, var2}),
                 new StatementExpression(new OperatorCall("=",new Expression[] {var, new Value(true)}))));

    b.add(new If(new OperatorCall("^", new Expression[] {var, var2}),
      new StatementExpression(new OperatorCall("=",new Expression[] {var, new Value(true)})),
      new StatementExpression(new OperatorCall("=",new Expression[] {var, new Value(false)}))));

                  
    /* > */

    b.add(new OperatorCall("=",
      new Expression[] {var, new OperatorCall(">",new Expression[] {var3,var4})}));

    b.add(new OperatorCall("=",
      new Expression[] {var, new OperatorCall ("?:", new Expression[] {
                                            new OperatorCall(">",new Expression[] {var3, var4}),
                                            var,
                                            var2})}));
    
    b.add(new If(new OperatorCall(">",new Expression[] {var3,var4}),
                 new StatementExpression(new OperatorCall("=",new Expression[] {var, new Value(true)}))));

    b.add(new If(new OperatorCall(">",new Expression[] {var3,var4}),
                 new StatementExpression(new OperatorCall("=",new Expression[] {var, new Value(true)})),
                 new StatementExpression(new OperatorCall("=",new Expression[] {var, new Value(false)}))));

    /* < */

    b.add(new OperatorCall("=",
      new Expression[] {var, new OperatorCall("<",new Expression[] {var3,var4})}));

    b.add(new OperatorCall("=",
      new Expression[] {var, new OperatorCall ("?:", new Expression[] {
                                            new OperatorCall("<",new Expression[] {var3, var4}),
                                            var,
                                            var2})}));

    b.add(new If(new OperatorCall("<",new Expression[] {var3,var4}),
                 new StatementExpression(new OperatorCall("=",new Expression[] {var, new Value(true)}))));
    
    b.add(new If(new OperatorCall("<",new Expression[] {var3,var4}),
                 new StatementExpression(new OperatorCall("=",new Expression[] {var, new Value(true)})),
                 new StatementExpression(new OperatorCall("=",new Expression[] {var, new Value(false)}))));

    /* >= */

    b.add(new OperatorCall("=",
      new Expression[] {var, new OperatorCall(">=",new Expression[] {var3,var4})}));

    b.add(new OperatorCall("=",
      new Expression[] {var, new OperatorCall ("?:", new Expression[] {
                                            new OperatorCall("<=",new Expression[] {var3, var4}),
                                            var,
                                            var2})}));

    b.add(new If(new OperatorCall(">=",new Expression[] {var3,var4}),
                 new StatementExpression(new OperatorCall("=",new Expression[] {var, new Value(true)}))));

    b.add(new If(new OperatorCall(">=",new Expression[] {var3,var4}),
                 new StatementExpression(new OperatorCall("=",new Expression[] {var, new Value(true)})),
                 new StatementExpression(new OperatorCall("=",new Expression[] {var, new Value(false)}))));

    /* <= */

    b.add(new OperatorCall("=",
      new Expression[] {var, new OperatorCall("<=",new Expression[] {var3,var4})}));

    b.add(new OperatorCall("=",
      new Expression[] {var, new OperatorCall ("?:", new Expression[] {
                                            new OperatorCall("<=",new Expression[] {var3, var4}),
                                            var,
                                            var2})}));

    b.add(new If(new OperatorCall("<=",new Expression[] {var3,var4}),
                 new StatementExpression(new OperatorCall("=",new Expression[] {var, new Value(true)}))));

    b.add(new If(new OperatorCall("<=",new Expression[] {var3,var4}),
                 new StatementExpression(new OperatorCall("=",new Expression[] {var, new Value(true)})),
                 new StatementExpression(new OperatorCall("=",new Expression[] {var, new Value(false)}))));

    
    /* == */

    b.add(new OperatorCall("=",
      new Expression[] {var, new OperatorCall("==",new Expression[] {var3,var4})}));

    b.add(new OperatorCall("=",
      new Expression[] {var, new OperatorCall ("?:", new Expression[] {
                                            new OperatorCall("==",new Expression[] {var3, var4}),
                                            var,
                                            var2})}));

    b.add(new If(new OperatorCall("==",new Expression[] {var3,var4}),
                 new StatementExpression(new OperatorCall("=",new Expression[] {var, new Value(true)}))));

    b.add(new If(new OperatorCall("==",new Expression[] {var3,var4}),
                 new StatementExpression(new OperatorCall("=",new Expression[] {var, new Value(true)})),
                 new StatementExpression(new OperatorCall("=",new Expression[] {var, new Value(false)}))));

   /* != */

    b.add(new OperatorCall("=",
      new Expression[] {var, new OperatorCall("!=",new Expression[] {var3,var4})}));

    b.add(new OperatorCall("=",
      new Expression[] {var, new OperatorCall ("?:", new Expression[] {
                                            new OperatorCall("!=",new Expression[] {var3, var4}),
                                            var,
                                            var2})}));

    b.add(new If(new OperatorCall("!=",new Expression[] {var3,var4}),
                 new StatementExpression(new OperatorCall("=",new Expression[] {var, new Value(true)}))));

    b.add(new If(new OperatorCall("!=",new Expression[] {var3,var4}),
                 new StatementExpression(new OperatorCall("=",new Expression[] {var, new Value(true)})),
                 new StatementExpression(new OperatorCall("=",new Expression[] {var, new Value(false)}))));


    /* ?: */

    b.add(new OperatorCall("=",
      new Expression[] {var, new OperatorCall("?:",new Expression[] {var,var,var2})}));

    b.add(new If(new OperatorCall("?:",new Expression[] {var,var,var2}),
                 new StatementExpression(new OperatorCall("=",new Expression[] {var, new Value(true)}))));

    b.add(new If(new OperatorCall("?:",new Expression[] {var,var,var2}),
                 new StatementExpression(new OperatorCall("=",new Expression[] {var, new Value(true)})),
                 new StatementExpression(new OperatorCall("=",new Expression[] {var, new Value(false)}))));


    // While statement  
    
    Block whileBlock = new Block();
    
    whileBlock.add(new If(new OperatorCall("!",new Expression[] {var}),new Continue()));
    whileBlock.add(new OperatorCall("=",new Expression[] {var,
                                        new OperatorCall("!", new Expression[] {var})}));
    b.add(new While(var,whileBlock));
    
    
    // Do statement
    
    Block doBlock = new Block();
    doBlock.add(new OperatorCall("=",
      new Expression [] {var,
      new OperatorCall("!", new Expression[] {var})}));
    If iff = new If(new OperatorCall("&&", new Expression[] { var, var2 }),
      new Break());
    doBlock.add(iff);
    b.add(new Do(doBlock,var));

    b.add(new Return());
    
    MethodInfo mi = new MethodInfo(new Access(ACC_PUBLIC),
      mr,
      null,
      b);
    ci.add(mi);
    
    // ************* Output the bytes to file  *************
    FileOutputStream fileOutStream = new FileOutputStream("TestStatement.class");
    fileOutStream.write(ci.getBytes(true));
    fileOutStream.close();
    
    
    //************** Load the new class into this VM ************
    Class cl = Class.forName("com.gensym.classtools.tests.TestStatement");
    System.out.println("Loaded the " + cl);
    TestExpressionInterface a = (TestExpressionInterface) cl.newInstance();
    System.out.println("New instance created " + a);
    a.test();
    
  }
  catch (Exception e) 
  {
    System.out.println("Failure " + e);
    e.printStackTrace();
  }
}
}
