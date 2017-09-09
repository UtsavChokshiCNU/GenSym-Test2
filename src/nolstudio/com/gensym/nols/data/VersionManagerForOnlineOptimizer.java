package com.gensym.nols.data;

/**
 *		Gensym VersionManagerForOnlineOptimizer. Class.
 *		This class is extended from Object.class
 *		Created 3/18/99 by Gchen
 */

import java.io.*;
import java.util.zip.*;

import com.gensym.nols.deploy.*;

/**
  * A class whose sole purpose in life is to control the reading, writing and repair of files written
  * in different vesions. */

public class VersionManagerForOnlineOptimizer implements Cloneable, Serializable {
	static final long serialVersionUID = 1L;
	static final int productFileVersion = 1; // change this when necessary

	private int instanceFileVersion = productFileVersion;
	private transient OnlineOptimizer optimizer;

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
		VersionManagerForOnlineOptimizer cloned = (VersionManagerForOnlineOptimizer) super.clone();
		cloned.optimizer = optimizer == null ? null : (OnlineOptimizer) optimizer.clone();
		return cloned;
	}
	
	private void readObject(ObjectInputStream in) throws ClassNotFoundException, IOException {
		in.defaultReadObject();
		if (productFileVersion < instanceFileVersion)
			throw new IOException("Incompatible file versions");
     // could do some initial preparation before reading in the project...
		optimizer = (OnlineOptimizer)in.readObject();
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
		out.writeObject(optimizer);
	}
   
	public OnlineOptimizer getOptimizer() {
		return optimizer;
	}

	public void setOptimizer(OnlineOptimizer optimizer){
		this.optimizer = optimizer;
	}
}

