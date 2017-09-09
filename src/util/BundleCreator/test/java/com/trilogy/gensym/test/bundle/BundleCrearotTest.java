package com.trilogy.gensym.test.bundle;

import java.io.File;
import java.io.FileOutputStream;
import java.io.OutputStream;
import java.lang.reflect.Field;
import java.util.Properties;

import com.trilogy.gensym.bundle.BundleCreator;
import com.trilogy.gensym.bundle.OSStorage;
import com.trilogy.gensym.bundle.file.FilesWorker;
import com.trilogy.gensym.constants.BundleStringConstants;
import com.trilogy.gensym.constants.FilenamesStringConstants;
import com.trilogy.gensym.propertiesloader.PropertiesLoader;
import com.trilogy.gensym.xml.XMLParser;
import com.trilogy.gensym.xml.elements.FamilyType;
import com.trilogy.gensym.xml.elements.G2OKComponent;

import junit.framework.TestCase;

public class BundleCrearotTest extends TestCase{
	
	private final static String EXAMPLE_FILE_NAME 		= "test\\res\\Bundle.xml";
	private final static String SHORT_EXAMPLE_FILE_NAME = "test\\res\\ShortBundle.xml";
	private final static String TEMP_FILE_NAME 			= "File.tmp";

	public final void testGenerateBundle() throws Exception {
		BundleCreator bc = new BundleCreator();
		Properties paths = PropertiesLoader.loadPropertyFile(FilenamesStringConstants.PART_PATHS_FILE);
		FamilyType xmlComtent = new XMLParser(EXAMPLE_FILE_NAME).parseXML();
		String printName = xmlComtent.getPrintName();
		String family = ((G2OKComponent)xmlComtent.getG2Components().get(0)).getFamilyName();
		String outFolderPath = paths.getProperty(BundleStringConstants.DSTBOX) + File.separator + 
			getPrivateField(bc, "BUNDLES") + File.separator + printName;
		File outFolder = new File(outFolderPath); 
		if (outFolder.exists()){
			FilesWorker.deleteFolder(outFolder);
		}
		String outFileZip = outFolderPath + File.separator + family + File.separator + getPrivateField(bc, "TAR") + 
				File.separator + OSStorage.getInstance().getNameTag() + getPrivateField(bc, "DOT_ZIP");
		bc.generateBundle(EXAMPLE_FILE_NAME);
		File outFolderZ = new File(outFileZip);
		assertTrue(outFolderZ.exists());
		assertTrue(outFolderZ.length() != 0);
		FilesWorker.deleteFolder(outFolder);
	}
	
	public final void testGenerateBundleLoggesError() throws Exception {
		BundleCreator bc = new BundleCreator();
		Properties paths = PropertiesLoader.loadPropertyFile(FilenamesStringConstants.PART_PATHS_FILE);
		FamilyType xmlComtent = new XMLParser(SHORT_EXAMPLE_FILE_NAME).parseXML();
		String printName = xmlComtent.getPrintName();
		String family = ((G2OKComponent)xmlComtent.getG2Components().get(0)).getFamilyName();
		String outFolderPath = paths.getProperty(BundleStringConstants.DSTBOX) + File.separator + 
			getPrivateField(bc, "BUNDLES") + File.separator + printName;
		File outFolder = new File(outFolderPath); 
		if (outFolder.exists()){
			FilesWorker.deleteFolder(outFolder);
		}
		String outFileZip = outFolderPath + File.separator + family + File.separator + getPrivateField(bc, "TAR") + 
				File.separator + OSStorage.getInstance().getNameTag() + getPrivateField(bc, "DOT_ZIP");
		new File(outFolderPath + File.separator + family + File.separator + getPrivateField(bc, "TREE")).mkdirs();
		File tempFile = new File(outFolderPath + File.separator + family + File.separator + getPrivateField(bc, "TREE") + File.separator + TEMP_FILE_NAME);
		tempFile.createNewFile();
		OutputStream out = new FileOutputStream(tempFile.getAbsoluteFile());
		out.write(0);
		bc.generateBundle(SHORT_EXAMPLE_FILE_NAME);
		File outFolderZ = new File(outFileZip);
		assertTrue(outFolderZ.exists());
		assertTrue(new File(outFolderPath + File.separator + family + File.separator + getPrivateField(bc, "TREE")).exists());
		out.close();
		FilesWorker.deleteFolder(outFolder);
	}
	
	public final void testGenerateBundleException() throws Exception {
		BundleCreator bc = new BundleCreator();
		Properties paths = PropertiesLoader.loadPropertyFile(FilenamesStringConstants.PART_PATHS_FILE);
		FamilyType xmlComtent = new XMLParser(EXAMPLE_FILE_NAME).parseXML();
		String printName = xmlComtent.getPrintName();
		String family = ((G2OKComponent)xmlComtent.getG2Components().get(0)).getFamilyName();
		String outFolderPath = paths.getProperty(BundleStringConstants.DSTBOX) + File.separator + 
			getPrivateField(bc, "BUNDLES") + File.separator + printName;
		File outFolder = new File(outFolderPath); 
		if (outFolder.exists()){
			FilesWorker.deleteFolder(outFolder);
		}
		new File(outFolderPath + File.separator + family + File.separator + getPrivateField(bc, "TREE") + File.separator + 
				OSStorage.getInstance().getNameTag() + getPrivateField(bc, "DASH") + printName).mkdirs();
		try {
			bc.generateBundle(EXAMPLE_FILE_NAME);
			fail();
		} catch (IllegalArgumentException e) {}
		FilesWorker.deleteFolder(outFolder);
	}
	
	public final void testMain() throws Exception {
		BundleCreator bc = new BundleCreator();
		Properties paths = PropertiesLoader.loadPropertyFile(FilenamesStringConstants.PART_PATHS_FILE);
		FamilyType xmlComtent = new XMLParser(SHORT_EXAMPLE_FILE_NAME).parseXML();
		String printName = xmlComtent.getPrintName();
		BundleCreator.main(new String [] {SHORT_EXAMPLE_FILE_NAME});
		String outFolderPath = paths.getProperty(BundleStringConstants.DSTBOX) + File.separator + 
		getPrivateField(bc, "BUNDLES") + File.separator + printName;
		File outFolder = new File(outFolderPath); 
		FilesWorker.deleteFolder(outFolder);
	}
	
	public final void testMainLogsException() throws Exception {
		BundleCreator.main(new String [] {});
	}
	
	public static Object getPrivateField(Object obj, String fieldName) throws Exception
    {
        if (obj == null || fieldName == null)
            throw new IllegalArgumentException("Cannot access null object/field");

        final Field field = obj.getClass().getDeclaredField(fieldName);
        field.setAccessible(true);
        return field.get(obj);
    }
}
