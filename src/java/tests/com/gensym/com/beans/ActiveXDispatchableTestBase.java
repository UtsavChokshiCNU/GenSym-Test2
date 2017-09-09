package com.gensym.com.beans;

import com.gensym.com.ActiveXDispatchable;
import com.gensym.com.ActiveXDispatchableImpl;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.excel12.Range;
import com.gensym.com.beans.excel12.Window;
import com.gensym.com.beans.office20.Assistant;
import com.gensym.com.beans.office20.FileSearch;
import com.gensym.com.beans.office20.IFind;
import com.gensym.com.beans.vbide50.VBE;
import org.mockito.ArgumentCaptor;
import org.mockito.Mockito;

import java.awt.*;
import java.util.Comparator;
import java.util.Date;
import java.util.HashMap;
import java.util.Map;
import java.util.Vector;

import static org.assertj.core.api.Assertions.assertThat;
import static org.assertj.core.api.Assertions.fail;
import static org.mockito.Matchers.eq;
import static org.mockito.Mockito.RETURNS_DEEP_STUBS;
import static org.mockito.Mockito.mock;
import static org.mockito.Mockito.when;

/**
 * Base class for Tests of Dispatchable components.
 */
public abstract class ActiveXDispatchableTestBase {

    protected static final Map<Class<?>, Object> ARBITRARY_MOCKS = new HashMap<Class<?>, Object>();
    private static final Comparator<Variant> VARIANT_COMPARATOR = new Comparator<Variant>() {
        @Override
        public int compare(Variant o1, Variant o2) {
            return o1.equals(o2) ? 0 : -1;
        }
    };

    static {
        addForClass(ActiveXDispatchable.class);
        addForClass(Range.class);
        addForClass(Window.class);
        addForClass(com.gensym.com.beans.excel12.Window.class);
        addForClass(com.gensym.com.beans.vbide50.Window.class);
        addForClass(com.gensym.com.beans.excel12.AddIn.class);
        addForClass(com.gensym.com.beans.vbide50.AddIn.class);
        addForClass(com.gensym.com.beans.vbide50.Reference.class);
        addForClass(com.gensym.com.beans.excel12.Shape.class);
        addForClass(com.gensym.com.beans.office20.Shape.class);
        addForClass(com.gensym.com.beans.excel12.ColorFormat.class);
        addForClass(com.gensym.com.beans.excel12.Toolbar.class);
        addForClass(com.gensym.com.beans.vbide50.VBControl.class);
        addForClass(com.gensym.com.beans.vbide50.ControlTemplate.class);
        addForClass(com.gensym.com.beans.vbide50.VBForm.class);
        addForClass(VBE.class);
        addForClass(IFind.class);
        addForClass(FileSearch.class);
        addForClass(Assistant.class);
        addForClass(Vector.class);
        addForClass(Color.class);
    }

    protected final ActiveXDispatchableImpl axProxy = mock(ActiveXDispatchableImpl.class, RETURNS_DEEP_STUBS);
    protected boolean onProxy;

    private static void addForClass(Class<?> clazz) {
        ARBITRARY_MOCKS.put(clazz, mock(clazz));
    }

    @SuppressWarnings("unchecked")
    protected <T> T getMock(Class<T> clazz) {
        return (T) ARBITRARY_MOCKS.get(clazz);
    }

    protected Verificator on(int memid) {
        return new Verificator(memid);
    }

    protected abstract static class Void {
        public abstract void invoke() throws ActiveXException;
    }

    protected abstract static class Returns<T> {
        public abstract T invoke() throws ActiveXException;
    }

    protected static class UnsupportedType {

        final int value;

        public UnsupportedType(int value) {
            this.value = value;
        }

        @Override
        public boolean equals(Object o) {
            if (this == o) {
                return true;
            }
            if (o == null || getClass() != o.getClass()) {
                return false;
            }
            UnsupportedType that = (UnsupportedType) o;
            return value == that.value;
        }
    }

