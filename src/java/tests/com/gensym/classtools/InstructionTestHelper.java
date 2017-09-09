package com.gensym.classtools;

import org.junit.Before;

import java.io.ByteArrayOutputStream;
import java.io.PrintStream;
import java.util.Hashtable;
import java.util.Vector;

import static com.gensym.classtools.RuntimeConstants.*;
import static com.gensym.classtools.RuntimeConstants.opc_land;
import static com.gensym.classtools.RuntimeConstants.opc_lushr;
import static com.gensym.helpers.ObjectsFactory.anyInteger;
import static org.junit.Assert.assertEquals;

public class InstructionTestHelper {
    protected final ByteArrayOutputStream outContent = new ByteArrayOutputStream();
    protected final ByteArrayOutputStream errContent = new ByteArrayOutputStream();
    protected Instruction sut;

    @Before
    public void init() {
        setupStreams();
        Instruction.setTrace(true);
    }

    protected void assertByteArraysAreEqual(byte[] expected, byte[] actual) {
        assertEquals(expected.length, actual.length);
        for (int idx = 0; idx < expected.length; idx++) {
            assertEquals(expected[idx], actual[idx]);
        }
    }

    protected void assertByteArraysListAreEqual(Vector expected, Vector actual) {
        assertEquals(expected.size(), actual.size());
        for (int idx = 0; idx < expected.size(); idx++) {
            assertByteArraysAreEqual((byte[]) expected.elementAt(idx), ((Instruction) actual.elementAt(idx)).getBytes());
        }
    }

    protected void assertStateContainsInstructions(EmitState state, String[] expectedInsturctions) {
        assertEquals(expectedInsturctions[0], state.instructions.lastElement().toString());
        if (expectedInsturctions.length > 1) {
            assertEquals(expectedInsturctions[1], state.instructions.elementAt(state.instructions.size() - 2).toString());
        }
    }

    protected Vector<Integer> createValidOpCodes() {
        Vector<Integer> opcodes = new Vector<Integer>();

        // Negative op codes
        opcodes.add(-1);
        opcodes.add(-2);
        opcodes.add((int) Byte.MIN_VALUE);

        // Lesser than opcodes length
        for (int opcode = 0; opcode < opcLengths.length; opcode++) {
            opcodes.add(opcode);
        }

        return opcodes;
    }

    protected Instruction createInstruction() {
        return createInstruction(opc_iload);
    }

    protected Instruction createInstruction(int opcode) {
        return Instruction.makeInstruction(opcode, anyInteger(), anyInteger(), anyInteger(), anyInteger());
    }

    protected Vector<Integer> createInvalidOpCodes() {
        Vector<Integer> opcodes = new Vector<Integer>();

        // Greater than opcodes length
        opcodes.add(opcLengths.length);
        opcodes.add(opcLengths.length + 1);
        opcodes.add(Integer.MAX_VALUE);

        return opcodes;
    }

    protected Vector<InstructionTestCase> getArgumentTestCases() {
        Vector<InstructionTestCase> testCases = new Vector<InstructionTestCase>();

        // opcode < 0
        testCases.add(new InstructionTestCase(-1, 10));

        // opcode with Start Index = 1
        testCases.add(new InstructionTestCase(getOpCodeWithStartIndex(1), 10));

        // opcode with Start Index = 0
        testCases.add(new InstructionTestCase(getOpCodeWithStartIndex(0), 20));

        // opcode with Start Index = Wide Start Market
        testCases.add(new InstructionTestCase(getOpCodeWithStartIndex(WIDE_START_MARKER), 30));

        // opcode == opcodes count
        testCases.add(new InstructionTestCase(opcLengths.length, 40));

        // opcode > opcodes count
        testCases.add(new InstructionTestCase(opcLengths.length + 1, 50));

        return testCases;
    }

    protected Vector<int[]> getArgumentsTestCases() {
        Vector<int[]> testCases = new Vector<int[]>();

        // 2 length arguments (Wide Start Marker)
        int[] args = new int[2];
        args[0] = getOpCodeWithStartIndex(WIDE_START_MARKER);
        args[1] = 50;
        testCases.add(args);

        // 3 length arguments (Wide Start Marker)
        args = new int[3];
        args[0] = getOpCodeWithStartIndex(WIDE_START_MARKER);
        args[1] = 50;
        args[2] = 100;
        testCases.add(args);

        // 4 length arguments (Wide Start Marker)
        args = new int[4];
        args[0] = getOpCodeWithStartIndex(WIDE_START_MARKER);
        args[1] = 50;
        args[2] = 100;
        args[3] = 120;
        testCases.add(args);

        // Start Index = 0
        args = new int[5];
        args[0] = getOpCodeWithStartIndex(0);
        args[1] = 25;
        args[2] = 50;
        args[3] = 100;
        args[4] = 120;
        testCases.add(args);

        // Start Index = 1
        args = new int[5];
        args[0] = getOpCodeWithStartIndex(1);
        args[1] = 25;
        args[2] = 50;
        args[3] = 100;
        args[4] = 120;
        testCases.add(args);

        return testCases;
    }

