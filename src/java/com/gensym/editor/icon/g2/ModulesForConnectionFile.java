package com.gensym.editor.icon.g2;

import com.gensym.ntw.files.*;
import javax.swing.*;
import com.gensym.message.Trace;
import java.net.URL;
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
import com.gensym.classes.ModuleInformation;
import com.gensym.files.FileType;

public class ModulesForConnectionFile extends G2ConnectionFile{

  public ModulesForConnectionFile(String path, FileType type){
    super(path, type);
  }
  
  public ModulesForConnectionFile(String path, String name, FileType type){
    super(path, name, type);
  }

  ModulesForConnectionFile(URL url){
    super(url);
  }

  public G2Access getAccess() {
    return getConnection();
  }
  
  private static final Symbol MODULE_INFORMATION_ = Symbol.intern ("MODULE-INFORMATION");
  @Override
  public String[] list(){
    try{
      G2Access connection = getConnection();
      Sequence moduleInfos = connection.getStrictInstancesOfClass(MODULE_INFORMATION_);
      
      Enumeration elements = moduleInfos.elements();
      String[] modules = new String[moduleInfos.size()];
      int i = 0;
      while (elements.hasMoreElements()) {
	ModuleInformation moduleInfo = (ModuleInformation)elements.nextElement();
	Symbol moduleName = moduleInfo.getTopLevelModule();
	modules[i++] = (moduleName != null)?moduleName.toString():"UNNAMED MODULE";
      }
      return modules;
    }
    catch(G2AccessException ex){
      Trace.exception(ex);
      return new String[0];
    } 
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
  public String getParent(){
    return "g2://";
  }

  @Override
  public String getName(){
    return url.getHost()+":"+url.getPort();
  }

  
  @Override
  public String toString()
  {
    return "<ModulesForConnectionFile: g2://"+url.getHost()+":"+url.getPort()+">";
  }

       
}
