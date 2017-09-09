/*
 *
 * Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * GENSYM MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE
 * SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 * PURPOSE, OR NON-INFRINGEMENT. GENSYM SHALL NOT BE LIABLE FOR ANY DAMAGES
 * SUFFERED BY LICENSEE AS A RESULT OF USING, MODIFYING OR DISTRIBUTING
 * THIS SOFTWARE OR ITS DERIVATIVES.
 *
 */

package com.gensym.demos.jlp;

import java.util.*;
import java.awt.*;
import java.applet.*;
import java.text.*;
import java.util.Vector;
import com.gensym.jgi.*;
import com.gensym.jlp.*;

public class TickGenerator extends Frame implements Runnable{

  G2Connection g2_connection = null;
  private Vector tickListeners = new Vector();
  private long tick = 0;
  private int tickWaitTime = 1000;
  private long TD;
  private Frame f;
  private int oldCount=0;
  Thread timer = null;
  int lastxs=0, lastys=0, lastxm=0, lastym=0, lastxh=0, lastyh=0;
  Date dummy = new Date();
  GregorianCalendar cal = new GregorianCalendar();
  SimpleDateFormat df = new SimpleDateFormat("EEE MMM dd HH:mm:ss yyyy");
  String lastdate = df.format(dummy);
  Font F = new Font("TimesRoman", Font.PLAIN, 14);
  Date dat = null;
  Color fgcol = Color.blue;
  Color fgcol2 = Color.darkGray;

  private java.awt.Image img =
  Toolkit.getDefaultToolkit().getImage( "watchface.jpg");

  public synchronized void addTickListener(TickListener listener) {
    Vector newlist = (Vector)tickListeners.clone();

    newlist.addElement(listener);
    synchronized(tickListeners) {
      tickListeners = newlist;
    }
    System.out.println("Added " + listener);
  }

  public synchronized void removeTickListener(TickListener listener) {
    Vector newlist = (Vector)tickListeners.clone();
    newlist.removeElement(listener);

    synchronized(tickListeners) {
      tickListeners = newlist;
    }
    System.out.println("Removed " + listener);
  }

  public void setTickWaitTime(int waittime) {
    tickWaitTime = waittime;
  }



  public void engageRuleEngine(String host , String port)
  {
       	System.out.print("Engaging Java Rule Engine");

  	try {
	  // Attempt to connect to G2, and wait until successful or timeout
	  g2_connection =
	    G2Gateway.getOrMakeConnection(
       					  (host == null ? "localhost" : host),
					  (port == null ? "1111" : port));
	} catch (Exception e) {
	  System.out.println("Could not connect to G2, error was " + e.toString());

	}


        if (g2_connection != null){
            System.out.print("Interface Connected to G2 OK...");
	    
	    // Below TBD.....

	    // We have connected OK, create a JavaInvokeEventRule
	    //JavaInvokeEventRule G2ProcCaller = new JavaInvokeEventRule(g2_connection);
            //RuleController rc = RuleController.getRuleController();
	    //rc.addRuleEventSource(g2_connection, this, com.gensym.demos.jlp.TickListener.class);

        }

  }


    // Plotpoints allows calculation to only cover 45 degrees of the circle,
    // and then mirror

  public void plotpoints(int x0, int y0, int x, int y, Graphics g) {

    g.drawLine(x0+x,y0+y,x0+x,y0+y);
    g.drawLine(x0+y,y0+x,x0+y,y0+x);
    g.drawLine(x0+y,y0-x,x0+y,y0-x);
    g.drawLine(x0+x,y0-y,x0+x,y0-y);
    g.drawLine(x0-x,y0-y,x0-x,y0-y);
    g.drawLine(x0-y,y0-x,x0-y,y0-x);
    g.drawLine(x0-y,y0+x,x0-y,y0+x);
    g.drawLine(x0-x,y0+y,x0-x,y0+y);
  }

   //
   public void circle(int x0, int y0, int r, Graphics g) {
    int x,y;
    float d;

    x=0;
    y=r;
    d=5/4-r;
    plotpoints(x0,y0,x,y,g);

    while (y>x){
      if (d<0) {
        d=d+2*x+3;
        x++;
      }
      else {
        d=d+2*(x-y)+5;
        x++;
        y--;
      }
      plotpoints(x0,y0,x,y,g);
    }
  }




  @Override
  public void paint(Graphics g) {
    int xh, yh, xm, ym, xs, ys, s, m, h, xcenter, ycenter;
    String today;

    dat = new Date(TD + (tick*1000));
    cal.setTime(dat);
    s = (int)cal.get(Calendar.SECOND);
    m = (int)cal.get(Calendar.MINUTE);
    h = (int)cal.get(Calendar.HOUR_OF_DAY);
    today = df.format(dat);
    xcenter=134;
    ycenter=117;

    // a= s* pi/2 - pi/2 (to switch 0,0 from 3:00 to 12:00)
    // x = r(cos a) + xcenter, y = r(sin a) + ycenter
      g.drawImage(img, 40,40,this);
    xs = (int)(Math.cos(s * 3.14f/30 - 3.14f/2) * 45 + xcenter);
    ys = (int)(Math.sin(s * 3.14f/30 - 3.14f/2) * 45 + ycenter);
    xm = (int)(Math.cos(m * 3.14f/30 - 3.14f/2) * 40 + xcenter);
    ym = (int)(Math.sin(m * 3.14f/30 - 3.14f/2) * 40 + ycenter);
    xh = (int)(Math.cos((h*30 + m/2) * 3.14f/180 - 3.14f/2) * 30 + xcenter);
    yh = (int)(Math.sin((h*30 + m/2) * 3.14f/180 - 3.14f/2) * 30 + ycenter);

    // Draw the circle and numbers

    g.setFont(F);
    g.setColor(fgcol);

    g.setColor(fgcol2);


    // Erase if necessary, and redraw

    g.setColor(getBackground());
    if (xs != lastxs || ys != lastys) {
      g.drawString(lastdate, 50, 225);

      g.fillRect(5, 225,200,200);
    }

    g.setColor(fgcol2);
    g.drawString(today, 50, 225);
    g.drawString("Subscribers "+ tickListeners.size(), 50, 245);
    g.drawLine(xcenter, ycenter, xs, ys);
    g.setColor(fgcol);
    g.drawLine(xcenter, ycenter-1, xm, ym);
    g.drawLine(xcenter-1, ycenter, xm, ym);
    g.drawLine(xcenter, ycenter-1, xh, yh);
    g.drawLine(xcenter-1, ycenter, xh, yh);
    lastxs=xs; lastys=ys;
    lastxm=xm; lastym=ym;
    lastxh=xh; lastyh=yh;
    lastdate = today;


    dat=null;
  }



  public void start() {
  if(timer == null)
    {
      timer = new Thread(this);
      timer.start();
    }
  }

  public void stop() {
    timer = null;
  }


  @Override
  public void update(Graphics g) {
    paint(g);
  }

  @Override
  public void run() {
      Date TDay = new Date();
      TD = TDay.getTime();

      this.setLocation (0, 0);
      this.setSize (250, 290);
      this.setVisible (true);
       start();
       while (timer != null) {
      try {Thread.sleep(tickWaitTime);} catch (InterruptedException e){}
        repaint();
       // System.out.println("Tick Generator Tick " + tick );
      tick++;
      TickEvent evt = new TickEvent(this, tick);
      for (int i = 0; i<tickListeners.size(); i++) {

    	TickListener listener = (TickListener)tickListeners.elementAt(i);
    	listener.tick(evt);
      }
      }
      timer = null;


  }


}



