package com.gensym.classtools;

/** An Expression node used as a place-marker for an expression, typically when
* it is already known that the result needed is already on the stack
*/
class Noop extends Expression {
      boolean push = false;

	// a Noop expression still has a type, the type of the thing which it 
	// represents that is assumed already to be on the stack
	Noop(Type type) {
		expressionType = type;
	}

      // sometimes I want my Noop to sub in for something which pushes
      // onto the stack
      Noop(Type type, boolean push) {
		this(type);
            this.push = push;
	}

	// Emit nothing for Noop
	@Override
	void emit (EmitState state, boolean leaveOnStack, 
                 Statement continuation) 
        throws ClassException
      {
	  if (push) 
        {
            if(expressionType.isDoubleType() || 
                expressionType.isLongType())
            state.pushStack(2);
            else state.pushStack();
        }
      }	
}
