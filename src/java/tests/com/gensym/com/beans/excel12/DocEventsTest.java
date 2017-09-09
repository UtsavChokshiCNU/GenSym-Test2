package com.gensym.com.beans.excel12;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import org.junit.Before;
import org.junit.Test;

public class DocEventsTest extends ActiveXDispatchableTestBase {

    private DocEvents component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new DocEvents(axProxy);
    }

    @Test
    public void test_QueryInterface_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60000000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(991), new Variant(554))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.QueryInterface(new Variant(991), new Variant(554));
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
        on(0x60010000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(123))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfoCount(new Variant(123));
                    }
                });
    }

    @Test
    public void test_GetTypeInfo_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010001).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42L), new Variant(42L), new
                Variant(546))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfo(42L, 42L, new Variant(546));
                    }
                });
    }

    @Test
    public void test_GetIDsOfNames_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(802), new Variant(500), new
                Variant(42L), new Variant(42L), new Variant(901))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetIDsOfNames(new Variant(802), new Variant(500), 42L, 42L, new Variant(901));
                    }
                });
    }

    @Test
    public void test_Invoke_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010003).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(729), new
                Variant(42L), new Variant(42), new Variant(383), new Variant(343), new Variant(212), new Variant(470))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Invoke(42, new Variant(729), 42L, 42, new Variant(383), new Variant(343), new
                                Variant(212), new Variant(470));
                    }
                });
    }

    @Test
    public void test_SelectionChange_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x607).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SelectionChange(getMock(Range.class));
                    }
                });
    }

    @Test
    public void test_BeforeDoubleClick_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x601).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (567))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.BeforeDoubleClick(getMock(Range.class), new Variant(567));
                    }
                });
    }

    @Test
    public void test_BeforeRightClick_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5fe).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (623))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.BeforeRightClick(getMock(Range.class), new Variant(623));
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
    public void test_Calculate_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x117).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Calculate();
                    }
                });
    }

    @Test
    public void test_Change_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x609).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Change(getMock(Range.class));
                    }
                });
    }

}