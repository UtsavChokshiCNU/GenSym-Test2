package com.gensym.g2script;

import antlr.ASTFactory;
import antlr.collections.AST;
import antlr.Token;

public class G2ScriptASTFactory extends ASTFactory
{
  public G2ScriptASTFactory()
  {
    super();
  }

  public AST create() { 
    return new G2ScriptAST(); 
  }
  /** Create a new AST node from type */
  public AST create(int ttype) {
    return create(ttype, null);
  }
  /** Create a new AST node from type and text */
  public AST create(int ttype, String text) {
    AST ast = new G2ScriptAST();
    ast.setType(ttype);
    ast.setText(text);
    return ast;
  }
  /** Create a new AST node from an existing AST node */
  public AST create(AST ast) {
    AST newast = new G2ScriptAST();
    if (ast instanceof G2ScriptAST)
      {
	G2ScriptAST g2ast = (G2ScriptAST)ast;
	((G2ScriptAST)newast).setLineNumber(g2ast.getLineNumber());
      }
    newast.setType(ast.getType());
    newast.setText(ast.getText());
    return newast;
  }

  public AST create(Token t) 
  {
    AntlrToken token = (AntlrToken)t;
    G2ScriptAST ast = (G2ScriptAST) create(t.getType(), t.getText());
    ast.setLineNumber(token.getLine());
    if (token.g2Token != null)
      ast.setValue(token.g2Token.getValue());
    return ast;
  }
}
