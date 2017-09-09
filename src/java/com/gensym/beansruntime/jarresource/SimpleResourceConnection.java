package com.gensym.beansruntime.jarresource;

import java.net.*;
import java.io.*;
import com.gensym.beansruntime.G2ClassLoader;

public class SimpleResourceConnection extends URLConnection {
    private static boolean debug = false;

    private Object resource;	// the resource we are fetching
    private String cookie;	// identification of the loader instance to use
    private String name;	// name of the resource
    private final String prefix = G2ClassLoader.urlPrefix;
    private final int prefixLength = prefix.length();

    protected SimpleResourceConnection (URL url)
		throws MalformedURLException, IOException
    {
	super(url);
	debug("SimpleResourceConnection("+url+")");
	String file = url.getFile();
	if (file.startsWith("/")) {
	    file = file.substring(1);
	}
	if (! file.startsWith(prefix)) {
	    throw new MalformedURLException("SimpleResource file should start with /SIMPLE");
	}
	cookie = file.substring(prefixLength, file.indexOf("/+/"));
	name = file.substring(file.indexOf("/+/")+3);

	debug(" cookie: "+cookie);
	debug(" name: "+name);
    }

    @Override
    public void connect() throws IOException {
	debug("Looking for "+cookie+", "+name+" in SimpleResourceLoader");
	Object o = G2ClassLoader.getLocalResource(cookie, name);
	if (o == null) {
	    debug("Invalid resource name");
	    resource = null;
	    return;
	} else {
	    debug("Found resource "+o);
	    resource = o;
	}
    }

    @Override
    public Object getContent() throws IOException {
	if (!connected) {
	    connect();
	}
	return resource;
    }

    @Override
    public InputStream getInputStream() throws IOException {
	if (!connected) {
	    connect();
	}

	if (resource instanceof InputStream) {
	    return (InputStream) resource;
	}
	return G2ClassLoader.getLocalResourceAsStream(cookie, name);
    }


    private void debug(String msg) {
	if (debug) {
	    System.err.println(msg);
	}
    }


}
