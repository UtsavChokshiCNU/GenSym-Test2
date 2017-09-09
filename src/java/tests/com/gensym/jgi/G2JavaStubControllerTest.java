package com.gensym.jgi;

import static org.junit.Assert.*;
import static org.mockito.Matchers.any;
import static org.mockito.Matchers.matches;
import static org.mockito.Mockito.verify;
import static org.mockito.Mockito.inOrder;
import static org.powermock.api.mockito.PowerMockito.*;

import com.gensym.beansruntime.Enum;
import com.gensym.classes.*;
import com.gensym.classes.modules.g2evliss.G2EventObjectImpl;
import com.gensym.jgi.download.G2StubCreationException;
import com.gensym.jgi.rmi.G2RMIAccess;
import com.gensym.jgi.rmi.G2RMIClientImpl;
import com.gensym.jgi.rmi.RMIEventQueueProcessor;
import com.gensym.util.*;
import com.gensym.util.symbol.G2ClassSymbols;
import org.assertj.core.api.Assertions;
import org.junit.*;
import org.junit.Rule;
import org.junit.rules.ExpectedException;
import org.junit.runner.RunWith;
import org.mockito.*;
import org.mockito.invocation.InvocationOnMock;
import org.mockito.stubbing.Answer;
import org.powermock.core.classloader.annotations.PrepareForTest;
import org.powermock.modules.junit4.PowerMockRunner;
import org.powermock.reflect.Whitebox;

import java.lang.reflect.Array;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.lang.Object;
import java.rmi.RemoteException;
import java.util.Enumeration;
import java.util.Hashtable;

@RunWith(PowerMockRunner.class)
@PrepareForTest({
        G2JavaStubController.class, G2JavaStubController.ConnectionRegistry.class, G2ClassTranslator.class,
        G2_ExternalEventObjectRoot.class, G2JavaStubControllerEvent.class, Array.class, Symbol.class
})
public class G2JavaStubControllerTest {

    private static G2JavaStubController g2JavaStubController = null;

    private static final Symbol CLASS_ = Symbol.intern("CLASS");
    private static final Symbol VAL_ = Symbol.intern("VAL");

    private static Symbol JAVA_LANG_INTEGER_TYPE_ = Symbol.intern("JAVA.LANG.INTEGER.TYPE");
    private static Symbol JAVA_LANG_FLOAT_TYPE_ = Symbol.intern("JAVA.LANG.FLOAT.TYPE");
    private static Symbol JAVA_LANG_BYTE_TYPE_ = Symbol.intern("JAVA.LANG.BYTE.TYPE");
    private static Symbol JAVA_LANG_CHARACTER_TYPE_ = Symbol.intern("JAVA.LANG.CHARACTER.TYPE");
    private static Symbol JAVA_LANG_SHORT_TYPE_ = Symbol.intern("JAVA.LANG.SHORT.TYPE");
    private static Symbol JAVA_LANG_LONG_TYPE_ = Symbol.intern("JAVA.LANG.LONG.TYPE");
    private static Symbol JAVA_LANG_STRING_ = Symbol.intern("JAVA.LANG.STRING");


    @Rule
    public ExpectedException expectedException = ExpectedException.none();


    @Before
    public void setUp() {
        initializeG2JavaStubController();
    }

    @After
    public void tearDown() {
        g2JavaStubController = null;
    }

    @Test
    public void test_resolveJavaObjects_array_object() throws Exception {
        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        G2JavaStubController.ConnectionRegistry registryInfo = mock(G2JavaStubController.ConnectionRegistry.class);

        // arrange
        Object[] o = {};
        Object[] resolvedO = {};

        // given
        when(g2JavaStubController, "resolveJavaObjectsInObjectArray", registryInfo, o).thenReturn(resolvedO);

        // when
        when(g2JavaStubController, "resolveJavaObjects", registryInfo, o).thenCallRealMethod();
        Object result = Whitebox.invokeMethod(g2JavaStubController, "resolveJavaObjects", registryInfo, o);

        // assert
        Assertions.assertThat(result).isSameAs(resolvedO);
        verifyPrivate(g2JavaStubController).invoke("resolveJavaObjectsInObjectArray", registryInfo, o);
    }

    @Test
    public void test_resolveJavaObjects_structure_object() throws Exception {
        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        G2JavaStubController.ConnectionRegistry registryInfo = mock(G2JavaStubController.ConnectionRegistry.class);
        Structure o = mock(Structure.class);
        Structure resolvedO = mock(Structure.class);

        // given
        when(g2JavaStubController, "resolveJavaObjectsInStructure", registryInfo, o).thenReturn(resolvedO);

        // when
        when(g2JavaStubController, "resolveJavaObjects", registryInfo, o).thenCallRealMethod();
        Object result = Whitebox.invokeMethod(g2JavaStubController, "resolveJavaObjects", registryInfo, o);

        // assert
        Assertions.assertThat(result).isSameAs(resolvedO);
        verifyPrivate(g2JavaStubController).invoke("resolveJavaObjectsInStructure", registryInfo, o);
    }

    @Test
    public void test_resolveJavaObjects_sequence_object() throws Exception {
        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        G2JavaStubController.ConnectionRegistry registryInfo = mock(G2JavaStubController.ConnectionRegistry.class);
        Sequence o = mock(Sequence.class);
        Sequence resolvedO = mock(Sequence.class);

        // given
        when(g2JavaStubController, "resolveJavaObjectsInSequence", registryInfo, o).thenReturn(resolvedO);

        // when
        when(g2JavaStubController, "resolveJavaObjects", registryInfo, o).thenCallRealMethod();
        Object result = Whitebox.invokeMethod(g2JavaStubController, "resolveJavaObjects", registryInfo, o);

        // assert
        Assertions.assertThat(result).isSameAs(resolvedO);
        verifyPrivate(g2JavaStubController).invoke("resolveJavaObjectsInSequence", registryInfo, o);
    }

    @Test
    public void test_resolveJavaObjects_object_is_null() throws Exception {
        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        G2JavaStubController.ConnectionRegistry registryInfo = mock(G2JavaStubController.ConnectionRegistry.class);

        // arrenge
        Object o = null;

        // when
        when(g2JavaStubController, "resolveJavaObjects", registryInfo, o).thenCallRealMethod();
        Object result = Whitebox.invokeMethod(g2JavaStubController, "resolveJavaObjects", registryInfo, o);

        // assert
        Assertions.assertThat(result).isNull();
    }

    @Test
    public void test_resolveJavaObject_() throws Exception {

        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        G2JavaStubController.ConnectionRegistry registryInfo = mock(G2JavaStubController.ConnectionRegistry.class);
        G2Access connection = mock(G2Access.class);
        Object java_object = mock(Object.class);
        Object resolvedJavaObject = mock(Object.class);

        // given
        when(g2JavaStubController, "getConnectionRegistry", connection).thenReturn(registryInfo);
        when(g2JavaStubController, "resolveJavaObject", registryInfo, java_object).thenReturn(resolvedJavaObject);

        // when
        when(g2JavaStubController, "resolveJavaObject", connection, java_object).thenCallRealMethod();
        Object result = Whitebox.invokeMethod(g2JavaStubController, "resolveJavaObject", connection, java_object);

        // assert
        Assertions.assertThat(result).isSameAs(resolvedJavaObject);

        // verify
        verifyPrivate(g2JavaStubController).invoke("getConnectionRegistry", connection);
        verifyPrivate(g2JavaStubController).invoke("resolveJavaObject", registryInfo, java_object);
    }


    @Test
    public void test_resolveG2StubsInObjectArray_() throws Exception {
        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        G2JavaStubController.ConnectionRegistry registryInfo = mock(G2JavaStubController.ConnectionRegistry.class);
        Object targetObj = mock(Object.class);
        Object resolvedTargetObj = mock(Object.class);

        // arrange
        Object[] oarray = {targetObj};
        int i = 0;
        Object[]  expectedOarray = {resolvedTargetObj};

        // given
        when(g2JavaStubController, "resolveG2Stubs", registryInfo, targetObj, oarray[i]).thenReturn(resolvedTargetObj);

        // when
        when(g2JavaStubController, "resolveG2StubsInObjectArray", registryInfo, targetObj, oarray).thenCallRealMethod();
        Object[] result = Whitebox.invokeMethod(g2JavaStubController, "resolveG2StubsInObjectArray", registryInfo, targetObj, oarray);

        // assert
        Assertions.assertThat(result).isEqualTo(expectedOarray);
        verifyPrivate(g2JavaStubController).invoke("resolveG2StubsInObjectArray", registryInfo, targetObj, oarray);
    }

    @Test
    public void test_resolveG2StubsInSequence_sequance_has_elements() throws Exception {
        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        G2JavaStubController.ConnectionRegistry registryInfo = mock(G2JavaStubController.ConnectionRegistry.class);
        Object targetObj = mock(Object.class);
        Sequence s = mock(Sequence.class);
        Object o = mock(Object.class);
        Object resolvedObject = mock(Object.class);

        // arrange
        boolean isEmpty = false;
        int numElts = 1;
        int i = 0;

        // given
        when(s.isEmpty()).thenReturn(isEmpty);
        when(s.size()).thenReturn(numElts);
        when(s.elementAt(i)).thenReturn(o);
        when(g2JavaStubController, "resolveG2Stubs", registryInfo, targetObj, o).thenReturn(resolvedObject);

        // when
        when(g2JavaStubController, "resolveG2StubsInSequence", registryInfo, targetObj, s).thenCallRealMethod();
        Sequence result = Whitebox.invokeMethod(g2JavaStubController, "resolveG2StubsInSequence", registryInfo, targetObj, s);


        // assert
        Assertions.assertThat(result).isSameAs(s);

        // verify
        verify(s).isEmpty();
        verify(s).setElementAt(resolvedObject, i);

    }

    @Test
    public void test_resolveG2StubsInSequence_sequance_is_empty() throws Exception {
        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        G2JavaStubController.ConnectionRegistry registryInfo = mock(G2JavaStubController.ConnectionRegistry.class);
        Object targetObj = mock(Object.class);
        Sequence s = mock(Sequence.class);

        // arrange
        boolean isEmpty = true;

        // given
        when(s.isEmpty()).thenReturn(isEmpty);

        // when
        when(g2JavaStubController, "resolveG2StubsInSequence", registryInfo, targetObj, s).thenCallRealMethod();
        Sequence result = Whitebox.invokeMethod(g2JavaStubController, "resolveG2StubsInSequence", registryInfo, targetObj, s);

        // assert
        Assertions.assertThat(result).isSameAs(s);

        // verify
        verify(s).isEmpty();

    }

    @Test
    public void test_getG2JavaStubController_create_new_instance_if_there_is_no_instances() throws Exception {
        // static mocks
        mockStatic(G2JavaStubController.class);

        // mocks
        G2JavaStubController newController = mock(G2JavaStubController.class);

        // arrange
        G2JavaStubController controller = null;
        Whitebox.setInternalState(G2JavaStubController.class, "controller", controller);

        // when
        whenNew(G2JavaStubController.class).withNoArguments().thenReturn(newController);
        when(G2JavaStubController.getG2JavaStubController()).thenCallRealMethod();
        G2JavaStubController result = G2JavaStubController.getG2JavaStubController();

        // assert
        Assertions.assertThat(result).isSameAs(newController);

        // verify
        verifyNew(G2JavaStubController.class).withNoArguments();

    }

    @Test
    public void test_getG2JavaStubController_get_existing_instance() {
        // static mocks
        mockStatic(G2JavaStubController.class);

        // mocks
        G2JavaStubController controller = mock(G2JavaStubController.class);

        // arrange
        Whitebox.setInternalState(G2JavaStubController.class, "controller", controller);

        // when
        when(G2JavaStubController.getG2JavaStubController()).thenCallRealMethod();
        G2JavaStubController result = G2JavaStubController.getG2JavaStubController();

        // assert
        Assertions.assertThat(result).isSameAs(controller);

    }

    @Test
    public void test_call_method_method_founded() throws Exception {
        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        Item g2proxy = mock(Item.class);
        Item g2method = mock(Item.class);
        Sequence args = mock(Sequence.class);

        G2JavaStubController.ConnectionRegistry registryInfo = mock(G2JavaStubController.ConnectionRegistry.class);
        Object javaobj = mock(Object.class);
        Method method = mock(Method.class);
        Sequence resolvedSequence = mock(Sequence.class);

        Object methodReturn = mock(Object.class);

        // arrange
        String methodName = "";

        // given
        when(g2JavaStubController, "getConnectionRegistry", g2proxy).thenReturn(registryInfo);
        when(registryInfo.getAssociatedJavaObject(g2proxy)).thenReturn(javaobj);
        when(registryInfo.lookupMethod(javaobj.getClass(), g2method)).thenReturn(method);
        when(g2JavaStubController, "resolveG2StubsInSequence", registryInfo, javaobj, args).thenReturn(resolvedSequence);
        when(g2JavaStubController, "callMethod", g2proxy, javaobj, registryInfo, null, method, resolvedSequence, null).thenReturn(methodReturn);

        // when
        when(g2JavaStubController, "callMethod", g2proxy, methodName, g2method, args).thenCallRealMethod();
        Object result = Whitebox.invokeMethod(g2JavaStubController, "callMethod", g2proxy, methodName, g2method, args);

        // assert
        Assertions.assertThat(result).isSameAs(methodReturn);

        // verify
        verifyPrivate(g2JavaStubController).invoke("getConnectionRegistry", g2proxy);
        verify(registryInfo).getAssociatedJavaObject(g2proxy);
        verify(registryInfo).lookupMethod(javaobj.getClass(), g2method);
        verifyPrivate(g2JavaStubController).invoke("resolveG2StubsInSequence", registryInfo, javaobj, args);
        verifyPrivate(g2JavaStubController).invoke("callMethod", g2proxy, javaobj, registryInfo, null, method, resolvedSequence, null);


    }

    @Test
    public void test_removeConnectionRegistry_()  throws Exception {

        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        Hashtable connectionsTable = mock(Hashtable.class);
        G2Access g2Connection = mock(G2Access.class);

        // arrange
        Whitebox.setInternalState(g2JavaStubController, "connectionsTable", connectionsTable);

        // when
        doCallRealMethod().when(g2JavaStubController, "removeConnectionRegistry", g2Connection);
        Whitebox.invokeMethod(g2JavaStubController, "removeConnectionRegistry", g2Connection);

        // verify
        verifyPrivate(connectionsTable).invoke("remove", g2Connection);

    }

    @Test
    public void test_getJavaTypeObjectForG2Type_char() throws Exception {
        // static mocks
        mockStatic(G2ClassTranslator.class);
        mockStatic(G2JavaStubController.class);

        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        Item g2proxy = mock(Item.class);
        final Symbol CLASS_ = mock(Symbol.class);
        final Symbol VAL_ = mock(Symbol.class);
        final Symbol g2ClassName = mock(Symbol.class);

        // arrange
        Class knownType = Character.TYPE;
        final Object val = "abc";
        Character expectedVal = 'a';
        Whitebox.setInternalState(G2JavaStubController.class, "CLASS_", CLASS_);
        Whitebox.setInternalState(G2JavaStubController.class, "VAL_", VAL_);

        // given
        when(g2proxy.getPropertyValue(any(Symbol.class))).thenAnswer(new Answer<Object>() {
            @Override
            public Object answer(InvocationOnMock invocation) throws Throwable {
                Symbol propertyName = invocation.getArgumentAt(0, Symbol.class);
                if (propertyName == (CLASS_)) return g2ClassName;
                if (propertyName == (VAL_)) return val;
                return null;
            }
        });
        when(G2ClassTranslator.getJavaTypeForG2Class(g2ClassName)).thenReturn(knownType);

        // when
        when(g2JavaStubController, "getJavaTypeObjectForG2Type", g2proxy).thenCallRealMethod();
        Object result = Whitebox.invokeMethod(g2JavaStubController, "getJavaTypeObjectForG2Type", g2proxy);

        // assert
        Assertions.assertThat(result).isEqualTo(expectedVal);

        // verify
        verify(g2proxy, Mockito.times(2)).getPropertyValue(any(Symbol.class));
        verifyStatic();
        G2ClassTranslator.getJavaTypeForG2Class(g2ClassName);

    }

    @Test
    public void test_getJavaTypeObjectForG2Type_char_for_empty_string() throws Exception {
        // static mocks
        mockStatic(G2ClassTranslator.class);
        mockStatic(G2JavaStubController.class);

        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        Item g2proxy = mock(Item.class);
        final Symbol CLASS_ = mock(Symbol.class);
        final Symbol VAL_ = mock(Symbol.class);
        final Symbol g2ClassName = mock(Symbol.class);

        // arrange
        Class knownType = Character.TYPE;
        final Object val = "";
        Character expectedVal = ' ';
        Whitebox.setInternalState(G2JavaStubController.class, "CLASS_", CLASS_);
        Whitebox.setInternalState(G2JavaStubController.class, "VAL_", VAL_);

        // given
        when(g2proxy.getPropertyValue(any(Symbol.class))).thenAnswer(new Answer<Object>() {
            @Override
            public Object answer(InvocationOnMock invocation) throws Throwable {
                Symbol propertyName = invocation.getArgumentAt(0, Symbol.class);
                if (propertyName == (CLASS_)) return g2ClassName;
                if (propertyName == (VAL_)) return val;
                return null;
            }
        });
        when(G2ClassTranslator.getJavaTypeForG2Class(g2ClassName)).thenReturn(knownType);

        // when
        when(g2JavaStubController, "getJavaTypeObjectForG2Type", g2proxy).thenCallRealMethod();
        Object result = Whitebox.invokeMethod(g2JavaStubController, "getJavaTypeObjectForG2Type", g2proxy);

        // assert
        Assertions.assertThat(result).isEqualTo(expectedVal);

        // verify
        verify(g2proxy, Mockito.times(2)).getPropertyValue(any(Symbol.class));
        verifyStatic();
        G2ClassTranslator.getJavaTypeForG2Class(g2ClassName);

    }

    @Test
    public void test_getJavaTypeObjectForG2Type_short_type() throws Exception {
        // static mocks
        mockStatic(G2ClassTranslator.class);
        mockStatic(G2JavaStubController.class);

        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        Item g2proxy = mock(Item.class);
        final Symbol CLASS_ = mock(Symbol.class);
        final Symbol VAL_ = mock(Symbol.class);
        final Symbol g2ClassName = mock(Symbol.class);

        // arrange
        Class knownType = Short.TYPE;
        final Object val = 1;
        Short expectedVal = 1;
        Whitebox.setInternalState(G2JavaStubController.class, "CLASS_", CLASS_);
        Whitebox.setInternalState(G2JavaStubController.class, "VAL_", VAL_);

        // given
        when(g2proxy.getPropertyValue(any(Symbol.class))).thenAnswer(new Answer<Object>() {
            @Override
            public Object answer(InvocationOnMock invocation) throws Throwable {
                Symbol propertyName = invocation.getArgumentAt(0, Symbol.class);
                if (propertyName == (CLASS_)) return g2ClassName;
                if (propertyName == (VAL_)) return val;
                return null;
            }
        });
        when(G2ClassTranslator.getJavaTypeForG2Class(g2ClassName)).thenReturn(knownType);

        // when
        when(g2JavaStubController, "getJavaTypeObjectForG2Type", g2proxy).thenCallRealMethod();
        Object result = Whitebox.invokeMethod(g2JavaStubController, "getJavaTypeObjectForG2Type", g2proxy);

        // assert
        Assertions.assertThat(result).isEqualTo(expectedVal);

        // verify
        verify(g2proxy, Mockito.times(2)).getPropertyValue(any(Symbol.class));
        verifyStatic();
        G2ClassTranslator.getJavaTypeForG2Class(g2ClassName);

    }

