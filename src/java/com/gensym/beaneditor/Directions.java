package com.gensym.beaneditor;

class Directions
{
  public static final int LEFT = 0;
  public static final int TOP = 1;
  public static final int RIGHT = 2;
  public static final int BOTTOM = 3;
  public static final int TOP_LEFT = 4;
  public static final int TOP_RIGHT = 5;
  public static final int BOTTOM_LEFT = 6;
  public static final int BOTTOM_RIGHT = 7;

  public static int invertDirection(int direction)
  {
    switch (direction)
      {
      case LEFT:
	return RIGHT;
      case RIGHT:
	return LEFT;
      case TOP:
	return BOTTOM;
      case BOTTOM:
	return TOP;
      }
    return LEFT;
  }
  
  public static String getName(int direction)
  {
    switch (direction)
      {
      case LEFT:
	return "LEFT";
      case RIGHT:
	return "RIGHT";
      case TOP:
	return "TOP";
      case BOTTOM:
	return "BOTTOM";
      }
    return "LEFT";
  }
}
