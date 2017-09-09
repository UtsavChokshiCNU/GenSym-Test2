package com.gensym.com.beans.excel12;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXDispatchable;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import org.junit.Before;
import org.junit.Test;

public class ChartObjectsTest extends ActiveXDispatchableTestBase {

    private ChartObjects component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new ChartObjects(axProxy);
    }

    @Test
    public void test_QueryInterface_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60000000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(982), new Variant(37))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.QueryInterface(new Variant(982), new Variant(37));
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
        on(0x60010000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(80))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfoCount(new Variant(80));
                    }
                });
    }

    @Test
    public void test_GetTypeInfo_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010001).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42L), new Variant(42L), new
                Variant(441))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfo(42L, 42L, new Variant(441));
                    }
                });
    }

    @Test
    public void test_GetIDsOfNames_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(332), new Variant(340), new
                Variant(42L), new Variant(42L), new Variant(293))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetIDsOfNames(new Variant(332), new Variant(340), 42L, 42L, new Variant(293));
                    }
                });
    }

    @Test
    public void test_Invoke_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010003).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(871), new
                Variant(42L), new Variant(42), new Variant(196), new Variant(280), new Variant(458), new Variant(653))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Invoke(42, new Variant(871), 42L, 42, new Variant(196), new Variant(280), new
                                Variant(458), new Variant(653));
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
    public void test__Dummy3_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x10003).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component._Dummy3();
                    }
                });
    }

    @Test
    public void test_BringToFront_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x25a).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.BringToFront();
                    }
                });
    }

    @Test
    public void test_Copy_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x227).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Copy();
                    }
                });
    }

    @Test
    public void test_CopyPicture_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0xd5).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.CopyPicture(42, 42);
                    }
                });
    }

    @Test
    public void test_Cut_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x235).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Cut();
                    }
                });
    }

    @Test
    public void test_Delete_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x75).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Delete();
                    }
                });
    }

    @Test
    public void test_Duplicate_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x40f).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.Duplicate();
                    }
                });
    }

    @Test
    public void test_getAxEnabled_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x258).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxEnabled();
                    }
                });
    }

    @Test
    public void test_setAxEnabled_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x258).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxEnabled(false);
                    }
                });
    }

    @Test
    public void test_getAxHeight_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x7b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDouble(new Returns<Double>() {
                    @Override
                    public Double invoke() throws ActiveXException {
                        return component.getAxHeight();
                    }
                });
    }

    @Test
    public void test_setAxHeight_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x7b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42.32d))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxHeight(42.32d);
                    }
                });
    }

    @Test
    public void test__Dummy12_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1000c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component._Dummy12();
                    }
                });
    }

    @Test
    public void test_getAxLeft_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x7f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDouble(new Returns<Double>() {
                    @Override
                    public Double invoke() throws ActiveXException {
                        return component.getAxLeft();
                    }
                });
    }

    @Test
    public void test_setAxLeft_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x7f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42.32d))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxLeft(42.32d);
                    }
                });
    }

    @Test
    public void test_getAxLocked_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x10d).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxLocked();
                    }
                });
    }

    @Test
    public void test_setAxLocked_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x10d).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxLocked(false);
                    }
                });
    }

    @Test
    public void test__Dummy15_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1000f).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component._Dummy15();
                    }
                });
    }

    @Test
    public void test_getAxOnAction_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x254).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxOnAction();
                    }
                });
    }

    @Test
    public void test_setAxOnAction_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x254).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("WvedUaQIKI"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxOnAction("WvedUaQIKI");
                    }
                });
    }

    @Test
    public void test_getAxPlacement_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x269).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxPlacement();
                    }
                });
    }

    @Test
    public void test_setAxPlacement_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x269).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(861))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxPlacement(new Variant(861));
                    }
                });
    }

    @Test
    public void test_getAxPrintObject_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x26a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxPrintObject();
                    }
                });
    }

    @Test
    public void test_setAxPrintObject_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x26a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxPrintObject(false);
                    }
                });
    }

    @Test
    public void test_Select_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xeb).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Select();
                    }
                });
    }

    @Test
    public void test_Select_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xeb).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(112))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Select(new Variant(112));
                    }
                });
    }

    @Test
    public void test_SendToBack_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x25d).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SendToBack();
                    }
                });
    }

    @Test
    public void test_getAxTop_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x7e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDouble(new Returns<Double>() {
                    @Override
                    public Double invoke() throws ActiveXException {
                        return component.getAxTop();
                    }
                });
    }

    @Test
    public void test_setAxTop_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x7e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42.32d))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxTop(42.32d);
                    }
                });
    }

    @Test
    public void test__Dummy22_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x10016).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component._Dummy22();
                    }
                });
    }

    @Test
    public void test_getAxVisible_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x22e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxVisible();
                    }
                });
    }

    @Test
    public void test_setAxVisible_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x22e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxVisible(false);
                    }
                });
    }

    @Test
    public void test_getAxWidth_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x7a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDouble(new Returns<Double>() {
                    @Override
                    public Double invoke() throws ActiveXException {
                        return component.getAxWidth();
                    }
                });
    }

    @Test
    public void test_setAxWidth_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x7a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42.32d))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxWidth(42.32d);
                    }
                });
    }

    @Test
    public void test__Dummy25_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x10019).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component._Dummy25();
                    }
                });
    }

    @Test
    public void test_getAxShapeRange_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5f8).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<ShapeRange>() {
                    @Override
                    public ShapeRange invoke() throws ActiveXException {
                        return component.getAxShapeRange();
                    }
                });
    }

    @Test
    public void test__Dummy27_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1001b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component._Dummy27();
                    }
                });
    }

    @Test
    public void test__Dummy28_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1001c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component._Dummy28();
                    }
                });
    }

    @Test
    public void test__Dummy29_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1001d).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component._Dummy29();
                    }
                });
    }

    @Test
    public void test_getAxRoundedCorners_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x26b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxRoundedCorners();
                    }
                });
    }

    @Test
    public void test_setAxRoundedCorners_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x26b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxRoundedCorners(false);
                    }
                });
    }

    @Test
    public void test_getAxBorder_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x80).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Border>() {
                    @Override
                    public Border invoke() throws ActiveXException {
                        return component.getAxBorder();
                    }
                });
    }

    @Test
    public void test_getAxInterior_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x81).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Interior>() {
                    @Override
                    public Interior invoke() throws ActiveXException {
                        return component.getAxInterior();
                    }
                });
    }

    @Test
    public void test_getAxShadow_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x67).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxShadow();
                    }
                });
    }

    @Test
    public void test_setAxShadow_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x67).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxShadow(false);
                    }
                });
    }

    @Test
    public void test_Add_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0xb5).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42.32d), new Variant(42.32d), new
                Variant(42.32d), new Variant(42.32d))
                .verifyReturnsDispatchable(new Returns<ChartObject>() {
                    @Override
                    public ChartObject invoke() throws ActiveXException {
                        return component.Add(42.32d, 42.32d, 42.32d, 42.32d);
                    }
                });
    }

    @Test
    public void test_getAxCount_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x76).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxCount();
                    }
                });
    }

    @Test
    public void test_Group_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2e).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsDispatchable(new Returns<GroupObject>() {
                    @Override
                    public GroupObject invoke() throws ActiveXException {
                        return component.Group();
                    }
                });
    }

    @Test
    public void test_Item_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xaa).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(867))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.Item(new Variant(867));
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

}