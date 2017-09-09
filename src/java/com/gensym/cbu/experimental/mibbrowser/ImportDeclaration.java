package com.gensym.cbu.experimental.mibbrowser;

import java.util.*;

public class ImportDeclaration implements MibFileObjectTableObject
{
  public String mibName;
  public Vector objectNames;
  
  //MibFileObject Interface
  @Override
  public int getRowCount()
    {
      return 2;
    }

  @Override
  public String getAttribute(int row)
    {
      switch (row) {
      case 0: return "Name";
      case 1: return "Object Names";
      default: return "?";
      }
    }

    @Override
    public String getValue(int row)
    {
      switch (row) {
      case 0: return mibName;
      case 1: {
	String s = new String();
	for (Enumeration e = objectNames.elements(); e.hasMoreElements();)
	  s += e.nextElement() + " ";
	return s;
      }
      default: return "?";
      }
    }
    //end MibFileObject Interface
  
  public ImportDeclaration (String s, Vector v)
    {
      mibName = s;
      objectNames = v;
    }

  @Override
  public String toString()
    {
      String s = new String();
      for (Enumeration e = objectNames.elements(); e.hasMoreElements(); ) {
	s += e.nextElement() + " ";
      }
      s += "from " + mibName;
      return s;
    }
}
