package com.gensym.classtools;

import java.util.Hashtable;
import java.util.Vector;

public class TryExpression extends Expression {
    
    private static Type throwableType  
             = new Type(T_CLASS,
                        null,
                        "Ljava/lang/Throwable;",
                        0);
    private static String throwableString = "java/lang/Throwable";  

    private int countOfCatches;

    private Type expressionType; 

    public TryExpression(Expression tryExpression,
      VariableDeclaration[] catchVars,
      Expression[] catchExpressions)
        throws ClassException
    {
        int countOfCatchExpressions;

        if (tryExpression == null)
        {
          throw new ClassException("No Expression provided for TryExpression");
        }

        if (catchVars == null || 
            (countOfCatches = catchVars.length) == 0)
        {
           throw new ClassException("No catch expression specified for TryExpression");
        }

        if (catchExpressions == null || 
            (countOfCatchExpressions = catchExpressions.length) == 0)
        {
           throw new ClassException("No catch expression specified for TryExpression");
        }

        if (countOfCatches != countOfCatchExpressions)
          throw new ClassException("TryExpression invalid specification");

        addJavaNode(tryExpression);
        
        Hashtable catchTypes = new Hashtable();

        expressionType = tryExpression.getExpressionType();

        VariableDeclaration vdecl;
        Expression exp;
        Type tpe;
        for (int i = 0; i < countOfCatches; i++)
        {
           exp = catchExpressions[i];
           tpe = exp.getExpressionType();
           if (! expressionType.potentialSubType(tpe)) 
              throw new ClassException("TryExpression type mismatch");
           
           vdecl = catchVars[i];
           tpe = vdecl.getVariableType();
       
           if (vdecl.hasChildren()) 
             throw 
             new ClassException("TryExpression variable declaration cannot" +
             "contain assignment");
           
           if (catchTypes.containsKey(tpe))
             throw new ClassException("Catch statement unreachable");
           
           catchTypes.put(tpe, tpe);

           addJavaNode(new ClassRef(
             Type.className(tpe.getReturnTypeString())));

           addJavaNode(generateCatchExpression(vdecl,exp,tpe));   
        }
    }

    @Override
    public Type getExpressionType() 
    {
        return expressionType;
    }

    private Expression generateCatchExpression(VariableDeclaration vdecl, 
                                          Expression exp,
                                          Type exceptionType)
            throws ClassException
    {
      VariableDeclaration newDecl = 
        new VariableDeclaration(vdecl.getName(),
                                vdecl.getVariableType().getReturnTypeString(),
                                new Noop(exceptionType,true));

      ScopedExpression scopedExpression =
        new ScopedExpression(new VariableDeclaration[] { newDecl },
                             exp);
      return scopedExpression;
    }


    @Override
    void emit(EmitState state, boolean leaveOnStack,
              Statement continuation)
      throws ClassException {
        generateLineNumberInfo(state);  
        System.out.println("Leave on the stack = " + leaveOnStack);
        Try.emit(state, leaveOnStack, continuation,
             children, countOfCatches, 
             false, false);
    }


}


