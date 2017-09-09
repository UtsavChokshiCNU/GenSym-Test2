/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      MediaBin.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:01:13 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import com.gensym.jgi.G2Access;
import com.gensym.jgi.G2Gateway;
import com.gensym.util.*;
import com.gensym.message.*;
import java.io.IOException;
import java.util.Vector;

public interface MediaBin extends com.gensym.classes.Entity, com.gensym.classes.Item {

  public static final Symbol MEDIA_BIN_ = com.gensym.util.symbol.G2ClassSymbols.MEDIA_BIN_;
  static final Symbol g2ClassName = MEDIA_BIN_;
  static final Symbol[] classInheritancePath = new Symbol[] {MEDIA_BIN_, ENTITY_, BLOCK_, KB_FRAME_, ITEM_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /* Overriden Property - IGNORE-LAST-BYTE */
  /**  Property Setter for IGNORE-LAST-BYTE */
  public void setIgnoreLastByte(int fileDescriptor)
       throws IOException;

  /**
   * Generated Property Getter for attribute -- MEDIA-BIN-DATA
   * @return the value of the MEDIA-BIN-DATA attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for MEDIA-BIN-DATA is : 
   * Value
   *
   */
  public java.lang.Object getMediaBinData() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- MEDIA-BIN-DATA
   * @param mediaBinData new value to conclude for MEDIA-BIN-DATA
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setMediaBinData(java.lang.Object mediaBinData) throws G2AccessException;

  /* Overriden method - MAKE-DIRECTORY */
  public boolean makeDirectory(Vector path, String newDirectoryName)
       throws IOException;

  /* Overriden method - DELETE-0 */
  public boolean delete(Vector path , String filename)
       throws IOException;

  /* Overriden method - DELETE */
  public boolean delete(Vector path)
       throws IOException;

  /* Overriden method - DESCRIBE-1 */
  public Structure describe(Vector path , String filename)
       throws IOException;

  /* Overriden method - DESCRIBE-0 */
  public Structure describe(Vector path)
       throws IOException;

  /* Overriden method - DESCRIBE */
  public Structure describe(int fileDescriptor)
       throws IOException;

  /* Overriden method - READ */
  public char[] read(int fileDescriptor, int maxLength)
       throws IOException;

  /* Overriden method - WRITE */
  public void write(int fileDescriptor, char[] data)
       throws IOException;

  /* Overriden method - CLOSE-STREAM */
  public void closeStream(int fileDescriptor)
       throws IOException;

  /* Overriden method - MAKE-BINARY-INPUT-STREAM */
  public G2BinaryInputStream makeBinaryInputStream(Vector path, String name)
       throws IOException;

  /* Overriden method - MAKE-BINARY-OUTPUT-STREAM */
  public G2BinaryOutputStream makeBinaryOutputStream(Vector path, String name)
       throws IOException;

  /* Overriden method - OPEN-STREAM */
  public int openStream(Vector path, String name, int direction,
			int fileType, int mode)
       throws IOException;

}
