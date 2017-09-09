package com.gensym.cbu.experimental.mibbrowser;

import java.awt.*;
import java.io.*;
import java.util.*;
import javax.swing.*;

public class TrapType extends MibFileObjectAdapter implements MibFileObjectTableObject
{
  String enterprise = new String();
  Vector variables = new Vector();

  //MibFileObject Interface
  @Override
  public int getRowCount()
    {
      return 7;
    }

  @Override
  public String getAttribute(int row)
    {
      switch (row) {
      case 0: return "SymbolicName";
      case 1: return "Enterprise";
      case 2: return "Description";
      case 3: return "NumericName";
      case 4: return "Variables";
      case 5: return "FullSymbolicName";
      case 6: return "FullNumericName";
      default: return "?";
      }
    }

    @Override
    public String getValue(int row)
    {
      switch (row) {
      case 0: return symbolicName;
      case 1: return enterprise;
      case 2: return description;
      case 3: return numericName;
      case 4: { String vars = new String();
      for (Enumeration e = variables.elements(); e.hasMoreElements(); )
	vars += e.nextElement() + " ";
	return vars;}
      case 5: if(fullSymbolicName == null) return ""; else return fullSymbolicName;
      case 6: if(fullNumericName == null) return ""; else return fullNumericName;
      default: return "?";
      }
    }
    //end MibFileObject Interface

  @Override
  public String toString()
    {
      return symbolicName;
    }

  public TrapType (String name)
    {
      symbolicName = name;
    }

  public void load(MibFileReader reader) throws IOException, KeywordNotFoundException
    {
      String[] keywords = {"MAX-ACCESS",
			   "ACCESS",
			   "STATUS",
			   "DESCRIPTION",
			   "::= ",
			   "REFERENCE",
			   "INDEX",
			   "VARIABLES",
			   "ENTERPRISE"};

      //read junk before first Keyword
      String entry = reader.readToFirst(keywords, false);

      StringTokenizer st;
      String keyword;
      boolean done = false;
      while (!done) {
	//get first keyword
	keyword = reader.readToFirst(keywords, true);
	//System.out.println("key: " + keyword);
	if (keyword.equals("ENTERPRISE")) {
	  st = new StringTokenizer(reader.readLine());
	  enterprise = st.nextToken();
	  reader.readToFirst(keywords, false);
	  //System.out.println("Enterprise: " + enterprise);
	}
	else if (keyword.equals("DESCRIPTION")) {
	  reader.readToFirst(MibFileReader.doubleQuotes, true);
	  entry = reader.readToFirst(MibFileReader.doubleQuotes, false);
	  st = new StringTokenizer(entry);
	  description = st.nextToken();
	  while(st.hasMoreTokens()) {
	    description += " " + st.nextToken();
	  }
	  reader.readToFirst(keywords, false);
	  //System.out.println("Description: " + description);
	}
	else if (keyword.equals("VARIABLES")) {
	  entry = reader.readToFirst(keywords, false);
	  entry = entry.replace(',', ' ');
	  entry = entry.replace('{', ' ');
	  entry = entry.replace('}', ' ');
	  //System.out.println("vars entry:" + entry);
	  st = new StringTokenizer(entry);
	  while(st.hasMoreTokens()) {
	    variables.add(st.nextToken());
	  }
	}
	else if (keyword.equals("::= "))
	  {
	    st = new StringTokenizer(reader.readLine());
	    done = true;
	    numericName = st.nextToken();
	    //System.out.println("OidExtension: " + oidExtension);
	  }
	else {
	  System.out.println("doing else");
	  reader.readToFirst(keywords, false);
	}
      }
    }

  public void setEnterprise(String s)
    {
      enterprise = s;
    }

  public String getEnterprise()
    {
      return enterprise;
    }
}
