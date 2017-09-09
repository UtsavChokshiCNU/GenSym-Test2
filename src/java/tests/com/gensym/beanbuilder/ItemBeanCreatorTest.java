package com.gensym.beanbuilder;

import com.gensym.classes.G2JavaBean;
import com.gensym.classes.G2_ItemWrapperEvent;
import com.gensym.classes.G2__BaseImpl;
import com.gensym.com.BeanXporterListener;
import com.gensym.util.SourceCompiler;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.mockito.Matchers;
import org.powermock.api.mockito.PowerMockito;
import org.powermock.core.classloader.annotations.PrepareForTest;
import org.powermock.modules.junit4.PowerMockRunner;
import org.powermock.reflect.Whitebox;

import java.io.File;
import java.lang.reflect.Method;

import static org.junit.Assert.*;

@RunWith(PowerMockRunner.class)
@PrepareForTest({ SourceCompiler.class })
public class ItemBeanCreatorTest {

    private File inputXmlFile = new File(this.getClass().getResource("").getFile());
    private ItemBeanCreator itemBeanCreator;

    @Before
    public void setup() throws Exception {

        PowerMockito.mockStatic(SourceCompiler.class);

        PowerMockito.doNothing().when(SourceCompiler.class, "Compile", Matchers.anyString());

        itemBeanCreator = new ItemBeanCreator(G2__BaseImpl.class, inputXmlFile.getAbsolutePath(), new int[] {0,1});

        itemBeanCreator.generateBean();
    }

    private Object invokePrivateMethod(String methodName, Class[] paramTypes, Object[] paramValues) throws Exception {

        Method method = ItemBeanCreator.class.getDeclaredMethod(methodName, paramTypes);
        method.setAccessible(true);

        return method.invoke(itemBeanCreator, paramValues);
    }

    /**
     *
     * Method: getJavaTypeString()
     *
     */
    @Test
    public void test_getJavaTypeString_onCall_returnsSetClassName() throws Exception {

        // Arrange
        String methodName = "getJavaTypeString";
        Class[] paramTypes = new Class[]{ Class.class };
        Object[] paramValues = new Object[] { G2__BaseImpl.class };

        // Act
        String actualResult = (String)invokePrivateMethod(methodName, paramTypes, paramValues);

        // Assert
        assertNotNull(actualResult);
        assertEquals(G2__BaseImpl.class.getName(), actualResult);
    }

    /**
     *
     * Method: isStandardListenerInterface(Class)
     *
     */
    @Test
    public void test_isStandardListenerInterface_ParamTypeIsAssignableFromEventObject_returnsFalse() throws Exception {

        // Arrange
        String methodName = "isStandardListenerInterface";
        Class[] paramTypes = new Class[]{ Class.class };
        Object[] paramValues = new Object[] { BeanXporterListener.class };

        // Act
        Boolean actualResult = (Boolean)invokePrivateMethod(methodName, paramTypes, paramValues);

        // Assert
        assertFalse(actualResult);
    }

    /**
     *
     * Method: isStandardListenerInterface(Class)
     *
     */
    @Test
    public void test_isStandardListenerInterface_methodParamsNotEqualOne_returnsFalse() throws Exception {

        // Arrange
        String methodName = "isStandardListenerInterface";
        Class[] paramTypes = new Class[]{ Class.class };
        Object[] paramValues = new Object[] { G2_ItemWrapperEvent.class };

        // Act
        Boolean actualResult = (Boolean)invokePrivateMethod(methodName, paramTypes, paramValues);

        // Assert
        assertFalse(actualResult);
    }

    /**
     *
     * Method: generateBeanInfo()
     *
     */
    @Test
    public void test_generateBeanInfo_onCall_verifiesSetBeanClassAndSourceCompilerCall() throws Exception {

        // Arrange
        PowerMockito.mockStatic(SourceCompiler.class);

        itemBeanCreator = new ItemBeanCreator(G2__BaseImpl.class.getName()
                , inputXmlFile.getAbsolutePath(), new int[] {0,1});

        Whitebox.setInternalState(itemBeanCreator, "javaClassName", "G2Java");

        // Act
        itemBeanCreator.generateBeanInfo();

        // Assert
        assertEquals(G2JavaBean.class, Whitebox.getInternalState(itemBeanCreator, "beanClass"));
        PowerMockito.verifyStatic();
        SourceCompiler.Compile(Matchers.anyString());
    }

    /**
     *
     * Method: generateBean()
     *
     */
    @Test
    public void test_generateBean_onCall_verifiesSourceCompilerCall() throws Exception {

        // Arrange
        PowerMockito.mockStatic(SourceCompiler.class);

        // Act
        itemBeanCreator.generateBean();

        // Assert
        PowerMockito.verifyStatic();
        SourceCompiler.Compile(Matchers.anyString());
    }
}
