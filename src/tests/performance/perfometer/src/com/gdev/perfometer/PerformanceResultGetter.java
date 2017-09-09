package com.gdev.perfometer;

import java.io.File;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

import org.apache.commons.io.FileUtils;

public class PerformanceResultGetter {

	private static class Container {
		public String folder;
		public String command;

		public Container(String aFolder, String aCommand) {
			folder = aFolder;
			command = aCommand;
		}
	};

	private Map<String, Container> useCaseMap = new HashMap<String, Container>();
	private CommandRunner runner = new CommandRunner();

	public void addUseCase(String useCaseID, String folderToRunFrom,
			String cmdToRun) {
		useCaseMap.put(useCaseID, new Container(folderToRunFrom, cmdToRun));
	}

	public double takeResult(String useCaseID) throws IOException,
			InterruptedException {
		return takeResult(useCaseID, null);
	}

	public double takeResult(String useCaseID, String workingFolder)
			throws IOException, InterruptedException {
		return takeResult(useCaseID, workingFolder, false);
	}

	public double takeResult(String useCaseID, String workingFolder,
			boolean useInstaller) throws IOException, InterruptedException {
		Container container = useCaseMap.get(useCaseID);
		runner.run(container.command, container.folder, workingFolder,
				useInstaller);
		File resultFile = new File(container.folder + "/" + useCaseID + ".txt");
		double result = new Double(FileUtils.readFileToString(resultFile));
		resultFile.delete();
		return result;
	}
}
