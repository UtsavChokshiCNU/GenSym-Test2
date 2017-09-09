package com.gensym.common.openpojo;

import com.openpojo.random.RandomGenerator;

import java.awt.*;
import java.util.Arrays;
import java.util.Collection;
import java.util.List;

import static org.mockito.Mockito.mock;

public class AwtMockRandomGenerator implements RandomGenerator {

    private static final List<Class<?>> MOCK_CLASSES = Arrays.asList(
            Image.class,
            Component.class);

    @Override
    public Collection<Class<?>> getTypes() {
        return MOCK_CLASSES;
    }

    @Override
    public Object doGenerate(Class<?> type) {
        return mock(type);
    }
}
