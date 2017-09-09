package com.gensym.util;

import java.util.Enumeration;
import java.util.Hashtable;
import com.gensym.jgi.G2Access;
import com.gensym.jgi.G2ConnectionAdapter;
import com.gensym.jgi.G2ConnectionEvent;
import com.gensym.jgi.G2ConnectionListener;

/**
 * G2ConnectionTable is a Hashtable with the following behavior:
 * Any instances of a G2Access that are put in the table, as either
 * a key or a value, will automatically be removed when the connection
 * closes.
 */
public class G2ConnectionTable extends Hashtable{

  private G2ConnectionListener closingListener = new ClosingListener();
  private Hashtable connectionToKeyTable = new Hashtable();

  @Override
  public Object put(Object key, Object value){
    if (key instanceof G2Access)
      ((G2Access)key).addG2ConnectionListener(closingListener);
    if (value instanceof G2Access){
      connectionToKeyTable.put(value, key);
      ((G2Access)value).addG2ConnectionListener(closingListener);
    }
    Object oldValue = super.put(key, value);
    if (oldValue instanceof G2Access)
      ((G2Access)oldValue).removeG2ConnectionListener(closingListener);
    return oldValue;
  }

  @Override
  public Object remove(Object key){
    if (key instanceof G2Access)
      ((G2Access)key).removeG2ConnectionListener(closingListener);
    Object value = super.remove(key);
    if (value instanceof G2Access)
      ((G2Access)value).removeG2ConnectionListener(closingListener);
    return value;
  }

  @Override
  public void clear(){
    Enumeration keys = keys();
    while (keys.hasMoreElements())
      remove(keys.nextElement());
  }

  class ClosingListener extends G2ConnectionAdapter{

    @Override
    public void g2ConnectionClosed(G2ConnectionEvent event){
      G2Access connection = (G2Access)event.getSource();
      if (contains(connection)){
	Object key = connectionToKeyTable.get(connection);
	connectionToKeyTable.remove(connection);
	remove(key);
      }

      if (containsKey(connection))
	remove(connection);
    }
  }
}
