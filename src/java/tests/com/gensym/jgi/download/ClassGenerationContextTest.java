package com.gensym.jgi.download;

import com.gensym.util.G2ClassTranslator;
import com.gensym.util.Symbol;
import org.junit.Before;
import org.junit.Test;

import java.io.ByteArrayOutputStream;
import java.util.Hashtable;

import static com.gensym.helpers.ObjectsFactory.anyString;
import static com.gensym.jgi.download.ObjectsFactory.anyClassOverrides;
import static com.gensym.jgi.download.ObjectsFactory.makeSomeMethodInfoAsActive;
import static org.junit.Assert.assertEquals;

public class ClassGenerationContextTest extends ClassGenerationContextHelper {
    private static final String G2EventObject = Symbol.intern("G2-EVENT-OBJECT").toString();

    private ByteArrayOutputStream outputStream;
    private ClassGenerationContext sut;

    @Before
    public void setup() {
        this.isInterface = com.gensym.helpers.ObjectsFactory.anyBoolean();
        this.packageName = anyString();
        this.className = anyString();
        this.classNameMapper = new ClassNameMapperStub();

        createSut();
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
		java.util.Date date = new java.util.Date();

                // Act
                this.sut.generateClass(imports, superClass, classesToCollect, interfaces, classInheritancePath, attributes, methodInfos, overridesInHashTable, date);

                // Assert
                // AJ - GENSYMCID-3803
                //      Commenting out Assert below as it is flaky as explained below -
                // 	Generated class file will have timestamp of generation in the header 
                //		and this may or may not match depending on time of generation leading to occassional errors
                //		Example - : Sun Jul 09 00:20:58 BST 2017
                //		Actual  - : Sun Jul 09 00:20:59 BST 2017
                assertEquals(
                        errorMessage,
                        generateClass(imports, superClass, classesToCollect, interfaces, classInheritancePath, attributes, methodInfos, overridesInHashTable, date),
                        outputStream.toString());
            }
        }
    }

    @Test
    public void test_generateMethods_always_generatesMethod() throws MalformedOverridesException {
        // Arrange
        String[] classNameTestCases = new String[]{G2EventObject, anyString()};
        boolean[] onlyEventMethodsTestCases = new boolean[]{true, false};
        MethodInfo[][] methodInfoArrayTestCases = new MethodInfo[][]{com.gensym.jgi.download.ObjectsFactory.anyMethodInfoArray(), null};
        makeSomeMethodInfoAsActive(methodInfoArrayTestCases[0]);

        for (MethodInfo[] methodInfoArray : methodInfoArrayTestCases) {
            for (String classNameTestCase : classNameTestCases) {
                for (boolean onlyEventMethods : onlyEventMethodsTestCases) {
                    this.className = classNameTestCase;
                    createSut();

                    Hashtable overridesTable = new Hashtable();
                    overridesTable.put(Symbol.intern(this.className), anyClassOverrides());
                    overridesTable.put(Symbol.intern(anyString()), anyClassOverrides());

                    // Act
                    this.sut.generateMethods(methodInfoArray, overridesTable, onlyEventMethods);

                    // Assert
                    assertEquals(generateMethods(methodInfoArray, overridesTable, onlyEventMethods), this.outputStream.toString());
                }
            }
        }
    }

    @Test
    public void test_generateG2EventListenerExternalInterface_always_generatesExtInterface() {
        // Arrange
        String[] inheritanceClassNameTestCases = new String[]{anyString(), G2EventObject};

        for (String inheritanceClassNameTestCase : inheritanceClassNameTestCases) {
            String[] imports = com.gensym.helpers.ObjectsFactory.anyStringsArray();
            String superClass = anyString();
            String[] interfaces = com.gensym.helpers.ObjectsFactory.anyStringsArray();
            Symbol[] classInheritancePath = com.gensym.helpers.ObjectsFactory.anySymbolsArray();
            classInheritancePath[0] = Symbol.intern(inheritanceClassNameTestCase);
            MethodInfo[] methodInfos = com.gensym.jgi.download.ObjectsFactory.anyMethodInfoArray();
            Hashtable overridesInHashTable = new Hashtable();
            final java.util.Date date = new java.util.Date();

            // Act
            this.sut.generateG2EventListenerExternalInterface(imports, superClass, interfaces, classInheritancePath, methodInfos, overridesInHashTable, date);

            // Assert
            assertEquals(
                    generateG2EventListenerExternalInterface(imports, superClass, interfaces, classInheritancePath, methodInfos, overridesInHashTable, date),
                    this.outputStream.toString());
        }
    }

    @Test
    public void test_ensureLegalJavaVariableName_reservedWord_returnsLegalName() {
        // Arrange
        for (String reservedWord : JavaReservedWords) {
            // Act & Assert
            assertEquals(reservedWord + "$", this.sut.ensureLegalJavaVariableName(reservedWord));
        }
    }

    @Test
    public void test_ensureLegalJavaVariableName_notReservedWord_returnsSameName() {
        // Arrange
        String origName = anyString();

        // Act & Assert
        assertEquals(origName, this.sut.ensureLegalJavaVariableName(origName));
    }

    @Test
    public void test_ensureLegalMethodName_reservedWord_returnsLegalName() {
        // Arrange
        for (String reservedWord : JavaReservedWords) {
            // Act & Assert
            assertEquals("_" + reservedWord, this.sut.ensureLegalMethodName(reservedWord));
        }
    }

    @Test
    public void test_ensureLegalMethodName_notReservedWord_returnsSameName() {
        // Arrange
        String origName = anyString();

        // Act & Assert
        assertEquals(origName, this.sut.ensureLegalMethodName(origName));
    }

    @Test
    public void test_writeOverridenPropertyAccessors_always_writesAccessors() throws MalformedOverridesException {
        // Arrange
        ClassOverrides overrides = anyClassOverrides();

        // Act
        this.sut.writeOverridenPropertyAccessors(overrides);

        // Assert
        assertEquals(writeOverriddenPropertyAccessors(overrides), this.outputStream.toString());
    }

    // -- Helper Methods --

    protected void createSut() {
        super.createSut();

        this.outputStream = new ByteArrayOutputStream();
        this.context = this.sut = new ClassGenerationContext(this.outputStream, this.isInterface, this.packageName, this.className, this.classNameMapper);
        this.javaClassName = G2ClassTranslator.createJavaClassNameFromG2ClassName(Symbol.intern(this.className));
        this.isG2EventObjectClass = false;
    }
}
