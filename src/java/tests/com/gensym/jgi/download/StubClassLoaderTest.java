package com.gensym.jgi.download;

import static com.gensym.classes.modules.g2evliss.G2EventObject.G2_EVENT_OBJECT_;
import static com.gensym.helpers.ObjectsFactory.*;
import static com.gensym.jgi.download.StubClassLoader.FILE_NAME_LIMIT;
import static com.gensym.util.symbol.AttributeExportSymbols.ATTRIBUTE_NAME_;
import static com.gensym.util.symbol.MethodExportSymbols.ARGUMENT_TYPES_;
import static com.gensym.util.symbol.MethodExportSymbols.METHOD_NAME_;
import static org.junit.Assert.*;
import static org.powermock.api.mockito.PowerMockito.*;

import com.gensym.jgi.Designation;
import com.gensym.jgi.G2Access;
import com.gensym.jgi.G2JavaStubController;
import com.gensym.util.*;
import org.assertj.core.api.Assertions;
import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.ExpectedException;
import org.junit.runner.RunWith;
import org.mockito.Mockito;
import org.powermock.core.classloader.annotations.PrepareForTest;
import org.powermock.modules.junit4.PowerMockRunner;
import org.powermock.reflect.Whitebox;

import java.io.Serializable;
import java.security.NoSuchAlgorithmException;
import java.util.Arrays;
import java.util.Hashtable;
import java.util.Vector;
@RunWith(PowerMockRunner.class)
@PrepareForTest({Class.class, StubClassLoader.MultiPackageChecker.class})
public class StubClassLoaderTest extends StubClassLoaderTestHelper {

    @Rule
    public ExpectedException thrown = ExpectedException.none();

    @Test(expected = ClassNotFoundException.class)
    public void test_loadClass_pusudo_class() throws Exception {

        // Arrange
        StubClassLoader stubClassLoader = mock(StubClassLoader.class);
        Symbol g2ClassName = mock(Symbol.class);
        G2Access context = mock(G2Access.class);

        final boolean isInterface = false;
        final boolean canCallRPC = true;
        when(context.canCallRPC()).thenReturn(canCallRPC);

        final String contextFieldName = "context";
        Whitebox.setInternalState(stubClassLoader, contextFieldName, context);

        Hashtable uninitlzedClasses = mock(Hashtable.class);
        final String uninitlzedClassesFieldName = "uninitlzedClasses";
        Whitebox.setInternalState(stubClassLoader, uninitlzedClassesFieldName, uninitlzedClasses);

        Hashtable loadedStubs = mock(Hashtable.class);
        final String loadedStubsFieldName = "loadedStubs";
        Whitebox.setInternalState(stubClassLoader, loadedStubsFieldName, loadedStubs);

        Hashtable uncompilableClasses = mock(Hashtable.class);
        uncompilableClasses.put(g2ClassName, this.getClass());
        final String uncompilableClassesFieldName = "uncompilableClasses";
        Whitebox.setInternalState(stubClassLoader, uncompilableClassesFieldName, uncompilableClasses);

        Hashtable pseudoClasses = mock(Hashtable.class);
        final String pseudoClassesFieldName = "pseudoClasses";
        Whitebox.setInternalState(stubClassLoader, pseudoClassesFieldName, pseudoClasses);

        Hashtable loadedInterfaces = mock(Hashtable.class);
        loadedInterfaces.put(g2ClassName, this.getClass());
        final String loadedInterfacesFieldName = "loadedInterfaces";
        Whitebox.setInternalState(stubClassLoader, loadedInterfacesFieldName, loadedInterfaces);

        final boolean isPseudoClass = false;
        when(stubClassLoader.generateClassName(g2ClassName, isInterface, isPseudoClass)).thenReturn("");

        Hashtable loadedClasses = mock(Hashtable.class);
        final String loadedClassesFieldName = "loadingClasses";
        Whitebox.setInternalState(stubClassLoader, loadedClassesFieldName, loadedClasses);

        Hashtable bestGuessForRecursionTable = mock(Hashtable.class);
        final String bestGuessForRecursionTableFeildName = "bestGuessForRecursionTable";
        Whitebox.setInternalState(stubClassLoader, bestGuessForRecursionTableFeildName, bestGuessForRecursionTable);

        Whitebox.setInternalState(StubClassLoader.class, "IS_BOOTSTRAPPING", true);

        thrown.expect(StubCreationException.class);

        when(stubClassLoader.loadClass(g2ClassName, isInterface)).thenCallRealMethod();

        // Act
        Class result = stubClassLoader.loadClass(g2ClassName, isInterface);

        // Assert
        Mockito.verify(loadedClasses).remove(g2ClassName);
        Mockito.verify(uncompilableClasses).remove(g2ClassName);
        Mockito.verify(bestGuessForRecursionTable).remove(g2ClassName);


    }


