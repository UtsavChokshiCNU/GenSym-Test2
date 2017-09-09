package com.gensym.com.beans.excel12;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXDispatchable;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import org.junit.Before;
import org.junit.Test;

public class WindowTest extends ActiveXDispatchableTestBase {

    private Window component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new Window(axProxy);
    }

    @Test
    public void test_QueryInterface_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60000000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(803), new Variant(352))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.QueryInterface(new Variant(803), new Variant(352));
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
        on(0x60010000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(92))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfoCount(new Variant(92));
                    }
                });
    }

    @Test
    public void test_GetTypeInfo_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010001).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42L), new Variant(42L), new
                Variant(319))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfo(42L, 42L, new Variant(319));
                    }
                });
    }

    @Test
    public void test_GetIDsOfNames_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(756), new Variant(465), new
                Variant(42L), new Variant(42L), new Variant(318))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetIDsOfNames(new Variant(756), new Variant(465), 42L, 42L, new Variant(318));
                    }
                });
    }

    @Test
    public void test_Invoke_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010003).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(921), new
                Variant(42L), new Variant(42), new Variant(837), new Variant(163), new Variant(635), new Variant(636))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Invoke(42, new Variant(921), 42L, 42, new Variant(837), new Variant(163), new
                                Variant(635), new Variant(636));
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
    public void test_Activate_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x130).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Activate();
                    }
                });
    }

    @Test
    public void test_ActivateNext_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x45b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ActivateNext();
                    }
                });
    }

    @Test
    public void test_ActivatePrevious_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x45c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ActivatePrevious();
                    }
                });
    }

    @Test
    public void test_getAxActiveCell_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x131).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.getAxActiveCell();
                    }
                });
    }

    @Test
    public void test_getAxActiveChart_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xb7).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<ExcelChart>() {
                    @Override
                    public ExcelChart invoke() throws ActiveXException {
                        return component.getAxActiveChart();
                    }
                });
    }

    @Test
    public void test_getAxActivePane_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x282).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Pane>() {
                    @Override
                    public Pane invoke() throws ActiveXException {
                        return component.getAxActivePane();
                    }
                });
    }

    @Test
    public void test_getAxActiveSheet_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x133).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.getAxActiveSheet();
                    }
                });
    }

    @Test
    public void test_getAxCaption_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x8b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxCaption();
                    }
                });
    }

    @Test
    public void test_setAxCaption_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x8b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(278))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxCaption(new Variant(278));
                    }
                });
    }

    @Test
    public void test_Close_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x115).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Close();
                    }
                });
    }

    @Test
    public void test_Close_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x115).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(69))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Close(new Variant(69));
                    }
                });
    }

    @Test
    public void test_Close_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x115).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(474), new Variant(230))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Close(new Variant(474), new Variant(230));
                    }
                });
    }

    @Test
    public void test_Close_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x115).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(710), new Variant(918), new
                Variant(519))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Close(new Variant(710), new Variant(918), new Variant(519));
                    }
                });
    }

    @Test
    public void test_getAxDisplayFormulas_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x284).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxDisplayFormulas();
                    }
                });
    }

    @Test
    public void test_setAxDisplayFormulas_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x284).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxDisplayFormulas(false);
                    }
                });
    }

    @Test
    public void test_getAxDisplayGridlines_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x285).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxDisplayGridlines();
                    }
                });
    }

    @Test
    public void test_setAxDisplayGridlines_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x285).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxDisplayGridlines(false);
                    }
                });
    }

    @Test
    public void test_getAxDisplayHeadings_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x286).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxDisplayHeadings();
                    }
                });
    }

    @Test
    public void test_setAxDisplayHeadings_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x286).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxDisplayHeadings(false);
                    }
                });
    }

    @Test
    public void test_getAxDisplayHorizontalScrollBar_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x399).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxDisplayHorizontalScrollBar();
                    }
                });
    }

    @Test
    public void test_setAxDisplayHorizontalScrollBar_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x399).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxDisplayHorizontalScrollBar(false);
                    }
                });
    }

    @Test
    public void test_getAxDisplayOutline_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x287).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxDisplayOutline();
                    }
                });
    }

    @Test
    public void test_setAxDisplayOutline_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x287).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxDisplayOutline(false);
                    }
                });
    }

    @Test
    public void test_getAxDisplayRightToLeft_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x288).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxDisplayRightToLeft();
                    }
                });
    }

    @Test
    public void test_setAxDisplayRightToLeft_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x288).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxDisplayRightToLeft(false);
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
    public void test_getAxDisplayWorkbookTabs_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x39b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxDisplayWorkbookTabs();
                    }
                });
    }

    @Test
    public void test_setAxDisplayWorkbookTabs_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x39b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxDisplayWorkbookTabs(false);
                    }
                });
    }

    @Test
    public void test_getAxDisplayZeros_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x289).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxDisplayZeros();
                    }
                });
    }

    @Test
    public void test_setAxDisplayZeros_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x289).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxDisplayZeros(false);
                    }
                });
    }

    @Test
    public void test_getAxEnableResize_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x4a8).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxEnableResize();
                    }
                });
    }

    @Test
    public void test_setAxEnableResize_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x4a8).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxEnableResize(false);
                    }
                });
    }

    @Test
    public void test_getAxFreezePanes_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x28a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxFreezePanes();
                    }
                });
    }

    @Test
    public void test_setAxFreezePanes_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x28a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxFreezePanes(false);
                    }
                });
    }

    @Test
    public void test_getAxGridlineColor_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x28b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxGridlineColor();
                    }
                });
    }

    @Test
    public void test_setAxGridlineColor_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x28b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxGridlineColor(42);
                    }
                });
    }

    @Test
    public void test_getAxGridlineColorIndex_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x28c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxGridlineColorIndex();
                    }
                });
    }

    @Test
    public void test_setAxGridlineColorIndex_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x28c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxGridlineColorIndex(42);
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
    public void test_getAxIndex_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1e6).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxIndex();
                    }
                });
    }

    @Test
    public void test_LargeScroll_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x223).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.LargeScroll();
                    }
                });
    }

    @Test
    public void test_LargeScroll_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x223).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(984))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.LargeScroll(new Variant(984));
                    }
                });
    }

    @Test
    public void test_LargeScroll_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x223).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(746), new Variant(193))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.LargeScroll(new Variant(746), new Variant(193));
                    }
                });
    }

    @Test
    public void test_LargeScroll_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x223).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(976), new Variant(366), new
                Variant(41))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.LargeScroll(new Variant(976), new Variant(366), new Variant(41));
                    }
                });
    }

    @Test
    public void test_LargeScroll_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x223).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(970), new Variant(693), new
                Variant(259), new Variant(879))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.LargeScroll(new Variant(970), new Variant(693), new Variant(259), new Variant(879));
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
    public void test_NewWindow_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x118).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsDispatchable(new Returns<Window>() {
                    @Override
                    public Window invoke() throws ActiveXException {
                        return component.NewWindow();
                    }
                });
    }

    @Test
    public void test_getAxOnWindow_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x26f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxOnWindow();
                    }
                });
    }

    @Test
    public void test_setAxOnWindow_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x26f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("vOqbEMWYIg"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxOnWindow("vOqbEMWYIg");
                    }
                });
    }

    @Test
    public void test_getAxPanes_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x28d).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Panes>() {
                    @Override
                    public Panes invoke() throws ActiveXException {
                        return component.getAxPanes();
                    }
                });
    }

    @Test
    public void test_PrintOut_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x389).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PrintOut();
                    }
                });
    }

    @Test
    public void test_PrintOut_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x389).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(76))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PrintOut(new Variant(76));
                    }
                });
    }

    @Test
    public void test_PrintOut_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x389).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(354), new Variant(625))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PrintOut(new Variant(354), new Variant(625));
                    }
                });
    }

    @Test
    public void test_PrintOut_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x389).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(708), new Variant(219), new
                Variant(683))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PrintOut(new Variant(708), new Variant(219), new Variant(683));
                    }
                });
    }

    @Test
    public void test_PrintOut_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x389).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(542), new Variant(321), new
                Variant(412), new Variant(203))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PrintOut(new Variant(542), new Variant(321), new Variant(412), new Variant(203));
                    }
                });
    }

    @Test
    public void test_PrintOut_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x389).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(266), new Variant(382), new
                Variant(45), new Variant(648), new Variant(373))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PrintOut(new Variant(266), new Variant(382), new Variant(45), new Variant(648), new
                                Variant(373));
                    }
                });
    }

    @Test
    public void test_PrintOut_SixArgs_ShouldRedirectToProxy() throws Exception {
        on(0x389).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(770), new Variant(815), new
                Variant(830), new Variant(477), new Variant(112), new Variant(736))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PrintOut(new Variant(770), new Variant(815), new Variant(830), new Variant(477),
                                new Variant(112), new Variant(736));
                    }
                });
    }

    @Test
    public void test_PrintOut_SevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x389).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(94), new Variant(245), new Variant
                (835), new Variant(973), new Variant(403), new Variant(66), new Variant(118))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PrintOut(new Variant(94), new Variant(245), new Variant(835), new Variant(973), new
                                Variant(403), new Variant(66), new Variant(118));
                    }
                });
    }

    @Test
    public void test_PrintPreview_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x119).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PrintPreview();
                    }
                });
    }

    @Test
    public void test_PrintPreview_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x119).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(908))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PrintPreview(new Variant(908));
                    }
                });
    }

    @Test
    public void test_getAxRangeSelection_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x4a5).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.getAxRangeSelection();
                    }
                });
    }

    @Test
    public void test_getAxScrollColumn_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x28e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxScrollColumn();
                    }
                });
    }

    @Test
    public void test_setAxScrollColumn_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x28e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxScrollColumn(42);
                    }
                });
    }

    @Test
    public void test_getAxScrollRow_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x28f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxScrollRow();
                    }
                });
    }

    @Test
    public void test_setAxScrollRow_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x28f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxScrollRow(42);
                    }
                });
    }

    @Test
    public void test_ScrollWorkbookTabs_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x296).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ScrollWorkbookTabs();
                    }
                });
    }

    @Test
    public void test_ScrollWorkbookTabs_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x296).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(826))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ScrollWorkbookTabs(new Variant(826));
                    }
                });
    }

    @Test
    public void test_ScrollWorkbookTabs_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x296).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(527), new Variant(915))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ScrollWorkbookTabs(new Variant(527), new Variant(915));
                    }
                });
    }

    @Test
    public void test_getAxSelectedSheets_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x290).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Sheets>() {
                    @Override
                    public Sheets invoke() throws ActiveXException {
                        return component.getAxSelectedSheets();
                    }
                });
    }

    @Test
    public void test_getAxSelection_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x93).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.getAxSelection();
                    }
                });
    }

    @Test
    public void test_SmallScroll_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x224).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SmallScroll();
                    }
                });
    }

    @Test
    public void test_SmallScroll_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x224).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(639))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SmallScroll(new Variant(639));
                    }
                });
    }

    @Test
    public void test_SmallScroll_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x224).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(59), new Variant(744))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SmallScroll(new Variant(59), new Variant(744));
                    }
                });
    }

    @Test
    public void test_SmallScroll_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x224).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(237), new Variant(213), new
                Variant(480))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SmallScroll(new Variant(237), new Variant(213), new Variant(480));
                    }
                });
    }

    @Test
    public void test_SmallScroll_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x224).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(195), new Variant(899), new
                Variant(506), new Variant(441))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SmallScroll(new Variant(195), new Variant(899), new Variant(506), new Variant(441));
                    }
                });
    }

    @Test
    public void test_getAxSplit_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x291).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxSplit();
                    }
                });
    }

    @Test
    public void test_setAxSplit_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x291).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxSplit(false);
                    }
                });
    }

    @Test
    public void test_getAxSplitColumn_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x292).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxSplitColumn();
                    }
                });
    }

    @Test
    public void test_setAxSplitColumn_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x292).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxSplitColumn(42);
                    }
                });
    }

    @Test
    public void test_getAxSplitHorizontal_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x293).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDouble(new Returns<Double>() {
                    @Override
                    public Double invoke() throws ActiveXException {
                        return component.getAxSplitHorizontal();
                    }
                });
    }

    @Test
    public void test_setAxSplitHorizontal_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x293).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42.32d))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxSplitHorizontal(42.32d);
                    }
                });
    }

    @Test
    public void test_getAxSplitRow_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x294).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxSplitRow();
                    }
                });
    }

    @Test
    public void test_setAxSplitRow_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x294).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxSplitRow(42);
                    }
                });
    }

    @Test
    public void test_getAxSplitVertical_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x295).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDouble(new Returns<Double>() {
                    @Override
                    public Double invoke() throws ActiveXException {
                        return component.getAxSplitVertical();
                    }
                });
    }

    @Test
    public void test_setAxSplitVertical_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x295).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42.32d))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxSplitVertical(42.32d);
                    }
                });
    }

    @Test
    public void test_getAxTabRatio_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2a1).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDouble(new Returns<Double>() {
                    @Override
                    public Double invoke() throws ActiveXException {
                        return component.getAxTabRatio();
                    }
                });
    }

    @Test
    public void test_setAxTabRatio_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x2a1).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42.32d))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxTabRatio(42.32d);
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
    public void test_getAxType_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxType();
                    }
                });
    }

    @Test
    public void test_getAxUsableHeight_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x185).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDouble(new Returns<Double>() {
                    @Override
                    public Double invoke() throws ActiveXException {
                        return component.getAxUsableHeight();
                    }
                });
    }

    @Test
    public void test_getAxUsableWidth_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x186).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDouble(new Returns<Double>() {
                    @Override
                    public Double invoke() throws ActiveXException {
                        return component.getAxUsableWidth();
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
    public void test_getAxVisibleRange_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x45e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.getAxVisibleRange();
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
    public void test_getAxWindowNumber_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x45f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxWindowNumber();
                    }
                });
    }

    @Test
    public void test_getAxWindowState_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x18c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxWindowState();
                    }
                });
    }

    @Test
    public void test_setAxWindowState_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x18c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxWindowState(42);
                    }
                });
    }

    @Test
    public void test_getAxZoom_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x297).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxZoom();
                    }
                });
    }

    @Test
    public void test_setAxZoom_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x297).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(618))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxZoom(new Variant(618));
                    }
                });
    }

    @Test
    public void test_getAxView_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x4aa).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxView();
                    }
                });
    }

    @Test
    public void test_setAxView_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x4aa).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxView(42);
                    }
                });
    }

}