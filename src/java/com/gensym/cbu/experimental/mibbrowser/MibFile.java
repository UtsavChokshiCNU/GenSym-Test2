package com.gensym.cbu.experimental.mibbrowser;

import java.awt.*;
import java.awt.event.*;
import java.io.*;
import javax.swing.*;
import javax.swing.tree.*;
import java.util.*;

public class MibFile
{
  File file;
  String name;
  Vector objectTypes = new Vector();
  Vector trapTypes = new Vector();
  Vector notificationTypes = new Vector();
  Vector mibDataTypes = new Vector();
  Vector imports = new Vector();
  Vector objectIdentifiers = new Vector();
  StringBuffer fileContents = new StringBuffer();
  
  public MibFile()
    {
    }

  @Override
  public String toString()
    {
      return file.getName();
    }

  public String getFileName()
    {
      return file.getAbsolutePath();
    }
  
  public String getName()
    {
      return name;
    }

  public MibFile(String fileName)
    {
      setFile(fileName);
    }

  public MibFile(File file)
    {
      setFile(file);
    }

  public File getFile()
    {
      return file;
    }

  public void setFile(String filename)
    {
      file = new File(filename);
    }

  public void setFile(File file)
    {
      this.file = file;
    }

  public void loadFile()
    throws IOException
    {
      FileReader fileReader;
      try {
	fileReader = new FileReader(file);
      } catch (FileNotFoundException fnfe) {
	System.out.println(fnfe);
	return;
      }
      BufferedReader br = new BufferedReader(fileReader);
      String line;
      StringTokenizer st;
      
      while( (line = br.readLine()) != null)
	{
	  st = new StringTokenizer(line);
	  if (st.countTokens() == 0 || st.nextToken().startsWith("--"))
	    {
	      //Throw the line away
	    }
	  else
	    {
	      fileContents.append(line + "\n");
	      //System.out.println(line);
	    }
	}
    }
  
  public void parseFile()
    throws IOException, KeywordNotFoundException, TokenNotFoundException
    {
      StringReader stringReader;
      stringReader = new StringReader(fileContents.toString());

      MibFileReader reader = new MibFileReader(stringReader);
      
      String firstToken, secondToken, thirdToken, fourthToken;
      ObjectType objectType;
      TrapType trapType;
      NotificationType notificationType;
      MibDataType mibDataType;
      ObjectIdentifier objectIdentifier;
      String entry;
      String nextToken;
      String[] keywords;
      StringTokenizer st;
      
      //read junk to before definition 
      keywords = new String[] {"DEFINITIONS ::= BEGIN"};
      reader.readToTokenBeforeFirst(keywords);
      //read defintions
      entry = reader.readToFirst(keywords, true);
      st = new StringTokenizer(entry);
      name = st.nextToken();
      //System.out.println("DEFINITION : name = " + name);

      //look for Imports
      keywords = new String[] {"IMPORTS"};
      if(reader.keywordFound(keywords)) {
	//read to Imports
	//System.out.println("IMPORTS");
	reader.readToFirst(keywords, true);
	entry = reader.readToFirst(new String[] {";"}, false);
	entry = entry.replace(',', ' '); //replace commas with spaces
	st = new StringTokenizer(entry);
	ImportDeclaration importDec;
	Vector importNames = new Vector();
	while(st.hasMoreTokens())
	  {
	    if (importNames == null) importNames = new Vector();
	    nextToken = st.nextToken();
	    //System.out.println("nextToken " + nextToken);
	    if (nextToken.equals("FROM"))
	      {
		nextToken = st.nextToken();
		importDec = new ImportDeclaration (nextToken, importNames);
		//System.out.println(importDec.toString());
		imports.add(importDec);
		importNames = null;
	      }
	    else {
	      importNames.add(nextToken);
	    }
	  }

	reader.read();//throws away ;

	keywords = new String[] {"OBJECT IDENTIFIER",
				 "TRAP-TYPE",
				 "OBJECT-TYPE",
				 "::=",
				 "NOTIFICATION-TYPE"};
	//look for ObjectTypes, TrapTypes, ObjectIdentifiers
	while(reader.keywordFound(keywords)) {
	  reader.readToTokenBeforeFirst(keywords);
	  entry = reader.readToFirst(keywords, true);
	  st = new StringTokenizer(entry);
	  firstToken = st.nextToken();
	  secondToken = st.nextToken();
	  if (secondToken.equals("OBJECT-TYPE")) {
	    //System.out.println("reading ObjectType : " + firstToken);
	    objectType = new ObjectType(firstToken);
	    objectType.load(reader);
	    objectTypes.add(objectType);
	  }
	  else if (secondToken.equals("TRAP-TYPE")) {
	    trapType = new TrapType(firstToken);
	    //System.out.println("reading TrapType : " + firstToken);
	    trapType.load(reader);
	    trapTypes.add(trapType);
	  }
	  else if (secondToken.equals("NOTIFICATION-TYPE")) {
	    notificationType = new NotificationType(firstToken);
	    //System.out.println("reading Notification Type : " + firstToken);
	    notificationType.load(reader);
	    notificationTypes.add(notificationType);
	  }
	  else if (secondToken.equals("OBJECT")) {
	    thirdToken = st.nextToken();
	    if (thirdToken.equals("IDENTIFIER")){
	      objectIdentifier = new ObjectIdentifier(firstToken);
	      //System.out.println("reading ObjectIdentifier : " + firstToken);
	      entry = reader.readToFirst(new String[] {"}"}, true);
	      entry = entry.replace('{', ' ');
	      entry = entry.replace('}', ' ');
	      entry = entry.replace(':', ' ');
	      entry = entry.replace('=', ' ');
	      st = new StringTokenizer(entry);
	      objectIdentifier.setOidParentName(st.nextToken());
	      objectIdentifier.numericName = st.nextToken();
	      objectIdentifiers.add(objectIdentifier);
	    }
	  }
	  else if (secondToken.equals("::=")) {
	    mibDataType = new MibDataType(firstToken);
	    //System.out.println("reading MibDataType : " + firstToken);
	    mibDataType.load(reader);
	    mibDataTypes.add(mibDataType);
	  }
	}
      }
      stringReader.close();

      //System.out.println("ObjectTypes : " + objectTypes.size());
      //System.out.println("TrapTypes : " + trapTypes.size());
      //System.out.println("NotificationTypes : " + notificationTypes.size());
    }

  public Vector getRequiredFiles()
    {
      Vector v = new Vector();
      for (Enumeration e = imports.elements(); e.hasMoreElements(); )
	{
	  v.add( ((ImportDeclaration)(e.nextElement())).mibName);
	}
      return v;
    }
	  
}


