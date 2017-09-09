
package com.gensym.uiutil;


public class UIHeartBeat extends Thread {

  private static UIHeartBeat heartbeatThread;
  private static volatile int startIn, beatInterval; // milliseconds
  private static UIHeartBeatRecipient registeredWidget;
  private static final Class lock = UIHeartBeat.class;

  private UIHeartBeat () {
    super ("UI Heart Beat");
    synchronized (lock) {
      try {
	start ();
	lock.wait ();		// Why?
      } catch (InterruptedException ie) {
      }
    }
  }

  @Override
  public void run () {
    synchronized (lock) {
      lock.notify ();
      try {
	while (true) {
	  if (startIn == 0)
	    lock.wait ();

	  if (startIn != 0) {	// They might already have unregistered
	    lock.wait (startIn);
	    startIn = 0;
	    if (startIn == 0 && beatInterval != 0)
	      notifyListener ();
	  }
	  
	  while (beatInterval != 0) {
	    lock.wait (beatInterval);
	    if (beatInterval != 0)
	      notifyListener ();
	  }
	}
      } catch (InterruptedException ie) {
      }
    }
  }

  private void notifyListener () {
    registeredWidget.dub ();
  }

  public static synchronized void registerForUIHeartBeat (UIHeartBeatRecipient widget,
							  int desiredStartTime,
							  int desiredBeatInterval) {
    if (widget != null && widget.equals(registeredWidget))
	return;

    if (heartbeatThread == null || !heartbeatThread.isAlive())
      heartbeatThread = new UIHeartBeat ();

    if (registeredWidget != null)
      throw new IllegalStateException ("Another widget has the heartbeat");
    
    registeredWidget = widget;
    startIn = desiredStartTime;
    beatInterval = desiredBeatInterval;
    lock.notify ();
  }

  public static synchronized void unregisterForUIHeartBeat (UIHeartBeatRecipient widget) {
    if (registeredWidget != widget)
      throw new IllegalArgumentException ("Not Registered Widget!");

    registeredWidget = null;
    startIn = 0;
    beatInterval = 0;
    lock.notify ();
  }
}
