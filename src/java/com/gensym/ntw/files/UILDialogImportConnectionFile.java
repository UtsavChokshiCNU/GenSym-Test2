package com.gensym.ntw.files;

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
import com.gensym.files.*;

public class UILDialogImportConnectionFile extends G2ConnectionFile{

  private static final Symbol UPP_GET_MASTER_DIALOG_MODULES_LIST_ = 
                              Symbol.intern("UPP-GET-MASTER-DIALOG-MODULES-LIST");

  public UILDialogImportConnectionFile(String path, FileType type){
    super(path, type);
  }
  
  public UILDialogImportConnectionFile(String path, String name, FileType type){
    super(path, name, type);
  }

  UILDialogImportConnectionFile(URL url){
    super(url);
  }

  @Override
  public String[] list(){
    try{
      G2Access connection = getConnection();
      Sequence moduleList = (Sequence)connection.callRPC(UPP_GET_MASTER_DIALOG_MODULES_LIST_, 
						new java.lang.Object[] {});
      Enumeration elements = moduleList.elements();
      String[] modules = new String[moduleList.size()];
      int i = 0;
      while (elements.hasMoreElements())
	modules[i++] = elements.nextElement().toString();
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
    return "<UILDialogImportConnectionFile: g2://"+url.getHost()+":"+url.getPort()+">";
  }

       
}
