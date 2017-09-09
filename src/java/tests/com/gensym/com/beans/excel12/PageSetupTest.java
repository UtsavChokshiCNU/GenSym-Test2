package com.gensym.com.beans.excel12;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXDispatchable;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import org.junit.Before;
import org.junit.Test;

public class PageSetupTest extends ActiveXDispatchableTestBase {

    private PageSetup component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new PageSetup(axProxy);
    }

    @Test
    public void test_QueryInterface_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60000000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(782), new Variant(175))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.QueryInterface(new Variant(782), new Variant(175));
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
        on(0x60010000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(882))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfoCount(new Variant(882));
                    }
                });
    }

    @Test
    public void test_GetTypeInfo_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010001).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42L), new Variant(42L), new
                Variant(171))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfo(42L, 42L, new Variant(171));
                    }
                });
    }

    @Test
    public void test_GetIDsOfNames_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(943), new Variant(9), new
                Variant(42L), new Variant(42L), new Variant(594))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetIDsOfNames(new Variant(943), new Variant(9), 42L, 42L, new Variant(594));
                    }
                });
    }

    @Test
    public void test_Invoke_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010003).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(367), new
                Variant(42L), new Variant(42), new Variant(66), new Variant(618), new Variant(1), new Variant(217))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Invoke(42, new Variant(367), 42L, 42, new Variant(66), new Variant(618), new
                                Variant(1), new Variant(217));
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
    public void test_getAxBlackAndWhite_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3f1).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxBlackAndWhite();
                    }
                });
    }

    @Test
    public void test_setAxBlackAndWhite_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x3f1).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxBlackAndWhite(false);
                    }
                });
    }

    @Test
    public void test_getAxBottomMargin_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3ea).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDouble(new Returns<Double>() {
                    @Override
                    public Double invoke() throws ActiveXException {
                        return component.getAxBottomMargin();
                    }
                });
    }

    @Test
    public void test_setAxBottomMargin_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x3ea).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42.32d))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxBottomMargin(42.32d);
                    }
                });
    }

    @Test
    public void test_getAxCenterFooter_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3f2).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxCenterFooter();
                    }
                });
    }

    @Test
    public void test_setAxCenterFooter_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x3f2).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("dSSumTLNAV"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxCenterFooter("dSSumTLNAV");
                    }
                });
    }

    @Test
    public void test_getAxCenterHeader_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3f3).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxCenterHeader();
                    }
                });
    }

    @Test
    public void test_setAxCenterHeader_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x3f3).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("laWxbSQHPF"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxCenterHeader("laWxbSQHPF");
                    }
                });
    }

    @Test
    public void test_getAxCenterHorizontally_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3ed).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxCenterHorizontally();
                    }
                });
    }

    @Test
    public void test_setAxCenterHorizontally_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x3ed).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxCenterHorizontally(false);
                    }
                });
    }

    @Test
    public void test_getAxCenterVertically_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3ee).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxCenterVertically();
                    }
                });
    }

    @Test
    public void test_setAxCenterVertically_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x3ee).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxCenterVertically(false);
                    }
                });
    }

    @Test
    public void test_getAxChartSize_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3f4).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxChartSize();
                    }
                });
    }

    @Test
    public void test_setAxChartSize_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x3f4).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxChartSize(42);
                    }
                });
    }

    @Test
    public void test_getAxDraft_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3fc).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxDraft();
                    }
                });
    }

    @Test
    public void test_setAxDraft_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x3fc).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxDraft(false);
                    }
                });
    }

    @Test
    public void test_getAxFirstPageNumber_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3f0).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxFirstPageNumber();
                    }
                });
    }

    @Test
    public void test_setAxFirstPageNumber_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x3f0).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxFirstPageNumber(42);
                    }
                });
    }

    @Test
    public void test_getAxFitToPagesTall_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3f5).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxFitToPagesTall();
                    }
                });
    }

    @Test
    public void test_setAxFitToPagesTall_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x3f5).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(359))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxFitToPagesTall(new Variant(359));
                    }
                });
    }

    @Test
    public void test_getAxFitToPagesWide_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3f6).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxFitToPagesWide();
                    }
                });
    }

    @Test
    public void test_setAxFitToPagesWide_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x3f6).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(448))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxFitToPagesWide(new Variant(448));
                    }
                });
    }

    @Test
    public void test_getAxFooterMargin_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3f7).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDouble(new Returns<Double>() {
                    @Override
                    public Double invoke() throws ActiveXException {
                        return component.getAxFooterMargin();
                    }
                });
    }

    @Test
    public void test_setAxFooterMargin_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x3f7).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42.32d))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxFooterMargin(42.32d);
                    }
                });
    }

    @Test
    public void test_getAxHeaderMargin_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3f8).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDouble(new Returns<Double>() {
                    @Override
                    public Double invoke() throws ActiveXException {
                        return component.getAxHeaderMargin();
                    }
                });
    }

    @Test
    public void test_setAxHeaderMargin_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x3f8).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42.32d))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxHeaderMargin(42.32d);
                    }
                });
    }

    @Test
    public void test_getAxLeftFooter_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3f9).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxLeftFooter();
                    }
                });
    }

    @Test
    public void test_setAxLeftFooter_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x3f9).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("TEWxPdiXKs"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxLeftFooter("TEWxPdiXKs");
                    }
                });
    }

    @Test
    public void test_getAxLeftHeader_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3fa).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxLeftHeader();
                    }
                });
    }

    @Test
    public void test_setAxLeftHeader_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x3fa).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("PYNSkIWDsT"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxLeftHeader("PYNSkIWDsT");
                    }
                });
    }

    @Test
    public void test_getAxLeftMargin_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3e7).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDouble(new Returns<Double>() {
                    @Override
                    public Double invoke() throws ActiveXException {
                        return component.getAxLeftMargin();
                    }
                });
    }

    @Test
    public void test_setAxLeftMargin_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x3e7).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42.32d))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxLeftMargin(42.32d);
                    }
                });
    }

    @Test
    public void test_getAxOrder_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xc0).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxOrder();
                    }
                });
    }

    @Test
    public void test_setAxOrder_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xc0).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxOrder(42);
                    }
                });
    }

    @Test
    public void test_getAxOrientation_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x86).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxOrientation();
                    }
                });
    }

    @Test
    public void test_setAxOrientation_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x86).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxOrientation(42);
                    }
                });
    }

    @Test
    public void test_getAxPaperSize_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3ef).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxPaperSize();
                    }
                });
    }

    @Test
    public void test_setAxPaperSize_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x3ef).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxPaperSize(42);
                    }
                });
    }

    @Test
    public void test_getAxPrintArea_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3fb).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxPrintArea();
                    }
                });
    }

    @Test
    public void test_setAxPrintArea_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x3fb).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("wndATntUEJ"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxPrintArea("wndATntUEJ");
                    }
                });
    }

    @Test
    public void test_getAxPrintGridlines_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3ec).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxPrintGridlines();
                    }
                });
    }

    @Test
    public void test_setAxPrintGridlines_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x3ec).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxPrintGridlines(false);
                    }
                });
    }

    @Test
    public void test_getAxPrintHeadings_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3eb).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxPrintHeadings();
                    }
                });
    }

    @Test
    public void test_setAxPrintHeadings_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x3eb).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxPrintHeadings(false);
                    }
                });
    }

    @Test
    public void test_getAxPrintNotes_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3fd).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxPrintNotes();
                    }
                });
    }

    @Test
    public void test_setAxPrintNotes_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x3fd).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxPrintNotes(false);
                    }
                });
    }

    @Test
    public void test_PrintQuality_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3fe).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.PrintQuality();
                    }
                });
    }

    @Test
    public void test_PrintQuality_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x3fe).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(190))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.PrintQuality(new Variant(190));
                    }
                });
    }

    @Test
    public void test_getAxPrintTitleColumns_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3ff).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxPrintTitleColumns();
                    }
                });
    }

    @Test
    public void test_setAxPrintTitleColumns_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x3ff).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("UrJjHcMrYE"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxPrintTitleColumns("UrJjHcMrYE");
                    }
                });
    }

    @Test
    public void test_getAxPrintTitleRows_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x400).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxPrintTitleRows();
                    }
                });
    }

    @Test
    public void test_setAxPrintTitleRows_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x400).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("EiylHtJGHJ"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxPrintTitleRows("EiylHtJGHJ");
                    }
                });
    }

    @Test
    public void test_getAxRightFooter_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x401).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxRightFooter();
                    }
                });
    }

    @Test
    public void test_setAxRightFooter_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x401).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("iYtWYQvYOd"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxRightFooter("iYtWYQvYOd");
                    }
                });
    }

    @Test
    public void test_getAxRightHeader_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x402).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxRightHeader();
                    }
                });
    }

    @Test
    public void test_setAxRightHeader_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x402).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("xyvNHOtiVX"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxRightHeader("xyvNHOtiVX");
                    }
                });
    }

    @Test
    public void test_getAxRightMargin_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3e8).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDouble(new Returns<Double>() {
                    @Override
                    public Double invoke() throws ActiveXException {
                        return component.getAxRightMargin();
                    }
                });
    }

    @Test
    public void test_setAxRightMargin_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x3e8).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42.32d))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxRightMargin(42.32d);
                    }
                });
    }

    @Test
    public void test_getAxTopMargin_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3e9).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDouble(new Returns<Double>() {
                    @Override
                    public Double invoke() throws ActiveXException {
                        return component.getAxTopMargin();
                    }
                });
    }

    @Test
    public void test_setAxTopMargin_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x3e9).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42.32d))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxTopMargin(42.32d);
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
        on(0x297).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(954))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxZoom(new Variant(954));
                    }
                });
    }

    @Test
    public void test_getAxPrintComments_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5f4).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxPrintComments();
                    }
                });
    }

    @Test
    public void test_setAxPrintComments_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x5f4).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxPrintComments(42);
                    }
                });
    }

}