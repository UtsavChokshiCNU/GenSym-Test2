package com.gensym.nols.data;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNotNull;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.util.zip.GZIPInputStream;

import org.junit.Before;
import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.TemporaryFolder;

import com.gensym.nols.deploy.OnlineOptimizer;

public class VersionManagerForOnlineOptimizerTest {
	private OnlineOptimizer sutOptimizer;
	private String fileName;
	private VersionManagerForOnlineOptimizer sut;

	@Rule
	public TemporaryFolder folder = new TemporaryFolder();

	@Before
	public void setup() {
		sut = new VersionManagerForOnlineOptimizer();
	}

	@Test
	public void test_saveToFile_FileExists_SavesFile() throws ClassNotFoundException, IOException {
		// Arrange
		arrangeForSaveToFile();

		// Act
		sut.saveToFile(fileName);

		// Assert
		OnlineOptimizer optimizer = readFile();
		assertNotNull(optimizer);
		assertEquals(sut.getOptimizer().getName(), optimizer.getName());
	}

	private void arrangeForSaveToFile() throws IOException {
		fileName = "Serialized Object.tmp";
		sutOptimizer = new OnlineOptimizer();
		sutOptimizer.setName("VersionManagerForOnlineOptimizer OnlineOptimizer");
		sut.setOptimizer(sutOptimizer);
	}

	private OnlineOptimizer readFile() throws IOException, ClassNotFoundException {
		OnlineOptimizer optimizer = null;
		ObjectInputStream in = null;

		try {
			File sourceFile = new File(fileName);
			FileInputStream fis = new FileInputStream(sourceFile);
			GZIPInputStream gzis = new GZIPInputStream(fis);
			in = new ObjectInputStream(gzis);
			VersionManagerForOnlineOptimizer ver = (VersionManagerForOnlineOptimizer) in.readObject();
			optimizer = ver.getOptimizer();
		} catch (Exception ex) {
		} finally {
			if (in != null) {
				in.close();
			}
		}

		return optimizer;
	}
}
