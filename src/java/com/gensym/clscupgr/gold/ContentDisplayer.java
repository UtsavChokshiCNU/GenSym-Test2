
package com.gensym.clscupgr.gold;

public interface ContentDisplayer {

  void displayDocument (String urlLocation);

  boolean isNextDocumentAvailable ();
  
  boolean isPreviousDocumentAvailable ();

  void nextDocument ();

  void previousDocument ();

}
