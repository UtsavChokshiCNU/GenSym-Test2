package com.gensym.jgi.download;

import com.gensym.util.*;
import org.junit.Before;
import org.junit.Test;
import org.mockito.Matchers;
import org.mockito.invocation.InvocationOnMock;
import org.mockito.stubbing.Answer;

import java.io.ByteArrayOutputStream;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.nio.charset.Charset;
import java.util.Collections;
import java.util.Enumeration;

import static com.gensym.jgi.download.ExtendedTypeSymbols.FLOAT_OR_NULL_;
import static com.gensym.jgi.download.ExtendedTypeSymbols.INTEGER_OR_NULL_;
import static com.gensym.jgi.download.ExtendedTypeSymbols.TRUTH_VALUE_OR_NULL_;
import static com.gensym.util.symbol.G2TypeSymbols.*;
import static org.junit.Assert.*;
import static org.powermock.api.mockito.PowerMockito.*;

public class MethodInfoTest {
    private static int lastInteger = 1;
    private static Sequence g2EventClasses;
    protected static final Symbol[] knownG2Types = new Symbol[]{ITEM_OR_VALUE_,
            VALUE_,
            SEQUENCE_,
            STRUCTURE_,
            TRUTH_VALUE_,
            QUANTITY_,
            INTEGER_,
            FLOAT_,
            TEXT_,
            SYMBOL_,
            TRUTH_VALUE_OR_NULL_,
            INTEGER_OR_NULL_,
            FLOAT_OR_NULL_
    };

    private boolean isStatic;
    private MethodInfo sut;
    private Symbol g2MethodName;
    private Sequence g2ArgumentTypes;
    private Sequence g2ResultTypes;
    private String g2MethodSource;
    private Symbol definingG2Class;
    private Symbol absoluteG2ClassReference;
    private StubClassLoader stubClassLoader;

    @Before
    public void setup() {
        isStatic = anyBoolean();
        g2MethodName = createSymbol();
        g2ResultTypes = createSymbolSequence();
        g2MethodSource = anyString();
        definingG2Class = createSymbol();
        absoluteG2ClassReference = createSymbol();
        stubClassLoader = createStubClassLoader();
        g2EventClasses = new Sequence();

        g2ArgumentTypes = new Sequence();
        Collections.addAll(g2ArgumentTypes, knownG2Types);

        createSut();
    }

    @Test
    public void test_instance_always_setsProperties() {
        // Arrange
        // Nothing to arrange

        // Act
        createSut();

        // Assert
        assertEquals(g2MethodName, this.sut.getG2MethodName());
        assertEquals(definingG2Class, this.sut.getDefiningG2Class());
        assertEquals(absoluteG2ClassReference, this.sut.getAbsoluteG2ClassReference());
        assertEquals(g2MethodSource, this.sut.getG2MethodSource());
        assertEquals(g2ArgumentTypes, this.sut.getArgumentTypes());
        assertEquals(g2ResultTypes, this.sut.getResultTypes());
        assertEquals(G2ClassTranslator.createJavaNameFromG2Name(g2MethodName), this.sut.getJavaMethodName());
    }

    @Test
    public void test_instance_isStatic_doesNotSetThisArgument() {
        // Arrange
        // Nothing to arrange

        // Act
        isStatic = true;
        g2MethodSource = "";
        createSut();

        // Assert
        assertFalse(this.sut.getArgumentNames().firstElement().equals("this"));
    }

    @Test
    public void test_instance_isNotStatic_setsThisArgument() {
        // Arrange
        // Nothing to arrange

        // Act
        isStatic = false;
        g2MethodSource = "";
        createSut();

        // Assert
        assertEquals("this", this.sut.getArgumentNames().firstElement());
    }

    @Test
    public void test_instance_isAddListenerMethod_SetsIsAddEventListener() {
        // Arrange
        g2ResultTypes.clear();
        while (g2ArgumentTypes.size() > 1) {
            g2ArgumentTypes.removeElementAt(1);
        }

        String methodName = "ANY-EVENT-LISTENER";
        g2MethodName = Symbol.intern("Add-" + methodName);
        g2ArgumentTypes.add(Symbol.intern(methodName));

        // Act
        createSut();

        // Assert
        assertTrue(this.sut.isAddListenerMethod());
    }

