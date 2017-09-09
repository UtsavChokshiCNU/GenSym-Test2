package com.gensym.nols.deploy;

import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.net.URL;

import java.util.*;

import javax.swing.text.*;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.border.*;

public class NolFileDialog extends Object {
	private static Frame frame = new Frame();
	private FileDialog fileDialog;
	private String file;
	private String directory;
	private int flag;

	public NolFileDialog(String fileType) {
		super();
		fileDialog = new FileDialog(frame);
		fileDialog.setMode(FileDialog.LOAD);
		fileDialog.setFile(fileType);
		fileDialog.setLocation(200,200);
		fileDialog.setModal(false);
		fileDialog.setVisible(true);
		fileDialog.toFront();

		file = fileDialog.getFile();
		if (file == null){
			flag = -1;
		}else{
			flag = 1;
			directory = fileDialog.getDirectory();
		}
	}

	public int getFlag(){
		return flag;
	}

	public String getFile(){
		if(flag == 1){
			return file;
		}else{
			return "";
		}
	}
	public String getDirectory(){
		if(flag == 1){
			return directory;
		}else{
			return "";
		}
	}
	public String getPath(){
		if(flag == 1){
			return directory+file;
		}else{
			return "";
		}
	}
}

