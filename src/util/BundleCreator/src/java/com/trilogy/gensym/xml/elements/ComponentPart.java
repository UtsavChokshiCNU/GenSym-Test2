package com.trilogy.gensym.xml.elements;

import java.util.List;

/**
 * @author rvasyl
 *
 */
public class ComponentPart {
    
    private String version;
    private String register;
    private String makeNROnly;
    private String componentpartname;
    private String printName;
    private String source;
    private String sourceSubdirectory;
    private List   platforms;             //Strings
    private List   sourceFilename;        //Strings
    private String destDir;
    private String destFilename;
    private String sourceSType;
    private String indep;
    private List   removeFromS;           //Strings
    private List   envVariables;          //EnvironmentVariable
    private List   regEntries;            //Strings
    private List   shortcuts;             //ShortCuts
    private String postinstallCode;
    private List   nonPlatforms;          //String
    
    /**
     * Content of 'componentpart' tag in XML file.
     * 
     * @param version
     * @param register
     * @param makeNROnly
     * @param componentpartname
     * @param printName
     * @param source
     * @param sourceSubdirectory
     * @param platforms
     * @param sourceFilename
     * @param destDir
     * @param destFilename
     * @param sourceSType
     * @param indep
     * @param removeFromS
     * @param envVariables
     * @param regEntries
     * @param shortcuts
     * @param postinstallCode
     * @param nonPlatforms
     */
    public ComponentPart(String version, String register, String makeNROnly,String componentpartname, 
            String printName, String source, String sourceSubdirectory, List platforms,
            List sourceFilename,  String destDir, String destFilename,  String sourceSType, 
            String indep, List removeFromS,  List envVariables,
            List regEntries,  List shortcuts, String postinstallCode, List nonPlatforms) {
        this.version = version;
        this.register = register;
        this.makeNROnly = makeNROnly;
        this.componentpartname = componentpartname;
        this.printName = printName;
        this.source = source ;
        this.sourceSubdirectory = sourceSubdirectory;
        this.platforms = platforms;
        this.sourceFilename = sourceFilename;
        this.destDir = destDir;
        this.destFilename = destFilename;
        this.sourceSType = sourceSType;
        this.indep = indep;
        this.removeFromS = removeFromS;
        this.envVariables = envVariables;
        this.regEntries = regEntries;
        this.shortcuts = shortcuts;
        this.postinstallCode = postinstallCode;
        this.nonPlatforms = nonPlatforms;
    }

    public String getVersion() {
        return version;
    }

    public String getRegister() {
        return register;
    }

    public String getMakeNROnly() {
        return makeNROnly;
    }

    public String getComponentpartname() {
        return componentpartname;
    }

    public String getPrintName() {
        return printName;
    }

    public String getSource() {
        return source;
    }

    public String getSourceSubdirectory() {
        return sourceSubdirectory;
    }

    public List getPlatforms() {
        return platforms;
    }

    public List getSourceFilename() {
        return sourceFilename;
    }

    public String getDestDir() {
        return destDir;
    }

    public String getDestFilename() {
        return destFilename;
    }

    public String getSourceSType() {
        return sourceSType;
    }

    public String getIndep() {
        return indep;
    }

    public List getRemoveFromS() {
        return removeFromS;
    }

    public List getEnvVariables() {
        return envVariables;
    }

    public List getRegEntries() {
        return regEntries;
    }

    public List getShortcuts() {
        return shortcuts;
    }

    public String getPostinstallCode() {
        return postinstallCode;
    }

    public List getNonPlatforms() {
        return nonPlatforms;
    }
}
