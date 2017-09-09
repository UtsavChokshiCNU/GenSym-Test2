package com.gensym.ntw.files;

import com.gensym.classes.MediaBin;
import com.gensym.util.Symbol;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.jgi.*;
import com.gensym.message.Trace;
import com.gensym.files.*;
import java.net.URL;
import java.io.*;
import java.util.Vector;
import java.util.StringTokenizer;

public class G2MediaFile extends G2ConnectionFile
{
  transient MediaBin mediaBin;
  private Symbol binName;
  private Vector location;
  private Structure description;
  private boolean potentialFile;
  private static final Symbol MEDIA_BIN_ = Symbol.intern ("MEDIA-BIN");
  private static final Symbol TYPE_ = Symbol.intern ("TYPE");
  private static final Symbol CONTENTS_ = Symbol.intern ("CONTENTS");
  private static final Symbol DIRECTORY_ = Symbol.intern ("DIRECTORY");


  public G2MediaFile(String path, FileType type)
  {
    super(path,type);
  }
  
  public G2MediaFile(String path, String name, FileType type)
  {
    super(path,name,type);
  }

  G2MediaFile(URL url)
  {
    super(url);
  }

  @Override
  protected void finishURLParsing()
  {
    StringTokenizer tokenizer = new StringTokenizer (url.getFile(), "/", false);
    location = new Vector ();
    while (tokenizer.hasMoreTokens ()) {
      String token = tokenizer.nextToken ();
      location.addElement (token);
    }
    if ((location.size() < 2) ||
	!location.elementAt(0).equals("namedBin"))
      throw new URLFileParseException("Bad Media Bin Specification");
    binName = Symbol.intern((String)location.elementAt(1));
    location.removeElementAt(0);
    location.removeElementAt(0);
  }
  
  private void cacheMediaBin()
  {
    Exception e = null;
    try {
      mediaBin 
	= (MediaBin) getConnection().getUniqueNamedItem (MEDIA_BIN_, binName);
      description = mediaBin.describe(location);
      if (description == null)
	potentialFile = true;
    } 
    catch (G2AccessException g2ae)
      {
	e = g2ae;
      }
    catch (IOException ioe)
      {
	e = ioe;
      }
    if (e != null)
      throw new RuntimeException("nested exception: "+e.getMessage());
  }

  @Override
  public boolean isDirectory()
  {
    cacheMediaBin();
    if (potentialFile)
      return false;
    else
      return description.getAttributeValue(TYPE_,null).equals(DIRECTORY_);
  }

  @Override
  public boolean isFile()
  {
    cacheMediaBin();
    if (potentialFile)
      return true;
    else
      return !description.getAttributeValue(TYPE_,null).equals(DIRECTORY_);
  }

  @Override
  public String[] list()
  {
    cacheMediaBin();
    if (isDirectory())
      {
	Vector contents 
	  = (Vector) description.getAttributeValue(CONTENTS_,null);
	String[] names = new String[contents.size()];
	contents.copyInto(names);
	return names;
      }
    else
      return new String[0];
  }

  @Override
  void dumpInfo()
  {
    cacheMediaBin();
    System.out.println(this+".describe("+
		       location+")="+description);
  }

  @Override
  public String getParent()
  {
    int i, size = location.size();
    String root = "g2://"+url.getHost()+":"+url.getPort()+"/namedBin";
    if (size == 0)
      return "g2://"+url.getHost()+":"+url.getPort()+"/namedBin";
    else
      {
	StringBuffer buffer = new StringBuffer(root+binName.toString());
	for (i=0; i<(size - 1) ; i++)
	  {
	    if (i > 0)
	      buffer.append("/");
	    buffer.append(location.elementAt(i).toString());
	  }
	return buffer.toString();
      }
  }

  @Override
  public String getName()
  {
    if (location.size() == 0)
      return getMediaBinName(mediaBin);
    else
      return (String) location.lastElement();
  }

  static String getMediaBinName(MediaBin mediaBin)
  {
    Object nameOrNames;
    try 
      { 
	nameOrNames = mediaBin.getNames();
	if (nameOrNames instanceof Sequence)
	  return ((Symbol)((Sequence)nameOrNames).elementAt(0)).getPrintValue();
	else if (nameOrNames instanceof Symbol)
	  return ((Symbol)nameOrNames).getPrintValue();
	else
	  return null;
      } catch (G2AccessException e)
	{
	  Trace.exception(e);
	  return null;
	}
  }
    
  @Override
  public String toString()
  {
    if (url == null)
      return "<G2MediaFile>";
    else
      return "<G2MediaFile @ \""+url.toExternalForm()+"\">";
  }

  @Override
  public InputStream getInputStream()
       throws IOException
  {
    cacheMediaBin();
    if (potentialFile)
      throw new FileNotFoundException(this+"is not found");
    Vector locationCopy = (Vector)location.clone();
    if (locationCopy.size() < 1)
      throw new IllegalStateException("Bad MediaBinFile");
    String name = (String) location.lastElement();
    locationCopy.removeElementAt(locationCopy.size() - 1);
    return mediaBin.makeBinaryInputStream(locationCopy, name);
  }

  @Override
  public Object getContents()
  {
    return null;
  }

  @Override
  public boolean canRead()
  {
    return isFile();
  }

  @Override
  public boolean canWrite()
  {
    return isFile();
  }

  public boolean makeSubDirectory(String subDirectoryName)
       throws IOException
  {
    cacheMediaBin();
    if (isDirectory())
      {
	mediaBin.makeDirectory(location,subDirectoryName);
	return true;
      }
    else
      return false;
  }

  @Override
  public OutputStream getOutputStream()
       throws IOException
  {
    cacheMediaBin();
    Vector locationCopy = (Vector)location.clone();
    if (locationCopy.size() < 1)
      throw new IllegalStateException("Bad MediaBinFile");
    String name = (String) location.lastElement();
    locationCopy.removeElementAt(locationCopy.size() - 1);
    return mediaBin.makeBinaryOutputStream(locationCopy, name);
  }

}
