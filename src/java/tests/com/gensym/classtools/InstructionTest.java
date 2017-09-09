package com.gensym.classtools;

import org.junit.Test;

import java.util.Hashtable;
import java.util.Vector;

import static com.gensym.classtools.RuntimeConstants.*;
import static com.gensym.helpers.ObjectsFactory.anyInteger;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;

public class InstructionTest extends InstructionTestHelper {
    @Test
    public void test_makeInstruction_validOpCode_createsNewIns() {
        Vector<Integer> validOpCodes = createValidOpCodes();
        for (int opcode : validOpCodes) {
            // Arrange
            // Nothing to arrange

            // Act
            Instruction result = Instruction.makeInstruction(opcode);

            // Assert
            assertByteArraysAreEqual(new byte[]{(byte) opcode}, result.getBytes());
        }
    }

    @Test
    public void test_makeInstruction_invalidOpCode_createsNullIns() {
        Vector<Integer> invalidOpCodes = createInvalidOpCodes();
        for (int opcode : invalidOpCodes) {
            // Arrange
            // Nothing to arrange

            // Act
            Instruction result = Instruction.makeInstruction(opcode);

            // Assert
            assertByteArraysAreEqual(getNullInstructionBytes(), result.getBytes());
        }
    }

    @Test
    public void test_makeInstruction_opCodeAndLongBranch_createsNullIns() {
        // Arrange
        // Nothing to arrange

        // Act
        Instruction result = Instruction.makeInstruction(anyInteger(), (long) anyInteger());

        // Assert
        assertByteArraysAreEqual(getNullInstructionBytes(), result.getBytes());
    }

    // Assert
    @Test(expected = IndexOutOfBoundsException.class)
    public void test_makeInstruction_emptyArgs_throwsException() {
        // Arrange
        int[] args = new int[0];

        // Act
        Instruction.makeInstruction(args);
    }

    @Test
    public void test_makeInstructionWithArgs_always_returnsIns() {
        Vector<int[]> testCases = getArgumentsTestCases();
        for (int[] args : testCases) {
            // Arrange
            // Nothing to arrange

            // Act
            Instruction result = Instruction.makeInstruction(args);

            // Assert
            assertByteArraysAreEqual(getExpectedBytes(args), result.getBytes());
        }
    }

    @Test
    public void test_makeInstructionWithArgs_indexOutOfBounds_returnsNullIns() {
        Vector<int[]> testCases = getInvalidArgumentsTestCases();
        for (int[] args : testCases) {
            // Arrange
            // Nothing to arrange

            // Act
            Instruction result = Instruction.makeInstruction(args);

            // Assert
            assertByteArraysAreEqual(getNullInstructionBytes(), result.getBytes());
        }
    }

    @Test
    public void test_makeInstructionWithArg_always_returnsIns() {
        Vector<InstructionTestCase> testCases = getArgumentTestCases();
        for (InstructionTestCase key : testCases) {
            // Arrange
            // Nothing to arrange

            // Act
            Instruction result = Instruction.makeInstruction(key.opcode, key.arg1);

            // Assert
            assertByteArraysAreEqual(getExpectedBytes(key.opcode, key.arg1), result.getBytes());
        }
    }

    @Test
    public void test_makeInstructionWithTwoArgs_always_returnsNewIns() {
        // Arrange
        int opcode = 0;
        int arg1 = 10;
        int arg2 = 20;

        // Act
        Instruction result = Instruction.makeInstruction(opcode, arg1, arg2);

        // Assert
        assertByteArraysAreEqual(getExpectedBytes(opcode, arg1, arg2), result.getBytes());
    }

    @Test
    public void test_makeInstructionWithThreeArgs_always_returnsNewIns() {
        // Arrange
        int opcode = 0;
        int arg1 = 10;
        int arg2 = 20;
        int arg3 = 30;

        // Act
        Instruction result = Instruction.makeInstruction(opcode, arg1, arg2, arg3);

        // Assert
        assertByteArraysAreEqual(getExpectedBytes(opcode, arg1, arg2, arg3), result.getBytes());
    }

