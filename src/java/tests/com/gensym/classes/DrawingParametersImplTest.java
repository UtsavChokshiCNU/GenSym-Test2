package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class DrawingParametersImplTest extends G2TestBase<DrawingParametersImpl> {

    @Override
    protected Class<DrawingParametersImpl> forClass() {
        return DrawingParametersImpl.class;
    }

    @Test
    public void test_setAllowScheduledDrawing_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setAllowScheduledDrawing(false);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.ALLOW_SCHEDULED_DRAWINGQ_)).isEqualTo(false);
    }
    @Test
    public void test_getAllowScheduledDrawing_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.ALLOW_SCHEDULED_DRAWINGQ_, false);

        assertThat(instance.getAllowScheduledDrawing()).isEqualTo(false);
    }


    @Test
    public void test_setPaintMode_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setPaintMode(false);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.PAINT_MODEQ_)).isEqualTo(false);
    }
    @Test
    public void test_getPaintMode_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.PAINT_MODEQ_, false);

        assertThat(instance.getPaintMode()).isEqualTo(false);
    }


    @Test
    public void test_setImagePalette_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setImagePalette("ABC");

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.IMAGE_PALETTE_)).isEqualTo("ABC");
    }
    @Test
    public void test_getImagePalette_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.IMAGE_PALETTE_, "ABC");

        assertThat(instance.getImagePalette()).isEqualTo("ABC");
    }


    @Test
    public void test_setShowSelectionHandles_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setShowSelectionHandles(false);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.SHOW_SELECTION_HANDLES_)).isEqualTo(false);
    }
    @Test
    public void test_getShowSelectionHandles_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.SHOW_SELECTION_HANDLES_, false);

        assertThat(instance.getShowSelectionHandles()).isEqualTo(false);
    }


    @Test
    public void test_setPrimarySelectionColor_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setPrimarySelectionColor(getStub(com.gensym.util.Symbol.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.PRIMARY_SELECTION_COLOR_)).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }
    @Test
    public void test_getPrimarySelectionColor_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.PRIMARY_SELECTION_COLOR_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getPrimarySelectionColor()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_setSecondarySelectionColor_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setSecondarySelectionColor(getStub(com.gensym.util.Symbol.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.SECONDARY_SELECTION_COLOR_)).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }
    @Test
    public void test_getSecondarySelectionColor_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.SECONDARY_SELECTION_COLOR_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getSecondarySelectionColor()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_setAlignmentGrid_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setAlignmentGrid(getStub(com.gensym.util.Structure.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.ALIGNMENT_GRID_)).isEqualTo(getStub(com.gensym.util.Structure.class));
    }
    @Test
    public void test_getAlignmentGrid_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.ALIGNMENT_GRID_, getStub(com.gensym.util.Structure.class));

        assertThat(instance.getAlignmentGrid()).isEqualTo(getStub(com.gensym.util.Structure.class));
    }


}