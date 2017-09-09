package com.gensym.nols.main;

import java.awt.*;
import java.io.*;
import java.net.URL;
import javax.swing.*;

public class Logo extends JWindow {

	public Logo() {
		super();
		setLocation(200,200); //default
		URL url = this.getClass().getResource("firstWindow.gif");
		ImageIcon logoImage = new ImageIcon(url);
		JLabel logoLabel = new JLabel(logoImage);
		getContentPane().add(logoLabel);
	}

	public void showLogo(int x, int y) {  
		pack();
		setLocation(x,y);
		setVisible(true);
	}

	// show at default location
	public void showLogo() {
		pack();
		setVisible(true);
	}

	public void hideLogo() {
		this.dispose();
	}
}
