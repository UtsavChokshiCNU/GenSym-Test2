package com.gensym.beanbuilder;


import java.net.URL;
import java.net.MalformedURLException;



/**
 * This class is used in conjunction with class symantec.itools.OS.Context to
 * provide URLs that are relative to an applet’s or application’s
 * document base. For applets the document base is the URL of the document
 * that the applet is embedded in. For applications the document base is the
 * same as the “user.dir” system property.
 */
public class RelativeURL
{
    /**
     * Don’t use, this is an all-static class.
     */
    public RelativeURL() {
    }

    /**
     * Determines the absolute URL given a relative URL.
     * If the spec parameter is relative, it is considered to be relative
     * to the current document base as determined by getDocumentBase() in
     * class symantec.itools.lang.Context.
     *
     * @param spec a possibly relative URL
     * @return the absolute URL equivalent to the given relativeURL
     * @exception MalformedURLException
     * if cannot generate the resultant URL due to a bad spec parameter
     * or a bad document base
     */
    public static URL getURL(final String spec)
        throws MalformedURLException
    {
    	String specParam = spec;
        // InternetExplorer for some reason strips out a single anchor symbol (#)
        // when the URL is passed to showDocument() so we double up the symbol (##)
        if (System.getProperty("java.vendor").startsWith("Microsoft") &&
    		specParam.indexOf('#') > -1) {
        		specParam = ieAnchorHack(specParam);
        }

        URL documentBase = Context.getDocumentBase();

        if(documentBase != null && specParam.indexOf("//") == -1)
        {
            return new URL(documentBase,specParam);
        }

        return new URL(specParam);
    }

    private static String ieAnchorHack(String spec) {
        String str = spec.substring(0, spec.lastIndexOf('#'));
        str += "#";
        str += spec.substring(spec.lastIndexOf('#'));
        return str;
    }


}
