package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class ModuleInformationImplTest extends G2TestBase<ModuleInformationImpl> {

    @Override
    protected Class<ModuleInformationImpl> forClass() {
        return ModuleInformationImpl.class;
    }

    @Test
    public void test_setModuleFileName_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setModuleFileName("ABC");

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.MODULE_FILE_NAME_)).isEqualTo("ABC");
    }
    @Test
    public void test_getModuleFileName_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.MODULE_FILE_NAME_, "ABC");

        assertThat(instance.getModuleFileName()).isEqualTo("ABC");
    }


    @Test
    public void test_setTopLevelModule_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setTopLevelModule(getStub(com.gensym.util.Symbol.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.TOP_LEVEL_MODULE_)).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }
    @Test
    public void test_getTopLevelModule_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.TOP_LEVEL_MODULE_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getTopLevelModule()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_setDirectlyRequiredModules_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setDirectlyRequiredModules(getStub(com.gensym.util.Sequence.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.DIRECTLY_REQUIRED_MODULES_)).isEqualTo(getStub(com.gensym.util.Sequence.class));
    }
    @Test
    public void test_getDirectlyRequiredModules_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.DIRECTLY_REQUIRED_MODULES_, getStub(com.gensym.util.Sequence.class));

        assertThat(instance.getDirectlyRequiredModules()).isEqualTo(getStub(com.gensym.util.Sequence.class));
    }


    @Test
    public void test_setModuleAnnotations_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setModuleAnnotations(getStub(com.gensym.util.Sequence.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.MODULE_ANNOTATIONS_)).isEqualTo(getStub(com.gensym.util.Sequence.class));
    }
    @Test
    public void test_getModuleAnnotations_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.MODULE_ANNOTATIONS_, getStub(com.gensym.util.Sequence.class));

        assertThat(instance.getModuleAnnotations()).isEqualTo(getStub(com.gensym.util.Sequence.class));
    }


}