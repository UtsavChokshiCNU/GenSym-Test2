package com.gensym.ntw.files;

import com.gensym.jgi.G2Access;
import com.gensym.jgi.G2AccessException;

import com.gensym.classes.TextList;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.message.Trace;
import com.gensym.files.*;

import java.io.*;
import java.util.Vector;
import java.util.StringTokenizer;
import java.net.*;

public class G2ServerFile extends G2ConnectionFile
{
  private Vector location;
  private String filename;


  public G2ServerFile(String path, FileType type)
  {
    super(path,type);
  }
  
  public G2ServerFile(String path, String name, FileType type)
  {
    super(path,name,type);
  }

  G2ServerFile(URL url, FileType type) {
    super(url, type);
  }
  
  G2ServerFile(URL url)
  {
    super(url);
  }
  
  // PPrintz 02/28/02
  // Added as suggested by Bug Id  4432834 from Sun
  // The problem is that when double clicking on a directory with
  // G2 6.1 and jre 1.3.1 the directory is selected as a valid file
  // instead of drilling to the subdirectory and displaying the files.
  // As a consequence, we generate an error message since G2 cannot
  // load directories (!). This is very annoying for users since
  // everybody is double clicking on directories and expects to see
  // the files in the subdirectory instead of an error message.

  // yduJ followup: We considered putting this on G2ConnectionFile
  // instead, on the grounds that other classes which inherit from it
  // might have the same problem, but we were concerned about fanout.
  // We should consider this if we ran into a similar problem with
  // other inheritors.

  @Override
  public File getCanonicalFile() throws IOException {
      return new G2ServerFile(super.getCanonicalPath(), null);
  }

  @Override
  protected void finishURLParsing()
  {
    String rawFilename = url.getFile();
    StringTokenizer tokenizer = new StringTokenizer (rawFilename, "/", false);
    location = new Vector ();
    while (tokenizer.hasMoreTokens ()) {
      String token = tokenizer.nextToken ();
      location.addElement (token);
    }
    if (URLFile.debug)
      System.out.println("SFS URL parse raw=("+rawFilename+
			 ") parse = "+location);
    if ((location.size() < 1) ||
	!location.elementAt(0).equals("serverFileSystem"))
      throw new URLFileParseException("Bad Server File Specification");
    if (rawFilename.equals("/serverFileSystem"))
      filename = "/";
    else
      filename = rawFilename.substring(17);
    location.removeElementAt(0);
  }

  @Override
  public boolean isDirectory()
  {
    try {
      return getType().isContainer();
    } catch (TypeNotSetException tnse) {
      if (URLFile.debug) {
       System.out.println("CALLING IS DIRECTORY FOR " + this);
       Thread.dumpStack();
      }
      return g2DirectoryExists(filename) &&  g2FileIsDirectory(filename);
    }
  }

  @Override
  public boolean isFile()
  {
    return !isDirectory();
  }

  @Override
  public File[] listFiles() {
    String parentPath = getPath();
    if ((location.size() == 0) && g2FileSystemIsWindows()){
      Sequence contents = g2DevicesOnMachine();
      return makeFiles(parentPath,contents, contents);
    } else {
      Sequence contents = g2FilesInDirectory(filename);
      if (contents == null)  
	return new File[0];
      Vector directories = null;
      try {
	directories = getSubDirectoriesInDirectory(filename);
      } catch (G2AccessException g2ae) {
	Trace.exception(g2ae);
	directories = new Vector();
      }
      return makeFiles(parentPath,contents, directories);
    }
  }

  @Override
  public boolean supportsListFiles() {
    return true;
  }

  private String makeFullPath(String parentPath, String fileName) {
    String separator = "/";
    if (parentPath.equals("") ||
	parentPath.charAt(parentPath.length()-1) == '/')
      separator = "";
    return parentPath+separator+fileName;
  }