    @Test
    public void test_instance_isRemoveListenerMethod_SetsIsRemoveEventListener() {
        // Arrange
        g2ResultTypes.clear();
        while (g2ArgumentTypes.size() > 1) {
            g2ArgumentTypes.removeElementAt(1);
        }

        String methodName = "ANY-EVENT-LISTENER";
        g2MethodName = Symbol.intern("Remove-" + methodName);
        g2ArgumentTypes.add(Symbol.intern(methodName));

        // Act
        createSut();

        // Assert
        assertTrue(this.sut.isRemoveListenerMethod());
    }

    @Test
    public void test_getMethodSignatureAsSequence_noArgument_retsEmptySeq() {
        // Arrange
        String signature = anyString();

        // Act & Assert
        assertEquals(0, MethodInfo.getMethodSignatureAsSequence(signature).size());
    }

    @Test
    public void test_getMethodSignatureAsSequence_always_retsMethodSig() {
        // Arrange
        String methodName = "methodName";
        String argument1 = "argument1";
        String argument2 = "argument2";
        String signature = methodName + "(\"" + argument1 + "\", \"" + argument2 + "\")";

        // Act
        Sequence result = MethodInfo.getMethodSignatureAsSequence(signature);

        // Assert
        assertEquals(3, result.size());
        assertEquals("", result.elementAt(0));
        assertEquals(methodName, result.elementAt(1));
        assertEquals("\"" + argument1 + "\"", result.elementAt(2));
    }

    @Test
    public void test_generateInterfaceComment_emptyResultTypes_generatesComment() {
        // Arrange
        g2ResultTypes.clear();
        isStatic = false;
        createSut();

        // Act & Assert
        assertEquals(expectedInterfaceComment(), this.sut.generateInterfaceComment());
    }

    @Test
    public void test_generateInterfaceComment_singleResultType_generatesComment() {
        // Arrange
        g2ResultTypes.clear();
        g2ResultTypes.add(createSymbol());
        isStatic = false;
        createSut();

        // Act & Assert
        assertEquals(expectedInterfaceComment(), this.sut.generateInterfaceComment());
    }

    @Test
    public void test_generateInterfaceComment_multiResultTypes_generatesComment() {
        // Arrange
        g2ResultTypes = createSymbolSequence();
        isStatic = false;
        createSut();

        // Act & Assert
        assertEquals(expectedInterfaceComment(), this.sut.generateInterfaceComment());
    }

    @Test
    public void test_getJavaReturnType_emptyResultTypes_retsVoid() {
        // Arrange
        g2ResultTypes.clear();
        createSut();
        this.sut.setDebug(true);

        // Act & Assert
        assertEquals("void", this.sut.getJavaReturnType());
    }

    @Test
    public void test_getJavaReturnType_singleResultTypes_retsResultType() {
        // Arrange
        g2ResultTypes.clear();
        g2ResultTypes.add(Symbol.intern("string"));
        createSut();
        this.sut.setDebug(true);

        // Act & Assert
        assertEquals("string", this.sut.getJavaReturnType());
    }

    @Test
    public void test_getJavaReturnType_multiResultTypes_retsSequence() {
        // Arrange
        g2ResultTypes.clear();
        g2ResultTypes.add(Symbol.intern("string"));
        g2ResultTypes.add(Symbol.intern("int"));
        createSut();
        this.sut.setDebug(true);

        // Act & Assert
        assertEquals("com.gensym.util.Sequence", this.sut.getJavaReturnType());
    }

    @Test
    public void test_generateMethodInterface_listenerInterfaceNotSet_retsInterface() {
        // Arrange
        isStatic = false;
        boolean externalListenerInterface = anyBoolean();
        createSut();
        ClassGenerationContext context = createClassGenerationContext();

        // Act & Assert
        assertEquals(
                expectedMethodInterface(context, false, externalListenerInterface),
                this.sut.generateMethodInterface(context, false, externalListenerInterface));
    }

    @Test
    public void test_generateMethodInterface_listenerInterfaceIsSet_retsInterface() {
        // Arrange
        isStatic = false;
        boolean externalListenerInterface = anyBoolean();
        createSut();
        ClassGenerationContext context = createClassGenerationContext();

        // Act & Assert
        assertEquals(
                expectedMethodInterface(context, true, externalListenerInterface),
                this.sut.generateMethodInterface(context, true, externalListenerInterface));
    }