    @Test
    public void test_loadClass_best_guess_interface() throws Exception {

        // Arrange
        StubClassLoader stubClassLoader = mock(StubClassLoader.class);
        Symbol g2ClassName = mock(Symbol.class);
        G2Access context = mock(G2Access.class);

        final boolean isInterface = true;
        final boolean canCallRPC = true;
        when(context.canCallRPC()).thenReturn(canCallRPC);

        final String contextFieldName = "context";
        Whitebox.setInternalState(stubClassLoader, contextFieldName, context);

        Hashtable uninitlzedClasses = mock(Hashtable.class);
        final String uninitlzedClassesFieldName = "uninitlzedClasses";
        Whitebox.setInternalState(stubClassLoader, uninitlzedClassesFieldName, uninitlzedClasses);

        Hashtable loadedStubs = mock(Hashtable.class);
        final String loadedStubsFieldName = "loadedStubs";
        Whitebox.setInternalState(stubClassLoader, loadedStubsFieldName, loadedStubs);

        Hashtable uncompilableClasses = mock(Hashtable.class);
        final String uncompilableClassesFieldName = "uncompilableClasses";
        Whitebox.setInternalState(stubClassLoader, uncompilableClassesFieldName, uncompilableClasses);

        Hashtable pseudoClasses = mock(Hashtable.class);
        final String pseudoClassesFieldName = "pseudoClasses";
        Whitebox.setInternalState(stubClassLoader, pseudoClassesFieldName, pseudoClasses);

        final boolean isPseudoClass = false;
        when(stubClassLoader.generateClassName(g2ClassName, isInterface, isPseudoClass)).thenReturn("");

        Hashtable loadedClasses = mock(Hashtable.class);
        when(loadedClasses.get(g2ClassName)).thenReturn(loadedClasses);
        final String loadedClassesFieldName = "loadingClasses";
        Whitebox.setInternalState(stubClassLoader, loadedClassesFieldName, loadedClasses);

        Hashtable currentlyLoadingDefinitions = mock(Hashtable.class);
        final String currentlyLoadingDefinitionsFieldName = "currentlyLoadingDefinitions";
        Whitebox.setInternalState(stubClassLoader, currentlyLoadingDefinitionsFieldName, currentlyLoadingDefinitions);

        Hashtable loadedInterfaces = mock(Hashtable.class);
        final String loadedInterfacesFieldName = "loadedInterfaces";
        Whitebox.setInternalState(stubClassLoader, loadedInterfacesFieldName, loadedInterfaces);

        Hashtable bestGuessForRecursionTable = mock(Hashtable.class);
        final String bestGuessForRecursionTableFeildName = "bestGuessForRecursionTable";
        Whitebox.setInternalState(stubClassLoader, bestGuessForRecursionTableFeildName, bestGuessForRecursionTable);

//        Class bestGuessInterface = this.getClass();
//        final String getBestCurrentGuessForInterfaceMethodName = "getBestCurrentGuessForInterface";
//        when(stubClassLoader, getBestCurrentGuessForInterfaceMethodName, g2ClassName, loadedInterfaces).thenReturn(bestGuessInterface);

        when(stubClassLoader.loadClass(g2ClassName, isInterface)).thenCallRealMethod();

        // Act
        Class result = stubClassLoader.loadClass(g2ClassName, isInterface);

        // Assert
//        Assertions.assertThat(result).isEqualTo(bestGuessClass);
        Assertions.assertThat(result).isNull();
        Mockito.verify(bestGuessForRecursionTable).put(g2ClassName, null);


    }

