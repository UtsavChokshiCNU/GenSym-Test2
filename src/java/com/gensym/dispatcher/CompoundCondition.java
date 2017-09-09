package com.gensym.dispatcher;

import java.awt.*;
import java.util.*;
import java.awt.event.*;
import com.gensym.util.*;
import com.gensym.message.*;

public abstract class CompoundCondition extends Condition
{

  @Override
  public abstract boolean isSatisfied(DispatchTable table)
       throws IllegalAccessException;

}
