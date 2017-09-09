package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class G2HtmlViewImplTest extends G2TestBase<G2HtmlViewImpl> {

    @Override
    protected Class<G2HtmlViewImpl> forClass() {
        return G2HtmlViewImpl.class;
    }

    @Test
    public void test_setUrlOfView_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setUrlOfView("ABC");

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.URL_OF_VIEW_)).isEqualTo("ABC");
    }
    @Test
    public void test_getUrlOfView_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.URL_OF_VIEW_, "ABC");

        assertThat(instance.getUrlOfView()).isEqualTo("ABC");
    }


}