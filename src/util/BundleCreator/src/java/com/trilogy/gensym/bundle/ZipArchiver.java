package com.trilogy.gensym.bundle;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.zip.ZipEntry;
import java.util.zip.ZipOutputStream;

import org.apache.log4j.Logger;

/**
 * @author rvasyl
 *
 */
public class ZipArchiver {

    private static Logger logger = Logger.getLogger(ZipArchiver.class);

    private static final int BUFFER = 2048;

    private final File folderToArchive;
    private final File zipFile;

    /**
     * Class for creating ZIP archive. 
     * 
     * @param folderToArchive
     * @param zipFileName
     */
    public ZipArchiver (File folderToArchive, String zipFileName) {
        if (!folderToArchive.exists())
            throw new IllegalArgumentException("Folder for archiving doesn't exists.");
        if (folderToArchive.isFile())
            throw new IllegalArgumentException("There must be folder for archiving, but not file.");
        this.folderToArchive = folderToArchive;
        zipFile = new File(zipFileName);
        if (zipFile.exists())
            throw new IllegalArgumentException("ZIP file with the same name '" + zipFileName + "' exists. Please delete this file.");
    }

    /**
     * Method creates ZIP archive with name zipFileName from folder 
     * folderToArchive passed in constructor. It archives all content of 
     * the folder including directory hierarchy.
     * 
     * @return zipFile
     * @throws IOException
     */
    public File zipFolder() throws IOException {
        logger.info("Creating archve file: " + zipFile.getAbsoluteFile());
        ZipOutputStream out = new ZipOutputStream(new BufferedOutputStream(new FileOutputStream(zipFile)));
        BufferedInputStream in = null;
        byte[] data = new byte[BUFFER];
        Object files[] = getFilesNames(folderToArchive, null).toArray();
        for (int i = 0; i < files.length; i ++) {
            logger.debug("Archiving: " + files[i]);
            FileInputStream fis = new FileInputStream(folderToArchive.getPath() + File.separator + files[i]);
            in = new BufferedInputStream(fis, BUFFER);
            out.putNextEntry(new ZipEntry((String)files[i]));
            int count;
            while((count = in.read(data, 0, BUFFER)) != -1) {
                out.write(data, 0, count);
            }
            out.closeEntry();
            fis.close();
        }
        out.flush();
        out.close();
        in.close();
        logger.info("Archive file was created sucessfully.");
        return zipFile;
    }

    private List getFilesNames(File inFolder, String subfolder) {
        List tempStorage;
        List fileNames = new ArrayList();    
        File [] contentOfPath = inFolder.listFiles();
        for (int i = 0; i < contentOfPath.length; i++) {
            if (contentOfPath[i].isFile()){
                fileNames.add(getFileOrFolderName(subfolder, contentOfPath[i].getName()));
            } else {
                tempStorage =  getFilesNames(contentOfPath[i], 
                        getFileOrFolderName(subfolder, contentOfPath[i].getName()));
                for (int j = 0; j < tempStorage.size(); j++) {
                    fileNames.add(tempStorage.get(j));
                }
            }
        }
        return fileNames;
    }

    private String getFileOrFolderName(String subfolder, String fileName) {
        if (subfolder == null)
            return fileName;
        else
            return subfolder + File.separator + fileName;
    }
}
