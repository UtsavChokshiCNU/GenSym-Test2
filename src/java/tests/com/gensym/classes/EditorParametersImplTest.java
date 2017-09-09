package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class EditorParametersImplTest extends G2TestBase<EditorParametersImpl> {

    @Override
    protected Class<EditorParametersImpl> forClass() {
        return EditorParametersImpl.class;
    }

    @Test
    public void test_setMaximumNumberOfNamesInMenus_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setMaximumNumberOfNamesInMenus(42);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.MAXIMUM_NUMBER_OF_NAMES_IN_MENUS_)).isEqualTo(42);
    }
    @Test
    public void test_getMaximumNumberOfNamesInMenus_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.MAXIMUM_NUMBER_OF_NAMES_IN_MENUS_, 42);

        assertThat(instance.getMaximumNumberOfNamesInMenus()).isEqualTo(42);
    }


    @Test
    public void test_setObjectNameMenusInUpperCase_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setObjectNameMenusInUpperCase(false);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.OBJECT_NAME_MENUS_IN_UPPER_CASEQ_)).isEqualTo(false);
    }
    @Test
    public void test_getObjectNameMenusInUpperCase_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.OBJECT_NAME_MENUS_IN_UPPER_CASEQ_, false);

        assertThat(instance.getObjectNameMenusInUpperCase()).isEqualTo(false);
    }


    @Test
    public void test_setNumberOfSpacesToInsertOnATab_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setNumberOfSpacesToInsertOnATab(42);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.NUMBER_OF_SPACES_TO_INSERT_ON_A_TAB_)).isEqualTo(42);
    }
    @Test
    public void test_getNumberOfSpacesToInsertOnATab_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.NUMBER_OF_SPACES_TO_INSERT_ON_A_TAB_, 42);

        assertThat(instance.getNumberOfSpacesToInsertOnATab()).isEqualTo(42);
    }


    @Test
    public void test_setMaximumNumberOfUndosToRemember_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setMaximumNumberOfUndosToRemember(42);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.MAXIMUM_NUMBER_OF_UNDOS_TO_REMEMBER_)).isEqualTo(42);
    }
    @Test
    public void test_getMaximumNumberOfUndosToRemember_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.MAXIMUM_NUMBER_OF_UNDOS_TO_REMEMBER_, 42);

        assertThat(instance.getMaximumNumberOfUndosToRemember()).isEqualTo(42);
    }


    @Test
    public void test_setMaximumNumberOfScrapsToKeep_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setMaximumNumberOfScrapsToKeep(42);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.MAXIMUM_NUMBER_OF_SCRAPS_TO_KEEP_)).isEqualTo(42);
    }
    @Test
    public void test_getMaximumNumberOfScrapsToKeep_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.MAXIMUM_NUMBER_OF_SCRAPS_TO_KEEP_, 42);

        assertThat(instance.getMaximumNumberOfScrapsToKeep()).isEqualTo(42);
    }


    @Test
    public void test_setMinimumWidthForEditBox_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setMinimumWidthForEditBox(42);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.MINIMUM_WIDTH_FOR_EDIT_BOX_)).isEqualTo(42);
    }
    @Test
    public void test_getMinimumWidthForEditBox_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.MINIMUM_WIDTH_FOR_EDIT_BOX_, 42);

        assertThat(instance.getMinimumWidthForEditBox()).isEqualTo(42);
    }


    @Test
    public void test_setAuthorRecordingEnabled_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setAuthorRecordingEnabled(false);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.AUTHOR_RECORDING_ENABLEDQ_)).isEqualTo(false);
    }
    @Test
    public void test_getAuthorRecordingEnabled_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.AUTHOR_RECORDING_ENABLEDQ_, false);

        assertThat(instance.getAuthorRecordingEnabled()).isEqualTo(false);
    }


    @Test
    public void test_setPopUpEditOperationsMenu_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setPopUpEditOperationsMenu(false);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.POP_UP_EDIT_OPERATIONS_MENU_)).isEqualTo(false);
    }
    @Test
    public void test_getPopUpEditOperationsMenu_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.POP_UP_EDIT_OPERATIONS_MENU_, false);

        assertThat(instance.getPopUpEditOperationsMenu()).isEqualTo(false);
    }


    @Test
    public void test_setButtonsForEditOperations_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setButtonsForEditOperations(false);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.BUTTONS_FOR_EDIT_OPERATIONS_)).isEqualTo(false);
    }
    @Test
    public void test_getButtonsForEditOperations_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.BUTTONS_FOR_EDIT_OPERATIONS_, false);

        assertThat(instance.getButtonsForEditOperations()).isEqualTo(false);
    }


    @Test
    public void test_setShowProcedureSignatures_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setShowProcedureSignatures(false);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.SHOW_PROCEDURE_SIGNATURESQ_)).isEqualTo(false);
    }
    @Test
    public void test_getShowProcedureSignatures_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.SHOW_PROCEDURE_SIGNATURESQ_, false);

        assertThat(instance.getShowProcedureSignatures()).isEqualTo(false);
    }


    @Test
    public void test_setSmartSpaceInsertion_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setSmartSpaceInsertion(false);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.SMART_SPACE_INSERTION_)).isEqualTo(false);
    }
    @Test
    public void test_getSmartSpaceInsertion_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.SMART_SPACE_INSERTION_, false);

        assertThat(instance.getSmartSpaceInsertion()).isEqualTo(false);
    }


    @Test
    public void test_setPreferNativeEditor_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setPreferNativeEditor(false);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.PREFER_NATIVE_EDITOR_)).isEqualTo(false);
    }
    @Test
    public void test_getPreferNativeEditor_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.PREFER_NATIVE_EDITOR_, false);

        assertThat(instance.getPreferNativeEditor()).isEqualTo(false);
    }


}