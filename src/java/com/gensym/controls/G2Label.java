/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 G2Label.java
 *
 */

package com.gensym.controls;

import java.awt.*;
import java.io.IOException;
import com.gensym.beansruntime.Enum;
import com.gensym.util.Symbol;
import com.gensym.util.UnexpectedException;
import com.gensym.message.Resource;
import java.util.MissingResourceException;
import com.gensym.dlgevent.ObjectUpdateListener;
import com.gensym.dlgevent.ObjectUpdateEvent;
import com.gensym.dlgevent.ObjectChangeListener;
import com.gensym.dlgevent.ObjectChangeEvent;
import com.gensym.message.Trace;

/** A label bean which is capable of storing a G2 item attribute
*/
public class G2Label extends Canvas implements ObjectUpdateListener
{
  /*
   * Allow deserialization
   */
  static final long serialVersionUID = -5349440256454089047L;

  static final int TEXT_XPAD = 12;
  static final int TEXT_YPAD = 8;

  public static final int LEFT = 0;
  public static final int CENTER = 1;
  public static final int RIGHT = 2;

  private String label = "Label:";
  private String attributeName = "";
  private Symbol attributeSymbol = null;
  private String defaultContents = "";
  private FieldType fieldType = new FieldType();
  private String   resourceName = "";
  private String   labelKey     = "";
  private transient Resource bundle = null;
  /**
   * Implementation of this property is reversed from the implementation in
   * G2TextField, so that old components will continue
   * to behave as they have in the past when deserialized.
   * This is because old saved G2Labels will not have the
   * following field, which will cause defaultReadObject
   * to initialize the field with the default for this
   * type, which is "false". The visual representation is the same
   * for user consistency.
   */
  private boolean hideQuotesForTextType = false;
  private Enum alignment;

  /** Contructor for this bean
   */
  public G2Label ()
  {
    alignment = new Enum(new String[]{"Left", "Center", "Right"}, 
                         new int[]{LEFT, CENTER, RIGHT}, RIGHT);
  }

  /** Gets the name of the G2 Item attribute which this bean is
   * storing as a Symbol.
   * @see com.gensym.util.Symbol
   */ 
 public Symbol getAttribute()
  {
    return attributeSymbol;
  }

  /** Sets the name of the G2 Item attribute which this bean is
   * storing from a Symbol.
   * @see com.gensym.util.Symbol
   */
  public void setAttribute(Symbol symbol)
  {
    attributeSymbol = symbol;
    attributeName = symbol.toString();
  }

  /** Gets the G2 item attribute type information for this bean
  */
  public FieldType getFieldType()
  {
    return fieldType;
  }

  /** Sets the G2 item attribute type information for this bean
  */
  public void setFieldType(FieldType type)
  {
    fieldType = type;
  }
  
  /** Paints the Graphics context for this bean
  */
  @Override
  public synchronized void paint(Graphics g)
  {
    int width = getSize().width;
    int height = getSize().height;
    
    g.setColor(getBackground());
    g.fillRect(0, 0, width - 1, height - 1);

    if (!isEnabled())
      g.setColor(Color.white);
    else
      g.setColor(getForeground());
    g.setFont(getFont());
       
    FontMetrics fm = g.getFontMetrics();
    int x = width - fm.stringWidth(label);
    if (alignment != null){
      int align = alignment.value;
      if (align == CENTER)
	x = (width - fm.stringWidth(label))/2;
      else if (align == LEFT)
	x = 1;
    }

    g.drawString(label, x, 
		 (height + fm.getMaxAscent() - fm.getMaxDescent()) / 2);

    if (!isEnabled()){
      g.setColor(Color.gray);
      g.drawString(label, x-1, 
		   ((height + fm.getMaxAscent() - fm.getMaxDescent()) / 2)-1);
      
    }
  }

  /**  Sets the font of this bean
  */
  @Override
  public void setFont(Font f)
  {
    Font old = getFont();
    super.setFont(f);
  }
  
  /** Sets the label of this bean
  */
  public void setLabel(String newLabel)
  {
    String oldLabel = label;
    label = newLabel;
    repaint();
  }
  
  /** Gets the label of this bean
  */
  public String getLabel()
  {
    return label;
  }
  
  public void setAlignment(Enum alignment){
    this.alignment = alignment;
    repaint();
  }

  public Enum getAlignment(){
    return alignment;
  }
  

  @Override
  public Dimension getMinimumSize(){
    return getPreferredSize();
  }

  /** Gets the preferred Size for this bean
  */
  @Override
  public Dimension getPreferredSize()
  {
    Font font = getFont();
    if (font == null)
      return new Dimension(TEXT_XPAD, TEXT_YPAD);
    else{
      FontMetrics fm = getFontMetrics(font);
      return new Dimension(fm.stringWidth(label) + TEXT_XPAD, 
			   fm.getMaxAscent() + fm.getMaxDescent() + TEXT_YPAD);
    }
  }

  /**  This method responds to objectUpdateEvents by setting the text
  * of the bean and updating the G2 item attribute it is storing
  */
  @Override
  public void objectUpdated(ObjectUpdateEvent e)
  {
    Object fieldValue = e.getUpdatedValue(attributeSymbol,defaultContents);
    
    try {
      String labelText = fieldType.objectToString(fieldValue);
      if (fieldType.isText() && hideQuotesForTextType)
	labelText = labelText.substring(1,(labelText.length() - 1));
      setLabel(labelText);
    } catch (IOException ioException)
      {
	throw new UnexpectedException(ioException);
      }

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
    return !hideQuotesForTextType;
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
    this.hideQuotesForTextType = !showQuotesForTextType;
  }

  /** 
   * Sets the label key for this bean.  The labelKey is used to 
   * lookup a string in the resource bundle named by the resource
   * property.
   */
  public void setLabelKey(String labelKey)  
  {
    this.labelKey = labelKey;

    if (bundle != null)
    {
      try
      {
        setLabel(bundle.getString(labelKey));
      }
      catch (MissingResourceException ex)
      {
        Trace.exception (ex, null);
      }
    }
  }

  /** Returns the label key for this bean.
   */
  public String getLabelKey()  
  {
    return labelKey;  
  }

  /** Sets the name of the resource for internationalization.
   *  The labelKey will be used in as an index into the resource
   *  to find a label for the Button.
   * @param  resourceName String
   * @see com.gensym.controls.G2Button#getLabelKey
   */
  public void setResourceName(String resourceName)
  {
    this.resourceName = resourceName;
    
    try
    {
      bundle = ResourceUtil.getBundle(resourceName);
      if (bundle != null)
        setLabel(bundle.getString(labelKey));
    }
    catch (MissingResourceException ex)
    {
      Trace.exception (ex, null);
    }
  }

  /** Returns the name of the resource for Internationalization.
   *  The labelKey will be used in as an index into the resource
   *  to find a label for the Button.
   * @return the resource's name
   * @see com.gensym.controls.G2Button#getLabelKey
   */
  public String getResourceName()
  {
    return resourceName; 
  }  

  private void readObject(java.io.ObjectInputStream stream) throws
                   java.lang.ClassNotFoundException, java.io.IOException,
                   java.io.NotActiveException
  {
    stream.defaultReadObject();
    setResourceName(resourceName); // refreshes bundle and label in possibly new locale
    if (alignment == null)
      alignment = new Enum(new String[]{"Left", "Center", "Right"}, 
                         new int[]{LEFT, CENTER, RIGHT}, RIGHT);
  } 

}
