package com.gensym.rules;

import java.io.*;

public class DefaultRuleClassManager extends Object
  implements RuleClassManager
{
  public static final String ruleAdapterRepository = "\\hax\\com\\gensym\\g2scriptruntime\\adapters";

  @Override
  public Class findAdapterClass(String string)
       throws ClassNotFoundException
  {
    return Class.forName(string);
  }

  @Override
  public Class findInstanceClass(String string)
       throws ClassNotFoundException
  {
    return Class.forName(string);
  }

  @Override
  public String getAdapterPackageName()
  {
    return "com.gensym.g2scriptruntime.adapters";
  }

  @Override
  public void storeAdapterClass(String unqualifiedClassName, byte[] bytes)
       throws java.io.IOException
  {
    String fileName = ruleAdapterRepository + java.io.File.separator + 
      unqualifiedClassName + ".class";
    FileOutputStream fileOutStream = new FileOutputStream(fileName);
    fileOutStream.write(bytes);
    fileOutStream.close();
  }
}
