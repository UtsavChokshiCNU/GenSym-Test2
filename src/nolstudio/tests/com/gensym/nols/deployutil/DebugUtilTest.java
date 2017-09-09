package com.gensym.nols.deployutil;

import org.junit.After;
import org.junit.Before;
import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.TemporaryFolder;

import java.awt.*;
import java.io.*;
import java.lang.reflect.Array;
import java.util.*;

import static org.hamcrest.MatcherAssert.assertThat;
import static org.hamcrest.core.Is.is;
import static org.hamcrest.core.IsEqual.equalTo;
import static org.junit.Assert.*;

public class DebugUtilTest implements Serializable {
    private static final String ANY_STRING = "Any String";
    private static final Random randomGenerator = new Random();

    private final ByteArrayOutputStream inputStream = new ByteArrayOutputStream();
    private final ByteArrayOutputStream outContent = new ByteArrayOutputStream();
    private final Vector<File> files = new Vector<>();

    @Rule
    public TemporaryFolder temporaryFolder = new TemporaryFolder();
    private InputStream stdin;

    @Before
    public void before() {
        setupStreams();
    }

    @After
    public void after() {
        for (File file : files) {
            file.delete();
        }

        files.removeAllElements();
        cleanUpStreams();
    }

    @Test
    public void test_getName_standardColor_retColorString() {
        // Arrange
        Map<Color, String> testCases = new HashMap<>();
        testCases.put(Color.white, "White");
        testCases.put(Color.lightGray, "Light Gray");
        testCases.put(Color.gray, "Gray");
        testCases.put(Color.darkGray, "Dark Gray");
        testCases.put(Color.black, "Black");
        testCases.put(Color.red, "Red");
        testCases.put(Color.pink, "Pink");
        testCases.put(Color.orange, "Orange");
        testCases.put(Color.yellow, "Yellow");
        testCases.put(Color.green, "Green");
        testCases.put(Color.magenta, "Magenta");
        testCases.put(Color.cyan, "Cyan");
        testCases.put(Color.blue, "Blue");

        Iterator it = testCases.entrySet().iterator();
        while (it.hasNext()) {
            Map.Entry pair = (Map.Entry) it.next();

            // Act & Assert
            assertThat(DebugUtil.getName((Color) pair.getKey()), is(equalTo(pair.getValue())));
        }
    }

    @Test
    public void test_getName_nonStandardColor_retNonStandardColorString() {
        // Arrange
        // Creating any non-standard color
        Color color = Color.getHSBColor(anyFloat(100) + 5, anyFloat(150) + 10, anyFloat(200) + 15);

        // Act & Assert
        assertThat(DebugUtil.getName(color), is(equalTo("NonStandard " + color)));
    }

    @Test
    public void test_writeToFile_validObject_writesToFile() throws IOException {
        // Arrange
        // Creating random objects
        Object[] objects = new Object[]{new Integer(anyInteger()), "A String", true, false, null};

        for (Object object : objects) {
            File file = createFile();

            // Act
            boolean result = DebugUtil.writeToFile(object, file.getAbsolutePath());

            // Assert
            assertTrue(result);
            Object writtenObject = readObject(file.getAbsolutePath());
            assertThat(writtenObject, is(equalTo(object)));
        }
    }

    @Test
    public void test_writeToFile_nonSerializableObject_errorToConsole() throws IOException {
        // Arrange
        File file = createFile();
        Object nonSerializable = new NonSerializableClass("Object 1");
        String expectedErrorMessage = "Error during save of " + nonSerializable;

        // Act
        boolean result = DebugUtil.writeToFile(nonSerializable, file.getAbsolutePath());

        // Assert
        assertFalse(result);
        assertTrue(outContent.toString().contains(expectedErrorMessage));
    }

    @Test
    public void test_readFromFile_fileContainsAnObject_retObject() throws IOException {
        // Arrange
        // Creating random objects
        Object[] objects = new Object[]{new Integer(anyInteger()), "A String", true, false, null};

        for (Object object : objects) {
            File file = createFile();
            writeObject(object, file.getAbsolutePath());

            // Act
            Object result = DebugUtil.readFromFile(file.getAbsolutePath());

            // Assert
            assertThat(result, is(equalTo(object)));
        }
    }

    @Test
    public void test_readFromFile_noObjectInFile_errorToConsole() throws IOException {
        // Arrange
        File file = createFile();
        String expectedErrorMessage = "Error during load from file : " + file.getAbsolutePath();

        // Act
        Object result = DebugUtil.readFromFile(file.getAbsolutePath());

        // Assert
        assertNull(result);
        assertTrue(outContent.toString().contains(expectedErrorMessage));
    }

    @Test
    public void test_readFromFile_objectsCountSpecified_retSpecifiedObjects() throws IOException {
        // Arrange
        // Creating random objects
        File file = createFile();
        Object[] objects = new Object[]{new Integer(anyInteger()), "A String", true, false, null};
        writeObjects(objects, file.getAbsolutePath());
        int objectsToBeFetched = 3;

        // Act
        Object[] result = DebugUtil.readFromFile(file.getAbsolutePath(), objectsToBeFetched);

        // Assert
        assertThat(result.length, is(equalTo(objectsToBeFetched)));
        for (int i = 0; i < objectsToBeFetched; i++) {
            assertThat(result[i], is(equalTo(objects[i])));
        }
    }

