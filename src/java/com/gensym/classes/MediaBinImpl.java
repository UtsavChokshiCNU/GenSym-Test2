/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      MediaBinImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:01:14 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.G2Access;
import com.gensym.jgi.G2Gateway;
import com.gensym.util.*;
import java.io.IOException;
import java.util.Vector;
import java.awt.Rectangle;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.G2Version;
import com.gensym.util.AttributeDenotation;
import com.gensym.util.ItemListener;
import com.gensym.util.ItemEvent;
import com.gensym.jgi.AttributeUncachableException;
import com.gensym.util.NoSuchAttributeException;
import com.gensym.util.NtwIllegalArgumentException;
import com.gensym.util.CorruptionException;

public class MediaBinImpl extends com.gensym.classes.EntityImpl implements MediaBin {


  static final long serialVersionUID = 2L;

  /* Overriden Field */
  static boolean initialized = false;
  /* Overriden Field */
  private static int MediaBinTimeout = 0;
  /* Overriden Field */
  public static final int INPUT = 0;
  /* Overriden Field */
  public static final int OUTPUT = 1;
  /* Overriden Field */
  private static Symbol[] directions = { Symbol.intern("INPUT"), Symbol.intern("OUTPUT") };
  /* Overriden Field */
  public static final int TEXT = 0;
  /* Overriden Field */
  public static final int BINARY = 1;
  /* Overriden Field */
  private static Symbol[] fileTypes = { Symbol.intern("TEXT") , Symbol.intern("BINARY") };
  /* Overriden Field */
  public static final int CREATE_OVERWRITE = 0;
  /* Overriden Field */
  public static final int READ_SHARED = 1;
  /* Overriden Field */
  private static Symbol[] modes = { Symbol.intern("CREATE-OR-OVERWRITE"), Symbol.intern("READ-SHARED") };
  /* Overriden Field */
  private static Symbol g2_media_bin_open_stream_ = Symbol.intern("G2-MEDIA-BIN-OPEN-STREAM");
  /* Overriden Field */
  private static Symbol g2_media_bin_close_stream_ = Symbol.intern("G2-MEDIA-BIN-CLOSE-STREAM");
  /* Overriden Field */
  private static Symbol g2_media_bin_write_ = Symbol.intern("G2-MEDIA-BIN-WRITE");
  /* Overriden Field */
  private static Symbol g2_media_bin_read_ = Symbol.intern("G2-MEDIA-BIN-READ");
  /* Overriden Field */
  private static Symbol g2_media_bin_make_directory_ = Symbol.intern("G2-MEDIA-BIN-MAKE-DIRECTORY");
  /* Overriden Field */
  private static Symbol g2_media_bin_describe_ = Symbol.intern("G2-MEDIA-BIN-DESCRIBE");
  /* Overriden Field */
  private static Symbol g2_media_bin_delete_ = Symbol.intern("G2-MEDIA-BIN-DELETE");
  /* Overriden Field */
  private static Symbol g2_media_bin_set_ignore_last_byte_ = Symbol.intern("G2-MEDIA-BIN-SET-IGNORE-LAST-BYTE");
  /* Overriden Field */
  private static Symbol g2_media_bin_ignore_last_byte_ = Symbol.intern("G2-MEDIA-BIN-IGNORE-LAST-BYTE");
  /* Overriden Field */
  static final G2Version G2_VERSION_FOR_USER_MENU_CHOICES_FOR_SESSION = new G2Version(5, 1, "Rev", 1, "BC10");
  /* Overriden Field */
  private static final Symbol MODIFY_ = Symbol.intern ("MODIFY");
private static final Symbol DELETE_ = Symbol.intern ("DELETE");
private static final Symbol SUBSCRIPTION_HANDLE_ = Symbol.intern ("SUBSCRIPTION-HANDLE");
private static final Symbol INITIAL_VALUE_ = Symbol.intern ("INITIAL-VALUE");
  /* Overriden Field */
private static final Symbol G2_DELETE_ITEM_ = Symbol.intern ("G2-DELETE-ITEM");
private static final Symbol G2_ENABLE_ITEM_                  = Symbol.intern ("G2-ENABLE-ITEM");
private static final Symbol G2_DISABLE_ITEM_                 = Symbol.intern ("G2-DISABLE-ITEM");
private static final Symbol G2_MAKE_PERMANENT_               = Symbol.intern ("G2-MAKE-PERMANENT");
private static final Symbol G2_MAKE_TRANSIENT_               = Symbol.intern ("G2-MAKE-TRANSIENT");
private static final Symbol G2_LIFT_ITEM_TO_TOP_             = Symbol.intern ("G2-LIFT-ITEM-TO-TOP");
private static final Symbol G2_DROP_ITEM_TO_BOTTOM_          = Symbol.intern ("G2-DROP-ITEM-TO-BOTTOM");
private static final Symbol G2_CLONE_ITEM_                   = Symbol.intern ("G2-CLONE-ITEM");
private static final Symbol G2_MOVE_WS_ITEM_                 = Symbol.intern ("G2-MOVE-WS-ITEM");
private static final Symbol G2_MOVE_WS_ITEM_BY_              = Symbol.intern ("G2-MOVE-WS-ITEM-BY");
private static final Symbol G2_GET_CONTAINMENT_HIERARCHY_    = Symbol.intern ("G2-GET-CONTAINMENT-HIERARCHY");
private static final Symbol G2_GET_CURRENT_USER_MENU_CHOICES_= Symbol.intern ("G2-GET-CURRENT-USER-MENU-CHOICES");
private static final Symbol G2_TRANSFER_ITEM_                = Symbol.intern ("G2-TRANSFER-ITEM");
private static final Symbol G2_CHANGE_SIZE_OF_ITEM_PER_AREA_ = Symbol.intern ("G2-CHANGE-SIZE-OF-ITEM-PER-AREA");
private static final Symbol G2_RESTORE_ITEM_TO_NORMAL_SIZE_  = Symbol.intern ("G2-RESTORE-ITEM-TO-NORMAL-SIZE");  
private static final Symbol G2_GET_DIALOG_                   = Symbol.intern ("G2-GET-DIALOG");
  /* Overriden Field */
  private static final Symbol G2_ITEM_IS_DISABLED_ = Symbol.intern ("G2-ITEM-IS-DISABLED");
  /* Overriden Field */
  private static final Symbol G2_GET_CURRENT_USER_MENU_CHOICES_FOR_SESSION_ = Symbol.intern ("G2-GET-CURRENT-USER-MENU-CHOICES-FOR-SESSION");
  /* Overriden Field */
  private static final Symbol DEFAULT_ = Symbol.intern("DEFAULT");
  /* Generated constructors */

