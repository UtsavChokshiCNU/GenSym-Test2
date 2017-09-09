package com.gensym.classtools.examples.EmitInterface;

import com.gensym.classtools.*;
import java.io.*;

   /*
   *    An example use of the classtools facility to create a .class file for
   *    the following code:
   *
   *    import java.lang.*;
   *    import com.gensym.util.*;
   *    import com.gensym.jgi.*;
   *
   *	public interface Item extends SystemItem {
   *
   *    public static final Symbol ITEM_ = Symbol.intern ("ITEM");
   *    static final Symbol g2ClassName = ITEM_;
   *    static final Symbol[] classInheritancePath 
   *              = new Symbol[] {ITEM_, SYSTEM_ITEM_, ROOT_};
   *
   *
   *    public com.gensym.util.Symbol getRepresentationType() 
   *                           throws G2AccessException;
   *
   *    public int getItemWidth() throws G2AccessException;
   *
   *    public int getItemHeight() throws G2AccessException;
   *
   *    public int getItemYPosition() throws G2AccessException;
   *
   *    public int getItemXPosition() throws G2AccessException;
   *   }
   */

class EmitInterface implements RuntimeConstants {
  private static final boolean trace = false;

  EmitInterface () {}


  public static void addSimpleField(ClassInfo ci, Access acc,
				    FieldRef fr,
				    Expression e) 
       throws ClassException {
	 // Create a FieldInfo from this object and add it to the class
	 FieldInfo fi =  new FieldInfo(acc,fr,e);			
	 ci.add(fi);	
  } 

  public static void addSimpleMethod(ClassInfo ci, Access acc,
				     String methodName, String descriptor,
				     ClassRef[] exceptions) 
       throws ClassException {
	 MethodRef mrc = new MethodRef(ci.getClassName(),
				       methodName,
				       descriptor);
	 MethodInfo mi =  new MethodInfo(acc,mrc,null,exceptions);
	 ci.add(mi);
  }
	
  public static void main (String[] args) {	
    String className = "com/gensym/classes/Item";
    String superClassName = "com/gensym/classes/SystemItem";
    String rootClassName = "com/gensym/classes/Root";
    String symbolClassName = "Lcom/gensym/util/Symbol;";
    String symbolArrayClassName = "[Lcom/gensym/util/Symbol;";
    Access publicStaticFinal = new Access(ACC_PUBLIC |
					  ACC_STATIC |
					  ACC_FINAL);
    Access staticFinal = new Access(ACC_STATIC |
				    ACC_FINAL);
    Access publicAbstract = new Access(ACC_PUBLIC |
				       ACC_ABSTRACT);

    try {

      // Create a ClassInfo to hold the class being created.  
      // This class is named TestInterface, it has no superior
      // classes and it is public and final.
      ClassInfo ci =  new ClassInfo(new InterfaceAccess(ACC_INTERFACE |
							ACC_PUBLIC),
				    className,
				    superClassName,
				    false);
		
      // *** Creating fields and their initializers ***

      // public static final Symbol ITEM_ = Symbol.intern ("ITEM");
      MethodRef mrc = new MethodRef(symbolClassName,
				    "intern",
			       "(Ljava/lang/String;)Lcom/gensym/util/Symbol;");
      MethodCall mc =  new MethodCall(mrc,new Expression[] { new Value("ITEM")
							       },
      MTH_CALL_STATIC);
      FieldRef fr =  new FieldRef(ci.getClassName(),
				  "ITEM_",
				  symbolClassName,true);
      addSimpleField(ci,publicStaticFinal,fr,mc);

			
      // static final Symbol g2ClassName = ITEM_;

      FieldRef fr2 =  new FieldRef(ci.getClassName(),
				   "g2Class",
				   symbolClassName,true);
      addSimpleField(ci,staticFinal,fr2,fr);
			

      // static final Symbol[] classInheritancePath 
      // = new Symbol[] {ITEM_, SYSTEM_ITEM_, ROOT_};

      FieldRef fr4 =  new FieldRef(ci.getSuperClassName(),
				   "SYSTEM_ITEM_",
				   symbolClassName,true);
      FieldRef fr5 =  new FieldRef(rootClassName,
				   "ROOT_",
				   symbolClassName,true);
      NewArray na 
	= new NewArray(symbolArrayClassName,new Expression[] {fr, fr4, fr5});
			
      FieldRef fr3 =  new FieldRef(ci.getClassName(),
				   "classInheritancePath",
				   symbolArrayClassName,true);
      addSimpleField(ci,publicStaticFinal,fr3,na);


      // *** Create abstract methods

      ClassRef[] exceptions 
	= new ClassRef[] { new ClassRef("com/gensym/jgi/G2AccessException")};

      addSimpleMethod(ci,
		      publicAbstract,
		      "getRepresentationType",
		      "()Lcom/gensym/util/Symbol;",
		      exceptions);

      addSimpleMethod(ci,
		      publicAbstract,
		      "getItemWidth",
		      "()I",
		      exceptions);

      addSimpleMethod(ci,
		      publicAbstract,
		      "getItemHeight",
		      "()I",
		      exceptions);

      addSimpleMethod(ci,
		      publicAbstract,
		      "getItemXPosition",
		      "()I",		
		      exceptions);

      addSimpleMethod(ci,
		      publicAbstract,
		      "getItemYPosition",
		      "()I",		
		      exceptions);
			
      // ************* Output the bytes to file  *************
      ci.toFile("TestInterface.class",true);

    }
    catch (Exception e) {
      System.out.println("Example failed" + e);
      e.printStackTrace();

    }
  }
}
