package com.gensym.editor.icon.g2;

import com.gensym.ntw.files.*;
import com.gensym.classes.MediaBin;
import com.gensym.util.Symbol;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.jgi.*;
import com.gensym.message.Trace;
import com.gensym.classes.Item;
import com.gensym.classes.KbWorkspace;
import java.net.URL;
import java.io.*;
import java.util.Vector;
import java.util.StringTokenizer;
import com.gensym.files.URLFileParseException;

public class ItemFile extends G2ConnectionFile{

  private String module;
  private String id;

  ItemFile(URL url){
    super(url);
  }

  @Override
  protected void finishURLParsing(){
    StringTokenizer tokenizer = new StringTokenizer (url.getFile(), "/", false);
    if (tokenizer.countTokens() == 2){
      module = tokenizer.nextToken();
      id = tokenizer.nextToken();
    }
    else throw new URLFileParseException("Bad Dialog Specification");
  }


  @Override
  public boolean isDirectory(){
    return false;
  }

  @Override
  public boolean isFile(){
    return true;
  }

  @Override
  public String[] list(){
    return null;
  }

  @Override
  public String getParent()
  {
    return "g2://"+url.getHost()+":"+url.getPort()+"/"+module;
  }

  @Override
  public String getName(){
    return id;
  }

  
  @Override
  public String toString()
  {
    return "<ItemFile: g2://"+url.getHost()+":"+url.getPort()+module+id+">";
  }

  public G2Access getConnectionForItem(){
    return getConnection();
  }

  public KbWorkspace getWorkspaceForItem() {
    return null;
  }
  
  public Item getItem(Symbol className) throws G2AccessException{
    String definitionName = getName();
    G2Access currentConnection = getConnection();
    Item def = currentConnection.getUniqueNamedItem
      (className, Symbol.intern (definitionName));    
    return def;
  }
}
