package com.gensym.com.beans.vbide50;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import org.junit.Before;
import org.junit.Test;

public class VBProjectsTest extends ActiveXDispatchableTestBase {

    private VBProjects component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new VBProjects(axProxy);
    }

    @Test
    public void test_QueryInterface_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60000000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(668), new Variant(950))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.QueryInterface(new Variant(668), new Variant(950));
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
        on(0x60010000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(420))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfoCount(new Variant(420));
                    }
                });
    }

    @Test
    public void test_GetTypeInfo_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010001).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42L), new Variant(42L), new
                Variant(543))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfo(42L, 42L, new Variant(543));
                    }
                });
    }

    @Test
    public void test_GetIDsOfNames_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(379), new Variant(157), new
                Variant(42L), new Variant(42L), new Variant(924))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetIDsOfNames(new Variant(379), new Variant(157), 42L, 42L, new Variant(924));
                    }
                });
    }

    @Test
    public void test_Invoke_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010003).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(124), new
                Variant(42L), new Variant(42), new Variant(851), new Variant(275), new Variant(940), new Variant(671))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Invoke(42, new Variant(124), 42L, 42, new Variant(851), new Variant(275), new
                                Variant(940), new Variant(671));
                    }
                });
    }

    @Test
    public void test_Item_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x0).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(823))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Item(new Variant(823));
                    }
                });
    }

    @Test
    public void test_getAxVBE_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x14).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<VBE>() {
                    @Override
                    public VBE invoke() throws ActiveXException {
                        return component.getAxVBE();
                    }
                });
    }

    @Test
    public void test_getAxParent_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<VBE>() {
                    @Override
                    public VBE invoke() throws ActiveXException {
                        return component.getAxParent();
                    }
                });
    }

    @Test
    public void test_getAxCount_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xa).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
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
    public void test_Add_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x80).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(false))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Add(42, false);
                    }
                });
    }

    @Test
    public void test_AddFromTemplate_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x81).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("cUjKQzBNeF"), new Variant(false))
                .verifyReturnsDispatchable(new Returns<VBNewProjects>() {
                    @Override
                    public VBNewProjects invoke() throws ActiveXException {
                        return component.AddFromTemplate("cUjKQzBNeF", false);
                    }
                });
    }

    @Test
    public void test_AddFromFile_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x82).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("FGRYqAkgIl"), new Variant(false))
                .verifyReturnsDispatchable(new Returns<VBNewProjects>() {
                    @Override
                    public VBNewProjects invoke() throws ActiveXException {
                        return component.AddFromFile("FGRYqAkgIl", false);
                    }
                });
    }

    @Test
    public void test_Remove_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x83).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(283))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Remove(new Variant(283));
                    }
                });
    }

    @Test
    public void test_getAxStartProject_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x84).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxStartProject();
                    }
                });
    }

    @Test
    public void test_setAxStartProject_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x84).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(137))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxStartProject(new Variant(137));
                    }
                });
    }

    @Test
    public void test_FileName_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x85).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.FileName();
                    }
                });
    }

    @Test
    public void test_getAxIconState_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x86).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxIconState();
                    }
                });
    }

    @Test
    public void test_setAxIconState_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x86).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxIconState(42);
                    }
                });
    }

    @Test
    public void test_SaveAs_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x87).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("lAMLeBfXAR"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SaveAs("lAMLeBfXAR");
                    }
                });
    }

}