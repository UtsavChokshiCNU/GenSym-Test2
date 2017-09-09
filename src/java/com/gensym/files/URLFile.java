package com.gensym.files;

import java.net.*;
import java.io.*;
import java.lang.reflect.*;

public abstract class URLFile extends TypedFile
{
  protected URL url;
  protected static boolean debug = false;
  
  public URLFile(String path, FileType type)
  {
    super(path,type);
    try {
      url = new URL(path);
    } catch (MalformedURLException e)
      {
	throw new URLFileParseException("Bad path: "+path);
      }
    finishURLParsing();
  }
  
  public URLFile(String path, String name, FileType type)
  {
    super(path,name,type);
    try {
      url = new URL(path+"/"+name);
    } catch (MalformedURLException e)
      {
	throw new URLFileParseException("Bad path: "+path+" and "+name);
      }
    finishURLParsing();
  }

  protected URLFile(URL url, FileType fileType)
  {
    super(url.toExternalForm(),fileType);
    this.url = url;
    finishURLParsing();
  }

  protected URLFile(FileType fileType)
  {
    super("",fileType);
  }

  public boolean supportsListFiles() {
    return false;
  }
  
  protected void finishURLParsing()
  {

  }

  @Override
  public String getCanonicalPath()
       throws IOException
  {
    // hack from HELL!
    // assume that all of our paths are canonical until proven otherwise.
    return getPath();
  }

  @Override
  public boolean mkdir()
  {
    return false;
  }

  // I know this clobbers the 1.2 definition of is hidden that is likely
  // to be more accurate than whatever I do in the subclasses of URLFile,
  // but this code has to work in 1.1 for a little while longer.  None
  // of the protocols except LocalFile (e.g. "file://...") have a notion of hiding.
  @Override
  public boolean isHidden()
  {
    return false;
  }

  @Override
  public String getPath()
  {
    if (url == null)
      return "";
    else
      return url.toExternalForm();
  }

  public URLConnection openConnection()
  {
    throw new RuntimeException("Not Yet Implemented");
  }

  public InputStream getInputStream()
       throws IOException
  {
    return null;
  }

  public Object getContents()
  {
    return null;
  }

  @Override
  public boolean canRead()
  {
    return false;
  }

  @Override
  public boolean canWrite()
  {
    return false;
  }

  public OutputStream getOutputStream()
       throws IOException
  {
    return null;
  }

}
