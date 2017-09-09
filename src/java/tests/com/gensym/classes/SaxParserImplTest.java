package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class SaxParserImplTest extends G2TestBase<SaxParserImpl> {

    @Override
    protected Class<SaxParserImpl> forClass() {
        return SaxParserImpl.class;
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
    public void test_getNumberOfPendingCallbacks_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.NUMBER_OF_PENDING_CALLBACKS_, 42);

        assertThat(instance.getNumberOfPendingCallbacks()).isEqualTo(42);
    }


    @Test
    public void test_setStartDocumentProcedure_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setStartDocumentProcedure(getStub(com.gensym.util.Symbol.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.START_DOCUMENT_PROCEDURE_)).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }
    @Test
    public void test_getStartDocumentProcedure_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.START_DOCUMENT_PROCEDURE_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getStartDocumentProcedure()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_setEndDocumentProcedure_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setEndDocumentProcedure(getStub(com.gensym.util.Symbol.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.END_DOCUMENT_PROCEDURE_)).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }
    @Test
    public void test_getEndDocumentProcedure_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.END_DOCUMENT_PROCEDURE_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getEndDocumentProcedure()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_setStartElementProcedure_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setStartElementProcedure(getStub(com.gensym.util.Symbol.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.START_ELEMENT_PROCEDURE_)).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }
    @Test
    public void test_getStartElementProcedure_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.START_ELEMENT_PROCEDURE_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getStartElementProcedure()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_setEndElementProcedure_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setEndElementProcedure(getStub(com.gensym.util.Symbol.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.END_ELEMENT_PROCEDURE_)).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }
    @Test
    public void test_getEndElementProcedure_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.END_ELEMENT_PROCEDURE_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getEndElementProcedure()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_setCharactersProcedure_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setCharactersProcedure(getStub(com.gensym.util.Symbol.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.CHARACTERS_PROCEDURE_)).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }
    @Test
    public void test_getCharactersProcedure_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.CHARACTERS_PROCEDURE_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getCharactersProcedure()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_setCommentProcedure_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setCommentProcedure(getStub(com.gensym.util.Symbol.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.COMMENT_PROCEDURE_)).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }
    @Test
    public void test_getCommentProcedure_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.COMMENT_PROCEDURE_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getCommentProcedure()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_setWarningProcedure_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setWarningProcedure(getStub(com.gensym.util.Symbol.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.WARNING_PROCEDURE_)).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }
    @Test
    public void test_getWarningProcedure_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.WARNING_PROCEDURE_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getWarningProcedure()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_setErrorProcedure_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setErrorProcedure(getStub(com.gensym.util.Symbol.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.ERROR_PROCEDURE_)).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }
    @Test
    public void test_getErrorProcedure_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.ERROR_PROCEDURE_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getErrorProcedure()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_setFatalErrorProcedure_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setFatalErrorProcedure(getStub(com.gensym.util.Symbol.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.FATAL_ERROR_PROCEDURE_)).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }
    @Test
    public void test_getFatalErrorProcedure_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.FATAL_ERROR_PROCEDURE_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getFatalErrorProcedure()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


}