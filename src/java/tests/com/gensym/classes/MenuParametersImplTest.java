package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class MenuParametersImplTest extends G2TestBase<MenuParametersImpl> {

    @Override
    protected Class<MenuParametersImpl> forClass() {
        return MenuParametersImpl.class;
    }

    @Test
    public void test_setAlignmentForMenuChoices_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setAlignmentForMenuChoices(getStub(com.gensym.util.Symbol.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.ALIGNMENT_FOR_MENU_CHOICES_)).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }
    @Test
    public void test_getAlignmentForMenuChoices_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.ALIGNMENT_FOR_MENU_CHOICES_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getAlignmentForMenuChoices()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_setWhenToAllowMultipleMenus_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setWhenToAllowMultipleMenus(getStub(com.gensym.util.Symbol.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.WHEN_TO_ALLOW_MULTIPLE_MENUS_)).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }
    @Test
    public void test_getWhenToAllowMultipleMenus_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.WHEN_TO_ALLOW_MULTIPLE_MENUS_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getWhenToAllowMultipleMenus()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_setWalkingMenus_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setWalkingMenus(false);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.WALKING_MENUSQ_)).isEqualTo(false);
    }
    @Test
    public void test_getWalkingMenus_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.WALKING_MENUSQ_, false);

        assertThat(instance.getWalkingMenus()).isEqualTo(false);
    }


    @Test
    public void test_setAutomaticallyShowDeveloperMenuBar_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setAutomaticallyShowDeveloperMenuBar(getStub(com.gensym.util.Structure.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.AUTOMATICALLY_SHOW_DEVELOPER_MENU_BAR_)).isEqualTo(getStub(com.gensym.util.Structure.class));
    }
    @Test
    public void test_getAutomaticallyShowDeveloperMenuBar_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.AUTOMATICALLY_SHOW_DEVELOPER_MENU_BAR_, getStub(com.gensym.util.Structure.class));

        assertThat(instance.getAutomaticallyShowDeveloperMenuBar()).isEqualTo(getStub(com.gensym.util.Structure.class));
    }


}