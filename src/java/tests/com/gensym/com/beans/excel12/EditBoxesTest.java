package com.gensym.com.beans.excel12;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXDispatchable;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import org.junit.Before;
import org.junit.Test;

public class EditBoxesTest extends ActiveXDispatchableTestBase {

    private EditBoxes component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new EditBoxes(axProxy);
    }

    @Test
    public void test_QueryInterface_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60000000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(742), new Variant(268))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.QueryInterface(new Variant(742), new Variant(268));
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
        on(0x60010000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(261))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfoCount(new Variant(261));
                    }
                });
    }

    @Test
    public void test_GetTypeInfo_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010001).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42L), new Variant(42L), new
                Variant(414))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfo(42L, 42L, new Variant(414));
                    }
                });
    }

    @Test
    public void test_GetIDsOfNames_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(847), new Variant(108), new
                Variant(42L), new Variant(42L), new Variant(563))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetIDsOfNames(new Variant(847), new Variant(108), 42L, 42L, new Variant(563));
                    }
                });
    }

    @Test
    public void test_Invoke_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010003).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(416), new
                Variant(42L), new Variant(42), new Variant(916), new Variant(98), new Variant(305), new Variant(504))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Invoke(42, new Variant(416), 42L, 42, new Variant(916), new Variant(98), new
                                Variant(305), new Variant(504));
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
        on(0x254).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("xKWcOYOwiU"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxOnAction("xKWcOYOwiU");
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
        on(0x269).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(120))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxPlacement(new Variant(120));
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
        on(0xeb).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(679))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Select(new Variant(679));
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
    public void test_getAxZOrder_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x26e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxZOrder();
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
    public void test_getAxCaption_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x8b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxCaption();
                    }
                });
    }

    @Test
    public void test_setAxCaption_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x8b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("QxlytoGJbI"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxCaption("QxlytoGJbI");
                    }
                });
    }

    @Test
    public void test_getAxCharacters_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x25b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Characters>() {
                    @Override
                    public Characters invoke() throws ActiveXException {
                        return component.getAxCharacters();
                    }
                });
    }

    @Test
    public void test_getAxCharacters_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x25b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(225))
                .verifyReturnsDispatchable(new Returns<Characters>() {
                    @Override
                    public Characters invoke() throws ActiveXException {
                        return component.getAxCharacters(new Variant(225));
                    }
                });
    }

    @Test
    public void test_getAxCharacters_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x25b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(802), new Variant(127))
                .verifyReturnsDispatchable(new Returns<Characters>() {
                    @Override
                    public Characters invoke() throws ActiveXException {
                        return component.getAxCharacters(new Variant(802), new Variant(127));
                    }
                });
    }

    @Test
    public void test_CheckSpelling_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.CheckSpelling();
                    }
                });
    }

    @Test
    public void test_CheckSpelling_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x1f9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(212))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.CheckSpelling(new Variant(212));
                    }
                });
    }

    @Test
    public void test_CheckSpelling_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(69), new Variant(723))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.CheckSpelling(new Variant(69), new Variant(723));
                    }
                });
    }

    @Test
    public void test_CheckSpelling_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(553), new Variant(713), new
                Variant(120))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.CheckSpelling(new Variant(553), new Variant(713), new Variant(120));
                    }
                });
    }

    @Test
    public void test_CheckSpelling_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(886), new Variant(562), new
                Variant(837), new Variant(76))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.CheckSpelling(new Variant(886), new Variant(562), new Variant(837), new Variant(76));
                    }
                });
    }

    @Test
    public void test_CheckSpelling_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(512), new Variant(182), new
                Variant(519), new Variant(154), new Variant(669))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.CheckSpelling(new Variant(512), new Variant(182), new Variant(519), new Variant
                                (154), new Variant(669));
                    }
                });
    }

    @Test
    public void test_CheckSpelling_SixArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(370), new Variant(519), new
                Variant(505), new Variant(77), new Variant(221), new Variant(412))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.CheckSpelling(new Variant(370), new Variant(519), new Variant(505), new Variant(77)
                                , new Variant(221), new Variant(412));
                    }
                });
    }

    @Test
    public void test_getAxLockedText_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x268).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxLockedText();
                    }
                });
    }

    @Test
    public void test_setAxLockedText_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x268).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxLockedText(false);
                    }
                });
    }

    @Test
    public void test_getAxText_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x8a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxText();
                    }
                });
    }

    @Test
    public void test_setAxText_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x8a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("ijUggfloII"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxText("ijUggfloII");
                    }
                });
    }

    @Test
    public void test_getAxDisplayVerticalScrollBar_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x39a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxDisplayVerticalScrollBar();
                    }
                });
    }

    @Test
    public void test_setAxDisplayVerticalScrollBar_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x39a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxDisplayVerticalScrollBar(false);
                    }
                });
    }

    @Test
    public void test_getAxInputType_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x356).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxInputType();
                    }
                });
    }

    @Test
    public void test_setAxInputType_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x356).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxInputType(42);
                    }
                });
    }

    @Test
    public void test__Dummy34_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x10022).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component._Dummy34();
                    }
                });
    }

    @Test
    public void test_getAxMultiLine_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x357).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxMultiLine();
                    }
                });
    }

    @Test
    public void test_setAxMultiLine_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x357).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxMultiLine(false);
                    }
                });
    }

    @Test
    public void test_getAxPasswordEdit_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x48a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxPasswordEdit();
                    }
                });
    }

    @Test
    public void test_setAxPasswordEdit_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x48a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxPasswordEdit(false);
                    }
                });
    }

    @Test
    public void test_Add_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0xb5).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42.32d), new Variant(42.32d), new
                Variant(42.32d), new Variant(42.32d))
                .verifyReturnsDispatchable(new Returns<EditBox>() {
                    @Override
                    public EditBox invoke() throws ActiveXException {
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
        on(0xaa).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(613))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Item(new Variant(613));
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