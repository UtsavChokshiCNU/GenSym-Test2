package com.gensym.classtools;

import org.junit.Test;

import java.util.Vector;

import static com.gensym.helpers.ObjectsFactory.anyInteger;
import static com.gensym.helpers.ObjectsFactory.anyString;
import static org.junit.Assert.*;

public class ValueTest extends ValueTestHelper {
    // Assert
    @Test(expected = ClassException.class)
    public void test_instance_anyObject_throwsException() throws ClassException {
        // Arrange
        // Nothing to arrange

        // Act
        this.sut = new Value(new Object());
    }

    @Test
    public void test_instance_nullObject_doesNotThrowException() throws ClassException {
        // Arrange
        // Nothing to arrange

        try {
            // Act
            this.sut = new Value((Object) null);
        } catch (Exception ex) {
            fail("Value constructor: Should not throw exception.");
        }
    }

    @Test
    public void test_instance_nullString_doesNotThrowException() throws ClassException {
        // Arrange
        // Nothing to arrange

        try {
            // Act
            this.sut = new Value(null);
        } catch (Exception ex) {
            fail("Value constructor: Should not throw exception.");
        }
    }

    @Test
    public void test_canFitInSingleByte_singleByte_returnsTrue() throws ClassException {
        for (Object value : singleByteTestCases) {
            // Arrange
            createSut(value);

            // Act & Assert
            assertTrue(this.sut.canFitInSingleByte());
        }
    }

    @Test
    public void test_canFitInSingleByte_multipleBytes_returnsFalse() throws ClassException {
        for (Object value : multipleByteTestCases) {
            // Arrange
            createSut(value);

            // Act & Assert
            assertFalse(this.sut.canFitInSingleByte());
        }
    }

    @Test
    public void test_canFitInSingleSignedByte_singleByte_returnsTrue() throws ClassException {
        for (Object value : singleSignedByteTestCases) {
            // Arrange
            createSut(value);

            // Act & Assert
            assertTrue(this.sut.canFitInSingleSignedByte());
        }
    }

    @Test
    public void test_canFitInSingleSignedByte_multipleBytes_returnsFalse() throws ClassException {
        for (Object value : multipleSignedByteTestCases) {
            // Arrange
            createSut(value);

            // Act & Assert
            assertFalse(this.sut.canFitInSingleSignedByte());
        }
    }

    @Test
    public void test_isZero_isZero_returnsTrue() throws ClassException {
        for (Object value : zeroTestCases) {
            // Arrange
            createSut(value);

            // Act & Assert
            assertTrue(this.sut.isZero());
        }
    }

    @Test
    public void test_isZero_isNonNumeric_returnsFalse() throws ClassException {
        for (Object value : nonNumericTestCases) {
            // Arrange
            createSut(value);

            // Act & Assert
            assertFalse(this.sut.isZero());
        }
    }

    @Test
    public void test_isZero_isNonZero_returnsFalse() throws ClassException {
        for (Object value : nonZeroTestCases) {
            // Arrange
            createSut(value);

            // Act & Assert
            assertFalse(this.sut.isZero());
        }
    }

    @Test
    public void test_isNull_isNull_returnsTrue() throws ClassException {
        // Arrange
        createSut(null);

        // Act & Assert
        assertTrue(this.sut.isNull());
    }

    @Test
    public void test_isNull_isNotNull_returnsTrue() throws ClassException {
        for (Object value : nonNullTestCases) {
            // Arrange
            createSut(value);

            // Act & Assert
            assertFalse(this.sut.isNull());
        }
    }

    @Test
    public void test_isConstantExpression_always_returnsTrue() throws ClassException {
        // Arrange
        createSut(null);

        // Act & Assert
        assertTrue(this.sut.isConstantExpression());
    }

    @Test
    public void test_getIntegerValueIfAny_isInteger_returnsInteger() throws ClassException {
        for (Object value : integerTestCases) {
            // Arrange
            createSut(value);

            // Act & Assert
            assertEquals(expectedInteger(value), this.sut.getIntegerValueIfAny());
        }
    }

    // Assert
    @Test(expected = ClassException.class)
    public void test_getIntegerValueIfAny_isNotInteger_throwsException() throws ClassException {
        // Arrange
        createSut((float) anyInteger());

        // Act
        this.sut.getIntegerValueIfAny();
    }

