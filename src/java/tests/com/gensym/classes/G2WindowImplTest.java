package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class G2WindowImplTest extends G2TestBase<G2WindowImpl> {

    @Override
    protected Class<G2WindowImpl> forClass() {
        return G2WindowImpl.class;
    }

    @Test
    public void test_setG2UserMode_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setG2UserMode(getStub(com.gensym.util.Symbol.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.G2_USER_MODE_)).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }
    @Test
    public void test_getG2UserMode_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.G2_USER_MODE_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getG2UserMode()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_setG2WindowSpecificLanguage_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setG2WindowSpecificLanguage(getStub(com.gensym.util.Symbol.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.G2_WINDOW_SPECIFIC_LANGUAGE_)).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }
    @Test
    public void test_getG2WindowSpecificLanguage_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.G2_WINDOW_SPECIFIC_LANGUAGE_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getG2WindowSpecificLanguage()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_getG2WindowManagementType_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.G2_WINDOW_MANAGEMENT_TYPE_, "ABC");

        assertThat(instance.getG2WindowManagementType()).isEqualTo("ABC");
    }


    @Test
    public void test_getG2WindowX_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.G2_WINDOW_X_, 42);

        assertThat(instance.getG2WindowX()).isEqualTo(42);
    }


    @Test
    public void test_getG2WindowY_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.G2_WINDOW_Y_, 42);

        assertThat(instance.getG2WindowY()).isEqualTo(42);
    }


    @Test
    public void test_getG2WindowWidth_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.G2_WINDOW_WIDTH_, 42);

        assertThat(instance.getG2WindowWidth()).isEqualTo(42);
    }


    @Test
    public void test_getG2WindowHeight_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.G2_WINDOW_HEIGHT_, 42);

        assertThat(instance.getG2WindowHeight()).isEqualTo(42);
    }


    @Test
    public void test_getG2WindowXResolution_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.G2_WINDOW_X_RESOLUTION_, 42);

        assertThat(instance.getG2WindowXResolution()).isEqualTo(42);
    }


    @Test
    public void test_getG2WindowYResolution_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.G2_WINDOW_Y_RESOLUTION_, 42);

        assertThat(instance.getG2WindowYResolution()).isEqualTo(42);
    }


    @Test
    public void test_getG2WindowRemoteHostName_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.G2_WINDOW_REMOTE_HOST_NAME_, "ABC");

        assertThat(instance.getG2WindowRemoteHostName()).isEqualTo("ABC");
    }


    @Test
    public void test_getG2WindowUserNameInOperatingSystem_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.G2_WINDOW_USER_NAME_IN_OPERATING_SYSTEM_, "ABC");

        assertThat(instance.getG2WindowUserNameInOperatingSystem()).isEqualTo("ABC");
    }


    @Test
    public void test_getG2WindowTimeOfLastConnection_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.G2_WINDOW_TIME_OF_LAST_CONNECTION_, getStub(com.gensym.util.Structure.class));

        assertThat(instance.getG2WindowTimeOfLastConnection()).isEqualTo(getStub(com.gensym.util.Structure.class));
    }


    @Test
    public void test_getG2WindowInitialWindowConfigurationString_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.G2_WINDOW_INITIAL_WINDOW_CONFIGURATION_STRING_, "ABC");

        assertThat(instance.getG2WindowInitialWindowConfigurationString()).isEqualTo("ABC");
    }


    @Test
    public void test_getG2WindowRerouteProblemReport_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.G2_WINDOW_REROUTE_PROBLEM_REPORT_, "ABC");

        assertThat(instance.getG2WindowRerouteProblemReport()).isEqualTo("ABC");
    }


    @Test
    public void test_getG2WindowOperatingSystemType_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.G2_WINDOW_OPERATING_SYSTEM_TYPE_, "ABC");

        assertThat(instance.getG2WindowOperatingSystemType()).isEqualTo("ABC");
    }


    @Test
    public void test_setShowOperatorLogbookInThisWindow_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setShowOperatorLogbookInThisWindow(false);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.SHOW_OPERATOR_LOGBOOK_IN_THIS_WINDOWQ_)).isEqualTo(false);
    }
    @Test
    public void test_getShowOperatorLogbookInThisWindow_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.SHOW_OPERATOR_LOGBOOK_IN_THIS_WINDOWQ_, false);

        assertThat(instance.getShowOperatorLogbookInThisWindow()).isEqualTo(false);
    }


    @Test
    public void test_getG2WindowUserIsValid_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.G2_WINDOW_USER_IS_VALID_, false);

        assertThat(instance.getG2WindowUserIsValid()).isEqualTo(false);
    }


    @Test
    public void test_getG2WindowModeIsValid_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.G2_WINDOW_MODE_IS_VALID_, false);

        assertThat(instance.getG2WindowModeIsValid()).isEqualTo(false);
    }


    @Test
    public void test_setMouseCursor_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setMouseCursor(getStub(com.gensym.util.Symbol.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.MOUSE_CURSOR_)).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }
    @Test
    public void test_getMouseCursor_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.MOUSE_CURSOR_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getMouseCursor()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_getG2WindowIsEmbedded_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.G2_WINDOW_IS_EMBEDDED_, false);

        assertThat(instance.getG2WindowIsEmbedded()).isEqualTo(false);
    }


    @Test
    public void test_getWindowHandles_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.WINDOW_HANDLES_, getStub(com.gensym.util.Sequence.class));

        assertThat(instance.getWindowHandles()).isEqualTo(getStub(com.gensym.util.Sequence.class));
    }


    @Test
    public void test_setSelectedWindowHandle_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setSelectedWindowHandle(42);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.SELECTED_WINDOW_HANDLE_)).isEqualTo(42);
    }
    @Test
    public void test_getSelectedWindowHandle_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.SELECTED_WINDOW_HANDLE_, 42);

        assertThat(instance.getSelectedWindowHandle()).isEqualTo(42);
    }


    @Test
    public void test_getG2WindowClientVersion_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.G2_WINDOW_CLIENT_VERSION_, getStub(com.gensym.util.Structure.class));

        assertThat(instance.getG2WindowClientVersion()).isEqualTo(getStub(com.gensym.util.Structure.class));
    }


    @Test
    public void test_getG2WindowUiStyle_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.G2_WINDOW_UI_STYLE_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getG2WindowUiStyle()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_setSelectedItems_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setSelectedItems(getStub(com.gensym.util.Sequence.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.SELECTED_ITEMS_)).isEqualTo(getStub(com.gensym.util.Sequence.class));
    }
    @Test
    public void test_getSelectedItems_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.SELECTED_ITEMS_, getStub(com.gensym.util.Sequence.class));

        assertThat(instance.getSelectedItems()).isEqualTo(getStub(com.gensym.util.Sequence.class));
    }


    @Test
    public void test_setSelectedWorkspace_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setSelectedWorkspace("ABC");

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.SELECTED_WORKSPACE_)).isEqualTo("ABC");
    }
    @Test
    public void test_getSelectedWorkspace_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.SELECTED_WORKSPACE_, "ABC");

        assertThat(instance.getSelectedWorkspace()).isEqualTo("ABC");
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