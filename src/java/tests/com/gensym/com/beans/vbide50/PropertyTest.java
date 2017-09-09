package com.gensym.com.beans.vbide50;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXDispatchable;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import org.junit.Before;
import org.junit.Test;

public class PropertyTest extends ActiveXDispatchableTestBase {

    private Property component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new Property(axProxy);
    }

    @Test
    public void test_QueryInterface_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60000000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(618), new Variant(551))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.QueryInterface(new Variant(618), new Variant(551));
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
        on(0x60010000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(270))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfoCount(new Variant(270));
                    }
                });
    }

    @Test
    public void test_GetTypeInfo_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010001).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42L), new Variant(42L), new
                Variant(900))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfo(42L, 42L, new Variant(900));
                    }
                });
    }

    @Test
    public void test_GetIDsOfNames_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(357), new Variant(366), new
                Variant(42L), new Variant(42L), new Variant(335))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetIDsOfNames(new Variant(357), new Variant(366), 42L, 42L, new Variant(335));
                    }
                });
    }

    @Test
    public void test_Invoke_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010003).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(117), new
                Variant(42L), new Variant(42), new Variant(590), new Variant(913), new Variant(825), new Variant(818))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Invoke(42, new Variant(117), 42L, 42, new Variant(590), new Variant(913), new
                                Variant(825), new Variant(818));
                    }
                });
    }

    @Test
    public void test_getAxValue_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x0).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxValue();
                    }
                });
    }

    @Test
    public void test_setAxValue_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x0).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(75))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxValue(new Variant(75));
                    }
                });
    }

    @Test
    public void test_getAxIndexedValue_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x3).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(215))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxIndexedValue(new Variant(215));
                    }
                });
    }

    @Test
    public void test_getAxIndexedValue_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(963), new Variant(740))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxIndexedValue(new Variant(963), new Variant(740));
                    }
                });
    }

    @Test
    public void test_getAxIndexedValue_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(243), new Variant(816), new
                Variant(250))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxIndexedValue(new Variant(243), new Variant(816), new Variant(250));
                    }
                });
    }

    @Test
    public void test_getAxIndexedValue_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(705), new Variant(235), new
                Variant(936), new Variant(160))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxIndexedValue(new Variant(705), new Variant(235), new Variant(936), new
                                Variant(160));
                    }
                });
    }

    @Test
    public void test_setAxIndexedValue_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(31), new Variant(711))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxIndexedValue(new Variant(31), new Variant(711));
                    }
                });
    }

    @Test
    public void test_setAxIndexedValue_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(357), new Variant(888), new
                Variant(909))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxIndexedValue(new Variant(357), new Variant(888), new Variant(909));
                    }
                });
    }

    @Test
    public void test_setAxIndexedValue_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(998), new Variant(709), new
                Variant(918), new Variant(53))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxIndexedValue(new Variant(998), new Variant(709), new Variant(918), new Variant
                                (53));
                    }
                });
    }

    @Test
    public void test_setAxIndexedValue_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(575), new Variant(694), new
                Variant(484), new Variant(290), new Variant(672))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxIndexedValue(new Variant(575), new Variant(694), new Variant(484), new Variant
                                (290), new Variant(672));
                    }
                });
    }

    @Test
    public void test_getAxNumIndices_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x4).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsShort(new Returns<Short>() {
                    @Override
                    public Short invoke() throws ActiveXException {
                        return component.getAxNumIndices();
                    }
                });
    }

    @Test
    public void test_getAxApplication_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.getAxApplication();
                    }
                });
    }

    @Test
    public void test_getAxParent_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxParent();
                    }
                });
    }

    @Test
    public void test_getAxName_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x28).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxName();
                    }
                });
    }

    @Test
    public void test_getAxVBE_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x29).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<VBE>() {
                    @Override
                    public VBE invoke() throws ActiveXException {
                        return component.getAxVBE();
                    }
                });
    }

    @Test
    public void test_getAxCollection_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxCollection();
                    }
                });
    }

    @Test
    public void test_getAxObject_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2d).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsGenericValue(new Returns<Object>() {
                    @Override
                    public Object invoke() throws ActiveXException {
                        return component.getAxObject();
                    }
                });
    }

}