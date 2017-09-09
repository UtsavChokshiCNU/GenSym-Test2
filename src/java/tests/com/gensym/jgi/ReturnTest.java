package com.gensym.jgi;

import com.gensym.helpers.ObjectsFactory;
import org.junit.Test;

import java.util.Random;

import static com.gensym.helpers.ObjectsFactory.anyInteger;
import static com.gensym.helpers.ObjectsFactory.anyString;
import static org.junit.Assert.*;

public class ReturnTest {
    //test_MethodName_StateUnderTest_ExpectedBehaviour
    @Test
    public void test_setValueInteger_onCall_verifySameValueAsInput() {
        // Arrange
        Integer i = anyInteger();
        Return_Integer target = new Return_Integer();
        // Act
        target.setValue(i);
        // Assert
        assertTrue(target.isValueSet());
        assertEquals(String.valueOf(target.getValue()), String.valueOf(i));
    }

    @Test
    public void test_setValueLong_onCall_verifySameValueAsInput() {
        // Arrange
        Random rng = new Random();
        Long i = rng.nextLong();
        Return_long target = new Return_long();
        // Act
        target.setValue(i);
        // Assert
        assertTrue(target.isValueSet());
        assertEquals(String.valueOf(target.getValue()), String.valueOf(i));
    }

    @Test
    public void test_setValueInt_onCall_verifySameValueAsInput() {
        // Arrange
        Random rng = new Random();
        int i = rng.nextInt();
        Return_int target = new Return_int();
        // Act
        target.setValue(i);
        // Assert
        assertTrue(target.isValueSet());
        assertEquals(String.valueOf(target.getValue()), String.valueOf(i));
    }

    @Test
    public void test_setValueString_onCall_verifySameValueAsInput() {
        // Arrange
        String str = anyString();
        Return_String target = new Return_String();
        // Act
        target.setValue(str);
        // Assert
        assertTrue(target.isValueSet());
        assertEquals(target.getValue(), str);
    }

    @Test
    public void test_setValueBoolean_onCall_verifySameValueAsInput() {
        // Arrange
        Boolean i = ObjectsFactory.anyBoolean();
        Return_boolean target = new Return_boolean();
        // Act
        target.setValue(i);
        // Assert
        assertTrue(target.isValueSet());
        assertEquals(String.valueOf(target.getValue()), String.valueOf(i));
    }

    @Test
    public void test_setValueObject_onCall__verifySameValueAsInput() {
        // Arrange
        Object i =  ObjectsFactory.anyObjectsArray()[0];
        Return_Object target = new Return_Object();
        // Act
        target.setValue(i);
        // Assert
        assertTrue(target.isValueSet());
        assertEquals(String.valueOf(target.getValue()), String.valueOf(i));
    }

}
