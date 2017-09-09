package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class MethodDeclarationImplTest extends G2TestBase<MethodDeclarationImpl> {

    @Override
    protected Class<MethodDeclarationImpl> forClass() {
        return MethodDeclarationImpl.class;
    }

    @Test
    public void test_setRequiresCallNextMethod_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setRequiresCallNextMethod(false);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.REQUIRES_CALL_NEXT_METHODQ_)).isEqualTo(false);
    }
    @Test
    public void test_getRequiresCallNextMethod_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.REQUIRES_CALL_NEXT_METHODQ_, false);

        assertThat(instance.getRequiresCallNextMethod()).isEqualTo(false);
    }


}