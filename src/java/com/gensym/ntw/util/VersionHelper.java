package com.gensym.ntw.util;

import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import com.gensym.classes.KbWorkspace;
import com.gensym.message.Trace;
import com.gensym.util.UnexpectedException;
import com.gensym.wksp.WorkspaceView;
import javax.swing.JSplitPane;

public class VersionHelper{

  private static final String SCALABLE_WORKSPACE_VIEW_NAME = "com.gensym.wksp.ScalableWorkspaceView";

  private static Boolean usingJava2D;

  public static boolean isUsingJava2D(Class clazz){
    if (usingJava2D == null){
      usingJava2D = Boolean.FALSE;
      try{
	ClassLoader cl = clazz.getClassLoader();
	if (cl == null)
	  Class.forName("java.awt.Graphics2D");
	else
	  cl.loadClass("java.awt.Graphics2D");
	usingJava2D = Boolean.TRUE;
      }
      catch(ClassNotFoundException ex){
	//Trace.exception(ex);
      }
    }

    return usingJava2D.booleanValue();
  }

  public static WorkspaceView createScalableWorkspaceView(Object requestor, KbWorkspace wksp){
    return (WorkspaceView)createInstanceFromConstructor(requestor, SCALABLE_WORKSPACE_VIEW_NAME, 
							new Class[]{com.gensym.classes.KbWorkspace.class}, 
							new Object[] {wksp});
  }

  private static Object createInstanceFromConstructor(Object requestor, String className, 
						      Class[] argTypes, Object[] args) {
    try{
      Constructor constructor = getConstructorForClass(requestor, className, argTypes);
      return constructor.newInstance(args);
    }
    catch(ClassNotFoundException ex){
      throw new UnexpectedException(ex);
    }
    catch(NoSuchMethodException ex){
      throw new UnexpectedException(ex);
    }
    catch(InstantiationException ex){
      throw new UnexpectedException(ex);
    }
    catch(IllegalAccessException ex){
      throw new UnexpectedException(ex);
    }
    catch(IllegalArgumentException ex){
      throw new UnexpectedException(ex);
    }
    catch(InvocationTargetException ex){
      Trace.exception(ex);
      throw new UnexpectedException(ex.getTargetException());
    }
  }

  private static Constructor getConstructorForClass(Object requestor, String className, 
						    Class[] args) throws ClassNotFoundException, 
                                                                         NoSuchMethodException{
    ClassLoader cl = requestor.getClass().getClassLoader();
    if (cl == null)
      return Class.forName(className).getConstructor(args);
    else
      return cl.loadClass(className).getConstructor(args);
  }

  private static Class scalableWkspViewClass;

  public static boolean isInstanceOfScalableWorkspaceView(WorkspaceView view){
    if (isUsingJava2D(view.getClass())){
      initializeScalableWkspViewClass(view);
      return (scalableWkspViewClass.isInstance(view));
    }
    return false;
  }

  private static void initializeScalableWkspViewClass(Object requestor){
    if (scalableWkspViewClass != null) return;
    ClassLoader cl = requestor.getClass().getClassLoader();
    try{
      if (cl == null)
	scalableWkspViewClass = Class.forName(SCALABLE_WORKSPACE_VIEW_NAME);
      else
	scalableWkspViewClass = cl.loadClass(SCALABLE_WORKSPACE_VIEW_NAME);
    }
    catch(ClassNotFoundException ex){
      throw new UnexpectedException(ex);
    }
  }

  private static final Class[] setScaleArgTypes = new Class[]{Double.TYPE, Double.TYPE};
  
  public static void setScale(WorkspaceView view, double sx, double sy){
    if (isInstanceOfScalableWorkspaceView(view))
      invokeMethod(view, "setScale", setScaleArgTypes, new Object[]{new Double(sx), new Double(sy)});
  }

  private static final Class[] setResizeWeightArgTypes = new Class[]{Double.TYPE};  

  private static Object invokeMethodNoExceptions(Object object, 
						 String methodName, 
						 Class[] argTypes, 
						 Object[] args){
    try{
      Method method = object.getClass().getMethod(methodName, argTypes);
      return method.invoke(object, args);
    }
    catch(NoSuchMethodException ex){
      throw new UnexpectedException(ex);
    }
    catch(IllegalAccessException ex){
      throw new UnexpectedException(ex);
    }
    catch(IllegalArgumentException ex){
      throw new UnexpectedException(ex);
    }
    catch(InvocationTargetException ex){
      throw new UnexpectedException(ex);
    }
  }
  
  public static boolean setResizeWeight(JSplitPane splitPane, double weight) {
  try{
      Method method = splitPane.getClass().getMethod("setResizeWeight", setResizeWeightArgTypes);
      method.invoke(splitPane, new Object[]{new Double(weight)});
      return true;
    }
    catch(NoSuchMethodException ex){
    }
    catch(IllegalAccessException ex){
    }
    catch(IllegalArgumentException ex){
    }
    catch(InvocationTargetException ex){
    }
    return false;
  }  

  public static double getScaleX(WorkspaceView view){
    if (isInstanceOfScalableWorkspaceView(view)){
      Double sx = (Double)invokeMethod(view, "getScaleX", new Class[0], new Object[0]);
      return sx.doubleValue();
    }
    else
      throw new IllegalArgumentException("view is not an instance of ScalableWorkspaceView");
  }

  public static double getScaleY(WorkspaceView view){
    if (isInstanceOfScalableWorkspaceView(view)){
      Double sy = (Double)invokeMethod(view, "getScaleY", new Class[0], new Object[0]);
      return sy.doubleValue();
    }
    else
      throw new IllegalArgumentException("view is not an instance of ScalableWorkspaceView");
  }

  private static final Class[] scaledToFitArgs = new Class[]{Boolean.TYPE};

  public static void setScaledToFit(WorkspaceView view, boolean scaledToFit){
    if (isInstanceOfScalableWorkspaceView(view))
      invokeMethod(view, "setScaledToFit", scaledToFitArgs, new Object[]{new Boolean(scaledToFit)});
  }

  public static boolean isScaledToFit(WorkspaceView view){
    if (isInstanceOfScalableWorkspaceView(view)){
      Boolean scaled = (Boolean)invokeMethod(view, "isScaledToFit", new Class[0], new Object[0]);
      return scaled.booleanValue();
    }
    else
      throw new IllegalArgumentException("view is not an instance of ScalableWorkspaceView");
  }

  private static Object invokeMethod(Object object, String methodName, Class[] argTypes, 
				   Object[] args){
    try{
      Method method = object.getClass().getMethod(methodName, argTypes);
      return method.invoke(object, args);
    }
    catch(NoSuchMethodException ex){
      throw new UnexpectedException(ex);
    }
    catch(IllegalAccessException ex){
      throw new UnexpectedException(ex);
    }
    catch(IllegalArgumentException ex){
      throw new UnexpectedException(ex);
    }
    catch(InvocationTargetException ex){
      throw new UnexpectedException(ex);
    }
  }
    
}
  
