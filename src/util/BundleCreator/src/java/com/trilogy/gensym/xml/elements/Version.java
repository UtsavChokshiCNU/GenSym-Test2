package com.trilogy.gensym.xml.elements;

/**
 * @author rvasyl
 *
 */
public class Version {

    private final String versionid;
    private final String versionguid;

    /**
     * Content of 'version' tag (it may be 'previous-versions' or 
     * 'compatible-previous-versions' tag) in XML file.
     * 
     * @param versionID
     * @param versionguID
     */
    public Version(String versionID, String versionguID) {
        versionid = versionID;
        versionguid = versionguID;
    }

    public String getVersionid() {
        return versionid;
    }

    public String getVersionguid() {
        return versionguid;
    }
}
