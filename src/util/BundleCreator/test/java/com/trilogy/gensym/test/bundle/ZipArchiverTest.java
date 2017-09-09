package com.trilogy.gensym.test.bundle;

import java.io.File;

import com.trilogy.gensym.bundle.ZipArchiver;

import junit.framework.TestCase;

public class ZipArchiverTest extends TestCase{
	
	private final static String EMPTY_STRING = "";
	private final static String TEMP_FILE_NAME = "File.tmp";
	private final static String TEMP_FOLDER_NAME = "TempFolder";
	
	public final void testCreateZipArchiveException1() throws Exception {
		try{
			new ZipArchiver(new File(EMPTY_STRING), EMPTY_STRING);
			fail();
		} catch (IllegalArgumentException e) {}
	}
	
	public final void testCreateZipArchiveException2() throws Exception {
		File file = null;
		try{
			file = new File(TEMP_FILE_NAME);
			file.createNewFile();
			new ZipArchiver(file, EMPTY_STRING);
			fail();
		} catch (IllegalArgumentException e) {
			file.delete();
		}
	}
	
	public final void testCreateZipArchiveException3() throws Exception {
		File file = null;
		File folder = null;
		try{
			file = new File(TEMP_FILE_NAME);
			folder = new File(TEMP_FOLDER_NAME);
			file.createNewFile();
			folder.mkdir();
			new ZipArchiver(folder, TEMP_FILE_NAME);
			fail();
		} catch (IllegalArgumentException e) {}
		file.delete();
		folder.delete();
	}
}