    @Test
    public void test_getJavaTypeObjectForG2Type_byte_type() throws Exception {
        // static mocks
        mockStatic(G2ClassTranslator.class);
        mockStatic(G2JavaStubController.class);

        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        Item g2proxy = mock(Item.class);
        final Symbol CLASS_ = mock(Symbol.class);
        final Symbol VAL_ = mock(Symbol.class);
        final Symbol g2ClassName = mock(Symbol.class);

        // arrange
        Class knownType = Byte.TYPE;
        final Object val = 1;
        Byte expectedVal = 1;
        Whitebox.setInternalState(G2JavaStubController.class, "CLASS_", CLASS_);
        Whitebox.setInternalState(G2JavaStubController.class, "VAL_", VAL_);

        // given
        when(g2proxy.getPropertyValue(any(Symbol.class))).thenAnswer(new Answer<Object>() {
            @Override
            public Object answer(InvocationOnMock invocation) throws Throwable {
                Symbol propertyName = invocation.getArgumentAt(0, Symbol.class);
                if (propertyName == (CLASS_)) return g2ClassName;
                if (propertyName == (VAL_)) return val;
                return null;
            }
        });
        when(G2ClassTranslator.getJavaTypeForG2Class(g2ClassName)).thenReturn(knownType);

        // when
        when(g2JavaStubController, "getJavaTypeObjectForG2Type", g2proxy).thenCallRealMethod();
        Object result = Whitebox.invokeMethod(g2JavaStubController, "getJavaTypeObjectForG2Type", g2proxy);

        // assert
        Assertions.assertThat(result).isEqualTo(expectedVal);

        // verify
        verify(g2proxy, Mockito.times(2)).getPropertyValue(any(Symbol.class));
        verifyStatic();
        G2ClassTranslator.getJavaTypeForG2Class(g2ClassName);

    }

    @Test
    public void test_getJavaTypeObjectForG2Type_float_type() throws Exception {
        // static mocks
        mockStatic(G2ClassTranslator.class);
        mockStatic(G2JavaStubController.class);

        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        Item g2proxy = mock(Item.class);
        final Symbol CLASS_ = mock(Symbol.class);
        final Symbol VAL_ = mock(Symbol.class);
        final Symbol g2ClassName = mock(Symbol.class);

        // arrange
        Class knownType = Float.TYPE;
        final Object val = 1d;
        Float expectedVal = 1f;
        Whitebox.setInternalState(G2JavaStubController.class, "CLASS_", CLASS_);
        Whitebox.setInternalState(G2JavaStubController.class, "VAL_", VAL_);

        // given
        when(g2proxy.getPropertyValue(any(Symbol.class))).thenAnswer(new Answer<Object>() {
            @Override
            public Object answer(InvocationOnMock invocation) throws Throwable {
                Symbol propertyName = invocation.getArgumentAt(0, Symbol.class);
                if (propertyName == (CLASS_)) return g2ClassName;
                if (propertyName == (VAL_)) return val;
                return null;
            }
        });
        when(G2ClassTranslator.getJavaTypeForG2Class(g2ClassName)).thenReturn(knownType);

        // when
        when(g2JavaStubController, "getJavaTypeObjectForG2Type", g2proxy).thenCallRealMethod();
        Object result = Whitebox.invokeMethod(g2JavaStubController, "getJavaTypeObjectForG2Type", g2proxy);

        // assert
        Assertions.assertThat(result).isEqualTo(expectedVal);

        // verify
        verify(g2proxy, Mockito.times(2)).getPropertyValue(any(Symbol.class));
        verifyStatic();
        G2ClassTranslator.getJavaTypeForG2Class(g2ClassName);

    }

    @Test
    public void test_getJavaTypeObjectForG2Type_integer_type() throws Exception {
        // static mocks
        mockStatic(G2ClassTranslator.class);
        mockStatic(G2JavaStubController.class);

        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        Item g2proxy = mock(Item.class);
        final Symbol CLASS_ = mock(Symbol.class);
        final Symbol VAL_ = mock(Symbol.class);
        final Symbol g2ClassName = mock(Symbol.class);

        // arrange
        Class knownType = Integer.TYPE;
        final Object val = "1";
        Integer expectedVal = 1;
        Whitebox.setInternalState(G2JavaStubController.class, "CLASS_", CLASS_);
        Whitebox.setInternalState(G2JavaStubController.class, "VAL_", VAL_);

        // given
        when(g2proxy.getPropertyValue(any(Symbol.class))).thenAnswer(new Answer<Object>() {
            @Override
            public Object answer(InvocationOnMock invocation) throws Throwable {
                Symbol propertyName = invocation.getArgumentAt(0, Symbol.class);
                if (propertyName == (CLASS_)) return g2ClassName;
                if (propertyName == (VAL_)) return val;
                return null;
            }
        });
        when(G2ClassTranslator.getJavaTypeForG2Class(g2ClassName)).thenReturn(knownType);

        // when
        when(g2JavaStubController, "getJavaTypeObjectForG2Type", g2proxy).thenCallRealMethod();
        Object result = Whitebox.invokeMethod(g2JavaStubController, "getJavaTypeObjectForG2Type", g2proxy);

        // assert
        Assertions.assertThat(result).isSameAs(expectedVal);

        // verify
        verify(g2proxy, Mockito.times(2)).getPropertyValue(any(Symbol.class));
        verifyStatic();
        G2ClassTranslator.getJavaTypeForG2Class(g2ClassName);

    }

    @Test
    public void test_getJavaTypeObjectForG2Type_long_type() throws Exception {
        // static mocks
        mockStatic(G2ClassTranslator.class);
        mockStatic(G2JavaStubController.class);

        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        Item g2proxy = mock(Item.class);
        final Symbol CLASS_ = mock(Symbol.class);
        final Symbol VAL_ = mock(Symbol.class);
        final Symbol g2ClassName = mock(Symbol.class);

        // arrange
        Class knownType = Long.TYPE;
        final Object val = "1";
        Long expectedVal = 1L;
        Whitebox.setInternalState(G2JavaStubController.class, "CLASS_", CLASS_);
        Whitebox.setInternalState(G2JavaStubController.class, "VAL_", VAL_);

        // given
        when(g2proxy.getPropertyValue(any(Symbol.class))).thenAnswer(new Answer<Object>() {
            @Override
            public Object answer(InvocationOnMock invocation) throws Throwable {
                Symbol propertyName = invocation.getArgumentAt(0, Symbol.class);
                if (propertyName == (CLASS_)) return g2ClassName;
                if (propertyName == (VAL_)) return val;
                return null;
            }
        });
        when(G2ClassTranslator.getJavaTypeForG2Class(g2ClassName)).thenReturn(knownType);

        // when
        when(g2JavaStubController, "getJavaTypeObjectForG2Type", g2proxy).thenCallRealMethod();
        Object result = Whitebox.invokeMethod(g2JavaStubController, "getJavaTypeObjectForG2Type", g2proxy);

        // assert
        Assertions.assertThat(result).isSameAs(expectedVal);

        // verify
        verify(g2proxy, Mockito.times(2)).getPropertyValue(any(Symbol.class));
        verifyStatic();
        G2ClassTranslator.getJavaTypeForG2Class(g2ClassName);

    }

    @Test
    public void test_getJavaTypeObjectForG2Type_know_type_doesnt_match_g2_types() throws Exception {
        // static mocks
        mockStatic(G2ClassTranslator.class);
        mockStatic(G2JavaStubController.class);

        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        Item g2proxy = mock(Item.class);
        Class knownType = Object.class;
        final Symbol CLASS_ = mock(Symbol.class);
        final Symbol VAL_ = mock(Symbol.class);
        final Symbol g2ClassName = mock(Symbol.class);
        final Object val = mock(Object.class);

        // arrange
        Whitebox.setInternalState(G2JavaStubController.class, "CLASS_", CLASS_);
        Whitebox.setInternalState(G2JavaStubController.class, "VAL_", VAL_);

        // given
        when(g2proxy.getPropertyValue(any(Symbol.class))).thenAnswer(new Answer<Object>() {
            @Override
            public Object answer(InvocationOnMock invocation) throws Throwable {
                Symbol propertyName = invocation.getArgumentAt(0, Symbol.class);
                if (propertyName == (CLASS_)) return g2ClassName;
                if (propertyName == (VAL_)) return val;
                return null;
            }
        });
        when(G2ClassTranslator.getJavaTypeForG2Class(g2ClassName)).thenReturn(knownType);

        // when
        when(g2JavaStubController, "getJavaTypeObjectForG2Type", g2proxy).thenCallRealMethod();
        Object result = Whitebox.invokeMethod(g2JavaStubController, "getJavaTypeObjectForG2Type", g2proxy);

        // assert
        Assertions.assertThat(result).isSameAs(val);

        // verify
        verify(g2proxy, Mockito.times(2)).getPropertyValue(any(Symbol.class));
        verifyStatic();
        G2ClassTranslator.getJavaTypeForG2Class(g2ClassName);

    }

    @Test
    public void test_getJavaTypeObjectForG2Type_cant_access_g2_class() throws Exception {
        // static mocks
        mockStatic(G2JavaStubController.class);

        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        Item g2proxy = mock(Item.class);
        Symbol CLASS_ = mock(Symbol.class);

        // arrange
        Whitebox.setInternalState(G2JavaStubController.class, "CLASS_", CLASS_);

        // given
        when(g2proxy.getPropertyValue(CLASS_)).thenThrow(G2AccessException.class);
        expectedException.expect(RuntimeException.class);

        // when
        when(g2JavaStubController, "getJavaTypeObjectForG2Type", g2proxy).thenCallRealMethod();
        Whitebox.invokeMethod(g2JavaStubController, "getJavaTypeObjectForG2Type", g2proxy);

        // verify
        verify(g2proxy).getPropertyValue(CLASS_);

    }


    @Test
    public void test_getJavaTypeObjectForG2Type_not_know_type() throws Exception {
        // static mocks
        mockStatic(G2ClassTranslator.class);
        mockStatic(G2JavaStubController.class);

        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        Item g2proxy = mock(Item.class);
        Symbol CLASS_ = mock(Symbol.class);
        Symbol g2ClassName = mock(Symbol.class);

        // arrange
        Whitebox.setInternalState(G2JavaStubController.class, "CLASS_", CLASS_);
        Class knownType = null;

        // given
        when(g2proxy.getPropertyValue(CLASS_)).thenReturn(g2ClassName);
        when(G2ClassTranslator.getJavaTypeForG2Class(g2ClassName)).thenReturn(knownType);

        // when
        when(g2JavaStubController, "getJavaTypeObjectForG2Type", g2proxy).thenCallRealMethod();
        Object result = Whitebox.invokeMethod(g2JavaStubController, "getJavaTypeObjectForG2Type", g2proxy);

        // assert
        Assertions.assertThat(result).isNull();

        // verify
        verify(g2proxy).getPropertyValue(CLASS_);
        verifyStatic();
        G2ClassTranslator.getJavaTypeForG2Class(g2ClassName);

    }

    @Test
    public void test_registerMethod_registered_methods_table_for_proxy_class_is_null() throws Exception {
        // mocks
        G2JavaStubController.ConnectionRegistry connectionRegistry = mock(G2JavaStubController.ConnectionRegistry.class);
        Hashtable registeredMethodTables = mock(Hashtable.class);
        Class javaProxyClass = Object.class;
        Item g2Method = mock(Item.class);
        Method method = mock(Method.class);
        Hashtable newRegisteredMethodsTableForProxyClass = mock(Hashtable.class);

        // arrange
        int initialCapacity = 11;
        Hashtable registeredMethodsTableForProxyClass = null;
        Whitebox.setInternalState(connectionRegistry, "registeredMethodTables", registeredMethodTables);

        // given
        when(registeredMethodTables.get(javaProxyClass)).thenReturn(registeredMethodsTableForProxyClass);
        whenNew(Hashtable.class).withArguments(11).thenReturn(newRegisteredMethodsTableForProxyClass);

        // when
        doCallRealMethod().when(connectionRegistry, "registerMethod", javaProxyClass, g2Method, method);
        Whitebox.invokeMethod(connectionRegistry, "registerMethod", javaProxyClass, g2Method, method);

        // verify
        verifyNew(Hashtable.class).withArguments(11);
        verify(registeredMethodTables).put(javaProxyClass, newRegisteredMethodsTableForProxyClass);
        verify(newRegisteredMethodsTableForProxyClass).put(g2Method, method);

    }

    @Test
    public void test_lookupMethod_registered_method_table_for_proxy_class_is_not_null() throws Exception{
        // mocks
        G2JavaStubController.ConnectionRegistry connectionRegistry = mock(G2JavaStubController.ConnectionRegistry.class);
        Hashtable registeredMethodTables = mock(Hashtable.class);
        Class javaProxyClass = Object.class;
        Item g2Method = mock(Item.class);
        Hashtable registeredMethodsTableForProxyClass = mock(Hashtable.class);
        Method returedMethod = mock(Method.class);

        // arrange
        Whitebox.setInternalState(connectionRegistry, "registeredMethodTables", registeredMethodTables);

        // given
        when(registeredMethodTables.get(javaProxyClass)).thenReturn(registeredMethodsTableForProxyClass);
        when(registeredMethodsTableForProxyClass.get(g2Method)).thenReturn(returedMethod);

        // when
        when(connectionRegistry, "lookupMethod", javaProxyClass, g2Method).thenCallRealMethod();
        Method result = Whitebox.invokeMethod(connectionRegistry, "lookupMethod", javaProxyClass, g2Method);

        // assert
        Assertions.assertThat(result).isSameAs(returedMethod);

        // verify
        verify(registeredMethodTables).get(javaProxyClass);
        verify(registeredMethodsTableForProxyClass).get(g2Method);

    }

    @Test
    public void test_lookupMethod_registered_method_table_for_proxy_class_is_null() throws Exception{
        // mocks
        G2JavaStubController.ConnectionRegistry connectionRegistry = mock(G2JavaStubController.ConnectionRegistry.class);
        Hashtable registeredMethodTables = mock(Hashtable.class);
        Class javaProxyClass = Object.class;
        Item g2Method = mock(Item.class);

        // arrange
        Whitebox.setInternalState(connectionRegistry, "registeredMethodTables", registeredMethodTables);
        Hashtable registeredMethodsTableForProxyClass = null;

        // given
        when(registeredMethodTables.get(javaProxyClass)).thenReturn(registeredMethodsTableForProxyClass);

        // when
        when(connectionRegistry, "lookupMethod", javaProxyClass, g2Method).thenCallRealMethod();
        Method result = Whitebox.invokeMethod(connectionRegistry, "lookupMethod", javaProxyClass, g2Method);

        // assert
        Assertions.assertThat(result).isNull();

        // verify
        verify(registeredMethodTables).get(javaProxyClass);

    }

    @Test
    public void test_loadJavaClass_() throws Exception {
        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        DownLoad downloader = mock(DownLoad.class);

        // arrange
        String classname = "classname";
        String source = "source";
        String loadedClass = "loadedClass";

        Whitebox.setInternalState(g2JavaStubController, "downloader", downloader);

        // given
        when(downloader.loadJavaClass(classname, source)).thenReturn(loadedClass);

        // when
        when(g2JavaStubController, "loadJavaClass", classname, source).thenCallRealMethod();
        String result = Whitebox.invokeMethod(g2JavaStubController, "loadJavaClass", classname, source);

        // assert
        Assertions.assertThat(result).isEqualTo(loadedClass);

        // verify
        verify(downloader).loadJavaClass(classname, source);

    }

    @Test
    public void test_callG2ItemListenerMethod_call_method() throws Exception {
        // static mock
        mockStatic(G2_ExternalEventObjectRoot.class);

        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        Item g2proxy = mock(Item.class);
        Item associatedJavaObject = g2proxy;
        Item g2method = mock(Item.class);
        Symbol g2EventClassSym = mock(Symbol.class);
        Structure eventAttributes = mock(Structure.class);
        Item g2EventSource = mock(Item.class);
        G2JavaStubController.ConnectionRegistry registryInfo = mock(G2JavaStubController.ConnectionRegistry.class);
        G2Access g2connection = mock(G2Access.class);
        Sequence args = mock(Sequence.class);
        G2_ExternalEventObjectRoot event = mock(G2_ExternalEventObjectRoot.class);

        // arrange
        String methodName = "methodName";
        registryInfo.g2connection = g2connection;

        // given
        when(g2JavaStubController, "getConnectionRegistry", g2proxy).thenReturn(registryInfo);
        when(registryInfo.getAssociatedJavaObject(g2proxy)).thenReturn(associatedJavaObject);
        when(G2_ExternalEventObjectRoot.createExternalEventObject(g2EventSource, eventAttributes, g2EventClassSym, g2connection)).thenReturn(event);
        whenNew(Sequence.class).withNoArguments().thenReturn(args);

        // when
        doCallRealMethod().when(g2JavaStubController).callG2ItemListenerMethod(g2proxy, methodName, g2method, g2EventClassSym, eventAttributes, g2EventSource);
        g2JavaStubController.callG2ItemListenerMethod(g2proxy, methodName, g2method, g2EventClassSym, eventAttributes, g2EventSource);

        // verify
        verifyPrivate(g2JavaStubController).invoke("getConnectionRegistry", g2proxy);
        verify(registryInfo).getAssociatedJavaObject(g2proxy);
        verifyStatic();
        G2_ExternalEventObjectRoot.createExternalEventObject(g2EventSource, eventAttributes, g2EventClassSym, g2connection);
        verifyNew(Sequence.class).withNoArguments();
        verify(args).addElement(event);
        verify(g2JavaStubController).callMethod(g2proxy, methodName, g2method, args);
    }

    @Test
    public void test_callG2ItemListenerMethod_cant_access_g2() throws Exception {
        // static mock
        mockStatic(G2_ExternalEventObjectRoot.class);

        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        Item g2proxy = mock(Item.class);
        Item associatedJavaObject = g2proxy;
        Item g2method = mock(Item.class);
        Symbol g2EventClassSym = mock(Symbol.class);
        Structure eventAttributes = mock(Structure.class);
        Item g2EventSource = mock(Item.class);
        G2JavaStubController.ConnectionRegistry registryInfo = mock(G2JavaStubController.ConnectionRegistry.class);
        G2Access g2connection = mock(G2Access.class);

        // arrange
        String methodName = "methodName";
        registryInfo.g2connection = g2connection;

        // given
        when(g2JavaStubController, "getConnectionRegistry", g2proxy).thenReturn(registryInfo);
        when(registryInfo.getAssociatedJavaObject(g2proxy)).thenReturn(associatedJavaObject);
        when(G2_ExternalEventObjectRoot.createExternalEventObject(g2EventSource, eventAttributes, g2EventClassSym, g2connection)).thenThrow(G2AccessException.class);
        expectedException.expect(RuntimeException.class);

        // when
        doCallRealMethod().when(g2JavaStubController).callG2ItemListenerMethod(g2proxy, methodName, g2method, g2EventClassSym, eventAttributes, g2EventSource);
        g2JavaStubController.callG2ItemListenerMethod(g2proxy, methodName, g2method, g2EventClassSym, eventAttributes, g2EventSource);

        // verify
        verifyPrivate(g2JavaStubController).invoke("getConnectionRegistry", g2proxy);
        verify(registryInfo).getAssociatedJavaObject(g2proxy);
        verifyStatic();
        G2_ExternalEventObjectRoot.createExternalEventObject(g2EventSource, eventAttributes, g2EventClassSym, g2connection);
    }

