package com.gensym.com.beans.vbide50;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import org.junit.Before;
import org.junit.Test;

public class CodePanesTest extends ActiveXDispatchableTestBase {

    private CodePanes component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new CodePanes(axProxy);
    }

    @Test
    public void test_QueryInterface_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60000000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(644), new Variant(614))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.QueryInterface(new Variant(644), new Variant(614));
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
        on(0x60010000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(855))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfoCount(new Variant(855));
                    }
                });
    }

    @Test
    public void test_GetTypeInfo_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010001).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42L), new Variant(42L), new
                Variant(630))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfo(42L, 42L, new Variant(630));
                    }
                });
    }

    @Test
    public void test_GetIDsOfNames_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(161), new Variant(89), new
                Variant(42L), new Variant(42L), new Variant(192))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetIDsOfNames(new Variant(161), new Variant(89), 42L, 42L, new Variant(192));
                    }
                });
    }

    @Test
    public void test_Invoke_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010003).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(377), new
                Variant(42L), new Variant(42), new Variant(80), new Variant(521), new Variant(863), new Variant(371))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Invoke(42, new Variant(377), 42L, 42, new Variant(80), new Variant(521), new
                                Variant(863), new Variant(371));
                    }
                });
    }

    @Test
    public void test_getAxParent_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60020000).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<VBE>() {
                    @Override
                    public VBE invoke() throws ActiveXException {
                        return component.getAxParent();
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
    public void test_Item_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x0).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(621))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Item(new Variant(621));
                    }
                });
    }

    @Test
    public void test_getAxCount_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60020003).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxCount();
                    }
                });
    }

    @Test
    public void test__NewEnum_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xfffffffc).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsGenericValue(new Returns<Object>() {
                    @Override
                    public Object invoke() throws ActiveXException {
                        return component._NewEnum();
                    }
                });
    }

    @Test
    public void test_getAxCurrent_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60020005).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxCurrent();
                    }
                });
    }

    @Test
    public void test_setAxCurrent_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x60020005).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(168))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxCurrent(new Variant(168));
                    }
                });
    }

}