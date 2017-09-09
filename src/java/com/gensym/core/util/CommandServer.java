package com.gensym.core.util;

import java.net.*;
import java.nio.charset.Charset;
import java.io.*;

public class CommandServer implements Runnable {
  private ServerSocket serverSocket;
  
  private Thread listener=null;
  boolean trace = false;  
  protected int listenerPort = 8888;

  public CommandServer()
  {  
    this(8888);
  }
  
  public CommandServer(int listenerPort)
  {  
    this.listenerPort = listenerPort;
    listener = new Thread(this);
    listener.start();
  }

  @Override
  public void run() {
    
    try{
      if (trace)
	System.out.println("CommandServer listening on port:"+listenerPort);
      serverSocket = new ServerSocket(listenerPort);
      while(true) {
	Socket s = serverSocket.accept(); 
	new Thread(new Command(s,this)).start();
      }
      } catch(Exception e) {
	e.printStackTrace();
	System.out.println("CommandServer listener thread failure:"+e);
      }
   }
   
  public static void main(String[] args)
  {
    if (args[0].equals("launch"))
      {
	try 
	  {
	    Runtime r = Runtime.getRuntime();
	    Process process = 
	      r.exec("java com.gensym.core.util.CommandServer run "+(args.length == 1? "" : args[1]));
	    System.out.println("Started command server in process "+process);
	  } catch (Exception e)
	    {
	      e.printStackTrace();
	    }
      }
    else
      {
	if (args.length == 1)
	  new CommandServer();
	else
	  new CommandServer(Integer.parseInt(args[1]));
      }
  }
}


class Command implements Runnable{
  private Socket client;
  private CommandServer server;
  
  
  Command(Socket s, CommandServer server) 
  { 
    this.server = server;
    client = s;
  }
  
  @Override
  public void run() 
  {
    try {
      Charset charset = Charset.defaultCharset();
      Runtime runtime = Runtime.getRuntime();
      PrintWriter out = new PrintWriter(new OutputStreamWriter(new BufferedOutputStream(client.getOutputStream()), charset));
      BufferedReader dis = new BufferedReader(new InputStreamReader(client.getInputStream(), charset));
      String directory = dis.readLine();
      String line=dis.readLine();
      System.out.println("Received remote command 2 "+line+" in dir "+directory);
      if (line != null)
	{
	  Process process = runtime.exec(line,
					 new String[0],
					 new File(directory));
	  Thread t = new Thread(new BufferedCopy(process.getInputStream(), out));
	  t.start();
	  // Copy the error stream.
	  new BufferedCopy(process.getErrorStream(), out).run();
	  int exitCode = process.waitFor(); // Wait for the termination of the child
	  t.join();			// Wait for the end of the input stream	  BufferedReader outputReader
	  System.out.println("DONE with command in process "+process+" status="+exitCode);
	  
	}
      
      out.flush();
      out.close();
    }
    catch (InterruptedException ie)
      {
	// yeah right
	ie.printStackTrace();
      }
    catch (IOException e)
      {
	e.printStackTrace();
      }
    catch (RuntimeException e)
      {
	e.printStackTrace();
      } 
  }

  private static class BufferedCopy implements Runnable {
    private InputStream is;
    private PrintWriter out;

    BufferedCopy(InputStream is, PrintWriter out) {
      this.is = is;
      this.out = out;
    }
      
    @Override
    public void run() {
      BufferedReader br = new BufferedReader(new InputStreamReader(is, Charset.defaultCharset()));
      try {
	for (;;) {
	  String line = br.readLine();
	  if (line == null)
	    break;
	  out.println(line);
	}
	br.close();
      }
      catch (IOException ex)
	{
	  ex.printStackTrace();
	}
    }
  }
}
