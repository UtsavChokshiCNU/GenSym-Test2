package com.gensym.classes.modules.jgidemo;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class REmployeeImplTest extends G2TestBase<REmployeeImpl> {

    @Override
    protected Class<REmployeeImpl> forClass() {
        return REmployeeImpl.class;
    }

    @Test
    public void test_setSocialSecurityNumber_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setSocialSecurityNumber(getStub(com.gensym.classes.modules.jgidemo.RaSymbolicParameter.class));

        assertThat(attributes.getAttributeValue(Symbol.intern("SOCIAL-SECURITY-NUMBER"))).isEqualTo(getStub(com.gensym.classes.modules.jgidemo.RaSymbolicParameter.class));
    }
    @Test
    public void test_getSocialSecurityNumber_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(Symbol.intern("SOCIAL-SECURITY-NUMBER"), getStub(com.gensym.classes.modules.jgidemo.RaSymbolicParameter.class));

        assertThat(instance.getSocialSecurityNumber()).isEqualTo(getStub(com.gensym.classes.modules.jgidemo.RaSymbolicParameter.class));
    }


    @Test
    public void test_setTitle_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setTitle(getStub(com.gensym.classes.modules.jgidemo.RaSymbolicParameter.class));

        assertThat(attributes.getAttributeValue(Symbol.intern("TITLE"))).isEqualTo(getStub(com.gensym.classes.modules.jgidemo.RaSymbolicParameter.class));
    }
    @Test
    public void test_getTitle_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(Symbol.intern("TITLE"), getStub(com.gensym.classes.modules.jgidemo.RaSymbolicParameter.class));

        assertThat(instance.getTitle()).isEqualTo(getStub(com.gensym.classes.modules.jgidemo.RaSymbolicParameter.class));
    }


    @Test
    public void test_setSupervisor_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setSupervisor(getStub(com.gensym.classes.modules.jgidemo.RaSymbolicParameter.class));

        assertThat(attributes.getAttributeValue(Symbol.intern("SUPERVISOR"))).isEqualTo(getStub(com.gensym.classes.modules.jgidemo.RaSymbolicParameter.class));
    }
    @Test
    public void test_getSupervisor_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(Symbol.intern("SUPERVISOR"), getStub(com.gensym.classes.modules.jgidemo.RaSymbolicParameter.class));

        assertThat(instance.getSupervisor()).isEqualTo(getStub(com.gensym.classes.modules.jgidemo.RaSymbolicParameter.class));
    }


    @Test
    public void test_setPayScale_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setPayScale(getStub(com.gensym.classes.modules.jgidemo.RaIntegerParameter.class));

        assertThat(attributes.getAttributeValue(Symbol.intern("PAY-SCALE"))).isEqualTo(getStub(com.gensym.classes.modules.jgidemo.RaIntegerParameter.class));
    }
    @Test
    public void test_getPayScale_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(Symbol.intern("PAY-SCALE"), getStub(com.gensym.classes.modules.jgidemo.RaIntegerParameter.class));

        assertThat(instance.getPayScale()).isEqualTo(getStub(com.gensym.classes.modules.jgidemo.RaIntegerParameter.class));
    }


}