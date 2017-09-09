package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class WorkspaceImplTest extends G2TestBase<WorkspaceImpl> {

    @Override
    protected Class<WorkspaceImpl> forClass() {
        return WorkspaceImpl.class;
    }

    @Test
    public void test_setWorkspaceMargin_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setWorkspaceMargin(42);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.WORKSPACE_MARGIN_)).isEqualTo(42);
    }
    @Test
    public void test_getWorkspaceMargin_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.WORKSPACE_MARGIN_, 42);

        assertThat(instance.getWorkspaceMargin()).isEqualTo(42);
    }


    @Test
    public void test_setBackgroundImages_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setBackgroundImages(getStub(com.gensym.util.Sequence.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.BACKGROUND_IMAGES_)).isEqualTo(getStub(com.gensym.util.Sequence.class));
    }
    @Test
    public void test_getBackgroundImages_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.BACKGROUND_IMAGES_, getStub(com.gensym.util.Sequence.class));

        assertThat(instance.getBackgroundImages()).isEqualTo(getStub(com.gensym.util.Sequence.class));
    }


    @Test
    public void test_setFrameStyle_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setFrameStyle(getStub(com.gensym.util.Symbol.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.FRAME_STYLE_)).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }
    @Test
    public void test_getFrameStyle_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.FRAME_STYLE_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getFrameStyle()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_setTitleBarText_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setTitleBarText("ABC");

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.TITLE_BAR_TEXT_)).isEqualTo("ABC");
    }
    @Test
    public void test_getTitleBarText_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.TITLE_BAR_TEXT_, "ABC");

        assertThat(instance.getTitleBarText()).isEqualTo("ABC");
    }


    @Test
    public void test_setViewPreferences_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setViewPreferences(getStub(com.gensym.util.Structure.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.VIEW_PREFERENCES_)).isEqualTo(getStub(com.gensym.util.Structure.class));
    }
    @Test
    public void test_getViewPreferences_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.VIEW_PREFERENCES_, getStub(com.gensym.util.Structure.class));

        assertThat(instance.getViewPreferences()).isEqualTo(getStub(com.gensym.util.Structure.class));
    }


    @Test
    public void test_setPreferBufferedDrawing_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setPreferBufferedDrawing(false);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.PREFER_BUFFERED_DRAWING_)).isEqualTo(false);
    }
    @Test
    public void test_getPreferBufferedDrawing_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.PREFER_BUFFERED_DRAWING_, false);

        assertThat(instance.getPreferBufferedDrawing()).isEqualTo(false);
    }


}