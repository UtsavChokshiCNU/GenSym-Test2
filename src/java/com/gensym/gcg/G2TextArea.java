package com.gensym.gcg;

import java.awt.Frame;
import java.awt.Window;
import java.awt.event.ComponentAdapter;
import java.awt.event.ComponentEvent;
import java.util.Locale;
import java.util.StringTokenizer;
import javax.swing.JTextArea;
import com.gensym.classes.Item;
import com.gensym.dlgevent.ObjectUpdateListener;
import com.gensym.dlgevent.ObjectUpdateEvent;
import com.gensym.editor.text.Session;
import com.gensym.jgi.G2AccessException;
import com.gensym.ntw.TwAccess;
import com.gensym.message.Trace;
import com.gensym.message.Resource;
import com.gensym.util.Sequence;
import com.gensym.util.Structure;
import com.gensym.util.Symbol;

/**
 *  G2TextArea is a text area for displaying and editing a complex attribute type, e.g., an attribute of type
 *  sequence, structure, object, or an attribute with grammar.  The attribute is edited by a sub dialog.
 *  @see launchSubDialog()
 */
public class G2TextArea extends G2ReadOnlyTextArea implements EditedBySubDialog{

  private static final Resource i18n = Resource.getBundle("com.gensym.gcg.UiLabels");
  private Item subItem;
  private Symbol className;
  private Locale locale;
  private Symbol userMode;

  /**
   *  Creates a G2TextArea for editing an attribute that is an item.
   */
  public G2TextArea(TwAccess connection, Item item, Item subItem, Symbol attribute, Structure denotation, 
		    Symbol userMode, Locale locale){
    super(connection, item, attribute, denotation);
    this.subItem = subItem;
    this.userMode = userMode;
    this.locale = locale;
    textArea.setBackground(java.awt.Color.white);
  }

  /**
   *  Creates a G2TextArea for editing a complex attribute type that is not an item.
   */
  public G2TextArea(TwAccess connection, Item item, Structure denotation, Symbol className, 
		    Symbol attributeName){
    super(connection, item, attributeName, denotation);
    this.className = className;
    textArea.setBackground(java.awt.Color.white);
  }

  private Window fullEditor = null;


  /**
   * Launches a dialog for editing the attribute.  The text editor is used to edit complex attribute
   * types.  The DialogManager is used to launch a dialog to edit an attribute that is an item.
   */
  @Override
  public void launchSubDialog(){
    if (subItem == null){
      if (fullEditor == null){
	Session session = new Session(item, attribute, className);
	fullEditor = session.getFrame();
	fullEditor.addComponentListener(new ComponentAdapter(){
       @Override
       public void componentHidden(ComponentEvent e){
         if (fullEditor != null) {
           fullEditor.removeComponentListener(this);
           fullEditor = null;
         }
       }
     });
      }
      else{
	if (fullEditor instanceof Frame){
	  Frame frame = (Frame)fullEditor;
	  // This throws a NoSuchMethodError in jdk1.1.x, possibly
	  // leaving an iconified TextEditor still iconified
	  try {
	    if (frame.getState() == Frame.ICONIFIED)
	      frame.setState(Frame.NORMAL);
	  } catch (NoSuchMethodError nsme) {
	    java.awt.Dialog hack =
	      new com.gensym.dlg.WarningDialog(frame, i18n.getString("editorWarningTitle"), true, i18n.getString("attributeAlreadyEdited"), null);
	    hack.setVisible(true);
	    hack.dispose();
	  }
	}
	fullEditor.toFront();
	fullEditor.requestFocus();
      }
    }
    else{
      try{
	connection.getDialogManager().editItem(this, subItem, userMode, locale);
      }
      catch (Exception e){
	Trace.exception(e);
      }
    }
  }

}





