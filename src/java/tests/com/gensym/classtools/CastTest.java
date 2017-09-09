package com.gensym.classtools;

import org.junit.Before;
import org.junit.Test;

import java.util.Hashtable;
import java.util.Vector;

import static com.gensym.classtools.RuntimeConstants.*;
import static com.gensym.helpers.ObjectsFactory.anyString;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;

public class CastTest {
    private Cast sut;
    private EmitState state;
    private boolean leaveOnStack;
    private Statement continuation;

    @Before
    public void init() throws ClassException {
        createSut();

        this.state = new EmitState(new ConstantPool(), new Vector(), new Vector(), new Vector());
        this.leaveOnStack = false;
        this.continuation = new Statement();
    }

    // Assert
    @Test(expected = ClassException.class)
    public void test_instance_castFromNonNumericToNumeric_exception() throws ClassException {
        // Arrange
        // Nothing to arrange

        // Act
        this.sut = new Cast(String.valueOf(SIGC_INT), new Value(anyString()));
    }

    @Test
    public void test_instance_bothTypesAreSmallIntegral_expansionRequired() throws ClassException {
        // Arrange
        String toType = String.valueOf(SIGC_INT);

        // Act
        this.sut = new Cast(toType, new Value((short)1));

        // Assert
        assertTrue(this.sut.expansionRequired());
    }

    @Test
    public void test_emit_notRequireExpansion_emitsAccordingly() throws ClassException {
        // Arrange
        Type type = Type.parseType(String.valueOf(SIGC_ARRAY) + String.valueOf(SIGC_INT));
        this.sut = new Cast(type, new Value(null));
        String expectedSecondLastIns = Instruction.makeInstruction(opc_aconst_null).toString();

        ClassRef classRef =  new ClassRef(Type.className(type.getReturnTypeString()));
        classRef.generateConstants(state.pool);
        String expectedLastIns = Instruction.makeInstruction(opc_checkcast,classRef.getWhere()).toString();

        // Act
        this.sut.emit(this.state, this.leaveOnStack, this.continuation);

        // Assert
        assertEquals(expectedSecondLastIns, this.state.instructions.elementAt(this.state.instructions.size() - 2).toString());
        assertEquals(expectedLastIns, this.state.instructions.lastElement().toString());
    }

    @Test
    public void test_emit_requiresExpansion_emitsAccordingly() throws ClassException {
        // Arrange
        String expected = Instruction.makeInstruction(opc_iconst_1).toString();

        // Act
        this.sut.emit(this.state, this.leaveOnStack, this.continuation);

        // Assert
        assertEquals(expected, this.state.instructions.lastElement().toString());
    }

    @Test
    public void test_evaluateConstantExpression_definedExpressionType_evaluates() throws ClassException {
        Hashtable<CastTestCase, Expression> testCases = evaluateConstantExpressionTestCases();
        for (CastTestCase key : testCases.keySet()) {
            // Arrange
            this.sut = new Cast(key.type, key.expression);

            // Act && Assert
            assertEquals(testCases.get(key).toString(), this.sut.evaluateConstantExpression().toString());
        }
    }

    @Test
    public void test_evaluateConstantExpression_undefinedExpressionType_returnsSut() throws ClassException {
        // Arrange
        this.sut = new Cast(new Type(T_INT), new Value('A'));

        // Act && Assert
        assertEquals(this.sut.toString(), this.sut.evaluateConstantExpression().toString());
    }

    @Test
    public void test_evaluateConstantExpression_notConstantExpression_returnsSut() throws ClassException {
        // Arrange
        this.sut = new Cast(new Type(T_INT), new Variable(0, String.valueOf(SIGC_INT)));

        // Act && Assert
        assertEquals(this.sut.toString(), this.sut.evaluateConstantExpression().toString());
    }

    private void createSut() throws ClassException {
        this.sut = new Cast(String.valueOf(SIGC_INT), new Value(1));
        this.sut.setTrace(true);
    }

    private Hashtable<CastTestCase, Expression> evaluateConstantExpressionTestCases() {
        Hashtable<CastTestCase, Expression> testCases = new Hashtable<CastTestCase, Expression>();
        testCases.put(new CastTestCase(new Value(1), new Type(T_BYTE)), new Value((byte)1));
        testCases.put(new CastTestCase(new Value(2), new Type(T_SHORT)), new Value((short)2));
        testCases.put(new CastTestCase(new Value(3), new Type(T_LONG)), new Value((long)3));
        testCases.put(new CastTestCase(new Value(4), new Type(T_FLOAT)), new Value((float)4));
        testCases.put(new CastTestCase(new Value(5), new Type(T_DOUBLE)), new Value((double)5));
        testCases.put(new CastTestCase(new Value(6), new Type(T_CHAR)), new Value((char)6));
        testCases.put(new CastTestCase(new Value(7.1f), new Type(T_INT)), new Value((int)7.1f));
        testCases.put(new CastTestCase(new Value(8.2f), new Type(T_LONG)), new Value((long)8.2f));
        testCases.put(new CastTestCase(new Value(9.3f), new Type(T_DOUBLE)), new Value((double)9.3f));
        testCases.put(new CastTestCase(new Value(10.1), new Type(T_INT)), new Value((int)10.1));
        testCases.put(new CastTestCase(new Value(11.2), new Type(T_LONG)), new Value((long)11.2));
        testCases.put(new CastTestCase(new Value(12.3), new Type(T_FLOAT)), new Value((float)12.3));
        testCases.put(new CastTestCase(new Value(13L), new Type(T_INT)), new Value((int) 13L));
        testCases.put(new CastTestCase(new Value(14L), new Type(T_DOUBLE)), new Value((double) 14L));
        testCases.put(new CastTestCase(new Value(15L), new Type(T_FLOAT)), new Value((float) 15L));
        return testCases;
    }

    private class CastTestCase {
        Expression expression;
        Type type;

        CastTestCase(Expression expression, Type type) {
            this.expression = expression;
            this.type = type;
        }
    }
}
