package com.gensym.classtools;

import java.util.Vector;

/**
* @deprecated Please use ExpressionStatement instead
*/
public class StatementExpression extends ExpressionStatement {
      
      public StatementExpression (Expression exp)
        throws ClassException 
      {
         super(exp);
      }
  
      public StatementExpression() {
          super();
      }
}
