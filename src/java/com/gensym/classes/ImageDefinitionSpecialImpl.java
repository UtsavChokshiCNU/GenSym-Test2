/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      EntitySpecialImpl.java
 *
 *   Description: Overides for generated Interface files. 
 *
 *        Author: Paul B. Konigberg
 *
 *       Version: 5.0 Rev. 1
 *
 *          Date: Thu Jul 15 10:44:44 EDT 1998
 *
 */


package com.gensym.classes;

import java.awt.Image;
import java.awt.Toolkit;
import com.gensym.jgi.G2AccessException;
import java.util.Vector;
import com.gensym.util.*;


public class ImageDefinitionSpecialImpl extends ItemImpl {
  private transient Image image;
  private static final Symbol sizeKey = Symbol.intern ("SIZE-IN-BYTES");
  private transient boolean valid = false;

  /**
   * @return an <code>java.awt.Image<code> of the image pointed to
   * by this <code>ImageDefinition<code>.
   * @exception G2AccessException if there are any communication problems
   */
  public Image getImage() throws G2AccessException {
    if (image != null && valid) return image;
    try {
      int fileDescriptor = 1;
      MediaBin mb = (MediaBin)getCachedMediaBin ();
      if (mb == null)
	return null;
      Vector location = new Vector ();
      G2BinaryInputStream mbis = mb.makeBinaryInputStream (location, "image");
      Structure metaData = mb.describe (location, "image");
      Integer size
	= (Integer) metaData.getAttributeValue (sizeKey,sizeKey);
      int fileSize = size.intValue();
      byte[] imageData = new byte[fileSize];
      for (int i = 0; i<fileSize;i++) {
	imageData[i] = (byte)mbis.read ();
      }
      mbis.close();
      image = Toolkit.getDefaultToolkit ().createImage(imageData);
      valid = true;
      return image;
    } catch (java.io.IOException ioe) {
      com.gensym.message.Trace.exception (ioe, "Problems Getting Image From IMAGE-DEFINITION");
      return null;
    }
  }

  /**
   * @undocumented 
   */
  @Override
  public void processItemEvent (ItemEvent e) {
    valid = false;
    super.processItemEvent(e);
  }
}
