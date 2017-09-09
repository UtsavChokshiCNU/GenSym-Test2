package antlr;

import java.util.Vector;

public class TraceNode implements java.io.Serializable
{
  public static long serialVersionUID = 1;

  public static final int RULE_DEF = 0;
  public static final int SEQ = 1;
  public static final int ALT = 2;
  public static final int OPTIONAL = 3;
  public static final int ZERO_OR_MORE = 4;
  public static final int ONE_OR_MORE = 5;
  public static final int TOKEN_REF = 6;
  public static final int RULE_REF = 7;
  public static final int LITERAL = 8;

  public static final String[] typeNames = 
  { "RULE_DEF", "SEQ", "ALT", "OPTIONAL", "ZERO_OR_MORE",
      "ONE_OR_MORE", "TOKEN_REF", "RULE_REF", "LITERAL" };

  public int type;
  public String text;
  public Vector subNodes;

  public TraceNode(int type)
  {
    this.type = type;
  }

  public TraceNode(int type, String text)
  {
    this.type = type;
    this.text = text;
  }

  public void extendSubNodes(TraceNode node)
  {
    if (subNodes == null)
      subNodes = new Vector();
    subNodes.addElement(node);
  }

  public String toString()
  {
    if (type == TOKEN_REF ||
	type == RULE_REF ||
	type == LITERAL)
      return text;
    else
      {
	StringBuffer buffer = new StringBuffer("("+typeNames[type]);
	if (type == RULE_DEF)
	  buffer.append(" "+text);
	if (subNodes == null)
	  buffer.append(")");
	else
	  {
	    int i,len = subNodes.size();
	    for (i=0; i<len; i++)
	      buffer.append(" "+subNodes.elementAt(i));
	  }
	buffer.append(")");
	return buffer.toString();
      }
  }
}
