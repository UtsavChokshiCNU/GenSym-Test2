package com.gensym.core.util;

import java.net.*;
import java.nio.charset.Charset;
import java.io.*;

public class CommandClient
{
  public static void main(String[] args)
  {
    try {
      Socket socket = new Socket(InetAddress.getByName(args[0]),
				 Integer.parseInt(args[1]));
      String directory = args[2];
      String command = args[3];
      PrintStream out = new PrintStream(socket.getOutputStream(), false, Charset.defaultCharset().name());
      InputStream in = socket.getInputStream();
      System.out.println("in = "+in);
      Thread t = new Thread(new BufferedCopy(in));
      t.start();
      System.out.println("before command sent");
      out.println(directory);
      out.println(command);
      System.out.println("after command sent");
      t.join();
      out.close();
    } catch (Exception e)
      {
	e.printStackTrace();
      }
  }

  private static class BufferedCopy implements Runnable {
    private InputStream is;
    private PrintWriter out;

    BufferedCopy(InputStream is) {
      this.is = is;
      this.out = out;
    }
      
    @Override
    public void run() {
      BufferedReader br = new BufferedReader(new InputStreamReader(is, Charset.defaultCharset()));
      System.out.println("made buffered reader ");
      try {
	for (;;) {
	  String line = br.readLine();
	  if (line == null)
	    break;
	  System.out.println(line);
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