    @Test
    public void test_makeInstructionWithFourArgs_always_returnsNewIns() {
        // Arrange
        int opcode = 0;
        int arg1 = 10;
        int arg2 = 20;
        int arg3 = 30;
        int arg4 = 40;

        // Act
        Instruction result = Instruction.makeInstruction(opcode, arg1, arg2, arg3, arg4);

        // Assert
        assertByteArraysAreEqual(getExpectedBytes(opcode, arg1, arg2, arg3, arg4), result.getBytes());
    }

    @Test
    public void test_readInstructions_always_returnsNewIns() throws ClassException {
        Vector<byte[]> testCases = getReadInstructionsTestCases();
        for (byte[] bytes : testCases) {
            // Arrange
            Vector expectedBytesList = getExpectedReadInstructionBytes(bytes, bytes.length);

            // Act
            Vector result = Instruction.readInstructions(bytes, 0, bytes.length);

            // Assert
            assertByteArraysListAreEqual(expectedBytesList, result);
        }
    }

    @Test
    public void test_isIfInstruction_isIfInstruction_returnsTrue() {
        int[] ifInstructions = new int[]{opc_ifeq, opc_ifne, opc_iflt, opc_ifge, opc_ifgt, opc_ifle, opc_if_icmpeq, opc_if_icmpne, opc_if_acmpeq, opc_if_acmpne, opc_ifnonnull, opc_ifnull};
        for (int opcode : ifInstructions) {
            // Arrange
            this.sut = new Instruction(opcode);

            // Act & Assert
            assertTrue(this.sut.isIfInstruction());
        }
    }

    @Test
    public void test_isIfInstruction_isNotIfInstruction_returnsFalse() {
        for (int opcode : getNotIfInstructions()) {
            // Arrange
            this.sut = new Instruction(opcode);

            // Act & Assert
            assertFalse(this.sut.isIfInstruction());
        }
    }

    @Test
    public void test_isReturnOrThrowInstruction_isReturnOrThrow_returnsTrue() {
        int[] returnOrThrowInstructions = new int[]{opc_ret, opc_return, opc_ireturn, opc_freturn, opc_lreturn, opc_dreturn, opc_areturn, opc_athrow};
        for (int opcode : returnOrThrowInstructions) {
            // Arrange
            this.sut = new Instruction(opcode);

            // Act & Assert
            assertTrue(this.sut.isReturnOrThrowInstruction());
        }
    }

    @Test
    public void test_isReturnOrThrowInstruction_isNotReturnOrThrow_returnsFalse() {
        for (int opcode : getNotReturnOrThrowInstructions()) {
            // Arrange
            this.sut = new Instruction(opcode);

            // Act & Assert
            assertFalse(this.sut.isReturnOrThrowInstruction());
        }
    }

    // Assert
    @Test(expected = ClassException.class)
    public void test_readInstructions_undefinedSubOpCode_throwsException() throws ClassException {
        // Arrange
        byte[] bytes = new byte[]{(byte) getOpCodeWithStartIndex(WIDE_START_MARKER), (byte) (opcLengths.length + 1), 3, 4, 5, 6, 7, 8, 9};

        // Act
        Instruction.readInstructions(bytes, 0, bytes.length);
    }

    // Assert
    @Test(expected = ClassException.class)
    public void test_readInstructions_invalidSubOpCode_throwsException() throws ClassException {
        // Arrange
        byte[] bytes = new byte[]{(byte) getOpCodeWithStartIndex(WIDE_START_MARKER), (byte) opc_ldc, 3, 4, 5, 6, 7, 8, 9};

        // Act
        Instruction.readInstructions(bytes, 0, bytes.length);
    }

