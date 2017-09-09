package com.gensym.jgi;

import com.gensym.jgi.download.G2AccessStub;
import com.gensym.util.DownLoad;
import com.gensym.util.Symbol;
import org.junit.Before;
import org.junit.Test;

import static com.gensym.helpers.ObjectsFactory.anyString;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;

public class G2JavaStubInterfaceGeneratorTest extends G2JavaStubInterfaceGeneratorTestHelper {
    @Before
    public void init() {
        initializeParameters();
        createSut();
        setOutput();
        setSystemProperties();
    }

    @Test
    public void test_getAdapterConstructor_success_returnsConstructor() throws NoSuchMethodException, G2AccessException, ClassNotFoundException {
        // Arrange
        Class adapterClass = G2JavaStubInterfaceGeneratorTestHelperClassA.class;
        DownLoad downloader = createDownLoad(adapterClass);
        G2AccessStub context = new G2AccessStub();
        setClassManager(context);
        Symbol className = Symbol.intern(anyString());

        // Act & Assert
        assertEquals(adapterClass.getConstructor(constructorParams),
                G2JavaStubInterfaceGenerator.getAdapterConstructor(downloader, this.interfacesToImplement, context, className));
    }

    // Assert
    @Test(expected = RuntimeException.class)
    public void test_getAdapterConstructor_failedToGetDefinition_runtimeException() throws NoSuchMethodException, G2AccessException, ClassNotFoundException {
        // Arrange
        this.getDefinitionThrowsException = true;
        Class adapterClass = G2JavaStubInterfaceGeneratorTestHelperClassA.class;
        DownLoad downloader = createDownLoad(adapterClass);
        G2AccessStub context = new G2AccessStub();
        setClassManager(context);
        Symbol className = Symbol.intern(anyString());

        // Act
        G2JavaStubInterfaceGenerator.getAdapterConstructor(downloader, this.interfacesToImplement, context, className);
    }

    @Test
    public void test_emitClass_always_emitsCorrectClass() {
        // Arrange
        // No arrangement

        // Act
        this.sut.emitClass();

        // Assert
        assertTrue(this.outputStringWriter.toString().contains(expectedEmittedClass()));
    }

    @Test
    public void test_emitHeader_always_emitsCorrectHeader() {
        // Arrange
        // Nothing to arrange

        // Act
        this.sut.emitHeader();

        // Assert
        assertTrue(this.outputStringWriter.toString().contains(expectedEmittedHeader()));
    }

    @Test
    public void test_emitInterfaceAdapter_always_emitsCorrectCode() {
        // Arrange


        // Act & Assert
        assertTrue(this.sut.emitInterfaceAdapter().contains(expectedEmittedClass()));
    }
    
    @Test
    public void test_iprintMultiLineString_always_writesMultilineString() {
        // Arrange
        String multilineString = anyMultiLineString();
        
        // Act
        this.sut.iprintMultiLineString(multilineString);
        
        // Assert
        assertEquals(multilineString.trim(), this.outputStringWriter.toString().trim());
    }
}
