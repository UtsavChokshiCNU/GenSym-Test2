package com.gensym.dispatcher;

import java.lang.reflect.*;

/**
 * Action
 */

public abstract class Action extends Node

{
  public abstract Object invoke(DispatchTable table)
       throws IllegalAccessException,
	 IllegalArgumentException,
	 InvocationTargetException;

}

