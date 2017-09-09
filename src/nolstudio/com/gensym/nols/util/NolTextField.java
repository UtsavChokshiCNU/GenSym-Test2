/*
 *  This class supports the formula entry dialog associated with preprocessors.
 *  It features an legacy, AWT-event handling mechanism.
 *	The undo/redo Undo is static, so actions on the input/output fields
 *  are stored together, enabling undos to be global.
 * 
 */
package com.gensym.nols.util;
import java.awt.event.*;
import java.awt.*;
import java.util.*;

import javax.swing.*;


public class NolTextField extends JTextField {

	private Vector focusListener;
	private Vector keyListener;
	private Vector mouseListener;
	private Vector mouseMotionListener;
	private Dimension viewport;

    public NolTextField() {
		this("", 0);
		viewport = null;
    }

    public NolTextField(String text) {
		this(text, text.length());
		viewport = null;
    }
 
    public NolTextField(int columns) {
		this("", columns);
    }

    public NolTextField(String text, int columns) {
		super(text,columns);
		viewport = null;
		focusListener = new Vector();
		keyListener = new Vector();
		mouseListener = new Vector();
		mouseMotionListener	= new Vector();
    }
    
    @Override
    public synchronized void addFocusListener(FocusListener l) {
		if(focusListener == null) {
			focusListener = new Vector();
		}
		super.addFocusListener(l);
		focusListener.addElement(l);
		enableEvents(AWTEvent.FOCUS_EVENT_MASK);
    }
    /**
     * Removes the specified focus listener so that it no longer
     * receives focus events from this component.
     */ 
    @Override
    public synchronized void removeFocusListener(FocusListener l) {
        focusListener.removeElement(l);
    }   
    /**
     * Adds the specified key listener to receive key events from
     * this component.
	 */
    @Override
    public synchronized void addKeyListener(KeyListener l) {
		if(keyListener == null)
			keyListener = new Vector();
		super.addKeyListener(l);
        keyListener.addElement(l);
		enableEvents(AWTEvent.KEY_EVENT_MASK);
	}
    /**
     * Removes the specified key listener so that it no longer
     * receives focus events from this component.
     */ 
    @Override
    public synchronized void removeKeyListener(KeyListener l) {
        keyListener.removeElement(l);
	}

    /**
     * Adds the specified mouse listener to receive key events from
     * this component.
	 */
    @Override
    public synchronized void addMouseListener(MouseListener l) {
		if(mouseListener == null)
			mouseListener = new Vector();
		super.addMouseListener(l);
        mouseListener.addElement(l);
		enableEvents(AWTEvent.MOUSE_EVENT_MASK);
	}
    /**
     * Removes the specified mouse listener so that it no longer
     * receives focus events from this component.
     */ 
    @Override
    public synchronized void removeMouseListener(MouseListener l) {
        mouseListener.removeElement(l);
	}

//    protected void dispatchEventImpl(AWTEvent e) {
//		processEvent(e);
//	}

	/** 
     * Processes events occurring on this component. By default this
     * method calls the appropriate 
     * <code>process&lt;event&nbsp;type&gt;Event</code>  
     * method for the given class of event.
     * @param     e the event.
     */   
    @Override
    public void processEvent(AWTEvent e) {
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
              default:
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
    @Override
    protected synchronized void processFocusEvent(FocusEvent e) {
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
	           default:
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
    @Override
    protected synchronized void processKeyEvent(KeyEvent e) {
		 for(int i=0;i<keyListener.size();i++){
		    KeyListener l = (KeyListener)keyListener.elementAt(i);
//System.out.println("Sending key event "+e.getID()+" to listener "+i+", class = "+l.getClass().getName());
            int id = e.getID();
            switch(id) {
              case KeyEvent.KEY_TYPED:
                l.keyTyped(e);
                break;
              case KeyEvent.KEY_PRESSED:
				  l.keyPressed(e);
                break;
              case KeyEvent.KEY_RELEASED:
//				  l.keyReleased(e);
				break;
			  default:
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
    @Override
    protected synchronized void processMouseEvent(MouseEvent e) {
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
              default:
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
    @Override
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
              default:
            }
        }            
    }

	public void setPreferredScrollableViewportSize(Dimension d) {
		viewport = d;
	}

	@Override
	public Dimension getPreferredScrollableViewportSize() {
		if(viewport==null) {
			return super.getPreferredScrollableViewportSize();
		}
		else return viewport;
	}


}
