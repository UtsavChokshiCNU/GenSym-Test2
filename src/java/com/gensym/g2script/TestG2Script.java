package com.gensym.g2script;

import antlr.*;
import antlr.CommonAST;
import antlr.collections.AST;
import antlr.DumpASTVisitor;
import com.gensym.types.G2Token;
import com.gensym.types.G2TokenReader;
import com.gensym.classtools.*;
import java.io.FileReader;
import java.io.File;
import java.io.BufferedReader;

// 1 floppy disks for backup / or networking portable - ONGOING
// 5 add real G2 grammar
//     actions create/delete/inform (delete is meaningless in this context)
//     expressions (aa exists, aa does not exist , i.e. aa == NULL)
//     for/repeat
// 8 resurrect real(?) compiler work.
// 9 java type browser as editor support
// re-arrange bean editor 
//   (preference objects) Mostly done
//   (easy storage/over-riding of G2 class dialogs - late work)
//   (save modes, bean, launchable-dialog, javascript/html, etc)


public class TestG2Script
{
  
  public static void main(String[] args) {
    try {
      // Parse the input expression
      String simpleClassName = (args.length < 2) ? "TestClass" : args[1];
      String className 
	= (args.length < 3 ? "com.gensym.g2script" : args[2])+"."+
	simpleClassName;
      Compiler compiler = new Compiler();
      // Put the method in a Class
      ClassAccess access 
	= new ClassAccess(RuntimeConstants.ACC_PUBLIC);
      ClassInfo classInfo = new ClassInfo(access,
				  className,
				  "java/lang/Object",
				  true);
      MethodInfo methodInfo 
	= compiler.compileMethod(new FileReader(args[0]),
				 classInfo,
				 true);
      classInfo.add(methodInfo);
      classInfo.add(new SourceFileAttribute(args[0]));
      // Show the world our nice new class
      classInfo.emit();
      byte[] classData = classInfo.getBytes();
      classInfo.toStdout();
      String classFileName = simpleClassName+".class";
      System.out.println("emitted class "+classFileName+
			 " is "+classData.length+" bytes.");
      classInfo.toFile(classFileName,false);

    } catch(Exception e) 
      {
	System.err.println("exception: "+e);
	System.err.println("  MSG:"+e.getMessage());
	e.printStackTrace();
      }
  }
}