    protected byte[] getExpectedBytes(int[] args) {
        ByteArrayOutputStream outputStream = new ByteArrayOutputStream();
        int opcode = args[0];
        int startIndex = opcStartMultiByteValue[opcode];
        if ((opcode >= 0) && (opcode < opcLengths.length)) {
            outputStream.write(opcode);
            int i = 1;
            if (startIndex == WIDE_START_MARKER) {
                if (args.length == 3) {
                    outputStream.write((byte) args[i]);
                    i++;
                    outputStream.write((byte) ((args[i] >>> 8) & 0xFF));
                    outputStream.write((byte) (args[i] & 0xFF));
                } else if (args.length == 4) {
                    outputStream.write((byte) args[i]);
                    i++;
                    outputStream.write((byte) ((args[i] >>> 8) & 0xFF));
                    outputStream.write((byte) (args[i] & 0xFF));
                    i++;
                    outputStream.write((byte) ((args[i] >>> 8) & 0xFF));
                    outputStream.write((byte) (args[i] & 0xFF));
                } else {
                    return getNullInstructionBytes();
                }
            } else {
                for (; i < args.length; i++) {
                    if (startIndex == i) {
                        outputStream.write((byte) ((args[i] >>> 8) & 0xFF));
                        outputStream.write((byte) (args[i] & 0xFF));
                    } else {
                        outputStream.write((byte) args[i]);
                    }
                }
            }

            return outputStream.toByteArray();
        } else {
            return getNullInstructionBytes();
        }
    }

    protected byte[] getExpectedBytes(int opcode, int arg1, int arg2) {
        int[] args = {opcode, arg1, arg2};
        return getExpectedBytes(args);
    }

    protected byte[] getExpectedBytes(int opcode, int arg1, int arg2, int arg3) {
        int[] args = {opcode, arg1, arg2, arg3};
        return getExpectedBytes(args);
    }

    protected byte[] getExpectedBytes(int opcode, int arg1, int arg2, int arg3, int arg4) {
        int[] args = {opcode, arg1, arg2, arg3, arg4};
        return getExpectedBytes(args);
    }

    public static byte[] getExpectedBytes(int opcode, int arg1) {
        if (opcode < 0) {
            byte[] bytes = new byte[2];
            bytes[0] = (byte) opcode;
            bytes[1] = (byte) arg1;
            return bytes;
        } else if (opcode < opcLengths.length) {
            byte[] bytes;
            int startIndex = opcStartMultiByteValue[opcode];
            if (startIndex == 1) {
                bytes = new byte[3];
                bytes[0] = (byte) opcode;
                bytes[1] = (byte) ((arg1 >>> 8) & 0xFF);
                bytes[2] = (byte) (arg1 & 0xFF);
            } else {
                bytes = new byte[2];
                bytes[0] = (byte) opcode;
                bytes[1] = (byte) arg1;
            }

            return bytes;
        } else {
            return getNullInstructionBytes();
        }
    }

    protected Vector<int[]> getInvalidArgumentsTestCases() {
        Vector<int[]> testCases = new Vector<int[]>();

        // opcode < 0
        int[] args = new int[2];
        args[0] = -1;
        args[1] = 50;
        testCases.add(args);

        // opcode == op codes length
        args = new int[2];
        args[0] = opcLengths.length;
        args[1] = 50;
        testCases.add(args);

        // opcode > op codes length
        args = new int[2];
        args[0] = opcLengths.length + 1;
        args[1] = 50;
        testCases.add(args);

        return testCases;
    }

    protected static byte[] getNullInstructionBytes() {
        byte[] bytes = new byte[1];
        bytes[0] = 0;
        return bytes;
    }

    protected int getOpCodeWithStartIndex(int startIndex) {
        int opcode = 0;

        for (int idx = 0; idx < opcStartMultiByteValue.length; idx++) {
            if (opcStartMultiByteValue[idx] == startIndex) {
                opcode = idx;
                break;
            }
        }

        return opcode;
    }

    protected Vector<byte[]> getReadInstructionsTestCases() {
        Vector<byte[]> testCases = new Vector<byte[]>();

        // table switch
        testCases.add(new byte[]{(byte) 0xAA, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 10, 0, 0, 0, 10, 17, 18, 19, 20});

        // lookup switch
        testCases.add(new byte[]{(byte) 0xAB, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 1, 13, 14, 15, 16, 17, 18, 19, 20});

        // lookup switch - invalid padding
        //testCases.add(new byte[]{(byte)0xAB, 0, 0, 1, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 });

        testCases.add(new byte[]{(byte) getOpCodeWithStartIndex(0), 2, 3, 4, 5, 6, 7, 8, 9});
        testCases.add(new byte[]{(byte) getOpCodeWithStartIndex(1), 2, 3, 4, 5, 6, 7, 8, 9});

        int[] subOpCodes = new int[]{opc_iinc, opc_aload, opc_iload, opc_fload, opc_dload, opc_lload, opc_astore, opc_istore, opc_fstore, opc_dstore, opc_lstore};
        for (int subOpCode : subOpCodes) {
            testCases.add(new byte[]{(byte) getOpCodeWithStartIndex(WIDE_START_MARKER), (byte) subOpCode, 3, 4, 5, 6, 7, 8, 9});
        }

        return testCases;
    }

    protected Vector<byte[]> getExpectedReadInstructionBytes(byte[] bytes, int length) throws ClassException {
        int nextop;
        int nextlength = 0;
        Vector ret = new Vector<byte[]>(length);

        for (int i = 0; i < length; i += nextlength) {
            nextop = (bytes[i] & 0xFF);
            if (i < (length)) {
                if (nextop < opcLengths.length) {
                    nextlength = determineInstructionLength(nextop, i, bytes);

                    if (nextlength == WIDE_MARKER_LENGTH) {
                        int subop = (bytes[i + 1] & 0xFF);
                        if (subop == opc_iinc) {
                            nextlength = WIDE_IINC_LENGTH;
                        } else {
                            switch (subop) {
                                case opc_aload:
                                case opc_iload:
                                case opc_fload:
                                case opc_dload:
                                case opc_lload:
                                case opc_astore:
                                case opc_istore:
                                case opc_fstore:
                                case opc_dstore:
                                case opc_lstore: {
                                    nextlength = WIDE_OTHER_LENGTH;
                                    break;
                                }
                            }
                        }
                    }

                    byte[] newBytes = new byte[nextlength];
                    System.arraycopy(bytes, i, newBytes, 0, nextlength);
                    ret.add(newBytes);
                }
            }
        }

        return ret;
    }

