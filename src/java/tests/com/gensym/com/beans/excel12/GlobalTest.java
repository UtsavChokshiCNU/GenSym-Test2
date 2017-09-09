package com.gensym.com.beans.excel12;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXDispatchable;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import com.gensym.com.beans.office20.Assistant;
import com.gensym.com.beans.office20.CommandBars;
import org.junit.Before;
import org.junit.Test;

public class GlobalTest extends ActiveXDispatchableTestBase {

    private Global component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new Global(axProxy);
    }

    @Test
    public void test_QueryInterface_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60000000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(2), new Variant(495))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.QueryInterface(new Variant(2), new Variant(495));
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
        on(0x60010000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(41))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfoCount(new Variant(41));
                    }
                });
    }

    @Test
    public void test_GetTypeInfo_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010001).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42L), new Variant(42L), new
                Variant(617))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfo(42L, 42L, new Variant(617));
                    }
                });
    }

    @Test
    public void test_GetIDsOfNames_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(155), new Variant(742), new
                Variant(42L), new Variant(42L), new Variant(209))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetIDsOfNames(new Variant(155), new Variant(742), 42L, 42L, new Variant(209));
                    }
                });
    }

    @Test
    public void test_Invoke_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010003).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(798), new
                Variant(42L), new Variant(42), new Variant(350), new Variant(57), new Variant(309), new Variant(77))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Invoke(42, new Variant(798), 42L, 42, new Variant(350), new Variant(57), new
                                Variant(309), new Variant(77));
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
                .verifyReturnsDispatchable(new Returns<ExcelApplication>() {
                    @Override
                    public ExcelApplication invoke() throws ActiveXException {
                        return component.getAxParent();
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
    public void test_getAxActiveDialog_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x32f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<DialogSheet>() {
                    @Override
                    public DialogSheet invoke() throws ActiveXException {
                        return component.getAxActiveDialog();
                    }
                });
    }

    @Test
    public void test_getAxActiveMenuBar_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2f6).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<MenuBar>() {
                    @Override
                    public MenuBar invoke() throws ActiveXException {
                        return component.getAxActiveMenuBar();
                    }
                });
    }

    @Test
    public void test_getAxActivePrinter_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x132).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxActivePrinter();
                    }
                });
    }

    @Test
    public void test_setAxActivePrinter_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x132).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("lShPzsDwcA"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxActivePrinter("lShPzsDwcA");
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
    public void test_getAxActiveWindow_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2f7).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Window>() {
                    @Override
                    public Window invoke() throws ActiveXException {
                        return component.getAxActiveWindow();
                    }
                });
    }

    @Test
    public void test_getAxActiveWorkbook_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x134).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxActiveWorkbook();
                    }
                });
    }

    @Test
    public void test_getAxAddIns_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x225).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<AddIns>() {
                    @Override
                    public AddIns invoke() throws ActiveXException {
                        return component.getAxAddIns();
                    }
                });
    }

    @Test
    public void test_getAxAssistant_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x59e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Assistant>() {
                    @Override
                    public Assistant invoke() throws ActiveXException {
                        return component.getAxAssistant();
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
    public void test_getAxCharts_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x79).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Sheets>() {
                    @Override
                    public Sheets invoke() throws ActiveXException {
                        return component.getAxCharts();
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
    public void test_getAxCommandBars_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x59f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<CommandBars>() {
                    @Override
                    public CommandBars invoke() throws ActiveXException {
                        return component.getAxCommandBars();
                    }
                });
    }

    @Test
    public void test_getAxDDEAppReturnCode_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x14c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxDDEAppReturnCode();
                    }
                });
    }

    @Test
    public void test_DDEExecute_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x14d).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant("GZhOioGxEy"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.DDEExecute(42, "GZhOioGxEy");
                    }
                });
    }

    @Test
    public void test_DDEInitiate_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x14e).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("JvDGJdApGH"), new Variant
                ("JpgVyYpMgH"))
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.DDEInitiate("JvDGJdApGH", "JpgVyYpMgH");
                    }
                });
    }

    @Test
    public void test_DDEPoke_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x14f).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(382), new Variant
                (131))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.DDEPoke(42, new Variant(382), new Variant(131));
                    }
                });
    }

    @Test
    public void test_DDERequest_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x150).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant("BMuLqkXHGn"))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.DDERequest(42, "BMuLqkXHGn");
                    }
                });
    }

    @Test
    public void test_DDETerminate_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x151).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.DDETerminate(42);
                    }
                });
    }

    @Test
    public void test_getAxDialogSheets_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2fc).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Sheets>() {
                    @Override
                    public Sheets invoke() throws ActiveXException {
                        return component.getAxDialogSheets();
                    }
                });
    }

    @Test
    public void test_Evaluate_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x1).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(181))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Evaluate(new Variant(181));
                    }
                });
    }

    @Test
    public void test__Evaluate_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xfffffffb).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(821))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._Evaluate(new Variant(821));
                    }
                });
    }

    @Test
    public void test_ExecuteExcel4Macro_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x15e).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("mAZMeHJDEI"))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.ExecuteExcel4Macro("mAZMeHJDEI");
                    }
                });
    }

    @Test
    public void test_Intersect_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2fe).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Intersect(getMock(Range.class), getMock(Range.class));
                    }
                });
    }

    @Test
    public void test_Intersect_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2fe).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(359))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Intersect(getMock(Range.class), getMock(Range.class), new Variant(359));
                    }
                });
    }

    @Test
    public void test_Intersect_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2fe).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(549), new Variant(617))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Intersect(getMock(Range.class), getMock(Range.class), new Variant(549), new
                                Variant(617));
                    }
                });
    }

    @Test
    public void test_Intersect_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2fe).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(243), new Variant(496), new Variant(679))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Intersect(getMock(Range.class), getMock(Range.class), new Variant(243), new
                                Variant(496), new Variant(679));
                    }
                });
    }

    @Test
    public void test_Intersect_SixArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2fe).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(834), new Variant(436), new Variant(650), new Variant(584))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Intersect(getMock(Range.class), getMock(Range.class), new Variant(834), new
                                Variant(436), new Variant(650), new Variant(584));
                    }
                });
    }

    @Test
    public void test_Intersect_SevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2fe).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(112), new Variant(409), new Variant(940), new Variant(977), new
                Variant(465))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Intersect(getMock(Range.class), getMock(Range.class), new Variant(112), new
                                Variant(409), new Variant(940), new Variant(977), new Variant(465));
                    }
                });
    }

    @Test
    public void test_Intersect_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2fe).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(401), new Variant(37), new Variant(251), new Variant(427), new
                Variant(101), new Variant(293))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Intersect(getMock(Range.class), getMock(Range.class), new Variant(401), new
                                Variant(37), new Variant(251), new Variant(427), new Variant(101), new Variant(293));
                    }
                });
    }

    @Test
    public void test_Intersect_NineArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2fe).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(753), new Variant(606), new Variant(869), new Variant(824), new
                Variant(384), new Variant(137), new Variant(56))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Intersect(getMock(Range.class), getMock(Range.class), new Variant(753), new
                                Variant(606), new Variant(869), new Variant(824), new Variant(384), new Variant(137),
                                new Variant(56));
                    }
                });
    }

    @Test
    public void test_Intersect_TenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2fe).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(79), new Variant(266), new Variant(735), new Variant(936), new
                Variant(932), new Variant(26), new Variant(710), new Variant(164))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Intersect(getMock(Range.class), getMock(Range.class), new Variant(79), new
                                Variant(266), new Variant(735), new Variant(936), new Variant(932), new Variant(26),
                                new Variant(710), new Variant(164));
                    }
                });
    }

    @Test
    public void test_Intersect_ElevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2fe).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(819), new Variant(403), new Variant(308), new Variant(719), new
                Variant(336), new Variant(233), new Variant(814), new Variant(894), new Variant(201))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Intersect(getMock(Range.class), getMock(Range.class), new Variant(819), new
                                Variant(403), new Variant(308), new Variant(719), new Variant(336), new Variant(233),
                                new Variant(814), new Variant(894), new Variant(201));
                    }
                });
    }

    @Test
    public void test_Intersect_TwelveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2fe).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(344), new Variant(838), new Variant(934), new Variant(241), new
                Variant(411), new Variant(136), new Variant(940), new Variant(541), new Variant(565), new Variant(569))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Intersect(getMock(Range.class), getMock(Range.class), new Variant(344), new
                                Variant(838), new Variant(934), new Variant(241), new Variant(411), new Variant(136),
                                new Variant(940), new Variant(541), new Variant(565), new Variant(569));
                    }
                });
    }

    @Test
    public void test_Intersect_ThirteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2fe).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(758), new Variant(342), new Variant(12), new Variant(205), new
                Variant(582), new Variant(420), new Variant(931), new Variant(756), new Variant(375), new Variant
                (444), new Variant(206))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Intersect(getMock(Range.class), getMock(Range.class), new Variant(758), new
                                Variant(342), new Variant(12), new Variant(205), new Variant(582), new Variant(420),
                                new Variant(931), new Variant(756), new Variant(375), new Variant(444), new Variant
                                        (206));
                    }
                });
    }

    @Test
    public void test_Intersect_FourteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2fe).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(735), new Variant(664), new Variant(278), new Variant(113), new
                Variant(157), new Variant(886), new Variant(637), new Variant(433), new Variant(965), new Variant
                (919), new Variant(971), new Variant(572))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Intersect(getMock(Range.class), getMock(Range.class), new Variant(735), new
                                Variant(664), new Variant(278), new Variant(113), new Variant(157), new Variant(886),
                                new Variant(637), new Variant(433), new Variant(965), new Variant(919), new Variant
                                        (971), new Variant(572));
                    }
                });
    }

    @Test
    public void test_Intersect_FifteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2fe).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(447), new Variant(56), new Variant(761), new Variant(588), new
                Variant(131), new Variant(775), new Variant(24), new Variant(606), new Variant(581), new Variant(109)
                , new Variant(999), new Variant(897), new Variant(764))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Intersect(getMock(Range.class), getMock(Range.class), new Variant(447), new
                                Variant(56), new Variant(761), new Variant(588), new Variant(131), new Variant(775),
                                new Variant(24), new Variant(606), new Variant(581), new Variant(109), new Variant
                                        (999), new Variant(897), new Variant(764));
                    }
                });
    }

    @Test
    public void test_Intersect_SixteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2fe).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(371), new Variant(505), new Variant(122), new Variant(870), new
                Variant(973), new Variant(754), new Variant(732), new Variant(330), new Variant(972), new Variant
                (830), new Variant(453), new Variant(857), new Variant(670), new Variant(550))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Intersect(getMock(Range.class), getMock(Range.class), new Variant(371), new
                                Variant(505), new Variant(122), new Variant(870), new Variant(973), new Variant(754),
                                new Variant(732), new Variant(330), new Variant(972), new Variant(830), new Variant
                                        (453), new Variant(857), new Variant(670), new Variant(550));
                    }
                });
    }

    @Test
    public void test_Intersect_SeventeenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2fe).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(204), new Variant(65), new Variant(400), new Variant(648), new
                Variant(935), new Variant(952), new Variant(659), new Variant(129), new Variant(657), new Variant
                (945), new Variant(860), new Variant(602), new Variant(631), new Variant(398), new Variant(902))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Intersect(getMock(Range.class), getMock(Range.class), new Variant(204), new
                                Variant(65), new Variant(400), new Variant(648), new Variant(935), new Variant(952),
                                new Variant(659), new Variant(129), new Variant(657), new Variant(945), new Variant
                                        (860), new Variant(602), new Variant(631), new Variant(398), new Variant(902));
                    }
                });
    }

    @Test
    public void test_Intersect_EighteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2fe).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(396), new Variant(692), new Variant(515), new Variant(186), new
                Variant(378), new Variant(650), new Variant(98), new Variant(646), new Variant(866), new Variant(649)
                , new Variant(273), new Variant(148), new Variant(799), new Variant(533), new Variant(876), new
                        Variant(993))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Intersect(getMock(Range.class), getMock(Range.class), new Variant(396), new
                                Variant(692), new Variant(515), new Variant(186), new Variant(378), new Variant(650),
                                new Variant(98), new Variant(646), new Variant(866), new Variant(649), new Variant
                                        (273), new Variant(148), new Variant(799), new Variant(533), new Variant(876)
                                , new Variant(993));
                    }
                });
    }

    @Test
    public void test_Intersect_NineteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2fe).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(110), new Variant(511), new Variant(295), new Variant(950), new
                Variant(306), new Variant(782), new Variant(909), new Variant(627), new Variant(382), new Variant
                (190), new Variant(846), new Variant(87), new Variant(79), new Variant(790), new Variant(840), new
                Variant(181), new Variant(92))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Intersect(getMock(Range.class), getMock(Range.class), new Variant(110), new
                                Variant(511), new Variant(295), new Variant(950), new Variant(306), new Variant(782),
                                new Variant(909), new Variant(627), new Variant(382), new Variant(190), new Variant
                                        (846), new Variant(87), new Variant(79), new Variant(790), new Variant(840),
                                new Variant(181), new Variant(92));
                    }
                });
    }

    @Test
    public void test_Intersect_TwentyArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2fe).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(95), new Variant(133), new Variant(848), new Variant(586), new
                Variant(601), new Variant(29), new Variant(774), new Variant(832), new Variant(8), new Variant(616),
                new Variant(131), new Variant(444), new Variant(651), new Variant(578), new Variant(749), new Variant
                        (777), new Variant(701), new Variant(523))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Intersect(getMock(Range.class), getMock(Range.class), new Variant(95), new
                                Variant(133), new Variant(848), new Variant(586), new Variant(601), new Variant(29),
                                new Variant(774), new Variant(832), new Variant(8), new Variant(616), new Variant
                                        (131), new Variant(444), new Variant(651), new Variant(578), new Variant(749)
                                , new Variant(777), new Variant(701), new Variant(523));
                    }
                });
    }

    @Test
    public void test_Intersect_TwentyOneArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2fe).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(916), new Variant(78), new Variant(732), new Variant(98), new
                Variant(132), new Variant(251), new Variant(175), new Variant(670), new Variant(211), new Variant
                (890), new Variant(285), new Variant(312), new Variant(981), new Variant(144), new Variant(952), new
                Variant(280), new Variant(112), new Variant(543), new Variant(913))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Intersect(getMock(Range.class), getMock(Range.class), new Variant(916), new
                                Variant(78), new Variant(732), new Variant(98), new Variant(132), new Variant(251),
                                new Variant(175), new Variant(670), new Variant(211), new Variant(890), new Variant
                                        (285), new Variant(312), new Variant(981), new Variant(144), new Variant(952)
                                , new Variant(280), new Variant(112), new Variant(543), new Variant(913));
                    }
                });
    }

    @Test
    public void test_Intersect_TwentyTwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2fe).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(42), new Variant(385), new Variant(977), new Variant(85), new
                Variant(796), new Variant(653), new Variant(571), new Variant(764), new Variant(272), new Variant
                (108), new Variant(604), new Variant(586), new Variant(817), new Variant(95), new Variant(608), new
                Variant(87), new Variant(515), new Variant(146), new Variant(717), new Variant(889))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Intersect(getMock(Range.class), getMock(Range.class), new Variant(42), new
                                Variant(385), new Variant(977), new Variant(85), new Variant(796), new Variant(653),
                                new Variant(571), new Variant(764), new Variant(272), new Variant(108), new Variant
                                        (604), new Variant(586), new Variant(817), new Variant(95), new Variant(608),
                                new Variant(87), new Variant(515), new Variant(146), new Variant(717), new Variant
                                        (889));
                    }
                });
    }

    @Test
    public void test_Intersect_TwentyThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2fe).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(492), new Variant(909), new Variant(433), new Variant(281), new
                Variant(320), new Variant(484), new Variant(718), new Variant(307), new Variant(246), new Variant
                (559), new Variant(468), new Variant(590), new Variant(125), new Variant(524), new Variant(817), new
                Variant(436), new Variant(793), new Variant(951), new Variant(743), new Variant(876), new Variant(608))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Intersect(getMock(Range.class), getMock(Range.class), new Variant(492), new
                                Variant(909), new Variant(433), new Variant(281), new Variant(320), new Variant(484),
                                new Variant(718), new Variant(307), new Variant(246), new Variant(559), new Variant
                                        (468), new Variant(590), new Variant(125), new Variant(524), new Variant(817)
                                , new Variant(436), new Variant(793), new Variant(951), new Variant(743), new Variant
                                        (876), new Variant(608));
                    }
                });
    }

    @Test
    public void test_Intersect_TwentyFourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2fe).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(547), new Variant(138), new Variant(947), new Variant(228), new
                Variant(475), new Variant(636), new Variant(361), new Variant(813), new Variant(306), new Variant
                (855), new Variant(407), new Variant(852), new Variant(80), new Variant(39), new Variant(702), new
                Variant(838), new Variant(125), new Variant(849), new Variant(34), new Variant(971), new Variant(112)
                , new Variant(780))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Intersect(getMock(Range.class), getMock(Range.class), new Variant(547), new
                                Variant(138), new Variant(947), new Variant(228), new Variant(475), new Variant(636),
                                new Variant(361), new Variant(813), new Variant(306), new Variant(855), new Variant
                                        (407), new Variant(852), new Variant(80), new Variant(39), new Variant(702),
                                new Variant(838), new Variant(125), new Variant(849), new Variant(34), new Variant
                                        (971), new Variant(112), new Variant(780));
                    }
                });
    }

    @Test
    public void test_Intersect_TwentyFiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2fe).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(798), new Variant(386), new Variant(345), new Variant(947), new
                Variant(378), new Variant(515), new Variant(709), new Variant(355), new Variant(463), new Variant
                (888), new Variant(223), new Variant(871), new Variant(434), new Variant(249), new Variant(651), new
                Variant(422), new Variant(863), new Variant(51), new Variant(934), new Variant(286), new Variant(637)
                , new Variant(284), new Variant(225))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Intersect(getMock(Range.class), getMock(Range.class), new Variant(798), new
                                Variant(386), new Variant(345), new Variant(947), new Variant(378), new Variant(515),
                                new Variant(709), new Variant(355), new Variant(463), new Variant(888), new Variant
                                        (223), new Variant(871), new Variant(434), new Variant(249), new Variant(651)
                                , new Variant(422), new Variant(863), new Variant(51), new Variant(934), new Variant
                                        (286), new Variant(637), new Variant(284), new Variant(225));
                    }
                });
    }

    @Test
    public void test_Intersect_TwentySixArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2fe).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(479), new Variant(567), new Variant(437), new Variant(580), new
                Variant(390), new Variant(139), new Variant(348), new Variant(864), new Variant(300), new Variant
                (707), new Variant(565), new Variant(357), new Variant(499), new Variant(193), new Variant(877), new
                Variant(322), new Variant(149), new Variant(824), new Variant(179), new Variant(242), new Variant
                (944), new Variant(845), new Variant(427), new Variant(499))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Intersect(getMock(Range.class), getMock(Range.class), new Variant(479), new
                                Variant(567), new Variant(437), new Variant(580), new Variant(390), new Variant(139),
                                new Variant(348), new Variant(864), new Variant(300), new Variant(707), new Variant
                                        (565), new Variant(357), new Variant(499), new Variant(193), new Variant(877)
                                , new Variant(322), new Variant(149), new Variant(824), new Variant(179), new Variant
                                        (242), new Variant(944), new Variant(845), new Variant(427), new Variant(499));
                    }
                });
    }

    @Test
    public void test_Intersect_TwentySevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2fe).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(298), new Variant(804), new Variant(9), new Variant(883), new
                Variant(213), new Variant(327), new Variant(926), new Variant(715), new Variant(6), new Variant(394),
                new Variant(841), new Variant(189), new Variant(992), new Variant(793), new Variant(357), new Variant
                        (122), new Variant(377), new Variant(642), new Variant(595), new Variant(668), new Variant
                        (933), new Variant(176), new Variant(516), new Variant(338), new Variant(871))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Intersect(getMock(Range.class), getMock(Range.class), new Variant(298), new
                                Variant(804), new Variant(9), new Variant(883), new Variant(213), new Variant(327),
                                new Variant(926), new Variant(715), new Variant(6), new Variant(394), new Variant
                                        (841), new Variant(189), new Variant(992), new Variant(793), new Variant(357)
                                , new Variant(122), new Variant(377), new Variant(642), new Variant(595), new Variant
                                        (668), new Variant(933), new Variant(176), new Variant(516), new Variant(338)
                                , new Variant(871));
                    }
                });
    }

    @Test
    public void test_Intersect_TwentyEightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2fe).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(876), new Variant(301), new Variant(346), new Variant(409), new
                Variant(736), new Variant(416), new Variant(592), new Variant(299), new Variant(566), new Variant
                (459), new Variant(365), new Variant(64), new Variant(186), new Variant(503), new Variant(547), new
                Variant(849), new Variant(609), new Variant(734), new Variant(589), new Variant(564), new Variant
                (465), new Variant(378), new Variant(931), new Variant(61), new Variant(383), new Variant(750))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Intersect(getMock(Range.class), getMock(Range.class), new Variant(876), new
                                Variant(301), new Variant(346), new Variant(409), new Variant(736), new Variant(416),
                                new Variant(592), new Variant(299), new Variant(566), new Variant(459), new Variant
                                        (365), new Variant(64), new Variant(186), new Variant(503), new Variant(547),
                                new Variant(849), new Variant(609), new Variant(734), new Variant(589), new Variant
                                        (564), new Variant(465), new Variant(378), new Variant(931), new Variant(61),
                                new Variant(383), new Variant(750));
                    }
                });
    }

    @Test
    public void test_Intersect_TwentyNineArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2fe).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(914), new Variant(975), new Variant(392), new Variant(788), new
                Variant(570), new Variant(310), new Variant(815), new Variant(667), new Variant(130), new Variant
                (972), new Variant(573), new Variant(65), new Variant(222), new Variant(687), new Variant(807), new
                Variant(645), new Variant(952), new Variant(540), new Variant(401), new Variant(554), new Variant
                (933), new Variant(370), new Variant(385), new Variant(745), new Variant(854), new Variant(301), new
                Variant(310))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Intersect(getMock(Range.class), getMock(Range.class), new Variant(914), new
                                Variant(975), new Variant(392), new Variant(788), new Variant(570), new Variant(310),
                                new Variant(815), new Variant(667), new Variant(130), new Variant(972), new Variant
                                        (573), new Variant(65), new Variant(222), new Variant(687), new Variant(807),
                                new Variant(645), new Variant(952), new Variant(540), new Variant(401), new Variant
                                        (554), new Variant(933), new Variant(370), new Variant(385), new Variant(745)
                                , new Variant(854), new Variant(301), new Variant(310));
                    }
                });
    }

    @Test
    public void test_Intersect_ThirtyArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2fe).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(982), new Variant(238), new Variant(437), new Variant(414), new
                Variant(796), new Variant(140), new Variant(826), new Variant(823), new Variant(808), new Variant
                (438), new Variant(198), new Variant(517), new Variant(575), new Variant(733), new Variant(600), new
                Variant(418), new Variant(661), new Variant(336), new Variant(896), new Variant(532), new Variant(19)
                , new Variant(441), new Variant(684), new Variant(609), new Variant(284), new Variant(371), new
                        Variant(390), new Variant(5))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Intersect(getMock(Range.class), getMock(Range.class), new Variant(982), new
                                Variant(238), new Variant(437), new Variant(414), new Variant(796), new Variant(140),
                                new Variant(826), new Variant(823), new Variant(808), new Variant(438), new Variant
                                        (198), new Variant(517), new Variant(575), new Variant(733), new Variant(600)
                                , new Variant(418), new Variant(661), new Variant(336), new Variant(896), new Variant
                                        (532), new Variant(19), new Variant(441), new Variant(684), new Variant(609),
                                new Variant(284), new Variant(371), new Variant(390), new Variant(5));
                    }
                });
    }

    @Test
    public void test_getAxMenuBars_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x24d).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<MenuBars>() {
                    @Override
                    public MenuBars invoke() throws ActiveXException {
                        return component.getAxMenuBars();
                    }
                });
    }

    @Test
    public void test_getAxModules_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x246).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Modules>() {
                    @Override
                    public Modules invoke() throws ActiveXException {
                        return component.getAxModules();
                    }
                });
    }

    @Test
    public void test_getAxNames_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1ba).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Names>() {
                    @Override
                    public Names invoke() throws ActiveXException {
                        return component.getAxNames();
                    }
                });
    }

    @Test
    public void test_getAxRange_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xc5).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(444))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.getAxRange(new Variant(444));
                    }
                });
    }

    @Test
    public void test_getAxRange_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0xc5).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(909), new Variant(655))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.getAxRange(new Variant(909), new Variant(655));
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
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(188))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(188));
                    }
                });
    }

    @Test
    public void test_Run_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(662), new Variant(112))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(662), new Variant(112));
                    }
                });
    }

    @Test
    public void test_Run_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(293), new Variant(219), new
                Variant(184))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(293), new Variant(219), new Variant(184));
                    }
                });
    }

    @Test
    public void test_Run_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(932), new Variant(68), new Variant
                (96), new Variant(21))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(932), new Variant(68), new Variant(96), new Variant(21));
                    }
                });
    }

    @Test
    public void test_Run_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(465), new Variant(947), new
                Variant(922), new Variant(791), new Variant(313))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(465), new Variant(947), new Variant(922), new Variant(791),
                                new Variant(313));
                    }
                });
    }

    @Test
    public void test_Run_SixArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(534), new Variant(546), new
                Variant(366), new Variant(971), new Variant(860), new Variant(665))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(534), new Variant(546), new Variant(366), new Variant(971),
                                new Variant(860), new Variant(665));
                    }
                });
    }

    @Test
    public void test_Run_SevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(890), new Variant(306), new
                Variant(884), new Variant(36), new Variant(57), new Variant(324), new Variant(281))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(890), new Variant(306), new Variant(884), new Variant(36),
                                new Variant(57), new Variant(324), new Variant(281));
                    }
                });
    }

    @Test
    public void test_Run_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(131), new Variant(189), new
                Variant(854), new Variant(879), new Variant(999), new Variant(37), new Variant(141), new Variant(72))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(131), new Variant(189), new Variant(854), new Variant(879),
                                new Variant(999), new Variant(37), new Variant(141), new Variant(72));
                    }
                });
    }

    @Test
    public void test_Run_NineArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(985), new Variant(598), new
                Variant(583), new Variant(648), new Variant(71), new Variant(270), new Variant(584), new Variant(257)
                , new Variant(41))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(985), new Variant(598), new Variant(583), new Variant(648),
                                new Variant(71), new Variant(270), new Variant(584), new Variant(257), new Variant(41));
                    }
                });
    }

    @Test
    public void test_Run_TenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(909), new Variant(89), new Variant
                (236), new Variant(138), new Variant(825), new Variant(594), new Variant(333), new Variant(338), new
                Variant(324), new Variant(432))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(909), new Variant(89), new Variant(236), new Variant(138),
                                new Variant(825), new Variant(594), new Variant(333), new Variant(338), new Variant
                                        (324), new Variant(432));
                    }
                });
    }

    @Test
    public void test_Run_ElevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(249), new Variant(504), new
                Variant(452), new Variant(602), new Variant(55), new Variant(245), new Variant(367), new Variant(445)
                , new Variant(856), new Variant(700), new Variant(888))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(249), new Variant(504), new Variant(452), new Variant(602),
                                new Variant(55), new Variant(245), new Variant(367), new Variant(445), new Variant
                                        (856), new Variant(700), new Variant(888));
                    }
                });
    }

    @Test
    public void test_Run_TwelveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(232), new Variant(396), new
                Variant(597), new Variant(738), new Variant(617), new Variant(555), new Variant(136), new Variant
                (288), new Variant(718), new Variant(852), new Variant(711), new Variant(135))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(232), new Variant(396), new Variant(597), new Variant(738),
                                new Variant(617), new Variant(555), new Variant(136), new Variant(288), new Variant
                                        (718), new Variant(852), new Variant(711), new Variant(135));
                    }
                });
    }

    @Test
    public void test_Run_ThirteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(64), new Variant(277), new Variant
                (837), new Variant(905), new Variant(946), new Variant(832), new Variant(450), new Variant(23), new
                Variant(487), new Variant(335), new Variant(656), new Variant(986), new Variant(305))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(64), new Variant(277), new Variant(837), new Variant(905),
                                new Variant(946), new Variant(832), new Variant(450), new Variant(23), new Variant
                                        (487), new Variant(335), new Variant(656), new Variant(986), new Variant(305));
                    }
                });
    }

    @Test
    public void test_Run_FourteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(44), new Variant(520), new Variant
                (670), new Variant(606), new Variant(287), new Variant(581), new Variant(75), new Variant(301), new
                Variant(804), new Variant(795), new Variant(209), new Variant(695), new Variant(120), new Variant(352))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(44), new Variant(520), new Variant(670), new Variant(606),
                                new Variant(287), new Variant(581), new Variant(75), new Variant(301), new Variant
                                        (804), new Variant(795), new Variant(209), new Variant(695), new Variant(120)
                                , new Variant(352));
                    }
                });
    }

    @Test
    public void test_Run_FifteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(983), new Variant(288), new
                Variant(496), new Variant(152), new Variant(88), new Variant(28), new Variant(78), new Variant(95),
                new Variant(483), new Variant(198), new Variant(465), new Variant(71), new Variant(926), new Variant
                        (220), new Variant(824))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(983), new Variant(288), new Variant(496), new Variant(152),
                                new Variant(88), new Variant(28), new Variant(78), new Variant(95), new Variant(483),
                                new Variant(198), new Variant(465), new Variant(71), new Variant(926), new Variant
                                        (220), new Variant(824));
                    }
                });
    }

    @Test
    public void test_Run_SixteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(585), new Variant(839), new
                Variant(647), new Variant(756), new Variant(696), new Variant(958), new Variant(390), new Variant
                (439), new Variant(177), new Variant(281), new Variant(545), new Variant(604), new Variant(510), new
                Variant(293), new Variant(475), new Variant(819))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(585), new Variant(839), new Variant(647), new Variant(756),
                                new Variant(696), new Variant(958), new Variant(390), new Variant(439), new Variant
                                        (177), new Variant(281), new Variant(545), new Variant(604), new Variant(510)
                                , new Variant(293), new Variant(475), new Variant(819));
                    }
                });
    }

    @Test
    public void test_Run_SeventeenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(898), new Variant(15), new Variant
                (345), new Variant(617), new Variant(496), new Variant(765), new Variant(336), new Variant(730), new
                Variant(908), new Variant(19), new Variant(147), new Variant(189), new Variant(386), new Variant(365)
                , new Variant(49), new Variant(563), new Variant(445))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(898), new Variant(15), new Variant(345), new Variant(617),
                                new Variant(496), new Variant(765), new Variant(336), new Variant(730), new Variant
                                        (908), new Variant(19), new Variant(147), new Variant(189), new Variant(386),
                                new Variant(365), new Variant(49), new Variant(563), new Variant(445));
                    }
                });
    }

    @Test
    public void test_Run_EighteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(614), new Variant(853), new
                Variant(842), new Variant(728), new Variant(723), new Variant(911), new Variant(492), new Variant
                (481), new Variant(703), new Variant(880), new Variant(223), new Variant(132), new Variant(188), new
                Variant(971), new Variant(889), new Variant(75), new Variant(947), new Variant(870))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(614), new Variant(853), new Variant(842), new Variant(728),
                                new Variant(723), new Variant(911), new Variant(492), new Variant(481), new Variant
                                        (703), new Variant(880), new Variant(223), new Variant(132), new Variant(188)
                                , new Variant(971), new Variant(889), new Variant(75), new Variant(947), new Variant
                                        (870));
                    }
                });
    }

    @Test
    public void test_Run_NineteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(138), new Variant(602), new
                Variant(728), new Variant(400), new Variant(254), new Variant(280), new Variant(693), new Variant
                (188), new Variant(957), new Variant(570), new Variant(784), new Variant(820), new Variant(17), new
                Variant(466), new Variant(756), new Variant(313), new Variant(76), new Variant(270), new Variant(978))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(138), new Variant(602), new Variant(728), new Variant(400),
                                new Variant(254), new Variant(280), new Variant(693), new Variant(188), new Variant
                                        (957), new Variant(570), new Variant(784), new Variant(820), new Variant(17),
                                new Variant(466), new Variant(756), new Variant(313), new Variant(76), new Variant
                                        (270), new Variant(978));
                    }
                });
    }

    @Test
    public void test_Run_TwentyArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(734), new Variant(691), new
                Variant(211), new Variant(745), new Variant(93), new Variant(330), new Variant(943), new Variant(473)
                , new Variant(745), new Variant(605), new Variant(661), new Variant(800), new Variant(403), new
                        Variant(401), new Variant(251), new Variant(30), new Variant(592), new Variant(869), new
                        Variant(616), new Variant(996))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(734), new Variant(691), new Variant(211), new Variant(745),
                                new Variant(93), new Variant(330), new Variant(943), new Variant(473), new Variant
                                        (745), new Variant(605), new Variant(661), new Variant(800), new Variant(403)
                                , new Variant(401), new Variant(251), new Variant(30), new Variant(592), new Variant
                                        (869), new Variant(616), new Variant(996));
                    }
                });
    }

    @Test
    public void test_Run_TwentyOneArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(270), new Variant(192), new
                Variant(250), new Variant(708), new Variant(71), new Variant(264), new Variant(892), new Variant(980)
                , new Variant(559), new Variant(492), new Variant(340), new Variant(797), new Variant(48), new
                        Variant(607), new Variant(914), new Variant(123), new Variant(461), new Variant(682), new
                        Variant(732), new Variant(632), new Variant(307))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(270), new Variant(192), new Variant(250), new Variant(708),
                                new Variant(71), new Variant(264), new Variant(892), new Variant(980), new Variant
                                        (559), new Variant(492), new Variant(340), new Variant(797), new Variant(48),
                                new Variant(607), new Variant(914), new Variant(123), new Variant(461), new Variant
                                        (682), new Variant(732), new Variant(632), new Variant(307));
                    }
                });
    }

    @Test
    public void test_Run_TwentyTwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(268), new Variant(70), new Variant
                (177), new Variant(890), new Variant(696), new Variant(271), new Variant(660), new Variant(571), new
                Variant(939), new Variant(527), new Variant(460), new Variant(517), new Variant(841), new Variant
                (117), new Variant(35), new Variant(248), new Variant(644), new Variant(373), new Variant(324), new
                Variant(322), new Variant(951), new Variant(999))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(268), new Variant(70), new Variant(177), new Variant(890),
                                new Variant(696), new Variant(271), new Variant(660), new Variant(571), new Variant
                                        (939), new Variant(527), new Variant(460), new Variant(517), new Variant(841)
                                , new Variant(117), new Variant(35), new Variant(248), new Variant(644), new Variant
                                        (373), new Variant(324), new Variant(322), new Variant(951), new Variant(999));
                    }
                });
    }

    @Test
    public void test_Run_TwentyThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(698), new Variant(823), new
                Variant(341), new Variant(522), new Variant(568), new Variant(539), new Variant(737), new Variant
                (982), new Variant(517), new Variant(403), new Variant(793), new Variant(914), new Variant(795), new
                Variant(170), new Variant(836), new Variant(394), new Variant(13), new Variant(551), new Variant(357)
                , new Variant(770), new Variant(955), new Variant(756), new Variant(516))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(698), new Variant(823), new Variant(341), new Variant(522),
                                new Variant(568), new Variant(539), new Variant(737), new Variant(982), new Variant
                                        (517), new Variant(403), new Variant(793), new Variant(914), new Variant(795)
                                , new Variant(170), new Variant(836), new Variant(394), new Variant(13), new Variant
                                        (551), new Variant(357), new Variant(770), new Variant(955), new Variant(756)
                                , new Variant(516));
                    }
                });
    }

    @Test
    public void test_Run_TwentyFourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(512), new Variant(419), new
                Variant(889), new Variant(287), new Variant(947), new Variant(22), new Variant(599), new Variant(50),
                new Variant(266), new Variant(500), new Variant(361), new Variant(240), new Variant(408), new Variant
                        (700), new Variant(420), new Variant(132), new Variant(883), new Variant(860), new Variant
                        (455), new Variant(585), new Variant(11), new Variant(122), new Variant(605), new Variant(746))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(512), new Variant(419), new Variant(889), new Variant(287),
                                new Variant(947), new Variant(22), new Variant(599), new Variant(50), new Variant
                                        (266), new Variant(500), new Variant(361), new Variant(240), new Variant(408)
                                , new Variant(700), new Variant(420), new Variant(132), new Variant(883), new Variant
                                        (860), new Variant(455), new Variant(585), new Variant(11), new Variant(122),
                                new Variant(605), new Variant(746));
                    }
                });
    }

    @Test
    public void test_Run_TwentyFiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(696), new Variant(709), new
                Variant(927), new Variant(583), new Variant(932), new Variant(371), new Variant(847), new Variant
                (412), new Variant(903), new Variant(727), new Variant(408), new Variant(784), new Variant(457), new
                Variant(766), new Variant(81), new Variant(263), new Variant(171), new Variant(839), new Variant(40),
                new Variant(20), new Variant(230), new Variant(37), new Variant(403), new Variant(199), new Variant
                        (973))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(696), new Variant(709), new Variant(927), new Variant(583),
                                new Variant(932), new Variant(371), new Variant(847), new Variant(412), new Variant
                                        (903), new Variant(727), new Variant(408), new Variant(784), new Variant(457)
                                , new Variant(766), new Variant(81), new Variant(263), new Variant(171), new Variant
                                        (839), new Variant(40), new Variant(20), new Variant(230), new Variant(37),
                                new Variant(403), new Variant(199), new Variant(973));
                    }
                });
    }

    @Test
    public void test_Run_TwentySixArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(490), new Variant(537), new
                Variant(679), new Variant(167), new Variant(289), new Variant(767), new Variant(732), new Variant
                (468), new Variant(96), new Variant(143), new Variant(419), new Variant(193), new Variant(273), new
                Variant(915), new Variant(823), new Variant(510), new Variant(347), new Variant(791), new Variant
                (136), new Variant(860), new Variant(681), new Variant(429), new Variant(683), new Variant(156), new
                Variant(407), new Variant(882))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(490), new Variant(537), new Variant(679), new Variant(167),
                                new Variant(289), new Variant(767), new Variant(732), new Variant(468), new Variant
                                        (96), new Variant(143), new Variant(419), new Variant(193), new Variant(273),
                                new Variant(915), new Variant(823), new Variant(510), new Variant(347), new Variant
                                        (791), new Variant(136), new Variant(860), new Variant(681), new Variant(429)
                                , new Variant(683), new Variant(156), new Variant(407), new Variant(882));
                    }
                });
    }

    @Test
    public void test_Run_TwentySevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(238), new Variant(531), new
                Variant(277), new Variant(133), new Variant(174), new Variant(849), new Variant(18), new Variant(151)
                , new Variant(447), new Variant(385), new Variant(709), new Variant(869), new Variant(319), new
                        Variant(267), new Variant(842), new Variant(979), new Variant(223), new Variant(725), new
                        Variant(120), new Variant(844), new Variant(207), new Variant(600), new Variant(707), new
                        Variant(948), new Variant(677), new Variant(327), new Variant(675))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(238), new Variant(531), new Variant(277), new Variant(133),
                                new Variant(174), new Variant(849), new Variant(18), new Variant(151), new Variant
                                        (447), new Variant(385), new Variant(709), new Variant(869), new Variant(319)
                                , new Variant(267), new Variant(842), new Variant(979), new Variant(223), new Variant
                                        (725), new Variant(120), new Variant(844), new Variant(207), new Variant(600)
                                , new Variant(707), new Variant(948), new Variant(677), new Variant(327), new Variant
                                        (675));
                    }
                });
    }

    @Test
    public void test_Run_TwentyEightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(430), new Variant(986), new
                Variant(378), new Variant(896), new Variant(537), new Variant(865), new Variant(280), new Variant
                (672), new Variant(965), new Variant(101), new Variant(155), new Variant(215), new Variant(412), new
                Variant(518), new Variant(797), new Variant(906), new Variant(403), new Variant(335), new Variant
                (801), new Variant(936), new Variant(719), new Variant(15), new Variant(572), new Variant(693), new
                Variant(861), new Variant(377), new Variant(283), new Variant(452))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(430), new Variant(986), new Variant(378), new Variant(896),
                                new Variant(537), new Variant(865), new Variant(280), new Variant(672), new Variant
                                        (965), new Variant(101), new Variant(155), new Variant(215), new Variant(412)
                                , new Variant(518), new Variant(797), new Variant(906), new Variant(403), new Variant
                                        (335), new Variant(801), new Variant(936), new Variant(719), new Variant(15),
                                new Variant(572), new Variant(693), new Variant(861), new Variant(377), new Variant
                                        (283), new Variant(452));
                    }
                });
    }

    @Test
    public void test_Run_TwentyNineArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(626), new Variant(979), new
                Variant(46), new Variant(864), new Variant(57), new Variant(752), new Variant(841), new Variant(375),
                new Variant(627), new Variant(922), new Variant(419), new Variant(972), new Variant(280), new Variant
                        (479), new Variant(447), new Variant(287), new Variant(395), new Variant(679), new Variant
                        (88), new Variant(51), new Variant(12), new Variant(744), new Variant(642), new Variant(180),
                new Variant(743), new Variant(21), new Variant(819), new Variant(316), new Variant(498))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(626), new Variant(979), new Variant(46), new Variant(864),
                                new Variant(57), new Variant(752), new Variant(841), new Variant(375), new Variant
                                        (627), new Variant(922), new Variant(419), new Variant(972), new Variant(280)
                                , new Variant(479), new Variant(447), new Variant(287), new Variant(395), new Variant
                                        (679), new Variant(88), new Variant(51), new Variant(12), new Variant(744),
                                new Variant(642), new Variant(180), new Variant(743), new Variant(21), new Variant
                                        (819), new Variant(316), new Variant(498));
                    }
                });
    }

    @Test
    public void test_Run_ThirtyArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(834), new Variant(193), new
                Variant(480), new Variant(620), new Variant(604), new Variant(189), new Variant(427), new Variant
                (185), new Variant(905), new Variant(532), new Variant(199), new Variant(450), new Variant(860), new
                Variant(591), new Variant(611), new Variant(785), new Variant(370), new Variant(936), new Variant
                (829), new Variant(370), new Variant(390), new Variant(981), new Variant(421), new Variant(573), new
                Variant(973), new Variant(369), new Variant(860), new Variant(943), new Variant(832), new Variant(997))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(834), new Variant(193), new Variant(480), new Variant(620),
                                new Variant(604), new Variant(189), new Variant(427), new Variant(185), new Variant
                                        (905), new Variant(532), new Variant(199), new Variant(450), new Variant(860)
                                , new Variant(591), new Variant(611), new Variant(785), new Variant(370), new Variant
                                        (936), new Variant(829), new Variant(370), new Variant(390), new Variant(981)
                                , new Variant(421), new Variant(573), new Variant(973), new Variant(369), new Variant
                                        (860), new Variant(943), new Variant(832), new Variant(997));
                    }
                });
    }

    @Test
    public void test_Run_ThirtyOneArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(408), new Variant(289), new
                Variant(804), new Variant(454), new Variant(885), new Variant(616), new Variant(919), new Variant
                (800), new Variant(481), new Variant(323), new Variant(560), new Variant(457), new Variant(580), new
                Variant(508), new Variant(707), new Variant(736), new Variant(905), new Variant(117), new Variant
                (721), new Variant(995), new Variant(966), new Variant(348), new Variant(648), new Variant(872), new
                Variant(316), new Variant(25), new Variant(212), new Variant(707), new Variant(971), new Variant(676)
                , new Variant(513))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(408), new Variant(289), new Variant(804), new Variant(454),
                                new Variant(885), new Variant(616), new Variant(919), new Variant(800), new Variant
                                        (481), new Variant(323), new Variant(560), new Variant(457), new Variant(580)
                                , new Variant(508), new Variant(707), new Variant(736), new Variant(905), new Variant
                                        (117), new Variant(721), new Variant(995), new Variant(966), new Variant(348)
                                , new Variant(648), new Variant(872), new Variant(316), new Variant(25), new Variant
                                        (212), new Variant(707), new Variant(971), new Variant(676), new Variant(513));
                    }
                });
    }

    @Test
    public void test__Run2_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x326).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._Run2();
                    }
                });
    }

    @Test
    public void test__Run2_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x326).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(911))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._Run2(new Variant(911));
                    }
                });
    }

    @Test
    public void test__Run2_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x326).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(598), new Variant(779))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._Run2(new Variant(598), new Variant(779));
                    }
                });
    }

    @Test
    public void test__Run2_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x326).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(12), new Variant(184), new Variant
                (270))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._Run2(new Variant(12), new Variant(184), new Variant(270));
                    }
                });
    }

    @Test
    public void test__Run2_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x326).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(905), new Variant(493), new
                Variant(204), new Variant(325))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._Run2(new Variant(905), new Variant(493), new Variant(204), new Variant(325));
                    }
                });
    }

    @Test
    public void test__Run2_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x326).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(707), new Variant(643), new
                Variant(442), new Variant(170), new Variant(395))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._Run2(new Variant(707), new Variant(643), new Variant(442), new Variant(170)
                                , new Variant(395));
                    }
                });
    }

    @Test
    public void test__Run2_SixArgs_ShouldRedirectToProxy() throws Exception {
        on(0x326).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(852), new Variant(10), new Variant
                (716), new Variant(671), new Variant(855), new Variant(356))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._Run2(new Variant(852), new Variant(10), new Variant(716), new Variant(671),
                                new Variant(855), new Variant(356));
                    }
                });
    }

    @Test
    public void test__Run2_SevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x326).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(132), new Variant(485), new
                Variant(217), new Variant(413), new Variant(731), new Variant(189), new Variant(736))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._Run2(new Variant(132), new Variant(485), new Variant(217), new Variant(413)
                                , new Variant(731), new Variant(189), new Variant(736));
                    }
                });
    }

    @Test
    public void test__Run2_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x326).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(573), new Variant(13), new Variant
                (72), new Variant(990), new Variant(571), new Variant(457), new Variant(694), new Variant(166))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._Run2(new Variant(573), new Variant(13), new Variant(72), new Variant(990),
                                new Variant(571), new Variant(457), new Variant(694), new Variant(166));
                    }
                });
    }

    @Test
    public void test__Run2_NineArgs_ShouldRedirectToProxy() throws Exception {
        on(0x326).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(841), new Variant(391), new
                Variant(795), new Variant(644), new Variant(108), new Variant(469), new Variant(699), new Variant
                (964), new Variant(772))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._Run2(new Variant(841), new Variant(391), new Variant(795), new Variant(644)
                                , new Variant(108), new Variant(469), new Variant(699), new Variant(964), new Variant
                                        (772));
                    }
                });
    }

    @Test
    public void test__Run2_TenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x326).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(357), new Variant(749), new
                Variant(403), new Variant(82), new Variant(942), new Variant(604), new Variant(57), new Variant(71),
                new Variant(909), new Variant(488))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._Run2(new Variant(357), new Variant(749), new Variant(403), new Variant(82),
                                new Variant(942), new Variant(604), new Variant(57), new Variant(71), new Variant
                                        (909), new Variant(488));
                    }
                });
    }

    @Test
    public void test__Run2_ElevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x326).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(323), new Variant(465), new
                Variant(199), new Variant(852), new Variant(556), new Variant(576), new Variant(718), new Variant
                (760), new Variant(963), new Variant(791), new Variant(207))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._Run2(new Variant(323), new Variant(465), new Variant(199), new Variant(852)
                                , new Variant(556), new Variant(576), new Variant(718), new Variant(760), new Variant
                                        (963), new Variant(791), new Variant(207));
                    }
                });
    }

    @Test
    public void test__Run2_TwelveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x326).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(654), new Variant(693), new
                Variant(198), new Variant(756), new Variant(898), new Variant(144), new Variant(157), new Variant
                (730), new Variant(618), new Variant(257), new Variant(187), new Variant(393))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._Run2(new Variant(654), new Variant(693), new Variant(198), new Variant(756)
                                , new Variant(898), new Variant(144), new Variant(157), new Variant(730), new Variant
                                        (618), new Variant(257), new Variant(187), new Variant(393));
                    }
                });
    }

    @Test
    public void test__Run2_ThirteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x326).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(213), new Variant(74), new Variant
                (939), new Variant(547), new Variant(80), new Variant(388), new Variant(0), new Variant(555), new
                Variant(115), new Variant(444), new Variant(423), new Variant(492), new Variant(731))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._Run2(new Variant(213), new Variant(74), new Variant(939), new Variant(547),
                                new Variant(80), new Variant(388), new Variant(0), new Variant(555), new Variant(115)
                                , new Variant(444), new Variant(423), new Variant(492), new Variant(731));
                    }
                });
    }

    @Test
    public void test__Run2_FourteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x326).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(693), new Variant(683), new
                Variant(635), new Variant(368), new Variant(211), new Variant(535), new Variant(282), new Variant
                (742), new Variant(199), new Variant(619), new Variant(321), new Variant(697), new Variant(708), new
                Variant(713))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._Run2(new Variant(693), new Variant(683), new Variant(635), new Variant(368)
                                , new Variant(211), new Variant(535), new Variant(282), new Variant(742), new Variant
                                        (199), new Variant(619), new Variant(321), new Variant(697), new Variant(708)
                                , new Variant(713));
                    }
                });
    }

    @Test
    public void test__Run2_FifteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x326).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(11), new Variant(690), new Variant
                (540), new Variant(186), new Variant(659), new Variant(623), new Variant(415), new Variant(74), new
                Variant(825), new Variant(614), new Variant(650), new Variant(578), new Variant(428), new Variant(97)
                , new Variant(888))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._Run2(new Variant(11), new Variant(690), new Variant(540), new Variant(186),
                                new Variant(659), new Variant(623), new Variant(415), new Variant(74), new Variant
                                        (825), new Variant(614), new Variant(650), new Variant(578), new Variant(428)
                                , new Variant(97), new Variant(888));
                    }
                });
    }

    @Test
    public void test__Run2_SixteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x326).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(140), new Variant(733), new
                Variant(757), new Variant(584), new Variant(376), new Variant(630), new Variant(788), new Variant
                (442), new Variant(981), new Variant(574), new Variant(747), new Variant(815), new Variant(956), new
                Variant(963), new Variant(110), new Variant(900))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._Run2(new Variant(140), new Variant(733), new Variant(757), new Variant(584)
                                , new Variant(376), new Variant(630), new Variant(788), new Variant(442), new Variant
                                        (981), new Variant(574), new Variant(747), new Variant(815), new Variant(956)
                                , new Variant(963), new Variant(110), new Variant(900));
                    }
                });
    }

    @Test
    public void test__Run2_SeventeenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x326).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(334), new Variant(138), new
                Variant(904), new Variant(330), new Variant(630), new Variant(517), new Variant(694), new Variant
                (742), new Variant(401), new Variant(129), new Variant(259), new Variant(464), new Variant(762), new
                Variant(155), new Variant(846), new Variant(242), new Variant(106))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._Run2(new Variant(334), new Variant(138), new Variant(904), new Variant(330)
                                , new Variant(630), new Variant(517), new Variant(694), new Variant(742), new Variant
                                        (401), new Variant(129), new Variant(259), new Variant(464), new Variant(762)
                                , new Variant(155), new Variant(846), new Variant(242), new Variant(106));
                    }
                });
    }

    @Test
    public void test__Run2_EighteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x326).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(671), new Variant(127), new
                Variant(703), new Variant(332), new Variant(973), new Variant(561), new Variant(933), new Variant
                (999), new Variant(945), new Variant(432), new Variant(568), new Variant(405), new Variant(748), new
                Variant(916), new Variant(757), new Variant(752), new Variant(788), new Variant(807))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._Run2(new Variant(671), new Variant(127), new Variant(703), new Variant(332)
                                , new Variant(973), new Variant(561), new Variant(933), new Variant(999), new Variant
                                        (945), new Variant(432), new Variant(568), new Variant(405), new Variant(748)
                                , new Variant(916), new Variant(757), new Variant(752), new Variant(788), new Variant
                                        (807));
                    }
                });
    }

    @Test
    public void test__Run2_NineteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x326).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(775), new Variant(531), new
                Variant(421), new Variant(40), new Variant(522), new Variant(574), new Variant(98), new Variant(178),
                new Variant(266), new Variant(732), new Variant(157), new Variant(422), new Variant(622), new Variant
                        (415), new Variant(822), new Variant(844), new Variant(975), new Variant(603), new Variant(35))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._Run2(new Variant(775), new Variant(531), new Variant(421), new Variant(40),
                                new Variant(522), new Variant(574), new Variant(98), new Variant(178), new Variant
                                        (266), new Variant(732), new Variant(157), new Variant(422), new Variant(622)
                                , new Variant(415), new Variant(822), new Variant(844), new Variant(975), new Variant
                                        (603), new Variant(35));
                    }
                });
    }

    @Test
    public void test__Run2_TwentyArgs_ShouldRedirectToProxy() throws Exception {
        on(0x326).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(569), new Variant(711), new
                Variant(272), new Variant(180), new Variant(538), new Variant(648), new Variant(217), new Variant
                (466), new Variant(183), new Variant(698), new Variant(617), new Variant(484), new Variant(155), new
                Variant(448), new Variant(381), new Variant(142), new Variant(336), new Variant(287), new Variant
                (901), new Variant(502))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._Run2(new Variant(569), new Variant(711), new Variant(272), new Variant(180)
                                , new Variant(538), new Variant(648), new Variant(217), new Variant(466), new Variant
                                        (183), new Variant(698), new Variant(617), new Variant(484), new Variant(155)
                                , new Variant(448), new Variant(381), new Variant(142), new Variant(336), new Variant
                                        (287), new Variant(901), new Variant(502));
                    }
                });
    }

    @Test
    public void test__Run2_TwentyOneArgs_ShouldRedirectToProxy() throws Exception {
        on(0x326).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(767), new Variant(412), new
                Variant(700), new Variant(52), new Variant(573), new Variant(305), new Variant(318), new Variant(957)
                , new Variant(969), new Variant(748), new Variant(193), new Variant(36), new Variant(81), new Variant
                        (476), new Variant(244), new Variant(214), new Variant(813), new Variant(33), new Variant
                        (893), new Variant(768), new Variant(619))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._Run2(new Variant(767), new Variant(412), new Variant(700), new Variant(52),
                                new Variant(573), new Variant(305), new Variant(318), new Variant(957), new Variant
                                        (969), new Variant(748), new Variant(193), new Variant(36), new Variant(81),
                                new Variant(476), new Variant(244), new Variant(214), new Variant(813), new Variant
                                        (33), new Variant(893), new Variant(768), new Variant(619));
                    }
                });
    }

    @Test
    public void test__Run2_TwentyTwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x326).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(695), new Variant(111), new
                Variant(615), new Variant(793), new Variant(6), new Variant(192), new Variant(252), new Variant(466),
                new Variant(954), new Variant(600), new Variant(474), new Variant(111), new Variant(322), new Variant
                        (957), new Variant(173), new Variant(743), new Variant(638), new Variant(44), new Variant
                        (281), new Variant(193), new Variant(554), new Variant(610))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._Run2(new Variant(695), new Variant(111), new Variant(615), new Variant(793)
                                , new Variant(6), new Variant(192), new Variant(252), new Variant(466), new Variant
                                        (954), new Variant(600), new Variant(474), new Variant(111), new Variant(322)
                                , new Variant(957), new Variant(173), new Variant(743), new Variant(638), new Variant
                                        (44), new Variant(281), new Variant(193), new Variant(554), new Variant(610));
                    }
                });
    }

    @Test
    public void test__Run2_TwentyThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x326).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(948), new Variant(214), new
                Variant(769), new Variant(72), new Variant(209), new Variant(364), new Variant(80), new Variant(117),
                new Variant(810), new Variant(860), new Variant(673), new Variant(533), new Variant(937), new Variant
                        (381), new Variant(168), new Variant(959), new Variant(787), new Variant(762), new Variant
                        (894), new Variant(317), new Variant(74), new Variant(150), new Variant(79))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._Run2(new Variant(948), new Variant(214), new Variant(769), new Variant(72),
                                new Variant(209), new Variant(364), new Variant(80), new Variant(117), new Variant
                                        (810), new Variant(860), new Variant(673), new Variant(533), new Variant(937)
                                , new Variant(381), new Variant(168), new Variant(959), new Variant(787), new Variant
                                        (762), new Variant(894), new Variant(317), new Variant(74), new Variant(150),
                                new Variant(79));
                    }
                });
    }

    @Test
    public void test__Run2_TwentyFourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x326).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(28), new Variant(781), new Variant
                (856), new Variant(986), new Variant(395), new Variant(134), new Variant(457), new Variant(733), new
                Variant(49), new Variant(144), new Variant(106), new Variant(522), new Variant(279), new Variant(610)
                , new Variant(267), new Variant(65), new Variant(116), new Variant(28), new Variant(686), new Variant
                        (275), new Variant(183), new Variant(630), new Variant(186), new Variant(489))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._Run2(new Variant(28), new Variant(781), new Variant(856), new Variant(986),
                                new Variant(395), new Variant(134), new Variant(457), new Variant(733), new Variant
                                        (49), new Variant(144), new Variant(106), new Variant(522), new Variant(279),
                                new Variant(610), new Variant(267), new Variant(65), new Variant(116), new Variant
                                        (28), new Variant(686), new Variant(275), new Variant(183), new Variant(630),
                                new Variant(186), new Variant(489));
                    }
                });
    }

    @Test
    public void test__Run2_TwentyFiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x326).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(135), new Variant(216), new
                Variant(684), new Variant(879), new Variant(79), new Variant(873), new Variant(255), new Variant(961)
                , new Variant(933), new Variant(399), new Variant(420), new Variant(528), new Variant(537), new
                        Variant(847), new Variant(557), new Variant(600), new Variant(19), new Variant(554), new
                        Variant(747), new Variant(561), new Variant(533), new Variant(877), new Variant(567), new
                        Variant(32), new Variant(584))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._Run2(new Variant(135), new Variant(216), new Variant(684), new Variant(879)
                                , new Variant(79), new Variant(873), new Variant(255), new Variant(961), new Variant
                                        (933), new Variant(399), new Variant(420), new Variant(528), new Variant(537)
                                , new Variant(847), new Variant(557), new Variant(600), new Variant(19), new Variant
                                        (554), new Variant(747), new Variant(561), new Variant(533), new Variant(877)
                                , new Variant(567), new Variant(32), new Variant(584));
                    }
                });
    }

    @Test
    public void test__Run2_TwentySixArgs_ShouldRedirectToProxy() throws Exception {
        on(0x326).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(835), new Variant(877), new
                Variant(218), new Variant(634), new Variant(897), new Variant(189), new Variant(269), new Variant
                (988), new Variant(69), new Variant(188), new Variant(554), new Variant(938), new Variant(884), new
                Variant(687), new Variant(474), new Variant(980), new Variant(431), new Variant(239), new Variant
                (516), new Variant(858), new Variant(369), new Variant(960), new Variant(129), new Variant(484), new
                Variant(984), new Variant(803))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._Run2(new Variant(835), new Variant(877), new Variant(218), new Variant(634)
                                , new Variant(897), new Variant(189), new Variant(269), new Variant(988), new Variant
                                        (69), new Variant(188), new Variant(554), new Variant(938), new Variant(884),
                                new Variant(687), new Variant(474), new Variant(980), new Variant(431), new Variant
                                        (239), new Variant(516), new Variant(858), new Variant(369), new Variant(960)
                                , new Variant(129), new Variant(484), new Variant(984), new Variant(803));
                    }
                });
    }

    @Test
    public void test__Run2_TwentySevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x326).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(149), new Variant(15), new Variant
                (309), new Variant(644), new Variant(601), new Variant(555), new Variant(857), new Variant(997), new
                Variant(545), new Variant(345), new Variant(990), new Variant(545), new Variant(159), new Variant
                (858), new Variant(696), new Variant(830), new Variant(427), new Variant(283), new Variant(262), new
                Variant(809), new Variant(624), new Variant(429), new Variant(841), new Variant(21), new Variant(739)
                , new Variant(144), new Variant(744))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._Run2(new Variant(149), new Variant(15), new Variant(309), new Variant(644),
                                new Variant(601), new Variant(555), new Variant(857), new Variant(997), new Variant
                                        (545), new Variant(345), new Variant(990), new Variant(545), new Variant(159)
                                , new Variant(858), new Variant(696), new Variant(830), new Variant(427), new Variant
                                        (283), new Variant(262), new Variant(809), new Variant(624), new Variant(429)
                                , new Variant(841), new Variant(21), new Variant(739), new Variant(144), new Variant
                                        (744));
                    }
                });
    }

    @Test
    public void test__Run2_TwentyEightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x326).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(318), new Variant(650), new
                Variant(40), new Variant(412), new Variant(104), new Variant(703), new Variant(719), new Variant(671)
                , new Variant(381), new Variant(376), new Variant(962), new Variant(268), new Variant(115), new
                        Variant(525), new Variant(264), new Variant(795), new Variant(67), new Variant(245), new
                        Variant(949), new Variant(380), new Variant(318), new Variant(964), new Variant(477), new
                        Variant(837), new Variant(130), new Variant(741), new Variant(739), new Variant(409))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._Run2(new Variant(318), new Variant(650), new Variant(40), new Variant(412),
                                new Variant(104), new Variant(703), new Variant(719), new Variant(671), new Variant
                                        (381), new Variant(376), new Variant(962), new Variant(268), new Variant(115)
                                , new Variant(525), new Variant(264), new Variant(795), new Variant(67), new Variant
                                        (245), new Variant(949), new Variant(380), new Variant(318), new Variant(964)
                                , new Variant(477), new Variant(837), new Variant(130), new Variant(741), new Variant
                                        (739), new Variant(409));
                    }
                });
    }

    @Test
    public void test__Run2_TwentyNineArgs_ShouldRedirectToProxy() throws Exception {
        on(0x326).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(722), new Variant(608), new
                Variant(9), new Variant(63), new Variant(372), new Variant(705), new Variant(538), new Variant(860),
                new Variant(660), new Variant(789), new Variant(595), new Variant(958), new Variant(182), new Variant
                        (777), new Variant(329), new Variant(79), new Variant(393), new Variant(209), new Variant
                        (884), new Variant(594), new Variant(654), new Variant(473), new Variant(536), new Variant
                        (765), new Variant(40), new Variant(692), new Variant(708), new Variant(578), new Variant(397))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._Run2(new Variant(722), new Variant(608), new Variant(9), new Variant(63),
                                new Variant(372), new Variant(705), new Variant(538), new Variant(860), new Variant
                                        (660), new Variant(789), new Variant(595), new Variant(958), new Variant(182)
                                , new Variant(777), new Variant(329), new Variant(79), new Variant(393), new Variant
                                        (209), new Variant(884), new Variant(594), new Variant(654), new Variant(473)
                                , new Variant(536), new Variant(765), new Variant(40), new Variant(692), new Variant
                                        (708), new Variant(578), new Variant(397));
                    }
                });
    }

    @Test
    public void test__Run2_ThirtyArgs_ShouldRedirectToProxy() throws Exception {
        on(0x326).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(598), new Variant(579), new
                Variant(460), new Variant(602), new Variant(992), new Variant(328), new Variant(163), new Variant(70)
                , new Variant(336), new Variant(111), new Variant(708), new Variant(861), new Variant(714), new
                        Variant(559), new Variant(503), new Variant(12), new Variant(360), new Variant(547), new
                        Variant(990), new Variant(548), new Variant(521), new Variant(111), new Variant(272), new
                        Variant(447), new Variant(672), new Variant(784), new Variant(351), new Variant(96), new
                        Variant(980), new Variant(924))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._Run2(new Variant(598), new Variant(579), new Variant(460), new Variant(602)
                                , new Variant(992), new Variant(328), new Variant(163), new Variant(70), new Variant
                                        (336), new Variant(111), new Variant(708), new Variant(861), new Variant(714)
                                , new Variant(559), new Variant(503), new Variant(12), new Variant(360), new Variant
                                        (547), new Variant(990), new Variant(548), new Variant(521), new Variant(111)
                                , new Variant(272), new Variant(447), new Variant(672), new Variant(784), new Variant
                                        (351), new Variant(96), new Variant(980), new Variant(924));
                    }
                });
    }

    @Test
    public void test__Run2_ThirtyOneArgs_ShouldRedirectToProxy() throws Exception {
        on(0x326).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(788), new Variant(279), new
                Variant(216), new Variant(825), new Variant(700), new Variant(906), new Variant(966), new Variant
                (170), new Variant(607), new Variant(855), new Variant(348), new Variant(219), new Variant(462), new
                Variant(501), new Variant(499), new Variant(101), new Variant(574), new Variant(59), new Variant(208)
                , new Variant(317), new Variant(501), new Variant(840), new Variant(658), new Variant(359), new
                        Variant(712), new Variant(226), new Variant(455), new Variant(497), new Variant(758), new
                        Variant(306), new Variant(122))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._Run2(new Variant(788), new Variant(279), new Variant(216), new Variant(825)
                                , new Variant(700), new Variant(906), new Variant(966), new Variant(170), new Variant
                                        (607), new Variant(855), new Variant(348), new Variant(219), new Variant(462)
                                , new Variant(501), new Variant(499), new Variant(101), new Variant(574), new Variant
                                        (59), new Variant(208), new Variant(317), new Variant(501), new Variant(840),
                                new Variant(658), new Variant(359), new Variant(712), new Variant(226), new Variant
                                        (455), new Variant(497), new Variant(758), new Variant(306), new Variant(122));
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
    public void test_SendKeys_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x17f).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(978))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SendKeys(new Variant(978));
                    }
                });
    }

    @Test
    public void test_SendKeys_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x17f).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(37), new Variant(340))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SendKeys(new Variant(37), new Variant(340));
                    }
                });
    }

    @Test
    public void test_getAxSheets_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1e5).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Sheets>() {
                    @Override
                    public Sheets invoke() throws ActiveXException {
                        return component.getAxSheets();
                    }
                });
    }

    @Test
    public void test_getAxShortcutMenus_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x308).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(42))
                .verifyReturnsDispatchable(new Returns<Menu>() {
                    @Override
                    public Menu invoke() throws ActiveXException {
                        return component.getAxShortcutMenus(42);
                    }
                });
    }

    @Test
    public void test_getAxThisWorkbook_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x30a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxThisWorkbook();
                    }
                });
    }

    @Test
    public void test_getAxToolbars_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x228).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Toolbars>() {
                    @Override
                    public Toolbars invoke() throws ActiveXException {
                        return component.getAxToolbars();
                    }
                });
    }

    @Test
    public void test_Union_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x30b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Union(getMock(Range.class), getMock(Range.class));
                    }
                });
    }

    @Test
    public void test_Union_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x30b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(765))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Union(getMock(Range.class), getMock(Range.class), new Variant(765));
                    }
                });
    }

    @Test
    public void test_Union_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x30b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(673), new Variant(999))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Union(getMock(Range.class), getMock(Range.class), new Variant(673), new
                                Variant(999));
                    }
                });
    }

    @Test
    public void test_Union_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x30b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(308), new Variant(774), new Variant(681))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Union(getMock(Range.class), getMock(Range.class), new Variant(308), new
                                Variant(774), new Variant(681));
                    }
                });
    }

    @Test
    public void test_Union_SixArgs_ShouldRedirectToProxy() throws Exception {
        on(0x30b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(656), new Variant(692), new Variant(954), new Variant(634))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Union(getMock(Range.class), getMock(Range.class), new Variant(656), new
                                Variant(692), new Variant(954), new Variant(634));
                    }
                });
    }

    @Test
    public void test_Union_SevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x30b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(927), new Variant(522), new Variant(515), new Variant(483), new
                Variant(71))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Union(getMock(Range.class), getMock(Range.class), new Variant(927), new
                                Variant(522), new Variant(515), new Variant(483), new Variant(71));
                    }
                });
    }

    @Test
    public void test_Union_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x30b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(294), new Variant(167), new Variant(683), new Variant(985), new
                Variant(41), new Variant(775))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Union(getMock(Range.class), getMock(Range.class), new Variant(294), new
                                Variant(167), new Variant(683), new Variant(985), new Variant(41), new Variant(775));
                    }
                });
    }

    @Test
    public void test_Union_NineArgs_ShouldRedirectToProxy() throws Exception {
        on(0x30b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(856), new Variant(207), new Variant(698), new Variant(0), new
                Variant(127), new Variant(303), new Variant(18))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Union(getMock(Range.class), getMock(Range.class), new Variant(856), new
                                Variant(207), new Variant(698), new Variant(0), new Variant(127), new Variant(303),
                                new Variant(18));
                    }
                });
    }

    @Test
    public void test_Union_TenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x30b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(169), new Variant(505), new Variant(306), new Variant(7), new
                Variant(578), new Variant(742), new Variant(216), new Variant(341))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Union(getMock(Range.class), getMock(Range.class), new Variant(169), new
                                Variant(505), new Variant(306), new Variant(7), new Variant(578), new Variant(742),
                                new Variant(216), new Variant(341));
                    }
                });
    }

    @Test
    public void test_Union_ElevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x30b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(301), new Variant(339), new Variant(818), new Variant(960), new
                Variant(972), new Variant(687), new Variant(932), new Variant(695), new Variant(383))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Union(getMock(Range.class), getMock(Range.class), new Variant(301), new
                                Variant(339), new Variant(818), new Variant(960), new Variant(972), new Variant(687),
                                new Variant(932), new Variant(695), new Variant(383));
                    }
                });
    }

    @Test
    public void test_Union_TwelveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x30b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(52), new Variant(365), new Variant(490), new Variant(903), new
                Variant(993), new Variant(612), new Variant(812), new Variant(692), new Variant(356), new Variant(657))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Union(getMock(Range.class), getMock(Range.class), new Variant(52), new
                                Variant(365), new Variant(490), new Variant(903), new Variant(993), new Variant(612),
                                new Variant(812), new Variant(692), new Variant(356), new Variant(657));
                    }
                });
    }

    @Test
    public void test_Union_ThirteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x30b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(515), new Variant(600), new Variant(901), new Variant(581), new
                Variant(596), new Variant(166), new Variant(661), new Variant(934), new Variant(132), new Variant
                (378), new Variant(125))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Union(getMock(Range.class), getMock(Range.class), new Variant(515), new
                                Variant(600), new Variant(901), new Variant(581), new Variant(596), new Variant(166),
                                new Variant(661), new Variant(934), new Variant(132), new Variant(378), new Variant
                                        (125));
                    }
                });
    }

    @Test
    public void test_Union_FourteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x30b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(619), new Variant(178), new Variant(695), new Variant(636), new
                Variant(145), new Variant(808), new Variant(887), new Variant(144), new Variant(48), new Variant(15),
                new Variant(242), new Variant(205))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Union(getMock(Range.class), getMock(Range.class), new Variant(619), new
                                Variant(178), new Variant(695), new Variant(636), new Variant(145), new Variant(808),
                                new Variant(887), new Variant(144), new Variant(48), new Variant(15), new Variant
                                        (242), new Variant(205));
                    }
                });
    }

    @Test
    public void test_Union_FifteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x30b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(181), new Variant(242), new Variant(110), new Variant(123), new
                Variant(188), new Variant(419), new Variant(366), new Variant(193), new Variant(721), new Variant
                (474), new Variant(267), new Variant(136), new Variant(531))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Union(getMock(Range.class), getMock(Range.class), new Variant(181), new
                                Variant(242), new Variant(110), new Variant(123), new Variant(188), new Variant(419),
                                new Variant(366), new Variant(193), new Variant(721), new Variant(474), new Variant
                                        (267), new Variant(136), new Variant(531));
                    }
                });
    }

    @Test
    public void test_Union_SixteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x30b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(356), new Variant(148), new Variant(299), new Variant(230), new
                Variant(896), new Variant(731), new Variant(650), new Variant(764), new Variant(853), new Variant
                (966), new Variant(774), new Variant(112), new Variant(303), new Variant(750))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Union(getMock(Range.class), getMock(Range.class), new Variant(356), new
                                Variant(148), new Variant(299), new Variant(230), new Variant(896), new Variant(731),
                                new Variant(650), new Variant(764), new Variant(853), new Variant(966), new Variant
                                        (774), new Variant(112), new Variant(303), new Variant(750));
                    }
                });
    }

    @Test
    public void test_Union_SeventeenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x30b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(591), new Variant(574), new Variant(344), new Variant(336), new
                Variant(233), new Variant(562), new Variant(99), new Variant(14), new Variant(308), new Variant(596),
                new Variant(35), new Variant(841), new Variant(315), new Variant(820), new Variant(963))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Union(getMock(Range.class), getMock(Range.class), new Variant(591), new
                                Variant(574), new Variant(344), new Variant(336), new Variant(233), new Variant(562),
                                new Variant(99), new Variant(14), new Variant(308), new Variant(596), new Variant(35)
                                , new Variant(841), new Variant(315), new Variant(820), new Variant(963));
                    }
                });
    }

    @Test
    public void test_Union_EighteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x30b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(452), new Variant(36), new Variant(399), new Variant(887), new
                Variant(128), new Variant(942), new Variant(78), new Variant(951), new Variant(824), new Variant(385)
                , new Variant(904), new Variant(923), new Variant(40), new Variant(383), new Variant(484), new
                        Variant(986))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Union(getMock(Range.class), getMock(Range.class), new Variant(452), new
                                Variant(36), new Variant(399), new Variant(887), new Variant(128), new Variant(942),
                                new Variant(78), new Variant(951), new Variant(824), new Variant(385), new Variant
                                        (904), new Variant(923), new Variant(40), new Variant(383), new Variant(484),
                                new Variant(986));
                    }
                });
    }

    @Test
    public void test_Union_NineteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x30b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(591), new Variant(273), new Variant(221), new Variant(101), new
                Variant(214), new Variant(996), new Variant(345), new Variant(584), new Variant(308), new Variant
                (650), new Variant(560), new Variant(25), new Variant(967), new Variant(12), new Variant(30), new
                Variant(537), new Variant(129))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Union(getMock(Range.class), getMock(Range.class), new Variant(591), new
                                Variant(273), new Variant(221), new Variant(101), new Variant(214), new Variant(996),
                                new Variant(345), new Variant(584), new Variant(308), new Variant(650), new Variant
                                        (560), new Variant(25), new Variant(967), new Variant(12), new Variant(30),
                                new Variant(537), new Variant(129));
                    }
                });
    }

    @Test
    public void test_Union_TwentyArgs_ShouldRedirectToProxy() throws Exception {
        on(0x30b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(901), new Variant(284), new Variant(407), new Variant(309), new
                Variant(962), new Variant(906), new Variant(500), new Variant(540), new Variant(486), new Variant
                (745), new Variant(305), new Variant(609), new Variant(658), new Variant(464), new Variant(516), new
                Variant(261), new Variant(313), new Variant(638))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Union(getMock(Range.class), getMock(Range.class), new Variant(901), new
                                Variant(284), new Variant(407), new Variant(309), new Variant(962), new Variant(906),
                                new Variant(500), new Variant(540), new Variant(486), new Variant(745), new Variant
                                        (305), new Variant(609), new Variant(658), new Variant(464), new Variant(516)
                                , new Variant(261), new Variant(313), new Variant(638));
                    }
                });
    }

    @Test
    public void test_Union_TwentyOneArgs_ShouldRedirectToProxy() throws Exception {
        on(0x30b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(914), new Variant(999), new Variant(834), new Variant(718), new
                Variant(198), new Variant(276), new Variant(351), new Variant(852), new Variant(399), new Variant
                (255), new Variant(754), new Variant(346), new Variant(280), new Variant(741), new Variant(119), new
                Variant(423), new Variant(513), new Variant(879), new Variant(204))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Union(getMock(Range.class), getMock(Range.class), new Variant(914), new
                                Variant(999), new Variant(834), new Variant(718), new Variant(198), new Variant(276),
                                new Variant(351), new Variant(852), new Variant(399), new Variant(255), new Variant
                                        (754), new Variant(346), new Variant(280), new Variant(741), new Variant(119)
                                , new Variant(423), new Variant(513), new Variant(879), new Variant(204));
                    }
                });
    }

    @Test
    public void test_Union_TwentyTwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x30b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(709), new Variant(195), new Variant(741), new Variant(620), new
                Variant(21), new Variant(857), new Variant(12), new Variant(875), new Variant(593), new Variant(370),
                new Variant(899), new Variant(397), new Variant(950), new Variant(154), new Variant(520), new Variant
                        (768), new Variant(172), new Variant(792), new Variant(522), new Variant(615))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Union(getMock(Range.class), getMock(Range.class), new Variant(709), new
                                Variant(195), new Variant(741), new Variant(620), new Variant(21), new Variant(857),
                                new Variant(12), new Variant(875), new Variant(593), new Variant(370), new Variant
                                        (899), new Variant(397), new Variant(950), new Variant(154), new Variant(520)
                                , new Variant(768), new Variant(172), new Variant(792), new Variant(522), new Variant
                                        (615));
                    }
                });
    }

    @Test
    public void test_Union_TwentyThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x30b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(460), new Variant(731), new Variant(130), new Variant(536), new
                Variant(917), new Variant(461), new Variant(459), new Variant(749), new Variant(522), new Variant
                (130), new Variant(331), new Variant(286), new Variant(676), new Variant(393), new Variant(773), new
                Variant(400), new Variant(831), new Variant(505), new Variant(517), new Variant(207), new Variant(467))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Union(getMock(Range.class), getMock(Range.class), new Variant(460), new
                                Variant(731), new Variant(130), new Variant(536), new Variant(917), new Variant(461),
                                new Variant(459), new Variant(749), new Variant(522), new Variant(130), new Variant
                                        (331), new Variant(286), new Variant(676), new Variant(393), new Variant(773)
                                , new Variant(400), new Variant(831), new Variant(505), new Variant(517), new Variant
                                        (207), new Variant(467));
                    }
                });
    }

    @Test
    public void test_Union_TwentyFourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x30b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(983), new Variant(895), new Variant(303), new Variant(954), new
                Variant(3), new Variant(620), new Variant(584), new Variant(600), new Variant(683), new Variant(530),
                new Variant(816), new Variant(132), new Variant(767), new Variant(38), new Variant(690), new Variant
                        (402), new Variant(860), new Variant(665), new Variant(764), new Variant(827), new Variant
                        (972), new Variant(356))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Union(getMock(Range.class), getMock(Range.class), new Variant(983), new
                                Variant(895), new Variant(303), new Variant(954), new Variant(3), new Variant(620),
                                new Variant(584), new Variant(600), new Variant(683), new Variant(530), new Variant
                                        (816), new Variant(132), new Variant(767), new Variant(38), new Variant(690),
                                new Variant(402), new Variant(860), new Variant(665), new Variant(764), new Variant
                                        (827), new Variant(972), new Variant(356));
                    }
                });
    }

    @Test
    public void test_Union_TwentyFiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x30b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(638), new Variant(922), new Variant(578), new Variant(842), new
                Variant(614), new Variant(203), new Variant(787), new Variant(161), new Variant(625), new Variant
                (906), new Variant(704), new Variant(531), new Variant(308), new Variant(900), new Variant(640), new
                Variant(567), new Variant(641), new Variant(838), new Variant(787), new Variant(895), new Variant
                (444), new Variant(601), new Variant(913))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Union(getMock(Range.class), getMock(Range.class), new Variant(638), new
                                Variant(922), new Variant(578), new Variant(842), new Variant(614), new Variant(203),
                                new Variant(787), new Variant(161), new Variant(625), new Variant(906), new Variant
                                        (704), new Variant(531), new Variant(308), new Variant(900), new Variant(640)
                                , new Variant(567), new Variant(641), new Variant(838), new Variant(787), new Variant
                                        (895), new Variant(444), new Variant(601), new Variant(913));
                    }
                });
    }

    @Test
    public void test_Union_TwentySixArgs_ShouldRedirectToProxy() throws Exception {
        on(0x30b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(247), new Variant(29), new Variant(767), new Variant(800), new
                Variant(729), new Variant(768), new Variant(477), new Variant(572), new Variant(735), new Variant
                (744), new Variant(532), new Variant(313), new Variant(662), new Variant(114), new Variant(485), new
                Variant(501), new Variant(803), new Variant(925), new Variant(353), new Variant(728), new Variant
                (413), new Variant(384), new Variant(842), new Variant(797))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Union(getMock(Range.class), getMock(Range.class), new Variant(247), new
                                Variant(29), new Variant(767), new Variant(800), new Variant(729), new Variant(768),
                                new Variant(477), new Variant(572), new Variant(735), new Variant(744), new Variant
                                        (532), new Variant(313), new Variant(662), new Variant(114), new Variant(485)
                                , new Variant(501), new Variant(803), new Variant(925), new Variant(353), new Variant
                                        (728), new Variant(413), new Variant(384), new Variant(842), new Variant(797));
                    }
                });
    }

    @Test
    public void test_Union_TwentySevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x30b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(590), new Variant(476), new Variant(242), new Variant(138), new
                Variant(447), new Variant(320), new Variant(294), new Variant(763), new Variant(839), new Variant
                (332), new Variant(382), new Variant(798), new Variant(616), new Variant(21), new Variant(4), new
                Variant(687), new Variant(687), new Variant(358), new Variant(598), new Variant(547), new Variant
                (862), new Variant(280), new Variant(785), new Variant(289), new Variant(687))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Union(getMock(Range.class), getMock(Range.class), new Variant(590), new
                                Variant(476), new Variant(242), new Variant(138), new Variant(447), new Variant(320),
                                new Variant(294), new Variant(763), new Variant(839), new Variant(332), new Variant
                                        (382), new Variant(798), new Variant(616), new Variant(21), new Variant(4),
                                new Variant(687), new Variant(687), new Variant(358), new Variant(598), new Variant
                                        (547), new Variant(862), new Variant(280), new Variant(785), new Variant(289)
                                , new Variant(687));
                    }
                });
    }

    @Test
    public void test_Union_TwentyEightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x30b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(656), new Variant(964), new Variant(196), new Variant(815), new
                Variant(206), new Variant(783), new Variant(366), new Variant(436), new Variant(495), new Variant(63)
                , new Variant(791), new Variant(557), new Variant(176), new Variant(431), new Variant(691), new
                        Variant(717), new Variant(467), new Variant(563), new Variant(561), new Variant(603), new
                        Variant(998), new Variant(772), new Variant(391), new Variant(864), new Variant(110), new
                        Variant(379))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Union(getMock(Range.class), getMock(Range.class), new Variant(656), new
                                Variant(964), new Variant(196), new Variant(815), new Variant(206), new Variant(783),
                                new Variant(366), new Variant(436), new Variant(495), new Variant(63), new Variant
                                        (791), new Variant(557), new Variant(176), new Variant(431), new Variant(691)
                                , new Variant(717), new Variant(467), new Variant(563), new Variant(561), new Variant
                                        (603), new Variant(998), new Variant(772), new Variant(391), new Variant(864)
                                , new Variant(110), new Variant(379));
                    }
                });
    }

    @Test
    public void test_Union_TwentyNineArgs_ShouldRedirectToProxy() throws Exception {
        on(0x30b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(443), new Variant(134), new Variant(475), new Variant(172), new
                Variant(141), new Variant(626), new Variant(477), new Variant(633), new Variant(976), new Variant
                (350), new Variant(964), new Variant(223), new Variant(607), new Variant(430), new Variant(181), new
                Variant(377), new Variant(500), new Variant(764), new Variant(272), new Variant(552), new Variant(59)
                , new Variant(890), new Variant(262), new Variant(532), new Variant(422), new Variant(996), new
                        Variant(608))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Union(getMock(Range.class), getMock(Range.class), new Variant(443), new
                                Variant(134), new Variant(475), new Variant(172), new Variant(141), new Variant(626),
                                new Variant(477), new Variant(633), new Variant(976), new Variant(350), new Variant
                                        (964), new Variant(223), new Variant(607), new Variant(430), new Variant(181)
                                , new Variant(377), new Variant(500), new Variant(764), new Variant(272), new Variant
                                        (552), new Variant(59), new Variant(890), new Variant(262), new Variant(532),
                                new Variant(422), new Variant(996), new Variant(608));
                    }
                });
    }

    @Test
    public void test_Union_ThirtyArgs_ShouldRedirectToProxy() throws Exception {
        on(0x30b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(609), new Variant(210), new Variant(863), new Variant(11), new
                Variant(352), new Variant(30), new Variant(666), new Variant(912), new Variant(753), new Variant(611)
                , new Variant(815), new Variant(352), new Variant(698), new Variant(311), new Variant(782), new
                        Variant(436), new Variant(863), new Variant(300), new Variant(15), new Variant(658), new
                        Variant(590), new Variant(566), new Variant(353), new Variant(259), new Variant(781), new
                        Variant(321), new Variant(324), new Variant(10))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Union(getMock(Range.class), getMock(Range.class), new Variant(609), new
                                Variant(210), new Variant(863), new Variant(11), new Variant(352), new Variant(30),
                                new Variant(666), new Variant(912), new Variant(753), new Variant(611), new Variant
                                        (815), new Variant(352), new Variant(698), new Variant(311), new Variant(782)
                                , new Variant(436), new Variant(863), new Variant(300), new Variant(15), new Variant
                                        (658), new Variant(590), new Variant(566), new Variant(353), new Variant(259)
                                , new Variant(781), new Variant(321), new Variant(324), new Variant(10));
                    }
                });
    }

    @Test
    public void test_getAxWindows_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1ae).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Windows>() {
                    @Override
                    public Windows invoke() throws ActiveXException {
                        return component.getAxWindows();
                    }
                });
    }

    @Test
    public void test_getAxWorkbooks_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x23c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Workbooks>() {
                    @Override
                    public Workbooks invoke() throws ActiveXException {
                        return component.getAxWorkbooks();
                    }
                });
    }

    @Test
    public void test_getAxWorksheetFunction_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5a0).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<WorksheetFunction>() {
                    @Override
                    public WorksheetFunction invoke() throws ActiveXException {
                        return component.getAxWorksheetFunction();
                    }
                });
    }

    @Test
    public void test_getAxWorksheets_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1ee).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Sheets>() {
                    @Override
                    public Sheets invoke() throws ActiveXException {
                        return component.getAxWorksheets();
                    }
                });
    }

    @Test
    public void test_getAxExcel4IntlMacroSheets_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x245).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Sheets>() {
                    @Override
                    public Sheets invoke() throws ActiveXException {
                        return component.getAxExcel4IntlMacroSheets();
                    }
                });
    }

    @Test
    public void test_getAxExcel4MacroSheets_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x243).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Sheets>() {
                    @Override
                    public Sheets invoke() throws ActiveXException {
                        return component.getAxExcel4MacroSheets();
                    }
                });
    }

}