package com.trilogy.gensym.bundle;

import java.util.Properties;

/**
 * @author rvasyl
 *
 */
public class OSStorage {

    private final static String OS_NAMRE = "os.name";
    
    private final String nikName;
    private final String nameTag;
    private final String name;
    
    private OSStorage (String nikName, String nameTag, String name) {
        this.nikName = nikName; 
        this.nameTag = nameTag; 
        this.name = name;
    }
    
    /**
     * Method returns new instance of OSStorage object, it is determined
     * from system properties. In case if there is some unknown platform,
     * IllegalArgumentException is thrown.
     * 
     * @return
     * @throws IllegalArgumentException
     */
    public static OSStorage getInstance() throws IllegalArgumentException{
        Properties sysprops = System.getProperties();
        String operationSystemName = sysprops.getProperty(OS_NAMRE);
        if (operationSystemName.indexOf("Windows") != -1) {
            return new OSStorage("nt", "intelnt", "Windows");
        }
        if (operationSystemName.indexOf("Red Hat Linux") != -1) {
            return new OSStorage("linux", "linux", "Red Hat Linux");
        }
        if (operationSystemName.indexOf("Compaq Tru64 UNIX") != -1) {
            return new OSStorage("alphaosf", "alphaosf", "Compaq Tru64 UNIX");
        }
        if (operationSystemName.indexOf("IBM AIX") != -1) {
            return new OSStorage("aix", "rs6000", "IBM AIX");
        }
        if (operationSystemName.indexOf("Sun Solaris") != -1) {
            return new OSStorage("sparcsol", "sparcsol", "Sun Solaris");
        }
        if (operationSystemName.indexOf("PA-RISC HP-UX") != -1) {
            return new OSStorage("hpux", "hp9000s700", "PA-RISC HP-UX");
        }
        if (operationSystemName.indexOf("Itanium HP-UX") != -1) {
            return new OSStorage("hpia64", "hpia64", "Itanium HP-UX");
        }
        throw new IllegalArgumentException("Unknown platform: " + operationSystemName);
    }

    public String getNikName() {
        return nikName;
    }

    public String getNameTag() {
        return nameTag;
    }

    public String getName() {
        return name;
    }
}