    @Test
    public void test_getJavaMethodParameterTypes_java_parameter_types_are_exist() throws Exception {
        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        Item g2method = mock(Item.class);
        Symbol JAVA_PARAMETER_TYPES_ = mock(Symbol.class);
        Sequence parameterClassesSeq = mock(Sequence.class);
        DownLoad downloader = mock(DownLoad.class);
        Class parameterClass = G2_EventObject.class;
        Class G2_parameterClass = Object.class;

        // arrange
        Whitebox.setInternalState(G2JavaStubController.class, "JAVA_PARAMETER_TYPES_", JAVA_PARAMETER_TYPES_);
        int numParameters = 1;
        int i = 0;
        String parameterClassStr = "parameterClassStr";
        Whitebox.setInternalState(g2JavaStubController, "downloader", downloader);
        String G2_parameterClassStr = "G2_parameterClassStr";
        Class[] parameterClasses = {G2_parameterClass};

        // given
        when(g2method.getPropertyValue(JAVA_PARAMETER_TYPES_)).thenReturn(parameterClassesSeq);
        when(parameterClassesSeq.size()).thenReturn(numParameters);
        when(parameterClassesSeq.elementAt(i)).thenReturn(parameterClassStr);
        when(downloader.lookupClass(parameterClassStr)).thenReturn(parameterClass);
        when(g2JavaStubController, "getG2_ClassName", parameterClassStr).thenReturn(G2_parameterClassStr);
        when(downloader.lookupClass(G2_parameterClassStr)).thenReturn(G2_parameterClass);

        // when
        when(g2JavaStubController, "getJavaMethodParameterTypes", g2method).thenCallRealMethod();
        Class[] result = Whitebox.invokeMethod(g2JavaStubController, "getJavaMethodParameterTypes", g2method);

        // assert
        Assertions.assertThat(result).isEqualTo(parameterClasses);

        // verify
        verify(g2method).getPropertyValue(JAVA_PARAMETER_TYPES_);
        verify(parameterClassesSeq).size();
        verify(parameterClassesSeq).elementAt(i);
        verify(downloader).lookupClass(parameterClassStr);
        verifyPrivate(g2JavaStubController).invoke("getG2_ClassName", parameterClassStr);
        verify(downloader).lookupClass(G2_parameterClassStr);
    }

    @Test(expected = MethodInvocationException.class)
    public void test_getJavaMethodParameterTypes_java_parameter_types_attribute_not_found() throws Exception {
        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        Item g2method = mock(Item.class);
        Symbol JAVA_PARAMETER_TYPES_ = mock(Symbol.class);

        // arrange
        Whitebox.setInternalState(G2JavaStubController.class, "JAVA_PARAMETER_TYPES_", JAVA_PARAMETER_TYPES_);

        // given
        when(g2method.getPropertyValue(JAVA_PARAMETER_TYPES_)).thenThrow(NoSuchAttributeException.class);
        expectedException.expect(MethodInvocationException.class);

        // when
        when(g2JavaStubController, "getJavaMethodParameterTypes", g2method).thenCallRealMethod();
        Whitebox.invokeMethod(g2JavaStubController, "getJavaMethodParameterTypes", g2method);

        // verify
        verify(g2method).getPropertyValue(JAVA_PARAMETER_TYPES_);

    }

    @Test
    public void test_getG2_ClassName_() throws Exception {
        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);

        // arrange
        String javaClassName = "java.class.name";

        // when
        when(g2JavaStubController, "getG2_ClassName", javaClassName).thenCallRealMethod();
        String result = Whitebox.invokeMethod(g2JavaStubController, "getG2_ClassName", javaClassName);