    @Test
    public void test_toString_always_returnsStringRep() {
        for (int opcode = -3; opcode < opcLengths.length; opcode++) {
            // Arrange
            int[] args = new int[1];
            if (opcode >= 0) {
                args = new int[opcLengths[opcode] > 0 ? opcLengths[opcode] + 1 : 1];
                for (int idx = 1; idx < opcLengths[opcode]; idx++) {
                    args[idx] = anyInteger();
                }
            }

            args[0] = opcode;

            this.sut = Instruction.makeInstruction(args);

            byte[] bytes = opcode >= 0 ? getExpectedBytes(args) : new byte[]{(byte) this.sut.getOpcode()};
            String expected;
            if (this.sut.getOpcode() > 0) {
                expected = "<Instruction, name=" + opcNames[this.sut.getOpcode()] +
                        ",opcode=" + this.sut.getOpcode() +
                        ",length=" + opcLengths[this.sut.getOpcode()] +
                        ",rawBytes=" + toDecimalString(bytes) +
                        ">";
            } else if (this.sut.getOpcode() == opc_label) {
                expected = "<Instruction, name=label, opcode = -1, length = 0>";
            } else {
                expected = "<Instruction, opcode=" + this.sut.getOpcode() + ", rawBytes=" +
                        toDecimalString(bytes) + ">";
            }

            // Act & Assert
            assertEquals(expected, this.sut.toString());
        }
    }

    @Test
    public void test_toStdout_always_printsInstructions() {
        // Arrange
        Instruction[] instructions = new Instruction[0];
        String prefix = "// ";

        // Act
        Instruction.toStdout(instructions, prefix);

        // Assert
        assertTrue(this.outContent.toString().startsWith(prefix + "Instructions"));
    }

    // Assert
    @Test(expected = ClassException.class)
    public void test_get2ByteValue_notMultiByteIndex_throwsException() throws ClassException {
        // Arrange
        int opCode = 0;
        int startIndex = opcStartMultiByteValue[opCode] + 1;
        this.sut = Instruction.makeInstruction(opCode);

        // Act
        this.sut.get2ByteValue(startIndex);
    }

    // Assert
    @Test(expected = ClassException.class)
    public void test_set2ByteValue_notMultiByteIndex_throwsException() throws ClassException {
        // Arrange
        int opCode = 0;
        int startIndex = opcStartMultiByteValue[opCode] + 1;
        this.sut = Instruction.makeInstruction(opCode);

        // Act
        this.sut.set2ByteValue(startIndex, anyInteger());
    }

    @Test
    public void test_get4ByteValue_always_returns4ByteValue() throws ClassException {
        // Arrange
        int[] args = new int[]{opc_iload, anyInteger(), anyInteger(), anyInteger(), anyInteger()};
        this.sut = Instruction.makeInstruction(args);
        int startIndex = 1;

        // Act & Assert
        assertEquals(get4ByteValue(getExpectedBytes(args), startIndex), this.sut.get4ByteValue(startIndex));
    }

    @Test
    public void test_set4ByteValue_always_sets4ByteValue() throws ClassException {
        // Arrange
        int startIndex = 1;
        this.sut = createInstruction();
        byte[] existingBytes = new byte[this.sut.getBytes().length];
        System.arraycopy(this.sut.getBytes(), 0, existingBytes, 0, existingBytes.length);

        // Act
        this.sut.set4ByteValue(startIndex, anyInteger());

        // Assert
        assertEquals((byte) ((existingBytes[startIndex] >>> 24) & 0xFF), this.sut.getBytes()[startIndex]);
        assertEquals((byte) ((existingBytes[startIndex + 1] >>> 16) & 0xFF), this.sut.getBytes()[startIndex + 1]);
        assertEquals((byte) ((existingBytes[startIndex + 2] >>> 8) & 0xFF), this.sut.getBytes()[startIndex + 2]);
        assertEquals((byte) ((existingBytes[startIndex + 3]) & 0xFF), this.sut.getBytes()[startIndex + 3]);
    }