    @Test
    public void test_generateMethodInterface_extListenerInterfaceNotSet_retsInterface() {
        // Arrange
        isStatic = false;
        boolean generateExternalAddRemoveListenerInterface = anyBoolean();
        createSut();
        ClassGenerationContext context = createClassGenerationContext();

        // Act & Assert
        assertEquals(
                expectedMethodInterface(context, generateExternalAddRemoveListenerInterface, false),
                this.sut.generateMethodInterface(context, generateExternalAddRemoveListenerInterface, false));
    }

    @Test
    public void test_generateMethodInterface_extListenerInterfaceIsSet_retsInterface() {
        // Arrange
        isStatic = false;
        boolean generateExternalAddRemoveListenerInterface = anyBoolean();

        for (Object argType : g2ArgumentTypes) {
            g2EventClasses.add(getMethodG2Type(argType));
        }

        createSut();
        ClassGenerationContext context = createClassGenerationContext();

        // Act & Assert
        assertEquals(
                expectedMethodInterface(context, generateExternalAddRemoveListenerInterface, true),
                this.sut.generateMethodInterface(context, generateExternalAddRemoveListenerInterface, true));
    }

    @Test
    public void test_generateMethodInterface_noResultType_retsInterface() {
        // Arrange
        isStatic = false;
        boolean generateExternalAddRemoveListenerInterface = anyBoolean();
        boolean externalListenerInterface = anyBoolean();
        g2ResultTypes.clear();
        createSut();
        ClassGenerationContext context = createClassGenerationContext();

        // Act & Assert
        assertEquals(
                expectedMethodInterface(context, generateExternalAddRemoveListenerInterface, externalListenerInterface),
                this.sut.generateMethodInterface(context, generateExternalAddRemoveListenerInterface, externalListenerInterface));
    }

    @Test
    public void test_generateMethodInterface_singleResultType_retsInterface() {
        // Arrange
        isStatic = false;
        boolean generateExternalAddRemoveListenerInterface = anyBoolean();
        boolean externalListenerInterface = anyBoolean();
        g2ResultTypes.clear();
        g2ResultTypes.add(Symbol.intern("String"));
        createSut();
        ClassGenerationContext context = createClassGenerationContext();

        // Act & Assert
        assertEquals(
                expectedMethodInterface(context, generateExternalAddRemoveListenerInterface, externalListenerInterface),
                this.sut.generateMethodInterface(context, generateExternalAddRemoveListenerInterface, externalListenerInterface));
    }

    @Test
    public void test_generateMethodInterface_isAddListener_retsInterface() {
        // Arrange
        isStatic = false;
        g2ResultTypes.clear();
        while (g2ArgumentTypes.size() > 1) {
            g2ArgumentTypes.removeElementAt(1);
        }

        String methodName = "ANY-EVENT-LISTENER";
        g2MethodName = Symbol.intern("Add-" + methodName);
        g2ArgumentTypes.add(Symbol.intern(methodName));
        createSut();
        boolean generateExternalAddRemoveListenerInterface = anyBoolean();
        boolean externalListenerInterface = anyBoolean();
        ClassGenerationContext context = createClassGenerationContext();

        // Act & Assert
        assertEquals(
                expectedMethodInterface(context, generateExternalAddRemoveListenerInterface, externalListenerInterface),
                this.sut.generateMethodInterface(context, generateExternalAddRemoveListenerInterface, externalListenerInterface));
    }

    @Test
    public void test_generateMethodInterface_isRemoveListener_retsInterface() {
        // Arrange
        isStatic = false;
        g2ResultTypes.clear();
        while (g2ArgumentTypes.size() > 1) {
            g2ArgumentTypes.removeElementAt(1);
        }

        String methodName = "ANY-EVENT-LISTENER";
        g2MethodName = Symbol.intern("Remove-" + methodName);
        g2ArgumentTypes.add(Symbol.intern(methodName));
        createSut();
        boolean generateExternalAddRemoveListenerInterface = anyBoolean();
        boolean externalListenerInterface = anyBoolean();
        ClassGenerationContext context = createClassGenerationContext();

        // Act & Assert
        assertEquals(
                expectedMethodInterface(context, generateExternalAddRemoveListenerInterface, externalListenerInterface),
                this.sut.generateMethodInterface(context, generateExternalAddRemoveListenerInterface, externalListenerInterface));
    }

