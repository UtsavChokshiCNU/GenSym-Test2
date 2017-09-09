package com.gensym.draw;

import java.awt.*;
import java.util.Hashtable;
import java.util.Vector;

public class ColorTable extends Hashtable
{
  static final long serialVersionUID = -3394283550830869343L;
  Vector observers = new Vector();

  public ColorTable ()
  {
    super(100);
  }

  public Object put(Object key, Color color)
  {
    Object res = super.put(key,color);
    notifyObservers(key);
    return res;
  }

  @Override
  public Object remove(Object key)
  {
    Object res = super.remove(key);
    notifyObservers(key);
    return res;
  }

  public Color lookup(Object key)
  {
    return (Color) get(key);
  }

  @Override
  public void clear()
  {
    super.clear();
    notifyObservers(null);
  }

  public void addColorTableListener(ColorTableListener listener)
  {
    observers.addElement(listener);
  }

  private void notifyObservers(Object key)
  {
    ColorTableEvent event = new ColorTableEvent(this,key);
    int len = observers.size();
    for (int i = 0 ; i < len ; i++)
      ((ColorTableListener)observers.elementAt(i))
	.colorTableChanged(event);
  }

  public static ColorTable createDefaultColorTable()
  {
    ColorTable colorTable = new ColorTable();

    colorTable.put("black",Color.black);
    colorTable.put("darkGray",Color.darkGray);
    colorTable.put("gray",Color.gray);
    colorTable.put("lightGray",Color.lightGray);
    colorTable.put("white",Color.white);
    colorTable.put("red",Color.red);
    colorTable.put("pink",Color.pink);
    colorTable.put("orange",Color.orange);
    colorTable.put("yellow",Color.yellow);
    colorTable.put("green",Color.green);
    colorTable.put("magenta",Color.magenta);
    colorTable.put("cyan",Color.cyan);
    colorTable.put("blue",Color.blue);

    return colorTable;
  }

 
}
