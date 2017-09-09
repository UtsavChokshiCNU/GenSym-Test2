
package com.gensym.ntw;

import com.gensym.jgi.G2ConnectionEvent;
import com.gensym.util.Symbol;

/** Sent whenever an important change occurs regarding the details
 * of a UiClientSession. These are when a session had logged in, logged
 * out, or if the usermode of that session has changed.
 * @see com.gensym.classes.UiClientSession
 */
public class TwConnectionEvent extends G2ConnectionEvent {

  /** The TwAccess has logged into G2.
   */
  public static final int CONNECTION_LOGGED_IN  = 300;
  /** The TwAccess has logged out of G2.
   */
  public static final int CONNECTION_LOGGED_OUT = 301;
  /** The user mode has changed.
   */
  public static final int USER_MODE_CHANGED     = 302;
  private Symbol mode;

  public static final int
     TW_FIRST = 300,
     TW_LAST  = 302;

  public TwConnectionEvent (TwGateway source, int id) {
    super (source, id);
  }

  public TwConnectionEvent (TwGateway source, int id, Symbol mode) {
    super (source, id);
    this.mode = mode;
  }

  public Symbol getUserMode () {
    return mode;
  }

}
