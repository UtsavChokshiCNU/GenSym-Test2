package com.gensym.common.openpojo;

import com.openpojo.reflection.PojoField;
import com.openpojo.validation.test.Tester;

import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;

public abstract class MockingTester implements Tester {

    private static final Set<String> PACKAGES_TO_MOCK = new HashSet<String>(Arrays.asList(
            "java.awt"));

    private Set<Class<?>> classesToMock = new HashSet<Class<?>>();

    public MockingTester(Class<?>... classesToMock) {
        this.classesToMock.addAll(Arrays.asList(classesToMock));
    }

    protected boolean shouldBeMocked(PojoField fieldEntry) {
        Class<?> type = fieldEntry.getType();
        return PACKAGES_TO_MOCK.contains(type.getPackage().getName()) || classesToMock.contains(type);
    }
}
