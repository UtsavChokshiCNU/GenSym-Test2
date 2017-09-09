package com.gensym.common.openpojo;

import com.openpojo.log.LoggerFactory;
import com.openpojo.random.RandomFactory;
import com.openpojo.reflection.PojoClass;
import com.openpojo.reflection.PojoField;
import com.openpojo.validation.affirm.Affirm;
import com.openpojo.validation.utils.IdentityHandlerStub;
import com.openpojo.validation.utils.ValidationHelper;

import static org.mockito.Mockito.mock;

public class MockingGetterTester extends MockingTester {

    public MockingGetterTester(Class<?>... classesToMock) {
        super(classesToMock);
    }

    @Override
    public void run(PojoClass pojoClass) {
        final Object classInstance = ValidationHelper.getBasicInstance(pojoClass);
        for (final PojoField fieldEntry : pojoClass.getPojoFields()) {
            if (fieldEntry.hasGetter()) {
                Object value = fieldEntry.get(classInstance);

                if (!fieldEntry.isFinal()) {
                    value = shouldBeMocked(fieldEntry) ? mock(fieldEntry.getType()) : RandomFactory.getRandomValue(fieldEntry);
                    fieldEntry.set(classInstance, value);
                }

                IdentityHandlerStub.registerIdentityHandlerStubForValue(value);

                LoggerFactory.getLogger(this.getClass()).debug("Testing Field [{0}] with value [{1}]", fieldEntry, value);

                Affirm.affirmEquals("Getter returned non equal value for field=[" + fieldEntry + "]", value,
                        fieldEntry.invokeGetter(classInstance));
                IdentityHandlerStub.unregisterIdentityHandlerStubForValue(value);
            } else {
                LoggerFactory.getLogger(this.getClass()).debug("Field [{0}] has no getter skipping", fieldEntry);
            }
        }
    }
}
