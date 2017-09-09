package com.gensym.classes;

import com.gensym.common.openpojo.AwtMockRandomGenerator;
import com.gensym.jgi.ConnectionResolver;
import com.openpojo.reflection.PojoClass;
import com.openpojo.reflection.PojoClassFilter;
import com.openpojo.reflection.filters.FilterChain;
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

import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;

import static org.powermock.api.mockito.PowerMockito.mockStatic;

@RunWith(PowerMockRunner.class)
@PrepareForTest({ConnectionResolver.class})
public class PojoTest {

    private static final Set<String> EXCLUSIONS = new HashSet<String>(Arrays.asList(
            "com.gensym.classes.ModuleImpl",
            "com.gensym.classes.G2_ExternalEventObjectRoot",
            "com.gensym.classes.ImageDefinitionImpl",
            "com.gensym.classes.ImageDefinitionSpecialImpl",
            "com.gensym.classes.MediaBinSpecialImpl",
            "com.gensym.classes.SystemClassDefinitionImpl",
            "com.gensym.classes.G2__BaseImpl",
            "com.gensym.classes.DefinitionSpecialImpl"));

    @Before
    public void setUp() {
        mockStatic(ConnectionResolver.class);
    }

    @Test
    public void testSettersAndGetters() {
        ServiceRegistrar.getInstance().getRandomGeneratorService().registerRandomGenerator(new AwtMockRandomGenerator
                ());
        final Validator validator = ValidatorBuilder.create()
                .with(new GetterTester())
                .with(new SetterTester())
                .build();
        validator.validate(PojoClassFactory.getPojoClasses("com.gensym.classes", new FilterChain(new FilterClassName
                ("^(?!.*Test)"),
                new PojoClassFilter() {
                    @Override
                    public boolean include(PojoClass pojoClass) {
                        String name = pojoClass.getName();
                        return !EXCLUSIONS.contains(name) &&
                                !name.contains("com.gensym.classes.KbImpl") &&
                                !name.contains("com.gensym.classes.G2_ItemWrapper");
                    }
                }
        )));
    }
}