  public MediaBinImpl() {
    super();
  }

  public MediaBinImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public MediaBinImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /* Overriden Property - IGNORE-LAST-BYTE */

  /**  Property Setter for IGNORE-LAST-BYTE */
  @Override
  public void setIgnoreLastByte(int fileDescriptor)
       throws IOException   {
    
        java.lang.Object[] args = new java.lang.Object[2];
        args[0] = this;
        args[1] = fileDescriptor;
        Boolean result = (Boolean) callRPCNormalizingExceptions
          ( g2_media_bin_set_ignore_last_byte_ , args);
      
  }

  /* Overriden Property - BOUNDS */
  /**
   * @undocumented
   */
  @Override
  public Rectangle getBounds () throws G2AccessException {
    
        int xCenter = ((Integer)getAttributeValue (ITEM_X_POSITION_)).intValue ();
        int yCenter = ((Integer)getAttributeValue (ITEM_Y_POSITION_)).intValue ();
        int width   = ((Integer)getAttributeValue (ITEM_WIDTH_)).intValue ();
        int height  = ((Integer)getAttributeValue (ITEM_HEIGHT_)).intValue ();
        int x       = xCenter - (width >> 1);
        int y       = yCenter + (height >> 1);
        return new Rectangle (x, y, width, height);
      
  }

  /**
   * Sets the bounds of this Item
   * @param the new left bound of this Item.
   * @param the new top bound of this Item.
   * @param the new right bound of this Item.
   * @param the new bottom bound of this Item.
   * @exception G2AccessException if there are any communication problems
   *   or exceptions within the remote method call
   */
  @Override
  public void setBounds (int left, int top, int right, int bottom)
       throws G2AccessException   {
    
        checkItemValidity ();
        java.lang.Object[] args = {this, left, top, right, bottom, DEFAULT_};
        callRPC (G2_CHANGE_SIZE_OF_ITEM_PER_AREA_, args);
      
  }

