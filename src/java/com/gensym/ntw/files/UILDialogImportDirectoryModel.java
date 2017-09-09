package com.gensym.ntw.files;

import java.util.Vector;
import java.io.File;
import java.lang.reflect.Method;
import com.gensym.files.*;

public class UILDialogImportDirectoryModel extends URLDirectoryModel
{
  public UILDialogImportDirectoryModel(String startingPoint)
  {
    super(false,startingPoint,makeProtocolInfo());
  }

  private static ProtocolInfo makeProtocolInfo()
  {
    try {
      Class c = Class.forName("com.gensym.ntw.files.UILDialogImportG2File");
      Method m = c.getMethod("makeUILDialogImportG2File", new Class[] { String.class });
      return new ProtocolInfo("g2","g2://",m);
    } catch (Exception e)
      {
	throw new NoSuchMethodError("UILDialogImportG2File.makeUILDialogImportG2File");
      }
  }

  @Override
  public void setCurrentDirectory(File dir){
    if (dir == null)
      dir = makeFileFromPath("g2://");
    super.setCurrentDirectory(dir);
  }

}
