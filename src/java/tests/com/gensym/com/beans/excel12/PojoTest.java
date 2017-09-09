package com.gensym.com.beans.excel12;

import com.gensym.com.ActiveXProxy;
import com.gensym.com.Guid;
import com.gensym.com.NativeMethodBroker;
import com.gensym.common.openpojo.AwtMockRandomGenerator;
import com.openpojo.random.RandomGenerator;
import com.openpojo.reflection.filters.FilterClassName;
import com.openpojo.reflection.impl.PojoClassFactory;
import com.openpojo.registry.ServiceRegistrar;
import com.openpojo.validation.Validator;
import com.openpojo.validation.ValidatorBuilder;
import com.openpojo.validation.test.impl.GetterTester;
import com.openpojo.validation.test.impl.SetterTester;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.powermock.core.classloader.annotations.PrepareForTest;
import org.powermock.modules.junit4.PowerMockRunner;

import java.util.Collection;
import java.util.Collections;
import java.util.Date;
import java.util.Random;

import static org.mockito.Mockito.mock;
import static org.mockito.Mockito.when;
import static org.powermock.api.mockito.PowerMockito.mockStatic;

@RunWith(PowerMockRunner.class)
@PrepareForTest({NativeMethodBroker.class, ActiveXProxy.class})
public class PojoTest {

    @Before
    public void setUp() {
        mockStatic(ActiveXProxy.class);
        mockStatic(NativeMethodBroker.class);
        when(NativeMethodBroker.loadLibrary()).thenReturn(true);
    }

    @Test
    public void testSettersAndGetters() {
        ServiceRegistrar.getInstance().getRandomGeneratorService().registerRandomGenerator(new AwtMockRandomGenerator
                ());
        ServiceRegistrar.getInstance().getRandomGeneratorService().registerRandomGenerator(new RandomGenerator() {
            @Override
            public Collection<Class<?>> getTypes() {
                return Collections.singletonList(ActiveXProxy.class);
            }

            @Override
            public Object doGenerate(Class<?> type) {
                return mock(ActiveXProxy.class);
            }
        });
        ServiceRegistrar.getInstance().getRandomGeneratorService().registerRandomGenerator(new RandomGenerator() {

            private final Random RANDOM = new Random(new Date().getTime());

            @Override
            public Collection<Class<?>> getTypes() {
                return Collections.singletonList(Guid.class);
            }

            @Override
            public Object doGenerate(Class<?> type) {
                return new Guid(RANDOM.nextInt(),
                        RANDOM.nextInt(),
                        RANDOM.nextInt(),
                        RANDOM.nextInt(),
                        RANDOM.nextInt(),
                        RANDOM.nextInt(),
                        RANDOM.nextInt(),
                        RANDOM.nextInt(),
                        RANDOM.nextInt(),
                        RANDOM.nextInt(),
                        RANDOM.nextInt());
            }
        });
        final Validator validator = ValidatorBuilder.create()
                .with(new GetterTester())
                .with(new SetterTester())
                .build();
        validator.validate(PojoClassFactory.getPojoClasses("com.gensym.com.beans.excel12", new FilterClassName("^(?!" +
                ".*Test)")));
    }
}