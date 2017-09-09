package com.gensym.beaneditor;

import java.io.*;
import java.util.*;

public class G2Manifest
{
  private Vector entries = new Vector(); // list of headers that all pertain to a file

  public G2Manifest()
  {
  }

  public G2Manifest(byte[] bytes) throws IOException
  {
    this(new ByteArrayInputStream(bytes));
  }

  /**
   * Parse a manifest from a stream
   */

  public G2Manifest(InputStream is) throws IOException
  {
    while (is.available() != 0)
      {
	G2MessageHeader m = new G2MessageHeader(is);
	entries.addElement(m);
      }
  }

  /* recursively generate manifests from directory tree */
  public G2Manifest(String[] files) throws IOException
  {
    G2MessageHeader globals = new G2MessageHeader();
    globals.add("Manifest-Version", "1.0");
    addEntry(globals);
    addFiles(null, files);
  }

  public void addEntry(G2MessageHeader entry)
  {
    entries.addElement(entry);
  }

  public G2MessageHeader getEntry(String name)
  {
    Enumeration enumeration = entries();
    while(enumeration.hasMoreElements())
      {
	G2MessageHeader mh = (G2MessageHeader)enumeration.nextElement();
	String nameVal = mh.findValue("Name");
	if (nameVal != null && nameVal.equals(name))
	  {
	    return mh;
	  }
      }
    return null;
  }

  public G2MessageHeader entryAt(int i)
  {
    return (G2MessageHeader) entries.elementAt(i);
  }

  public Enumeration entries()
  {
    return entries.elements();
  }
	
  public void addFiles(File dir, String[] files) throws IOException
  {
    if (files == null)
      return;
    for (int i = 0; i < files.length; i++)
      {
	File file;
	if (dir == null)
	  {
	    file = new File(files[i]);
	  }
	else
	  {
	    file = new File(dir, files[i]);
	  }
	if (file.isDirectory())
	  {
	    addFiles(file, file.list());
	  }
	else
	  {
	    addFile(file);
	  }
      }
  }

  public void addFile(File f) throws IOException
  {
    G2MessageHeader mh = new G2MessageHeader();
    mh.add("Name", f.getPath());
    addEntry(mh);
  }

  /** Add a manifest file at current position in a stream
   */

  public void stream(OutputStream os, Vector extraFiles) throws IOException
  {

    /** the first header in the file should be the global one.
     *  It should say "Manifest-Version: x.x"; barf if not
     */

    G2MessageHeader globals = (G2MessageHeader) entries.elementAt(0);

    if (globals.findValue("Manifest-Version") == null)
      {
	throw new IOException("Manifest file requires " +
			      "Manifest-Version: 1.0 in 1st header");
      }

    PrintWriter ps = new PrintWriter(os);
    globals.print(ps);

    for (int i = 1; i < entries.size(); ++i)
      {
	G2MessageHeader mh = (G2MessageHeader) entries.elementAt(i);
	mh.print(ps);

	/* REMIND: could be adding files twice!!! */
	String name = mh.findValue("name");
	if (extraFiles != null && name != null)
	  {
	    extraFiles.addElement(name);
	  }
      }
  }

  public static boolean isManifestName(String name)
  {
	
    // remove leading /
    if (name.charAt(0) == '/')
      {
	name = name.substring(1, name.length());
      }

    // case insensitive
    name = name.toUpperCase();
	
    if (name.equals("META-INF/MANIFEST.MF"))
      {
	return true;
      }

    return false;
  }

						  
}