    protected Vector<Integer> getNotIfInstructions() {
        int[] ins = {opc_ifeq, opc_ifne, opc_iflt, opc_ifge, opc_ifgt, opc_ifle, opc_if_icmpeq, opc_if_icmpne, opc_if_acmpeq, opc_if_acmpne, opc_ifnonnull, opc_ifnull};
        Vector<Integer> ifInstructions = new Vector<Integer>();
        for (int in : ins) {
            ifInstructions.add(in);
        }

        Vector<Integer> notIfInstructions = new Vector<Integer>();

        for (int idx = 0; idx < opcLengths.length; idx++) {
            if (!ifInstructions.contains(idx)) {
                notIfInstructions.add(idx);
            }
        }

        return notIfInstructions;
    }

    protected Vector<Integer> getNotReturnOrThrowInstructions() {
        int[] ins = new int[]{opc_ret, opc_return, opc_ireturn, opc_freturn, opc_lreturn, opc_dreturn, opc_areturn, opc_athrow};
        Vector<Integer> returnOrThrowIns = new Vector<Integer>();
        for (int in : ins) {
            returnOrThrowIns.add(in);
        }

        Vector<Integer> notIfInstructions = new Vector<Integer>();

        for (int idx = 0; idx < opcLengths.length; idx++) {
            if (!returnOrThrowIns.contains(idx)) {
                notIfInstructions.add(idx);
            }
        }

        return notIfInstructions;
    }

    protected String toDecimalString(byte[] bts) {
        if (bts == null)
            return null;
        StringBuilder newints = new StringBuilder();
        newints.append("").append(bts[0] & 0xFF);
        for (int i = 1; i < bts.length; i++)
            newints.append(" ").append(bts[i] & 0xFF);
        return newints.toString();
    }

    protected long get4ByteValue(byte[] bytes, int startIndex) {
        return (bytes[startIndex] << 24) |
                (bytes[startIndex + 1] << 16) |
                (bytes[startIndex + 2] << 8) |
                (bytes[startIndex + 3] & 0xFF);
    }

    protected EmitState createEmitState() {
        EmitState state = new EmitState(new ConstantPool(), new Vector(), new Vector(), new Vector());
        state.pushStack(100);
        return state;
    }

    protected Hashtable<Type, String> emitArrayLoadInstructionTestCases() {
        Hashtable<Type, String> testCases = new Hashtable<Type, String>();
        testCases.put(new Type(T_SHORT), Instruction.makeInstruction(opc_saload).toString());
        testCases.put(new Type(T_BYTE), Instruction.makeInstruction(opc_baload).toString());
        testCases.put(new Type(T_CHAR), Instruction.makeInstruction(opc_caload).toString());
        testCases.put(new Type(T_LONG), Instruction.makeInstruction(opc_laload).toString());
        testCases.put(new Type(T_FLOAT), Instruction.makeInstruction(opc_faload).toString());
        testCases.put(new Type(T_DOUBLE), Instruction.makeInstruction(opc_daload).toString());
        testCases.put(new Type(T_INT), Instruction.makeInstruction(opc_iaload).toString());
        testCases.put(new Type(T_CLASS), Instruction.makeInstruction(opc_aaload).toString());
        return testCases;
    }

    protected Hashtable<Type, String> emitArrayStoreInstructionTestCases() {
        Hashtable<Type, String> testCases = new Hashtable<Type, String>();
        testCases.put(new Type(T_SHORT), Instruction.makeInstruction(opc_sastore).toString());
        testCases.put(new Type(T_BYTE), Instruction.makeInstruction(opc_bastore).toString());
        testCases.put(new Type(T_CHAR), Instruction.makeInstruction(opc_castore).toString());
        testCases.put(new Type(T_LONG), Instruction.makeInstruction(opc_lastore).toString());
        testCases.put(new Type(T_FLOAT), Instruction.makeInstruction(opc_fastore).toString());
        testCases.put(new Type(T_DOUBLE), Instruction.makeInstruction(opc_dastore).toString());
        testCases.put(new Type(T_INT), Instruction.makeInstruction(opc_iastore).toString());
        testCases.put(new Type(T_CLASS), Instruction.makeInstruction(opc_aastore).toString());
        return testCases;
    }

    protected Hashtable<Type, String> emitPlusInstructionTestCases() {
        Hashtable<Type, String> testCases = new Hashtable<Type, String>();
        testCases.put(new Type(T_INT), Instruction.makeInstruction(opc_iadd).toString());
        testCases.put(new Type(T_FLOAT), Instruction.makeInstruction(opc_fadd).toString());
        testCases.put(new Type(T_DOUBLE), Instruction.makeInstruction(opc_dadd).toString());
        testCases.put(new Type(T_LONG), Instruction.makeInstruction(opc_ladd).toString());
        return testCases;
    }

    protected Hashtable<Type, String> emitMinusInstructionTestCases() {
        Hashtable<Type, String> testCases = new Hashtable<Type, String>();
        testCases.put(new Type(T_INT), Instruction.makeInstruction(opc_isub).toString());
        testCases.put(new Type(T_FLOAT), Instruction.makeInstruction(opc_fsub).toString());
        testCases.put(new Type(T_DOUBLE), Instruction.makeInstruction(opc_dsub).toString());
        testCases.put(new Type(T_LONG), Instruction.makeInstruction(opc_lsub).toString());
        return testCases;
    }

