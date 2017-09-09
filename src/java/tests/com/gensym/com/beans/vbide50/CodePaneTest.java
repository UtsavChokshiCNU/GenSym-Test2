package com.gensym.com.beans.vbide50;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import org.junit.Before;
import org.junit.Test;

public class CodePaneTest extends ActiveXDispatchableTestBase {

    private CodePane component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new CodePane(axProxy);
    }

    @Test
    public void test_QueryInterface_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60000000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(451), new Variant(469))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.QueryInterface(new Variant(451), new Variant(469));
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
        on(0x60010000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(909))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfoCount(new Variant(909));
                    }
                });
    }

    @Test
    public void test_GetTypeInfo_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010001).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42L), new Variant(42L), new
                Variant(837))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfo(42L, 42L, new Variant(837));
                    }
                });
    }

    @Test
    public void test_GetIDsOfNames_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(570), new Variant(106), new
                Variant(42L), new Variant(42L), new Variant(852))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetIDsOfNames(new Variant(570), new Variant(106), 42L, 42L, new Variant(852));
                    }
                });
    }

    @Test
    public void test_Invoke_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010003).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(591), new
                Variant(42L), new Variant(42), new Variant(122), new Variant(583), new Variant(339), new Variant(403))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Invoke(42, new Variant(591), 42L, 42, new Variant(122), new Variant(583), new
                                Variant(339), new Variant(403));
                    }
                });
    }

    @Test
    public void test_getAxCollection_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60020000).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxCollection();
                    }
                });
    }

    @Test
    public void test_getAxVBE_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60020001).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<VBE>() {
                    @Override
                    public VBE invoke() throws ActiveXException {
                        return component.getAxVBE();
                    }
                });
    }

    @Test
    public void test_getAxWindow_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60020002).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Window>() {
                    @Override
                    public Window invoke() throws ActiveXException {
                        return component.getAxWindow();
                    }
                });
    }

    @Test
    public void test_GetSelection_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60020003).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(798), new Variant(96), new
                Variant(703), new Variant(562))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetSelection(new Variant(798), new Variant(96), new Variant(703), new Variant(562));
                    }
                });
    }

    @Test
    public void test_SetSelection_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60020004).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(42), new
                Variant(42), new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SetSelection(42, 42, 42, 42);
                    }
                });
    }

    @Test
    public void test_getAxTopLine_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60020005).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxTopLine();
                    }
                });
    }

    @Test
    public void test_setAxTopLine_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x60020005).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxTopLine(42);
                    }
                });
    }

    @Test
    public void test_getAxCountOfVisibleLines_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60020007).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxCountOfVisibleLines();
                    }
                });
    }

    @Test
    public void test_getAxCodeModule_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60020008).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxCodeModule();
                    }
                });
    }

    @Test
    public void test_Show_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60020009).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Show();
                    }
                });
    }

    @Test
    public void test_getAxCodePaneView_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6002000a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxCodePaneView();
                    }
                });
    }

}