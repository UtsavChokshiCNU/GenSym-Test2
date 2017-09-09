package com.gensym.cbu.experimental.mibbrowser;

import java.io.*;
import java.util.*;
import javax.swing.*;

public class ObjectType extends MibFileObjectAdapter implements MibFileObjectTableObject
{
  String syntax = new String();

  //MibFileObject Interface
  @Override
  public int getRowCount()
    {
      return 6;
    }

  @Override
  public String getAttribute(int row)
    {
      switch (row) {
      case 0: return "Symbolic Name";
      case 1: return "Numeric Name";
      case 2: return "Description";
      case 3: return "ParentSymbolicName";
      case 4: return "FSN";
      case 5: return "FNN";
      default: return "?";
      }
    }

    @Override
    public String getValue(int row)
    {
      switch (row) {
      case 0: return symbolicName;
      case 1: return numericName;
      case 2: return description;
      case 3: if(parentSymbolicName == null) return ""; else return parentSymbolicName;
      case 4: if(fullSymbolicName == null) return ""; else return fullSymbolicName;
      case 5: if(fullNumericName == null) return ""; else return fullNumericName;
      default: return "?";
      }
    }
    //end MibFileObject Interface

  @Override
  public String toString()
    {
      return symbolicName;
    }

  public ObjectType (String name)
    {
      symbolicName = name;
    }

  public void load(MibFileReader reader) throws IOException, KeywordNotFoundException
    {
      String[] keywords = {"SYNTAX",
			   "MAX-ACCESS",
			   "ACCESS",
			   "STATUS",
			   "DESCRIPTION",
			   "::= {",
			   "REFERENCE",
			   "INDEX"};
      
      //read junk before first Keyword
      String entry = reader.readToFirst(keywords, false);
      //System.out.println("TAE: " + entry);

      StringTokenizer st;
      String keyword;
      boolean done = false;
      while (!done) {
	//get first keyword
	keyword = reader.readToFirst(keywords, true);
	//System.out.println("key: " + keyword);
	if (keyword.equals("SYNTAX")) {
	  syntax = reader.readToFirst(keywords, false);
	}
	else if (keyword.equals("DESCRIPTION")) {
	  reader.readToFirst(MibFileReader.doubleQuotes, false);
	  st = new StringTokenizer(reader.readToFirst(MibFileReader.doubleQuotes, false));
	  while(st.hasMoreTokens()) {
	    description += " " + st.nextToken();
	  }
	  reader.readToFirst(keywords, false);
	  //System.out.println(description);
	}
	else if (keyword.equals("::= {"))
	  {
	    st = new StringTokenizer(reader.readToFirst(MibFileReader.curlyBraces, false));
	    done = true;
	    parentSymbolicName = st.nextToken();
	    numericName = st.nextToken();
	  }
	else {
	  reader.readToFirst(keywords, false);
	}
      }
    }

  public void setSyntax (String s)
    {
       syntax = s;
    }

  public String getSyntax()
    {
      return syntax;
    }
}
