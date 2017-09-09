package com.gensym.jgi.download;

import static org.hamcrest.CoreMatchers.equalTo;
import static org.hamcrest.MatcherAssert.assertThat;
import static org.mockito.Mockito.times;
import static org.mockito.Mockito.verify;

import java.lang.reflect.Method;
import java.util.List;

import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.mockito.ArgumentCaptor;
import org.mockito.Captor;
import org.mockito.Mock;
import org.mockito.Mockito;
import org.mockito.runners.MockitoJUnitRunner;

import com.gensym.classtools.ClassException;
import com.gensym.classtools.ClassInfo;
import com.gensym.classtools.Expression;
import com.gensym.classtools.FieldRef;
import com.gensym.classtools.MethodCall;
import com.gensym.classtools.Type;
import com.gensym.classtools.Variable;

@RunWith(MockitoJUnitRunner.class)
public class PseudoClassDelegateInfoTest {
	@Mock
	private ClassInfo classInfo;

	@Captor
	private ArgumentCaptor<com.gensym.classtools.MethodInfo> methodInfoArgCaptor;

	private Class<PseudoClassTestHelper> theClass = PseudoClassTestHelper.class;

	private PseudoClassDelegateInfo target;

	@Before
	public void setup() {
		this.target = new PseudoClassDelegateInfo(this.classInfo, this.theClass);
	}

	@Test
	public void test_getClassForDelegate_Always_ReturnsClassDefined() {
		assertThat(this.target.getClassForDelegate(), equalTo((Class) this.theClass));
	}

	@Test
	public void test_setFieldRef_Always_SetsValue() {
		final FieldRef fieldRef = createFieldRef();
		this.target.setFieldRef(fieldRef);
		assertThat(this.target.getFieldRef(), equalTo(fieldRef));
	}

	@Test
	public void test_getDelegateName_Success_ReturnsPrefixMoreDelegateClassSimpleName() {
		final String expected = "mv" + this.theClass.getSimpleName();
		assertThat(this.target.getDelegateName(), equalTo(expected));
	}

	@Test
	public void test_makeConstructorCall_Success_ReturnsConstructorMethodCallForDelegateClass() throws ClassException {
		// Arrange
		final String argsDescriptor = "(ILjava/lang/String;Ljava/lang/Object;)V";
		final Expression[] args = {
				new Variable(0, "I"),
				new Variable(1, "Ljava/lang/String;"),
				new Variable(2, "Ljava/lang/Object;")
		};

		// Act
		final MethodCall result = this.target.makeConstructorCall(argsDescriptor, args);

		// Assert
		assertThat(result.getClassName(), equalTo(this.theClass.getName()));
		assertThat(result.getName(), equalTo("<init>"));
	}

	@Test
	public void test_createDelegationMethods_Success_AddsEachMethodToImplement() throws Exception {
		// Arrange
		final Method method1 = this.theClass.getMethod("method1", int.class, float.class);
		final Method method2 = this.theClass.getMethod("method2");
		final Method method3 = this.theClass.getMethod("method3", Object.class, String.class, double.class);

		this.target.addMethod(null, method1);
		this.target.addMethod(null, method2);
		this.target.addMethod(null, method3);
		this.target.setFieldRef(createFieldRef());

		// Act
		this.target.createDelegationMethods();

		// Assert
		verify(this.classInfo, times(3)).add(this.methodInfoArgCaptor.capture());

		final List<com.gensym.classtools.MethodInfo> methodsAdded = this.methodInfoArgCaptor.getAllValues();
		assertThat(methodsAdded.get(0).getDescriptor(), equalTo("(IF)V"));
		assertThat(methodsAdded.get(0).getName(), equalTo("method1"));

		assertThat(methodsAdded.get(1).getDescriptor(), equalTo("()I"));
		assertThat(methodsAdded.get(1).getName(), equalTo("method2"));

		assertThat(methodsAdded.get(2).getDescriptor(),
				equalTo("(Ljava/lang/Object;Ljava/lang/String;D)Ljava/lang/String;"));
		assertThat(methodsAdded.get(2).getName(), equalTo("method3"));
	}

	private FieldRef createFieldRef() {
		final FieldRef fieldRef = Mockito.mock(FieldRef.class);
		final Type type = Mockito.mock(Type.class);
		Mockito.when(fieldRef.getExpressionType()).thenReturn(type);
		Mockito.when(type.isClassType()).thenReturn(true);

		return fieldRef;
	}
}