/*
 * 
 * This program connects to G2, and makes it load, recompile all procedures,
 * and save the resulting kb, saving only the top level module.
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
import com.gensym.uitools.inspect.*;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;

public class RecompileKB {

  public static void main(String args[]) {

    // Here an attempt to connect to a G2 server if a port ('-g2port <port>')
    // and/or host name ('-g2host <host>') is specified on the commandline
    CmdLineArgHandler cmdline = new CmdLineArgHandler(args);

    String host = cmdline.getOptionValue("-g2host");
    String port = cmdline.getOptionValue("-g2port");
    String URL = cmdline.getOptionValue("-tsName");
    String kbname = cmdline.getOptionValue("-kb");

    TwAccess g2_connection = null;

    if ((port != null || host != null) && kbname != null)
      {
	try { 
	  // Attempt to connect to G2, and wait until successful or timeout
	  g2_connection = 
	    TwGateway.openConnection(URL, (host == null ? "localhost" : host),
					  (port == null ? "1111" : port));

	  // We have connected OK, load and save the KB
          LoadSaveKBTools.setSaveRequiredModules(Boolean.FALSE);

	  doLoad(g2_connection, kbname);

	  doInspect(g2_connection);

	  doSave(g2_connection, kbname);
	} catch (Exception e) {
	  System.out.println("Problem, error was " + e.toString());
	  e.printStackTrace();
	}

      } else
	System.out.println("Usage: -g2host <g2hostname> [-g2port <g2portName>] -kb <kbname>");

    System.exit(0);
  }

  public static void doLoad(TwAccess g2_connection, String kbname) throws com.gensym.jgi.G2AccessException, java.io.FileNotFoundException {

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

    Symbol state = g2_connection.getG2State();

    if (state.equals(G2Gateway.RUNNING_)) {
      g2_connection.setG2State(G2Gateway.RESET_);
    }

  }

  public static Symbol getModule(TwAccess g2_connection) throws com.gensym.jgi.G2AccessException {
    Kb kb = g2_connection.getKb();
    Module module = kb.getTopLevelModule();
    if (module != null)
      return module.getName();
    else return null;
  }


  public static void doSave(TwAccess g2_connection, String kbname) throws com.gensym.jgi.G2AccessException, java.io.FileNotFoundException {

    Symbol modsym = getModule(g2_connection);

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

  protected static Symbol status = Symbol.intern("SLEEPING");
  private static final Symbol FINISHED_ = Symbol.intern ("FINISHED");

  public static void doInspect(TwAccess g2_connection) throws com.gensym.jgi.G2AccessException, java.io.FileNotFoundException {
    
    Symbol modsym = getModule(g2_connection);
    System.out.println("recompiling module " + modsym);
    InspectSession IS =
      new InspectSession(" every item " +
			 ((modsym == null) ? "" : ("assigned to module " + modsym)));
    IS.setPrefix(InspectSession.RECOMPILE);
    IS.addInspectSessionListener(new RecompilerListener());
    IS.addConnection(g2_connection);
    IS.start();
    while (status != FINISHED_)
      try {
	Thread.sleep(500); 
      } catch (Exception e) {
	System.out.println("Interrupted while sleeping.");
      }
  }

}

class RecompilerListener implements InspectSessionListener {
  @Override
  public void infoUpdated(InspectSessionEvent event) {
    RecompileKB.status = event.getStatus();    
  }
}
