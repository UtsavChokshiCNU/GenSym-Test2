package com.gensym.editor.text;

import java.util.Vector;
import com.gensym.util.Symbol;
import com.gensym.ntw.TwAccess;
import javax.swing.text.JTextComponent;
import javax.swing.event.DocumentListener;
import java.util.Hashtable;
import com.gensym.classes.Item;

/**
 * EditContext is a central location in which editors can register 
 * themselves, and obtain a parsing context for the attribute they are 
 * editing. Likewise, a prompter for these editors can be set or retrieved
 * by anyone. Those adding themselves as parsing status, or prompt update
 * listeners will receive events from all open parsing sessions.  There
 * should only be one EditContext, which is accessed through the method
 * static EditContext.getContext(), and which can be set throught the static
 * method EditContext.setContext().
 */
public class EditContext {
  private static EditContext theContext;  
  private Vector promptsUpdatedListeners = new Vector();
  private Vector parsingStatusUpdatedListeners = new Vector();    
  private Hashtable editSessions = new Hashtable();
  private Hashtable editors = new Hashtable();
  private Prompter prompter;

  public JTextComponent getEditor(G2SideParser parser) {
    return (JTextComponent)editors.get(parser);
  }
  public Prompter getPrompter() {
    return prompter;
  }
  public void setPrompter(Prompter prompter) {
    this.prompter = prompter;
  }
  public G2SideParser addEditor(JTextComponent editor,
				TwAccess cxn,
				Symbol className,
				Symbol attributeName) {
			
    EditSession editSession = new EditSession(editor, cxn, className, attributeName);
    PromptsUpdatedListener[] puls;
    synchronized(promptsUpdatedListeners) {
      puls = new PromptsUpdatedListener[promptsUpdatedListeners.size()];
      promptsUpdatedListeners.copyInto(puls);
    }
    for (int i=0;i<puls.length;i++)  
      editSession.addPromptsUpdatedListener(puls[i]);
    
    ParsingStatusUpdatedListener[] psuls;
    synchronized(parsingStatusUpdatedListeners) {
      psuls = new ParsingStatusUpdatedListener[parsingStatusUpdatedListeners.size()];
      parsingStatusUpdatedListeners.copyInto(psuls);
    }
    for (int i=0;i<psuls.length;i++)  
      editSession.addParsingStatusUpdatedListener(psuls[i]);
    //promptsDisplay.addListSelectionListener(currentEditContextAdapter);
    editSessions.put(editor, editSession);
    editors.put(editSession.parser, editor);
    return editSession.parser;
  }
  
  public void removeEditor(Object editor) {
    EditSession editSession = (EditSession)editSessions.get(editor);
    PromptsUpdatedListener[] puls;
    synchronized(promptsUpdatedListeners) {
      puls = new PromptsUpdatedListener[promptsUpdatedListeners.size()];
      promptsUpdatedListeners.copyInto(puls);
    }
    for (int i=0;i<puls.length;i++) {
      PromptsUpdatedListener pul = puls[i];
      editSession.removePromptsUpdatedListener(pul);
      pul.updatePrompts(null);
    }
    ParsingStatusUpdatedListener[] psuls;
    synchronized(parsingStatusUpdatedListeners) {
      psuls = new ParsingStatusUpdatedListener[parsingStatusUpdatedListeners.size()];
      parsingStatusUpdatedListeners.copyInto(psuls);
    }
    for (int i=0;i<psuls.length;i++) {
      ParsingStatusUpdatedListener psul = psuls[i];
      editSession.removeParsingStatusUpdatedListener(psul);
      psul.changeParsingStatus(null);
    }
    editors.remove(editSession.parser);
    editSession.close();
    editSessions.remove(editSession);
  }

  public void addParsingStatusUpdatedListener(ParsingStatusUpdatedListener psul) {
    parsingStatusUpdatedListeners.addElement(psul);
  }
  
  public void removeParsingStatusUpdatedListener(ParsingStatusUpdatedListener psul) {
    parsingStatusUpdatedListeners.removeElement(psul);
  }  
  
  public void addPromptsUpdatedListener(PromptsUpdatedListener promptsUpdatedListener) {
    promptsUpdatedListeners.addElement(promptsUpdatedListener);
  }
  
  public void removePromptsUpdatedListener(PromptsUpdatedListener promptsUpdatedListener) {
    promptsUpdatedListeners.removeElement(promptsUpdatedListener);
  }  

  public static EditContext getContext() {
    if (theContext == null)
      theContext = new EditContext();
    return theContext;
  }

  public static void setContext(EditContext context) {
    //throw an exception if its already set?
    theContext = context;
  }

  class EditSession {
    private Session session;
    G2SideParser parser;
    private G2ParserDocumentListener docAdapter;
    private JTextComponent editor;
    
    public EditSession(JTextComponent editor,
		       TwAccess connection,
		       Symbol className,
		       Symbol attributeName) {
      this.editor = editor;
      session = new Session();
      parser = session.openParsingSession(connection,
					  className,
					  attributeName);
      docAdapter = new G2ParserDocumentListener(parser);    
      editor.getDocument().addDocumentListener(docAdapter);
      editor.addCaretListener(docAdapter);
    }

    public void addPromptsUpdatedListener(PromptsUpdatedListener l) {
      parser.addPromptsUpdatedListener(l);
    }
    
    public void removePromptsUpdatedListener(PromptsUpdatedListener l) {
      if (parser != null)
	parser.removePromptsUpdatedListener(l);
    }

    public void addParsingStatusUpdatedListener(ParsingStatusUpdatedListener l) {
      parser.addParsingStatusUpdatedListener(l);
    }
    
    public void removeParsingStatusUpdatedListener(ParsingStatusUpdatedListener l) {
      if (parser != null)      
	parser.removeParsingStatusUpdatedListener(l);
    }
    
    public void close() {
      editor.getDocument().removeDocumentListener(docAdapter);
      editor.removeCaretListener(docAdapter);      
      session = null;//dispose?
      parser.shutdownParsingContext();
      parser = null;
      docAdapter = null;
    }
  }

}
