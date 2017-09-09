package com.gensym.jgi.download;

import com.gensym.ui.AbstractCommand;
import com.gensym.util.NtwIllegalArgumentException;
import com.gensym.util.Sequence;
import com.gensym.util.Structure;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.AttributeExportSymbols;
import com.gensym.util.symbol.G2TypeSymbols;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import java.beans.PropertyChangeListener;
import java.io.IOException;
import java.util.Hashtable;

import static com.gensym.util.symbol.AttributeExportSymbols.ATTRIBUTE_NAME_;
import static com.gensym.util.symbol.AttributeTypeSpecificationSymbols.TYPE_OR_OPERATOR_;
import static org.junit.Assert.*;

public class InterfaceGeneratorTest {

    private InterfaceGenerator interfaceGenerator;
    private String genPackage = "COM\\sun\\java\\ding";
    private String locationWindows = "\\home\\me\\java\\gensources\\";
    private String locationPOSIX = "/home/me/java/gensources/";
    private String location = java.io.File.separatorChar == '/' ? locationPOSIX : locationWindows;
    private static final Symbol ORIGINAL_ATTRIBUTE_NAME_ = Symbol.intern ("ORIGINAL-ATTRIBUTE-NAME");
    private static final Symbol POSITIVE_INTEGER_ = Symbol.intern ("POSITIVE-INTEGER");

    @Before
    public void setUp() throws Exception {

        final String[] specificImports = new String[]
            {
                    "com.gensym.jgi.download.DefaultStubFactory",
                    "com.gensym.jgi.classes.SystemPredicate",
            };
        final ClassNameMapper nameMapper = new ClassNameMapper() {
            @Override
            public String javaClassNameFromG2ClassName(Symbol g2ClassName_) {
                return "javaClassNameFromG2ClassName";
            }

            @Override
            public String getVersionForClass(Symbol g2ClassName_) {
                return "getVersionForClass";
            }
        };

        interfaceGenerator = new InterfaceGenerator(genPackage, location, specificImports, nameMapper);

    }

    @After
    public void tearDown() { interfaceGenerator = null; }

    @Test
    public void test_ensureDirectory_onCall_returnsDirectoryName() {

        // Arrange
        String packageName = "com.gensym.util.Symbol";
        final char sepr = java.io.File.separatorChar;

        // Act
        String actualResult = interfaceGenerator.ensureDirectory(packageName);

        // Assert
        assertEquals(location + "com" +sepr+ "gensym" +sepr+ "util" +sepr+ "Symbol", actualResult);
    }

    @Test
    public void test_generateInterface_onCall_returnsFullyQualifiedNameOfInterface() throws IOException {

        // Arrange
        Symbol className_ = Symbol.intern("JGInterface");
        String genPackage = "com.gensym.jgi";
        Symbol[] superClassNames = new Symbol[]{};
        Symbol[] classInheritancePath = new Symbol[]{};
        Sequence classAttrDescrpns = new Sequence();
        Sequence attrDescrpns = new Sequence();
        MethodInfo[] methodInfoArray = new MethodInfo[]{};
        Hashtable overridesTable = new Hashtable();

        // Act
        String actualResult = interfaceGenerator.generateInterface(className_, genPackage, superClassNames, classInheritancePath, classAttrDescrpns, attrDescrpns, methodInfoArray, overridesTable);

        // Assert
        assertEquals("com.gensym.classes.Item", actualResult);
    }

