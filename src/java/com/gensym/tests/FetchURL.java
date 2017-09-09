import java.applet.*;
import java.awt.*;
import java.net.*;
import java.io.*;

// This applet demonstrates the use of the URL and URLConnection
// class to read a file from a web server. The applet reads its
// own .class file, since we can always be sure it exists.

public class FetchURL
{

	public String fetch(String URLstring)
	{
		
		try {

// Open a URL to this applet's .class file. We can locate it by
// using the getCodeBase method and the applet's class name.
			URL url = new URL(URLstring);

// Open a URLConnection to the URL
			URLConnection urlConn = url.openConnection();


// See if we can find out the length of the file. This allows us to
// create a buffer exactly as large as we need.

			int length = urlConn.getContentLength();


// Since we can't be sure of the size of the .class file, use a
// ByteArrayOutputStream as a temporary container. Once we are finished
// reading, we can convert it to a byte array.

			ByteArrayOutputStream tempBuffer;

// If we don't know the length of the .class file, use the default size
			if (length < 0) {
				tempBuffer = new ByteArrayOutputStream();
			} else {
				tempBuffer = new ByteArrayOutputStream(length);
			}

// Get an input stream to this URL		
			//InputStream instream = urlConn.getInputStream();
			InputStream instream = url.openStream();


// Read the contents of the URL and copy it to the temporary buffer
			int ch;
			while ((ch = instream.read()) >= 0) {
				tempBuffer.write(ch);
			}

			System.out.println("Got " + tempBuffer.toString());

// Convert the temp buffer to a byte array (we don't do anything with
// the array in this applet other than take its size.
			return tempBuffer.toString();

		} catch (Exception e) {
			return e.toString();
		}
	}

	
}		
