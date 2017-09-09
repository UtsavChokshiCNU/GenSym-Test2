package com.gensym.gcg;

import java.util.StringTokenizer;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import com.gensym.classes.Item;
import com.gensym.controls.AttributeEditor;
import com.gensym.dlgevent.ObjectChangeListener;
import com.gensym.dlgevent.ObjectUpdateListener;
import com.gensym.dlgevent.ObjectUpdateEvent;
import com.gensym.jgi.G2AccessException;
import com.gensym.ntw.TwAccess;
import com.gensym.message.Trace;
import com.gensym.util.Sequence;
import com.gensym.util.Structure;
import com.gensym.util.Symbol;

/**
 *  G2ReadOnlyTextArea is a text area for displaying the value of an attribute as text
 *  The text area is contained in a scroll pane.
 *  This component is typically used to display non-simple types, e.g., sequence and
 *  structure, or attributes with grammar.  The G2ReadOnlyTextArea responds to ObjectUpdateEvents.
 **/
public class G2ReadOnlyTextArea extends JScrollPane implements AttributeEditor{

  private static final Symbol g2GetDenotedAttributeTexts_
     = Symbol.intern("G2-GET-DENOTED-ATTRIBUTE-TEXTS");

  protected JTextArea textArea;

  TwAccess connection;
  protected Item item;
  protected Symbol attribute;
  protected Structure denotation;

  private int maxRows = 5;
  private Runnable updater = new TextAreaUpdater();

  public G2ReadOnlyTextArea(TwAccess connection, Item item, Symbol attribute, Structure denotation){
    super(VERTICAL_SCROLLBAR_AS_NEEDED, HORIZONTAL_SCROLLBAR_NEVER);
    this.connection = connection;
    this.item = item;
    this.attribute = attribute;
    this.denotation = denotation;

    textArea = createTextArea();
    setViewportView(textArea);
    textArea.setEditable(false);
    textArea.setLineWrap(true);
    textArea.setWrapStyleWord(true);
    textArea.setBackground(java.awt.Color.lightGray);
  }

  protected JTextArea createTextArea() {
    return new JTextArea("", 1, 25){      
      @Override
      public boolean isFocusTraversable(){
	return false;
      }
    };
  }
  
  @Override
  public boolean isFocusTraversable(){
    return false;
  }

  @Override
  public void objectUpdated(ObjectUpdateEvent e){
    new Thread(updater).start();
  }

  void update() throws G2AccessException{
    String newText = getAttributeText();
    if (newText != null){
      if (firstUpdate && maxRows > 0){
	StringTokenizer tokenizer = new StringTokenizer(newText, "\n");
	textArea.setRows(Math.min(tokenizer.countTokens(), maxRows));
      }
      else
	firstUpdate = false;
      textArea.setText(newText);
      textArea.repaint();//bug?
    }
    else
      textArea.setText("<NO-TEXT-FOR-ATTRIBUTE>");
  }

  private boolean firstUpdate = true;

  class TextAreaUpdater implements Runnable{
    @Override
    public void run(){
      try{
	if (denotation == null) {
		return;
	}
	update();
      }
      catch(G2AccessException ex){
	Trace.exception(ex);
      }
    }
  }

  String getAttributeText() throws G2AccessException{
    Sequence request = new Sequence();
    request.addElement(denotation);
    Sequence result = null;
    if (connection != null && connection.isAlive())
      result = (Sequence)connection.callRPC(g2GetDenotedAttributeTexts_, 
					    new Object[] {item, request});
    if (result == null)
      return null;
    return (String)result.elementAt(0);
  }

  @Override
  public Symbol getAttribute(){
    return attribute;
  }

  @Override
  public void setAttribute(Symbol symbol){
  }

  @Override
  public void addObjectChangeListener (ObjectChangeListener listener){
  }

  @Override
  public void removeObjectChangeListener(ObjectChangeListener listener){
  }
  

}









