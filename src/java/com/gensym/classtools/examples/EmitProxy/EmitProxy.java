package com.gensym.classtools.examples.EmitProxy;

import com.gensym.classtools.*;
import java.io.*;

class EmitProxy implements TestRemote, RuntimeConstants {
  private static final boolean trace = false;

  EmitProxy () {}

  /*
   * Create a .class file for the following piece of Java code
   * 
   * public final class TestProxy {
   *	TestRemote o;
   *
   *   public TestProxy() {
   *   }
   *
   *   public TestProxy(TestRemote o) {
   *			setO(o);
   *         }
   *
   *  public void setO (TestRemote o) {
   *			this.o = o;
   *   }
   *
   *  public int bar(int i, float y, String s) {
   *			int foo = 1;
   *			return o.bar(foo,y,s);
   *	}
   * }
   */
  public static void main (String[] args) {	
    try {
			
      // Create a ClassInfo to hold the class being created.  This class is
      // named  TestProxy, it has no superior classes and it is public and
      // final.
      ClassInfo ci =  new ClassInfo(new ClassAccess(ACC_PUBLIC |
						    ACC_FINAL  |
						    ACC_SUPER),
			 "com/gensym/classtools/examples/EmitProxy/TestProxy",
				    true);

      // *** Adding an Interface ***
      InterfaceInfo intinf = new InterfaceInfo("com/gensym/classtools/examples/EmitProxy/TestRemote");
      ci.add(intinf);


      // *** Creating a field ***
      // Create a FieldRef to refer to the field o in this class
      FieldRef fr =  new FieldRef("com/gensym/classtools/examples/EmitProxy/TestProxy",
				  "o",
				  "Lcom/gensym/classtools/examples/EmitProxy/TestRemote;");
			
      // Create a FieldInfo from this object and add it to the class
      FieldInfo fi =  new FieldInfo(new Access(ACC_PRIVATE),fr);
      ci.add(fi);


      // ******** Creating 1 arg constructor method *********
			
      // Call superior constructor
      MethodRef mrc = new MethodRef("java/lang/Object",
				    "<init>",
				    "()V");

      MethodRef mrc2 = new MethodRef("com/gensym/classtools/examples/EmitProxy/TestProxy",
				     "<init>",
				     "(Lcom/gensym/classtools/examples/EmitProxy/TestRemote;)V");
			
      MethodRef mrc3 =  new MethodRef("com/gensym/classtools/examples/EmitProxy/TestProxy",
				      "setO",
				      "(Lcom/gensym/classtools/examples/EmitProxy/TestRemote;)V");

      Block bl1 = new Block();				
      MethodCall mc0 = new MethodCall(mrc,MTH_CALL_SPECIAL);
			
      Variable var1;
      MethodCall mc1 = new MethodCall(mrc3,
				      new Expression[] {var1 = new Variable("o","Lcom/gensym/classtools/examples/EmitProxy/TestRemote;")},
				      MTH_CALL_VIRTUAL);
			
      // Add statements to the block
      bl1.add(mc0);
      bl1.add(mc1);
      bl1.add(new Return());

      // Add block to MethodInfo
      MethodInfo mi = new MethodInfo(new Access(ACC_PUBLIC),
				     mrc2,
				     new String[] { "o" },
				     bl1);
			
      // Add the constructor MethodInfo to the class
      ci.add(mi);



      // ********** Create Set method ***************************

      Block bl2 = new Block();
			
      // Assign field o to be the first argument of the constructor
      OperatorCall st =  new OperatorCall("=",
					  new Expression[] 
					  {fr,
					     new Variable("o","Lcom/gensym/classtools/examples/EmitProxy/TestRemote;")
					     });
      bl2.add(st);
      bl2.add(new Return());


      // Add block to MethodInfo
      MethodInfo mi2 = new MethodInfo(new Access(ACC_PUBLIC),
				      mrc3,
				      new String[] { "o" },
				      bl2);		

      // Add the set method to the class
      ci.add(mi2);

			
      // ********** Create Instance Method ***************
      // Create the block for the instance method
      MethodRef mrc5 = new MethodRef("com/gensym/classtools/examples/EmitProxy/TestProxy",
				     "bar",
				     "(IFLjava/lang/String;)I");	

      InterfaceMethodRef mrc6 = new InterfaceMethodRef("com/gensym/classtools/examples/EmitProxy/TestRemote",
						       "bar",
						       "(IFLjava/lang/String;)I");
      Block bl3 =  new Block();
      bl3.add(new VariableDeclaration("foo","I",new Value(1)));


      Expression[] eargs = {new Variable("foo","I"),
			    new Variable("y","F"),
			    new Variable("s","Ljava/lang/String;")};
      bl3.add(new Return(new MethodCall(fr,mrc6,eargs,MTH_CALL_INTERFACE)));

      MethodInfo mi3 = new MethodInfo(new Access(ACC_PUBLIC),
				      mrc5,
				      new String[] { "i", "y", "s" },
				      bl3);

      // Add the instance method to the class
      ci.add(mi3);
			

      // ************* Output the bytes to file  *************
      FileOutputStream fileOutStream = new FileOutputStream(args[0]);
      fileOutStream.write(ci.getBytes(true));
      fileOutStream.close();
			
      //************** Load the new class into this VM ************
      Class cl = Class.forName("com.gensym.classtools.examples.EmitProxy.TestProxy");
      System.out.println("Loaded the " + cl);
			
      // Create an instance and do some operations on it
      TestRemote tr = (TestRemote) cl.newInstance();
      System.out.println(tr);
      tr.setO((TestRemote) new EmitProxy());
      System.out.println(tr.bar(1,(float) 4.0, "foo"));
    }
    catch (Exception e) {
      System.out.println("Failure " + e);
      e.printStackTrace();
    }
  }

  @Override
  public int bar(int i, float f, String s) {
    return (int) (f * i + s.hashCode());
  }

  @Override
  public void setO(TestRemote o) {
  }
}



