package com.gensym.ntw;

import com.gensym.util.Symbol;
import com.gensym.util.Structure;
import com.gensym.message.Resource;
import com.gensym.util.G2ConnectionSourceEvent;
import com.gensym.classes.Item;
import com.gensym.jgi.G2Gateway;

public class FieldEditEvent extends G2ConnectionSourceEvent {

  private static final Resource i18n =
              Resource.getBundle("com.gensym.ntw.Messages");

  private static final
  Symbol CANCEL_ = Symbol.intern ("CANCEL"),
    CREATE_ = Symbol.intern ("CREATE"),
    REFRESH_ = Symbol.intern ("REFRESH"),
    UPDATE_ = Symbol.intern ("UPDATE"),
    END_ = Symbol.intern ("END");
  public static final int CREATE = 0;
  public static final int CANCEL = 1;
  public static final int END = 2;
  public static final int REFRESH = 3;
  public static final int UPDATE = 4;
  private int ID;
  Structure particulars = null;
  Item workspace;
  Object userData;
  int subscriptionHandle;

  public FieldEditEvent(G2Gateway source, Symbol notfnCode,
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

  public static Symbol getNotificationCode(int ID) {
    switch (ID) {
    case CREATE:
      return CREATE_;
    case CANCEL:
      return CANCEL_;
    case END:
      return END_;
    case REFRESH:
      return REFRESH_;
    case UPDATE:
      return UPDATE_;
    default:
      throw new IllegalArgumentException(i18n.format("fieldEditEventInvalidID", ID));
    }
  }

  private static int mapCodeToID (Symbol notfnCode) {
    if (CREATE_.equals(notfnCode))
      return CREATE;
    else if (CANCEL_.equals(notfnCode)) 
      return CANCEL;
    else if (END_.equals(notfnCode)) 
      return END;
    else if (REFRESH_.equals(notfnCode)) 
      return REFRESH;
    else if (UPDATE_.equals(notfnCode)) 
      return UPDATE;    
    else 
      throw new IllegalArgumentException(i18n.format("fieldEditEventInvalidCode",
						     notfnCode));
  }

  /**
   * Returns the notification code of the event
   */
  public Symbol getNotificationCode () {
    return getNotificationCode(ID);
  }

  public int getID() {
    return ID;
  }

  public Item getWorkspace()
  {
    return workspace;
  }

  public Object getUserData()
  {  
    return userData;
  }

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
