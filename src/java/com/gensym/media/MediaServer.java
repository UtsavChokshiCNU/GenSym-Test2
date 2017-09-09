package com.gensym.media;

import java.net.*;
import java.io.*;
import java.util.Vector;
import java.util.StringTokenizer;
import java.util.Hashtable;
import java.util.Properties;
import com.gensym.classes.MediaBin;
import com.gensym.util.Symbol;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.jgi.*;
import com.gensym.message.Trace;

public class MediaServer implements Runnable {
  private ServerSocket serverSocket;
  
  private Thread listener=null;
  
  // The server's configuration information is stored in these properties
  protected static Properties props = new Properties();
  
  // The mime types information is stored in this propertie list
  protected static Properties MimeTypes = new Properties();

  protected String localRoot = "c:\\";
  protected String host = "localhost";
  protected String port = "1111";
  protected int listenerPort = 80;
  private Hashtable mediaBins = new Hashtable();
  private G2Access connection;

  static final Symbol MEDIA_BIN_ = Symbol.intern ("MEDIA-BIN");
  static final Symbol TYPE_ = Symbol.intern ("TYPE");
  static final Symbol CONTENTS_ = Symbol.intern ("CONTENTS");
  static final Symbol DIRECTORY_ = Symbol.intern ("DIRECTORY");  
  
  public MediaServer(String localRoot, String host, String port)
  {  
    this.localRoot = localRoot;
    this.host = host;
    this.port = port;
    listener = new Thread(this);
    listener.start();
  }
  
  public MediaServer() 
  {   
    listener = new Thread(this);
    listener.start();
  }
  
  public static void main(String[] args) {
    Trace.setExceptionTraceOn(true);
    if (args.length < 3) 
      throw new IllegalArgumentException("must specific localRoot, host, and port");
    MediaServer server = new MediaServer(args[0], args[1], args[2]);
  }
  
  @Override
  public void run() {
    
    try{
      
      loadMimes();
      
      System.out.println("MediaServer listening on port:"+listenerPort);
      serverSocket = new ServerSocket(listenerPort);
      while(true) {
	Socket s = serverSocket.accept(); 
	new Thread(new Getter(s,this)).start();
      }
      } catch(Exception e) {
	e.printStackTrace();
	System.out.println("MediaServer listner thread failure:"+e);
      }
   }
   
   // load the properties file
   static void loadProps() throws IOException {
      File f = new File("MediaServer.properties");
      if (f.exists()) {
         InputStream is =new BufferedInputStream(new FileInputStream(f));
         props.load(is);
         is.close();
      }
   } 

   static void loadMimes() throws IOException {
      File f = new File("mimetypes.properties");
      if (f.exists()) {
         InputStream is =new BufferedInputStream(new FileInputStream(f));
         MimeTypes.load(is);
         is.close();
      }
   }

  protected G2Access getConnection()
  {
    if (connection != null)
      return connection;
    try {
      connection 
	= G2Gateway.getOrMakeConnection(new G2ConnectionInfo(host,port));
    } catch (ConnectionTimedOutException ctoe)
      {
	Trace.exception(ctoe);
      }
    catch (G2AccessInitiationException gaie)
      {
	Trace.exception(gaie);
      }
    return connection;
  }


  protected MediaBin getMediaBin(String binName)
  {
    Object entry = mediaBins.get(binName);
    if (entry != null)
      return (MediaBin) entry;
    else
      {
	Exception e = null;
	try {
	  Symbol binNameSymbol = Symbol.intern(binName);
	  MediaBin mediaBin 
	    = (MediaBin) getConnection().getUniqueNamedItem (MEDIA_BIN_, 
							     binNameSymbol);
	  // Structure description = mediaBin.describe(location);
	  mediaBins.put(binName,mediaBin);
	  return mediaBin; // can return null
	} 
	catch (G2AccessException g2ae)
	  {
	    e = g2ae;
	  }
	catch (Exception ioe)
	  {
	    e = ioe;
	  }
	if (e != null)
	  e.printStackTrace();
	throw new RuntimeException("nested exception: "+e.getMessage());
      }
  }

   
} 

