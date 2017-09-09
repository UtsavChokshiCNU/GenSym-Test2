/*
 * @(#)g2TextField.java	97/10/20
 * 
 */
package java.awt;
import java.awt.peer.TextFieldPeer;
import java.awt.event.*;
import java.awt.*;
import java.util.*;
import java.io.ObjectOutputStream;
import java.io.ObjectInputStream;
import java.io.IOException;


public class g2TextField extends TextField {

	private Vector focusListener;
	private Vector keyListener;
	private Vector mouseListener;
	private Vector mouseMotionListener;

    public g2TextField() {
		this("", 0);
    }

    /**
     * Constructs a new text field initialized with the specified text.
     * @param      text       the text to be displayed.
     * @since      JDK1.0
     */
    public g2TextField(String text) {
		this(text, text.length());
    }

    /**
     * Constructs a new empty TextField with the specified number of columns.
     * @param columns the number of columns
     */ 
    public g2TextField(int columns) {
		this("", columns);
    }

    /**
     * Constructs a new text field initialized with the specified text
     * to be displayed, and wide enough to hold the specified 
     * number of characters.
     * @param      text       the text to be displayed.
     * @param      columns    the number of characters.
     * @since      JDK1.0
     */
    public g2TextField(String text, int columns) {
		super(text,columns);
		focusListener = new Vector();
		keyListener = new Vector();
		mouseListener = new Vector();
		mouseMotionListener	= new Vector();
    }

    /**
     * Adds the specified focus listener to receive focus events from
     * this component.
     */     
    public synchronized void addFocusListener(FocusListener l) {
		focusListener.addElement(l);
		enableEvents(AWTEvent.FOCUS_EVENT_MASK);
    }
    /**
     * Removes the specified focus listener so that it no longer
     * receives focus events from this component.
     */ 
    public synchronized void removeFocusListener(FocusListener l) {
        focusListener.removeElement(l);
    }   
    /**
     * Adds the specified key listener to receive key events from
     * this component.
	 */
    public synchronized void addKeyListener(KeyListener l) {
        keyListener.addElement(l);
		enableEvents(AWTEvent.KEY_EVENT_MASK);
	}
    /**
     * Removes the specified key listener so that it no longer
     * receives focus events from this component.
     */ 
    public synchronized void removeKeyListener(KeyListener l) {
        keyListener.removeElement(l);
	}

    /**
     * Adds the specified mouse listener to receive key events from
     * this component.
	 */
    public synchronized void addMouseListener(MouseListener l) {
        mouseListener.addElement(l);
		enableEvents(AWTEvent.MOUSE_EVENT_MASK);
	}
    /**
     * Removes the specified mouse listener so that it no longer
     * receives focus events from this component.
     */ 
    public synchronized void removeMouseListener(MouseListener l) {
        mouseListener.removeElement(l);
	}

    void dispatchEventImpl(AWTEvent e) {
        processEvent(e);
	}

	/** 
     * Processes events occurring on this component. By default this
     * method calls the appropriate 
     * <code>process&lt;event&nbsp;type&gt;Event</code>  
     * method for the given class of event.
     * @param     e the event.
     */   
    protected void processEvent(AWTEvent e) {

        if (e instanceof FocusEvent) {  
            processFocusEvent((FocusEvent)e);

        } else if (e instanceof MouseEvent) {
            switch(e.getID()) {
              case MouseEvent.MOUSE_PRESSED:
              case MouseEvent.MOUSE_RELEASED:
              case MouseEvent.MOUSE_CLICKED:
                processMouseEvent((MouseEvent)e);
                break;
              case MouseEvent.MOUSE_MOVED:
              case MouseEvent.MOUSE_DRAGGED:
                processMouseMotionEvent((MouseEvent)e);
                break;
            }

        } else if (e instanceof KeyEvent) {
            processKeyEvent((KeyEvent)e);
        } 
    }
    

