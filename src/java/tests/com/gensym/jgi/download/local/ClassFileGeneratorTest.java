package com.gensym.jgi.download.local;

import com.gensym.classtools.*;
import com.gensym.jgi.download.ClassFileGenerationException;
import com.gensym.util.Sequence;
import org.junit.Before;
import org.junit.Test;

import java.io.IOException;
import java.util.*;

import static com.gensym.classtools.RuntimeConstants.*;
import static com.gensym.helpers.ObjectsFactory.anyBoolean;
import static com.gensym.helpers.ObjectsFactory.anyString;
import static org.junit.Assert.*;

public class ClassFileGeneratorTest extends ClassFileGeneratorTestHelper {
    @Before
    public void init() throws ClassException, IOException {
        setSystemProperties();
        initializeVariables();
        createSut();
    }

    @Test
    public void test_getClassName_always_returnsClassName() {
        // Arrange
        // Nothing to arrange

        // Act & Assert
        assertEquals(this.className.replace('.', '/'), this.sut.getClassName());
    }

    @Test
    public void test_getClassDescriptor_always_returnsDescriptor() {
        // Arrange
        // Nothing to arrange

        // Act & Assert
        assertEquals(ClassFileGenerator.getVMDescriptorForJavaType(this.className), this.sut.getClassDescriptor());
    }

    @Test
    public void test_getSuperClassName_classSpecified_returnsSuperClassName() {
        // Arrange
        // Nothing to arrange

        // Act & Assert
        assertEquals(this.superClassName, this.sut.getSuperClassName());
    }

    @Test
    public void test_getSuperClassName_classNotSpecified_returnsObject() throws ClassException {
        // Arrange
        this.superClassName = null;
        createSut();

        // Act & Assert
        assertEquals("java/lang/Object", this.sut.getSuperClassName());
    }

    @Test
    public void test_getSuperClassDescriptor_always_returnsDescriptor() {
        // Arrange
        // Nothing to arrange

        // Act & Assert
        assertEquals(ClassFileGenerator.getVMDescriptorForJavaType(this.superClassName), this.sut.getSuperClassDescriptor());
    }

    @Test
    public void test_implementInterface_always_implementsInterfaceName() throws IOException, ClassException {
        // Arrange
        String interfaceName = anyString();
        InterfaceInfo interfaceInfo = new InterfaceInfo(interfaceName);

        // Act
        this.sut.implementInterface(interfaceInfo);

        // Assert
        assertTrue(Arrays.asList(this.sut.getInterfaceNames()).contains(interfaceName));
    }

    @Test
    public void test_implementInterfaceName_always_implementsInterfaceName() throws IOException {
        // Arrange
        String interfaceName = anyString();

        // Act
        this.sut.implementInterface(interfaceName);

        // Assert
        assertTrue(Arrays.asList(this.sut.getInterfaceNames()).contains(interfaceName));
    }

    @Test
    public void test_addMethod_methodNotAdded_addsMethod() throws ClassException, IOException {
        // Arrange
        arrangeAddMethodParameters();

        // Act
        this.sut.addMethod(this.methodName, this.descriptor, this.parameterNames, this.access, this.exceptions);

        // Assert
        this.sut.writeClass();
        assertOutputStreamContains(this.methodName);
    }

    // Assert
    @Test(expected = ClassFileGenerationException.class)
    public void test_addMethod_methodAlreadyAdded_throwsException() throws ClassException, IOException {
        // Arrange
        arrangeAddMethodParameters();

        this.sut.addMethod(this.methodName, this.descriptor, this.parameterNames, this.access, this.exceptions);

        // Act
        this.sut.addMethod(this.methodName, this.descriptor, this.parameterNames, this.access, this.exceptions);
    }

    @Test
    public void test_addMethodIgnoreMergeProblems_always_addsMethod() throws ClassException, IOException {
        // Arrange
        arrangeAddMethodParameters();

        // Act
        this.sut.addMethodIgnoreMergeProblems(this.methodName, this.descriptor, this.parameterNames, this.access, this.exceptions);

        // Assert
        this.sut.writeClass();
        assertOutputStreamContains(descriptor);
        assertOutputStreamContains(this.methodName);
    }

    @Test
    public void test_addMethodIgnoreMergeProblems_methodAlreadyExists_doesNotThrow() throws ClassException, IOException {
        // Arrange
        arrangeAddMethodParameters();

        this.sut.addMethod(this.methodName, this.descriptor, this.parameterNames, this.access, this.exceptions);

        try {
            // Act
            this.sut.addMethodIgnoreMergeProblems(this.methodName, this.descriptor, this.parameterNames, this.access, this.exceptions);
        } catch (Exception ex) {
            // Assert
            fail("addMethodIgnoreMergeProblems: Duplicate method should not throw exception.");
        }
    }