    protected class Verificator {
        public static final String UNEXPECTED_FAILURE = "Unexpected ActiveXException from %s. Possibly not a mock?";
        private final int memid;
        private int dispatchType = ActiveXRuntimeConstants.AX_INVOKE;
        private int dispatchPointer = ActiveXRuntimeConstants.AX_NO_DISPATCH;
        private Variant[] args = new Variant[]{};
        private ArgumentCaptor<Vector> vectorArgumentCaptor = ArgumentCaptor.forClass(Vector.class);

        public Verificator(int memid) {
            this.memid = memid;
        }

        public Verificator dispatchType(int dispatchType) {
            this.dispatchType = dispatchType;
            return this;
        }

        public Verificator args(Variant... args) {
            this.args = args;
            return this;
        }

        /**
         * Verifies that given proxy caller properly redirects arguments
         * @param proxyCall a proxy caller which returns void
         */
        public void verifyNoReturn(Void proxyCall) {
            try {
                proxyCall.invoke();

                if (onProxy) {
                    Mockito.verify(axProxy).axInvoke(
                            eq(memid),
                            eq(dispatchType),
                            eq(true),
                            vectorArgumentCaptor.capture());
                } else {
                    Mockito.verify(axProxy.getActiveXProxy()).axInvoke(eq(dispatchPointer),
                            eq(memid),
                            eq(dispatchType),
                            eq(true),
                            vectorArgumentCaptor.capture());
                }
                verifyArgs();
            } catch (ActiveXException e) {
                fail(UNEXPECTED_FAILURE, axProxy.getActiveXProxy());
            }
        }

        /**
         * Verifies that given proxy caller properly redirects arguments and returns expected dispatchable component
         * @param proxyCall a proxy caller which returns an element with expected proxy
         */
        public void verifyReturnsDispatchable(Returns<? extends ActiveXDispatchable> proxyCall) {
            try {
                ActiveXDispatchable dispatchable = mock(ActiveXDispatchable.class, RETURNS_DEEP_STUBS);
                Variant variant = new Variant(dispatchable);
                captureArgs(variant);

                ActiveXDispatchable result = proxyCall.invoke();

                verifyArgs();
                assertThat(result.getActiveXProxy()).isSameAs(dispatchable.getActiveXProxy());
                assertThat(result.getDispatchPointer()).isSameAs(dispatchable.getDispatchPointer());
            } catch (ActiveXException e) {
                fail(UNEXPECTED_FAILURE, axProxy.getActiveXProxy());
            }
        }

        /**
         * Verifies that given proxy caller properly redirects arguments and returns expected dispatchable value
         * @param proxyCall a proxy caller which returns ActiveXDispatchable value
         */
        public void verifyReturnsDispatchableValue(Returns<ActiveXDispatchable> proxyCall) {
            ActiveXDispatchable dispatchable = mock(ActiveXDispatchable.class, RETURNS_DEEP_STUBS);
            Variant variant = new Variant(dispatchable);
            runOn(variant, dispatchable, proxyCall);
        }

        /**
         * Verifies that given proxy caller properly redirects arguments and returns variant
         * @param proxyCall a proxy caller which returns variant
         */
        public void verifyReturnsVariant(Returns<Variant> proxyCall) {
            try {
                Variant expected = new Variant("123");
                captureArgs(expected);

                Variant result = proxyCall.invoke();

                verifyArgs();
                assertThat(result).isSameAs(expected);
            } catch (ActiveXException e) {
                fail(UNEXPECTED_FAILURE, axProxy.getActiveXProxy());
            }
        }

        /**
         * Verifies that given proxy caller properly redirects arguments and returns arbitrary object
         * @param proxyCall a proxy caller which returns arbitrary object
         */
        public void verifyReturnsGenericValue(Returns<Object> proxyCall) {
            try {
                Variant variant = new Variant();
                captureArgs(variant);

                Object result = proxyCall.invoke();

                verifyArgs();
                assertThat(result).isExactlyInstanceOf(Object.class);
            } catch (ActiveXException e) {
                fail(UNEXPECTED_FAILURE, axProxy.getActiveXProxy());
            }
        }

