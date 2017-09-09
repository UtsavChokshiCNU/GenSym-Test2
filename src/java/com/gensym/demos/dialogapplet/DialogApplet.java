package com.gensym.demos.dialogapplet;

import java.applet.Applet;
import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.lang.*;
import java.net.*;
import com.gensym.dlgruntime.*;
import com.gensym.controls.*;
import com.gensym.classes.Item;
import com.gensym.net.g2.*;
import com.gensym.core.GensymApplication;
import com.gensym.message.Trace;

import com.sun.media.util.JMFSecurity;

public class DialogApplet
    extends Applet
    implements MouseListener, KeyListener
{
  boolean isStopped;
  String hostName;
  String portName;
  boolean willWork = true;
  URL url;
  
  @Override
  public synchronized void init() 
  {
    try {
      try {
	JMFSecurity.enablePrivilege.invoke(JMFSecurity.privilegeManager,
					   JMFSecurity.writePropArgs);
	JMFSecurity.enablePrivilege.invoke(JMFSecurity.privilegeManager,
					   JMFSecurity.readPropArgs);
	JMFSecurity.enablePrivilege.invoke(JMFSecurity.privilegeManager,
					   JMFSecurity.connectArgs);
      } catch (Exception e) {}
      
      G2ProtocolRegistry.loadInterpreters();
      String homeDir = System.getProperty("user.home");
      System.out.println("homDir "+homeDir);
      String altDir = System.getProperty("java.home");
      System.out.println("altDir"+altDir);
      GensymApplication.initialize();

      System.out.println("param is "+getParameter("resource"));
      System.out.println("sec manager "+System.getSecurityManager());
      System.out.println("class loader "+getClass().getClassLoader());
      hostName = getParameter("host");
      portName = getParameter("port");
      url = new URL(getParameter("resource"));
      System.out.println("url "+url);
      repaint();
    } catch (Exception e)
      {
	Trace.exception (e);
	willWork = false;
      }
  }
  
  @Override
  public void stop() {
    isStopped = true;
  }
  
  @Override
  public void start() {
    System.out.println("start()");
    isStopped = false;
    if (willWork)
      try 
      {
	DialogAppletResource res = new DialogAppletResource(url);
	System.out.println("res= "+res+" url "+url);
	Thread.dumpStack();
	res.launchForTesting(this);
	repaint();
      } catch (Exception e)
	{
	  e.printStackTrace();
	}
    

  }
  
  @Override
  public void destroy() {
    
  }
  
  @Override
  public synchronized void paint(Graphics g) {
    super.paint (g);
  }

      //1.1 event handling
      
  @Override
  public void mouseClicked(MouseEvent e)
  {}
      
  @Override
  public void mousePressed(MouseEvent e)
  {
  }

  @Override
  public void mouseReleased(MouseEvent e) 
  {}
      
  @Override
  public void mouseEntered(MouseEvent e)
  {}
      
  @Override
  public void mouseExited(MouseEvent e)         
  {}

  @Override
  public void keyPressed(KeyEvent e)
  {
  
  }
  
  @Override
  public void keyTyped(KeyEvent e) {
  }
  
  @Override
  public void keyReleased(KeyEvent e)
  {}   
      
  @Override
  public String getAppletInfo() {
    return "Title: My wonderful applet";
  }
      
  @Override
  public String[][] getParameterInfo() {
    String[][] info = {
      {"resource", "string", "The URL of the dialog resource"}
    };
    return info;
  }


}

  
