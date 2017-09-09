package com.gdev.perfometer;

import static org.hamcrest.CoreMatchers.equalTo;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertThat;
import static org.junit.Assert.assertTrue;

import java.io.File;
import java.io.IOException;

import org.apache.commons.io.FileUtils;
import org.junit.Test;

public class TestCommandRunner {
	
	@Test
	public void testRun() throws IOException, InterruptedException {
		File testFile = new File("testScripts/TestPerf.txt");
		testFile.delete();
		CommandRunner runner = new CommandRunner();
		assertTrue(runner.run("cmd /c test.bat", "testScripts", null, false));
		assertTrue(testFile.exists());
		assertThat(FileUtils.readFileToString(testFile), 
				equalTo("245.352\r\n"));
		testFile.delete();
	}

	@Test
	public void testUnsuccessfulRun() throws IOException, InterruptedException {
		CommandRunner runner = new CommandRunner();
		assertFalse(runner.run("cmd1 /c test.bat", "testScripts", null, false));
	}
}
