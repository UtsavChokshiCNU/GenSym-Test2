package com.gensym.demos.g2studiosample;

import java.awt.Shape;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.Color;
import java.awt.Rectangle;
import java.awt.Toolkit;
import javax.swing.JLabel;
import javax.swing.text.JTextComponent;
import com.gensym.message.Trace;
import com.gensym.editor.text.ParsingStatusUpdatedEvent;
import com.gensym.editor.text.PromptsUpdatedEvent;
import com.gensym.editor.text.PromptsUpdatedListener;
import com.gensym.editor.text.EditContext;
import com.gensym.editor.text.G2SideParser;
import com.gensym.editor.text.StatusManager;
import com.gensym.editor.text.Session;

public class ShellParsingStatusManager extends StatusManager implements PromptsUpdatedListener {
  private String parsingStatusDefault = "none";  
  private JLabel statusLabel, errorLabel;
  private boolean started;
  private Object currentErrorHighlight;
  private ErrorHighlighter errorHighlighter = new ErrorHighlighter();  
  
  ShellParsingStatusManager(JLabel statusLabel, JLabel errorLabel) {
    this.statusLabel = statusLabel;
    this.errorLabel = errorLabel;
    setStatusText(statusLabel);
    setErrorText(errorLabel);
  }

  public void setParsingStatusDefaultValue(String defaultValue) {
    this.parsingStatusDefault=defaultValue;
  }
  
  @Override
  public void updatePrompts(PromptsUpdatedEvent e) {//using this to see when we start the parse
    if (!started) {
      started = true;
      statusLabel.setText("ok");
    }
  }
  
  @Override
  public void changeParsingStatus(ParsingStatusUpdatedEvent e) {
    //POSSIBLE THREAD LOCK PROBLEM HERE!!!!!
    if (e == null) {
      statusLabel.setText(parsingStatusDefault);
      errorLabel.setText("");
      statusLabel.setForeground(Color.black);	
      errorLabel.setForeground(Color.black);
      started = false;
    } else {
      int errorIndex = e.getErrorIndex();
      G2SideParser parser = (G2SideParser)e.getSource();
      JTextComponent textArea = null;	
      if (parser != null)
	textArea = EditContext.getContext().getEditor(parser);
      if (textArea != null) {
	if (errorIndex == -1) {	    
	  if (currentErrorHighlight != null) {
	    textArea.getHighlighter().removeHighlight(currentErrorHighlight);
	    currentErrorHighlight = null;
	  }
	} else {
	  if (currentErrorHighlight == null) {
	    try {
	      currentErrorHighlight = textArea.getHighlighter().addHighlight(errorIndex,errorIndex,
									     errorHighlighter);
	    } catch (javax.swing.text.BadLocationException ble) {
	      Trace.exception(ble);
	    }
	  }
	}
      }
      super.changeParsingStatus(e);
    }
  }
}

class ErrorHighlighter implements javax.swing.text.Highlighter.HighlightPainter {
  private Image bugImage = Toolkit.getDefaultToolkit().getImage(Session.class.getResource("redBug.gif"));
  @Override
  public void paint(Graphics g,
		    int p0,
		    int p1,
		    Shape bounds,
		    JTextComponent c) {
    try {
      Rectangle rect = c.modelToView(p0);
      int size = 3*Math.max(rect.width, rect.height)/4;
      g.drawImage(bugImage, rect.x-size/4, rect.y, size,size, null);
      c.repaint();
    } catch (javax.swing.text.BadLocationException ble) {
      Trace.exception(ble);
    }
  }
}
