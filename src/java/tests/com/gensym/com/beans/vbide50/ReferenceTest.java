package com.gensym.com.beans.vbide50;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import org.junit.Before;
import org.junit.Test;

public class ReferenceTest extends ActiveXDispatchableTestBase {

    private Reference component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new Reference(axProxy);
    }

    @Test
    public void test_QueryInterface_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60000000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(923), new Variant(398))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.QueryInterface(new Variant(923), new Variant(398));
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
        on(0x60010000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(178))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfoCount(new Variant(178));
                    }
                });
    }

    @Test
    public void test_GetTypeInfo_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010001).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42L), new Variant(42L), new
                Variant(469))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfo(42L, 42L, new Variant(469));
                    }
                });
    }

    @Test
    public void test_GetIDsOfNames_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(776), new Variant(903), new
                Variant(42L), new Variant(42L), new Variant(248))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetIDsOfNames(new Variant(776), new Variant(903), 42L, 42L, new Variant(248));
                    }
                });
    }

    @Test
    public void test_Invoke_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010003).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(45), new
                Variant(42L), new Variant(42), new Variant(203), new Variant(997), new Variant(233), new Variant(88))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Invoke(42, new Variant(45), 42L, 42, new Variant(203), new Variant(997), new
                                Variant(233), new Variant(88));
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
    public void test_getAxName_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60020002).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxName();
                    }
                });
    }

    @Test
    public void test_getAxGuid_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60020003).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxGuid();
                    }
                });
    }

    @Test
    public void test_getAxMajor_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60020004).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxMajor();
                    }
                });
    }

    @Test
    public void test_getAxMinor_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60020005).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxMinor();
                    }
                });
    }

    @Test
    public void test_getAxFullPath_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60020006).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxFullPath();
                    }
                });
    }

    @Test
    public void test_getAxBuiltIn_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60020007).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxBuiltIn();
                    }
                });
    }

    @Test
    public void test_getAxIsBroken_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60020008).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxIsBroken();
                    }
                });
    }

    @Test
    public void test_getAxType_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60020009).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxType();
                    }
                });
    }

    @Test
    public void test_getAxDescription_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6002000a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxDescription();
                    }
                });
    }

}