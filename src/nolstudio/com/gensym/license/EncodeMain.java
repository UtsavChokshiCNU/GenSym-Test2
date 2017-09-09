package com.gensym.license;

import java.io.*;
import java.lang.*;
import java.util.*;

public class EncodeMain {

	static int ROTORSIZ = 256;
	static int MASK = 0377;
	static int EMPTY = 07777;
	static int X_SIZE = 4099;

	static int[] r1;
	static int[] r2;
	static int[] r3;
	static int x[];
	
	static {
		r1 = new int[ROTORSIZ];
		r2 = new int[ROTORSIZ];
		r3 = new int[ROTORSIZ];
		x = new int[X_SIZE];
		// --- comment out seed for each version and add ---
		// int seed = ; // for version 1
		int seed = 62682382; // for version 2
		int i, random, index;
        for (i = 0 ; i < ROTORSIZ; i++) r1[i] = r2[i] = r3[i] = EMPTY;
        i = 0;
        while (i < ROTORSIZ) {
                seed = (5 * seed + i);
                random = (seed % 65521);
                index = (random & MASK);
                if (r1[index] == EMPTY) {
//System.out.println("seed = "+seed+", random = "+random+", index = "+index);
					r1[index] = i++;
				}
        }
        i = 0;
        while (i < ROTORSIZ) {
                seed = (5 * seed + i);
                random = (seed % 65521);
                index = (random & MASK);
                if (r2[index] == EMPTY) r2[index] = i++;
        }

        i = 0;
        while (i < ROTORSIZ) {
                seed = (5 * seed + i);
                random = (seed % 65521);
                index = (random & MASK);
                if (r3[index] == EMPTY) r3[index] = i++;
        }

        for (i = 0; i < X_SIZE; i++)
        {
                seed = (5 * seed + i);
                random = (seed % 65521);
                x[i] = random & 03;
        }


	}

	// Encrypts .class files starting from current or specified directory
	// If no directory is specified, the current working directory is the root
	// The option -r causes recursive descent below the root directory
	// The option -d causes deletion of the .class file after it is encrypted

	public  static void main(String[] args) 
		throws SecurityException,FileNotFoundException, IOException {
		// Parse optional args
		String dirString = "";
		boolean recurse = false, delete = false;
		for(int k=0;k<args.length;k++) {
			if(args[k].startsWith("-")) {  // option string follows
				String options = args[k];
				for(int l=1;l<options.length();l++) {
					String opt = options.substring(l,l+1);
					if(opt.equals("r")) recurse = true;
					else if(opt.equals("d")) delete = true;
					else {
						System.out.println("Unknown option "+opt);
						System.exit(1);
					}
				}
			}
			else dirString = args[k];   // assume the other input arg, if any, is the directory
		}
		if(dirString.equals("")) dirString = System.getProperty("user.dir");
		// Create directory object 
		File dir = null;
		try {
			dir = new File(dirString);
		} catch (Throwable t) {
			System.out.println("Bad target directory "+dirString);
			System.exit(1);
		}
		// get target file list
		Vector classFiles = new Vector(0,10);
		getClassFiles(dir, classFiles, recurse);
		if(classFiles.size()==0) {
			System.out.println("No class files found");
			System.exit(1);
		}


		// open input and output streams
		for(int j=0;j<classFiles.size();j++) {
			File classFile = (File) classFiles.elementAt(j);
			File cryptFile = makeCryptFile(classFile, "cls");
			FileInputStream fis = new FileInputStream(classFile);
			FileOutputStream fos = new FileOutputStream(cryptFile);
			encode(fis,fos);
			fis.close();
			fos.close();
			System.out.println("Encrypted "+classFile.getName());
			// delete the source file
			if(delete) classFile.delete();
		}
	}

	// adds class files in the given directory to the vector
	private static void getClassFiles(File dir, Vector classFiles, boolean recurse) throws SecurityException {
		// if a single file is to be analyzed
		if(!dir.isDirectory()) {
			classFiles.addElement(dir);
			return;
		}
		// dir is a directory
		Vector directoryList = new Vector(0,10);
		directoryList.addElement(dir);
		while(directoryList.size()>0) {
			File currentDir = (File) directoryList.firstElement();
			directoryList.removeElement(currentDir);
			String[] allFiles = currentDir.list();
			for(int i=0;i<allFiles.length;i++) {
				String fileName = allFiles[i];
				File targetFile = new File(currentDir,fileName);
				if(targetFile.isDirectory()) {
					if(recurse) directoryList.addElement(targetFile);
				} else {
					if(fileName.endsWith(".class")) classFiles.addElement(targetFile);
				}
			}
		}
	}

	private static File makeCryptFile(File classFile, String extension) {
		File cryptFile = null;
		String path = classFile.getAbsolutePath();
		try {
			cryptFile = new File(path.substring(0,path.length()-5)+extension);
		} catch (StringIndexOutOfBoundsException e) {}
		return cryptFile;
	}

	private static void encode(FileInputStream fis, FileOutputStream fos) throws IOException {
		int i=0,j=0,ofs1=0,ofs2=0,ofs3=0;
		int nbytes, ech;
		byte b[], bb;
		b = new byte[256];
		while((nbytes = fis.read(b)) != -1) {
			for(int k=0; k<nbytes; k++) {
				bb = (byte) r3[r2[r1[(int) b[k]+ofs1&MASK]+ofs2&MASK]+ofs3&MASK];
//System.out.println(""+j+": original "+b[k]+" encoded: "+bb);
				j++;
                fos.write(bb);

                switch (x[i]){
                case 00:
                                ofs1 = ++ofs1 & MASK;
                                break;
                case 01:
                                ofs2 = ++ofs2 & MASK;
                                break;
                case 02:
                                ofs3 = ++ofs3 & MASK;
                                break;
                }
                if (ofs1 == 0) ofs2 = ++ofs2 & MASK;
                if (ofs2 == 0) ofs3 = ++ofs3 & MASK;
                if (++i == X_SIZE) i = 0;
			}
        }
	}
}

		

