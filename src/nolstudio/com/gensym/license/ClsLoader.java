package com.gensym.license;

import java.io.*;
import java.util.Hashtable;
import java.util.StringTokenizer;
import java.util.Vector;
import java.util.Enumeration;
import java.util.zip.*;

public class ClsLoader extends ClassLoader {
  private native Class bytesToClass(String name, byte[] b);
  private Hashtable table = new Hashtable();
  private int pathLength;
  private String[] classPath;
  private String mainClass;
  private static boolean DEBUG = false;

  static {
	  System.loadLibrary("jlt");
	  if(DEBUG) System.out.println("Loaded library OK");
  }

  public ClsLoader(String mainName) {
	  super();
	  mainClass = mainName;
	  buildClassPath();
  }

  @Override
  public java.net.URL getResource(String name) {
	// No special behavior from this class loader, use system class loader method
	  return ClassLoader.getSystemResource(name);
  }

  @Override
  public InputStream getResourceAsStream(String name) {
	return ClassLoader.getSystemResourceAsStream(name);
  }

  @Override
  public final Class loadClass(String name) throws ClassNotFoundException {
	  return loadClass(name,true);
  }

  @Override
  protected final Class loadClass(String name, boolean resolve) throws ClassNotFoundException {
	  if(DEBUG) System.out.println("In ClsLoader.loadClass, loading "+name);
	  // first try to use the default loader, but NEVER use the
	  // default loader on the main class
	  if(!name.equals(mainClass)) {
		  try {
		      Class systemClass = findSystemClass(name);
			  if (systemClass!=null) return systemClass;
		  } catch (Throwable t) {
			  if(DEBUG) System.out.println("findSystemClass did not find "+name);
		  }
	  }
	  Class c = (Class) table.get(name);
	  if (c != null) return c;
      // Now use our own loader to handle remaining classes
	  // Search for .cls files first (more efficient, since most of
	  // our classes will be encoded), then search for .class files,
	  // in case there are any unencrypted files
	  byte[] data;
	  if(DEBUG) System.out.println("Looking for .cls file for "+name);
	  data = getBytes(name,".cls");
	  if (data != null) {
          if(DEBUG) System.out.println("Got "+data.length+" bytes from .cls file for class " + name);
          try {
			 //if(DEBUG) System.out.println("Mangled name is "+name.replace('.','/'));
			 // peculiarity in JNI DefineClass wants qualified name with "/", not "."
			 c = bytesToClass(name.replace('.','/'),data);   // native method
			 if(DEBUG) System.out.println("returned OK from bytesToClass, class "+name);
		     table.put(name,c);
		     return c;
		  } catch (UnsatisfiedLinkError e) {
			 if(DEBUG) {
				 System.out.println("Could not find jlt.dll in path, error = "+e.getMessage());
				 e.printStackTrace();
			 }
			 throw e;
		  } catch (Throwable e) {
			 //System.err.println("exception: " + e.getMessage());
             //e.printStackTrace();
			 //System.exit(1);
			 if(DEBUG) {
				 System.out.println("In ClsLoader error trap, JLT declined to load class "+name+", error = "+e.getMessage());
				 e.printStackTrace();
			 }
			 throw new ClassNotFoundException(name);
		  }

	  } else {
		  // .cls file not found, try for .class
		  if(DEBUG) System.out.println("Attempting to find .class file for "+name);
		  c = findSystemClass(name);
		  if (c!=null){
			  table.put(name,c);
			  if(DEBUG) System.out.println("Loaded "+name+" via findSystemClass");
			  return c;
		  }
		  data = getBytes(name,".class");
		  if(data != null){
			  if(DEBUG) System.out.println("Got "+data.length+" unencrypted bytes for class "+name);
			  c=defineClass(name,data,0,data.length);
			  table.put(name,c);
			  return c;
		  }else{
			  if(DEBUG) System.out.println("Class "+name+" cannot be found on CLASSPATH");
			  throw new ClassNotFoundException(name);
		  }
	  }
  }

  private final void buildClassPath() {
	  StringTokenizer tokenizer = new StringTokenizer(System.getProperty("java.class.path"), System.getProperty("path.separator"));
	  pathLength = tokenizer.countTokens();
	  classPath = new String[pathLength];
	  for (int i=0; i<pathLength ; i++) classPath[i] = tokenizer.nextToken();
  }

