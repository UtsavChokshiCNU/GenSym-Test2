package com.gensym.com.beans.excel12;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXDispatchable;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import org.junit.Before;
import org.junit.Test;

public class PaneTest extends ActiveXDispatchableTestBase {

    private Pane component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new Pane(axProxy);
    }

    @Test
    public void test_QueryInterface_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60000000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(711), new Variant(110))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.QueryInterface(new Variant(711), new Variant(110));
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
        on(0x60010000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(226))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfoCount(new Variant(226));
                    }
                });
    }

    @Test
    public void test_GetTypeInfo_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010001).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42L), new Variant(42L), new
                Variant(391))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfo(42L, 42L, new Variant(391));
                    }
                });
    }

    @Test
    public void test_GetIDsOfNames_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(50), new Variant(391), new
                Variant(42L), new Variant(42L), new Variant(684))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetIDsOfNames(new Variant(50), new Variant(391), 42L, 42L, new Variant(684));
                    }
                });
    }

    @Test
    public void test_Invoke_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010003).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(650), new
                Variant(42L), new Variant(42), new Variant(430), new Variant(864), new Variant(290), new Variant(101))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Invoke(42, new Variant(650), 42L, 42, new Variant(430), new Variant(864), new
                                Variant(290), new Variant(101));
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
    public void test_getAxIndex_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1e6).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxIndex();
                    }
                });
    }

    @Test
    public void test_LargeScroll_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x223).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.LargeScroll();
                    }
                });
    }

    @Test
    public void test_LargeScroll_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x223).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(672))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.LargeScroll(new Variant(672));
                    }
                });
    }

    @Test
    public void test_LargeScroll_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x223).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(180), new Variant(814))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.LargeScroll(new Variant(180), new Variant(814));
                    }
                });
    }

    @Test
    public void test_LargeScroll_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x223).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(497), new Variant(371), new
                Variant(193))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.LargeScroll(new Variant(497), new Variant(371), new Variant(193));
                    }
                });
    }

    @Test
    public void test_LargeScroll_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x223).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(362), new Variant(380), new
                Variant(762), new Variant(103))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.LargeScroll(new Variant(362), new Variant(380), new Variant(762), new Variant(103));
                    }
                });
    }

    @Test
    public void test_getAxScrollColumn_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x28e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxScrollColumn();
                    }
                });
    }

    @Test
    public void test_setAxScrollColumn_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x28e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxScrollColumn(42);
                    }
                });
    }

    @Test
    public void test_getAxScrollRow_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x28f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxScrollRow();
                    }
                });
    }

    @Test
    public void test_setAxScrollRow_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x28f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxScrollRow(42);
                    }
                });
    }

    @Test
    public void test_SmallScroll_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x224).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SmallScroll();
                    }
                });
    }

    @Test
    public void test_SmallScroll_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x224).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(402))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SmallScroll(new Variant(402));
                    }
                });
    }

    @Test
    public void test_SmallScroll_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x224).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(841), new Variant(107))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SmallScroll(new Variant(841), new Variant(107));
                    }
                });
    }

    @Test
    public void test_SmallScroll_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x224).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(185), new Variant(725), new
                Variant(386))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SmallScroll(new Variant(185), new Variant(725), new Variant(386));
                    }
                });
    }

    @Test
    public void test_SmallScroll_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x224).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(667), new Variant(652), new
                Variant(263), new Variant(672))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SmallScroll(new Variant(667), new Variant(652), new Variant(263), new Variant(672));
                    }
                });
    }

    @Test
    public void test_getAxVisibleRange_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x45e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.getAxVisibleRange();
                    }
                });
    }

}