    protected Hashtable<Type, String> emitMultiplyInstructionTestCases() {
        Hashtable<Type, String> testCases = new Hashtable<Type, String>();
        testCases.put(new Type(T_INT), Instruction.makeInstruction(opc_imul).toString());
        testCases.put(new Type(T_FLOAT), Instruction.makeInstruction(opc_fmul).toString());
        testCases.put(new Type(T_DOUBLE), Instruction.makeInstruction(opc_dmul).toString());
        testCases.put(new Type(T_LONG), Instruction.makeInstruction(opc_lmul).toString());
        return testCases;
    }

    protected Hashtable<Type, String> emitDivideInstructionTestCases() {
        Hashtable<Type, String> testCases = new Hashtable<Type, String>();
        testCases.put(new Type(T_INT), Instruction.makeInstruction(opc_idiv).toString());
        testCases.put(new Type(T_FLOAT), Instruction.makeInstruction(opc_fdiv).toString());
        testCases.put(new Type(T_DOUBLE), Instruction.makeInstruction(opc_ddiv).toString());
        testCases.put(new Type(T_LONG), Instruction.makeInstruction(opc_ldiv).toString());
        return testCases;
    }

    protected Hashtable<Type, String> emitRemainderInstructionTestCases() {
        Hashtable<Type, String> testCases = new Hashtable<Type, String>();
        testCases.put(new Type(T_INT), Instruction.makeInstruction(opc_irem).toString());
        testCases.put(new Type(T_FLOAT), Instruction.makeInstruction(opc_frem).toString());
        testCases.put(new Type(T_DOUBLE), Instruction.makeInstruction(opc_drem).toString());
        testCases.put(new Type(T_LONG), Instruction.makeInstruction(opc_lrem).toString());
        return testCases;
    }

    protected Hashtable<InstructionTestCase, String> emitCastInstructionTestCases() {
        Hashtable<InstructionTestCase, String> testCases = new Hashtable<InstructionTestCase, String>();
        testCases.put(new InstructionTestCase(new Type(T_INT), new Type(T_LONG)), Instruction.makeInstruction(opc_i2l).toString());
        testCases.put(new InstructionTestCase(new Type(T_INT), new Type(T_FLOAT)), Instruction.makeInstruction(opc_i2f).toString());
        testCases.put(new InstructionTestCase(new Type(T_INT), new Type(T_DOUBLE)), Instruction.makeInstruction(opc_i2d).toString());
        testCases.put(new InstructionTestCase(new Type(T_INT), new Type(T_CHAR)), Instruction.makeInstruction(opc_i2c).toString());
        testCases.put(new InstructionTestCase(new Type(T_INT), new Type(T_BYTE)), Instruction.makeInstruction(opc_i2b).toString());
        testCases.put(new InstructionTestCase(new Type(T_INT), new Type(T_SHORT)), Instruction.makeInstruction(opc_i2s).toString());
        testCases.put(new InstructionTestCase(new Type(T_FLOAT), new Type(T_INT)), Instruction.makeInstruction(opc_f2i).toString());
        testCases.put(new InstructionTestCase(new Type(T_FLOAT), new Type(T_LONG)), Instruction.makeInstruction(opc_f2l).toString());
        testCases.put(new InstructionTestCase(new Type(T_FLOAT), new Type(T_DOUBLE)), Instruction.makeInstruction(opc_f2d).toString());
        testCases.put(new InstructionTestCase(new Type(T_DOUBLE), new Type(T_INT)), Instruction.makeInstruction(opc_d2i).toString());
        testCases.put(new InstructionTestCase(new Type(T_DOUBLE), new Type(T_LONG)), Instruction.makeInstruction(opc_d2l).toString());
        testCases.put(new InstructionTestCase(new Type(T_DOUBLE), new Type(T_FLOAT)), Instruction.makeInstruction(opc_d2f).toString());
        testCases.put(new InstructionTestCase(new Type(T_LONG), new Type(T_INT)), Instruction.makeInstruction(opc_l2i).toString());
        testCases.put(new InstructionTestCase(new Type(T_LONG), new Type(T_DOUBLE)), Instruction.makeInstruction(opc_l2d).toString());
        testCases.put(new InstructionTestCase(new Type(T_LONG), new Type(T_FLOAT)), Instruction.makeInstruction(opc_l2f).toString());
        return testCases;
    }

