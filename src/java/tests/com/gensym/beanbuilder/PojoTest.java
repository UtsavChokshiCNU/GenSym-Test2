package com.gensym.beanbuilder;

import com.gensym.common.openpojo.AwtMockRandomGenerator;
import com.openpojo.reflection.impl.PojoClassFactory;
import com.openpojo.registry.ServiceRegistrar;
import com.openpojo.validation.Validator;
import com.openpojo.validation.ValidatorBuilder;
import com.openpojo.validation.test.impl.GetterTester;
import com.openpojo.validation.test.impl.SetterTester;
import org.junit.Test;

import java.util.List;

import static java.util.Arrays.asList;

public class PojoTest {

    @Test
    public void testSettersAndGetters() {
        ServiceRegistrar.getInstance().getRandomGeneratorService().registerRandomGenerator(new AwtMockRandomGenerator());
        final Validator validator = ValidatorBuilder.create()
                .with(new SetterTester())
                .with(new GetterTester())
                .build();
        List<Class<?>> classes = asList(
                AboutDialog.class,
                AttentionDialog.class,
                ConfirmDialog.class,
                Context.class,
                G2DownloadInterfaces.class,
                ImageDisplay.class,
                ImageDisplayBeanInfo.class,
                ItemBeanCreator.class,
                PropertyChangeSupport.class,
                RelativeURL.class,
                RunActiveXBeanPackager.class,
                VetoableChangeSupport.class
        );
        for (Class<?> clazz : classes) {
            validator.validate(PojoClassFactory.getPojoClass(clazz));
        }
    }
}