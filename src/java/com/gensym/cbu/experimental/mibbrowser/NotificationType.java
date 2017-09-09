package com.gensym.cbu.experimental.mibbrowser;

import java.awt.*;
import java.io.*;
import java.util.*;
import javax.swing.*;

public class NotificationType extends MibFileObjectAdapter implements MibFileObjectTableObject
{
  Vector objects = new Vector();
  String status = new String();

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
      case 1: return "status";
      case 2: return "Description";
      case 3: return "NumericName";
      case 4: return "Objects";
      default: return "?";
      }
    }

    @Override
    public String getValue(int row)
    {
      switch (row) {
      case 0: return symbolicName;
      case 1: return status;
      case 2: return description;
      case 3: return numericName;
      case 4: { String objs = new String();
      for (Enumeration e = objects.elements(); e.hasMoreElements(); )
	objs += e.nextElement() + " ";
	return objs;}
      default: return "?";
      }
    }
    //end MibFileObject Interface

  @Override
  public String toString()
    {
      return symbolicName;
    }

  public NotificationType (String name)
    {
      symbolicName = name;
    }

  public void load(MibFileReader reader) throws IOException, KeywordNotFoundException
    {
      String[] keywords = {"STATUS",
			   "DESCRIPTION",
			   "::= ",
			   "OBJECTS"};

      //read junk before first Keyword
      String entry = reader.readToFirst(keywords, false);

      StringTokenizer st;
      String keyword;
      boolean done = false;
      while (!done) {
	//get first keyword
	keyword = reader.readToFirst(keywords, true);
	//System.out.println("key: " + keyword);
	if (keyword.equals("STATUS")) {
	  st = new StringTokenizer(reader.readLine());
	  status = st.nextToken();
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
	else if (keyword.equals("OBJECTS")) {
	  entry = reader.readToFirst(keywords, false);
	  entry = entry.replace(',', ' ');
	  entry = entry.replace('{', ' ');
	  entry = entry.replace('}', ' ');
	  System.out.println("objs entry:" + entry);
	  st = new StringTokenizer(entry);
	  while(st.hasMoreTokens()) {
	    objects.add(st.nextToken());
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
}
