package com.gensym.classtools;

import org.junit.Before;
import org.junit.Test;
import org.mockito.invocation.InvocationOnMock;
import org.mockito.stubbing.Answer;

import java.io.ByteArrayOutputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.util.Vector;

import static com.gensym.classtools.RuntimeConstants.*;
import static com.gensym.helpers.ObjectsFactory.anyInteger;
import static com.gensym.helpers.ObjectsFactory.anyString;
import static org.junit.Assert.*;
import static org.mockito.Matchers.any;
import static org.mockito.Matchers.anyInt;
import static org.powermock.api.mockito.PowerMockito.*;

public class CodeAttributeTest {
    private CodeAttribute sut;
    private ConstantPool constantPool;
    private byte[] bytes;
    private byte[] code;
    private byte[] attributesCount;
    private int attributesStartIndex;
    private int exceptionsStartIndex;
    private Vector normalizedObjects;
    private Vector localizedObjects;
    private Vector emittedInstructions;
    private int normalizedIndex;

    @Before
    public void init() throws ClassException {
        CodeAttribute.setTrace(true);

        this.constantPool = new ConstantPool();
        Constant[] pool = new Constant[]{createConstant(), createConstant("ConstantValue"), createIntegerConstant(), createConstant("ConstantValue"), createIntegerConstant()};
        this.constantPool.setPool(pool);
        createBytes();
        int start = 0;
        this.sut = new CodeAttribute(0, this.constantPool, this.bytes, start);

        this.localizedObjects = new Vector();
        this.normalizedObjects = new Vector();
        this.emittedInstructions = new Vector();
        this.normalizedIndex = 0;
    }

    @Test
    public void test_instance_withConstituentParts_instantiatesWithoutBytes() throws ClassException, IOException {
        // Arrange
        Vector instructions = createInstructions();
        Vector exceptionTable = createExceptionTable();
        int maxStack = 2;
        int maxLocals = 4;

        // Act
        this.sut = new CodeAttribute(this.constantPool, instructions, exceptionTable, maxStack, maxLocals);

        // Assert
        assertEquals(maxStack, this.sut.getMaxStack());
        assertEquals(maxLocals, this.sut.getMaxLocals());
        assertEqualCollections(instructions, this.sut.getRawInstructions());
        assertEqualCollections(exceptionTable, this.sut.getRawExceptionTable());
    }

    @Test
    public void test_instance_attributesNotSet_returnsEmptyArray() throws ClassException {
        // Arrange
        // Nothing to arrange

        // Act
        this.sut = new CodeAttribute(this.constantPool, new Vector(), new Vector(), 0, 0);

        // Assert
        assertNull(this.sut.getCode());
        assertEquals(0, this.sut.getAttributes().length);
    }

    @Test
    public void test_getCode_always_returnsCodeCopy() {
        // Arrange
        // Nothing to arrange

        // Act & Assert
        assertEqualCollections(this.code, this.sut.getCode());
    }

    @Test
    public void test_getInstructions_always_returnsInstructionsCopy() {
        // Arrange
        // Nothing to arrange

        // Act & Assert
        assertEqualCollections(expectedInstructions(), this.sut.getInstructions());
    }

    @Test
    public void test_getExceptionTable_always_returnsExceptionsCopy() throws ClassException {
        // Arrange
        // Nothing to arrange

        // Act & Assert
        assertEqualCollections(expectedExpectations(), this.sut.getExceptionTable());
    }

    @Test
    public void test_getAttributes_always_returnsAttributesCopy() throws ClassException {
        // Arrange
        // Nothing to arrange

        // Act & Assert
        assertEqualCollections(expectedAttributes(), this.sut.getAttributes());
    }

    @Test
    public void test_stripLdcInstructions_always_stripsLdcInstructions() throws ClassException {
        // Arrange


        // Act
        this.sut.stripLdcInstructions();

        // Assert
        assertTrue(this.sut.isLdcStripped());
    }

