package com.gensym.jgi;

import com.gensym.jgi.download.G2StubCreationException;
import com.gensym.util.*;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import static com.gensym.helpers.ObjectsFactory.anyBoolean;
import static org.junit.Assert.assertEquals;

public class G2JavaStubGeneratorTest {
    private static final Symbol CLASS_NAME = Symbol.intern("CLASS_NAME");
    private static final Symbol BEAN_INFO_STUBS = Symbol.intern("BEANINFO_STUBS");
    private static final Symbol CONSTRUCTOR_STUBS = Symbol.intern("CONSTRUCTOR_STUBS");
    private static final Symbol BEAN_INFO_PROPERTIES = Symbol.intern("BEANINFO_PROPERTIES");
    private static final boolean[] BOOLEAN_TEST_CASES = new boolean[] { false, true };

    private boolean recurse;
    private boolean forG2BeanWrapper;
    private Class classObj;
    private G2JavaStubGenerator sut;
    private String className;
    private Symbol classNameSymbol;
    private BeanInfoPropertiesHelper beanInfoPropertiesHelper;
    private WrapperStubsHelper wrapperStubsHelper;

    @Before
    public void init() {
        createSut();
        initializeFields();
    }

    @After
    public void teardown() {

    }

    @Test
    public void test_findDependentClasses_always_returnsClasses() throws G2StubCreationException, ClassNotFoundException {
        // Arrange
        Sequence expected = new JavaClassStubGeneratorHierarchy().detailAncestry(this.classObj);

        // Act
        Sequence result = this.sut.findDependentClasses(this.className, this.classObj, this.recurse);

        // Assert
        assertEquals(expected.size(), result.size());
    }

    @Test
    public void test_getG2StubDetailsForJavaClass_always_returnsDetails() throws G2StubCreationException, ClassNotFoundException, NtwIllegalArgumentException, NoSuchAttributeException {
        // Arrange
        for (boolean recursive : BOOLEAN_TEST_CASES) {
            for (boolean beanWrapper : BOOLEAN_TEST_CASES) {
                this.recurse = recursive;
                this.forG2BeanWrapper = beanWrapper;
                Structure expectedDetails = expectedStubDetails();

                // Act
                Structure result = this.sut.getG2StubDetailsForJavaClass(this.className, this.classObj, this.classNameSymbol, this.recurse, this.forG2BeanWrapper);

                // Assert
                assertEquals(expectedDetails.getAttributeValue(CLASS_NAME), result.getAttributeValue(CLASS_NAME));
                assertEquals(expectedDetails.getAttributeValue(BEAN_INFO_STUBS), result.getAttributeValue(BEAN_INFO_STUBS));
                assertEquals(expectedDetails.getAttributeValue(CONSTRUCTOR_STUBS), result.getAttributeValue(CONSTRUCTOR_STUBS));
                assertEquals(expectedDetails.getAttributeValue(BEAN_INFO_PROPERTIES), result.getAttributeValue(BEAN_INFO_PROPERTIES));
            }
        }
    }

    @Test
    public void test_getG2StubsForBeanInfo_always_returnsStubs() throws G2StubCreationException, ClassNotFoundException, NtwIllegalArgumentException {
        // Arrange
        for (boolean recursive : BOOLEAN_TEST_CASES) {
            this.recurse = recursive;
            Sequence expected = this.beanInfoPropertiesHelper.expectedG2Stubs(this.classObj, this.classNameSymbol, this.recurse);

            // Act
            Sequence result = this.sut.getG2StubsForBeanInfo(this.classObj, this.classNameSymbol, this.recurse);

            // Assert
            assertEquals(expected.size(), result.size());
            for(int idx = 0; idx < expected.size(); idx++) {
                Structure actualStructure = (Structure)result.elementAt(idx);
                Structure expectedStructure = (Structure)expected.elementAt(idx);
                assertEquals(expectedStructure, actualStructure);
            }
        }
    }

    @Test
    public void test_getG2StubsForWrapper_always_returnsStubs() throws NtwIllegalArgumentException, G2StubCreationException, ClassNotFoundException {
        // Arrange
        for (boolean recursive : BOOLEAN_TEST_CASES) {
            this.recurse = recursive;
            Sequence expected = this.wrapperStubsHelper.expectedStubs(this.classObj, this.classNameSymbol, this.recurse);

            // Act
            Sequence result = this.sut.getG2StubsForWrapper(this.classObj, this.classNameSymbol, this.recurse);

            // Assert
            assertEquals(expected.size(), result.size());
            for(int idx = 0; idx < expected.size(); idx++) {
                Structure actualStructure = (Structure)result.elementAt(idx);
                Structure expectedStructure = (Structure)expected.elementAt(idx);
                assertEquals(expectedStructure, actualStructure);
            }
        }
    }

    private Structure expectedStubDetails() throws NtwIllegalArgumentException, G2StubCreationException, ClassNotFoundException {
        Symbol[] keys = new Symbol[4];
        Object[] values = new Object[4];

        keys[0] = CLASS_NAME;
        values[0] = this.classNameSymbol;

        keys[1] = BEAN_INFO_STUBS;
        values[1] = forG2BeanWrapper
                        ? this.sut.getG2StubsForWrapper(this.classObj, this.classNameSymbol, recurse)
                        : this.sut.getG2StubsForBeanInfo(this.classObj, this.classNameSymbol, recurse);

        keys[2] = CONSTRUCTOR_STUBS;
        values[2] = this.sut.getG2StubsForConstructors(this.classObj, this.classNameSymbol);

        keys[3] = BEAN_INFO_PROPERTIES;
        values[3] = this.sut.getG2BeanInfoProperties(this.classObj, this.classNameSymbol, recurse);

        return new Structure(keys, values);
    }

    protected void createSut() {
        this.sut = new G2JavaStubGenerator();
    }

    protected void initializeFields() {
        this.classObj = G2JavaStubGeneratorTestHelperWithLargeNameToVerifyDifferentTestScenariosIncludingOneHundredAndFortyCharactersLongConstructorScenario.class;
        this.className = G2JavaStubGeneratorTestHelperWithLargeNameToVerifyDifferentTestScenariosIncludingOneHundredAndFortyCharactersLongConstructorScenario.class.getName();
        this.classNameSymbol = Symbol.intern(this.className);
        this.forG2BeanWrapper = anyBoolean();
        this.recurse = anyBoolean();

        this.beanInfoPropertiesHelper = new BeanInfoPropertiesHelper();
        this.wrapperStubsHelper = new WrapperStubsHelper();
    }
}
