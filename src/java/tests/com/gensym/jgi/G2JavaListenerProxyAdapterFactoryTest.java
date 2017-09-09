package com.gensym.jgi;

import static org.hamcrest.CoreMatchers.containsString;
import static org.hamcrest.CoreMatchers.is;
import static org.hamcrest.MatcherAssert.assertThat;
import static org.hamcrest.Matchers.equalTo;
import static org.hamcrest.Matchers.sameInstance;
import static org.junit.Assert.fail;
import static org.mockito.Matchers.any;
import static org.mockito.Matchers.eq;
import static org.mockito.Mockito.spy;
import static org.mockito.Mockito.verify;

import java.io.ByteArrayOutputStream;
import java.io.PrintStream;
import java.lang.reflect.Constructor;
import java.util.Vector;

import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.mockito.ArgumentCaptor;
import org.mockito.Captor;
import org.mockito.Mock;
import org.mockito.Mockito;
import org.powermock.api.mockito.PowerMockito;
import org.powermock.core.classloader.annotations.PrepareForTest;
import org.powermock.modules.junit4.PowerMockRunner;

import com.gensym.classes.Definition;
import com.gensym.classes.G2Definition;
import com.gensym.classes.Item;
import com.gensym.util.ClassManager;
import com.gensym.util.DownLoad;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;

@RunWith(PowerMockRunner.class)
@PrepareForTest({G2JavaStubController.class, G2JavaStubInterfaceGenerator.class})
public class G2JavaListenerProxyAdapterFactoryTest {
	@Mock
	private G2Connection g2Connection;

	@Mock
	private Item g2Proxy;

	@Mock
	private G2Definition g2Definition;

	@Mock
	private ClassManager classManager;

	@Mock
	private G2JavaStubController controller;

	@Mock
	private DownLoad downloader;

	@Mock
	private Sequence classInheritancePath;

	@Captor
	private ArgumentCaptor<Vector> interfaceListArgCaptor;

	private Symbol g2ClassName;
	private G2JavaListenerProxyAdapterFactory target;

	@Before
	public void setup() throws G2AccessException {
		PowerMockito.mockStatic(G2JavaStubController.class, G2JavaStubInterfaceGenerator.class);
		this.classInheritancePath = new Sequence();
		this.g2ClassName = Symbol.intern("TestClass");

		initializeMocks();
		this.target = new G2JavaListenerProxyAdapterFactory();
	}

	@Test
	public void test_getJavaObjectForG2Item_WhenInterfaceListIsEmpty_ReturnsG2ProxyItemArgument() {
		// Act
		final Object result1 = this.target.getJavaObjectForG2Item(this.g2Connection, new Object(), this.g2Proxy);
		final Object result2 = this.target.getJavaObjectForG2Item(this.g2Connection, new Object(), this.g2Proxy);

		// Assert
		assertThat(result1, sameInstance((Object) this.g2Proxy));
		// two results, to verify a "short-circuit" return of the method,
		// after detected that no interfaces were found
		assertThat(result2, sameInstance((Object) this.g2Proxy));
	}

	@Test
	public void test_getJavaObjectForG2Item_Success_AssociatesAndReturnsAdapter() throws Exception {
		// Arrange
		arrangeInterfaceList(TestInterface1.class, TestInterface2.class);
		final Object expected = new Object();
		final Constructor constructor = TestClass.class.getConstructor();

		PowerMockito.when(G2JavaStubInterfaceGenerator.getAdapterConstructor(
				eq(this.downloader),
				this.interfaceListArgCaptor.capture(),
				eq(this.g2Connection),
				eq(this.g2ClassName))).thenReturn(constructor);

		PowerMockito.when(G2JavaStubInterfaceGenerator.createAdapter(
				eq(constructor),
				eq(this.controller),
				eq(this.g2Connection),
				eq(this.g2Proxy))).thenReturn(expected);

		// Act
		final Object result = this.target.getJavaObjectForG2Item(this.g2Connection, new Object(), this.g2Proxy);

		// Assert
		assertThat(result, equalTo(expected));
		verify(this.controller).associate(this.g2Connection, this.g2Proxy, expected);
	}

	@Test(expected = RuntimeException.class)
	public void getJavaObjectForG2Item_AnyExceptionCaught_RethrowsRuntimeException() throws Exception {
		// Arrange
		final TestException exception = spy(new TestException());
		Mockito.doNothing().when(exception).printStackTrace();
		Mockito.when(this.g2Proxy.getG2ClassName()).thenThrow(exception);

		// Act
		this.target.getJavaObjectForG2Item(this.g2Connection, new Object(), this.g2Proxy);
	}

