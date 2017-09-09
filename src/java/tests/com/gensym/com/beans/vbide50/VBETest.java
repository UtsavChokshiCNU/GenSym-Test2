package com.gensym.com.beans.vbide50;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import com.gensym.com.beans.office20.CommandBars;
import org.junit.Before;
import org.junit.Test;

public class VBETest extends ActiveXDispatchableTestBase {

    private VBE component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new VBE(axProxy);
    }

    @Test
    public void test_QueryInterface_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60000000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(869), new Variant(64))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.QueryInterface(new Variant(869), new Variant(64));
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
        on(0x60010000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(597))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfoCount(new Variant(597));
                    }
                });
    }

    @Test
    public void test_GetTypeInfo_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010001).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42L), new Variant(42L), new
                Variant(514))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfo(42L, 42L, new Variant(514));
                    }
                });
    }

    @Test
    public void test_GetIDsOfNames_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(398), new Variant(9), new
                Variant(42L), new Variant(42L), new Variant(945))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetIDsOfNames(new Variant(398), new Variant(9), 42L, 42L, new Variant(945));
                    }
                });
    }

    @Test
    public void test_Invoke_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010003).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(589), new
                Variant(42L), new Variant(42), new Variant(965), new Variant(493), new Variant(371), new Variant(38))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Invoke(42, new Variant(589), 42L, 42, new Variant(965), new Variant(493), new
                                Variant(371), new Variant(38));
                    }
                });
    }

    @Test
    public void test_getAxName_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x0).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxName();
                    }
                });
    }

    @Test
    public void test_getAxFullName_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xa).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxFullName();
                    }
                });
    }

    @Test
    public void test_getAxLastUsedPath_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xb).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxLastUsedPath();
                    }
                });
    }

    @Test
    public void test_setAxLastUsedPath_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xb).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("rVkqmlYfcY"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxLastUsedPath("rVkqmlYfcY");
                    }
                });
    }

    @Test
    public void test_getAxVersion_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x64).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxVersion();
                    }
                });
    }

    @Test
    public void test_getAxReadOnlyMode_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsShort(new Returns<Short>() {
                    @Override
                    public Short invoke() throws ActiveXException {
                        return component.getAxReadOnlyMode();
                    }
                });
    }

    @Test
    public void test_setAxReadOnlyMode_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x6a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant((short) 42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxReadOnlyMode((short) 42);
                    }
                });
    }

    @Test
    public void test_getAxVBProjects_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxVBProjects();
                    }
                });
    }

    @Test
    public void test_getAxCommandBars_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<CommandBars>() {
                    @Override
                    public CommandBars invoke() throws ActiveXException {
                        return component.getAxCommandBars();
                    }
                });
    }

    @Test
    public void test_getAxCodePanes_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6d).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxCodePanes();
                    }
                });
    }

    @Test
    public void test_getAxWindows_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxWindows();
                    }
                });
    }

    @Test
    public void test_getAxEvents_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Events>() {
                    @Override
                    public Events invoke() throws ActiveXException {
                        return component.getAxEvents();
                    }
                });
    }

    @Test
    public void test_getAxAddins_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xc8).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxAddins();
                    }
                });
    }

    @Test
    public void test_getAxActiveVBProject_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xc9).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxActiveVBProject();
                    }
                });
    }

    @Test
    public void test_getAxSelectedVBComponent_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xca).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxSelectedVBComponent();
                    }
                });
    }

    @Test
    public void test_getAxTemplatePath_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xcb).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxTemplatePath();
                    }
                });
    }

    @Test
    public void test_getAxMainWindow_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xcc).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Window>() {
                    @Override
                    public Window invoke() throws ActiveXException {
                        return component.getAxMainWindow();
                    }
                });
    }

    @Test
    public void test_getAxActiveWindow_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xcd).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Window>() {
                    @Override
                    public Window invoke() throws ActiveXException {
                        return component.getAxActiveWindow();
                    }
                });
    }

    @Test
    public void test_getAxActiveCodePane_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xce).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxActiveCodePane();
                    }
                });
    }

    @Test
    public void test_Quit_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xcf).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Quit();
                    }
                });
    }

    @Test
    public void test_getAxDisplayModel_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xd0).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxDisplayModel();
                    }
                });
    }

    @Test
    public void test_setAxDisplayModel_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xd0).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxDisplayModel(42);
                    }
                });
    }

}