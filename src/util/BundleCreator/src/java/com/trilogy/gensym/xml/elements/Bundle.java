package com.trilogy.gensym.xml.elements;

import java.util.List;

/**
 * @author rvasyl
 *
 */
public class Bundle {

    private String    version;
    private String    directory;
    private String    bundlename;
    private String    printName;
    private List      components;        //Components

    /**
     * Content of 'bundle' tag in XML file.
     * 
     * @param version
     * @param directory
     * @param bundlename
     * @param printName
     * @param components
     */
    public Bundle (String version, String directory, String bundlename, String printName, List components) {
        this.version = version;
        this.directory = directory;
        this.bundlename = bundlename;
        this.printName = printName;
        this.components = components;
    }

    public String getVersion() {
        return version;
    }

    public String getDirectory() {
        return directory;
    }

    public String getBundlename() {
        return bundlename;
    }

    public List getComponents() {
        return components;
    }

    public String getPrintName() {
        return printName;
    }
}
