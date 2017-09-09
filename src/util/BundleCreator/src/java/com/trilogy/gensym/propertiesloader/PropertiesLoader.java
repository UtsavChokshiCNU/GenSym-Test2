package com.trilogy.gensym.propertiesloader;

import java.io.IOException;
import java.io.InputStream;
import java.util.Properties;

import org.apache.log4j.Logger;

/**
 * @author rvasyl
 *
 */
public class PropertiesLoader {

    private static Logger logger = Logger.getLogger(PropertiesLoader.class);

    /**
     * Class for loading property file. As input it takes path to properties file.
     * Throw IllegalArgumentException if passed properties file doesn't exist.
     * If all operations complete successfully, it returns Properties object.
     * 
     * @param fileName
     * @return properties
     * @throws IllegalArgumentException
     * @throws IOException
     */
    public static Properties loadPropertyFile(String fileName) throws IllegalArgumentException, IOException {
        logger.info("Start loading properties " + fileName);
        ClassLoader cl = PropertiesLoader.class.getClassLoader();
        InputStream in = cl.getResourceAsStream(fileName);
        if (in == null) {
            throw new IllegalArgumentException("Properties file '" + fileName + "' doesn't exist.");
        }
        Properties prop = new Properties();
        prop.load(in);
        in.close();
        logger.info("End loading properties " + fileName);
        return prop;
    }
}
