package com.gensym.com.beans.excel12;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXDispatchable;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import org.junit.Before;
import org.junit.Test;

public class AppEventsTest extends ActiveXDispatchableTestBase {

    private AppEvents component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new AppEvents(axProxy);
    }

    @Test
    public void test_QueryInterface_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60000000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(700), new Variant(966))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.QueryInterface(new Variant(700), new Variant(966));
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
                Variant(113))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfo(42L, 42L, new Variant(113));
                    }
                });
    }

    @Test
    public void test_GetIDsOfNames_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(155), new Variant(119), new
                Variant(42L), new Variant(42L), new Variant(393))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetIDsOfNames(new Variant(155), new Variant(119), 42L, 42L, new Variant(393));
                    }
                });
    }

    @Test
    public void test_Invoke_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010003).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(108), new
                Variant(42L), new Variant(42), new Variant(413), new Variant(165), new Variant(755), new Variant(852))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Invoke(42, new Variant(108), 42L, 42, new Variant(413), new Variant(165), new
                                Variant(755), new Variant(852));
                    }
                });
    }

    @Test
    public void test_NewWorkbook_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x61d).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(818))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.NewWorkbook(new Variant(818));
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
        ), new Variant(getMock(Range.class)), new Variant(418))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SheetBeforeDoubleClick(getMock(ActiveXDispatchable.class), getMock(Range.class),
                                new Variant(418));
                    }
                });
    }

    @Test
    public void test_SheetBeforeRightClick_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x618).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(ActiveXDispatchable.class)
        ), new Variant(getMock(Range.class)), new Variant(411))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SheetBeforeRightClick(getMock(ActiveXDispatchable.class), getMock(Range.class), new
                                Variant(411));
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

    @Test
    public void test_WorkbookOpen_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x61f).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(916))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.WorkbookOpen(new Variant(916));
                    }
                });
    }

    @Test
    public void test_WorkbookActivate_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x620).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(701))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.WorkbookActivate(new Variant(701));
                    }
                });
    }

    @Test
    public void test_WorkbookDeactivate_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x621).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(65))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.WorkbookDeactivate(new Variant(65));
                    }
                });
    }

    @Test
    public void test_WorkbookBeforeClose_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x622).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(380), new Variant(96))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.WorkbookBeforeClose(new Variant(380), new Variant(96));
                    }
                });
    }

    @Test
    public void test_WorkbookBeforeSave_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x623).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(646), new Variant(false), new
                Variant(289))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.WorkbookBeforeSave(new Variant(646), false, new Variant(289));
                    }
                });
    }

    @Test
    public void test_WorkbookBeforePrint_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x624).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(395), new Variant(34))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.WorkbookBeforePrint(new Variant(395), new Variant(34));
                    }
                });
    }

    @Test
    public void test_WorkbookNewSheet_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x625).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(949), new Variant(getMock
                (ActiveXDispatchable.class)))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.WorkbookNewSheet(new Variant(949), getMock(ActiveXDispatchable.class));
                    }
                });
    }

    @Test
    public void test_WorkbookAddinInstall_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x626).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(702))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.WorkbookAddinInstall(new Variant(702));
                    }
                });
    }

    @Test
    public void test_WorkbookAddinUninstall_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x627).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(637))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.WorkbookAddinUninstall(new Variant(637));
                    }
                });
    }

    @Test
    public void test_WindowResize_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x612).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(192), new Variant(getMock(Window
                .class)))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.WindowResize(new Variant(192), getMock(Window.class));
                    }
                });
    }

    @Test
    public void test_WindowActivate_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x614).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(489), new Variant(getMock(Window
                .class)))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.WindowActivate(new Variant(489), getMock(Window.class));
                    }
                });
    }

    @Test
    public void test_WindowDeactivate_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x615).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(466), new Variant(getMock(Window
                .class)))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.WindowDeactivate(new Variant(466), getMock(Window.class));
                    }
                });
    }

}