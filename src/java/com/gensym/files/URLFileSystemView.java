package com.gensym.files;

import java.util.Vector;
import java.net.URL;
import java.io.File;
import java.io.IOException;
import javax.swing.filechooser.*;

public class URLFileSystemView extends FileSystemView
{  
  URLDirectoryModel directoryModel; 

  public URLFileSystemView(URLDirectoryModel directoryModel)
  {
    this.directoryModel = directoryModel;
  }

  @Override
  public boolean isRoot(File f)
  {
    if (f instanceof ProtocolsFile)
      return true;
    else
      return false;
  }

  @Override
  public File createNewFolder(File containingDir) 
       throws IOException
  {
    System.out.println("New Folder is not yet implemented");
    throw new IOException("New Folder is not yet implemented");
  }

  @Override
  public boolean isHiddenFile(File f)
  {
    if (f instanceof URLFile)
      return ((URLFile)f).isHidden();
    else
      return false;
  }

  @Override
  public File[] getRoots()
  {
    return directoryModel.getRoots();
  }
  
  // the following is unmodified from the parent abstract class
  @Override
  public File getHomeDirectory() 
  {
    return createFileObject( directoryModel.useLocalFileSystem ? "file:///"+
			     System.getProperty("user.dir").replace('\\','/') : "");
  }
  
  @Override
  public File createFileObject(File dir, String filename)
  {
    File res;
    if (dir == null)
      res = directoryModel.getTypedFile(filename);
    else
      res = directoryModel.getTypedFile(dir.getPath(), filename);
    if (URLFile.debug)
      System.out.println("createFileObject("+dir+", \""+filename+"\") -> "+res);
    return res;
  }
  
  @Override
  public File createFileObject(String path) 
  {
    if (URLFile.debug)
      System.out.println("<pre-call> createFileObject(\""+path+"\"");
    File res;
    try 
      {
	res = directoryModel.getTypedFile(path);
      } catch (URLFileParseException ufpe)
	{
	  if (URLFile.debug)
	    System.out.println("making BadURLFile");
	  res = new BadURLFile(path);
	}
    if (URLFile.debug)
      System.out.println("createFileObject(\""+path+"\") -> "+res);
    return res;
  }
  
  @Override
  public File[] getFiles(File dir, boolean useFileHiding) 
  {
    // add all files in dir
    
    if (dir instanceof URLFile &&
	((URLFile)dir).supportsListFiles()) {
      File [] fls = dir.listFiles();
      if (useFileHiding) {
	Vector filteredFiles = new Vector();
	for (int i=0;i<fls.length;i++) {
	  File file = fls[i];
	  if (!isHiddenFile(file))
	    filteredFiles.addElement(file);
	}
	fls = new File[filteredFiles.size()];
	filteredFiles.copyInto(fls);
      }
      return fls;
    }

    Vector files = new Vector();    
    String[] names = dir.list();
    File f;
    
    int nameCount = names == null ? 0 : names.length;
    
    for (int i = 0; i < nameCount; i++) {
      f = createFileObject(dir, names[i]);
      if(useFileHiding) {
	if(!isHiddenFile(f)) {
	  files.addElement(f);
	}
      } else {
	files.addElement(f);
      }
    }
    
    File[] fileArray = new File[files.size()];
    files.copyInto(fileArray);
    
    return fileArray;
  }
  
  @Override
  public File getParentDirectory(File dir) 
  {
    if(dir != null) 
      {
	String parentPath = dir.getParent();
	if (parentPath == null)
	  return null;
	else
	  return directoryModel.makeFileFromPath(parentPath);
      }
    else
      return null;
  }

}

