package com.gensym.nols.data;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.fail;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.util.zip.GZIPInputStream;

import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.TemporaryFolder;

public class VersionManagerTest {
	@Rule
	public TemporaryFolder temporaryFolder = new TemporaryFolder();

	@Test
	public void test_isEvaluationCopy_always_returnsFalse() {
		// Arrange
		VersionManager sut = new VersionManager();

		// Act & Assert
		assertFalse(sut.isEvaluationCopy());
	}

	@Test
	public void test_setProject_always_setsProject() {
		// Arrange
		VersionManager sut = new VersionManager();
		Project2 project = createProject();

		// Act
		sut.setProject(project);

		// Assert
		assertEquals(project, sut.getProject());
	}

	@Test
	public void test_saveToFile_always_savesProjectToFile() throws IOException {
		// Arrange
		VersionManager sut = new VersionManager();
		Project2 project = createProject();
		sut.setProject(project);
		File file = createEmptyFile();

		// Act
		sut.saveToFile(file.getAbsolutePath());

		// Assert
		VersionManager versionManager = loadVersionManager(file.getAbsolutePath());
		assertNotNull(versionManager);
		assertNotNull(versionManager.getProject());
		assertEquals(project.getName(), versionManager.getProject().getName());
	}

	@Test
	public void test_saveToFileWithDirectory_always_savesProjectToFile() throws IOException {
		// Arrange
		VersionManager sut = new VersionManager();
		Project2 project = createProject();
		sut.setProject(project);
		File file = createEmptyFile();

		// Act
		sut.saveToFile(file.getAbsolutePath().replace(file.getName(), ""), file.getName());

		// Assert
		VersionManager versionManager = loadVersionManager(file.getAbsolutePath());
		assertNotNull(versionManager);
		assertNotNull(versionManager.getProject());
		assertEquals(project.getName(), versionManager.getProject().getName());
	}

	// -- Helper Methods --

	private File createEmptyFile() throws IOException {
		File file = temporaryFolder.newFile();
		return file;
	}

	private Project2 createProject() {
		Project2 project = new Project2();
		project.setName("Project2 Name");
		return project;
	}

	private VersionManager loadVersionManager(String fileName) throws IOException {
		VersionManager versionManager = null;
		ObjectInputStream in = null;

		try {
			in = new ObjectInputStream(new GZIPInputStream(new FileInputStream(fileName)));
			versionManager = (VersionManager) in.readObject();
		} catch (Exception ex) {
			fail("Failed to load project");
		} finally {
			if (in != null) {
				in.close();
			}
		}

		return versionManager;
	}
}
