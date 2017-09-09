package com.gensym.files;

import java.net.*;
import java.io.*;
import java.util.Vector;
import javax.swing.filechooser.*;

public class LocalFile extends URLFile
{
  private static Vector infos = new Vector();
  private static boolean isWindows 
    = System.getProperty("os.name").equals("Windows NT") ||
      System.getProperty("os.name").equals("Windows 95");
  private static FileSystemView oemFileSystemView 
    = FileSystemView.getFileSystemView();
  private static String[] windowsDrives;
  private File javaFile;
  private boolean isWindowsDriveList;
  private boolean isHardDrive;
  private boolean debug;

  public LocalFile(String path, FileType type)
  {    
    super(path,type);
    System.out.println("path "+path+" type "+type);
  }
  
  public LocalFile(String path, String name, FileType type)
  {
    super(path,name,type);
  }

  LocalFile(URL url)
  {
    super(url,null);
    inferFileType();
  }

  LocalFile()
  {
    super(null);
    inferFileType();
  }

  private void inferFileType()
  {
    if (isWindowsDriveList)
      setType(FileType.SharedComputer);
    else if (isHardDrive)
      setType (FileType.SharedHardDrive);
    else if (isDirectory())
      setType (FileType.SharedFolder);
    else
      setType(FileType.SharedGenericFile);
  }

  @Override
  protected void finishURLParsing()
  {
    String fileString = url.getFile().trim();
    if (debug)
      System.out.println("fileString = \""+fileString+"\"");
    if (isWindows && fileString.equals("/"))
      isWindowsDriveList = true;
    else if (isWindows)
      {
	fileString = fileString.substring(1);
	String firstPiece, tail;
	int slashIndex = fileString.indexOf("/");
	if (slashIndex == -1)
	  {
	    firstPiece = fileString;
	    tail = "";
	  }
	else
	  {
	    firstPiece = fileString.substring(0,slashIndex);
	    tail = fileString.substring(slashIndex);
	  }
	String driveName;
	int index = firstPiece.indexOf(':');
	if (index == -1)
	  index = firstPiece.indexOf('|');
	if (index == -1)
	  driveName = firstPiece;
	else
	  driveName = firstPiece.substring(0,index);
	String windowsFileSpec 
	  = driveName+":"+
	  (tail.equals("") ? "\\" : tail.replace('/','\\'));
	if (debug)
	  System.out.println("using windowsFileSpec \""+windowsFileSpec+
			     "\"");
	if (windowsFileSpec.length() == 3 &&
	    windowsFileSpec.charAt(1) == ':' &&
	    windowsFileSpec.charAt(2) == '\\')
	  isHardDrive = true;
	javaFile = new File(windowsFileSpec);
      }
    else
      {
	javaFile = new File(fileString);
      }
    // System.out.println(hashCode()+" done url parsing wdl "+isWindowsDriveList+
    // " jf "+javaFile);
  }
  
  @Override
  public String[] list()
  {
    if (isWindowsDriveList)
      {
	if (windowsDrives == null)
	  {
	    File[] devices = oemFileSystemView.getRoots();
	    Vector windowsDriveVector = new Vector();
	    for (int i = 0; i<devices.length; i++)
	      {
		char driveLetter = devices[i].getPath().charAt(0);
		// FloppyDisk existence checks are invoke "Abort/Ignore/Retry"
		// dialog on empty floppy drives
		if (driveLetter != 'A' && driveLetter != 'B') 
		  windowsDriveVector.addElement(driveLetter+":");
	      }
	    windowsDrives = new String[windowsDriveVector.size()];
	    windowsDriveVector.copyInto(windowsDrives);
	  }
	return windowsDrives;
      }
    else
      return javaFile.list();
  }

  @Override
  public boolean equals(Object o)
  {
    if (!isWindowsDriveList && javaFile == null)
      System.out.println("Bad Local File "+this);
    return 
      (o instanceof LocalFile) &&
      (isWindowsDriveList ? 
       ((LocalFile)o).isWindowsDriveList :
       javaFile.equals(((LocalFile)o).javaFile));
  }

  @Override
  public boolean isDirectory()
  {
    if (isWindowsDriveList)
      return true;
    else
      return javaFile.isDirectory();
  }

  @Override
  public boolean isFile()
  {
    if (isWindowsDriveList)
      return false;
    else
      return javaFile.isFile();
  }

  @Override
  public boolean isHidden() 
  {
    if (isWindowsDriveList)
      return false;
    else if (isWindows)
      return false; // let's boldly be wrong until we can assume JDK 1.2
    else
      {
	// In UNIX, filenames that start with a dot are "hidden",
	// although everyone seems to know about'em anyway.
	String filename = getName();
	if ("".equals(filename))
	  return true;
	return (filename.charAt(0) == '.');
      }
  }

  @Override
  public String getParent()
  {
    if (isWindowsDriveList)
      return "";
    else 
      {
	String path = getPath().substring(8); // length of "file:///"
	int index = path.lastIndexOf('/');
	if ((index == -1) || (index == (path.length() - 1)))
	  return "file:///";
	else
	  return "file:///"+path.substring(0,index);
      }
  }

  @Override
  public boolean mkdir()
  {
    if (isWindowsDriveList)
      return false;
    else
      return javaFile.mkdir();
  }

  @Override
  public String getPath()
  {
    if (isWindowsDriveList)
      return "file:///";
    else if (isWindows)
      {
	String path = javaFile.getAbsolutePath();
	int index = path.indexOf('\\');
	if (index == -1)
	  return "file:///";
	else
	  return "file:///"+path.substring(0,index-1)+
	         path.substring(index).replace('\\','/');
      }
    else
      return "file:///"+javaFile.getAbsolutePath();
  }

  public static LocalFile makeLocalFile(String path)
  {
    try {
       return new LocalFile(new URL(path));
    } catch (MalformedURLException e)
      {
	System.out.println("malformed url "+e.getMessage());
	e.printStackTrace();
	throw new URLFileParseException("Bad url: "+path);
      }
  }

  @Override
  public String getName()
  {
    if (isWindowsDriveList ||
	url.getFile().equals("/"))
      return "file:///";
    else
      return javaFile.getName();
      
  }

  @Override
  public String toString()
  {
    return "<LocalFile: "+getPath()+">";
  }

  @Override
  public InputStream getInputStream()
       throws IOException
  {
    if (isWindowsDriveList)
      throw new IOException("unsupported operation");
    else
      return new FileInputStream(javaFile);
  }

  @Override
  public Object getContents()
  {
    return null;
  }

  @Override
  public boolean canRead()
  {
    if (isWindowsDriveList)
      return false;
    else
      return javaFile.canRead();
  }

  @Override
  public boolean canWrite()
  {
    if (isWindowsDriveList)
      return false;
    else
      return javaFile.canWrite();
  }

  @Override
  public OutputStream getOutputStream()
       throws IOException
  {
    if (isWindowsDriveList)
      throw new IOException("unsupported operation");
    else
      return new FileOutputStream(javaFile);
  }

}
