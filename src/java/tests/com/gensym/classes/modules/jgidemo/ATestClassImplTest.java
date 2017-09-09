package com.gensym.classes.modules.jgidemo;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class ATestClassImplTest extends G2TestBase<ATestClassImpl> {

    @Override
    protected Class<ATestClassImpl> forClass() {
        return ATestClassImpl.class;
    }

    @Test
    public void test_setAInt_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setAInt(42);

        assertThat(attributes.getAttributeValue(Symbol.intern("A-INT"))).isEqualTo(42);
    }
    @Test
    public void test_getAInt_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(Symbol.intern("A-INT"), 42);

        assertThat(instance.getAInt()).isEqualTo(42);
    }


    @Test
    public void test_setAFloat_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setAFloat(42.32d);

        assertThat(attributes.getAttributeValue(Symbol.intern("A-FLOAT"))).isEqualTo(42.32d);
    }
    @Test
    public void test_getAFloat_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(Symbol.intern("A-FLOAT"), 42.32d);

        assertThat(instance.getAFloat()).isEqualTo(42.32d);
    }


    @Test
    public void test_setAText_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setAText("ABC");

        assertThat(attributes.getAttributeValue(Symbol.intern("A-TEXT"))).isEqualTo("ABC");
    }
    @Test
    public void test_getAText_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(Symbol.intern("A-TEXT"), "ABC");

        assertThat(instance.getAText()).isEqualTo("ABC");
    }


    @Test
    public void test_setASymbol_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setASymbol(getStub(com.gensym.util.Symbol.class));

        assertThat(attributes.getAttributeValue(Symbol.intern("A-SYMBOL"))).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }
    @Test
    public void test_getASymbol_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(Symbol.intern("A-SYMBOL"), getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getASymbol()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_setAThruthValue_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setAThruthValue(false);

        assertThat(attributes.getAttributeValue(Symbol.intern("A-THRUTH-VALUE"))).isEqualTo(false);
    }
    @Test
    public void test_getAThruthValue_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(Symbol.intern("A-THRUTH-VALUE"), false);

        assertThat(instance.getAThruthValue()).isEqualTo(false);
    }


    @Test
    public void test_setASequence_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setASequence(getStub(com.gensym.util.Sequence.class));

        assertThat(attributes.getAttributeValue(Symbol.intern("A-SEQUENCE"))).isEqualTo(getStub(com.gensym.util.Sequence.class));
    }
    @Test
    public void test_getASequence_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(Symbol.intern("A-SEQUENCE"), getStub(com.gensym.util.Sequence.class));

        assertThat(instance.getASequence()).isEqualTo(getStub(com.gensym.util.Sequence.class));
    }


    @Test
    public void test_setAStructure_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setAStructure(getStub(com.gensym.util.Structure.class));

        assertThat(attributes.getAttributeValue(Symbol.intern("A-STRUCTURE"))).isEqualTo(getStub(com.gensym.util.Structure.class));
    }
    @Test
    public void test_getAStructure_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(Symbol.intern("A-STRUCTURE"), getStub(com.gensym.util.Structure.class));

        assertThat(instance.getAStructure()).isEqualTo(getStub(com.gensym.util.Structure.class));
    }


    @Test
    public void test_getAuthorsForClass_ReturnsExpected() throws Exception {
        com.gensym.util.Structure expected = mockClassAttributeValue(SystemAttributeSymbols.AUTHORS_, com.gensym.util.Structure.class);

        assertThat(instance.getAuthorsForClass()).isEqualTo(expected);
    }


    @Test
    public void test_getChangeLogForClass_ReturnsExpected() throws Exception {
        com.gensym.util.Sequence expected = mockClassAttributeValue(SystemAttributeSymbols.CHANGE_LOG_, com.gensym.util.Sequence.class);

        assertThat(instance.getChangeLogForClass()).isEqualTo(expected);
    }


    @Test
    public void test_getClassNameForClass_ReturnsExpected() throws Exception {
        com.gensym.util.Symbol expected = mockClassAttributeValue(SystemAttributeSymbols.CLASS_NAME_, com.gensym.util.Symbol.class);

        assertThat(instance.getClassNameForClass()).isEqualTo(expected);
    }


    @Test
    public void test_getClassSpecificAttributesForClass_ReturnsExpected() throws Exception {
        com.gensym.util.Sequence expected = mockClassAttributeValue(SystemAttributeSymbols.CLASS_SPECIFIC_ATTRIBUTES_, com.gensym.util.Sequence.class);

        assertThat(instance.getClassSpecificAttributesForClass()).isEqualTo(expected);
    }


    @Test
    public void test_getClassRestrictionsForClass_ReturnsExpected() throws Exception {
        java.lang.Object expected = mockClassAttributeValue(SystemAttributeSymbols.CLASS_RESTRICTIONS_, java.lang.Object.class);

        assertThat(instance.getClassRestrictionsForClass()).isEqualTo(expected);
    }


    @Test
    public void test_getInstanceConfigurationForClass_ReturnsExpected() throws Exception {
        com.gensym.util.Sequence expected = mockClassAttributeValue(SystemAttributeSymbols.INSTANCE_CONFIGURATION_, com.gensym.util.Sequence.class);

        assertThat(instance.getInstanceConfigurationForClass()).isEqualTo(expected);
    }


    @Test
    public void test_getClassInheritancePathForClass_ReturnsExpected() throws Exception {
        com.gensym.util.Sequence expected = mockClassAttributeValue(SystemAttributeSymbols.CLASS_INHERITANCE_PATH_, com.gensym.util.Sequence.class);

        assertThat(instance.getClassInheritancePathForClass()).isEqualTo(expected);
    }


    @Test
    public void test_getInheritedAttributesForClass_ReturnsExpected() throws Exception {
        com.gensym.util.Sequence expected = mockClassAttributeValue(SystemAttributeSymbols.INHERITED_ATTRIBUTES_, com.gensym.util.Sequence.class);

        assertThat(instance.getInheritedAttributesForClass()).isEqualTo(expected);
    }


    @Test
    public void test_getSuperiorClassForClass_ReturnsExpected() throws Exception {
        java.lang.Object expected = mockClassAttributeValue(SystemAttributeSymbols.SUPERIOR_CLASS_, java.lang.Object.class);

        assertThat(instance.getSuperiorClassForClass()).isEqualTo(expected);
    }


    @Test
    public void test_getCapabilitiesAndRestrictionsForClass_ReturnsExpected() throws Exception {
        java.lang.Object expected = mockClassAttributeValue(SystemAttributeSymbols.CAPABILITIES_AND_RESTRICTIONS_, java.lang.Object.class);

        assertThat(instance.getCapabilitiesAndRestrictionsForClass()).isEqualTo(expected);
    }


    @Test
    public void test_getAttributesSpecificToClassForClass_ReturnsExpected() throws Exception {
        java.lang.Object expected = mockClassAttributeValue(SystemAttributeSymbols.ATTRIBUTES_SPECIFIC_TO_CLASS_, java.lang.Object.class);

        assertThat(instance.getAttributesSpecificToClassForClass()).isEqualTo(expected);
    }


    @Test
    public void test_getMenuOptionForClass_ReturnsExpected() throws Exception {
        java.lang.Object expected = mockClassAttributeValue(SystemAttributeSymbols.MENU_OPTION_, java.lang.Object.class);

        assertThat(instance.getMenuOptionForClass()).isEqualTo(expected);
    }


    @Test
    public void test_getDirectSuperiorClassesForClass_ReturnsExpected() throws Exception {
        com.gensym.util.Sequence expected = mockClassAttributeValue(SystemAttributeSymbols.DIRECT_SUPERIOR_CLASSES_, com.gensym.util.Sequence.class);

        assertThat(instance.getDirectSuperiorClassesForClass()).isEqualTo(expected);
    }


    @Test
    public void test_getChangeForClass_ReturnsExpected() throws Exception {
        java.lang.Object expected = mockClassAttributeValue(SystemAttributeSymbols.CHANGE_, java.lang.Object.class);

        assertThat(instance.getChangeForClass()).isEqualTo(expected);
    }


    @Test
    public void test_getAttributeInitializationsForClass_ReturnsExpected() throws Exception {
        com.gensym.util.Sequence expected = mockClassAttributeValue(SystemAttributeSymbols.ATTRIBUTE_INITIALIZATIONS_, com.gensym.util.Sequence.class);

        assertThat(instance.getAttributeInitializationsForClass()).isEqualTo(expected);
    }


    @Test
    public void test_getAttributeDisplaysForClass_ReturnsExpected() throws Exception {
        java.lang.Object expected = mockClassAttributeValue(SystemAttributeSymbols.ATTRIBUTE_DISPLAYS_, java.lang.Object.class);

        assertThat(instance.getAttributeDisplaysForClass()).isEqualTo(expected);
    }


    @Test
    public void test_getStubsForClass_ReturnsExpected() throws Exception {
        java.lang.Object expected = mockClassAttributeValue(SystemAttributeSymbols.STUBS_, java.lang.Object.class);

        assertThat(instance.getStubsForClass()).isEqualTo(expected);
    }


    @Test
    public void test_getDefaultSettingsForClass_ReturnsExpected() throws Exception {
        java.lang.Object expected = mockClassAttributeValue(SystemAttributeSymbols.DEFAULT_SETTINGS_, java.lang.Object.class);

        assertThat(instance.getDefaultSettingsForClass()).isEqualTo(expected);
    }


}