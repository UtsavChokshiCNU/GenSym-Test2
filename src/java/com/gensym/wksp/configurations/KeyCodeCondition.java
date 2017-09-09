package com.gensym.wksp.configurations;

import com.gensym.dispatcher.*;
import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.wksp.*;
import com.gensym.jgi.*;
import java.awt.event.*;
import java.util.Hashtable;

public class KeyCodeCondition extends CompoundCondition
{
  public static final int SHIFT_MASK = 1;
  public static final int CTRL_MASK = 2;
  public static final int ALT_MASK = 4;
  public static final int META_MASK = 8;
  public static final int NO_MOUSE_MODIFIERS = InputEvent.BUTTON1_MASK;
  public static final Symbol MODIFIERS_ = Symbol.intern ("MODIFIERS");
  public static final Symbol KEYBOARD_SYMBOL_ = Symbol.intern ("KEYBOARD-SYMBOL");
  private static int CONTROL_KEY_CONVERSION_FACTOR =  (int)'a' - (int)'';
  private Condition condition;
  public static final Symbol F1_ = Symbol.intern ("F1"),
    F2_ = Symbol.intern ("F2"),
    F3_ = Symbol.intern ("F3"),
    F4_ = Symbol.intern ("F4"),
    F5_ = Symbol.intern ("F5"),
    F6_ = Symbol.intern ("F6"),
    F7_ = Symbol.intern ("F7"),
    F8_ = Symbol.intern ("F8"),
    F9_ = Symbol.intern ("F9"),
    F10_ = Symbol.intern ("F10"),
    F11_ = Symbol.intern ("F11"),
    F12_ = Symbol.intern ("F12"),
    HELP_ = Symbol.intern ("Help"),
    BACKSPACE_ = Symbol.intern ("Backspace"),
    CLEAR_SCREEN_ = Symbol.intern ("Clear-screen"),
    DELETE_ = Symbol.intern ("Delete"),
    DOWN_ARROW_ = Symbol.intern ("Down-arrow"),
    END_ = Symbol.intern ("End"),
    ENTER_ = Symbol.intern ("Enter"),
    ESCAPE_ = Symbol.intern ("Escape"),
    HOME_ = Symbol.intern ("Home"),
    INSERT_ = Symbol.intern ("Insert"),
    LEFT_ARROW_ = Symbol.intern ("Left-arrow"),
    PAUSE_ = Symbol.intern ("Pause"),
    PRINT_ = Symbol.intern ("Print"),
    RETURN_ = Symbol.intern ("Return"),
    RIGHT_ARROW_ = Symbol.intern ("Right-arrow"),
    SPACE_ = Symbol.intern ("Space"),
    TAB_ = Symbol.intern ("Tab"),
    UP_ARROW_ = Symbol.intern ("Up-arrow");
  
  private static Hashtable keyCodes;
  static {
    keyCodes = new Hashtable();
    keyCodes.put(F1_,new Integer(KeyEvent.VK_F1));
    keyCodes.put(F2_,new Integer(KeyEvent.VK_F2));
    keyCodes.put(F3_,new Integer(KeyEvent.VK_F3));
    keyCodes.put(F4_,new Integer(KeyEvent.VK_F4));
    keyCodes.put(F5_,new Integer(KeyEvent.VK_F5));
    keyCodes.put(F6_,new Integer(KeyEvent.VK_F6));
    keyCodes.put(F7_,new Integer(KeyEvent.VK_F7));
    keyCodes.put(F8_,new Integer(KeyEvent.VK_F8));
    keyCodes.put(F9_,new Integer(KeyEvent.VK_F9));
    keyCodes.put(F10_,new Integer(KeyEvent.VK_F10));
    keyCodes.put(F11_,new Integer(KeyEvent.VK_F11));
    keyCodes.put(F12_,new Integer(KeyEvent.VK_F12));
    keyCodes.put(BACKSPACE_,new Integer(KeyEvent.VK_BACK_SPACE));
    keyCodes.put(CLEAR_SCREEN_,new Integer(KeyEvent.VK_CLEAR));
    keyCodes.put(DELETE_,new Integer(KeyEvent.VK_DELETE));
    keyCodes.put(DOWN_ARROW_,new Integer(KeyEvent.VK_DOWN));
    keyCodes.put(END_,new Integer(KeyEvent.VK_END));
    keyCodes.put(ENTER_,new Integer(KeyEvent.VK_ENTER));
    keyCodes.put(ESCAPE_,new Integer(KeyEvent.VK_ESCAPE));
    keyCodes.put(HELP_,new Integer(KeyEvent.VK_HELP));
    keyCodes.put(HOME_,new Integer(KeyEvent.VK_HOME));
    keyCodes.put(INSERT_,new Integer(KeyEvent.VK_INSERT));
    keyCodes.put(LEFT_ARROW_,new Integer(KeyEvent.VK_LEFT));
    keyCodes.put(PAUSE_,new Integer(KeyEvent.VK_PAUSE));
    keyCodes.put(PRINT_,new Integer(KeyEvent.VK_PRINTSCREEN));
    keyCodes.put(RETURN_,new Integer(KeyEvent.VK_ENTER));
    keyCodes.put(RIGHT_ARROW_,new Integer(KeyEvent.VK_RIGHT));
    keyCodes.put(SPACE_,new Integer(KeyEvent.VK_SPACE));
    keyCodes.put(TAB_,new Integer(KeyEvent.VK_TAB));
    keyCodes.put(UP_ARROW_,new Integer(KeyEvent.VK_UP));
  }