    @Test
    public void test_generateExternalG2EventInterface_onCall_returnsFullyQualifiedNameOfInterface() throws IOException {

        // Arrange
        Symbol className_ = Symbol.intern("JGInterface");
        String genPackage = "com.gensym.jgi";
        Symbol[] superClassNames = new Symbol[]{};
        Symbol[] classInheritancePath = new Symbol[]{};
        Sequence classAttrDescrpns = new Sequence();
        Sequence attrDescrpns = new Sequence();
        MethodInfo[] methodInfoArray = new MethodInfo[]{};
        Hashtable overridesTable = new Hashtable();
        final char sepr = java.io.File.separatorChar;

        // Act
        String actualResult = interfaceGenerator.generateExternalG2EventInterface(className_, genPackage, superClassNames, classInheritancePath, classAttrDescrpns, attrDescrpns, methodInfoArray, overridesTable);

        // Assert
        assertEquals(location + "com" +sepr+ "gensym" +sepr+ "jgi" +sepr+ "G2_Jginterface.java", actualResult);
    }

    @Test
    public void test_generateExternalG2ListenerInterface_onCall_returnsFullyQualifiedNameOfInterface() throws IOException {

        // Arrange
        Symbol className_ = Symbol.intern("JGInterface");
        String genPackage = "com.gensym.jgi";
        Symbol[] superClassNames = new Symbol[]{};
        Symbol[] classInheritancePath = new Symbol[]{};
        Sequence classAttrDescrpns = new Sequence();
        Sequence attrDescrpns = new Sequence();
        MethodInfo[] methodInfoArray = new MethodInfo[]{};
        Hashtable overridesTable = new Hashtable();
        final char sepr = java.io.File.separatorChar;

        // Act
        String actualResult = interfaceGenerator.generateExternalG2ListenerInterface(className_, genPackage, superClassNames, classInheritancePath, classAttrDescrpns, attrDescrpns, methodInfoArray, overridesTable);

        // Assert
        assertEquals(location + "com" +sepr+ "gensym" +sepr+ "jgi" +sepr+ "G2_Jginterface.java", actualResult);
    }

    @Test
    public void test_getAttributeInfo_onCall_returnsFullyQualifiedNameOfInterface() throws IOException, NtwIllegalArgumentException {

        // Arrange
        Symbol className_ = Symbol.intern("IconDescriptionCommands");
        Class classToExtend = AbstractCommand.class;
        String genPackage = "com.gensym.editor.icon.shell";
        Symbol[] classesToCollect = new Symbol[]{};
        Symbol[] classInheritancePath = new Symbol[]{};
        MethodInfo[] methodInfoArray = new MethodInfo[]{};
        Hashtable overridesTable = new Hashtable();
        Sequence classAttrDescrpns = new Sequence();
        Sequence attrDescrpns = new Sequence();

        // Act
        String actualResult = interfaceGenerator.generateStub(className_, classToExtend, classesToCollect, genPackage, classInheritancePath, classAttrDescrpns, attrDescrpns, methodInfoArray, overridesTable);

        // Assert
        assertEquals("com.gensym.classes.ItemImpl", actualResult);
    }

    @Test (expected = ClassFileGenerationException.class)
    public void test_generatePseudoStub_raiseClassException_throwsClassFileGenerationException() throws IOException {

        // Arrange
        String className = "IconDescriptionCommands";
        Class classToExtend = AbstractCommand.class;
        String genPackage = "com.gensym.editor.icon.shell";
        Class[] classesToDelegate = new Class[] { PropertyChangeListener.class };

        // Act
        byte[] actualResult = interfaceGenerator.generatePseudoStub(className, genPackage, classToExtend, classesToDelegate);
    }