    @Test
    public void test_setActive_isSetActive_setAsActive() {
        // Arrange
        // Nothing to arrange

        // Act
        this.sut.setActive(true);

        // Assert
        assertTrue(this.sut.isActive());
    }

    @Test
    public void test_setActive_isNotSetActive_setAsNotActive() {
        // Arrange
        // Nothing to arrange

        // Act
        this.sut.setActive(false);

        // Assert
        assertFalse(this.sut.isActive());
    }

    @Test
    public void test_getArgumentNamesAsStrings_always_retsArgNames() {
        // Arrange
        boolean[] testCases = new boolean[]{false, true};
        for (boolean testCast : testCases) {
            isStatic = testCast;
            createSut();
            String[] expected = expectedArgumentNames();

            // Act
            String[] result = this.sut.getArgumentNamesAsStrings();

            // Assert
            assertEquals(expected.length, result.length);
            for (int idx = 0; idx < expected.length; idx++) {
                assertEquals(expected[idx], result[idx]);
            }
        }
    }

    @Test
    public void test_getAllArgumentNamesAsStrings_always_returnsArgNames() {
        // Arrange
        String[] expected = expectedAllArgumentNames();

        // Act
        String[] result = this.sut.getAllArgumentNamesAsStrings();

        // Assert
        assertEquals(expected.length, result.length);
        for (int idx = 0; idx < expected.length; idx++) {
            assertEquals(expected[idx], result[idx]);
        }
    }

    @Test
    public void test_generateRpcDeclarationName_always_retsDeclarationName() {
        // Arrange
        Symbol[] testCases = new Symbol[]{null, createSymbol()};

        for (Symbol testCase : testCases) {
            absoluteG2ClassReference = testCase;
            createSut();

            // Act & Assert
            assertEquals(expectedRpcDeclarationName(), this.sut.generateRPCDeclarationName());
        }
    }

    @Test
    public void test_generateRPCDeclarartion_always_retsDeclaration() {
        // Arrange
        Symbol[] testCases = new Symbol[]{null, createSymbol()};

        for (Symbol testCase : testCases) {
            absoluteG2ClassReference = testCase;
            createSut();

            // Act & Assert
            assertEquals(expectedRPCDeclaration(), this.sut.generateRPCDeclarartion());
        }
    }

    @Test
    public void test_generateImplementationDeclarations_always_retsImpDeclarations() {
        // Arrange
        String expected = "private static String NoBodyExceptionString = \"This method has no implementation for local access\";";

        // Act & Assert
        assertEquals(expected, MethodInfo.generateImplementationDeclarations());
    }

    @Test
    public void test_generateMethodImplementation_always_retsMethodImplementation() {
        // Arrange
        boolean[] testCases = new boolean[]{false, true};

        for (boolean isStaticTestCase : testCases) {
            isStatic = isStaticTestCase;
            createSut();

            for (boolean testCase : testCases) {
                ByteArrayOutputStream outputStream = new ByteArrayOutputStream();
                StubGenerationContext context = createStubGenerationContext(outputStream);
                String overrideMethodBody = anyString();

                // Act
                this.sut.generateMethodImplementation(context, overrideMethodBody, testCase);

                // Assert
                assertEquals(expectedMethodImplementation(context, overrideMethodBody, testCase), outputStream.toString());
                outputStream.reset();
            }
        }
    }

    @Test
    public void test_generateMethodImplementation_isAddEvtListener_retsCorrectImpl() {
        // Arrange
        isStatic = false;
        g2ResultTypes.clear();
        while (g2ArgumentTypes.size() > 1) {
            g2ArgumentTypes.removeElementAt(1);
        }

        String methodName = "ANY-EVENT-LISTENER";
        g2MethodName = Symbol.intern("Add-" + methodName);
        g2ArgumentTypes.add(Symbol.intern(methodName));

        ByteArrayOutputStream outputStream = new ByteArrayOutputStream();
        StubGenerationContext context = createStubGenerationContext(outputStream);
        String overrideMethodBody = anyString();
        createSut();

        // Act
        this.sut.generateMethodImplementation(context, overrideMethodBody, true);

        // Assert
        assertEquals(expectedMethodImplementation(context, overrideMethodBody, true), outputStream.toString());
    }

