package com.gensym.com.beans.office20;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXDispatchable;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import org.junit.Before;
import org.junit.Test;

public class BalloonTest extends ActiveXDispatchableTestBase {

    private Balloon component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new Balloon(axProxy);
    }

    @Test
    public void test_QueryInterface_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60000000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(899), new Variant(685))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.QueryInterface(new Variant(899), new Variant(685));
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
        on(0x60010000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(177))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfoCount(new Variant(177));
                    }
                });
    }

    @Test
    public void test_GetTypeInfo_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010001).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42L), new Variant(42L), new
                Variant(637))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfo(42L, 42L, new Variant(637));
                    }
                });
    }

    @Test
    public void test_GetIDsOfNames_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(370), new Variant(635), new
                Variant(42L), new Variant(42L), new Variant(716))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetIDsOfNames(new Variant(370), new Variant(635), 42L, 42L, new Variant(716));
                    }
                });
    }

    @Test
    public void test_Invoke_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010003).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(417), new
                Variant(42L), new Variant(42), new Variant(329), new Variant(683), new Variant(216), new Variant(794))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Invoke(42, new Variant(417), 42L, 42, new Variant(329), new Variant(683), new
                                Variant(216), new Variant(794));
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
        on(0x60030000).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.getAxParent();
                    }
                });
    }

    @Test
    public void test_getAxCheckboxes_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60030001).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.getAxCheckboxes();
                    }
                });
    }

    @Test
    public void test_getAxLabels_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60030002).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.getAxLabels();
                    }
                });
    }

    @Test
    public void test_setAxBalloonType_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x60030003).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxBalloonType(42);
                    }
                });
    }

    @Test
    public void test_getAxBalloonType_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60030003).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxBalloonType();
                    }
                });
    }

    @Test
    public void test_setAxIcon_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x60030005).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxIcon(42);
                    }
                });
    }

    @Test
    public void test_getAxIcon_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60030005).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxIcon();
                    }
                });
    }

    @Test
    public void test_setAxHeading_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x60030007).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("UoGemERHlq"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxHeading("UoGemERHlq");
                    }
                });
    }

    @Test
    public void test_getAxHeading_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60030007).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxHeading();
                    }
                });
    }

    @Test
    public void test_setAxText_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x60030009).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("FfUBSJgHbf"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxText("FfUBSJgHbf");
                    }
                });
    }

    @Test
    public void test_getAxText_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60030009).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxText();
                    }
                });
    }

    @Test
    public void test_setAxMode_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x6003000b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxMode(42);
                    }
                });
    }

    @Test
    public void test_getAxMode_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6003000b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxMode();
                    }
                });
    }

    @Test
    public void test_setAxAnimation_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x6003000d).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxAnimation(42);
                    }
                });
    }

    @Test
    public void test_getAxAnimation_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6003000d).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxAnimation();
                    }
                });
    }

    @Test
    public void test_setAxButton_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x6003000f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxButton(42);
                    }
                });
    }

    @Test
    public void test_getAxButton_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6003000f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxButton();
                    }
                });
    }

    @Test
    public void test_setAxCallback_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x60030011).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("YyXuMxgNAT"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxCallback("YyXuMxgNAT");
                    }
                });
    }

    @Test
    public void test_getAxCallback_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60030011).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxCallback();
                    }
                });
    }

    @Test
    public void test_setAxPrivate_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x60030013).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxPrivate(42);
                    }
                });
    }

    @Test
    public void test_getAxPrivate_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60030013).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxPrivate();
                    }
                });
    }

    @Test
    public void test_SetAvoidRectangle_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60030015).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(42), new
                Variant(42), new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SetAvoidRectangle(42, 42, 42, 42);
                    }
                });
    }

    @Test
    public void test_getAxName_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60030016).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxName();
                    }
                });
    }

    @Test
    public void test_Show_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60030017).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.Show();
                    }
                });
    }

    @Test
    public void test_Close_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60030018).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Close();
                    }
                });
    }

}