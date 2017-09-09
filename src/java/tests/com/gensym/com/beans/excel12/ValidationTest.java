package com.gensym.com.beans.excel12;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXDispatchable;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import org.junit.Before;
import org.junit.Test;

public class ValidationTest extends ActiveXDispatchableTestBase {

    private Validation component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new Validation(axProxy);
    }

    @Test
    public void test_QueryInterface_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60000000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(245), new Variant(511))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.QueryInterface(new Variant(245), new Variant(511));
                    }
                });
    }

    @Test
    public void test_AddRef_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60000001).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsLong(new Returns<Long>() {
                    @Override
                    public Long invoke() throws ActiveXException {
                        return component.AddRef();
                    }
                });
    }

    @Test
    public void test_Release_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60000002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsLong(new Returns<Long>() {
                    @Override
                    public Long invoke() throws ActiveXException {
                        return component.Release();
                    }
                });
    }

    @Test
    public void test_GetTypeInfoCount_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x60010000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(59))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfoCount(new Variant(59));
                    }
                });
    }

    @Test
    public void test_GetTypeInfo_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010001).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42L), new Variant(42L), new
                Variant(651))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfo(42L, 42L, new Variant(651));
                    }
                });
    }

    @Test
    public void test_GetIDsOfNames_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(338), new Variant(775), new
                Variant(42L), new Variant(42L), new Variant(498))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetIDsOfNames(new Variant(338), new Variant(775), 42L, 42L, new Variant(498));
                    }
                });
    }

    @Test
    public void test_Invoke_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010003).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(678), new
                Variant(42L), new Variant(42), new Variant(459), new Variant(366), new Variant(347), new Variant(609))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Invoke(42, new Variant(678), 42L, 42, new Variant(459), new Variant(366), new
                                Variant(347), new Variant(609));
                    }
                });
    }

    @Test
    public void test_getAxApplication_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x94).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<ExcelApplication>() {
                    @Override
                    public ExcelApplication invoke() throws ActiveXException {
                        return component.getAxApplication();
                    }
                });
    }

    @Test
    public void test_getAxCreator_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x95).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxCreator();
                    }
                });
    }

    @Test
    public void test_getAxParent_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x96).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.getAxParent();
                    }
                });
    }

    @Test
    public void test_Add_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xb5).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Add(42);
                    }
                });
    }

    @Test
    public void test_Add_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0xb5).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(586))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Add(42, new Variant(586));
                    }
                });
    }

    @Test
    public void test_Add_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0xb5).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(137), new Variant
                (624))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Add(42, new Variant(137), new Variant(624));
                    }
                });
    }

    @Test
    public void test_Add_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0xb5).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(167), new Variant
                (488), new Variant(789))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Add(42, new Variant(167), new Variant(488), new Variant(789));
                    }
                });
    }

    @Test
    public void test_Add_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0xb5).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(295), new Variant
                (402), new Variant(209), new Variant(137))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Add(42, new Variant(295), new Variant(402), new Variant(209), new Variant(137));
                    }
                });
    }

    @Test
    public void test_getAxAlertStyle_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x645).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxAlertStyle();
                    }
                });
    }

    @Test
    public void test_getAxIgnoreBlank_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x646).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxIgnoreBlank();
                    }
                });
    }

    @Test
    public void test_setAxIgnoreBlank_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x646).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxIgnoreBlank(false);
                    }
                });
    }

    @Test
    public void test_getAxIMEMode_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x647).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxIMEMode();
                    }
                });
    }

    @Test
    public void test_setAxIMEMode_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x647).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxIMEMode(42);
                    }
                });
    }

    @Test
    public void test_getAxInCellDropdown_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x648).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxInCellDropdown();
                    }
                });
    }

    @Test
    public void test_setAxInCellDropdown_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x648).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxInCellDropdown(false);
                    }
                });
    }

    @Test
    public void test_Delete_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x75).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Delete();
                    }
                });
    }

    @Test
    public void test_getAxErrorMessage_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x649).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxErrorMessage();
                    }
                });
    }

    @Test
    public void test_setAxErrorMessage_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x649).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("icVocCXJdF"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxErrorMessage("icVocCXJdF");
                    }
                });
    }

    @Test
    public void test_getAxErrorTitle_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x64a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxErrorTitle();
                    }
                });
    }

    @Test
    public void test_setAxErrorTitle_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x64a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("PdjuRPXcYj"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxErrorTitle("PdjuRPXcYj");
                    }
                });
    }

    @Test
    public void test_getAxInputMessage_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x64b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxInputMessage();
                    }
                });
    }

    @Test
    public void test_setAxInputMessage_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x64b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("IyUFWVcpYT"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxInputMessage("IyUFWVcpYT");
                    }
                });
    }

    @Test
    public void test_getAxInputTitle_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x64c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxInputTitle();
                    }
                });
    }

    @Test
    public void test_setAxInputTitle_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x64c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("XISxLspGhx"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxInputTitle("XISxLspGhx");
                    }
                });
    }

    @Test
    public void test_getAxFormula1_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x62b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxFormula1();
                    }
                });
    }

    @Test
    public void test_getAxFormula2_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x62c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxFormula2();
                    }
                });
    }

    @Test
    public void test_Modify_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x62d).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Modify();
                    }
                });
    }

    @Test
    public void test_Modify_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x62d).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(59))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Modify(new Variant(59));
                    }
                });
    }

    @Test
    public void test_Modify_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x62d).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(352), new Variant(971))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Modify(new Variant(352), new Variant(971));
                    }
                });
    }

    @Test
    public void test_Modify_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x62d).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(986), new Variant(985), new
                Variant(823))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Modify(new Variant(986), new Variant(985), new Variant(823));
                    }
                });
    }

    @Test
    public void test_Modify_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x62d).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(345), new Variant(433), new
                Variant(625), new Variant(601))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Modify(new Variant(345), new Variant(433), new Variant(625), new Variant(601));
                    }
                });
    }

    @Test
    public void test_Modify_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x62d).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(773), new Variant(738), new
                Variant(123), new Variant(148), new Variant(497))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Modify(new Variant(773), new Variant(738), new Variant(123), new Variant(148), new
                                Variant(497));
                    }
                });
    }

    @Test
    public void test_getAxOperator_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x31d).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxOperator();
                    }
                });
    }

    @Test
    public void test_getAxShowError_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x64d).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxShowError();
                    }
                });
    }

    @Test
    public void test_setAxShowError_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x64d).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxShowError(false);
                    }
                });
    }

    @Test
    public void test_getAxShowInput_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x64e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxShowInput();
                    }
                });
    }

    @Test
    public void test_setAxShowInput_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x64e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxShowInput(false);
                    }
                });
    }

    @Test
    public void test_getAxType_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxType();
                    }
                });
    }

    @Test
    public void test_getAxValue_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxValue();
                    }
                });
    }

}