	@Test
	public void lookupJavaInterfacesImplementedByG2Class_Success_AddsToVectorInterfacesFound()
			throws G2AccessException {
		// Arrange
		final Vector<Class> interfaceList = new Vector<Class>();
		arrangeInterfaceList(TestInterface1.class, TestInterface2.class, TestInterface3.class, TestClass.class);

		// Act
		this.target.lookupJavaInterfacesImplementedByG2Class(this.g2Connection, this.g2Proxy, interfaceList);

		// Assert
		assertThat(interfaceList.size(), equalTo(3));
		assertThat(interfaceList.contains(TestInterface1.class), is(true));
		assertThat(interfaceList.contains(TestInterface2.class), is(true));
		assertThat(interfaceList.contains(TestInterface3.class), is(true));
	}

	@Test
	public void lookupJavaInterfacesImplementedByG2Class_ClassNotFoundExceptionCaught_LogsToSystemErr()
			throws G2AccessException {
		// Arrange
		final Vector<Class> interfaceList = new Vector<Class>();
		final ByteArrayOutputStream byteStream = new ByteArrayOutputStream();
		final PrintStream printStream = new PrintStream(byteStream);

		arrangeInterfaceList(TestInterface3.class, ShouldThrowNotFound.class);
		System.setErr(printStream);

		// Act
		this.target.lookupJavaInterfacesImplementedByG2Class(this.g2Connection, this.g2Proxy, interfaceList);

		// Assert
		assertThat(interfaceList.size(), equalTo(1));
		assertThat(interfaceList.contains(TestInterface3.class), is(true));
		assertThat(byteStream.toString(), containsString(
				"lookupJavaInterfacesImplementedByG2Class Could not find " + ShouldThrowNotFound.class.getName()));
	}

	/*
	 * Helper methods and classes
	 */
	@SuppressWarnings("unchecked")
	private void arrangeInterfaceList(final Class... classes) {
		try {
			for (final Class theClass : classes) {
				final String className = theClass.getName();
				final Symbol curG2ClassName = Symbol.intern(className);
				final Symbol supG2ClassName = Symbol.intern("Super" + className);
				final Definition curG2def = Mockito.mock(Definition.class, "Current G2 Def");
				final Definition supG2def = Mockito.mock(Definition.class, "Super G2 Def");
				final Sequence currentInheritancePath = Mockito.mock(Sequence.class);
				final Sequence superInheritancePath = Mockito.mock(Sequence.class);

				Mockito.when(this.classManager.getDefinition(curG2ClassName)).thenReturn(curG2def);
				Mockito.when(this.classManager.getDefinition(supG2ClassName)).thenReturn(supG2def);
				Mockito.when(curG2def.getClassInheritancePath()).thenReturn(currentInheritancePath);
				Mockito.when(supG2def.getClassInheritancePath()).thenReturn(superInheritancePath);
				Mockito.when(supG2def.getPropertyValue(any(Symbol.class))).thenReturn(className);
				Mockito.when(currentInheritancePath.size()).thenReturn(2);
				Mockito.when(superInheritancePath.size()).thenReturn(1);

				if (theClass == ShouldThrowNotFound.class) {
					Mockito.when(downloader.lookupClass(className)).thenThrow(new ClassNotFoundException());
				} else {
					Mockito.when(downloader.lookupClass(className)).thenReturn(theClass);
				}

				this.classInheritancePath.addElement(curG2ClassName);
				this.classInheritancePath.addElement(supG2ClassName);
			}

			initializeMocks();
		} catch (Throwable ex) {
			fail("Fail to arrange test: " + ex.getMessage());
		}
	}

	private void initializeMocks() throws G2AccessException {
		PowerMockito.when(G2JavaStubController.getG2JavaStubController()).thenReturn(this.controller);
		Mockito.when(this.controller.getDownloader()).thenReturn(this.downloader);
		Mockito.when(this.g2Proxy.getG2ClassName()).thenReturn(g2ClassName);
		Mockito.when(this.g2Connection.getClassManager()).thenReturn(classManager);
		Mockito.when(classManager.getDefinition(g2ClassName)).thenReturn(this.g2Definition);
		Mockito.when(this.g2Definition.getClassInheritancePath()).thenReturn(this.classInheritancePath);
	}

	private interface TestInterface1 {}

	private interface TestInterface2 {}

	private interface TestInterface3 {}

	private static class ShouldThrowNotFound {}

	private static class TestClass {
		public TestClass() {}
	}

	private class TestException extends Exception {
	}
}