    @Test
    public void test_getLongValueIfAny_isLong_returnsLong() throws ClassException {
        // Arrange
        long value = anyInteger();
        createSut(value);

        // Act & Assert
        assertEquals(value, this.sut.getLongValueIfAny());
    }

    // Assert
    @Test(expected = ClassException.class)
    public void test_getLongValueIfAny_isNotLong_throwsException() throws ClassException {
        // Arrange
        createSut((float) anyInteger());

        // Act
        this.sut.getLongValueIfAny();
    }

    @Test
    public void test_getFloatValueIfAny_isFloat_returnsFloat() throws ClassException {
        // Arrange
        float value = anyInteger();
        createSut(value);

        // Act & Assert
        assertEquals(value, this.sut.getFloatValueIfAny(), delta);
    }

    // Assert
    @Test(expected = ClassException.class)
    public void test_getFloatValueIfAny_isNotFloat_throwsException() throws ClassException {
        // Arrange
        createSut(anyInteger());

        // Act
        this.sut.getFloatValueIfAny();
    }

    @Test
    public void test_getDoubleValueIfAny_isDouble_returnsDouble() throws ClassException {
        // Arrange
        double value = anyInteger();
        createSut(value);

        // Act & Assert
        assertEquals(value, this.sut.getDoubleValueIfAny(), delta);
    }

    // Assert
    @Test(expected = ClassException.class)
    public void test_getDoubleValueIfAny_isNotDouble_throwsException() throws ClassException {
        // Arrange
        createSut(anyInteger());

        // Act
        this.sut.getDoubleValueIfAny();
    }

    @Test
    public void test_getBooleanValueIfAny_isBoolean_returnsBoolean() throws ClassException {
        for (boolean value : booleanTestCases) {
            // Arrange
            createSut(value);

            // Act & Assert
            assertEquals(value, this.sut.getBooleanValue());
        }
    }

    // Assert
    @Test(expected = ClassException.class)
    public void test_getBooleanValueIfAny_isNotBoolean_throwsException() throws ClassException {
        // Arrange
        createSut(anyInteger());

        // Act
        this.sut.getBooleanValue();
    }

    @Test
    public void test_getStringValueIfAny_isStringValue_returnsString() throws ClassException {
        // Arrange
        String value = anyString();
        createSut(value);

        // Act & Assert
        assertEquals(value, this.sut.getStringValueIfAny());
    }

    @Test
    public void test_getStringValueIfAny_isNotStringValue_returnsNull() throws ClassException {
        for (Object value : nonStringTestCases) {
            // Arrange
            createSut(value);

            // Act & Assert
            assertNull(this.sut.getStringValueIfAny());
        }
    }

    @Test
    public void test_generateConstants_constantToBeGenerated_generatesConstant() throws ClassException {
        for (Object value : constantTestCases) {
            // Arrange
            createSut(value);

            // Act
            this.sut.generateConstants(this.constantPool);

            // Assert
            assertEquals(expectedValueConstant(value), this.sut.constant);
        }
    }

    @Test
    public void test_generateConstants_constantNotToBeGenerated_doesNotGenerate() throws ClassException {
        for (Object value : nullConstantTestCases) {
            // Arrange
            createSut(value);

            // Act
            this.sut.generateConstants(this.constantPool);

            // Assert
            assertNull(this.sut.constant);
        }
    }

    @Test
    public void test_emit_always_emitsInstructions() throws ClassException {
        // Arrange
        EmitState emitState = new EmitState(this.constantPool, new Vector(), new Vector(), new Vector());
        Statement continuation = new Statement();
        for (Object value : emitTestCases) {
            createSut(value);
            int stackSize = emitState.stackSize;

            // Act
            this.sut.emit(emitState, true, continuation);

            // Assert
            emitState.instructions.contains(expectedInstruction(value));
            assertEquals(expectedStackSize(stackSize, value), emitState.stackSize);
        }
    }

    @Test
    public void test_getPrintedRepresentation_always_returnsPrintedRepresentation() throws ClassException {
        for (Object value : printedRepresentationTestCases) {
            // Arrange
            createSut(value);

            // Act & Assert
            assertEquals(expectedPrintedRepresentation(value), this.sut.getPrintedRepresentation());
        }
    }

    @Test
    public void test_toString_always_returnsStringValue() throws ClassException {
        for (Object value : toStringTestCases) {
            // Arrange
            createSut(value);

            // Act & Assert
            assertEquals(expectedString(value), this.sut.toString());
        }
    }
}
