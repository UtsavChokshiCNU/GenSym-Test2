package com.gensym.classtools;

import org.junit.Before;

import static com.gensym.classtools.RuntimeConstants.*;

public class ValueTestHelper {
    protected static final double delta = 0.0001;
    protected static final boolean[] booleanTestCases = new boolean[]{false, true};
    protected static final Object[] singleByteTestCases = new Object[]{0, 1, 10, 100, 254, 255, (short) 0, (short) 1, (short) 10, (short) 100, (short) 254, (short) 255, 'A', 'B', (byte) 0, (byte) 1, (byte) 2, (byte) 100, (byte) 126, Byte.MAX_VALUE, false, true, "A", "B", "ABC"};
    protected static final Object[] multipleByteTestCases = new Object[]{256, 257, 1000, 10000, Integer.MAX_VALUE, (short) 256, (short) 257, (short) 1000, (short) 10000, Short.MAX_VALUE, 0L, 10L, 100L, 1000L, Long.MAX_VALUE, 0f, 10f, 1000f, Float.MAX_VALUE, 0.0, 10.0, 1000.0, Double.MAX_VALUE};
    protected static final Object[] singleSignedByteTestCases = new Object[]{-128, -127, 0, 1, 126, 127, (short) -128, (short) -127, (short) 0, (short) 1, (short) 126, (short) 127, 'A', 'B', (byte) -128, (byte) -127, (byte) 0, (byte) 1, (byte) 126, Byte.MAX_VALUE, false, true, "A", "B", "ABC"};
    protected static final Object[] multipleSignedByteTestCases = new Object[]{Integer.MIN_VALUE, -130, -129, 128, 129, Integer.MAX_VALUE, Short.MIN_VALUE, (short) -130, (short) -129, (short) 128, (short) 129, Short.MAX_VALUE, 0L, 10L, 100L, 1000L, Long.MAX_VALUE, 0f, 10f, 1000f, Float.MAX_VALUE, 0.0, 10.0, 1000.0, Double.MAX_VALUE};
    protected static final Object[] zeroTestCases = new Object[]{0, (short) 0, 0L, 0.0, 0f};
    protected static final Object[] nonNullTestCases = new Object[]{"A", 'A', new Object(), 1, (short) 1, 1L, 1.0, 1f, false, true};
    protected static final Object[] nonNumericTestCases = new Object[]{null, "A", 'A'};
    protected static final Object[] nonZeroTestCases = new Object[]{1, (short) 1, 1L, 1.0, 1f, false, true};
    protected static final Object[] integerTestCases = new Object[]{1, (short) 2, 'A', (byte) 3, false, true};
    protected static final Object[] nonStringTestCases = new Object[]{1, (short) 2, (byte) 3, 4L, 5f, 6.0, false, true, 'A', null};
    protected static final Object[] constantTestCases = new Object[]{0.5f, 1.5f, 2.5f, 3f, 4f, Double.MIN_VALUE, -0.5, 0.5, 1.5, Double.MAX_VALUE, Long.MIN_VALUE, -1L, 2L, Long.MAX_VALUE, Integer.MIN_VALUE, -32769, 32768, Integer.MAX_VALUE, "A", "B", "CDE"};
    protected static final Object[] nullConstantTestCases = new Object[]{0.0f, 1.0f, 2.0f, 0.0, 1.0, 0L, 1L, -32768, -32767, 32766, 32767};
    protected static final Object[] emitTestCases = new Object[]{Float.MIN_VALUE, -2.0f, -1.0f, 0.0f, 1.0f, 2.0f, 3.0f, 4.0f, Float.MAX_VALUE, Double.MIN_VALUE, -2.0, -1.0, 0.0, 1.0, 2.0, Double.MAX_VALUE, Long.MIN_VALUE, -2L, -1L, 0L, 1L, 2L, Long.MAX_VALUE, Integer.MIN_VALUE, -32769, -32768, -129, -128, -1, 0, 1, 2, 3, 4, 5, 127, 128, 32767, 32768, Integer.MAX_VALUE, null, "A", "BC", "DEF"};
    protected static final Object[] printedRepresentationTestCases = new Object[]{10, 15.0f, 20.0, 25L, false, true, null, "ABC"};
    protected static final Object[] toStringTestCases = new Object[]{10, 15.0f, 20.0, 25L, false, true, 'A', 'B', "ABC"};

    protected Value sut;
    protected ConstantPool constantPool;

    @Before
    public void init() {
        this.constantPool = new ConstantPool();
    }

    protected void createSut(Object value) throws ClassException {
        if (value == null) {
            this.sut = new Value(null);
        } else if (value instanceof Boolean) {
            this.sut = new Value(((Boolean) value).booleanValue());
        } else if (value instanceof Byte) {
            this.sut = new Value(((Byte) value).byteValue());
        } else if (value instanceof Character) {
            this.sut = new Value(((Character) value).charValue());
        } else if (value instanceof Double) {
            this.sut = new Value(((Double) value).doubleValue());
        } else if (value instanceof Float) {
            this.sut = new Value(((Float) value).floatValue());
        } else if (value instanceof Integer) {
            this.sut = new Value(((Integer) value).intValue());
        } else if (value instanceof Long) {
            this.sut = new Value(((Long) value).longValue());
        } else if (value instanceof Short) {
            this.sut = new Value(((Short) value).shortValue());
        } else if (value instanceof String) {
            this.sut = new Value(value.toString());
        }
    }

