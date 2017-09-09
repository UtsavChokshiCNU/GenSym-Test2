package com.gensym.jgi.download;

import com.gensym.beanbuilder.ItemBeanCreator;
import com.gensym.classes.G2__BaseImpl;
import com.gensym.util.Sequence;
import org.junit.*;
import static org.junit.Assert.*;
import com.gensym.util.Structure;
import com.gensym.util.Symbol;
import org.mockito.Mockito;
import org.mockito.internal.matchers.Null;

import java.awt.*;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

/**
 * @author Deepti
 * @version $Revision: 1.0 $
 */
public class TypeHandlerTest {
	/**
	 * Run the TypeHandler() constructor test.
	 */
	@Test
	public void testTypeHandler() throws Exception {
		TypeHandler result = new TypeHandler();
		assertNotNull(result);
	}
	/**
	 * Run the Symbol getTypeFromTypeDescription(Structure) method test.
	 */
	@Test
	public void testGetTypeFromTypeDescriptionInteger() throws Exception {
		Structure typeDescrpn = new Structure();
		typeDescrpn.setAttributeValue(Symbol.intern("TYPE-OR-OPERATOR"), Symbol.intern ("INTEGER-RANGE"));
		Symbol result = TypeHandler.getTypeFromTypeDescription(typeDescrpn);
		assertEquals("INTEGER", result.toString());
	}
    /**
     * Run the Symbol getTypeFromTypeDescription(Structure) method test.
     */
    @Test
    public void testGetTypeFromTypeDescriptionFloat() throws Exception {
        Structure typeDescrpn = new Structure();
        typeDescrpn.setAttributeValue(Symbol.intern("TYPE-OR-OPERATOR"), Symbol.intern ("FLOAT-RANGE"));
        Symbol result = TypeHandler.getTypeFromTypeDescription(typeDescrpn);
        assertEquals("FLOAT", result.toString());
    }
    /**
     * Run the Symbol getTypeFromTypeDescription(Structure) method test.
     */
    @Test
    public void testGetTypeFromTypeDescriptionQuantity() throws Exception {
        Structure typeDescrpn = new Structure();
        typeDescrpn.setAttributeValue(Symbol.intern("TYPE-OR-OPERATOR"), Symbol.intern ("QUANTITY-RANGE"));
        Symbol result = TypeHandler.getTypeFromTypeDescription(typeDescrpn);
        assertEquals("QUANTITY", result.toString());
    }
    /**
     * Run the Symbol getTypeFromTypeDescription(Structure) method test.
     */
    @Test
    public void testGetTypeFromTypeDescriptionValue() throws Exception {
        Structure typeDescrpn = new Structure();
        typeDescrpn.setAttributeValue(Symbol.intern("TYPE-OR-OPERATOR"), Symbol.intern ("VALUE"));
        Symbol result = TypeHandler.getTypeFromTypeDescription(typeDescrpn);
        assertEquals("ITEM-OR-VALUE", result.toString());
    }
    /**
     * Run the Symbol getTypeFromTypeDescription(Structure) method test.
     */
    @Test
    public void testGetTypeFromTypeDescriptionMember() throws Exception {
        Structure typeDescrpn = new Structure();
        typeDescrpn.setAttributeValue(Symbol.intern("TYPE-OR-OPERATOR"), Symbol.intern ("MEMBER"));
        Symbol result = TypeHandler.getTypeFromTypeDescription(typeDescrpn);
        assertEquals("SYMBOL", result.toString());
    }
    /**
     * Run the Symbol getTypeFromTypeDescription(Structure) method test.
     */
    @Test
    public void testGetTypeFromTypeDescriptionClass() throws Exception {
        Structure typeDescrpn = new Structure();
        typeDescrpn.setAttributeValue(Symbol.intern("TYPE-OR-OPERATOR"), Symbol.intern ("CLASS"));
        typeDescrpn.setAttributeValue(Symbol.intern ("CLASS-NAME"), Symbol.intern ("CLASS"));
        Symbol result = TypeHandler.getTypeFromTypeDescription(typeDescrpn);
        assertEquals("CLASS", result.toString());
    }
    /**
     * Run the Symbol getTypeFromTypeDescription(Structure) method test.
     */
    @Test(expected = NullPointerException.class)
    public void testGetTypeFromTypeDescriptionOr() throws Exception {
        Structure type = new Structure();
        type.setAttributeValue(Symbol.intern("TYPE-OR-OPERATOR"), Symbol.intern ("CLASS"));
        Sequence seq = new Sequence();
        seq.add(type);
        Structure typeDescrpn = new Structure();
        typeDescrpn.setAttributeValue(Symbol.intern("TYPE-OR-OPERATOR"), Symbol.intern ("OR"));
        typeDescrpn.setAttributeValue(Symbol.intern ("OPERANDS"), seq);
        TypeHandler.getTypeFromTypeDescription(typeDescrpn);
    }
    /**
     * Run the Symbol getTypeFromTypeDescription(Structure) method test.
     */
    @Test(expected = IllegalArgumentException.class)
    public void testGetTypeFromTypeDescriptionNot() throws Exception {
        Structure typeDescrpn = new Structure();
        typeDescrpn.setAttributeValue(Symbol.intern("TYPE-OR-OPERATOR"), Symbol.intern ("NOT"));
        TypeHandler.getTypeFromTypeDescription(typeDescrpn);
    }
    /**
     * Run the Symbol getTypeFromTypeDescription(Structure) method test.
     */
    @Test
    public void testGetTypeFromTypeDescriptionNull() throws Exception {
        Structure typeDescrpn = new Structure();
        Symbol result = TypeHandler.getTypeFromTypeDescription(typeDescrpn);
        assertEquals(null, result);
    }
	/**
	 * Run the boolean isClassType(Symbol) method test.
	 */
	@Test
	public void testIsClassType() throws Exception {
		Symbol typeName_ = Symbol.intern("");
		boolean result = TypeHandler.isClassType(typeName_);
		assertEquals(true, result);
	}
    @Test
    public void testFindClosestEnclosingType() throws Exception {
        TypeHandler fixture = new TypeHandler();
        Symbol symbol1 = Symbol.intern("INTEGER");
        Symbol symbol2 = Symbol.intern("FLOAT");
        Method method = TypeHandler.class.getDeclaredMethod("findClosestEnclosingType", Symbol.class, Symbol.class);
        method.setAccessible(true);
        Symbol result = (Symbol)method.invoke(fixture, symbol1, symbol2);
        assertNotNull(result);
    }
    @Test
    public void testFindClosestEnclosingType1() throws Exception {
        TypeHandler fixture = new TypeHandler();
        Symbol symbol1 = Symbol.intern("INTEGER");
        Method method = TypeHandler.class.getDeclaredMethod("findClosestEnclosingType", Symbol.class, Symbol.class);
        method.setAccessible(true);
        Symbol result = (Symbol)method.invoke(fixture, symbol1, null);
        assertNotNull(result);
    }
    @Test
    public void testFindClosestEnclosingTypeNull() throws Exception {
        TypeHandler fixture = new TypeHandler();
        Method method = TypeHandler.class.getDeclaredMethod("findClosestEnclosingType", Symbol.class, Symbol.class);
        method.setAccessible(true);
        Symbol result = (Symbol)method.invoke(fixture, null, null);
        assertEquals(result, null);
    }
}