    @Test
    public void test_readFromFile_objectsAreLessThan100_retAllObjects() throws IOException {
        // Arrange
        // Creating random objects
        File file = createFile();
        Object[] objects = new Object[]{new Integer(anyInteger()), "A String", true, false, null};
        writeObjects(objects, file.getAbsolutePath());

        // Act
        Object[] result = DebugUtil.readFromFile(file.getAbsolutePath(), 0);

        // Assert
        assertThat(result.length, is(equalTo(objects.length)));
        for (int i = 0; i < objects.length; i++) {
            assertThat(result[i], is(equalTo(objects[i])));
        }
    }

    @Test
    public void test_readFromFile_objectsAreGreaterThan100_ret100Objects() throws IOException {
        // Arrange
        // Creating random objects
        File file = createFile();
        Object[] objects = new Object[101];
        for (int i = 0; i < objects.length; i++) {
            objects[i] = anyObject();
        }

        writeObjects(objects, file.getAbsolutePath());
        int maxFetchedItemsWhenNumberIsNotMentioned = 100;

        // Act
        Object[] result = DebugUtil.readFromFile(file.getAbsolutePath(), 0);

        // Assert
        assertThat(result.length, is(maxFetchedItemsWhenNumberIsNotMentioned));
        for (int i = 0; i < maxFetchedItemsWhenNumberIsNotMentioned; i++) {
            assertThat(result[i], is(equalTo(objects[i])));
        }
    }

    @Test
    public void test_readFromFile_noObjectsInFile_errorToConsole() throws IOException {
        // Arrange
        File file = createFile();
        String expectedErrorMessage = "Error during load from file : " + file.getAbsolutePath();

        // Act
        Object result = DebugUtil.readFromFile(file.getAbsolutePath(),0);

        // Assert
        assertNull(result);
        assertTrue(outContent.toString().contains(expectedErrorMessage));
    }

    @Test
    public void test_pause_isNotPaused_dontWriteToConsole() {
        // Arrange
        DebugUtil.setPause(false);

        // Act
        DebugUtil.pause(ANY_STRING, anyBoolean());

        // Assert
        assertThat(outContent.toString().length(), is(equalTo(0)));
    }

    @Test
    public void test_pause_msgNotPassed_startsWritingWithDebugUtilPause() {
        // Arrange
        // Empty input stream
        System.setIn(new ByteArrayInputStream("\r\n".getBytes()));
        DebugUtil.setPause(true);

        // Act
        DebugUtil.pause(null, false);

        // Assert
        assertTrue(outContent.toString().startsWith("DebugUtil.pause> "));
    }

    @Test
    public void test_pause_msgPassed_startsWritingWithMessage() {
        // Arrange
        // Empty input stream
        System.setIn(new ByteArrayInputStream("\r\n".getBytes()));
        DebugUtil.setPause(true);
        String message = "Console> ";

        // Act
        DebugUtil.pause(message, false);

        // Assert
        assertTrue(outContent.toString().startsWith(message));
    }

    @Test
    public void test_printArray_objectIsNull_retNull() {
        // Arrange
        int start = anyInteger();
        int end = start + 1;

        // Act & Assert
        assertThat(DebugUtil.printArray(null, start, end), is(equalTo("null")));

    }

    // Assert
    @Test(expected = IllegalArgumentException.class)
    public void test_printArray_objectIsNotAnArray_throwsException() {
        // Arrange
        // No arrangement

        // Act
        DebugUtil.printArray(new Object());

    }

    @Test
    public void test_printArray_arrayIsEmpty_retEmptyArrayString() {
        // Arrange
        Object[] array = new Object[0];

        // Act
        assertThat(DebugUtil.printArray(array), is(equalTo("[]")));
    }

    // Assert
    @Test(expected = Exception.class)
    public void test_printArray_startIndexIsInvalid_throwsException() {
        // Arrange
        // Creating an array of 50 objects (random number, no specific reason to select it)
        Object[] array = new Object[50];
        for (int i = 0; i < array.length; i++) {
            array[i] = anyObject();
        }

        // Act
        String result = DebugUtil.printArray(array, -1,array.length -1);
    }

    // Assert
    @Test
    public void test_printArray_endIndexIsMinusOne_retAllObjects() {
        // Arrange
        // Creating an array of 50 objects (random number, no specific reason to select it)
        Object[] array = new Object[50];
        for (int i = 0; i < array.length; i++) {
            array[i] = anyObject();
        }

        // Act
        String result = DebugUtil.printArray(array, 0,-1);

        // Assert
        assertNotNull(result);
        assertThat(result, is(equalTo(stringRepresentationOfObjects(array))));
    }

    @Test
    public void test_printArray_indicesNotSpecified_retAllObjects() {
        // Arrange
        // Creating an array of 50 objects (random number, no specific reason to select it)
        Object[] array = new Object[50];
        for (int i = 0; i < array.length; i++) {
            array[i] = anyObject();
        }

        // Act
        String result = DebugUtil.printArray(array);

        // Assert
        assertNotNull(result);
        assertThat(result, is(equalTo(stringRepresentationOfObjects(array))));
    }

