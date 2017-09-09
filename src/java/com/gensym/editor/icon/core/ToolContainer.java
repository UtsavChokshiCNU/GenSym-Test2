package com.gensym.editor.icon.core;

import javax.swing.Scrollable;
import java.awt.*;

public class ToolContainer extends Container
implements Scrollable
{
  public Color current_color = new Color (128, 128, 128);
  private Color background_color = Color.white;
  private transient Container nativeContainer = null;
  private transient Cursor outerCursor = null;
  private Tool eventHandler;
  private int element_count = 0;

  public ToolContainer()
  {
    enableEvents(AWTEvent.MOUSE_EVENT_MASK);
  }

  @Override
  public Dimension getPreferredSize() {
    return new Dimension(100,100);
  }
  
  @Override
  public Dimension getPreferredScrollableViewportSize() {
    return getPreferredSize();
  }

  @Override
  public int getScrollableBlockIncrement(Rectangle visibleRect,
					 int orientation, int direction) {
    return 8;
  }

  @Override
  public boolean getScrollableTracksViewportHeight() {
    return false;
  }

  @Override
  public boolean getScrollableTracksViewportWidth() {
    return false;
  }
  
  @Override
  public int getScrollableUnitIncrement(Rectangle visibleRect,
					int orientation, int direction)
  {
    return 4;
  }
  
  public void invalidate(Object obj) {
    repaint();
  }

  public void invalidateElement(Object obj) {
    repaint();
  }  
  
  public Component findElement(int x,int y) {
    return getComponentAt(x,y);
  }

  public void setBackgroundColor(Color color)
  {
    background_color = color;
  }

  public Color getBackgroundColor()
  {
    return background_color;
  }

  @Override
  public void addNotify()
  {
    super.addNotify();
    Container parent = this;

    while (! ((parent instanceof Panel) ||
	      (parent instanceof ScrollPane) ||
	      (parent instanceof Window)))
      parent = parent.getParent();
    nativeContainer = parent;
  }

  public void pushCursor(Cursor cursor)
  {
    outerCursor = nativeContainer.getCursor();
    nativeContainer.setCursor(cursor);
  }

  public void popCursor()
  {
    nativeContainer.setCursor(outerCursor);
    outerCursor = null;
  }
  
  @Override
  public synchronized void paint (Graphics g)
  {
    paintBackground(g);
    super.paint(g);
    if (eventHandler != null)
      eventHandler.Draw(g);
  } 

  protected void paintBackground(Graphics g)
  {
    Rectangle bounds = getBounds();
    g.setColor(background_color);
    g.fillRect(0,0,bounds.width,bounds.height);
  }

  public void addElement(Component element)
  {
    addElement(element, 0);
  }

  public void addElement(Component element,
			 int position) {
    add(element,position);
    if (element instanceof DrawElement)
      ((DrawElement)element).setCanvas(this);
    element.repaint();
  }
  
  public int getElementPosition(Component element)
  {
    Component[] elements = getComponents();
    int i, len = elements.length;

    for (i = 0; i<len ; i++)
      if (element == elements[i])
        return i;
    return -1;
  }

  public void moveElementUp(Component element)
  {
    int count = getComponentCount();

    if (count > 1)
    {
      int index = getElementPosition(element);
      Component other_element = getComponent(index - 1);

      remove(index - 1);
      remove(index - 1);
      add(other_element,index - 1);
      add(element, index - 1);
    }
  }

  public void moveElementDown (Component element)
  {
    int count = getComponentCount();

    if (count > 1)
    {
      int index = getElementPosition(element);
      Component other_element = getComponent(index + 1);

      remove(index);
      remove(index);
      add(element,index);
      add(other_element,index);
    }
  }

  public void moveElementToTop(Component element)
  {
    int count = getComponentCount();

    if (count > 1)
    {
      int index = getElementPosition(element);
      remove(index);
      add(element,0);
    }
  }

  public void moveElementToBottom(Component element)
  {
    int count = getComponentCount();

    if (count > 1)
    {
      int index = getElementPosition(element);
      remove(index);
      add(element,-1);
    }
  }

  public void removeElement(Component element)
  {
    Rectangle bounds[] = null;
    if (element instanceof DrawElement)
      bounds = ((DrawElement)element).getExactBounds();
    else {
	bounds = new Rectangle[1];
	bounds[0] = element.getBounds();
    }
    remove(element);
    for (int i=0;i<bounds.length;i++) {
      Rectangle bnd = bounds[i];
      repaint(bnd.x,bnd.y,bnd.width,bnd.height);
    }
  }

  public void setEventHandler(Tool eh)
  {
    if (eventHandler != null)
        eventHandler.deregisterListeners (this);
    eventHandler = eh;
    if (eventHandler != null)
      eventHandler.registerListeners (this);
  }

  public Tool getEventHandler()
  {
    return eventHandler;
  }


}