    @Test
    public void test_normalize_startIndexIsZero_returnsIndex() throws ClassException {
        // Arrange
        ConstantPool locals = new ConstantPool();
        ConstantPool normals = new ConstantPool();
        int index = 1;
        int expectedIndex = 1;
        byte[] bytes = new byte[0];
        this.sut = createInstruction();

        // Act & Assert
        assertEquals(expectedIndex, this.sut.normalize(locals, normals, index, bytes));
    }

    @Test
    public void test_emitArrayLoadInstruction_always_emitsInstruction() throws ClassException {
        // Arrange
        EmitState state = createEmitState();
        Hashtable<Type, String> testCases = emitArrayLoadInstructionTestCases();

        for (Type type : testCases.keySet()) {
            // Act
            Instruction.emitArrayLoadInstruction(state, type);

            // Assert
            assertEquals(testCases.get(type), state.instructions.lastElement().toString());
        }
    }

    @Test
    public void test_emitArrayStoreInstruction_always_emitsInstruction() throws ClassException {
        // Arrange
        EmitState state = createEmitState();
        Hashtable<Type, String> testCases = emitArrayStoreInstructionTestCases();

        for (Type type : testCases.keySet()) {
            // Act
            Instruction.emitArrayStoreInstruction(state, type);

            // Assert
            assertEquals(testCases.get(type), state.instructions.lastElement().toString());
        }
    }

    @Test
    public void test_emitPlusInstruction_always_emitsInstruction() throws ClassException {
        // Arrange
        EmitState state = createEmitState();
        Hashtable<Type, String> testCases = emitPlusInstructionTestCases();

        for (Type type : testCases.keySet()) {
            // Act
            Instruction.emitPlusInstruction(state, type);

            // Assert
            assertEquals(testCases.get(type), state.instructions.lastElement().toString());
        }
    }

    @Test
    public void test_emitMinusInstruction_always_emitsInstruction() throws ClassException {
        // Arrange
        EmitState state = createEmitState();
        Hashtable<Type, String> testCases = emitMinusInstructionTestCases();

        for (Type type : testCases.keySet()) {
            // Act
            Instruction.emitMinusInstruction(state, type);

            // Assert
            assertEquals(testCases.get(type), state.instructions.lastElement().toString());
        }
    }

    @Test
    public void test_emitMultiplyInstruction_always_emitsInstruction() throws ClassException {
        // Arrange
        EmitState state = createEmitState();
        Hashtable<Type, String> testCases = emitMultiplyInstructionTestCases();

        for (Type type : testCases.keySet()) {
            // Act
            Instruction.emitMultiplyInstruction(state, type);

            // Assert
            assertEquals(testCases.get(type), state.instructions.lastElement().toString());
        }
    }

    @Test
    public void test_emitDivideInstruction_always_emitsInstruction() throws ClassException {
        // Arrange
        EmitState state = createEmitState();
        Hashtable<Type, String> testCases = emitDivideInstructionTestCases();

        for (Type type : testCases.keySet()) {
            // Act
            Instruction.emitDivideInstruction(state, type);

            // Assert
            assertEquals(testCases.get(type), state.instructions.lastElement().toString());
        }
    }

    @Test
    public void test_emitRemainderInstruction_always_emitsInstruction() throws ClassException {
        // Arrange
        EmitState state = createEmitState();
        Hashtable<Type, String> testCases = emitRemainderInstructionTestCases();

        for (Type type : testCases.keySet()) {
            // Act
            Instruction.emitRemainderInstruction(state, type);

            // Assert
            assertEquals(testCases.get(type), state.instructions.lastElement().toString());
        }
    }

    @Test
    public void test_emitCastInstruction_always_emitsInstruction() throws ClassException {
        // Arrange
        EmitState state = createEmitState();
        Hashtable<InstructionTestCase, String> testCases = emitCastInstructionTestCases();

        for (InstructionTestCase key : testCases.keySet()) {
            // Act
            Instruction.emitCastInstruction(state, key.expressionType, key.type);

            // Assert
            assertEquals(testCases.get(key), state.instructions.lastElement().toString());
        }
    }

