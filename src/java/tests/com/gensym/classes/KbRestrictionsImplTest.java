package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class KbRestrictionsImplTest extends G2TestBase<KbRestrictionsImpl> {

    @Override
    protected Class<KbRestrictionsImpl> forClass() {
        return KbRestrictionsImpl.class;
    }

    @Test
    public void test_setMainMenuUserRestrictions_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setMainMenuUserRestrictions(getStub(com.gensym.util.Sequence.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.MAIN_MENU_USER_RESTRICTIONS_)).isEqualTo(getStub(com.gensym.util.Sequence.class));
    }
    @Test
    public void test_getMainMenuUserRestrictions_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.MAIN_MENU_USER_RESTRICTIONS_, getStub(com.gensym.util.Sequence.class));

        assertThat(instance.getMainMenuUserRestrictions()).isEqualTo(getStub(com.gensym.util.Sequence.class));
    }


    @Test
    public void test_setKeyboardCommandRestrictions_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setKeyboardCommandRestrictions(getStub(com.gensym.util.Sequence.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.KEYBOARD_COMMAND_RESTRICTIONS_)).isEqualTo(getStub(com.gensym.util.Sequence.class));
    }
    @Test
    public void test_getKeyboardCommandRestrictions_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.KEYBOARD_COMMAND_RESTRICTIONS_, getStub(com.gensym.util.Sequence.class));

        assertThat(instance.getKeyboardCommandRestrictions()).isEqualTo(getStub(com.gensym.util.Sequence.class));
    }


    @Test
    public void test_getInitialG2UserModeForThisKb_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.INITIAL_G2_USER_MODE_FOR_THIS_KB_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getInitialG2UserModeForThisKb()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_getAuthorizedOptionalModules_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.AUTHORIZED_OPTIONAL_MODULES_, getStub(com.gensym.util.Sequence.class));

        assertThat(instance.getAuthorizedOptionalModules()).isEqualTo(getStub(com.gensym.util.Sequence.class));
    }


    @Test
    public void test_setSimulatedOptionalModules_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setSimulatedOptionalModules("ABC");

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.SIMULATED_OPTIONAL_MODULES_)).isEqualTo("ABC");
    }
    @Test
    public void test_getSimulatedOptionalModules_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.SIMULATED_OPTIONAL_MODULES_, "ABC");

        assertThat(instance.getSimulatedOptionalModules()).isEqualTo("ABC");
    }


}