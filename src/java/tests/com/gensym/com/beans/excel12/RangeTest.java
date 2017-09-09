package com.gensym.com.beans.excel12;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXDispatchable;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import org.junit.Before;
import org.junit.Test;

public class RangeTest extends ActiveXDispatchableTestBase {

    private Range component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new Range(axProxy);
    }

    @Test
    public void test_QueryInterface_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60000000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(997), new Variant(638))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.QueryInterface(new Variant(997), new Variant(638));
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
        on(0x60010000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(285))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfoCount(new Variant(285));
                    }
                });
    }

    @Test
    public void test_GetTypeInfo_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010001).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42L), new Variant(42L), new
                Variant(363))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfo(42L, 42L, new Variant(363));
                    }
                });
    }

    @Test
    public void test_GetIDsOfNames_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(807), new Variant(563), new
                Variant(42L), new Variant(42L), new Variant(791))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetIDsOfNames(new Variant(807), new Variant(563), 42L, 42L, new Variant(791));
                    }
                });
    }

    @Test
    public void test_Invoke_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010003).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(797), new
                Variant(42L), new Variant(42), new Variant(681), new Variant(792), new Variant(831), new Variant(182))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Invoke(42, new Variant(797), 42L, 42, new Variant(681), new Variant(792), new
                                Variant(831), new Variant(182));
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
    public void test_getAxAddIndent_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x427).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxAddIndent();
                    }
                });
    }

    @Test
    public void test_setAxAddIndent_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x427).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(652))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxAddIndent(new Variant(652));
                    }
                });
    }

    @Test
    public void test_getAxAddress_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0xec).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(937), new Variant(412), new
                Variant(42))
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxAddress(new Variant(937), new Variant(412), 42);
                    }
                });
    }

    @Test
    public void test_getAxAddress_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0xec).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(709), new Variant(333), new
                Variant(42), new Variant(134))
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxAddress(new Variant(709), new Variant(333), 42, new Variant(134));
                    }
                });
    }

    @Test
    public void test_getAxAddress_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0xec).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(707), new Variant(757), new
                Variant(42), new Variant(462), new Variant(342))
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxAddress(new Variant(707), new Variant(757), 42, new Variant(462), new
                                Variant(342));
                    }
                });
    }

    @Test
    public void test_getAxAddressLocal_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1b5).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(734), new Variant(709), new
                Variant(42))
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxAddressLocal(new Variant(734), new Variant(709), 42);
                    }
                });
    }

    @Test
    public void test_getAxAddressLocal_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1b5).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(876), new Variant(217), new
                Variant(42), new Variant(144))
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxAddressLocal(new Variant(876), new Variant(217), 42, new Variant(144));
                    }
                });
    }

    @Test
    public void test_getAxAddressLocal_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1b5).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(642), new Variant(723), new
                Variant(42), new Variant(782), new Variant(35))
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxAddressLocal(new Variant(642), new Variant(723), 42, new Variant(782),
                                new Variant(35));
                    }
                });
    }

    @Test
    public void test_AdvancedFilter_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x36c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.AdvancedFilter(42);
                    }
                });
    }

    @Test
    public void test_AdvancedFilter_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x36c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(620))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.AdvancedFilter(42, new Variant(620));
                    }
                });
    }

    @Test
    public void test_AdvancedFilter_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x36c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(21), new Variant
                (709))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.AdvancedFilter(42, new Variant(21), new Variant(709));
                    }
                });
    }

    @Test
    public void test_AdvancedFilter_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x36c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(848), new Variant
                (394), new Variant(753))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.AdvancedFilter(42, new Variant(848), new Variant(394), new Variant(753));
                    }
                });
    }

    @Test
    public void test_ApplyNames_SixArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1b9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(866), new Variant(477), new
                Variant(250), new Variant(504), new Variant(462), new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ApplyNames(new Variant(866), new Variant(477), new Variant(250), new Variant(504),
                                new Variant(462), 42);
                    }
                });
    }

    @Test
    public void test_ApplyNames_SevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1b9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(541), new Variant(249), new
                Variant(812), new Variant(916), new Variant(674), new Variant(42), new Variant(283))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ApplyNames(new Variant(541), new Variant(249), new Variant(812), new Variant(916),
                                new Variant(674), 42, new Variant(283));
                    }
                });
    }

    @Test
    public void test_ApplyOutlineStyles_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1c0).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ApplyOutlineStyles();
                    }
                });
    }

    @Test
    public void test_getAxAreas_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x238).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Areas>() {
                    @Override
                    public Areas invoke() throws ActiveXException {
                        return component.getAxAreas();
                    }
                });
    }

    @Test
    public void test_AutoComplete_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x4a1).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("tESbbFKIMU"))
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.AutoComplete("tESbbFKIMU");
                    }
                });
    }

    @Test
    public void test_AutoFill_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1c1).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.AutoFill(getMock(Range.class), 42);
                    }
                });
    }

    @Test
    public void test_AutoFilter_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x319).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(953), new Variant(813), new
                Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.AutoFilter(new Variant(953), new Variant(813), 42);
                    }
                });
    }

    @Test
    public void test_AutoFilter_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x319).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(45), new Variant(536), new Variant
                (42), new Variant(901))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.AutoFilter(new Variant(45), new Variant(536), 42, new Variant(901));
                    }
                });
    }

    @Test
    public void test_AutoFilter_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x319).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(9), new Variant(110), new Variant
                (42), new Variant(868), new Variant(540))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.AutoFilter(new Variant(9), new Variant(110), 42, new Variant(868), new Variant(540));
                    }
                });
    }

    @Test
    public void test_AutoFit_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xed).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.AutoFit();
                    }
                });
    }

    @Test
    public void test_AutoFormat_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x72).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.AutoFormat(42);
                    }
                });
    }

    @Test
    public void test_AutoFormat_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x72).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(907))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.AutoFormat(42, new Variant(907));
                    }
                });
    }

    @Test
    public void test_AutoFormat_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x72).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(247), new Variant
                (481))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.AutoFormat(42, new Variant(247), new Variant(481));
                    }
                });
    }

    @Test
    public void test_AutoFormat_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x72).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(443), new Variant
                (679), new Variant(186))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.AutoFormat(42, new Variant(443), new Variant(679), new Variant(186));
                    }
                });
    }

    @Test
    public void test_AutoFormat_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x72).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(498), new Variant
                (414), new Variant(602), new Variant(707))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.AutoFormat(42, new Variant(498), new Variant(414), new Variant(602), new Variant
                                (707));
                    }
                });
    }

    @Test
    public void test_AutoFormat_SixArgs_ShouldRedirectToProxy() throws Exception {
        on(0x72).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(142), new Variant
                (654), new Variant(462), new Variant(961), new Variant(367))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.AutoFormat(42, new Variant(142), new Variant(654), new Variant(462), new Variant
                                (961), new Variant(367));
                    }
                });
    }

    @Test
    public void test_AutoFormat_SevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x72).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(410), new Variant
                (833), new Variant(350), new Variant(399), new Variant(30), new Variant(489))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.AutoFormat(42, new Variant(410), new Variant(833), new Variant(350), new Variant
                                (399), new Variant(30), new Variant(489));
                    }
                });
    }

    @Test
    public void test_AutoOutline_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x40c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.AutoOutline();
                    }
                });
    }

    @Test
    public void test_BorderAround_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x42b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(741), new Variant(42), new Variant
                (42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.BorderAround(new Variant(741), 42, 42);
                    }
                });
    }

    @Test
    public void test_BorderAround_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x42b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(111), new Variant(42), new Variant
                (42), new Variant(513))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.BorderAround(new Variant(111), 42, 42, new Variant(513));
                    }
                });
    }

    @Test
    public void test_getAxBorders_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1b3).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Borders>() {
                    @Override
                    public Borders invoke() throws ActiveXException {
                        return component.getAxBorders();
                    }
                });
    }

    @Test
    public void test_Calculate_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x117).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Calculate();
                    }
                });
    }

    @Test
    public void test_getAxCells_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xee).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.getAxCells();
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
        on(0x25b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(694))
                .verifyReturnsDispatchable(new Returns<Characters>() {
                    @Override
                    public Characters invoke() throws ActiveXException {
                        return component.getAxCharacters(new Variant(694));
                    }
                });
    }

    @Test
    public void test_getAxCharacters_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x25b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(147), new Variant(219))
                .verifyReturnsDispatchable(new Returns<Characters>() {
                    @Override
                    public Characters invoke() throws ActiveXException {
                        return component.getAxCharacters(new Variant(147), new Variant(219));
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
        on(0x1f9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(480))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.CheckSpelling(new Variant(480));
                    }
                });
    }

    @Test
    public void test_CheckSpelling_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(483), new Variant(910))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.CheckSpelling(new Variant(483), new Variant(910));
                    }
                });
    }

    @Test
    public void test_CheckSpelling_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(300), new Variant(328), new
                Variant(27))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.CheckSpelling(new Variant(300), new Variant(328), new Variant(27));
                    }
                });
    }

    @Test
    public void test_CheckSpelling_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(258), new Variant(875), new
                Variant(297), new Variant(276))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.CheckSpelling(new Variant(258), new Variant(875), new Variant(297), new Variant(276));
                    }
                });
    }

    @Test
    public void test_CheckSpelling_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(146), new Variant(215), new
                Variant(477), new Variant(835), new Variant(620))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.CheckSpelling(new Variant(146), new Variant(215), new Variant(477), new Variant
                                (835), new Variant(620));
                    }
                });
    }

    @Test
    public void test_CheckSpelling_SixArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(524), new Variant(544), new
                Variant(300), new Variant(21), new Variant(304), new Variant(274))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.CheckSpelling(new Variant(524), new Variant(544), new Variant(300), new Variant(21)
                                , new Variant(304), new Variant(274));
                    }
                });
    }

    @Test
    public void test_Clear_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6f).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Clear();
                    }
                });
    }

    @Test
    public void test_ClearContents_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x71).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ClearContents();
                    }
                });
    }

    @Test
    public void test_ClearFormats_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x70).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ClearFormats();
                    }
                });
    }

    @Test
    public void test_ClearNotes_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xef).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ClearNotes();
                    }
                });
    }

    @Test
    public void test_ClearOutline_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x40d).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ClearOutline();
                    }
                });
    }

    @Test
    public void test_getAxColumn_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xf0).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxColumn();
                    }
                });
    }

    @Test
    public void test_ColumnDifferences_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x1fe).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(395))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.ColumnDifferences(new Variant(395));
                    }
                });
    }

    @Test
    public void test_getAxColumns_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xf1).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.getAxColumns();
                    }
                });
    }

    @Test
    public void test_getAxColumnWidth_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xf2).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxColumnWidth();
                    }
                });
    }

    @Test
    public void test_setAxColumnWidth_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xf2).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(108))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxColumnWidth(new Variant(108));
                    }
                });
    }

    @Test
    public void test_Consolidate_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1e2).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Consolidate();
                    }
                });
    }

    @Test
    public void test_Consolidate_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x1e2).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(51))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Consolidate(new Variant(51));
                    }
                });
    }

    @Test
    public void test_Consolidate_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1e2).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(807), new Variant(684))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Consolidate(new Variant(807), new Variant(684));
                    }
                });
    }

    @Test
    public void test_Consolidate_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1e2).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(403), new Variant(690), new
                Variant(920))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Consolidate(new Variant(403), new Variant(690), new Variant(920));
                    }
                });
    }

    @Test
    public void test_Consolidate_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1e2).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(579), new Variant(967), new
                Variant(664), new Variant(203))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Consolidate(new Variant(579), new Variant(967), new Variant(664), new Variant(203));
                    }
                });
    }

    @Test
    public void test_Consolidate_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1e2).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(353), new Variant(168), new
                Variant(634), new Variant(677), new Variant(861))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Consolidate(new Variant(353), new Variant(168), new Variant(634), new Variant(677),
                                new Variant(861));
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
    public void test_Copy_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x227).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(692))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Copy(new Variant(692));
                    }
                });
    }

    @Test
    public void test_CopyFromRecordset_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x480).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(new UnsupportedType(0)))
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.CopyFromRecordset(new UnsupportedType(0));
                    }
                });
    }

    @Test
    public void test_CopyFromRecordset_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x480).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(new UnsupportedType(0)), new
                Variant(541))
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.CopyFromRecordset(new UnsupportedType(0), new Variant(541));
                    }
                });
    }

    @Test
    public void test_CopyFromRecordset_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x480).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(new UnsupportedType(0)), new
                Variant(415), new Variant(474))
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.CopyFromRecordset(new UnsupportedType(0), new Variant(415), new Variant(474));
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
    public void test_CreateNames_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1c9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.CreateNames();
                    }
                });
    }

    @Test
    public void test_CreateNames_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x1c9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(663))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.CreateNames(new Variant(663));
                    }
                });
    }

    @Test
    public void test_CreateNames_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1c9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(127), new Variant(278))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.CreateNames(new Variant(127), new Variant(278));
                    }
                });
    }

    @Test
    public void test_CreateNames_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1c9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(906), new Variant(117), new
                Variant(990))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.CreateNames(new Variant(906), new Variant(117), new Variant(990));
                    }
                });
    }

    @Test
    public void test_CreateNames_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1c9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(404), new Variant(31), new Variant
                (383), new Variant(673))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.CreateNames(new Variant(404), new Variant(31), new Variant(383), new Variant(673));
                    }
                });
    }

    @Test
    public void test_CreatePublisher_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1ca).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(677), new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.CreatePublisher(new Variant(677), 42);
                    }
                });
    }

    @Test
    public void test_CreatePublisher_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1ca).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(89), new Variant(42), new Variant
                (612))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.CreatePublisher(new Variant(89), 42, new Variant(612));
                    }
                });
    }

    @Test
    public void test_CreatePublisher_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1ca).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(193), new Variant(42), new Variant
                (844), new Variant(858))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.CreatePublisher(new Variant(193), 42, new Variant(844), new Variant(858));
                    }
                });
    }

    @Test
    public void test_CreatePublisher_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1ca).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(751), new Variant(42), new Variant
                (971), new Variant(3), new Variant(394))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.CreatePublisher(new Variant(751), 42, new Variant(971), new Variant(3), new Variant
                                (394));
                    }
                });
    }

    @Test
    public void test_CreatePublisher_SixArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1ca).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(94), new Variant(42), new Variant
                (469), new Variant(34), new Variant(767), new Variant(491))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.CreatePublisher(new Variant(94), 42, new Variant(469), new Variant(34), new Variant
                                (767), new Variant(491));
                    }
                });
    }

    @Test
    public void test_getAxCurrentArray_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f5).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.getAxCurrentArray();
                    }
                });
    }

    @Test
    public void test_getAxCurrentRegion_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xf3).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.getAxCurrentRegion();
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
    public void test_Cut_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x235).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(658))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Cut(new Variant(658));
                    }
                });
    }

    @Test
    public void test_DataSeries_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1d0).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(302), new Variant(42), new Variant
                (42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.DataSeries(new Variant(302), 42, 42);
                    }
                });
    }

    @Test
    public void test_DataSeries_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1d0).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(492), new Variant(42), new Variant
                (42), new Variant(227))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.DataSeries(new Variant(492), 42, 42, new Variant(227));
                    }
                });
    }

    @Test
    public void test_DataSeries_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1d0).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(100), new Variant(42), new Variant
                (42), new Variant(867), new Variant(597))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.DataSeries(new Variant(100), 42, 42, new Variant(867), new Variant(597));
                    }
                });
    }

    @Test
    public void test_DataSeries_SixArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1d0).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(163), new Variant(42), new Variant
                (42), new Variant(693), new Variant(188), new Variant(348))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.DataSeries(new Variant(163), 42, 42, new Variant(693), new Variant(188), new
                                Variant(348));
                    }
                });
    }

    @Test
    public void test_getAx_Default_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x0).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAx_Default();
                    }
                });
    }

    @Test
    public void test_getAx_Default_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x0).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(659))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAx_Default(new Variant(659));
                    }
                });
    }

    @Test
    public void test_getAx_Default_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x0).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(802), new Variant(503))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAx_Default(new Variant(802), new Variant(503));
                    }
                });
    }

    @Test
    public void test_setAx_Default_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x0).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(404))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAx_Default(new Variant(404));
                    }
                });
    }

    @Test
    public void test_setAx_Default_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x0).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(227), new Variant(957))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAx_Default(new Variant(227), new Variant(957));
                    }
                });
    }

    @Test
    public void test_setAx_Default_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x0).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(822), new Variant(928), new
                Variant(513))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAx_Default(new Variant(822), new Variant(928), new Variant(513));
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
    public void test_Delete_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x75).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(685))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Delete(new Variant(685));
                    }
                });
    }

    @Test
    public void test_getAxDependents_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x21f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.getAxDependents();
                    }
                });
    }

    @Test
    public void test_DialogBox_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xf5).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.DialogBox();
                    }
                });
    }

    @Test
    public void test_getAxDirectDependents_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x221).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.getAxDirectDependents();
                    }
                });
    }

    @Test
    public void test_getAxDirectPrecedents_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x222).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.getAxDirectPrecedents();
                    }
                });
    }

    @Test
    public void test_EditionOptions_SixArgs_ShouldRedirectToProxy() throws Exception {
        on(0x46b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(42), new Variant
                (535), new Variant(478), new Variant(42), new Variant(42))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.EditionOptions(42, 42, new Variant(535), new Variant(478), 42, 42);
                    }
                });
    }

    @Test
    public void test_EditionOptions_SevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x46b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(42), new Variant
                (301), new Variant(364), new Variant(42), new Variant(42), new Variant(302))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.EditionOptions(42, 42, new Variant(301), new Variant(364), 42, 42, new
                                Variant(302));
                    }
                });
    }

    @Test
    public void test_getAxEnd_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x1f4).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(42))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.getAxEnd(42);
                    }
                });
    }

    @Test
    public void test_getAxEntireColumn_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xf6).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.getAxEntireColumn();
                    }
                });
    }

    @Test
    public void test_getAxEntireRow_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xf7).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.getAxEntireRow();
                    }
                });
    }

    @Test
    public void test_FillDown_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xf8).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.FillDown();
                    }
                });
    }

    @Test
    public void test_FillLeft_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xf9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.FillLeft();
                    }
                });
    }

    @Test
    public void test_FillRight_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xfa).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.FillRight();
                    }
                });
    }

    @Test
    public void test_FillUp_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xfb).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.FillUp();
                    }
                });
    }

    @Test
    public void test_Find_SixArgs_ShouldRedirectToProxy() throws Exception {
        on(0x18e).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(645), new Variant(396), new
                Variant(277), new Variant(64), new Variant(584), new Variant(42))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Find(new Variant(645), new Variant(396), new Variant(277), new Variant(64),
                                new Variant(584), 42);
                    }
                });
    }

    @Test
    public void test_Find_SevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x18e).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(168), new Variant(807), new
                Variant(96), new Variant(726), new Variant(57), new Variant(42), new Variant(459))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Find(new Variant(168), new Variant(807), new Variant(96), new Variant(726),
                                new Variant(57), 42, new Variant(459));
                    }
                });
    }

    @Test
    public void test_Find_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x18e).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(863), new Variant(295), new
                Variant(804), new Variant(310), new Variant(852), new Variant(42), new Variant(646), new Variant(457))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Find(new Variant(863), new Variant(295), new Variant(804), new Variant(310),
                                new Variant(852), 42, new Variant(646), new Variant(457));
                    }
                });
    }

    @Test
    public void test_Find_NineArgs_ShouldRedirectToProxy() throws Exception {
        on(0x18e).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(843), new Variant(899), new
                Variant(990), new Variant(667), new Variant(704), new Variant(42), new Variant(402), new Variant(658)
                , new Variant(401))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Find(new Variant(843), new Variant(899), new Variant(990), new Variant(667),
                                new Variant(704), 42, new Variant(402), new Variant(658), new Variant(401));
                    }
                });
    }

    @Test
    public void test_Find_TenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x18e).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(667), new Variant(590), new
                Variant(484), new Variant(777), new Variant(634), new Variant(42), new Variant(892), new Variant(857)
                , new Variant(404), new Variant(788))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Find(new Variant(667), new Variant(590), new Variant(484), new Variant(777),
                                new Variant(634), 42, new Variant(892), new Variant(857), new Variant(404), new
                                        Variant(788));
                    }
                });
    }

    @Test
    public void test_Find_ElevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x18e).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(275), new Variant(384), new
                Variant(125), new Variant(158), new Variant(175), new Variant(42), new Variant(957), new Variant(747)
                , new Variant(62), new Variant(609), new Variant(759))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Find(new Variant(275), new Variant(384), new Variant(125), new Variant(158),
                                new Variant(175), 42, new Variant(957), new Variant(747), new Variant(62), new
                                        Variant(609), new Variant(759));
                    }
                });
    }

    @Test
    public void test_Find_TwelveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x18e).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(797), new Variant(237), new
                Variant(689), new Variant(162), new Variant(653), new Variant(42), new Variant(861), new Variant(974)
                , new Variant(625), new Variant(973), new Variant(600), new Variant(44))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Find(new Variant(797), new Variant(237), new Variant(689), new Variant(162),
                                new Variant(653), 42, new Variant(861), new Variant(974), new Variant(625), new
                                        Variant(973), new Variant(600), new Variant(44));
                    }
                });
    }

    @Test
    public void test_FindNext_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x18f).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.FindNext();
                    }
                });
    }

    @Test
    public void test_FindNext_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x18f).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(772))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.FindNext(new Variant(772));
                    }
                });
    }

    @Test
    public void test_FindPrevious_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x190).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.FindPrevious();
                    }
                });
    }

    @Test
    public void test_FindPrevious_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x190).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(406))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.FindPrevious(new Variant(406));
                    }
                });
    }

    @Test
    public void test_getAxFont_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x92).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Font>() {
                    @Override
                    public Font invoke() throws ActiveXException {
                        return component.getAxFont();
                    }
                });
    }

    @Test
    public void test_getAxFormula_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x105).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxFormula();
                    }
                });
    }

    @Test
    public void test_setAxFormula_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x105).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(264))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxFormula(new Variant(264));
                    }
                });
    }

    @Test
    public void test_getAxFormulaArray_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x24a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxFormulaArray();
                    }
                });
    }

    @Test
    public void test_setAxFormulaArray_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x24a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(620))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxFormulaArray(new Variant(620));
                    }
                });
    }

    @Test
    public void test_getAxFormulaLabel_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x564).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxFormulaLabel();
                    }
                });
    }

    @Test
    public void test_setAxFormulaLabel_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x564).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxFormulaLabel(42);
                    }
                });
    }

    @Test
    public void test_getAxFormulaHidden_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x106).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxFormulaHidden();
                    }
                });
    }

    @Test
    public void test_setAxFormulaHidden_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x106).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(681))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxFormulaHidden(new Variant(681));
                    }
                });
    }

    @Test
    public void test_getAxFormulaLocal_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x107).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxFormulaLocal();
                    }
                });
    }

    @Test
    public void test_setAxFormulaLocal_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x107).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(312))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxFormulaLocal(new Variant(312));
                    }
                });
    }

    @Test
    public void test_getAxFormulaR1C1_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x108).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxFormulaR1C1();
                    }
                });
    }

    @Test
    public void test_setAxFormulaR1C1_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x108).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(648))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxFormulaR1C1(new Variant(648));
                    }
                });
    }

    @Test
    public void test_getAxFormulaR1C1Local_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x109).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxFormulaR1C1Local();
                    }
                });
    }

    @Test
    public void test_setAxFormulaR1C1Local_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x109).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(617))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxFormulaR1C1Local(new Variant(617));
                    }
                });
    }

    @Test
    public void test_FunctionWizard_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x23b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.FunctionWizard();
                    }
                });
    }

    @Test
    public void test_GoalSeek_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1d8).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(386), new Variant(getMock(Range
                .class)))
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.GoalSeek(new Variant(386), getMock(Range.class));
                    }
                });
    }

    @Test
    public void test_Group_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2e).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Group();
                    }
                });
    }

    @Test
    public void test_Group_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x2e).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(36))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Group(new Variant(36));
                    }
                });
    }

    @Test
    public void test_Group_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2e).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(214), new Variant(62))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Group(new Variant(214), new Variant(62));
                    }
                });
    }

    @Test
    public void test_Group_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2e).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(844), new Variant(101), new Variant
                (803))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Group(new Variant(844), new Variant(101), new Variant(803));
                    }
                });
    }

    @Test
    public void test_Group_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2e).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(478), new Variant(119), new Variant
                (812), new Variant(329))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Group(new Variant(478), new Variant(119), new Variant(812), new Variant(329));
                    }
                });
    }

    @Test
    public void test_getAxHasArray_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x10a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxHasArray();
                    }
                });
    }

    @Test
    public void test_getAxHasFormula_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x10b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxHasFormula();
                    }
                });
    }

    @Test
    public void test_getAxHeight_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x7b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxHeight();
                    }
                });
    }

    @Test
    public void test_getAxHidden_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x10c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxHidden();
                    }
                });
    }

    @Test
    public void test_setAxHidden_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x10c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(371))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxHidden(new Variant(371));
                    }
                });
    }

    @Test
    public void test_getAxHorizontalAlignment_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x88).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxHorizontalAlignment();
                    }
                });
    }

    @Test
    public void test_setAxHorizontalAlignment_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x88).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(622))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxHorizontalAlignment(new Variant(622));
                    }
                });
    }

    @Test
    public void test_getAxIndentLevel_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xc9).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxIndentLevel();
                    }
                });
    }

    @Test
    public void test_setAxIndentLevel_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xc9).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(955))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxIndentLevel(new Variant(955));
                    }
                });
    }

    @Test
    public void test_InsertIndent_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x565).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.InsertIndent(42);
                    }
                });
    }

    @Test
    public void test_Insert_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xfc).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Insert();
                    }
                });
    }

    @Test
    public void test_Insert_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xfc).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(992))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Insert(new Variant(992));
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
    public void test_getAxItem_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xaa).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(352))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxItem(new Variant(352));
                    }
                });
    }

    @Test
    public void test_getAxItem_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0xaa).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(125), new Variant(89))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxItem(new Variant(125), new Variant(89));
                    }
                });
    }

    @Test
    public void test_setAxItem_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0xaa).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(420), new Variant(650))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxItem(new Variant(420), new Variant(650));
                    }
                });
    }

    @Test
    public void test_setAxItem_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0xaa).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(242), new Variant(228), new
                Variant(775))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxItem(new Variant(242), new Variant(228), new Variant(775));
                    }
                });
    }

    @Test
    public void test_Justify_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1ef).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Justify();
                    }
                });
    }

    @Test
    public void test_getAxLeft_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x7f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxLeft();
                    }
                });
    }

    @Test
    public void test_getAxListHeaderRows_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x4a3).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxListHeaderRows();
                    }
                });
    }

    @Test
    public void test_ListNames_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xfd).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ListNames();
                    }
                });
    }

    @Test
    public void test_getAxLocationInTable_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2b3).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxLocationInTable();
                    }
                });
    }

    @Test
    public void test_getAxLocked_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x10d).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxLocked();
                    }
                });
    }

    @Test
    public void test_setAxLocked_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x10d).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(465))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxLocked(new Variant(465));
                    }
                });
    }

    @Test
    public void test_Merge_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x234).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Merge();
                    }
                });
    }

    @Test
    public void test_Merge_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x234).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(906))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Merge(new Variant(906));
                    }
                });
    }

    @Test
    public void test_UnMerge_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x568).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.UnMerge();
                    }
                });
    }

    @Test
    public void test_getAxMergeArea_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x569).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.getAxMergeArea();
                    }
                });
    }

    @Test
    public void test_getAxMergeCells_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xd0).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxMergeCells();
                    }
                });
    }

    @Test
    public void test_setAxMergeCells_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xd0).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(333))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxMergeCells(new Variant(333));
                    }
                });
    }

    @Test
    public void test_getAxName_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxName();
                    }
                });
    }

    @Test
    public void test_setAxName_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x6e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(982))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxName(new Variant(982));
                    }
                });
    }

    @Test
    public void test_NavigateArrow_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x408).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.NavigateArrow();
                    }
                });
    }

    @Test
    public void test_NavigateArrow_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x408).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(740))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.NavigateArrow(new Variant(740));
                    }
                });
    }

    @Test
    public void test_NavigateArrow_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x408).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(41), new Variant(917))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.NavigateArrow(new Variant(41), new Variant(917));
                    }
                });
    }

    @Test
    public void test_NavigateArrow_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x408).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(947), new Variant(58), new Variant
                (852))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.NavigateArrow(new Variant(947), new Variant(58), new Variant(852));
                    }
                });
    }

    @Test
    public void test_getAx_NewEnum_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xfffffffc).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsGenericValue(new Returns<Object>() {
                    @Override
                    public Object invoke() throws ActiveXException {
                        return component.getAx_NewEnum();
                    }
                });
    }

    @Test
    public void test_getAxNext_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f6).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.getAxNext();
                    }
                });
    }

    @Test
    public void test_NoteText_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x467).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.NoteText();
                    }
                });
    }

    @Test
    public void test_NoteText_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x467).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(174))
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.NoteText(new Variant(174));
                    }
                });
    }

    @Test
    public void test_NoteText_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x467).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(7), new Variant(653))
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.NoteText(new Variant(7), new Variant(653));
                    }
                });
    }

    @Test
    public void test_NoteText_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x467).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(247), new Variant(68), new Variant
                (433))
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.NoteText(new Variant(247), new Variant(68), new Variant(433));
                    }
                });
    }

    @Test
    public void test_getAxNumberFormat_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xc1).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxNumberFormat();
                    }
                });
    }

    @Test
    public void test_setAxNumberFormat_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xc1).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(985))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxNumberFormat(new Variant(985));
                    }
                });
    }

    @Test
    public void test_getAxNumberFormatLocal_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x449).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxNumberFormatLocal();
                    }
                });
    }

    @Test
    public void test_setAxNumberFormatLocal_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x449).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(166))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxNumberFormatLocal(new Variant(166));
                    }
                });
    }

    @Test
    public void test_getAxOffset_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xfe).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.getAxOffset();
                    }
                });
    }

    @Test
    public void test_getAxOffset_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xfe).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(146))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.getAxOffset(new Variant(146));
                    }
                });
    }

    @Test
    public void test_getAxOffset_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0xfe).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(240), new Variant(547))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.getAxOffset(new Variant(240), new Variant(547));
                    }
                });
    }

    @Test
    public void test_getAxOrientation_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x86).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxOrientation();
                    }
                });
    }

    @Test
    public void test_setAxOrientation_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x86).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(778))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxOrientation(new Variant(778));
                    }
                });
    }

    @Test
    public void test_getAxOutlineLevel_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x10f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxOutlineLevel();
                    }
                });
    }

    @Test
    public void test_setAxOutlineLevel_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x10f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(752))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxOutlineLevel(new Variant(752));
                    }
                });
    }

    @Test
    public void test_getAxPageBreak_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xff).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxPageBreak();
                    }
                });
    }

    @Test
    public void test_setAxPageBreak_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xff).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxPageBreak(42);
                    }
                });
    }

    @Test
    public void test_Parse_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1dd).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Parse();
                    }
                });
    }

    @Test
    public void test_Parse_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x1dd).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(73))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Parse(new Variant(73));
                    }
                });
    }

    @Test
    public void test_Parse_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1dd).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(84), new Variant(787))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Parse(new Variant(84), new Variant(787));
                    }
                });
    }

    @Test
    public void test_PasteSpecial_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x403).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PasteSpecial(42, 42);
                    }
                });
    }

    @Test
    public void test_PasteSpecial_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x403).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(42), new Variant
                (274))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PasteSpecial(42, 42, new Variant(274));
                    }
                });
    }

    @Test
    public void test_PasteSpecial_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x403).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(42), new Variant
                (573), new Variant(53))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PasteSpecial(42, 42, new Variant(573), new Variant(53));
                    }
                });
    }

    @Test
    public void test_getAxPivotField_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2db).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<PivotField>() {
                    @Override
                    public PivotField invoke() throws ActiveXException {
                        return component.getAxPivotField();
                    }
                });
    }

    @Test
    public void test_getAxPivotItem_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2e4).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<PivotItem>() {
                    @Override
                    public PivotItem invoke() throws ActiveXException {
                        return component.getAxPivotItem();
                    }
                });
    }

    @Test
    public void test_getAxPivotTable_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2cc).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<PivotTable>() {
                    @Override
                    public PivotTable invoke() throws ActiveXException {
                        return component.getAxPivotTable();
                    }
                });
    }

    @Test
    public void test_getAxPrecedents_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x220).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.getAxPrecedents();
                    }
                });
    }

    @Test
    public void test_getAxPrefixCharacter_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f8).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxPrefixCharacter();
                    }
                });
    }

    @Test
    public void test_getAxPrevious_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f7).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.getAxPrevious();
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
        on(0x389).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(636))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PrintOut(new Variant(636));
                    }
                });
    }

    @Test
    public void test_PrintOut_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x389).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(845), new Variant(593))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PrintOut(new Variant(845), new Variant(593));
                    }
                });
    }

    @Test
    public void test_PrintOut_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x389).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(908), new Variant(751), new
                Variant(426))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PrintOut(new Variant(908), new Variant(751), new Variant(426));
                    }
                });
    }

    @Test
    public void test_PrintOut_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x389).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(3), new Variant(668), new Variant
                (646), new Variant(893))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PrintOut(new Variant(3), new Variant(668), new Variant(646), new Variant(893));
                    }
                });
    }

    @Test
    public void test_PrintOut_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x389).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(303), new Variant(371), new
                Variant(363), new Variant(111), new Variant(108))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PrintOut(new Variant(303), new Variant(371), new Variant(363), new Variant(111),
                                new Variant(108));
                    }
                });
    }

    @Test
    public void test_PrintOut_SixArgs_ShouldRedirectToProxy() throws Exception {
        on(0x389).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(532), new Variant(29), new Variant
                (534), new Variant(253), new Variant(669), new Variant(528))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PrintOut(new Variant(532), new Variant(29), new Variant(534), new Variant(253), new
                                Variant(669), new Variant(528));
                    }
                });
    }

    @Test
    public void test_PrintOut_SevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x389).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(231), new Variant(535), new
                Variant(540), new Variant(367), new Variant(386), new Variant(396), new Variant(554))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PrintOut(new Variant(231), new Variant(535), new Variant(540), new Variant(367),
                                new Variant(386), new Variant(396), new Variant(554));
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
        on(0x119).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(584))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PrintPreview(new Variant(584));
                    }
                });
    }

    @Test
    public void test_getAxQueryTable_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x56a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxQueryTable();
                    }
                });
    }

    @Test
    public void test_getAxRange_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xc5).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(940))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.getAxRange(new Variant(940));
                    }
                });
    }

    @Test
    public void test_getAxRange_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0xc5).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(186), new Variant(25))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.getAxRange(new Variant(186), new Variant(25));
                    }
                });
    }

    @Test
    public void test_RemoveSubtotal_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x373).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.RemoveSubtotal();
                    }
                });
    }

    @Test
    public void test_Replace_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0xe2).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(236), new Variant(226))
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.Replace(new Variant(236), new Variant(226));
                    }
                });
    }

    @Test
    public void test_Replace_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0xe2).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(324), new Variant(418), new Variant
                (137))
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.Replace(new Variant(324), new Variant(418), new Variant(137));
                    }
                });
    }

    @Test
    public void test_Replace_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0xe2).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(137), new Variant(626), new Variant
                (543), new Variant(70))
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.Replace(new Variant(137), new Variant(626), new Variant(543), new Variant(70));
                    }
                });
    }

    @Test
    public void test_Replace_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0xe2).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(266), new Variant(967), new Variant
                (47), new Variant(243), new Variant(442))
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.Replace(new Variant(266), new Variant(967), new Variant(47), new Variant
                                (243), new Variant(442));
                    }
                });
    }

    @Test
    public void test_Replace_SixArgs_ShouldRedirectToProxy() throws Exception {
        on(0xe2).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(927), new Variant(455), new Variant
                (627), new Variant(728), new Variant(339), new Variant(470))
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.Replace(new Variant(927), new Variant(455), new Variant(627), new Variant
                                (728), new Variant(339), new Variant(470));
                    }
                });
    }

    @Test
    public void test_Replace_SevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0xe2).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(911), new Variant(32), new Variant
                (59), new Variant(153), new Variant(832), new Variant(685), new Variant(582))
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.Replace(new Variant(911), new Variant(32), new Variant(59), new Variant(153)
                                , new Variant(832), new Variant(685), new Variant(582));
                    }
                });
    }

    @Test
    public void test_Replace_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0xe2).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(293), new Variant(880), new Variant
                (195), new Variant(401), new Variant(692), new Variant(141), new Variant(817), new Variant(874))
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.Replace(new Variant(293), new Variant(880), new Variant(195), new Variant
                                (401), new Variant(692), new Variant(141), new Variant(817), new Variant(874));
                    }
                });
    }

    @Test
    public void test_Replace_NineArgs_ShouldRedirectToProxy() throws Exception {
        on(0xe2).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(622), new Variant(619), new Variant
                (349), new Variant(607), new Variant(120), new Variant(797), new Variant(298), new Variant(560), new
                Variant(842))
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.Replace(new Variant(622), new Variant(619), new Variant(349), new Variant
                                (607), new Variant(120), new Variant(797), new Variant(298), new Variant(560), new
                                Variant(842));
                    }
                });
    }

    @Test
    public void test_Replace_TenArgs_ShouldRedirectToProxy() throws Exception {
        on(0xe2).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(256), new Variant(821), new Variant
                (614), new Variant(939), new Variant(356), new Variant(317), new Variant(142), new Variant(767), new
                Variant(16), new Variant(841))
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.Replace(new Variant(256), new Variant(821), new Variant(614), new Variant
                                (939), new Variant(356), new Variant(317), new Variant(142), new Variant(767), new
                                Variant(16), new Variant(841));
                    }
                });
    }

    @Test
    public void test_getAxResize_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x100).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.getAxResize();
                    }
                });
    }

    @Test
    public void test_getAxResize_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x100).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(942))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.getAxResize(new Variant(942));
                    }
                });
    }

    @Test
    public void test_getAxResize_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x100).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(40), new Variant(625))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.getAxResize(new Variant(40), new Variant(625));
                    }
                });
    }

    @Test
    public void test_getAxRow_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x101).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxRow();
                    }
                });
    }

    @Test
    public void test_RowDifferences_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x1ff).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(787))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.RowDifferences(new Variant(787));
                    }
                });
    }

    @Test
    public void test_getAxRowHeight_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x110).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxRowHeight();
                    }
                });
    }

    @Test
    public void test_setAxRowHeight_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x110).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(427))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxRowHeight(new Variant(427));
                    }
                });
    }

    @Test
    public void test_getAxRows_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x102).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.getAxRows();
                    }
                });
    }

    @Test
    public void test_Run_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run();
                    }
                });
    }

    @Test
    public void test_Run_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(442))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(442));
                    }
                });
    }

    @Test
    public void test_Run_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(246), new Variant(274))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(246), new Variant(274));
                    }
                });
    }

    @Test
    public void test_Run_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(333), new Variant(568), new
                Variant(699))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(333), new Variant(568), new Variant(699));
                    }
                });
    }

    @Test
    public void test_Run_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(765), new Variant(991), new
                Variant(645), new Variant(520))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(765), new Variant(991), new Variant(645), new Variant(520));
                    }
                });
    }

    @Test
    public void test_Run_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(899), new Variant(839), new
                Variant(101), new Variant(614), new Variant(480))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(899), new Variant(839), new Variant(101), new Variant(614),
                                new Variant(480));
                    }
                });
    }

    @Test
    public void test_Run_SixArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(534), new Variant(850), new
                Variant(93), new Variant(570), new Variant(180), new Variant(578))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(534), new Variant(850), new Variant(93), new Variant(570),
                                new Variant(180), new Variant(578));
                    }
                });
    }

    @Test
    public void test_Run_SevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(893), new Variant(66), new Variant
                (795), new Variant(357), new Variant(959), new Variant(685), new Variant(654))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(893), new Variant(66), new Variant(795), new Variant(357),
                                new Variant(959), new Variant(685), new Variant(654));
                    }
                });
    }

    @Test
    public void test_Run_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(140), new Variant(342), new
                Variant(146), new Variant(47), new Variant(621), new Variant(384), new Variant(70), new Variant(962))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(140), new Variant(342), new Variant(146), new Variant(47),
                                new Variant(621), new Variant(384), new Variant(70), new Variant(962));
                    }
                });
    }

    @Test
    public void test_Run_NineArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(955), new Variant(891), new
                Variant(267), new Variant(601), new Variant(714), new Variant(502), new Variant(143), new Variant
                (436), new Variant(545))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(955), new Variant(891), new Variant(267), new Variant(601),
                                new Variant(714), new Variant(502), new Variant(143), new Variant(436), new Variant
                                        (545));
                    }
                });
    }

    @Test
    public void test_Run_TenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(109), new Variant(545), new
                Variant(444), new Variant(216), new Variant(952), new Variant(934), new Variant(725), new Variant
                (377), new Variant(489), new Variant(25))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(109), new Variant(545), new Variant(444), new Variant(216),
                                new Variant(952), new Variant(934), new Variant(725), new Variant(377), new Variant
                                        (489), new Variant(25));
                    }
                });
    }

    @Test
    public void test_Run_ElevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(446), new Variant(683), new
                Variant(600), new Variant(514), new Variant(998), new Variant(161), new Variant(29), new Variant(181)
                , new Variant(389), new Variant(585), new Variant(280))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(446), new Variant(683), new Variant(600), new Variant(514),
                                new Variant(998), new Variant(161), new Variant(29), new Variant(181), new Variant
                                        (389), new Variant(585), new Variant(280));
                    }
                });
    }

    @Test
    public void test_Run_TwelveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(75), new Variant(972), new Variant
                (64), new Variant(880), new Variant(414), new Variant(362), new Variant(714), new Variant(687), new
                Variant(229), new Variant(356), new Variant(648), new Variant(727))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(75), new Variant(972), new Variant(64), new Variant(880),
                                new Variant(414), new Variant(362), new Variant(714), new Variant(687), new Variant
                                        (229), new Variant(356), new Variant(648), new Variant(727));
                    }
                });
    }

    @Test
    public void test_Run_ThirteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(728), new Variant(631), new
                Variant(658), new Variant(907), new Variant(469), new Variant(821), new Variant(132), new Variant
                (380), new Variant(960), new Variant(338), new Variant(630), new Variant(175), new Variant(418))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(728), new Variant(631), new Variant(658), new Variant(907),
                                new Variant(469), new Variant(821), new Variant(132), new Variant(380), new Variant
                                        (960), new Variant(338), new Variant(630), new Variant(175), new Variant(418));
                    }
                });
    }

    @Test
    public void test_Run_FourteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(146), new Variant(882), new
                Variant(559), new Variant(960), new Variant(586), new Variant(178), new Variant(12), new Variant(861)
                , new Variant(607), new Variant(2), new Variant(799), new Variant(890), new Variant(774), new Variant
                        (673))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(146), new Variant(882), new Variant(559), new Variant(960),
                                new Variant(586), new Variant(178), new Variant(12), new Variant(861), new Variant
                                        (607), new Variant(2), new Variant(799), new Variant(890), new Variant(774),
                                new Variant(673));
                    }
                });
    }

    @Test
    public void test_Run_FifteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(80), new Variant(769), new Variant
                (473), new Variant(901), new Variant(39), new Variant(929), new Variant(819), new Variant(788), new
                Variant(660), new Variant(659), new Variant(585), new Variant(415), new Variant(987), new Variant
                (603), new Variant(444))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(80), new Variant(769), new Variant(473), new Variant(901),
                                new Variant(39), new Variant(929), new Variant(819), new Variant(788), new Variant
                                        (660), new Variant(659), new Variant(585), new Variant(415), new Variant(987)
                                , new Variant(603), new Variant(444));
                    }
                });
    }

    @Test
    public void test_Run_SixteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(457), new Variant(943), new
                Variant(394), new Variant(639), new Variant(445), new Variant(490), new Variant(648), new Variant
                (561), new Variant(661), new Variant(374), new Variant(639), new Variant(0), new Variant(271), new
                Variant(459), new Variant(467), new Variant(99))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(457), new Variant(943), new Variant(394), new Variant(639),
                                new Variant(445), new Variant(490), new Variant(648), new Variant(561), new Variant
                                        (661), new Variant(374), new Variant(639), new Variant(0), new Variant(271),
                                new Variant(459), new Variant(467), new Variant(99));
                    }
                });
    }

    @Test
    public void test_Run_SeventeenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(658), new Variant(430), new
                Variant(214), new Variant(601), new Variant(558), new Variant(578), new Variant(480), new Variant
                (363), new Variant(770), new Variant(853), new Variant(803), new Variant(723), new Variant(855), new
                Variant(10), new Variant(196), new Variant(784), new Variant(705))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(658), new Variant(430), new Variant(214), new Variant(601),
                                new Variant(558), new Variant(578), new Variant(480), new Variant(363), new Variant
                                        (770), new Variant(853), new Variant(803), new Variant(723), new Variant(855)
                                , new Variant(10), new Variant(196), new Variant(784), new Variant(705));
                    }
                });
    }

    @Test
    public void test_Run_EighteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(734), new Variant(197), new
                Variant(343), new Variant(925), new Variant(985), new Variant(400), new Variant(423), new Variant
                (926), new Variant(507), new Variant(694), new Variant(753), new Variant(226), new Variant(241), new
                Variant(534), new Variant(467), new Variant(441), new Variant(731), new Variant(169))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(734), new Variant(197), new Variant(343), new Variant(925),
                                new Variant(985), new Variant(400), new Variant(423), new Variant(926), new Variant
                                        (507), new Variant(694), new Variant(753), new Variant(226), new Variant(241)
                                , new Variant(534), new Variant(467), new Variant(441), new Variant(731), new Variant
                                        (169));
                    }
                });
    }

    @Test
    public void test_Run_NineteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(855), new Variant(478), new
                Variant(419), new Variant(513), new Variant(180), new Variant(438), new Variant(171), new Variant
                (410), new Variant(161), new Variant(126), new Variant(555), new Variant(577), new Variant(537), new
                Variant(537), new Variant(854), new Variant(921), new Variant(216), new Variant(542), new Variant(913))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(855), new Variant(478), new Variant(419), new Variant(513),
                                new Variant(180), new Variant(438), new Variant(171), new Variant(410), new Variant
                                        (161), new Variant(126), new Variant(555), new Variant(577), new Variant(537)
                                , new Variant(537), new Variant(854), new Variant(921), new Variant(216), new Variant
                                        (542), new Variant(913));
                    }
                });
    }

    @Test
    public void test_Run_TwentyArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(308), new Variant(984), new
                Variant(256), new Variant(111), new Variant(431), new Variant(352), new Variant(815), new Variant
                (668), new Variant(646), new Variant(162), new Variant(388), new Variant(124), new Variant(518), new
                Variant(311), new Variant(689), new Variant(86), new Variant(289), new Variant(322), new Variant(511)
                , new Variant(418))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(308), new Variant(984), new Variant(256), new Variant(111),
                                new Variant(431), new Variant(352), new Variant(815), new Variant(668), new Variant
                                        (646), new Variant(162), new Variant(388), new Variant(124), new Variant(518)
                                , new Variant(311), new Variant(689), new Variant(86), new Variant(289), new Variant
                                        (322), new Variant(511), new Variant(418));
                    }
                });
    }

    @Test
    public void test_Run_TwentyOneArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(44), new Variant(638), new Variant
                (833), new Variant(868), new Variant(837), new Variant(548), new Variant(462), new Variant(957), new
                Variant(184), new Variant(485), new Variant(44), new Variant(21), new Variant(625), new Variant(600),
                new Variant(215), new Variant(599), new Variant(475), new Variant(880), new Variant(706), new Variant
                        (48), new Variant(943))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(44), new Variant(638), new Variant(833), new Variant(868),
                                new Variant(837), new Variant(548), new Variant(462), new Variant(957), new Variant
                                        (184), new Variant(485), new Variant(44), new Variant(21), new Variant(625),
                                new Variant(600), new Variant(215), new Variant(599), new Variant(475), new Variant
                                        (880), new Variant(706), new Variant(48), new Variant(943));
                    }
                });
    }

    @Test
    public void test_Run_TwentyTwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(557), new Variant(644), new
                Variant(357), new Variant(897), new Variant(70), new Variant(275), new Variant(616), new Variant(68),
                new Variant(768), new Variant(903), new Variant(798), new Variant(325), new Variant(590), new Variant
                        (156), new Variant(553), new Variant(468), new Variant(381), new Variant(379), new Variant
                        (453), new Variant(175), new Variant(578), new Variant(483))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(557), new Variant(644), new Variant(357), new Variant(897),
                                new Variant(70), new Variant(275), new Variant(616), new Variant(68), new Variant
                                        (768), new Variant(903), new Variant(798), new Variant(325), new Variant(590)
                                , new Variant(156), new Variant(553), new Variant(468), new Variant(381), new Variant
                                        (379), new Variant(453), new Variant(175), new Variant(578), new Variant(483));
                    }
                });
    }

    @Test
    public void test_Run_TwentyThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(817), new Variant(330), new
                Variant(674), new Variant(321), new Variant(76), new Variant(793), new Variant(101), new Variant(502)
                , new Variant(914), new Variant(294), new Variant(584), new Variant(615), new Variant(305), new
                        Variant(517), new Variant(606), new Variant(272), new Variant(364), new Variant(644), new
                        Variant(739), new Variant(674), new Variant(219), new Variant(792), new Variant(61))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(817), new Variant(330), new Variant(674), new Variant(321),
                                new Variant(76), new Variant(793), new Variant(101), new Variant(502), new Variant
                                        (914), new Variant(294), new Variant(584), new Variant(615), new Variant(305)
                                , new Variant(517), new Variant(606), new Variant(272), new Variant(364), new Variant
                                        (644), new Variant(739), new Variant(674), new Variant(219), new Variant(792)
                                , new Variant(61));
                    }
                });
    }

    @Test
    public void test_Run_TwentyFourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(36), new Variant(117), new Variant
                (499), new Variant(951), new Variant(5), new Variant(403), new Variant(826), new Variant(419), new
                Variant(871), new Variant(162), new Variant(443), new Variant(763), new Variant(711), new Variant
                (733), new Variant(107), new Variant(907), new Variant(113), new Variant(469), new Variant(61), new
                Variant(847), new Variant(201), new Variant(822), new Variant(927), new Variant(717))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(36), new Variant(117), new Variant(499), new Variant(951),
                                new Variant(5), new Variant(403), new Variant(826), new Variant(419), new Variant
                                        (871), new Variant(162), new Variant(443), new Variant(763), new Variant(711)
                                , new Variant(733), new Variant(107), new Variant(907), new Variant(113), new Variant
                                        (469), new Variant(61), new Variant(847), new Variant(201), new Variant(822),
                                new Variant(927), new Variant(717));
                    }
                });
    }

    @Test
    public void test_Run_TwentyFiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(708), new Variant(903), new
                Variant(79), new Variant(999), new Variant(13), new Variant(461), new Variant(627), new Variant(431),
                new Variant(123), new Variant(884), new Variant(701), new Variant(527), new Variant(792), new Variant
                        (844), new Variant(429), new Variant(228), new Variant(60), new Variant(876), new Variant
                        (976), new Variant(822), new Variant(791), new Variant(405), new Variant(799), new Variant
                        (535), new Variant(334))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(708), new Variant(903), new Variant(79), new Variant(999),
                                new Variant(13), new Variant(461), new Variant(627), new Variant(431), new Variant
                                        (123), new Variant(884), new Variant(701), new Variant(527), new Variant(792)
                                , new Variant(844), new Variant(429), new Variant(228), new Variant(60), new Variant
                                        (876), new Variant(976), new Variant(822), new Variant(791), new Variant(405)
                                , new Variant(799), new Variant(535), new Variant(334));
                    }
                });
    }

    @Test
    public void test_Run_TwentySixArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(485), new Variant(786), new
                Variant(749), new Variant(37), new Variant(159), new Variant(755), new Variant(678), new Variant(427)
                , new Variant(956), new Variant(88), new Variant(495), new Variant(915), new Variant(480), new
                        Variant(64), new Variant(881), new Variant(567), new Variant(987), new Variant(550), new
                        Variant(896), new Variant(407), new Variant(882), new Variant(627), new Variant(929), new
                        Variant(430), new Variant(281), new Variant(574))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(485), new Variant(786), new Variant(749), new Variant(37),
                                new Variant(159), new Variant(755), new Variant(678), new Variant(427), new Variant
                                        (956), new Variant(88), new Variant(495), new Variant(915), new Variant(480),
                                new Variant(64), new Variant(881), new Variant(567), new Variant(987), new Variant
                                        (550), new Variant(896), new Variant(407), new Variant(882), new Variant(627)
                                , new Variant(929), new Variant(430), new Variant(281), new Variant(574));
                    }
                });
    }

    @Test
    public void test_Run_TwentySevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(760), new Variant(517), new
                Variant(672), new Variant(927), new Variant(851), new Variant(49), new Variant(855), new Variant(305)
                , new Variant(967), new Variant(80), new Variant(903), new Variant(461), new Variant(125), new
                        Variant(929), new Variant(847), new Variant(627), new Variant(640), new Variant(313), new
                        Variant(743), new Variant(132), new Variant(781), new Variant(618), new Variant(37), new
                        Variant(963), new Variant(87), new Variant(710), new Variant(754))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(760), new Variant(517), new Variant(672), new Variant(927),
                                new Variant(851), new Variant(49), new Variant(855), new Variant(305), new Variant
                                        (967), new Variant(80), new Variant(903), new Variant(461), new Variant(125),
                                new Variant(929), new Variant(847), new Variant(627), new Variant(640), new Variant
                                        (313), new Variant(743), new Variant(132), new Variant(781), new Variant(618)
                                , new Variant(37), new Variant(963), new Variant(87), new Variant(710), new Variant
                                        (754));
                    }
                });
    }

    @Test
    public void test_Run_TwentyEightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(665), new Variant(175), new
                Variant(873), new Variant(711), new Variant(496), new Variant(485), new Variant(468), new Variant
                (713), new Variant(967), new Variant(429), new Variant(294), new Variant(999), new Variant(316), new
                Variant(992), new Variant(429), new Variant(380), new Variant(425), new Variant(798), new Variant
                (882), new Variant(917), new Variant(493), new Variant(221), new Variant(11), new Variant(368), new
                Variant(434), new Variant(713), new Variant(370), new Variant(214))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(665), new Variant(175), new Variant(873), new Variant(711),
                                new Variant(496), new Variant(485), new Variant(468), new Variant(713), new Variant
                                        (967), new Variant(429), new Variant(294), new Variant(999), new Variant(316)
                                , new Variant(992), new Variant(429), new Variant(380), new Variant(425), new Variant
                                        (798), new Variant(882), new Variant(917), new Variant(493), new Variant(221)
                                , new Variant(11), new Variant(368), new Variant(434), new Variant(713), new Variant
                                        (370), new Variant(214));
                    }
                });
    }

    @Test
    public void test_Run_TwentyNineArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(854), new Variant(352), new
                Variant(698), new Variant(368), new Variant(659), new Variant(921), new Variant(993), new Variant
                (946), new Variant(586), new Variant(552), new Variant(105), new Variant(934), new Variant(213), new
                Variant(728), new Variant(881), new Variant(335), new Variant(97), new Variant(262), new Variant(793)
                , new Variant(488), new Variant(858), new Variant(581), new Variant(3), new Variant(97), new Variant
                        (760), new Variant(364), new Variant(660), new Variant(269), new Variant(792))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(854), new Variant(352), new Variant(698), new Variant(368),
                                new Variant(659), new Variant(921), new Variant(993), new Variant(946), new Variant
                                        (586), new Variant(552), new Variant(105), new Variant(934), new Variant(213)
                                , new Variant(728), new Variant(881), new Variant(335), new Variant(97), new Variant
                                        (262), new Variant(793), new Variant(488), new Variant(858), new Variant(581)
                                , new Variant(3), new Variant(97), new Variant(760), new Variant(364), new Variant
                                        (660), new Variant(269), new Variant(792));
                    }
                });
    }

    @Test
    public void test_Run_ThirtyArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(704), new Variant(721), new
                Variant(627), new Variant(405), new Variant(199), new Variant(831), new Variant(87), new Variant(661)
                , new Variant(914), new Variant(475), new Variant(613), new Variant(696), new Variant(718), new
                        Variant(864), new Variant(233), new Variant(347), new Variant(600), new Variant(590), new
                        Variant(277), new Variant(67), new Variant(762), new Variant(303), new Variant(136), new
                        Variant(237), new Variant(127), new Variant(958), new Variant(584), new Variant(595), new
                        Variant(302), new Variant(137))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(704), new Variant(721), new Variant(627), new Variant(405),
                                new Variant(199), new Variant(831), new Variant(87), new Variant(661), new Variant
                                        (914), new Variant(475), new Variant(613), new Variant(696), new Variant(718)
                                , new Variant(864), new Variant(233), new Variant(347), new Variant(600), new Variant
                                        (590), new Variant(277), new Variant(67), new Variant(762), new Variant(303),
                                new Variant(136), new Variant(237), new Variant(127), new Variant(958), new Variant
                                        (584), new Variant(595), new Variant(302), new Variant(137));
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
    public void test_Show_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f0).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Show();
                    }
                });
    }

    @Test
    public void test_ShowDependents_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x36d).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ShowDependents();
                    }
                });
    }

    @Test
    public void test_ShowDependents_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x36d).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(244))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ShowDependents(new Variant(244));
                    }
                });
    }

    @Test
    public void test_getAxShowDetail_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x249).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxShowDetail();
                    }
                });
    }

    @Test
    public void test_setAxShowDetail_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x249).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(448))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxShowDetail(new Variant(448));
                    }
                });
    }

    @Test
    public void test_ShowErrors_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x36e).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ShowErrors();
                    }
                });
    }

    @Test
    public void test_ShowPrecedents_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x36f).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ShowPrecedents();
                    }
                });
    }

    @Test
    public void test_ShowPrecedents_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x36f).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(262))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ShowPrecedents(new Variant(262));
                    }
                });
    }

    @Test
    public void test_getAxShrinkToFit_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xd1).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxShrinkToFit();
                    }
                });
    }

    @Test
    public void test_setAxShrinkToFit_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xd1).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(661))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxShrinkToFit(new Variant(661));
                    }
                });
    }

    @Test
    public void test_Sort_TwelveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x370).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(272), new Variant(42), new Variant
                (796), new Variant(967), new Variant(42), new Variant(848), new Variant(42), new Variant(42), new
                Variant(837), new Variant(507), new Variant(42), new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Sort(new Variant(272), 42, new Variant(796), new Variant(967), 42, new Variant(848)
                                , 42, 42, new Variant(837), new Variant(507), 42, 42);
                    }
                });
    }

    @Test
    public void test_Sort_ThirteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x370).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(384), new Variant(42), new Variant
                (385), new Variant(468), new Variant(42), new Variant(631), new Variant(42), new Variant(42), new
                Variant(979), new Variant(379), new Variant(42), new Variant(42), new Variant(567))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Sort(new Variant(384), 42, new Variant(385), new Variant(468), 42, new Variant(631)
                                , 42, 42, new Variant(979), new Variant(379), 42, 42, new Variant(567));
                    }
                });
    }

    @Test
    public void test_Sort_FourteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x370).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(390), new Variant(42), new Variant
                (145), new Variant(33), new Variant(42), new Variant(29), new Variant(42), new Variant(42), new
                Variant(151), new Variant(875), new Variant(42), new Variant(42), new Variant(860), new Variant(168))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Sort(new Variant(390), 42, new Variant(145), new Variant(33), 42, new Variant(29),
                                42, 42, new Variant(151), new Variant(875), 42, 42, new Variant(860), new Variant(168));
                    }
                });
    }

    @Test
    public void test_Sort_FifteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x370).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(318), new Variant(42), new Variant
                (238), new Variant(640), new Variant(42), new Variant(245), new Variant(42), new Variant(42), new
                Variant(895), new Variant(970), new Variant(42), new Variant(42), new Variant(365), new Variant(527),
                new Variant(615))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Sort(new Variant(318), 42, new Variant(238), new Variant(640), 42, new Variant(245)
                                , 42, 42, new Variant(895), new Variant(970), 42, 42, new Variant(365), new Variant
                                        (527), new Variant(615));
                    }
                });
    }

    @Test
    public void test_SortSpecial_TwelveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x371).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(816), new Variant
                (42), new Variant(536), new Variant(728), new Variant(42), new Variant(181), new Variant(42), new
                Variant(42), new Variant(453), new Variant(97), new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SortSpecial(42, new Variant(816), 42, new Variant(536), new Variant(728), 42, new
                                Variant(181), 42, 42, new Variant(453), new Variant(97), 42);
                    }
                });
    }

    @Test
    public void test_getAxSoundNote_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x394).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<SoundNote>() {
                    @Override
                    public SoundNote invoke() throws ActiveXException {
                        return component.getAxSoundNote();
                    }
                });
    }

    @Test
    public void test_SpecialCells_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x19a).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.SpecialCells(42);
                    }
                });
    }

    @Test
    public void test_SpecialCells_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x19a).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(93))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.SpecialCells(42, new Variant(93));
                    }
                });
    }

    @Test
    public void test_getAxStyle_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x104).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxStyle();
                    }
                });
    }

    @Test
    public void test_setAxStyle_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x104).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(568))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxStyle(new Variant(568));
                    }
                });
    }

    @Test
    public void test_SubscribeTo_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1e1).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("zJLObLmSTu"), new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SubscribeTo("zJLObLmSTu", 42);
                    }
                });
    }

    @Test
    public void test_Subtotal_SixArgs_ShouldRedirectToProxy() throws Exception {
        on(0x372).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(42), new Variant
                (511), new Variant(56), new Variant(804), new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Subtotal(42, 42, new Variant(511), new Variant(56), new Variant(804), 42);
                    }
                });
    }

    @Test
    public void test_getAxSummary_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x111).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxSummary();
                    }
                });
    }

    @Test
    public void test_Table_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f1).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Table();
                    }
                });
    }

    @Test
    public void test_Table_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x1f1).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(898))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Table(new Variant(898));
                    }
                });
    }

    @Test
    public void test_Table_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f1).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(330), new Variant(257))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Table(new Variant(330), new Variant(257));
                    }
                });
    }

    @Test
    public void test_getAxText_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x8a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxText();
                    }
                });
    }

    @Test
    public void test_TextToColumns_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x410).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(101), new Variant(42), new Variant
                (42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.TextToColumns(new Variant(101), 42, 42);
                    }
                });
    }

    @Test
    public void test_TextToColumns_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x410).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(762), new Variant(42), new Variant
                (42), new Variant(0))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.TextToColumns(new Variant(762), 42, 42, new Variant(0));
                    }
                });
    }

    @Test
    public void test_TextToColumns_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x410).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(566), new Variant(42), new Variant
                (42), new Variant(626), new Variant(880))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.TextToColumns(new Variant(566), 42, 42, new Variant(626), new Variant(880));
                    }
                });
    }

    @Test
    public void test_TextToColumns_SixArgs_ShouldRedirectToProxy() throws Exception {
        on(0x410).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(43), new Variant(42), new Variant
                (42), new Variant(884), new Variant(348), new Variant(673))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.TextToColumns(new Variant(43), 42, 42, new Variant(884), new Variant(348), new
                                Variant(673));
                    }
                });
    }

    @Test
    public void test_TextToColumns_SevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x410).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(192), new Variant(42), new Variant
                (42), new Variant(109), new Variant(12), new Variant(258), new Variant(802))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.TextToColumns(new Variant(192), 42, 42, new Variant(109), new Variant(12), new
                                Variant(258), new Variant(802));
                    }
                });
    }

    @Test
    public void test_TextToColumns_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x410).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(596), new Variant(42), new Variant
                (42), new Variant(523), new Variant(993), new Variant(648), new Variant(104), new Variant(511))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.TextToColumns(new Variant(596), 42, 42, new Variant(523), new Variant(993), new
                                Variant(648), new Variant(104), new Variant(511));
                    }
                });
    }

    @Test
    public void test_TextToColumns_NineArgs_ShouldRedirectToProxy() throws Exception {
        on(0x410).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(846), new Variant(42), new Variant
                (42), new Variant(668), new Variant(464), new Variant(362), new Variant(361), new Variant(113), new
                Variant(12))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.TextToColumns(new Variant(846), 42, 42, new Variant(668), new Variant(464), new
                                Variant(362), new Variant(361), new Variant(113), new Variant(12));
                    }
                });
    }

    @Test
    public void test_TextToColumns_TenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x410).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(808), new Variant(42), new Variant
                (42), new Variant(798), new Variant(848), new Variant(724), new Variant(477), new Variant(307), new
                Variant(567), new Variant(522))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.TextToColumns(new Variant(808), 42, 42, new Variant(798), new Variant(848), new
                                Variant(724), new Variant(477), new Variant(307), new Variant(567), new Variant(522));
                    }
                });
    }

    @Test
    public void test_TextToColumns_ElevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x410).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(248), new Variant(42), new Variant
                (42), new Variant(642), new Variant(567), new Variant(242), new Variant(208), new Variant(345), new
                Variant(760), new Variant(610), new Variant(602))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.TextToColumns(new Variant(248), 42, 42, new Variant(642), new Variant(567), new
                                Variant(242), new Variant(208), new Variant(345), new Variant(760), new Variant(610),
                                new Variant(602));
                    }
                });
    }

    @Test
    public void test_getAxTop_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x7e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxTop();
                    }
                });
    }

    @Test
    public void test_Ungroup_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xf4).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Ungroup();
                    }
                });
    }

    @Test
    public void test_getAxUseStandardHeight_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x112).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxUseStandardHeight();
                    }
                });
    }

    @Test
    public void test_setAxUseStandardHeight_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x112).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(479))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxUseStandardHeight(new Variant(479));
                    }
                });
    }

    @Test
    public void test_getAxUseStandardWidth_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x113).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxUseStandardWidth();
                    }
                });
    }

    @Test
    public void test_setAxUseStandardWidth_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x113).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(595))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxUseStandardWidth(new Variant(595));
                    }
                });
    }

    @Test
    public void test_getAxValidation_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x56b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Validation>() {
                    @Override
                    public Validation invoke() throws ActiveXException {
                        return component.getAxValidation();
                    }
                });
    }

    @Test
    public void test_getAxValue_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxValue();
                    }
                });
    }

    @Test
    public void test_setAxValue_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x6).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(28))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxValue(new Variant(28));
                    }
                });
    }

    @Test
    public void test_getAxValue2_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x56c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxValue2();
                    }
                });
    }

    @Test
    public void test_setAxValue2_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x56c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(364))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxValue2(new Variant(364));
                    }
                });
    }

    @Test
    public void test_getAxVerticalAlignment_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x89).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxVerticalAlignment();
                    }
                });
    }

    @Test
    public void test_setAxVerticalAlignment_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x89).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(737))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxVerticalAlignment(new Variant(737));
                    }
                });
    }

    @Test
    public void test_getAxWidth_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x7a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxWidth();
                    }
                });
    }

    @Test
    public void test_getAxWorksheet_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x15c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<ExcelSheet>() {
                    @Override
                    public ExcelSheet invoke() throws ActiveXException {
                        return component.getAxWorksheet();
                    }
                });
    }

    @Test
    public void test_getAxWrapText_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x114).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxWrapText();
                    }
                });
    }

    @Test
    public void test_setAxWrapText_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x114).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(300))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxWrapText(new Variant(300));
                    }
                });
    }

    @Test
    public void test_AddComment_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x56d).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsDispatchable(new Returns<Comment>() {
                    @Override
                    public Comment invoke() throws ActiveXException {
                        return component.AddComment();
                    }
                });
    }

    @Test
    public void test_AddComment_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x56d).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(584))
                .verifyReturnsDispatchable(new Returns<Comment>() {
                    @Override
                    public Comment invoke() throws ActiveXException {
                        return component.AddComment(new Variant(584));
                    }
                });
    }

    @Test
    public void test_getAxComment_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x38e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Comment>() {
                    @Override
                    public Comment invoke() throws ActiveXException {
                        return component.getAxComment();
                    }
                });
    }

    @Test
    public void test_ClearComments_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x56e).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ClearComments();
                    }
                });
    }

    @Test
    public void test_getAxPhonetic_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x56f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Phonetic>() {
                    @Override
                    public Phonetic invoke() throws ActiveXException {
                        return component.getAxPhonetic();
                    }
                });
    }

    @Test
    public void test_getAxFormatConditions_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x570).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<FormatConditions>() {
                    @Override
                    public FormatConditions invoke() throws ActiveXException {
                        return component.getAxFormatConditions();
                    }
                });
    }

    @Test
    public void test_getAxReadingOrder_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3cf).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxReadingOrder();
                    }
                });
    }

    @Test
    public void test_setAxReadingOrder_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x3cf).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxReadingOrder(42);
                    }
                });
    }

    @Test
    public void test_getAxHyperlinks_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x571).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Hyperlinks>() {
                    @Override
                    public Hyperlinks invoke() throws ActiveXException {
                        return component.getAxHyperlinks();
                    }
                });
    }

}