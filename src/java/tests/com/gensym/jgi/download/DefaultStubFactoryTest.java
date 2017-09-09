package com.gensym.jgi.download;

import com.gensym.classes.*;
import com.gensym.jgi.G2AccessException;
import com.gensym.util.Structure;
import org.junit.Test;

import static com.gensym.helpers.ObjectsFactory.anyInteger;
import static com.gensym.helpers.ObjectsFactory.anyStructure;
import static org.junit.Assert.*;

public class DefaultStubFactoryTest extends DefaultStubFactoryTestHelper {
    @Test
    public void test_createG2Stub_oldStyleClass_returnsNewItem() {
        // Arrange
        int handle = anyInteger();
        G2AccessStub context = new G2AccessStub();
        Structure attributes = anyStructure();
        this.loadedStubIsOldStyleClass = true;

        // Act
        Item result = this.sut.createG2Stub(this.className, handle, context, attributes);

        // Assert
        assertTrue(result instanceof ItemG2ProxyStubOldStyle);
        assertEquals(this.className, ((ItemG2ProxyStubOldStyle) result).getInternalG2ClassName());
    }

    @Test
    public void test_createG2Stub_notLoadedPreviously_returnsNewItem() {
        // Arrange
        int handle = anyInteger();
        G2AccessStub context = new G2AccessStub();
        Structure attributes = anyStructure();

        // Act
        Item result = this.sut.createG2Stub(this.className, handle, context, attributes);

        // Assert
        assertTrue(result instanceof ItemG2ProxyStub);
        assertEquals(this.className, ((ItemG2ProxyStub) result).getInternalG2ClassName());
    }

    @Test
    public void test_createG2Stub_loadedPreviously_returnsSameItem() {
        // Arrange
        int handle = anyInteger();
        G2AccessStub context = new G2AccessStub();
        Structure attributes = anyStructure();

        Item previouslyLoaded = this.sut.createG2Stub(this.className, handle, context, attributes);

        // Act
        Item result = this.sut.createG2Stub(this.className, handle, context, attributes);

        // Assert
        assertEquals(previouslyLoaded, result);
    }

    // Assert
    @Test(expected = RuntimeException.class)
    public void test_createG2Stub_constructorNotDefined_throwsException() {
        // Arrange
        int handle = anyInteger();
        G2AccessStub context = new G2AccessStub();
        Structure attributes = anyStructure();
        this.loadedStubDoesNotContainConstructor = true;

        // Act
        this.sut.createG2Stub(this.className, handle, context, attributes);
    }

    @Test
    public void test_createG2Stub_zeroHandle_createsNewStub() {
        // Arrange
        G2AccessStub context = new G2AccessStub();
        Structure attributes = anyStructure();

        // Act & Assert
        assertNotNull(this.sut.createG2Stub(this.className, 0, context, attributes));
    }

    @Test
    public void test_createG2StubWithHandleVersion_stubExists_returnsSameStub() {
        // Arrange
        int handle = anyInteger();
        G2AccessStub context = new G2AccessStub();
        Structure attributes = anyStructure();
        Item stub = this.sut.createG2Stub(this.className, handle, context, attributes);
        int handleVersion = ((G2__BaseImpl) stub).getHandleVersion();

        // Act
        Item result = this.sut.createG2Stub(this.className, handle, handleVersion, context, attributes);

        // Assert
        assertEquals(stub, result);
    }

    @Test
    public void test_createG2StubWithHandleVersion_stubNotExist_returnsNewStub() {
        // Arrange
        int handle = anyInteger();
        G2AccessStub context = new G2AccessStub();
        Structure attributes = anyStructure();

        // Act
        Item result = this.sut.createG2Stub(this.className, handle, anyInteger(), context, attributes);

        // Assert
        assertTrue(result instanceof ItemG2ProxyStub);
        assertEquals(this.className, ((ItemG2ProxyStub) result).getInternalG2ClassName());
    }

