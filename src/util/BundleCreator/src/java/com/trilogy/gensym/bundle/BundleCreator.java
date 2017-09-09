package com.trilogy.gensym.bundle;

import java.io.File;
import java.io.IOException;
import java.net.URISyntaxException;

import java.util.List;
import java.util.Properties;

import javax.xml.parsers.ParserConfigurationException;

import org.apache.log4j.Logger;
import org.xml.sax.SAXException;

import com.trilogy.gensym.bundle.file.Finder;
import com.trilogy.gensym.bundle.file.FilesWorker;
import com.trilogy.gensym.constants.BundleStringConstants;
import com.trilogy.gensym.constants.FilenamesStringConstants;
import com.trilogy.gensym.propertiesloader.PropertiesLoader;
import com.trilogy.gensym.xml.XMLParser;
import com.trilogy.gensym.xml.elements.Bundle;
import com.trilogy.gensym.xml.elements.Component;
import com.trilogy.gensym.xml.elements.ComponentPart;
import com.trilogy.gensym.xml.elements.FamilyType;
import com.trilogy.gensym.xml.elements.G2OKComponent;
import com.trilogy.gensym.xml.exception.XMLParserException;

/**
 * @author rvasyl
 *
 */
public class BundleCreator {

    private static Logger logger = Logger.getLogger(BundleCreator.class);
    
    private static final String DASH = "-";
    private static final String TAR = "tar";
    private static final String DOT_ZIP = ".zip";
    private static final String BUNDLES = "bundles";
    private static final String TREE = "tree";

    private File outFolderT;
    private File outFolderZ;
    private OSStorage os;
    private Properties paths;
    
    public BundleCreator () throws IllegalArgumentException, IOException {
        os = OSStorage.getInstance();
        logger.info("Platform is: " + os.getNameTag());
        paths = PropertiesLoader.loadPropertyFile(FilenamesStringConstants.PART_PATHS_FILE);
    }

    /**
     * Method call other methods for creating bundle file. 
     * 
     * @param xmlFileName
     * @throws XMLParserException 
     * @throws ParserConfigurationException 
     * @throws IOException 
     * @throws SAXException 
     * @throws IllegalArgumentException 
     * @throws URISyntaxException 
     * @throws Exception
     */
    public void generateBundle(String xmlFileName) throws IllegalArgumentException, SAXException, IOException, ParserConfigurationException, XMLParserException, URISyntaxException   {
        FamilyType xmlComtent = new XMLParser(xmlFileName).parseXML();
        cerateOutputStructure(xmlComtent);
        copySelectedFiles(xmlComtent);
        new ZipArchiver(outFolderT, outFolderZ.getAbsolutePath() + File.separator + 
                os.getNameTag() + DOT_ZIP).zipFolder();
        if (FilesWorker.deleteFolder(outFolderT.getParentFile()))
            logger.info("Temp directory " + outFolderT.getParentFile().getAbsolutePath() + " was deleted sucessfully.");
        else
            logger.error("Some problem occurs while directory " + outFolderT.getParentFile().getAbsolutePath() + " deleting.");
    }

    /**
     * Create appropriate structure for copying files.
     * 
     * @param xmlComtent
     * @throws IllegalArgumentException
     */
    protected void cerateOutputStructure (FamilyType xmlComtent) throws IllegalArgumentException {
        String family = null;
        String printName = null;
        if (xmlComtent.getG2Components() != null && xmlComtent.getG2Components().get(0) != null) {
            family = ((G2OKComponent)xmlComtent.getG2Components().get(0)).getFamilyName();
        }
        if (xmlComtent.getPrintName() != null) {
            printName = xmlComtent.getPrintName();
        }
        String outFolderPath = paths.getProperty(BundleStringConstants.DSTBOX) + File.separator + 
                BUNDLES + File.separator + printName + File.separator + family;
        String outFolderTemp = outFolderPath + File.separator + TREE + File.separator + 
                os.getNameTag() + DASH + printName;
        String outFolderZip = outFolderPath + File.separator + TAR;
        outFolderZ = new File(outFolderZip);
        if(!outFolderZ.exists()) {
            outFolderZ.mkdirs();
        }
        outFolderT = new File(outFolderTemp);
        if (outFolderT.exists()) {
            throw new IllegalArgumentException ("The folder '" + outFolderTemp + "' exists. Please delete this folder");
        }
        outFolderT.mkdirs();
        logger.info("Temporary folder for copying all files into it: " + outFolderT.getAbsolutePath());
    }

