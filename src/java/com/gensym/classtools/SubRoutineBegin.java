package com.gensym.classtools;

import java.util.Vector;

class SubRoutineBegin extends Statement implements MacroNode {

    SubRoutineBegin() throws ClassException {
      VariableDeclaration vdecl =
        VariableDeclaration.generateUniqueVariableDeclaration(OBJECT_DESC);
      Variable var = vdecl.getVariable();
      OperatorCall setAddress = 
        new OperatorCall("=",
        new Expression[] {
        var,
          new Noop(var.getExpressionType(),true)});

      addJavaNode(Label.generateUniqueLabel());
      addJavaNode(vdecl);
      addJavaNode(setAddress);
    }

    @Override
    public boolean expansionRequired() {
      return true;
    }
  
    @Override
    public void expandInto(JavaNode j) throws ClassException {
      j.addJavaNode((JavaNode) children.elementAt(0));
      if (j instanceof Block) {
        Block b = (Block) j;
        b.add((VariableDeclaration) children.elementAt(1));
        b.add((OperatorCall) children.elementAt(2));
      }
      else {
        j.addJavaNode((JavaNode) children.elementAt(1));
        j.addJavaNode((JavaNode) children.elementAt(2));
      }
    }

    public SubRoutineJump getSubRoutineJump() throws ClassException {
      return new SubRoutineJump((Label) children.elementAt(0));
    }

    public SubRoutineReturn getSubRoutineReturn() throws ClassException {
      VariableDeclaration vdecl = (VariableDeclaration) children.elementAt(1);
      Variable var = vdecl.getVariable();
      return new SubRoutineReturn(var);
    }

    @Override
    void emit(EmitState state, boolean leaveOnStack, Statement continuation)
      throws ClassException {
        throw new ClassException("Attempt to emit unexpanded SubRoutineBegin node");
    }

}