    @Test
    public void test_generateMethodImplementation_singleRetType_retsCorrectImpl() {
        // Arrange
        ByteArrayOutputStream outputStream = new ByteArrayOutputStream();
        StubGenerationContext context = createStubGenerationContext(outputStream);
        String overrideMethodBody = anyString();

        g2ResultTypes.clear();
        g2ResultTypes.add(knownG2Types[0]);
        isStatic = false;

        createSut();

        // Act
        this.sut.generateMethodImplementation(context, overrideMethodBody, false);

        // Assert
        assertEquals(expectedMethodImplementation(context, overrideMethodBody, false), outputStream.toString());
    }

    @Test
    public void test_generateMethodImplementation_noOverrideBody_retsCorrectImpl() {
        // Arrange
        ByteArrayOutputStream outputStream = new ByteArrayOutputStream();
        StubGenerationContext context = createStubGenerationContext(outputStream);

        createSut();

        // Act
        this.sut.generateMethodImplementation(context, null, false);

        // Assert
        assertEquals(expectedMethodImplementation(context, null, false), outputStream.toString());
    }

    @Test
    public void test_getMethodType_structure_retsMethodType() throws NoSuchAttributeException {
        // Arrange
        ClassGenerationContext context = createClassGenerationContext();
        Structure type = createStructure();

        // Act & Assert
        assertEquals(
                context.getJavaTypeNameForG2Type((Symbol) type.getAttributeValue(CLASS_)),
                MethodInfo.getMethodType(context, type));
    }

    // Assert
    @Test(expected = RuntimeException.class)
    public void test_getMethodType_exceptionThrown_throwsException() throws NoSuchAttributeException {
        // Arrange
        ClassGenerationContext context = createClassGenerationContext();
        Structure type = createStructure();
        when(type.getAttributeValue(Matchers.any(Symbol.class))).thenThrow(new NoSuchAttributeException());

        // Act
        MethodInfo.getMethodType(context, type);
    }

    @Test
    public void test_setArgumentNames_always_setsArgs() {
        // Arrange
        String signature = anyString() + "( \"anyArgument\" , " + anyInteger() + " );";

        // Act
        this.sut.setArgumentNames(signature);

        // Assert
        assertTrue(this.sut.getArgumentNames().size() > 0);
    }

    // ---- Helper Methods ----

    private static boolean anyBoolean() {
        return lastInteger++ % 2 == 0;
    }

    private static int anyInteger() {
        return lastInteger++;
    }

    private static String anyString() {
        return "String " + lastInteger++;
    }

    private static Sequence createSymbolSequence() {
        Sequence sequence = new Sequence();
        sequence.add(createSymbol());
        sequence.add(createSymbol());
        sequence.add(createSymbol());
        return sequence;
    }

    private static StubClassLoader createStubClassLoader() {
        StubClassLoader loader = mock(StubClassLoader.class);

        mockStatic(StubClassLoader.class, new Answer() {
            @Override
            public Object answer(InvocationOnMock invocation) throws Throwable {
                String g2ListenerName = invocation.getArgumentAt(0, String.class);
                return g2ListenerName + " External G2 Listener Class Name";
            }
        });

        when(loader.isG2EventClass(Matchers.any(Symbol.class)))
                .then(new Answer<Object>() {
                    @Override
                    public Object answer(InvocationOnMock invocation) throws Throwable {
                        Symbol className = invocation.getArgumentAt(0, Symbol.class);
                        return g2EventClasses.contains(className);
                    }
                });

        return loader;
    }

    private static Symbol createSymbol() {
        return createSymbol(anyString());
    }

    private static Symbol createSymbol(String symValue) {
        return Symbol.intern(symValue);
    }

    private static String getMethodG2TypeWithClass(Object type) {

        if (type instanceof com.gensym.util.Structure) {
            try {
                return "CLASS " + ((Structure) type).getAttributeValue(CLASS_).toString();
            } catch (NoSuchAttributeException e) {
                throw new RuntimeException("Expected to find CLASS attribute in method result types");
            }
        } else {
            return type.toString();
        }
    }

    private static Symbol getMethodG2Type(Object type) {

        if (type instanceof com.gensym.util.Structure) {
            try {
                return ((Symbol) ((Structure) type).getAttributeValue(CLASS_));
            } catch (NoSuchAttributeException e) {
                throw new RuntimeException("Expected to find CLASS attribute in method result types");
            }
        } else {
            return ((Symbol) type);
        }
    }

