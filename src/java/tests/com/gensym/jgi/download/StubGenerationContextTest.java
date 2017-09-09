package com.gensym.jgi.download;

import com.gensym.types.G2Type;
import com.gensym.util.G2ClassTranslator;
import com.gensym.util.Structure;
import com.gensym.util.Symbol;
import org.junit.Before;
import org.junit.Test;

import java.io.ByteArrayOutputStream;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.nio.charset.Charset;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Hashtable;

import static com.gensym.helpers.ObjectsFactory.anyBoolean;
import static com.gensym.helpers.ObjectsFactory.anyString;
import static com.gensym.jgi.G2JavaStubController.JGI_G2PROXY_MIXIN_CLASS_;
import static com.gensym.jgi.download.ClassGenerationContext.HAND_CODED_METHODS_;
import static com.gensym.jgi.download.ObjectsFactory.anyClassOverrides;
import static com.gensym.jgi.download.ObjectsFactory.anyMethodInfoArray;
import static com.gensym.jgi.download.ObjectsFactory.makeSomeMethodInfoAsActive;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;
import static org.powermock.api.mockito.PowerMockito.when;

public class StubGenerationContextTest extends StubGenerationContextHelper {
    private static final int SamplesCount = 10;
    private static final String G2EventObject = Symbol.intern("G2-EVENT-OBJECT").toString();

    private ByteArrayOutputStream outputStream;
    private StubGenerationContext sut;

    @Before
    public void setup() {
        this.isInterface = anyBoolean();
        this.packageName = anyString();
        this.className = anyString();
        this.classNameMapper = new ClassNameMapperStub();

        createSut();
    }

    @Test
    public void test_generateHeader_always_generatesHeader() throws MalformedOverridesException {
        boolean[] isInterfaceTestCases = new boolean[]{true, false};
        ArrayList<String[]> interfacesTestCases = createInterfacesTestCases();
        String[] classNameTestCases = new String[]{anyString(), G2EventObject};
        final java.util.Date date = new java.util.Date();

        for (String classNameTestCase : classNameTestCases) {
            for (boolean isInterfaceTestCase : isInterfaceTestCases) {
                for (String[] interfaces : interfacesTestCases) {
                    this.outputStream = new ByteArrayOutputStream();
                    this.className = classNameTestCase;
                    this.isInterface = isInterfaceTestCase;
                    createSut();
                    String errorMessage = String.format(
                            "Failed for Class Name: %s, Is Interface: %s, Interface: %s",
                            this.className,
                            this.isInterface,
                            Arrays.toString(interfaces));

                    // Arrange
                    String[] imports = createImportsArray();
                    String superClass = anyString();
                    ClassOverrides overrides = anyClassOverrides();

                    // Act
                    this.sut.generateHeader(imports, superClass, interfaces, overrides, date);

                    // Assert
                    assertEquals(errorMessage, generateHeader(imports, superClass, interfaces, overrides, date), this.outputStream.toString());
                }
            }
        }
    }

    @Test
    public void test_generateConstructors_always_generateConstructors() {
        // Arrange
        // Nothing to arrange

        // Act
        this.sut.generateConstructors();

        // Assert
        assertEquals(generateConstructors(), this.outputStream.toString());
    }

    @Test
    public void test_generateFields_always_generateFields() throws MalformedOverridesException {
        // Arrange
        AttrInfo attrInfo = createAttrInfo();
        Symbol[] classInheritancePath = com.gensym.helpers.ObjectsFactory.anySymbolsArray();
        ClassOverrides overrides = anyClassOverrides();

        // Act
        this.sut.generateFields(attrInfo, classInheritancePath, overrides);

        // Assert
        assertEquals(generateFields(attrInfo, classInheritancePath, overrides), this.outputStream.toString());
    }

    @Test
    public void test_getPackageName_always_retsPackageName() {
        // Arrange
        // No arrangement

        // Act & Assert
        assertEquals(this.packageName, this.sut.getPackageName());
    }

    @Test
    public void test_generateMethods_onlyEventMethods_generatesMethods() throws MalformedOverridesException {
        test_generateMethods(anyMethodInfoArray(), true);
    }

