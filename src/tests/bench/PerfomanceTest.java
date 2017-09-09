import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Map;
import java.util.logging.Level;
import java.util.logging.Logger;

 class PerfTestSuite 
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
               
    PerfTestSuite() {}

    public void setoperatingsystem() //Edit to add new Operating systems.
    {
        operatingsystem=new String(System.getProperty("os.name"));
        System.out.println("\nCurrent Operating System = " + operatingsystem);
        if (operatingsystem.contains("Windows")) {
            operatingsystem="Windows";
            pathseperator=new String("\\");
            cmdstring = new String[3];
            cmdstring[0]=new String("cmd");
            cmdstring[1]=new String("/C");
            cmdstring[2]=new String("StartServer.bat -start -kb ");
            exeimage= new String("g2.exe");
            BridgePath= new String( testfolder + "\\opt-intc");
        } else {
            operatingsystem="Unix";
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
        env.put("G2_MODULE_SEARCH_PATH",testfolder);    // set the module path of test kbs, regression test kbs are dependent on eachother, we need to specify test folder directory
        ab2.directory(fd);           
        try {
            if ( operatingsystem.contains("Windows"))
              ab2.start();
        } catch (IOException ex) {
            Logger.getLogger(PerfTestSuite.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    public void SetSettingsAndFolders(String g2p,String fileArrayStr) throws IOException {

      setoperatingsystem();    //setoperating system and its specific variables.

      File tmpfile = new File("");                
	    testfolder= new String(tmpfile.getAbsolutePath());
      testfolder= testfolder + pathseperator + ".." +pathseperator;                 
	     
	    try {
	        String userName = System.getProperty ( "user.name" );                
	        String res = new String();  
	        BufferedReader set_input =  new BufferedReader(new FileReader(testfolder + "settings.txt"));
	        while ((res=set_input.readLine())!= null) {   
                int index_eql=res.indexOf(':');
                if(res.substring(0,index_eql).contains(operatingsystem)) {
                    int index_eql2=res.indexOf('=');
					if(res.substring(index_eql+1,index_eql2).contains("results")) {
						resultsfolder= new String(res.substring(index_eql2+1,res.length()));
					}
					if (operatingsystem.contains("Unix")) {
						resultsfolder=resultsfolder + userName + pathseperator + "results";   
					}
                }   
	        }   
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        File resultsdir =  new File(resultsfolder);
        if(!resultsdir.exists()) {
            resultsdir.mkdir();
        }
		resultsfolder = resultsfolder + pathseperator;
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
        
        testkbs_list =  fileArrayStr.split(fileSeperator);
        for(String testkbs:testkbs_list){
        	testkbs = new String(testfolder + pathseperator +testkbs);
        }
	    System.out.println("Test Folder = " + testfolder + "\nResults Folder = " + resultsfolder + "\nGensym Directory = " + GensymDir + "\nResults File = " + resultsfile + "\nG2 path = " + g2Path );
    }
        
    public void ConcludeTest() throws IOException
    {
        while(true)
        {   
            Boolean a=false;
            String image =exeimage;
            Process p;
            try {
                if (operatingsystem.contains("Windows")) {
                    p = Runtime.getRuntime().exec(String.format("..%sProcess", pathseperator));
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
	            e.printStackTrace();
	        }
	    }
    }
	public static void programinfo()
	{
	
      System.out.println("\t* 1>> Make sure that test folder Path does not contain any spaces");
	    System.out.println("\t* 2>> As a first argument give  the appropriate path of the g2 installation directory within quotes like Example=>\"C:\\Program Files\\Gensym\\g2-8.3r1\" as argument. and Results folder can be specified in settings.txt file(if not,by default c:\\results is taken)");
	    System.out.println("\t* 3>> If you dona€u8482 t intend to perform GSI regression test , then pass '-gsi' as a second argument to the test suite. Example: Java RegressionTest 'C:\\Program Files\\Gensym\\g2-8.3r1' -gsi");
	    System.out.println("\t* 4>> EDIT 'perfomance_testkbs_list.txt'(which is inside tests\\bench folder) for adding new tests or removing tests from the regression test suite and GSI regression test(gsi-suite.kb) is conducted by default no need to add that into the list");
	    System.out.println("\t* 5>> Output resides in the given results folder or C:\\results\\test-results-log.rg by default, which has Detailed log");
	    System.out.println("\t* 6>> Similarly Brief Summary of tests resides in the Regr-test-summary.log in the results folder");
      System.exit(0); 
	}
 }
 
 class G2PerfTestSuite extends PerfTestSuite
 {
     public void g2_RunTest() throws FileNotFoundException {
         String testkb;
         boolean run_twng=false;
         for (String testkbs : testkbs_list) {
			BufferedReader input = new BufferedReader(new FileReader(testkbs));
			try {
				while ((testkb = input.readLine()) != null) {
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
					String[] cmdArray = new String[] { cmdstring[0],
							cmdstring[1], cmdstring[2] + testfolder + testkb };
					File fd = new File(g2Path);

					ProcessBuilder ab = new ProcessBuilder(cmdArray);
					Map<String, String> env = ab.environment();
					env.put("G2_AUTO_TEST", resultsfolder);
					env.put("G2_MODULE_SEARCH_PATH", testfolder); 
					// set the module path of test kbs, regression test kbs are 
					//dependent on eachother, we need to specify test folder directory
					ab.directory(fd);
					ab.start();
					System.out.println(testkb + " - test is running.......");
					if (run_twng == true) {
						Start_Twng();
					}
					Thread.sleep(5000);
					ConcludeTest();
				}
			} catch (Exception e) {
				System.out.println(e);
				System.out.println("There was a Exception raised while performing tests, Check the log for information");
			}
		}
	}
 }
 
public class PerfomanceTest {
            
    @SuppressWarnings("static-access")
	public static void main(String[] args) throws IOException {
		try{
		    if(args[0].compareTo("-help")==0 || args[0].compareTo("/?")==0) {
		        PerfTestSuite.programinfo();
		    }
		} catch(ArrayIndexOutOfBoundsException a) {
		        PerfTestSuite.programinfo();
		}
		PerfTestSuite TS = new PerfTestSuite();                             
		TS.SetSettingsAndFolders(args[0],args[2]);  
		G2PerfTestSuite g2PerfTest= new G2PerfTestSuite();
		g2PerfTest.g2_RunTest();                        
		System.exit(0);
	}
}
