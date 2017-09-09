package antlr;

public class InteractiveParserToken extends CommonToken
{
  protected int column;

  public int getColumn() { return column; }

  public void setColumn(int c) { column=c; }
}