    protected Instruction expectedInstruction(Object value) {
        Instruction ins = null;

        if (value instanceof Double) {
            double doubleValue = (Double) value;
            if (Double.compare(doubleValue, 0.0) == 0)
                ins = Instruction.makeInstruction(opc_dconst_0);
            else if (Double.compare(doubleValue, 1.0) == 0)
                ins = Instruction.makeInstruction(opc_dconst_1);
            else
                ins = Instruction.makeInstruction(opc_ldc2_w, this.sut.constant.getWhere());
        } else if (value instanceof Float) {
            float floatValue = (Float) value;
            if (Float.compare(floatValue, 0.0f) == 0)
                ins = Instruction.makeInstruction(opc_fconst_0);
            else if (Float.compare(floatValue, 1.0f) == 0)
                ins = Instruction.makeInstruction(opc_fconst_1);
            else if (Float.compare(floatValue, 2.0f) == 0)
                ins = Instruction.makeInstruction(opc_fconst_2);
            else ins = chooseConstantPoolLoadInstruction(this.sut.constant.getWhere());
        } else if (value instanceof Integer) {
            int intValue = (Integer) value;
            switch (intValue) {
                case -1:
                    ins = Instruction.makeInstruction(opc_iconst_m1);
                    break;
                case 0:
                    ins = Instruction.makeInstruction(opc_iconst_0);
                    break;
                case 1:
                    ins = Instruction.makeInstruction(opc_iconst_1);
                    break;
                case 2:
                    ins = Instruction.makeInstruction(opc_iconst_2);
                    break;
                case 3:
                    ins = Instruction.makeInstruction(opc_iconst_3);
                    break;
                case 4:
                    ins = Instruction.makeInstruction(opc_iconst_4);
                    break;
                case 5:
                    ins = Instruction.makeInstruction(opc_iconst_5);
                    break;
                default:
                    if ((-129 < intValue) && (intValue < 128))
                        ins = Instruction.makeInstruction(opc_bipush, intValue);
                    else if ((-32769 < intValue) && (intValue < 32768))
                        ins = Instruction.makeInstruction(opc_sipush, intValue);
                    else
                        ins = chooseConstantPoolLoadInstruction(this.sut.constant.getWhere());
            }
        } else if (value instanceof Long) {
            long longValue = (Long) value;
            if (longValue == 0)
                ins = Instruction.makeInstruction(opc_lconst_0);
            else if (longValue == 1)
                ins = Instruction.makeInstruction(opc_lconst_1);
            else ins = Instruction.makeInstruction(opc_ldc2_w, this.sut.constant.getWhere());
        } else if (value instanceof String) {
            ins = chooseConstantPoolLoadInstruction(this.sut.constant.getWhere());
        } else if (value == null) {
            ins = Instruction.makeInstruction(opc_aconst_null);
        }

        return ins;
    }

    protected int expectedInteger(Object value) {
        if (value instanceof Boolean) {
            return (Boolean) value ? 1 : 0;
        } else if (value instanceof Byte) {
            return ((Byte) value).intValue();
        } else if (value instanceof Character) {
            return ((Character) value);
        } else if (value instanceof Integer) {
            return (Integer) value;
        } else if (value instanceof Short) {
            return ((Short) value).intValue();
        }

        return 0;
    }

    protected String expectedPrintedRepresentation(Object value) {
        if (value == null) {
            return "null";
        } else if (value instanceof Boolean) {
            return (Boolean) value ? "true" : "false";
        } else {
            return value.toString();
        }
    }

    protected int expectedStackSize(int currentStackSize, Object value) {
        if (value instanceof Double || value instanceof Long) {
            return currentStackSize + 2;
        } else {
            return currentStackSize + 1;
        }
    }

    protected String expectedString(Object value) {
        if (value instanceof Character) {
            return "<Value, type = " + this.sut.expressionType +
                    ", value = " + (int) (Character) value + ">";
        } else if (value instanceof Boolean) {
            return "<Value, type = " + this.sut.expressionType +
                    ", value = " + ((Boolean) value ? 1 : 0) + ">";
        }

        return "<Value, type = " + this.sut.expressionType +
                ", value = " + value + ">";
    }

    protected Constant expectedValueConstant(Object value) {
        ValueConstant valueConstant = null;

        if (value instanceof Double) {
            valueConstant = new ValueConstant(this.constantPool, (Double) value);
        } else if (value instanceof Float) {
            valueConstant = new ValueConstant(this.constantPool, (Float) value);
        } else if (value instanceof Integer) {
            valueConstant = new ValueConstant(this.constantPool, (Integer) value);
        } else if (value instanceof Long) {
            valueConstant = new ValueConstant(this.constantPool, (Long) value);
        } else if (value instanceof String) {
            valueConstant = new ValueConstant(this.constantPool, (String) value);
        }

        return this.constantPool.getPool(this.constantPool.member(valueConstant));
    }

    private static Instruction chooseConstantPoolLoadInstruction(int where) {
        // Later stages in the emit cannot handle the need for
        // opc_ldc's migrating to opc_ldc_w's.  This is an optimization
        // that it is a shame to miss
        //if (where > 254)
        return Instruction.makeInstruction(opc_ldc_w, where);
        //else return Instruction.makeInstruction(opc_ldc,where);
    }
}
