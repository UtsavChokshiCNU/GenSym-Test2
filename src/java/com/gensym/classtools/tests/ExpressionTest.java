package com.gensym.classtools.tests;

import com.gensym.classtools.*;
import java.util.*;
import java.io.*;

public class ExpressionTest implements RuntimeConstants {

  public static void main (String[] args) {	
    int typesStart = 0;
    int typesEnd = 7;
    int referencesStart = 0;
    int referencesEnd = 3;
    int arrayReferencesStart = 0;
    int arrayReferencesEnd = 2;
    int valsStart = 0;
    int valsEnd = -1;
    
    if (args != null && (args.length == 8)) {
        typesEnd = Math.min(Integer.parseInt(args[1]),typesEnd);
        typesStart = Math.min(Math.max(Integer.parseInt(args[0]),typesStart),
                                         typesEnd);
        
        referencesEnd = Math.min(Integer.parseInt(args[3]),referencesEnd);
        referencesStart = Math.min(Math.max(Integer.parseInt(args[2]),referencesStart),
                                   referencesEnd);
        arrayReferencesEnd = Math.min(Integer.parseInt(args[5]),arrayReferencesEnd);
        arrayReferencesStart = Math.min(Math.max(Integer.parseInt(args[4]),arrayReferencesStart), 
          arrayReferencesEnd);

        valsStart = Integer.parseInt(args[6]);
        valsEnd = Integer.parseInt(args[7]);
    }
    else System.out.println("usage = java com.gensym.classtools.ExpressionTest <types_start> " +
          "<types_end> <refs_start> <refs_end> <arefs_start> <arefs_end> <vals_start> <vals_end>"); 
    try {	
               
      String className = "com/gensym/classtools/tests/TestExpression";
      // Create a ClassInfo to hold the class being created.  This class is
      // named TestProxy, it has no superior classes and it is public and
      // final.
      ClassInfo ci =  new ClassInfo(new ClassAccess(ACC_PUBLIC |
                                                    ACC_FINAL  |
                                                    ACC_SUPER),
				    className,
                                    true);
      
      // *** Adding an Interface ***
      InterfaceInfo intinf = new InterfaceInfo("com/gensym/classtools/tests/TestExpressionInterface");
      ci.add(intinf);

      // *** Adding Fields ***

      String baseFieldName ="FIELD_";
      String[] fieldTypes = {"I", "J", "S", "D", "B", "Z", "F" };
      Expression[][] vals = { {new Value(0), new Value(1), new Value(-1),
                          new Value(128), new Value(-128), 
                          new Value(129), new Value(-129), 
			        new Value(-70000),
                          new Value(70000)
                        },
			      {new Value((long) 1), new Value((long) 129),
			       new Value((long) 70000)
                        },		
			      {new Value((short) 1), new Value((short) 128),
			       new Value((short) 129)
                        },
			      {new Value(0.0), new Value(1.0), 
			       new Value(100.0),  new Value(700000.0)},
			      {new Value((byte) 1), new Value((byte) -1)},
			      {new Value(true), new Value(false)},
			      {new Value((float) 0.0), new Value((float) 1.0), 
			       new Value((float) 100.0),
			       new Value((float) 70.000)}};

      Access pubaccess = new Access(ACC_PUBLIC);
      Access pubstaticaccess = new Access(ACC_PUBLIC | ACC_STATIC);

      Vector instanceFields = new Vector();
      Vector staticFields = new Vector();
      Vector instanceArrayFields = new Vector();
      Vector staticArrayFields = new Vector();

      Vector localVars = new Vector();
      Vector localArrayVars = new Vector();

			
      //	Fields		
      for (int i = 0; i < fieldTypes.length; i++) {
	String fieldType =fieldTypes[i];
	String arrayType = SIG_ARRAY + fieldType;

	// Create instance field
	FieldRef fr 
	  = new FieldRef(className,baseFieldName + fieldType,fieldType);
	ci.add(new FieldInfo(pubaccess,fr));
	instanceFields.addElement(fr);

	// Create static field
	fr = new FieldRef(className,
			  baseFieldName + fieldType + "_S",fieldType,true);
	ci.add(new FieldInfo(pubstaticaccess,fr));
	staticFields.addElement(fr);

	// Create instance array field
      fr = new FieldRef(className,baseFieldName + "A" + fieldType,arrayType);
	ci.add(new FieldInfo(pubaccess,fr));
	instanceArrayFields.addElement(fr);

	// Create static array field
	fr = new FieldRef(className,
			  baseFieldName + "A" + fieldType + "_S",arrayType,true);
	ci.add(new FieldInfo(pubstaticaccess,
			     fr,new NewArray(arrayType,vals[i])));
	staticArrayFields.addElement(fr);
      }

      // An instance method 

      MethodRef mr 
	= new MethodRef("com/gensym/classtools/tests/TestExpression",
			"test",
			"()V");			

      Block b = new Block();
      // local variable declarations

      String baseLocalVarName = "VAR";

      for (int i = 0; i < fieldTypes.length; i++) {
	String fieldType =fieldTypes[i];
	String arrayType = SIG_ARRAY + fieldType;

	// Create instance local vars
	VariableDeclaration vdecl 
	  = new VariableDeclaration(baseLocalVarName + fieldType,fieldType);
	Variable var = new Variable(baseLocalVarName + fieldType,fieldType);
	b.add(vdecl);
	localVars.addElement(var);

	// Create instance array local vars
	int [] dimensions = new int[] {vals[i].length};
	vdecl = new VariableDeclaration(baseLocalVarName + arrayType,
					arrayType, 
					new NewArray(arrayType,
						     dimensions));
	var = new Variable(baseLocalVarName + arrayType,arrayType);
	b.add(vdecl);
	localArrayVars.addElement(var);
      }

      // generate expressions
      for (int i = typesStart; i < typesEnd; i++) {
  
	Variable var = (Variable) localVars.elementAt(i);
	Variable vara = (Variable) localArrayVars.elementAt(i);
	FieldRef fri = (FieldRef) instanceFields.elementAt(i); 
	FieldRef fria = (FieldRef) instanceArrayFields.elementAt(i);
	FieldRef frs = (FieldRef) staticFields.elementAt(i); 
	FieldRef frsa = (FieldRef) staticArrayFields.elementAt(i); 
	Expression[] references = new Expression[] {var, fri, frs};
	
      int vals_end;
      if (valsEnd == -1)
        vals_end = vals[i].length;
      else
      vals_end = Math.min(Math.max(0, valsEnd), vals[i].length);
      int vals_start = Math.min(Math.max(0, valsStart), vals_end);
      
	for (int j = vals_start; j < vals_end; j++) {
	  Value index = new Value(j);
	  Value v = (Value) vals[i][j];
	  // NB. nees to add instance field array references once instance
	  // field initialization done
	  Expression[] arrayreferences 
	    = new Expression[] {new ArrayRef(vara,index),
				  new ArrayRef(frsa,index)};	
	  for (int k = referencesStart; (k < referencesEnd); k++) {
	    //for (int k = 1; (k < 2); k++) {
	    Expression ref = references[k];
	    Type expressionType = ref.getExpressionType();
	    Type tpe = expressionType;
	    boolean iszero = (v.getExpressionType().isSmallIntegralType() 
			      && v.getIntegerValueIfAny() == 0); 
	    b.add(new OperatorCall("=",new Expression[] {ref,v}));
	    //nesting check on assignment operator
	    b.add(new OperatorCall("=",
				   new Expression[] {ref,
					 new OperatorCall("=",
						  new Expression[] {ref,v})}));
							
	    // don't try to do arithmetic operations on boolean values
	    if (! expressionType.isBooleanType()) { 
            b.add(new OperatorCall("+=",new Expression[] {ref,v}));
	      b.add(new OperatorCall("-=",new Expression[] {ref,v}));
	      b.add(new OperatorCall("*=",new Expression[] {ref,v})); 
	      b.add(new OperatorCall("++",new Expression[] {ref}));
	      b.add(new OperatorCall("--",new Expression[] {ref}));
	      // nesting check on secondary assignment operator
            /*  
            //JAD can't deal with the compile for this. JAD also cannot deal
            //with how javac compiles this
	      b.add(new OperatorCall("+=",
				     new Expression[] {ref,
					  new OperatorCall("+=",
						 new Expression[] {ref,v})}));
            */
                                     
	      // Conditional Expressions
	      b.add(new OperatorCall("=",
			new Expression[] {ref,
			     new OperatorCall("?:",
				   new Expression[] {new OperatorCall("&&",
					 new Expression[] {new Value(true),
						     new Value(true)}),
						       v, 
					    new OperatorCall("-",
                                          new Expression[] {v,
                                                new Value(1)})})}));
	      b.add(new OperatorCall("=",
		       new Expression[] {ref,
                          new OperatorCall("?:",	
			      new Expression[] {new OperatorCall("!",
                                   new Expression[] {new Value(false)}),
  						     v, 
      		                      new OperatorCall("-",
			                    new Expression[] {v,
                                              new Value(1)})})}));
	      b.add(new OperatorCall("=",
		       new Expression[] {ref,
			   new OperatorCall("?:",
			       new Expression[] {new OperatorCall("||",
				    new Expression[] {new Value(true), 
					  new Value(true)}),
						    v, 
				     new OperatorCall("-",
					 new Expression[] {v,
					       new Value(1)})})}));
	      b.add(new OperatorCall("=",
		       new Expression[] {ref,
			   new OperatorCall("?:",
			       new Expression[] {new OperatorCall(">",
				  new Expression[] {ref,v}),
	   					v, 
				 new OperatorCall("-",
				      new Expression[] {v,new Value(1)})})}));
	      b.add(new OperatorCall("=",
				     new Expression[] {ref
				        ,new OperatorCall("?:",
				new Expression[] {new OperatorCall(">=",
				     new Expression[] {ref,v}),
			                  v,
				  new OperatorCall("-",
				      new Expression[] {v,new Value(1)})})}));
	      b.add(new OperatorCall("=",
				     new Expression[] {ref,
				       new OperatorCall("?:",
				     new Expression[] {new OperatorCall("<",
					 new Expression[] {ref,v}),
					    	v,
			       new OperatorCall("-",
				    new Expression[] {v,new Value(1)})})}));
	      b.add(new OperatorCall("=",
		      new Expression[] {ref,
			   new OperatorCall("?:",
				new Expression[] {new OperatorCall("<=",
				    new Expression[] {ref,v}),
				   v,
			new OperatorCall("-",
			    new Expression[] {v,new Value(1)})})}));


	      // Equality Operator
						
	      b.add(new OperatorCall("=",
		      new Expression[] {ref,
			   new OperatorCall("?:",
				new Expression[] {new OperatorCall("==",
				       new Expression[] {ref,v}),
						      v,
				   new OperatorCall("-",
				     new Expression[] {v,
					    new Value(1)})})}));

	      // Inequality Operator
							
	      b.add(new OperatorCall("=",
		       new Expression[] {ref,new OperatorCall("?:",
			      new Expression[] {new OperatorCall("!=",
					 new Expression[] {ref,v}),
						  v,
				   new OperatorCall("-",
					new Expression[] {v,
						    new Value(1)})})}));
				
	      // division by zero check
	      if (! iszero) {
		b.add(new OperatorCall("/=",new Expression[] {ref,v}));
		b.add(new OperatorCall("%=",new Expression[] {ref,v}));
	      }

	      // test operation as RHS to assignment
	      // Need to cast byte, char, and short results because 
	      // of numeric promotion	
	      if (expressionType.isSmallIntegralType() 
		  & (! expressionType.isIntegerType())) {
		// Unary + and -
		b.add(new OperatorCall("=",
		         new Expression[] {ref,
			     new Cast(tpe,
				  new OperatorCall("-",
					  new Expression[] {ref}))}));
		b.add(new OperatorCall("=",
			 new Expression[] {ref,
			       new Cast(tpe,
                                   new OperatorCall("+",
                                          new Expression[] {ref}))}));
		b.add(new OperatorCall("=",
			  new Expression[] {ref,
			       new Cast(tpe,
				    new OperatorCall("+",
					  new Expression[] {ref,v}))}));
		b.add(new OperatorCall("=",
			  new Expression[] {ref,
			       new Cast(tpe,
				     new OperatorCall("-",
					  new Expression[] {ref,v}))}));
		b.add(new OperatorCall("=",
			   new Expression[] {ref,
			        new Cast(tpe,new OperatorCall("*",
				      new Expression[] {ref,v}))}));	
		if (! iszero) {
		  b.add(new OperatorCall("=",
			   new Expression[] {ref,
				new Cast(tpe,
					new OperatorCall("/",
					      new Expression[] {ref,v}))}));
		  b.add(new OperatorCall("=",
			   new Expression[] {ref,
				new Cast(tpe,
					new OperatorCall("%",
					       new Expression[] {ref,v}))}));
		}	
	      }
	      else {
		b.add(new OperatorCall("=",
			  new Expression[] {ref,
                               new OperatorCall("+",
				     new Expression[] {ref,v})}));
		b.add(new OperatorCall("=",
			   new Expression[] {ref,
				new OperatorCall("-",
				      new Expression[] {ref,v})}));
		b.add(new OperatorCall("=",
			   new Expression[] {ref,
				 new OperatorCall("*",
				      new Expression[] {ref,v})}));	
		b.add(new OperatorCall("=",
			    new Expression[] {ref,
				  new OperatorCall("-",
				       new Expression[] {ref})}));
		// Unary + and -
		b.add(new OperatorCall("=",
			     new Expression[] {ref,
				  new OperatorCall("+",
					new Expression[] {ref})}));

		if (! iszero) {
		  b.add(new OperatorCall("=",
			     new Expression[] {ref,
				   new OperatorCall("/",
					 new Expression[] {ref,v})}));
		  b.add(new OperatorCall("=",
			     new Expression[] {ref,
				   new OperatorCall("%",
					 new Expression[] {ref,v})}));
		}
	      }
	    }
						
	    // Test Bitwise Operators, Integral Types only
	    if (expressionType.isIntegralType()) { 	  	
	      b.add(new OperatorCall("&=",new Expression[] {ref,v}));
	      b.add(new OperatorCall("|=",new Expression[] {ref,v}));
	      b.add(new OperatorCall("^=",new Expression[] {ref,v}));
	      if (! expressionType.isBooleanType()) {
		b.add(new OperatorCall(">>=",new Expression[] {ref,v}));
		b.add(new OperatorCall(">>>=",new Expression[] {ref,v}));
		b.add(new OperatorCall("<<=",new Expression[] {ref,v}));
		// Need to cast byte, char, and short results because of
		// numeric promotion	
		if (expressionType.isSmallIntegralType() 
		    & (! expressionType.isIntegerType())) {
		  b.add(new OperatorCall("=",new Expression [] {ref,new Cast(expressionType,new OperatorCall("&",new Expression[] {ref,v}))}));
		  b.add(new OperatorCall("=",new Expression [] {ref,new Cast(expressionType,new OperatorCall("|",new Expression[] {ref,v}))}));
		  b.add(new OperatorCall("=",new Expression [] {ref,new Cast(expressionType,new OperatorCall("^",new Expression[] {ref,v}))}));
		  b.add(new OperatorCall("=",new Expression [] {ref,new Cast(expressionType,new OperatorCall(">>",new Expression[] {ref,v}))}));
		  b.add(new OperatorCall("=",new Expression [] {ref,new Cast(expressionType,new OperatorCall("<<",new Expression[] {ref,v}))}));
		  b.add(new OperatorCall("=",new Expression [] {ref,new Cast(expressionType,new OperatorCall(">>>",new Expression[] {ref,v}))}));
		  b.add(new OperatorCall("=",new Expression [] {ref,new Cast(expressionType,new OperatorCall("~",new Expression[] {ref}))}));
		}
		else {
		  b.add(new OperatorCall("=",new Expression [] {ref,new OperatorCall("&",new Expression[] {ref,v})}));
		  b.add(new OperatorCall("=",new Expression [] {ref,new OperatorCall("|",new Expression[] {ref,v})}));
		  b.add(new OperatorCall("=",new Expression [] {ref,new OperatorCall("^",new Expression[] {ref,v})}));
		  b.add(new OperatorCall("=",new Expression [] {ref,new OperatorCall(">>",new Expression[] {ref,v})}));
		  b.add(new OperatorCall("=",new Expression [] {ref,new OperatorCall("<<",new Expression[] {ref,v})}));
		  b.add(new OperatorCall("=",new Expression [] {ref,new OperatorCall(">>>",new Expression[] {ref,v})}));
		  b.add(new OperatorCall("=",new Expression [] {ref,new OperatorCall("~",new Expression[] {ref})}));
		}
	      }
	    }
	  }
	  for (int k = arrayReferencesStart; k < arrayReferencesEnd; k++) {
	    //for (int k = 0; k < 1; k++) {
	    Expression ref = arrayreferences[k];
	    b.add(new OperatorCall("=",new Expression[] {ref,v}));
	    b.add(new OperatorCall("=",
				   new Expression[] {ref,
					 new OperatorCall("=",
						new Expression[] {ref,v})}));
	    if (ref.getExpressionType().isNumericType()) {	
	      b.add(new OperatorCall("+=",new Expression[] {ref,v}));
	      b.add(new OperatorCall("-=",new Expression[] {ref,v}));
	      b.add(new OperatorCall("*=",new Expression[] {ref,v}));
	      b.add(new OperatorCall("+=",
				     new Expression[] {ref,
					  new OperatorCall("+=",
						new Expression[] {ref,v})}));
	      // division by zero check
	      if (!(v.getExpressionType().isSmallIntegralType() 
		    && v.getIntegerValueIfAny() == 0)) {
		b.add(new OperatorCall("/=",new Expression[] {ref,v}));
		b.add(new OperatorCall("%=",new Expression[] {ref,v}));
	      }
	    }
	  }
	}	
      }
				

      // Tests for String addition.
      b.add(new VariableDeclaration("mystring","Ljava/lang/String;"));
      Variable myref = new Variable("mystring","Ljava/lang/String;");
      b.add(new OperatorCall("=",
		new Expression[] {myref,
		       new OperatorCall("+",
			       new Expression[] {new Value("foo"),
				    new OperatorCall("+",
					 new Expression[] {new Value("middle"),
							new Value("middle2")}),
						  new Value("baz")})}));
      b.add(new OperatorCall("+=",
			     new Expression[] {myref,new Value("foo")}));
			
      b.add(new Return());

      MethodInfo mi = new MethodInfo(pubaccess,
				     mr,
				     null,
				     b);
      ci.add(mi);

      // ************* Output the bytes to file  *************
      FileOutputStream fileOutStream = new FileOutputStream("TestExpression.class");
      fileOutStream.write(ci.getBytes(true));
      fileOutStream.close();
			

      //************** Load the new class into this VM ************
      Class cl = Class.forName("com.gensym.classtools.tests.TestExpression");
      System.out.println("Loaded the " + cl);
      TestExpressionInterface a = (TestExpressionInterface) cl.newInstance();
      System.out.println("New instance created " + a);
      a.test();

    }
    catch (Exception e) {
      System.out.println("Failure " + e);
      e.printStackTrace();
    }
  }
}
