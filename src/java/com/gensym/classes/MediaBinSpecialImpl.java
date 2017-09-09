package com.gensym.classes;

import com.gensym.jgi.G2Access;
import com.gensym.jgi.G2Gateway;
import com.gensym.util.*;
import com.gensym.message.*;
import java.io.IOException;
import java.util.Vector;

public class MediaBinSpecialImpl extends ItemImpl
{
  static boolean initialized = false;
  private static int MediaBinTimeout = 0; // indefinite

  public static final int INPUT = 0;
  public static final int OUTPUT = 1;
  private static Symbol[] directions
    = { Symbol.intern("INPUT"), Symbol.intern("OUTPUT") };

  public static final int TEXT = 0;
  public static final int BINARY = 1;
  private static Symbol[] fileTypes
    = { Symbol.intern("TEXT") , Symbol.intern("BINARY") };

  public static final int CREATE_OVERWRITE = 0;
  public static final int READ_SHARED = 1;
  private static Symbol[] modes
    = { Symbol.intern("CREATE-OR-OVERWRITE"), Symbol.intern("READ-SHARED") };

  private static Symbol g2_media_bin_open_stream_
    = Symbol.intern("G2-MEDIA-BIN-OPEN-STREAM");
  private static Symbol g2_media_bin_close_stream_
    = Symbol.intern("G2-MEDIA-BIN-CLOSE-STREAM");
  private static Symbol g2_media_bin_write_
    = Symbol.intern("G2-MEDIA-BIN-WRITE");
  private static Symbol g2_media_bin_read_ 
    = Symbol.intern("G2-MEDIA-BIN-READ");
  private static Symbol g2_media_bin_make_directory_
    = Symbol.intern("G2-MEDIA-BIN-MAKE-DIRECTORY");
  private static Symbol g2_media_bin_describe_
    = Symbol.intern("G2-MEDIA-BIN-DESCRIBE");
  private static Symbol g2_media_bin_delete_
    = Symbol.intern("G2-MEDIA-BIN-DELETE");
  private static Symbol g2_media_bin_set_ignore_last_byte_
    = Symbol.intern("G2-MEDIA-BIN-SET-IGNORE-LAST-BYTE");
  private static Symbol g2_media_bin_ignore_last_byte_
    = Symbol.intern("G2-MEDIA-BIN-IGNORE-LAST-BYTE");

  public MediaBinSpecialImpl(ItemImpl mediaBin)
  {
    super (mediaBin.getContext (), mediaBin.getHandle (), null, null);

    if (!initialized)
      initializeRPCs();
  }

  private void initializeRPCs()
  {
    initialized = true;
  }

  public int openStream(Vector path, String name, int direction,
			int fileType, int mode)
       throws IOException
  {
    if (direction < INPUT || direction > OUTPUT)
      throw new IOException("Bad IODirction");
    if (fileType < TEXT || fileType > BINARY)
      throw new IOException("Unknown File Type");
    if (mode < CREATE_OVERWRITE || mode > READ_SHARED)
      throw new IOException("Unknown Media File mode");
    java.lang.Object[] args = new java.lang.Object[6];
    args[0] = this;
    args[1] = makeSequence(path);
    args[2] = name;
    args[3] = directions[direction];
    args[4] = fileTypes[fileType];
    args[5] = modes[mode];
    Integer retnvalue 
      = (Integer) callRPCNormalizingExceptions
                   (g2_media_bin_open_stream_ , args);
    return retnvalue.intValue();
  }

  public G2BinaryOutputStream makeBinaryOutputStream(Vector path, String name)
       throws IOException
  {
    int fd = openStream(path,name,OUTPUT,BINARY,CREATE_OVERWRITE);
    return new G2BinaryOutputStream((MediaBin)this,fd);
  }

  public G2BinaryInputStream makeBinaryInputStream(Vector path, String name)
       throws IOException
  {
    int fd = openStream(path,name,INPUT,BINARY,READ_SHARED);
    return new G2BinaryInputStream((MediaBin)this,fd);
  }

  private Sequence makeSequence(Vector vector)
  {
    int len = vector.size();
    Sequence sequence = new Sequence(len);
    for (int i = 0 ; i<len ; i++)
      sequence.addElement(vector.elementAt(i));
    return sequence;
  }