    protected Hashtable<InstructionTestCase, String> emitElementStoreInstructionTestCases() {
        Hashtable<InstructionTestCase, String> testCases = new Hashtable<InstructionTestCase, String>();
        testCases.put(new InstructionTestCase(new Type(T_CLASS), 0), Instruction.makeInstruction(opc_astore_0).toString());
        testCases.put(new InstructionTestCase(new Type(T_CLASS), 1), Instruction.makeInstruction(opc_astore_1).toString());
        testCases.put(new InstructionTestCase(new Type(T_CLASS), 2), Instruction.makeInstruction(opc_astore_2).toString());
        testCases.put(new InstructionTestCase(new Type(T_CLASS), 3), Instruction.makeInstruction(opc_astore_3).toString());
        testCases.put(new InstructionTestCase(new Type(T_CLASS), 4), Instruction.makeInstruction(opc_astore, 4).toString());
        testCases.put(new InstructionTestCase(new Type(T_INT), 0), Instruction.makeInstruction(opc_istore_0).toString());
        testCases.put(new InstructionTestCase(new Type(T_INT), 1), Instruction.makeInstruction(opc_istore_1).toString());
        testCases.put(new InstructionTestCase(new Type(T_INT), 2), Instruction.makeInstruction(opc_istore_2).toString());
        testCases.put(new InstructionTestCase(new Type(T_INT), 3), Instruction.makeInstruction(opc_istore_3).toString());
        testCases.put(new InstructionTestCase(new Type(T_INT), 4), Instruction.makeInstruction(opc_istore, 4).toString());
        testCases.put(new InstructionTestCase(new Type(T_SHORT), 0), Instruction.makeInstruction(opc_istore_0).toString());
        testCases.put(new InstructionTestCase(new Type(T_SHORT), 1), Instruction.makeInstruction(opc_istore_1).toString());
        testCases.put(new InstructionTestCase(new Type(T_SHORT), 2), Instruction.makeInstruction(opc_istore_2).toString());
        testCases.put(new InstructionTestCase(new Type(T_SHORT), 3), Instruction.makeInstruction(opc_istore_3).toString());
        testCases.put(new InstructionTestCase(new Type(T_SHORT), 4), Instruction.makeInstruction(opc_istore, 4).toString());
        testCases.put(new InstructionTestCase(new Type(T_BYTE), 0), Instruction.makeInstruction(opc_istore_0).toString());
        testCases.put(new InstructionTestCase(new Type(T_BYTE), 1), Instruction.makeInstruction(opc_istore_1).toString());
        testCases.put(new InstructionTestCase(new Type(T_BYTE), 2), Instruction.makeInstruction(opc_istore_2).toString());
        testCases.put(new InstructionTestCase(new Type(T_BYTE), 3), Instruction.makeInstruction(opc_istore_3).toString());
        testCases.put(new InstructionTestCase(new Type(T_BYTE), 4), Instruction.makeInstruction(opc_istore, 4).toString());
        testCases.put(new InstructionTestCase(new Type(T_DOUBLE), 0), Instruction.makeInstruction(opc_dstore_0).toString());
        testCases.put(new InstructionTestCase(new Type(T_DOUBLE), 1), Instruction.makeInstruction(opc_dstore_1).toString());
        testCases.put(new InstructionTestCase(new Type(T_DOUBLE), 2), Instruction.makeInstruction(opc_dstore_2).toString());
        testCases.put(new InstructionTestCase(new Type(T_DOUBLE), 3), Instruction.makeInstruction(opc_dstore_3).toString());
        testCases.put(new InstructionTestCase(new Type(T_DOUBLE), 4), Instruction.makeInstruction(opc_dstore, 4).toString());
        testCases.put(new InstructionTestCase(new Type(T_LONG), 0), Instruction.makeInstruction(opc_lstore_0).toString());
        testCases.put(new InstructionTestCase(new Type(T_LONG), 1), Instruction.makeInstruction(opc_lstore_1).toString());
        testCases.put(new InstructionTestCase(new Type(T_LONG), 2), Instruction.makeInstruction(opc_lstore_2).toString());
        testCases.put(new InstructionTestCase(new Type(T_LONG), 3), Instruction.makeInstruction(opc_lstore_3).toString());
        testCases.put(new InstructionTestCase(new Type(T_LONG), 4), Instruction.makeInstruction(opc_lstore, 4).toString());
        testCases.put(new InstructionTestCase(new Type(T_FLOAT), 0), Instruction.makeInstruction(opc_fstore_0).toString());
        testCases.put(new InstructionTestCase(new Type(T_FLOAT), 1), Instruction.makeInstruction(opc_fstore_1).toString());
        testCases.put(new InstructionTestCase(new Type(T_FLOAT), 2), Instruction.makeInstruction(opc_fstore_2).toString());
        testCases.put(new InstructionTestCase(new Type(T_FLOAT), 3), Instruction.makeInstruction(opc_fstore_3).toString());
        testCases.put(new InstructionTestCase(new Type(T_FLOAT), 4), Instruction.makeInstruction(opc_fstore, 4).toString());
        return testCases;
    }

    protected Hashtable<InstructionTestCase, String> emitDupInstructionTestCases() {
        Hashtable<InstructionTestCase, String> testCases = new Hashtable<InstructionTestCase, String>();
        testCases.put(new InstructionTestCase(new Type(T_LONG)), Instruction.makeInstruction(opc_dup2).toString());
        testCases.put(new InstructionTestCase(new Type(T_DOUBLE)), Instruction.makeInstruction(opc_dup2).toString());
        testCases.put(new InstructionTestCase(new Type(T_SHORT)), Instruction.makeInstruction(opc_dup).toString());
        testCases.put(new InstructionTestCase(new Type(T_INT)), Instruction.makeInstruction(opc_dup).toString());
        return testCases;
    }

    protected Hashtable<InstructionTestCase, String> emitDupX1InstructionTestCases() {
        Hashtable<InstructionTestCase, String> testCases = new Hashtable<InstructionTestCase, String>();
        testCases.put(new InstructionTestCase(new Type(T_LONG)), Instruction.makeInstruction(opc_dup2_x1).toString());
        testCases.put(new InstructionTestCase(new Type(T_DOUBLE)), Instruction.makeInstruction(opc_dup2_x1).toString());
        testCases.put(new InstructionTestCase(new Type(T_SHORT)), Instruction.makeInstruction(opc_dup_x1).toString());
        testCases.put(new InstructionTestCase(new Type(T_INT)), Instruction.makeInstruction(opc_dup_x1).toString());
        return testCases;
    }

    protected Hashtable<InstructionTestCase, String> emitDupX2InstructionTestCases() {
        Hashtable<InstructionTestCase, String> testCases = new Hashtable<InstructionTestCase, String>();
        testCases.put(new InstructionTestCase(new Type(T_LONG)), Instruction.makeInstruction(opc_dup2_x2).toString());
        testCases.put(new InstructionTestCase(new Type(T_DOUBLE)), Instruction.makeInstruction(opc_dup2_x2).toString());
        testCases.put(new InstructionTestCase(new Type(T_SHORT)), Instruction.makeInstruction(opc_dup_x2).toString());
        testCases.put(new InstructionTestCase(new Type(T_INT)), Instruction.makeInstruction(opc_dup_x2).toString());
        return testCases;
    }

