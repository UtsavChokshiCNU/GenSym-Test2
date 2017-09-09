package com.gensym.dispatcher;

public class NoSuchVariableException extends Exception
{
  public NoSuchVariableException(String variableName)
  {
    super(variableName);
  }
  
}