    private static ClassGenerationContext createClassGenerationContext() {
        ClassGenerationContext context = mock(ClassGenerationContext.class);

        when(context.ensureLegalMethodName(Matchers.anyString()))
                .then(new Answer<Object>() {
                    @Override
                    public Object answer(InvocationOnMock invocation) throws Throwable {
                        String origName = invocation.getArgumentAt(0, String.class);
                        return origName + " Ensured Legal Method Name";
                    }
                });

        when(context.getJavaTypeNameForG2Type(Matchers.any(Symbol.class)))
                .then(new Answer<Object>() {
                    @Override
                    public Object answer(InvocationOnMock invocation) throws Throwable {
                        Symbol g2TypeName = invocation.getArgumentAt(0, Symbol.class);
                        return g2TypeName.toString() + " Java Type Name For G2 Type";
                    }
                });

        return context;
    }

    private static String getFullQExternalG2EventClassName(String className) {
        int dotPos = className.lastIndexOf(".");
        if (dotPos > 1) {
            return className.substring(0, dotPos) + ".G2_" + className.substring(dotPos + 1);
        }

        return "G2_" + className;
    }

    private static String indentStr(int indent) {
        StringBuilder indentString = new StringBuilder();

        for (int i = 0; i < indent; i++) {
            indentString.append(" ");
        }

        return indentString.toString();
    }

    private static Structure createStructure() throws NoSuchAttributeException {
        Structure model = mock(Structure.class);

        when(model.getAttributeValue(CLASS_)).thenReturn(knownG2Types[0]);

        return model;
    }

    private String expectedMethodInterface(
            ClassGenerationContext context,
            boolean generateExternalAddRemoveListenerInterface,
            boolean externalListenerInterface) {
        int i = 0;
        boolean ignoreFirst = false;
        String javaListenerClassName = null;

        StringBuilder argStrBuf = new StringBuilder(100);

        if (this.sut.isStatic()) {
            argStrBuf.append("G2Access context, int timeout");
            i = 2;
        } else {
            ignoreFirst = true;
        }

        Enumeration names = this.sut.getArgumentNames().elements();
        for (Enumeration args = this.sut.getArgumentTypes().elements();
             args.hasMoreElements();
             i++) {
            if (ignoreFirst) {
                args.nextElement();
                names.nextElement();
                ignoreFirst = false;
                i--;
                continue;
            }
            if (i > 0) {
                argStrBuf.append(",");
            }
            Object argType = args.nextElement();
            String argName = (String) names.nextElement();
            String argJavaType = getMethodType(context, argType);

            if (i == 0 && generateExternalAddRemoveListenerInterface) {
                argJavaType = StubClassLoader.getExternalG2ListenerClassName(argJavaType);
                javaListenerClassName = argJavaType;
            }

            if (externalListenerInterface) {
                if (stubClassLoader.isG2EventClass(getMethodG2Type(argType))) {
                    argJavaType = getFullQExternalG2EventClassName(argJavaType);
                }
            }

            argStrBuf.append(argJavaType).append(" ").append(argName);
        }


        String resultType;

        int numResultTypes = g2ResultTypes.size();
        if (numResultTypes == 0) {
            resultType = "void";
        } else if (numResultTypes == 1) {
            resultType = MethodInfo.getMethodType(context, g2ResultTypes.elementAt(0));

        } else {
            resultType = context.getJavaTypeNameForG2Type(SEQUENCE_);
        }


        String mName = G2ClassTranslator.createJavaNameFromG2Name(g2MethodName);
        mName = context.ensureLegalMethodName(mName);
        if (generateExternalAddRemoveListenerInterface && javaListenerClassName != null) {
            if (this.sut.isAddListenerMethod()) {
                mName = "add" + javaListenerClassName;
            } else if (this.sut.isRemoveListenerMethod()) {
                mName = "remove" + javaListenerClassName;
            }
        }

        return "public " +
                (isStatic ? "static " : " ") +
                resultType + " " +
                mName +
                "(" + argStrBuf.toString() + ") throws G2AccessException";
    }

