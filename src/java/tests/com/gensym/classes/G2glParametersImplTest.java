package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class G2glParametersImplTest extends G2TestBase<G2glParametersImpl> {

    @Override
    protected Class<G2glParametersImpl> forClass() {
        return G2glParametersImpl.class;
    }

    @Test
    public void test_setBreakOnAllExecutionFaults_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setBreakOnAllExecutionFaults(false);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.BREAK_ON_ALL_EXECUTION_FAULTS_)).isEqualTo(false);
    }
    @Test
    public void test_getBreakOnAllExecutionFaults_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.BREAK_ON_ALL_EXECUTION_FAULTS_, false);

        assertThat(instance.getBreakOnAllExecutionFaults()).isEqualTo(false);
    }


    @Test
    public void test_setSuppressUnspecifiedPartnerLinkVariableTypeFaults_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setSuppressUnspecifiedPartnerLinkVariableTypeFaults(false);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.SUPPRESS_UNSPECIFIED_PARTNER_LINK_VARIABLE_TYPE_FAULTS_)).isEqualTo(false);
    }
    @Test
    public void test_getSuppressUnspecifiedPartnerLinkVariableTypeFaults_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.SUPPRESS_UNSPECIFIED_PARTNER_LINK_VARIABLE_TYPE_FAULTS_, false);

        assertThat(instance.getSuppressUnspecifiedPartnerLinkVariableTypeFaults()).isEqualTo(false);
    }


    @Test
    public void test_setCompileTextElementsInSourceForExecutionDisplays_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setCompileTextElementsInSourceForExecutionDisplays(false);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.COMPILE_TEXT_ELEMENTS_IN_SOURCE_FOR_EXECUTION_DISPLAYS_)).isEqualTo(false);
    }
    @Test
    public void test_getCompileTextElementsInSourceForExecutionDisplays_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.COMPILE_TEXT_ELEMENTS_IN_SOURCE_FOR_EXECUTION_DISPLAYS_, false);

        assertThat(instance.getCompileTextElementsInSourceForExecutionDisplays()).isEqualTo(false);
    }


    @Test
    public void test_setDefaultThreadTokenColor_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setDefaultThreadTokenColor(getStub(com.gensym.util.Symbol.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.DEFAULT_THREAD_TOKEN_COLOR_)).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }
    @Test
    public void test_getDefaultThreadTokenColor_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.DEFAULT_THREAD_TOKEN_COLOR_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getDefaultThreadTokenColor()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


}