        /**
         * Verifies that given proxy caller properly redirects arguments and returns Color
         * @param proxy a proxy caller which returns Color object
         */
        public void verifyReturnsColor(Returns<Color> proxy) {
            Color color = new Color(123, 123, 123);
            Variant variant = new Variant(color);
            runOn(variant, color, proxy);
        }

        /**
         * Verifies that given proxy caller properly redirects arguments and returns Date
         * @param proxy a proxy caller which returns Date object
         */
        public void verifyReturnsDate(Returns<Date> proxy) {
            Date date = new Date(123);
            Variant variant = new Variant(date);
            runOn(variant, date, proxy);
        }

        /**
         * Verifies that given proxy caller properly redirects arguments and returns integer
         * @param proxyCall a proxy caller which returns integer
         */
        public void verifyReturnsInt(Returns<Integer> proxyCall) {
            runOn(new Variant(42), 42, proxyCall);
        }

        /**
         * Verifies that given proxy caller properly redirects arguments and returns boolean
         * @param proxyCall a proxy caller which returns boolean
         */
        public void verifyReturnsBoolean(Returns<Boolean> proxyCall) {
            runOn(new Variant(true), true, proxyCall);
        }

        /**
         * Verifies that given proxy caller properly redirects arguments and returns long
         * @param proxyCall a proxy caller which returns long
         */
        public void verifyReturnsLong(Returns<Long> proxyCall) {
            runOn(new Variant(456L), 456L, proxyCall);
        }

        /**
         * Verifies that given proxy caller properly redirects arguments and returns double
         * @param proxyCall a proxy caller which returns double
         */
        public void verifyReturnsDouble(Returns<Double> proxyCall) {
            runOn(new Variant(1.0d), 1.0d, proxyCall);
        }

        /**
         * Verifies that given proxy caller properly redirects arguments and returns float
         * @param proxyCall a proxy caller which returns float
         */
        public void verifyReturnsFloat(Returns<Float> proxyCall) {
            runOn(new Variant(1.123f), 1.123f, proxyCall);
        }

        /**
         * Verifies that given proxy caller properly redirects arguments and returns short
         * @param proxyCall a proxy caller which returns short
         */
        public void verifyReturnsShort(Returns<Short> proxyCall) {
            short value = 123;
            runOn(new Variant(value), value, proxyCall);
        }

        /**
         * Verifies that given proxy caller properly redirects arguments and returns String
         * @param proxyCall a proxy caller which returns String
         */
        public void verifyReturnsString(Returns<String> proxyCall) {
            runOn(new Variant("ABC"), "ABC", proxyCall);
        }

        private <T> void runOn(Variant variant, T expected, Returns<T> proxy) {
            try {
                captureArgs(variant);

                T result = proxy.invoke();

                verifyArgs();
                assertThat(result).isEqualTo(expected);
            } catch (ActiveXException e) {
                fail(UNEXPECTED_FAILURE, axProxy.getActiveXProxy());
            }
        }

        private void captureArgs(Variant variant) throws ActiveXException {
            if (onProxy) {
                when(axProxy.axInvoke(
                        eq(memid),
                        eq(dispatchType),
                        eq(false),
                        vectorArgumentCaptor.capture())).thenReturn(variant);
            } else {
                when(axProxy.getActiveXProxy().axInvoke(eq(dispatchPointer),
                        eq(memid),
                        eq(dispatchType),
                        eq(false),
                        vectorArgumentCaptor.capture())).thenReturn(variant);
            }
        }

        private void verifyArgs() {
            @SuppressWarnings("unchecked") Vector<Variant> capturedArgs = vectorArgumentCaptor.getValue();
            assertThat(capturedArgs).usingElementComparator(VARIANT_COMPARATOR).containsExactly(args);
        }
    }
}
