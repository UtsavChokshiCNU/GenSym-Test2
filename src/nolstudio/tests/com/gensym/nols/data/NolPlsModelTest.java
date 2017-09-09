package com.gensym.nols.data;

import java.io.File;
import java.io.IOException;

import org.junit.Test;

import com.gensym.math.MathException;
import com.gensym.nols.main.NolMainFrame;

import static org.junit.Assert.assertTrue;

public class NolPlsModelTest {
	private static String modelFileName = "model4.prj";
	private static String modelXMLFileName = "model4.xml";
	
	@Test
	public void SavePlsToXmlFileTest() throws IOException, MathException, InterruptedException{
		String projectsDir = System.getProperty("user.dir");
		if (!projectsDir.endsWith("nolstudio")) {
			if (projectsDir.endsWith("ant")) {
				projectsDir = projectsDir.replaceAll("ant", "nolstudio");
			}
			else {
				projectsDir = projectsDir.concat("/nolstudio");
			}
		}
		projectsDir = projectsDir.concat("/projects/examples/projects");
		System.out.println("projectsDir = " + projectsDir);
		//Load Nol 
		NolMainFrame frame = new NolMainFrame();
		NolMainFrame.projectDirectory = projectsDir;
		//Open file
		frame.openProjectActionPerformed(modelFileName);
		Thread.sleep(2000);
		Project2 project = frame.getProject();
		//Get the model
		NolPlsModel nolPlsModel = project.getPlsModel(0);
		NolModelXMLHandler handler = new NolModelXMLHandler();
		handler.setModel(nolPlsModel);
		//Save the model
		handler.saveToFile(modelXMLFileName, projectsDir);
		File file = new File(projectsDir + "/" + modelXMLFileName);
		if (file.exists()) {
			file.delete();
			assertTrue(true);
		} else {
			assertTrue("SavePlsToXmlFileTest failed", false);
		}
		
	}
}
