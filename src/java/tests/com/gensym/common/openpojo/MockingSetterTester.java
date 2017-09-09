package com.gensym.common.openpojo;

import com.openpojo.log.LoggerFactory;
import com.openpojo.random.RandomFactory;
import com.openpojo.reflection.PojoClass;
import com.openpojo.reflection.PojoField;
import com.openpojo.validation.affirm.Affirm;
import com.openpojo.validation.utils.IdentityHandlerStub;
import com.openpojo.validation.utils.ValidationHelper;

import static org.mockito.Mockito.mock;

public class MockingSetterTester extends MockingTester {

    public MockingSetterTester(Class<?>... classesToMock) {
        super(classesToMock);
    }

    @Override
    public void run(final PojoClass pojoClass) {
        final Object classInstance = ValidationHelper.getBasicInstance(pojoClass);
        for (final PojoField fieldEntry : pojoClass.getPojoFields()) {
            if (fieldEntry.hasSetter()) {
                final Object value = shouldBeMocked(fieldEntry) ? mock(fieldEntry.getType()) : RandomFactory.getRandomValue(fieldEntry);
                IdentityHandlerStub.registerIdentityHandlerStubForValue(value);
                LoggerFactory.getLogger(this.getClass()).debug("Testing Field [{0}] with random value [{1}]", fieldEntry, value);

                fieldEntry.invokeSetter(classInstance, value);

                Affirm.affirmEquals("Setter test failed, non equal value for field=[" + fieldEntry + "]", value,
                        fieldEntry.get(classInstance));

                IdentityHandlerStub.unregisterIdentityHandlerStubForValue(value);
            } else {
                LoggerFactory.getLogger(this.getClass()).debug("Field [{0}] has no setter skipping", fieldEntry);
            }
        }
    }
}
