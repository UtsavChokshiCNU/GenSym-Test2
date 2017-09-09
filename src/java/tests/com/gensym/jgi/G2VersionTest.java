package com.gensym.jgi;

import com.gensym.util.Symbol;
import com.gensym.util.Structure;
import org.junit.Test;
import org.junit.Before; 
import org.junit.After;
import org.junit.runners.Parameterized;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.Collection;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.assertTrue;
import static org.junit.Assert.assertFalse;

/** 
* G2Version Tester. 
* 
* @author Chaitanya Deepti
* @since <pre>May 19, 2017</pre> 
* @version 1.0 
*/ 
public class G2VersionTest { 

private G2Version fixture = new G2Version(1,1,"Rev",1,"2015");
/**
* Method: toString()
*/ 
@Test
public void testToString() throws Exception {
  String result = fixture.toString();
  assertEquals("G2Version [MAJOR = 1:MINOR = 1:TYPE  = Rev:REVISION = null:ID    = 2015 DOY = -2708]", result);
} 

/** 
* 
* Method: compareTo(G2Version version) 
* 
*/ 
@Test
public void testCompareTo() throws Exception {
    Structure structure = getStructure(2, 1, Symbol.intern("Rev"), 1, 1, "2016");
    G2Version g2Version = new G2Version(structure);
    int result = fixture.compareTo(g2Version);
    assertEquals(result, -1);
}
/**
 *
 * Method: compareTo(G2Version version)
 *
 */
@Test
public void testCompareToMajorVersion() throws Exception {
    Structure structure = getStructure(0, 1, Symbol.intern("Rev"), 1, 1, "2016");
    G2Version g2Version = new G2Version(structure);
    int result = fixture.compareTo(g2Version);
    assertEquals(result, 1);
}
/**
 *
 * Method: compareTo(G2Version version)
 *
 */
@Test
public void testCompareToMinorVersion() throws Exception {
    Structure structure = getStructure(1, 0, Symbol.intern("Rev"), 0, 0, "2014");
    G2Version g2Version = new G2Version(structure);
    int result = fixture.compareTo(g2Version);
    assertEquals(result, 1);
}
/**
 *
 * Method: compareTo(G2Version version)
 *
 */
@Test
public void testCompareToMinorVersionMore() throws Exception {
    Structure structure = getStructure(1, 2, Symbol.intern("Rev"), 0, 0, "2014");
    G2Version g2Version = new G2Version(structure);
    int result = fixture.compareTo(g2Version);
    assertEquals(result, -1);
}
/**
 *
 * Method: compareTo(G2Version version)
 *
 */
@Test
public void testCompareToRevision() throws Exception {
    Structure structure = getStructure(1, 1, Symbol.intern("Rev"), 0, 0, "2014");
    G2Version g2Version = new G2Version(structure);
    int result = fixture.compareTo(g2Version);
    assertEquals(result, 1);
}
/**
 *
 * Method: compareTo(G2Version version)
 *
 */
@Test
public void testCompareToRevisionMore() throws Exception {
    Structure structure = getStructure(1, 1, Symbol.intern("Rev"), 2, 0, "2014");
    G2Version g2Version = new G2Version(structure);
    int result = fixture.compareTo(g2Version);
    assertEquals(result, -1);
}
/**
 *
 * Method: compareTo(G2Version version)
 *
 */
@Test
public void testCompareToPatchNumber() throws Exception {
    Structure structure = getStructure(1, 1, Symbol.intern("Rev"), 1, 0, "2015");
    G2Version g2Version = new G2Version(structure);
    int result = fixture.compareTo(g2Version);
    assertEquals(result, 0);
}
/**
 *
 * Method: compareTo(G2Version version)
 *
 */
@Test
public void testCompareToPatchNumberMore() throws Exception {
    Structure structure = getStructure(1, 1, Symbol.intern("Rev"), 1, 2, "2015");
    G2Version g2Version = new G2Version(structure);
    int result = fixture.compareTo(g2Version);
    assertEquals(result, 0);
}
/**
 *
 * Method: compareTo(G2Version version)
 *
 */
@Test
public void testCompareToBuildId() throws Exception {
    Structure structure = getStructure(1, 1, Symbol.intern("Rev"), 1, 1, "2014");
    G2Version g2Version = new G2Version(structure);
    int result = fixture.compareTo(g2Version);
    assertEquals(result, 1);
}
/**
 *
 * Method: compareTo(G2Version version)
 *
 */
@Test
public void testCompareToBuildIdMore() throws Exception {
    Structure structure = getStructure(1, 1, Symbol.intern("Rev"), 1, 1, "2016");
    G2Version g2Version = new G2Version(structure);
    int result = fixture.compareTo(g2Version);
    assertEquals(result, -1);
}
/**
 *
 * Method: compareTo(G2Version version)
 *
 */
@Test
public void testCompareToRevMore() throws Exception {
    Structure structure = getStructure(1, 1, Symbol.intern("Beta"), 1, 1, "2016");
    G2Version g2Version = new G2Version(structure);
    int result = fixture.compareTo(g2Version);
    assertEquals(result, 1);
}
/**
 *
 * Method: compareTo(G2Version version)
 *
 */
@Test(expected = IllegalArgumentException.class)
public void testCompareToRelease() throws Exception {
    Structure structure = getStructure(1, 1, Symbol.intern("1234"), 1, 1, "2016");
    G2Version g2Version = new G2Version(structure);
    fixture.compareTo(g2Version);
}
/**
* 
* Method: equals(Object otherVersion) 
* 
*/ 
@Test
public void testEquals() throws Exception {
    G2Version g2Version = new G2Version("Version.1.1.Rev.1.2015");
    boolean result = fixture.equals(g2Version);
    assertTrue(result);
}
/**
 *
 * Method: equals(Object otherVersion)
 *
 */
@Test(expected = IllegalArgumentException.class)
public void testEqualsException() throws Exception {
    G2Version g2Version = new G2Version("1.1.Rev.1b.2015");
    fixture.equals(g2Version);
}
/**
 *
 * Method: equals(Object otherVersion)
 *
 */
@Test(expected = IllegalArgumentException.class)
public void testEqualsBuildIdException() throws Exception {
    G2Version g2Version = new G2Version("Version.1.1.Rev.1.201512");
    fixture.equals(g2Version);
}
/** 
* 
* Method: hashCode() 
* 
*/ 
@Test
public void testHashCode() throws Exception {
    int result = fixture.hashCode();
    assertNotNull(result);
}

/** 
* 
* Method: getMajorVersion() 
* 
*/ 
@Test
public void testGetMajorVersion() throws Exception {
    int result = fixture.getMajorVersion();
    assertEquals(result, 1);
}

/** 
* 
* Method: getMinorVersion() 
* 
*/ 
@Test
public void testGetMinorVersion() throws Exception {
    int result = fixture.getMinorVersion();
    assertEquals(result, 1);
} 

/** 
* 
* Method: getReleaseQuality() 
* 
*/ 
@Test
public void testGetReleaseQuality() throws Exception {
    String result = fixture.getReleaseQuality();
    assertEquals(result, "Rev");
}

/** 
* 
* Method: getRevision() 
* 
*/ 
@Test
public void testGetRevision() throws Exception {
    int result = fixture.getRevision();
    assertEquals(result, 1);
} 

/** 
* 
* Method: getBuildID() 
* 
*/ 
@Test
public void testGetBuildID() throws Exception {
    String result = fixture.getBuildID();
    assertEquals(result, "2015");
} 


/**
*
* Method: mapQualityToID(String releaseQuality)
*
*/
@Test
public void testMapQualityToID() throws Exception {
try {
   Method method = G2Version.class.getMethod("mapQualityToID", String.class);
   method.setAccessible(true);
   Object result = method.invoke(fixture, "Rev");
   assertEquals(result, 3);
} catch(NoSuchMethodException e) {
} catch(IllegalAccessException e) {
} catch(InvocationTargetException e) {
}

}
/**
 *
 * Method: mapQualityToID(String releaseQuality)
 *
 */
@Test
public void testMapQualityToIDBeta() throws Exception {
    G2Version fixture = new G2Version(1,1,"BETA",1,"2015");
    try {
        Method method = G2Version.class.getMethod("mapQualityToID", String.class);
        method.setAccessible(true);
        Object result = method.invoke(fixture, "BETA");
        assertEquals(result, 2);
    } catch(NoSuchMethodException e) {
    } catch(IllegalAccessException e) {
    } catch(InvocationTargetException e) {
    }

}
/**
 *
 * Method: mapQualityToID(String releaseQuality)
 *
 */
@Test
public void testMapQualityToIDAlpha() throws Exception {
    Structure structure = getStructure(1, 1, Symbol.intern("ALPHA"), 1, 1, "2016");
    G2Version g2Version = new G2Version(structure);
    try {
        Method method = G2Version.class.getMethod("mapQualityToID", String.class);
        method.setAccessible(true);
        Object result = method.invoke(g2Version, "ALPHA");
        assertEquals(result, 1);
    } catch(NoSuchMethodException e) {
    } catch(IllegalAccessException e) {
    } catch(InvocationTargetException e) {
    }

}
/**
 *
 * Method: mapQualityToID(String releaseQuality)
 *
 */
@Test
public void testMapQualityToIDPrototype() throws Exception {
    Structure structure = getStructure(1, 1, Symbol.intern("PROTOTYPE"), 1, 1, "2016");
    G2Version g2Version = new G2Version(structure);
    try {
        Method method = G2Version.class.getMethod("mapQualityToID", String.class);
        method.setAccessible(true);
        Object result = method.invoke(g2Version, "PROTOTYPE");
        assertEquals(result, 0);
    } catch(NoSuchMethodException e) {
    } catch(IllegalAccessException e) {
    } catch(InvocationTargetException e) {
    }

}
/**
* 
* Method: mapQualitySymbolToQuality(Symbol qualitySymbol_) 
* 
*/ 
@Test
public void testMapQualitySymbolToQuality() throws Exception {
try { 
   Method method = G2Version.class.getMethod("mapQualitySymbolToQuality", Symbol.class);
   method.setAccessible(true); 
   Object result = method.invoke(fixture, Symbol.intern("PROTOTYPE"));
   assertEquals(result, "PROTOTYPE_");
} catch(NoSuchMethodException e) { 
} catch(IllegalAccessException e) { 
} catch(InvocationTargetException e) { 
}
}
/**
 *
 * Method: getStructure
 * Helper Method.
 */
public Structure getStructure(int majorVersion, int minorVersion, Symbol releaseLevel, int revision, int patchNumber, String buildId) throws Exception {
    Structure structure = new Structure();
    structure.setAttributeValue(com.gensym.util.Symbol.intern("MAJOR-VERSION-NUMBER"), majorVersion);
    structure.setAttributeValue(com.gensym.util.Symbol.intern("MINOR-VERSION-NUMBER"), minorVersion);
    structure.setAttributeValue(com.gensym.util.Symbol.intern("RELEASE-LEVEL"), releaseLevel);
    structure.setAttributeValue(com.gensym.util.Symbol.intern("REVISION"), revision);
    structure.setAttributeValue(com.gensym.util.Symbol.intern("PATCH-NUMBER"), patchNumber);
    structure.setAttributeValue(com.gensym.util.Symbol.intern("BUILD-IDENTIFICATION"), buildId);
    return structure;
}
} 
