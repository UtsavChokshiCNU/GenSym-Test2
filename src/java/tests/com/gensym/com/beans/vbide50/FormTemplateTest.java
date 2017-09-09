package com.gensym.com.beans.vbide50;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import org.junit.Before;
import org.junit.Test;

public class FormTemplateTest extends ActiveXDispatchableTestBase {

    private FormTemplate component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new FormTemplate(axProxy);
    }

    @Test
    public void test_QueryInterface_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60000000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(643), new Variant(462))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.QueryInterface(new Variant(643), new Variant(462));
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
        on(0x60010000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(33))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfoCount(new Variant(33));
                    }
                });
    }

    @Test
    public void test_GetTypeInfo_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010001).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42L), new Variant(42L), new
                Variant(942))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfo(42L, 42L, new Variant(942));
                    }
                });
    }

    @Test
    public void test_GetIDsOfNames_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(131), new Variant(232), new
                Variant(42L), new Variant(42L), new Variant(255))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetIDsOfNames(new Variant(131), new Variant(232), 42L, 42L, new Variant(255));
                    }
                });
    }

    @Test
    public void test_Invoke_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010003).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(819), new
                Variant(42L), new Variant(42), new Variant(697), new Variant(490), new Variant(581), new Variant(974))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Invoke(42, new Variant(819), 42L, 42, new Variant(697), new Variant(490), new
                                Variant(581), new Variant(974));
                    }
                });
    }

    @Test
    public void test_getAxApplication_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Application>() {
                    @Override
                    public Application invoke() throws ActiveXException {
                        return component.getAxApplication();
                    }
                });
    }

    @Test
    public void test_getAxParent_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<ProjectTemplate>() {
                    @Override
                    public ProjectTemplate invoke() throws ActiveXException {
                        return component.getAxParent();
                    }
                });
    }

    @Test
    public void test_getAxSelectedControlTemplates_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<SelectedControlTemplates>() {
                    @Override
                    public SelectedControlTemplates invoke() throws ActiveXException {
                        return component.getAxSelectedControlTemplates();
                    }
                });
    }

    @Test
    public void test_getAxControlTemplates_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<ControlTemplates>() {
                    @Override
                    public ControlTemplates invoke() throws ActiveXException {
                        return component.getAxControlTemplates();
                    }
                });
    }

    @Test
    public void test_getAxProperties_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxProperties();
                    }
                });
    }

    @Test
    public void test_AddMenuTemplate_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2d).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("TmgTVtVNZa"), new Variant(getMock
                (ControlTemplate.class)))
                .verifyReturnsDispatchable(new Returns<ControlTemplate>() {
                    @Override
                    public ControlTemplate invoke() throws ActiveXException {
                        return component.AddMenuTemplate("TmgTVtVNZa", getMock(ControlTemplate.class));
                    }
                });
    }

    @Test
    public void test_InsertFile_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x2e).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("hFDKEEXFMy"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.InsertFile("hFDKEEXFMy");
                    }
                });
    }

}