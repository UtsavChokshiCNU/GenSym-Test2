package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class RemoteItemImplTest extends G2TestBase<RemoteItemImpl> {

    @Override
    protected Class<RemoteItemImpl> forClass() {
        return RemoteItemImpl.class;
    }

    @Test
    public void test_getTransient_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.TRANSIENT_, false);

        assertThat(instance.getTransient()).isEqualTo(false);
    }


    @Test
    public void test_setManuallyDisabled_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setManuallyDisabled(false);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.MANUALLY_DISABLEDQ_)).isEqualTo(false);
    }
    @Test
    public void test_getManuallyDisabled_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.MANUALLY_DISABLEDQ_, false);

        assertThat(instance.getManuallyDisabled()).isEqualTo(false);
    }


    @Test
    public void test_getPermanent_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.PERMANENT_, false);

        assertThat(instance.getPermanent()).isEqualTo(false);
    }


    @Test
    public void test_setDoNotStripTextMark_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setDoNotStripTextMark(false);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.DO_NOT_STRIP_TEXT_MARK_)).isEqualTo(false);
    }
    @Test
    public void test_getDoNotStripTextMark_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.DO_NOT_STRIP_TEXT_MARK_, false);

        assertThat(instance.getDoNotStripTextMark()).isEqualTo(false);
    }


    @Test
    public void test_setStripTextMark_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setStripTextMark(false);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.STRIP_TEXT_MARK_)).isEqualTo(false);
    }
    @Test
    public void test_getStripTextMark_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.STRIP_TEXT_MARK_, false);

        assertThat(instance.getStripTextMark()).isEqualTo(false);
    }


    @Test
    public void test_getRepresentationType_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.REPRESENTATION_TYPE_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getRepresentationType()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_getTableHeader_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.TABLE_HEADER_, "ABC");

        assertThat(instance.getTableHeader()).isEqualTo("ABC");
    }


    @Test
    public void test_getItemWidth_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.ITEM_WIDTH_, 42);

        assertThat(instance.getItemWidth()).isEqualTo(42);
    }


    @Test
    public void test_getItemHeight_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.ITEM_HEIGHT_, 42);

        assertThat(instance.getItemHeight()).isEqualTo(42);
    }


    @Test
    public void test_getItemYPosition_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.ITEM_Y_POSITION_, 42);

        assertThat(instance.getItemYPosition()).isEqualTo(42);
    }


    @Test
    public void test_getItemXPosition_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.ITEM_X_POSITION_, 42);

        assertThat(instance.getItemXPosition()).isEqualTo(42);
    }


}