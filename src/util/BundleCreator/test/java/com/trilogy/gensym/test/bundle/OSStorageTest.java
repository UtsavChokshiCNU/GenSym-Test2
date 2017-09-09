package com.trilogy.gensym.test.bundle;

import java.util.Properties;

import com.trilogy.gensym.bundle.OSStorage;

import junit.framework.TestCase;

public class OSStorageTest extends TestCase {
	
	private final static String OS_NAMRE = "os.name";
	private String realOS;
	
	public final void testGetInstanceWindows() throws Exception {
		OSStorage osStorage = OSStorage.getInstance();
		assertEquals(osStorage.getName(), "Windows");
		assertEquals(osStorage.getNameTag(), "intelnt");
		assertEquals(osStorage.getNikName(), "nt");
	}
	
	public final void testGenerateBundleLinux() throws Exception {
		Properties sysprops = System.getProperties();
		realOS = sysprops.getProperty(OS_NAMRE);
		sysprops.setProperty(OS_NAMRE, "Red Hat Linux");
		OSStorage osStorage = OSStorage.getInstance();
		assertEquals(osStorage.getName(), "Red Hat Linux");
		assertEquals(osStorage.getNameTag(), "linux");
		assertEquals(osStorage.getNikName(), "linux");
		sysprops.setProperty(OS_NAMRE, realOS);
	}
	
	public final void testGenerateBundleUnix() throws Exception {
		Properties sysprops = System.getProperties();
		realOS = sysprops.getProperty(OS_NAMRE);
		sysprops.setProperty(OS_NAMRE, "Compaq Tru64 UNIX");
		OSStorage osStorage = OSStorage.getInstance();
		assertEquals(osStorage.getName(), "Compaq Tru64 UNIX");
		assertEquals(osStorage.getNameTag(), "alphaosf");
		assertEquals(osStorage.getNikName(), "alphaosf");
		sysprops.setProperty(OS_NAMRE, realOS);
	}
	
	public final void testGenerateBundleIBM() throws Exception {
		Properties sysprops = System.getProperties();
		realOS = sysprops.getProperty(OS_NAMRE);
		sysprops.setProperty(OS_NAMRE, "IBM AIX");
		OSStorage osStorage = OSStorage.getInstance();
		assertEquals(osStorage.getName(), "IBM AIX");
		assertEquals(osStorage.getNameTag(), "rs6000");
		assertEquals(osStorage.getNikName(), "aix");
		sysprops.setProperty(OS_NAMRE, realOS);
	}
	
	public final void testGenerateBundleSolaris() throws Exception {
		Properties sysprops = System.getProperties();
		realOS = sysprops.getProperty(OS_NAMRE);
		sysprops.setProperty(OS_NAMRE, "Sun Solaris");
		OSStorage osStorage = OSStorage.getInstance();
		assertEquals(osStorage.getName(), "Sun Solaris");
		assertEquals(osStorage.getNameTag(), "sparcsol");
		assertEquals(osStorage.getNikName(), "sparcsol");
		sysprops.setProperty(OS_NAMRE, realOS);
	}
	
	public final void testGenerateBundleRISCHP() throws Exception {
		Properties sysprops = System.getProperties();
		realOS = sysprops.getProperty(OS_NAMRE);
		sysprops.setProperty(OS_NAMRE, "PA-RISC HP-UX");
		OSStorage osStorage = OSStorage.getInstance();
		assertEquals(osStorage.getName(), "PA-RISC HP-UX");
		assertEquals(osStorage.getNameTag(), "hp9000s700");
		assertEquals(osStorage.getNikName(), "hpux");
		sysprops.setProperty(OS_NAMRE, realOS);
	}
	
	public final void testGenerateBundleItaniumHP() throws Exception {
		Properties sysprops = System.getProperties();
		realOS = sysprops.getProperty(OS_NAMRE);
		sysprops.setProperty(OS_NAMRE, "Itanium HP-UX");
		OSStorage osStorage = OSStorage.getInstance();
		assertEquals(osStorage.getName(), "Itanium HP-UX");
		assertEquals(osStorage.getNameTag(), "hpia64");
		assertEquals(osStorage.getNikName(), "hpia64");
		sysprops.setProperty(OS_NAMRE, realOS);
	}
	
	public final void testGenerateBundleException() throws Exception {
		Properties sysprops = System.getProperties();
		realOS = sysprops.getProperty(OS_NAMRE);
		sysprops.setProperty(OS_NAMRE, "SomeUnknownOS");
		try {
			OSStorage.getInstance();
			fail();
		} catch (IllegalArgumentException e) {}
		sysprops.setProperty(OS_NAMRE, realOS);
	}
}
