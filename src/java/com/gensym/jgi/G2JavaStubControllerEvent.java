package com.gensym.jgi;

import com.gensym.util.*;
import com.gensym.classes.Item;

/**
 * Event Class containing information generated from a G2JavaStubContoller Event.
 */
public class G2JavaStubControllerEvent extends SerializableSourceEvent {

  private Item target;
  private String methodName;
  private Sequence args;
  private int id;

  public static final int CALL_ASYNC_METHOD  = 0;
  public static final int DELETE_INSTANCE   = 1;

  public G2JavaStubControllerEvent(Object source, 
				   int id,
				   Item target, 
				   String methodName, 
				   Sequence args) {
    super(source);
    this.target = target;
    this.methodName = methodName;
    this.args = args;
    this.id = id;
  }

  public G2JavaStubControllerEvent(Object source,
				   int id,
				   Item target) {
    super(source);
    this.target = target;
    this.id = id;
  }

  public Item getTarget() {
    return target;
  }

  public String getMethodName() {
    return methodName;
  }

  public Sequence getArgs() {
    return args;
  }

  public int getID() {
    return id;
  }
}

