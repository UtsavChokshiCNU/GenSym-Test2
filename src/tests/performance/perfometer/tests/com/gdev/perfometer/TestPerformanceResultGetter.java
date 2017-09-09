package com.gdev.perfometer;

import static org.hamcrest.CoreMatchers.equalTo;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertThat;

import java.io.File;
import java.io.IOException;

import org.junit.Before;
import org.junit.Test;

public class TestPerformanceResultGetter {

	private PerformanceResultGetter getter;
	private static final String TEST_FOLDER = "testScripts";
	private static final String TEST_SUBFOLDER = "testScripts/subTests";

	@Before
	public void setup() {
		getter = new PerformanceResultGetter();
	}

	@Test
	public void testGetPerformanceResult() throws IOException,
			InterruptedException {
		getter.addUseCase("TestPerf", TEST_FOLDER, "cmd /c test.bat");
		assertThat(getter.takeResult("TestPerf"), equalTo(245.352));
	}

	@Test
	public void testGetPerformanceAnotherResult() throws IOException,
			InterruptedException {
		getter.addUseCase("TestPerf", TEST_FOLDER, "cmd /c test2.bat");
		assertThat(getter.takeResult("TestPerf"), equalTo(2.3));
	}

	@Test
	public void testRemoveResultFile() throws IOException, InterruptedException {
		getter.addUseCase("TestPerf", TEST_SUBFOLDER, "cmd /c test3.bat");
		getter.takeResult("TestPerf");
		assertFalse(new File(TEST_SUBFOLDER + "/TestPerf.txt").exists());
	}

	@Test
	public void testGetPerformanceResultWithGivenFolder() throws IOException,
			InterruptedException {
		getter.addUseCase("TestPerf", TEST_FOLDER, "cmd /c test.bat");
		assertThat(getter.takeResult("TestPerf", "SomeFolder"), equalTo(6.5));
	}

	@Test
	public void testGetPerformanceResultWithGivenFolderWithSpaces()
			throws IOException, InterruptedException {
		getter.addUseCase("TestPerf", TEST_FOLDER, "cmd /c test2.bat");
		assertThat(getter.takeResult("TestPerf", "Some Folder"), equalTo(16.5));
	}

	@Test
	public void testGetPerformanceResultWithGivenFolderAgainstInstaller()
			throws IOException, InterruptedException {
		getter.addUseCase("TestPerf", TEST_SUBFOLDER, "cmd /c test3.bat");
		assertThat(getter.takeResult("TestPerf", "Some Folder", true),
				equalTo(11.1));
	}

}
