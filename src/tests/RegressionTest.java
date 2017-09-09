import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Map;
import java.util.logging.Level;
import java.util.logging.Logger;
import java.util.ArrayList;

 class TestSuite
 {
    public static String operatingsystem; //Has current Operating System, I have considered only two values , One is Windows and other is UNIX based as Solaris, Redhat , HP-UX which are currently supported by Gensym.
        public static String testfolder = new String();//Folder where all the test kbs reside, folder is usually "tests"
        public static String BridgePath;   //specfies the bridge path where buildsh.exe and other file resides
        public static String resultsfolder; //results folder, where the log is is written by default its should be mentioned in settings.txt, Default value is "C:\results\"
        public static String GensymDir;   //Directory of Gensym, example "C:\Program Files\Gensym\g2-8.4r0" on Windows, doesnt include G2 inside.
        public static String resultsfile;  //File name if log, "test-results-log.rg" it includes the complete pysical path.
        public static String g2Path;    // this is complete path of g2.exe of g2.o, this is = Gensymdir + \g2  i,e; C:\Program Files\Gensym\g2-8.4r0\G2  on windows.
        public static String[] cmdstring; //Command string to exectute G2, in windows "CMD" and Unix "sh"
        public static String exeimage; //the name of g2 in Process list., G2.exe in windows and G2 in Unix.
        public static String[] testkbs_list; //name of the text file which contains the list of kbs to run for testing, its testkbs_list.txt which is there in testfolder.
        public static String pathseperator; //path seperator to b set according to platform;
        public static String fileSeperator = new String(";");
        public static ArrayList<TestFile> kblist = new ArrayList<TestFile>(170);

        public void setoperatingsystem() //Edit to add new Operating systems.
        {
            operatingsystem=new String(System.getProperty("os.name"));
            System.out.println("\nCurrent Operating System = " + operatingsystem);
                if (operatingsystem.contains("Windows"))
                {
                    operatingsystem="Windows";
                    pathseperator=new String("\\");
                    testfolder= testfolder + pathseperator;
                    cmdstring = new String[3];
                    cmdstring[0]=new String("cmd");
                    cmdstring[1]=new String("/C");
                    cmdstring[2]=new String("StartServer.bat -start -kb ");
                    exeimage= new String("g2.exe");
                    BridgePath= new String( testfolder + "\\opt-intc");
                }
                else
                {
                    operatingsystem="Unix";
                    pathseperator=new String("/");
                    testfolder= testfolder + pathseperator;
                    cmdstring = new String[3];
                    cmdstring[0]=new String("sh");
                    cmdstring[1]=new String("-c");
                    cmdstring[2]=new String("./startserver -start -kb ");
                    exeimage= new String("g2");
                    //BridgePath= new String( testfolder + "\\opt-intc");
                }
        }
     public void Start_Twng(String testkb)
        {
            String[] twng_cmdstring = new String[3];
            twng_cmdstring[0]= new String("cmd");
            twng_cmdstring[1]= new String("/C");
            twng_cmdstring[2]= new String("twng localhost");
	    try {
		 if (testkb.contains("f102demo.kb"))
			Thread.sleep(50000);
		 else
			Thread.sleep(2000);
	    } catch (Exception e) {
	        System.out.println("Process can't wait 5 seconds for starting twng");
	    }
	    //twng_cmdstring[2] = new String("C:\\g2\\dst\\twng\\opt\\twng localhost");

            String[] twngcmdArray = new String[]{twng_cmdstring[0],twng_cmdstring[1],twng_cmdstring[2]};
	    File fd = new File(g2Path);
            ProcessBuilder ab2= new ProcessBuilder(twngcmdArray);
            Map<String, String> env= ab2.environment();
            env.put("G2_AUTO_TEST", resultsfolder);
            env.put("G2_MODULE_SEARCH_PATH",testfolder);    // set the module path of test kbs, regression test kbs are dependent on eachother, we need to specify test folder directory
            ab2.directory(fd);
        try {
            if ( operatingsystem.contains("Windows"))
                            ab2.start();
        } catch (IOException ex) {
            Logger.getLogger(TestSuite.class.getName()).log(Level.SEVERE, null, ex);
        }
        }
     public void Start_odbc()
        {
            Process p;
			try{
                    if (operatingsystem.contains("Windows"))
                    {
                         p = Runtime.getRuntime().exec("cmd /k start odbc.bat");
                    }
				}

			catch (IOException e) {
			 e.printStackTrace();
			 }

        }

      @SuppressWarnings("static-access") public static void startJMailBridge()
	{
		String gsPath = "C:\\Program Files\\Gensym";
		File gensymFolder = new File(gsPath);

		// check whether there is a GENSYM folder in "C:\Programm Files"
		if(!gensymFolder.exists()) {
			System.out.println("\nGensym application is not installed on your system. jmail-demo-01.kb won't work.");
			return;
		}

		String [] gsFolderList = gensymFolder.list();
		// check whether there is a versioned GENSYM's folder in "C:\Programm Files\Gensym"
		if(gsFolderList.length == 0 || !gsFolderList[0].substring(0, 2).equals("g2")) {
			System.out.println("\nGensym application is not installed on your system. jmail-demo-01.kb won't work.");
			return;
		}

		String jMailBridgePath = gsPath + "\\" + gsFolderList[0] + "\\jmail\\bin\\";
		Runtime run = Runtime.getRuntime();
		try {
			run.exec("cmd /K start /D \"" + jMailBridgePath + "\" " + "StartJMailBridge.bat");
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

    public void SetSettingsAndFolders(String g2p,String fileArrayStr) throws IOException
    {

            File tmpfile = new File("");
            testfolder= new String(tmpfile.getAbsolutePath());

             setoperatingsystem();    //setoperating system and its specific variables.

            try {
                String userName = System.getProperty ( "user.name" );
                String res = new String();
                BufferedReader set_input =  new BufferedReader(new FileReader(testfolder +"settings.txt"));
        while ((res=set_input.readLine())!= null)
            {
                int index_eql=res.indexOf(':');
                                if(res.substring(0,index_eql).contains(operatingsystem))
                {
                    int index_eql2=res.indexOf('=');
                //System.out.println(res.substring(0,index_eql));
                                    if(res.substring(index_eql+1,index_eql2).contains("results"))
                                    {
                    resultsfolder= new String(res.substring(index_eql2+1,res.length()));
                                    }
                                    if (operatingsystem.contains("Unix"))
                                    {
                                     resultsfolder=resultsfolder + userName + pathseperator + "results";
                                    }
                }
                        }
                } catch (FileNotFoundException e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
                }


               File resultsdir =  new File(resultsfolder);
            if(!resultsdir.exists())
            {
                resultsdir.mkdir();
            }
                resultsfolder = resultsfolder + pathseperator;
               resultsfile= resultsfolder + "test-results-log.rg";
         File sum =new File(resultsfile);
            try{
                if(!(sum.exists()))
                    sum.createNewFile();
                else
                {
                    sum.delete();
                    sum.createNewFile();

                }}
                catch(IOException ie)
                {
                    System.out.println("Log File Creation Error");
                }

                 GensymDir=new String(g2p);
            g2Path = new String(GensymDir);

            testkbs_list =  fileArrayStr.split(fileSeperator);
            for(String testkbs:testkbs_list){
            	testkbs = new String(testfolder + pathseperator +testkbs);
            }

    System.out.println("Test Folder = " + testfolder + "\nResults Folder = " + resultsfolder + "\nGensym Directory = " + GensymDir + "\nResults File = " + resultsfile + "\nG2 path = " + g2Path );


        }

    public void ConcludeTest(String imagename) throws IOException
    {
        while(true)
        {
            Boolean a=false;
            String image = imagename;
            if (imagename.equals(""))
                image = exeimage;
            Process p;
            try {
                            if (operatingsystem.contains("Windows"))
                                        {
                                                 p = Runtime.getRuntime().exec("Process");
                                        }
                                        else
                                        {
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
                            // TODO Auto-generated catch block
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
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }
 }
    public int processlogfile() throws FileNotFoundException
    {
        String logFile_path=resultsfile;
        File sum= new File(resultsfolder +"Regr-test-summary.log");
        try{
        if(!(sum.exists()))
            sum.createNewFile();
        else
        {
            sum.delete();
            sum.createNewFile();

        }}
        catch(IOException ie)
        {
        }
        BufferedReader loginput =  new BufferedReader(new FileReader(logFile_path));


        ArrayList<TestFile> passedTests = new ArrayList<TestFile>();
        ArrayList<TestFile> failedTests = new ArrayList<TestFile>();
        String logline;
        int passed=0,failed=0;
        int gpassed=0,gfailed=0;
        int testindex = 0;
        //Gensym-472 fix
        Boolean b = false;
        //Gensym-472 fix
        try
        {
            BufferedWriter logoutput= new BufferedWriter(new FileWriter(sum));
            //Gensym-472 fix
            //while ((logline=loginput.readLine())!=null)
            logline = loginput.readLine();

            while ( logline != null)
            //Gensym-472 fix
            {
                if(logline.contains("written"))
                        {
                            StringBuilder ftests= new StringBuilder();
                            StringBuilder ptests= new StringBuilder();
                            String testtitle=logline.substring(0, logline.indexOf("written"));

                            TestFile testFile = kblist.get(testindex);
                            String kbfilename = testFile.GetName();


                            while(!(logline=loginput.readLine()).contains("-------------"))
                            {
                            		//Gensym-472 fix
                            		if (logline.contains("written"))
                            		{
                            			  System.out.println("\n"+testtitle);
                            			  System.out.println("Tests failed(hung)");
                            			  System.out.println("------------------------------------------");
                            			  logoutput.write(testtitle);
                            			  logoutput.write("Test failed(hung)");
                            			  logoutput.newLine();
                            			  logoutput.write("------------------------------------------");
                                    logoutput.newLine();

                                    passed=0;
                            				failed=0;

                            				b = true;

                            				break;
                            		}
                            		//Gensym-472 fix

                                if(logline.contains("PASSED"))
                                {
                                    TestFile tempTestFile = new TestFile();
                                    tempTestFile.SetName(testFile.GetName());
                                    tempTestFile.SetPath(testFile.GetPath());
                                    String testName = logline.substring(0,logline.indexOf("PASSED"));
                                    tempTestFile.SetTestName(testName);
                                    passed++;
                                    passedTests.add(tempTestFile);
                                }
                                else if(logline.contains("FAILED"))
                                {

                                    String testName = logline.substring(0,logline.indexOf("FAILED"));
                                    ftests.append(logline.substring(0,logline.indexOf("FAILED")));
                                     TestFile tempTestFile = new TestFile();
                                    tempTestFile.SetName(testFile.GetName());
                                    tempTestFile.SetPath(testFile.GetPath());
                                    tempTestFile.SetTestName(testName);
                                    failed++;
                                     failedTests.add(tempTestFile);
                                }
                            }

                            //Gensym-472 fix
                            if (b)
                            {
                            		 b = false;
                            	   continue;
                            }
                            //Gensym-472 fix
                              testindex++;

//                            System.out.println("\n"+testname);
//                            System.out.println("Total Number of Tests in "+ testname+ " " + kbfilename + " = " + (passed +  failed));
//                            System.out.println("Number of passed tests -- " + passed);
//                            System.out.println("Number of Failed tests -- " + failed);
//                            System.out.println("------------------------------------------");
//                            logoutput.write(testname);
//                            logoutput.write("Total Number of Tests in "+ testname+ " " + kbfilename + " = " + (passed +  failed));
//
//                            logoutput.newLine();
//                            logoutput.write("Number of passed tests -- " + passed);
//                            logoutput.newLine();
//                            logoutput.write("Number of Failed tests -- " + failed);
//                            logoutput.newLine();
//                            if(ftests.length()>0)
//                                logoutput.write("Failed tests are : " + ftests.toString() );
//                            logoutput.newLine();
//                            logoutput.write("------------------------------------------");
//                            logoutput.newLine();
                            gpassed=gpassed+passed;
                            gfailed=gfailed+failed;
                            passed=0;
                            failed=0;
                        }
                //Gensym-472 fix
                logline = loginput.readLine();
                //Gensym-472 fix
            }
            System.out.println("\n------------------------------------------");
            System.out.println("------------------------------------------");
            System.out.println("Total Number of Tests performed = " + (gpassed +  gfailed));
			System.out.println("Total Number of Failed tests -- " + gfailed);
            System.out.println("Total Number of passed tests -- " + gpassed);
            
            System.out.println("------------------------------------------");

            logoutput.write("------------------------------------------");
            logoutput.write("------------------------------------------\n");
            logoutput.write("Total Number of Tests performed = " + (gpassed +  gfailed));
            logoutput.newLine();
			logoutput.write("Total Number of Failed tests -- " + gfailed);
            logoutput.newLine();
            logoutput.write("Total Number of passed tests -- " + gpassed);
            logoutput.newLine();
            logoutput.write("------------------------------------------");
            logoutput.write("------------------------------------------");

            for (int i=0;i<failedTests.size();i++) {
                System.out.println("FAILED : \"" + failedTests.get(i).GetPath() +"\" " + failedTests.get(i).GetTestName());
                 logoutput.write("\nFAILED : \"" + failedTests.get(i).GetPath() +"\" " + failedTests.get(i).GetTestName());
            }

           for (int j=0;j<passedTests.size();j++) {
                System.out.println("PASSED : \"" + passedTests.get(j).GetPath() +"\" " + passedTests.get(j).GetTestName());
                 logoutput.write("\nPASSED : \"" + passedTests.get(j).GetPath() +"\" " + passedTests.get(j).GetTestName());
            }
            
            logoutput.close();
            return 1;
        }
        catch (IOException io)
        {
            System.out.println("ERROR IN READING FROM THE LOG FILE");
            return 0;
        }
        }
        public static void programinfo() {

            System.out.println("\t* 1>> Make sure that test folder Path does not contain any spaces");
            System.out.println("\t* 2>> As a first argument give  the appropriate path of the g2 installation directory within quotes like Example=>\"C:\\Program Files\\Gensym\\g2-8.3r1\" as argument. and Results folder can be specified in settings.txt file(if not,by default c:\\results is taken)");
            System.out.println("\t* 3>> If you dona€u8482 t intend to perform GSI regression test , then pass '-gsi' as a second argument to the test suite. Example: Java RegressionTest 'C:\\Program Files\\Gensym\\g2-8.3r1' -gsi");
            System.out.println("\t* 4>> EDIT 'testkbs_list.txt'(which is inside tests folder) for adding new tests or removing tests from the regression test suite and GSI regression test(gsi-suite.kb) is conducted by default no need to add that into the list");
            System.out.println("\t* 5>> Output resides in the given results folder or C:\\results\\test-results-log.rg by default, which has Detailed log");
            System.out.println("\t* 6>> Similarly Brief Summary of tests resides in the Regr-test-summary.log in the results folder");
            System.exit(0);
        }


    private boolean needCoverage = false;

    public boolean isNeedCoverage() {
   		return needCoverage;
 }

   	public void setNeedCoverage(boolean needCoverage) {
   		this.needCoverage = needCoverage;
   	}


}

 class G2TestSuite extends TestSuite
 {
         public void g2_RunTest() throws FileNotFoundException
     {
         String testkb;
                 boolean run_twng=false;
                 boolean run_odbc=false;
                 boolean run_jmail=false;

        for (String testkbs : testkbs_list) {
			BufferedReader input = new BufferedReader(new FileReader(testkbs));
			try {
				while ((testkb = input.readLine()) != null) {
					if (testkb.compareTo("gsi-suite.kb") == 0) {
						if ((testkb = input.readLine()) == null) {
							break;
						}
					}

					if (testkb.compareTo("db-bridges-test.kb") == 0) {
						if (operatingsystem.contains("Windows")) {
							run_odbc= true;
						}
					}

					if ((testkb.compareTo("jmail-demo-01.kb") == 0) || (testkb.compareTo("jmail-demo-02.kb") == 0))  {
						if (operatingsystem.contains("Windows")) {
							run_jmail = true;
						}
					}
					if (testkb.startsWith("#"))
						continue;

					if (testkb.contains("@") && testkb.endsWith("twng")) {
						if (operatingsystem.contains("Windows")) {
							run_twng = true;
							testkb = testkb.substring(0, testkb.indexOf("@"));
						} else {
							continue;
						}
					}
					//If a KB does not exist, print the message and proceed.
					File f = new File(testkb);

					if (!f.exists())
					{
						System.out.println("KB file: " + f + " does not exist. Processing the next KB...");
						continue;
					}

                                        TestFile testFile = new TestFile();
                                        testFile.SetName(testkb);
                                        testFile.SetPath(f.getAbsolutePath());
					kblist.add(testFile);
					String[] cmdArray = new String[] { cmdstring[0],
							cmdstring[1], cmdstring[2] + testfolder + testkb };
					// System.out.println(cmdArray);
					File fd = new File(g2Path);

					ProcessBuilder ab = new ProcessBuilder(cmdArray);
					Map<String, String> env = ab.environment();

					if (isNeedCoverage()) {
						env.put("MI_COVERAGE_REPORT_FILE", resultsfolder + "kbcov-" + testkb.substring(0, testkb.indexOf(".")) + ".html");
					}
					env.put("G2_AUTO_TEST", resultsfolder);
					env.put("G2_MODULE_SEARCH_PATH", testfolder); // set the directory
					ab.directory(fd);
					if (run_odbc == true) {
						Start_odbc();
						Thread.sleep(25000);
					}
					if (run_jmail == true) {
					      startJMailBridge();
						Thread.sleep(25000);
					}
					ab.start();
					System.out.println(testkb + " - test is running.......");
					if (run_twng == true) {
                                    run_twng = false;
						Start_Twng(testkb);
					}

					Thread.sleep(5000);
					ConcludeTest(exeimage);

					if (run_odbc)
					{
					    run_odbc =  false;
					    //Add code to terminate odbc batch file
					}
					if (run_jmail)
					{
					    run_jmail =  false;
					    //Add code to terminate jmail batch file
					}
				}
			} catch (Exception e) {
				System.out.println(e);
				System.out
						.println("There was a Exception raised while performing tests, Check the log for information");
			}
		}
	}
 }
 class GsiTestSuite extends TestSuite
 {
     public void Gsi_RunTest()
    {
        String[] cmdArray1 = new String[]{cmdstring[0],cmdstring[1],cmdstring[2]+ testfolder + "gsi-suite.kb"};
        String[] cmdArray2 = new String[]{cmdstring[0],cmdstring[1],"buildsh.exe"};
        ProcessBuilder grt= new ProcessBuilder(cmdArray1);
        ProcessBuilder bsh= new ProcessBuilder(cmdArray2);

        Map<String, String> envr =grt.environment();
        envr.put("GSI_BRIDGE_PATH",BridgePath);
        envr.put("G2_AUTO_TEST", resultsfolder);
        File g2fd=new File(g2Path);
        grt.directory(g2fd);

       File bshfd=new File(BridgePath);
       bsh.directory(bshfd);
        try {
            try {
                bsh.start();
                grt.start();
                System.out.println("gsi-suite.kb - test is running.......");

                Thread.sleep(3000);
            } catch (InterruptedException e) {
                // TODO Auto-generated catch block
                System.out.println("Error opening bridge,buildsh.exe not found. Check the path");
                System.exit(0);
            }
        ConcludeTest("");
                Process endp;
                if (operatingsystem.contains("Windows"))
                {
                endp=Runtime.getRuntime().exec("taskkill /f /im buildsh.exe");
                }
                else
                {
                        endp=Runtime.getRuntime().exec("killall -9 g2");
                }
            } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }

    }
 }

 class TestFile
{
    private String name;
    private String path;
    private String test;

    public String GetName()
    {
        return name;
    }

    public void SetName(String value)
    {
        name =value;
    }

    public String GetPath()
    {
        return path;
    }

    public void SetPath(String value)
    {
        path=value;
    }

    public void SetTestName(String value)
     {
      test =value;
    }
    public String GetTestName()
     {
        return test;
    }

}

 /**
 * @author bgr
 *
 */
public class RegressionTest {

            public static void main(String[] args) throws IOException {
            // TODO Auto-generated method stub
                try{
                    if(args[0].compareTo("-help")==0 || args[0].compareTo("/?")==0)
                    {
                        TestSuite.programinfo();
                    }
                  }
                catch(ArrayIndexOutOfBoundsException a)
                    {
                        TestSuite.programinfo();
                    }
            TestSuite TS = new TestSuite();
                TS.SetSettingsAndFolders(args[0],args[2]);

                G2TestSuite g2Test= new G2TestSuite();
                for (String arg : args) {
	                if (arg.equals("-need_coverage")) {
	                	g2Test.setNeedCoverage(true);
	                	break;
	                }
	            }
                g2Test.g2_RunTest();


                GsiTestSuite gsiTest= new GsiTestSuite();
                try{
                    if(args[1].compareTo("-gsi")!=0)
                    {

                    }
                }
                catch(ArrayIndexOutOfBoundsException a)
                {
                                     if(TS.operatingsystem.contains("Windows"))
                    {
                                            gsiTest.Gsi_RunTest();
                    }
                }


                try {
                    TS.processlogfile();
                    System.exit(0);
                } catch (FileNotFoundException e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
                }
        }

}