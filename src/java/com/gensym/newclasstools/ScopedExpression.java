package com.gensym.newclasstools;

public class ScopedExpression extends Expression 
                              implements MacroNode 
{
  private VariableScope variableScope = new VariableScope();
  
  private boolean requiresExpansion = false;;

  private Expression expansion;

  public ScopedExpression(VariableDeclaration[] vdecls,
                          Expression e)
       throws ClassException
  {
    if ((vdecls == null) ||
        (vdecls.length == 0))
    {
      requiresExpansion = true;
      expansion = e;
    }

    int length = vdecls.length;
    VariableDeclaration vdecl;

    for (int i = 0; i < length; i++)
    {
      vdecl = vdecls[i];
      if (! vdecl.hasChildren()) {
        throw 
          new ClassException("ScopedExpression variable declaration must" +
          "contain assignment");
      }
      variableScope.add(vdecl);
      addJavaNode(vdecl);
    }
      addJavaNode(e);
  } 

  @Override
  public boolean expansionRequired()
  { 
    return requiresExpansion;
  }

  @Override
  public void expandInto(JavaNode j) throws ClassException {
    j.addJavaNode(expansion);
  }

  @Override
  public Type getExpressionType()
  {
    if (requiresExpansion)
      return expansion.getExpressionType();
    Expression e = (Expression) children.lastElement();
    return e.getExpressionType();
  }

  @Override
  void generateVariableIds(EmitState state) throws ClassException {
      variableScope.generateVariableIds(state);
  }

  @Override
  void emit(EmitState state, boolean leaveOnStack, 
                Statement continuation)
                throws ClassException {
    VariableScope scope = state.scope;
    super.emit(state,leaveOnStack,continuation);
    state.scope = variableScope;
    int length =  children.size();
    int vdeclsLength = length - 1;

    for (int i = 0; i < vdeclsLength; i++)
    {
      VariableDeclaration vdecl =
        (VariableDeclaration) children.elementAt(i);
      vdecl.emit(state, false, continuation);
    }

    Expression e = (Expression) children.elementAt(vdeclsLength);
    e.emit(state, leaveOnStack, continuation);
    state.scope = scope;
  }  
}