class Getter implements Runnable{
  private Socket client;
  private MediaServer server;
  private String header;
  private DataInputStream requestedFile;
  private int fileLength;
  
  Getter(Socket s, MediaServer server) 
  { 
    this.server = server;
    client = s;
  }
  
  @Override
  public void run() 
  {
    String line, fileName = null, mediaBinName = null;
    Vector mediaLocation = null;
    boolean isTop = false;
    boolean isLocal = true;
    boolean isIndex = false;
    boolean isServerFileSystem = false;
    boolean isMediaBinIndex = false;
    
    try {
      BufferedReader dis 
	   = new BufferedReader(new InputStreamReader(client.getInputStream()));
      
      while((line=dis.readLine())!=null) // not really a loop, zero or one passes
	{ // read request from browser
	  StringTokenizer requestTokenizer = new StringTokenizer(line," ");
	  System.out.println("loop top : line = "+line);
	  System.out.println(" with filename "+fileName);
	  if(!requestTokenizer.hasMoreTokens()) break;
	  
	  if(requestTokenizer.nextToken().equals("GET")) // ignore the rest of HTTP
	    {
	      String request = requestTokenizer.nextToken();
	      System.out.println("Get \""+request+"\"");
	      if (request.equals("") || request.equals("/"))
		isTop = true;
	      else if (request.equalsIgnoreCase("local/") ||
		       request.equalsIgnoreCase("/local/"))
		{
		  isIndex = true;
		  fileName = "/";
		}
	      else
		{
		  StringTokenizer tokenizer = new StringTokenizer(request,"/");
		  int tokenCount = tokenizer.countTokens();
		  if (tokenCount >= 2)
		    {
		      String area = tokenizer.nextToken();
		      System.out.println("request area : "+area);
		      if (area.equalsIgnoreCase("local"))
			{
			  // System.out.println("Get Local\""+fileName+"\"");
			  if(request.endsWith("/"))
			    {
			      fileName = makeFileName(tokenizer,true);
			      isIndex = true;
			    }
			  else
			    fileName = makeFileName(tokenizer,false);
			}
		      else if (area.equalsIgnoreCase("g2media") &&
			       (tokenCount >= 3 ||
				(tokenCount == 2 && request.endsWith("/"))))
			{
			  // System.out.println("Get Media File\""+fileName+"\"");
			  mediaBinName = tokenizer.nextToken();
			  isLocal = false;
			  if(request.endsWith("/"))
			    {
			      mediaLocation = makeMediaLocation(tokenizer);
			      isIndex = true;
			    }
			  else
			    mediaLocation = makeMediaLocation(tokenizer);
			}
		      else 
			fileName = null;
		    }
		  else
		    fileName = null;
		}
	    }
	  else
	    {
	      // do nothing with the other input lines yet
	    }
	}
      
      System.out.println("after parse fileName "+fileName+
			 " is IDX "+isIndex+" is Local "+isLocal+
			 " mediaLoc "+mediaLocation);
      if (isLocal && fileName != null)
	{
	  if (isIndex)
	    getLocalIndex(fileName);
	  else
	    getLocalFile(fileName);
	}
      else if (mediaLocation != null)
	{
	  if (isIndex)
	    getMediaIndex(mediaBinName,mediaLocation);
	  else
	    getMediaFile(mediaBinName,mediaLocation);
	}
      
      dis.close();
      client.close();
    } catch(Exception e) {
      e.printStackTrace();
      System.out.print("Error closing Socket\n"+e);
    }
  } // end of SendFile

  private String makeFileName(StringTokenizer tokenizer, boolean keepFirstSlash)
  {
    StringBuffer buffer = new StringBuffer();
    int count = 0;
    while (tokenizer.hasMoreTokens())
      {
	if (count > 0 || keepFirstSlash)
	  buffer.append('/');
	buffer.append(tokenizer.nextToken());
	count++;
      }
    return buffer.toString();
  }
  
