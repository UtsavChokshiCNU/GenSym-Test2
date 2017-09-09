package com.gensym.files;

import java.net.*;
import java.io.File;
import java.util.Vector;
import java.util.Enumeration;
import java.lang.reflect.Method;

public class ProtocolsFile extends URLFile
{
  private static Vector infos = new Vector();
  private boolean exists = true;
  private URLDirectoryModel directoryModel;
   
  ProtocolsFile(String path, FileType type)
  {
    super(path,type);
  }
  
  ProtocolsFile(String path, String name, FileType type)
  {
    super(path,name,type);
  }
  
  ProtocolsFile(URL url, URLDirectoryModel directoryModel)
  {
    super(url,FileType.SharedFolder);
    this.directoryModel = directoryModel;
  }
  
  ProtocolsFile(URLDirectoryModel directoryModel)
  {
    super(FileType.SharedFolder);
    this.directoryModel = directoryModel;
  }

  public static ProtocolsFile makeNonExistentProtocolsFile(URLDirectoryModel directoryModel)
  {
    ProtocolsFile pf = new ProtocolsFile(directoryModel);
    pf.exists = false;
    return pf;
  }

  @Override
  public boolean exists()
  {
    return exists;
  }

  @Override
  public boolean equals(Object o)
  {
    return o instanceof ProtocolsFile;
  }

  @Override
  public boolean isDirectory()
  {
    return true;
  }

  @Override
  public boolean isFile()
  {
    return false;
  }

  @Override
  public String[] list()
  {
    Enumeration protocols = directoryModel.getProtocols();
    int i = 0;
    String[] result = new String[directoryModel.getProtocolCount()];
    while (protocols.hasMoreElements())
      {
	ProtocolInfo info = (ProtocolInfo)protocols.nextElement();
	result[i] = info.urlBase;
	i++;
      }
    return result;
  }

  @Override
  public String toString()
  {
    return "<Protocols File>";
  }

  @Override
  public String getPath()
  {
    return "";
  }

  @Override
  public String getParent()
  {
    return null;
  }
}
 
