/* This file implements the synchronizers needed by JGInterface to wait for
 * return values from C functions; see JGInterface.doWait.  Real java studs
 * could probably figure out how to do this with reflection.
 */

package com.gensym.jgi;

abstract class Return {
	private boolean valueSet;
	protected void notifyAwaiters(){
	    valueSet = true;
	    this.notifyAll();
	}
	
	protected boolean isValueSet() {
		return valueSet;
	}
}

class Return_int extends Return {
  public int value;
  public synchronized void setValue (int input_value) {
    value = input_value;
    notifyAwaiters();
  }
  public int getValue () {
    return value;
  }
}

class Return_long extends Return {
  public long value;
  public synchronized void setValue (long input_value) {
    value = input_value;
    notifyAwaiters();
  }
  public long getValue () {
    return value;
  }
}

class Return_Integer extends Return {
  public int value;
  public synchronized void setValue (int input_value) {
    value = input_value;
    notifyAwaiters();
  }
  public Integer getValue () {
    return new Integer (value);
  }
}

class Return_String extends Return {
  private String value;
  public synchronized void setValue (String input_value) {
    value = input_value;
    notifyAwaiters();
  }
  public String getValue () {
    return value;
  }
}

class Return_Object extends Return {
  private Object value;
  public synchronized void setValue (Object input_value) {
    value = input_value;
    notifyAwaiters();
  }
  public Object getValue () {
    return value;
  }
}


class Return_boolean extends Return {
  private boolean value;
  public synchronized void setValue (boolean input_value) {
    value = input_value;
    //System.out.println ("Done waiting for "+ this+" value = "+ input_value);
    notifyAwaiters(); 
  }
  public boolean getValue () {
    return value;
  }
}

