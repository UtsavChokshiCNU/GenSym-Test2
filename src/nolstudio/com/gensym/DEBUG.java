package com.gensym;
import java.io.*	  ;
import java.nio.charset.Charset;
public class DEBUG extends PrintStream implements Serializable{
	public static boolean debugFlag = false;
	public static final boolean more = false;
	public static boolean debugOutput = false;
	private static boolean initFile = true;
	private BufferedWriter out;
	public DEBUG() throws UnsupportedEncodingException {
		super(new BufferedOutputStream(System.out), false, Charset.defaultCharset().name());
	}

	/** this prints the usual stack trace **/
	@Override
	public void print(char c[]) {
		String s = new String(c);
		dumpToFile(s);		
	}

	/** this prints the usual stack trace **/
	@Override
	public void println(char c[]) {
		String s = new String(c);
		dumpToFile(s);		
	}

	/** this prints out the exception error that occurred **/
	@Override
	public void println(String s) { 
		if(s != null){
			dumpToFile(s);		
		}
	}

	/** this prints out the exception error that occurred **/
	@Override
	public void print(String s) { 
		dumpToFile(s);		
	}

	/** this prints the usual stack trace **/
	@Override
	public void println(Object o) { 
		dumpToFile(o.toString());		
	}

	/** this prints the usual stack trace **/
	@Override
	public void print(Object o) { 
		dumpToFile(o.toString());		
	}

	private void dumpToFile(String s) {
		File targetFile = new File("debug.txt");
		if(!targetFile.canWrite()){
			targetFile.delete();
		}
		FileOutputStream outStream = null;
	    Writer fileOut = null;
		try {
			Charset charset = Charset.defaultCharset();
			if(initFile) { // open a new one, effectively deleting the old one.
				outStream = new FileOutputStream("debug.txt", false);
		    	fileOut = new OutputStreamWriter(outStream, charset);
				out = new BufferedWriter(fileOut);
				initFile = false;
			}
			else { // append to current file...
				outStream = new FileOutputStream("debug.txt", true);
				fileOut = new OutputStreamWriter(outStream, charset);
				out = new BufferedWriter(fileOut);
			}
			
			out.write(s);
			out.newLine(); 
			out.flush();
		} catch(IOException e) { 
			System.err.println("Non-Fatal exception: " + e.getMessage());
			e.printStackTrace();
		} finally {                       // always close the file
		  	closeSilently(out);
		  	closeSilently(fileOut);
		  	closeSilently(outStream);
		}
		
	}
	
	protected void closeSilently(Closeable obj){
	  try {
	      if (obj != null) 
	    	  obj.close();
      } catch (IOException e) {
    	  System.err.println("Non-Fatal exception: " + e.getMessage());
		  e.printStackTrace();
      } 
	}
}