  private final byte[] getBytes(String qualifiedName, String extension) {
	  // Get the bytes for this class
	  if(DEBUG) System.out.println("qualifiedName=" + qualifiedName + " extension=" + extension);
	  String fileSeparator = System.getProperty("file.separator");
	  String pathEntry = "";
	  byte[] b = null;
	  int i;
	  for (i=0; i<pathLength ; i++) {
		try {
		  pathEntry = classPath[i];
		  //if(DEBUG) System.out.println("pathEntry = " + pathEntry);
		  if(pathEntry.endsWith(".jar") || pathEntry.endsWith(".zip")) {
			  ZipFile zipFile = new ZipFile(pathEntry);
			  String archiveFileName = makeFileName(qualifiedName,extension,true);
			  //if(DEBUG) System.out.println("archiveFileName = " + archiveFileName);
///////////////////////			
/*			  Enumeration e = zipFile.entries();
			  while(e.hasMoreElements()) {
				ZipEntry ze = (ZipEntry)e.nextElement();
				String zeName = ze.getName();
				if((zeName.indexOf(qualifiedName)) > 0)
					System.out.println("Found it---" + zeName);
			  }*/
//////////////////////
			  ZipEntry zipEntry = zipFile.getEntry(archiveFileName);
			  if (zipEntry != null) {
				  if(DEBUG) { 
					  System.out.println("Zip Entry not null, and name = " + zipEntry.getName());	
					  System.out.println(dumpZipEntry(zipEntry));
				  }
				  InputStream in = zipFile.getInputStream(zipEntry);
				  int length = (int) zipEntry.getSize();
				  if(length!=-1) b = readBytes(in,length);
				  else b = readBytes(in);
				  zipFile.close();
				  in.close();
				  break;
			  }
		  } else {
			  String classFileName = makeFileName(qualifiedName,extension,false);
			  String fullClassFileName = pathEntry+fileSeparator+classFileName;
			  File classFile = new File(fullClassFileName);
			  if (classFile.exists()) {
				  FileInputStream fis = new FileInputStream(classFile);
				  b = readBytes(fis,(int) classFile.length());
				  fis.close();
				  break;
			  }
		  }
		} catch(Exception e) {// eat it and keep looking
		}
	  }
	  // to make loading faster in the future, put pathEntry at the front
	  // of classPath.  This is the most likely place to look, next time.
	  if (b!=null && i!=0) {
          String hold = classPath[0];
          classPath[0] = pathEntry;
		  classPath[i] = hold;
	  }
	  return b;
  }

   /**
   ** Dumps a zip entry into a string.
   **
   ** @param ze a ZipEntry
   **/
   private String dumpZipEntry(ZipEntry ze) {
       StringBuffer sb=new StringBuffer();
       if (ze.isDirectory()) {
          sb.append("d "); 
       } else {
          sb.append("f "); 
       }
       if (ze.getMethod()==ZipEntry.STORED) {
          sb.append("stored   "); 
       } else {
          sb.append("deflated ");
       }
       sb.append(ze.getName());
       sb.append("\t");
       sb.append(""+ze.getSize());
       if (ze.getMethod()==ZipEntry.DEFLATED) {
          sb.append("/"+ze.getCompressedSize());
       }
       return (sb.toString());
   }


  private static final byte[] readBytes(InputStream is, int nbytes) throws IOException {
	  byte[] b = new byte[nbytes];
	  is.read(b);
	  return b;
  }

  private static final byte[] readBytes(InputStream is) throws IOException {
	  // reads the input stream and creates a byte array of the contents
	  // If the number of bytes is known, use getBytes(is, long)
    int len = 0;
	Vector vec = new Vector(0,10);
	Vector howmany = new Vector(0,10);
	int chunk = 512;
    byte[] b;
    for (;;) {
		b = new byte[chunk];
		int r = is.read(b);
		if (r < 0) break;
		len += r;
		vec.addElement(b);
		howmany.addElement(new Integer(r));
    }
	// form one big byte array
	byte[] bb = new byte[len];
	int m = 0;
	for(int i=0;i<vec.size();i++) {
		b = (byte[]) vec.elementAt(i);
		int n = ((Integer) howmany.elementAt(i)).intValue();
		System.arraycopy(b,0,bb,m,n);
		m+=n;
	}
    return bb;
  }

  private static final String makeFileName(String qualifiedName,String extension, boolean forArchive) {
	  StringBuffer buffer = new StringBuffer();
	  StringTokenizer tokenizer = new StringTokenizer(qualifiedName,".");
	  String fileSeparator  = forArchive ? "/" : System.getProperty("file.separator");
	  int pathSize = tokenizer.countTokens();
	  for (int i = 0; i<pathSize ; i++) {
		  if (i > 0) buffer.append(fileSeparator);
		  buffer.append(tokenizer.nextToken());
	  }
	  buffer.append(extension);
	  return buffer.toString();
  }
}
