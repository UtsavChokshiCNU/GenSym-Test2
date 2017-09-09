package com.gensym.dispatcher;

import java.awt.*;
import java.util.*;
import java.awt.event.*;
import com.gensym.util.*;
import com.gensym.message.*;

public abstract class Condition

{

  public Condition()
  {
  }

  public boolean isSatisfied(DispatchTable table)
       throws IllegalAccessException
  {
    return false;
  }

}
