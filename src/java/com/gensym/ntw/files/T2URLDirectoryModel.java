package com.gensym.ntw.files;

import com.gensym.files.*;
import com.gensym.jgi.G2Access;
import com.gensym.jgi.G2ConnectionInfo;
import java.util.Vector;
import java.net.URL;
import java.io.File;
import java.lang.reflect.Method;

public class T2URLDirectoryModel extends URLDirectoryModel
{
  boolean useServerFileSystem;
  boolean useMediaBins;
  G2Access connection;
  private boolean debug = false;

  public T2URLDirectoryModel(boolean useLocalFileSystem,
			     boolean useServerFileSystem,
			     boolean useMediaBins,
			     G2ConnectionInfo info,
			     String startingPoint)
  {
    super(useLocalFileSystem,startingPoint,
	  makeProtocolInfo(useServerFileSystem,useMediaBins));
    this.useLocalFileSystem = useLocalFileSystem;
    this.useServerFileSystem = useServerFileSystem;
    this.useMediaBins = useMediaBins;
    // this.connection = connection;
    if (info != null)
      G2File.registerG2ConnectionInfo(info);
  }

  private static ProtocolInfo makeProtocolInfo(boolean useServerFileSystem,
				       boolean useMediaBins)
  {
    if (useServerFileSystem || useMediaBins)
      {
	try {
	  Class c = Class.forName("com.gensym.ntw.files.G2File");
	  Method m = c.getMethod("makeG2File", new Class[] { String.class });
	  return new ProtocolInfo("g2","g2://",m);
	} catch (Exception e)
	  {
	    throw new NoSuchMethodError("G2File.makeG2File");
	  }
      }
    else
      return null;
  }

  @Override
  public void setCurrentDirectory(File dir)
  {
    if (debug)
      {
	System.out.println("setCurDir call with "+dir+" cur "+curDir+" from ");
	Thread.dumpStack();
      }
    if (dir == null){
      if (useLocalFileSystem)
	dir = makeFileFromPath("file:///"+
				       System.getProperty("user.home"));
      else
	dir = makeFileFromPath("g2://");
    }
    //dir = new File(System.getProperty("user.home"));
    
    dir = makeAbsolute(dir);
    if (curDir != null && debug)
      System.out.println("curDir{="+
			 curDir+"}.equals(dir) =>"+curDir.equals(dir));
    else if (debug)
      System.out.println("curDir is null");
    /*
     * Note that we compare literal paths, not canonical
     * paths. If they want the chooser to represent the
     * files at the end of a different route to the same
     * place, that's perfectly legitimate. See NextStep
     * for e.g.
     */
    if (curDir == null || !curDir.equals(dir)) {
      invalidateCache();
      File oldDir = curDir;
      curDir = dir;
      firePropertyChange("currentDirectory", oldDir, dir);
      fireContentsChanged();
    }

    if (debug)
      System.out.println("now current directory is "+curDir);
  }
}
