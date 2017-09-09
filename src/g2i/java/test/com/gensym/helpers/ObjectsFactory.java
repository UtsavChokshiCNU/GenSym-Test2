package com.gensym.helpers;

import com.gensym.util.Sequence;
import com.gensym.util.Structure;
import com.gensym.util.Symbol;

import static com.gensym.util.symbol.AttributeExportSymbols.*;
import static com.gensym.util.symbol.OverrideSymbols.FIELD_NAME_;
import static com.gensym.util.symbol.OverrideSymbols.INITIAL_VALUE_;

public class ObjectsFactory {
    public static final Symbol TYPE_OR_OPERATOR_ = Symbol.intern("TYPE-OR-OPERATOR");
    public static final Symbol OPERANDS_ = Symbol.intern("OPERANDS");
    public static final Symbol ORIGINAL_ATTRIBUTE_NAME_ = Symbol.intern("ORIGINAL-ATTRIBUTE-NAME");

    private static int typeOrOperatorIdx = 0;
    private static int LastInteger = 1;
    private static int SamplesCount = 10;

    public static boolean anyBoolean() {
        return LastInteger++ % 2 == 0;
    }

    public static boolean[] anyBooleansArray() {
        boolean[] array = new boolean[SamplesCount];

        for (int idx = 0; idx < SamplesCount; idx++) {
            array[idx] = anyBoolean();
        }

        return array;
    }

    public static int anyInteger() {
        return LastInteger++;
    }

    public static Object[] anyObjectsArray() {
        Object[] array = new Object[SamplesCount];

        for (int idx = 0; idx < SamplesCount; idx++) {
            array[idx] = new Object();
        }

        return array;
    }

    public static Sequence anyObjectsSequence() {
        Sequence array = new Sequence();

        for (int idx = 0; idx < SamplesCount; idx++) {
            array.add(new Object());
        }

        return array;
    }

    public static String anyString() {
        return "string" + LastInteger++;
    }

    public static String anyLongString(int length) {
        String string = "string" + LastInteger++;

        while (string.length() < length) {
            string += LastInteger++;
        }

        return string;
    }

    public static String[] anyStringsArray() {
        String[] array = new String[SamplesCount];

        for (int idx = 0; idx < SamplesCount; idx++) {
            array[idx] = anyString();
        }

        return array;
    }

    public static Sequence anyStringsSequence() {
        Sequence sequence = new Sequence();

        for (int i = 0; i < SamplesCount; i++) {
            sequence.addElement(com.gensym.helpers.ObjectsFactory.anyString());
        }

        return sequence;
    }

    public static Structure anyStructure() {
        Structure structure = new Structure();
        structure.setAttributeValue(ATTRIBUTE_NAME_, anySymbol());
        structure.setAttributeValue(ORIGINAL_ATTRIBUTE_NAME_, anySymbol());
        structure.setAttributeValue(DEFINING_CLASS_, anySymbol());
        structure.setAttributeValue(TYPE_, anyString());
        structure.setAttributeValue(VALUE_READABLE_, anyBoolean());
        structure.setAttributeValue(VALUE_WRITABLE_, anyBoolean());
        structure.setAttributeValue(IS_SYSTEM_DEFINED_, anyBoolean());
        structure.setAttributeValue(OPERANDS_, anyStringsSequence());
        structure.setAttributeValue(TYPE_OR_OPERATOR_, anyTypeOrOperator());

        structure.setAttributeValue(FIELD_NAME_, Symbol.intern(com.gensym.helpers.ObjectsFactory.anyString()));
        structure.setAttributeValue(INITIAL_VALUE_, com.gensym.helpers.ObjectsFactory.anyString());
        return structure;
    }

    public static Sequence anyStructuresSequence() {
        Sequence sequence = new Sequence();

        for (int i = 0; i < SamplesCount; i++) {
            sequence.add(com.gensym.helpers.ObjectsFactory.anyStructure());
        }

        return sequence;
    }

    public static Symbol anySymbol() {
        return Symbol.intern(anyString());
    }

    public static Symbol anyLongSymbol(int length) {
        return Symbol.intern(anyLongString(length));
    }

    public static Symbol[] anySymbolsArray() {
        Symbol[] array = new Symbol[SamplesCount];

        for (int idx = 0; idx < SamplesCount; idx++) {
            array[idx] = anySymbol();
        }

        return array;
    }

    public static Sequence anySymbolsSequence() {
        Sequence sequence = new Sequence(SamplesCount);

        for (int idx = 0; idx < SamplesCount; idx++) {
            sequence.add(anySymbol());
        }

        return sequence;
    }

    private static Symbol anyTypeOrOperator() {
        if (typeOrOperatorIdx == 5) {
            typeOrOperatorIdx = 0;
        }

        return new Symbol[] {
                Symbol.intern("FLOAT"),
                Symbol.intern("INTEGER"),
                Symbol.intern("LONG"),
                Symbol.intern("SYMBOL"),
                Symbol.intern("TEXT")
        }[typeOrOperatorIdx++];
    }

    public static double anyDouble() {
        return LastInteger++;
    }
}
