
package com.gensym.ntw;

/**
 * Review public access to this class?
 */
public class NtwNotification {

  public static final int ERROR        = 0;
  public static final int EXCEPTION    = 1;
  public static final int FAILURE      = 2;
  public static final int TIMEOUT      = 3;
  public static final int STATUSCHANGE = 4;
  public static final int UPDATE       = 5;
  public static final int REPLY        = 6;
  public static final int RESULT       = 7;

  public static final int MIN_PRIORITY     = 0;
  public static final int MAX_PRIORITY     = 10;
  public static final int DEFAULT_PRIORITY = 5;

  public static final Object ACTIVITY_START = new Object (),
                             ACTIVITY_STOP  = new Object ();

  private static NtwNotificationHandler[] listeners = new NtwNotificationHandler[20];
  private static int listenerCount = 0;

  public int notfnCode;
  public int priority;
  public String details;
  public Object data;
  public Object source;
 
  public NtwNotification (int notfnCode, int priority, String details,
			  Object source, Object data) {
    this.notfnCode = notfnCode;
    this.priority = priority;
    this.details = details;
    this.source = source;
    this.data = data;
    //System.out.println ("Notification created.");
    //System.out.flush ();
  }

  public NtwNotification (int notfnCode, Object source, String details) {
    this (notfnCode, DEFAULT_PRIORITY, details, source, null);
  }

  public NtwNotification (int notfnCode, int priority, Object source, String details) {
    this (notfnCode, priority, details, source, null);
  }

  @Override
  public String toString () {
    return "NtwNotification : type = " + pprintStatus(notfnCode) + ", Details = " + details;
  }

  private final String pprintStatus (int notfnCode) {
    switch (notfnCode)
      {
      case ERROR: return "ERROR";
      case EXCEPTION: return "EXCEPTION";
      case FAILURE: return "FAILURE";
      case TIMEOUT: return "TIMEOUT";
      case STATUSCHANGE: return "STATUSCHANGE";
      case UPDATE: return "UPDATE";
      case REPLY: return "REPLY";
      case RESULT: return "RESULT";
      default: return "Duh";
      }
  }

  public static synchronized void registerListener (NtwNotificationHandler newListener,
						    NtwNotificationFilter filter) {
    listeners[listenerCount++] = newListener;
  }

  public void send () {
    //System.out.println ("NTW: Notification sent -> " + this);
    for (int i=0; i<listenerCount; i++)
      listeners[i].handleNtwNotification (this);
  }
}
