package antlr;

public class InteractiveParserResult
{
  boolean ok;
  boolean complete;
  int column;
  int line;
  String errorMessage;
  TraceNode[] stack;

  InteractiveParserResult(boolean ok,
			  boolean complete,
			  int line,
			  int column,
			  String errorMessage,
			  TraceNode[] stack)
  {
    this.ok = ok;
    this.complete = complete;
    this.line = line;
    this.column = column;
    this.errorMessage = errorMessage;
    this.stack = stack;
  }

  public boolean isOk()
  {
    return ok;
  }

  public boolean isComplete()
  {
    return complete;
  }

  public int getColumn()
  {
    return column;
  }

  public int getLine()
  {
    return line;
  }

  public String getErrorMessage()
  {
    return errorMessage;
  }

  public TraceNode[] getStack()
  {
    return stack;
  }

  public String pprintString()
  {
    String outputMsg = "";

    outputMsg = outputMsg.concat("ParseResult: ok="+ok+" complete="+complete+
		     " at line="+line+", column="+column+"\n");
    if (ok)
      {
	if (stack != null)
	  {
	    int i,len = stack.length;
	    for (i=0; i<len; i++)
	      outputMsg = outputMsg.concat("  "+stack[i]+"\n");
	  }
	else
	  outputMsg = outputMsg.concat("empty stack\n");
      }
    else
      outputMsg = outputMsg.concat("  "+errorMessage+"\n");

    return outputMsg;
  }

  public void pprint()
  {
    System.out.println(pprintString());
  }
}
