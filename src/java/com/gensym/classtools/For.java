package com.gensym.classtools;

import java.util.Vector;

public class For extends Statement {
		
    		// Consider Providing a constructor to cover the cases when part is not specified.
  
		public For (VariableDeclaration varDec, Expression expression, ExpressionStatement[] updates, Statement body) {	
		}

		public For (ExpressionStatement[] inits, Expression expression, ExpressionStatement[] updates, 
			         Statement body) {	
		}


		private void initA(ExpressionStatement[] inits) {

		}

		private void initB(VariableDeclaration varDec) {
				
		}

		private void initC(Expression expression, ExpressionStatement[] updates, Statement body) {	
					
		}


		@Override
		void emit(EmitState state, boolean leaveOnStack, Statement continuation)
              throws ClassException {
                  generateLineNumberInfo(state);

			// Create jump tag instructions

			// Emit InitForm if any

			// Emit Goto with branch to tag #2

			// Emit Jump tag #1

			// Emit Statement if any

			// Emit Update forms if any

			// Emit Jump tag #2

			// Emit Condition with branch to tag #1

		}
}
