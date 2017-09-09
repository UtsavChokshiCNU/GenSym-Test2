package com.gensym.newclasstools;

import java.util.Hashtable;
import java.util.Vector;

public class Try extends Statement {
    
    private boolean requiresExpansion = false;;
    
    private static Type throwableType  
             = Type.makeType("java.lang.Throwable");
    private static String throwableString = "java/lang/Throwable";  

    private int countOfCatches;
    boolean extraCatchBlock = false;
    boolean includesFinally = false;

    public Try(Block tryBlock,
      VariableDeclaration[] catchVars,
      Block[] catchBlocks,
      Block finallyBlock) 
      throws ClassException
    {
      throw new ClassException("Try not yet implemented (old classtools implementation was completely broken)");
    }

    public Try(Block tryBlock,
      VariableDeclaration[] catchVars,
      Block[] catchBlocks) 
      throws ClassException
    {
      this(tryBlock,catchVars,catchBlocks, null);
    }
    
    public Try(Block tryBlock,
               Block finallyBlock) 
               throws ClassException
    {
        this(tryBlock, null, null, finallyBlock);
    }

  /*
    private Block generateCatchBlock(VariableDeclaration vdecl, 
                                     Block block,
                                     Type exceptionType)
            throws ClassException
    {
      Block newBlock =  new Block();
      newBlock.add(vdecl);
      newBlock.add(new OperatorCall("=",
        new Expression[] {vdecl.getVariable(),
        new Noop(exceptionType,true)}));
      newBlock.add(block);
      return newBlock;
    }


    private Block generateCatchBlockForFinally (SubRoutineBegin subroutinebegin)
            throws ClassException
    {
      Block newBlock =  new Block();
      VariableDeclaration vdecl 
        = VariableDeclaration.generateUniqueVariableDeclaration("Ljava/lang/Throwable;");
      Variable var = vdecl.getVariable();
      SubRoutineJump subjump = subroutinebegin.getSubRoutineJump();
        
      newBlock.add(vdecl);
      newBlock.add(new OperatorCall("=",
        new Expression[] {var,
        new Noop(var.getExpressionType(),true)}));
      newBlock.add(subjump);
      newBlock.add(new Throw(var));
      return newBlock;
    }

    private Block generateFinallyBlock(Block block, SubRoutineBegin subroutinebegin) 
          throws ClassException
    {
      Block newBlock = new Block();
      SubRoutineReturn subroutineReturn = subroutinebegin.getSubRoutineReturn();
    
      newBlock.add(subroutinebegin);
      newBlock.add(block);
      newBlock.add(subroutineReturn);
      return newBlock;
    }


    void emit(EmitState state, boolean leaveOnStack,
              Statement continuation)
      throws ClassException {
        generateLineNumberInfo(state);  
        emit(state, leaveOnStack, continuation,
             children, countOfCatches, 
             extraCatchBlock, includesFinally);
    }


    static void emit(EmitState state, 
                     boolean leaveOnStack,
                     Statement continuation,
                     Vector children,
                     int countOfCatches,
                     boolean extraCatchBlock,
                     boolean includesFinally)
          throws ClassException 
    { 
        Vector instructions = state.instructions;
        Statement possibleContinuation;
        int i = 0;
        JavaNode tryBlock = (JavaNode) children.elementAt(i++);
        int size = children.size();
                
        // Generate labels for each individual exception type
        
        Instruction afterTry = state.getJumpTargetInstruction();
        Instruction endOfTryCatch = null;

        if ((continuation != null) || includesFinally)
          endOfTryCatch = state.getJumpTargetInstruction();

        Instruction[] catchStarts = new Instruction[countOfCatches]; 
        JavaNode[] catchBlocks = new JavaNode[countOfCatches];

        for (int j=0; j < countOfCatches ; j++) {
          Instruction catchTarget =  state.getJumpTargetInstruction();  
          catchStarts[j] = catchTarget;
          ClassRef exception = (ClassRef) children.elementAt(i+ (2 * j));
          exception.generateConstants(state.pool);  
          catchBlocks[j] = (JavaNode) children.elementAt(i + (2 * j) + 1);
          Instruction tryInstruct = state.getTryInstruction(afterTry,
            catchTarget,
            exception.getWhere());
          instructions.addElement(tryInstruct);
        } 

        Instruction extraCatchTarget = null;
        if (extraCatchBlock) {
          extraCatchTarget =  state.getJumpTargetInstruction();  
          Instruction tryInstruct 
            = state.getTryInstruction(afterTry,
                                      extraCatchTarget,
                                      0);
          instructions.addElement(tryInstruct);
        }

        if (includesFinally)
          possibleContinuation = new Statement();
        else possibleContinuation = continuation;

        // Emit the try block
        tryBlock.emit(state,leaveOnStack,possibleContinuation);

        
        if ((countOfCatches > 0) && (possibleContinuation != null))
        {
          Instruction ins = Instruction.makeInstruction(opc_goto,0);
          ins.jumpTagIfAny = endOfTryCatch.jumpTagIfAny;
          instructions.addElement(ins);
        }
        else state.doContinuation(possibleContinuation);

        instructions.addElement(afterTry);

        // Emit the catch blocks
        for (int k = 0; k < countOfCatches; k++) {
          JavaNode catchBlock = catchBlocks[k];
          instructions.addElement(catchStarts[k]);
          catchBlock.emit(state,leaveOnStack,possibleContinuation);
          if ((k + 1) < countOfCatches) {
            if (possibleContinuation != null)
            {
              Instruction ins = Instruction.makeInstruction(opc_goto,0);
              ins.jumpTagIfAny = endOfTryCatch.jumpTagIfAny;
              instructions.addElement(ins);
            }
            else state.doContinuation(possibleContinuation);
          }
        }

        if (endOfTryCatch != null)
          instructions.addElement(endOfTryCatch);

        // Emit finally block if there is one
        int location = (countOfCatches * 2) + i;
        if (includesFinally) {

          // Emit jsr  
          SubRoutineJump subJump = (SubRoutineJump) children.elementAt(location++);
          subJump.emit(state,false,continuation);

          // Emit jump to end of statement

          Instruction endOfStatement = null;
          if (continuation != null) {
            endOfStatement = state.getJumpTargetInstruction();
            Instruction gotoEnd = Instruction.makeInstruction(opc_goto,0);
            gotoEnd.jumpTagIfAny = endOfStatement.jumpTagIfAny;
            instructions.addElement(gotoEnd);
          }
          else state.doContinuation(continuation);

          // Only when an additonal catch needed to be created
          if (extraCatchBlock) { 
              instructions.addElement(extraCatchTarget);
              Block extraCatch = (Block) children.elementAt(location++);
              extraCatch.emit(state,false,continuation);
          }

          Block finallyBlock = (Block) children.elementAt(location);
          finallyBlock.emit(state,false,continuation);
          if (continuation != null)
            instructions.addElement(endOfStatement);
        }        
        state.doContinuation(continuation);
    }
    */
 }
