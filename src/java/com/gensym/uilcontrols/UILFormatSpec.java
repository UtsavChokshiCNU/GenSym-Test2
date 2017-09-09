package com.gensym.uilcontrols;

import java.awt.Component;
import java.awt.TextField;
import java.io.Serializable;
import java.io.IOException;
import java.io.EOFException;
import java.util.StringTokenizer;
import com.gensym.util.Symbol;
import com.gensym.util.UnexpectedException;
import com.gensym.controls.FieldType;
import com.gensym.controls.LimitMode;
import com.gensym.jgi.G2Access;
import com.gensym.jgi.G2AccessException;
import com.gensym.message.Trace;
import com.gensym.types.G2SyntaxException;
import com.gensym.types.G2ParserException;
import com.gensym.types.G2TokenizerException;
import com.gensym.classes.modules.uillib.UilFormatSpecificationClass;

class UILFormatSpec implements Serializable{

  static final long serialVersionUID = 321224503142806976L;

  private static final Symbol UNSPECIFIED_ = Symbol.intern("UNSPECIFIED");
  private static final Symbol UIL_FORMAT_SPECIFICATION_CLASS_ = 
                                         Symbol.intern("UIL-FORMAT-SPECIFICATION-CLASS");
  private static final Symbol SYMBOL_ = Symbol.intern("SYMBOL");
  private static final Symbol TEXT_ = Symbol.intern("TEXT");
  private static final Symbol INTEGER_ = Symbol.intern("INTEGER");
  private static final Symbol QUANTITY_ = Symbol.intern("QUANTITY");

  private static final Symbol DEFAULT_ = Symbol.intern("DEFAULT");
  private static final Symbol UPPER_CASE_ALL_ = Symbol.intern("UPPER-CASE-ALL");
  private static final Symbol CAPITALIZE_FIRST_WORD_ = Symbol.intern("CAPITALIZE-FIRST-WORD");
  private static final Symbol LOWER_CASE_ALL_ = Symbol.intern("LOWER-CASE-ALL");
  private static final Symbol MANAGE_QUOTES_ = Symbol.intern("MANAGE-QUOTE-MARKS");

  public static final String OK = "ok";

  private String type;
  private FieldType fieldType;
  private Symbol uilFormatSpecificationName;
  private boolean formatSpecExists = false;
  private boolean formatTypeSpecified = false;
  private Symbol uilTextCaseHandling = DEFAULT_;
  private boolean manageQuotes = true;
  private boolean uilRevertValueOnError = true;
  private boolean uilAllowNoneAsValid = false;
  private LimitMode lowerValueLimitMode = new LimitMode("none");
  private LimitMode upperValueLimitMode = new LimitMode("none");
  private double minimumValue;
  private double maximumValue;
  private LimitMode lowerLengthLimitMode = new LimitMode("none");
  private LimitMode upperLengthLimitMode = new LimitMode("none");
  private double minimumLength;
  private double maximumLength;

  static UILFormatSpec create(G2Access connection, Symbol uilFormatSpecificationName) 
       throws G2AccessException{
    UILFormatSpec formatSpec = new UILFormatSpec("Text");

    UilFormatSpecificationClass uilFormatSpec = null;
    if (!uilFormatSpecificationName.equals(UNSPECIFIED_)){
      try{
	uilFormatSpec = (UilFormatSpecificationClass)connection.getUniqueNamedItem(UIL_FORMAT_SPECIFICATION_CLASS_, uilFormatSpecificationName);
      }
      catch(G2AccessException ex){
	//it is ok if named format spec does not exist
	Trace.exception(ex);
      }
    }

    if (uilFormatSpec != null){
      Symbol type = (Symbol)uilFormatSpec.getUilFormatType();
      formatSpec.formatTypeSpecified = true;
      if (type.equals(SYMBOL_)) formatSpec.fieldType = new FieldType("Symbol");
      else if (type.equals(TEXT_)) formatSpec.fieldType = new FieldType("Text");
      else if (type.equals(INTEGER_)) formatSpec.fieldType = new FieldType("Integer");
      else if (type.equals(QUANTITY_)) formatSpec.fieldType = new FieldType("Quantity");
      else formatSpec.formatTypeSpecified = false;

      formatSpec.uilFormatSpecificationName = uilFormatSpecificationName;
      formatSpec.formatSpecExists = true;
      formatSpec.uilTextCaseHandling = (Symbol)uilFormatSpec.getUilTextCaseHandling();
      Symbol manageQuotes = (Symbol)uilFormatSpec.getUilQuoteMarkHandling();
      formatSpec.manageQuotes = (MANAGE_QUOTES_.equals(manageQuotes));
      formatSpec.uilRevertValueOnError = ((Boolean)uilFormatSpec.getUilRevertValueOnError()).booleanValue(); 
      formatSpec.uilAllowNoneAsValid = ((Boolean)uilFormatSpec.getUilAllowNoneAsValid()).booleanValue(); 
      Object value;
      value = uilFormatSpec.getUilMinimumValue();
      if (value instanceof Number){
	formatSpec.lowerValueLimitMode = new LimitMode("inclusive");
	formatSpec.minimumValue = ((Number)value).doubleValue();
      }
      value = uilFormatSpec.getUilMaximumValue();
      if (value instanceof Number){
	formatSpec.upperValueLimitMode = new LimitMode("inclusive");
	formatSpec.maximumValue = ((Number)value).doubleValue();
      }
      value = uilFormatSpec.getUilMinimumLength();
      if (value instanceof Number){
	formatSpec.lowerLengthLimitMode = new LimitMode("inclusive");
	formatSpec.minimumLength = ((Number)value).doubleValue();
      }
      value = uilFormatSpec.getUilMaximumLength();
      if (value instanceof Number){
	formatSpec.upperLengthLimitMode = new LimitMode("inclusive");
	formatSpec.maximumLength = ((Number)value).doubleValue();
      }
    }

    return formatSpec;
  }