    @Test
    public void test_generateMethods_notOnlyEventMethods_generatesMethods() throws MalformedOverridesException {
        test_generateMethods(anyMethodInfoArray(), false);
    }

    @Test
    public void test_generateMethods_methodInfoArrayIsNull_generatesMethods() throws MalformedOverridesException {
        test_generateMethods(null, anyBoolean());
    }

    @Test
    public void test_generateClass_always_generatesClass() {
        // Arrange
        this.isInterface = true;
        String[] classNameTestCases = new String[]{G2EventObject, anyString()};
        String[] inheritanceClassNameTestCases = new String[]{anyString(), G2EventObject};

            for (String classNameTestCase : classNameTestCases) {
                for (String inheritanceClassNameTestCase : inheritanceClassNameTestCases) {
                    this.className = classNameTestCase;
                    createSut();

                    String errorMessage = String.format(
                            "Failed for Class Name: %s, Is Interface: %s, InheritanceClassName: %s",
                            this.className,
                            this.isInterface,
                            inheritanceClassNameTestCase);

                    String[] imports = com.gensym.helpers.ObjectsFactory.anyStringsArray();
                    String superClass = anyString();
                    Symbol[] classesToCollect = com.gensym.helpers.ObjectsFactory.anySymbolsArray();
                    String[] interfaces = com.gensym.helpers.ObjectsFactory.anyStringsArray();
                    Symbol[] classInheritancePath = com.gensym.helpers.ObjectsFactory.anySymbolsArray();
                    classInheritancePath[0] = Symbol.intern(inheritanceClassNameTestCase);
                    AttrInfo attributes = createAttrInfo();
                    MethodInfo[] methodInfos = com.gensym.jgi.download.ObjectsFactory.anyMethodInfoArray();
                    Hashtable overridesInHashTable = new Hashtable();

                    // Act
                    this.sut.generateClass(imports, superClass, classesToCollect, interfaces, classInheritancePath, attributes, methodInfos, overridesInHashTable);

                    // Assert
                    assertTrue(errorMessage, outputStream.toString().contains(expectedGeneratedClass(imports, superClass, classesToCollect, interfaces, classInheritancePath, attributes, methodInfos, overridesInHashTable)));
                }
            }
    }

    @Test
    public void test_generatePropertyAccessors_always_generatesAccessors() throws MalformedOverridesException {
        // Arrange
        String[] jSlotTypes = com.gensym.helpers.ObjectsFactory.anyStringsArray();
        String[] jSlotNames = com.gensym.helpers.ObjectsFactory.anyStringsArray();
        Symbol[] slotNames = com.gensym.helpers.ObjectsFactory.anySymbolsArray();
        jSlotNames[0] = "Text";
        slotNames[0] = Symbol.intern(jSlotNames[0]);
        int[] generationFlags = anyIntegersArray();
        G2Type[] typeSpecifications = com.gensym.jgi.download.ObjectsFactory.anyG2TypesArray();
        generateSutFields();

        // Act
        this.sut.generatePropertyAccessors(jSlotTypes, jSlotNames, slotNames, generationFlags, typeSpecifications);

        // Assert
        assertEquals(this.generatePropertyAccessors(jSlotTypes, jSlotNames, slotNames, generationFlags), this.outputStream.toString());
    }

    @Test
    public void test_writeOverridenPropertyAccessors_always_writesPropertyAccessors() throws MalformedOverridesException {
        // Arrange
        ClassOverrides overrides = anyClassOverrides();

        // Act
        this.sut.writeOverridenPropertyAccessors(overrides);

        // Assert
        assertEquals(writeOverriddenPropertyAccessors(overrides), this.outputStream.toString());
    }

    @Test
    public void test_codeToMakeObject_always_retsVarWithType() {
        // Arrange
        String varName = anyString();
        String[] typesTestCases = new String[]{"int", "double", "boolean", "anyType"};
        String[] expectedTestCases = new String[]{
                "new Integer (" + varName + ")",
                "new Double (" + varName + ")",
                "new Boolean (" + varName + ")",
                varName
        };

        for (int idx = 0; idx < typesTestCases.length; idx++) {
            String type = typesTestCases[idx];

            // Act & Assert
            assertEquals(expectedTestCases[idx], StubGenerationContext.codeToMakeObject(varName, type));
        }
    }

