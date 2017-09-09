import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class CorrectBullseyeReport {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		if (args.length == 1) {
			String srcFileName = args[0];
			String copyFileName = srcFileName + "~"; 
	        File srcFile = new File(srcFileName);
	        File cpFile = new File(copyFileName);
	        if(cpFile.exists()) {
				cpFile.delete();
			}
			srcFile.renameTo(cpFile);
	        
	        BufferedReader input = null;
			try {
				input = new BufferedReader(new FileReader(copyFileName));
			} catch (FileNotFoundException e) {
				e.printStackTrace();
			}
	        
      String logline;
      try {
          BufferedWriter output= new BufferedWriter(new FileWriter(srcFileName));
          Boolean tagFound = false;
          while ((logline = input.readLine()) != null) {
            if (!tagFound) {
              if (!logline.startsWith("<?xml")) {
                continue;
              } else {
                tagFound = true;
              }
            }
            output.write(logline);
          output.newLine();
          }
          output.flush();
          output.close();
      }
      catch (IOException io) {
      }
		}
	}
}
