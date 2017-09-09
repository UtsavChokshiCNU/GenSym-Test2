package com.gdev.perfometer;

import java.io.File;
import java.io.IOException;

public class CommandRunner {

	private boolean exec(String command, String startingFolder)
			throws IOException, InterruptedException {
		try {
			Process process = Runtime.getRuntime().exec(command, null,
					new File(startingFolder));
			process.waitFor();
			return true;
		} catch (IOException exception) {
			return false;
		}
	}

	public boolean run(String command, String startingFolder,
			String workingFolder, boolean useInstaller) throws IOException,
			InterruptedException {
		StringBuilder cmd = new StringBuilder(command);
		if (workingFolder != null)
			cmd.append(" \"").append(workingFolder).append("\"");
		if (useInstaller)
			cmd.append(' ').append(useInstaller);
		return exec(cmd.toString(), startingFolder);
	}
}
