package com.gensym.beaneditor;

import java.awt.*;

public class PreviewArea extends TextArea{
	private int width = 350;
	private int height = 70;

	public PreviewArea() {
		super("",0,0,3);
	}

	@Override
	public Dimension getPreferredSize(){
		return new Dimension(width,height);
	}
}
