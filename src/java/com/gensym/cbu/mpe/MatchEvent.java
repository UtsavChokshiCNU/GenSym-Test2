package com.gensym.cbu.mpe;

import java.util.EventObject;

public class MatchEvent extends EventObject
{
  String tokenType;
  String matchedText;
  String[] bindingNames;
  String[] bindingValues;

  public MatchEvent(Object source, String tokenType,
		    String matchedText,
		    String[] bindingNames,
		    String[] bindingValues)
  {
    super(source);
    this.tokenType = tokenType;
    this.matchedText = matchedText;
    this.bindingNames = bindingNames;
    this.bindingValues = bindingValues;
  }

  public String getMatchedText()
  {
    return matchedText;
  }

  public String getTokenType()
  {
    return tokenType;
  }

  @Override
  public String toString()
  {
    StringBuffer buffer 
      = new StringBuffer("<Match type="+tokenType+" text=\""+matchedText+"\" ");
    if (bindingNames != null)
      {
	for (int i=0; i<bindingNames.length; i++)
	  {
	    buffer.append("\n  "+bindingNames[i]+"=\""+bindingValues[i]+"\" ");
	  }
      }
    buffer.append(">");
    return buffer.toString();
  }

}
