package com.gensym.classtools;

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

	private int handler_pc, catch_type;
      
      public int getHandlerPc()
      { 
         return handler_pc;
      }

      public int getCatchType()
      {
         return catch_type;
      }

	private String handler_type;
      public String getHandlerType()
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
		catch_type = Attribute.readU2(bytes, start+=2);
		
		boolean invalidStartEnd = (start_pc > code.length) || (end_pc > code.length) || (end_pc < start_pc);
		if (invalidStartEnd ||
			(handler_pc > code.length) ||
		    (catch_type > constantPool.getLength())){
				throw new ClassException();
		}
		
        if (catch_type == 0){
          handler_type = "any";
        } else {
        	handler_type = constantPool.getPool(catch_type).getClassName();
        }
        
	}

      ExceptionTableEntry(ConstantPool constantPool,
                          int start_pc,
                          int end_pc,
                          int handler_pc,
                          int catch_type)
  			throws ClassException  {
          this.start_pc = start_pc;
          this.end_pc = end_pc;
          this.handler_pc = handler_pc;
	    this.catch_type = catch_type;
          if (catch_type == 0)
            handler_type ="any";
          else handler_type = constantPool.getPool(catch_type).getClassName();
      }	

  
	@Override
	int normalize(final ConstantPool locals, final ConstantPool normals, final int index)
	  throws ClassException
	{
       if (catch_type == 0)
         return 0;

	 Constant handler = locals.getPool(catch_type);
	 int normalizedIndex = handler.normalize(locals,normals,index);
	 catch_type = normals.member(normals,handler);
	 handler_type = normals.getPool(catch_type).getClassName();
	 return normalizedIndex;
	}

    @Override
    void localize(ConstantPool locals, ConstantPool normals)
	   throws ClassException
	{
	  if (catch_type != 0) {
          Constant handler = normals.getPool(catch_type); 
          catch_type =  handler.localize(locals,normals);
          handler_type = locals.getPool(catch_type).getClassName();
        }
	}

	@Override
	void emit(DataOutputStream out)
	 throws IOException {
		if (false)
			System.out.println("Emitting an exception table");
		out.writeShort(start_pc);
		out.writeShort(end_pc);
		out.writeShort(handler_pc);
		out.writeShort(catch_type);
	}

	static void emit(ExceptionTableEntry[] etes,DataOutputStream out)
	   throws IOException {
		if (etes != null) {
		 out.writeShort(etes.length);
		 for (int i=0; i < etes.length;i++) {
			 etes[i].emit(out);
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
