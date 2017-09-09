package com.gensym.classtools;

import org.junit.Before;
import org.junit.Test;

import java.io.ByteArrayOutputStream;
import java.io.PrintStream;
import java.util.Hashtable;

import static com.gensym.classtools.RuntimeConstants.*;
import static org.junit.Assert.assertEquals;

public class AccessTest {
    private Access sut;
    private ByteArrayOutputStream out;

    @Before
    public void init() {
        resetSystemOut();
    }

    @Test
    public void test_isPublic_ifPublic_returnsTrue() {
        // Arrange
        Hashtable<Integer, Boolean> testCases = modifiersTestCases();
        testCases.put(ACC_PUBLIC, true);

        for (Integer key : testCases.keySet()) {
            this.sut = new Access(key);

            // Act & Assert
            assertEquals(testCases.get(key), this.sut.isPublic());
        }
    }

    @Test
    public void test_isPrivate_ifPrivate_returnsTrue() {
        // Arrange
        Hashtable<Integer, Boolean> testCases = modifiersTestCases();
        testCases.put(ACC_PRIVATE, true);

        for (Integer key : testCases.keySet()) {
            this.sut = new Access(key);

            // Act & Assert
            assertEquals(testCases.get(key), this.sut.isPrivate());
        }
    }

    @Test
    public void test_isProtected_ifProtected_returnsTrue() {
        // Arrange
        Hashtable<Integer, Boolean> testCases = modifiersTestCases();
        testCases.put(ACC_PROTECTED, true);

        for (Integer key : testCases.keySet()) {
            this.sut = new Access(key);

            // Act & Assert
            assertEquals(testCases.get(key), this.sut.isProtected());
        }
    }

    @Test
    public void test_isStatic_ifStatic_returnsTrue() {
        // Arrange
        Hashtable<Integer, Boolean> testCases = modifiersTestCases();
        testCases.put(ACC_STATIC, true);

        for (Integer key : testCases.keySet()) {
            this.sut = new Access(key);

            // Act & Assert
            assertEquals(testCases.get(key), this.sut.isStatic());
        }
    }

    @Test
    public void test_isFinal_ifFinal_returnsTrue() {
        // Arrange
        Hashtable<Integer, Boolean> testCases = modifiersTestCases();
        testCases.put(ACC_FINAL, true);

        for (Integer key : testCases.keySet()) {
            this.sut = new Access(key);

            // Act & Assert
            assertEquals(testCases.get(key), this.sut.isFinal());
        }
    }

    @Test
    public void test_isSynchronized_ifSynchronized_returnsTrue() {
        // Arrange
        Hashtable<Integer, Boolean> testCases = modifiersTestCases();
        testCases.put(ACC_SYNCHRONIZED, true);

        for (Integer key : testCases.keySet()) {
            this.sut = new Access(key);

            // Act & Assert
            assertEquals(testCases.get(key), this.sut.isSynchronized());
        }
    }

    @Test
    public void test_isVolatile_ifVolatile_returnsTrue() {
        // Arrange
        Hashtable<Integer, Boolean> testCases = modifiersTestCases();
        testCases.put(ACC_VOLATILE, true);

        for (Integer key : testCases.keySet()) {
            this.sut = new Access(key);

            // Act & Assert
            assertEquals(testCases.get(key), this.sut.isVolatile());
        }
    }

    @Test
    public void test_isTransient_ifTransient_returnsTrue() {
        // Arrange
        Hashtable<Integer, Boolean> testCases = modifiersTestCases();
        testCases.put(ACC_TRANSIENT, true);

        for (Integer key : testCases.keySet()) {
            this.sut = new Access(key);

            // Act & Assert
            assertEquals(testCases.get(key), this.sut.isTransient());
        }
    }

    @Test
    public void test_isNative_ifNative_returnsTrue() {
        // Arrange
        Hashtable<Integer, Boolean> testCases = modifiersTestCases();
        testCases.put(ACC_NATIVE, true);

        for (Integer key : testCases.keySet()) {
            this.sut = new Access(key);

            // Act & Assert
            assertEquals(testCases.get(key), this.sut.isNative());
        }
    }

    @Test
    public void test_isInterface_ifInterface_returnsTrue() {
        // Arrange
        Hashtable<Integer, Boolean> testCases = modifiersTestCases();
        testCases.put(ACC_INTERFACE, true);

        for (Integer key : testCases.keySet()) {
            this.sut = new Access(key);

            // Act & Assert
            assertEquals(testCases.get(key), this.sut.isInterface());
        }
    }