  private File[] makeFiles(String parentPath,
			   Vector fileAndDirectoryStrings,
			   Vector directoryStrings)
  {
    int count = 0;
    if (fileAndDirectoryStrings != null)
      count = fileAndDirectoryStrings.size();
    File[] files = new File[count];
    for(int i=0;i<count;i++) {
      String fileString = (String)fileAndDirectoryStrings.elementAt(i);
      boolean isDirectory = false;
      if (directoryStrings != null && fileString != null)
        isDirectory = directoryStrings.contains(fileString);
      fileString = makeFullPath(parentPath, fileString);
      FileType type;
      if (isDirectory)
	type = FileType.SharedFolder;
      else
	type = FileType.SharedGenericFile;    
      URLFile file = G2File.makeG2File(fileString, type);
      files[i]=file;
    }
    return files;
  }
  
  @Override
  public String[] list() {
    if (isDirectory()) {
      if ((location.size() == 0) && g2FileSystemIsWindows()){
	Sequence contents = g2DevicesOnMachine();
	String[] names = new String[contents.size()];
	contents.copyInto(names);
	return names;
      } else {
	Sequence contents = g2FilesInDirectory(filename);
	String[] names = new String[contents.size()];
	contents.copyInto(names);
	return names;
      }
    } else
      return new String[0];
  }
  
  @Override
  void dumpInfo()
  {
    System.out.println("server file: "+filename);
  }

  @Override
  public String getParent()
  {
    int i, size = location.size();
    String root = "g2://"+url.getHost()+":"+url.getPort()+"/serverFileSystem";
    if (size == 0) 
      return "g2://"+url.getHost()+":"+url.getPort()+"/";
    else
      {
	StringBuffer buffer = new StringBuffer(root);
	for (i=0; i<(size - 1) ; i++)
	  {
	    buffer.append("/");
	    buffer.append(location.elementAt(i).toString());
	  }
	if (URLFile.debug)
	  System.out.println("getParent "+filename+
			     " parent "+buffer.toString());
	return buffer.toString();
      }
  }

  @Override
  public String getName()
  {
    if (location.size() == 0)
      return "serverFileSystem";
    else
      {
	if (URLFile.debug)
	  System.out.println("SFS getName loc size = "+location.size()+
			     " loc elts "+location);
	return (String) location.lastElement();
      }
  }
    
  @Override
  public String toString()
  {
    if (url == null)
      return "<G2ServerFile>";
    else
      return "<G2ServerFile @ \""+url.toExternalForm()+"\">";
  }

  @Override
  public InputStream getInputStream()
  {
    return null;
  }

  @Override
  public Object getContents()
  {
    return null;
  }

  @Override
  public boolean canRead()
  {
    return isFile();
  }

  @Override
  public boolean canWrite()
  {
    return isFile();
  }

  @Override
  public OutputStream getOutputStream()
       throws IOException
  {
    return null;
  }

  // package private low-level access

  private static final Symbol g2ChangeDefaultDirectory_
    = Symbol.intern ("G2-CHANGE-DEFAULT-DIRECTORY");
  private static final Symbol g2DefaultDirectory_
    = Symbol.intern ("G2-DEFAULT-DIRECTORY");
  private static final Symbol g2DevicesOnMachine_
    = Symbol.intern ("G2-DEVICES-ON-MACHINE");
  private static final Symbol g2DirectoryExists_
    = Symbol.intern ("G2-DIRECTORY-EXISTS");
  private static final Symbol g2DiskSpaceAvailableInDirectory_
    = Symbol.intern ("G2-DISK-SPACE-AVAILABLE-IN-DIRECTORY");
  private static final Symbol g2FilesInDirectory_
    = Symbol.intern ("G2-FILES-IN-DIRECTORY");
  private static final Symbol g2SubdirectoriesInDirectory_
    = Symbol.intern ("G2-SUBDIRECTORIES-IN-DIRECTORY");

  private static final Symbol g2FileExists_
    = Symbol.intern ("G2-FILE-EXISTS");
  private static final Symbol g2TypeOfFileSystem_
    = Symbol.intern ("G2-TYPE-OF-FILE-SYSTEM");

  private static final Symbol dos_ = Symbol.intern("DOS");
  private static final Symbol win32_ = Symbol.intern("WIN32");

  Sequence g2DevicesOnMachine()
  {
    try {
      G2Access connection = getConnection();
      TextList list = (TextList) connection.callRPC(g2DevicesOnMachine_, new Object[0]);
      Sequence s = list.getG2ListSequence();
      s.removeElement("A:"); // wild hack
      s.removeElement("B:"); // but so is Windows!!
      if (URLFile.debug)
	System.out.println("SFS devices: "+s);
      return s;
    }
    catch (G2AccessException e)
      {
	Trace.exception(e);
	return null;
      }
  }

