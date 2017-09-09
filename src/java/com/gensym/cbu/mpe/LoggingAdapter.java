package com.gensym.cbu.mpe;

import com.gensym.denali.model.*;

public class LoggingAdapter extends DataAdapter
{
  String text = "";

  public Object getExpressionValue (DataNodeImpl dataNode) 
  {
    return text;
  }

  public void extendLog(String newText)
  {
    if (text.equals(""))
      text = newText;
    else
      text = text + "\n" + newText;
    fireDataEvent(new DataEvent(this,1,text));
  }
}
