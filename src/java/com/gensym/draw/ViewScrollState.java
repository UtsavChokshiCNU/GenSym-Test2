package com.gensym.draw;

import java.util.Observable;
import java.lang.Math;

public class ViewScrollState extends Observable
implements java.io.Serializable
{
  static final long serialVersionUID = -7858907401246759913L;
  protected int logical_min = 0;
  protected int logical_max = 100;
  protected int view_min = 0;
  protected int view_max = 100;
  private boolean isHorizontal;

  public ViewScrollState (boolean isHorizontal) {
    this.isHorizontal = isHorizontal;
  }

  public void setScrollState(int lmin, int lmax, 
			     int vmin, int vmax)
  {
    logical_min = lmin;
    logical_max = lmax;
    view_min = vmin;
    view_max = vmax;

    setChanged();
    notifyObservers();
  }

  @Override
  public String toString()
  {
   return "ScrollState[ Logical = "+logical_min+","+logical_max+
          " View = "+view_min+","+view_max+"]";
  }

  public void grow(int size, boolean setMinimum)
  {
    grow(size,setMinimum,view_max);
  }
   
  public void grow(int size, boolean setMinimum, int newViewMax)
  {
    if (setMinimum)
      logical_min -= size;
    else
      logical_max += size;
    view_max = newViewMax;
    setChanged();
    notifyObservers();
  }
  
  public void adjustView(int size)
  {
    int new_view_max = view_max + size;

    if (size > 0)
    {
      if (new_view_max > logical_max)
       {
         view_max = logical_max;
         view_min = Math.max(0,view_min - 
                               (new_view_max - logical_max));
       }
      else
      {
         view_max = new_view_max;
      }
    }
    else
    {
      view_max = Math.max(view_min,new_view_max);
    }
    setChanged();
    notifyObservers();
  }

  public void setView(int newMin, int newMax)
  {
    // no error checking yet
    view_min = newMin;
    view_max = newMax;
    setChanged();
    notifyObservers();
  }

  public void shift (int size)
  {
    int shift;

    if (size < 0)
      shift = (view_min + size < logical_min) ?
               logical_min - view_min : size;
    else
      shift = (view_max + size > logical_max) ?
               logical_max - view_max : size;

    /* System.out.println("size="+size+" view_min="+view_min+
                       " lmin="+logical_min+
                       " shift="+shift); */
    view_min += shift;
    view_max += shift;
    setChanged();
    notifyObservers();
  }

  public boolean isHorizontal () {
    return isHorizontal;
  }

  public int getLogicalMin () {
    return logical_min;
  }

  public int getLogicalMax () {
    return logical_max;
  }

  public int getViewMin () {
    return view_min;
  }

  public int getViewMax () {
    return view_max;
  }
}