    @Test
    public void test_loadClass_best_guess_class() throws Exception {

        // Arrange
        StubClassLoader stubClassLoader = mock(StubClassLoader.class);
        Symbol g2ClassName = mock(Symbol.class);
        G2Access context = mock(G2Access.class);

        final boolean isInterface = false;
        final boolean canCallRPC = true;
        when(context.canCallRPC()).thenReturn(canCallRPC);

        final String contextFieldName = "context";
        Whitebox.setInternalState(stubClassLoader, contextFieldName, context);

        Hashtable uninitlzedClasses = mock(Hashtable.class);
        final String uninitlzedClassesFieldName = "uninitlzedClasses";
        Whitebox.setInternalState(stubClassLoader, uninitlzedClassesFieldName, uninitlzedClasses);

        Hashtable loadedStubs = mock(Hashtable.class);
        final String loadedStubsFieldName = "loadedStubs";
        Whitebox.setInternalState(stubClassLoader, loadedStubsFieldName, loadedStubs);

        Hashtable uncompilableClasses = mock(Hashtable.class);
        final String uncompilableClassesFieldName = "uncompilableClasses";
        Whitebox.setInternalState(stubClassLoader, uncompilableClassesFieldName, uncompilableClasses);

        Hashtable pseudoClasses = mock(Hashtable.class);
        final String pseudoClassesFieldName = "pseudoClasses";
        Whitebox.setInternalState(stubClassLoader, pseudoClassesFieldName, pseudoClasses);

        final boolean isPseudoClass = false;
        when(stubClassLoader.generateClassName(g2ClassName, isInterface, isPseudoClass)).thenReturn("");

        Hashtable loadedClasses = mock(Hashtable.class);
        when(loadedClasses.get(g2ClassName)).thenReturn(loadedClasses);
        final String loadedClassesFieldName = "loadingClasses";
        Whitebox.setInternalState(stubClassLoader, loadedClassesFieldName, loadedClasses);

        Class currentlyLoadedClassDefinitions = this.getClass();
        Hashtable currentlyLoadingDefinitions = mock(Hashtable.class);
        when(currentlyLoadingDefinitions.get(g2ClassName)).thenReturn(currentlyLoadedClassDefinitions);
        final String currentlyLoadingDefinitionsFieldName = "currentlyLoadingDefinitions";
        Whitebox.setInternalState(stubClassLoader, currentlyLoadingDefinitionsFieldName, currentlyLoadingDefinitions);

        Hashtable loadedInterfaces = mock(Hashtable.class);
        final String loadedInterfacesFieldName = "loadedInterfaces";
        Whitebox.setInternalState(stubClassLoader, loadedInterfacesFieldName, loadedInterfaces);

        Class bestGuessClass = this.getClass();
        Hashtable bestGuessForRecursionTable = mock(Hashtable.class);
        when(bestGuessForRecursionTable.get(g2ClassName)).thenReturn(bestGuessClass);
        final String bestGuessForRecursionTableFeildName = "bestGuessForRecursionTable";
        Whitebox.setInternalState(stubClassLoader, bestGuessForRecursionTableFeildName, bestGuessForRecursionTable);

        final String getBestCurrentGuessForStubMethodName = "getBestCurrentGuessForStub";
        when(stubClassLoader, getBestCurrentGuessForStubMethodName, g2ClassName, loadedClasses).thenReturn(bestGuessClass);


        when(stubClassLoader.loadClass(g2ClassName, isInterface)).thenCallRealMethod();

        // Act
        Class result = stubClassLoader.loadClass(g2ClassName, isInterface);

        // Assert
        Assertions.assertThat(result).isEqualTo(bestGuessClass);

    }

    @Test
    public void test_loadClass_currently_loaded_interface() {

        // Arrange
        StubClassLoader stubClassLoader = mock(StubClassLoader.class);
        Symbol g2ClassName = mock(Symbol.class);
        G2Access context = mock(G2Access.class);

        final boolean isInterface = true;
        final boolean canCallRPC = true;
        when(context.canCallRPC()).thenReturn(canCallRPC);

        final String contextFieldName = "context";
        Whitebox.setInternalState(stubClassLoader, contextFieldName, context);

        Hashtable uninitlzedClasses = mock(Hashtable.class);
        final String uninitlzedClassesFieldName = "uninitlzedClasses";
        Whitebox.setInternalState(stubClassLoader, uninitlzedClassesFieldName, uninitlzedClasses);

        Hashtable loadedInterfaces = mock(Hashtable.class);
        final String loadedInterfacesFieldName = "loadedInterfaces";
        Whitebox.setInternalState(stubClassLoader, loadedInterfacesFieldName, loadedInterfaces);

        Hashtable uncompilableClasses = mock(Hashtable.class);
        final String uncompilableClassesFieldName = "uncompilableClasses";
        Whitebox.setInternalState(stubClassLoader, uncompilableClassesFieldName, uncompilableClasses);

        Hashtable pseudoClasses = mock(Hashtable.class);
        final String pseudoClassesFieldName = "pseudoClasses";
        Whitebox.setInternalState(stubClassLoader, pseudoClassesFieldName, pseudoClasses);

        final boolean isPseudoClass = false;
        when(stubClassLoader.generateClassName(g2ClassName, isInterface, isPseudoClass)).thenReturn("");


        Class loadedInterface = this.getClass();

        Hashtable loadingClasses = mock(Hashtable.class);
        final String loadingClassesFieldName = "loadingClasses";
        when(loadingClasses.get(g2ClassName)).thenReturn(loadedInterface);
        Whitebox.setInternalState(stubClassLoader, loadingClassesFieldName, loadingClasses);


        final String currentlyLoadingDefinitionsFieldName = "currentlyLoadingDefinitions";
        Hashtable currentlyLoadingDefinitions = mock(Hashtable.class);
        when(currentlyLoadingDefinitions.get(g2ClassName)).thenReturn(loadedInterface);
        Whitebox.setInternalState(stubClassLoader, currentlyLoadingDefinitionsFieldName, loadingClasses);

        when(stubClassLoader.loadClass(g2ClassName, isInterface)).thenCallRealMethod();

        // Act
        Class result = stubClassLoader.loadClass(g2ClassName, isInterface);

        // Assert
        Assertions.assertThat(result).isEqualTo(loadedInterface);

    }


