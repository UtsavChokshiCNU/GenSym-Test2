package com.gensym.beansruntime.jarresource;

import java.net.*;
import java.io.*;

public class Handler extends URLStreamHandler {
    @Override
    public URLConnection openConnection(URL u) throws IOException {
	return new SimpleResourceConnection(u);
    }
}

