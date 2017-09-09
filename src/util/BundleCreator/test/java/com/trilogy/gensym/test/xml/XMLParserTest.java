package com.trilogy.gensym.test.xml;

import java.lang.reflect.Field;
import java.util.List;

import com.trilogy.gensym.constants.FilenamesStringConstants;
import com.trilogy.gensym.xml.XMLParser;
import com.trilogy.gensym.xml.elements.Bundle;
import com.trilogy.gensym.xml.elements.Component;
import com.trilogy.gensym.xml.elements.ComponentPart;
import com.trilogy.gensym.xml.elements.EnvironmentVariable;
import com.trilogy.gensym.xml.elements.FamilyType;
import com.trilogy.gensym.xml.elements.G2OKComponent;
import com.trilogy.gensym.xml.elements.Shortcut;
import com.trilogy.gensym.xml.elements.Version;

import junit.framework.TestCase;

public class XMLParserTest extends TestCase{
	
	private final static String EXAMPLE_FILE_NAME 	= "test\\res\\Example.xml";
	private final static String EMPTY_FILE_NAME 	= "test\\res\\Empty.xml";
	private final static String WRONG_FILE_NAME 	= "WrongFileName.xml";
	
	FamilyType ft;
	
	public final void testParseXML() throws Exception {
		XMLParser parser = new XMLParser(EXAMPLE_FILE_NAME);
		ft = parser.parseXML();
		g2AttributesTest();
		g2OkComponentsTest();
		compartiblePreviousVersionTest();
		previousVersionTest();
		bundlesTest();
	}
	
	public final void testParseEmptyXML() throws Exception {
		XMLParser parser = new XMLParser(EMPTY_FILE_NAME);
		parser.parseXML();
	}
	
	public final void testCreateXMLParserException() throws Exception {
		try{
			new XMLParser(WRONG_FILE_NAME);
			fail();
		} catch (IllegalArgumentException e) {}
	}
	
	private final void g2AttributesTest() throws Exception {
		assertTrue(ft.getIndex() == 111);
		assertTrue(ft.getFileSyntaxVersion() == 222);
		assertEquals(ft.getPrintName(), "PrintNameContent");
		assertEquals(ft.getDirectory(), "DirectoryContent");
		assertEquals(ft.getGuid(), "GuidContent");
		assertEquals(ft.getSplashScreen(), "SplashScreenContent");
		assertEquals(ft.getLicenseText(), "LicenseTextContent");
		assertEquals(ft.getPlatforms(), "PlatformsContent");
	}
	
	private final void g2OkComponentsTest() throws Exception {
		List g2Components = ft.getG2Components();
		G2OKComponent g2OkComponents = (G2OKComponent)g2Components.get(0);
		assertEquals(g2OkComponents.getBundleName(), "BundleNameContentG2Component1");
		assertEquals(g2OkComponents.getFamilyName(), "FamilyNameContentG2Component1");
		assertEquals(g2OkComponents.getPrintName(), "PrintNameContentG2Component1");
		List options = g2OkComponents.getOptions();
		assertEquals(options.get(0), "Option1G2Component1");
		assertEquals(options.get(1), "Option2G2Component1");
		assertEquals(options.get(2), "Option3G2Component1");
		List clientsList = g2OkComponents.getClientList();
		assertEquals((Double)clientsList.get(0), new Double(331.1));
		assertEquals((Double)clientsList.get(1), new Double(332.1));
		assertEquals((Double)clientsList.get(2), new Double(333.1));
		g2OkComponents = (G2OKComponent)g2Components.get(1);
		assertEquals(g2OkComponents.getBundleName(), "BundleNameContentG2Component2");
		assertEquals(g2OkComponents.getFamilyName(), "FamilyNameContentG2Component2");
		assertEquals(g2OkComponents.getPrintName(), "PrintNameContentG2Component2");
		options = g2OkComponents.getOptions();
		assertEquals(options.get(0), "Option1G2Component2");
		assertEquals(options.get(1), "Option2G2Component2");
		assertEquals(options.get(2), "Option3G2Component2");
		clientsList = g2OkComponents.getClientList();
		assertEquals((Double)clientsList.get(0), new Double(331.2));
		assertEquals((Double)clientsList.get(1), new Double(332.2));
		assertEquals((Double)clientsList.get(2), new Double(333.2));
	}
	
