package com.gensym.wksp;

import java.awt.*;
import java.awt.event.*;
import java.util.Observer;
import java.util.Observable;
import java.text.*;
import com.gensym.irm.*;
import com.gensym.draw.*;
import com.gensym.ntw.*;
import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.draw.TextBoxElement;
import com.gensym.draw.TextStyle;
import com.gensym.jgi.G2AccessException;
import com.gensym.dlg.WarningDialog;
import com.gensym.ntw.util.G2FontMap;


/**
 * EditContext
 */

public class EditContext extends BasicDrawElement
implements KeyListener,  MouseListener
{
  private Dimension minSize;
  private static int padding = 7;
  private static int minBufferSize = 10;
  private char[] charBuffer = new char[minBufferSize];
  private int currentIndex = 0;
  private int currentLength = 0;
  private boolean insertMode = true;
  private static final Font defaultFont = G2FontMap.get(18);
  private Font theFont = defaultFont;
  private Editable itemBeingEdited;
  private TextCell textCell;
  private int mostRecentX = -1;
  private static boolean windows = false;
  static {
    try {
      windows = isWindows();
    } catch (Exception e) {
      //if we don't match then assume it's not windows
    }
  }
  
  private static boolean isWindows() {
    return System.getProperty ("os.name").toLowerCase().indexOf ("windows") >= 0;
  }

  public EditContext(Editable editable,
		     int width,
		     TextStyle style) {
    this.textCell = new TextCell(width, 
				 "",
				 style,
				 Color.white,//bg
				 Color.black,//text
				 0,//border_width,
				 Color.black//Color border_color
				 );
    this.minSize = new Dimension(20,20);
    this.itemBeingEdited = editable;
    this.addKeyListener (this);
    this.addMouseListener(this);
  }

  private void ensureCapacity(int minC) {
    int maxC = charBuffer.length;
    if (minC>maxC) {
      int newC = (maxC + 1) * 2;
      if (minC > newC) {
	newC = minC;
      }
      char newValue[] = new char[newC];
      System.arraycopy(charBuffer, 0, newValue, 0, currentLength);
      charBuffer = newValue;
    }
  }

  private void insert(int offset, char newChars[]) {
    if ((offset < 0) || (offset > currentLength)) {
      return;//throw new StringIndexOutOfBoundsException();
    }
    int len = newChars.length;
    ensureCapacity(currentLength + len);
    System.arraycopy(charBuffer, offset, charBuffer, offset + len, currentLength - offset);
    System.arraycopy(newChars, 0, charBuffer, offset, len);
    currentLength += len;
  }
  
  static Dimension computeTextStringDimensions(String string,
					       FontMetrics metrics)
  {
    int stringWidth = 0, maxWidth = 0;
    int stringHeight = lineHeight;
    char currentChar;
    if (string != null) {
      int charCount = string.length();
      for (int i=0;i<charCount;i++) {
	currentChar = string.charAt(i);
	if (currentChar == '\n') {
	  stringHeight+=lineHeight;
	  stringWidth = 0;
	} else {
	  stringWidth = stringWidth + metrics.charWidth(currentChar);
	  maxWidth = Math.max(maxWidth, stringWidth);
	}
      }
    }
    return new Dimension(maxWidth, stringHeight);
  }

  private boolean adjustSize() {
    Rectangle bounds = getBounds();
    FontMetrics metrics
      = Toolkit.getDefaultToolkit().getFontMetrics(theFont);
    Dimension d = computeTextStringDimensions(toString(), metrics);
    int currentStringWidth=d.width;
    int currentStringHeight=d.height;
    bounds.width = Math.max(minSize.width, currentStringWidth + 2*padding);
    bounds.height = Math.max(minSize.height, currentStringHeight + 3*padding);
    setBounds(bounds);
    textCell.setWidth(bounds.width);
    return true;
  }

  @Override
  public void setFont(Font newFont) {
    theFont = newFont;
  }
  
  public boolean isInsertMode() {
    return insertMode;
  }

  public void setInsertMode(boolean newMode) {
    this.insertMode = newMode;
  }
  
  public int getIndex() {
    return currentIndex;
  }

  public int getEndIndex() {
    return currentLength;
  }

  public void setIndex(int newIndex) {
    currentIndex = Math.max(0,Math.min(currentLength,newIndex));
    canvas.invalidateElement(this);
  }

  @Override
  public Rectangle[] getExactBounds() {
    return new Rectangle[] {getBounds()};
  }

  @Override
  public boolean inside(int logical_x, int logical_y)
  {
    return contains(logical_x, logical_y);
  }

  @Override
  public boolean contains(int x, int y)
  {
    Rectangle[] bounds = getExactBounds();
    x = x + bounds[0].x;
    y = y + bounds[0].y;
    int length = bounds.length;

    for (int i = 0 ; i<length ; i++)
      if (bounds[i].contains(x,y))
        return true;

    return false;
  }

  public void clear() {
    charBuffer = new char[10];
    setIndex(0);
    currentLength = 0;
    adjustSize();
    setTextCellText();
    canvas.invalidateElement(this);
  }

  public void deleteChars(int start, int end) {
    int newLength = currentLength-(1 + (end-start));
    char[] newBuffer = new char[Math.max(minBufferSize,newLength)];
    System.arraycopy(charBuffer, 0,
		     newBuffer, 0,
		     start);
    System.arraycopy(charBuffer, end+1,
		     newBuffer, start,
		     currentLength-(end+1));
    charBuffer = newBuffer;
    currentLength = newLength;
    Rectangle[] bounds = getExactBounds();
    adjustSize();
    setTextCellText();
    canvas.invalidate(bounds);
    canvas.invalidateElement(this);
  }
  
  public void deleteBackwardChar() {
    int prevIndex = currentIndex-1;
    if (currentIndex == currentLength) {
      charBuffer[prevIndex] = ' ';
      currentLength--;      
    } else {
      deleteChars(prevIndex, prevIndex);
    }
    setIndex(prevIndex);
    adjustSize();
    setTextCellText();
    canvas.invalidateElement(this);
  } 

  public void deleteFowardChar() {
    if (currentIndex < currentLength) {
      if (currentIndex == currentLength) {
	charBuffer[currentIndex] = ' ';
	currentLength--;	
      } else {
	deleteChars(currentIndex, currentIndex);
      }
    } else {
      //System.out.println("CANT DELETE ANY MORE");
    }
    adjustSize();
    setTextCellText();
    canvas.invalidateElement(this);
  }
  
  @Override
  public void setMinimumSize(Dimension d) {
    minSize = d;
  }

  @Override
  public Dimension getMinimumSize() {
    return minSize;
  }
    
  public void addString(String string) {
    int len = string.length();
    char[] newChars = new char[len];
    string.getChars(0, len, newChars, 0);
    insert(currentIndex, newChars);
    setIndex(currentIndex + len);
    adjustSize();
    setTextCellText();
    canvas.invalidateElement(this);
  }
  
  public void addChar(char newChar) {
    if (insertMode || currentIndex == currentLength) {
      ensureCapacity(currentLength+1);
      insert(currentIndex, new char[]{newChar});
    } else {
      charBuffer[currentIndex] = newChar;
    }
    setIndex(currentIndex + 1);
    adjustSize();
    setTextCellText();
    canvas.invalidateElement(this);
  }

  private void setTextCellText() {
    String str = toString();
    if (str != null)
      textCell.setText(toString());
    else
      textCell.setText(" ");
  }
    
  @Override
  public String toString() {
    if (currentLength != 0) 
      return new String(charBuffer, 0, currentLength);
    else
      return null;
  }
  private static int lineHeight = 21;
  
  public int getIndex(int xpos, int ypos, FontMetrics metrics)
  {
    int currentX=0, currentY=padding+lineHeight,charWidth;
    char currentChar;
    for (int i=0; i<currentLength;i++) {
      currentChar = charBuffer[i];
      if (currentChar == '\n') {
	if (ypos <= currentY) return i;
	currentX=0;
	currentY+=lineHeight;
      } else {
	charWidth = metrics.charWidth(currentChar);
	if ((xpos <= (currentX + charWidth/2)) &&
	    (ypos <= (currentY)))
	  return i;
	currentX=currentX+charWidth;
      }
    }
    return currentLength;
  }

  public Point getCharLocation(int index, FontMetrics metrics) {

    if (index > currentLength || index <0)
      return new Point(0,0);
    int currentX=0, currentY = padding + lineHeight, charWidth;
    char currentChar;
    for (int i=0; i<index;i++) {
      currentChar = charBuffer[i];
      if (currentChar == '\n') {
	currentY+=lineHeight;
	currentX=0;
      } else {
	charWidth = metrics.charWidth(currentChar);
	currentX=currentX+charWidth;
      }
    }
    return new Point(currentX,currentY);
  }
  
  @Override
  public void paint(Graphics g) {
    g.setFont(theFont);
    FontMetrics metrics = g.getFontMetrics();
    Rectangle bounds=getBounds();
    int width = bounds.width;
    int height = bounds.height;
    g.setColor(Color.white);
    g.fillRect(0,0,width-1,height-1);
    g.setColor(Color.black);
    int top = (2*height)/3;
    int left = padding;
    textCell.draw(g, padding, padding);
    int cursorWidth = metrics.charWidth('^');
    int cursorHeight = 9;
    int currentIndex = getIndex();
    Point indexPos = getCharLocation(currentIndex, metrics);
    int cursorX = indexPos.x;
    int cursorY = indexPos.y+cursorHeight;
    int cursorLeft
      = Math.min(width-(padding +cursorWidth),
		 Math.min(left, 0)+cursorX);
    g.drawString("^",cursorLeft + cursorWidth/2, cursorY);
    g.setColor(Color.black);
    g.drawRect(0,0,width-1,height-1);
  }

  @Override
  public void keyPressed(KeyEvent e)
  {
    char key = e.getKeyChar();
    int keyCode = e.getKeyCode();
    switch (keyCode) {
    case KeyEvent.VK_CANCEL:
    case KeyEvent.VK_ESCAPE:
      itemBeingEdited.setEditing(false);
      mostRecentX=-1;
      break;
    case KeyEvent.VK_CONTROL:
    case KeyEvent.VK_ALT:
    case KeyEvent.VK_META:
      break;
    case KeyEvent.VK_ENTER:
    case KeyEvent.VK_ACCEPT:      
      Object newValue;
      String editString = toString();
      try {
	itemBeingEdited.setValue(editString);
      } catch (InvalidTypeException ite) {
	/*addChar('.'); addChar('.'); addChar('.');*/
	new WarningDialog(null, "Invalid Type", true, ite.getMessage(), null).setVisible(true);
	return;
      }
      itemBeingEdited.setEditing(false);      
      break;
    case KeyEvent.VK_TAB:
      mostRecentX=-1;
      addChar(' ');
      addChar(' ');
      addChar(' ');
      addChar(' ');
      break;
    case KeyEvent.VK_CLEAR:
      mostRecentX=-1;
      clear();
    case KeyEvent.VK_INSERT: 
      setInsertMode(!isInsertMode());
      break;
    case KeyEvent.VK_DOWN:
      int currentIndex = getIndex();
      Rectangle bounds = getBounds();
      FontMetrics metrics
	= Toolkit.getDefaultToolkit().getFontMetrics(theFont);
      Point d = getCharLocation(currentIndex, metrics);
      if (mostRecentX == -1)
	mostRecentX = d.x;
      else
	d.x = mostRecentX;
      d.y  = d.y+lineHeight;
      if (!(d.y > bounds.height)) {
	int newIndex = getIndex(d.x,d.y, metrics);
	setIndex(newIndex);
      }
      break;
    case KeyEvent.VK_UP:
      currentIndex = getIndex();
      bounds = getBounds();
      metrics
	= Toolkit.getDefaultToolkit().getFontMetrics(theFont);
      d = getCharLocation(currentIndex, metrics);
      if (mostRecentX == -1)
	mostRecentX = d.x;
      else
	d.x = mostRecentX;
      d.y = Math.max(0,d.y-lineHeight);
      int newIndex = getIndex(d.x,d.y, metrics);
      setIndex(newIndex);
      break;
    case KeyEvent.VK_LEFT:
      mostRecentX=-1;
      setIndex(getIndex()-1);
      break;
    case KeyEvent.VK_RIGHT:
      mostRecentX=-1;
      setIndex(getIndex()+1);
      break;
    case KeyEvent.VK_SHIFT:
    case KeyEvent.VK_CAPS_LOCK:
      break;
    case KeyEvent.VK_DELETE:
      mostRecentX=-1;
      deleteFowardChar();
      break;
    case KeyEvent.VK_END:
      mostRecentX=-1;
      setIndex(getEndIndex());
      break;
    case KeyEvent.VK_HOME:
      mostRecentX=-1;
      setIndex(0);
      break;
    case KeyEvent.VK_BACK_SPACE:
      mostRecentX=-1;
      deleteBackwardChar();
      break;
      // NOTE: the following cases need restructuring.
      // be very careful!!!
    case KeyEvent.VK_X:
      if (e.isControlDown()) {
	mostRecentX=-1;
	currentIndex = getIndex();
	deleteChars(0, currentIndex-1);
	setIndex(0);
	break;
      }
    case KeyEvent.VK_J:
      if (e.isControlDown()) {
	mostRecentX=-1;
	addChar('\n');
	break;
      }
    case KeyEvent.VK_A:
      if (e.isControlDown()) {
	mostRecentX=-1;
	itemBeingEdited.setEditing(false);
	break;
      }
    default:
      // paranoid simplified restructuring of existing logic.
      // done this way for ease of comparison
      if (keyCode == KeyEvent.VK_UNDEFINED && windows)
	//BUG FOUND ON SOLARIS & HP; CAPITAL KEYS ARE UNDEFINED
	//SO WE NEED TO INCLUDE ALL UNDEFINED KEYS       
	break;
      else if (!e.isActionKey() && !e.isControlDown()) {
	mostRecentX=-1;
	addChar(key);
      }
    }
  }
  
  @Override
  public void keyTyped(KeyEvent e){}
  @Override
  public void keyReleased(KeyEvent e){}

  @Override
  public void mouseClicked (MouseEvent e) {
    mostRecentX = -1;
    requestFocus();
    FontMetrics metrics
      = Toolkit.getDefaultToolkit().getFontMetrics(theFont);
    String editString = toString();
    int x = e.getX (),y = e.getY ();
    Rectangle viewBounds = canvas.getViewBounds();
    x+=viewBounds.x;y+=viewBounds.y;
    Rectangle itemBounds = getBounds();
    x-=itemBounds.x;y-=itemBounds.y;
    int newIndex = getIndex(x, y,metrics);
    setIndex(newIndex);
  }
  
  @Override
  public void mousePressed (MouseEvent e) {}
  @Override
  public void mouseEntered (MouseEvent e) {}
  @Override
  public void mouseExited (MouseEvent e) {}
  public void mouseMoved(MouseEvent e) {}
  public void mouseDragged (MouseEvent e) {}
  @Override
  public void mouseReleased (MouseEvent e) {}

  @Override
  public void shift (int shift_x, int shift_y)
  {
    Point location = getLocation();
    setLocation(location.x + shift_x, location.y + shift_y);
  }
}