    @Test
    public void test_loadClass_class_is_uncompilable() {

        // Arrange
        StubClassLoader stubClassLoader = mock(StubClassLoader.class);
        Symbol g2ClassName = mock(Symbol.class);
        G2Access context = mock(G2Access.class);

        final boolean isInterface = false;
        final boolean canCallRPC = true;
        when(context.canCallRPC()).thenReturn(canCallRPC);

        final String contextFieldName = "context";
        Whitebox.setInternalState(stubClassLoader, contextFieldName, context);

        Hashtable uninitlzedClasses = mock(Hashtable.class);
        final String uninitlzedClassesFieldName = "uninitlzedClasses";
        Whitebox.setInternalState(stubClassLoader, uninitlzedClassesFieldName, uninitlzedClasses);

        Hashtable loadedStubs = mock(Hashtable.class);
        final String loadedStubsFieldName = "loadedStubs";
        Whitebox.setInternalState(stubClassLoader, loadedStubsFieldName, loadedStubs);

        Hashtable uncompilableClasses = mock(Hashtable.class);
        final String uncompilableClassesFieldName = "uncompilableClasses";
        Class uncompilableClazz = this.getClass();
        when(uncompilableClasses.get(g2ClassName)).thenReturn(uncompilableClazz);
        Whitebox.setInternalState(stubClassLoader, uncompilableClassesFieldName, uncompilableClasses);

        Sequence classDepthTracing = mock(Sequence.class);
        boolean isClassDepthTracingEmpty = false;
        when(classDepthTracing.isEmpty()).thenReturn(isClassDepthTracingEmpty);
        String classDepthTracingFieldName = "classDepthTracing";
        Whitebox.setInternalState(StubClassLoader.class, classDepthTracingFieldName, classDepthTracing);

        when(stubClassLoader.loadClass(g2ClassName, isInterface)).thenCallRealMethod();
        // Act
        Class result = stubClassLoader.loadClass(g2ClassName, isInterface);

        // Assert
        Assertions.assertThat(result).isNull();

    }

    @Test
    public void test_loadClass_class_is_previously_loaded() {

        // Arrange
        StubClassLoader stubClassLoader = mock(StubClassLoader.class);
        Symbol g2ClassName = mock(Symbol.class);
        G2Access context = mock(G2Access.class);

        final boolean isInterface = false;
        final boolean canCallRPC = true;
        when(context.canCallRPC()).thenReturn(canCallRPC);

        final String contextFieldName = "context";
        Whitebox.setInternalState(stubClassLoader, contextFieldName, context);

        Hashtable uninitlzedClasses = mock(Hashtable.class);
        final String uninitlzedClassesFieldName = "uninitlzedClasses";
        Whitebox.setInternalState(stubClassLoader, uninitlzedClassesFieldName, uninitlzedClasses);

        Hashtable loadedStubs = mock(Hashtable.class);
        final String loadedStubsFieldName = "loadedStubs";
        Class loadedClazz = this.getClass();
        when(loadedStubs.get(g2ClassName)).thenReturn(loadedClazz);
        Whitebox.setInternalState(stubClassLoader, loadedStubsFieldName, loadedStubs);

        when(stubClassLoader.loadClass(g2ClassName, isInterface)).thenCallRealMethod();

        // Act
        Class result = stubClassLoader.loadClass(g2ClassName, isInterface);

        // Assert
        Assertions.assertThat(result).isEqualTo(loadedClazz);

    }

    @Test(expected = StubCreationException.class)
    public void test_loadClass_context_cant_call_rpc() {

        // Arrange
        StubClassLoader stubClassLoader = mock(StubClassLoader.class);
        Symbol g2ClassName = mock(Symbol.class);
        G2Access context = mock(G2Access.class);

        final boolean isInterface = false;
        final boolean canCallRPC = false;
        when(context.canCallRPC()).thenReturn(canCallRPC);

        final String contextFieldName = "context";
        Whitebox.setInternalState(stubClassLoader, contextFieldName, context);

        when(stubClassLoader.loadClass(g2ClassName, isInterface)).thenCallRealMethod();

        // Act
        stubClassLoader.loadClass(g2ClassName, isInterface);

    }


    @Test
    public void test_MultiPackageChecker_findUserClass_class_not_found() throws Exception {
        // Arrange
        Vector userPackages = new Vector();
        final String invalidPackageName ="invalid.package.";
        userPackages.addElement(invalidPackageName);
        userPackages.addElement(invalidPackageName);
        userPackages.addElement(invalidPackageName);
        userPackages.addElement(invalidPackageName);
        final String userPackagesFieldName = "userPackages";
        Whitebox.setInternalState(stubClassLoader, userPackagesFieldName, userPackages);
        StubClassLoader.MultiPackageChecker multiPackageChecker = stubClassLoader.new MultiPackageChecker();

        // Act
        final String testClassName = "StubClassLoaderTest";
        Class result = multiPackageChecker.findUserClass(testClassName);

        // Assert
        Assertions.assertThat(result).isNull();

    }

    @Test
    public void test_MultiPackageChecker_findUserClass_class_is_found() throws Exception {
        // Arrange
        final String invalidPackageName ="invalid.package.";
        final String validPackageName ="com.gensym.jgi.download.";

        Vector userPackages = new Vector();
        userPackages.addElement(invalidPackageName);
        userPackages.addElement(invalidPackageName);
        userPackages.addElement(validPackageName);
        userPackages.addElement(invalidPackageName);

        final String userPackagesFieldName = "userPackages";
        Whitebox.setInternalState(stubClassLoader,userPackagesFieldName, userPackages);
        StubClassLoader.MultiPackageChecker multiPackageChecker = stubClassLoader.new MultiPackageChecker();
        final String testClassName = "StubClassLoaderTest";

        // Act
        Class result = multiPackageChecker.findUserClass(testClassName);

        // Assert
        final String classFullName = "com.gensym.jgi.download.StubClassLoaderTest";
        Class expectedClass = Class.forName(classFullName);

        Assertions.assertThat(result).isEqualTo(expectedClass);

    }