        // assert
        Assertions.assertThat(result).isEqualTo("java.class.G2_name");

    }

    @Test
    public void test_callMethod_local_multi_caster() throws Exception {
        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        Item g2proxy = mock(Item.class);
        G2JavaStubController.ConnectionRegistry registryInfo = mock(G2JavaStubController.ConnectionRegistry.class);
        Method method = mock(Method.class);
        Sequence args = mock(Sequence.class);
        G2JavaStubController.LocalMultiCaster javaobj = mock(G2JavaStubController.LocalMultiCaster.class);
        Class argClass = Object.class;
        Object ele = mock(Object.class);
        G2JavaStubController.LocalMultiCaster clocalMultiCaster = mock(G2JavaStubController.LocalMultiCaster.class);

        // arrange
        String method_name = "method_name";
        Class[] argClasses = {argClass};
        int i = 0;
        RuntimeException callJavaMethodException = new RuntimeException();

        // given
        when(javaobj.clone()).thenReturn(clocalMultiCaster);
        when(clocalMultiCaster.size()).thenReturn(1);
        when(clocalMultiCaster.elementAt(i)).thenReturn(ele);
        doThrow(callJavaMethodException).when(g2JavaStubController, "callJavaMethod", g2proxy, ele, method_name, method, args, argClasses, registryInfo);

        // when
        when(g2JavaStubController, "callMethod", g2proxy, javaobj, registryInfo, method_name, method, args, argClasses).thenCallRealMethod();
        Object result = Whitebox.invokeMethod(g2JavaStubController, "callMethod", g2proxy, javaobj, registryInfo, method_name, method, args, argClasses);

        // assert
        Assertions.assertThat(result).isNull();

        // verify
        verify(javaobj).clone();
        verify(javaobj).listenerError(ele, callJavaMethodException);
        verifyPrivate(g2JavaStubController).invoke("callJavaMethod", g2proxy, ele, method_name, method, args, argClasses, registryInfo);

    }

    @Test(expected = IllegalAccessException.class)
    public void test_callMethod_illegal_access() throws Exception {
        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        Item g2proxy = mock(Item.class);
        G2JavaStubController.ConnectionRegistry registryInfo = mock(G2JavaStubController.ConnectionRegistry.class);
        Method method = mock(Method.class);
        Sequence args = mock(Sequence.class);

        // arrange
        Object javaobj = null;
        String method_name = null;
        Class[] argClasses = {};

        // when
        when(g2JavaStubController, "callMethod", g2proxy, javaobj, registryInfo, method_name, method, args, argClasses).thenCallRealMethod();
        Whitebox.invokeMethod(g2JavaStubController, "callMethod", g2proxy, javaobj, registryInfo, method_name, method, args, argClasses);

    }

    @Test(expected = MethodInvocationException.class)
    public void test_callJavaMethod_cant_invoke_method() throws Exception {
        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        Item g2proxy = mock(Item.class);
        Integer javaobj = mock(Integer.class);
        Sequence args = mock(Sequence.class);
        G2JavaStubController.ConnectionRegistry registryInfo = mock(G2JavaStubController.ConnectionRegistry.class);

        // arrange
        Method method = method(Integer.class, "parseInt", String.class);
        Class[] argClasses = null;
        String method_name = null;
        Object[] sequanceContents = {"unparsed_string"};

        // given
        when(args.getContents()).thenReturn(sequanceContents);

        // when
        when(g2JavaStubController, "callJavaMethod", g2proxy, javaobj, method_name, method, args, argClasses, registryInfo).thenCallRealMethod();
        Whitebox.invokeMethod(g2JavaStubController, "callJavaMethod", g2proxy, javaobj, method_name, method, args, argClasses, registryInfo);


    }

    @Test
    public void test_callJavaMethod_g2_listener_and_method_is_provided() throws Exception {
        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        Item g2proxy = mock(Item.class);
        G2JavaStubControllerListener javaobj = mock(G2JavaStubControllerListener.class);
        Sequence args = mock(Sequence.class);
        G2JavaStubController.ConnectionRegistry registryInfo = mock(G2JavaStubController.ConnectionRegistry.class);
        G2JavaStubControllerEvent event = mock(G2JavaStubControllerEvent.class);

        // arrange
        Method method = method(Integer.class, "parseInt", String.class);
        Class[] argClasses = null;
        String method_name = null;
        int CALL_ASYNC_METHOD = 0;
        Whitebox.setInternalState(G2JavaStubControllerEvent.class, "CALL_ASYNC_METHOD", CALL_ASYNC_METHOD);

        // given
        whenNew(G2JavaStubControllerEvent.class).withArguments(g2JavaStubController,
                G2JavaStubControllerEvent.CALL_ASYNC_METHOD, g2proxy, method.getName(), args).thenReturn(event);

        // when
        when(g2JavaStubController, "callJavaMethod", g2proxy, javaobj, method_name, method, args, argClasses, registryInfo).thenCallRealMethod();
        Object result = Whitebox.invokeMethod(g2JavaStubController, "callJavaMethod", g2proxy, javaobj, method_name, method, args, argClasses, registryInfo);

        // assert
        Assertions.assertThat(result).isNull();

        // verify
        verifyNew(G2JavaStubControllerEvent.class).withArguments(g2JavaStubController, G2JavaStubControllerEvent.CALL_ASYNC_METHOD, g2proxy, method.getName(), args);
        verify(javaobj).callMethod(event);
    }

    @Test
    public void test_callJavaMethod_g2_listener() throws Exception {
        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        Item g2proxy = mock(Item.class);
        G2JavaStubControllerListener javaobj = mock(G2JavaStubControllerListener.class);
        Sequence args = mock(Sequence.class);
        G2JavaStubController.ConnectionRegistry registryInfo = mock(G2JavaStubController.ConnectionRegistry.class);
        G2JavaStubControllerEvent event = mock(G2JavaStubControllerEvent.class);

        // arrange
        Method method = null;
        Class[] argClasses = null;
        String method_name = "method_name";
        int CALL_ASYNC_METHOD = 0;
        Whitebox.setInternalState(G2JavaStubControllerEvent.class, "CALL_ASYNC_METHOD", CALL_ASYNC_METHOD);

        // given
        whenNew(G2JavaStubControllerEvent.class).withArguments(g2JavaStubController,
                G2JavaStubControllerEvent.CALL_ASYNC_METHOD, g2proxy, method_name, args).thenReturn(event);

        // when
        when(g2JavaStubController, "callJavaMethod", g2proxy, javaobj, method_name, method, args, argClasses, registryInfo).thenCallRealMethod();
        Object result = Whitebox.invokeMethod(g2JavaStubController, "callJavaMethod", g2proxy, javaobj, method_name, method, args, argClasses, registryInfo);

        // assert
        Assertions.assertThat(result).isNull();

        // verify
        verifyNew(G2JavaStubControllerEvent.class).withArguments(g2JavaStubController, G2JavaStubControllerEvent.CALL_ASYNC_METHOD, g2proxy, method_name, args);
        verify(javaobj).callMethod(event);
    }

    @Test
    public void test_callStaticMethod_() throws  Exception {

        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        Item g2proxy = mock(Item.class);
        Sequence args = mock(Sequence.class);
        G2JavaStubController.ConnectionRegistry registryInfo = mock(G2JavaStubController.ConnectionRegistry.class);
        DownLoad downloader = mock(DownLoad.class);
        Object retval = mock(Object.class);
        Object resolvedRetval = mock(Object.class);

        // arrange
        String java_class_name = "java_class_name";
        String method_name = "method_name";
        Whitebox.setInternalState(g2JavaStubController, "downloader", downloader);
        Class argClass = Object.class;
        Class[] argClasses = {argClass};

        // given
        when(g2JavaStubController, "getConnectionRegistry", g2proxy).thenReturn(registryInfo);
        when(g2JavaStubController, "getArgClassesAndResolve", registryInfo, null, args).thenReturn(argClasses);
        when(downloader.callStaticMethod(java_class_name, method_name, args, argClasses)).thenReturn(retval);
        when(g2JavaStubController, "resolveJavaObjects", registryInfo, retval).thenReturn(resolvedRetval);


        // when
        when(g2JavaStubController.callStaticMethod(g2proxy, java_class_name, method_name, args)).thenCallRealMethod();
        Object result = g2JavaStubController.callStaticMethod(g2proxy, java_class_name, method_name, args);

        // assert
        Assertions.assertThat(result).isSameAs(resolvedRetval);

        // verify
        verifyPrivate(g2JavaStubController).invoke("getConnectionRegistry", g2proxy);
        verifyPrivate(g2JavaStubController).invoke("getArgClassesAndResolve", registryInfo, null, args);
        verify(downloader).callStaticMethod(java_class_name, method_name, args, argClasses);
        verifyPrivate(g2JavaStubController).invoke("resolveJavaObjects", registryInfo, retval);

    }

    @Test
    public void test_callStaticMethod_method_be_invoke() throws Exception {
        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        Item g2proxy = mock(Item.class);
        Item g2method = mock(Item.class);
        Sequence args = mock(Sequence.class);
        G2JavaStubController.ConnectionRegistry registryInfo = mock(G2JavaStubController.ConnectionRegistry.class);
        DownLoad downloader = mock(DownLoad.class);
        Sequence resolvedSequence = mock(Sequence.class);
        Object resolvedRetval = mock(Object.class);

        // arrange
        Class targetClass = Integer.class;
        Class parameterClass = String.class;
        String sequenceContent = "123";

        String java_class_name = "java_class_name";
        String methodName = "parseInt";
        Whitebox.setInternalState(g2JavaStubController, "downloader", downloader);
        Class[] parameterClasses = {parameterClass};
        Method method = targetClass.getMethod(methodName, parameterClasses);
        Object[] sequenceContents = {sequenceContent};

        // given
        when(g2JavaStubController, "getConnectionRegistry", g2proxy).thenReturn(registryInfo);
        when(downloader.lookupClass(java_class_name)).thenReturn(targetClass);
        when(registryInfo.lookupMethod(targetClass, g2method)).thenReturn(null);
        when(g2JavaStubController, "getJavaMethodParameterTypes", g2method).thenReturn(parameterClasses);
        when(g2JavaStubController, "resolveG2StubsInSequence", registryInfo, targetClass, args).thenReturn(resolvedSequence);
        when(resolvedSequence.getContents()).thenReturn(sequenceContents);
        when(g2JavaStubController, "resolveJavaObjects", registryInfo, 123).thenReturn(resolvedRetval);

        // when
        when(g2JavaStubController.callStaticMethod(g2proxy, java_class_name, methodName, g2method, args)).thenCallRealMethod();
        Object result = g2JavaStubController.callStaticMethod(g2proxy, java_class_name, methodName, g2method, args);

        // assert
        Assertions.assertThat(result).isSameAs(resolvedRetval);

        // verify
        verifyPrivate(g2JavaStubController).invoke("getConnectionRegistry", g2proxy);
        verify(downloader).lookupClass(java_class_name);
        verify(registryInfo).lookupMethod(targetClass, g2method);
        verify(registryInfo).registerMethod(targetClass, g2method, method);
        verifyPrivate(g2JavaStubController).invoke("resolveG2StubsInSequence", registryInfo, targetClass, args);

    }

    @Test
    public void test_callStaticMethod_method_cant_be_invoke() throws Exception {
        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        Item g2proxy = mock(Item.class);
        Item g2method = mock(Item.class);
        Sequence args = mock(Sequence.class);
        G2JavaStubController.ConnectionRegistry registryInfo = mock(G2JavaStubController.ConnectionRegistry.class);
        DownLoad downloader = mock(DownLoad.class);
        Sequence resolvedSequence = mock(Sequence.class);

        // arrange
        Class targetClass = Integer.class;
        Class parameterClass = String.class;
        String sequenceContent = "cant_parse_to_integer";

        String java_class_name = "java_class_name";
        String methodName = "parseInt";
        Whitebox.setInternalState(g2JavaStubController, "downloader", downloader);
        Class[] parameterClasses = {parameterClass};
        Method method = targetClass.getMethod(methodName, parameterClasses);
        Object[] sequenceContents = {sequenceContent};

        // given
        when(g2JavaStubController, "getConnectionRegistry", g2proxy).thenReturn(registryInfo);
        when(downloader.lookupClass(java_class_name)).thenReturn(targetClass);
        when(registryInfo.lookupMethod(targetClass, g2method)).thenReturn(null);
        when(g2JavaStubController, "getJavaMethodParameterTypes", g2method).thenReturn(parameterClasses);
        when(g2JavaStubController, "resolveG2StubsInSequence", registryInfo, targetClass, args).thenReturn(resolvedSequence);
        when(resolvedSequence.getContents()).thenReturn(sequenceContents);
        expectedException.expect(MethodInvocationException.class);

        // when
        when(g2JavaStubController.callStaticMethod(g2proxy, java_class_name, methodName, g2method, args)).thenCallRealMethod();
        g2JavaStubController.callStaticMethod(g2proxy, java_class_name, methodName, g2method, args);


        // verify
        verifyPrivate(g2JavaStubController).invoke("getConnectionRegistry", g2proxy);
        verify(downloader).lookupClass(java_class_name);
        verify(registryInfo).lookupMethod(targetClass, g2method);
        verify(registryInfo).registerMethod(targetClass, g2method, method);
        verifyPrivate(g2JavaStubController).invoke("resolveG2StubsInSequence", registryInfo, targetClass, args);

    }

    @Test
    public void test_deleteInstance_() throws Exception{
        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        Item g2proxy = mock(Item.class);


        // arrange
        boolean strictCheck = true;

        // when
        doCallRealMethod().when(g2JavaStubController).deleteInstance(g2proxy);
        g2JavaStubController.deleteInstance(g2proxy);

        // verify
        verify(g2JavaStubController).deleteInstance(g2proxy, strictCheck);
    }

    @Test
    public void test_deleteInstance_not_strict() throws Exception {
        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        G2JavaStubController.ConnectionRegistry registryInfo = mock(G2JavaStubController.ConnectionRegistry.class);
        Item g2proxy = mock(Item.class);

        // arrange
        boolean strictCheck = false;
        Object javaobj = null;

        // given
        when(g2JavaStubController, "getConnectionRegistry", g2proxy).thenReturn(registryInfo);

        // when
        doCallRealMethod().when(g2JavaStubController).deleteInstance(g2proxy, strictCheck);
        g2JavaStubController.deleteInstance(g2proxy, strictCheck);

        // verify
        verifyPrivate(g2JavaStubController).invoke("getConnectionRegistry", g2proxy);
        verify(registryInfo).removeAssociation(g2proxy);

    }

    @Test
    public void test_deleteInstance_stricted_and_java_object_is_null() throws Exception {
        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        G2JavaStubController.ConnectionRegistry registryInfo = mock(G2JavaStubController.ConnectionRegistry.class);
        Item g2proxy = mock(Item.class);

        // arrange
        boolean strictCheck = true;
        Object javaobj = null;

        // given
        when(g2JavaStubController, "getConnectionRegistry", g2proxy).thenReturn(registryInfo);
        expectedException.expect(IllegalAccessException.class);

        // when
        doCallRealMethod().when(g2JavaStubController).deleteInstance(g2proxy, strictCheck);
        g2JavaStubController.deleteInstance(g2proxy, strictCheck);

        // verify
        verifyPrivate(g2JavaStubController).invoke("getConnectionRegistry", g2proxy);
        verify(registryInfo).removeAssociation(g2proxy);

    }

    @Test
    public void test_getG2StubsForJavaBeanClass_create_g2_stub() throws Exception {
        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        G2JavaStubClassReflectionProvider g2JavaStubClassReflectionProvider = mock(G2JavaStubClassReflectionProvider.class);
        DownLoad  downloader = mock(DownLoad.class);
        Class the_class = Object.class;
        Structure returnedStructure = mock(Structure.class);
        Symbol g2ClassName = mock(Symbol.class);

        // arrange
        String class_name = "class_name";
        boolean recurse = false;
        Whitebox.setInternalState(g2JavaStubController, "g2JavaStubClassReflectionProvider", g2JavaStubClassReflectionProvider);
        Whitebox.setInternalState(g2JavaStubController, "downloader", downloader);
        boolean forBeanWrapper = true;

        // given
        when(downloader.lookupClass(class_name)).thenReturn(the_class);
        when(g2JavaStubClassReflectionProvider.getG2StubDetailsForJavaClass(class_name, the_class, g2ClassName, recurse, forBeanWrapper)).thenReturn(returnedStructure);

        // when
        when(g2JavaStubController, "getG2StubsForJavaBeanClass", class_name, g2ClassName, recurse).thenCallRealMethod();
        Structure result = Whitebox.invokeMethod(g2JavaStubController, "getG2StubsForJavaBeanClass", class_name, g2ClassName, recurse);

        // assert
        Assertions.assertThat(result).isSameAs(returnedStructure);

        // verify
        verify(downloader).lookupClass(class_name);
        verify(g2JavaStubClassReflectionProvider).getG2StubDetailsForJavaClass(class_name, the_class, g2ClassName, recurse, forBeanWrapper);

    }

    @Test(expected = G2StubCreationException.class)
    public void test_getG2StubsForJavaBeanClass_cant_create_g2_stub() throws Exception {
        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        Symbol g2ClassName = mock(Symbol.class);

        // arrange
        String class_name = "class_name";
        boolean recurse = false;
        G2JavaStubClassReflectionProvider g2JavaStubClassReflectionProvider = null;
        Whitebox.setInternalState(g2JavaStubController, "g2JavaStubClassReflectionProvider", g2JavaStubClassReflectionProvider);

        // when
        when(g2JavaStubController, "getG2StubsForJavaBeanClass", class_name, g2ClassName, recurse).thenCallRealMethod();
        Whitebox.invokeMethod(g2JavaStubController, "getG2StubsForJavaBeanClass", class_name, g2ClassName, recurse);

    }


    @Test
    public void test_findStubHierarchyForjavaClass_create_g2_stub() throws Exception {
        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        G2JavaStubClassReflectionProvider g2JavaStubClassReflectionProvider = mock(G2JavaStubClassReflectionProvider.class);
        DownLoad  downloader = mock(DownLoad.class);
        Class the_class = Object.class;
        Sequence foundedSequence = mock(Sequence.class);

        // arrange
        String class_name = "class_name";
        boolean recurse = false;
        Whitebox.setInternalState(g2JavaStubController, "g2JavaStubClassReflectionProvider", g2JavaStubClassReflectionProvider);
        Whitebox.setInternalState(g2JavaStubController, "downloader", downloader);

        // given
        when(downloader.lookupClass(class_name)).thenReturn(the_class);
        when(g2JavaStubClassReflectionProvider.findDependentClasses(class_name, the_class, recurse)).thenReturn(foundedSequence);

        // when
        when(g2JavaStubController, "findStubHierarchyForjavaClass", class_name, recurse).thenCallRealMethod();
        Sequence result = Whitebox.invokeMethod(g2JavaStubController, "findStubHierarchyForjavaClass", class_name, recurse);

        // assert
        Assertions.assertThat(result).isSameAs(foundedSequence);

        // verify
        verify(downloader).lookupClass(class_name);
        verify(g2JavaStubClassReflectionProvider).findDependentClasses(class_name, the_class, recurse);

    }

    @Test(expected = G2StubCreationException.class)
    public void test_findStubHierarchyForjavaClass_cant_create_g2_stub() throws Exception {
        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);

        // arrange
        String class_name = "class_name";
        boolean recurse = false;
        G2JavaStubClassReflectionProvider g2JavaStubClassReflectionProvider = null;
        Whitebox.setInternalState(g2JavaStubController, "g2JavaStubClassReflectionProvider", g2JavaStubClassReflectionProvider);

        // when
        when(g2JavaStubController, "findStubHierarchyForjavaClass", class_name, recurse).thenCallRealMethod();
        Whitebox.invokeMethod(g2JavaStubController, "findStubHierarchyForjavaClass", class_name, recurse);


    }

    @Test
    public void test_registerG2ClassWithJavaClass_() throws Exception {
        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        Item g2Proxy = mock(Item.class);
        G2JavaStubController.ConnectionRegistry registryInfo = mock(G2JavaStubController.ConnectionRegistry.class);

        // arrange
        String java_class_name = "java_class_name";

        // given
        when(g2JavaStubController, "getConnectionRegistry", g2Proxy).thenReturn(registryInfo);

        // when
        doCallRealMethod().when(g2JavaStubController).registerG2ClassWithJavaClass(g2Proxy, java_class_name);
        g2JavaStubController.registerG2ClassWithJavaClass(g2Proxy, java_class_name);

        // verify
        verifyPrivate(g2JavaStubController).invoke("getConnectionRegistry", g2Proxy);
        verify(registryInfo).registerG2ClassWithJavaClass(g2Proxy, java_class_name);
    }

    @Test
    public void test_associate_() throws Exception {
        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        G2Connection g2Connection = mock(G2Connection.class);
        Item g2Proxy = mock(Item.class);
        Object javaObject = mock(Object.class);
        G2JavaStubController.ConnectionRegistry registryInfo = mock(G2JavaStubController.ConnectionRegistry.class);


        // given
        when(g2JavaStubController, "getConnectionRegistry", g2Connection).thenReturn(registryInfo);

        // when
        doCallRealMethod().when(g2JavaStubController).associate(g2Connection, g2Proxy, javaObject);
        g2JavaStubController.associate(g2Connection, g2Proxy, javaObject);

        // verify
        verifyPrivate(g2JavaStubController).invoke("getConnectionRegistry", g2Connection);
        verify(registryInfo).associate(g2Proxy, javaObject);
    }

    @Test
    public void test_addJavaListenerToG2EventSource_no_local_multi_caster() throws Exception {
        //mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        Item g2EventSource =  mock(Item.class);
        Symbol adderMethodName = mock(Symbol.class);
        Symbol g2ParentClass = mock(Symbol.class);
        Object javaListener = mock(Object.class);
        G2JavaStubController.ConnectionRegistry registryInfo = mock(G2JavaStubController.ConnectionRegistry.class);
        G2Connection g2Connection = mock(G2Connection.class);
        G2JavaStubController.LocalMultiCaster localMultiCaster = mock(G2JavaStubController.LocalMultiCaster.class);

        // arrange
        Item g2proxy = null;
        Whitebox.setInternalState(localMultiCaster, "g2proxy", g2proxy);
        boolean listening = false;
        Whitebox.setInternalState(localMultiCaster, "listening", listening);

        registryInfo.g2connection = g2Connection;
        String javaProxyClass = "javaProxyClass";

        Object[] args = new java.lang.Object[]{g2proxy, adderMethodName, g2EventSource};

        Symbol JgiAddProxyEventListener = mock(Symbol.class);
        Whitebox.setInternalState(G2JavaStubController.class, "JgiAddProxyEventListener", JgiAddProxyEventListener);

        // given
        when(g2JavaStubController, "getConnectionRegistry", g2EventSource).thenReturn(registryInfo);
        when(registryInfo.getMultiCaster(g2EventSource, g2ParentClass)).thenReturn(null);
        when(g2JavaStubController, "getG2ProxyForJavaObjectAttachedToEventSource", g2Connection, javaProxyClass, g2ParentClass, localMultiCaster, g2EventSource).thenReturn(g2proxy);
        whenNew(G2JavaStubController.LocalMultiCaster.class).withNoArguments().thenReturn(localMultiCaster);

        // when
        when(g2JavaStubController, "addJavaListenerToG2EventSource",   g2EventSource, adderMethodName, javaProxyClass, g2ParentClass, javaListener).thenCallRealMethod();
        Item result = Whitebox.invokeMethod(g2JavaStubController, "addJavaListenerToG2EventSource",   g2EventSource, adderMethodName, javaProxyClass, g2ParentClass, javaListener);

        // assert
        Assertions.assertThat(result).isSameAs(g2proxy);
        Assertions.assertThat((Boolean)Whitebox.getInternalState(localMultiCaster, "listening")).isTrue();

        // verify
        verifyPrivate(g2JavaStubController).invoke("getConnectionRegistry", g2EventSource);
        verify(registryInfo).getMultiCaster(g2EventSource, g2ParentClass);
        verify(registryInfo).setMultiCaster(g2EventSource, g2ParentClass, localMultiCaster);
        verifyNew(G2JavaStubController.LocalMultiCaster.class).withNoArguments();
        verify(g2Connection).callRPC(JgiAddProxyEventListener, args);
    }

    @Test
    public void test_getG2ProxyForJavaObjectAttachedToEventSource_g2_class_sys()  throws  Exception {
        // static mocks
        mockStatic(Symbol.class);

        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        G2Connection g2Connection = mock(G2Connection.class);
        Symbol g2ParentClass = mock(Symbol.class);
        Object javaObject = mock(Object.class);
        Item eventSource = mock(Item.class);
        G2JavaStubController.ConnectionRegistry registryInfo = mock(G2JavaStubController.ConnectionRegistry.class);
        Item newproxy = mock(Item.class);

        // arrange
        String javaProxyClass = "javaProxyClass";
        Item g2proxy = null;
        Symbol NONE_ = null;
        Whitebox.setInternalState(G2JavaStubController.class, "NONE_",NONE_);
        Symbol g2ProxyClassSym = mock(Symbol.class);
        Object[] args = {g2ProxyClassSym, g2ParentClass, javaProxyClass, eventSource};
        Symbol JgiCreateClassAndReturnProxyForEventSourceSymbol = mock(Symbol.class);
        Whitebox.setInternalState(G2JavaStubController.class, "JgiCreateClassAndReturnProxyForEventSourceSymbol", JgiCreateClassAndReturnProxyForEventSourceSymbol);

        // given
        when(g2JavaStubController, "getConnectionRegistry", g2Connection).thenReturn(registryInfo);
        when(registryInfo.getG2ProxyForJavaObject(javaObject)).thenReturn(g2proxy);
        when(registryInfo.getG2ClassForJavaObject(javaObject)).thenReturn(g2ProxyClassSym);
        when(Symbol.intern("_AG2PROXYLISTENER_" + javaProxyClass.toUpperCase())).thenReturn(g2ProxyClassSym);
        when(g2Connection.callRPC(JgiCreateClassAndReturnProxyForEventSourceSymbol, args, 0)).thenReturn(newproxy);

        // when
        when(g2JavaStubController, "getG2ProxyForJavaObjectAttachedToEventSource", g2Connection, javaProxyClass, g2ParentClass, javaObject, eventSource).thenCallRealMethod();
        Item result = Whitebox.invokeMethod(g2JavaStubController, "getG2ProxyForJavaObjectAttachedToEventSource", g2Connection, javaProxyClass, g2ParentClass, javaObject, eventSource);

        // assert
        Assertions.assertThat(result).isSameAs(newproxy);

        // verify
        verifyPrivate(g2JavaStubController).invoke("getConnectionRegistry", g2Connection);
        verify(registryInfo).getG2ProxyForJavaObject(javaObject);
        verifyStatic();
        Symbol.intern("_AG2PROXYLISTENER_" + javaProxyClass.toUpperCase());
        verify(registryInfo).ensureJavaLinkModuleVersionIsValid();
        verify(registryInfo).associate(newproxy, javaObject);

    }

    @Test
    public void test_getG2ProxyForJavaObjectAttachedToEventSource_g2_parent_none()  throws  Exception {
        // static mocks
        mockStatic(Symbol.class);

        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        G2Connection g2Connection = mock(G2Connection.class);
        Symbol g2ParentClass = mock(Symbol.class);
        Object javaObject = mock(Object.class);
        Item eventSource = mock(Item.class);
        G2JavaStubController.ConnectionRegistry registryInfo = mock(G2JavaStubController.ConnectionRegistry.class);

        // arrange
        String javaProxyClass = null;
        Item g2proxy = null;
        Symbol NONE_ = g2ParentClass;
        Whitebox.setInternalState(G2JavaStubController.class, "NONE_",NONE_);
        Symbol g2ProxyClassSym = null;

        // given
        when(g2JavaStubController, "getConnectionRegistry", g2Connection).thenReturn(registryInfo);
        when(registryInfo.getG2ProxyForJavaObject(javaObject)).thenReturn(g2proxy);
        when(registryInfo.getG2ClassForJavaObject(javaObject)).thenReturn(g2ProxyClassSym);
        expectedException.expect(G2AccessException.class);

        // when
        when(g2JavaStubController, "getG2ProxyForJavaObjectAttachedToEventSource", g2Connection, javaProxyClass, g2ParentClass, javaObject, eventSource).thenCallRealMethod();
        Whitebox.invokeMethod(g2JavaStubController, "getG2ProxyForJavaObjectAttachedToEventSource", g2Connection, javaProxyClass, g2ParentClass, javaObject, eventSource);

        // verify
        verifyPrivate(g2JavaStubController).invoke("getConnectionRegistry", g2Connection);
        verify(registryInfo).getG2ProxyForJavaObject(javaObject);
    }

    @Test
    public void test_getG2ProxyForJavaObjectAttachedToEventSource_java_object_have_g2_proxy() throws Exception{
        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        G2Connection g2Connection = mock(G2Connection.class);
        Symbol g2ParentClass = mock(Symbol.class);
        Object javaObject = mock(Object.class);
        Item eventSource = mock(Item.class);
        G2JavaStubController.ConnectionRegistry registryInfo = mock(G2JavaStubController.ConnectionRegistry.class);
        Item g2proxy = mock(Item.class);

        // arrange
        String javaProxyClass = "javaProxyClass";

        // given
        when(g2JavaStubController, "getConnectionRegistry", g2Connection).thenReturn(registryInfo);
        when(registryInfo.getG2ProxyForJavaObject(javaObject)).thenReturn(g2proxy);

        // when
        when(g2JavaStubController, "getG2ProxyForJavaObjectAttachedToEventSource", g2Connection, javaProxyClass, g2ParentClass, javaObject, eventSource).thenCallRealMethod();
        Item result = Whitebox.invokeMethod(g2JavaStubController, "getG2ProxyForJavaObjectAttachedToEventSource", g2Connection, javaProxyClass, g2ParentClass, javaObject, eventSource);

        // assert
        Assertions.assertThat(result).isSameAs(g2proxy);

        // verify
        verifyPrivate(g2JavaStubController).invoke("getConnectionRegistry", g2Connection);
        verify(registryInfo).getG2ProxyForJavaObject(javaObject);

    }

    @Test
    public void test_getG2ProxyForJavaObjectAttachedToEventSource_java_object_is_item() throws Exception{
        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        G2Connection g2Connection = mock(G2Connection.class);
        String javaProxyClass = "javaProxyClass";
        Symbol g2ParentClass = mock(Symbol.class);
        Item javaObject = mock(Item.class);
        Item eventSource = mock(Item.class);

        // given
        when(javaObject.isItemLocal()).thenReturn(false);

        // when
        when(g2JavaStubController, "getG2ProxyForJavaObjectAttachedToEventSource", g2Connection, javaProxyClass, g2ParentClass, javaObject, eventSource).thenCallRealMethod();
        Item result = Whitebox.invokeMethod(g2JavaStubController, "getG2ProxyForJavaObjectAttachedToEventSource", g2Connection, javaProxyClass, g2ParentClass, javaObject, eventSource);

        // assert
        Assertions.assertThat(result).isSameAs(javaObject);

        // verify
        verify(javaObject).isItemLocal();

    }

    @Test
    public void test_removeJavaListenerFromG2EventSource_no_local_multi_caster() throws Exception {
        //mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        Item g2EventSource = mock(Item.class);
        Symbol g2ParentClass = mock(Symbol.class);
        G2JavaStubController.ConnectionRegistry registryInfo = mock(G2JavaStubController.ConnectionRegistry.class);
        G2Access g2Connection = mock(G2Access.class);
        Symbol removerMethodName = mock(Symbol.class);
        Object javaListener = mock(Object.class);

        // arrange
        G2JavaStubController.LocalMultiCaster localMultiCaster = null;
        registryInfo.g2connection = g2Connection;
        String javaProxyClass = "javaProxyClass";

        // given
        when(g2JavaStubController, "getConnectionRegistry", g2EventSource).thenReturn(registryInfo);
        when(registryInfo.getMultiCaster(g2EventSource, g2ParentClass)).thenReturn(localMultiCaster);

        // when
        when(g2JavaStubController, "removeJavaListenerFromG2EventSource",   g2EventSource, removerMethodName, javaProxyClass, g2ParentClass, javaListener).thenCallRealMethod();
        Item result = Whitebox.invokeMethod(g2JavaStubController, "removeJavaListenerFromG2EventSource",   g2EventSource, removerMethodName, javaProxyClass, g2ParentClass, javaListener);

        // assert
        Assertions.assertThat(result).isNull();

        // verify
        verifyPrivate(g2JavaStubController).invoke("getConnectionRegistry", g2EventSource);
        verify(registryInfo).getMultiCaster(g2EventSource, g2ParentClass);
    }

    @Test
    public void test_removeJavaListenerFromG2EventSource_remove_listener() throws Exception {
        //mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        Item g2EventSource = mock(Item.class);
        Symbol removerMethodName = mock(Symbol.class);
        Symbol g2ParentClass = mock(Symbol.class);
        Object javaListener = mock(Object.class);
        G2JavaStubController.ConnectionRegistry registryInfo = mock(G2JavaStubController.ConnectionRegistry.class);
        G2Access g2Connection = mock(G2Access.class);
        G2JavaStubController.LocalMultiCaster localMultiCaster = mock(G2JavaStubController.LocalMultiCaster.class);
        Item g2proxy = mock(Item.class);
        Symbol JgiRemoveProxyEventListener = mock(Symbol.class);

        // arrange
        String javaProxyClass = "javaProxyClass";
        registryInfo.g2connection = g2Connection;
        localMultiCaster.g2proxy = g2proxy;
        Object[] args = new java.lang.Object[]{localMultiCaster.g2proxy, removerMethodName, g2EventSource};
        Whitebox.setInternalState(G2JavaStubController.class, "JgiRemoveProxyEventListener", JgiRemoveProxyEventListener);

        // given
        when(g2JavaStubController, "getConnectionRegistry", g2EventSource).thenReturn(registryInfo);
        when(registryInfo.getMultiCaster(g2EventSource, g2ParentClass)).thenReturn(localMultiCaster);
        when(localMultiCaster.isEmpty()).thenReturn(true);

        // when
        when(g2JavaStubController, "removeJavaListenerFromG2EventSource",   g2EventSource, removerMethodName, javaProxyClass, g2ParentClass, javaListener).thenCallRealMethod();
        Item result = Whitebox.invokeMethod(g2JavaStubController, "removeJavaListenerFromG2EventSource",   g2EventSource, removerMethodName, javaProxyClass, g2ParentClass, javaListener);

        // assert
        Assertions.assertThat(result).isSameAs(g2proxy);
        Boolean listening = Whitebox.getInternalState(localMultiCaster, "listening");
        Assertions.assertThat(listening).isFalse();

        // verify
        verifyPrivate(g2JavaStubController).invoke("getConnectionRegistry", g2EventSource);
        verify(registryInfo).getMultiCaster(g2EventSource, g2ParentClass);
        verify(localMultiCaster).removeElement(javaListener);
        verify(g2Connection).callRPC(JgiRemoveProxyEventListener, args);

    }

    @Test
    public void test_getG2ProxyForJavaObject_g2_parent_class_is_not_none()  throws  Exception {
        // static mocks
        mockStatic(Symbol.class);

        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        G2Connection g2Connection = mock(G2Connection.class);
        Symbol g2ParentClass = mock(Symbol.class);
        Object javaObject = mock(Object.class);
        G2JavaStubController.ConnectionRegistry registryInfo = mock(G2JavaStubController.ConnectionRegistry.class);
        Symbol g2ProxyClassSym = mock(Symbol.class);
        Item newproxy = mock(Item.class);

        // arrenge
        String javaProxyClass = "javaProxyClass";
        Symbol NONE_ = null;
        Whitebox.setInternalState(G2JavaStubController.class, "NONE_", NONE_);

        // given
        when(g2JavaStubController, "getConnectionRegistry", g2Connection).thenReturn(registryInfo);
        when(registryInfo.getG2ClassForJavaObject(javaObject)).thenReturn(g2ProxyClassSym);
        when(Symbol.intern("_AG2PROXY_" + javaProxyClass.toUpperCase())).thenReturn(g2ProxyClassSym);
        when(g2JavaStubController, "createG2ObjectAndReturnProxy", registryInfo, g2ProxyClassSym, g2ParentClass, javaProxyClass).thenReturn(newproxy);

        // when
        when(g2JavaStubController, "getG2ProxyForJavaObject", g2Connection, javaProxyClass, g2ParentClass, javaObject).thenCallRealMethod();
        Item result = Whitebox.invokeMethod(g2JavaStubController, "getG2ProxyForJavaObject", g2Connection, javaProxyClass, g2ParentClass, javaObject);

        // assert
        Assertions.assertThat(result).isSameAs(newproxy);

        // verify
        verifyPrivate(g2JavaStubController).invoke("getConnectionRegistry", g2Connection);
        verify(registryInfo).getG2ProxyForJavaObject(javaObject);
        verifyStatic();
        Symbol.intern("_AG2PROXY_" + javaProxyClass.toUpperCase());
        verifyPrivate(g2JavaStubController).invoke("createG2ObjectAndReturnProxy", registryInfo, g2ProxyClassSym, g2ParentClass, javaProxyClass);
        verify(registryInfo).associate(newproxy, javaObject);


    }

    @Test
    public void getG2ProxyForJavaObject_no_g2_class_to_create_proxy()  throws  Exception {
        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        G2Connection g2Connection = mock(G2Connection.class);
        Symbol g2ParentClass = mock(Symbol.class);
        Object javaObject = mock(Object.class);
        G2JavaStubController.ConnectionRegistry registryInfo = mock(G2JavaStubController.ConnectionRegistry.class);

        // arrenge
        String javaProxyClass = null;
        Symbol g2ProxyClassSym = null;
        Whitebox.setInternalState(G2JavaStubController.class, "NONE_", g2ParentClass);

        // given
        when(g2JavaStubController, "getConnectionRegistry", g2Connection).thenReturn(registryInfo);
        when(registryInfo.getG2ClassForJavaObject(javaObject)).thenReturn(g2ProxyClassSym);
        expectedException.expect(G2AccessException.class);

        // when
        when(g2JavaStubController, "getG2ProxyForJavaObject", g2Connection, javaProxyClass, g2ParentClass, javaObject).thenCallRealMethod();
        Whitebox.invokeMethod(g2JavaStubController, "getG2ProxyForJavaObject", g2Connection, javaProxyClass, g2ParentClass, javaObject);

        // verify
        verifyPrivate(g2JavaStubController).invoke("getConnectionRegistry", g2Connection);
        verify(registryInfo).getG2ProxyForJavaObject(javaObject);

    }

    @Test
    public void getG2ProxyForJavaObject_java_object_is_g2_proxy()  throws  Exception {
        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        G2Connection g2Connection = mock(G2Connection.class);
        Symbol g2ParentClass = mock(Symbol.class);
        Object javaObject = mock(Object.class);
        G2JavaStubController.ConnectionRegistry registryInfo = mock(G2JavaStubController.ConnectionRegistry.class);
        Item g2proxy = mock(Item.class);

        // arrenge
        String javaProxyClass = "javaProxyClass";

        // given
        when(g2JavaStubController, "getConnectionRegistry", g2Connection).thenReturn(registryInfo);
        when(registryInfo.getG2ProxyForJavaObject(javaObject)).thenReturn(g2proxy);

        // when
        when(g2JavaStubController, "getG2ProxyForJavaObject", g2Connection, javaProxyClass, g2ParentClass, javaObject).thenCallRealMethod();
        Item result = Whitebox.invokeMethod(g2JavaStubController, "getG2ProxyForJavaObject", g2Connection, javaProxyClass, g2ParentClass, javaObject);

        // assert
        Assertions.assertThat(result).isSameAs(g2proxy);

        // verify
        verifyPrivate(g2JavaStubController).invoke("getConnectionRegistry", g2Connection);
        verify(registryInfo).getG2ProxyForJavaObject(javaObject);

    }

    @Test
    public void getG2ProxyForJavaObject_java_object_not_is_item_local()  throws  Exception {
        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        G2Connection g2Connection = mock(G2Connection.class);
        Symbol g2ParentClass = mock(Symbol.class);
        Item javaObject = mock(Item.class);

        // arrenge
        String javaProxyClass = "";

        // given
        when(javaObject.isItemLocal()).thenReturn(false);

        // when
        when(g2JavaStubController, "getG2ProxyForJavaObject", g2Connection, javaProxyClass, g2ParentClass, javaObject).thenCallRealMethod();
        Item result = Whitebox.invokeMethod(g2JavaStubController, "getG2ProxyForJavaObject", g2Connection, javaProxyClass, g2ParentClass, javaObject);

        // assert
        Assertions.assertThat(result).isSameAs(javaObject);

        // verify
        verify(javaObject).isItemLocal();

    }

    @Test
    public void test_newArrayInstance_() throws Exception {
        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        Item g2proxy = mock(Item.class);
        DownLoad downloader = mock(DownLoad.class);
        G2JavaStubController.ConnectionRegistry registryInfo = mock(G2JavaStubController.ConnectionRegistry.class);
        Object obj = mock(Object.class);

        // arrange
        int size = 1;
        String java_class_name = "testClass";
        Whitebox.setInternalState(g2JavaStubController, "downloader", downloader);

        // given
        when(g2JavaStubController, "getConnectionRegistry", g2proxy).thenReturn(registryInfo);
        when(downloader.newArrayInstance(java_class_name, size)).thenReturn(obj);

        // when
        doCallRealMethod().when(g2JavaStubController, "newArrayInstance", g2proxy, java_class_name, size);
        Whitebox.invokeMethod(g2JavaStubController, "newArrayInstance", g2proxy, java_class_name, size);

        // verify
        verifyPrivate(g2JavaStubController).invoke("getConnectionRegistry", g2proxy);
        verify(downloader).newArrayInstance(java_class_name, size);
        verify(registryInfo).registerG2ClassWithJavaClass(g2proxy, java_class_name);
        verify(registryInfo).associate(g2proxy, obj);

    }

    @Test
    public void test_newArrayInstanceWithDimensions_dimension_is_int() throws Exception {

        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        G2JavaStubController.ConnectionRegistry registryInfo = mock(G2JavaStubController.ConnectionRegistry.class);
        Item g2proxy = mock(Item.class);
        Sequence dimensions = mock(Sequence.class);
        DownLoad downloader = mock(DownLoad.class);
        Object obj = mock(Object.class);

        // arrange
        String java_class_name = "testClass";
        int length = 1;
        int i=0;
        Object dimension = 1;
        int[] dimensionsArray = {1};
        Whitebox.setInternalState(g2JavaStubController, "downloader", downloader);

        // given
        when(g2JavaStubController, "getConnectionRegistry", g2proxy).thenReturn(registryInfo);
        when(dimensions.size()).thenReturn(length);
        when(dimensions.elementAt(i)).thenReturn(dimension);
        when(downloader.newArrayInstance(java_class_name, dimensionsArray)).thenReturn(obj);

        // when
        doCallRealMethod().when(g2JavaStubController, "newArrayInstanceWithDimensions", g2proxy, java_class_name, dimensions);
        Whitebox.invokeMethod(g2JavaStubController, "newArrayInstanceWithDimensions", g2proxy, java_class_name, dimensions);

        // verify
        verifyPrivate(g2JavaStubController).invoke("getConnectionRegistry", g2proxy);
        verify(dimensions).size();
        verify(dimensions).elementAt(i);
        verify(downloader).newArrayInstance(java_class_name, dimensionsArray);
        verify(registryInfo).registerG2ClassWithJavaClass(g2proxy, java_class_name);
        verify(registryInfo).associate(g2proxy, obj);
    }

    @Test
    public void test_newArrayInstanceWithDimensions_dimension_is_not_int() throws Exception {

        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        Item g2proxy = mock(Item.class);
        Sequence dimensions = mock(Sequence.class);
        Object dimension = mock(Object.class);

        // arrange
        String java_class_name = "testClass";
        int length = 1;
        int i=0;

        // given
        when(dimensions.size()).thenReturn(length);
        when(dimensions.elementAt(i)).thenReturn(dimension);
        expectedException.expect(IllegalArgumentException.class);

        // when
        doCallRealMethod().when(g2JavaStubController, "newArrayInstanceWithDimensions", g2proxy, java_class_name, dimensions);
        Whitebox.invokeMethod(g2JavaStubController, "newArrayInstanceWithDimensions", g2proxy, java_class_name, dimensions);

        // verify
        verify(dimensions).size();
        verify(dimensions).elementAt(i);
    }

    @Test
    public void test_newArrayInstanceWithDimensions_dimension_is_null() throws Exception {

        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        Item g2proxy = mock(Item.class);
        Sequence dimensions = mock(Sequence.class);

        // arrange
        String java_class_name = "testClass";
        int length = 1;
        int i=0;
        Object dimension = null;

        // given
        when(dimensions.size()).thenReturn(length);
        when(dimensions.elementAt(i)).thenReturn(dimension);
        expectedException.expect(IllegalArgumentException.class);

        // when
        doCallRealMethod().when(g2JavaStubController, "newArrayInstanceWithDimensions", g2proxy, java_class_name, dimensions);
        Whitebox.invokeMethod(g2JavaStubController, "newArrayInstanceWithDimensions", g2proxy, java_class_name, dimensions);

        // verify
        verify(dimensions).size();
        verify(dimensions).elementAt(i);
    }

    @Test
    public void test_getArrayElement_java_object_is_array() throws Exception {
        // static mocks
        mockStatic(Array.class);

        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        G2JavaStubController.ConnectionRegistry registryInfo = mock(G2JavaStubController.ConnectionRegistry.class);
        Item g2proxy = mock(Item.class);
        Object retval = mock(Object.class);
        Object resolvedRetval = mock(Object.class);
        Sequence retseq = mock(Sequence.class);
        // arrange
        int pos = 0;
        Object[] javaobj = {retval};

        // given
        when(g2JavaStubController, "getConnectionRegistry", g2proxy).thenReturn(registryInfo);
        when(registryInfo.getAssociatedJavaObject(g2proxy)).thenReturn(javaobj);
        when(Array.get(javaobj, pos)).thenReturn(retval);
        when(g2JavaStubController, "resolveJavaObjects", registryInfo, retval).thenReturn(resolvedRetval);
        whenNew(Sequence.class).withArguments(1).thenReturn(retseq);


        // when
        doCallRealMethod().when(g2JavaStubController, "getArrayElement", g2proxy, pos);
        Sequence result = Whitebox.invokeMethod(g2JavaStubController, "getArrayElement", g2proxy, pos);

        // assert
        Assertions.assertThat(result).isSameAs(retseq);

        // verify
        verifyPrivate(g2JavaStubController).invoke("getConnectionRegistry", g2proxy);
        verify(registryInfo).getAssociatedJavaObject(g2proxy);
        verifyStatic();
        Array.get(javaobj, pos);
        verifyNew(Sequence.class).withArguments(1);
        verify(retseq).addElement(resolvedRetval);

    }

    @Test
    public void test_getArrayElement_java_object_is_not_array() throws Exception {
        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        G2JavaStubController.ConnectionRegistry registryInfo = mock(G2JavaStubController.ConnectionRegistry.class);
        Item g2proxy = mock(Item.class);
        Object javaObj = mock(Object.class);

        // arrange
        int pos = 0;

        // given
        when(g2JavaStubController, "getConnectionRegistry", g2proxy).thenReturn(registryInfo);
        when(registryInfo.getAssociatedJavaObject(g2proxy)).thenReturn(javaObj);
        expectedException.expect(IllegalArgumentException.class);

        // when
        doCallRealMethod().when(g2JavaStubController, "getArrayElement", g2proxy, pos);
        Whitebox.invokeMethod(g2JavaStubController, "getArrayElement", g2proxy, pos);

        // verify
        verifyPrivate(g2JavaStubController).invoke("getConnectionRegistry", g2proxy);
        verify(registryInfo).getAssociatedJavaObject(g2proxy);
    }

    @Test
    public void test_getArrayElement_java_object_is_null() throws Exception {
        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        G2JavaStubController.ConnectionRegistry registryInfo = mock(G2JavaStubController.ConnectionRegistry.class);
        Item g2proxy = mock(Item.class);
        Object element = mock(Object.class);

        // arrange
        int pos = 0;

        // given
        when(g2JavaStubController, "getConnectionRegistry", g2proxy).thenReturn(registryInfo);
        expectedException.expect(IllegalAccessException.class);

        // when
        doCallRealMethod().when(g2JavaStubController, "getArrayElement", g2proxy, pos);
        Whitebox.invokeMethod(g2JavaStubController, "getArrayElement", g2proxy, pos);

        // verify
        verifyPrivate(g2JavaStubController).invoke("getConnectionRegistry", g2proxy);
        verify(registryInfo).getAssociatedJavaObject(g2proxy);
        verifyPrivate(g2JavaStubController).invoke("resolveG2Stubs", registryInfo, null, element);
    }

    @Test
    public void test_setArrayElement_java_object_is_array() throws Exception {
        // static mock
        mockStatic(Array.class);

        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        G2JavaStubController.ConnectionRegistry registryInfo = mock(G2JavaStubController.ConnectionRegistry.class);
        Item g2proxy = mock(Item.class);
        Object element = mock(Object.class);
        Object elementObj = mock(Object.class);

        // arrange
        int pos = 0;
        Object[] javaobj = {};

        // given
        when(g2JavaStubController, "getConnectionRegistry", g2proxy).thenReturn(registryInfo);
        when(registryInfo.getAssociatedJavaObject(g2proxy)).thenReturn(javaobj);
        when(g2JavaStubController, "resolveG2Stubs", registryInfo, javaobj, element).thenReturn(elementObj);

        // when
        doCallRealMethod().when(g2JavaStubController, "setArrayElement", g2proxy, pos, element);
        Whitebox.invokeMethod(g2JavaStubController, "setArrayElement", g2proxy, pos, element);

        // verify
        verifyPrivate(g2JavaStubController).invoke("getConnectionRegistry", g2proxy);
        verify(registryInfo).getAssociatedJavaObject(g2proxy);
        verifyPrivate(g2JavaStubController).invoke("resolveG2Stubs", registryInfo, javaobj, element);
        verifyStatic();
        Array.set(javaobj, pos, elementObj);
    }

    @Test
    public void test_setArrayElement_java_object_is_not_array() throws Exception {
        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        G2JavaStubController.ConnectionRegistry registryInfo = mock(G2JavaStubController.ConnectionRegistry.class);
        Item g2proxy = mock(Item.class);
        Object element = mock(Object.class);
        Object javaObj = mock(Object.class);

        // arrange
        int pos = 0;

        // given
        when(g2JavaStubController, "getConnectionRegistry", g2proxy).thenReturn(registryInfo);
        when(registryInfo.getAssociatedJavaObject(g2proxy)).thenReturn(javaObj);
        expectedException.expect(IllegalArgumentException.class);

        // when
        doCallRealMethod().when(g2JavaStubController, "setArrayElement", g2proxy, pos, element);
        Whitebox.invokeMethod(g2JavaStubController, "setArrayElement", g2proxy, pos, element);

        // verify
        verifyPrivate(g2JavaStubController).invoke("getConnectionRegistry", g2proxy);
        verify(registryInfo).getAssociatedJavaObject(g2proxy);
        verifyPrivate(g2JavaStubController).invoke("resolveG2Stubs", registryInfo, null, element);
    }

    @Test
    public void test_setArrayElement_java_object_is_null() throws Exception {
        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        G2JavaStubController.ConnectionRegistry registryInfo = mock(G2JavaStubController.ConnectionRegistry.class);
        Item g2proxy = mock(Item.class);
        Object element = mock(Object.class);

        // arrange
        int pos = 0;

        // given
        when(g2JavaStubController, "getConnectionRegistry", g2proxy).thenReturn(registryInfo);
        expectedException.expect(IllegalAccessException.class);

        // when
        doCallRealMethod().when(g2JavaStubController, "setArrayElement", g2proxy, pos, element);
        Whitebox.invokeMethod(g2JavaStubController, "setArrayElement", g2proxy, pos, element);

        // verify
        verifyPrivate(g2JavaStubController).invoke("getConnectionRegistry", g2proxy);
        verify(registryInfo).getAssociatedJavaObject(g2proxy);
        verifyPrivate(g2JavaStubController).invoke("resolveG2Stubs", registryInfo, null, element);
    }


    @Test
    public void test_getArrayContents_java_object_is_array() throws Exception {

        // static mock
        mockStatic(Array.class);

        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        G2JavaStubController.ConnectionRegistry registryInfo = mock(G2JavaStubController.ConnectionRegistry.class);
        Item g2proxy = mock(Item.class);
        Symbol G2_ARRAY_SEQUENCE_ = mock(Symbol.class);
        Sequence retseq = mock(Sequence.class);
        Object arrayElement = mock(Object.class);
        Object resolvedArrayVal = mock(Object.class);
        Object arrayVal = mock(Object.class);

        // arrange
        Object[] javaobj = {};
        Whitebox.setInternalState(G2JavaStubController.class, "G2_ARRAY_SEQUENCE_", G2_ARRAY_SEQUENCE_);
        int length = 1;
        int i = 0;

        // given
        when(g2JavaStubController, "getConnectionRegistry", g2proxy).thenReturn(registryInfo);
        when(registryInfo.getAssociatedJavaObject(g2proxy)).thenReturn(javaobj);
        when(Array.getLength(javaobj)).thenReturn(length);
        whenNew(Sequence.class).withArguments(length).thenReturn(retseq);
        when(Array.get(javaobj, i)).thenReturn(arrayVal);
        when(g2JavaStubController, "resolveJavaObjects", registryInfo, arrayVal).thenReturn(resolvedArrayVal);

        // when
        doCallRealMethod().when(g2JavaStubController, "getArrayContents", g2proxy);
        Whitebox.invokeMethod(g2JavaStubController, "getArrayContents", g2proxy);

        // verify
        verifyPrivate(g2JavaStubController).invoke("getConnectionRegistry", g2proxy);
        verify(registryInfo).getAssociatedJavaObject(g2proxy);
        verifyPrivate(g2JavaStubController).invoke("resolveJavaObjects", registryInfo, arrayVal);
        verifyStatic();
        Array.getLength(javaobj);
        verifyNew(Sequence.class).withArguments(length);
        verifyStatic();
        Array.get(javaobj, i);
        verify(g2proxy).setPropertyValue(G2_ARRAY_SEQUENCE_, retseq);


    }

    @Test
    public void test_getArrayContents_java_object_is_not_array() throws Exception {
        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        G2JavaStubController.ConnectionRegistry registryInfo = mock(G2JavaStubController.ConnectionRegistry.class);
        Item g2proxy = mock(Item.class);
        Object javaobj = mock(Object.class);

        // given
        when(g2JavaStubController, "getConnectionRegistry", g2proxy).thenReturn(registryInfo);
        when(registryInfo.getAssociatedJavaObject(g2proxy)).thenReturn(javaobj);
        expectedException.expect(IllegalArgumentException.class);

        // when
        doCallRealMethod().when(g2JavaStubController, "getArrayContents", g2proxy);
        Whitebox.invokeMethod(g2JavaStubController, "getArrayContents", g2proxy);

        // verify
        verifyPrivate(g2JavaStubController).invoke("getConnectionRegistry", g2proxy);
        verify(registryInfo).getAssociatedJavaObject(g2proxy);
    }

    @Test
    public void test_getArrayContents_java_object_is_null() throws Exception {
        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        G2JavaStubController.ConnectionRegistry registryInfo = mock(G2JavaStubController.ConnectionRegistry.class);
        Item g2proxy = mock(Item.class);

        // given
        when(g2JavaStubController, "getConnectionRegistry", g2proxy).thenReturn(registryInfo);
        expectedException.expect(IllegalAccessException.class);

        // when
        doCallRealMethod().when(g2JavaStubController, "getArrayContents", g2proxy);
        Whitebox.invokeMethod(g2JavaStubController, "getArrayContents", g2proxy);

        // verify
        verifyPrivate(g2JavaStubController).invoke("getConnectionRegistry", g2proxy);
        verify(registryInfo).getAssociatedJavaObject(g2proxy);
    }

    @Test
    public void test_setArrayContents_java_object_is_array() throws Exception {
        // static mock
        mockStatic(Array.class);

        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        G2JavaStubController.ConnectionRegistry registryInfo = mock(G2JavaStubController.ConnectionRegistry.class);
        Item g2proxy = mock(Item.class);
        Symbol G2_ARRAY_SEQUENCE_ = mock(Symbol.class);
        Sequence arraySequence = mock(Sequence.class);
        Object arrayElement = mock(Object.class);
        Object resolvedArrayElement = mock(Object.class);

        // arrange
        Object[] javaobj = {};
        Whitebox.setInternalState(G2JavaStubController.class, "G2_ARRAY_SEQUENCE_", G2_ARRAY_SEQUENCE_);

        // given
        when(g2JavaStubController, "getConnectionRegistry", g2proxy).thenReturn(registryInfo);
        when(registryInfo.getAssociatedJavaObject(g2proxy)).thenReturn(javaobj);
        when(g2proxy.getPropertyValue(G2_ARRAY_SEQUENCE_)).thenReturn(arraySequence);
        when(arraySequence.size()).thenReturn(1);
        when(arraySequence.elementAt(0)).thenReturn(arrayElement);
        when(g2JavaStubController, "resolveG2Stubs", registryInfo, javaobj, arrayElement).thenReturn(resolvedArrayElement);

        // when
        doCallRealMethod().when(g2JavaStubController, "setArrayContents", g2proxy);
        Whitebox.invokeMethod(g2JavaStubController, "setArrayContents", g2proxy);

        // verify
        verifyPrivate(g2JavaStubController).invoke("getConnectionRegistry", g2proxy);
        verify(registryInfo).getAssociatedJavaObject(g2proxy);
        verify(g2proxy).getPropertyValue(G2_ARRAY_SEQUENCE_);
        verify(arraySequence).elementAt(0);
        verifyPrivate(g2JavaStubController).invoke("resolveG2Stubs", registryInfo, javaobj, arrayElement);
        verifyStatic();
        Array.set(javaobj, 0, resolvedArrayElement);

    }

    @Test
    public void test_setArrayContents_java_object_is_not_array() throws Exception {
        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        G2JavaStubController.ConnectionRegistry registryInfo = mock(G2JavaStubController.ConnectionRegistry.class);
        Item g2proxy = mock(Item.class);
        Object javaobj = mock(Object.class);

        // given
        when(g2JavaStubController, "getConnectionRegistry", g2proxy).thenReturn(registryInfo);
        when(registryInfo.getAssociatedJavaObject(g2proxy)).thenReturn(javaobj);
        expectedException.expect(IllegalArgumentException.class);

        // when
        doCallRealMethod().when(g2JavaStubController, "setArrayContents", g2proxy);
        Whitebox.invokeMethod(g2JavaStubController, "setArrayContents", g2proxy);

        // verify
        verifyPrivate(g2JavaStubController).invoke("getConnectionRegistry", g2proxy);
        verify(registryInfo).getAssociatedJavaObject(g2proxy);
    }

    @Test
    public void test_setArrayContents_java_object_is_null() throws Exception {
        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        G2JavaStubController.ConnectionRegistry registryInfo = mock(G2JavaStubController.ConnectionRegistry.class);
        Item g2proxy = mock(Item.class);

        // given
        when(g2JavaStubController, "getConnectionRegistry", g2proxy).thenReturn(registryInfo);
        expectedException.expect(IllegalAccessException.class);

        // when
        doCallRealMethod().when(g2JavaStubController, "setArrayContents", g2proxy);
        Whitebox.invokeMethod(g2JavaStubController, "setArrayContents", g2proxy);

        // verify
        verifyPrivate(g2JavaStubController).invoke("getConnectionRegistry", g2proxy);
        verify(registryInfo).getAssociatedJavaObject(g2proxy);
    }

    @Test
    public void test_processG2JavaStubControllerEvent_call_delete_instance() throws Exception {
        // static mock
        mockStatic(G2JavaStubControllerEvent.class);

        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        G2JavaStubControllerEvent e = mock(G2JavaStubControllerEvent.class);

        // arrange
        int CALL_ASYNC_METHOD = 0;
        Whitebox.setInternalState(G2JavaStubControllerEvent.class, "CALL_ASYNC_METHOD", CALL_ASYNC_METHOD);

        int DELETE_INSTANCE = 1;
        Whitebox.setInternalState(G2JavaStubControllerEvent.class, "DELETE_INSTANCE", DELETE_INSTANCE);

        // given
        when(e.getID()).thenReturn(DELETE_INSTANCE);

        // when
        doCallRealMethod().when(g2JavaStubController).processG2JavaStubControllerEvent(e);
        g2JavaStubController.processG2JavaStubControllerEvent(e);

        // verify
        verify(g2JavaStubController).deleteInstance(e.getTarget());

    }

    @Test
    public void test_processG2JavaStubControllerEvent_call_async_method() throws Exception {
        // static mock
        mockStatic(G2JavaStubControllerEvent.class);

        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        G2JavaStubControllerEvent e = mock(G2JavaStubControllerEvent.class);

        // arrange
        int CALL_ASYNC_METHOD = 0;
        Whitebox.setInternalState(G2JavaStubControllerEvent.class, "CALL_ASYNC_METHOD", CALL_ASYNC_METHOD);

        int DELETE_INSTANCE = 1;
        Whitebox.setInternalState(G2JavaStubControllerEvent.class, "DELETE_INSTANCE", DELETE_INSTANCE);


        // given
        when(e.getID()).thenReturn(CALL_ASYNC_METHOD);

        // when
        doCallRealMethod().when(g2JavaStubController).processG2JavaStubControllerEvent(e);
        g2JavaStubController.processG2JavaStubControllerEvent(e);

        // verify
        verify(g2JavaStubController).callMethod(e.getTarget(), e.getMethodName(), e.getArgs());

    }

    @Test
    public void test_callG2ProxyFromJava_with_param_array() throws Exception {
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        G2Connection context = mock(G2Connection.class);
        Symbol methodName = mock(Symbol.class);
        Object javaParam = mock(Object.class);
        Object resolvedObject = mock(Object.class);
        G2JavaStubController.ConnectionRegistry registryInfo = mock(G2JavaStubController.ConnectionRegistry.class);
        Object resolvedJavaParam = mock(Object.class);
        Object ret = mock(Object.class);

        // arrange
        Object[] javaParams = {javaParam};
        Object[] resolvedJavaParamArray = {resolvedJavaParam};

        // given
        when(g2JavaStubController, "getConnectionRegistry", context).thenReturn(registryInfo);
        when(g2JavaStubController, "resolveJavaObjectsInObjectArray", registryInfo, javaParams).thenReturn(resolvedJavaParamArray);
        when(context.callRPC(methodName, resolvedJavaParamArray)).thenReturn(ret);
        when(g2JavaStubController, "resolveG2Stubs", registryInfo, javaParam, ret).thenReturn(resolvedObject);

        // when
        when(g2JavaStubController.callG2ProxyFromJava(context, methodName, javaParams)).thenCallRealMethod();
        Object result = g2JavaStubController.callG2ProxyFromJava(context, methodName, javaParams);

        // assertions
        Assertions.assertThat(result).isSameAs(resolvedObject);

        // verify
        verifyPrivate(g2JavaStubController).invoke("getConnectionRegistry", context);
        verifyPrivate(g2JavaStubController).invoke("resolveJavaObjectsInObjectArray", registryInfo, javaParams);
        verify(context).callRPC(methodName, resolvedJavaParamArray);
        verifyPrivate(g2JavaStubController).invoke("resolveG2Stubs", registryInfo, javaParam, ret);

    }

    @Test
    public void test_resolveG2Stub_item() throws Exception {
        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        Item g2Object = mock(Item.class);
        G2JavaStubController.ConnectionRegistry registryInfo = mock(G2JavaStubController.ConnectionRegistry.class);
        Object resolvedObject = mock(Object.class);

        // given
        when(g2JavaStubController, "getConnectionRegistry", g2Object).thenReturn(registryInfo);
        when(g2JavaStubController,"resolveG2ItemStub", registryInfo, null, g2Object).thenReturn(resolvedObject);

        // when
        when(g2JavaStubController.resolveG2Stub(g2Object)).thenCallRealMethod();
        Object result = g2JavaStubController.resolveG2Stub(g2Object);

        // assertion
        Assertions.assertThat(result).isSameAs(resolvedObject);

        // verify
        verifyPrivate(g2JavaStubController).invoke("getConnectionRegistry", g2Object);
        verifyPrivate(g2JavaStubController).invoke("resolveG2ItemStub", registryInfo, null, g2Object);

    }

    @Test
    public void test_resolveG2Stubs_connection() throws Exception{
        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        G2Connection connection = mock(G2Connection.class);
        Object targetObj = mock(Object.class);
        Object obj = mock(Object.class);
        G2JavaStubController.ConnectionRegistry registryInfo = mock(G2JavaStubController.ConnectionRegistry.class);
        Object resolvedObject = mock(Object.class);

        // given
        when(g2JavaStubController, "getConnectionRegistry", connection).thenReturn(registryInfo);
        when(g2JavaStubController,"resolveG2Stubs", registryInfo, targetObj, obj).thenReturn(resolvedObject);

        // when
        when(g2JavaStubController.resolveG2Stubs(connection, targetObj, obj)).thenCallRealMethod();
        Object result = g2JavaStubController.resolveG2Stubs(connection, targetObj, obj);

        // assertion
        Assertions.assertThat(result).isSameAs(resolvedObject);

        // verify
        verifyPrivate(g2JavaStubController).invoke("getConnectionRegistry", connection);
        verifyPrivate(g2JavaStubController).invoke("resolveG2Stubs", registryInfo, targetObj, obj);

    }

    @Test
    public void test_resolveG2Stubs_object() throws Exception {
        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        G2JavaStubController.ConnectionRegistry registryInfo = mock(G2JavaStubController.ConnectionRegistry.class);
        Object targetObj = mock(Object.class);
        Object mockO = mock(Object.class);
        Object o = mock(Object.class);

        // when
        when(g2JavaStubController, "resolveG2Stubs", registryInfo, targetObj, o).thenCallRealMethod();
        Object result = Whitebox.invokeMethod(g2JavaStubController, "resolveG2Stubs", registryInfo, targetObj, o);

        // assert
        Assertions.assertThat(result).isSameAs(o);

    }

    @Test
    public void test_resolveG2Stubs_object_array() throws Exception {
        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        G2JavaStubController.ConnectionRegistry registryInfo = mock(G2JavaStubController.ConnectionRegistry.class);
        Object targetObj = mock(Object.class);
        Object mockO = mock(Object.class);
        Object[] o = {mockO};
        Object mockResolvedObject = mock(Object.class);
        Object[] resolvedObject = {mockResolvedObject};

        // given
        when(g2JavaStubController, "resolveG2StubsInObjectArray", registryInfo, targetObj, o).thenReturn(resolvedObject);

        // when
        when(g2JavaStubController, "resolveG2Stubs", registryInfo, targetObj, o).thenCallRealMethod();
        Object result = Whitebox.invokeMethod(g2JavaStubController, "resolveG2Stubs", registryInfo, targetObj, o);

        // assert
        Assertions.assertThat(result).isSameAs(resolvedObject);

        // verify
        verifyPrivate(g2JavaStubController).invoke("resolveG2StubsInObjectArray", registryInfo, targetObj, o);
    }

    @Test
    public void test_resolveG2Stubs_structure() throws Exception {
        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        G2JavaStubController.ConnectionRegistry registryInfo = mock(G2JavaStubController.ConnectionRegistry.class);
        Object targetObj = mock(Object.class);
        Structure o = mock(Structure.class);
        Structure resolvedObject = mock(Structure.class);

        // given
        when(g2JavaStubController, "resolveG2StubsInStructure", registryInfo, targetObj, o).thenReturn(resolvedObject);

        // when
        when(g2JavaStubController, "resolveG2Stubs", registryInfo, targetObj, o).thenCallRealMethod();
        Object result = Whitebox.invokeMethod(g2JavaStubController, "resolveG2Stubs", registryInfo, targetObj, o);

        // assert
        Assertions.assertThat(result).isSameAs(resolvedObject);

        // verify
        verifyPrivate(g2JavaStubController).invoke("resolveG2StubsInStructure", registryInfo, targetObj, o);
    }

    @Test
    public void test_resolveG2Stubs_sequance() throws Exception {
        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        G2JavaStubController.ConnectionRegistry registryInfo = mock(G2JavaStubController.ConnectionRegistry.class);
        Object targetObj = mock(Object.class);
        Sequence o = mock(Sequence.class);
        Sequence resolvedObject = mock(Sequence.class);

        // given
        when(g2JavaStubController, "resolveG2StubsInSequence", registryInfo, targetObj, o).thenReturn(resolvedObject);

        // when
        when(g2JavaStubController, "resolveG2Stubs", registryInfo, targetObj, o).thenCallRealMethod();
        Object result = Whitebox.invokeMethod(g2JavaStubController, "resolveG2Stubs", registryInfo, targetObj, o);

        // assert
        Assertions.assertThat(result).isSameAs(resolvedObject);

        // verify
        verifyPrivate(g2JavaStubController).invoke("resolveG2StubsInSequence", registryInfo, targetObj, o);
    }

    @Test
    public void test_resolveG2Stubs_item() throws Exception {
        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        G2JavaStubController.ConnectionRegistry registryInfo = mock(G2JavaStubController.ConnectionRegistry.class);
        Object targetObj = mock(Object.class);
        Item o = mock(Item.class);
        Object resolvedObject = mock(Object.class);

        // given
        when(g2JavaStubController, "resolveG2ItemStub", registryInfo, targetObj, o).thenReturn(resolvedObject);

        // when
        when(g2JavaStubController, "resolveG2Stubs", registryInfo, targetObj, o).thenCallRealMethod();
        Object result = Whitebox.invokeMethod(g2JavaStubController, "resolveG2Stubs", registryInfo, targetObj, o);

        // assert
        Assertions.assertThat(result).isSameAs(resolvedObject);

        // verify
        verifyPrivate(g2JavaStubController).invoke("resolveG2Stubs", registryInfo, targetObj, o);
    }

    @Test
    public void test_resolveG2Stubs_null_object() throws Exception {
        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        G2JavaStubController.ConnectionRegistry registryInfo = mock(G2JavaStubController.ConnectionRegistry.class);
        Object targetObj = mock(Object.class);
        Object o = null;

        // when
        when(g2JavaStubController, "resolveG2Stubs", registryInfo, targetObj, o).thenCallRealMethod();
        Object result = Whitebox.invokeMethod(g2JavaStubController, "resolveG2Stubs", registryInfo, targetObj, o);

        // assert
        Assertions.assertThat(result).isNull();

    }

    @Test
    public void test_resolveG2ItemStub_not_g2_class_no_g2_access() throws Exception {
        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        G2JavaStubController.ConnectionRegistry registryInfo = mock(G2JavaStubController.ConnectionRegistry.class);
        Object targetObj = new Object();
        Item g2item = mock(Item.class);
        Symbol CLASS_ = mock(Symbol.class);
        Symbol g2ClassName = mock(Symbol.class);

        // arrange
        Whitebox.setInternalState(G2JavaStubController.class, "CLASS_",CLASS_);

        //given
        when(g2item.getPropertyValue(CLASS_)).thenThrow(G2AccessException.class);
        when(registryInfo.getJavaClassForG2Class(null)).thenReturn(null);


        // when
        when(g2JavaStubController, "resolveG2ItemStub", registryInfo, targetObj, g2item).thenCallRealMethod();
        Object result = Whitebox.invokeMethod(g2JavaStubController, "resolveG2ItemStub", registryInfo, targetObj, g2item);

        // assertions
        Assertions.assertThat(result).isSameAs(g2item);

        // verify
        verify(g2item).getPropertyValue(CLASS_);
        verify(registryInfo).getAssociatedJavaObject(targetObj, g2item);
        verify(registryInfo).getJavaClassForG2Class(null);

    }


    @Test
    public void test_resolveG2ItemStub_not_g2_class_property_value_not_found() throws Exception {
        // mocks

        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        G2JavaStubController.ConnectionRegistry registryInfo = mock(G2JavaStubController.ConnectionRegistry.class);
        Object targetObj = new Object();
        Item g2item = mock(Item.class);
        Symbol CLASS_ = mock(Symbol.class);
        Symbol g2ClassName = mock(Symbol.class);

        // arrange
        Whitebox.setInternalState(G2JavaStubController.class, "CLASS_",CLASS_);

        //given
        when(g2item.getPropertyValue(CLASS_)).thenThrow(NoSuchAttributeException.class);
        when(registryInfo.getJavaClassForG2Class(null)).thenReturn(null);


        // when
        when(g2JavaStubController, "resolveG2ItemStub", registryInfo, targetObj, g2item).thenCallRealMethod();
        Object result = Whitebox.invokeMethod(g2JavaStubController, "resolveG2ItemStub", registryInfo, targetObj, g2item);

        // assertions
        Assertions.assertThat(result).isSameAs(g2item);

        // verify
        verify(g2item).getPropertyValue(CLASS_);
        verify(registryInfo).getAssociatedJavaObject(targetObj, g2item);
        verify(registryInfo).getJavaClassForG2Class(null);

    }

    @Test
    public void test_resolveG2ItemStub_not_g2_class_associated_with_java_object() throws Exception {
        // mocks

        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        G2JavaStubController.ConnectionRegistry registryInfo = mock(G2JavaStubController.ConnectionRegistry.class);
        Object targetObj = new Object();
        Item g2item = mock(Item.class);
        Symbol CLASS_ = mock(Symbol.class);
        Symbol g2ClassName = mock(Symbol.class);

        // arrange
        String javaClass = "testClass";
        Whitebox.setInternalState(G2JavaStubController.class, "CLASS_",CLASS_);

        //given
        when(g2item.getPropertyValue(CLASS_)).thenReturn(g2ClassName);
        when(registryInfo.getJavaClassForG2Class(g2ClassName)).thenReturn(javaClass);
        expectedException.expectMessage("Can find associated Java Object for " +
                g2item + "whose G2 Class was registered for Java Class " + javaClass);
        expectedException.expect(RuntimeException.class);

        // when
        when(g2JavaStubController, "resolveG2ItemStub", registryInfo, targetObj, g2item).thenCallRealMethod();
        Whitebox.invokeMethod(g2JavaStubController, "resolveG2ItemStub", registryInfo, targetObj, g2item);

        // verify
        verify(g2item).getPropertyValue(CLASS_);
        verify(registryInfo).getAssociatedJavaObject(targetObj, g2item);
        verify(registryInfo).getJavaClassForG2Class(g2ClassName);

    }

    @Test
    public void test_resolveG2ItemStub_not_g2_class_resolved() throws Exception {
        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        G2JavaStubController.ConnectionRegistry registryInfo = mock(G2JavaStubController.ConnectionRegistry.class);
        Object targetObj = new Object();
        Item g2item = mock(Item.class);
        Symbol CLASS_ = mock(Symbol.class);
        Symbol g2ClassName = mock(Symbol.class);
        Object java_object = mock(Object.class);

        // arrange
        Whitebox.setInternalState(G2JavaStubController.class, "CLASS_",CLASS_);

        //given
        when(g2item.getPropertyValue(CLASS_)).thenReturn(g2ClassName);
        when(registryInfo.getAssociatedJavaObject(targetObj, g2item)).thenReturn(java_object);

        // when
        when(g2JavaStubController, "resolveG2ItemStub", registryInfo, targetObj, g2item).thenCallRealMethod();
        Object result = Whitebox.invokeMethod(g2JavaStubController, "resolveG2ItemStub", registryInfo, targetObj, g2item);

        // assert
        Assertions.assertThat(result).isSameAs(java_object);

        // verify
        verify(g2item).getPropertyValue(CLASS_);
        verify(registryInfo).getAssociatedJavaObject(targetObj, g2item);

    }

    @Test
    public void test_resolveG2ItemStub_not_g2_class_cant_be_resolve() throws Exception {
        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        G2JavaStubController.ConnectionRegistry registryInfo = mock(G2JavaStubController.ConnectionRegistry.class);
        Object targetObj = new Object();
        Item g2item = mock(Item.class);
        Symbol CLASS_ = mock(Symbol.class);
        Symbol g2ClassName = mock(Symbol.class);

        // arrange
        Whitebox.setInternalState(G2JavaStubController.class, "CLASS_",CLASS_);

        //given
        when(g2item.getPropertyValue(CLASS_)).thenReturn(g2ClassName);

        // when
        when(g2JavaStubController, "resolveG2ItemStub", registryInfo, targetObj, g2item).thenCallRealMethod();
        Object result = Whitebox.invokeMethod(g2JavaStubController, "resolveG2ItemStub", registryInfo, targetObj, g2item);

        // assert
        Assertions.assertThat(result).isSameAs(g2item);

        // verify
        verify(g2item).getPropertyValue(CLASS_);
        verify(registryInfo).getAssociatedJavaObject(targetObj, g2item);
        verify(registryInfo).getJavaClassForG2Class(g2ClassName);

    }

    @Test
    public void test_resolveG2ItemStub_g2_event_object_cant_access() throws Exception {
        // static mocks
        mockStatic(G2_ExternalEventObjectRoot.class);

        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        G2JavaStubController.ConnectionRegistry registryInfo = mock(G2JavaStubController.ConnectionRegistry.class);
        Object targetObj = new Object();
        G2EventObjectImpl g2item = mock(G2EventObjectImpl.class);
        G2_ExternalEventObjectRoot event = mock(G2_ExternalEventObjectRoot.class);
        Class evenClass = Object.class;

        //given
        when(g2item.getExternalEventClass()).thenReturn(evenClass);
        when(G2_ExternalEventObjectRoot.createExternalEventObject(null, g2item, evenClass)).thenThrow(G2AccessException.class);
        expectedException.expect(RuntimeException.class);

        // when
        when(g2JavaStubController, "resolveG2ItemStub", registryInfo, targetObj, g2item).thenCallRealMethod();
        Object result = Whitebox.invokeMethod(g2JavaStubController, "resolveG2ItemStub", registryInfo, targetObj, g2item);

        // assert
        Assertions.assertThat(result).isSameAs(event);

        // verify
        verifyStatic();
        G2_ExternalEventObjectRoot.createExternalEventObject(null, g2item, evenClass);


    }

    @Test
    public void test_resolveG2ItemStub_g2_event_object() throws Exception {
        // static mocks
        mockStatic(G2_ExternalEventObjectRoot.class);

        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        G2JavaStubController.ConnectionRegistry registryInfo = mock(G2JavaStubController.ConnectionRegistry.class);
        Object targetObj = new Object();
        G2EventObjectImpl g2item = mock(G2EventObjectImpl.class);
        G2_ExternalEventObjectRoot event = mock(G2_ExternalEventObjectRoot.class);
        Class evenClass = Object.class;

        //given
        when(g2item.getExternalEventClass()).thenReturn(evenClass);
        when(G2_ExternalEventObjectRoot.createExternalEventObject(null, g2item, evenClass)).thenReturn(event);

        // when
        when(g2JavaStubController, "resolveG2ItemStub", registryInfo, targetObj, g2item).thenCallRealMethod();
        Object result = Whitebox.invokeMethod(g2JavaStubController, "resolveG2ItemStub", registryInfo, targetObj, g2item);

        // assert
        Assertions.assertThat(result).isSameAs(event);

        // verify
        verifyStatic();
        G2_ExternalEventObjectRoot.createExternalEventObject(null, g2item, evenClass);


    }

    @Test
    public void test_resolveJavaObjectsInSequence_sequence_is_not_empty() throws Exception {
        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        G2JavaStubController.ConnectionRegistry registryInfo = mock(G2JavaStubController.ConnectionRegistry.class);
        Sequence s = mock(Sequence.class);
        Object o = mock(Object.class);
        Object resolvedObject = mock(Object.class);

        // given
        when(s.isEmpty()).thenReturn(false);
        when(s.size()).thenReturn(1);
        when(s.elementAt(0)).thenReturn(o);
        when(g2JavaStubController, "resolveJavaObjects", registryInfo, o).thenReturn(resolvedObject);

        // when
        when(g2JavaStubController, "resolveJavaObjectsInSequence", registryInfo, s).thenCallRealMethod();
        Sequence result = Whitebox.invokeMethod(g2JavaStubController, "resolveJavaObjectsInSequence", registryInfo, s);

        // assert
        Assertions.assertThat(result).isSameAs(s);

        // verify
        verify(s).isEmpty();
        verify(s).elementAt(0);

        verify(s).setElementAt(resolvedObject,0);


    }

    @Test
    public void test_resolveJavaObjectsInSequence_sequence_is_empty() throws Exception {
        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        G2JavaStubController.ConnectionRegistry registryInfo = mock(G2JavaStubController.ConnectionRegistry.class);
        Sequence s = mock(Sequence.class);

        // given
        when(s.isEmpty()).thenReturn(true);

        // when
        when(g2JavaStubController, "resolveJavaObjectsInSequence", registryInfo, s).thenCallRealMethod();
        Sequence result = Whitebox.invokeMethod(g2JavaStubController, "resolveJavaObjectsInSequence", registryInfo, s);

        // assert
        Assertions.assertThat(result).isSameAs(s);

        // verify
        verify(s).isEmpty();

    }

    @Test
    public void test_resolveJavaObjectsInObjectArray_() throws  Exception {
        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        G2JavaStubController.ConnectionRegistry registryInfo = mock(G2JavaStubController.ConnectionRegistry.class);
        Object oarrayObject = mock(Object.class);
        Object resolvedObject = mock(Object.class);

        // arrange
        Object[] expectedResult = {resolvedObject};
        Object[] oarray = {oarrayObject};

        // given
        when(g2JavaStubController, "resolveJavaObjects", registryInfo, oarray[0]).thenReturn(resolvedObject);

        // when
        when(g2JavaStubController, "resolveJavaObjectsInObjectArray", registryInfo, oarray).thenCallRealMethod();
        Object[] result = Whitebox.invokeMethod(g2JavaStubController, "resolveJavaObjectsInObjectArray", registryInfo, oarray);

        // assert
        Assertions.assertThat(result).isEqualTo(expectedResult);

        // verify
        verifyPrivate(g2JavaStubController).invoke("resolveJavaObjects", registryInfo, oarrayObject);

    }

    @Test(expected = G2AccessException.class)
    public void test_getArgClassesAndResolve_item_attribute_not_exist() throws  Exception {

        // static mocks
        mockStatic(G2JavaStubController.class);
        mockStatic(G2JavaStubController.ConnectionRegistry.class);
        mockStatic(G2ClassTranslator.class);


        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        Symbol CLASS_ = mock(Symbol.class);
        Object targetObj = mock(Object.class);
        G2JavaStubController.ConnectionRegistry registryInfo = mock(G2JavaStubController.ConnectionRegistry.class);
        Sequence args = spy(new Sequence(1));
        Item arg = mock(Item.class);
        Object newarg = mock(Object.class);

        // arrange
        Whitebox.setInternalState(G2JavaStubController.class, "CLASS_",CLASS_);
        args.add(arg);

        // given
        when(g2JavaStubController, "resolveG2Stubs", registryInfo, targetObj, arg).thenReturn(newarg);
        when(arg.getPropertyValue(CLASS_)).thenThrow(NoSuchAttributeException.class);

        // when
        when(g2JavaStubController, "getArgClassesAndResolve", registryInfo, targetObj, args).thenCallRealMethod();
        Whitebox.invokeMethod(g2JavaStubController, "getArgClassesAndResolve", registryInfo, targetObj, args);
    }


    @Test
    public void test_getArgClassesAndResolve_primative_args_not_item() throws  Exception {

        // static mocks
        mockStatic(G2JavaStubController.class);
        mockStatic(G2JavaStubController.ConnectionRegistry.class);
        mockStatic(G2ClassTranslator.class);

        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        Symbol CLASS_ = mock(Symbol.class);
        Object targetObj = mock(Object.class);
        G2JavaStubController.ConnectionRegistry registryInfo = mock(G2JavaStubController.ConnectionRegistry.class);
        Sequence args = spy(new Sequence(1));
        Object arg = mock(Object.class);
        Object newarg = mock(Object.class);
        Class newParamClass = Object.class;

        // arrange
        args.add(arg);
        Class[] expectedClasses = {newParamClass};

        // given
        when(g2JavaStubController, "resolveG2Stubs", registryInfo, targetObj, arg).thenReturn(newarg);
        when(G2ClassTranslator.getJavaTypeForG2WrappedPrimitive(arg.getClass())).thenReturn(newParamClass);

        // when
        when(g2JavaStubController, "getArgClassesAndResolve", registryInfo, targetObj, args).thenCallRealMethod();
        Class[] result = Whitebox.invokeMethod(g2JavaStubController, "getArgClassesAndResolve", registryInfo, targetObj, args);

        // assert
        Assertions.assertThat(result).isEqualTo(expectedClasses);

        // verify
        verify(args).elementAt(0);
        verifyStatic();
        G2ClassTranslator.getJavaTypeForG2WrappedPrimitive(arg.getClass());
    }


    @Test
    public void test_getArgClassesAndResolve_primative_args_item() throws  Exception {

        // static mocks
        mockStatic(G2JavaStubController.class);
        mockStatic(G2JavaStubController.ConnectionRegistry.class);
        mockStatic(G2ClassTranslator.class);


        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        Symbol CLASS_ = mock(Symbol.class);
        Object targetObj = mock(Object.class);
        G2JavaStubController.ConnectionRegistry registryInfo = mock(G2JavaStubController.ConnectionRegistry.class);
        Sequence args = spy(new Sequence(1));
        Item arg = mock(Item.class);
        Object newarg = mock(Object.class);
        Symbol g2ClassName = mock(Symbol.class);
        Class newParamClass = Object.class;

        // arrange
        Whitebox.setInternalState(G2JavaStubController.class, "CLASS_",CLASS_);
        args.add(arg);
        Class[] expectedClasses = {newParamClass};

        // given
        when(g2JavaStubController, "resolveG2Stubs", registryInfo, targetObj, arg).thenReturn(newarg);
        when(arg.getPropertyValue(CLASS_)).thenReturn(g2ClassName);
        when(G2ClassTranslator.getJavaTypeForG2Class(g2ClassName)).thenReturn(newParamClass);

        // when
        when(g2JavaStubController, "getArgClassesAndResolve", registryInfo, targetObj, args).thenCallRealMethod();
        Class[] result = Whitebox.invokeMethod(g2JavaStubController, "getArgClassesAndResolve", registryInfo, targetObj, args);

        // assert
        Assertions.assertThat(result).isEqualTo(expectedClasses);

        // verify
        verify(args).elementAt(0);
        verify(arg).getPropertyValue(CLASS_);
        verifyStatic();
        G2ClassTranslator.getJavaTypeForG2Class(g2ClassName);
        verifyPrivate(g2JavaStubController).invoke("resolveG2Stubs", registryInfo, targetObj, arg);
    }


    @Test
    public void test_getArgClassesAndResolve_args_is_not_item() throws  Exception {

        // static mocks
        mockStatic(G2JavaStubController.class);
        mockStatic(G2JavaStubController.ConnectionRegistry.class);
        mockStatic(G2ClassTranslator.class);


        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        Object targetObj = mock(Object.class);
        G2JavaStubController.ConnectionRegistry registryInfo = mock(G2JavaStubController.ConnectionRegistry.class);
        Sequence args = spy(new Sequence(1));
        Object arg = mock(Object.class);
        Object newarg = mock(Object.class);

        // arrange
        args.add(arg);
        Class[] expectedClasses = {newarg.getClass()};

        // given
        when(g2JavaStubController, "resolveG2Stubs", registryInfo, targetObj, arg).thenReturn(newarg);

        // when
        when(g2JavaStubController, "getArgClassesAndResolve", registryInfo, targetObj, args).thenCallRealMethod();
        Class[] result = Whitebox.invokeMethod(g2JavaStubController, "getArgClassesAndResolve", registryInfo, targetObj, args);

        // assert
        Assertions.assertThat(result).isEqualTo(expectedClasses);

        // verify
        verify(args).elementAt(0);
        verifyStatic();
        G2ClassTranslator.getJavaTypeForG2WrappedPrimitive(arg.getClass());
    }


    @Test
    public void test_getArgClassesAndResolve_item_args() throws  Exception {

        // static mocks
        mockStatic(G2JavaStubController.class);
        mockStatic(G2JavaStubController.ConnectionRegistry.class);
        mockStatic(G2ClassTranslator.class);


        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        Symbol CLASS_ = mock(Symbol.class);
        Object targetObj = mock(Object.class);
        G2JavaStubController.ConnectionRegistry registryInfo = mock(G2JavaStubController.ConnectionRegistry.class);
        Sequence args = spy(new Sequence(1));
        Item arg = mock(Item.class);
        Object newarg = mock(Object.class);

        // arrange
        Whitebox.setInternalState(G2JavaStubController.class, "CLASS_",CLASS_);
        args.add(arg);
        Class[] expectedClasses = {newarg.getClass()};

        // given
        when(g2JavaStubController, "resolveG2Stubs", registryInfo, targetObj, arg).thenReturn(newarg);

        // when
        when(g2JavaStubController, "getArgClassesAndResolve", registryInfo, targetObj, args).thenCallRealMethod();
        Class[] result = Whitebox.invokeMethod(g2JavaStubController, "getArgClassesAndResolve", registryInfo, targetObj, args);

        // assert
        Assertions.assertThat(result).isEqualTo(expectedClasses);

        // verify
        verify(args).elementAt(0);
        verify(arg).getPropertyValue(CLASS_);
        verifyStatic();
        G2ClassTranslator.getJavaTypeForG2Class(null);
        verifyPrivate(g2JavaStubController).invoke("resolveG2Stubs", registryInfo, targetObj, arg);
        verify(args).setElementAt(newarg,0);
    }

    @Test
    public void test_g2ConnectionClosed_close_connection() throws Exception {
        // mocks
        mockStatic(G2JavaStubController.class);
        mockStatic(G2JavaStubController.ConnectionRegistry.class);

        G2JavaStubController.ConnectionRegistry connectionRegistry = mock(G2JavaStubController.ConnectionRegistry.class);
        G2ConnectionEvent e = mock(G2ConnectionEvent.class);
        G2Access g2connection = mock(G2Access.class);
        Hashtable controlledJavaObjects = mock(Hashtable.class);
        Hashtable associatedG2Proxies = mock(Hashtable.class);
        Hashtable registeredMethodTables = mock(Hashtable.class);

        // arrange
        Whitebox.setInternalState(connectionRegistry, "g2connection", g2connection);
        Whitebox.setInternalState(connectionRegistry, "controlledJavaObjects", controlledJavaObjects);
        Whitebox.setInternalState(connectionRegistry, "associatedG2Proxies", associatedG2Proxies);
        Whitebox.setInternalState(connectionRegistry, "registeredMethodTables", registeredMethodTables);

        // when
        doCallRealMethod().when(connectionRegistry).g2ConnectionClosed(e);
        connectionRegistry.g2ConnectionClosed(e);

        // assert
        Assertions.assertThat(Whitebox.getInternalState(connectionRegistry, "g2connection")).isNull();

        // verify
        verify(controlledJavaObjects).clear();
        verify(associatedG2Proxies).clear();
        verify(registeredMethodTables).clear();

    }

    @Test
    public void test_getG2ClassForJavaObject_java_object_is_null() throws Exception {
        // mocks
        mockStatic(G2JavaStubController.ConnectionRegistry.class);
        G2JavaStubController.ConnectionRegistry connectionRegistry = mock(G2JavaStubController.ConnectionRegistry.class);
        Object java_object = null;

        // when
        when(connectionRegistry, "getG2ClassForJavaObject", java_object).thenCallRealMethod();
        Symbol result = Whitebox.invokeMethod(connectionRegistry, "getG2ClassForJavaObject", java_object);

        // assert
        Assertions.assertThat(result).isNull();

    }

    @Test
    public void test_getJavaClassForG2Class_() throws  Exception{
        // mocks
        mockStatic(G2JavaStubController.ConnectionRegistry.class);
        G2JavaStubController.ConnectionRegistry connectionRegistry = mock(G2JavaStubController.ConnectionRegistry.class);
        Hashtable registeredJavaClasses = mock(Hashtable.class);
        Symbol g2ClassName = mock(Symbol.class);
        String g2ClassNameStr = "test";

        // arrange
        Whitebox.setInternalState(connectionRegistry, "registeredJavaClasses", registeredJavaClasses);

        // given
        when(registeredJavaClasses.get(g2ClassName)).thenReturn(g2ClassNameStr);

        // when
        when(connectionRegistry, "getJavaClassForG2Class", g2ClassName).thenCallRealMethod();
        String result = Whitebox.invokeMethod(connectionRegistry, "getJavaClassForG2Class", g2ClassName);

        // assert
        Assertions.assertThat(result).isEqualTo(g2ClassNameStr);

        // verify
        verify(registeredJavaClasses).get(g2ClassName);
    }

    @Test
    public void test_removeAssociation_object_with_multicasters() throws Exception {

        // mocks
        mockStatic(G2JavaStubController.ConnectionRegistry.class);
        G2JavaStubController.ConnectionRegistry connectionRegistry = mock(G2JavaStubController.ConnectionRegistry.class);
        Hashtable  associatedG2ProxyMultiCasters = mock(Hashtable.class);
        Hashtable proxyMultiCasterHash = mock(Hashtable.class);
        Hashtable controlledJavaObjects = mock(Hashtable.class);
        Hashtable associatedG2Proxies = mock(Hashtable.class);

        Item g2Proxy = mock(Item.class);
        G2JavaStubController.LocalMultiCaster java_object = mock(G2JavaStubController.LocalMultiCaster.class);

        // arrange
        Whitebox.setInternalState(connectionRegistry, "associatedG2ProxyMultiCasters", associatedG2ProxyMultiCasters);
        Whitebox.setInternalState(connectionRegistry, "controlledJavaObjects", controlledJavaObjects);
        Whitebox.setInternalState(connectionRegistry, "associatedG2Proxies", associatedG2Proxies);

        // given
        when(associatedG2ProxyMultiCasters.remove(g2Proxy)).thenReturn(proxyMultiCasterHash);
        when(controlledJavaObjects.remove(g2Proxy)).thenReturn(java_object);

        // when
        doCallRealMethod().when(connectionRegistry, "removeAssociation", g2Proxy);
        Object result =Whitebox.invokeMethod(connectionRegistry, "removeAssociation", g2Proxy);

        // assert
        Assertions.assertThat(result).isSameAs(java_object);

        // verify
        verify(associatedG2ProxyMultiCasters).remove(g2Proxy);
        verify(proxyMultiCasterHash).clear();
        verify(controlledJavaObjects).remove(g2Proxy);
        verify(java_object).disable();
        verify(associatedG2Proxies).remove(java_object);

    }

    @Test
    public void test_getMultiCaster_when_no_multi_caster() throws Exception {
        // mocks
        mockStatic(G2JavaStubController.ConnectionRegistry.class);
        G2JavaStubController.ConnectionRegistry connectionRegistry = mock(G2JavaStubController.ConnectionRegistry.class);
        Hashtable  associatedG2ProxyMultiCasters = mock(Hashtable.class);
        Hashtable proxyMultiCasterHash = null;
        Item g2Proxy = mock(Item.class);
        Symbol g2ClassName = mock(Symbol.class);

        // arrange
        Whitebox.setInternalState(connectionRegistry, "associatedG2ProxyMultiCasters", associatedG2ProxyMultiCasters);

        // given
        when(associatedG2ProxyMultiCasters.get(g2Proxy)).thenReturn(proxyMultiCasterHash);

        // when
        doCallRealMethod().when(connectionRegistry, "getMultiCaster", g2Proxy, g2ClassName);
        G2JavaStubController.LocalMultiCaster result =Whitebox.invokeMethod(connectionRegistry, "getMultiCaster", g2Proxy, g2ClassName);

        // assert
        Assertions.assertThat(result).isNull();

        // verify
        verify(associatedG2ProxyMultiCasters).get(g2Proxy);
    }

    @Test
    public void test_getMultiCaster_when_multi_caster() throws Exception {
        // mocks
        mockStatic(G2JavaStubController.ConnectionRegistry.class);
        G2JavaStubController.ConnectionRegistry connectionRegistry = mock(G2JavaStubController.ConnectionRegistry.class);
        Hashtable  associatedG2ProxyMultiCasters = mock(Hashtable.class);
        Hashtable proxyMultiCasterHash = mock(Hashtable.class);
        Item g2Proxy = mock(Item.class);
        Symbol g2ClassName = mock(Symbol.class);
        G2JavaStubController.LocalMultiCaster classMultiCaster = mock(G2JavaStubController.LocalMultiCaster.class);

        // arrange
        Whitebox.setInternalState(connectionRegistry, "associatedG2ProxyMultiCasters", associatedG2ProxyMultiCasters);

        // given
        when(associatedG2ProxyMultiCasters.get(g2Proxy)).thenReturn(proxyMultiCasterHash);
        when(proxyMultiCasterHash.get(g2ClassName)).thenReturn(classMultiCaster);

        // when
        doCallRealMethod().when(connectionRegistry, "getMultiCaster", g2Proxy, g2ClassName);
        G2JavaStubController.LocalMultiCaster result =Whitebox.invokeMethod(connectionRegistry, "getMultiCaster", g2Proxy, g2ClassName);

        // assert
        Assertions.assertThat(result).isSameAs(classMultiCaster);

        // verify
        verify(associatedG2ProxyMultiCasters).get(g2Proxy);
        verify(proxyMultiCasterHash).get(g2ClassName);

    }


    @Test
    public void test_setMultiCaster_when_multi_caster() throws Exception {
        // mocks
        mockStatic(G2JavaStubController.ConnectionRegistry.class);
        G2JavaStubController.ConnectionRegistry connectionRegistry = mock(G2JavaStubController.ConnectionRegistry.class);
        Hashtable  associatedG2ProxyMultiCasters = mock(Hashtable.class);
        Hashtable proxyMultiCasterHash = mock(Hashtable.class);
        Item g2Proxy = mock(Item.class);
        Symbol g2ClassName = mock(Symbol.class);
        G2JavaStubController.LocalMultiCaster multiCaster = mock(G2JavaStubController.LocalMultiCaster.class);

        // arrange
        Whitebox.setInternalState(connectionRegistry, "associatedG2ProxyMultiCasters", associatedG2ProxyMultiCasters);

        // given
        when(associatedG2ProxyMultiCasters.get(g2Proxy)).thenReturn(proxyMultiCasterHash);

        // when
        doCallRealMethod().when(connectionRegistry, "setMultiCaster", g2Proxy, g2ClassName, multiCaster);
        Whitebox.invokeMethod(connectionRegistry, "setMultiCaster", g2Proxy, g2ClassName, multiCaster);

        // verify
        verify(associatedG2ProxyMultiCasters).get(g2Proxy);
        verify(proxyMultiCasterHash).put(g2ClassName, multiCaster);

    }

    @Test
    public void test_setMultiCaster_no_multi_caster() throws Exception {
        // mocks
        mockStatic(G2JavaStubController.ConnectionRegistry.class);
        G2JavaStubController.ConnectionRegistry connectionRegistry = mock(G2JavaStubController.ConnectionRegistry.class);
        Hashtable  associatedG2ProxyMultiCasters = mock(Hashtable.class);
        Hashtable proxyMultiCasterHash = null;
        Item g2Proxy = mock(Item.class);
        Symbol g2ClassName = mock(Symbol.class);
        G2JavaStubController.LocalMultiCaster multiCaster = mock(G2JavaStubController.LocalMultiCaster.class);
        Hashtable newProxyMultiCasterHash = mock(Hashtable.class);

        // arrange
        Whitebox.setInternalState(connectionRegistry, "associatedG2ProxyMultiCasters", associatedG2ProxyMultiCasters);

        // given
        when(associatedG2ProxyMultiCasters.get(g2Proxy)).thenReturn(proxyMultiCasterHash);
        whenNew(Hashtable.class).withNoArguments().thenReturn(newProxyMultiCasterHash);

        // when
        doCallRealMethod().when(connectionRegistry, "setMultiCaster", g2Proxy, g2ClassName, multiCaster);
        Whitebox.invokeMethod(connectionRegistry, "setMultiCaster", g2Proxy, g2ClassName, multiCaster);

        // verify
        verify(associatedG2ProxyMultiCasters).get(g2Proxy);
        verify(associatedG2ProxyMultiCasters).put(g2Proxy, newProxyMultiCasterHash);
        verify(newProxyMultiCasterHash).put(g2ClassName, multiCaster);
        verifyNew(Hashtable.class);

    }

    @Test
    public void LocalMultiCaster_listenerError_no_element_count() throws Exception {
        //given

        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);

        G2JavaStubController.LocalMultiCaster localMultiCaster = spy(g2JavaStubController.new LocalMultiCaster());
        Object listener = mock(Object.class);
        Exception e = mock(Exception.class);
        G2Connection g2Connection = mock(G2Connection.class);
        Whitebox.setInternalState(localMultiCaster, "g2Connection", g2Connection);
        Item g2proxy = mock(Item.class);
        Whitebox.setInternalState(localMultiCaster, "g2proxy", g2proxy);
        int elementCount = 0;
        Whitebox.setInternalState(localMultiCaster, "elementCount", elementCount);
        Symbol JgiRemoveProxyAssociation = mock(Symbol.class);
        Whitebox.setInternalState(G2JavaStubController.class, "JgiRemoveProxyAssociation", JgiRemoveProxyAssociation);

        G2JavaStubController.ConnectionRegistry registryInfo = mock(G2JavaStubController.ConnectionRegistry.class);
        when(g2JavaStubController,"getConnectionRegistry", g2proxy).thenReturn(registryInfo);

        // when
        doCallRealMethod().when(localMultiCaster).listenerError(listener, e);
        localMultiCaster.listenerError(listener, e);

        // then
        verify(localMultiCaster).removeElement(listener);
        verify(g2Connection).reportLogBookErrorMessage(
                Symbol.intern("G2-EVENT-MULTICAST-ERROR"), "Exception thrown while sending G2 Event to " + listener +
                        "from " + g2proxy + "\n Events will no longer be sent to this object" + "\n Exception was " + e.toString());
        verify(g2Connection).callRPC(JgiRemoveProxyAssociation, new Object[]{g2proxy});
        verifyPrivate(g2JavaStubController).invoke("getConnectionRegistry", g2proxy);
        verify(registryInfo).removeAssociation(g2proxy);
        verify(localMultiCaster).disable();
        Assertions.assertThat(Whitebox.getInternalState(localMultiCaster, "g2proxy")).isNull();
        Assertions.assertThat(Whitebox.getInternalState(localMultiCaster, "listening")).isEqualTo(false);


    }

    private void initializeG2JavaStubController() {
        if (g2JavaStubController == null) {
            g2JavaStubController = new G2JavaStubController();
        }
    }

    private Object testGetAssociatedJavaObjectMethod(Object propValue, Symbol symbol) throws G2AccessException {

        // Arrange
        G2RMIClientImpl connection = new G2RMIClientImpl();
        G2JavaListenerProxyAdapterFactory factory = new G2JavaListenerProxyAdapterFactory();
        Object targetObj = new Object();
        ItemImpl g2proxy = new ItemImpl();
        g2proxy.setPropertyValue(CLASS_, symbol);
        g2proxy.setPropertyValue(VAL_, propValue);

        g2JavaStubController.setJavaObjectForG2ItemFactory(connection, factory);

        G2JavaStubController.ConnectionRegistry registry = g2JavaStubController.new ConnectionRegistry(connection);

        // Act
        Object actualResult = registry.getAssociatedJavaObject(targetObj, g2proxy);

        // Return
        return actualResult;
    }

    @Test
    public void test_getDownloader_() {
        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        DownLoad downloader = mock(DownLoad.class);

        // arrange
        Whitebox.setInternalState(g2JavaStubController,  "downloader", downloader);

        // when
        when(g2JavaStubController.getDownloader()).thenCallRealMethod();
        DownLoad result = g2JavaStubController.getDownloader();

        // assert
        Assertions.assertThat(result).isSameAs(downloader);


    }

    @Test
    public void test_setJavaObjectForG2ItemFactory_longJavaType_returnsSetLongValue() throws Exception {

        // mocks
        G2JavaStubController g2JavaStubController = mock(G2JavaStubController.class);
        G2Access connection = mock(G2Access.class);
        JavaObjectForG2ItemFactory factory = mock(JavaObjectForG2ItemFactory.class);
        G2JavaStubController.ConnectionRegistry registryInfo = mock(G2JavaStubController.ConnectionRegistry.class);

        // given
        when(g2JavaStubController, "getConnectionRegistry", connection).thenReturn(registryInfo);

        // when
        doCallRealMethod().when(g2JavaStubController).setJavaObjectForG2ItemFactory(connection, factory);
        g2JavaStubController.setJavaObjectForG2ItemFactory(connection, factory);

        // verify
        verifyPrivate(g2JavaStubController).invoke("getConnectionRegistry", connection);
        verify(registryInfo).setJavaObjectForG2ItemFactory(factory);

    }

    @Test(expected = RuntimeException.class)
    public void test_setJavaObjectForG2ItemFactory_RaiseNoSuchAttributeException_ThrowsRuntimeException()
            throws G2AccessException, NoSuchAttributeException {

        // Arrange
        G2RMIClientImpl connection = new G2RMIClientImpl();
        G2ClassForJavaObjectFactory factory = Mockito.mock(G2ClassForJavaObjectFactory.class);
        Object targetObj = new Object();
        Item g2proxy = Mockito.mock(Item.class);

        g2JavaStubController.setG2ClassForJavaObjectFactory(connection, factory);

        G2JavaStubController.ConnectionRegistry registry = g2JavaStubController.new ConnectionRegistry(connection);

        Mockito.when(g2proxy.getPropertyValue(CLASS_)).thenThrow(NoSuchAttributeException.class);

        // Act
        Object actualResult = registry.getAssociatedJavaObject(targetObj, g2proxy);
    }

    @Test(expected = RuntimeException.class)
    public void test_setJavaObjectForG2ItemFactory_RaiseG2AccessException_ThrowsRuntimeException()
            throws G2AccessException, NoSuchAttributeException {

        // Arrange
        G2RMIClientImpl connection = new G2RMIClientImpl();
        G2ItemForJavaObjectFactory factory = Mockito.mock(G2ItemForJavaObjectFactory.class);
        Object targetObj = new Object();
        Item g2proxy = Mockito.mock(Item.class);

        g2JavaStubController.setG2ItemForJavaObjectFactory(connection, factory);

        G2JavaStubController.ConnectionRegistry registry = g2JavaStubController.new ConnectionRegistry(connection);

        Mockito.when(g2proxy.getPropertyValue(CLASS_)).thenThrow(G2AccessException.class);

        // Act
        Object actualResult = registry.getAssociatedJavaObject(targetObj, g2proxy);
    }

    @Test
    public void test_getG2StubsForJavaClass_notNullProvider_returnsStructureOfSetClass()
            throws G2StubCreationException, ClassNotFoundException, NoSuchAttributeException {

        // Arrange
        String class_name = "com.gensym.jgi.G2Gateway";
        Symbol g2ClassName = Symbol.intern(class_name);
        boolean recurse = true;
        DownLoad newDownLoader = new DownLoad();
        newDownLoader.loadClass(G2Gateway.class);

        G2JavaStubGenerator provider = new G2JavaStubGenerator();

        g2JavaStubController.setG2JavaStubClassReflectionProvider(provider);
        g2JavaStubController.setDownloader(newDownLoader);

        // Act
        Structure actualResult = g2JavaStubController.getG2StubsForJavaClass(class_name, g2ClassName, recurse);

        // Assert
        assertNotNull(actualResult);
        assertTrue(actualResult.toString().contains("CLASS_NAME:" + class_name));
        assertEquals(Symbol.intern(class_name), actualResult.getAttributeValue(Symbol.intern("CLASS_NAME")));
    }

    @Test(expected = G2StubCreationException.class)
    public void test_getG2StubsForJavaClass_nullProvider_throwsG2StubCreationException()
            throws G2StubCreationException, ClassNotFoundException, NoSuchAttributeException {

        // Arrange
        String class_name = "com.gensym.jgi.G2Gateway";
        Symbol g2ClassName = Symbol.intern(class_name);
        boolean recurse = true;

        g2JavaStubController.setG2JavaStubClassReflectionProvider(null);

        // Act
        g2JavaStubController.getG2StubsForJavaClass(class_name, g2ClassName, recurse);
    }

    @Test(expected = G2AccessException.class)
    public void test_newInstance_nullg2connection_throwsG2AccessException() throws Exception {

        // Arrange
        ItemImpl g2proxy = new ItemImpl();
        String java_class_name = "";
        Sequence args = new Sequence();

        // Act
        g2JavaStubController.newInstance(g2proxy, java_class_name, args);
    }

    private void mockForNewInstance(ItemImpl g2proxy, final String java_class_name
            , G2RMIClientImpl context, Structure attributes, Item expectedItemMock) throws Exception {

        // Arrange
        int handle = 1;
        String method_name = "getPreferredSize";
        Symbol g2ClassName = G2ClassSymbols.ACTION_BUTTON_;
        attributes.addAttribute(CLASS_, g2ClassName);
        Structure attributesG2Method = new Structure();
        attributesG2Method.addAttribute(Symbol.intern(java_class_name), new Sequence());
        attributesG2Method.addAttribute(Symbol.intern("JAVA-PARAMETER-TYPES"), new Sequence());
        G2__BaseImplDefinitionStub definition1 = new G2__BaseImplDefinitionStub();

        Sequence classPathSequence = new Sequence();
        G2RMIAccess server = Mockito.mock(G2RMIAccess.class);
        ClassManager classManager = new ClassManager(context);
        G2__BaseImplDefinitionStub definition = new G2__BaseImplDefinitionStub(context, handle, 1, definition1, attributes);
        definition.g2ClassName = g2ClassName;
        definition.classPathSequence = classPathSequence;
        classManager.storeClassDefinition(g2ClassName, definition, false);

        Mockito.when(server.callRPC(Matchers.any(Symbol.class), Matchers.any(Object[].class))).thenAnswer(
                new Answer<String>() {
                    @Override
                    public String answer(InvocationOnMock invocation) {

                        Symbol g2ProcedureName = (Symbol) invocation.getArguments()[0];

                        if (g2ProcedureName.equals(Symbol.intern("G2-GET-FROM-ITEM")))
                            return java_class_name;
                        else
                            return "Version.2.1.123";
                    }
                });
        Mockito.when(server.callRPC(Matchers.any(Symbol.class), Matchers.any(Object[].class), Matchers.eq(0)))
                .thenReturn(expectedItemMock);

        Whitebox.setInternalState(context, "classManager", classManager);
        Whitebox.setInternalState(context, "server", server);

        ItemImpl g2method = new ItemImpl(context, 0, attributesG2Method);
        G2Access g2connection = ((ImplAccess) g2proxy).getContext();

        DownLoad newDownLoader = new DownLoad();
        newDownLoader.loadClass(G2Connector.class);

        g2JavaStubController.setDownloader(newDownLoader);
    }

    @Test
    public void test_newInstance_onCall_createsJavaClassInstance() throws Exception {

        // Arrange
        String java_class_name = G2Connector.class.getName();
        Sequence args = new Sequence();
        G2RMIClientImpl context = new G2RMIClientImpl();
        Structure attributes = new Structure();
        ItemImpl g2proxy = new ItemImpl(context, 1, attributes);
        G2Access g2connection = ((ImplAccess) g2proxy).getContext();
        Item expectedItemMock = Mockito.mock(Item.class);

        mockForNewInstance(g2proxy, java_class_name, context, attributes, expectedItemMock);

        // Act
        g2JavaStubController.newInstance(g2proxy, java_class_name, args);

        // Assert
        Hashtable connectionsTable = (Hashtable) Whitebox.getInternalState(g2JavaStubController, "connectionsTable");
        assertNotNull(connectionsTable);
        assertEquals(1, connectionsTable.size());
        G2JavaStubController.ConnectionRegistry registryInfo = (G2JavaStubController.ConnectionRegistry) connectionsTable.get(g2connection);
        assertNotNull(registryInfo);
        Hashtable registeredG2Classes = (Hashtable) Whitebox.getInternalState(registryInfo, "registeredG2Classes");
        assertNotNull(registeredG2Classes);
        assertEquals(G2ClassSymbols.ACTION_BUTTON_, registeredG2Classes.get(java_class_name.intern()));
        Hashtable registeredJavaClasses = (Hashtable) Whitebox.getInternalState(registryInfo, "registeredJavaClasses");
        assertNotNull(registeredJavaClasses);
        assertEquals(java_class_name.intern(), registeredJavaClasses.get(G2ClassSymbols.ACTION_BUTTON_));
        Hashtable controlledJavaObjects = (Hashtable) Whitebox.getInternalState(registryInfo, "controlledJavaObjects");
        assertNotNull(controlledJavaObjects);
        Object java_object = controlledJavaObjects.get(g2proxy);
        Hashtable associatedG2Proxies = (Hashtable) Whitebox.getInternalState(registryInfo, "associatedG2Proxies");
        assertNotNull(associatedG2Proxies);
        assertEquals(g2proxy, associatedG2Proxies.get(java_object));
    }

    @Test
    public void test_callMethod_onCall_createsJavaClassInstanceAndCallsMethod() throws Exception {

        // Arrange
        String method_name = "getPreferredSize";
        String java_class_name = G2Connector.class.getName();
        Sequence args = new Sequence();
        G2RMIClientImpl context = new G2RMIClientImpl();
        Structure attributes = new Structure();
        ItemImpl g2proxy = new ItemImpl(context, 1, attributes);
        G2Access g2connection = ((ImplAccess) g2proxy).getContext();
        Item expectedItemMock = Mockito.mock(Item.class);

        mockForNewInstance(g2proxy, java_class_name, context, attributes, expectedItemMock);

        g2JavaStubController.newInstance(g2proxy, java_class_name, args);

        // Act
        Object actualResult = g2JavaStubController.callMethod(g2proxy, method_name, args);

        // Assert
        assertEquals(expectedItemMock, actualResult);
        Hashtable connectionsTable = (Hashtable) Whitebox.getInternalState(g2JavaStubController, "connectionsTable");
        assertNotNull(connectionsTable);
        assertEquals(1, connectionsTable.size());
        G2JavaStubController.ConnectionRegistry registryInfo = (G2JavaStubController.ConnectionRegistry) connectionsTable.get(g2connection);
        assertNotNull(registryInfo);
        Hashtable controlledJavaObjects = (Hashtable) Whitebox.getInternalState(registryInfo, "controlledJavaObjects");
        assertNotNull(controlledJavaObjects);
        Object java_object = controlledJavaObjects.get(expectedItemMock);
        Hashtable associatedG2Proxies = (Hashtable) Whitebox.getInternalState(registryInfo, "associatedG2Proxies");
        assertNotNull(associatedG2Proxies);
        assertEquals(expectedItemMock, associatedG2Proxies.get(java_object));
    }
                
}
