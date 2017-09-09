package com.gensym.cbu.experimental.mibbrowser;

import java.awt.*;
import java.io.*;
import java.util.*;
import javax.swing.*;

public class MibDataType implements MibFileObjectTableObject
{
  String name = new String();
  String value = new String();

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
      case 1: return "Value";
      default: return "?";
      }
    }

    @Override
    public String getValue(int row)
    {
      switch (row) {
      case 0: return name;
      case 1: return value;
      default: return "?";
      }
    }
    //end MibFileObject Interface


  @Override
  public String toString()
    {
      return name;
    }

  public MibDataType (String name)
    {
      setName(name);
    }

  public void load(MibFileReader reader) throws IOException, KeywordNotFoundException
    {
      String[] keywords = {"}"};

      String entry = reader.readToFirst(keywords, true);

      entry = entry.replace(',', ' ');
      entry = entry.replace('{', ' ');
      entry = entry.replace('}', ' ');

      StringTokenizer st;
      st = new StringTokenizer(entry);
      while(st.hasMoreTokens()) {
	    value += st.nextToken();
	  }
    }

  public void setName(String s)
    {
      name = s;
    }

  public String getName()
    {
      return name;
    }
}
