package com.gensym.ntw.util;

/**
 * Interface for listening to file load and save status.
 */
public interface FileProgressListener extends java.util.EventListener {
  
  public void addFile(FileProgressEvent evt);
  
  public void removeFile(FileProgressEvent evt);

}
