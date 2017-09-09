package com.gensym.g2script;

public abstract class TreeWalker
{
  static G2ScriptAST child(G2ScriptAST ast)
  {
    return (G2ScriptAST)ast.getFirstChild();
  }

  static G2ScriptAST sibling(G2ScriptAST ast)
  {
    return (G2ScriptAST)ast.getNextSibling();
  }

  static int siblingCount(final G2ScriptAST ast)
  {
	G2ScriptAST tree = ast;  
    int count = 0;
    if (tree == null) {
    	return count;
    }
    while (tree.getNextSibling() != null)
      {
    	tree = sibling(tree);
    	count++;
      }
    return count;
  }

  static boolean siblingsContain(final G2ScriptAST ast, final int type)
  {
	G2ScriptAST tree = ast;  
    while (tree != null)
      {
	if (tree.getType() == type){
	  return true;
	}
	tree = sibling(tree);
      }
    return false;
  }

}