  /* Overriden Property - CONTAINMENT-HIERARCHY */
  /**
   * @return a Sequence of the Items and/or KbWorkspaces in which this
   * item is contained.
   * @exception G2AccessException if there are any communication problems
   *   or exceptions within the remote method call
   */
  @Override
  public Sequence getContainmentHierarchy()
       throws G2AccessException {
    
        checkItemValidity ();
        java.lang.Object[] args = new java.lang.Object[] {this};
        return (Sequence)callRPC(G2_GET_CONTAINMENT_HIERARCHY_, args);
      
  }


  /* Overriden Property - CURRENT-USER-MENU-CHOICES */
  /**
   * Retrieves the current set of user-menu-choices applicable for this instance
   * in a particular mode.
   * @param a Symbol indicating the G2 user mode with which to make this
   *   query.
   * @return a Sequence of the UserMenuChoices that are currently availible 
   *   for this item in the given mode.
   * @exception G2AccessException if there are any communication problems
   *   or exceptions within the remote method call
   * @deprecated use retrieveCurrentUserMenuChoices()
   */
  @Override
  public Sequence getCurrentUserMenuChoices(Symbol userMode)
       throws G2AccessException {
    
        checkItemValidity ();
        java.lang.Object[] args = new java.lang.Object[] {this, userMode};
        return (Sequence)callRPC(G2_GET_CURRENT_USER_MENU_CHOICES_, args);
      
  }


  /**
   * Generated Property Setter for attribute -- MEDIA-BIN-DATA
   * @param mediaBinData new value to conclude for MEDIA-BIN-DATA
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setMediaBinData(java.lang.Object mediaBinData) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.MEDIA_BIN_DATA_, mediaBinData);
  }

  /**
   * Generated Property Getter for attribute -- MEDIA-BIN-DATA
   * @return the value of the MEDIA-BIN-DATA attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getMediaBinData() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.MEDIA_BIN_DATA_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- TRANSIENT
   * @return the value of the TRANSIENT attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getTransient() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.TRANSIENT_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Setter for attribute -- MANUALLY-DISABLED?
   * @param manuallyDisabled new value to conclude for MANUALLY-DISABLED?
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setManuallyDisabled(boolean manuallyDisabled) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.MANUALLY_DISABLEDQ_, manuallyDisabled);
  }

  /**
   * Generated Property Getter for attribute -- MANUALLY-DISABLED?
   * @return the value of the MANUALLY-DISABLED? attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getManuallyDisabled() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.MANUALLY_DISABLEDQ_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Getter for attribute -- PERMANENT
   * @return the value of the PERMANENT attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getPermanent() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.PERMANENT_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Setter for attribute -- DO-NOT-STRIP-TEXT-MARK
   * @param doNotStripTextMark new value to conclude for DO-NOT-STRIP-TEXT-MARK
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setDoNotStripTextMark(boolean doNotStripTextMark) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.DO_NOT_STRIP_TEXT_MARK_, doNotStripTextMark);
  }

  /**
   * Generated Property Getter for attribute -- DO-NOT-STRIP-TEXT-MARK
   * @return the value of the DO-NOT-STRIP-TEXT-MARK attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getDoNotStripTextMark() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.DO_NOT_STRIP_TEXT_MARK_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Setter for attribute -- STRIP-TEXT-MARK
   * @param stripTextMark new value to conclude for STRIP-TEXT-MARK
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setStripTextMark(boolean stripTextMark) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.STRIP_TEXT_MARK_, stripTextMark);
  }

  /**
   * Generated Property Getter for attribute -- STRIP-TEXT-MARK
   * @return the value of the STRIP-TEXT-MARK attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getStripTextMark() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.STRIP_TEXT_MARK_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Getter for attribute -- REPRESENTATION-TYPE
   * @return the value of the REPRESENTATION-TYPE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getRepresentationType() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.REPRESENTATION_TYPE_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- TABLE-HEADER
   * @return the value of the TABLE-HEADER attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.String getTableHeader() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.TABLE_HEADER_);
    return (java.lang.String)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- ITEM-WIDTH
   * @return the value of the ITEM-WIDTH attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public int getItemWidth() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.ITEM_WIDTH_);
    return ((Integer)retnValue).intValue ();
  }

  /**
   * Generated Property Getter for attribute -- ITEM-HEIGHT
   * @return the value of the ITEM-HEIGHT attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public int getItemHeight() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.ITEM_HEIGHT_);
    return ((Integer)retnValue).intValue ();
  }

  /**
   * Generated Property Getter for attribute -- ITEM-Y-POSITION
   * @return the value of the ITEM-Y-POSITION attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public int getItemYPosition() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.ITEM_Y_POSITION_);
    return ((Integer)retnValue).intValue ();
  }

  /**
   * Generated Property Getter for attribute -- ITEM-X-POSITION
   * @return the value of the ITEM-X-POSITION attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public int getItemXPosition() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.ITEM_X_POSITION_);
    return ((Integer)retnValue).intValue ();
  }

  /* Overriden  - ITEM Event Listener - Adder1 */
  @Override
  public void addItemListener (ItemListener il) throws G2AccessException {
    
    
        addItemListener (il, WILDCARD_ARRAY);
          
      
  }

