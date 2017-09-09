package com.gensym.classtools;

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
  public final int PLUS_PLUS = 11;
  public final int MINUS_MINUS = 12;
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
			       "++", // 11
			       "--", // 12
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
			       "instanceof" //25
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
					  1, //11
					  1, //12
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
                                          2 // 25
  };

	
  public Type[] operandType = new Type[] {
    new Type(T_NUMERIC), //0
      new Type(T_NUMERIC), //1
      new Type(T_BOOLEAN),   //2
      new Type(T_INTEGRAL),  //3
      new Type(T_ANY),       //4
      new Type(T_ANY),       //5
      new Type(T_NUMERIC), //6
      new Type(T_ANY),       //7 
      new Type(T_ANY),       //8
      new Type(T_BOOLEAN),   //9
      new Type(T_BOOLEAN),   //10
      new Type(T_NUMERIC), //11
      new Type(T_NUMERIC), //12
      new Type(T_ANY), //13
      new Type(T_NUMERIC), //14
      new Type(T_NUMERIC),  //15
      new Type(T_NUMERIC),  //16
      new Type(T_INTEGRAL),  //17
      new Type(T_INTEGRAL),  //18
      new Type(T_INTEGRAL),  //19
      new Type(T_NUMERIC),  //20
      new Type(T_INTEGRAL),  //21
      new Type(T_INTEGRAL),  //22
      new Type(T_INTEGRAL),  //23
      new Type(T_ANY),  //24
      new Type(T_CLASS) // 25
      };			
}
