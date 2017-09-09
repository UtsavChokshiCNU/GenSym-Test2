package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class UiClientSessionImplTest extends G2TestBase<UiClientSessionImpl> {

    @Override
    protected Class<UiClientSessionImpl> forClass() {
        return UiClientSessionImpl.class;
    }

    @Test
    public void test_setUiClientSessionUserMode_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setUiClientSessionUserMode(getStub(com.gensym.util.Symbol.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.UI_CLIENT_SESSION_USER_MODE_)).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }
    @Test
    public void test_getUiClientSessionUserMode_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.UI_CLIENT_SESSION_USER_MODE_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getUiClientSessionUserMode()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_getUiClientSessionUserName_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.UI_CLIENT_SESSION_USER_NAME_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getUiClientSessionUserName()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_getUiClientSessionUserNameInOperatingSystem_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.UI_CLIENT_SESSION_USER_NAME_IN_OPERATING_SYSTEM_, "ABC");

        assertThat(instance.getUiClientSessionUserNameInOperatingSystem()).isEqualTo("ABC");
    }


    @Test
    public void test_getUiClientSessionTimeOfLastConnection_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.UI_CLIENT_SESSION_TIME_OF_LAST_CONNECTION_, getStub(com.gensym.util.Structure.class));

        assertThat(instance.getUiClientSessionTimeOfLastConnection()).isEqualTo(getStub(com.gensym.util.Structure.class));
    }


    @Test
    public void test_getUiClientSessionNetworkHostName_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.UI_CLIENT_SESSION_NETWORK_HOST_NAME_, "ABC");

        assertThat(instance.getUiClientSessionNetworkHostName()).isEqualTo("ABC");
    }


    @Test
    public void test_getUiClientSessionOperatingSystemType_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.UI_CLIENT_SESSION_OPERATING_SYSTEM_TYPE_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getUiClientSessionOperatingSystemType()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_getUiClientSessionUserIsValid_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.UI_CLIENT_SESSION_USER_IS_VALID_, false);

        assertThat(instance.getUiClientSessionUserIsValid()).isEqualTo(false);
    }


    @Test
    public void test_getUiClientSessionModeIsValid_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.UI_CLIENT_SESSION_MODE_IS_VALID_, false);

        assertThat(instance.getUiClientSessionModeIsValid()).isEqualTo(false);
    }


    @Test
    public void test_getUiClientInterface_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.UI_CLIENT_INTERFACE_, "ABC");

        assertThat(instance.getUiClientInterface()).isEqualTo("ABC");
    }


    @Test
    public void test_getUsesFloatingLicense_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.USES_FLOATING_LICENSE_, false);

        assertThat(instance.getUsesFloatingLicense()).isEqualTo(false);
    }


    @Test
    public void test_getUiClientModeIsValid_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.UI_CLIENT_MODE_IS_VALID_, false);

        assertThat(instance.getUiClientModeIsValid()).isEqualTo(false);
    }


    @Test
    public void test_getUiClientUserIsValid_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.UI_CLIENT_USER_IS_VALID_, false);

        assertThat(instance.getUiClientUserIsValid()).isEqualTo(false);
    }


    @Test
    public void test_getUiClientConnectionStatus_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.UI_CLIENT_CONNECTION_STATUS_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getUiClientConnectionStatus()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_getUiClientSpecificLanguage_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.UI_CLIENT_SPECIFIC_LANGUAGE_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getUiClientSpecificLanguage()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_getUiClientUserNameInOperatingSystem_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.UI_CLIENT_USER_NAME_IN_OPERATING_SYSTEM_, "ABC");

        assertThat(instance.getUiClientUserNameInOperatingSystem()).isEqualTo("ABC");
    }


    @Test
    public void test_getUiClientTimeOfLastConnection_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.UI_CLIENT_TIME_OF_LAST_CONNECTION_, getStub(com.gensym.util.Structure.class));

        assertThat(instance.getUiClientTimeOfLastConnection()).isEqualTo(getStub(com.gensym.util.Structure.class));
    }


    @Test
    public void test_getUiClientOperatingSystemType_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.UI_CLIENT_OPERATING_SYSTEM_TYPE_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getUiClientOperatingSystemType()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_getUiClientRemoteHostName_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.UI_CLIENT_REMOTE_HOST_NAME_, "ABC");

        assertThat(instance.getUiClientRemoteHostName()).isEqualTo("ABC");
    }


    @Test
    public void test_getUiClientUserName_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.UI_CLIENT_USER_NAME_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getUiClientUserName()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_setUiClientUserMode_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setUiClientUserMode(getStub(com.gensym.util.Symbol.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.UI_CLIENT_USER_MODE_)).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }
    @Test
    public void test_getUiClientUserMode_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.UI_CLIENT_USER_MODE_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getUiClientUserMode()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


}