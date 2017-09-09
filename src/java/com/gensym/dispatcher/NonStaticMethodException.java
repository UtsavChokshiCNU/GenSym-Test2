package com.gensym.dispatcher;

import java.lang.reflect.Method;

public class NonStaticMethodException extends Exception
{
  NonStaticMethodException(Method method) {
    super(method.toString());
  }
}
