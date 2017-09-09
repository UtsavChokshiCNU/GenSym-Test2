package com.gensym.ntw.files;

import java.net.*;
import java.io.File;
import java.util.Vector;
import java.util.StringTokenizer;
import com.gensym.jgi.G2ConnectionInfo;
import com.gensym.core.GensymApplication;
import com.gensym.net.g2.*;
import com.gensym.files.*;

public class UILDialogImportG2File extends G2File
{

  public static URLFile makeUILDialogImportG2File(String urlString)
  {
    URLFile result = null;
    if (urlString.equals(""))
      return new G2ProtocolFile();
    if (urlString.equals("g2:") ||
	urlString.equals("g2://")) 
      return new UILDialogImportG2File();

    URL url = null;
    try {
      url = new URL(urlString);
    } catch (MalformedURLException e)
      {
	e.printStackTrace();
	throw new URLFileParseException("Bad url: "+urlString);
      }
    String tail = url.getFile().substring(1);

    if (tail.equals(""))
      result = new UILDialogImportConnectionFile(url);
    else{
      int slashIndex = tail.indexOf("/");
      if (slashIndex == (tail.length() - 1) || // g2://h:p/module/
	  slashIndex == -1)                    // g2://h:p/module
	result = new UILDialogImportModuleFile(url);
      else
	result = new UILDialogImportDialogFile(url);// g2://h:p/module/dialog
    }
    return result;
  }

  
  @Override
  public String toString()
  {
    return "<UILDialogImportG2File: g2://>";
  }


}
