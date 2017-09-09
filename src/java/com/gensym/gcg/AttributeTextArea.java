package com.gensym.gcg;

import java.awt.*;
import java.awt.event.*;
import java.util.StringTokenizer;
import java.util.Locale;

import com.gensym.editor.text.Session;
import com.gensym.classes.Item;
import com.gensym.util.Symbol;
import com.gensym.ntw.TwAccess;
import com.gensym.message.*;

public class AttributeTextArea extends TextArea 
  implements MouseListener, KeyListener
{
  AttributeDialogInfo info;
  Item item;
  Item subItem;
  Symbol userMode;
  TwAccess connection;
  boolean isModal;
  Locale locale;

  public AttributeTextArea(String initialText, AttributeDialogInfo info,
			   Item item, Symbol userMode,
			   TwAccess connection, boolean isModal,
			   Item subItem,
			   Locale locale)
  {
    super(initialText,1,25,TextArea.SCROLLBARS_VERTICAL_ONLY);
    this.info = info;
    this.item = item;
    this.userMode = userMode;
    this.connection = connection;
    this.isModal = isModal;
    this.subItem = subItem;
    this.locale = locale;
    setEditable(false);
    addKeyListener(this);
    if (info.isTextWritable)
      {
	addMouseListener(this);
	setBackground(new Color(240,240,240));
      }
  }

  /*
  void objectUpdated(ObjectUpdateEvent e)
  {
    String newText = (String) e.getUpdatedObject();
    System.out.println("ATA received Object update "+newText);
    setText(newText);    
  }
  */
  
  private void edit()
  {
    if (subItem == null)
      new Session(item, info.simpleAttributeName, 
		  info.definingClass);
    else
      {
	try
	  {
	    connection.getDialogManager().editItem(this, subItem,userMode,locale);
	  }
	catch (Exception e)
	  {
	    Trace.exception(e);
	  }
      }
  }

  @Override
  public void keyPressed(KeyEvent e)
  {
    if (e.getKeyCode() == KeyEvent.VK_TAB)
      transferFocus();
    else if (e.getKeyCode() == KeyEvent.VK_ENTER)
      edit();
  }

  @Override
  public void keyTyped(KeyEvent e)
  {
  }

  @Override
  public void keyReleased(KeyEvent e)
  {
  }

  @Override
  public void mouseClicked(MouseEvent e)
  {
  }

  @Override
  public void mousePressed(MouseEvent e)
  {
  }

  @Override
  public void mouseReleased(MouseEvent e)
  {
    if (!e.isPopupTrigger())
      edit();
  }

  @Override
  public void mouseEntered(MouseEvent e)
  {
  }

  @Override
  public void mouseExited(MouseEvent e)
  {
  }

  @Override
  public Dimension getPreferredSize()
  {
    Dimension size = super.getPreferredSize();
    StringTokenizer tokenizer = new StringTokenizer(getText(),"\n");
    int lineCount = 1 + tokenizer.countTokens();
    Font font = getFont();
    try {
      FontMetrics metrics = getFontMetrics(font);
      size.height = metrics.getHeight() * lineCount;
    } catch (Exception e)
      {
	e.printStackTrace();
      }
    return size;
  }
}