    @Test
    public void test_isAbstract_ifAbstract_returnsTrue() {
        // Arrange
        Hashtable<Integer, Boolean> testCases = modifiersTestCases();
        testCases.put(ACC_ABSTRACT, true);

        for (Integer key : testCases.keySet()) {
            this.sut = new Access(key);

            // Act & Assert
            assertEquals(testCases.get(key), this.sut.isAbstract());
        }
    }

    @Test
    public void test_isSuper_ifSuper_returnsTrue() {
        // Arrange
        Hashtable<Integer, Boolean> testCases = modifiersTestCases();
        testCases.put(ACC_SUPER, true);

        for (Integer key : testCases.keySet()) {
            this.sut = new Access(key);

            // Act & Assert
            assertEquals(testCases.get(key), this.sut.isSuper());
        }
    }

    @Test
    public void test_toStdout_always_writesInfo() {
        // Arrange
        Hashtable<Integer, String> testCases = toStdoutTestCases();

        for (Integer key : testCases.keySet()) {
            resetSystemOut();
            this.sut = new Access(key);

            // Act
            this.sut.toStdout();

            // Assert
            assertEquals(testCases.get(key), this.out.toString().trim());
        }
    }

    @Test
    public void test_getModifiers_always_returnsModifiers() {
        int[] testCases = getModifiersTestCases();
        for (int flags : testCases) {
            // Arrange
            this.sut = new Access(flags);

            // Act & Assert
            assertEquals(flags, this.sut.getModifiers());
        }
    }

    @Test
    public void test_ClassAccess_ClassAccess_returnsSuperClass() throws ClassException {
        // Arrange
        this.sut = new ClassAccess(ACC_PUBLIC | ACC_SYNCHRONIZED | ACC_INTERFACE);

        // Act
        this.sut.toStdout();

        // Assert
        assertEquals("Access Restrictions: public super interface", this.out.toString().trim());
    }

    private int[] getModifiersTestCases() {
        return new int[] {
                ACC_PUBLIC,
                ACC_PRIVATE,
                ACC_PROTECTED,
                ACC_STATIC,
                ACC_FINAL,
                ACC_SYNCHRONIZED,
                ACC_VOLATILE,
                ACC_TRANSIENT,
                ACC_NATIVE,
                ACC_INTERFACE,
                ACC_ABSTRACT,
                ACC_SUPER
        };
    }

    private Hashtable<Integer, Boolean> modifiersTestCases() {
        Hashtable<Integer, Boolean> testCases = new Hashtable<Integer, Boolean>();
        testCases.put(ACC_PUBLIC, false);
        testCases.put(ACC_PRIVATE, false);
        testCases.put(ACC_PROTECTED, false);
        testCases.put(ACC_STATIC, false);
        testCases.put(ACC_FINAL, false);
        testCases.put(ACC_SYNCHRONIZED, false);
        testCases.put(ACC_VOLATILE, false);
        testCases.put(ACC_TRANSIENT, false);
        testCases.put(ACC_NATIVE, false);
        testCases.put(ACC_INTERFACE, false);
        testCases.put(ACC_ABSTRACT, false);
        testCases.put(ACC_SUPER, false);
        return testCases;
    }

    private void resetSystemOut() {
        this.out = new ByteArrayOutputStream();
        System.setOut(new PrintStream(out));
    }

    private Hashtable<Integer, String> toStdoutTestCases() {
        Hashtable<Integer, String> testCases = new Hashtable<Integer, String>();
        testCases.put(ACC_PUBLIC | ACC_STATIC | ACC_SYNCHRONIZED, "Access Restrictions: public static synchronized");
        testCases.put(ACC_PRIVATE | ACC_VOLATILE, "Access Restrictions: private volatile");
        testCases.put(ACC_PROTECTED | ACC_FINAL | ACC_TRANSIENT, "Access Restrictions: protected final transient");
        testCases.put(ACC_PUBLIC | ACC_NATIVE, "Access Restrictions: public native");
        testCases.put(ACC_PRIVATE | ACC_ABSTRACT, "Access Restrictions: private abstract");
        testCases.put(ACC_PROTECTED | ACC_INTERFACE, "Access Restrictions: protected interface");
        return testCases;
    }
}
