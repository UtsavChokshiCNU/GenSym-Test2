package com.gensym.classtools;

import java.util.Vector;

public class If extends Statement implements OperatorConstants, MacroNode {
		private boolean expressionStatement = false;	
		private boolean requiresExpansion = false;

		public If (Expression condition,Statement thenClause) throws ClassException {			
				init(condition,thenClause,null);
		}

		public If (Expression condition,Statement thenClause,Statement elseClause) throws ClassException {
				init(condition,thenClause,elseClause);
		}

		private void init(Expression condition, Statement thenClause, Statement elseClause) throws ClassException {
			if (! condition.getExpressionType().isBooleanType())
					throw new ClassException("Conditional statement contains non-boolean condition: "
												+ condition.getExpressionType());
				addJavaNode(condition);
				addJavaNode(thenClause);
				if (elseClause != null)
					addJavaNode(elseClause);
				JavaNode afterExpansion = (JavaNode) children.elementAt(0);
				// Case where we already know the condition at compile time
				if (afterExpansion instanceof Value)
					requiresExpansion = true;
		}


		//********************** Macro Expansion ************************/

		@Override
		public boolean expansionRequired() {
				return requiresExpansion;
		}
		
		@Override	
		public void expandInto(JavaNode j) throws ClassException {
				Value condition = (Value) children.elementAt(0);
				boolean actualval = condition.getBooleanValue();
				int branches = (children.size() - 1);
				if (actualval)
					j.addJavaNode((JavaNode) children.elementAt(1));
				else {
					if (branches == 2)
						j.addJavaNode((JavaNode) children.elementAt(2));
					// If there is only an if branch and the condition is false then
					// it expands to nothing
				}
		}


		//********************** Emitting *******************************/

		@Override
		void emit(EmitState state, boolean leaveOnStack, Statement continuation) 
              throws ClassException {
              generateLineNumberInfo(state);
              // Sharing implementation with conditional, a little perverse but reuses code 
              if (children.size() == 3)
                OperatorCall.emitConditional(state,
                false,
                (JavaNode) children.elementAt(0),
                (JavaNode) children.elementAt(1),
                (JavaNode) children.elementAt(2),
                continuation);
              else  {
                Expression exp = (Expression) children.elementAt(0);
                OperatorCall.emitConditional(state,
                  false,
                  (JavaNode) children.elementAt(0),
                  (JavaNode) children.elementAt(1),
                  null,
                  continuation);                 
              }
            }
}
