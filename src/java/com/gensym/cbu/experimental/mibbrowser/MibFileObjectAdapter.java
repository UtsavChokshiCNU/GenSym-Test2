package com.gensym.cbu.experimental.mibbrowser;

public class MibFileObjectAdapter implements MibFileObject
{

  String symbolicName = new String("symbolic name");
  String numericName = new String("numeric name");;
  String fullSymbolicName = null;
  String fullNumericName = null;
  String description = new String("description");
  String parentSymbolicName = null;
  
  @Override
  public String toString()
    {
      String s = "symbolicName = " + symbolicName  + "\n";
      s += "numericName = " + numericName + "\n";
      if (parentSymbolicName == null)
	s += "parentSymbolicName = null\n";
      else 
	s += "parentSymbolicName = " + parentSymbolicName + "\n";
      if (fullSymbolicName == null)
	s += "fullSymbolicName = null\n";
      else
	s += "fullSymbolicName = " + fullSymbolicName + "\n";
      if (fullNumericName == null)
	s += "fullNumericName = null\n";
      else
	s += "fullNumericName = " + fullNumericName + "\n";
      return s;
    }

  @Override
  public String getSymbolicName()
    {
      return symbolicName;
    }

  @Override
  public void setSymbolicName(String name)
    {
      symbolicName = name;
    }
  
  @Override
  public String getNumericName()
    {
      return numericName;
    }

  @Override
  public void setNumericName(String name)
    {
      numericName = name;
    }
  
  @Override
  public String getFullSymbolicName()
    {
      return fullSymbolicName;
    }
  
  @Override
  public void setFullSymbolicName(String name)
    {
      fullSymbolicName = name;
    }
  
  @Override
  public String getFullNumericName()
    {
      return fullNumericName;
    }
  
  @Override
  public void setFullNumericName(String name)
    {
      fullNumericName = name;
    }

  @Override
  public String getDescription()
    {
      return description;
    }

  @Override
  public String getParentSymbolicName()
    {
      return parentSymbolicName;
    }

  @Override
  public void setParentSymbolicName(String name)
    {
      parentSymbolicName = name;
    }
  
}
