package com.gensym.uiutil;

import java.awt.*;
import java.awt.event.*;

public class IntTextField extends TextField implements KeyListener, MouseListener{

	public IntTextField() {
		super("",3);
		addKeyListener(this);
	}

	public IntTextField(int i) {
		super(i);
		addKeyListener(this);
	}

	public IntTextField(int i, int value) {
		super(i);
		setValue(value);
		addKeyListener(this);
	}

	public void setValue(int i){
		setText("" + i);
	}

	public int getValue(){
		int value = (Integer.valueOf(getText())).intValue();
		if (value > 255)
			return(255);
		return value;
	}

	@Override
	public void keyPressed(KeyEvent e){
		int i = e.getKeyCode();
		if (((i < 58) && (i >47)) || (i == 127) || (i == 8)){
			setEditable(true);
		}
		else {
			setEditable(false);
		}
	}

	@Override
	public void keyReleased(KeyEvent e){
		if (isEditable()) {
			int i = e.getKeyCode();
			if ((i < 58) && (i >47)){
				int value = (Integer.valueOf(getText())).intValue();
				if (value > 255)
					setText("255");
			}
		}
		else
			setEditable(true);
	}

	@Override
	public void keyTyped(KeyEvent e) {
	}

  @Override
  public void mouseClicked(MouseEvent e) {
  }

  @Override
  public void mousePressed(MouseEvent e) {
	}
  @Override
  public void mouseEntered(MouseEvent e) {
	}
  @Override
  public void mouseExited(MouseEvent e) {
	}
  @Override
  public void mouseReleased(MouseEvent e) {
	}
}