  Sequence g2FilesInDirectory(String directoryName)
  {
    try {
      directoryName = nativize(directoryName);
      if (g2FileSystemIsWindows() &&
	  (directoryName.length() > 0) &&
	  (directoryName.charAt(directoryName.length() - 1) != '\\'))
	directoryName = directoryName + "\\";
      G2Access connection = getConnection();
      TextList list = (TextList) connection.callRPC(g2FilesInDirectory_,
						    new Object[] { directoryName });
      Sequence res = list.getG2ListSequence();
      if (URLFile.debug)
	System.out.println("SFS ("+directoryName+") = "+res);
      return res;
    }
    catch (G2AccessException e)
      {
	Trace.exception(e);
	return null;
      }
  }

  // Here:
  // implement getters for input and output streams

  boolean g2DirectoryExists(String directoryName)
  {
    try {
      directoryName = nativize(directoryName);
      if ((directoryName.length() == 3 ||
	   directoryName.length() == 2) &&
	  directoryName.charAt(1) == ':' &&
	  g2FileSystemIsWindows())
	return true; // dumb-ass device heuristic
      G2Access connection = getConnection();
      Boolean b = (Boolean) connection.callRPC(g2DirectoryExists_,
					       new Object[] { directoryName });
      if (URLFile.debug)
	System.out.println("SFS directory exists ("+directoryName+") = "+b);
      return b.booleanValue();
    }
    catch (G2AccessException e)
      {
	Trace.exception(e);
	return false;
      }
  }

  boolean g2FileExists(String fileName)
  {
    try {
      fileName = nativize(fileName);
      G2Access connection = getConnection();
      Boolean b = (Boolean) connection.callRPC(g2FileExists_,
					       new Object[] { fileName });
      if (URLFile.debug)
	System.out.println("SFS file exists ("+fileName+") = "+b);
      return b.booleanValue();
    }
    catch (G2AccessException e)
      {
	Trace.exception(e);
	return false;
      }
  }

  private Sequence getSubDirectoriesInDirectory(String directoryName)
       throws G2AccessException
  {
    try {
      directoryName = nativize(directoryName);
      if (g2FileSystemIsWindows() &&
	  (directoryName.length() > 0) &&
	  (directoryName.charAt(directoryName.length() - 1) != '\\'))
	directoryName = directoryName + "\\";
      G2Access connection = getConnection();
      TextList list = (TextList)connection.callRPC(g2SubdirectoriesInDirectory_,
						   new Object[] { directoryName });
      Sequence res = list.getG2ListSequence();
      if (URLFile.debug)
	System.out.println("SFS ("+directoryName+") = "+res);
      return res;
    } catch (G2AccessException e) {
      Trace.exception(e);
      return null;
    }
  }
  
  boolean g2FileIsDirectory(String filename)
  {
    try {
      filename = nativize(filename);
      if ((filename.length() == 3 ||
	   filename.length() == 2) &&
	  filename.charAt(1) == ':' &&
	  g2FileSystemIsWindows())
	return true; // dumb-ass device heuristic
      getSubDirectoriesInDirectory(filename);
      // will error if not directory
      return true;
    }
    catch (G2AccessException e)
      {
	// Trace.exception(e);
	return false;
      }
  }

  boolean g2FileSystemIsWindows()
  {
    try
      {
	G2Access connection = getConnection();
	Symbol fileSystem 
	  = (Symbol) connection.callRPC(g2TypeOfFileSystem_, new Object[0]);
	// will error if not directory
	return fileSystem.equals(win32_) || fileSystem.equals(dos_);
      }
    catch (G2AccessException e)
      {
	// Trace.exception(e);
	return false;
      }
  }

  private String nativize(String filename)
  {
    boolean windoze = g2FileSystemIsWindows();
    int len = filename.length();
    if (len > 0 &&
	filename.charAt(0) == '/' &&
	windoze)
      filename = filename.substring(1);
    return filename.replace('/',(windoze ? '\\' : '/'));
  }
  
}
