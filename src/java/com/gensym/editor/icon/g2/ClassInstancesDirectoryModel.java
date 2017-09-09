package com.gensym.editor.icon.g2;

import javax.swing.*;
import java.util.Vector;
import java.io.File;
import java.net.*;
import com.gensym.util.Symbol;
import com.gensym.ntw.files.*;
import com.gensym.files.URLDirectoryModel;
import com.gensym.files.TypedFile;
import com.gensym.files.URLFile;
import com.gensym.files.URLFileParseException;

public class ClassInstancesDirectoryModel extends T2URLDirectoryModel {

  private Symbol className,attributeToDisplayName;
  public ClassInstancesDirectoryModel(String startingPoint,
				      Symbol className,
				      Symbol attributeToDisplayName){
    super(true, true, false, null, startingPoint);
    this.className = className;
    this.attributeToDisplayName = attributeToDisplayName;
  }

  @Override
  public TypedFile getTypedFile(String path) {
    if (path.startsWith("g2:") &&
	!(path.equals("g2:") ||
	  path.equals("g2://")))
      return makeClassInstancesForConnectionFile(path, className,attributeToDisplayName);
    else
      return super.getTypedFile(path);
  }  
  
  public static URLFile makeClassInstancesForConnectionFile(String urlString,
							    Symbol className,
							    Symbol attributeToDisplayName)
  {
    URLFile result = null;
    URL url = null;
    try {
      url = new URL(urlString);
    } catch (MalformedURLException e) {
	throw new URLFileParseException("Bad url: "+urlString);	
    }
    String file = url.getFile();
    String tail = "";
    if (file.length() > 1)
      tail = url.getFile().substring(1);
    if (tail.equals(""))
      result = new ModulesForConnectionFile(url);
    else{
      int slashIndex = tail.indexOf("/");
      if (slashIndex == (tail.length() - 1) || // g2://h:p/module/
	  slashIndex == -1)                    // g2://h:p/module
	result = new ClassInstancesForModuleFile(url,className,attributeToDisplayName);
      else
	result = new ItemFile(url);// g2://h:p/module/item
    }
    return result;
  }
  
}
