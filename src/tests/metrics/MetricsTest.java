import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileFilter;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.logging.Level;
import java.util.logging.Logger;

 class MetricsTestSuite 
 {
    public static String os; //Has current Operating System, I have considered only two values , One is Windows and other is UNIX based as Solaris, Redhat , HP-UX which are currently supported by Gensym.
        public String searchKbFolder = new String();//Folder where all the test kbs reside, folder is usually "tests"
        public static String startFolder = new String();//Folder where all the test kbs reside, folder is usually "tests"
        public static String BridgePath;   //specfies the bridge path where buildsh.exe and other file resides
        public String resultsfolder; //results folder, where the log is is written by default its should be mentioned in settings.txt, Default value is "C:\results\"
        public static String GensymDir;   //Directory of Gensym, example "C:\Program Files\Gensym\g2-8.4r0" on Windows, doesnt include G2 inside.
        public static String resultsfile;  //File name if log, "test-results-log.rg" it includes the complete pysical path.
        public static String g2Path;    // this is complete path of g2.exe of g2.o, this is = Gensymdir + \g2  i,e; C:\Program Files\Gensym\g2-8.4r0\G2  on windows.
        public String[] cmdstring; //Command string to exectute G2, in windows "CMD" and Unix "sh"
        public static String exeimage; //the name of g2 in Process list., G2.exe in windows and G2 in Unix.
        public List<String> kbsList; //name of the text file which contains the list of kbs to run for testing, its testkbs_list.txt which is there in searchKbFolder.

		public static String pathseperator; //path seperator to b set according to platform;
        public static String fileSeperator = new String(";");
               
    MetricsTestSuite() {}

    public void setoperatingsystem() //Edit to add new Operating systems.
    {
        os=new String(System.getProperty("os.name"));
        System.out.println("\nCurrent Operating System = " + os);
        if (os.contains("Windows")) {
            os="Windows";
            pathseperator=new String("\\");
            cmdstring = new String[3];
            cmdstring[0]=new String("cmd");
            cmdstring[1]=new String("/C");
            cmdstring[2]=new String("StartServer.bat -start -kb ");
            exeimage= new String("g2.exe");
            BridgePath= new String( searchKbFolder + "\\opt-intc");
        } else {
            os="Unix";
            pathseperator=new String("/");
            cmdstring = new String[3];
            cmdstring[0]=new String("sh");
            cmdstring[1]=new String("-c");
            cmdstring[2]=new String("./startserver -start -kb ");
            exeimage= new String("g2");
        }
    }

    public void Start_Twng() {
        String[] twng_cmdstring = new String[3];
        twng_cmdstring[0]= new String("cmd");
        twng_cmdstring[1]= new String("/C");
        twng_cmdstring[2]= new String("twng localhost");
        String[] twngcmdArray = new String[]{twng_cmdstring[0],twng_cmdstring[1],twng_cmdstring[2]};
        File fd = new File(g2Path); 
        ProcessBuilder ab2= new ProcessBuilder(twngcmdArray);
        Map<String, String> env= ab2.environment();
        env.put("G2_AUTO_TEST", resultsfolder);
        env.put("G2_MODULE_SEARCH_PATH", searchKbFolder);    // set the module path of test kbs, regression test kbs are dependent on eachother, we need to specify test folder directory
        ab2.directory(fd);           
        try {
            if ( os.contains("Windows"))
              ab2.start();
        } catch (IOException ex) {
            Logger.getLogger(MetricsTestSuite.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    public void SetSettingsAndFolders(String g2p,String fileArrayStr, String reportDir) throws IOException {
	    setoperatingsystem();    //setoperating system and its specific variables.

		File tmpfile = new File("");                
	    startFolder = new String(tmpfile.getAbsolutePath());
		if (!startFolder.endsWith(pathseperator)) {
			startFolder = startFolder + pathseperator;
		}
		searchKbFolder = String.format("%s..%s..%skbs%s", startFolder, pathseperator, pathseperator, pathseperator);
	    try {
	        String userName = System.getProperty ( "user.name" );                
	        String res = new String();
	        resultsfolder = reportDir;
	        if (resultsfolder.length() == 0) {
		        BufferedReader set_input =  new BufferedReader(new FileReader(startFolder + "settings.txt"));
		        while ((res=set_input.readLine())!= null) {   
	                int index_eql=res.indexOf(':');
	                if(res.substring(0,index_eql).contains(os)) {
	                    int index_eql2=res.indexOf('=');
						if(res.substring(index_eql+1,index_eql2).contains("results")) {
							resultsfolder= new String(res.substring(index_eql2+1,res.length()));
						}
						if (os.contains("Unix")) {
							resultsfolder=resultsfolder + userName + pathseperator + "results";   
						}
	                }   
		        }
	        }
			resultsfolder = resultsfolder + pathseperator + "mi" + pathseperator;
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        File resultsdir =  new File(resultsfolder);
        if(!resultsdir.exists()) {
            resultsdir.mkdir();
        }
		resultsfile= resultsfolder + "test-results-log.rg";  
        File sum =new File(resultsfile);
        try{
            if(!(sum.exists()))
                sum.createNewFile();        
            else {
                sum.delete();
                sum.createNewFile();
            }
        } catch(IOException ie) {   
            System.out.println("Log File Creation Error");
        }
        
        GensymDir=new String(g2p);              
        g2Path = new String(GensymDir);
        
	    System.out.println(String.format("Results Folder = %s\nGensym Directory = %s\nResults File = %s\nG2 path = %s", resultsfolder, GensymDir, resultsfile, g2Path));
	    kbsList = prepareList(fileArrayStr);
    }
    
    public List<String> prepareList(String fileArrayStr) {
		String testkb;
		LinkedList<String> list = new LinkedList<String>();
		for(String testkbs : fileArrayStr.split(fileSeperator)){
			try {
				BufferedReader input = new BufferedReader(new FileReader(testkbs));
				while ((testkb = input.readLine()) != null) {
					if (testkb.length() > 0) {
						list.add(testkb);
					}
				}
			} catch (IOException e) {
			}
		}
		return list;
    }
        
    public void ConcludeTest() throws IOException
    {
        while(true)
        {   
            Boolean a=false;
            String image =exeimage;
            Process p;
            try {
                if (os.contains("Windows")) {
                    p = Runtime.getRuntime().exec(".." + pathseperator + "Process");
                } else {
                    String cmds[] = {"sh","-c","ps -e | grep g2"};
                    p =Runtime.getRuntime().exec(cmds);
                }
            
	            BufferedReader reader = new BufferedReader(new InputStreamReader(p.getInputStream()));
	            String line;
	            
	            while ( ( line = reader.readLine() ) != null )
	            {               
	                if (line.contains(image) ) 
	                {   
	                         try {
	                            Thread.sleep(5000);
	                        } catch (InterruptedException e) {
	                            e.printStackTrace();
	                        }
	                         a=true;
	                         
	                }                       
	            }
	            if(reader.readLine()== null && a==false )
	            {
	                break;                          
	            }
	            reader.close();             
	        }
	        catch (IOException e) {
	            e.printStackTrace();
	        }
	    }
    }
    
    public int processFullReportFile() throws FileNotFoundException
    {
        final String logFileName = "dump.txt";
        File sumReport = new File(resultsfolder + logFileName);
        try{
	        if(!(sumReport.exists()))
	        	sumReport.createNewFile();        
	        else
	        {
	        	sumReport.delete();
	        	sumReport.createNewFile();
	        }
        } catch(IOException ie) {       
        }

        String logLine;
		BufferedWriter logOutput;
		HashSet<String> processedKbSet = new HashSet<String>();
		try {
			logOutput = new BufferedWriter(new FileWriter(sumReport));
			try {
				for (String absFileFath : kbsList) {
			        File file = new File(absFileFath);
					if (file != null && file.exists() && file.isFile()) {
						String kbName = file.getName();
						String kbPath = file.getParent();
					
						if (kbPath.startsWith("#") || kbName.startsWith("#")) {
							continue;
						}

				        File curKbLog = new File(resultsfolder + kbName + "-mi-report.txt");
				        if(!curKbLog.exists()) {
				        	continue;        
				        }
							
				        BufferedReader logInput =  new BufferedReader(new FileReader(curKbLog));
				        logLine = logInput.readLine();
				        while (logLine != null) {
							if (logLine.startsWith("KB Project#")) {
								logLine = logInput.readLine();
								continue;
							}
							int firstSharpPos = logLine.indexOf("#");
							if (firstSharpPos > 0) {
								String moduleName = logLine.substring(0, firstSharpPos);
								if (!processedKbSet.contains(moduleName)) {
									processedKbSet.add(moduleName);
									logOutput.write(logLine);
									logOutput.newLine();
								}
							}
							logLine = logInput.readLine();
				        }
					}
				}
			} catch (Exception e) {
				System.out.println(e);
				System.out.println("There was a Exception raised while Metricsorming tests, Check the log for information");
			}
	        logOutput.close();
	        ProcessBuilder repGenerator= new ProcessBuilder(cmdstring);
			Map<String, String> env = repGenerator.environment();
			String cmdPath = env.get("SRCBOX");
			cmdPath = cmdPath + (pathseperator == "/" ? "/lisp/mi/generate-kb-mi-report" : "\\lisp\\mi\\generate-kb-mi-report"); 
	        repGenerator.command(cmdstring[0], cmdstring[1], cmdPath, resultsfolder);
	        repGenerator.start();           
	        processedKbSet.clear();
	        return 1;
		} catch (IOException e1) {
			e1.printStackTrace();
			return 0;
		}
    }
    
    
	public static void programinfo()
	{
        System.out.println("\t* 1>> Make sure that test folder Path does not contain any spaces");
	    System.out.println("\t* 2>> As a first argument give  the appropriate path of the g2 installation directory within quotes like Example=>\"C:\\Program Files\\Gensym\\g2-8.3r1\" as argument. and Results folder can be specified in settings.txt file(if not,by default c:\\results is taken)");
	    System.out.println("\t* 3>> If you dona€u8482 t intend to Metricsorm GSI regression test , then pass '-gsi' as a second argument to the test suite. Example: Java RegressionTest 'C:\\Program Files\\Gensym\\g2-8.3r1' -gsi");
	    System.out.println("\t* 4>> EDIT 'kbs_list_for_metrics.txt'(which is inside tests\\metrics folder) for adding new tests or removing tests from the regression test suite and GSI regression test(gsi-suite.kb) is conducted by default no need to add that into the list");
	    System.out.println("\t* 5>> Output resides in the given results folder or C:\\results\\test-results-log.rg by default, which has Detailed log");
	    System.out.println("\t* 6>> Similarly Brief Summary of tests resides in the Regr-test-summary.log in the results folder");
        System.exit(0); 
	}
 }
 
 class G2MetricsTestSuite extends MetricsTestSuite
 {
	private void processFile(String absFileFath) {
        if (absFileFath == null)
        	return;
        boolean run_twng = false;
        File file = new File(absFileFath);
		if (file != null && file.exists() && file.isFile()) {
			String kbName = file.getName();
			String kbPath = file.getParent();
			 
			if (kbPath.startsWith("#"))
				return;
			if (kbName.contains("@") && kbName.endsWith("twng")) {
				if (os.contains("Windows")) {
					run_twng = true;
					kbName = kbName.substring(0, kbName.indexOf("@"));
				} else {
					return;
				}
			}
			String[] cmdArray = new String[] { cmdstring[0],
					cmdstring[1], cmdstring[2] + startFolder + "static-metric-runner.kb" };
			File fd = new File(g2Path);
			
			ProcessBuilder ab = new ProcessBuilder(cmdArray);
			Map<String, String> env = ab.environment();
			env.put("G2_AUTO_TEST", resultsfolder);
			env.put("G2_MODULE_SEARCH_PATH", searchKbFolder); 
			
			// set the module path of test kbs, regression test kbs are 
			//dependent on eachother, we need to specify test folder directory
			env.put("G2_MERGE_KB_PATH", kbPath); 
			env.put("G2_MERGE_KB_NAME", kbName); 
			ab.directory(fd);
			try {
				ab.start();
				System.out.println(kbName + " - is processing.......");
				if (run_twng == true) {
					Start_Twng();
				}
				Thread.sleep(5000);
				ConcludeTest();
			} catch (Exception e) {
				e.printStackTrace();
			}
		 }
	 }
	 
	public void g2_RunTest() throws FileNotFoundException {
		int count = kbsList.size();
		int number = 0;
		
		for (String kb : kbsList) {
			number++;
			System.out.print(String.format("[%3d/%d]  ", number, count));
			processFile(kb);
		}
	}
 }

class KbListBuilder {
	
	public static List<String> Build(String rootDir) {
		System.out.println("rootDir=" + rootDir);
		KbListBuilder builder = new KbListBuilder(rootDir);
		return new ArrayList<String>(builder.fileList);
	}

	private HashSet<String> fileList = new HashSet<String>();
	private FileFilter fileFilter = new FileFilter() {
		public boolean accept(File pathname) {
			return pathname.isFile() && (pathname.getName().endsWith(".kb"));
		}
	};
	private String rootDirectory = "";
	
	private KbListBuilder(String rootDir) {
		rootDirectory = rootDir;
		prepareList(new File(rootDirectory));
	}
	
	private void prepare(File rootFile) {
		if (rootFile != null && rootFile.exists() && rootFile.isDirectory()) {
			File list[] = rootFile.listFiles();
			for (File file : list) {
				if (file.isDirectory()) {
					prepare(file);
					for (File f : file.listFiles(fileFilter)) {
						fileList.add(f.getAbsolutePath());
					}
				} else if (fileFilter.accept(file)) {
					fileList.add(file.getAbsolutePath());
				}
			}
		}
	}
	private  void prepareList(File rootDir) {
		fileList.clear(); 
		prepare(rootDir);
	}
}

public class MetricsTest {
    //@SuppressWarnings("static-access")        
    public static void main(String[] args) throws IOException {
		try{
		    if(args[0].compareTo("-help")==0 || args[0].compareTo("/?")==0) {
		        MetricsTestSuite.programinfo();
		    }
		} catch(ArrayIndexOutOfBoundsException a) {
		        MetricsTestSuite.programinfo();
		}
		
		G2MetricsTestSuite g2MetricsTest= new G2MetricsTestSuite();
		g2MetricsTest.SetSettingsAndFolders(args[0],args[2], args.length == 4 ? args[3] : "");  
		if (args[1].equals("-files")) {
			g2MetricsTest.kbsList = g2MetricsTest.prepareList(args[2]); //use searchKbFolder = /src/kbs
		} else {
			g2MetricsTest.kbsList = KbListBuilder.Build(args[2]);
		}
		g2MetricsTest.g2_RunTest();

		try {
			g2MetricsTest.processFullReportFile();
            System.exit(0); 
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }   
	}
}
