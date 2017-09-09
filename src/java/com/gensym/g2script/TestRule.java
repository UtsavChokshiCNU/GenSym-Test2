package com.gensym.g2script;

import antlr.*;
import antlr.CommonAST;
import antlr.collections.AST;
import antlr.DumpASTVisitor;
import com.gensym.types.G2Token;
import com.gensym.types.G2TokenReader;
import com.gensym.classtools.*;
import com.gensym.g2scriptruntime.*;
import com.gensym.rules.Rule;
import java.io.*;

public class TestRule
{
  
  public static void main(String[] args) {
    try {
      // Parse the input expression
      String sourceFileName = args[0].substring(0,args[0].indexOf('.'));
      String simpleClassName = ((args.length < 2) ? 
				sourceFileName+"RuleInstance" : 
				args[1]);
      String className = "com.gensym.g2script."+simpleClassName;
      Compiler compiler = new Compiler();
      // Put the method in a Class
      ClassAccess access 
	= new ClassAccess(RuntimeConstants.ACC_PUBLIC);
      ClassInfo classInfo = new ClassInfo(access,
					  className,
					  "com/gensym/g2scriptruntime/RuleInstance",
					  true);
      Rule rule = compiler.compileRule(new FileReader(args[0]),
				       classInfo,
				       true);
      
      // Show the world our nice new class
      classInfo.emit();
      byte[] classData = classInfo.getBytes();
      classInfo.toStdout();
      String classFileName = simpleClassName+".class";
      System.out.println("emitted class "+classFileName+
			 " is "+classData.length+" bytes.");
      classInfo.toFile(classFileName,false);

      String serializedRuleFileName;
      if (args.length > 2)
	serializedRuleFileName = args[2];
      else 
	serializedRuleFileName = sourceFileName+".ser";
	  
      FileOutputStream fos = new FileOutputStream(serializedRuleFileName);
      ObjectOutputStream oos = new ObjectOutputStream(fos);
      oos.writeObject(rule);
      oos.close();
      
    } catch(Exception e) 
      {
	System.err.println("exception: "+e);
	System.err.println("  MSG:"+e.getMessage());
	e.printStackTrace();
      }
  }
}
