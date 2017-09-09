package com.gensym.files;

import java.util.Vector;
import java.util.Enumeration;
import java.net.URL;
import java.io.File;
import java.lang.reflect.*;

public class URLDirectoryModel extends DirectoryModel
{
  protected boolean useLocalFileSystem;
  private boolean debug = false;
  private Vector protocols = new Vector();

  public URLDirectoryModel(boolean useLocalFileSystem,
			   String startingPoint,
			   ProtocolInfo protocolOrNull)
  {
    this.useLocalFileSystem = useLocalFileSystem;
    if (protocolOrNull != null)
      protocols.addElement(protocolOrNull);
    if (useLocalFileSystem)
      addProtocol("file","file:///",null);
    if (startingPoint == null)
      setCurrentDirectory(null);
    else
      setCurrentDirectory(makeFileFromPath(startingPoint));
    // this.connection = connection;
    //if (info != null)
    //   G2File.registerG2ConnectionInfo(info);
  }

  protected String makeDefaultHomeDirectoryName()
  {
    return "file:///"+System.getProperty("user.home");
  }

  @Override
  public void setCurrentDirectory(File dir)
  {
    if (debug)
      {
	System.out.println("setCurDir call with "+dir+" cur "+curDir+" from ");
	Thread.dumpStack();
      }
    if (dir == null)
      {
	makeFileFromPath(makeDefaultHomeDirectoryName());
      }
    
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

  @Override
  protected File makeAbsolute(File f)
  {
    return f;
  }

  @Override
  public URLFile makeFileFromPath(String path)
  {
    if (debug)
      System.out.println("makefilefrompath called with \""+path+"\"");
    if (path.equals(""))
      return new ProtocolsFile(this);
    int colonIndex = path.indexOf(':');
    if (colonIndex == -1)
      throw new URLFileParseException("malformed URL-path "+path);
    else
      {
	String protocol = path.substring(0,colonIndex).toLowerCase();
	Method parseMethod = getProtocolParseMethod(protocol);
	if (parseMethod != null)
	  {
	    try
	      {
		return (URLFile)parseMethod.invoke(null,new Object[] { path });
	      }
	    catch (Exception e)
	      {
		e.printStackTrace();
		throw new RuntimeException("internal error in protocol parse function for"+
					   protocol);
	      }
	  }
	else if (protocol.equals("file"))
	  return LocalFile.makeLocalFile(path);
	else
	  throw new URLFileParseException("unknown protocol "+protocol);
      }
  }

  protected void addProtocol(String name, String urlBase, Method parseMethod)
  {
    protocols.addElement(new ProtocolInfo(name,urlBase,parseMethod));
  }

  public Method getProtocolParseMethod(String name)
  {
    int i,len = protocols.size();
    for (i=0; i<len; i++)
      {
	ProtocolInfo info = (ProtocolInfo)protocols.elementAt(i);
	if (info.name.equals(name))
	  return info.parseMethod;
      }
    return null;
  }

  public Enumeration getProtocols()
  {
    return protocols.elements();
  }

  public int getProtocolCount()
  {
    return protocols.size();
  }
  
  @Override
  public boolean canGoUp() 
  {
    if (debug)
      System.out.println("can go up at "+getCurrentDirectory());
    return getCurrentDirectory().getParent() != null;
  }
 
  @Override
  public void goUp() 
  {
    if (debug)
      System.out.println("go up at "+getCurrentDirectory());
    File curDir = getCurrentDirectory();
    
    String parentPath = curDir.getParent();
    File parent
      = parentPath == null ? 
      null : 
      makeFileFromPath(parentPath);
    if (parent != null) {
      setCurrentDirectory(parent);
    }
  }


  // methods to override
  // makeAbsolute(File f) - maybe
  // setCurrentDirectory(File dir)
  // getTypedFile(String path, String name)
  // getTypedFile(String path)
  // getTypedFilesForDirectory(File dir)
  // goUp()
  // ... from List
  // getSize()
  // getElementAt()


  /**
   * Given a path and a file name, return a TypedFile
   */
  @Override
  public TypedFile getTypedFile(String path, String name)
  {
    String separator = "/";
    if (path.equals("") ||
	path.charAt(path.length()-1) == '/')
      separator = "";
    return getTypedFile(path+separator+name);
  }
  
  /**
   * Given a path, return a TypedFile
   */
  @Override
  public TypedFile getTypedFile(String path) {
    return makeFileFromPath(path);
  }
  

  /**
   * Convenience, same as 
   * <code>getTypedFilesForDirectory(getCurrentDirectory())</code>
   */
  @Override
  public Vector getTypedFiles() {
    return getTypedFilesForDirectory(getCurrentDirectory());
  }

  @Override
  public File[] getRoots()
  {
    return new File[] { new ProtocolsFile(this) };
  }

  /**
   * Return a Vector of the files in the given directory, filtered
   * according to <code>knownTypes</code> and hiddenRule. The Vector
   * may be empty.
   *
   * The objects in the Vector are of instances of TypedFile
   */
  @Override
  public Vector getTypedFilesForDirectory(File dir) 
  {
    boolean useCache = dir.equals(getCurrentDirectory());
    
    if(useCache && currentFilesFresh)
      return currentFiles;
    
    Vector resultSet;
    if (useCache)
      {
	resultSet = currentFiles;
	resultSet.removeAllElements();
      } 
    else 
      resultSet = new Vector();
    
    if (debug)
      System.out.println("calling list on "+dir+"with path \""+
			 dir.getPath()+"\"");
    String[] names = dir.list();
    
    int nameCount = names == null ? 0 : names.length;
    for (int i = 0; i < nameCount; i++) {
      if (debug)
	System.out.println("names["+i+"]="+names[i]);
      TypedFile f;
      if (dir instanceof WindowsRootDir) {
	f = getTypedFile(names[i]);
      } else {
	f = getTypedFile(dir.getPath(), names[i]);
      }
      
      FileType t = f.getType();
      if (debug)
	System.out.println("file "+f+" class "+f.getClass());
      if ((shownType == null || t.isContainer() || shownType == t)
	  && (hiddenRule == null || !hiddenRule.testFile(f))) {
	resultSet.addElement(f);
      }
    }
    
    // The fake windows root dir will get mangled by sorting
    if (!(dir instanceof DirectoryModel.WindowsRootDir)) {
      sort(resultSet);
    }
    
    if (useCache)
      currentFilesFresh = true;
    return resultSet;
  }
}

