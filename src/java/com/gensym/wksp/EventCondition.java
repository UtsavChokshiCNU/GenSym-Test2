package com.gensym.wksp;

import com.gensym.dispatcher.*;
import java.util.EventObject;

public class EventCondition extends SimpleCondition {

  public EventCondition(Class type) throws NonStaticMethodException
  {
    super(InstanceOfSwitchDecision.instanceOfMethod,
	  new EventReference(),
	  new ConstantReference(type));
  }
}