  private Vector makeMediaLocation(StringTokenizer tokenizer)
  {
    Vector location = new Vector();
    int count = 0;
    while (tokenizer.hasMoreTokens())
      {
	location.addElement(tokenizer.nextToken());
	count++;
      }
    return location;
  }
  
  private void getTopIndex()
  {
    
  }
  
  private void getLocalIndex(String fileName)
       throws IOException
  {
    String directoryName = server.localRoot+fileName;
    File directory = new File(directoryName);
    System.out.println("Local Index of "+directoryName);
    DataOutputStream clientStream 
      = new DataOutputStream(new BufferedOutputStream(client.getOutputStream()));
    if (directory.exists() && directory.isDirectory())
      {
	constructDirectoryHeader(fileName);
	clientStream.writeBytes(header);
	String[] files = directory.list();
	int i,len = files.length;
	clientStream.writeBytes(makeDirectoryHeader(fileName));
	for (i=0; i<len ; i++)
	  {
	    File subFile = new File(directoryName+files[i]);
	    if (subFile.isDirectory())
	      clientStream.writeBytes(makeIndexLine(files[i]+"/","Directory: "+files[i]));
	    else
	      clientStream.writeBytes(makeIndexLine(files[i],"File:      "+files[i]));
	  }
	clientStream.writeBytes(makeDirectoryFooter());
      }
    else
      {
	clientStream.writeBytes( "HTTP/1.0 404 File not found\n" + 
				 "Allow: GET\n" +
				 "MIME-Version: 1.0\n"+
				 "Server : MediaServer:\n"+
				 "\n\n <H1>404 File not Found</H1>\n");
      }

    clientStream.flush();
    clientStream.close();
  }

  private void getMediaIndex(String mediaBinName, Vector location)
       throws IOException
  {
    MediaBin mediaBin = server.getMediaBin(mediaBinName);
    Structure description = mediaBin.describe(location);
    DataOutputStream clientStream 
      = new DataOutputStream(new BufferedOutputStream(client.getOutputStream()));
    if (description.getAttributeValue(MediaServer.TYPE_,null)
	.equals(MediaServer.DIRECTORY_))
      {
	String directoryName = (location.size() == 0 ? 
				"Top Level" :
				(String)location.lastElement());
	constructDirectoryHeader(directoryName);
	clientStream.writeBytes(header);
	Vector contents 
	  = (Vector) description.getAttributeValue(MediaServer.CONTENTS_,null);   // Strings
	int i,len = contents.size(), lastSubIndex = location.size();
	clientStream.writeBytes(makeDirectoryHeader(directoryName));
	Vector subLocation = (Vector) location.clone();
	subLocation.addElement("");
	for (i=0; i<len ; i++)
	  {
	    String subName = (String)contents.elementAt(i);
	    subLocation.setElementAt(subName,lastSubIndex);
	    System.out.println("media dir sub location "+subLocation);
	    Structure subDescription = mediaBin.describe(subLocation);
	    if (subDescription.getAttributeValue(MediaServer.TYPE_,null)
		.equals(MediaServer.DIRECTORY_))
	      clientStream.writeBytes(makeIndexLine(subName+"/","Directory: "+subName));
	    else
	      clientStream.writeBytes(makeIndexLine(subName,"File:      "+subName));
	  }
	clientStream.writeBytes(makeDirectoryFooter());
      }
    else
      {
	clientStream.writeBytes( "HTTP/1.0 404 File not found\n" + 
				 "Allow: GET\n" +
				 "MIME-Version: 1.0\n"+
				 "Server : MediaServer:\n"+
				 "\n\n <H1>404 File not Found</H1>\n");
      }

    clientStream.flush();
    clientStream.close();
  }

