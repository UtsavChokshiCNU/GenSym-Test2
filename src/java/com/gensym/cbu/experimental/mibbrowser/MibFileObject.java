package com.gensym.cbu.experimental.mibbrowser;

public interface MibFileObject
{
  public String getSymbolicName();
  public void setSymbolicName(String name);
  public String getNumericName();
  public void setNumericName(String name);
  public String getFullSymbolicName();
  public void setFullSymbolicName(String name);
  public String getFullNumericName();
  public void setFullNumericName(String name);
  public String getDescription();
  public String getParentSymbolicName();
  public void setParentSymbolicName(String name);
}
