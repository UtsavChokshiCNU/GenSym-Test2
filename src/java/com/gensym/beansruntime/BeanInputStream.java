/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	BeanInputStream - BeanInputStream.java
 *
 *
 *   Modifications:
 *
 */

package com.gensym.beansruntime;

import java.io.*;

/**
 * This class is responsible for loading serialized beans
 */

public class BeanInputStream extends ObjectInputStream
{
  private ClassLoader loader;

  /**
   * Constructor;
   */
  public BeanInputStream (InputStream in, ClassLoader loader)
       throws IOException, StreamCorruptedException
  {
    super(in);
    if (loader == null || in == null)
      {
	throw new IllegalArgumentException("Illegal null argument to ObjectInputStreamWithLoader");
      }
    this.loader = loader;
  }

  /**
   * Use the given ClassLoader rather than using the system class
   */
  @Override
  protected Class resolveClass (ObjectStreamClass classDesc)
       throws IOException, ClassNotFoundException
  {
    String classname = classDesc.getName();
    return loader.loadClass(classname);
  }


  /**
   * Get the class loader used by this stream 
   */
  public ClassLoader getClassLoader()
  {
    return loader;
  }
}