  private java.lang.Object callRPCNormalizingExceptions(Symbol rpcName,
					      java.lang.Object[] args)
       throws IOException
  {
    java.lang.Object result = null;
    try {
      result = getContext().callRPC(rpcName, args);
    } catch (Exception e)
      {
	throw new IOException("Re-thrown Exception original was "+
			      e.getClass().getName()+" with message: "+
			      e.getMessage());
      }
    return result;
  }

  public void closeStream(int fileDescriptor)
       throws IOException
  {
    java.lang.Object[] args = new java.lang.Object[3];
    args[0] = this;
    args[1] = new Integer(fileDescriptor);
    args[2] = new Boolean(false);
    Boolean result = (Boolean) callRPCNormalizingExceptions
      ( g2_media_bin_close_stream_ , args);
  }

  public void write(int fileDescriptor, char[] data)
       throws IOException
  {
    java.lang.Object[] args = new java.lang.Object[3];
    args[0] = this;
    args[1] = new Integer(fileDescriptor);
    args[2] = data;
    Boolean result = (Boolean) callRPCNormalizingExceptions
      ( g2_media_bin_write_ , args);
  }

  public char[] read(int fileDescriptor, int maxLength)
       throws IOException
  {
    java.lang.Object[] args = new java.lang.Object[3];
    args[0] = this;
    args[1] = new Integer(fileDescriptor);
    args[2] = new Integer(maxLength);
    char[] result = (char[]) callRPCNormalizingExceptions
      ( g2_media_bin_read_ , args);

    if (false)
      {
	int len = result.length;
	for (int i = 0; i < len ; i++)
	  {
	    char ch = result[i];
	    System.out.print((ch & 255)+"/"+(ch >> 8)+" ");
	  }
	System.out.println(" ");
      }

    return result;
  }

  public Structure describe(int fileDescriptor)
       throws IOException
  {
    java.lang.Object[] args = new java.lang.Object[2];
    args[0] = this;
    args[1] = new Integer(fileDescriptor);
    java.lang.Object result = callRPCNormalizingExceptions
      ( g2_media_bin_describe_ , args);
    if (!(result instanceof Structure))
      throw new IOException("no description for fd = "+fileDescriptor);
    return (Structure)result;
  }

  public Structure describe(Vector path)
       throws IOException
  {
    java.lang.Object[] args = new java.lang.Object[2];
    args[0] = this;
    args[1] = makeSequence(path);
    java.lang.Object result = callRPCNormalizingExceptions
      ( g2_media_bin_describe_ , args);
    if (result instanceof Structure)
      return (Structure) result;
    else
      return null;
  }

  public Structure describe(Vector path , String filename)
       throws IOException
  {
    Vector pathCopy = (Vector)path.clone();
    pathCopy.addElement(filename);
    return describe(pathCopy);
  }

  public boolean delete(Vector path)
       throws IOException
  {
    java.lang.Object[] args = new java.lang.Object[2];
    args[0] = this;
    args[1] = makeSequence(path);
    Boolean result = (Boolean) callRPCNormalizingExceptions
      ( g2_media_bin_delete_ , args);
    return result.booleanValue();
  }

  public boolean delete(Vector path , String filename)
       throws IOException
  {
    Vector pathCopy = (Vector)path.clone();
    pathCopy.addElement(filename);
    return delete(pathCopy);
  }

  public boolean makeDirectory(Vector path, String newDirectoryName)
       throws IOException
  {
    java.lang.Object[] args = new java.lang.Object[3];
    args[0] = this;
    args[1] = makeSequence(path);
    args[2] = newDirectoryName;
     Boolean result = (Boolean) callRPCNormalizingExceptions
      ( g2_media_bin_make_directory_ , args);
    return result.booleanValue();
  }

  public void setIgnoreLastByte(int fileDescriptor)
       throws IOException
  {
    java.lang.Object[] args = new java.lang.Object[2];
    args[0] = this;
    args[1] = new Integer(fileDescriptor);
    Boolean result = (Boolean) callRPCNormalizingExceptions
      ( g2_media_bin_set_ignore_last_byte_ , args);
  }

  protected boolean ignoreLastByte(int fileDescriptor)
       throws IOException
  {
    java.lang.Object[] args = new java.lang.Object[2];
    args[0] = this;
    args[1] = new Integer(fileDescriptor);
    Boolean result = (Boolean) callRPCNormalizingExceptions
      ( g2_media_bin_ignore_last_byte_ , args);
    return result.booleanValue();
  }
}
