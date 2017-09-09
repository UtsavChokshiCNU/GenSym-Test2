package com.gensym.jgi.download;

import com.gensym.util.NoSuchAttributeException;
import com.gensym.util.Sequence;
import com.gensym.util.Structure;
import com.gensym.util.Symbol;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import java.io.IOException;

import static com.gensym.helpers.ObjectsFactory.anyString;
import static com.gensym.util.symbol.OverrideSymbols.CLASS_INFO_;
import static com.gensym.util.symbol.OverrideSymbols.INTERFACES_;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;

public class OverrideAnalyzerTest extends OverrideAnalyzerTestHelper {
    @Before
    public void init() throws IOException {
        createFile();
        createSut();
    }

    @After
    public void teardown() {
        removeFile();
    }

    // Assert
    @Test(expected = StringIndexOutOfBoundsException.class)
    public void test_parse_withoutCode_throwsException() throws NoSuchAttributeException {
        // Arrange
        this.sut = new OverrideAnalyzer();

        // Act
        this.sut.parse();
    }

    // Assert
    @Test(expected = IOException.class)
    public void test_instance_fileDoesNotExist_throwsException() throws IOException {
        // Arrange
        // Nothing to arrange

        // Act
        this.sut = new OverrideAnalyzer(anyString());
    }

    @Test
    public void test_parse_always_parsesImports() throws NoSuchAttributeException {
        // Arrange
        // Nothing to arrange

        // Act
        Structure result = this.sut.parse();

        // Assert
        assertThatImportsAreParsed(result);
    }

    @Test
    public void test_parse_always_parsesInterfaces() throws NoSuchAttributeException {
        // Arrange
        // Nothing to arrange

        // Act
        Structure result = this.sut.parse();

        // Assert
        assertThatInterfacesAreParsed(result);
    }

    @Test
    public void test_parse_commentedCode_parsesImports() throws NoSuchAttributeException {
        // Arrange
        // Nothing to arrange

        // Act
        Structure result = this.sut.parse(getContent());

        // Assert
        assertThatImportsAreParsed(result);
    }

    @Test
    public void test_parse_commentedCode_parsesInterfaces() throws NoSuchAttributeException {
        // Arrange
        // Nothing to arrange

        // Act
        Structure result = this.sut.parse(getContent());

        // Assert
        assertThatInterfacesAreParsed(result);
    }

    private void assertThatImportsAreParsed(Structure result) throws NoSuchAttributeException {
        Sequence imports = (Sequence)result.getAttributeValue(IMPORTS_);
        for (int idx = 0; idx < PACKAGE_IMPORTS_LIST.length; idx++) {
            assertEquals(Symbol.intern(EXPECTED_IMPORTS[idx]), ((Structure)imports.elementAt(idx)).getAttributeValue(Symbol.intern("IMPORT-NAME")));
            String packageName = trim(PACKAGE_IMPORTS_LIST[idx].toString(), ';');
            assertEquals(packageName, ((Structure)imports.elementAt(idx)).getAttributeValue(Symbol.intern("TYPE-OR-PACKAGE")));
        }
    }

    private void assertThatInterfacesAreParsed(Structure result) throws NoSuchAttributeException {
        Structure classInfo = (Structure) result.getAttributeValue(CLASS_INFO_);
        Sequence interfaces = (Sequence)classInfo.getAttributeValue(INTERFACES_);
        for(String interfaceStr : INTERFACES_LIST) {
            assertTrue(interfaces.contains(interfaceStr));
        }
    }
}
