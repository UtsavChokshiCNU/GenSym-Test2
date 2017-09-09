package com.gensym.cbu.experimental.mibbrowser;

import java.io.*;
import java.util.*;
import javax.swing.*;

public class ObjectIdentifier extends MibFileObjectAdapter implements MibFileObjectTableObject
{
  String oidParentName = new String();

    //MibFileObject Interface
  @Override
  public int getRowCount()
    {
      return 5;
    }

  @Override
  public String getAttribute(int row)
    {
      switch (row) {
      case 0: return "SymbolicName";
      case 1: return "NumericName";
      case 2: return "ParentName";
      case 3: return "FSN";
      case 4: return "FNN";
      default: return "?";
      }
    }

    @Override
    public String getValue(int row)
    {
      switch (row) {
      case 0: return symbolicName;
      case 1: return numericName;
      case 2: return oidParentName;
      case 3: if(fullSymbolicName == null) return ""; else return fullSymbolicName;
      case 4: if(fullNumericName == null) return ""; else return fullNumericName;
      default: return "?";
      }
    }
    //end MibFileObject Interface

  @Override
  public String toString()
    {
      return symbolicName;
    }

  public ObjectIdentifier (String name)
    {
      symbolicName = name;
    }

  public void setOidParentName (String s)
    {
       oidParentName = s;
    }

  public String getOidParentName()
    {
      return oidParentName;
    }
}