    @Test
    public void test_checkExistingStub_handleIsZero_returnsNull() {
        // Arrange
        // Nothing to arrange

        // Act & Assert
        assertEquals(null, this.sut.checkExistingStub(0, anyInteger()));
    }

    @Test
    public void test_checkExistingStub_stubExists_returnsStub() {
        // Arrange
        int handle = anyInteger();
        G2AccessStub context = new G2AccessStub();
        Structure attributes = anyStructure();
        Item existingStub = this.sut.createG2Stub(this.className, handle, context, attributes);
        int handleVersion = ((G2__BaseImpl) existingStub).getHandleVersion();

        // Act & Assert
        assertEquals(existingStub, this.sut.checkExistingStub(handle, handleVersion));
    }

    @Test
    public void test_checkExistingStub_stubInvalidated_returnsFromPreviousVersions() {
        // Arrange
        int handle = anyInteger();
        G2AccessStub context = new G2AccessStub();
        Structure attributes = anyStructure();
        Item existingStub = this.sut.createG2Stub(this.className, handle, context, attributes);
        int handleVersion = ((G2__BaseImpl) existingStub).getHandleVersion();
        this.sut.invalidateG2Stub(handle, context);

        // Act & Assert
        assertEquals(existingStub, this.sut.checkExistingStub(handle, handleVersion));
    }

    @Test
    public void test_getG2StubForHandle_stubNotExist_returnsNull() {
        // Arrange
        int handle = anyInteger();
        G2AccessStub context = new G2AccessStub();
        Structure attributes = anyStructure();
        this.sut.createG2Stub(this.className, handle, context, attributes);

        // Act & Assert
        assertNull(this.sut.getG2StubForHandle(handle + 1, context));
    }

    @Test
    public void test_getG2StubForHandle_stubExists_returnsStub() {
        // Arrange
        int handle = anyInteger();
        G2AccessStub context = new G2AccessStub();
        Structure attributes = anyStructure();
        Item existingStub = this.sut.createG2Stub(this.className, handle, context, attributes);

        // Act & Assert
        assertEquals(existingStub, this.sut.getG2StubForHandle(handle, context));
    }

    @Test
    public void test_invalidateStubClassLoader_sameContext_invalidatesLoader() throws G2AccessException {
        // Arrange
        // Nothing to arrange

        // Act
        this.sut.invalidateStubClassLoader(this.nativeCxn);

        // Assert
        assertNull(this.sut.getStubClassLoader());
    }

    @Test
    public void test_invalidateStubClassLoader_diffContext_doesNotInvalidateLoader() throws G2AccessException {
        // Arrange
        // Nothing to arrange

        // Act
        this.sut.invalidateStubClassLoader(new G2AccessStub());

        // Assert
        assertNotNull(this.sut.getStubClassLoader());
    }

    @Test
    public void test_getOrLoadDefinition_loadsSuccessfully_returnsDefinition() throws G2AccessException {
        // Arrange
        // Nothing to arrange

        // Act
        G2Definition result = this.sut.getOrLoadDefinition(this.className);

        // Assert
        assertTrue(this.loadedInterface);
        assertEquals(this.nativeCxn.getClassManager().getDefinition0(this.className), result);
    }

    // Assert
    @Test(expected = NullPointerException.class)
    public void test_getOrLoadDefinition_loaderInvalidated_exception() throws G2AccessException {
        // Arrange
        this.sut.invalidateStubClassLoader(this.nativeCxn);

        // Act
        this.sut.getOrLoadDefinition(this.className);
    }

    // Assert
    @Test(expected = G2AccessException.class)
    public void test_getOrLoadDefinition_noSuchClassException_throwsException() throws G2AccessException {
        // Arrange
        this.loadClassThrowsNoSuchClassException = true;

        // Act
        this.sut.getOrLoadDefinition(this.className);
    }

    // Assert
    @Test(expected = StubCreationException.class)
    public void test_getOrLoadDefinition_otherException_throwsException() throws G2AccessException {
        // Arrange
        this.loadClassThrowsException = true;

        // Act
        this.sut.getOrLoadDefinition(this.className);
    }
}
