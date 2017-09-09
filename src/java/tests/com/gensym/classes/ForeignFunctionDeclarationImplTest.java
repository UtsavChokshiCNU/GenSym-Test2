package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class ForeignFunctionDeclarationImplTest extends G2TestBase<ForeignFunctionDeclarationImpl> {

    @Override
    protected Class<ForeignFunctionDeclarationImpl> forClass() {
        return ForeignFunctionDeclarationImpl.class;
    }

    @Test
    public void test_setAuthors_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setAuthors(getStub(com.gensym.util.Structure.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.AUTHORS_)).isEqualTo(getStub(com.gensym.util.Structure.class));
    }
    @Test
    public void test_getAuthors_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.AUTHORS_, getStub(com.gensym.util.Structure.class));

        assertThat(instance.getAuthors()).isEqualTo(getStub(com.gensym.util.Structure.class));
    }


    @Test
    public void test_getChangeLog_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.CHANGE_LOG_, getStub(com.gensym.util.Sequence.class));

        assertThat(instance.getChangeLog()).isEqualTo(getStub(com.gensym.util.Sequence.class));
    }


    @Test
    public void test_setNameInForeignImage_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setNameInForeignImage("ABC");

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.NAME_IN_FOREIGN_IMAGE_)).isEqualTo("ABC");
    }
    @Test
    public void test_getNameInForeignImage_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.NAME_IN_FOREIGN_IMAGE_, "ABC");

        assertThat(instance.getNameInForeignImage()).isEqualTo("ABC");
    }


    @Test
    public void test_setTimeoutInterval_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setTimeoutInterval("ABC");

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.TIMEOUT_INTERVAL_)).isEqualTo("ABC");
    }
    @Test
    public void test_getTimeoutInterval_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.TIMEOUT_INTERVAL_, "ABC");

        assertThat(instance.getTimeoutInterval()).isEqualTo("ABC");
    }


}