    // Assert
    @Test(expected = ClassFileGenerationException.class)
    public void test_addMethodIgnoreMergeProblems_wrongDescriptor_throwsException() throws ClassException, IOException {
        // Arrange
        arrangeAddMethodParameters();
        this.descriptor = anyString();

        // Act
        this.sut.addMethodIgnoreMergeProblems(this.methodName, this.descriptor, this.parameterNames, this.access, this.exceptions);
    }

    // Assert
    @Test(expected = ClassFileGenerationException.class)
    public void test_addMethodWithBlock_nullDescriptor_throwsException() throws ClassException {
        // Arrange
        arrangeAddMethodParameters();

        // Act
        this.sut.addMethod(this.methodName, null, this.parameterNames, this.access, this.block, this.exceptions);
    }

    @Test
    public void test_addMethodWithBlock_methodNotAdded_addsMethod() throws ClassException, IOException {
        // Arrange
        arrangeAddMethodParameters();

        // Act
        this.sut.addMethod(this.methodName, this.descriptor, this.parameterNames, this.access, this.block, this.exceptions);

        // Assert
        this.sut.writeClass();
        assertOutputStreamContains(this.methodName);
    }

    // Assert
    @Test(expected = ClassFileGenerationException.class)
    public void test_addMethodWithBlock_methodAlreadyAdded_throwsException() throws ClassException, IOException {
        // Arrange
        arrangeAddMethodParameters();

        this.sut.addMethod(this.methodName, this.descriptor, this.parameterNames, this.access, this.block, this.exceptions);

        // Act
        this.sut.addMethod(this.methodName, this.descriptor, this.parameterNames, this.access, this.block, this.exceptions);
    }

    @Test
    public void test_addMethodIgnoreMergeProblemsWithBlock_always_addsMethod() throws ClassException, IOException {
        // Arrange
        arrangeAddMethodParameters();

        // Act
        this.sut.addMethodIgnoreMergeProblems(this.methodName, this.descriptor, this.parameterNames, this.access, this.block, this.exceptions);

        // Assert
        this.sut.writeClass();
        assertOutputStreamContains(this.methodName);
    }

    @Test
    public void test_addMethodIgnoreMergeProblemsWithBlock_methodAlreadyExists_doesNotThrow() throws ClassException, IOException {
        // Arrange
        arrangeAddMethodParameters();

        this.sut.addMethod(this.methodName, this.descriptor, this.parameterNames, this.access, this.block, this.exceptions);

        try {
            // Act
            this.sut.addMethodIgnoreMergeProblems(this.methodName, this.descriptor, this.parameterNames, this.access, this.block, this.exceptions);
        } catch (Exception ex) {
            // Assert
            fail("addMethodIgnoreMergeProblems: Duplicate method should not throw exception.");
        }
    }

    // Assert
    @Test(expected = ClassFileGenerationException.class)
    public void test_addMethodIgnoreMergeProblemsWithBlock_wrongDescriptor_throwsException() throws ClassException, IOException {
        // Arrange
        arrangeAddMethodParameters();
        this.descriptor = anyString();

        // Act
        this.sut.addMethodIgnoreMergeProblems(this.methodName, this.descriptor, this.parameterNames, this.access, this.block, this.exceptions);
    }

    @Test
    public void test_getWrapperClass_always_returnsCorrectClass() {
        // Arrange
        Hashtable testCases = new Hashtable();
        testCases.put("boolean", "java.lang.Boolean");
        testCases.put("char", "java.lang.Character");
        testCases.put("byte", "java.lang.Byte");
        testCases.put("short", "java.lang.Short");
        testCases.put("int", "java.lang.Integer");
        testCases.put("long", "java.lang.Long");
        testCases.put("float", "java.lang.Float");
        testCases.put("double", "java.lang.Double");
        testCases.put(anyString(), "");

        Set<String> keys = testCases.keySet();
        for (String testCase : keys) {
            // Act && Assert
            assertEquals(testCases.get(testCase), ClassFileGenerator.getWrapperClass(testCase));
        }
    }

    @Test
    public void test_getAccessorMethod_always_returnsCorrectMethod() {
        // Arrange
        Hashtable testCases = new Hashtable();
        testCases.put("boolean", "booleanValue");
        testCases.put("char", "charValue");
        testCases.put("byte", "byteValue");
        testCases.put("short", "shortValue");
        testCases.put("int", "intValue");
        testCases.put("long", "longValue");
        testCases.put("float", "floatValue");
        testCases.put("double", "doubleValue");
        testCases.put(anyString(), "");

        Set<String> keys = testCases.keySet();
        for (String testCase : keys) {
            // Act && Assert
            assertEquals(testCases.get(testCase), ClassFileGenerator.getAccessorMethod(testCase));
        }
    }

