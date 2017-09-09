package com.gensym.rules;

public interface RuleClassManager
{
  public Class findInstanceClass(String string)
       throws ClassNotFoundException;

  public Class findAdapterClass(String string)
       throws ClassNotFoundException;

  public String getAdapterPackageName();

  public void storeAdapterClass(String unqualifiedClassName, byte[] bytes)
       throws java.io.IOException;
}
