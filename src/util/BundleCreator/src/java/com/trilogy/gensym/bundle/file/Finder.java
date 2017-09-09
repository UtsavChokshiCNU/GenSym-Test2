package com.trilogy.gensym.bundle.file;

import java.io.File;
import java.io.IOException;
import java.net.URISyntaxException;
import java.util.ArrayList;
import java.util.List;
import java.util.Properties;

import javax.xml.parsers.ParserConfigurationException;

import org.apache.log4j.Logger;
import org.xml.sax.SAXException;

import com.trilogy.gensym.constants.BundleStringConstants;
import com.trilogy.gensym.constants.FilenamesStringConstants;
import com.trilogy.gensym.xml.PathsXMLParser;
import com.trilogy.gensym.xml.elements.ComponentPart;

/**
 * @author rvasyl
 *
 */
public class Finder {

    private List pathsToLookForFiles;
    private boolean useOptIntc = false;
    private Properties paths;

    /**
     * Class for finding paths to files and directories in local computer.
     * 
     * @throws ParserConfigurationException
     * @throws SAXException
     * @throws IOException
     * @throws URISyntaxException
     */
    public Finder (Properties paths) throws ParserConfigurationException, SAXException, IOException, URISyntaxException {
        pathsToLookForFiles = new PathsXMLParser(FilenamesStringConstants.PATHS_FILE).getPaths();
        if (paths.getProperty(BundleStringConstants.USE_INTC).equalsIgnoreCase("true"))
            useOptIntc = true;
        this.paths = paths;
    }

    private static Logger logger = Logger.getLogger(Finder.class);

    /**
     * Method look for files passed in componentPart object in local computer.
     * If file is present in local computer, it is added into list filesToCopy
     * and returned back. In case if file is not present in local computer,
     * appropriate message is logged. 
     * 
     * @param componentPart
     * @param paths
     * @return filesToCopy 
     * @throws ParserConfigurationException
     * @throws SAXException
     * @throws IOException
     * @throws URISyntaxException
     */
    public List findFilesToCopy(ComponentPart componentPart) throws ParserConfigurationException, SAXException, IOException, URISyntaxException {
        List filesToCopy = new ArrayList();
        List srcFilenames = componentPart.getSourceFilename();
        File file;
        int initialLength;
        if (srcFilenames != null) {
            String sourceFileName;
            initialLength = filesToCopy.size();
             for (int i = 0; i < srcFilenames.size(); i++) {
                 sourceFileName = (String)srcFilenames.get(i);
                 if (useOptIntc) {
                     file = new File(paths.getProperty(BundleStringConstants.DSTBOX) +
                            File.separator + componentPart.getSource() +
                            File.separator + paths.getProperty(BundleStringConstants.OPT_INTC) +
                            File.separator + sourceFileName);
                     if (file.exists()) {
                         filesToCopy.add(file);
                         logger.debug("File was added for copying: " + sourceFileName);
                         continue;
                     }
                 }
                 file = new File(paths.getProperty(BundleStringConstants.DSTBOX) +
                         File.separator + componentPart.getSource() +
                        File.separator + paths.getProperty(BundleStringConstants.OPT) +
                        File.separator + sourceFileName);
                 if (file.exists()) {
                     filesToCopy.add(file);
                     logger.debug("File was added for copying: " + sourceFileName);
                     continue;
                 }
                 file = new File(paths.getProperty(BundleStringConstants.DSTBOX) +
                         File.separator + componentPart.getSource() +
                         File.separator + paths.getProperty(BundleStringConstants.TAPE) +
                         File.separator + sourceFileName);
                 if (file.exists()) {
                     filesToCopy.add(file);
                     logger.debug("File was added for copying: " + sourceFileName);
                     continue;
                 }
                 if (componentPart.getSource() != null && componentPart.getSourceSubdirectory() != null) {
                     file = new File(paths.getProperty(BundleStringConstants.SRCBOX) +
                             File.separator + componentPart.getSource() +
                             File.separator + componentPart.getSourceSubdirectory() +
                             File.separator + sourceFileName);
                     if (file.exists()) {
                         filesToCopy.add(file);
                         logger.debug("File was added for copying: " + sourceFileName);
                         continue;
                     }
                     file = new File(paths.getProperty(BundleStringConstants.DSTBOX) +
                             File.separator + componentPart.getSource() +
                             File.separator + componentPart.getSourceSubdirectory() +
                             File.separator + sourceFileName);
                     if (file.exists()) {
                         filesToCopy.add(file);
                         logger.debug("File was added for copying: " + sourceFileName);
                         continue;
                     }
                 }
                 for (int j = 0; j < pathsToLookForFiles.size(); j ++) {
                     file = new File(pathsToLookForFiles.get(j) +
                             File.separator + sourceFileName);
                     if (file.exists()) {
                         filesToCopy.add(file);
                         logger.debug("File was added for copying: " + sourceFileName);
                         break;
                     } 
                 }
                 if (initialLength == filesToCopy.size())
                     logger.error("Impossible to find " + sourceFileName + " file");
             }
        }
        return filesToCopy;
    }

    /**
     * Method look for folder passed in componentPart object in local computer.
     * If folder is present in local computer, it returns back. In case if 
     * folder is not present in local computer, appropriate message is logged. 
     * 
     * @param componentPart
     * @param paths
     * @return folder
     * @throws ParserConfigurationException
     * @throws SAXException
     * @throws IOException
     * @throws URISyntaxException
     */
    public File findFolderToCopy(ComponentPart componentPart) throws ParserConfigurationException, SAXException, IOException, URISyntaxException {
        if (componentPart.getSource() != null && componentPart.getSourceSubdirectory() != null) {
            File folder;
            folder = new File(paths.getProperty(BundleStringConstants.DSTBOX) +
                    File.separator + componentPart.getSource() +
                    File.separator + componentPart.getSourceSubdirectory());
            if (folder.exists()) {
                logger.debug("Folder added for copying: " + folder.getAbsolutePath());
                return folder;
            }
            folder = new File(paths.getProperty(BundleStringConstants.SRCBOX) +
                File.separator + componentPart.getSource() +
                File.separator + componentPart.getSourceSubdirectory());
                if (folder.exists()) {
                    logger.debug("Folder added for copying: " + folder.getAbsolutePath());
                    return folder;
                }
            logger.error("Impossible to find " + folder.getAbsolutePath() + " folder");
        }
        return null;
    }
}
