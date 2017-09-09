package com.gensym.nols.data;
/*
 */

import java.io.BufferedReader;
import java.io.Closeable;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.Reader;
import java.io.Serializable;
import java.nio.charset.Charset;
import java.util.Vector;

import com.gensym.math.matrix.Matlib;
import com.gensym.math.matrix.Matrix;
import com.gensym.nols.main.NolMainFrame;

public class NolClassicModelTrainer implements Runnable,
	Cloneable, Serializable {
	public static final long serialVersionUID = 1L;
	public static final int BPNTRAINING = 0;
	public static final int RBFNTRAINING = 1;
	public static final int ANNTRAINING = 2;
	public static final int RHOTRAINING = 3;

	public static final int RBFNFIT = 11;
	public static final int ANNFIT = 12;
	public static final int RHOFIT = 13;


	public static int modelCounter = 0;
	//0:bpn training, 1:rbfn training,2:ann training,3:rho training
	private int flag;  
	private NolBpnModel bpnNet;
	private NolRbfnModel rbfnNet;
	private NolRhoModel rhoNet;
	private Matrix input;
	private Matrix output;
	private Vector itsListeners;

	public native int jbpn_trainer(String infile, String outfile);
	public native int jautoassociative_net(String infile, String outfile);
	public native int jrbfn_trainer(String infile, String outfile);
	public native int jrho_trainer(String infile, String outfile);
	public native int jfit_tester(String infile, String outfile);
	public native int jsensitivity_tester(String infile, String outfile);
	public native int joptimizer(String infile, String outfile);

	public String dllName = "jnol";

	public NolClassicModelTrainer(NolBpnModel net ){
		super();
		this.bpnNet = net;
		net.setTrainer(this);
		flag = BPNTRAINING;
		itsListeners = new Vector();
		loadClassicLibrary();
	}

	public NolClassicModelTrainer(NolRbfnModel net ){
		super();
		this.rbfnNet = net;
		net.setTrainer(this);
		flag = RBFNTRAINING;
		itsListeners = new Vector();
		loadClassicLibrary();
	}

	public NolClassicModelTrainer(NolRhoModel net ){
		super();
		this.rhoNet = net;
		net.setTrainer(this);
		flag = RHOTRAINING;
		itsListeners = new Vector();
		loadClassicLibrary();
	}
	
	@Override
	public Object clone() throws CloneNotSupportedException {
		NolClassicModelTrainer cloned = (NolClassicModelTrainer) super.clone();
		cloned.bpnNet = bpnNet == null ? null : (NolBpnModel) bpnNet.clone();
		cloned.rbfnNet = rbfnNet == null ? null : (NolRbfnModel) rbfnNet.clone();
		cloned.rhoNet = rhoNet == null ? null : (NolRhoModel) rhoNet.clone();
		cloned.input = input == null ? null : (Matrix) input.clone();
		cloned.output = output == null ? null : (Matrix) output.clone();

		cloned.itsListeners  = itsListeners == null  ? null : (Vector) itsListeners.clone();
		
		return super.clone();
	}

	private void loadClassicLibrary(){
		String dirStr = NolMainFrame.mainFrame.getRootDirectory();
//		dirStr = dirStr+"\\bin;"+dirStr+"\\nolstudio\\bin;"+System.getProperty("java.library.path");
/*		ErrorManagerFrame errf = new ErrorManagerFrame("message");
		errf.setMessage("lib path="+System.getProperty("java.library.path"));
		errf.setVisible(true);
*/
//		System.setProperty("java.library.path", dirStr);

//System.out.println("dir = "+dirStr);
//System.out.println("lib = "+System.getProperty("java.library.path"));

		if (dirStr.endsWith("\\nolstudio")){
			String newDir =  dirStr+"\\bin";
			System.setProperty("user.dir", newDir);
		}else if (dirStr.endsWith("\\projects")){
			String newDir =  dirStr;
			newDir = newDir.replaceAll("projects", "bin");
//System.out.println("newDir = "+newDir);
			System.setProperty("user.dir", newDir);
		}
		System.loadLibrary(dllName);
		System.setProperty("user.dir", dirStr);

	}

	public void setFlag(int flag){
		this.flag = flag;
	}

	public void addListener(ClassicModelTrainerListener l) {
		itsListeners.addElement(l);
	}

	public void removeListener(ClassicModelTrainerListener l) {					 
		itsListeners.removeElement(l);
	}

	public void informListeners(String id, String message) {
		for (int i=0; i<itsListeners.size(); ++i) {
			ClassicModelTrainerListener l = (ClassicModelTrainerListener) itsListeners.elementAt(i);
			if(id.equals("complete")){
				l.trainingComplete();
				clearTrainingMatrix();
			}else if(id.equals("update"))
				l.modelUpdated();
			else if(id.equals("error"))
				l.error(message);
		}
	}

	@Override
	public void run (){
		if(input == null || output == null){
			return;
		}
		try{
			if(flag == BPNTRAINING){
				if(bpnNet == null){
					return;
				}
				bpnNet.train(input,output);
			}else if(flag == RBFNTRAINING){
				if(rbfnNet == null){
					return;
				}
				rbfnNet.train(input,output);
			}else if(flag == ANNTRAINING){
			}else if(flag == RHOTRAINING){
				if(rhoNet == null){
					return;
				}
				rhoNet.train(input,output);
			}
		}catch(Exception ev){
			ev.printStackTrace();
		}
	}

	public String[] makeRPCfileNames(){
		String pre = "bpn";
		if(flag == RBFNTRAINING || flag == RBFNFIT) 
			pre = "rbfn";
		else if(flag == RHOFIT || flag == RHOTRAINING) 
			pre = "rho";
		String[] fileNames = new String[2];
		String pathDir = System.getProperties().getProperty("user.dir");
		fileNames[0] = pathDir+File.separatorChar+pre+"in"+ modelCounter+".txt";
		fileNames[1] = pathDir+File.separatorChar+pre+"out"+ modelCounter+".txt";
		modelCounter++;
		return fileNames;
	}

	public void deleteFiles(String[] fileNames){
		for(int i=0;i<fileNames.length;i++){
			File file = new File(fileNames[i]);
			if(file.exists()){
				file.delete();
			}
		}
	}

	public void setBpnModel(NolBpnModel bpnNet){
		this.bpnNet = bpnNet;
	}

	public void setRbfnModel(NolRbfnModel rbfnNet){
		this.rbfnNet = rbfnNet;
	}

	public void setRhoModel(NolRhoModel rhoNet){
		this.rhoNet = rhoNet;
	}

	public NolBpnModel getBpnModel(){
		return this.bpnNet;
	}
	
	public void setInput(Matrix X){
		if(input == null) {
			input = Matlib.createMatrix();
		}
		Matlib.copy(X,input);
	}

	public Matrix getInput(){
		return input;
	}
	
	public void setOutput(Matrix Y){
		if(output == null) {
			output = Matlib.createMatrix();
		}
		Matlib.copy(Y,output);
	}

	public Matrix getOutput(){
		return output;
	}

	public String readErrorFromFile(String infile)throws IOException{
		File SourceFile = new File(infile);
		if (!SourceFile.exists() || !SourceFile.isFile() || !SourceFile.canRead()) 
			return "";
		
		FileInputStream inStream = null;
	    Reader streamReader = null;
	    BufferedReader Source = null;
	    String lineStr = null;
	    try {
	      inStream = new FileInputStream(SourceFile);	
	      streamReader = new InputStreamReader(inStream, Charset.defaultCharset());
	      Source = new BufferedReader(streamReader);
	      lineStr = Source.readLine();
	    } finally {
	  	  closeSilently(Source);
	  	  closeSilently(streamReader);
	  	  closeSilently(inStream);
	  	}
	    
		return lineStr;
	}
	
	private void closeSilently(Closeable obj){
	  try {
	      if (obj != null) 
	    	  obj.close();
      } catch (IOException e) {
    	  System.err.println("NON-FATAL: Error while closing stream : " + e.toString());
      } 
    }
	
	private void clearTrainingMatrix(){
		if(input != null){
			Matlib.clear(input);
		}
		if(output != null){
			Matlib.clear(output);
		}
	}
}