    @Test
    public void test_NullObject_toString() {
        Assertions.assertThat(new NullObject().toString()).isEqualTo("Null Object");
    }

    @Test
    public void test_MultiPackageChecker_findUserClass_class_is_not_found() {
        // Arrange
        StubClassLoader.MultiPackageChecker multiPackageChecker = stubClassLoader.new MultiPackageChecker();

        // Act
        final String missingClassName = "missingClass";
        Class result = multiPackageChecker.findUserClass(missingClassName);

        // Assert
        Assertions.assertThat(result).isNull();

    }

    @Test
    public void testLoadClass1() throws ClassNotFoundException {
        stubClassLoader.setGenerationMode(0);
        assertEquals(Designation.class.getName(), stubClassLoader.loadClass(Designation.class.getName(), false).getName());
        stubClassLoader.setGenerationMode(1);
        assertEquals(Designation.class.getName(), stubClassLoader.loadClass(Designation.class.getName(), false).getName());
        stubClassLoader.setGenerationMode(2);
        assertEquals(Designation.class.getName(), stubClassLoader.loadClass(Designation.class.getName(), false).getName());
        stubClassLoader.setGenerationMode(3);
        assertEquals(Designation.class.getName(), stubClassLoader.loadClass(Designation.class.getName(), false).getName());

        stubClassLoader.setGenerationMode(0);
        assertEquals(G2Access.class.getName(), stubClassLoader.loadClass(G2Access.class.getName(), true).getName());
        stubClassLoader.setGenerationMode(1);
        assertEquals(G2Access.class.getName(), stubClassLoader.loadClass(G2Access.class.getName(), true).getName());
        stubClassLoader.setGenerationMode(2);
        assertEquals(G2Access.class.getName(), stubClassLoader.loadClass(G2Access.class.getName(), true).getName());
        stubClassLoader.setGenerationMode(3);
        assertEquals(G2Access.class.getName(), stubClassLoader.loadClass(G2Access.class.getName(), true).getName());
    }

    @Test(expected = ArrayIndexOutOfBoundsException.class)
    public void testLoadClassFailure1() {
        stubClassLoader.loadClass(symbolInterface, true);
    }

    @Test
    public void testLoadClassFailure2() {
        stubClassLoader.setGenerationMode(0);
        try {
            stubClassLoader.loadClass(symbolInterface, true);
        } catch (StubCreationException sce) {
            assertEquals("Interface Generation not allowed", sce.getMessage());
        }
    }

    @Test(expected = RuntimeException.class)
    public void testLoadClassFailure4() {
        stubClassLoader.setGenerationMode(1);
        stubClassLoader.loadClass(symbolInterface, true);
    }

    @Test(expected = StubCreationException.class)
    public void testLoadClassFailure3() {
        stubClassLoader.setGenerationMode(2);
        stubClassLoader.loadClass(symbolInterface, true);
    }

    @Test
    public void testToHex() {
        byte[] bytes = new byte[3];
        bytes[0] = 9;
        bytes[1] = 1;
        bytes[2] = 0;
        assertEquals("090100", StubClassLoader.toHex(bytes));
    }

    /**
     * Found Bug in the code. Null pointer in thrown at StubClassLoader
     * line#1677 because currentlyLoadingDefinitions.get (g2ClassName_) does not
     * contain Designation.class in this case. But, as per the code
     * currentlyLoadingDefinitions can be populated ONLY if second argument of
     * method in test i.e stubClassLoader.loadClass(symbol, false) is true. But,
     * that will not be the case always. Also, a very big mistake as it seems
     * is: Line#1677 can only be called if isInterface(second argument) is
     * false. Hence, non-interface cases will never pass this test!
     */
    @Test(expected = NullPointerException.class)
    public void testLoadClass2() {
        stubClassLoader.loadClass(symbol, false);
    }

    @Test
    public void test_getUserInterfaceGenerator_always_returnsGenerator() {
        // Arrange
        // No arrangement

        // Act & Assert
        assertTrue(this.stubClassLoader.getUserInterfaceGenerator() != null);
    }

    @Test
    public void test_unloadClass_always_unloadsClass() {
        // Arrange
        Symbol g2ClassName = anySymbol();

        // Act
        this.stubClassLoader.unloadClass(g2ClassName);

        // Assert
        assertFalse(this.stubClassLoader.loadedInterfaces.containsKey(g2ClassName));
        assertFalse(this.stubClassLoader.loadedStubs.containsKey(g2ClassName));
        assertFalse(this.stubClassLoader.ClassInheritancePathTable.containsKey(g2ClassName));
    }

