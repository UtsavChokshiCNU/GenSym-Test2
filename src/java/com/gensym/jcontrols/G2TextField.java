/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 G2TextField.java
 *
 */

package com.gensym.jcontrols;

import javax.swing.JTextField;
import javax.swing.event.DocumentListener;
import javax.swing.event.DocumentEvent;
import java.awt.*;
import java.awt.event.*;
import java.beans.Beans;
import java.io.EOFException;
import java.io.IOException;
import com.gensym.util.Symbol;
import com.gensym.util.UnexpectedException;
import com.gensym.types.G2SyntaxException;
import com.gensym.dlg.WarningDialog;
import com.gensym.dlgevent.ObjectUpdateListener;
import com.gensym.dlgevent.ObjectUpdateEvent;
import com.gensym.dlgevent.ObjectChangeListener;
import com.gensym.dlgevent.ObjectChangeEvent;
import com.gensym.controls.AttributeEditor;
import com.gensym.controls.FieldType;
import com.gensym.controls.LimitMode;
import com.gensym.message.Trace;

/** The G2TextField is a G2-Data-aware version of the
 * java.awt.TextField.  It can handle the transformation of a variety
 * of values in to strings for editing, and vice-versa.  This is
 * governed by the fieldType property.  The G2TextField can generate
 * warnings for type-in that is not appropriate for a given data type,
 * e.g. "qwerty" is not of type com.gensym.types.IntegerType.  The
 * G2TextField responds to ObjectUpdateEvents and generates
 * ObjectChangeEvents.  The generation of ObjectChangeEvents is
 * controlled can be for every key press or just on focus changes and
 * typing the return/enter key.
 * 
 * @see com.gensym.types;
 * @see java.awt.TextField
 */