    @Test
    public void test_toString_always_returnsCodeAttributeStringRep() {
        // Arrange
        String expected =   "<CodeAttribute, max_stack=" + Attribute.readU2(this.bytes, 0) +
                ", max_locals=" + Attribute.readU2(this.bytes, 2) +
                ", code_length=" + Attribute.readU4(this.bytes, 4);

        // Act & Assert
        assertTrue(this.sut.toString().startsWith(expected));
    }

    @Test
    public void test_add_always_addsAttribute() throws ClassException {
        // Arrange
        this.sut = new CodeAttribute(this.constantPool, new Vector(), new Vector(), 0, 0);
        String name = anyString();
        Attribute attribute = new Attribute(name, this.constantPool);

        // Act
        this.sut.add(attribute);

        // Assert
        assertEquals(attribute.toString(), this.sut.getAttributes()[this.sut.getAttributes().length - 1].toString());
    }

    @Test
    public void test_normalize_always_normalizesEverything() throws ClassException, IOException {
        // Arrange
        createSut();
        setAttributes();
        ConstantPool locals = new ConstantPool();
        locals.setPool(createConstantsArray());
        ConstantPool normals = new ConstantPool();
        normals.setPool(createConstantsArray());
        int index = 0;

        // Act
        int result = this.sut.normalize(locals, normals, index);

        // Assert
        assertEquals(this.normalizedIndex, result);

        for (int idx = 0; idx < this.sut.getInstructions().length; idx++) {
            assertTrue(this.normalizedObjects.contains(this.sut.getInstructions()[idx]));
        }

        for (int idx = 0; idx < this.sut.getAttributes().length; idx++) {
            assertTrue(this.normalizedObjects.contains(this.sut.getAttributes()[idx]));
        }
    }

    @Test
    public void test_localizes_always_localizesEverything() throws ClassException, IOException {
        // Arrange
        createSut();
        setAttributes();
        ConstantPool locals = new ConstantPool();
        locals.setPool(createConstantsArray());
        ConstantPool normals = new ConstantPool();
        normals.setPool(createConstantsArray());

        // Act
        this.sut.localize(locals, normals);

        // Assert
        for (int idx = 0; idx < this.sut.getInstructions().length; idx++) {
            assertTrue(this.localizedObjects.contains(this.sut.getInstructions()[idx]));
        }

        for (int idx = 0; idx < this.sut.getExceptionTable().length; idx++) {
            assertTrue(this.localizedObjects.contains(this.sut.getExceptionTable()[idx]));
        }

        for (int idx = 0; idx < this.sut.getAttributes().length; idx++) {
            assertTrue(this.localizedObjects.contains(this.sut.getAttributes()[idx]));
        }
    }

    @Test
    public void test_emit_always_() throws IOException, ClassException {
        // Arrange
        createSut();
        setAttributes();
        ByteArrayOutputStream byteStream = new ByteArrayOutputStream();
        DataOutputStream stream = new DataOutputStream(byteStream);

        // Act
        this.sut.emit(stream);

        // Assert
        for (int idx = 0; idx < this.sut.getInstructions().length; idx++) {
            assertTrue(this.emittedInstructions.contains(this.sut.getInstructions()[idx]));
        }
    }

    private Constant[] createConstantsArray() throws ClassException {
        Constant[] constants = new Constant[100];

        for (int idx = 0; idx < constants.length; idx++) {
            constants[idx] = createConstant();
        }

        return constants;
    }

    private void setAttributes() throws ClassException {
        Attribute attribute = createAttribute();
        this.sut.add(attribute);
    }

    private Attribute createAttribute() throws ClassException {
        final Attribute attribute = mock(Attribute.class);
        when(attribute.getConstantPool()).thenReturn(this.constantPool);
        when(attribute.normalize(any(ConstantPool.class), any(ConstantPool.class), anyInt()))
                .thenAnswer(new Answer<Object>() {
                    @Override
                    public Object answer(InvocationOnMock invocation) throws Throwable {
                        normalizedObjects.add(attribute);
                        return ++normalizedIndex;
                    }
                });

        doAnswer(new Answer<Object>() {
            @Override
            public Object answer(InvocationOnMock invocation) throws Throwable {
                localizedObjects.add(attribute);
                return null;
            }
        }).when(attribute).localize(any(ConstantPool.class), any(ConstantPool.class));
        return attribute;
    }

