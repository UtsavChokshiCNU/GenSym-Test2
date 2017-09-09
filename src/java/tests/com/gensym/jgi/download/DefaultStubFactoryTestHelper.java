package com.gensym.jgi.download;

import com.gensym.classes.*;
import com.gensym.message.Trace;
import com.gensym.util.ClassManager;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import org.junit.After;
import org.junit.Before;
import org.mockito.invocation.InvocationOnMock;
import org.mockito.stubbing.Answer;

import java.lang.Object;

import static com.gensym.helpers.ObjectsFactory.anyString;
import static org.powermock.api.mockito.PowerMockito.mock;
import static org.powermock.api.mockito.PowerMockito.when;

public class DefaultStubFactoryTestHelper {
    private static final String NO_SUCH_CLASS_ERROR_TEXT = "NO-SUCH-CLASS-ERROR";
    private static final Symbol G2_GET_SHORT_CLASS_INFO_ = Symbol.intern("G2-GET-SHORT-CLASS-INFO");

    private boolean traceOn;

    protected DefaultStubFactory sut;
    protected G2AccessStub nativeCxn;
    protected StubClassLoader loader;
    protected Symbol className;
    protected Symbol stubClassName;
    protected boolean loadedInterface;
    protected boolean loadedStub;
    protected boolean loadClassThrowsNoSuchClassException;
    protected boolean loadClassThrowsException;
    protected boolean loadedStubDoesNotContainConstructor;
    protected boolean loadedStubIsOldStyleClass;

    @Before
    public void init() {
        setSystemProperties();
        initializeAllVariables();

        createSut();
        traceOn = Trace.getTraceOn();
        Trace.setTraceOn(true);
    }

    @After
    public void teardown() {
        Trace.setTraceOn(traceOn);
    }

    protected void createSut() {
        this.sut = new DefaultStubFactory(this.nativeCxn);

        createLoader();
        this.sut.setLoader(this.loader);
    }

    private void createNativeConnection() {
        this.nativeCxn = new G2AccessStub();
        this.nativeCxn.canCallRPC(true);
        this.nativeCxn.setClassManager(createClassManager());

        Sequence shortClassInfo = new Sequence();
        shortClassInfo.add(new Sequence());
        shortClassInfo.add(new ClassDefinitionStub());
        shortClassInfo.add(Symbol.intern("com.gensym.jgi.download"));
        this.nativeCxn.setRpcCall(G2_GET_SHORT_CLASS_INFO_, shortClassInfo);
    }

    private ClassManager createClassManager() {
        ClassManager classManager = mock(ClassManager.class);
        G2Definition definition = mock(G2Definition.class);
        when(classManager.getDefinition0(this.className)).thenReturn(definition);

        return classManager;
    }

    private void createLoader() {
        this.loader = mock(StubClassLoader.class);

        when(this.loader.loadClass(this.className, true)).thenAnswer(loadInterfaceResponse());
        when(this.loader.loadClass(this.stubClassName, true)).thenAnswer(loadInterfaceResponse());
        when(this.loader.loadClass(this.className, false)).thenAnswer(loadStubResponse());
        when(this.loader.loadClass(this.stubClassName, false)).thenAnswer(loadStubResponse());
    }

    private void initializeAllVariables() {
        this.className = Symbol.intern(ItemG2Proxy.class.getName());
        this.stubClassName = Symbol.intern(ItemG2ProxyStub.class.getName());

        createNativeConnection();

        this.loadedInterface = false;
        this.loadedStub = false;
        this.loadClassThrowsNoSuchClassException = false;
        this.loadClassThrowsException = false;
        this.loadedStubDoesNotContainConstructor = false;
        this.loadedStubIsOldStyleClass = false;
    }

    private Answer<Object> loadInterfaceResponse() {
        return new Answer<Object>() {
            @Override
            public Object answer(InvocationOnMock invocation) throws Throwable {
                if (loadClassThrowsNoSuchClassException) {
                    throw new StubCreationException(NO_SUCH_CLASS_ERROR_TEXT);
                } else if (loadClassThrowsException) {
                    throw new StubCreationException(anyString());
                }

                loadedInterface = true;
                return ItemG2Proxy.class;
            }
        };
    }

    private Answer<Object> loadStubResponse() {
        return new Answer<Object>() {
            @Override
            public Object answer(InvocationOnMock invocation) throws Throwable {
                loadedStub = true;

                if (loadedStubDoesNotContainConstructor) {
                    return ItemG2ProxyStubWithoutConstructor.class;
                }

                if (loadedStubIsOldStyleClass) {
                    return ItemG2ProxyStubOldStyle.class;
                }

                return ItemG2ProxyStub.class;
            }
        };
    }

    private void setSystemProperties() {
        System.setProperty("com.gensym.class.user.package", "com.gensym.jgi.download");
    }
}