    /** 
     * Processes focus events occurring on this component by
     * dispatching them to any registered 
     * <code>FocusListener</code> objects. 
     * <p>
     * This method is not called unless focus events are 
     * enabled for this component. Focus events are enabled 
     * when one of the following occurs:
     * <p><ul>
     * <li>A <code>FocusListener</code> object is registered 
     * via <code>addFocusListener</code>.
     * <li>Focus events are enabled via <code>enableEvents</code>.
     * </ul>
     * @param       e the focus event.
     */       
    protected void processFocusEvent(FocusEvent e) {
		for(int i=0;i<focusListener.size();i++){
		    FocusListener l = (FocusListener)focusListener.elementAt(i);
	         int id = e.getID();
	         switch(id) {
	           case FocusEvent.FOCUS_GAINED:
	             l.focusGained(e);
	             break;
	           case FocusEvent.FOCUS_LOST:
	             l.focusLost(e);
	             break;
	         }
		}
    }

    /** 
     * Processes key events occurring on this component by
     * dispatching them to any registered 
     * <codeKeyListener</code> objects. 
     * <p>
     * This method is not called unless key events are 
     * enabled for this component. Key events are enabled 
     * when one of the following occurs:
     * <p><ul>
     * <li>A <code>KeyListener</code> object is registered 
     * via <code>addKeyListener</code>.
     * <li>Key events are enabled via <code>enableEvents</code>.
     * </ul>
     * @param       e the key event.
     */   
    protected void processKeyEvent(KeyEvent e) {
		 for(int i=0;i<keyListener.size();i++){
		    KeyListener l = (KeyListener)keyListener.elementAt(i);
            int id = e.getID();
            switch(id) {
              case KeyEvent.KEY_TYPED:
                l.keyTyped(e);
                break;
              case KeyEvent.KEY_PRESSED:
                l.keyPressed(e);
                break;
              case KeyEvent.KEY_RELEASED:
                l.keyReleased(e);
                break;
            }
        } 
    }

    /** 
     * Processes mouse events occurring on this component by
     * dispatching them to any registered 
     * <code>MouseListener</code> objects. 
     * <p>
     * This method is not called unless mouse events are 
     * enabled for this component. Mouse events are enabled 
     * when one of the following occurs:
     * <p><ul>
     * <li>A <code>MouseListener</code> object is registered 
     * via <code>addMouseListener</code>.
     * <li>Mouse events are enabled via <code>enableEvents</code>.
     * </ul>
     * @param       e the mouse event.
     */   
    protected void processMouseEvent(MouseEvent e) {
		 for(int i=0;i<mouseListener.size();i++){
		    MouseListener l = (MouseListener)mouseListener.elementAt(i);
            int id = e.getID();
            switch(id) {
              case MouseEvent.MOUSE_PRESSED:
				this.requestFocus();
                l.mousePressed(e);
                break;
              case MouseEvent.MOUSE_RELEASED:
                l.mouseReleased(e);
                break;
              case MouseEvent.MOUSE_CLICKED:
                l.mouseClicked(e);
                break;
              case MouseEvent.MOUSE_EXITED:
                l.mouseExited(e);
                break;
              case MouseEvent.MOUSE_ENTERED:
                l.mouseEntered(e);
                break;
            }
        }            
    }

    /** 
     * Processes mouse motion events occurring on this component by
     * dispatching them to any registered 
     * <code>MouseMotionListener</code> objects. 
     * <p>
     * This method is not called unless mouse motion events are 
     * enabled for this component. Mouse motion events are enabled 
     * when one of the following occurs:
     * <p><ul>
     * <li>A <code>MouseMotionListener</code> object is registered 
     * via <code>addMouseMotionListener</code>.
     * <li>Mouse motion events are enabled via <code>enableEvents</code>.
     * </ul>
     * @param       e the mouse motion event.
     * @since       JDK1.1
     */   
    protected void processMouseMotionEvent(MouseEvent e) {
 		 for(int i=0;i<mouseMotionListener.size();i++){
		   MouseMotionListener l = (MouseMotionListener)mouseMotionListener.elementAt(i);
            int id = e.getID();
            switch(id) {
              case MouseEvent.MOUSE_MOVED:
                l.mouseMoved(e);
                break;
              case MouseEvent.MOUSE_DRAGGED:
                l.mouseDragged(e);
                break;
            }
        }            
    }

}
