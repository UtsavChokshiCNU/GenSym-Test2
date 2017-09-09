package com.gensym.classtools;

import com.gensym.helpers.ObjectsFactory;
import org.junit.Before;
import org.junit.Test;

import java.util.Hashtable;
import java.util.Vector;

import static com.gensym.classtools.RuntimeConstants.*;
import static com.gensym.helpers.ObjectsFactory.anyBoolean;
import static com.gensym.helpers.ObjectsFactory.anyInteger;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.mockito.Matchers.any;
import static org.mockito.Matchers.anyString;
import static org.powermock.api.mockito.PowerMockito.mock;
import static org.powermock.api.mockito.PowerMockito.when;

public class VariableTest {
    private Variable sut;
    private EmitState state;

    @Before
    public void init() throws ClassException {
        this.sut = new Variable(0, Character.toString(SIGC_VOID));
        this.state = new EmitState(new ConstantPool(), new Vector(), new Vector(), new Vector());
        this.state.scope = mock(VariableScope.class);
    }

    @Test
    public void test_emit_always_addsInstruction() throws ClassException {
        // Arrange
        Hashtable<VariableTestCase, String> key = emitTestCases();
        Statement continuation = new Statement();

        for (VariableTestCase testCase : key.keySet()) {
            this.sut = new Variable(testCase.argumentNumber, testCase.type);

            // Act
            sut.emit(this.state, anyBoolean(), continuation);

            // Assert
            assertEquals(key.get(testCase), this.state.instructions.lastElement().toString());
        }
    }

    @Test
    public void test_isConstantExpression_always_returnsFalse() {
        // Arrange
        // Nothing to arrange

        // Act & Assert
        assertFalse(this.sut.isConstantExpression());
    }

    @Test
    public void test_generateVariableIds_varNameSet_generatesId() throws ClassException {
        // Arrange
        String variableName = ObjectsFactory.anyString();
        String type = Character.toString(SIGC_VOID);
        this.sut = new Variable(variableName, type);
        when(this.state.scope.getVariableId(variableName, this.sut.expressionType)).thenReturn(anyInteger());

        // Act
        this.sut.generateVariableIds(this.state);

        // Assert
        assertEquals(this.state.scope.getVariableId(variableName, this.sut.expressionType), this.sut.argumentNumber);
    }

    // Assert
    @Test(expected = ClassException.class)
    public void test_generateVariableIds_argNumAndVarNameNotSet_exception() throws ClassException {
        // Arrange
        this.sut = new Variable(-1, Character.toString(SIGC_VOID));

        // Act
        this.sut.generateVariableIds(this.state);
    }

    @Test
    public void test_toString_always_returnsVariableStringRep() throws ClassException {
        // Arrange
        String type = Character.toString(SIGC_INT);
        this.sut = new Variable(ObjectsFactory.anyString(), type);
        String expected = "<Variable, name = " + this.sut.getVariableName() + ", type = " + this.sut.expressionType + ">";

        // Act & Assert
        assertEquals(expected, this.sut.toString());
    }
    
