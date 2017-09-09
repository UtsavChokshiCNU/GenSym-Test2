package com.gensym.ntw;

import com.gensym.util.Symbol;
import com.gensym.util.Structure;
import com.gensym.message.Resource;
import com.gensym.util.G2ConnectionSourceEvent;
import com.gensym.classes.Item;
import com.gensym.jgi.G2Gateway;

public class WorkspaceShowingEvent extends G2ConnectionSourceEvent {

  private static final Resource i18n =
              Resource.getBundle("com.gensym.ntw.Messages");

  private static final Symbol SHOW_ = Symbol.intern ("SHOW");
  private static final Symbol HIDE_ = Symbol.intern ("HIDE");

  /**
   * The integer id found within an event where the workspace should
   * be shown.
   */
  public static final int SHOW = 0;
  /**
   * The integer id found within an event where the workspace should
   * be hidden.
   */
  public static final int HIDE = 1;

  private int ID;
  Structure particulars = null;
  Item workspace;
  Object userData;
  int subscriptionHandle;
  
  public WorkspaceShowingEvent(G2Gateway source, Symbol notfnCode,
			       Structure particulars,
			       Item workspace, Object userData,
			       int subscriptionHandle)

  {
    super(source);
    ID = mapCodeToID(notfnCode);
    this.particulars = particulars;
    this.workspace = workspace;
    this.userData = userData;
    this.subscriptionHandle = subscriptionHandle;
  }

  /**
   * Maps integer ids for <code>SHOW</code> and <code>HIDE</code> to the
   * <code>Symbol</code>s <code>SHOW_</code> and <code>HIDE_</code>, respectively.
   */
  public static Symbol getNotificationCode(int ID) {
    switch (ID) {
    case SHOW:
      return SHOW_;
    case HIDE:
      return HIDE_;
    default:
      throw new IllegalArgumentException(i18n.format("wseInvalidID",ID));
    }
  }

  private static int mapCodeToID (Symbol notfnCode) {
    if (SHOW_.equals(notfnCode)) {
      return SHOW;
    } else if (HIDE_.equals(notfnCode)) {
      return HIDE;
    } else {
      throw new IllegalArgumentException(i18n.format("wseInvalidCode",
						     notfnCode));
    }
  }

  /**
   * Returns the symbolic notification code of the event, as specified by G2.
   * This equivalent to calling <code>getNotificationCode(getID())</code>.
   */
  public Symbol getNotificationCode () {
    return getNotificationCode(ID);
  }

  /**
   * Gets the integer id for this event, which may have either the value
   * <code>SHOW</code> or <code>HIDE</code>. This is the preferred method to
   * use for determining whether the given workspace should be shown or hidden.
   */
  public int getID() {
    return ID;
  }

  /**
   * Gets the <code>KbWorkspace</code> that should be
   * shown for this event.
   */
  public Item getWorkspace()
  {
    return workspace;
  }

  /**
   * Reserved for future use.
   */
  public Object getUserData()
  {  
    return userData;
  }

  /**
   * A description of how the workspace should be shown.
   * @return a <code>Structure</code> containing 
   * any of the following attributes:
   *  <code>
   *  symbolic-x-scale 
   *  symbolic-y-scale 
   *  symbolic-x-in-workspace 
   *  symbolic-y-in-workspace 
   *  symbolic-x-in-window 
   *  symbolic-y-in-window 
   *  x-offset-units 
   *  y-offset-units 
   *  symbolic-x-offset-direction 
   *  symbolic-y-offset-direction 
   *  x-magnification 
   *  y-magnification 
   *  x-in-workspace 
   *  y-in-workspace 
   *  x-in-window 
   *  y-in-window
   *  </code>
   */       
  public Structure getParticulars()
  {
    return particulars;
  }

  @Override
  public String toString () {

    return super.toString() + " [Source = " + source + ", modfcnCode = " +
      getNotificationCode () + ", Particulars = " + particulars
      + " Workspace = " + workspace + "]";
  }


}
