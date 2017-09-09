package com.gensym.ntw.util;

import com.gensym.classes.Item;
import com.gensym.classes.Block;
import com.gensym.classes.Procedure;
import com.gensym.classes.MethodDeclaration;
import com.gensym.classes.Statement;
import com.gensym.classes.ClassDefinition;
import com.gensym.classes.Rule;
import com.gensym.classes.Relation;
import com.gensym.classes.KbWorkspace;
import com.gensym.jgi.G2AccessException;
import com.gensym.message.Trace;
import com.gensym.util.Symbol;
import com.gensym.util.Sequence;
import com.gensym.util.symbol.SystemAttributeSymbols;

public class AttributeHelper {
  private static final Symbol
  WILDCARD_ = Symbol.intern("*"),
    NONE_ = Symbol.intern ("NONE");

  public static String getTableHeader(Item item) throws G2AccessException {
    //item.getTableHeader();//NOTE: attribute not cachable!
    String header = "";
    Object name=null;
    if ((item instanceof Statement && !(item instanceof Rule)) ||
	(item instanceof Procedure && !(item instanceof MethodDeclaration))) {
      String text = null;
      if (item instanceof Statement)
	text = ((Statement)item).getText();
      else
	text = ((Procedure)item).getText();
      if (text != null) {
	int paren = text.indexOf('(');
	if (paren >0)
	  name = text.substring(0,paren);
      }
    } else if (item instanceof ClassDefinition) {
      name = ((ClassDefinition)item).getClassName();
    } else if (item instanceof Relation) {
      name = ((Relation)item).getRelationName();
    } else if (item instanceof KbWorkspace) {
      //The goal is to support custom captions/titles for workspace views,
      //especially if it does not have a g2 name and needed to add additional
      //custom information in title. Attributes on workspaces to get title name is title-bar-text.
      Sequence titleBarText = new Sequence();
      titleBarText.addElement(SystemAttributeSymbols.TITLE_BAR_TEXT_);
      String a_title =  (((KbWorkspace)item).getAttributeValues(titleBarText)).toString();
      if (a_title != null && !(a_title.equals(""))) {
        name = a_title.trim().replace('\n', ' ');
      }
    }
    else if (item instanceof Block)
      name = ((Block)item).getNames();
    if (name != null && !NONE_.equals(name))
      header = name+", ";
    header += "a "+ item.getG2ClassName().toString();
    return header.toLowerCase();
  }

  public static Symbol[] getNeededAttributes(Item item) {
    if ((item instanceof Statement && !(item instanceof Rule)) ||
	(item instanceof Procedure && !(item instanceof MethodDeclaration)))
      return new Symbol[] {SystemAttributeSymbols.TEXT_};
    else if (item instanceof ClassDefinition)
      return new Symbol[] {SystemAttributeSymbols.CLASS_NAME_};
    else if (item instanceof Relation)
      return new Symbol[] {SystemAttributeSymbols.RELATION_NAME_};
    else if (item instanceof Block)
      return new Symbol[] {SystemAttributeSymbols.NAMES_};
    else
      return new Symbol[] {WILDCARD_};
  }

}