    // Assert
    @Test(expected = UnexpectedException.class)
    public void test_generateG2MethodStubInfo_missingAttribute_Exception() {
        // Arrange
        arrangeForGenerateG2MethodStubInfo();
        Structure classInfo = new Structure();
        this.stubClassLoader.classInfoTable.put(this.className, classInfo);

        // Act
        this.stubClassLoader.generateG2MethodStubInfo(this.instanceMethods, this.staticMethods, this.className, this.classInheritancePath, this.collectedClasses, this.isInterface, this.isPseudoClass);
    }

    @Test
    public void test_generateG2MethodStubInfo_always_generatesStubInfo() throws NoSuchAttributeException {
        // Arrange
        arrangeForGenerateG2MethodStubInfo();
        Structure classInfo = new Structure();
        Sequence classInstanceMethods = createClassInstanceMethods();
        classInfo.setAttributeValue(INSTANCE_METHODS_, classInstanceMethods);
        this.stubClassLoader.classInfoTable.put(this.className, classInfo);

        // Act
        MethodInfo[] result = this.stubClassLoader.generateG2MethodStubInfo(
                this.instanceMethods,
                this.staticMethods,
                this.className,
                this.classInheritancePath,
                this.collectedClasses,
                this.isInterface,
                this.isPseudoClass);

        // Assert
        for (int idx = 0; idx < classInstanceMethods.size(); idx++) {
            Structure methodStructure = (Structure) classInstanceMethods.elementAt(idx);
            assertEquals(methodStructure.getAttributeValue(METHOD_NAME_), result[idx].G2MethodName);
            assertEquals(methodStructure.getAttributeValue(ARGUMENT_TYPES_), result[idx].getArgumentTypes());
        }
    }

    // Assert
    @Test(expected = RuntimeException.class)
    public void test_collectInheritedAttributes_missingInstanceAttributes_exception() {
        // Arrange
        Structure classInfo = new Structure();
        classInfo.setAttributeValue(CLASS_ATTRIBUTES_, new Sequence());
        this.stubClassLoader.classInfoTable.put(this.className, classInfo);

        // Act
        this.stubClassLoader.collectInheritedAttributes(this.className, false);
    }

    // Assert
    @Test(expected = RuntimeException.class)
    public void test_collectInheritedAttributes_missingClassAttributes_exception() {
        // Arrange
        Structure classInfo = new Structure();
        classInfo.setAttributeValue(INSTANCE_ATTRIBUTES_, new Sequence());
        this.stubClassLoader.classInfoTable.put(this.className, classInfo);

        // Act
        this.stubClassLoader.collectInheritedAttributes(this.className, true);
    }

    // Assert
    @Test(expected = RuntimeException.class)
    public void test_collectInheritedAttributes_classMissingInPathTable_exception() {
        // Arrange
        Structure classInfo = createClassInfo();
        this.stubClassLoader.classInfoTable.put(this.className, classInfo);
        this.stubClassLoader.ClassInheritancePathTable.put(this.className, new Symbol[0]);

        // Act
        this.stubClassLoader.collectInheritedAttributes(this.className, false);
    }

    @Test
    public void test_collectInheritedAttributes_always_returnsUniqueAttributes() throws NoSuchAttributeException {
        // Arrange
        for (boolean staticAttributes : booleanTestCases) {
            arrangeForCollectInheritedAttributes();
            this.stubClassLoader.ClassInheritancePathTable.put(this.className, this.collectedClasses);
            Sequence expectedAttributes = expectedCollectedInheritedAttributes(staticAttributes);

            // Act
            Sequence result = this.stubClassLoader.collectInheritedAttributes(this.className, staticAttributes);

            // Assert
            assertEquals(expectedAttributes.size(), result.size());
            for (Object elem : expectedAttributes) {
                Symbol expectedAttributeName = (Symbol) elem;

                boolean matched = false;
                for (Object actualElem : result) {
                    Structure actualAttribute = (Structure) actualElem;
                    if (expectedAttributeName == actualAttribute.getAttributeValue(ATTRIBUTE_NAME_)) {
                        matched = true;
                        break;
                    }
                }

                if (matched == false) {
                    fail("collectInheritedAttributes: Expected attribute '" + expectedAttributeName + "' is not returned.");
                }
            }
        }
    }

    @Test
    public void test_debugIndent_always_writesMessage() {
        // Arrange
        String message = anyString();

        // Act
        this.stubClassLoader.debugIndent(message);

        // Assert
        assertTrue(this.outContent.toString().contains(message));
    }

    @Test
    public void test_getUserPackage_packageDefined_returnsPackage() {
        // Arrange
        String userPackage = anyString();
        System.setProperty("com.gensym.class.user.package", userPackage);

        // Act & Assert
        assertEquals(userPackage, StubClassLoader.getUserPackage());
    }

    @Test
    public void test_getUserPackage_packageNotDefined_returnsDefaultPackage() {
        // Arrange
        String userPackage = "com.gensym.classes.modules";
        System.clearProperty("com.gensym.class.user.package");

        // Act & Assert
        assertEquals(userPackage, StubClassLoader.getUserPackage());
    }

