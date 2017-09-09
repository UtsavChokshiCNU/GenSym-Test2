package com.gensym.com.beans.office20;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXDispatchable;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import org.junit.Before;
import org.junit.Test;

public class AdjustmentsTest extends ActiveXDispatchableTestBase {

    private Adjustments component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new Adjustments(axProxy);
    }

    @Test
    public void test_QueryInterface_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60000000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(81), new Variant(932))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.QueryInterface(new Variant(81), new Variant(932));
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
        on(0x60010000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(98))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfoCount(new Variant(98));
                    }
                });
    }

    @Test
    public void test_GetTypeInfo_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010001).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42L), new Variant(42L), new
                Variant(771))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfo(42L, 42L, new Variant(771));
                    }
                });
    }

    @Test
    public void test_GetIDsOfNames_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(117), new Variant(661), new
                Variant(42L), new Variant(42L), new Variant(684))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetIDsOfNames(new Variant(117), new Variant(661), 42L, 42L, new Variant(684));
                    }
                });
    }

    @Test
    public void test_Invoke_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010003).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(409), new
                Variant(42L), new Variant(42), new Variant(991), new Variant(772), new Variant(284), new Variant(122))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Invoke(42, new Variant(409), 42L, 42, new Variant(991), new Variant(772), new
                                Variant(284), new Variant(122));
                    }
                });
    }

    @Test
    public void test_getAxApplication_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60020000).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.getAxApplication();
                    }
                });
    }

    @Test
    public void test_getAxCreator_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60020001).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxCreator();
                    }
                });
    }

    @Test
    public void test_getAxParent_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.getAxParent();
                    }
                });
    }

    @Test
    public void test_getAxCount_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxCount();
                    }
                });
    }

    @Test
    public void test_getAxItem_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x0).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(42))
                .verifyReturnsFloat(new Returns<Float>() {
                    @Override
                    public Float invoke() throws ActiveXException {
                        return component.getAxItem(42);
                    }
                });
    }

    @Test
    public void test_setAxItem_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x0).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42), new Variant(42.32f))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxItem(42, 42.32f);
                    }
                });
    }

}