    private void testMaybeUndoPaulsBrokenTypeSpecificationMethod(Object attributeType,
         Symbol expectedAttrType, String expectedTypeSpecification) throws Exception {

        // Arrange
        Sequence classAttrDescrpns = new Sequence();
        Sequence attrDescrpns = new Sequence();

        attrDescrpns.add(new Structure(new Symbol[]{
                ATTRIBUTE_NAME_,
                ORIGINAL_ATTRIBUTE_NAME_,
                AttributeExportSymbols.DEFINING_CLASS_,
                AttributeExportSymbols.INITIAL_VALUE_,
                AttributeExportSymbols.TYPE_,
                AttributeExportSymbols.VALUE_READABLE_,
                AttributeExportSymbols.VALUE_WRITABLE_,
                AttributeExportSymbols.IS_SYSTEM_DEFINED_
        }, new Object[]{
                Symbol.intern("SetAttributeName"),
                Symbol.intern("SetOriginalAttributeName"),
                Symbol.intern("SetDefiningClass"),
                "SetInitialValue",
                attributeType,
                new Boolean(true),
                new Boolean(true),
                new Boolean(true)
        }));

        // Act
        AttrInfo actualResult = interfaceGenerator.getAttributeInfo(classAttrDescrpns, attrDescrpns);

        // Assert
        assertEquals(expectedAttrType, actualResult.attrTypes[0]);
        assertEquals(Symbol.intern("SetAttributeName"), actualResult.attrNames[0]);
        assertTrue(actualResult.systemDefined[0]);
        assertTrue(actualResult.readable[0]);
        assertTrue(actualResult.writable[0]);
        assertFalse(actualResult.staticP[0]);
        assertEquals(Symbol.intern("SetOriginalAttributeName"), actualResult.origNames[0]);
        assertEquals(Symbol.intern("SetDefiningClass"), actualResult.defClasses[0]);
        if(expectedTypeSpecification == null)
            assertNull(actualResult.typeSpecifications[0]);
        else
            assertEquals(expectedTypeSpecification, actualResult.typeSpecifications[0].toString());
        assertEquals("SetInitialValue", actualResult.initialValues[0]);
    }

    @Test
    public void test_generateStub_onCall_returnsAttrInfo() throws Exception {

        Symbol attributeType = Symbol.intern("SetType");
        Symbol expectedAttrType = G2TypeSymbols.ITEM_OR_VALUE_;
        String expectedTypeSpecification = "<G2 ItemOrValueType>";

        testMaybeUndoPaulsBrokenTypeSpecificationMethod(attributeType, expectedAttrType, expectedTypeSpecification);
    }

    @Test
    public void test_generateStub_PositiveIntegerType_returnsAttrInfo() throws Exception {

        Symbol attributeType = POSITIVE_INTEGER_;
        Symbol expectedAttrType = G2TypeSymbols.INTEGER_;
        String expectedTypeSpecification = "<G2 IntegerType>";

        testMaybeUndoPaulsBrokenTypeSpecificationMethod(attributeType, expectedAttrType, expectedTypeSpecification);
    }

    @Test
    public void test_generateStub_SymbolType_returnsAttrInfo() throws Exception {

        Symbol attributeType = G2TypeSymbols.SYMBOL_;
        Symbol expectedAttrType = G2TypeSymbols.SYMBOL_;
        String expectedTypeSpecification = "<G2 SymbolType>";

        testMaybeUndoPaulsBrokenTypeSpecificationMethod(attributeType, expectedAttrType, expectedTypeSpecification);
    }

    @Test
    public void test_generateStub_nullType_returnsAttrInfo() throws Exception {

        Symbol attributeType = null;
        Symbol expectedAttrType = G2TypeSymbols.ITEM_OR_VALUE_;
        String expectedTypeSpecification = null;

        testMaybeUndoPaulsBrokenTypeSpecificationMethod(attributeType, expectedAttrType, expectedTypeSpecification);
    }

    @Test
    public void test_generateStub_structureType_returnsAttrInfo() throws Exception {

        Structure attributeType = new Structure();
        attributeType.setAttributeValue (TYPE_OR_OPERATOR_, G2TypeSymbols.ITEM_OR_VALUE_);
        Symbol expectedAttrType = G2TypeSymbols.ITEM_OR_VALUE_;
        String expectedTypeSpecification = "<G2 ItemOrValueType>";

        testMaybeUndoPaulsBrokenTypeSpecificationMethod(attributeType, expectedAttrType, expectedTypeSpecification);
    }
}
