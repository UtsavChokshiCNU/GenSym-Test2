package com.gensym.jgi.download;

import java.io.*;
import java.nio.charset.Charset;

public class ClassGenerationHelper {
    private static final String Spaces = "                                ";

    protected ByteArrayOutputStream testStream;
    protected PrintWriter printWriter;

    private int indent = 0;
    private String indentString = "";

    public ClassGenerationHelper() {
        this.clearStream();
    }

    protected void clearStream() {
        this.testStream = new ByteArrayOutputStream();
        this.printWriter = new PrintWriter(new OutputStreamWriter(this.testStream, Charset.defaultCharset()), true);
    }

    protected void decreaseIndent(int delta) {
        this.indent -= delta;
        this.indentString = Spaces.substring(0, this.indent);
    }

    protected void increaseIndent(int delta) {
        this.indent += delta;
        this.indentString = Spaces.substring(0, this.indent);
    }

    protected void print(String x) {
        this.printWriter.print(x);
    }

    protected void println() {
        this.printWriter.println();
    }

    protected void println(String x) {
        this.printWriter.println(x);
    }

    protected void iprint(String x) {
        this.printWriter.print(indentString);
        this.printWriter.print(x);
    }

    protected void iprintln(String x) {
        this.iprint(x);
        this.printWriter.println();
    }

    protected void iprintMultiLineString(String x) {
        BufferedReader br = new BufferedReader(new StringReader(x));
        String line;
        try {
            while ((line = br.readLine()) != null)
                iprintln(line);
        } catch (IOException ioe) {
            System.err.println(ioe);
        }
    }

    protected void createSut() {
        this.testStream = new ByteArrayOutputStream();
        this.printWriter = new PrintWriter(new OutputStreamWriter(testStream, Charset.defaultCharset()), true);
    }
}