    @Test
    public void test_emitElementStoreInstruction_always_emitsInstruction() throws ClassException {
        // Arrange
        EmitState state = createEmitState();
        Hashtable<InstructionTestCase, String> testCases = emitElementStoreInstructionTestCases();

        for (InstructionTestCase key : testCases.keySet()) {
            // Act
            Instruction.emitElementStoreInstruction(state, key.type, key.argumentNumber);

            // Assert
            assertEquals(testCases.get(key), state.instructions.lastElement().toString());
        }
    }

    // Assert
    @Test(expected = ClassException.class)
    public void test_emitElementStoreInstruction_invalidType_throwsException() throws ClassException {
        // Arrange
        EmitState state = createEmitState();

        // Act
        Instruction.emitElementStoreInstruction(state, new Type(T_ANY), anyInteger());
    }

    @Test
    public void test_emitDupInstruction_always_emitsInstruction() throws ClassException {
        // Arrange
        EmitState state = createEmitState();
        Hashtable<InstructionTestCase, String> testCases = emitDupInstructionTestCases();

        for (InstructionTestCase key : testCases.keySet()) {
            // Act
            Instruction.emitDupInstruction(state, key.type);

            // Assert
            assertEquals(testCases.get(key), state.instructions.lastElement().toString());
        }
    }

    @Test
    public void test_emitDup2Instruction_always_emitsInstruction() throws ClassException {
        // Arrange
        EmitState state = createEmitState();

        // Act
        Instruction.emitDup2Instruction(state);

        // Assert
        assertEquals(Instruction.makeInstruction(opc_dup2).toString(), state.instructions.lastElement().toString());
    }

    @Test
    public void test_emitDupX1Instruction_always_emitsInstruction() throws ClassException {
        // Arrange
        EmitState state = createEmitState();
        Hashtable<InstructionTestCase, String> testCases = emitDupX1InstructionTestCases();

        for (InstructionTestCase key : testCases.keySet()) {
            // Act
            Instruction.emitDupX1Instruction(state, key.type);

            // Assert
            assertEquals(testCases.get(key), state.instructions.lastElement().toString());
        }
    }

    @Test
    public void test_emitDupX2Instruction_always_emitsInstruction() throws ClassException {
        // Arrange
        EmitState state = createEmitState();
        Hashtable<InstructionTestCase, String> testCases = emitDupX2InstructionTestCases();

        for (InstructionTestCase key : testCases.keySet()) {
            // Act
            Instruction.emitDupX2Instruction(state, key.type);

            // Assert
            assertEquals(testCases.get(key), state.instructions.lastElement().toString());
        }
    }

    @Test
    public void test_emitBitwiseOrInstruction_always_emitsInstruction() throws ClassException {
        // Arrange
        EmitState state = createEmitState();
        Hashtable<InstructionTestCase, String> testCases = emitBitwiseOrInstructionTestCases();

        for (InstructionTestCase key : testCases.keySet()) {
            // Act
            Instruction.emitBitwiseOrInstruction(state, key.type);

            // Assert
            assertEquals(testCases.get(key), state.instructions.lastElement().toString());
        }
    }

    // Assert
    @Test(expected = ClassException.class)
    public void test_emitBitwiseOrInstruction_invalidType_throwsException() throws ClassException {
        // Arrange
        EmitState state = createEmitState();

        // Act
        Instruction.emitBitwiseOrInstruction(state, new Type(T_ANY));
    }

    @Test
    public void test_emitBitwiseAndInstruction_always_emitsInstruction() throws ClassException {
        // Arrange
        EmitState state = createEmitState();
        Hashtable<InstructionTestCase, String> testCases = emitBitwiseAndInstructionTestCases();

        for (InstructionTestCase key : testCases.keySet()) {
            // Act
            Instruction.emitBitwiseAndInstruction(state, key.type);

            // Assert
            assertEquals(testCases.get(key), state.instructions.lastElement().toString());
        }
    }

