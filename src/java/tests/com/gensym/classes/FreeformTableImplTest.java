package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class FreeformTableImplTest extends G2TestBase<FreeformTableImpl> {

    @Override
    protected Class<FreeformTableImpl> forClass() {
        return FreeformTableImpl.class;
    }

    @Test
    public void test_setTableSize_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setTableSize(getStub(com.gensym.util.Structure.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.TABLE_SIZE_)).isEqualTo(getStub(com.gensym.util.Structure.class));
    }
    @Test
    public void test_getTableSize_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.TABLE_SIZE_, getStub(com.gensym.util.Structure.class));

        assertThat(instance.getTableSize()).isEqualTo(getStub(com.gensym.util.Structure.class));
    }


    @Test
    public void test_setTableCells_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setTableCells(getStub(com.gensym.util.Sequence.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.TABLE_CELLS_)).isEqualTo(getStub(com.gensym.util.Sequence.class));
    }
    @Test
    public void test_getTableCells_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.TABLE_CELLS_, getStub(com.gensym.util.Sequence.class));

        assertThat(instance.getTableCells()).isEqualTo(getStub(com.gensym.util.Sequence.class));
    }


    @Test
    public void test_setEvaluationAttributes_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setEvaluationAttributes(getStub(com.gensym.util.Structure.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.EVALUATION_ATTRIBUTES_)).isEqualTo(getStub(com.gensym.util.Structure.class));
    }
    @Test
    public void test_getEvaluationAttributes_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.EVALUATION_ATTRIBUTES_, getStub(com.gensym.util.Structure.class));

        assertThat(instance.getEvaluationAttributes()).isEqualTo(getStub(com.gensym.util.Structure.class));
    }


    @Test
    public void test_setSizeInWorkspace_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setSizeInWorkspace(getStub(com.gensym.util.Structure.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.SIZE_IN_WORKSPACE_)).isEqualTo(getStub(com.gensym.util.Structure.class));
    }
    @Test
    public void test_getSizeInWorkspace_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.SIZE_IN_WORKSPACE_, getStub(com.gensym.util.Structure.class));

        assertThat(instance.getSizeInWorkspace()).isEqualTo(getStub(com.gensym.util.Structure.class));
    }


    @Test
    public void test_setDefaultCellFormat_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setDefaultCellFormat(getStub(com.gensym.util.Structure.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.DEFAULT_CELL_FORMAT_)).isEqualTo(getStub(com.gensym.util.Structure.class));
    }
    @Test
    public void test_getDefaultCellFormat_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.DEFAULT_CELL_FORMAT_, getStub(com.gensym.util.Structure.class));

        assertThat(instance.getDefaultCellFormat()).isEqualTo(getStub(com.gensym.util.Structure.class));
    }


    @Test
    public void test_setDefaultEvaluationSetting_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setDefaultEvaluationSetting(getStub(com.gensym.util.Structure.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.DEFAULT_EVALUATION_SETTING_)).isEqualTo(getStub(com.gensym.util.Structure.class));
    }
    @Test
    public void test_getDefaultEvaluationSetting_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.DEFAULT_EVALUATION_SETTING_, getStub(com.gensym.util.Structure.class));

        assertThat(instance.getDefaultEvaluationSetting()).isEqualTo(getStub(com.gensym.util.Structure.class));
    }


    @Test
    public void test_setItemConfiguration_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setItemConfiguration(getStub(com.gensym.util.Sequence.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.ITEM_CONFIGURATION_)).isEqualTo(getStub(com.gensym.util.Sequence.class));
    }
    @Test
    public void test_getItemConfiguration_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.ITEM_CONFIGURATION_, getStub(com.gensym.util.Sequence.class));

        assertThat(instance.getItemConfiguration()).isEqualTo(getStub(com.gensym.util.Sequence.class));
    }


    @Test
    public void test_setNames_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setNames("ABC");

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.NAMES_)).isEqualTo("ABC");
    }
    @Test
    public void test_getNames_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.NAMES_, "ABC");

        assertThat(instance.getNames()).isEqualTo("ABC");
    }


    @Test
    public void test_getLayerPosition_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.LAYER_POSITION_, 42);

        assertThat(instance.getLayerPosition()).isEqualTo(42);
    }


    @Test
    public void test_setFollowingItemInWorkspaceLayering_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setFollowingItemInWorkspaceLayering(getStub(com.gensym.classes.Block.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.FOLLOWING_ITEM_IN_WORKSPACE_LAYERING_)).isEqualTo(getStub(com.gensym.classes.Block.class));
    }
    @Test
    public void test_getFollowingItemInWorkspaceLayering_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.FOLLOWING_ITEM_IN_WORKSPACE_LAYERING_, getStub(com.gensym.classes.Block.class));

        assertThat(instance.getFollowingItemInWorkspaceLayering()).isEqualTo(getStub(com.gensym.classes.Block.class));
    }


    @Test
    public void test_setPositionInWorkspace_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setPositionInWorkspace(getStub(com.gensym.util.Structure.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.POSITION_IN_WORKSPACE_)).isEqualTo(getStub(com.gensym.util.Structure.class));
    }
    @Test
    public void test_getPositionInWorkspace_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.POSITION_IN_WORKSPACE_, getStub(com.gensym.util.Structure.class));

        assertThat(instance.getPositionInWorkspace()).isEqualTo(getStub(com.gensym.util.Structure.class));
    }


    @Test
    public void test_setRelationships_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setRelationships(getStub(com.gensym.util.Sequence.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.RELATIONSHIPS_)).isEqualTo(getStub(com.gensym.util.Sequence.class));
    }
    @Test
    public void test_getRelationships_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.RELATIONSHIPS_, getStub(com.gensym.util.Sequence.class));

        assertThat(instance.getRelationships()).isEqualTo(getStub(com.gensym.util.Sequence.class));
    }


    @Test
    public void test_getItemNotes_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.ITEM_NOTES_, getStub(com.gensym.util.Sequence.class));

        assertThat(instance.getItemNotes()).isEqualTo(getStub(com.gensym.util.Sequence.class));
    }


    @Test
    public void test_getContainingModule_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.CONTAINING_MODULE_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getContainingModule()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_getItemActive_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.ITEM_ACTIVE_, false);

        assertThat(instance.getItemActive()).isEqualTo(false);
    }


    @Test
    public void test_getItemStatus_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.ITEM_STATUS_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getItemStatus()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_getInstantiateForClass_ReturnsExpected() throws Exception {
        boolean expected = mockClassAttributeValue(SystemAttributeSymbols.INSTANTIATE_, boolean.class);

        assertThat(instance.getInstantiateForClass()).isEqualTo(expected);
    }


    @Test
    public void test_getIncludeInMenusForClass_ReturnsExpected() throws Exception {
        boolean expected = mockClassAttributeValue(SystemAttributeSymbols.INCLUDE_IN_MENUS_, boolean.class);

        assertThat(instance.getIncludeInMenusForClass()).isEqualTo(expected);
    }


    @Test
    public void test_getSystemMenuChoicesForClass_ReturnsExpected() throws Exception {
        java.lang.Object expected = mockClassAttributeValue(SystemAttributeSymbols.SYSTEM_MENU_CHOICES_, java.lang.Object.class);

        assertThat(instance.getSystemMenuChoicesForClass()).isEqualTo(expected);
    }


}