    protected Hashtable<InstructionTestCase, String> emitBitwiseOrInstructionTestCases() {
        Hashtable<InstructionTestCase, String> testCases = new Hashtable<InstructionTestCase, String>();
        testCases.put(new InstructionTestCase(new Type(T_BOOLEAN)), Instruction.makeInstruction(opc_ior).toString());
        testCases.put(new InstructionTestCase(new Type(T_BYTE)), Instruction.makeInstruction(opc_ior).toString());
        testCases.put(new InstructionTestCase(new Type(T_SHORT)), Instruction.makeInstruction(opc_ior).toString());
        testCases.put(new InstructionTestCase(new Type(T_SMALL_INTEGRAL)), Instruction.makeInstruction(opc_ior).toString());
        testCases.put(new InstructionTestCase(new Type(T_INT)), Instruction.makeInstruction(opc_ior).toString());
        testCases.put(new InstructionTestCase(new Type(T_LONG)), Instruction.makeInstruction(opc_lor).toString());
        return testCases;
    }

    protected Hashtable<InstructionTestCase, String> emitBitwiseAndInstructionTestCases() {
        Hashtable<InstructionTestCase, String> testCases = new Hashtable<InstructionTestCase, String>();
        testCases.put(new InstructionTestCase(new Type(T_BOOLEAN)), Instruction.makeInstruction(opc_iand).toString());
        testCases.put(new InstructionTestCase(new Type(T_BYTE)), Instruction.makeInstruction(opc_iand).toString());
        testCases.put(new InstructionTestCase(new Type(T_SHORT)), Instruction.makeInstruction(opc_iand).toString());
        testCases.put(new InstructionTestCase(new Type(T_SMALL_INTEGRAL)), Instruction.makeInstruction(opc_iand).toString());
        testCases.put(new InstructionTestCase(new Type(T_INT)), Instruction.makeInstruction(opc_iand).toString());
        testCases.put(new InstructionTestCase(new Type(T_LONG)), Instruction.makeInstruction(opc_land).toString());
        return testCases;
    }

    protected Hashtable<InstructionTestCase, String> emitBitwiseXorInstructionTestCases() {
        Hashtable<InstructionTestCase, String> testCases = new Hashtable<InstructionTestCase, String>();
        testCases.put(new InstructionTestCase(new Type(T_BOOLEAN)), Instruction.makeInstruction(opc_ixor).toString());
        testCases.put(new InstructionTestCase(new Type(T_BYTE)), Instruction.makeInstruction(opc_ixor).toString());
        testCases.put(new InstructionTestCase(new Type(T_SHORT)), Instruction.makeInstruction(opc_ixor).toString());
        testCases.put(new InstructionTestCase(new Type(T_SMALL_INTEGRAL)), Instruction.makeInstruction(opc_ixor).toString());
        testCases.put(new InstructionTestCase(new Type(T_INT)), Instruction.makeInstruction(opc_ixor).toString());
        testCases.put(new InstructionTestCase(new Type(T_LONG)), Instruction.makeInstruction(opc_lxor).toString());
        return testCases;
    }

    protected Hashtable<InstructionTestCase, String> emitLeftShiftInstructionTestCases() {
        Hashtable<InstructionTestCase, String> testCases = new Hashtable<InstructionTestCase, String>();
        testCases.put(new InstructionTestCase(new Type(T_BOOLEAN)), Instruction.makeInstruction(opc_ishl).toString());
        testCases.put(new InstructionTestCase(new Type(T_BYTE)), Instruction.makeInstruction(opc_ishl).toString());
        testCases.put(new InstructionTestCase(new Type(T_SHORT)), Instruction.makeInstruction(opc_ishl).toString());
        testCases.put(new InstructionTestCase(new Type(T_SMALL_INTEGRAL)), Instruction.makeInstruction(opc_ishl).toString());
        testCases.put(new InstructionTestCase(new Type(T_INT)), Instruction.makeInstruction(opc_ishl).toString());
        testCases.put(new InstructionTestCase(new Type(T_LONG)), Instruction.makeInstruction(opc_lshl).toString());
        return testCases;
    }

    protected Hashtable<InstructionTestCase, String> emitRightShiftInstructionTestCases() {
        Hashtable<InstructionTestCase, String> testCases = new Hashtable<InstructionTestCase, String>();
        testCases.put(new InstructionTestCase(new Type(T_BOOLEAN)), Instruction.makeInstruction(opc_ishr).toString());
        testCases.put(new InstructionTestCase(new Type(T_BYTE)), Instruction.makeInstruction(opc_ishr).toString());
        testCases.put(new InstructionTestCase(new Type(T_SHORT)), Instruction.makeInstruction(opc_ishr).toString());
        testCases.put(new InstructionTestCase(new Type(T_SMALL_INTEGRAL)), Instruction.makeInstruction(opc_ishr).toString());
        testCases.put(new InstructionTestCase(new Type(T_INT)), Instruction.makeInstruction(opc_ishr).toString());
        testCases.put(new InstructionTestCase(new Type(T_LONG)), Instruction.makeInstruction(opc_lshr).toString());
        return testCases;
    }

    protected Hashtable<InstructionTestCase, String> emitUnsignedRightShiftInstructionTestCases() {
        Hashtable<InstructionTestCase, String> testCases = new Hashtable<InstructionTestCase, String>();
        testCases.put(new InstructionTestCase(new Type(T_BOOLEAN)), Instruction.makeInstruction(opc_iushr).toString());
        testCases.put(new InstructionTestCase(new Type(T_BYTE)), Instruction.makeInstruction(opc_iushr).toString());
        testCases.put(new InstructionTestCase(new Type(T_SHORT)), Instruction.makeInstruction(opc_iushr).toString());
        testCases.put(new InstructionTestCase(new Type(T_SMALL_INTEGRAL)), Instruction.makeInstruction(opc_iushr).toString());
        testCases.put(new InstructionTestCase(new Type(T_INT)), Instruction.makeInstruction(opc_iushr).toString());
        testCases.put(new InstructionTestCase(new Type(T_LONG)), Instruction.makeInstruction(opc_lushr).toString());
        return testCases;
    }