    @Test
    public void test_getRealG2ClassForG2ProxyClass_inheritancePathShort_returnsNull() {
        // Arrange
        this.classInheritancePath = new Symbol[]{this.className};

        // Act & Assert
        assertNull(this.stubClassLoader.getRealG2ClassForG2ProxyClass(this.className, this.classInheritancePath));
    }

    @Test
    public void test_getRealG2ClassForG2ProxyClass_mixinClassInPath_returnsSecondClass() {
        // Arrange
        this.classInheritancePath = new Symbol[]{
                this.className,
                Symbol.intern(anyString()),
                com.gensym.jgi.G2JavaStubController.JGI_G2PROXY_MIXIN_CLASS_
        };

        // Act & Assert
        assertEquals(this.classInheritancePath[1], this.stubClassLoader.getRealG2ClassForG2ProxyClass(this.className, this.classInheritancePath));
    }

    @Test
    public void test_getRealG2ClassForG2ProxyClass_mixinClassNotInPath_returnsNull() {
        // Arrange
        this.classInheritancePath = new Symbol[]{
                this.className,
                Symbol.intern(anyString()),
                Symbol.intern(anyString())
        };

        // Act & Assert
        assertNull(this.stubClassLoader.getRealG2ClassForG2ProxyClass(this.className, this.classInheritancePath));
    }

    @Test
    public void test_isSubclassOfG2ProxyClass_isSubClass_returnsTrue() {
        // Arrange
        this.classInheritancePath = new Symbol[]{
                this.className,
                Symbol.intern(anyString()),
                com.gensym.jgi.G2JavaStubController.JGI_PROXY_MIXIN_CLASS_
        };

        // Act & Assert
        assertTrue(this.stubClassLoader.isSubclassOfG2ProxyClass(this.classInheritancePath));
    }

    @Test
    public void test_isSubclassOfG2ProxyClass_isNotSubClass_returnsFalse() {
        // Arrange
        this.classInheritancePath = new Symbol[]{
                this.className,
                Symbol.intern(anyString()),
                Symbol.intern(anyString())
        };

        // Act & Assert
        assertFalse(this.stubClassLoader.isSubclassOfG2ProxyClass(this.classInheritancePath));
    }

    @Test
    public void test_isG2ClassG2ProxyClass_isClass_returnsTrue() {
        // Arrange
        // Nothing to arrange

        // Act & Assert
        assertTrue(StubClassLoader.isG2ClassG2ProxyClass(G2JavaStubController.JGI_PROXY_MIXIN_CLASS_));
    }

    @Test
    public void test_isG2ClassG2ProxyClass_isNotClass_returnsFalse() {
        // Arrange
        // Nothing to arrange

        // Act & Assert
        assertFalse(StubClassLoader.isG2ClassG2ProxyClass(Symbol.intern(anyString())));
    }

    @Test
    public void test_isG2ClassG2EventListenerClass_isClass_returnsTrue() {
        // Arrange
        // Nothing to arrange

        // Act & Assert
        assertTrue(StubClassLoader.isG2ClassG2EventListenerClass(G2_EVENT_LISTENER_));
    }

    @Test
    public void test_isG2ClassG2EventListenerClass_isNotClass_returnsFalse() {
        // Arrange
        // Nothing to arrange

        // Act & Assert
        assertFalse(StubClassLoader.isG2ClassG2EventListenerClass(Symbol.intern(anyString())));
    }

    @Test
    public void test_isG2ListenerClass_inheritancePathEmpty_returnsFalse() {
        // Arrange
        // Nothing to arrange

        // Act
        assertFalse(StubClassLoader.isG2ListenerClass(anySymbol(), new Symbol[0]));
    }

    @Test
    public void test_isG2ListenerClass_isG2EventListenerClass_returnsFalse() {
        // Arrange
        // Nothing to arrange

        // Act
        assertFalse(StubClassLoader.isG2ListenerClass(G2_EVENT_LISTENER_, new Symbol[]{G2_EVENT_LISTENER_}));
    }

    @Test
    public void test_isG2ListenerClass_isNotInheritedFromG2EventListenerClass_returnsFalse() {
        // Arrange
        // Nothing to arrange

        // Act
        assertFalse(StubClassLoader.isG2ListenerClass(anySymbol(), new Symbol[]{anySymbol()}));
    }

    @Test
    public void test_isG2ListenerClass_isInheritedFromG2EventListenerClass_returnsFalse() {
        // Arrange
        // Nothing to arrange

        // Act
        assertTrue(StubClassLoader.isG2ListenerClass(anySymbol(), new Symbol[]{anySymbol(), G2_EVENT_LISTENER_}));
    }

    @Test
    public void test_getExternalG2ListenerClassName_always_returnsClassName() {
        // Arrange
        String className_ = StubClassLoaderTestHelper.class.getName();
        String expected = "G2_" + className_.substring(className_.lastIndexOf(".") + 1);

        // Act
        assertEquals(expected, StubClassLoader.getExternalG2ListenerClassName(className_));
    }