    @Test
    public void test_codeToGetPrimitiveValueOrCastReturnObject_always_retsValueOrObject() {
        // Arrange
        String varName = anyString();
        String[] typesTestCases = new String[]{"int", "double", "boolean", "anyType"};
        String[] expectedTestCases = new String[]{
                "((Integer)" + varName + ").intValue ()",
                "((Double)" + varName + ").doubleValue ()",
                "((Boolean)" + varName + ").booleanValue ()",
                "(" + typesTestCases[3] + ")" + varName
        };

        for (int idx = 0; idx < typesTestCases.length; idx++) {
            String type = typesTestCases[idx];

            // Act & Assert
            assertEquals(expectedTestCases[idx], StubGenerationContext.codeToGetPrimitiveValueOrCastReturnObject(varName, type));
        }
    }

    @Test
    public void test_generateEventMethods_always_generatesMethods() throws MalformedOverridesException {
        // Arrange
        ClassOverrides overrides = anyClassOverrides();

        // Act
        this.sut.generateEventMethods(overrides);

        // Assert
        assertEquals(this.generateEventMethods(overrides), this.outputStream.toString());
    }

    // -- Helper Methods --

    private static ArrayList<String[]> createInterfacesTestCases() {
        ArrayList<String[]> interfacesTestCases = new ArrayList<String[]>();
        interfacesTestCases.add(com.gensym.helpers.ObjectsFactory.anyStringsArray());
        interfacesTestCases.add(null);
        return interfacesTestCases;
    }

    private static int[] anyIntegersArray() {
        int[] array = new int[SamplesCount];

        for (int idx = 0; idx < SamplesCount; idx++) {
            array[idx] = com.gensym.helpers.ObjectsFactory.anyInteger();
        }

        return array;
    }

    private static String[] createImportsArray() {
        String[] imports = new String[SamplesCount];

        for (int i = 0; i < SamplesCount; i++) {
            imports[i] = anyString();
        }

        imports[3] = null;
        imports[4] = "";
        return imports;
    }

    private void test_generateMethods(MethodInfo[] methodInfoArray, boolean onlyEventMethods) throws MalformedOverridesException {
        // Arrange
        if (methodInfoArray != null) {
            makeSomeMethodInfoAsActive(methodInfoArray);
        }

        createSut();
        this.testStream = new ByteArrayOutputStream();
        this.printWriter = new PrintWriter(new OutputStreamWriter(testStream, Charset.defaultCharset()), true);

        ClassOverrides classOverrides = anyClassOverrides();
        ClassOverrides otherClassOverrides = anyClassOverrides();
        ClassOverrides handCodedOverrides = anyClassOverrides();
        String anotherClass = anyString();
        Hashtable overridesTable = createOverridesTable(classOverrides, otherClassOverrides, handCodedOverrides, anotherClass);
        Hashtable overridesTableClone = createOverridesTable(classOverrides, otherClassOverrides, handCodedOverrides, anotherClass);

        // Act
        this.sut.generateMethods(methodInfoArray, overridesTable, onlyEventMethods);

        // Assert
        assertEquals(generateMethods(methodInfoArray, overridesTableClone, onlyEventMethods).length(), this.outputStream.toString().length());
    }

    private Hashtable createOverridesTable(ClassOverrides classOverrides, ClassOverrides otherClassOverrides, ClassOverrides handCodedOverrides, String anotherClass) {
        Hashtable overridesTable = new Hashtable();
        overridesTable.put(Symbol.intern(this.className), classOverrides);
        overridesTable.put(Symbol.intern(anotherClass), otherClassOverrides);
        overridesTable.put(HAND_CODED_METHODS_, handCodedOverrides);
        return overridesTable;
    }

    @Override
    protected void createSut() {
        super.createSut();

        this.isG2EventObjectClass = false;
        this.isG2ProxyObjectClass = false;

        this.outputStream = new ByteArrayOutputStream();
        this.context = this.sut = new StubGenerationContext(this.outputStream, this.isInterface, this.packageName, this.className, this.classNameMapper);
        this.javaClassInterfaceName = this.javaClassName = G2ClassTranslator.createJavaClassNameFromG2ClassName(Symbol.intern(this.className));
        this.javaClassName += "Impl";
    }
}
