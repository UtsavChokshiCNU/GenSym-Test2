package com.gensym.classtools.examples.EmitNativeStubs;

import java.io.FileOutputStream;
import java.io.IOException;
import com.gensym.classtools.*;

public class EmitNativeStubs implements RuntimeConstants {
  private ClassInfo c;
	
  public EmitNativeStubs(ClassAccess acc, String className)
       throws ClassException{	
    c = new ClassInfo(acc,className,true);		
  }

  public void addNativeMethod(String methodName, String descriptor)
       throws ClassException {
    MethodRef mr = new MethodRef(c.getClassName(),
				 methodName,
				 descriptor);
    MethodInfo mi = new MethodInfo(new Access(ACC_PUBLIC | ACC_NATIVE),mr);
    c.add(mi);
  }

  public void toFile(String filename) throws IOException {
    c.toFile(filename,true);	
  }

  /* Example use of this class to emit the following:
   *
   * public class WindowManager {
   *
   * public native int createWindow(String windowName, 
   *                                double xsize, double ysize);
   *
   * public native boolean destroyWindow(int handle);
   *
   * public native void minimizeWindow(int handle);
   *
   * public native void maximizeWindow(int handle);
   * }
   */
  public static void main(String[] args) {
    try {
      EmitNativeStubs ens = new EmitNativeStubs(new ClassAccess(ACC_PUBLIC), 
						"WindowManager");
      ens.addNativeMethod("createWindow","(SDD)I");
      ens.addNativeMethod("destroyWindow","(I)Z");
      ens.addNativeMethod("minimizeWindow","(I)V");
      ens.addNativeMethod("maximizeWindow","(I)V");
      ens.toFile("WindowManager.class");
      ClassInfo.main(new String[] {"report", "WindowManager.class"});
    }
    catch (Exception e) {
      System.out.println("EmitNativeStubs failed: " + e);
      e.printStackTrace();
    }
  }

}
