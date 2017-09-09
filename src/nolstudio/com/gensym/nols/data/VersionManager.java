package com.gensym.nols.data;

/**
 *		Gensym Project Class.
 *		This class is extended from Object.class
 *		Modified 11/12/97 by Gchen
 */
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;
import java.util.Vector;
import java.util.zip.GZIPOutputStream;
/**
  * A class whose sole purpose in life is to control the reading, writing and repair of files written
  * in different vesions. */

public class VersionManager implements Cloneable, Serializable {
	static final long serialVersionUID = 1L;
	static final int productFileVersion = 3; // change this when necessary. new version 12.6.2002
	private static final boolean isEvaluationCopy = false;

	private int instanceFileVersion = productFileVersion;
	private transient Project2 projectObject;

 /**Return the indicator of evaluation */
	public boolean isEvaluationCopy(){
		return isEvaluationCopy;
	}
	
	@Override
	public Object clone() throws CloneNotSupportedException {
		VersionManager cloned = (VersionManager) super.clone();
		cloned.projectObject = projectObject == null ? null : (Project2) projectObject.clone();
		return cloned;
	}

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
			System.err.println(e.getMessage());
			e.printStackTrace();}
	}


	private void readObject(ObjectInputStream in) throws ClassNotFoundException, IOException {
//System.out.println("start readobject in the versionmanager");
		in.defaultReadObject();
//System.out.println("finishen default readobject in the versionmanager");
		if (productFileVersion < instanceFileVersion)
			throw new IOException("Incompatible file versions");
		if(productFileVersion<instanceFileVersion){
			throw new IOException("Cannot load project file, it was created in a newer version of NeurOnLine Studio than this.");
		}

//		System.out.println("instanceFileVersion="+instanceFileVersion);
		switch (instanceFileVersion) {
		case 1:
			Project pObject1 = (Project)in.readObject();
			// Upgrade NolModel to NolModel2...introduced in V20b0 (3/15/99)
			Vector models = pObject1.getPredictiveModels();
			for(int i=0;i<models.size();i++) {
				NolModel oldModel = (NolModel) models.elementAt(i);
				NolModel2 newModel = oldModel.upgrade_1_2();
				models.setElementAt(newModel,i);
			}
			// Upgrade formulas
			Vector preps = pObject1.getPreprocessors();
			for(int i=0;i<preps.size();i++) {
				Preprocessor prep = (Preprocessor) preps.elementAt(i);
				Vector formulas = prep.getFormulas();
				for(int j=0;j<formulas.size();j++) {
					Formula oldFormula = (Formula) formulas.elementAt(j);
					Formula2 newFormula = oldFormula.convert_1_2();
					formulas.setElementAt(newFormula,j);
				}
			}
			// Boldly delete the opt models
			Vector optModels = pObject1.getOptimizationModels();
			optModels.removeAllElements();
			projectObject = new Project2(pObject1); 
			break;
		case 2:
			// Now we start do thing for version 2.Convert 
			Project pObject2 = (Project)in.readObject();
			projectObject = new Project2(pObject2); 
		   break;
		case 3:
			projectObject = (Project2)in.readObject();
		   // projectObject is an instance variable, so it doesn't need to be passed around
		//		   doALittleInternalRepairToBringItUpToCurrentNeeds();
//System.out.println("load from here");
//System.out.println("nuber of gen="+projectObject.getNumberOfGenOptimizations());
		   break;
		default:
           // everythings cool
		}
	}
 

// change
	private void writeObject(ObjectOutputStream out) throws IOException{
		out.defaultWriteObject();
		out.writeObject(projectObject);
	}
   
	public Project2 getProject() {
		return (Project2)projectObject;
	}

	public void setProject(Project2 projectObject){
		this.projectObject = projectObject;
	}
}

