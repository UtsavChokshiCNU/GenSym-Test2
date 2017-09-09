package com.gensym.wksp;

import java.util.Locale;
import java.awt.*;
import java.awt.event.*;
import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.draw.*;
import com.gensym.dispatcher.*;
import com.gensym.classes.Item;
import com.gensym.classes.CheckBox;
import com.gensym.classes.RadioButton;
import com.gensym.classes.KbWorkspaceImpl;
import com.gensym.jgi.G2AccessException;
import com.gensym.ntw.TwAccess;
import com.gensym.jgi.G2ConnectionListener;
import com.gensym.jgi.G2ConnectionEvent;
import com.gensym.jgi.G2CommunicationErrorEvent;

public interface WorkspaceViewListener extends //TableDrivenEventHandler
//implements
java.io.Serializable
{

  public static final int LASSO = 0;
  public static final int DRAG = 1;
  public static final int CONNECTION_DRAG = 2;
  public static final int BUTTON_PRESS = 3;
  public static final int RESIZING = 4;
  public static final int SLIDER_DRAG = 5;
  
  public abstract void doConnectionDragMousePressed(MouseEvent e,//unconfigurable-->private
					   Component d,
					   PersistentCanvas canvas)
       throws IllegalAccessException;

  public abstract void doConnectionMousePressed(MouseEvent e)
       throws IllegalAccessException;

  public abstract void doWorkspaceElementMousePressed(MouseEvent e)
       throws G2AccessException, IllegalAccessException;
       
  public abstract void postContextMenu (MouseEvent e)
       throws IllegalAccessException;

  public abstract void noteSliderPress (MouseEvent e, SliderInput sliderInput)//unconfigurable-->private
       throws IllegalAccessException;

  public void doResizePress (MouseEvent e, MarkerElement marker)//unconfigurable-->private?
       throws IllegalAccessException;

  public abstract void doSliderDrag (MouseEvent e);
    
  public abstract void doResizeDrag (MouseEvent e);//unconfigurable-->private?

  public abstract void doSliderRelease (MouseEvent e);

  public abstract void doResizeRelease (MouseEvent e);//unconfigurable-->private?

       //private abstract void doButtonPress (MouseEvent e) throws IllegalAccessException;

  public abstract void doButtonDrag (MouseEvent e);//unconfigurable-->private

  public abstract void doButtonRelease (MouseEvent e);
  
  public abstract void doDragPress (MouseEvent e)
       throws IllegalAccessException;
  
  public abstract void doDragDrag (MouseEvent e);//unconfigurable-->private
       
  public abstract void doDragRelease (MouseEvent e,
				      boolean enlargeWorkspaceIfNeccessary)
       throws IllegalAccessException;

  public abstract void endDragState(MouseEvent e);
  
  public abstract void doConnectionDragPress(MouseEvent e);
       
  public abstract void doConnectionDragDrag (MouseEvent e);//unconfigurable-->private

  public abstract void doConnectionDragRelease (MouseEvent e);
  
  public abstract void doLassoPress (MouseEvent e);

  public abstract void doLassoDrag (MouseEvent e)//unconfigurable-->private
       throws IllegalAccessException;

  public abstract void doLassoRelease (MouseEvent e)//unconfigurable-->private
       throws IllegalAccessException;
  
  public abstract void doMouseClicked(MouseEvent e);
       
}
