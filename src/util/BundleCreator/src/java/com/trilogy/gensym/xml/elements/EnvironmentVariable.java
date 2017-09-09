package com.trilogy.gensym.xml.elements;

import java.util.List;

/**
 * @author rvasyl
 *
 */
public class EnvironmentVariable {

    private String value;
    private String appendOrMerge;
    private List   name;              //String
    private List   envVarName;        //String

    /**
     * Content of 'environment-variables' tag in XML file.
     * 
     * @param value
     * @param appendOrMerge
     * @param envVarName
     * @param name
     */
    public EnvironmentVariable (String value, String appendOrMerge, List envVarName, List name) {
        this.value = value;
        this.appendOrMerge = appendOrMerge;
        this.envVarName = envVarName;
        this.name = name;
    }

    public String getValue() {
        return value;
    }

    public String getAppendOrMerge() {
        return appendOrMerge;
    }

    public List getEnvVarName() {
        return envVarName;
    }

    public List getName() {
        return name;
    }
}
