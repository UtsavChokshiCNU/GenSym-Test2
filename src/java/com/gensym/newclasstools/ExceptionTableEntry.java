package com.gensym.newclasstools;

import java.io.*;

public class ExceptionTableEntry extends Info{

	private int start_pc, end_pc;
      
      public int getStartPc()
      {
        return start_pc;
      }

      public int getEndPc()
      {
        return end_pc;
      }

  private int handler_pc;
  private ClassConstant catch_type;
      
  public int getHandlerPc()
  { 
    return handler_pc;
  }

  public Type getCatchType()
  {
    return catch_type.getMyClass();
  }

  private Type handler_type;
  public Type getHandlerType()
      {
          return handler_type;
      }
	      
      private static final boolean trace = false;

  ExceptionTableEntry(ConstantPool constantPool,byte [] bytes, 
		      byte[] code,int start) 
      throws ClassException	
  {
    start_pc = Attribute.readU2(bytes, start);
    end_pc = Attribute.readU2(bytes, start+=2);
    handler_pc = Attribute.readU2(bytes, start+=2);
    int catch_type_index = Attribute.readU2(bytes, start+=2);
    if ((start_pc > code.length) ||
	(end_pc > code.length) ||
	(end_pc < start_pc) ||
	(handler_pc > code.length) ||
	(catch_type_index > constantPool.getLength()))
      throw new ClassException();

    if (catch_type_index == 0)
      catch_type = null;
    else 
      catch_type = (ClassConstant)constantPool.getConstant(catch_type_index);
    
    if (false)
      System.out.println("ExceptionTableEntry:"  + start_pc + " " + end_pc + " " +
			 handler_pc + " " + catch_type );
		
    
            if (catch_type == null)
              handler_type = null;
            else handler_type = catch_type.getMyClass();
		
		if (false)
			System.out.println("Method throws exception: " + handler_type);
	}

      ExceptionTableEntry(int start_pc,
                          int end_pc,
                          int handler_pc,
                          ClassConstant catch_type)
  			throws ClassException  {
          this.start_pc = start_pc;
          this.end_pc = end_pc;
          this.handler_pc = handler_pc;
	    this.catch_type = catch_type;
          if (catch_type == null)
            handler_type = null;
          else handler_type = catch_type.getMyClass();
      }	

	@Override
	void emit(DataOutputStream out, ConstantPool cp)
	 throws IOException {
	   if (false)
	     System.out.println("Emitting an exception table");
	   out.writeShort(start_pc);
	   out.writeShort(end_pc);
	   out.writeShort(handler_pc);
	   if (catch_type == null)
	     out.writeShort(0);
	   else
	     out.writeShort(cp.getIndex(catch_type));
	}

	static void emit(ExceptionTableEntry[] etes,DataOutputStream out, ConstantPool cp)
      throws IOException
  {
    if (etes != null) {
      out.writeShort(etes.length);
      for (int i=0; i < etes.length;i++) {
	etes[i].emit(out, cp);
      }
    }
    else
      out.writeShort(0);
  }

	public static void toStdout(ExceptionTableEntry[] etes, String prefix) {
			System.out.println(prefix + "Exception Table");
			System.out.println(prefix + "---------------");
			Info.toStdout(etes,prefix);
	}

	@Override
	public String toString() {
			return "<ExceptionTableEntry, handletype=" + handler_type +
				   ", startpc=" + start_pc +
				   ", endpc=" + end_pc +
				   ", hanlderpc=" + handler_pc +
				   ", catchtype=" + catch_type + ">";
	}
}
