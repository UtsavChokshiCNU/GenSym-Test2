package com.trilogy.gensym.bundle.file;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.MappedByteBuffer;
import java.nio.channels.FileChannel;

import org.apache.log4j.Logger;

/**
 * @author rvasyl
 *
 */
public class FilesWorker {

    private static Logger logger = Logger.getLogger(FilesWorker.class);

    /**
     * Method for copying file 'out' into file 'in'.
     * 
     * @param in     file to copy
     * @param out    file must be copyed
     * @throws IOException 
     */
    public static void copyFile(File in, File out) throws IOException  {
        logger.debug("Copying file: " + out.getAbsolutePath() + " to file " + in.getAbsolutePath());
        FileChannel fcin = new FileInputStream(out.getAbsoluteFile()).getChannel();
        FileChannel fcout = new FileOutputStream(in.getAbsoluteFile()).getChannel();
        MappedByteBuffer buf = fcin.map(FileChannel.MapMode.READ_ONLY, 0, fcin.size());
        fcout.write(buf);
        fcin.close();
        fcout.close();
    }

    /**
     * Method for copying all files from folder folderOut into folder folderIn.
     * 
     * @param folderOut     files from this folder must be copyed
     * @param folderIn      all files must be copyed into this folder
     * @throws IOException
     */
    public static void copyFilesInFolder(File folderOut, File folderIn) throws IOException {
        logger.debug("Copying folder: " + folderOut.getAbsolutePath() + " to folder " + folderIn.getAbsolutePath());
        File[] contentOfPath = folderOut.listFiles();
        for (int i = 0; i < contentOfPath.length; i++) {
            if (contentOfPath[i].isFile()) {
                File copyIn = new File(folderIn + File.separator +  contentOfPath[i].getName());
                if (!copyIn.exists())
                    copyIn.createNewFile();
                copyFile(copyIn, contentOfPath[i]);
            }
        }
        logger.debug("Copying folder " + folderOut.getName() + " complete successfully.");
    }

    /**
     * Method for deleting passed directory. 
     * 
     * @param directory    directory must be deleted
     * @return
     */
    public static boolean deleteFolder(File directory) {
        File[] contentOfPath = directory.listFiles();
        for (int i = 0; i < contentOfPath.length; i++) {
            if (contentOfPath[i].isFile()) {
                contentOfPath[i].delete();
            } else {
                deleteFolder(contentOfPath[i]);
            }
        }
        return directory.delete();
    }
}
