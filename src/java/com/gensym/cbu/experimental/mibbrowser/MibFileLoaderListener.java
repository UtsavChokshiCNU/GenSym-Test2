package com.gensym.cbu.experimental.mibbrowser;

import java.io.*;
import com.adventnet.snmp.mibs.*;


public interface MibFileLoaderListener
{
//  public void progressEvent(String mibFile, String message);
  public void loadError(String mibFile, String msg);
  public void loadFinished(MibModule mibFile);
  public void loadingFile(String mibFile);  
//  public void loadingRequiredFile(String mibFile);
//  public void requiredFileLoaded(MibModule mibFile);
}
