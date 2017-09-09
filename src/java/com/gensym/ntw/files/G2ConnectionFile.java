package com.gensym.ntw.files;

import java.net.*;
import com.gensym.jgi.*;
import com.gensym.message.Trace;
import java.io.File;
import java.util.Vector;
import com.gensym.files.*;

public abstract class G2ConnectionFile extends URLFile
{
  transient G2Access connection;
  String host;
  String port;
  String subProtocol;
  String[] tail;

  public G2ConnectionFile(String path, FileType type)
  {
    super(path,type);
  }
  
  public G2ConnectionFile(String path, String name, FileType type)
  {
    super(path,name,type);
  }

  public G2ConnectionFile(URL url, FileType type) {
    super(url, type);
    if (type == null) {
      if (isDirectory())
	setType(FileType.SharedFolder);
      else 
	setType(FileType.SharedGenericFile);
    }
  }
  
  public G2ConnectionFile(URL url)
  {
    this(url, null);
  }

  /**
   *@undocumented
   */
  public G2Access getConnection()
  {
    try {
      connection 
	= G2Gateway.getOrMakeConnection(new com.gensym.ntw.TwConnectionInfo (url.getHost(),
									    ""+url.getPort()));
    } catch (ConnectionTimedOutException ctoe)
      {
	Trace.exception(ctoe);
      }
    catch (G2AccessInitiationException gaie)
      {
	Trace.exception(gaie);
      }
    
    return connection;
  }

  void dumpInfo()
  {

  }

 
}