  private int convertToAWTModifiers(int modifiers, boolean isMouse) {
    int mod = 0;
    if (isMouse)
      mod = NO_MOUSE_MODIFIERS;//4 if right button
    if ((modifiers & ALT_MASK) != 0) 
      mod |= InputEvent.ALT_MASK;
    if ((modifiers & CTRL_MASK) != 0)
      mod |= InputEvent.CTRL_MASK;
    if ((modifiers & META_MASK) != 0) 
      mod |= InputEvent.META_MASK;
    if ((modifiers & SHIFT_MASK) != 0) 
      mod |= InputEvent.SHIFT_MASK;
    return mod;
  }

  public KeyCodeCondition(Structure keyCode) 
  {
    //System.out.println("STRUCT " + keyCode);
    condition = null;
    //Symbol mouseButton
    //= (Symbol)keyCode.getAttributeValue(MOUSE_BUTTON_, null);//'any
    int modifiers
      = ((Integer)keyCode.getAttributeValue(MODIFIERS_, new Integer(0))).intValue();
    
    Symbol keyboardSymbol
      = (Symbol)keyCode.getAttributeValue(KEYBOARD_SYMBOL_, null);

    if (keyboardSymbol != null) {
      char ch = getChar(keyboardSymbol, modifiers);
      modifiers = convertToAWTModifiers(modifiers, false);
      if (ch != KeyEvent.CHAR_UNDEFINED)
	condition =  new SimpleCondition
	  (SimpleCondition.EQUAL,
	   new ConstantReference(Character.TYPE,
				 new Character(ch)),
	   new NestedPropertyReference(Character.TYPE,
				       "getKeyChar",
				       new EventReference(KeyEvent.class)));
      else {
	Integer codeObject
	  = (Integer)keyCodes.get(keyboardSymbol);
	if (codeObject == null)
	  return;//should throw and unsupported configuration exception
	int code = codeObject.intValue();
	condition = new SimpleCondition
	  (SimpleCondition.EQUAL,
	   new ConstantReference(Integer.TYPE,
				 new Integer(code)),
	   new NestedPropertyReference(Integer.TYPE,
				       "getKeyCode",
				       new EventReference(KeyEvent.class)));
      }
    } else 
      modifiers = convertToAWTModifiers(modifiers, true);

    Condition mods = modifiersCondition(modifiers);

    if (condition == null)
      condition = mods;
    else
      condition = new AndCondition(mods, condition);
  }

  //JDK_BUG_4117523 is a sun bug in jdk versions prior to 1.2
  //on SOLARIS ONLY, in which the mouse modifiers of a mousePressed event
  //(ie: ((InputEvent)e).getModifiers()) is not correctly set to 
  //InputEvent.BUTTON1_MASK when just the left button is pressed.
  //More simply, it is set to zero instead of sixteen.
  //THIS IS A PRIVATE CONSTRUCTOR DESIGNED ONLY FOR THAT BUG
  //AND SHOULD NOT BE USED ELSEWHERE. THIS CODE CAN HOPEFULLY BE
  //REMOVED AT SOME POINT IN THE FUTURE.  THIS CONSTRUCTOR IS 
  //ONLY CALLED BY ConfigurationSupport.java
  KeyCodeCondition(Structure keyCode, boolean JDK_BUG_4117523_IS_PRESENT) 
  {
    int modifiers
      = ((Integer)keyCode.getAttributeValue(MODIFIERS_, new Integer(0))).intValue();
    modifiers = convertToAWTModifiers(modifiers, true);
    if (modifiers == NO_MOUSE_MODIFIERS)
      //the bug is that where it should be InputEvent.BUTTON1_MASK
      //it is coming up zero, so the work around is to change our dispatch
      //table to match it.
      modifiers = 0;
    condition = modifiersCondition(modifiers);
  }
  
  static Condition modifiersCondition(int AWTModifiers)
  {
    return new SimpleCondition
      (SimpleCondition.EQUAL,
       new ConstantReference(Integer.TYPE, new Integer(AWTModifiers)),
       new NestedPropertyReference(Integer.TYPE,
				   "getModifiers",
				   new EventReference(InputEvent.class)));
  }
  
  private char getChar(Symbol keyboardSymbol, int g2Modifiers)
  {    
    String keyBoardString = keyboardSymbol.getPrintValue();
    if (keyBoardString.length()>1)
      return KeyEvent.CHAR_UNDEFINED;
    char ch = keyboardSymbol.getPrintValue().toLowerCase().charAt(0);
    if ((g2Modifiers & CTRL_MASK) != 0) {
      ch = (char)((int)ch - CONTROL_KEY_CONVERSION_FACTOR);
   } else {
     /*if ((g2Modifiers & ALT_MASK) != 0)
	ch = keyboardSymbol.toString().toLowerCase().charAt(0);*/
      if ((g2Modifiers & SHIFT_MASK) != 0)
	ch = Character.toUpperCase(ch);
    }
    return ch;
  }

  @Override
  public boolean isSatisfied(DispatchTable table)
       throws IllegalAccessException
  {
    InputEvent e = (InputEvent)(new EventReference()).getValue(table);
    if (condition != null){
      return condition.isSatisfied(table);
    } else
      return false;
  }

  @Override
  public String toString()
  {
    if (condition != null)
      return condition.toString();
    else
      return "false";
  }
  
}