    private int appendBytes(byte[] source, int index) {
        System.arraycopy(source, 0, this.bytes, index, source.length);
        index += source.length;
        return index;
    }

    private void assertEqualCollections(byte[] expected, byte[] actual) {
        assertEquals(expected.length, actual.length);
        for (int idx = 0; idx < expected.length; idx++) {
            assertEquals(expected[idx], actual[idx]);
        }
    }

    private void assertEqualCollections(Object[] expected, Object[] actual) {
        assertEquals(expected.length, actual.length);
        for (int idx = 0; idx < expected.length; idx++) {
            assertEquals(expected[idx].toString(), actual[idx].toString());
        }
    }

    private void assertEqualCollections(Vector expected, Vector actual) {
        assertEquals(expected.size(), actual.size());
        for (int idx = 0; idx < expected.size(); idx++) {
            assertEquals(expected.elementAt(idx).toString(), actual.elementAt(idx).toString());
        }
    }

    private void createBytes() {
        byte[] maxStack = new byte[] { 0, 1 };
        byte[] maxLocals = new byte[] { 0, 1 };
        byte[] codeLength = new byte[] { 0, 0, 0, 10 };
        this.code = new byte[] { opc_iconst_1, opc_iconst_2, opc_iconst_3, opc_iconst_4, opc_iconst_5, opc_lconst_0, opc_lconst_1, opc_fconst_0, opc_fconst_1, opc_fconst_2 };
        byte[] exceptionsCount = new byte[] { 0, 1 };
        byte[] exceptionStartPc = new byte[] { 0, 2 };
        byte[] exceptionEndPc = new byte[] { 0, 4 };
        byte[] exceptionHandlerPc = new byte[] { 0, 5 };
        byte[] exceptionCatchType = new byte[] { 0, 0 };
        this.attributesCount = new byte[] { 0, 2 };
        byte[] attribute1NameIndex = new byte[] { 0, 1 };
        byte[] attribute1DataLength = new byte[] { 0, 0, 0, 2 };
        byte[] attribute1DataIndex = new byte[] { 0, 2 };
        byte[] attribute2NameIndex = new byte[] { 0, 3 };
        byte[] attribute2DataLength = new byte[] { 0, 0, 0, 4 };
        byte[] attribute2DataIndex = new byte[] { 0, 4 };
        this.bytes = new byte[50];
        int index = 0;
        index = appendBytes(maxStack, index);
        index = appendBytes(maxLocals, index);
        index = appendBytes(codeLength, index);
        index = appendBytes(this.code, index);
        index = appendBytes(exceptionsCount, index);
        this.exceptionsStartIndex = index;
        index = appendBytes(exceptionStartPc, index);
        index = appendBytes(exceptionEndPc, index);
        index = appendBytes(exceptionHandlerPc, index);
        index = appendBytes(exceptionCatchType, index);
        index = appendBytes(this.attributesCount, index);
        this.attributesStartIndex = index;
        index = appendBytes(attribute1NameIndex, index);
        index = appendBytes(attribute1DataLength, index);
        index = appendBytes(attribute1DataIndex, index);
        index = appendBytes(attribute2NameIndex, index);
        index = appendBytes(attribute2DataLength, index);
        appendBytes(attribute2DataIndex, index);
    }

    private Constant createConstant() throws ClassException {
        return createConstant(anyString());
    }

    private Constant createConstant(String name) throws ClassException {
        Constant constant = mock(Constant.class);
        when(constant.getClassName()).thenReturn(anyString());
        when(constant.getName()).thenReturn(name);
        when(constant.normalize(any(ConstantPool.class), any(ConstantPool.class), anyInt())).thenReturn(anyInteger());
        when(constant.equalSemantic(any(ConstantPool.class), any(ConstantPool.class), any(Constant.class))).thenReturn(true);
        return constant;
    }