    // Assert
    @Test(expected = ClassException.class)
    public void test_emitBitwiseAndInstruction_invalidType_throwsException() throws ClassException {
        // Arrange
        EmitState state = createEmitState();

        // Act
        Instruction.emitBitwiseAndInstruction(state, new Type(T_ANY));
    }

    @Test
    public void test_emitBitwiseXorInstruction_always_emitsInstruction() throws ClassException {
        // Arrange
        EmitState state = createEmitState();
        Hashtable<InstructionTestCase, String> testCases = emitBitwiseXorInstructionTestCases();

        for (InstructionTestCase key : testCases.keySet()) {
            // Act
            Instruction.emitBitwiseXorInstruction(state, key.type);

            // Assert
            assertEquals(testCases.get(key), state.instructions.lastElement().toString());
        }
    }

    // Assert
    @Test(expected = ClassException.class)
    public void test_emitBitwiseXorInstruction_invalidType_throwsException() throws ClassException {
        // Arrange
        EmitState state = createEmitState();

        // Act
        Instruction.emitBitwiseXorInstruction(state, new Type(T_ANY));
    }

    @Test
    public void test_emitLeftShiftInstruction_always_emitsInstruction() throws ClassException {
        // Arrange
        EmitState state = createEmitState();
        Hashtable<InstructionTestCase, String> testCases = emitLeftShiftInstructionTestCases();

        for (InstructionTestCase key : testCases.keySet()) {
            // Act
            Instruction.emitLeftShiftInstruction(state, key.type);

            // Assert
            assertEquals(testCases.get(key), state.instructions.lastElement().toString());
        }
    }

    // Assert
    @Test(expected = ClassException.class)
    public void test_emitLeftShiftInstruction_invalidType_throwsException() throws ClassException {
        // Arrange
        EmitState state = createEmitState();

        // Act
        Instruction.emitLeftShiftInstruction(state, new Type(T_ANY));
    }

    @Test
    public void test_emitRightShiftInstruction_always_emitsInstruction() throws ClassException {
        // Arrange
        EmitState state = createEmitState();
        Hashtable<InstructionTestCase, String> testCases = emitRightShiftInstructionTestCases();

        for (InstructionTestCase key : testCases.keySet()) {
            // Act
            Instruction.emitRightShiftInstruction(state, key.type);

            // Assert
            assertEquals(testCases.get(key), state.instructions.lastElement().toString());
        }
    }

    // Assert
    @Test(expected = ClassException.class)
    public void test_emitRightShiftInstruction_invalidType_throwsException() throws ClassException {
        // Arrange
        EmitState state = createEmitState();

        // Act
        Instruction.emitRightShiftInstruction(state, new Type(T_ANY));
    }

    @Test
    public void test_emitUnsignedRightShiftInstruction_always_emitsInstruction() throws ClassException {
        // Arrange
        EmitState state = createEmitState();
        Hashtable<InstructionTestCase, String> testCases = emitUnsignedRightShiftInstructionTestCases();

        for (InstructionTestCase key : testCases.keySet()) {
            // Act
            Instruction.emitUnsignedRightShiftInstruction(state, key.type);

            // Assert
            assertEquals(testCases.get(key), state.instructions.lastElement().toString());
        }
    }

    // Assert
    @Test(expected = ClassException.class)
    public void test_emitUnsignedRightShiftInstruction_invalidType_throwsException() throws ClassException {
        // Arrange
        EmitState state = createEmitState();

        // Act
        Instruction.emitUnsignedRightShiftInstruction(state, new Type(T_ANY));
    }

    @Test
    public void test_emitLtInstructions_always_emitsInstruction() throws ClassException {
        // Arrange
        EmitState state = createEmitState();
        Hashtable<InstructionTestCase, String[]> testCases = emitLtInstructionsTestCases();

        for (InstructionTestCase key : testCases.keySet()) {
            // Act
            Instruction.emitLtInstructions(state, key.type);

            // Assert
            assertStateContainsInstructions(state, testCases.get(key));
        }
    }