    @Test
    public void test_printArray_indicesAreSpecified_retSpecifiedObjects() {
        // Arrange
        // Creating an array of 50 objects (random number, no specific reason to select it)
        Object[] array = new Object[50];
        for (int i = 0; i < array.length; i++) {
            array[i] = anyObject();
        }

        int start = 10; // random number, no specific reason to select it
        int end = 30;   // random number greater than start, no specific reason to select it

        // Act
        String result = DebugUtil.printArray(array, start, end);

        // Assert
        assertNotNull(result);
        assertThat(result, is(equalTo(stringRepresentationOfObjects(array, start, end))));
    }

    @Test
    public void test_describe_objectIsNull_retNull() {
        // Arrange
        // No arrangement

        // Act & Assert
        assertThat(DebugUtil.describe(null), is(equalTo("null")));
    }

    @Test
    public void test_describe_objectIsNotNull_retDescription() {
        // Arrange
        Object object = new NonSerializableClass("Non Serializable Object 1");
        String expected = "Class " + object.getClass().getName() + " -> " + object.toString();

        // Act & Assert
        assertThat(DebugUtil.describe(object), is(equalTo(expected)));
    }

    @Test
    public void test_removeCharFromString_charNotInString_retSameString() {
        // Arrange
        String string = "This sentence does not contain small Y.";
        char charToRemove = 'y';

        // Act & Assert
        assertThat(DebugUtil.removeCharFromString(string, charToRemove), is(equalTo(string)));
    }

    @Test
    public void test_removeCharFromString_charInString_removesCharFromString() {
        // Arrange
        String string = "This y sentence y contains y multiple y small y characters.";
        String expected = "This  sentence  contains  multiple  small  characters.";
        char charToRemove = 'y';

        // Act & Assert
        assertThat(DebugUtil.removeCharFromString(string, charToRemove), is(equalTo(expected)));
    }

    // -- Helper Methods --

    private float anyFloat() {
        return randomGenerator.nextInt() + 1;
    }

    private float anyFloat(int maxValue) {
        return randomGenerator.nextInt(maxValue);
    }

    private int anyInteger() {
        return randomGenerator.nextInt() + 1;
    }

    private Object anyObject() {
        int anyInt = anyInteger();
        return anyInt % 5 == 0
                ? anyInteger()
                : anyInt % 5 == 1
                    ? "A String"
                    : anyInt % 5 == 2
                        ? anyFloat()
                        : anyInt % 5 == 3
                            ? anyBoolean()
                            : null;

    }

    private boolean anyBoolean() {
        return anyInteger() % 2 == 0;
    }

    private void cleanUpStreams() {
        System.setOut(null);
        System.setIn(stdin);
    }

    private File createFile() throws IOException {
        File file = temporaryFolder.newFile();
        files.addElement(file);
        return file;
    }

    private Object readObject(String path) throws IOException {
        FileInputStream fis = null;
        ObjectInputStream ois = null;
        Object object = null;

        try {
            fis = new FileInputStream(path);
            ois = new ObjectInputStream(fis);

            object = ois.readObject();
        } catch (Exception ex) {
            fail("Failed to read file contents.");
        } finally {
            if (ois != null) {
                ois.close();
            } else if (fis != null) {
                fis.close();
            }
        }

        return object;
    }

    private void setupStreams() {
        stdin = System.in;
        System.setOut(new PrintStream(outContent));
    }

    private String stringRepresentationOfObjects(Object[] array) {
        return stringRepresentationOfObjects(array, 0, array.length - 1);
    }

    private String stringRepresentationOfObjects(Object[] array, int start, int end) {
        StringBuffer buffer = new StringBuffer("[");

        for (int i = start; i <= end; i++) {
            buffer.append(Array.get(array, i)).append(i != array.length - 1 ? " " : "");
        }

        buffer.append("]");
        return buffer.toString();
    }

    private void writeObject(Object object, String fileName) throws IOException {
        FileOutputStream fos = null;
        ObjectOutputStream oos = null;

        try {
            fos = new FileOutputStream(fileName);
            oos = new ObjectOutputStream(fos);
            oos.writeObject(object);
            fos.close();
        } finally {
            if (oos != null) {
                oos.close();
            } else if (fos != null) {
                fos.close();
            }
        }
    }

    private void writeObjects(Object[] objects, String fileName) throws IOException {
        FileOutputStream fos = null;
        ObjectOutputStream oos = null;

        try {
            fos = new FileOutputStream(fileName);
            oos = new ObjectOutputStream(fos);
            for (Object object : objects) {
                oos.writeObject(object);
            }

            fos.close();
        } finally {
            if (oos != null) {
                oos.close();
            } else if (fos != null) {
                fos.close();
            }
        }
    }

    private class NonSerializableClass {
        public String name;

        public NonSerializableClass(String n) {
            name = n;
        }

        @Override
        public String toString() {
            return name;
        }
    }
}