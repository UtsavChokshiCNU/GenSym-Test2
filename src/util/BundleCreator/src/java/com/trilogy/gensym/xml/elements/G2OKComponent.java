package com.trilogy.gensym.xml.elements;

import java.util.List;

/**
 * @author rvasyl
 *
 */
public class G2OKComponent {

    private String bundleName;
    private String familyName;
    private String printName;
    private List   options;           /*Strings*/
    private List   clientList;        /*Double*/

    /**
     * Content of 'g2-ok-component' tag in XML file.
     * 
     * @param bundleName
     * @param familyName
     * @param printName
     * @param options
     * @param clientList
     */
    public G2OKComponent(String bundleName, String familyName, String printName, List options, List clientList) {
        this.bundleName = bundleName;
        this.familyName = familyName;
        this.printName = printName;
        this.options = options;
        this.clientList = clientList;
    }

    public String getBundleName() {
        return bundleName;
    }

    public String getFamilyName() {
        return familyName;
    }

    public String getPrintName() {
        return printName;
    }

    public List getOptions() {
        return options;
    }

    public List getClientList() {
        return clientList;
    }
}
