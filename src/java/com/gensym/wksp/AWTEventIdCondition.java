package com.gensym.wksp;

import com.gensym.dispatcher.*;
import java.util.EventObject;

public class AWTEventIdCondition extends SimpleCondition {

  public AWTEventIdCondition(int id)
  {
    super(SimpleCondition.EQUAL,
	  new NestedPropertyReference(Integer.TYPE,"getID",
				      new EventReference(java.awt.AWTEvent.class)),
	  new ConstantReference(Integer.TYPE,
				new Integer(id)));
  }
  
}