    protected Hashtable<InstructionTestCase, String[]> emitLtInstructionsTestCases() {
        Hashtable<InstructionTestCase, String[]> testCases = new Hashtable<InstructionTestCase, String[]>();
        testCases.put(new InstructionTestCase(new Type(T_SHORT)), new String[] { Instruction.makeInstruction(opc_if_icmpge, 0).toString() });
        testCases.put(new InstructionTestCase(new Type(T_LONG)), new String[] { Instruction.makeInstruction(opc_ifge,0).toString(), Instruction.makeInstruction(opc_lcmp).toString() });
        testCases.put(new InstructionTestCase(new Type(T_FLOAT)), new String[] { Instruction.makeInstruction(opc_ifge,0).toString(), Instruction.makeInstruction(opc_fcmpg).toString() });
        testCases.put(new InstructionTestCase(new Type(T_DOUBLE)), new String[] { Instruction.makeInstruction(opc_ifge,0).toString(), Instruction.makeInstruction(opc_dcmpg).toString() });
        return testCases;
    }

    protected Hashtable<InstructionTestCase, String[]> emitGtInstructionsTestCases() {
        Hashtable<InstructionTestCase, String[]> testCases = new Hashtable<InstructionTestCase, String[]>();
        testCases.put(new InstructionTestCase(new Type(T_SHORT)), new String[] { Instruction.makeInstruction(opc_if_icmple, 0).toString() });
        testCases.put(new InstructionTestCase(new Type(T_LONG)), new String[] { Instruction.makeInstruction(opc_ifle,0).toString(), Instruction.makeInstruction(opc_lcmp).toString() });
        testCases.put(new InstructionTestCase(new Type(T_FLOAT)), new String[] { Instruction.makeInstruction(opc_ifle,0).toString(), Instruction.makeInstruction(opc_fcmpl).toString() });
        testCases.put(new InstructionTestCase(new Type(T_DOUBLE)), new String[] { Instruction.makeInstruction(opc_ifle,0).toString(), Instruction.makeInstruction(opc_dcmpl).toString() });
        return testCases;
    }

    protected Hashtable<InstructionTestCase, String[]> emitGeqInstructionsTestCases() {
        Hashtable<InstructionTestCase, String[]> testCases = new Hashtable<InstructionTestCase, String[]>();
        testCases.put(new InstructionTestCase(new Type(T_SHORT)), new String[] { Instruction.makeInstruction(opc_if_icmplt, 0).toString() });
        testCases.put(new InstructionTestCase(new Type(T_LONG)), new String[] { Instruction.makeInstruction(opc_iflt,0).toString(), Instruction.makeInstruction(opc_lcmp).toString() });
        testCases.put(new InstructionTestCase(new Type(T_FLOAT)), new String[] { Instruction.makeInstruction(opc_iflt,0).toString(), Instruction.makeInstruction(opc_fcmpl).toString() });
        testCases.put(new InstructionTestCase(new Type(T_DOUBLE)), new String[] { Instruction.makeInstruction(opc_iflt,0).toString(), Instruction.makeInstruction(opc_dcmpl).toString() });
        return testCases;
    }

    protected Hashtable<InstructionTestCase, String[]> emitLeqInstructionsTestCases() {
        Hashtable<InstructionTestCase, String[]> testCases = new Hashtable<InstructionTestCase, String[]>();
        testCases.put(new InstructionTestCase(new Type(T_SHORT)), new String[] { Instruction.makeInstruction(opc_if_icmpgt, 0).toString() });
        testCases.put(new InstructionTestCase(new Type(T_LONG)), new String[] { Instruction.makeInstruction(opc_ifgt,0).toString(), Instruction.makeInstruction(opc_lcmp).toString() });
        testCases.put(new InstructionTestCase(new Type(T_FLOAT)), new String[] { Instruction.makeInstruction(opc_ifgt,0).toString(), Instruction.makeInstruction(opc_fcmpg).toString() });
        testCases.put(new InstructionTestCase(new Type(T_DOUBLE)), new String[] { Instruction.makeInstruction(opc_ifgt,0).toString(), Instruction.makeInstruction(opc_dcmpg).toString() });
        return testCases;
    }

    protected Hashtable<InstructionTestCase, String[]> emitEqInstructionsTestCases() throws ClassException {
        Hashtable<InstructionTestCase, String[]> testCases = new Hashtable<InstructionTestCase, String[]>();
        testCases.put(new InstructionTestCase(new Type(T_SHORT)), new String[] { Instruction.makeInstruction(opc_if_icmpeq, 0).toString() });
        testCases.put(new InstructionTestCase(new Type(T_LONG)), new String[] { Instruction.makeInstruction(opc_ifeq,0).toString(), Instruction.makeInstruction(opc_lcmp).toString() });
        testCases.put(new InstructionTestCase(new Type(T_FLOAT)), new String[] { Instruction.makeInstruction(opc_ifeq,0).toString(), Instruction.makeInstruction(opc_fcmpg).toString() });
        testCases.put(new InstructionTestCase(new Type(T_DOUBLE)), new String[] { Instruction.makeInstruction(opc_ifeq,0).toString(), Instruction.makeInstruction(opc_dcmpg).toString() });
        testCases.put(new InstructionTestCase(new Type(T_CLASS)), new String[] { Instruction.makeInstruction(opc_if_acmpeq,0).toString() });
        testCases.put(new InstructionTestCase(new Type(T_ARRAY)), new String[] { Instruction.makeInstruction(opc_if_acmpeq,0).toString() });
        testCases.put(new InstructionTestCase(new Type(T_BOOLEAN), new Value(true), new Variable(0, "B")), new String[] { Instruction.makeInstruction(opc_ifne,0).toString() });
        testCases.put(new InstructionTestCase(new Type(T_BOOLEAN), new Variable(0, "B"), new Value(true)), new String[] { Instruction.makeInstruction(opc_ifne,0).toString() });
        testCases.put(new InstructionTestCase(new Type(T_BOOLEAN), new Value(false), new Variable(0, "B")), new String[] { Instruction.makeInstruction(opc_ifeq,0).toString() });
        testCases.put(new InstructionTestCase(new Type(T_BOOLEAN), new Variable(0, "B"), new Value(false)), new String[] { Instruction.makeInstruction(opc_ifeq,0).toString() });
        testCases.put(new InstructionTestCase(new Type(T_BOOLEAN), new Variable(0, "B"), new Variable(1, "B")), new String[] { Instruction.makeInstruction(opc_if_icmpeq,0).toString() });
        return testCases;
    }

