package com.gensym.uitools.utils;

import java.io.File;
import java.io.IOException;
import java.io.FileOutputStream;
import java.io.OutputStream;
import java.io.InputStream;
import java.net.URL;
import java.net.URLClassLoader;
import java.net.MalformedURLException;
import javax.swing.JFileChooser;

public class JarInstaller {
  private static JarClassLoader newJarsClassLoader;
  
  public static Class forName(String className) throws ClassNotFoundException {
    return Class.forName(className, true, newJarsClassLoader);
  }

  public static File downloadJar(String url) throws IOException {
    return downloadJar(url, 1000);
  }
  
  public static File downloadJar(String url, int chunkSize) throws IOException {
    chunkSize = Math.max(chunkSize, 1);
    URL urlObject = new URL(url);
    String pluginName = urlObject.getFile();
    int slashIndex = pluginName.lastIndexOf("/");
    if (slashIndex > -1) 
      pluginName=pluginName.substring(slashIndex+1, pluginName.length());
    
    JFileChooser chooser = new JFileChooser();
    chooser.setDialogTitle("Install required plugin '" + pluginName + "'?");
    int returnVal = chooser.showSaveDialog(null);
    if(returnVal != JFileChooser.APPROVE_OPTION)
      return null;   
    
    File file = chooser.getSelectedFile();
    if (!file.exists())
      file.createNewFile();
    OutputStream ostream = new FileOutputStream(file);
    InputStream istream = urlObject.openStream();    

    byte[] newBytes = new byte[chunkSize];
    int bytesRead;
    while ((bytesRead = istream.read(newBytes)) > 0) {
      ostream.write(newBytes,0,bytesRead);
    }
    
    ostream.flush();
    istream.close();    
    ostream.close();
    return file;
  }

  public static void addURL(URL newURL) throws MalformedURLException {
    if (newJarsClassLoader == null)
      newJarsClassLoader = new JarClassLoader(new URL[] {newURL});
    else
      newJarsClassLoader.addURL(newURL);
  }

}

  class JarClassLoader extends URLClassLoader {
    JarClassLoader(URL[] urls) {
      super(urls);
    }
    @Override
    protected void addURL(URL url) {
      super.addURL(url);
    }
  }
