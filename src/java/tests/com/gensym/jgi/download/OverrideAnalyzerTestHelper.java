package com.gensym.jgi.download;

import com.gensym.util.Symbol;
import org.junit.Rule;
import org.junit.rules.TemporaryFolder;

import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;

import static com.gensym.helpers.ObjectsFactory.anyString;

public class OverrideAnalyzerTestHelper {
    protected static final Symbol IMPORTS_ = Symbol.intern("IMPORTS");
    protected static final String[] PACKAGE_IMPORTS_LIST = new String[]{
            "com.gensym.*;",
            "java.io.File;",
            "java.io.IOException;",
            "java.io.PrintWriter;"
    };
    protected static final String[] EXPECTED_IMPORTS = new String[]{
            "PACKAGE-GENSYM",
            "FILE",
            "IOEXCEPTION",
            "PRINT-WRITER"
    };

    protected static final String[] INTERFACES_LIST = new String[] {
            "IFancyOne",
            "IFancyTwo",
            "IFancyThird"
    };

    protected File file;
    protected OverrideAnalyzer sut;

    @Rule
    public TemporaryFolder folder = new TemporaryFolder();

    protected void createFile() throws IOException {
        this.file = this.folder.newFile(anyString() + "");
        writeContent();
    }

    protected void createSut() throws IOException {
        this.sut = new OverrideAnalyzer(this.file.getAbsolutePath());
    }

    protected void removeFile() {
        this.file.delete();
    }

    protected String getContent() {
        StringBuilder importsString = new StringBuilder();
        for (String packageImport : PACKAGE_IMPORTS_LIST) {
            importsString.append("import ").append(packageImport).append("\n");
        }

        StringBuilder interfacesString = new StringBuilder();
        for (String interfaceStr : INTERFACES_LIST) {
            interfacesString.append(interfaceStr).append(" ");
        }

        return "package com.gensym.jgi.download;\n" +
                "\n" +
                importsString +
                "\n" +
                "public class FancyImplementation implements " + interfacesString + "{\n" +
                "\tprivate File _file;\n" +
                "\t\n" +
                "\tprotected OverrideAnalyzer sut;\n" +
                "\n" +
                "\n/// Constructor" +
                "\tpublic FancyImplementation() {\n" +
                "\t\t// Inline comment" +
                "\t\tcreateFile();" +
                "\t}\n" +
                "\n" +
                "\tpublic void init() throws IOException {\n" +
                "\t\t/* Multi-" +
                "\t\t   line" +
                "\t\t   comment */" +
                "\t\tcreateFile();\n" +
                "\t\tcreateSut();\n" +
                "\t}\n" +
                "\n" +
                "\tpublic void teardown() {\n" +
                "\t\t/** Multi-" +
                "\t\t   line" +
                "\t\t   comment **/" +
                "\t\tremoveFile();\n" +
                "\t}\n" +
                "\n" +
                "\tprotected void createFile() throws IOException {\n" +
                "\t\tthis._file = this.folder.newFile();\n" +
                "\t\twriteContent();\n" +
                "\t}\n" +
                "\n" +
                "\tprotected void createSut() throws IOException {\n" +
                "\t\tthis.sut = new OverrideAnalyzer(this._file.getAbsolutePath());\n" +
                "\t}\n" +
                "\n" +
                "\tprotected void removeFile() {\n" +
                "\t\tthis._file.delete();\n" +
                "\t}" +
                "\n" +
                "\tprotected void removeFile(String filename) {\n" +
                "\t\tnew File(filename).delete();\n" +
                "\t}" +
                "\n" +
                "\tprotected void removeFile(String filename, boolean delete) {\n" +
                "\t\tif (delete) {\n" +
                "\t\t\tnew File(filename).delete();\n" +
                "\t\t}\n" +
                "\t}\n" +
                "\t}\n" +
                "\n" +
                "\tprotected String addAnyListener(String anyString) {\n" +
                "\t\t// Add listener stuff here\n" +
                "\t}\n" +
                "\n" +
                "\tprotected String removeAnyListener(String anyString) {\n" +
                "\t\t// Remove listener stuff here\n" +
                "\t}\n" +
                "\n" +
                "\tpublic File getFile() {\n" +
                "\t\treturn this._file;\n" +
                "\t}\n" +
                "\n" +
                "\tpublic void setFile(File f) {\n" +
                "\t\tthis._file = f;\n" +
                "\t}\n" +
                "\n";
    }

    protected String trim(String str, char trimCharacter) {
        if (str != null && str.length() > 0 && str.charAt(str.length() - 1) == trimCharacter) {
            str = str.substring(0, str.length() - 1);
        }

        return str;
    }

    private void writeContent() {
        try {
            PrintWriter writer = new PrintWriter(this.file.getAbsolutePath(), "UTF-8");
            writer.print(getContent());
            writer.close();
        } catch (IOException e) {
            // do something
        }
    }
}
