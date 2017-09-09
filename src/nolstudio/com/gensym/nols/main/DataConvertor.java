package com.gensym.nols.main;

import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.net.URL;
import java.util.*;
import java.text.*;

import javax.swing.text.*;
import javax.swing.*;
import javax.swing.border.*;
import javax.swing.event.*;
import com.gensym.nols.data.*;
import com.gensym.nols.util.NolCmdLineArgHandler;
/**
 */
public class DataConvertor {
	private Project2 project;
	private String  dataDirectory;
	private SimpleDateFormat dateFormat = new SimpleDateFormat("MM/dd/yy");	
	private SimpleDateFormat timeFormat = new SimpleDateFormat("H:mm:ss");
	public static void main(String[] args) {
		String vers = System.getProperty("java.version");		
		if (vers.compareTo("1.1.7") < 0) {
			System.out.println("!!!WARNING: Swing must be run with a " +
				"1.1.7 or higher version VM!!!");
		}
		if(args.length != 6){
			System.out.println("The input arguments number is not 3! ");
			return;
		}
		DataConvertor nol = new DataConvertor(); 
		NolCmdLineArgHandler cmdline = new NolCmdLineArgHandler(args);
		String inputFileName = cmdline.getOptionValue("-input");
		String outputFileName = cmdline.getOptionValue("-output");
		String formatName = cmdline.getOptionValue("-format");
		nol.convert(inputFileName,formatName,outputFileName );
    }

	public DataConvertor(){
		dataDirectory = System.getProperties().getProperty("user.dir");
		project = new Project2();
	}

	public void convert(String inputFileName, String formatName, String outputFileName){
		Vector dfs = project.getDataSeriesFileFormats();

		System.out.println("dfs.size."+dfs.size());
		System.out.println("formatName="+formatName);

		DataSeriesFileFormat dataFormat = project.getDataSeriesFileFormat(formatName);
	   	if (dataFormat == null){
			System.out.println("!!!WARNING: File format name is not correct.");
			return;
		}
		String objName = "tempData";
		DataSeries ds = new DataSeries();
		ds.setDataSource(project.getRawDataSource());
		try{
			ds.LoadViaFormat(dataDirectory, inputFileName, dataFormat, objName);
			ds.setComment("");
		} catch(Exception evt){
			System.out.println("!!!WARNING: Exception occur during loading process.");
			return;
		}
		ds.saveAscii(dataDirectory,outputFileName,1,dateFormat,timeFormat);
	}

}


