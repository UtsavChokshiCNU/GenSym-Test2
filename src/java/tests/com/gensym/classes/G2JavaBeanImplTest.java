package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class G2JavaBeanImplTest extends G2TestBase<G2JavaBeanImpl> {

    @Override
    protected Class<G2JavaBeanImpl> forClass() {
        return G2JavaBeanImpl.class;
    }

    @Test
    public void test_getInternalMediaBin_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.INTERNAL_MEDIA_BIN_, getStub(com.gensym.classes.MediaBin.class));

        assertThat(instance.getInternalMediaBin()).isEqualTo(getStub(com.gensym.classes.MediaBin.class));
    }


    @Test
    public void test_setLatentListeners_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setLatentListeners(getStub(com.gensym.util.Structure.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.LATENT_LISTENERS_)).isEqualTo(getStub(com.gensym.util.Structure.class));
    }
    @Test
    public void test_getLatentListeners_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.LATENT_LISTENERS_, getStub(com.gensym.util.Structure.class));

        assertThat(instance.getLatentListeners()).isEqualTo(getStub(com.gensym.util.Structure.class));
    }


}