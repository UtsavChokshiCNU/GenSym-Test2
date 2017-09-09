package com.gensym.wksp;


import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.jgi.*;
import com.gensym.ntw.*;
import com.gensym.draw.*;
import java.awt.*; //Rectangle
import java.awt.event.*;
import java.util.Locale;
import com.gensym.classes.Item;
import com.gensym.classes.UserMenuChoice;


public class UserMenuItem extends MenuItem {
  private UserMenuChoice umc;
  private Item item;

  public UserMenuItem(UserMenuChoice umc,
		      Item item) throws G2AccessException
  {
    super();
    Symbol umcLabel_ = (Symbol)umc.getLabel();
    String umcLabel  = umcLabel_.getPrintValue ();
    setActionCommand (umcLabel);
    setLabel (getMenuLabel (umcLabel));
    this.umc = umc;
    this.item = item;
  }

  public boolean fire() throws G2AccessException {
    TwAccess context = (TwAccess)((com.gensym.classes.ImplAccess)item).getContext(); //hack for now
    return umc.invoke(item);
  }

  private static String getMenuLabel(String label) throws G2AccessException {
    return WorkspaceUtil.computePrettyClassName(label);
  }
  
}