    private static String getMethodType(ClassGenerationContext classGenerationContext, Object type) {
        if (type instanceof com.gensym.util.Structure) {
            try {
                return classGenerationContext.getJavaTypeNameForG2Type((Symbol) ((Structure) type).getAttributeValue(CLASS_));
            } catch (NoSuchAttributeException e) {
                throw new RuntimeException("Expected to find CLASS attribute in method result types");
            }
        } else {
            return classGenerationContext.getJavaTypeNameForG2Type((Symbol) type);
        }
    }

    private static StubGenerationContext createStubGenerationContext(OutputStream outputStream) {
        boolean isInterface = anyBoolean();
        String packageName = anyString();
        String className = anyString();
        String javaClassName = anyString();
        ClassNameMapper nameMapper = new ClassNameMapperStub();

        return new StubGenerationContext(outputStream, isInterface, packageName, className, javaClassName, nameMapper);
    }

    private String expectedMethodImplementation(
            StubGenerationContext context,
            String overrideMethodBody,
            boolean opAddRemoveInterface) {
        ByteArrayOutputStream stream = new ByteArrayOutputStream();
        PrintWriter output = new PrintWriter(new OutputStreamWriter(stream, Charset.defaultCharset()), true);
        output.println("{");
        int indent = 2;

        if (isStatic) {
            output.print(indentStr(indent));
            output.println("if (context == null) {");
        } else {
            output.print(indentStr(indent));
            output.println("if (isByHandle()) {");
        }

        indent += 2;

        Sequence argumentNames = this.sut.getArgumentNames();
        if (opAddRemoveInterface) {
            String firstArg = (String) argumentNames.elementAt(1);

            Symbol argG2Type = getMethodG2Type(g2ArgumentTypes.elementAt(1));

            if (this.sut.isAddListenerMethod()) {
                String _addJavaListenerMethodName = "G2JavaStubController.getG2JavaStubController().addJavaListenerToG2EventSource";
                output.print(indentStr(indent));
                output.println(_addJavaListenerMethodName + "(this,");
            } else {
                String _removeJavaListenerMethodName = "G2JavaStubController.getG2JavaStubController().removeJavaListenerFromG2EventSource";
                output.print(indentStr(indent));
                output.println(_removeJavaListenerMethodName + "(this,");
            }

            indent += 10;
            output.print(indentStr(indent));
            output.println(expectedRpcDeclarationName() + ",");
            output.print(indentStr(indent));
            output.println("\"" + context.getPackageName() + "." + this.sut.listenerClassName + "\",");
            output.print(indentStr(indent));
            output.println("Symbol.intern(\"" + argG2Type + "\"),");
            output.print(indentStr(indent));
            output.println(firstArg + ");");
            indent -= 10;
        } else {
            output.print(indentStr(indent));
            output.println("java.lang.Object result;");
            output.print(indentStr(indent));
            output.print("java.lang.Object[] args = new java.lang.Object[] {");

            int j;

            String arg_name;
            Enumeration args = g2ArgumentTypes.elements();
            j = 0;
            for (Enumeration e = argumentNames.elements(); e.hasMoreElements(); j++) {
                arg_name = (String) e.nextElement();
                if (j > 0) {
                    output.print(",");
                }

                output.print(StubGenerationContext.codeToMakeObject(arg_name, getMethodType(context, args.nextElement())));
            }

            output.println("};");

            if (isStatic) {
                output.print(indentStr(indent));
                output.print("result = (java.lang.Object)context.callRPC");
            } else {
                output.print(indentStr(indent));
                output.print("result = (java.lang.Object)callRPC");
            }

            output.print("(" + expectedRpcDeclarationName() + ", args");

            if (isStatic) {
                output.print(", timeout");
            }

            output.println(");");

            int numResultTypes = g2ResultTypes.size();
            String resultType;
            if (numResultTypes > 0) {
                if (numResultTypes == 1) {
                    resultType = getMethodType(context, g2ResultTypes.elementAt(0));
                } else {
                    resultType = context.getJavaTypeNameForG2Type(SEQUENCE_);
                }

                output.print(indentStr(indent));
                output.println("return " +
                        StubGenerationContext.codeToGetPrimitiveValueOrCastReturnObject("result", resultType) + ";");
            }
        }

        indent -= 2;
        output.print(indentStr(indent));
        output.println("}");

        output.print(indentStr(indent));
        output.println("else {");
        indent += 2;

        boolean opCopyCode = false;

        if (overrideMethodBody != null && !overrideMethodBody.equals("")) {
            output.print(indentStr(indent));
            output.println(overrideMethodBody);
            opCopyCode = true;
        }

        if (!opCopyCode) {
            output.print(indentStr(indent));
            output.println("// No MethodBody for by-copy exported");
            output.print(indentStr(indent));
            output.println("throw new RuntimeException(NoBodyExceptionString);");
        }

        indent -= 2;
        output.print(indentStr(indent));
        output.println("}");

        indent -= 2;
        output.print(indentStr(indent));
        output.println("}");

        return stream.toString();
    }