public class G2TextField extends JTextField
           implements DocumentListener, ObjectUpdateListener, FocusListener,
                      AttributeEditor, KeyListener, Cloneable
{
  /*
   * Allow deserialization
   */
  static final long serialVersionUID = 2987903833019483287L;

  private java.util.Vector listeners = null;
  private String attributeName = "";
  private Symbol attributeSymbol = null;
  private String defaultContents = "";
  private FieldType fieldType = new FieldType();
  /* warning: volatile field */
  private volatile boolean inhibitChangePropagation = false;
  private volatile boolean inhibitUpdatePropagation = false;
  private int updateCount = 0;
  private boolean emptyFieldImpliesNull;
  private boolean nextTextChangeIsProbablyFromTypeIn = true;
  private boolean warnOnBadSyntax = true;
  private boolean propagateEveryCharacterTyped = false;
  private LimitMode lowerLimitMode = new LimitMode();
  private LimitMode upperLimitMode = new LimitMode();
  private double lowerLimit = 0.0;
  private double upperLimit = 100.0;
  private boolean showQuotesForTextType = true;

  private transient G2DocumentAdapter documentAdapter;

  /** Creates the bean
   */
  public G2TextField()
  {
    setColumns (8);
    // don't do the following until we want to worry about syntax locally
    initiateModelListening();
    addFocusListener(this);
    addKeyListener(this);
  }

  @Override
  public Object clone() throws CloneNotSupportedException{
    G2TextField newThing = (G2TextField)super.clone();
    newThing.ui = null;
    return newThing;
  }

  private void readObject(java.io.ObjectInputStream in)
       throws IOException, ClassNotFoundException {
	 in.defaultReadObject();
	 // is this necessary in jdk1.2?
	 initiateModelListening();
  }

//   private static final boolean NEED_HACK = true;
  private transient boolean isCloneForSerialization = false;

//   protected Object writeReplace() throws ObjectStreamException {
//     if (isCloneForSerialization)
//       return this;
//     try {
//       G2TextField thingToWrite = (G2TextField)this.clone();
//       thingToWrite.isCloneForSerialization = true;
//       thingToWrite.setUI(null);
//       return thingToWrite;
//     } catch (CloneNotSupportedException cnse) {
//       Trace.exception(cnse);
//       isCloneForSerialization = true;
//       setUI(null);
//       return this;
//     }
//   }

//   public void setUI(TextUI ui) {
//     if (ui == null) {
//       if (!isCloneForSerialization) {
// 	Thread.dumpStack();
// 	return;
//       }
//     }
//     super.setUI(ui);
//   }    
  
//    private void writeObject(java.io.ObjectOutputStream out)
//    throws IOException {
//      System.out.println("ui=" + getUI());
// // 	 //    TextUI ui = getUI();
// // 	 //    boolean needHack = !(ui instanceof Serializable);
// // 	 //    System.out.println("ui=" + ui + ";hack?=" + needHack);
// // 	 if (NEED_HACK)
// // 	   setUI(null);
// // 	 //    try {
// // 	 //ui = null;
//  	 out.defaultWriteObject();
// // 	 //    } finally {
// // 	 //      if (needHack)
// // 	 //        setUI(ui);
// // 	 //    }
//    }
  
  private void initiateModelListening() {
    documentAdapter = new G2DocumentAdapter();
    documentAdapter.setG2TextField(this);
    getDocument().addDocumentListener(documentAdapter); 
  }
  /** Gets the name of the G2 Item attribute which this bean is
   * storing as a Symbol.
   * @see com.gensym.util.Symbol
   */ 
 @Override
 public Symbol getAttribute()
  {
    return attributeSymbol;
  }

  /** Sets the name of the G2 Item attribute which this bean is
   * storing from a Symbol.
   * @see com.gensym.util.Symbol
   */
  @Override
  public void setAttribute(Symbol symbol)
  {
    attributeSymbol = symbol;
    attributeName = symbol.toString();
  }

  /** This property can change the interpretation of the data implied
   *  by empty fields into a null references.
   */
  public boolean getEmptyFieldImpliesNull()
  {
    return emptyFieldImpliesNull;
  }

  /** This property can change the interpretation of the data implied
   *  by empty fields into a null references.
   */
  public void setEmptyFieldImpliesNull(boolean impliesNull)
  {
    emptyFieldImpliesNull = impliesNull;
  }

  /** The propagateEveryKeyTyped property controls whether
   *  ObjectChangeEvents are generated for every key typed, or just on
   *  focus changes and the enter key.
   */
  public boolean getPropagateEveryKeyTyped()
  {
    return propagateEveryCharacterTyped;
  }

  /** The propagateEveryKeyTyped property controls whether
   *  ObjectChangeEvents are generated for every key typed, or just on
   *  focus changes and the enter key.
   *  @see com.gensym.controls.ObjectChangeEvent
   */
  public void setPropagateEveryKeyTyped(boolean propagate)
  {
    propagateEveryCharacterTyped = propagate;
  }

  /** The warnOnBadSyntax property controls whether a modal dialog.
   *  will be shown for type-in that does not match the specified
   *  fieldType property.
   */
  public boolean getWarnOnBadSyntax()
  {
    return warnOnBadSyntax;
  }

  /** The warnOnBadSyntax property controls whether a modal dialog.
   *  will be shown for type-in that does not match the specified
   *  fieldType property.
   */
  public void setWarnOnBadSyntax(boolean warn)
  {
    warnOnBadSyntax = warn;
  }

  /** The showQuotesForTextType property controls whether the 
   *  the G2TextField requires the use of double quotes, when the attribute is
   *  of type Text.  If the fieldType is Value, double quotes are required to 
   *  distinguish symbols from string.  This setting has no effect on other
   *  field types.
   *
   *  @see setFieldType
   *  @see getFieldType
   */ 
  public boolean getShowQuotesForTextType()
  {
    return showQuotesForTextType;
  }

  /** The showQuotesForTextType property controls whether the 
   *  the G2TextField requires the use of double quotes, when the attribute is
   *  of type Text.  If the fieldType is Value, double quotes are required to 
   *  distinguish symbols from string.  This setting has no effect on other
   *  field types.
   *
   *  @see setFieldType
   *  @see getFieldType
   */ 
  public void setShowQuotesForTextType(boolean showQuotesForTextType)
  {
    this.showQuotesForTextType = showQuotesForTextType;
  }

  /** The defaultContents property contains a string which will be
  * used as input if none is received through an ObjectUpdateEvent or 
  * typed in.
  */
  public String getDefaultContents()
  {
    return defaultContents;
  }

  /** The defaultContents property contains a string which will be
   * used as input if none is received through an ObjectUpdateEvent or 
   * typed in.
   */
  public void setDefaultContents (String string)
  {
    defaultContents = string;
  }

  /** The fieldType property controls the transformation of strings
   * into other data types that this field may represent.  All G2 data
   * types (as presented by JavaLink) are supported.
   * @see com.gensym.types.G2Type
   * @see com.gensym.util.Structure
   * @see com.gensym.util.Sequence
   * @see com.gensym.util.Symbol
   */
  public FieldType getFieldType()
  {
    return fieldType;
  }

  /** The fieldType property controls the transformation of strings
   * into other data types that this field may represent.  All G2 data
   * types (as presented by JavaLink) are supported.
   * @see com.gensym.types.G2Type
   * @see com.gensym.util.Structure
   * @see com.gensym.util.Sequence
   * @see com.gensym.util.Symbol
   */
  public void setFieldType(FieldType type)
  {
    fieldType = type;
  }

  /** The lowerLimitMode property (along with the lowerLimit) the
   *  lower range of input to this field, if numeric.  It can be
   *  unlimited, exclusive, or inclusive.  */
  public LimitMode getLowerLimitMode()
  {
    return lowerLimitMode;
  }

  /** The lowerLimitMode property (along with the lowerLimit) the
   *  lower range of input to this field, if numeric.  It can be
   *  unlimited, exclusive, or inclusive.  */
  public void setLowerLimitMode(LimitMode mode)
  {
    lowerLimitMode = mode;
  }

  /** The lowerLimit property is the lower bound for numeric input
   *  if the mode is set to exclusive or inclusive, and ignored 
   * otherwise. */
  public double getLowerLimit()
  {
    return lowerLimit;
  }

  /** The lowerLimit property is the lower bound for numeric input
   *  if the mode is set to exclusive or inclusive, and ignored 
   * otherwise. */
  public void setLowerLimit(double limit)
  {
    lowerLimit = limit;
  }

  /** The upperLimitMode property (along with the upperLimit) the
   *  upper range of input to this field, if numeric.  It can be
   *  unlimited, exclusive, or inclusive.  */
  public LimitMode getUpperLimitMode()
  {
    return upperLimitMode;
  }

  /** The upperLimitMode property (along with the lowerLimit) the
   *  upper range of input to this field, if numeric.  It can be
   *  unlimited, exclusive, or inclusive.  */
  public void setUpperLimitMode(LimitMode mode)
  {
    upperLimitMode = mode;
  }

  /** The upperLimit property is the upper bound for numeric input
   *  if the mode is set to exclusive or inclusive, and ignored 
   * otherwise. */
  public double getUpperLimit()
  {
    return upperLimit;
  }

  /** The upperLimit property is the upper bound for numeric input
   *  if the mode is set to exclusive or inclusive, and ignored 
   * otherwise. */
  public void setUpperLimit(double limit)
  {
    upperLimit = limit;
  }

  // DocumentListener
  @Override
  public void insertUpdate(DocumentEvent e){
    textValueChanged();
  }
  
  @Override
  public void removeUpdate(DocumentEvent e){
    textValueChanged();
  }
  
  @Override
  public void changedUpdate(DocumentEvent e){
  }

  void textValueChanged() {
    if (nextTextChangeIsProbablyFromTypeIn) {
      if (propagateEveryCharacterTyped)
	fireObjectChangeOnContents();
    }
  }

  /**
   * Listener method, do not call 
   * @undocumented
   */  
  @Override
  public void keyPressed(KeyEvent e)
  {
    //nextTextChangeIsProbablyFromTypeIn = true;
  }

  /**
   * Listener method, do not call 
   * @undocumented
   */
  @Override
  public void keyTyped(KeyEvent e)
  {

  }

  /**
   * Listener method, do not call 
   * @undocumented
   */
  @Override
  public void keyReleased(KeyEvent e)
  {
    // System.out.println("G2TF key Release "+e);
    if (e.getKeyCode() == KeyEvent.VK_ENTER)
      fireObjectChangeOnContents();
  }

  String oldText;

  /**
   * Listener method, do not call 
   * @undocumented
   */  
  @Override
  public void focusGained(FocusEvent e)
  {
    oldText = getText();
  }

  /**
   * Listener method, do not call 
   * @undocumented
   */  
  @Override
  public void focusLost(FocusEvent e)
  {
    // System.out.println("G2TF focus LOST "+e);
    String textOnExit = getText();
    boolean textChanged = textOnExit == null ? oldText != null :
      !textOnExit.equals(oldText);
    if (!e.isTemporary() && textChanged)
      fireObjectChangeOnContents();
  }

  /**  This method implements the ObjectUpdateListener interface.
   * When this method is called the text of the TextField is changed.
   * to human-readable representation of a piece of data as governed by
   * the fieldType property.
   * @see com.gensym.controls.G2TextField#setFieldType
   */
  @Override
  public void objectUpdated(ObjectUpdateEvent e)
  {
    Object fieldValue
      = e.getUpdatedValue(attributeSymbol,
			  emptyFieldImpliesNull ? null : defaultContents);
    Updater updater = new Updater(fieldValue);
    if (javax.swing.SwingUtilities.isEventDispatchThread()) 
      updater.run();
    else {
      try {
	javax.swing.SwingUtilities.invokeAndWait(updater);
      } catch (InterruptedException ie) {
	Trace.exception(ie);
      } catch (java.lang.reflect.InvocationTargetException ite) {
	Trace.exception(ite);
      }
    }
  }

  class Updater implements Runnable {
    private Object fieldValue;
    Updater(Object fieldValue) {
      this.fieldValue = fieldValue;
    }
    @Override
    public void run() {
      boolean wasEditable = isEditable();
      if (fieldValue != null){
	setEditable(true);
	try {
	  String fieldText = fieldType.objectToString(fieldValue);
	  if (fieldType.isText() && !showQuotesForTextType)
	    fieldText = fieldText.substring(1,(fieldText.length() - 1));
	  nextTextChangeIsProbablyFromTypeIn = false;
	  setText(fieldText);
	  oldText = fieldText;
	  nextTextChangeIsProbablyFromTypeIn = true;
	} catch (IOException exception) {
	  throw new UnexpectedException(exception);
	}
	setEditable(wasEditable);
      } else if (emptyFieldImpliesNull) {
	setEditable(true);
	setText("");
	setEditable(wasEditable);
      }
      int len = getText().length();
      setSelectionStart(len);
      setSelectionEnd(len);
      repaint();
    }
  }
  
  /** Adds a listener to this bean for ObjectChangeEvents.
   * for either all type-in or just on focus changes and the 
   * ENTER key.
   * @see com.gensym.controls.G2TextField#setPropagateEveryKeyTyped
   */
  @Override
  public synchronized void addObjectChangeListener (ObjectChangeListener
						      listener)
  {
    if (listeners == null) {
      listeners = new java.util.Vector();
    }
    listeners.addElement(listener);
  }
  
  /** Removes a listener from this bean for ObjectChangeEvents.
   */
  @Override
  public synchronized void removeObjectChangeListener(ObjectChangeListener
							listener) 
  {
    if (listeners == null) {
      return;
    }
    listeners.removeElement(listener);
  }

  private Object getValidatedValue(final String string)
       throws G2SyntaxException, EOFException, IOException
  {
	String value = string;  
    if (fieldType.isText() && !showQuotesForTextType)
    	value = "\"" + value + "\"";
    Object object = fieldType.stringToObject(value);
    if (lowerLimitMode == null)
      setupDefaultLimits();
    if (fieldType.isNumeric())
      {
	if ((lowerLimitMode.isExclusive()) &&
	    (((Number)object).doubleValue() <= lowerLimit))
	  throw new G2SyntaxException("Value out of range: "+object+" <= "+lowerLimit);
	else if ((lowerLimitMode.isInclusive()) &&
		 (((Number)object).doubleValue() < lowerLimit))
	  throw new G2SyntaxException("Value out of range: "+object+" < "+lowerLimit);
	else if ((upperLimitMode.isExclusive()) &&
		 (((Number)object).doubleValue() >= upperLimit))
	  throw new G2SyntaxException("Value out of range: "+object+" >= "+upperLimit);
	else if ((upperLimitMode.isInclusive()) &&
		 (((Number)object).doubleValue() > upperLimit))
	  throw new G2SyntaxException("Value out of range: "+object+" > "+upperLimit);
      }
    return object;
  }

  private void setupDefaultLimits()
  {
    lowerLimitMode = new LimitMode();
    upperLimitMode = new LimitMode();
    lowerLimit = 0.0;
    upperLimit = 100.0;
  }

  protected void fireObjectChangeOnContents()
  {
    String textInField = getText();
    Object object = null;

    try {
      if (emptyFieldImpliesNull && textInField.equals(""))
	object = null;
      else
	object = getValidatedValue(textInField);
      if (object != null || emptyFieldImpliesNull) {
	fireObjectChange(object);
	oldText = textInField;
      }
    } catch (G2SyntaxException syntaxException)
      {
	// syntaxException.printStackTrace();
	if (warnOnBadSyntax)
	  warningDialog(syntaxException.getMessage());
      }
    catch (EOFException eof)
      {
	// eof.printStackTrace();
	if (warnOnBadSyntax)
	  warningDialog("Incomplete text");
      }
    catch (IOException e)
      {
	throw new UnexpectedException(e);
      }
  }

  private void warningDialog(String message)
  {
    if (!Beans.isDesignTime())
      {
	WarningDialog dialog 
	  = new WarningDialog(null,"",true,message,null);
	dialog.pack ();
	dialog.setVisible (true);
      }
  }

  /**  Invokes the ObjectChanged method on each of this beans ObjectChange
  * listeners
  */
  void fireObjectChange(Object newObject)
  {
    java.util.Vector targets;
    synchronized (this) {
      if (listeners == null) {
	return;
      }
      targets = (java.util.Vector) listeners.clone();
    }
    
    ObjectChangeEvent evt;
    if (attributeName.equals(""))
       evt = new ObjectChangeEvent(this, newObject);
    else
       evt = new ObjectChangeEvent(this, newObject, attributeName);

    for (int i = 0; i < targets.size(); i++) {
      ObjectChangeListener target = (ObjectChangeListener)targets.elementAt(i);
      target.objectChanged(evt);
    }
  }
  
  /** Specialization of the AWT method.  Currently does nothing interesting.
   */
  @Override
  public Dimension getPreferredSize()
  {
    Dimension size = super.getPreferredSize();
    return size;
  }

}

