/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 *   BeanEditor Message Output Manager - BeanMessageOut.java
 *
 *     
 *   Modifications:
 *
 */


package com.gensym.beaneditor;

import java.awt.Frame;
import com.gensym.message.Message;
import com.gensym.message.MessageListener;
import com.gensym.message.MessageEvent;
import com.gensym.message.Resource;
import com.gensym.com.ActiveXTraceLevels;


/**
 *  This Class is used to catch messages which have been sent
 *  by classes belonging to the BeanEditor
 *
 */
     
class BeanMessageOut implements MessageListener, ActiveXTraceLevels
{ 
  public  static final int GUI_LEVEL = 2;
  private Frame frame;
    
  /**  A simple constructor which adds this class as a listener
   *  for errors messages related to the beaneditor 
   */
  public BeanMessageOut(Frame frame)
  {
    Message.addMessageListener(this, "com.gensym.beaneditor", Object.class, GUI_LEVEL);
    Message.addMessageListener(this, "com.gensym.com", Object.class, AX_ERROR);
    this.frame = frame;
  }
    
  /**  This method is called when a MessageEvent is received
   */
  @Override
  public void processMessageEvent(MessageEvent event)
  {
    String message, key;
    int x, y;

    x = frame.getLocation().x + frame.getSize().width/2;
    y = frame.getLocation().y + frame.getSize().height/2;
    message = event.getMessage();
    key = event.getMessageKey();

    if (key.equals("com.gensym.com")) {
      new ErrorDialog (frame, message, x, y, false);
    } else {
      new ErrorDialog (frame, message, x, y);
    }
  }
}