    protected Hashtable<InstructionTestCase, String[]> emitNeqInstructionsTestCases() throws ClassException {
        Hashtable<InstructionTestCase, String[]> testCases = new Hashtable<InstructionTestCase, String[]>();
        testCases.put(new InstructionTestCase(new Type(T_SHORT)), new String[] { Instruction.makeInstruction(opc_if_icmpne, 0).toString() });
        testCases.put(new InstructionTestCase(new Type(T_LONG)), new String[] { Instruction.makeInstruction(opc_ifne,0).toString(), Instruction.makeInstruction(opc_lcmp).toString() });
        testCases.put(new InstructionTestCase(new Type(T_FLOAT)), new String[] { Instruction.makeInstruction(opc_ifne,0).toString(), Instruction.makeInstruction(opc_fcmpg).toString() });
        testCases.put(new InstructionTestCase(new Type(T_DOUBLE)), new String[] { Instruction.makeInstruction(opc_ifne,0).toString(), Instruction.makeInstruction(opc_dcmpg).toString() });
        testCases.put(new InstructionTestCase(new Type(T_CLASS)), new String[] { Instruction.makeInstruction(opc_if_acmpne,0).toString() });
        testCases.put(new InstructionTestCase(new Type(T_ARRAY)), new String[] { Instruction.makeInstruction(opc_if_acmpne,0).toString() });
        testCases.put(new InstructionTestCase(new Type(T_BOOLEAN), new Value(true), new Variable(0, "B")), new String[] { Instruction.makeInstruction(opc_ifeq,0).toString() });
        testCases.put(new InstructionTestCase(new Type(T_BOOLEAN), new Variable(0, "B"), new Value(true)), new String[] { Instruction.makeInstruction(opc_ifeq,0).toString() });
        testCases.put(new InstructionTestCase(new Type(T_BOOLEAN), new Value(false), new Variable(0, "B")), new String[] { Instruction.makeInstruction(opc_ifne,0).toString() });
        testCases.put(new InstructionTestCase(new Type(T_BOOLEAN), new Variable(0, "B"), new Value(false)), new String[] { Instruction.makeInstruction(opc_ifne,0).toString() });
        testCases.put(new InstructionTestCase(new Type(T_BOOLEAN), new Variable(0, "B"), new Variable(1, "B")), new String[] { Instruction.makeInstruction(opc_if_icmpne,0).toString() });
        return testCases;
    }

    private static boolean isDefiniteLengthInstruction(int nextop) {
        return opcLengths[nextop] >= 0;
    }

    private static int determineInstructionLength(final int opCode, final int index, final byte[] bytes) throws ClassException {
        int indexLocal = index;
        if (isDefiniteLengthInstruction(opCode)) {
            return opcLengths[opCode];
        }

        int startIndex = indexLocal;
        while ((++indexLocal) % 4 != 0) {
            if ((bytes[indexLocal] & 0xFF) != 0)
                throw new ClassException("Illegal padding in instruction " + opCode + " at index " + indexLocal);
        }

        int instrLength;
        if (opCode == 0xAA) {
            indexLocal += 4;
            int lowIndex = Attribute.readU4(bytes, indexLocal);
            indexLocal += 4;
            int highIndex = Attribute.readU4(bytes, indexLocal);
            indexLocal += 4;
            instrLength = (indexLocal - startIndex) + (highIndex - lowIndex + 1) * 4;
        } else {
            indexLocal += 4;
            int numPairs = Attribute.readU4(bytes, indexLocal);
            indexLocal += 4;
            instrLength = (indexLocal - startIndex) + numPairs * 2 * 4;
        }

        return instrLength;
    }

    private void setupStreams() {
        System.setOut(new PrintStream(outContent));
        System.setErr(new PrintStream(errContent));
    }

    protected class InstructionTestCase {
        int opcode;
        int arg1;
        Type type;
        Type expressionType;
        int argumentNumber;
        Expression arg0Expression;
        Expression arg1Expression;

        protected InstructionTestCase(int opcode, int arg1) {
            this.opcode = opcode;
            this.arg1 = arg1;
        }

        protected InstructionTestCase(Type type) {
            this.type = type;
        }

        protected InstructionTestCase(Type type, Expression arg0, Expression arg1) {
            this.type = type;
            this.arg0Expression = arg0;
            this.arg1Expression = arg1;
        }

        protected InstructionTestCase(Type type, Type expressionType) {
            this.type = type;
            this.expressionType = expressionType;
        }

        protected InstructionTestCase(Type type, int argumentNumber) {
            this.type = type;
            this.argumentNumber = argumentNumber;
        }
    }
}
