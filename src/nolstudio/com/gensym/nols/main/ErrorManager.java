package com.gensym.nols.main;

import java.io.*;
import java.nio.charset.Charset;

/**
 * a class to capture exceptions and errors to 
 *
 * @version	1.1 December 30, 1998
 * @author brian o bush, gearhead
**/
//public class ErrorManager extends PrintWriter {  // cannot do this, since System.setErr() requires a printStream
public class ErrorManager extends PrintStream {

	private GenericFrame errFrame;
	private BufferedWriter out;
	private static boolean initFile = true;
	private NolMainFrame mainFrame;
	private boolean intoFileOnly = true;	   //need to set to true when release.

	public ErrorManager() throws UnsupportedEncodingException {
		super(new BufferedOutputStream(System.out), false, Charset.defaultCharset().name());
		errFrame = new GenericFrame("An Error has Occurred");
	}


	public void setMainFrame(NolMainFrame mainFrame) {
		this.mainFrame = mainFrame;
	}

	/** this prints the usual stack trace **/
	@Override
	public void print(char c[]) {
		String s = new String(c);
		if(intoFileOnly){
			dumpToFile(s);		
		}else{
			postErrorToFrame(s);
		}
	}

	/** this prints the usual stack trace **/
	@Override
	public void println(char c[]) {
		String s = new String(c);
		if(intoFileOnly){
			dumpToFile(s);		
		}else{
			postErrorToFrame(s);
		}
	}

	/** this prints out the exception error that occurred **/
	@Override
	public void println(String s) { 
		if(s != null){
			if(intoFileOnly){
				dumpToFile(s);		
			}else{
				postErrorToFrame(s);
			}
		}
	}

	/** this prints out the exception error that occurred **/
	@Override
	public void print(String s) { 
		if(intoFileOnly){
			dumpToFile(s);		
		}else{
			postErrorToFrame(s);
		}
	}

	/** this prints the usual stack trace **/
	@Override
	public void println(Object o) { 
		if(intoFileOnly){
			dumpToFile(o.toString());		
		}else{
			postErrorToFrame(o.toString());
		}
	}

	/** this prints the usual stack trace **/
	@Override
	public void print(Object o) { 
		if(intoFileOnly){
			dumpToFile(o.toString());		
		}else{
			postErrorToFrame(o.toString());
		}
	}

	private void dumpToFile(String s) {
		File targetFile = new File("error.txt");
		if(!targetFile.canWrite()){
			targetFile.delete();
		}
		
		FileOutputStream outStream = null;
		Writer streamWriter = null;
		try {
			Charset charset = Charset.defaultCharset();
			if(initFile) { // open a new one, effectively deleting the old one.
				outStream = new FileOutputStream("error.txt", false);
				initFile = false;
			}
			else { // append to current file...
				outStream = new FileOutputStream("error.txt", true);
			}
			
			streamWriter = new OutputStreamWriter( outStream, charset);
			out = new BufferedWriter(streamWriter);
			
			out.write(s);
			out.newLine(); 
			out.flush();
		} catch(IOException e) { 
			System.err.println("Non-Fatal exception: " + e.getMessage());
			e.printStackTrace();
		} finally {                       // always close the file
			closeSilently(out);
			closeSilently(streamWriter);
			closeSilently(outStream);
		}
	}
	
	private void closeSilently(Closeable obj){
	  try {
	      if (obj != null) 
	    	  obj.close();
      } catch (IOException e) {
    	  System.err.println("Non-Fatal exception: Error while closing stream : " + e.toString());
    	  e.printStackTrace();
      } 
	}

	private void postErrorToFrame(String s) {
		if (mainFrame!=null) {
//			mainFrame.setWaitCursor(false);
		}

//Should not suppress any exception!

/*		// Suppress any exception error that is not nolstudio exception.
		if((s.indexOf("com.gensym.nols") <0)){
			System.out.println(s);
			return;
		}

		// Suppress the AWT class cast exception error
		if( (s.indexOf("Exception") >=0) && (s.indexOf("java.lang.ClassCastException") >=0) )
			return;
		if( s.indexOf("java.awt.FlowLayout") >=0 )
			return;

  */
		// Normal error processing
		char c [] = new char[s.length()];
		for(int i = 0; i < s.length(); i++) {
			if(s.charAt(i) == '\u0009')
				c[i] = '\n';
			else 
				c[i] = s.charAt(i);
		}
		String s2 = new String(c);
		dumpToFile(s2);
		if(errFrame.isVisible()) {
			errFrame.setMessage(s2);
		}
		else {
			errFrame.clearMessage();
			errFrame.setMessage("An unexpected error has occurred.  Save your project under a different file name, and try to reload,or revert to an earlier saved copy.  Please report the circumstances of this error to Gensym Corporation, and include the error.txt file in NOL Studio's root directory.\n");
			errFrame.setMessage(s2);
			errFrame.setBounds(100,100,650,400);
			errFrame.setVisible(true);
		}
	}
}