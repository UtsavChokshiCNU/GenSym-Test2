/*
 * 
 * This program connects to G2, and makes it load and save a kb, saving only the
 * top level module.
 *   Usage: -g2host <g2hostname> [-g2port <g2portName>] -kb <kbname>
 *   -g2port defaults to 1111.
 * 
 */
package com.gensym.tests;

import com.gensym.classes.Kb;
import com.gensym.classes.Module;
import com.gensym.jgi.*;  
import com.gensym.ntw.*;  
import com.gensym.core.CmdLineArgHandler;
import com.gensym.ntw.util.LoadSaveKBTools;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;

public class LoadAndSaveKB {

  public static void main(String args[]) {

    // Here an attempt to connect to a G2 server if a port ('-g2port <port>')
    // and/or host name ('-g2host <host>') is specified on the commandline
    CmdLineArgHandler cmdline = new CmdLineArgHandler(args);

    String host = cmdline.getOptionValue("-g2host");
    String port = cmdline.getOptionValue("-g2port");
    String kbname = cmdline.getOptionValue("-kb");

    TwAccess g2_connection = null;

    if ((port != null || host != null) && kbname != null)
      {
	try { 
	  // Attempt to connect to G2, and wait until successful or timeout
	  g2_connection = 
	    TwGateway.openConnection((host == null ? "localhost" : host),
					  (port == null ? "1111" : port));

	  // We have connected OK, load and save the KB
          LoadSaveKBTools.setSaveRequiredModules(Boolean.FALSE);

          doLoadSave(g2_connection, kbname);
	} catch (Exception e) {
	  System.out.println("Problem, error was " + e.toString());
	  e.printStackTrace();
	  System.exit(0);
	}

      } else
	System.out.println("Usage: -g2host <g2hostname> [-g2port <g2portName>] -kb <kbname>");
      
    System.exit(0);
  }

  public static void doLoadSave(TwAccess g2_connection, String kbname) throws com.gensym.jgi.G2AccessException, java.io.FileNotFoundException {

    Boolean loaded = LoadSaveKBTools.loadKB(g2_connection, kbname);

    boolean timedout = true;

    try {
      /* Nod off a while to let the kb load. This is a KLUGE.
	 It's possible that there is a javalink or Telewindows 2 mechanism to be
	 notified of KB load finished, but I couldn't find it */
	Thread.sleep(10000); 
    } catch (Exception e) {
      System.out.println("Interrupted while sleeping.");
    }

    Kb kb = g2_connection.getKb();
    Module module = kb.getTopLevelModule();
    Symbol modsym = module.getName();
    Symbol state = g2_connection.getG2State();

    if (state.equals(G2Gateway.RUNNING_)) {
      g2_connection.setG2State(G2Gateway.RESET_);
    }

    Sequence s = LoadSaveKBTools.saveModule(g2_connection, modsym, kbname);
    if (s != null) 
      System.out.println("Save problems? " + s);
    else
      System.out.println("Saved " + modsym + " as " + kbname);

    try {
      /* and let it finish saving as well.  This is probably not as big a deal,
         since the whole save mechanism has a start/continue/finish set up
         already */
      Thread.sleep(2000);  


    } catch (Exception e) {
      System.out.println (e);
    }


  }

}
