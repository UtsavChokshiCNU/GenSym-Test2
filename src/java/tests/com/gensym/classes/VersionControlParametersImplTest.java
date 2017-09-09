package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class VersionControlParametersImplTest extends G2TestBase<VersionControlParametersImpl> {

    @Override
    protected Class<VersionControlParametersImpl> forClass() {
        return VersionControlParametersImpl.class;
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