package com.gensym.dlgevent;

import java.util.EventListener;

public interface ItemDeletionListener extends EventListener{

  public void itemDeleted(ItemDeletionEvent event);
}