  private void getLocalFile(String fileName)
       throws IOException
  {
    try {
      fileName = fileName.replace('/',File.separatorChar); // jed
      System.out.println("fn "+fileName);
      System.out.println("root "+server.localRoot);
      requestedFile 
	= new DataInputStream
	(new BufferedInputStream(new FileInputStream(server.localRoot+fileName)));
      fileLength = requestedFile.available();
      constructHeader(fileName);
    } catch(IOException e) { // file not found send 404.
      header = "HTTP/1.0 404 File not found\n" + 
	"Allow: GET\n" +
	"MIME-Version: 1.0\n"+
	"Server : MediaServer:\n"+
	"\n\n <H1>404 File not Found</H1>\n";
      fileName = null;
    }
    
    int i;
    
    DataOutputStream clientStream = new DataOutputStream(new BufferedOutputStream(client.getOutputStream()));
    clientStream.writeBytes(header);
    if (fileName != null) {
      while((i = requestedFile.read()) != -1) {
	clientStream.writeByte(i);
      }
    }
    
    clientStream.flush();
    clientStream.close();
  }

  private void getMediaFile(String mediaBinName, Vector location)
       throws IOException
  {
    String name = null;
    try {
      MediaBin mediaBin = server.getMediaBin(mediaBinName);
      Vector locationCopy = (Vector)location.clone();
      if (locationCopy.size() < 1)
	throw new IllegalStateException("Bad MediaBinFile");
      name = (String) location.lastElement();
      locationCopy.removeElementAt(locationCopy.size() - 1);
      requestedFile 
	= new DataInputStream
	(new BufferedInputStream( mediaBin.makeBinaryInputStream(locationCopy, name)));
      fileLength = requestedFile.available();
      constructHeader(name);
    } catch(IOException e) { // file not found send 404.
      Trace.exception(e);
      header = "HTTP/1.0 404 File not found\n" + 
	"Allow: GET\n" +
	"MIME-Version: 1.0\n"+
	"Server : MediaServer:\n"+
	"\n\n <H1>404 File not Found</H1>\n";
      name = null;
    }
    
    int i;
    
    DataOutputStream clientStream = new DataOutputStream(new BufferedOutputStream(client.getOutputStream()));
    clientStream.writeBytes(header);
    if (name != null) {
      while((i = requestedFile.read()) != -1) {
	clientStream.writeByte(i);
      }
    }
    
    clientStream.flush();
    clientStream.close();
  }



  private String makeDirectoryHeader(String indexName)
  {
    return
      "<HTML>\n"+
      "<HEAD>\n"+
      "<META HTTP-EQUIV=\"Content-Type\" CONTENT=\"text/html; charset=iso-8859-1\">\n"+
      "<META NAME=\"Author\" CONTENT=\"default\">\n"+
      "<META NAME=\"GENERATOR\" CONTENT=\"Gensym Media Server 0.01\">\n"+
      "<TITLE> Index of "+indexName+"</TITLE>\n"+
      "</HEAD>\n"+
      "<BODY>\n"+
      "<H1>Index of "+indexName+"</H1>\n";
  }

  private String makeIndexLine(String fileName,String label)
  {
    return "<P>&nbsp;<A HREF="+fileName+">"+label+"</A>\n";
  }
  
  private String makeDirectoryFooter()
  {
    return "</BODY>\n</HTML>\n";
  }
       
    
  private void constructHeader(String fileName)
  {
    String fileType;
    
    fileType = fileName.substring(fileName.lastIndexOf(".")+1,fileName.length());
    fileType = MediaServer.MimeTypes.getProperty(fileType);
    
    System.out.println("getting "+fileName+" with type "+fileType);
    header = "HTTP/1.0 200 OK\n" + 
      "Allow: GET\nMIME-Version: 1.0\n"+
      "Server : G2 MediaServer:\n"+
      "Content-Type: " + fileType + "\n"+
      "Content-Length: " + fileLength +
      "\n\n";
  }

  private void constructDirectoryHeader(String fileName)
  {
    String fileType;
    
    header = "HTTP/1.0 200 OK\n" + 
      "Allow: GET\nMIME-Version: 1.0\n"+
      "Server : G2 MediaServer:\n"+
      "Content-Type: text/html\n"+
      "Content-Length: " + 10000 +
      "\n\n";
  }
}
