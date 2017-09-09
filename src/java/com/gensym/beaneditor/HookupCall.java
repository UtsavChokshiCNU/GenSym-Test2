package com.gensym.beaneditor;

import java.awt.Frame;
import java.lang.reflect.*;
import java.beans.MethodDescriptor;
import java.beans.ParameterDescriptor;
import com.gensym.classtools.Expression;
import com.gensym.classtools.ClassInfo;

public class HookupCall
{

  Method method;
  HookupArgument[] arguments;
  Wrapper sourceWrapper;
  Wrapper targetWrapper;

  HookupCall(Method method, MethodDescriptor methodDescriptor,
	     Wrapper sourceWrapper, Wrapper targetWrapper)
  {
    this.method = method;
    this.sourceWrapper = sourceWrapper;
    this.targetWrapper = targetWrapper;
    Class[] parameterTypes = method.getParameterTypes();
    ParameterDescriptor[] parameterDescriptors 
      = ((methodDescriptor != null) ?
	 methodDescriptor.getParameterDescriptors():
	 null);
    int i,len = parameterTypes.length;
    arguments = new HookupArgument[len];
    for (i=0; i<len; i++)
      {
	String argumentName 
	  = ((parameterDescriptors != null) ?
	     parameterDescriptors[i].getName() :
	     makeArgumentName(parameterTypes[i],i));
	arguments[i] 
	  = new HookupArgument(argumentName, parameterTypes[i]);
      }
  }

  String makeArgumentName(Class c, int index)
  {
    String name = c.getName();
    int lastIndex = name.lastIndexOf('.');
    if (lastIndex == -1)
      lastIndex = 0;
    else
      lastIndex++;
    return name.substring(lastIndex)+"Arg"+index;
  }

  Expression generateArgumentCode(ClassInfo classInfo, int index, 
				  Class eventType, String eventObjectArgumentName)
  {
    return arguments[index].generateCode(this,classInfo,
					 eventType,eventObjectArgumentName);
  }

  void setupLegacyArguments()
  {
    int i,len = arguments.length;
    for (i=0; i<len; i++)
      {
	arguments[i].valueType = HookupArgument.OBJECT_ITSELF;
	arguments[i].objectName = "event";
      }
  }

  HookupArgument[] setupArguments(Frame frame, Class eventType){
    ArgumentMatcher matcher = new ArgumentMatcher(frame, this, eventType);
    HookupArgument[] args = matcher.matchArguments();
    return args;
  }

  @Override
  public String toString(){
    String args = "";
    if (arguments != null)
      for (int i=0; i<arguments.length; i++)
	args = args + "\n" + arguments[i];
    return getClass().getName() + "(" + method +" "+ args +" "+ sourceWrapper +" "+ targetWrapper +")";
  }
}
