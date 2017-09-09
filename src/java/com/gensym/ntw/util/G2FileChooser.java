/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 G2FileChooser.java
 *
 */
package com.gensym.ntw.util;

import com.gensym.message.Resource;
import com.gensym.files.URLFile;
import com.gensym.files.URLFileSystemView;
import com.gensym.jgi.G2ConnectionInfo;
import com.gensym.jgi.G2Gateway;
import com.gensym.ntw.files.T2URLDirectoryModel;
import com.gensym.ntw.files.G2ServerFile;
import com.gensym.ntw.TwAccess;
import com.gensym.uitools.utils.ConfigurableJFileChooser;

public class G2FileChooser extends ConfigurableJFileChooser {
  private static Resource i18n = Resource.getBundle("com/gensym/ntw/util/FileIO");
  public static OpenFileFilter kbFileFilter 
  = new OpenFileFilter(i18n.getString("KbFileFilter"),
		       i18n.getString("KbFileFilterDescription"));
  private TwAccess connection;
  private URLFile urlFile;

  public G2FileChooser (TwAccess connection) {
    this(((G2Gateway)connection).getG2ConnectionInfo());
    removeChoosableFileFilter(getAcceptAllFileFilter());
    addChoosableFileFilter(kbFileFilter);
    setFileFilter(kbFileFilter);
    this.connection = connection;    
  }
  
  private G2FileChooser(G2ConnectionInfo cxnInfo) {
    super("g2://"+cxnInfo.getHost()+":"+cxnInfo.getPort()+"/serverFileSystem/",
	  new URLFileSystemView(new T2URLDirectoryModel(false, true, false, cxnInfo, null)));
  }

  public void setConnection(TwAccess cxn) {
    this.connection = connection;
    //need to update the file system view
  }
  
  //New method,add to T2 to be able to access connection used by file chooser.
  public TwAccess getConnection(){
    return this.connection;
  }

  public String getG2FileSpecification() {
    URLFile result = (URLFile)getSelectedFile();
    String path = LoadSaveKBTools.getG2FileSpecificationFromURL(connection, result);
    return path;
  }

  public void setG2FileSpecification(String path) {
    String urlString = LoadSaveKBTools.revertG2FileSpecificationToURLString(connection, path);
    G2ConnectionInfo cxnInfo = ((G2Gateway)connection).getG2ConnectionInfo();
    String host = cxnInfo.getHost();
    String port = cxnInfo.getPort();
    path = "g2://"+host+":"+port+"/serverFileSystem/"+urlString;
    setSelectedFile(new G2ServerFile(path, null));
  }

}

