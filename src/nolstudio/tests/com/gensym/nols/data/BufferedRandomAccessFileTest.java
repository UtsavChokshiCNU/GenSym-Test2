package com.gensym.nols.data;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNull;
import static org.junit.Assert.fail;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.TemporaryFolder;

public class BufferedRandomAccessFileTest {
	@Rule
	public TemporaryFolder temporaryFolder = new TemporaryFolder();

	@Test
	public void test_read_emptyFileIsLoaded_returnsMinusOne() throws IOException {
		// Arrange
		File file = createEmptyFile();
		BufferedRandomAccessFile sut = createSut(file);

		// Act & Assert
		assertEquals(-1, sut.read());
	}

	@Test
	public void test_read_endOfFileIsNotReached_returnsNextByte() throws IOException {
		// Arrange
		String content = "File Content";
		File file = createFile(content);
		BufferedRandomAccessFile sut = createSut(file);

		for (int idx = 0; idx < content.length(); idx++) {
			// Act & Assert
			assertEquals(content.getBytes()[idx], sut.read());
		}
	}

	@Test
	public void test_read_endOfFileIsReached_returnsMinusOne() throws IOException {
		// Arrange
		String content = "File Content";
		File file = createFile(content);
		BufferedRandomAccessFile sut = createSut(file);

		for (int idx = 0; idx < content.length(); idx++) {
			assertEquals(content.getBytes()[idx], sut.read());
		}

		// Assert
		assertEquals(-1, sut.read());
	}

	@Test
	public void test_getNextLine_emptyFileIsLoaded_returnsNull() throws IOException {
		// Arrange
		File file = createEmptyFile();
		BufferedRandomAccessFile sut = createSut(file);

		// Act & Assert
		assertNull(sut.getNextLine());
	}

	@Test
	public void test_getNextLine_fileContainsOnlyOneLineContent_returnsWholeContent() throws IOException {
		// Arrange
		String content = "File Content without any lines.";
		File file = createFile(content);
		BufferedRandomAccessFile sut = createSut(file);

		// Act & Assert
		assertEquals(content, sut.getNextLine().toString());
	}

	@Test
	public void test_getNextLine_endOfFileIsNotReached_returnsNextLine() throws IOException {
		// Arrange
		String[] lines = new String[] { "File Content Line 1", "File Content Line 2", "File Content Line 3" };
		String content = String.join("\n", lines);
		File file = createFile(content);
		BufferedRandomAccessFile sut = createSut(file);

		for (int idx = 0; idx < lines.length; idx++) {
			// Act & Assert
			assertEquals(lines[idx], sut.getNextLine().toString());
		}
	}

	@Test
	public void test_getNextLine_endOfFileIsReached_returnsNull() throws IOException {
		// Arrange
		String[] lines = new String[] { "File Content Line 1", "File Content Line 2", "File Content Line 3" };
		String content = String.join("\n", lines);
		File file = createFile(content);
		BufferedRandomAccessFile sut = createSut(file);

		for (int idx = 0; idx < lines.length; idx++) {
			sut.getNextLine().toString();
		}

		// Act & Assert
		assertNull(sut.getNextLine());
	}

	@Test
	public void test_getNextLineAsString_emptyFileIsLoaded_returnsNull() throws IOException {
		// Arrange
		File file = createEmptyFile();
		BufferedRandomAccessFile sut = createSut(file);

		// Act & Assert
		assertNull(sut.getNextLineAsString());
	}

	@Test
	public void test_getNextLineAsString_fileContainsOnlyOneLineContent_returnsWholeContent() throws IOException {
		// Arrange
		String content = "File Content without any lines.";
		File file = createFile(content);
		BufferedRandomAccessFile sut = createSut(file);

		// Act & Assert
		assertEquals(content, sut.getNextLineAsString());
	}

	@Test
	public void test_getNextLineAsString_endOfFileIsNotReached_returnsNextLine() throws IOException {
		// Arrange
		String[] lines = new String[] { "File Content Line 1", "File Content Line 2", "File Content Line 3" };
		String content = String.join("\n", lines);
		File file = createFile(content);
		BufferedRandomAccessFile sut = createSut(file);

		for (int idx = 0; idx < lines.length; idx++) {
			// Act & Assert
			assertEquals(lines[idx], sut.getNextLineAsString());
		}
	}

