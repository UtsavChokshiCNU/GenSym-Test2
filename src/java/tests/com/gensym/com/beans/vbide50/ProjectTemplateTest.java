package com.gensym.com.beans.vbide50;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXDispatchable;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import org.junit.Before;
import org.junit.Test;

public class ProjectTemplateTest extends ActiveXDispatchableTestBase {

    private ProjectTemplate component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new ProjectTemplate(axProxy);
    }

    @Test
    public void test_QueryInterface_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60000000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(491), new Variant(847))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.QueryInterface(new Variant(491), new Variant(847));
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
        on(0x60010000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(311))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfoCount(new Variant(311));
                    }
                });
    }

    @Test
    public void test_GetTypeInfo_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010001).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42L), new Variant(42L), new
                Variant(79))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfo(42L, 42L, new Variant(79));
                    }
                });
    }

    @Test
    public void test_GetIDsOfNames_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(97), new Variant(206), new
                Variant(42L), new Variant(42L), new Variant(922))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetIDsOfNames(new Variant(97), new Variant(206), 42L, 42L, new Variant(922));
                    }
                });
    }

    @Test
    public void test_Invoke_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010003).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(263), new
                Variant(42L), new Variant(42), new Variant(771), new Variant(323), new Variant(868), new Variant(268))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Invoke(42, new Variant(263), 42L, 42, new Variant(771), new Variant(323), new
                                Variant(868), new Variant(268));
                    }
                });
    }

    @Test
    public void test_getAxActiveForm_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x0).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<FormTemplate>() {
                    @Override
                    public FormTemplate invoke() throws ActiveXException {
                        return component.getAxActiveForm();
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
                .verifyReturnsDispatchable(new Returns<Application>() {
                    @Override
                    public Application invoke() throws ActiveXException {
                        return component.getAxParent();
                    }
                });
    }

    @Test
    public void test_getAxSelectedComponents_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x64).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<SelectedComponents>() {
                    @Override
                    public SelectedComponents invoke() throws ActiveXException {
                        return component.getAxSelectedComponents();
                    }
                });
    }

    @Test
    public void test_AddFile_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x65).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("MEYvFkuhco"))
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.AddFile("MEYvFkuhco");
                    }
                });
    }

    @Test
    public void test_RemoveComponent_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x66).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(66), new Variant(false))
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.RemoveComponent(new Variant(66), false);
                    }
                });
    }

    @Test
    public void test_AddReference_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x67).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.AddReference();
                    }
                });
    }

    @Test
    public void test_AddReference_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x67).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(443))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.AddReference(new Variant(443));
                    }
                });
    }

    @Test
    public void test_AddReference_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x67).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(349), new Variant(382))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.AddReference(new Variant(349), new Variant(382));
                    }
                });
    }

    @Test
    public void test_AddReference_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x67).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(399), new Variant(558), new Variant
                (739))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.AddReference(new Variant(399), new Variant(558), new Variant(739));
                    }
                });
    }

    @Test
    public void test_AddReference_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x67).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(43), new Variant(989), new Variant
                (295), new Variant(221))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.AddReference(new Variant(43), new Variant(989), new Variant(295), new Variant(221));
                    }
                });
    }

    @Test
    public void test_AddToolboxTypelib_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x68).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("DBGaKysIwv"), new Variant((short)
                42), new Variant((short) 42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.AddToolboxTypelib("DBGaKysIwv", (short) 42, (short) 42);
                    }
                });
    }

    @Test
    public void test_AddToolboxTypelib_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x68).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("jPYgmlNiEI"), new Variant((short)
                42), new Variant((short) 42), new Variant(251))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.AddToolboxTypelib("jPYgmlNiEI", (short) 42, (short) 42, new Variant(251));
                    }
                });
    }

    @Test
    public void test_AddToolboxProgID_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x69).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("KlxUVGzSwI"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.AddToolboxProgID("KlxUVGzSwI");
                    }
                });
    }

    @Test
    public void test_AddToolboxProgID_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x69).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("tONvMZcfuh"), new Variant(954))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.AddToolboxProgID("tONvMZcfuh", new Variant(954));
                    }
                });
    }

    @Test
    public void test_AddToolboxVBX_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x6a).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("xMGrBLdqzA"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.AddToolboxVBX("xMGrBLdqzA");
                    }
                });
    }

    @Test
    public void test_AddFormTemplate_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsDispatchable(new Returns<FormTemplate>() {
                    @Override
                    public FormTemplate invoke() throws ActiveXException {
                        return component.AddFormTemplate();
                    }
                });
    }

    @Test
    public void test_AddMDIFormTemplate_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsDispatchable(new Returns<FormTemplate>() {
                    @Override
                    public FormTemplate invoke() throws ActiveXException {
                        return component.AddMDIFormTemplate();
                    }
                });
    }

    @Test
    public void test_getAxFileName_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6d).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxFileName();
                    }
                });
    }

    @Test
    public void test_getAxIsDirty_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxIsDirty();
                    }
                });
    }

    @Test
    public void test_setAxIsDirty_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x6e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxIsDirty(false);
                    }
                });
    }

    @Test
    public void test_WriteProperty_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6f).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("CetrGMVFLK"), new Variant
                ("FBHPuUGWnR"), new Variant("vbRumPdUtt"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.WriteProperty("CetrGMVFLK", "FBHPuUGWnR", "vbRumPdUtt");
                    }
                });
    }

    @Test
    public void test_ReadProperty_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x70).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("HmiEQxUSOB"), new Variant
                ("fjFBsyVkdG"))
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.ReadProperty("HmiEQxUSOB", "fjFBsyVkdG");
                    }
                });
    }

    @Test
    public void test_ConnectEvents_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x71).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(ActiveXDispatchable.class)))
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.ConnectEvents(getMock(ActiveXDispatchable.class));
                    }
                });
    }

    @Test
    public void test_DisconnectEvents_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x72).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.DisconnectEvents(42);
                    }
                });
    }

    @Test
    public void test_getAxComponents_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x73).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxComponents();
                    }
                });
    }

}