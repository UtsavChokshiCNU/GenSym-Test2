package com.gensym.com.beans.excel12;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXDispatchable;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import org.junit.Before;
import org.junit.Test;

public class ToolbarButtonTest extends ActiveXDispatchableTestBase {

    private ToolbarButton component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new ToolbarButton(axProxy);
    }

    @Test
    public void test_QueryInterface_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60000000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(648), new Variant(449))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.QueryInterface(new Variant(648), new Variant(449));
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
        on(0x60010000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(601))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfoCount(new Variant(601));
                    }
                });
    }

    @Test
    public void test_GetTypeInfo_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010001).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42L), new Variant(42L), new
                Variant(905))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfo(42L, 42L, new Variant(905));
                    }
                });
    }

    @Test
    public void test_GetIDsOfNames_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(87), new Variant(604), new
                Variant(42L), new Variant(42L), new Variant(528))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetIDsOfNames(new Variant(87), new Variant(604), 42L, 42L, new Variant(528));
                    }
                });
    }

    @Test
    public void test_Invoke_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010003).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(558), new
                Variant(42L), new Variant(42), new Variant(989), new Variant(469), new Variant(841), new Variant(481))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Invoke(42, new Variant(558), 42L, 42, new Variant(989), new Variant(469), new
                                Variant(841), new Variant(481));
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
    public void test_getAxBuiltIn_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x229).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxBuiltIn();
                    }
                });
    }

    @Test
    public void test_getAxBuiltInFace_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x22a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxBuiltInFace();
                    }
                });
    }

    @Test
    public void test_setAxBuiltInFace_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x22a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxBuiltInFace(false);
                    }
                });
    }

    @Test
    public void test_Copy_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x227).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Toolbar.class)), new
                Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Copy(getMock(Toolbar.class), 42);
                    }
                });
    }

    @Test
    public void test_CopyFace_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3c6).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.CopyFace();
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
    public void test_Edit_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x232).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Edit();
                    }
                });
    }

    @Test
    public void test_getAxEnabled_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x258).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxEnabled();
                    }
                });
    }

    @Test
    public void test_setAxEnabled_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x258).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxEnabled(false);
                    }
                });
    }

    @Test
    public void test_getAxHelpContextID_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x163).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxHelpContextID();
                    }
                });
    }

    @Test
    public void test_setAxHelpContextID_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x163).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxHelpContextID(42);
                    }
                });
    }

    @Test
    public void test_getAxHelpFile_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x168).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxHelpFile();
                    }
                });
    }

    @Test
    public void test_setAxHelpFile_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x168).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("jdqPdIRzsk"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxHelpFile("jdqPdIRzsk");
                    }
                });
    }

    @Test
    public void test_getAxId_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x23a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxId();
                    }
                });
    }

    @Test
    public void test_getAxIsGap_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x231).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxIsGap();
                    }
                });
    }

    @Test
    public void test_Move_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x27d).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Toolbar.class)), new
                Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Move(getMock(Toolbar.class), 42);
                    }
                });
    }

    @Test
    public void test_getAxName_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxName();
                    }
                });
    }

    @Test
    public void test_setAxName_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x6e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("jLFMwoCecy"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxName("jLFMwoCecy");
                    }
                });
    }

    @Test
    public void test_getAxOnAction_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x254).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxOnAction();
                    }
                });
    }

    @Test
    public void test_setAxOnAction_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x254).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("HHPMfZiNgF"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxOnAction("HHPMfZiNgF");
                    }
                });
    }

    @Test
    public void test_PasteFace_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3c7).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PasteFace();
                    }
                });
    }

    @Test
    public void test_getAxPushed_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x230).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxPushed();
                    }
                });
    }

    @Test
    public void test_setAxPushed_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x230).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxPushed(false);
                    }
                });
    }

    @Test
    public void test_Reset_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x22b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Reset();
                    }
                });
    }

    @Test
    public void test_getAxStatusBar_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x182).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxStatusBar();
                    }
                });
    }

    @Test
    public void test_setAxStatusBar_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x182).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("NasJdfRdQR"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxStatusBar("NasJdfRdQR");
                    }
                });
    }

    @Test
    public void test_getAxWidth_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x7a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxWidth();
                    }
                });
    }

    @Test
    public void test_setAxWidth_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x7a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxWidth(42);
                    }
                });
    }

}