	private final void compartiblePreviousVersionTest() throws Exception {
		List versions = ft.getCompatiblePreviousVer();
		Version version = (Version)versions.get(0);
		assertEquals(version.getVersionid(), "versionid1_1");
		assertEquals(version.getVersionguid(), "versionguid1_1");
		version = (Version)versions.get(1);
		assertEquals(version.getVersionid(), "versionid2_1");
		assertEquals(version.getVersionguid(), "versionguid2_1");
		version = (Version)versions.get(2);
		assertEquals(version.getVersionid(), "versionid3_1");
		assertEquals(version.getVersionguid(), "versionguid3_1");
	}
	
	private final void previousVersionTest() throws Exception {
		List versions = ft.getPreviousVer();
		Version version = (Version)versions.get(0);
		assertEquals(version.getVersionid(), "versionid1_2");
		assertEquals(version.getVersionguid(), "versionguid1_2");
		version = (Version)versions.get(1);
		assertEquals(version.getVersionid(), "versionid2_2");
		assertEquals(version.getVersionguid(), "versionguid2_2");
		version = (Version)versions.get(2);
		assertEquals(version.getVersionid(), "versionid3_2");
		assertEquals(version.getVersionguid(), "versionguid3_2");
	}
	
	private final void bundlesTest() throws Exception {
		List bundles = ft.getBundles();
		Bundle bundle = (Bundle)bundles.get(0);
		assertEquals(bundle.getVersion(), "VersionContent_1");
		assertEquals(bundle.getDirectory(), "DirectoryContent_1");
		assertEquals(bundle.getBundlename(), "BundlenameContent_1");
		assertEquals(bundle.getPrintName(), "PrintNameeContent_1");
		
		List components = bundle.getComponents();
		Component component = (Component)components.get(0);
		assertEquals(component.getComponentname(), "ComponentnameContent_1");
		assertEquals(component.getOptional(), "OptionalContent_1");
		assertTrue(component.getRadioButtonGI() == (float)444.1);
		assertEquals(component.getTypical(), "TypicalContent_1");
		assertEquals(component.getWatermark(), "WatermarkContent_1");
		assertEquals(component.getPrintName(), "PrintnameComponentContent_1");
		List platforms = component.getPlatforms();
		assertEquals(platforms.get(0), "PlatformContent_1_1");
		assertEquals(platforms.get(1), "PlatformContent_2_1");
		assertEquals(platforms.get(2), "PlatformContent_3_1");
		
		List componentparts = component.getComponentparts();
		ComponentPart componentPart = (ComponentPart)componentparts.get(0);
		assertEquals(componentPart.getVersion(), "VersionContent_1");
		assertEquals(componentPart.getRegister(), "RegisterContent_1");
		assertEquals(componentPart.getMakeNROnly(), "MNROContent_1");
		assertEquals(componentPart.getComponentpartname(), "NameContent_1");
		assertEquals(componentPart.getPrintName(), "PrintnameContent_1");
		assertEquals(componentPart.getSource(), "SourceContent_1");
		assertEquals(componentPart.getSourceSubdirectory(), "SourceSubDirectoryContent_1");
		assertEquals(componentPart.getDestDir(), "DestinationDirectoryContent_1");
		assertEquals(componentPart.getDestFilename(), "DestinationFilenameContent_1");
		assertEquals(componentPart.getSourceSType(), "SourceShipTypeContent_1");
		assertEquals(componentPart.getIndep(), "IndepContent_1");
		assertEquals(componentPart.getPostinstallCode(), "PostinstallCodeContent_1");
		platforms = componentPart.getPlatforms();
		assertEquals(platforms.get(0), "PlatformContentComponent1_1_1");
		assertEquals(platforms.get(1), "PlatformContentComponent1_2_1");
		assertEquals(platforms.get(2), "PlatformContentComponent1_3_1");
		platforms = componentPart.getNonPlatforms();
		assertEquals(platforms.get(0), "NonPlatformContentComponent1_1_1");
		assertEquals(platforms.get(1), "NonPlatformContentComponent1_2_1");
		assertEquals(platforms.get(2), "NonPlatformContentComponent1_3_1");
		
		
		List srcFileNales = componentPart.getSourceFilename();
		assertEquals(srcFileNales.get(0), "SrcfilenameContent1_1");
		assertEquals(srcFileNales.get(1), "SrcfilenameContent2_1");
		assertEquals(srcFileNales.get(2), "SrcfilenameContent3_1");
		List removeFromSrc = componentPart.getRemoveFromS();
		assertEquals(removeFromSrc.get(0), "NameOfTheFile1_1");
		assertEquals(removeFromSrc.get(1), "NameOfTheFile2_1");
		assertEquals(removeFromSrc.get(2), "NameOfTheFile3_1");
		List regEntires = componentPart.getRegEntries();
		assertEquals(regEntires.get(0), "RegistryEntryNameContent1_1");
		assertEquals(regEntires.get(1), "RegistryEntryNameContent2_1");
		assertEquals(regEntires.get(2), "RegistryEntryNameContent3_1");
		List envVariables = componentPart.getEnvVariables();
		EnvironmentVariable envVariable = (EnvironmentVariable)envVariables.get(0);
		List envVarName = envVariable.getEnvVarName();
		assertEquals(envVarName.get(0), "EnvvarnameContent1_1_1");
		assertEquals(envVarName.get(1), "EnvvarnameContent2_1_1");
		assertEquals(envVarName.get(2), "EnvvarnameContent3_1_1");
		List name = envVariable.getName();
		assertEquals(name.get(0), "NameContent1_1_1");
		assertEquals(name.get(1), "NameContent2_1_1");
		assertEquals(name.get(2), "NameContent3_1_1");
		envVariable = (EnvironmentVariable)envVariables.get(1);
		envVarName = envVariable.getEnvVarName();
		assertEquals(envVarName.get(0), "EnvvarnameContent1_2_1");
		assertEquals(envVarName.get(1), "EnvvarnameContent2_2_1");
		assertEquals(envVarName.get(2), "EnvvarnameContent3_2_1");
		name = envVariable.getName();
		assertEquals(name.get(0), "NameContent1_2_1");
		assertEquals(name.get(1), "NameContent2_2_1");
		assertEquals(name.get(2), "NameContent3_2_1");
		assertEquals(envVariable.getValue(), "ValueContent_1");
		assertEquals(envVariable.getAppendOrMerge(), "AppendormergeContent_1");
		
		List shortCuts = componentPart.getShortcuts();
		Shortcut shortcut = (Shortcut)shortCuts.get(0);
		assertEquals(shortcut.getShortcutName(), "shortcutnamecontent1_1_1");
		assertEquals(shortcut.getFolderName(), "foldernamecontent1_1_1");
		assertEquals(shortcut.getSubfolderName(), "subfoldernamecontent1_1_1");
		assertEquals(shortcut.getSubsubfolderName(), "subsubfoldernamecontent1_1_1");
		assertEquals(shortcut.getAppDisplayName(), "applicationdisplaynamecontent1_1_1");
		assertEquals(shortcut.getAppDirectory(), "applicationdirectorycontent1_1_1");
		assertEquals(shortcut.getTargetName(), "targetnamecontent1_1_1");
		assertEquals(shortcut.getParameters(), "parameterscontent1_1_1");
		assertEquals(shortcut.getIconFile(), "iconfilecontent1_1_1");
		assertTrue(shortcut.getIconIndex() == (float)555.11);
		assertEquals(shortcut.getRunStyle(), "runstylecontent1_1_1");
		shortcut = (Shortcut)shortCuts.get(1);
		assertEquals(shortcut.getShortcutName(), "shortcutnamecontent2_1_2");
		assertEquals(shortcut.getFolderName(), "foldernamecontent2_1_2");
		assertEquals(shortcut.getSubfolderName(), "subfoldernamecontent2_1_2");
		assertEquals(shortcut.getSubsubfolderName(), "subsubfoldernamecontent2_1_2");
		assertEquals(shortcut.getAppDisplayName(), "applicationdisplaynamecontent2_1_2");
		assertEquals(shortcut.getAppDirectory(), "applicationdirectorycontent2_1_2");
		assertEquals(shortcut.getTargetName(), "targetnamecontent2_1_2");
		assertEquals(shortcut.getParameters(), "parameterscontent2_1_2");
		assertEquals(shortcut.getIconFile(), "iconfilecontent2_1_2");
		assertTrue(shortcut.getIconIndex() == (float)555.12);
		assertEquals(shortcut.getRunStyle(), "runstylecontent2_1_2");
		
		componentPart = (ComponentPart)componentparts.get(1);
		assertEquals(componentPart.getVersion(), "VersionContent_2");
		assertEquals(componentPart.getRegister(), "RegisterContent_2");
		assertEquals(componentPart.getMakeNROnly(), "MNROContent_2");
		assertEquals(componentPart.getComponentpartname(), "NameContent_2");
		assertEquals(componentPart.getPrintName(), "PrintnameContent_2");
		assertEquals(componentPart.getSource(), "SourceContent_2");
		assertEquals(componentPart.getSourceSubdirectory(), "SourceSubDirectoryContent_2");
		assertEquals(componentPart.getDestDir(), "DestinationDirectoryContent_2");
		assertEquals(componentPart.getDestFilename(), "DestinationFilenameContent_2");
		assertEquals(componentPart.getSourceSType(), "SourceShipTypeContent_2");
		assertEquals(componentPart.getIndep(), "IndepContent_2");
		assertEquals(componentPart.getPostinstallCode(), "PostinstallCodeContent_2");
		srcFileNales = componentPart.getSourceFilename();
		assertEquals(srcFileNales.get(0), "SrcfilenameContent_2");
		removeFromSrc = componentPart.getRemoveFromS();
		assertEquals(removeFromSrc.get(0), "NameOfTheFile_2");
		regEntires = componentPart.getRegEntries();
		assertEquals(regEntires.get(0), "RegistryEntryNameContent_2");
		platforms = componentPart.getPlatforms();
		assertEquals(platforms.get(0), "PlatformContentPart_1_2");
		envVariables = componentPart.getEnvVariables();
		envVariable = (EnvironmentVariable)envVariables.get(0);
		envVarName = envVariable.getEnvVarName();
		assertEquals(envVarName.get(0), "EnvvarnameContent1_2");
		name = envVariable.getName();
		assertEquals(name.get(0), "NameContent1_2");
		assertEquals(envVariable.getValue(), "ValueContent_2");
		assertEquals(envVariable.getAppendOrMerge(), "AppendormergeContent_2");
		shortCuts = componentPart.getShortcuts();
		shortcut = (Shortcut)shortCuts.get(0);
		assertEquals(shortcut.getShortcutName(), "shortcutnamecontent_2");
		assertEquals(shortcut.getFolderName(), "foldernamecontent_2");
		assertEquals(shortcut.getSubfolderName(), "subfoldernamecontent_2");
		assertEquals(shortcut.getSubsubfolderName(), "subsubfoldernamecontent_2");
		assertEquals(shortcut.getAppDisplayName(), "applicationdisplaynamecontent_2");
		assertEquals(shortcut.getAppDirectory(), "applicationdirectorycontent_2");
		assertEquals(shortcut.getTargetName(), "targetnamecontent_2");
		assertEquals(shortcut.getParameters(), "parameterscontent_2");
		assertEquals(shortcut.getIconFile(), "iconfilecontent_2");
		assertTrue(shortcut.getIconIndex() == (float)555.2);
		assertEquals(shortcut.getRunStyle(), "runstylecontent_2");
		
		component = (Component)components.get(1);
		assertEquals(component.getComponentname(), "ComponentnameContent_3");
		assertEquals(component.getOptional(), "OptionalContent_3");
		assertTrue(component.getRadioButtonGI() == (float)444.3);
		assertEquals(component.getTypical(), "TypicalContent_3");
		assertEquals(component.getWatermark(), "WatermarkContent_3");
		componentparts = component.getComponentparts();
		componentPart = (ComponentPart)componentparts.get(0);
		assertEquals(componentPart.getVersion(), "VersionContent_3");
		assertEquals(componentPart.getRegister(), "RegisterContent_3");
		assertEquals(componentPart.getMakeNROnly(), "MNROContent_3");
		assertEquals(componentPart.getComponentpartname(), "NameContent_3");
		assertEquals(componentPart.getPrintName(), "PrintnameContent_3");
		assertEquals(componentPart.getSource(), "SourceContent_3");
		assertEquals(componentPart.getSourceSubdirectory(), "SourceSubDirectoryContent_3");
		platforms = componentPart.getPlatforms();
		assertEquals(platforms.get(0), "PlatformContentPart_1_3");
		assertEquals(componentPart.getDestDir(), "DestinationDirectoryContent_3");
		assertEquals(componentPart.getDestFilename(), "DestinationFilenameContent_3");
		assertEquals(componentPart.getSourceSType(), "SourceShipTypeContent_3");
		assertEquals(componentPart.getIndep(), "IndepContent_3");
		assertEquals(componentPart.getPostinstallCode(), "PostinstallCodeContent_3");
		srcFileNales = componentPart.getSourceFilename();
		assertEquals(srcFileNales.get(0), "SrcfilenameContent_3");
		removeFromSrc = componentPart.getRemoveFromS();
		assertEquals(removeFromSrc.get(0), "NameOfTheFile_3");
		regEntires = componentPart.getRegEntries();
		assertEquals(regEntires.get(0), "RegistryEntryNameContent_3");
		envVariables = componentPart.getEnvVariables();
		envVariable = (EnvironmentVariable)envVariables.get(0);
		envVarName = envVariable.getEnvVarName();
		assertEquals(envVarName.get(0), "EnvvarnameContent1_3");
		name = envVariable.getName();
		assertEquals(name.get(0), "NameContent1_3");
		assertEquals(envVariable.getValue(), "ValueContent_3");
		assertEquals(envVariable.getAppendOrMerge(), "AppendormergeContent_3");
		shortCuts = componentPart.getShortcuts();
		shortcut = (Shortcut)shortCuts.get(0);
		assertEquals(shortcut.getShortcutName(), "shortcutnamecontent_3");
		assertEquals(shortcut.getFolderName(), "foldernamecontent_3");
		assertEquals(shortcut.getSubfolderName(), "subfoldernamecontent_3");
		assertEquals(shortcut.getSubsubfolderName(), "subsubfoldernamecontent_3");
		assertEquals(shortcut.getAppDisplayName(), "applicationdisplaynamecontent_3");
		assertEquals(shortcut.getAppDirectory(), "applicationdirectorycontent_3");
		assertEquals(shortcut.getTargetName(), "targetnamecontent_3");
		assertEquals(shortcut.getParameters(), "parameterscontent_3");
		assertEquals(shortcut.getIconFile(), "iconfilecontent_3");
		assertTrue(shortcut.getIconIndex() == (float)555.3);
		assertEquals(shortcut.getRunStyle(), "runstylecontent_3");
		
		
		bundle = (Bundle)bundles.get(1);
		assertEquals(bundle.getVersion(), "VersionContent_4");
		assertEquals(bundle.getDirectory(), "DirectoryContent_4");
		assertEquals(bundle.getBundlename(), "BundlenameContent_4");
		components = bundle.getComponents();
		component = (Component)components.get(0);
		assertEquals(component.getComponentname(), "ComponentnameContent_4");
		assertEquals(component.getOptional(), "OptionalContent_4");
		assertTrue(component.getRadioButtonGI() == (float)444.4);
		assertEquals(component.getTypical(), "TypicalContent_4");
		assertEquals(component.getWatermark(), "WatermarkContent_4");
		componentparts = component.getComponentparts();
		componentPart = (ComponentPart)componentparts.get(0);
		assertEquals(componentPart.getVersion(), "VersionContent_4");
		assertEquals(componentPart.getRegister(), "RegisterContent_4");
		assertEquals(componentPart.getMakeNROnly(), "MNROContent_4");
		assertEquals(componentPart.getComponentpartname(), "NameContent_4");
		assertEquals(componentPart.getPrintName(), "PrintnameContent_4");
		assertEquals(componentPart.getSource(), "SourceContent_4");
		assertEquals(componentPart.getSourceSubdirectory(), "SourceSubDirectoryContent_4");
		platforms = componentPart.getPlatforms();
		assertEquals(platforms.get(0), "PlatformContentPart_1_4");
		assertEquals(componentPart.getDestDir(), "DestinationDirectoryContent_4");
		assertEquals(componentPart.getDestFilename(), "DestinationFilenameContent_4");
		assertEquals(componentPart.getSourceSType(), "SourceShipTypeContent_4");
		assertEquals(componentPart.getIndep(), "IndepContent_4");
		assertEquals(componentPart.getPostinstallCode(), "PostinstallCodeContent_4");
		srcFileNales = componentPart.getSourceFilename();
		assertEquals(srcFileNales.get(0), "SrcfilenameContent_4");
		removeFromSrc = componentPart.getRemoveFromS();
		assertEquals(removeFromSrc.get(0), "NameOfTheFile_4");
		regEntires = componentPart.getRegEntries();
		assertEquals(regEntires.get(0), "RegistryEntryNameContent_4");
		envVariables = componentPart.getEnvVariables();
		envVariable = (EnvironmentVariable)envVariables.get(0);
		envVarName = envVariable.getEnvVarName();
		assertEquals(envVarName.get(0), "EnvvarnameContent1_4");
		name = envVariable.getName();
		assertEquals(name.get(0), "NameContent1_4");
		assertEquals(envVariable.getValue(), "ValueContent_4");
		assertEquals(envVariable.getAppendOrMerge(), "AppendormergeContent_4");
		shortCuts = componentPart.getShortcuts();
		shortcut = (Shortcut)shortCuts.get(0);
		assertEquals(shortcut.getShortcutName(), "shortcutnamecontent_4");
		assertEquals(shortcut.getFolderName(), "foldernamecontent_4");
		assertEquals(shortcut.getSubfolderName(), "subfoldernamecontent_4");
		assertEquals(shortcut.getSubsubfolderName(), "subsubfoldernamecontent_4");
		assertEquals(shortcut.getAppDisplayName(), "applicationdisplaynamecontent_4");
		assertEquals(shortcut.getAppDirectory(), "applicationdirectorycontent_4");
		assertEquals(shortcut.getTargetName(), "targetnamecontent_4");
		assertEquals(shortcut.getParameters(), "parameterscontent_4");
		assertEquals(shortcut.getIconFile(), "iconfilecontent_4");
		assertTrue(shortcut.getIconIndex() == (float)555.4);
		assertEquals(shortcut.getRunStyle(), "runstylecontent_4");
	}
}