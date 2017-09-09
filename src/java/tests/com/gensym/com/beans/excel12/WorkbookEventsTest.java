package com.gensym.com.beans.excel12;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXDispatchable;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import org.junit.Before;
import org.junit.Test;

public class WorkbookEventsTest extends ActiveXDispatchableTestBase {

    private WorkbookEvents component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new WorkbookEvents(axProxy);
    }

    @Test
    public void test_QueryInterface_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60000000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(476), new Variant(93))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.QueryInterface(new Variant(476), new Variant(93));
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
        on(0x60010000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(85))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfoCount(new Variant(85));
                    }
                });
    }

    @Test
    public void test_GetTypeInfo_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010001).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42L), new Variant(42L), new
                Variant(411))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfo(42L, 42L, new Variant(411));
                    }
                });
    }

    @Test
    public void test_GetIDsOfNames_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(57), new Variant(243), new
                Variant(42L), new Variant(42L), new Variant(212))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetIDsOfNames(new Variant(57), new Variant(243), 42L, 42L, new Variant(212));
                    }
                });
    }

    @Test
    public void test_Invoke_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010003).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(237), new
                Variant(42L), new Variant(42), new Variant(890), new Variant(203), new Variant(620), new Variant(709))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Invoke(42, new Variant(237), 42L, 42, new Variant(890), new Variant(203), new
                                Variant(620), new Variant(709));
                    }
                });
    }

    @Test
    public void test_Open_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2aa).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Open();
                    }
                });
    }

    @Test
    public void test_Activate_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x130).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Activate();
                    }
                });
    }

    @Test
    public void test_Deactivate_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5fa).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Deactivate();
                    }
                });
    }

    @Test
    public void test_BeforeClose_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x60a).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(27))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.BeforeClose(new Variant(27));
                    }
                });
    }

    @Test
    public void test_BeforeSave_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(false), new Variant(184))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.BeforeSave(false, new Variant(184));
                    }
                });
    }

    @Test
    public void test_BeforePrint_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x60d).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(871))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.BeforePrint(new Variant(871));
                    }
                });
    }

    @Test
    public void test_NewSheet_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x60e).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(ActiveXDispatchable.class)))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.NewSheet(getMock(ActiveXDispatchable.class));
                    }
                });
    }

    @Test
    public void test_AddinInstall_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x610).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.AddinInstall();
                    }
                });
    }

    @Test
    public void test_AddinUninstall_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x611).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.AddinUninstall();
                    }
                });
    }

    @Test
    public void test_WindowResize_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x612).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Window.class)))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.WindowResize(getMock(Window.class));
                    }
                });
    }

    @Test
    public void test_WindowActivate_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x614).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Window.class)))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.WindowActivate(getMock(Window.class));
                    }
                });
    }

    @Test
    public void test_WindowDeactivate_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x615).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Window.class)))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.WindowDeactivate(getMock(Window.class));
                    }
                });
    }

    @Test
    public void test_SheetSelectionChange_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x616).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(ActiveXDispatchable.class)
        ), new Variant(getMock(Range.class)))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SheetSelectionChange(getMock(ActiveXDispatchable.class), getMock(Range.class));
                    }
                });
    }

    @Test
    public void test_SheetBeforeDoubleClick_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x617).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(ActiveXDispatchable.class)
        ), new Variant(getMock(Range.class)), new Variant(463))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SheetBeforeDoubleClick(getMock(ActiveXDispatchable.class), getMock(Range.class),
                                new Variant(463));
                    }
                });
    }

    @Test
    public void test_SheetBeforeRightClick_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x618).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(ActiveXDispatchable.class)
        ), new Variant(getMock(Range.class)), new Variant(222))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SheetBeforeRightClick(getMock(ActiveXDispatchable.class), getMock(Range.class), new
                                Variant(222));
                    }
                });
    }

    @Test
    public void test_SheetActivate_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x619).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(ActiveXDispatchable.class)))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SheetActivate(getMock(ActiveXDispatchable.class));
                    }
                });
    }

    @Test
    public void test_SheetDeactivate_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x61a).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(ActiveXDispatchable.class)))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SheetDeactivate(getMock(ActiveXDispatchable.class));
                    }
                });
    }

    @Test
    public void test_SheetCalculate_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x61b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(ActiveXDispatchable.class)))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SheetCalculate(getMock(ActiveXDispatchable.class));
                    }
                });
    }

    @Test
    public void test_SheetChange_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x61c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(ActiveXDispatchable.class)
        ), new Variant(getMock(Range.class)))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SheetChange(getMock(ActiveXDispatchable.class), getMock(Range.class));
                    }
                });
    }

}