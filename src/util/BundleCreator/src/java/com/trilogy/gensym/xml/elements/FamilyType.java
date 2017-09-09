package com.trilogy.gensym.xml.elements;

import java.util.List;

/**
 * @author rvasyl
 *
 */
public class FamilyType {

    private float  index;
    private float  fileSyntaxVersion;
    private String printName;
    private String directory;
    private String guid;
    private String splashScreen;
    private String licenseText;
    private String platforms;
    private List   g2Components;                 //G2OKComponent        
    private List   bundles;                      //Bundle
    private List   compatiblePreviousVer;        //Version
    private List   previousVer;                  //Version

    /**
     * Content of 'type-family' tag (the first tag) in XML file.
     * 
     * @param index
     * @param fileSyntaxVersion
     * @param printName
     * @param directory
     * @param guid
     * @param splashScreen
     * @param licenseText
     * @param platforms
     * @param g2Components
     * @param bundles
     * @param compatiblePVer
     * @param previousVer
     */
    public FamilyType (float index, float fileSyntaxVersion, String printName, String directory, 
            String guid, String splashScreen, String licenseText, String platforms,
            List g2Components, List bundles, List compatiblePVer, List previousVer) {
        this.index = index;
        this.fileSyntaxVersion = fileSyntaxVersion;
        this.printName = printName;
        this.directory = directory;
        this.guid = guid;
        this.splashScreen = splashScreen;
        this.licenseText = licenseText;
        this.platforms = platforms;
        this.g2Components = g2Components;
        this.bundles = bundles;
        this.compatiblePreviousVer = compatiblePVer;
        this.previousVer = previousVer;
    }

    public float getIndex() {
        return index;
    }

    public float getFileSyntaxVersion() {
        return fileSyntaxVersion;
    }

    public String getPrintName() {
        return printName;
    }

    public String getDirectory() {
        return directory;
    }

    public String getGuid() {
        return guid;
    }

    public String getSplashScreen() {
        return splashScreen;
    }

    public String getLicenseText() {
        return licenseText;
    }

    public List getG2Components() {
        return g2Components;
    }

    public List getBundles() {
        return bundles;
    }

    public List getCompatiblePreviousVer() {
        return compatiblePreviousVer;
    }

    public List getPreviousVer() {
        return previousVer;
    }

    public String getPlatforms() {
        return platforms;
    }
}
