package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class SavingParametersImplTest extends G2TestBase<SavingParametersImpl> {

    @Override
    protected Class<SavingParametersImpl> forClass() {
        return SavingParametersImpl.class;
    }

    @Test
    public void test_setDefaultPriorityForRuntimeSaving_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setDefaultPriorityForRuntimeSaving(getStub(com.gensym.util.Symbol.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.DEFAULT_PRIORITY_FOR_RUNTIME_SAVING_)).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }
    @Test
    public void test_getDefaultPriorityForRuntimeSaving_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.DEFAULT_PRIORITY_FOR_RUNTIME_SAVING_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getDefaultPriorityForRuntimeSaving()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_getIdentifierOfBasisKb_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.IDENTIFIER_OF_BASIS_KB_, "ABC");

        assertThat(instance.getIdentifierOfBasisKb()).isEqualTo("ABC");
    }


    @Test
    public void test_setKbFileComment_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setKbFileComment("ABC");

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.KB_FILE_COMMENT_)).isEqualTo("ABC");
    }
    @Test
    public void test_getKbFileComment_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.KB_FILE_COMMENT_, "ABC");

        assertThat(instance.getKbFileComment()).isEqualTo("ABC");
    }


    @Test
    public void test_setEnableKbChangeLogging_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setEnableKbChangeLogging(false);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.ENABLE_KB_CHANGE_LOGGING_)).isEqualTo(false);
    }
    @Test
    public void test_getEnableKbChangeLogging_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.ENABLE_KB_CHANGE_LOGGING_, false);

        assertThat(instance.getEnableKbChangeLogging()).isEqualTo(false);
    }


}