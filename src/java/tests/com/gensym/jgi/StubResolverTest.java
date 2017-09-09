package com.gensym.jgi;

import com.gensym.classes.DeferredStub;
import com.gensym.classes.Item;
import com.gensym.jgi.download.*;
import com.gensym.util.Sequence;
import com.gensym.util.Structure;
import org.junit.*;

import static com.gensym.helpers.ObjectsFactory.*;
import static org.junit.Assert.*;
import static org.mockito.Matchers.any;
import static org.mockito.Mockito.mock;
import static org.mockito.Mockito.when;

public class StubResolverTest {

    @Test
    public void test_resolveDeferredStubs_callUsingObjectArray_verifyEqualToOriginal() {
        //Arragne
        Object[] objectArray = anyObjectsArray();
        StubResolver stubResolver = createNewStubResolver();
        //Act
        Object obj = stubResolver.resolveDeferredStubs(objectArray);
        //Assert
        assertEquals(obj,objectArray);
    }

    @Test
    public void test_resolveDeferredStubs_callUsingStructure_verifyEqualToOriginal() {
        //Arragne
        Structure attributes = anyStructure();
        StubResolver stubResolver = createNewStubResolver();
        //Act
        Object obj = stubResolver.resolveDeferredStubs(attributes);
        //Assert
        assertEquals(obj,attributes);
    }

    @Test
    public void test_resolveDeferredStubs_callUsingSequence_verifyEqualToOriginal() {
        //Arragne
        Sequence sequence = anyObjectsSequence();
        StubResolver stubResolver = createNewStubResolver();
        //Act
        Object obj = stubResolver.resolveDeferredStubs(sequence);
        //Assert
        assertEquals(obj,sequence);
    }

    @Test
    public void test_resolveDeferredStubs_callUsingDeferredStub_verifyEqualToExpected() {
        //Arragne
        Item itemMock = mock(Item.class);
        DeferredStub deferredStub = createDeferredStub(itemMock);
        StubResolver stubResolver = createNewStubResolver();
        //Act
        Object obj = stubResolver.resolveDeferredStubs(deferredStub);
        //Assert
        assertEquals(obj,itemMock);
    }

    @Test
    public void test_resolveDeferredStubs_callWithNull_verifyNull() {
        //Arragne
        StubResolver stubResolver = createNewStubResolver();
        //Act
        Object obj = stubResolver.resolveDeferredStubs(null);
        //Assert
        assertNull(obj);
    }

    @Test
    public void test_resolveDeferredStubs_callWithOtherInput_verifyEqualToOriginal() {
        //Arragne
        Integer integer = anyInteger();
        StubResolver stubResolver = createNewStubResolver();
        //Act
        Object obj = stubResolver.resolveDeferredStubs(integer);
        //Assert
        assertEquals(integer,obj);
    }

    @Test
    public void test_resolveDeferredStubs_callWithEmptySequence_verifyEmptySequence() {
        //Arragne
        Sequence sequence = new Sequence(0);
        StubResolver stubResolver = createNewStubResolver();
        //Act
        Sequence obj = (Sequence) stubResolver.resolveDeferredStubs(sequence);
        //Assert
        assertEquals(obj.size(),0);
    }

    private DeferredStub createDeferredStub(Item item) {
        DeferredStub deferredStub = mock(DeferredStub.class);
        when(deferredStub.getAttributes()).thenReturn(anyStructure());
        when(deferredStub.resolve(any(G2StubFactory.class))).thenReturn(item);
        return deferredStub;
    }

    private StubResolver createNewStubResolver(){
        G2AccessStub context = new G2AccessStub();
        DefaultStubFactory fac = new DefaultStubFactory(context);
        StubResolver stubResolver = new StubResolver(fac);
        return stubResolver;
    }
}