    private String expectedRPCDeclaration() {
        String symFieldModifiersAndType = "private static final Symbol ";

        String classRef = (absoluteG2ClassReference == null ?
                "" : absoluteG2ClassReference.toString() + "::");

        return symFieldModifiersAndType + expectedRpcDeclarationName() + " = " +
                "Symbol.intern (\"" + classRef + g2MethodName.toString() + "\");";
    }

    private String expectedRpcDeclarationName() {
        Symbol newG2MethodName = g2MethodName;
        if (absoluteG2ClassReference != null) {
            newG2MethodName = Symbol.intern(g2MethodName + "$" + absoluteG2ClassReference);
        }

        return "MethodName_" + ClassGenerationContext.createJavaSymbolVariableName(newG2MethodName);
    }

    private String[] expectedAllArgumentNames() {
        String[] argNames = new String[this.sut.getArgumentNames().size()];
        for (int i = 0; i < this.sut.getArgumentNames().size(); i++) {
            argNames[i] = (String) this.sut.getArgumentNames().elementAt(i);
        }
        return argNames;
    }

    private String[] expectedArgumentNames() {
        String[] paramNames;
        if (!isStatic) {
            paramNames = new String[this.sut.getArgumentNames().size() - 1];
            for (int i = 1; i < this.sut.getArgumentNames().size(); i++) {
                paramNames[i - 1] = (String) this.sut.getArgumentNames().elementAt(i);
            }
        } else {
            paramNames = new String[this.sut.getArgumentNames().size() + 2];
            paramNames[0] = "context";
            paramNames[1] = "timeout";
            for (int i = 0; i < this.sut.getArgumentNames().size(); i++) {
                paramNames[i + 2] = (String) this.sut.getArgumentNames().elementAt(i);
            }
        }

        return paramNames;
    }

    private String expectedInterfaceComment() {
        StringBuilder builder = new StringBuilder(201);
        int numResultTypes = g2ResultTypes.size();

        builder.append("/**\n");
        builder.append(" * Auto Generated method for G2 Method\n");
        builder.append(" * ").append(definingG2Class.toString()).append("::").append(g2MethodName.toString()).append("\n");
        if (numResultTypes > 0) {
            builder.append(" * @return the return from calling ").append(g2MethodName.toString()).append("\n");
        }
        builder.append(" * @exception G2AccessException if there are any communication problems");
        builder.append("\n * (");

        int i = 0;
        Enumeration names = this.sut.getArgumentNames().elements();
        for (Enumeration args = g2ArgumentTypes.elements();
             args.hasMoreElements();
             i++) {

            if (i > 0) {
                builder.append(",");
            }

            Object argType = args.nextElement();
            String argName = (String) names.nextElement();

            builder.append(argName).append(":").append(getMethodG2TypeWithClass(argType));
        }

        builder.append(") = (");

        if (numResultTypes != 0) {
            if (numResultTypes == 1) {
                builder.append(getMethodG2TypeWithClass(g2ResultTypes.elementAt(0)));
            } else {
                i = 0;
                for (Enumeration resTypes = g2ResultTypes.elements();
                     resTypes.hasMoreElements();
                     i++) {
                    if (i > 0) {
                        builder.append(",");
                    }
                    builder.append(getMethodG2TypeWithClass(resTypes.nextElement()));
                }
            }
        }

        builder.append(")\n */");

        return builder.toString();
    }

    private void createSut() {
        this.sut = new MethodInfo(
                g2MethodName,
                isStatic,
                g2ArgumentTypes,
                g2ResultTypes,
                g2MethodSource,
                definingG2Class,
                absoluteG2ClassReference,
                stubClassLoader);
    }
}
