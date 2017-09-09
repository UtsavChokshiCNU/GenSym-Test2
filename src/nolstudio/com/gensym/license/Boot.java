package com.gensym.license;

import com.gensym.license.ClsLoader;
import java.lang.reflect.*;

public class Boot {
	
	public static void main(String[] args) throws IllegalAccessException {
		Method mainMethod = null;
		try {
			if(args.length < 1) {
				System.err.println("The qualified name of main class required as an argument.  Exiting!");
				System.exit(1);
			}
			String mainClassName = args[0];
			ClsLoader loader = null;  // this and exception handling below added by Brian O. Bush, Feb 17, 1999
			try {
				loader = new ClsLoader(mainClassName);
			} catch (java.lang.UnsatisfiedLinkError e) { 
				System.err.println("ERROR: Path not set properly to include <Nolstudio home>\\bin"); 
				System.exit(1);
			}
			Class mainClass = loader.loadClass(mainClassName);
			mainMethod = mainClass.getDeclaredMethod("main",new Class[] { args.getClass() });
		}
		catch (Exception e) {
			System.err.println("ERROR: " + e.getMessage());
			e.printStackTrace();
			System.exit(1);
		}

		String[] mainArgs = new String[args.length-1];
		for(int i=0;i<args.length-1;i++)
			mainArgs[i] = args[i+1];

		if (mainMethod != null) 
			try {
				mainMethod.invoke(null , new Object[] { mainArgs });
			} catch (InvocationTargetException e) {
				Throwable t = e.getTargetException();
				System.err.println("ERROR: " + t.getMessage());
				t.printStackTrace();
				System.exit(1);
			}
		else {
			System.err.println("ERROR: no main method in "+args[0]);
			System.exit(1);
		}
	}
}

		
