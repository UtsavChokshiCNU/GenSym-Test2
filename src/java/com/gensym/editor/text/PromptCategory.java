package com.gensym.editor.text;

import com.gensym.util.Structure;
import com.gensym.util.Symbol;
import com.gensym.message.Trace;
import com.gensym.jgi.G2AccessException;
import java.util.Vector;

/**
 * A class that encapsulates the behaviors of a prompting category,
 * allowing access to its categories completions through the convieniency
 * of the method getCompletions(). 
 */
public class PromptCategory {
  private static final Symbol G2_MENU_OF_NAMES_FOR_CATEGORY_ =
  Symbol.intern ("G2-MENU-OF-NAMES-FOR-CATEGORY");
  private static final Symbol TOKEN_PROMPTS_FOR_CATEGORY_ =
  Symbol.intern ("TOKEN-PROMPTS-FOR-CATEGORY");    
  private String category;
  private G2SideParser parser;
  
  public PromptCategory(String category, G2SideParser parser) {
    this.category = category;
    this.parser = parser;
  }
  @Override
  public String toString() {
    return "["+category+"]";
  }
  private String stripOffTheANY(String originalCategoryPrompt) {
    String newPrompt = originalCategoryPrompt.substring(4);
    return newPrompt;
  }
  
  public Vector getCompletions() {
    Integer handle = parser.getParsingContext();
    Symbol categoryName = Symbol.intern(stripOffTheANY(category).toUpperCase());
    Object[] args = {categoryName,handle};
    try {
      Object returnValue = parser.getConnection().callRPC(G2_MENU_OF_NAMES_FOR_CATEGORY_, args, 3000000);
      if (returnValue instanceof Structure) 
	return (Vector)((Structure)returnValue).getAttributeValue(TOKEN_PROMPTS_FOR_CATEGORY_, null); 
    } catch (G2AccessException ae) {
      Trace.exception(ae);
    }
    return null;
  }
    
}
