package com.gensym.ntw.files;

import com.gensym.message.Trace;
import com.gensym.util.Symbol;
import com.gensym.util.Sequence;
import com.gensym.files.*;
import java.net.URL;
import java.util.Vector;
import com.gensym.jgi.G2Access;
import com.gensym.jgi.G2AccessException;
import com.gensym.classes.MediaBin;
import com.gensym.classes.Block;


public class G2MediaRootFile extends G2ConnectionFile
{
  private Vector classNames = null;

  private static final Symbol MEDIA_BIN_ = Symbol.intern ("MEDIA-BIN");

  public G2MediaRootFile(String path, FileType type)
  {
    super(path,type);
  }
  
  public G2MediaRootFile(String path, String name, FileType type)
  {
    super(path,name,type);
  }

  G2MediaRootFile(URL url)
  {
    super(url);
  }

  @Override
  public String[] list()
  {
    // get all named media bins from a G2
    try 
      {
	G2Access connection = getConnection();
	Vector names = new Vector();
	
	if (classNames == null)
	  {
	    classNames = new Vector();
	    cacheMediaBinClasses(connection, MEDIA_BIN_);
	  }
	int i,size = classNames.size();
	for (i=0; i<size ; i++)
	  {
	    Sequence mediaBins
	      = connection.getStrictInstancesOfClass((Symbol)classNames.elementAt(i));
	    int j,mediaBinCount = mediaBins.size();
	    for (j=0; j<mediaBinCount ; j++)
	      {
		MediaBin mediaBin = (MediaBin)mediaBins.elementAt(j);
		String name = G2MediaFile.getMediaBinName(mediaBin);
		if (name != null)
		  names.addElement(name);
	      }
	  }
	String[] result = new String[names.size()];
	names.copyInto(result);
	return result;
      } catch (G2AccessException e)
	{
	  Trace.exception(e);
	  return new String[0];
	}
  }

  private void cacheMediaBinClasses(G2Access connection, Symbol className)
       throws G2AccessException
  {
    classNames.addElement(className);
    System.out.println("con="+connection+" name "+className);
    Sequence subClassNames = connection.getDirectSubclasses(className);
    
    int i,size = subClassNames.size();
    for (i=0; i<size ; i++)
      cacheMediaBinClasses(connection,(Symbol)subClassNames.elementAt(i));
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
    return "g2://"+url.getHost()+":"+url.getPort();
  }

  @Override
  public String getName()
  {
    return "namedBin";
  }
       
}
