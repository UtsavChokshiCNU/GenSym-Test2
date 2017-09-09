package com.gensym.com.beans.excel12;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXDispatchable;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import org.junit.Before;
import org.junit.Test;

public class InteriorTest extends ActiveXDispatchableTestBase {

    private Interior component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new Interior(axProxy);
    }

    @Test
    public void test_QueryInterface_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60000000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(503), new Variant(35))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.QueryInterface(new Variant(503), new Variant(35));
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
        on(0x60010000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(856))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfoCount(new Variant(856));
                    }
                });
    }

    @Test
    public void test_GetTypeInfo_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010001).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42L), new Variant(42L), new
                Variant(714))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfo(42L, 42L, new Variant(714));
                    }
                });
    }

    @Test
    public void test_GetIDsOfNames_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(513), new Variant(953), new
                Variant(42L), new Variant(42L), new Variant(915))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetIDsOfNames(new Variant(513), new Variant(953), 42L, 42L, new Variant(915));
                    }
                });
    }

    @Test
    public void test_Invoke_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010003).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(902), new
                Variant(42L), new Variant(42), new Variant(654), new Variant(962), new Variant(282), new Variant(365))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Invoke(42, new Variant(902), 42L, 42, new Variant(654), new Variant(962), new
                                Variant(282), new Variant(365));
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
    public void test_getAxColor_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x63).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxColor();
                    }
                });
    }

    @Test
    public void test_setAxColor_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x63).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(683))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxColor(new Variant(683));
                    }
                });
    }

    @Test
    public void test_getAxColorIndex_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x61).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxColorIndex();
                    }
                });
    }

    @Test
    public void test_setAxColorIndex_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x61).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(851))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxColorIndex(new Variant(851));
                    }
                });
    }

    @Test
    public void test_getAxInvertIfNegative_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x84).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxInvertIfNegative();
                    }
                });
    }

    @Test
    public void test_setAxInvertIfNegative_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x84).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(512))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxInvertIfNegative(new Variant(512));
                    }
                });
    }

    @Test
    public void test_getAxPattern_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxPattern();
                    }
                });
    }

    @Test
    public void test_setAxPattern_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x5f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(473))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxPattern(new Variant(473));
                    }
                });
    }

    @Test
    public void test_getAxPatternColor_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x64).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxPatternColor();
                    }
                });
    }

    @Test
    public void test_setAxPatternColor_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x64).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(555))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxPatternColor(new Variant(555));
                    }
                });
    }

    @Test
    public void test_getAxPatternColorIndex_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x62).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxPatternColorIndex();
                    }
                });
    }

    @Test
    public void test_setAxPatternColorIndex_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x62).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(642))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxPatternColorIndex(new Variant(642));
                    }
                });
    }

}