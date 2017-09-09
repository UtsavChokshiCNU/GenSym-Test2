package com.gensym.nols.data;

/**
 *		Gensym Project Class.
 *		This class is extended from Object.class
 *		Modified 3/2/99 by Gchen
 */
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;
import java.util.zip.GZIPOutputStream;

import com.gensym.nols.deploy.OnlineProcessor;
/**
  * A class whose sole purpose in life is to control the reading, writing and repair of files written
  * in different vesions. */

public class VersionManagerForOnlineProcessor implements Cloneable, Serializable {
	static final long serialVersionUID = 1L;
	static final int productFileVersion = 1; // change this when necessary

	private int instanceFileVersion = productFileVersion;
	private transient OnlineProcessor processor;

 /**Save the project to a file.*/
	public void saveToFile(String fileName){
		saveToFile(null,fileName);
	}

/**Save the project to a file.*/
	public void saveToFile(String directory, String fileName){
		try {
			File sourceFile;
			if(directory==null)
				sourceFile = new File(fileName);	
			else
				sourceFile = new File(directory,fileName);
        // Create the necessary output streams to save the data.
			FileOutputStream fos = new FileOutputStream(sourceFile); // Save to file
			GZIPOutputStream gzos = new GZIPOutputStream(fos);     // Compresse
			ObjectOutputStream out = new ObjectOutputStream(gzos); // Save object
			out.writeObject(this);      // Write the entire Vector of scribbles
			out.flush();                 // Always flush the output.
			out.close();                 // And close the stream.
		}catch (IOException e) { 	
			System.err.println("Non-Fatal exception: " + e.getMessage());
			e.printStackTrace();
		}
	}

	@Override
	public Object clone() throws CloneNotSupportedException {
		VersionManagerForOnlineProcessor cloned = (VersionManagerForOnlineProcessor) super.clone();
		cloned.processor = processor == null ? null : (OnlineProcessor) processor.clone();
		return cloned;
	}

	private void readObject(ObjectInputStream in) throws ClassNotFoundException, IOException {
		in.defaultReadObject();
		if (productFileVersion < instanceFileVersion)
			throw new IOException("Incompatible file versions");
     // change
     // could do some initial preparation before reading in the project...
		processor = (OnlineProcessor)in.readObject();
		if(productFileVersion<instanceFileVersion){
			throw new IOException("Isn't it time you upgraded?");
		}
		switch (instanceFileVersion) {
		case 1:
//			throw new IOException("Isn't it time you upgraded?");
		case 2:
		//		   doTheThingForVersion2(in); // version2 stupidly wrote extra stuff in its writeObject, so now we need to read over it
		case 3:
		   // projectObject is an instance variable, so it doesn't need to be passed around
		//		   doALittleInternalRepairToBringItUpToCurrentNeeds();
		   break;
		default:
           // everythings cool
		}
	}
 

// change
	private void writeObject(ObjectOutputStream out) throws IOException{
		out.defaultWriteObject();
		out.writeObject(processor);
	}
   
	public OnlineProcessor getProcessor() {
		return processor;
	}

	public void setProcessor(OnlineProcessor processor){
		this.processor = processor;
	}
}