	@Test
	public void test_getNextLineAsString_endOfFileIsReached_returnsNull() throws IOException {
		// Arrange
		String[] lines = new String[] { "File Content Line 1", "File Content Line 2", "File Content Line 3" };
		String content = String.join("\n", lines);
		File file = createFile(content);
		BufferedRandomAccessFile sut = createSut(file);

		for (int idx = 0; idx < lines.length; idx++) {
			sut.getNextLineAsString();
		}

		// Act & Assert
		assertNull(sut.getNextLineAsString());
	}

	@Test
	public void test_reset_isInvokedAfterEndOfFileIsReached_getNextLineReturnsFromTheStart() throws IOException {
		// Arrange
		String[] lines = new String[] { "File Content Line 1", "File Content Line 2", "File Content Line 3" };
		String content = String.join("\n", lines);
		File file = createFile(content);
		BufferedRandomAccessFile sut = createSut(file);

		for (int idx = 0; idx < lines.length; idx++) {
			sut.getNextLine();
		}

		// Act
		sut.reset();

		// Assert
		for (int idx = 0; idx < lines.length; idx++) {
			assertEquals(lines[idx], sut.getNextLine().toString());
		}
	}

	@Test
	public void test_countLines_always_returnsLinesCount() throws IOException {
		// Arrange
		String[] lines = new String[] { "File Content Line 1", "File Content Line 2", "File Content Line 3" };
		String content = String.join("\n", lines);
		File file = createFile(content);
		BufferedRandomAccessFile sut = createSut(file);

		// Act & Assert
		assertEquals(lines.length, sut.countLines());
	}

	@Test
	public void test_read_always_returnsNumberOfBytes() throws IOException {
		// Arrange
		String content = createContent();
		File file = createFile(content);
		BufferedRandomAccessFile sut = createSut(file);
		byte[] buffer = new byte[content.length()];
		int length = 10;

		for (int idx = 0; idx < content.length(); idx += length) {
			// Act
			int readBytesCount = sut.read(buffer, idx, length);

			// Assert
			int endIndex = Math.min(idx + length, content.length());
			assertEquals(endIndex - idx, readBytesCount);
			byte[] expected = content.substring(idx, endIndex).getBytes();
			for (int byteIdx = 0; byteIdx < readBytesCount; byteIdx++) {
				assertEquals(expected[byteIdx], buffer[idx + byteIdx]);
			}
		}
	}

	@Test
	public void test_getFilePointer_always_returnsFilePointerCurrentLocation() throws IOException {
		// Arrange
		String content = createContent();
		File file = createFile(content);
		BufferedRandomAccessFile sut = createSut(file);
		byte[] buffer = new byte[content.length()];
		int length = 10;

		for (int idx = 0; idx < content.length(); idx += length) {
			// Act
			sut.read(buffer, idx, length);

			// Assert
			int endIndex = Math.min(idx + length, content.length());
			assertEquals(endIndex, sut.getFilePointer());
		}
	}

	// -- Helper Methods --

	private String createContent() {
		return "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Phasellus a efficitur lectus. Cras ullamcorper risus vel viverra efficitur. Sed mattis dolor augue, nec aliquet mi ullamcorper condimentum. Etiam blandit ante at semper aliquam. Fusce convallis blandit nisi commodo posuere. Phasellus ullamcorper semper porttitor. Nulla non velit leo. Sed sodales justo a dictum pellentesque. Praesent ornare maximus nunc, et venenatis augue rutrum id. Mauris rhoncus bibendum elit, sed scelerisque tortor molestie eu. Nullam id justo diam. Sed eu sollicitudin massa, quis tristique enim.";
	}

	private File createEmptyFile() throws IOException {
		return createFile("");
	}

	private File createFile(String content) throws IOException {
		File file = temporaryFolder.newFile();
		BufferedWriter writer = null;

		try {
			writer = new BufferedWriter(new FileWriter(file));
			writer.write(content);
		} catch (Exception ex) {
			fail("Failed to create file.");
		} finally {
			if (writer != null) {
				writer.close();
			}
		}

		return file;
	}

	private BufferedRandomAccessFile createSut(File file) throws IOException {
		BufferedRandomAccessFile randomAccessFile = new BufferedRandomAccessFile(file, "rw", (int) file.length());
		return randomAccessFile;
	}
}