    @Test
    public void test_emitGtInstructions_always_emitsInstruction() throws ClassException {
        // Arrange
        EmitState state = createEmitState();
        Hashtable<InstructionTestCase, String[]> testCases = emitGtInstructionsTestCases();

        for (InstructionTestCase key : testCases.keySet()) {
            // Act
            Instruction.emitGtInstructions(state, key.type);

            // Assert
            assertStateContainsInstructions(state, testCases.get(key));
        }
    }

    @Test
    public void test_emitGeqInstructions_always_emitsInstruction() throws ClassException {
        // Arrange
        EmitState state = createEmitState();
        Hashtable<InstructionTestCase, String[]> testCases = emitGeqInstructionsTestCases();

        for (InstructionTestCase key : testCases.keySet()) {
            // Act
            Instruction.emitGeqInstructions(state, key.type);

            // Assert
            assertStateContainsInstructions(state, testCases.get(key));
        }
    }

    @Test
    public void test_emitLeqInstructions_always_emitsInstruction() throws ClassException {
        // Arrange
        EmitState state = createEmitState();
        Hashtable<InstructionTestCase, String[]> testCases = emitLeqInstructionsTestCases();

        for (InstructionTestCase key : testCases.keySet()) {
            // Act
            Instruction.emitLeqInstructions(state, key.type);

            // Assert
            assertStateContainsInstructions(state, testCases.get(key));
        }
    }

    @Test
    public void test_emitEqInstructions_always_emitsInstruction() throws ClassException {
        // Arrange
        EmitState state = createEmitState();
        Hashtable<InstructionTestCase, String[]> testCases = emitEqInstructionsTestCases();

        for (InstructionTestCase key : testCases.keySet()) {
            // Act
            Instruction.emitEqInstructions(state, key.type, key.arg0Expression, key.arg1Expression);

            // Assert
            assertStateContainsInstructions(state, testCases.get(key));
        }
    }

    // Assert
    @Test(expected = ClassException.class)
    public void test_emitEqInstructions_constantBooleans_throwsException() throws ClassException {
        // Arrange
        EmitState state = createEmitState();

        // Act
        Instruction.emitEqInstructions(state, new Type(T_BOOLEAN), new Value(true), new Value(false));
    }

    @Test
    public void test_emitNeqInstructions_always_emitsInstruction() throws ClassException {
        // Arrange
        EmitState state = createEmitState();
        Hashtable<InstructionTestCase, String[]> testCases = emitNeqInstructionsTestCases();

        for (InstructionTestCase key : testCases.keySet()) {
            // Act
            Instruction.emitNeqInstructions(state, key.type, key.arg0Expression, key.arg1Expression);

            // Assert
            assertStateContainsInstructions(state, testCases.get(key));
        }
    }

    // Assert
    @Test(expected = ClassException.class)
    public void test_emitNeqInstructions_constantBooleans_throwsException() throws ClassException {
        // Arrange
        EmitState state = createEmitState();

        // Act
        Instruction.emitNeqInstructions(state, new Type(T_BOOLEAN), new Value(true), new Value(false));
    }

    @Test
    public void test_emitIfeqInstruction_always_emitsInstruction() throws ClassException {
        // Arrange
        EmitState state = createEmitState();

        // Act
        Instruction.emitIfeqInstruction(state);

        // Assert
        assertEquals(Instruction.makeInstruction(opc_ifeq,0).toString(), state.instructions.lastElement().toString());
    }

    @Test
    public void test_emitIfneInstruction_always_emitsInstruction() throws ClassException {
        // Arrange
        EmitState state = createEmitState();

        // Act
        Instruction.emitIfneInstruction(state);

        // Assert
        assertEquals(Instruction.makeInstruction(opc_ifne,0).toString(), state.instructions.lastElement().toString());
    }
}