  private UILFormatSpec(String type){
    this.type = type;
    fieldType = new FieldType(type);
  }

  void setFormatType(String type){
    this.type = type;
    fieldType = new FieldType(type);
    formatTypeSpecified = true;
  }

  void setFormatTypeForValue(Object value){
    if (value instanceof Integer)
      type = "Integer";
    else if (value instanceof Number)
      type = "Quantity";
    else if (value instanceof Symbol)
      type = "Symbol";
    else
      type = "Text";
    fieldType = new FieldType(type);
  }

  boolean isFormatTypeSpecified(){
    return formatTypeSpecified;
  }

  boolean isText(){
    return fieldType.isText();
  }

  void setMinimumValue(double minValue){
    lowerValueLimitMode = new LimitMode("inclusive");
    minimumValue = minValue;
  }

  void setMaximumValue(double maxValue){
    upperValueLimitMode = new LimitMode("inclusive");
    maximumValue = maxValue;
  }

  boolean getUilRevertValueOnError(){
    return uilRevertValueOnError;
  }

  boolean getManageQuotes(){
    return manageQuotes;
  }

  public String objectToString(Object object){
    return formatText(object.toString());
  } 

  private String formatText(String txt){
    if (!formatSpecExists) return txt;
    String formattedText = txt;
    if (fieldType.isText()){
      if (uilTextCaseHandling != null){
	if (uilTextCaseHandling.equals(UPPER_CASE_ALL_))
	  return formattedText.toUpperCase();
	else if (uilTextCaseHandling.equals(CAPITALIZE_FIRST_WORD_))
	  return upperCaseWords(formattedText);
	else if (uilTextCaseHandling.equals(LOWER_CASE_ALL_))
	  return formattedText.toLowerCase();
      }
    }
    return formattedText;
  }

  private String upperCaseWords(String text){
    StringTokenizer tokenizer = new StringTokenizer(text);
    String formattedText = null;
    while (tokenizer.hasMoreTokens()){
      if (formattedText == null)
	formattedText = capitalizeWord(tokenizer.nextToken());
      else
	formattedText= formattedText + " " + capitalizeWord(tokenizer.nextToken());
    }
    return formattedText;
  }

  private String capitalizeWord(String word){
    String firstLetter = word.substring(0, 1).toUpperCase();
    return firstLetter + word.substring(1, word.length());
  }

  public Object stringToObject(String text)
       throws G2TokenizerException, G2ParserException, EOFException, IOException{
    if (fieldType.isText())
      return text;
    else
      return fieldType.stringToObject(text);
  }

  private static final String NONE = "none";

  String validate(String text, Symbol attributeName){
    //System.out.println("UILFormatSpec.validate("+text+","+attributeName+")");
    if (!formatSpecExists) 
      return "Error: The specification object named:"+uilFormatSpecificationName+" could not be found";
    else{
      if (NONE.equals(text.toLowerCase())){
	//System.out.println("uilAllowNoneAsValid="+uilAllowNoneAsValid);
	if (uilAllowNoneAsValid) return OK;
	else return "The value <none> was specified for the format "+uilFormatSpecificationName+" which is expecting a value of type "+type+".\n  This format does not allow <none> as a valid option.";
      }
      else{
	try{
	  //check type
	  Object object = stringToObject(text);

	  //check character length
	  int length = text.length();
	  //System.out.println("length="+length+" lowerLengthLimitMode="+lowerLengthLimitMode+" minLength="+minimumLength+" uppperLengthLimitMode="+upperLengthLimitMode+" maxLength="+maximumLength);
	  if (lowerLengthLimitMode.isInclusive() && length < minimumLength)
	    return "Data Input Error: \n\n Entering a value for attribute: "+attributeName+" \n\n Expected a "+type+" value having a character length no less than "+minimumLength+".  Received: "+object;
	  if (upperLengthLimitMode.isInclusive() && length > maximumLength)
	    return "Data Input Error: \n\n Entering a value for attribute: "+attributeName+" \n\n Expected a "+type+" value having a character length no more than "+maximumLength+".  Received: "+object;
	  
	  //check range
	  if (fieldType.isNumeric()){
	    //System.out.println("lowerValueLimitMode="+lowerValueLimitMode+" minValue="+minimumValue+" upperValueLimitMode="+upperValueLimitMode+" maxValue="+maximumValue); 
	    if (lowerValueLimitMode.isInclusive() && (((Number)object).doubleValue() < minimumValue))
	      return "Data Input Error: \n\n Entering a value for attribute: "+attributeName+" \n\n Expected a minimum value of "+minimumValue+". \n\n Received: "+object;
	    if (upperValueLimitMode.isInclusive() && (((Number)object).doubleValue() > maximumValue))
	      return "Data Input Error: \n\n Entering a value for attribute: "+attributeName+" \n\n Expected a maximum value of "+maximumValue+". \n\n Received: "+object;
	  }
	}
	catch(G2SyntaxException syntaxException){
	  return "Data Input Error: \n\n Entering a value for attribute: "+attributeName+" \n\n Expected a "+type+" but received "+text;
	}
	catch(EOFException eof){
	  return "Data Input Error: \n\n Entering a value for attribute: "+attributeName+" \n\n Expected a "+type+" but received "+text;
	}
	catch(IOException e){
	    throw new UnexpectedException(e);
	}
      }
    }
    return OK;
  }

}
