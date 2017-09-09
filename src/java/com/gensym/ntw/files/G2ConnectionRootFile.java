package com.gensym.ntw.files;

import com.gensym.message.Trace;
import com.gensym.files.*;
import java.net.URL;

public class G2ConnectionRootFile extends G2ConnectionFile
{
  private static boolean serverFileSystemVisible = false;
  private static boolean mediaBinsVisible = true;

  public G2ConnectionRootFile(String path, FileType type)
  {
    super(path,type);
  }
  
  public G2ConnectionRootFile(String path, String name, FileType type)
  {
    super(path,name,type);
  }

  public static void setServerFileSystemVisible(boolean visible)
  {
    serverFileSystemVisible = visible;
  }

  public static boolean isServerFileSystemVisible()
  {
    return serverFileSystemVisible;
  }

  public static void setMediaBinsVisible(boolean visible)
  {
    mediaBinsVisible = visible;
  }

  public static boolean areMediaBinsVisible()
  {
    return mediaBinsVisible;
  }

  G2ConnectionRootFile(URL url)
  {
    super(url);
  }

  @Override
  public String[] list()
  {
    if (serverFileSystemVisible && mediaBinsVisible)
      return new String[] {"namedBin", "serverFileSystem" };
    else if (serverFileSystemVisible)
      return new String[] {"serverFileSystem" };
    else if (mediaBinsVisible)
      return new String[] {"namedBin" };
    else
      return new String[] {};
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
  public String getParent()
  {
    return "g2://";
  }

  @Override
  public String getName()
  {
    return url.getHost()+":"+url.getPort();
  }
       
}
