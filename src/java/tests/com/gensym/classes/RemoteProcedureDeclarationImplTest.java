package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class RemoteProcedureDeclarationImplTest extends G2TestBase<RemoteProcedureDeclarationImpl> {

    @Override
    protected Class<RemoteProcedureDeclarationImpl> forClass() {
        return RemoteProcedureDeclarationImpl.class;
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
    public void test_setNameInRemoteSystem_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setNameInRemoteSystem("ABC");

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.NAME_IN_REMOTE_SYSTEM_)).isEqualTo("ABC");
    }
    @Test
    public void test_getNameInRemoteSystem_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.NAME_IN_REMOTE_SYSTEM_, "ABC");

        assertThat(instance.getNameInRemoteSystem()).isEqualTo("ABC");
    }


}