    private Vector createExceptionTable() throws ClassException {
        Vector exceptionTable = new Vector();
        exceptionTable.add(createExceptionTableEntry());
        exceptionTable.add(createExceptionTableEntry());
        exceptionTable.add(createExceptionTableEntry());
        return exceptionTable;
    }

    private ExceptionTableEntry createExceptionTableEntry() throws ClassException {
        final ExceptionTableEntry entry = mock(ExceptionTableEntry.class);
        when(entry.normalize(any(ConstantPool.class), any(ConstantPool.class), anyInt()))
            .thenAnswer(new Answer<Object>() {
                @Override
                public Object answer(InvocationOnMock invocation) throws Throwable {
                    normalizedObjects.add(entry);
                    return ++normalizedIndex;
                }
            });

        doAnswer(new Answer<Object>() {
            @Override
            public Object answer(InvocationOnMock invocation) throws Throwable {
                localizedObjects.add(entry);
                return null;
            }
        }).when(entry).localize(any(ConstantPool.class), any(ConstantPool.class));
        return entry;
    }

    private Constant createIntegerConstant() {
        return new Constant(CONSTANT_INTEGER);
    }

    private Vector createInstructions() throws ClassException, IOException {
        Vector instructions = new Vector();
        instructions.add(createInstruction());
        instructions.add(createInstruction());
        instructions.add(createInstruction());
        return instructions;
    }

    private Instruction createInstruction() throws ClassException, IOException {
        final Instruction instruction = mock(Instruction.class);
        when(instruction.normalize(any(ConstantPool.class), any(ConstantPool.class), anyInt(), any(byte[].class)))
                .thenAnswer(new Answer<Object>() {
                    @Override
                    public Object answer(InvocationOnMock invocation) throws Throwable {
                        normalizedObjects.add(instruction);
                        return ++normalizedIndex;
                    }
                });

        doAnswer(new Answer<Object>() {
            @Override
            public Object answer(InvocationOnMock invocation) throws Throwable {
                localizedObjects.add(instruction);
                return null;
            }
        }).when(instruction).localize(any(ConstantPool.class), any(ConstantPool.class), any(byte[].class));

        doAnswer(new Answer<Object>() {
            @Override
            public Object answer(InvocationOnMock invocation) throws Throwable {
                emittedInstructions.add(instruction);
                return null;
            }
        }).when(instruction).emit(any(DataOutputStream.class));
        return instruction;
    }

    private void createSut() throws ClassException, IOException {
        Vector instructions = createInstructions();
        Vector exceptionTable = createExceptionTable();
        int maxStack = 2;
        int maxLocals = 4;
        this.sut = new CodeAttribute(this.constantPool, instructions, exceptionTable, maxStack, maxLocals);
    }

    private ExceptionTableEntry[] expectedExpectations() throws ClassException {
        ExceptionTableEntry[] expectations = new ExceptionTableEntry[1];
        expectations[0] = new ExceptionTableEntry(this.constantPool, this.bytes, this.code, this.exceptionsStartIndex);
        return expectations;
    }

    private Instruction[] expectedInstructions() {
        Instruction[] instructions = new Instruction[10];
        for (int idx = 0; idx < this.code.length; idx++) {
            instructions[idx] = Instruction.makeInstruction(this.code[idx]);
        }

        return instructions;
    }

    private Attribute[] expectedAttributes() throws ClassException {
        int count = Attribute.readU2(this.attributesCount, 0);
        Attribute[] attributes = new Attribute[2];
        for(int idx = 0; idx < count; idx++) {
            attributes[idx] = Attribute.readAttribute(this.constantPool, this.bytes, this.attributesStartIndex);
            this.attributesStartIndex += (attributes[idx].length + 6);
        }

        return attributes;
    }
}
