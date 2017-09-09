/*
 * JarFile
 */

package com.gensym.jartools;
import java.io.*;
import java.util.zip.*;

/**
 * 
 */
public class JarFile extends Bucket
{
	private String fileName=null;

	/**
	 * Creates a JarFile with no content.
	 */
	public JarFile()
	{
		super();
	}

	/**
	 * Creates a Jar with the content of a jar file.
	 * @param pfileName Name of jar file.
	 * @exception	IOException		May be thrown when
	 *						reading from the jar file.
	 *
	 * @exception	ZipException 	May be thrown when
	 *						processing the contents of the
	 *						jar file.
	 */
	public JarFile(String pfileName)
		throws IOException, ZipException
	{
		super(new FileInputStream(pfileName));
		fileName=pfileName;
	}

	/**
	 * Write the Jar contents to a jar file.
	 *
	 * @param pfileName Name of jar file.
	 *
	 * @exception	IOException		May be thrown when
	 *						writting to the jar file.
	 *
	 * @exception	ZipException 	May be thrown when
	 *						processing the contents of the
	 *						jar file.
	 */
	public void saveAs(String pfileName)
		throws IOException, ZipException
	{
		fileName=pfileName;
		jar(new FileOutputStream(pfileName));
	}

	/**
	 * Update the jar file.
	 *
	 * @exception	IOException		May be thrown when
	 *						writting to the jar file.
	 *
	 * @exception	ZipException 	May be thrown when
	 *						processing the contents of the
	 *						jar file.
	 */
	public void save()
		throws IOException, ZipException
	{
		saveAs(fileName);
	}

	/**
	 * Put a file in the Jar.
	 * @param pfileName Name of the file to be put in the Jar.
	 * @exception IOException May be thrown when reading the file.
	 */
	public void putFile(String pfileName)
		throws IOException
	{
        putFile(pfileName,pfileName);
	}

	// modified to take boolean flag for bean
		public void putFile(String pfileName , boolean isBean)
		throws IOException
	{
        putFile(pfileName,pfileName,isBean);
	}


	/**
	 * Put a file in the Jar.
	 * @param pfileName Name of the file to be read.
	 * @param as Name of the file added to the Jar.
	 * @exception IOException May be thrown when reading the file.
	 */
	public void putFile(String pfileName, String as)
		throws IOException
	{
		File file=new File(pfileName);
		long modified=file.lastModified();
		InputStream is=new FileInputStream(file);
		String name=as.replace('\\','/');
		byte value[]=Reads.read(is);
		is.close ();
		put(name,value,modified);
		if (!name.equals(MANIFEST_NAME)){
			manifest.force(name).addHash(value);
		}
	}


	/**
	 * Put a file in the Jar.
	 * @param pfileName Name of the file to be read.
	 * @param as Name of the file added to the Jar.
	 * @param isBean Mark this file as a Java bean
	 * @exception IOException May be thrown when reading the file.
	 */
	public void putFile(String pfileName, String as , boolean isBean)
	throws IOException
	{
		File file=new File(pfileName);
		long modified=file.lastModified();
		InputStream is=new FileInputStream(file);
		String name=as.replace('\\','/');
		byte value[]=Reads.read(is);
		is.close ();
		put(name,value,modified);
		if (!name.equals(MANIFEST_NAME)){
			manifest.force(name,isBean).addHash(value);
		}
	}

  public ManifestSection getManifestSection(String name) {
    String testName = name.replace('\\','/');
    return manifest.get(testName);
  }
}
