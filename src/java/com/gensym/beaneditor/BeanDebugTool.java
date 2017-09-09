package com.gensym.beaneditor;

import java.awt.*;
import java.awt.event.*;
import java.lang.Math;
import com.gensym.draw.*;
import java.util.Vector;
import java.util.Locale;
import com.gensym.message.Trace;
import com.gensym.message.Resource;
import com.gensym.message.MessageKey;
import com.gensym.message.Message;
import com.gensym.util.Helper;

class BeanDebugTool extends EventHandler
  implements MouseListener, MouseMotionListener, ActionListener
{
  private boolean mouseDown = false;
  private BeanCanvas canvas;
  private Frame frame;
  private ViewScrollState horizontalState; 
  private ViewScrollState verticalState;
  private PopupMenu popup;
  private int gesture;

  private static final int UNDETERMINED_GESTURE = 0;

  // Standard Tracing Requirements
  static private MessageKey traceKey =
  Trace.registerMessageKey("com.gensym.beaneditor",
			   BeanEditTool.class);

  static private Resource i18nTrace =
  Trace.getBundle("com.gensym.beaneditor.translations",
		  Locale.getDefault());

  // Standard Messaging Requirements
  static private Resource i18n =
  Resource.getBundle("com.gensym.resources.Messages",
		     Locale.getDefault());
  static private int GUI_LEVEL = 2;

  private static final int DEF_TRACE_LEVEL = 5;
  private static final int DEF_WARN_LEVEL  = 2;

  public BeanDebugTool (PersistentCanvas parent, Frame newFrame)
  {   
    canvas = (BeanCanvas) parent;
    frame = newFrame; 
    horizontalState = canvas.getScrollState(true);
    verticalState = canvas.getScrollState(false);
  }

  @Override
  public void registerListeners(PersistentCanvas canvas)
  {

  }
  @Override
  public void deregisterListeners(PersistentCanvas canvas)
  {

  }

  @Override
  public void actionPerformed(ActionEvent e) 
  {
    String command = e.getActionCommand();
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
  public void mouseMoved(MouseEvent e)
  {  
  }
  @Override
  public void mouseDragged(MouseEvent e)
  {  
  }

}
