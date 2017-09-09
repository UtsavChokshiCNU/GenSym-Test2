package com.gensym.classes.modules.jgidemo;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class LotsOfAttsRootImplTest extends G2TestBase<LotsOfAttsRootImpl> {

    @Override
    protected Class<LotsOfAttsRootImpl> forClass() {
        return LotsOfAttsRootImpl.class;
    }

    @Test
    public void test_setSym1_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setSym1("ABC");

        assertThat(attributes.getAttributeValue(Symbol.intern("SYM-1"))).isEqualTo("ABC");
    }
    @Test
    public void test_getSym1_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(Symbol.intern("SYM-1"), "ABC");

        assertThat(instance.getSym1()).isEqualTo("ABC");
    }


    @Test
    public void test_setSym2_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setSym2("ABC");

        assertThat(attributes.getAttributeValue(Symbol.intern("SYM-2"))).isEqualTo("ABC");
    }
    @Test
    public void test_getSym2_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(Symbol.intern("SYM-2"), "ABC");

        assertThat(instance.getSym2()).isEqualTo("ABC");
    }


    @Test
    public void test_setSym18_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setSym18("ABC");

        assertThat(attributes.getAttributeValue(Symbol.intern("SYM-18"))).isEqualTo("ABC");
    }
    @Test
    public void test_getSym18_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(Symbol.intern("SYM-18"), "ABC");

        assertThat(instance.getSym18()).isEqualTo("ABC");
    }


    @Test
    public void test_setSym3_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setSym3("ABC");

        assertThat(attributes.getAttributeValue(Symbol.intern("SYM-3"))).isEqualTo("ABC");
    }
    @Test
    public void test_getSym3_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(Symbol.intern("SYM-3"), "ABC");

        assertThat(instance.getSym3()).isEqualTo("ABC");
    }


    @Test
    public void test_setSym19_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setSym19("ABC");

        assertThat(attributes.getAttributeValue(Symbol.intern("SYM-19"))).isEqualTo("ABC");
    }
    @Test
    public void test_getSym19_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(Symbol.intern("SYM-19"), "ABC");

        assertThat(instance.getSym19()).isEqualTo("ABC");
    }


    @Test
    public void test_setSym4_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setSym4("ABC");

        assertThat(attributes.getAttributeValue(Symbol.intern("SYM-4"))).isEqualTo("ABC");
    }
    @Test
    public void test_getSym4_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(Symbol.intern("SYM-4"), "ABC");

        assertThat(instance.getSym4()).isEqualTo("ABC");
    }


    @Test
    public void test_setSym111_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setSym111("ABC");

        assertThat(attributes.getAttributeValue(Symbol.intern("SYM-111"))).isEqualTo("ABC");
    }
    @Test
    public void test_getSym111_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(Symbol.intern("SYM-111"), "ABC");

        assertThat(instance.getSym111()).isEqualTo("ABC");
    }


    @Test
    public void test_setSym5_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setSym5("ABC");

        assertThat(attributes.getAttributeValue(Symbol.intern("SYM-5"))).isEqualTo("ABC");
    }
    @Test
    public void test_getSym5_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(Symbol.intern("SYM-5"), "ABC");

        assertThat(instance.getSym5()).isEqualTo("ABC");
    }


    @Test
    public void test_setSym122_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setSym122("ABC");

        assertThat(attributes.getAttributeValue(Symbol.intern("SYM-122"))).isEqualTo("ABC");
    }
    @Test
    public void test_getSym122_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(Symbol.intern("SYM-122"), "ABC");

        assertThat(instance.getSym122()).isEqualTo("ABC");
    }


    @Test
    public void test_setSym6_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setSym6("ABC");

        assertThat(attributes.getAttributeValue(Symbol.intern("SYM-6"))).isEqualTo("ABC");
    }
    @Test
    public void test_getSym6_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(Symbol.intern("SYM-6"), "ABC");

        assertThat(instance.getSym6()).isEqualTo("ABC");
    }


    @Test
    public void test_setSym133_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setSym133("ABC");

        assertThat(attributes.getAttributeValue(Symbol.intern("SYM-133"))).isEqualTo("ABC");
    }
    @Test
    public void test_getSym133_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(Symbol.intern("SYM-133"), "ABC");

        assertThat(instance.getSym133()).isEqualTo("ABC");
    }


    @Test
    public void test_setSym7_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setSym7("ABC");

        assertThat(attributes.getAttributeValue(Symbol.intern("SYM-7"))).isEqualTo("ABC");
    }
    @Test
    public void test_getSym7_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(Symbol.intern("SYM-7"), "ABC");

        assertThat(instance.getSym7()).isEqualTo("ABC");
    }


    @Test
    public void test_setSym144_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setSym144("ABC");

        assertThat(attributes.getAttributeValue(Symbol.intern("SYM-144"))).isEqualTo("ABC");
    }
    @Test
    public void test_getSym144_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(Symbol.intern("SYM-144"), "ABC");

        assertThat(instance.getSym144()).isEqualTo("ABC");
    }


    @Test
    public void test_setSym8_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setSym8("ABC");

        assertThat(attributes.getAttributeValue(Symbol.intern("SYM-8"))).isEqualTo("ABC");
    }
    @Test
    public void test_getSym8_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(Symbol.intern("SYM-8"), "ABC");

        assertThat(instance.getSym8()).isEqualTo("ABC");
    }


    @Test
    public void test_setSym155_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setSym155("ABC");

        assertThat(attributes.getAttributeValue(Symbol.intern("SYM-155"))).isEqualTo("ABC");
    }
    @Test
    public void test_getSym155_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(Symbol.intern("SYM-155"), "ABC");

        assertThat(instance.getSym155()).isEqualTo("ABC");
    }


    @Test
    public void test_setSym9_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setSym9("ABC");

        assertThat(attributes.getAttributeValue(Symbol.intern("SYM-9"))).isEqualTo("ABC");
    }
    @Test
    public void test_getSym9_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(Symbol.intern("SYM-9"), "ABC");

        assertThat(instance.getSym9()).isEqualTo("ABC");
    }


    @Test
    public void test_setSym166_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setSym166("ABC");

        assertThat(attributes.getAttributeValue(Symbol.intern("SYM-166"))).isEqualTo("ABC");
    }
    @Test
    public void test_getSym166_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(Symbol.intern("SYM-166"), "ABC");

        assertThat(instance.getSym166()).isEqualTo("ABC");
    }


    @Test
    public void test_setSym10_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setSym10("ABC");

        assertThat(attributes.getAttributeValue(Symbol.intern("SYM-10"))).isEqualTo("ABC");
    }
    @Test
    public void test_getSym10_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(Symbol.intern("SYM-10"), "ABC");

        assertThat(instance.getSym10()).isEqualTo("ABC");
    }


    @Test
    public void test_setSym177_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setSym177("ABC");

        assertThat(attributes.getAttributeValue(Symbol.intern("SYM-177"))).isEqualTo("ABC");
    }
    @Test
    public void test_getSym177_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(Symbol.intern("SYM-177"), "ABC");

        assertThat(instance.getSym177()).isEqualTo("ABC");
    }


    @Test
    public void test_setSym11_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setSym11("ABC");

        assertThat(attributes.getAttributeValue(Symbol.intern("SYM-11"))).isEqualTo("ABC");
    }
    @Test
    public void test_getSym11_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(Symbol.intern("SYM-11"), "ABC");

        assertThat(instance.getSym11()).isEqualTo("ABC");
    }


    @Test
    public void test_setSym188_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setSym188("ABC");

        assertThat(attributes.getAttributeValue(Symbol.intern("SYM-188"))).isEqualTo("ABC");
    }
    @Test
    public void test_getSym188_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(Symbol.intern("SYM-188"), "ABC");

        assertThat(instance.getSym188()).isEqualTo("ABC");
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