    /**
     * Goes through content of XML file and create bundle according all records.
     * 
     * @param xmlComtent
     * @throws IOException
     * @throws ParserConfigurationException
     * @throws SAXException
     * @throws URISyntaxException
     */
    protected void copySelectedFiles(FamilyType xmlComtent) throws IOException, ParserConfigurationException, SAXException, URISyntaxException {
        List bundles = xmlComtent.getBundles();
        Finder fFinder = new Finder(paths);
        Bundle bundle;
        List components;
        Component component;
        List componentParts;
        ComponentPart componentPart;
        logger.info("Start copying files and folders into Temp directory");
        for (int i = 0; i < bundles.size(); i++) {
            bundle = (Bundle)bundles.get(i);
            components = bundle.getComponents();
            for (int j = 0; j < components.size(); j++) {
                component = (Component)components.get(j);
                componentParts = component.getComponentparts();
                for (int k = 0; k < componentParts.size(); k++) {
                    componentPart = (ComponentPart)componentParts.get(k);
                    if (!testIsNotPlatform(componentPart)) {
                        workWithFiles(componentPart, fFinder);
                    }
                }
            }
        }
        logger.info("End copying files and folders into Temp directory");
    }

    /**
     * Determine file or folder is in passed componentPart and copy it into 
     * appropriate structure.
     * 
     * @param componentPart
     * @param fFinder
     * @throws IOException
     * @throws ParserConfigurationException
     * @throws SAXException
     * @throws URISyntaxException
     */
    protected void workWithFiles(ComponentPart componentPart, Finder fFinder) throws IOException, ParserConfigurationException, SAXException, URISyntaxException {
        if (componentPart.getSourceFilename().isEmpty()) {
            File folderCopyOut = fFinder.findFolderToCopy(componentPart);
            if (folderCopyOut != null) {
                File folderCopyIn = new File(createDirCopyIn(componentPart, outFolderT));
                FilesWorker.copyFilesInFolder(folderCopyOut, folderCopyIn);
            }
        } else {
            List filesToCopy = fFinder.findFilesToCopy(componentPart);
            for (int l = 0; l < filesToCopy.size(); l++) {
                FilesWorker.copyFile(createFilesCopyIn(componentPart, outFolderT, 
                        (File)filesToCopy.get(l)), (File)filesToCopy.get(l));
            }
        }
    }

    /**
     * Creates file to copy in.
     * 
     * @param componentPart
     * @param outFolder
     * @param fileFromCopy
     * @return file
     * @throws IOException
     */
    protected File createFilesCopyIn(ComponentPart componentPart, File outFolder, File fileFromCopy) throws IOException {
        String dirCopyIn = createDirCopyIn(componentPart, outFolder);
            File fileCopyIn = new File(dirCopyIn + File.separator + fileFromCopy.getName());
            if (!fileCopyIn.exists())
                fileCopyIn.createNewFile();
        return fileCopyIn;
    }

    /**
     * Creates directories and files to copy in.
     * 
     * @param componentPart
     * @param outFolder
     * @return
     */
    protected String createDirCopyIn(ComponentPart componentPart, File outFolder) {
        File folder;
        String destatationDir = null;
        if (componentPart.getDestDir() != null)
            destatationDir = componentPart.getDestDir();
        folder = new File(outFolder.getAbsolutePath() + File.separator + destatationDir);
        if (!folder.exists()) {
            folder.mkdirs();
        }
        return folder.getAbsolutePath();
    }

    /**
     * Tests if current platform is in list of non-platforms in passed 
     * componentPart it returns true, in the other case returns false.
     * 
     * @param componentPart
     * @return
     */
    protected boolean testIsNotPlatform(ComponentPart componentPart) {
        List platforms = componentPart.getNonPlatforms();
        if (platforms != null) {
            for (int i = 0; i < platforms.size(); i++) {
                if (((String)platforms.get(i)).toLowerCase().equals(os.getNikName()))
                    return true;
            }
        }
        return false;
    }

    /**
     * Method for creating bundle from XML file passed as parameter.
     * 
     * @param args
     */
    public static void main(String[] args) {
        try{
            if (args.length == 0){
                throw new IllegalArgumentException("There must be passed XML file name as argument");
            }
            BundleCreator bc = new BundleCreator();
            bc.generateBundle(args[0]);
        } catch (Exception e) {
            logException(e);
        }
    }

    private static void logException(Exception e) {
        logger.fatal(e.toString());
        StackTraceElement elements[] = e.getStackTrace();
        for (int i=0, n=elements.length; i<n; i++) {
            logger.fatal("\t at " + elements[i].toString());
        }
    }
}