  /* Overriden  - ITEM Event Listener - Remover1 */
  @Override
  public void removeItemListener (ItemListener il) throws G2AccessException   {
    
        removeItemListener (il, WILDCARD_ARRAY);
      
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  /* Overriden method - IGNORE-LAST-BYTE */
  protected boolean ignoreLastByte(int fileDescriptor)
       throws IOException
 {
    
        java.lang.Object[] args = new java.lang.Object[2];
        args[0] = this;
        args[1] = fileDescriptor;
        Boolean result = (Boolean) callRPCNormalizingExceptions
          ( g2_media_bin_ignore_last_byte_ , args);
        return result.booleanValue();
      
  }

  /* Overriden method - MAKE-DIRECTORY */
  @Override
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

  /* Overriden method - DELETE-0 */
  @Override
  public boolean delete(Vector path , String filename)
       throws IOException
 {
    
        Vector pathCopy = (Vector)path.clone();
        pathCopy.addElement(filename);
        return delete(pathCopy);
      
  }

  /* Overriden method - DELETE */
  @Override
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

  /* Overriden method - DESCRIBE-1 */
  @Override
  public Structure describe(Vector path , String filename)
       throws IOException
 {
    
        Vector pathCopy = (Vector)path.clone();
        pathCopy.addElement(filename);
        return describe(pathCopy);
      
  }

  /* Overriden method - DESCRIBE-0 */
  @Override
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

  /* Overriden method - DESCRIBE */
  @Override
  public Structure describe(int fileDescriptor)
       throws IOException
 {
    
        java.lang.Object[] args = new java.lang.Object[2];
        args[0] = this;
        args[1] = fileDescriptor;
        java.lang.Object result = callRPCNormalizingExceptions
          ( g2_media_bin_describe_ , args);
        if (!(result instanceof Structure))
          throw new IOException("no description for fd = "+fileDescriptor);
        return (Structure)result;
      
  }

  /* Overriden method - READ */
  @Override
  public char[] read(int fileDescriptor, int maxLength)
       throws IOException
 {
    
        java.lang.Object[] args = new java.lang.Object[3];
        args[0] = this;
        args[1] = fileDescriptor;
        args[2] = maxLength;
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

  /* Overriden method - WRITE */
  @Override
  public void write(int fileDescriptor, char[] data)
       throws IOException
 {
    
        java.lang.Object[] args = new java.lang.Object[3];
        args[0] = this;
        args[1] = fileDescriptor;
        args[2] = data;
        Boolean result = (Boolean) callRPCNormalizingExceptions
          ( g2_media_bin_write_ , args);
      
  }

  /* Overriden method - CLOSE-STREAM */
  @Override
  public void closeStream(int fileDescriptor)
       throws IOException
 {
    
        java.lang.Object[] args = new java.lang.Object[3];
        args[0] = this;
        args[1] = fileDescriptor;
        args[2] = false;
        Boolean result = (Boolean) callRPCNormalizingExceptions
          ( g2_media_bin_close_stream_ , args);
      
  }

  /* Overriden method - CALL-RPCNORMALIZING-EXCEPTIONS */
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

  /* Overriden method - MAKE-SEQUENCE */
  private Sequence makeSequence(Vector vector)
 {
    
        int len = vector.size();
        Sequence sequence = new Sequence(len);
        for (int i = 0 ; i<len ; i++)
          sequence.addElement(vector.elementAt(i));
        return sequence;
      
  }

  /* Overriden method - MAKE-BINARY-INPUT-STREAM */
  @Override
  public G2BinaryInputStream makeBinaryInputStream(Vector path, String name)
       throws IOException
 {
    
        int fd = openStream(path,name,INPUT,BINARY,READ_SHARED);
        return new G2BinaryInputStream((MediaBin)this,fd);
      
  }

  /* Overriden method - MAKE-BINARY-OUTPUT-STREAM */
  @Override
  public G2BinaryOutputStream makeBinaryOutputStream(Vector path, String name)
       throws IOException
 {
    
        int fd = openStream(path,name,OUTPUT,BINARY,CREATE_OVERWRITE);
        return new G2BinaryOutputStream((MediaBin)this,fd);
      
  }

  /* Overriden method - OPEN-STREAM */
  @Override
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

  /* Overriden method - INITIALIZE-RPCS */
  private void initializeRPCs()
 {
    
        initialized = true;
      
  }

  /* Overriden method - REMOVE-ITEM-LISTENER-FOR-THREE-TIERS */
  @Override
  public void  removeItemListenerForThreeTiers(com.gensym.util.ItemListener l, Sequence subscriptionHandles)
    throws com.gensym.jgi.G2AccessException
 {
    
        
              Symbol[] attrNames = new Symbol[subscriptionHandles.size()];
              for (int i=0; i < subscriptionHandles.size(); i++) {
                attrNames[i] = data.subscriptionManager.getAttributeNameByHandle(((Integer) subscriptionHandles.elementAt(i)).intValue());
              }
              removeItemListener(l, attrNames);
    
      
  }

  /* Overriden method - ADD-ITEM-LISTENER-RETRIEVING-STATE-MULTIPLE */
  @Override
  public Sequence addItemListenerRetrievingStateMultiple (ItemListener l, Sequence denotation_sequences) throws G2AccessException
 {
    
        Symbol[] attributeNames = new Symbol[denotation_sequences.size()];
        for (int i=0; i < attributeNames.length; i++) {
          attributeNames[i] = ((AttributeDenotation) denotation_sequences.elementAt(i)).getAttributeName();
        }
        synchronized (data) {
          addItemListener(l, attributeNames);
          return makeSnapshot(attributeNames);
        }
      
  }

  /* Overriden method - REMOVE-ITEM-LISTENER */
  @Override
  public void removeItemListener (ItemListener il, Symbol[] attributeNames) throws G2AccessException
 {
    
            checkWILDCARD (attributeNames);
    
            ItemData principalData = getPrincipalData();
            if (principalData.subscriptionManager == null){
            	return;
            }
            principalData.subscriptionManager.removeEntry(il, attributeNames);
            Vector addedSubscriptions = principalData.subscriptionManager.getAddedSubscriptions();
            Vector removedSubscriptions = principalData.subscriptionManager.getRemovedSubscriptions();
            if ((addedSubscriptions != null) && (removedSubscriptions != null)) {
              subscribe(addedSubscriptions);
              unsubscribe (removedSubscriptions);
            } else if (removedSubscriptions != null)
              unsubscribe(removedSubscriptions);
            
    
      
  }

  /* Overriden method - CHECK-WILDCARD */
  private boolean checkWILDCARD(Symbol[] attributeNames) throws  G2AccessException
 {
    
        boolean hasWILDCARD = false;
    
            for (int i=0; i < attributeNames.length; i++) {
              if (attributeNames[i].equals(WILDCARD_)) {
                hasWILDCARD = true;
                break;
              }
            }
            if (hasWILDCARD && (attributeNames.length > 1))
              throw new G2AccessException("Wrong arguments. attributeNames should be either contain WILDCARD only or any attribute names without WILDCARD.");
    
            return hasWILDCARD;
      
  }

  /* Overriden method - ADD-ITEM-LISTENER */
  @Override
  public void addItemListener (ItemListener il, Symbol[] attributeNames) throws G2AccessException
 {
    
    
            boolean hasWILDCARD = checkWILDCARD (attributeNames);
            checkItemValidity ();
    
                                                
            Vector attrUncachable = new Vector();
            for (int i =0; i <attributeNames.length; i++) {
              if (!attributeSendsUpdates (attributeNames[i]))
                attrUncachable.addElement(attributeNames[i]);
            }
            if (!attrUncachable.isEmpty())
              throw new AttributeUncachableException(attrUncachable);
    
    
            ItemData principalData = getPrincipalData();
            synchronized (principalData) {
              if (principalData.subscriptionManager == null)
                principalData.subscriptionManager = new SubscriptionManager();
    
              principalData.subscriptionManager.addEntry(il, attributeNames);
              Vector addedSubscriptions = principalData.subscriptionManager.getAddedSubscriptions();
              Vector removedSubscriptions = principalData.subscriptionManager.getRemovedSubscriptions();
              if (addedSubscriptions != null && removedSubscriptions != null) {
                  subscribe(addedSubscriptions);
                  unsubscribe (removedSubscriptions);
              } else if (addedSubscriptions != null)
                  subscribe(addedSubscriptions);
    
            }
    
                                     
            Structure attributes = null;
            Sequence attributeDenotations = null;
            int sHandle = 0;
            if (hasWILDCARD) {
              attributes = getAttributes ();
              attributeDenotations = AttributeDenotation.WILDCARD_DENOTATION;
              sHandle = principalData.subscriptionManager.getHandleByAttributeName(attributeNames[0]);
    
            } else {
                                                       
              java.lang.Object[] objs = new java.lang.Object[attributeNames.length];
              try {
                for (int i=0; i < attributeNames.length; i++) {
                  objs[i] = principalData.attributes.getAttributeValue(attributeNames[i]);
                }
                attributes = new Structure(attributeNames, objs);
              }
              catch (NoSuchAttributeException ex) {
                throw new CorruptionException(ex, "No such attribute.");
              }
    	  catch (NtwIllegalArgumentException ex) {
    	    throw new CorruptionException(ex, "Error making Structure");
              }
    
                                                                            
    	                                                              
    	                                                                 
    	                                                                      
              attributeDenotations = null;
            }
            ItemEvent itemEvent = new ItemEvent (this, INITIAL_VALUE_, this,
    					     attributeDenotations,
    					     attributes, USER_DATA,
    					     sHandle);
            il.receivedInitialValues (itemEvent);
      
  }

  /* Overriden method - RESTORE-NORMAL-SIZE */
  @Override
  public void restoreNormalSize() throws G2AccessException
 {
    
        checkItemValidity ();
        java.lang.Object[] args = {this};
        callRPC(G2_RESTORE_ITEM_TO_NORMAL_SIZE_, args);
      
  }

  /* Overriden method - TRANSFER-OFF */
  @Override
  public boolean transferOff () throws G2AccessException
 {
    
        return transfer (null, 0, 0, Boolean.FALSE, Boolean.FALSE);
      
  }

  /* Overriden method - TRANSFER-TO-ITEM */
  @Override
  public boolean transferToItem (Item targetItem, Symbol attributeName, Symbol classQualifier) throws G2AccessException
 {
    
        return transferTo (targetItem, attributeName, classQualifier);
      
  }

  /* Overriden method - TRANSFER-TO-0 */
  @Override
  public boolean transferTo (Item targetItem, Symbol attributeName, Symbol classQualifier) throws G2AccessException
 {
    
        return transfer (targetItem, 0, 0, attributeName, classQualifier);
      
  }

  /* Overriden method - TRANSFER-TO-WORKSPACE */
  @Override
  public boolean transferToWorkspace (KbWorkspace wksp, int x, int y) throws G2AccessException
 {
    
        return transferTo (wksp, x, y);
      
  }

  /* Overriden method - TRANSFER-TO */
  @Override
  public boolean transferTo (KbWorkspace wksp, int x, int y) throws G2AccessException
 {
    
        return transfer (wksp, x, y, Boolean.FALSE, Boolean.FALSE);
      
  }

  /* Overriden method - TRANSFER */
  private boolean transfer (Item targetItem,
			    int x,
			    int y,
			    java.lang.Object attributeNameOrFalse,
			    java.lang.Object classQualifierOrFalse)
       throws G2AccessException
 {
    
        checkItemValidity ();
        if (targetItem != null)
          ((G2__BaseImpl)targetItem).checkItemValidity ();
        java.lang.Object[] args = new java.lang.Object[6];
        args[0] = this;
        args[1] = (targetItem != null ? 
    	       (java.lang.Object)targetItem : (java.lang.Object)Boolean.FALSE);
        args[2] = x;
        args[3] = y;
        args[4] = attributeNameOrFalse;
        args[5] = (classQualifierOrFalse == null ?
                   Boolean.FALSE : classQualifierOrFalse);
        Boolean retnvalue = (Boolean)
          context.callRPC(G2_TRANSFER_ITEM_, args);
        return retnvalue.booleanValue ();
      
  }

  /* Overriden method - RETRIEVE-CURRENT-USER-MENU-CHOICES */
  @Override
  public Sequence retrieveCurrentUserMenuChoices()
  throws G2AccessException
 {
    
        checkItemValidity ();
    
        G2Gateway context = (G2Gateway)getContext();
        UiClientSession session =
          (UiClientSession) invokeTwAccessMethod(context, "getSession", null, null);
    			 
        G2Version currentVersion = context.getG2Version();
    
        if (currentVersion.compareTo(G2_VERSION_FOR_USER_MENU_CHOICES_FOR_SESSION) == G2Version.OLDER) {
          return getCurrentUserMenuChoices(session.getUiClientSessionUserMode());
        } else {    
          java.lang.Object[] args = new java.lang.Object[] {this, session};
          return (Sequence)callRPC(G2_GET_CURRENT_USER_MENU_CHOICES_FOR_SESSION_, args);
        }
      
  }

  /* Overriden method - IS-PROPRIETARY-THROUGH-CONTAINMENT */
  @Override
  public boolean isProprietaryThroughContainment () throws G2AccessException
 {
    
    
        Boolean isProprietaryObject = data.itemIsProprietaryThroughContainment;
        if (isProprietaryObject != null)
          return isProprietaryObject.booleanValue ();
    
        boolean isProprietary = false;
    
        ItemData principalData = getPrincipalData();
        if (this instanceof KbWorkspace) {
          isProprietary = ((KbWorkspace)this).workspaceIsProprietary(null, -1);
        } else {
          isProprietary =
    	(principalData.parentWorkspace == null ? false :
    	 principalData.parentWorkspace.workspaceIsProprietary(null, -1));
        }
    
        if(isProprietary)
          principalData.itemIsProprietaryThroughContainment = Boolean.TRUE;
        else
          principalData.itemIsProprietaryThroughContainment = Boolean.FALSE;
    
        return isProprietary;
      
  }

  /* Overriden method - MOVE-BY-FOR-VB */
  @Override
  public boolean moveByForVB (int xDelta,
			      int yDelta,
			      int pseudoBooleanEnlargeWorkspaceIfNecessary)
       throws G2AccessException
 {
    
        return moveBy (xDelta, yDelta, (pseudoBooleanEnlargeWorkspaceIfNecessary != 0));
      
  }

  /* Overriden method - MOVE-BY */
  @Override
  public boolean moveBy(int xDelta,
			int yDelta,
			boolean enlargeWorkspaceIfNecessary)
       throws G2AccessException
 {
    
        checkItemValidity ();
        java.lang.Object[] args = new java.lang.Object[5];
        args[0] = this;
        args[1] = xDelta;
        args[2] = yDelta;
        args[3] = enlargeWorkspaceIfNecessary;
        args[4] = Boolean.FALSE;                         
        Boolean retnvalue = (Boolean)
          context.callRPC(G2_MOVE_WS_ITEM_BY_, args);
        return retnvalue.booleanValue ();
      
  }

  /* Overriden method - MOVE-FOR-VB */
  @Override
  public boolean moveForVB (int x,
			    int y,
			    int pseudoBooleanEnlargeWorkspaceIfNecessary)
       throws G2AccessException
 {
    
        return move (x, y, (pseudoBooleanEnlargeWorkspaceIfNecessary != 0));
      
  }

  /* Overriden method - MOVE */
  @Override
  public boolean move(int x,
		      int y,
		      boolean enlargeWorkspaceIfNecessary)
       throws G2AccessException
 {
    
        checkItemValidity ();
        java.lang.Object[] args = new java.lang.Object[5];
        args[0] = this;
        args[1] = x;
        args[2] = y;
        args[3] = enlargeWorkspaceIfNecessary;
        args[4] = Boolean.FALSE;                        
        Boolean retnvalue = (Boolean)
          context.callRPC(G2_MOVE_WS_ITEM_, args);
        return retnvalue.booleanValue ();
      
  }

  /* Overriden method - G2CLONE */
  @Override
  public Item g2Clone() throws G2AccessException
 {
    
        checkItemValidity ();
        java.lang.Object[] args = new java.lang.Object[] {this};
        return (Item) context.callRPC(G2_CLONE_ITEM_, args);
      
  }

  /* Overriden method - DROP-TO-BOTTOM */
  @Override
  public void dropToBottom () throws G2AccessException
 {
    
        checkItemValidity ();
        java.lang.Object[] args = new java.lang.Object[] {this};
        context.callRPC (G2_DROP_ITEM_TO_BOTTOM_, args);
      
  }

  /* Overriden method - LIFT-TO-TOP */
  @Override
  public void liftToTop () throws G2AccessException
 {
    
        checkItemValidity ();
        java.lang.Object[] args = new java.lang.Object[] {this};
        context.callRPC (G2_LIFT_ITEM_TO_TOP_, args);
      
  }

  /* Overriden method - MAKE-TRANSIENT */
  @Override
  public void makeTransient () throws G2AccessException
 {
    
        checkItemValidity ();
        java.lang.Object[] args = new java.lang.Object[] {this};
        context.callRPC(G2_MAKE_TRANSIENT_, args);
      
  }

  /* Overriden method - MAKE-PERMANENT */
  @Override
  public void makePermanent () throws G2AccessException
 {
    
        checkItemValidity ();
        java.lang.Object[] args = new java.lang.Object[] {this};
        context.callRPC(G2_MAKE_PERMANENT_, args);
      
  }

  /* Overriden method - IS-ENABLED */
  @Override
  public boolean isEnabled () throws G2AccessException
 {
    
        return !getManuallyDisabled();
      
  }

  /* Overriden method - DISABLE */
  @Override
  public void disable () throws G2AccessException
 {
    
        checkItemValidity ();
        java.lang.Object[] args = new java.lang.Object[] {this};
        Boolean retnvalue = (Boolean)
          context.callRPC(G2_DISABLE_ITEM_, args);
        //return retnvalue.booleanValue ();
      
  }

  /* Overriden method - ENABLE */
  @Override
  public void enable () throws G2AccessException
 {
    
        checkItemValidity ();
        java.lang.Object[] args = new java.lang.Object[] {this};
        Boolean retnvalue = (Boolean)
          context.callRPC(G2_ENABLE_ITEM_, args);
                                           
      
  }

  /* Overriden method - DELETE-FOR-VB */
  @Override
  public void deleteForVB (int pseudoBooleanWithPermanencyChecksDisabled,
			   int pseudoBooleanWithoutLeavingStubs) throws G2AccessException
 {
    
        delete ((pseudoBooleanWithPermanencyChecksDisabled != 0), (pseudoBooleanWithoutLeavingStubs != 0));
      
  }

  /* Overriden method - DELETE */
  @Override
  public void delete (boolean withPermanencyChecksDisabled,
		      boolean withoutLeavingStubs) throws G2AccessException
 {
    
                                                                                  
                                                                                   
                                                                             
       if ((com.gensym.core.GensymApplication.getApplication() == null) ||
           (com.gensym.core.GensymApplication.getApplication().deleteItem
    	(this,withPermanencyChecksDisabled, withoutLeavingStubs) == false)) {
         java.lang.Object[] args = new java.lang.Object[]
           {this, withPermanencyChecksDisabled ? Boolean.TRUE : Boolean.FALSE,
    	  withoutLeavingStubs ? Boolean.TRUE : Boolean.FALSE};
           context.callRPC (G2_DELETE_ITEM_, args);
       }
      
  }

  
}
