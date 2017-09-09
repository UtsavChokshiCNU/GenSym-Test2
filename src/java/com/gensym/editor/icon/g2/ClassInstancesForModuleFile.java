package com.gensym.editor.icon.g2;

import com.gensym.ntw.files.*;
import javax.swing.*;
import com.gensym.util.Symbol;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.jgi.*;
import com.gensym.message.Trace;
import java.net.URL;
import java.io.*;
import java.util.Vector;
import java.util.Enumeration;
import java.util.StringTokenizer;
import com.gensym.classes.Item;
import com.gensym.classes.Block;

public class ClassInstancesForModuleFile extends G2ConnectionFile{

  private Symbol moduleName;
  private Symbol className;
  private Symbol attributeToDisplayName;

  ClassInstancesForModuleFile(URL url, Symbol className, Symbol attributeToDisplayName){
    super(url);
    this.className = className;
    this.attributeToDisplayName = attributeToDisplayName;
  }

  @Override
  protected void finishURLParsing(){
    StringTokenizer tokenizer = new StringTokenizer (url.getFile(), "/", false);
    if (tokenizer.countTokens() == 1){
      moduleName = Symbol.intern(tokenizer.nextToken());
    }
    else throw new IllegalArgumentException("Bad Module Specification");
  }


  @Override
  public boolean isDirectory(){
    return true;
  }

  @Override
  public boolean isFile(){
    return false;
  }

  @Override
  public String[] list(){
    try{
      G2Access connection = getConnection();
      //need to restrict to module
      Sequence classInstancesList=connection.getStrictInstancesOfClass(className);
      Enumeration elements = classInstancesList.elements();
      String[] classInstances = new String[classInstancesList.size()];
      int i = 0;
      while (elements.hasMoreElements()) {
	Item nextInstance = (Item)elements.nextElement();
	try {
	  classInstances[i] = nextInstance.getPropertyValue(attributeToDisplayName).toString();
	} catch (com.gensym.util.NoSuchAttributeException nsae) {
	  Trace.exception(nsae);
	  classInstances[i] = nextInstance.toString();
	} catch (G2AccessException g2ae) {
	  Trace.exception(g2ae);
	  classInstances[i] = nextInstance.toString();
	}
	i++;
      }
      return classInstances;
    }
    catch(G2AccessException ex){
      Trace.exception(ex);
      return new String[0];
    } 
  }

  @Override
  public String getParent()
  {
    return "g2://"+url.getHost()+":"+url.getPort();
  }

  @Override
  public String getName(){
    return moduleName.toString();
  }

  
  @Override
  public String toString()
  {
    return "<ClassInstancesForModuleFile: g2://"+url.getHost()+":"+url.getPort()+moduleName+">";
  }


}