    @Test
    public void test_isG2ClassG2EventClass_isG2EventObject_returnsTrue() {
        // Arrange
        // Nothing to arrange

        // Act & Assert
        assertTrue(StubClassLoader.isG2ClassG2EventClass(G2_EVENT_OBJECT_));
    }

    @Test
    public void test_isG2ClassG2EventClass_isNotG2EventObject_returnsFalse() {
        // Arrange
        // Nothing to arrange

        // Act & Assert
        assertFalse(StubClassLoader.isG2ClassG2EventClass(anySymbol()));
    }

    @Test
    public void test_isG2EventClass_noInheritancePath_returnsFalse() {
        // Arrange
        this.stubClassLoader.ClassInheritancePathTable.remove(this.className);

        // Act & Assert
        assertFalse(this.stubClassLoader.isG2EventClass(this.className));
    }

    @Test
    public void test_isG2EventClass_shortInheritancePath_returnsFalse() {
        // Arrange
        this.stubClassLoader.ClassInheritancePathTable.put(this.className, new Symbol[0]);

        // Act & Assert
        assertFalse(this.stubClassLoader.isG2EventClass(this.className));
    }

    @Test
    public void test_isG2EventClass_isInheritedFromG2EventObject_returnsTrue() {
        // Arrange
        this.stubClassLoader.ClassInheritancePathTable.put(this.className, new Symbol[]{this.className, G2_EVENT_OBJECT_});

        // Act & Assert
        assertTrue(this.stubClassLoader.isG2EventClass(this.className));
    }

    @Test
    public void test_isG2EventClass_isNotInheritedFromG2EventObject_returnsFalse() {
        // Arrange
        this.stubClassLoader.ClassInheritancePathTable.put(this.className, new Symbol[]{this.className, anySymbol()});

        // Act & Assert
        assertFalse(this.stubClassLoader.isG2EventClass(this.className));
    }

    @Test
    public void test_getExternalG2EventClassName_always_returnsClassName() {
        // Arrange
        String className_ = StubClassLoaderTestHelper.class.getName();
        String expected = "G2_" + className_.substring(className_.lastIndexOf(".") + 1);

        // Act
        assertEquals(expected, StubClassLoader.getExternalG2EventClassName(className_));
    }

    @Test
    public void test_getClassManager_always_returnsClassManager() {
        // Arrange
        // Nothing to arrange

        // Act & Assert
        assertEquals(this.context.getClassManager(), this.stubClassLoader.getClassManager());
    }

    @Test
    public void test_getContext_always_returnsG2Context() {
        // Arrange
        // Nothing to arrange

        // Act & Assert
        assertEquals(this.context, this.stubClassLoader.getContext());
    }

    @Test
    public void test_setForceDownload_always_setsForceDownload() {
        for (boolean force : booleanTestCases) {
            // Arrange
            // Nothing to arrange

            // Act
            this.stubClassLoader.setForceDownload(force);

            // Assert
            assertEquals(force, this.stubClassLoader.getForceDownload());
        }
    }

    @Test
    public void test_addClassInvalidationListener_always_addsListener() {
        // Arrange
        ClassInvalidationListenerStub listener = new ClassInvalidationListenerStub();

        // Act
        this.stubClassLoader.addClassInvalidationListener(listener);

        // Assert
        this.stubClassLoader.unloadClass(this.className);
        assertEquals(1, listener.invalidatedClasses.size());
        ClassInvalidationEvent event = (ClassInvalidationEvent) listener.invalidatedClasses.elementAt(0);
        assertTrue(Arrays.asList(event.getInvalidClasses()).contains(this.className));
    }

    @Test
    public void test_addClassInvalidationListener_always_removesListener() {
        // Arrange
        ClassInvalidationListenerStub listener = new ClassInvalidationListenerStub();
        this.stubClassLoader.addClassInvalidationListener(listener);

        // Act
        this.stubClassLoader.removeClassInvalidationListener(listener);

        // Assert
        this.stubClassLoader.unloadClass(this.className);
        assertEquals(0, listener.invalidatedClasses.size());
    }

    @Test
    public void test_setGenerationMode_always_setsGenerationMode() {
        // Arrange
        int generationMode = anyInteger();

        // Act
        this.stubClassLoader.setGenerationMode(generationMode);

        // Assert
        assertEquals(generationMode, this.stubClassLoader.getGenerationMode());
    }

    @Test
    public void test_generatePseudoClassName_classNameWithinLimits_returnsSame() {
        // Arrange
        String expected = G2ClassTranslator.createJavaClassNameFromG2ClassName(this.className) + "Impl";

        // Act & Assert
        assertEquals(expected, this.stubClassLoader.generatePseudoClassName(this.className));
    }

    @Test
    public void test_generatePseudoClassName_classNameWithinLimits_returnsShortName() throws NoSuchAlgorithmException {
        // Arrange
        Symbol className_ = anyLongSymbol(FILE_NAME_LIMIT);

        // Act
        String result = this.stubClassLoader.generatePseudoClassName(className_);

        // Assert
        assertTrue(result.startsWith("Long"));
        assertTrue(result.endsWith("Impl"));
    }
}