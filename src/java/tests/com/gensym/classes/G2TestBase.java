package com.gensym.classes;

import com.gensym.jgi.G2Gateway;
import com.gensym.util.ClassManager;
import com.gensym.util.Structure;
import com.gensym.util.Symbol;
import org.junit.Before;
import org.mockito.Mockito;

import java.lang.reflect.Constructor;
import java.util.HashMap;
import java.util.Map;

import static org.mockito.Matchers.any;
import static org.mockito.Matchers.eq;
import static org.mockito.Mockito.RETURNS_DEEP_STUBS;
import static org.mockito.Mockito.mock;
import static org.mockito.Mockito.when;

public abstract class G2TestBase<T extends G2__Base> {

    private static final int HANDLE = -1;

    private static final Map<Class<?>, java.lang.Object> PRIMITIVES;

    static {
        PRIMITIVES = new HashMap<Class<?>, java.lang.Object>();
        PRIMITIVES.put(Boolean.class, Boolean.TRUE);
        PRIMITIVES.put(boolean.class, true);
        PRIMITIVES.put(Character.class, 'c');
        PRIMITIVES.put(char.class, 'c');
        PRIMITIVES.put(Byte.class, 120);
        PRIMITIVES.put(byte.class, 120);
        PRIMITIVES.put(Short.class, 43);
        PRIMITIVES.put(short.class, 43);
        PRIMITIVES.put(Integer.class, 42);
        PRIMITIVES.put(int.class, 42);
        PRIMITIVES.put(Long.class, 41L);
        PRIMITIVES.put(long.class, 41L);
        PRIMITIVES.put(Float.class, 40.0f);
        PRIMITIVES.put(float.class, 40.0);
        PRIMITIVES.put(Double.class, 39.0);
        PRIMITIVES.put(double.class, 39.0);
    }

    protected T instance;
    protected Structure attributes;
    protected ClassManager classManager;

    private G2Gateway context;
    private Map<Class<?>, java.lang.Object> stubs;

    @Before
    public void setUp() throws Exception {
        stubs = new HashMap<Class<?>, java.lang.Object>();
        context = mock(G2Gateway.class, RETURNS_DEEP_STUBS);
        classManager = context.getClassManager();
        SystemClassDefinitionImpl systemClassDefinition = mock(SystemClassDefinitionImpl.class);
        when(classManager.getDefinition0(any(Symbol.class))).thenReturn(systemClassDefinition);
        attributes = new Structure();
        instance = createNewInstance();
    }

    protected <V> V mockClassAttributeValue(Symbol symbol, Class<V> type) throws Exception {
        V stub;
        if (type.isPrimitive()) {
            stub = (V) PRIMITIVES.get(type);
        } else {
            stub = getStub(type);
        }
        when(classManager.getClassAttributeValue(any(Symbol.class), eq(symbol))).thenReturn(stub);
        return stub;
    }

    protected T createNewInstance() throws Exception {
        for (Constructor<?> constructor : forClass().getConstructors()) {
            if (constructor.getParameterTypes().length == 3) {
                return (T) constructor.newInstance(context, HANDLE, attributes);
            }
        }
        throw new IllegalStateException("Failed to find a proper constructor for class: " + forClass().getName());
    }

    protected <V> V getStub(Class<V> type) {
        if (!stubs.containsKey(type)) {
            java.lang.Object mock = Mockito.mock(type);
            stubs.put(type, mock);
        }
        return type.cast(stubs.get(type));
    }

    abstract protected Class<T> forClass();
}
