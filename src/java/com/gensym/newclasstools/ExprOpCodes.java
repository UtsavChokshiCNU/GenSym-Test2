package com.gensym.newclasstools;




/** Implemented by Type and OperatorCall */
public interface ExprOpCodes {


  /* It is a requirement for persistence of EXPRs that theese numeric codes 
   * not be changed.
   * It is a requirment for not breaking Java code that (1) the numeric values
   *  start at 0 and (2) are strictly incremental by 1, and (3) that
   * they are kept in exact correspondence with the String array  opCodes
   * that follows.
   * If the list is modified, examine Expr.isExprCode and update if necessary.
   */
  public static final int QUESTION_ = 0;
  public static final int ASSIGN_ = 1;
  public static final int EQUAL_ = 2;
  public static final int LNOT_ = 3;
  public static final int BNOT_ = 4;
  public static final int NOT_EQUAL_ = 5;
  public static final int DIV_ = 6;
  public static final int DIV_ASSIGN_ = 7;
  public static final int PLUS_ = 8;
  public static final int PLUS_ASSIGN_ = 9;
  public static final int POST_INC = 10;
  public static final int MINUS_ = 11;
  public static final int MINUS_ASSIGN_ = 12;
  public static final int POST_DEC = 13;
  public static final int STAR_ = 14;
  public static final int STAR_ASSIGN_ = 15;
  public static final int MOD_ = 16;
  public static final int MOD_ASSIGN_ = 17;
  public static final int SR_ = 18;
  public static final int SR_ASSIGN_ = 19;
  public static final int BSR_ = 20;
  public static final int BSR_ASSIGN_ = 21;
  public static final int GE_ = 22;
  public static final int GT_ = 23;
  public static final int SL_ = 24;
  public static final int SL_ASSIGN_ = 25;
  public static final int LE_ = 26;
  public static final int LT_ = 27;
  public static final int BXOR_ = 28;
  public static final int BXOR_ASSIGN_ = 29;
  public static final int BOR_ = 30;
  public static final int BOR_ASSIGN_ = 31;
  public static final int LOR_ = 32;
  public static final int BAND_ = 33;
  public static final int BAND_ASSIGN_ = 34;
  public static final int LAND_  = 35;
  public static final int UNARY_PLUS_ = 36;
  public static final int UNARY_MINUS_ = 37;


  public static final int LITERAL = 38;
  public static final int VARIABLE = 39;
  public static final int CAST = 40;
  public static final int FIELD = 41;
  public static final int STATIC_FIELD = 42;
  public static final int CLASS_FOR_STATIC_ACCESS = 43;
  public static final int INSTANCEOF = 44;
  public static final int METHOD = 45;
  public static final int ARRAY_ACCESS = 46;
  public static final int BLOCK_ = 47;
  public static final int IF = 48;
  public static final int WHILE = 49; 
  public static final int DO = 50;
  public static final int CONTINUE = 51;
  public static final int BREAK = 52;
  public static final int RETURN = 53;
  public static final int LOC_DEC = 54;
  public static final int EXPR_STATEMENT = 55;
  public static final int NEW = 56;
  public static final int NEW_ARRAY = 57;
  public static final int PRE_INC = 58;
  public static final int PRE_DEC = 59;

  static String[] opNames = new String[] {  //used by toString
    "?",
      "=",
      "==",
      "!",
      "~",
      "!=",
      "/",
      "/=",
      "+",
      "+=" ,
      "post++",
      "-",
      "-=",
      "post--",
      "*",
      "*=",
      "%",
      "%=",
      ">>",
      ">>=",
      ">>>",
      ">>>=",
      ">=",
      ">",
      "<<",
      "<<=",
      "<=",
      "<",
      "^",
      "^=",
      "|",
      "|=",
      "||",
      "&",
      "&=",
      "&&",
      "+",
      "-",
      "LITERAL", 
      "VARIABLE",
      "CAST", 
      "FIELD", 
      "STATIC_FIELD",
      "CLASS_FOR_STATIC_ACCESS",
      "instanceof",
      "METHOD",
      "ARRAY_ACCESS",
      "BLOCK",
      "IF",
      "WHILE",
      "DO",
      "CONTINUE",
      "BREAK",
      "RETURN",
      "LOC_DEC",
      "EXPR_STATEMENT",
      "NEW",
      "NEW_ARRAY",
      "pre++",
      "pre--"
      };

}
