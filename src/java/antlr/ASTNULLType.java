package antlr;

import antlr.collections.AST;
import antlr.collections.ASTEnumeration;
import antlr.Token;

/** There is only one instance of this class **/
public class ASTNULLType implements AST {

	public void addChild(AST c) {  }
	
	@Override
    public boolean equals(Object t) { 
    	if(t == this) {
    		return true;
    	}
    	return false;
    }

	@Override
	public int hashCode() {
		int prime = 31;
		return prime * ASTNULLType.class.hashCode();
	}

	public boolean equalsList(AST t) {return false;}
	public boolean equalsListPartial(AST t) {return false;}
    public boolean equalsTree(AST t) {return false;}
	public boolean equalsTreePartial(AST t) {return false;}
	public ASTEnumeration findAll(AST tree) {return null;}
	public ASTEnumeration findAllPartial(AST subtree) {
		return null;
	}
	public AST getFirstChild() { return this; }
	public AST getNextSibling() { return this; }
	public String getText() { return "<ASTNULL>"; }
	public int getType() { return Token.NULL_TREE_LOOKAHEAD; }
	public void initialize(int t, String txt) {}
	public void initialize(AST t) {}
	public void initialize(Token t) {}
	public void setFirstChild(AST c) {  }
	public void setNextSibling(AST n) {  }
	public void setText(String text) {  }
	public void setType(int ttype) {  }
public String toString() {return getText();}
public String toStringList() {return getText();}
public String toStringTree() {return getText();}
}