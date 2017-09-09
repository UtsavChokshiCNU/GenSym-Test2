package com.gensym.ntw.files;

import com.gensym.util.Symbol;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.jgi.*;
import com.gensym.message.Trace;
import com.gensym.files.*;
import java.net.URL;
import java.io.*;
import java.util.Vector;
import java.util.Enumeration;
import java.util.StringTokenizer;

public class UILDialogImportModuleFile extends G2ConnectionFile{

  private static final Symbol UPP_GET_MASTER_DIALOG_LIST_ = 
                              Symbol.intern("UPP-GET-MASTER-DIALOG-LIST");
  private Symbol name;

  UILDialogImportModuleFile(URL url){
    super(url);
  }

  @Override
  protected void finishURLParsing(){
    StringTokenizer tokenizer = new StringTokenizer (url.getFile(), "/", false);
    if (tokenizer.countTokens() == 1){
      name = Symbol.intern(tokenizer.nextToken());
    }
    else throw new URLFileParseException("Bad Module Specification");
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
      Sequence dialogList = (Sequence)connection.callRPC(UPP_GET_MASTER_DIALOG_LIST_, 
						new java.lang.Object[] {name});
      Enumeration elements = dialogList.elements();
      String[] dialogs = new String[dialogList.size()];
      int i = 0;
      while (elements.hasMoreElements())
	dialogs[i++] = elements.nextElement().toString();
      return dialogs;
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
    return name.toString();
  }

  
  @Override
  public String toString()
  {
    return "<UILDialogImportModuleFile: g2://"+url.getHost()+":"+url.getPort()+name+">";
  }


}
