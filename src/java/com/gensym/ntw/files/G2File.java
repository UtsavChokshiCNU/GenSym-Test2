package com.gensym.ntw.files;

import java.net.*;
import java.io.File;
import java.util.Vector;
import com.gensym.jgi.G2ConnectionInfo;
import com.gensym.core.GensymApplication;
import com.gensym.net.g2.*;
import com.gensym.files.*;


public class G2File extends URLFile
{
  private static Vector infos = new Vector();

  public G2File(String path, FileType type)
  {
    super(path,type);
  }
  
  public G2File(String path, String name, FileType type)
  {
    super(path,name,type);
  }

  G2File(URL url)
  {
    super(url,FileType.SharedFolder);
  }

  G2File()
  {
    super(FileType.SharedFolder);
  }

  @Override
  public String[] list()
  {
    int i, size = infos.size();
    String[] result = new String[size];
    for (i=0; i<size ; i++)
      {
	G2ConnectionInfo info = (G2ConnectionInfo)infos.elementAt(i);
	result[i] = info.getHost()+":"+info.getPort()+"/";
      }
    return result;
  }

  @Override
  public boolean equals(Object o)
  {
    return o instanceof G2File;
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
    return "";
  }

  @Override
  public String getPath()
  {
    return "g2://";
  }

  @Override
  public String toString()
  {
    return "<G2File: g2://>";
  }

  public static void registerG2ConnectionInfo(G2ConnectionInfo info)
  {
    if (!infos.contains(info))
      infos.addElement(info);
  }

  public static void deregisterG2ConnectionInfo(G2ConnectionInfo info)
  {
    infos.removeElement(info);
  }
  public static URLFile makeG2File(String urlString) {
    return makeG2File(urlString, null);
  }
  
  public static URLFile makeG2File(String urlString,
				   FileType type)
  {
    if (URLFile.debug)
      System.out.println("makeG2File called on "+urlString);
    if (urlString.equals("g2:") ||
	urlString.equals("g2://"))
      return new G2File();
    URL url = null;
    try {
      url = new URL(urlString);
    } catch (MalformedURLException e)
      {
	if (URLFile.debug)
	  System.out.println("malformed url "+e.getMessage());
	e.printStackTrace();
	throw new URLFileParseException("Bad url: "+urlString);
      }

    String tail = url.getFile().substring(1);    
    String subProtocol = "";
    int slashIndex = tail.indexOf("/");
    if (URLFile.debug)
      System.out.println("tail="+tail+" SLSHDX="+slashIndex);
    if (slashIndex != -1)
      subProtocol = tail.substring(0,slashIndex);
    else 
      subProtocol = tail;
    if (subProtocol.equals(""))
      return new G2ConnectionRootFile(url);
    else if (subProtocol.equals("namedBin"))
      {
	if (slashIndex == (tail.length() - 1) || // g2://h:p/namedBin/
	    slashIndex == -1)                    // g2://h:p/namedBin
	  return new G2MediaRootFile(url);
	else{
	  //workaround for bug HQ-2951645: 
	  //nameMediaBin in ComponentEditor file dialogs doesn't work on solaris
	  if (tail.indexOf("..", tail.length() - 2) != -1)
	    return null;
	  else
	    return new G2MediaFile(url);
	}
      }
    else if (subProtocol.equals("serverFileSystem")) 
      return new G2ServerFile(url, type);
    else 
      return null;
  }

  @Override
  public String getName()
  {
    return "g2://";
  }

  public static void main(String[] args)
  {
    GensymApplication.initialize();
    G2ConnectionInfo info = new G2ConnectionInfo("ganesha","1111");
    registerG2ConnectionInfo(info);
    System.out.println("HOME is "+System.getProperty("user.home"));
    System.out.println("OS is "+System.getProperty("os.name"));
    URL u1 = null;
    try {
      u1 = new URL("file:///");
    } catch (Exception e) {}
    System.out.println("url.getFile() -> \""+u1.getFile());
    System.out.println("url = "+u1.toExternalForm());
    try {
      u1 = new URL("file:///c:/bt");
    } catch (Exception e) {}
    System.out.println("url.getFile() -> \""+u1.getFile());
    System.out.println("url = "+u1.toExternalForm());
    try {
      u1 = new URL("file://ganesha:1111/c:/bt");
    } catch (Exception e) {}
    System.out.println("url.getFile() -> \""+u1.getFile());
    System.out.println("url = "+u1.toExternalForm());
     try {
      u1 = new URL("file://ganesha/c:/bt");
    } catch (Exception e) {}
    System.out.println("url.getFile() -> \""+u1.getFile());
    System.out.println("url = "+u1.toExternalForm());
    File file = new File(args[0]);
    while (file.getParent() != null)
      {
	System.out.println("at level "+file);
	file = new File(file.getParent());
      }
    System.out.println("at end "+file);
    /*
    file = new File("\\");
    String[] names = file.list();
    System.out.println("number of files = "+names.length);
    for (int i = 0; i<names.length ; i++)
      System.out.println("name "+i+" is "+names[i]);
      */
    G2ProtocolRegistry.loadInterpreters();
    URLFile uf
      = makeG2File("g2://");
    System.out.println("URLFile = "+uf+" dir?="+uf.isDirectory()+
		       " file?="+uf.isFile());
    if (uf.isDirectory())
      {
	String[] names = uf.list();
	for (int i = 0; i<names.length ; i++)
	  System.out.println("name "+i+" = "+names[i]);
      }
    uf
      = makeG2File("g2://ganesha:1111");
    System.out.println("URLFile = "+uf+" dir?="+uf.isDirectory()+
		       " file?="+uf.isFile());
    if (uf.isDirectory())
      {
	String[] names = uf.list();
	for (int i = 0; i<names.length ; i++)
	  System.out.println("name "+i+" = "+names[i]);
      }
    uf
      = makeG2File("g2://ganesha:1111/namedBin");
    System.out.println("URLFile = "+uf+" dir?="+uf.isDirectory()+
		       " file?="+uf.isFile());
    if (uf.isDirectory())
      {
	String[] names = uf.list();
	for (int i = 0; i<names.length ; i++)
	  System.out.println("name "+i+" = "+names[i]);
      }
    G2MediaFile mf 
      = (G2MediaFile) makeG2File("g2://ganesha:1111/namedBin/MB-1");
    System.out.println("mediaFile = "+mf+" dir?="+mf.isDirectory()+
		       " file?="+mf.isFile());
    mf.dumpInfo();
    if (mf.isDirectory())
      {
	String[] names = mf.list();
	for (int i = 0; i<names.length ; i++)
	  System.out.println("name "+i+" = "+names[i]);
      }
    mf = (G2MediaFile) makeG2File("g2://ganesha:1111/namedBin/MB-1/Bob");
    System.out.println("mediaFile = "+mf+" dir?="+mf.isDirectory()+
		       " file?="+mf.isFile());
    mf.dumpInfo();
    if (mf.isDirectory())
      {
	String[] names = mf.list();
	for (int i = 0; i<names.length ; i++)
	  System.out.println("name "+i+" = "+names[i]);
      }

    System.exit(0);
  }
}
