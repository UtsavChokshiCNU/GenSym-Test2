package com.gensym.uitools.utils;

import javax.swing.*;
import java.util.StringTokenizer;
import java.util.List;
import java.util.Vector;

public class DelimitedTextField extends JTextField{

  private String delimiter = ";";
  private boolean trim = true;
  
  public DelimitedTextField(){
  }

  public DelimitedTextField(int cols){
    super(cols);
  }

  public void setDelimiter(String delimiter){
    this.delimiter = delimiter;
  }

  public String getDelimiter(){
    return delimiter;
  }

  public String[] getValues(){
    StringTokenizer tokenizer = new StringTokenizer(getText(), delimiter);
    String[] values = new String[tokenizer.countTokens()];
    int i = 0;
    while (tokenizer.hasMoreTokens()){
      values[i] = tokenizer.nextToken();
      if (trim)
	values[i] = values[i].trim();
      i++;
    }
    return values;
  }

  public List getValuesList(){
    List valuesList = new Vector(0);
    String[] valuesArray = getValues();
    for (int i=0; i<valuesArray.length; i++){
      valuesList.add(valuesArray[i]);
    }
    return valuesList;
  }
      

  public void setText(String[] values){
    if (values == null || values.length == 0)
      setText("");
    else{    
      String text = values[0];
      for (int i=1; i<values.length; i++)
	text = text + delimiter + " " + values[i];
      setText(text);
    }
  }

  public void setText(List values){
    int size = values.size();
    String[] valuesArray = new String[size];
    if(size>0){
      for(int counter=0; counter<size; counter++){
	valuesArray[counter] = (String)values.get(counter);
      }
    }
    setText(valuesArray);
  }

  public void setTrimSpaces(boolean trim){
    this.trim = trim;
  }

  public boolean getTrimSpaces(){
    return trim;
  }
  
}
