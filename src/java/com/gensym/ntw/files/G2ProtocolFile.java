package com.gensym.ntw.files;

import java.net.*;
import java.io.File;
import java.util.Vector;
import com.gensym.files.*;

public class G2ProtocolFile extends URLFile
{

  private boolean exists = true;

  public G2ProtocolFile(String path, FileType type)
  {
    super(path,type);
  }
  
  public G2ProtocolFile(String path, String name, FileType type)
  {
    super(path,name,type);
  }

  G2ProtocolFile(URL url)
  {
    super(url,FileType.SharedFolder);
  }

  G2ProtocolFile()
  {
    super(FileType.SharedFolder);
  }

   @Override
   public boolean exists()
  {
    return exists;
  }

  @Override
  public boolean equals(Object o)
  {
    return o instanceof G2ProtocolFile;
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
    return new String [] {"g2://"};
  }

  @Override
  public String toString()
  {
    return "<G2Protocol File>";
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