    @Test
    public void test_wrapPrimitiveIfNecessary_always_wrapsPrimitiveTypes() throws ClassException {
        // Arrange
        ArrayList<Sequence> testCases = new ArrayList<Sequence>();
        testCases.add(createSequence(Integer.TYPE.getName(), T_INT, "Ljava/lang/Integer;"));
        testCases.add(createSequence(Double.TYPE.getName(), T_DOUBLE, "Ljava/lang/Double;"));
        testCases.add(createSequence(Float.TYPE.getName(), T_FLOAT, "Ljava/lang/Float;"));
        testCases.add(createSequence(Boolean.TYPE.getName(), T_BOOLEAN, "Ljava/lang/Boolean;"));

        for (Sequence testCase : testCases) {
            ExpressionStub expression = new ExpressionStub();
            expression.setExpressionType(new Type((Integer) testCase.get(1)));

            // Act
            Expression result = ClassFileGenerator.wrapPrimitiveIfNecessary((String) testCase.get(0), expression);

            // Assert
            assertEquals(testCase.get(2).toString(), result.getExpressionType().toString());
        }
    }

    @Test
    public void test_doCast_always_castsInstance() throws ClassException {
        // Arrange
        ArrayList<Sequence> testCases = new ArrayList<Sequence>();
        testCases.add(createSequence(Integer.TYPE.getName(), T_INT, "()I"));
        testCases.add(createSequence(Double.TYPE.getName(), T_DOUBLE, "()D"));
        testCases.add(createSequence(Float.TYPE.getName(), T_FLOAT, "()F"));
        testCases.add(createSequence(Boolean.TYPE.getName(), T_BOOLEAN, "()Z"));
        String type = anyString();
        testCases.add(createSequence(type, T_ANY, "L" + type + ";"));

        for (Sequence testCase : testCases) {
            ExpressionStub expression = new ExpressionStub();
            expression.setExpressionType(new Type((Integer) testCase.get(1)));

            // Act
            Expression result = ClassFileGenerator.doCast((String) testCase.get(0), expression);

            // Assert
            assertEquals(testCase.get(2).toString(), result.getExpressionType().toString());
        }
    }

    @Test
    public void test_addField_fieldNotAdded_addsField() {
        // Arrange
        this.descriptor = "I";
        ExpressionStub initialValue = new ExpressionStub();
        initialValue.setExpressionType(new Type(T_INT));
        boolean[] isStaticTestCases = new boolean[]{false, true};
        Expression[] initialValueTestCases = new Expression[]{initialValue, null};

        for (boolean isStaticTestCase : isStaticTestCases) {
            for (Expression initialValueTestCase : initialValueTestCases) {
                String fieldName = anyString();
                int flags = ACC_PUBLIC;
                if (isStaticTestCase) {
                    flags |= ACC_STATIC;
                }

                this.access = new Access(flags);

                // Act
                this.sut.addField(fieldName, this.descriptor, this.access, initialValueTestCase, isStaticTestCase);

                // Assert
                assertTrue(this.sut.isFieldDefined(fieldName));
            }
        }
    }

    // Assert
    @Test(expected = ClassFileGenerationException.class)
    public void test_addField_fieldAlreadyAdded_throwsException() {
        // Arrange
        this.descriptor = "I";
        ExpressionStub initialValue = new ExpressionStub();
        initialValue.setExpressionType(new Type(T_INT));
        boolean isStaticTestCase = anyBoolean();

        String fieldName = anyString();
        int flags = ACC_PUBLIC;
        if (isStaticTestCase) {
            flags |= ACC_STATIC;
        }

        this.access = new Access(flags);
        this.sut.addField(fieldName, this.descriptor, this.access, initialValue, isStaticTestCase);

        // Act
        this.sut.addField(fieldName, this.descriptor, this.access, initialValue, isStaticTestCase);
    }

    @Test
    public void test_isFieldDefined_fieldNotDefined_returnsFalse() {
        // Arrange
        // Nothing to arrange

        // Assert
        assertFalse(this.sut.isFieldDefined(anyString()));
    }

    @Test
    public void test_getFullyQualifiedInterfaceName_isStub_returnsInterface() throws ClassException {
        // Arrange
        this.className = anyString() + "Impl";
        createSut();
        String expected = this.className.replace("Impl", "");

        // Act & Assert
        assertEquals(expected, this.sut.getFullyQualifiedInterfaceName());
    }

    @Test
    public void test_getFullyQualifiedInterfaceName_isNotStub_returnsEmptyString() throws ClassException {
        // Arrange
        this.className = anyString();
        createSut();

        // Act & Assert
        assertEquals("", this.sut.getFullyQualifiedInterfaceName());
    }
}