    private Hashtable<VariableTestCase, String> emitTestCases() {
        Hashtable<VariableTestCase, String> testCases = new Hashtable<VariableTestCase, String>();
        testCases.put(new VariableTestCase(0, Character.toString(SIGC_VOID)), Instruction.makeInstruction(opc_aload_0).toString());
        testCases.put(new VariableTestCase(1, Character.toString(SIGC_ARRAY) + Character.toString(SIGC_INT)), Instruction.makeInstruction(opc_aload_1).toString());
        testCases.put(new VariableTestCase(2, Character.toString(SIGC_ARRAY) + Character.toString(SIGC_INT)), Instruction.makeInstruction(opc_aload_2).toString());
        testCases.put(new VariableTestCase(3, Character.toString(SIGC_ARRAY) + Character.toString(SIGC_INT)), Instruction.makeInstruction(opc_aload_3).toString());
        testCases.put(new VariableTestCase(4, Character.toString(SIGC_ARRAY) + Character.toString(SIGC_INT)), Instruction.makeInstruction(opc_aload, 4).toString());
        testCases.put(new VariableTestCase(1, Character.toString(SIGC_INT)), Instruction.makeInstruction(opc_iload_1).toString());
        testCases.put(new VariableTestCase(2, Character.toString(SIGC_INT)), Instruction.makeInstruction(opc_iload_2).toString());
        testCases.put(new VariableTestCase(3, Character.toString(SIGC_INT)), Instruction.makeInstruction(opc_iload_3).toString());
        testCases.put(new VariableTestCase(4, Character.toString(SIGC_INT)), Instruction.makeInstruction(opc_iload, 4).toString());
        testCases.put(new VariableTestCase(1, Character.toString(SIGC_SHORT)), Instruction.makeInstruction(opc_iload_1).toString());
        testCases.put(new VariableTestCase(2, Character.toString(SIGC_SHORT)), Instruction.makeInstruction(opc_iload_2).toString());
        testCases.put(new VariableTestCase(3, Character.toString(SIGC_SHORT)), Instruction.makeInstruction(opc_iload_3).toString());
        testCases.put(new VariableTestCase(4, Character.toString(SIGC_SHORT)), Instruction.makeInstruction(opc_iload, 4).toString());
        testCases.put(new VariableTestCase(1, Character.toString(SIGC_BYTE)), Instruction.makeInstruction(opc_iload_1).toString());
        testCases.put(new VariableTestCase(2, Character.toString(SIGC_BYTE)), Instruction.makeInstruction(opc_iload_2).toString());
        testCases.put(new VariableTestCase(3, Character.toString(SIGC_BYTE)), Instruction.makeInstruction(opc_iload_3).toString());
        testCases.put(new VariableTestCase(4, Character.toString(SIGC_BYTE)), Instruction.makeInstruction(opc_iload, 4).toString());
        testCases.put(new VariableTestCase(1, Character.toString(SIGC_DOUBLE)), Instruction.makeInstruction(opc_dload_1).toString());
        testCases.put(new VariableTestCase(2, Character.toString(SIGC_DOUBLE)), Instruction.makeInstruction(opc_dload_2).toString());
        testCases.put(new VariableTestCase(3, Character.toString(SIGC_DOUBLE)), Instruction.makeInstruction(opc_dload_3).toString());
        testCases.put(new VariableTestCase(4, Character.toString(SIGC_DOUBLE)), Instruction.makeInstruction(opc_dload, 4).toString());
        testCases.put(new VariableTestCase(1, Character.toString(SIGC_LONG)), Instruction.makeInstruction(opc_lload_1).toString());
        testCases.put(new VariableTestCase(2, Character.toString(SIGC_LONG)), Instruction.makeInstruction(opc_lload_2).toString());
        testCases.put(new VariableTestCase(3, Character.toString(SIGC_LONG)), Instruction.makeInstruction(opc_lload_3).toString());
        testCases.put(new VariableTestCase(4, Character.toString(SIGC_LONG)), Instruction.makeInstruction(opc_lload, 4).toString());
        testCases.put(new VariableTestCase(1, Character.toString(SIGC_FLOAT)), Instruction.makeInstruction(opc_fload_1).toString());
        testCases.put(new VariableTestCase(2, Character.toString(SIGC_FLOAT)), Instruction.makeInstruction(opc_fload_2).toString());
        testCases.put(new VariableTestCase(3, Character.toString(SIGC_FLOAT)), Instruction.makeInstruction(opc_fload_3).toString());
        testCases.put(new VariableTestCase(4, Character.toString(SIGC_FLOAT)), Instruction.makeInstruction(opc_fload, 4).toString());
        return testCases;
    }

    private class VariableTestCase {
        int argumentNumber;
        String type;

        VariableTestCase(int argumentNumber, String type) {
            this.argumentNumber = argumentNumber;
            this.type = type;
        }
    }
}
