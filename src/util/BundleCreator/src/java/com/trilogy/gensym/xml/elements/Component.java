package com.trilogy.gensym.xml.elements;

import java.util.List;

/**
 * @author rvasyl
 *
 */
public class Component {

    private String watermark;
    private String typical;
    private String optional;
    private float  radioButtonGI;
    private String componentname;
    private String printName;
    private List   platforms;             //String
    private List   componentparts;        //ComponentPart

    /**
     * Content of 'component' tag in XML file.
     * 
     * @param watermark
     * @param typical
     * @param optional
     * @param radioButtonGI
     * @param componentname
     * @param printName
     * @param platforms
     * @param componentpart
     */
    public Component(String watermark, String typical, String optional, 
            float radioButtonGI, String componentname, String printName, 
            List platforms, List componentpart) {
        this.watermark = watermark;
        this.typical = typical;
        this.optional = optional;
        this.radioButtonGI = radioButtonGI;
        this.componentname = componentname;
        this.printName = printName;
        this.platforms = platforms;
        this.componentparts = componentpart;
    }

    public String getWatermark() {
        return watermark;
    }

    public String getTypical() {
        return typical;
    }

    public String getOptional() {
        return optional;
    }

    public float getRadioButtonGI() {
        return radioButtonGI;
    }

    public String getComponentname() {
        return componentname;
    }

    public List getComponentparts() {
        return componentparts;
    }

    public String getPrintName() {
        return printName;
    }

    public List getPlatforms() {
        return platforms;
    }
}
