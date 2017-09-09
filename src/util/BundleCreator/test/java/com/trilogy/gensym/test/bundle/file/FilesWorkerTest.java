package com.trilogy.gensym.test.bundle.file;

import com.trilogy.gensym.bundle.file.FilesWorker;

import junit.framework.TestCase;

public class FilesWorkerTest extends TestCase{
	
	public final void testFilesWorkerCreator() throws Exception {
		FilesWorker fw = new FilesWorker();
		assertNotNull(fw);
	}
}
