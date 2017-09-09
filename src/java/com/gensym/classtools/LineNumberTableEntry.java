package com.gensym.classtools;
import java.io.*;

public class LineNumberTableEntry 
{
  private int start_pc; 

  public int getStartPc()
  {
      return start_pc;
  }

  private int line_number;

  public int getLineNumber()
  {
      return line_number;
  }

  public LineNumberTableEntry(int start_pc, int line_number)
  {
    this.start_pc = start_pc;
    this.line_number = line_number;
  }

  LineNumberTableEntry(byte [] bytes, 
    int start) 
    throws ClassException	
  { 
    start_pc = Attribute.readU2(bytes,start);
    line_number = Attribute.readU2(bytes,start+2);
  }

  void emit(DataOutputStream out) 
    throws IOException
  {
    out.writeShort(start_pc);
    out.writeShort(line_number);
  }

  public void toStdout(String prefix) {
       System.out.println(prefix + this);
  }

  @Override

  public String toString() {
      return "<LineNumberTableEntry, start_pc=" + start_pc +
               ", line_number=" + line_number + ">";
  }

}
