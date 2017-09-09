package com.gensym.classtools;

import java.util.Vector;
import java.util.Hashtable;

/* JavaNodes are a tree representation of Java code that is used to emit
 * class files.  JavaNodes are built around the following assumptions:
 * i) All class names are specified fully, eg java.lang.String rather than
 * String;<br>
 * ii) All virtual, interface and special method call distinctions are known;
 * <br> 
 * iii) All static, and non-static field reference distinctions are known;<br>
 * iv) The class of all field and method calls are known <br>
 * Given these assumptions the JavaNode facility and the supporting Info classes
 * are used to solve the following problems:
 * i) Return type analysis;<br>
 * ii) Dead code analysis;<br>
 * iii) Local Variable name conversion to integer references in a local 
 * variable vector;<br> 
 * iv) Conversion of constants into integer references;<br>
 * v) Emitting information about instructions and constants necessary for the
 *  MethodInfo, FieldInfo, and ClassInfo classes to emit a class file;<br>
 * vi) Simplification of constant expressions.<br>
*/
public abstract class JavaNode extends TreeNode implements RuntimeConstants {
  private boolean complete = false;
  private static final boolean trace = false;
  private int lineNumber = -1;
  private Object extension = null;
  protected String name;
  
  protected JavaNode() {
  }
  
  public boolean isComplete() {
    return complete;
  }

  public void addJavaNode(JavaNode j) 
       throws ClassException
  {			
    if ((j instanceof MacroNode) && ((MacroNode) j).expansionRequired()) {
      MacroNode m = (MacroNode) j; 
      if (trace) {
	System.out.println("MacroExpand");
	toStdout();
	j.toStdout("+");
      }
      m.expandInto(this);
      if (trace)
	toStdout("-->");
    }
    else if ((j instanceof Expression) 
	     && (! (j instanceof Value))
	     && ((Expression) j).isConstantExpression()) {
      Expression e = (Expression) j;
      JavaNode simpler = e.evaluateConstantExpression();
      addChild(simpler);
    }
    else addChild(j);
  }

  public void setLineNumber(int lineNumber) {
    this.lineNumber = lineNumber;
  }

  public int getLineNumber() {
    return lineNumber;
  }

  /** state - maintains the state of the emit<br>
   * leaveOnStack - indicates whether ExpressionStatements should
   * leave their arguments on the stack or not<br>
   * continuation - indicates whether there is a statement to follow
   * this one or not.  Continuation is used by statements that involve
   * branches to indicate whether they need to branch to the end or not,
   * or whether they should return
   */
  void emit(EmitState state, boolean leaveOnStack, Statement continuation)
       throws ClassException
  {
    generateConstants(state.pool);
    generateVariableIds(state);
    generateLineNumberInfo(state);
  }
	
  void generateConstants(ConstantPool pool) throws ClassException {
  }

  void generateVariableIds(EmitState state) throws ClassException {
  }

  /**
   *The extension allows one to store deeper compiler-specific
   * information along with JavaNodes, avoiding the need for parallel data
   * structures.
   */
  public Object getExtension()
  {
    return extension;
  }

  public void setExtension(Object extension)
  {
    this.extension = extension;
  }

  

  void generateLineNumberInfo(EmitState state) throws ClassException {
    if (lineNumber != -1) 
      {
        Instruction inst = state.getLineNumberInstruction(lineNumber);
        state.instructions.addElement(inst);
      }
  }

  public void toStdout() {
    toStdout("");
  }


  public String getName() {
    return name;
  }

  public void toStdout(String prefix) {	
    System.out.println(prefix + this);
    for (int i = 0; i < children.size(); i++)
      ((JavaNode) children.elementAt(i)).toStdout(prefix + "   ");
  }
}
