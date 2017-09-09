package com.gensym.newclasstools.tests;

import com.gensym.denali.eval.RuntimeEnvironment;
import com.gensym.denali.eval.CompileEnvironment;
import com.gensym.denali.eval.CompilerException;
import com.gensym.denali.model.JavaExpression;
import com.gensym.denali.model.JavaStatement;
import com.gensym.denali.model.CompiledJavaExpression;
import com.gensym.denali.model.BoundJavaExpression;
import com.gensym.core.GensymApplication;

import java.util.*;
import java.io.*;

public class TestJavaExpression
{
  public static void main(String[] args) {
    try {
      GensymApplication.initialize(new String[]{});
      JavaExpression jexp;
      TestEnvironment myenv = new TestEnvironment();
      for (int i = 0; i < args.length; i++) {
	String arg = args[i];
	System.out.println("Evaluating <" + arg + ">");
	if (arg.charAt(0) == '{')
	  jexp = new JavaStatement(arg);
	else
	  jexp = new JavaExpression(arg);
	System.out.println("Java Expression created");
	jexp.resolve(myenv, myenv);
	System.out.println("Java Expression resolved");
	Object result = jexp.evaluate(myenv);
	System.out.println("Java Expression evaluated");
	System.out.println("Result of evaluation is " + result);
      }
    } catch (Exception e) {
	e.printStackTrace();
    }
  }

}
