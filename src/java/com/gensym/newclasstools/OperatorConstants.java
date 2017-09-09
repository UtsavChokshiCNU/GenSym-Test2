package com.gensym.newclasstools;

interface OperatorConstants extends RuntimeConstants {
  public final int GREATER_THAN = 0;
  public final int LESS_THAN = 1;
  public final int NOT = 2;
  public final int ONES_COMPLEMENT = 3;
  public final int CONDITIONAL = 4;
  public final int EQUALITY = 5;
  public final int GREATER_THAN_OR_EQUAL = 6;
  public final int LESS_THAN_OR_EQUAL = 7;
  public final int NOT_EQUAL = 8;
  public final int BOOLEAN_AND = 9;
  public final int BOOLEAN_OR = 10;
  public final int POST_PLUS_PLUS = 11;
  public final int POST_MINUS_MINUS = 12;
  public final int PLUS = 13;
  public final int MINUS = 14;
  public final int MULTIPLY = 15;
  public final int DIVIDE = 16;
  public final int AND = 17;
  public final int OR = 18;
  public final int XOR = 19;
  public final int REMAINDER = 20; 
  public final int LEFT_SHIFT = 21;
  public final int RIGHT_SHIFT = 22;
  public final int UNSIGNED_RIGHT_SHIFT = 23;
  public final int ASSIGN = 24;
  public final int INSTANCEOF = 25;
  public final int PRE_PLUS_PLUS = 26;
  public final int PRE_MINUS_MINUS = 27;

  public final char ASSIGNC = '=';

  public String[] operators = {">",  // 0
			       "<",  // 1
			       "!",  // 2
			       "~",  // 3
			       "?:", // 4
			       "==", // 5
			       ">=", // 6
			       "<=", // 7
			       "!=", // 8 
			       "&&", // 9
			       "||", // 10
			       "post++", // 11
			       "post--", // 12
			       "+",  // 13
			       "-",  // 14
			       "*",  // 15
			       "/",  // 16
			       "&",  // 17
			       "|",  // 18
			       "^",  // 19
			       "%",  // 20
			       "<<", // 21
			       ">>", // 22
			       ">>>", // 23
			       "=",   // 24
			       "instanceof", //25
			       "pre++", // 26
			       "pre--" // 27

  };
		
  public String assignableOperators = "+-*^/|%<<<>>>&<<>>";
		
  public int[] operandCount = new int[] { 2, //0
				          2, //1
					  1, //2
					  1, //3
					  3, //4
					  2, //5
					  2, //6
					  2, //7
					  2, //8
					  2, //9
					  2, //10
					  2, //11
					  2, //12
                                         -1, //13
                                         -1, //14
                                          2, //15
                                          2, //16
                                          2, //17
                                          2, //18 
                                          2, //19
                                          2, //20
                                          2, //21
                                          2, //22
                                          2, //23
                                          2, //24
                                          2, //25
					  2, //26
					  2  //27

  };

}
