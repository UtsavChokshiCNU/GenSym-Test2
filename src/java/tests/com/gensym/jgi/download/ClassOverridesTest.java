package com.gensym.jgi.download;

import com.gensym.util.Sequence;
import com.gensym.util.Structure;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.OverrideSymbols;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import org.powermock.reflect.Whitebox;

import java.lang.reflect.Method;
import java.util.Enumeration;

import static org.junit.Assert.*;

public class ClassOverridesTest {

    private ClassOverrides classOverrides;

    @Before
    public void setUp() throws Exception {

        classOverrides = new ClassOverrides();
    }

    @After
    public void tearDown() { classOverrides = null; }

    private Object getClassOverridesField(ClassOverrides classOverridesObj, String fieldName) {

        return Whitebox.getInternalState(classOverridesObj, fieldName);
    }

    private ClassOverrides getClassOverridesObj(Object[] values) throws Exception {

        Symbol[] keys = new Symbol[]
                {
                        OverrideSymbols.CLASS_INFO_,
                        OverrideSymbols.PROPERTIES_,
                        OverrideSymbols.METHODS_,
                        OverrideSymbols.EVENTS_,
                        OverrideSymbols.FIELDS_,
                        OverrideSymbols.IMPORTS_
                };
        Structure overrides = new Structure(keys, values);

        return new ClassOverrides(overrides);
    }

    private ClassOverrides initializeClassOverridesGetterMethods(Symbol attrName, Symbol slotName, Symbol slotValue) throws Exception {
        return initializeClassOverridesGetterMethods(attrName, slotName, slotValue, "ExpectedResult", false);
    }

    private ClassOverrides initializeClassOverridesGetterMethods(Symbol attrName, Symbol slotName, Symbol slotValue, String outResult) throws Exception {
        return initializeClassOverridesGetterMethods(attrName, slotName, slotValue, outResult, false);
    }

    private ClassOverrides initializeClassOverridesGetterMethods(Symbol attrName, Symbol slotName, Symbol slotValue, String outResult, boolean hasNoMatchedProp) throws Exception {

        // Arrange
        Structure propStructure = new Structure(
                new Symbol[]
                        {
                                slotName,
                                attrName
                        },
                new Object[]
                        {
                                !hasNoMatchedProp ? slotValue : Symbol.intern(slotValue.toString() + "no"),
                                outResult
                        }
        );
        Sequence propertySequence = new Sequence();
        Sequence methodsSequence = new Sequence();
        Sequence eventsSequence = new Sequence();
        Sequence fieldsSequence = new Sequence();
        Sequence importsSequence = new Sequence();

        if (slotName == OverrideSymbols.PROPERTY_NAME_)
            propertySequence.add(propStructure);
        else if (slotName == OverrideSymbols.METHOD_NAME_)
            methodsSequence.add(propStructure);
        else if (slotName == OverrideSymbols.EVENT_NAME_)
            eventsSequence.add(propStructure);
        else if (slotName == OverrideSymbols.FIELD_NAME_)
            fieldsSequence.add(propStructure);
        else if (slotName == OverrideSymbols.IMPORT_NAME_)
            importsSequence.add(propStructure);

        Object[] values = new Object[]
                {
                        new Structure(),
                        propertySequence,
                        methodsSequence,
                        eventsSequence,
                        fieldsSequence,
                        importsSequence
                };
        Symbol[] keys = new Symbol[]
                {
                        OverrideSymbols.CLASS_INFO_,
                        OverrideSymbols.PROPERTIES_,
                        OverrideSymbols.METHODS_,
                        OverrideSymbols.EVENTS_,
                        OverrideSymbols.FIELDS_,
                        OverrideSymbols.IMPORTS_
                };
        Structure overrides = new Structure(keys, values);

        return new ClassOverrides(overrides);
    }

    @Test
    public void test_getImplementedInterfaces_nullClassInfo_ReturnsEmptySequence() throws Exception {

        // Act
        Sequence actualResult = classOverrides.getImplementedInterfaces();

        // Assert
        assertEquals(0, actualResult.size());
    }

    @Test
    public void test_getImplementedInterfaces_notNullClassInfo_returnsSetSequence() throws Exception {

        // Arrange
        Sequence classSequence = new Sequence();
        classSequence.add("Test");
        Structure classStructure = new Structure(
            new Symbol[]{ OverrideSymbols.INTERFACES_ },
            new Object[]{ classSequence }
        );
        Object[] values = new Object[]
        {
            classStructure, new Sequence(), new Sequence(), new Sequence(), new Sequence(), new Sequence()
        };
        ClassOverrides classOverridesObj = getClassOverridesObj(values);

        // Act
        Sequence actualResult = classOverridesObj.getImplementedInterfaces();

        // Assert
        assertEquals(classSequence, actualResult);
    }

    @Test
    public void test_getGetterComments_nullMatchingStructure_returnsNull() throws Exception {

        // Arrange
        Symbol propSymbol = Symbol.intern("SetPropertyValue");
        Structure propStructure = new Structure(
                new Symbol[]
                        {
                                OverrideSymbols.PROPERTY_NAME_,
                                OverrideSymbols.GETTER_COMMENTS_
                        },
                new Object[]
                        {
                                Symbol.intern("NotSetPropertyValue"),
                                "SetGetterComments"
                        }
        );
        Sequence propertySequence = new Sequence();
        propertySequence.add(propStructure);
        Object[] values = new Object[]
                {
                        new Structure(),
                        propertySequence,
                        new Sequence(),
                        new Sequence(),
                        new Sequence(),
                        new Sequence()
                };
        ClassOverrides classOverridesObj = getClassOverridesObj(values);

        // Act
        String actualResult = classOverridesObj.getGetterComments(propSymbol);

        // Assert
        assertNull(actualResult);
    }

    @Test
    public void test_getSetterInterface_notNullMatchingStructure_returnsSetGetterAttributeString() throws Exception {

        // Arrange
        Symbol attrName = OverrideSymbols.SETTER_INTERFACE_;
        Symbol slotName = OverrideSymbols.PROPERTY_NAME_;
        Symbol slotValue = Symbol.intern("SetPropertyValue");

        ClassOverrides classOverridesObj = initializeClassOverridesGetterMethods(attrName, slotName, slotValue);

        // Act
        String actualResult = classOverridesObj.getSetterInterface(slotValue);

        // Assert
        assertEquals("ExpectedResult", actualResult);
    }

    @Test
    public void test_getSetterComments_notNullMatchingStructure_returnsSetGetterAttributeString() throws Exception {

        // Arrange
        Symbol attrName = OverrideSymbols.SETTER_COMMENTS_;
        Symbol slotName = OverrideSymbols.PROPERTY_NAME_;
        Symbol slotValue = Symbol.intern("SetPropertyValue");

        ClassOverrides classOverridesObj = initializeClassOverridesGetterMethods(attrName, slotName, slotValue);

        // Act
        String actualResult = classOverridesObj.getSetterComments(slotValue);

        // Assert
        assertEquals("ExpectedResult", actualResult);
    }

    @Test
    public void test_getGetterImplementation_notNullMatchingStructure_returnsSetGetterAttributeString() throws Exception {

        // Arrange
        Symbol attrName = OverrideSymbols.GETTER_IMPLEMENTATION_;
        Symbol slotName = OverrideSymbols.PROPERTY_NAME_;
        Symbol slotValue = Symbol.intern("SetPropertyValue");

        ClassOverrides classOverridesObj = initializeClassOverridesGetterMethods(attrName, slotName, slotValue);

        // Act
        String actualResult = classOverridesObj.getGetterImplementation(slotValue);

        // Assert
        assertEquals("ExpectedResult", actualResult);
    }

    @Test
    public void test_getGetterComments_notNullMatchingStructure_returnsSetGetterAttributeString() throws Exception {

        // Arrange
        Symbol attrName = OverrideSymbols.GETTER_COMMENTS_;
        Symbol slotName = OverrideSymbols.PROPERTY_NAME_;
        Symbol slotValue = Symbol.intern("SetPropertyValue");

        ClassOverrides classOverridesObj = initializeClassOverridesGetterMethods(attrName, slotName, slotValue);

        // Act
        String actualResult = classOverridesObj.getGetterComments(slotValue);

        // Assert
        assertEquals("ExpectedResult", actualResult);
    }

    @Test
    public void test_getGetterInterface_notNullMatchingStructure_returnsSetGetterAttributeString() throws Exception {

        // Arrange
        Symbol attrName = OverrideSymbols.GETTER_INTERFACE_;
        Symbol slotName = OverrideSymbols.PROPERTY_NAME_;
        Symbol slotValue = Symbol.intern("SetPropertyValue");

        ClassOverrides classOverridesObj = initializeClassOverridesGetterMethods(attrName, slotName, slotValue);

        // Act
        String actualResult = classOverridesObj.getGetterInterface(slotValue);

        // Assert
        assertEquals("ExpectedResult", actualResult);
    }

    @Test
    public void test_getSetterImplementation_notNullMatchingStructure_returnsSetGetterAttributeString() throws Exception {

        // Arrange
        Symbol attrName = OverrideSymbols.SETTER_IMPLEMENTATION_;
        Symbol slotName = OverrideSymbols.PROPERTY_NAME_;
        Symbol slotValue = Symbol.intern("SetPropertyValue");

        ClassOverrides classOverridesObj = initializeClassOverridesGetterMethods(attrName, slotName, slotValue);

        // Act
        String actualResult = classOverridesObj.getSetterImplementation(slotValue);

        // Assert
        assertEquals("ExpectedResult", actualResult);
    }

    @Test
    public void test_getMethodComments_notNullMatchingStructure_returnsSetGetterAttributeString() throws Exception {

        // Arrange
        Symbol attrName = OverrideSymbols.COMMENTS_;
        Symbol slotName = OverrideSymbols.METHOD_NAME_;
        Symbol slotValue = Symbol.intern("SetPropertyValue");

        ClassOverrides classOverridesObj = initializeClassOverridesGetterMethods(attrName, slotName, slotValue);

        // Act
        String actualResult = classOverridesObj.getMethodComments(slotValue);

        // Assert
        assertEquals("ExpectedResult", actualResult);
    }

    @Test
    public void test_getMethodInterface_notNullMatchingStructure_returnsSetGetterAttributeString() throws Exception {

        // Arrange
        Symbol attrName = OverrideSymbols.INTERFACE_;
        Symbol slotName = OverrideSymbols.METHOD_NAME_;
        Symbol slotValue = Symbol.intern("SetPropertyValue");

        ClassOverrides classOverridesObj = initializeClassOverridesGetterMethods(attrName, slotName, slotValue);

        // Act
        String actualResult = classOverridesObj.getMethodInterface(slotValue);

        // Assert
        assertEquals("ExpectedResult", actualResult);
    }

    @Test
    public void test_getMethodImplementation_notNullMatchingStructure_returnsSetGetterAttributeString() throws Exception {

        // Arrange
        Symbol attrName = OverrideSymbols.IMPLEMENTATION_;
        Symbol slotName = OverrideSymbols.METHOD_NAME_;
        Symbol slotValue = Symbol.intern("SetPropertyValue");

        ClassOverrides classOverridesObj = initializeClassOverridesGetterMethods(attrName, slotName, slotValue);

        // Act
        String actualResult = classOverridesObj.getMethodImplementation(slotValue);

        // Assert
        assertEquals("ExpectedResult", actualResult);
    }

    @Test
    public void test_getAddListenerComments_notNullMatchingStructure_returnsSetGetterAttributeString() throws Exception {

        // Arrange
        Symbol attrName = OverrideSymbols.ADD_LISTENER_COMMENTS_;
        Symbol slotName = OverrideSymbols.EVENT_NAME_;
        Symbol slotValue = Symbol.intern("SetPropertyValue");

        ClassOverrides classOverridesObj = initializeClassOverridesGetterMethods(attrName, slotName, slotValue);

        // Act
        String actualResult = classOverridesObj.getAddListenerComments(slotValue);

        // Assert
        assertEquals("ExpectedResult", actualResult);
    }

    @Test
    public void test_getAddListenerInterface_notNullMatchingStructure_returnsSetGetterAttributeString() throws Exception {

        // Arrange
        Symbol attrName = OverrideSymbols.ADD_LISTENER_INTERFACE_;
        Symbol slotName = OverrideSymbols.EVENT_NAME_;
        Symbol slotValue = Symbol.intern("SetPropertyValue");

        ClassOverrides classOverridesObj = initializeClassOverridesGetterMethods(attrName, slotName, slotValue);

        // Act
        String actualResult = classOverridesObj.getAddListenerInterface(slotValue);

        // Assert
        assertEquals("ExpectedResult", actualResult);
    }

    @Test
    public void test_getAddListenerImplementation_notNullMatchingStructure_returnsSetGetterAttributeString() throws Exception {

        // Arrange
        Symbol attrName = OverrideSymbols.ADD_LISTENER_IMPLEMENTATION_;
        Symbol slotName = OverrideSymbols.EVENT_NAME_;
        Symbol slotValue = Symbol.intern("SetPropertyValue");

        ClassOverrides classOverridesObj = initializeClassOverridesGetterMethods(attrName, slotName, slotValue);

        // Act
        String actualResult = classOverridesObj.getAddListenerImplementation(slotValue);

        // Assert
        assertEquals("ExpectedResult", actualResult);
    }

    @Test
    public void test_getRemoveListenerComments_notNullMatchingStructure_returnsSetGetterAttributeString() throws Exception {

        // Arrange
        Symbol attrName = OverrideSymbols.REMOVE_LISTENER_COMMENTS_;
        Symbol slotName = OverrideSymbols.EVENT_NAME_;
        Symbol slotValue = Symbol.intern("SetPropertyValue");

        ClassOverrides classOverridesObj = initializeClassOverridesGetterMethods(attrName, slotName, slotValue);

        // Act
        String actualResult = classOverridesObj.getRemoveListenerComments(slotValue);

        // Assert
        assertEquals("ExpectedResult", actualResult);
    }

    @Test
    public void test_getRemoveListenerInterface_notNullMatchingStructure_returnsSetGetterAttributeString() throws Exception {

        // Arrange
        Symbol attrName = OverrideSymbols.REMOVE_LISTENER_INTERFACE_;
        Symbol slotName = OverrideSymbols.EVENT_NAME_;
        Symbol slotValue = Symbol.intern("SetPropertyValue");

        ClassOverrides classOverridesObj = initializeClassOverridesGetterMethods(attrName, slotName, slotValue);

        // Act
        String actualResult = classOverridesObj.getRemoveListenerInterface(slotValue);

        // Assert
        assertEquals("ExpectedResult", actualResult);
    }

    @Test
    public void test_getRemoveListenerImplementation_notNullMatchingStructure_returnsSetGetterAttributeString() throws Exception {

        // Arrange
        Symbol attrName = OverrideSymbols.REMOVE_LISTENER_IMPLEMENTATION_;
        Symbol slotName = OverrideSymbols.EVENT_NAME_;
        Symbol slotValue = Symbol.intern("SetPropertyValue");

        ClassOverrides classOverridesObj = initializeClassOverridesGetterMethods(attrName, slotName, slotValue);

        // Act
        String actualResult = classOverridesObj.getRemoveListenerImplementation(slotValue);

        // Assert
        assertEquals("ExpectedResult", actualResult);
    }

    @Test
    public void test_getFieldComments_notNullMatchingStructure_returnsSetGetterAttributeString() throws Exception {

        // Arrange
        Symbol attrName = OverrideSymbols.COMMENTS_;
        Symbol slotName = OverrideSymbols.FIELD_NAME_;
        Symbol slotValue = Symbol.intern("SetPropertyValue");

        ClassOverrides classOverridesObj = initializeClassOverridesGetterMethods(attrName, slotName, slotValue);

        // Act
        String actualResult = classOverridesObj.getFieldComments(slotValue);

        // Assert
        assertEquals("ExpectedResult", actualResult);
    }

    @Test
    public void test_getFieldDeclaration_notNullMatchingStructure_returnsSetGetterAttributeString() throws Exception {

        // Arrange
        Symbol attrName = OverrideSymbols.DECLARATION_;
        Symbol slotName = OverrideSymbols.FIELD_NAME_;
        Symbol slotValue = Symbol.intern("SetPropertyValue");

        ClassOverrides classOverridesObj = initializeClassOverridesGetterMethods(attrName, slotName, slotValue);

        // Act
        String actualResult = classOverridesObj.getFieldDeclaration(slotValue);

        // Assert
        assertEquals("ExpectedResult", actualResult);
    }

    @Test
    public void test_getFieldInitialValue_notNullMatchingStructure_returnsSetGetterAttributeString() throws Exception {

        // Arrange
        Symbol attrName = OverrideSymbols.INITIAL_VALUE_;
        Symbol slotName = OverrideSymbols.FIELD_NAME_;
        Symbol slotValue = Symbol.intern("SetPropertyValue");

        ClassOverrides classOverridesObj = initializeClassOverridesGetterMethods(attrName, slotName, slotValue);

        // Act
        String actualResult = classOverridesObj.getFieldInitialValue(slotValue);

        // Assert
        assertEquals("ExpectedResult", actualResult);
    }

    @Test
    public void test_getImportTypeOrPackage_notNullMatchingStructure_returnsSetGetterAttributeString() throws Exception {

        // Arrange
        Symbol attrName = OverrideSymbols.TYPE_OR_PACKAGE_;
        Symbol slotName = OverrideSymbols.IMPORT_NAME_;
        Symbol slotValue = Symbol.intern("SetPropertyValue");

        ClassOverrides classOverridesObj = initializeClassOverridesGetterMethods(attrName, slotName, slotValue);

        // Act
        String actualResult = classOverridesObj.getImportTypeOrPackage(slotValue);

        // Assert
        assertEquals("ExpectedResult", actualResult);
    }

    @Test
    public void test_getGetter_onCall_returnsNull() {

        // Arrange
        Symbol propName = Symbol.intern("SetPropertyName");

        // Act
        Method actualResult = classOverrides.getGetter(propName);

        // Assert
        assertNull(actualResult);
    }

    @Test
    public void test_getSetter_onCall_returnsNull() {

        // Arrange
        Symbol propName = Symbol.intern("SetPropertyName");

        // Act
        Method actualResult = classOverrides.getSetter(propName);

        // Assert
        assertNull(actualResult);
    }

    @Test
    public void test_getMethod_onCall_returnsNull() {

        // Arrange
        String methodName = "SetMethodName";
        Class[] params = new Class[]{ };

        // Act
        Method actualResult = classOverrides.getMethod(methodName, params);

        // Assert
        assertNull(actualResult);
    }

    @Test
    public void test_propertyExists_propertyExists_returnsTrue() throws Exception {

        // Arrange
        Symbol attrName = Symbol.intern("SomeAttributeName");
        Symbol slotName = OverrideSymbols.PROPERTY_NAME_;
        Symbol propName = Symbol.intern("SetPropertyName");

        ClassOverrides classOverridesObj = initializeClassOverridesGetterMethods(attrName, slotName, propName);

        // Act
        boolean actualResult = classOverridesObj.propertyExists(propName);

        // Assert
        assertTrue(actualResult);
    }

    @Test
    public void test_propertyExists_propertyNotExists_returnsFalse() throws Exception {

        // Arrange
        Symbol attrName = Symbol.intern("SomeAttributeName");
        Symbol slotName = OverrideSymbols.METHOD_NAME_;
        Symbol propName = Symbol.intern("SetPropertyName");

        ClassOverrides classOverridesObj = initializeClassOverridesGetterMethods(attrName, slotName, propName);

        // Act
        boolean actualResult = classOverridesObj.propertyExists(propName);

        // Assert
        assertFalse(actualResult);
    }

    @Test
    public void test_methodExists_methodPropExists_returnsTrue() throws Exception {

        // Arrange
        Symbol attrName = Symbol.intern("SomeAttributeName");
        Symbol slotName = OverrideSymbols.METHOD_NAME_;
        Symbol methodName = Symbol.intern("SetMethodName");

        ClassOverrides classOverridesObj = initializeClassOverridesGetterMethods(attrName, slotName, methodName);

        // Act
        boolean actualResult = classOverridesObj.methodExists(methodName);

        // Assert
        assertTrue(actualResult);
    }

    @Test
    public void test_methodExists_methodPropNotExists_returnsFalse() throws Exception {

        // Arrange
        Symbol attrName = Symbol.intern("SomeAttributeName");
        Symbol slotName = OverrideSymbols.PROPERTY_NAME_;
        Symbol methodName = Symbol.intern("SetMethodName");

        ClassOverrides classOverridesObj = initializeClassOverridesGetterMethods(attrName, slotName, methodName);

        // Act
        boolean actualResult = classOverridesObj.methodExists(methodName);

        // Assert
        assertFalse(actualResult);
    }

    @Test
    public void test_eventExists_eventPropExists_returnsTrue() throws Exception {

        // Arrange
        Symbol attrName = Symbol.intern("SomeAttributeName");
        Symbol slotName = OverrideSymbols.EVENT_NAME_;
        Symbol eventName = Symbol.intern("SetEventName");

        ClassOverrides classOverridesObj = initializeClassOverridesGetterMethods(attrName, slotName, eventName);

        // Act
        boolean actualResult = classOverridesObj.eventExists(eventName);

        // Assert
        assertTrue(actualResult);
    }

    @Test
    public void test_eventExists_eventPropNotExists_returnsFalse() throws Exception {

        // Arrange
        Symbol attrName = Symbol.intern("SomeAttributeName");
        Symbol slotName = OverrideSymbols.METHOD_NAME_;
        Symbol eventName = Symbol.intern("SetEventName");

        ClassOverrides classOverridesObj = initializeClassOverridesGetterMethods(attrName, slotName, eventName);

        // Act
        boolean actualResult = classOverridesObj.eventExists(eventName);

        // Assert
        assertFalse(actualResult);
    }

    @Test
    public void test_importExists_importPropExists_returnsTrue() throws Exception {

        // Arrange
        Symbol attrName = Symbol.intern("SomeAttributeName");
        Symbol slotName = OverrideSymbols.IMPORT_NAME_;
        Symbol importName = Symbol.intern("SetImportName");

        ClassOverrides classOverridesObj = initializeClassOverridesGetterMethods(attrName, slotName, importName);

        // Act
        boolean actualResult = classOverridesObj.importExists(importName);

        // Assert
        assertTrue(actualResult);
    }

    @Test
    public void test_importExists_importPropNotExists_returnsFalse() throws Exception {

        // Arrange
        Symbol attrName = Symbol.intern("SomeAttributeName");
        Symbol slotName = OverrideSymbols.METHOD_NAME_;
        Symbol importName = Symbol.intern("SetImportName");

        ClassOverrides classOverridesObj = initializeClassOverridesGetterMethods(attrName, slotName, importName);

        // Act
        boolean actualResult = classOverridesObj.importExists(importName);

        // Assert
        assertFalse(actualResult);
    }

    @Test
    public void test_concatenate_onCall_concatenatesClassOverridesParam() throws Exception {

        // Arrange
        Structure classStructure = new Structure(new Symbol[]{ }, new Object[]{ });
        Sequence propertySequence = new Sequence();
        Sequence propertySequenceObj = new Sequence();
        Sequence methodsSequence = new Sequence();
        Sequence eventsSequence = new Sequence();
        Sequence fieldsSequence = new Sequence();
        Sequence importsSequence = new Sequence();

        propertySequence.add(new Structure(new Symbol[]{ OverrideSymbols.PROPERTY_NAME_ },
                new Object[]{ "PropName" }));
        propertySequenceObj.add(new Structure(new Symbol[]{ OverrideSymbols.PROPERTY_NAME_ },
                new Object[]{ "PropName" }));

        Object[] values = new Object[]
            {
                classStructure, propertySequence, methodsSequence, eventsSequence, fieldsSequence, importsSequence
            };

        ClassOverrides co  = getClassOverridesObj(values);

        Object[] valuesObj = new Object[]
            {
                null, propertySequenceObj, new Sequence(), new Sequence(), new Sequence(), new Sequence()
            };

        ClassOverrides classOverridesObj  = getClassOverridesObj(valuesObj);

        // Act
        classOverridesObj.concatenate(co);

        // Assert
        assertEquals(classStructure, getClassOverridesField(classOverridesObj, "classInfo"));
        assertEquals(propertySequence, getClassOverridesField(classOverridesObj, "properties"));
        assertEquals(methodsSequence, getClassOverridesField(classOverridesObj, "methods"));
        assertEquals(eventsSequence, getClassOverridesField(classOverridesObj, "events"));
        assertEquals(fieldsSequence, getClassOverridesField(classOverridesObj, "fields"));
        assertEquals(importsSequence, getClassOverridesField(classOverridesObj, "imports"));
    }

    @Test
    public void test_clone_onCall_returnsClassOverrides() throws Exception {

        // Arrange
        Structure classStructure = new Structure(new Symbol[]{ }, new Object[]{ });
        Sequence propertySequence = new Sequence();
        Sequence methodsSequence = new Sequence();
        Sequence eventsSequence = new Sequence();
        Sequence fieldsSequence = new Sequence();
        Sequence importsSequence = new Sequence();

        Object[] values = new Object[]
                {
                        classStructure, propertySequence, methodsSequence, eventsSequence, fieldsSequence, importsSequence
                };

        ClassOverrides classOverridesObj  = getClassOverridesObj(values);

        // Act
        Object actualResult = classOverridesObj.clone();

        // Assert
        assertTrue(actualResult instanceof ClassOverrides);
        assertEquals(classStructure, getClassOverridesField(classOverridesObj, "classInfo"));
        assertEquals(propertySequence, getClassOverridesField(classOverridesObj, "properties"));
        assertEquals(methodsSequence, getClassOverridesField(classOverridesObj, "methods"));
        assertEquals(eventsSequence, getClassOverridesField(classOverridesObj, "events"));
        assertEquals(fieldsSequence, getClassOverridesField(classOverridesObj, "fields"));
        assertEquals(importsSequence, getClassOverridesField(classOverridesObj, "imports"));
    }

    @Test
    public void test_main_onCall_returnsClassOverrides() throws Exception {

        // Arrange
        String[] args = new String[]{};
        Structure classStructure = new Structure(new Symbol[]{ }, new Object[]{ });
        Sequence propertySequence = new Sequence();
        Sequence methodsSequence = new Sequence();
        Sequence eventsSequence = new Sequence();
        Sequence fieldsSequence = new Sequence();
        Sequence importsSequence = new Sequence();

        Object[] values = new Object[]
                {
                        classStructure, propertySequence, methodsSequence, eventsSequence, fieldsSequence, importsSequence
                };

        ClassOverrides classOverridesObj  = getClassOverridesObj(values);

        // Act
        classOverridesObj.main(args);

        // Assert
        assertEquals(classStructure, getClassOverridesField(classOverridesObj, "classInfo"));
        assertEquals(propertySequence, getClassOverridesField(classOverridesObj, "properties"));
        assertEquals(methodsSequence, getClassOverridesField(classOverridesObj, "methods"));
        assertEquals(eventsSequence, getClassOverridesField(classOverridesObj, "events"));
        assertEquals(fieldsSequence, getClassOverridesField(classOverridesObj, "fields"));
        assertEquals(importsSequence, getClassOverridesField(classOverridesObj, "imports"));
    }

    @Test
    public void test_hasMoreElements_SignatureContainsModifierToken_returnsTrue() throws Exception {

        // Arrange
        int modifier = 1;
        Sequence s = new Sequence();
        String signature = "publicMethodName";
        Symbol attrName = OverrideSymbols.INTERFACE_;
        Symbol slotName = OverrideSymbols.METHOD_NAME_;
        Symbol slotValue = Symbol.intern("SetPropertyValue");

        s.add(new Structure( new Symbol[]{ attrName }, new Object[]{ slotValue } ));

        ClassOverrides classOverridesObj = initializeClassOverridesGetterMethods(attrName, slotName, slotValue, signature);
        ClassOverrides.OverrideMethodsEnumerator overrideMethodsEnumerator = classOverridesObj.new OverrideMethodsEnumerator(s, attrName, modifier);

        // Act
        boolean actualResult = overrideMethodsEnumerator.hasMoreElements();

        // Assert
        assertTrue(actualResult);
    }

    @Test
    public void test_hasMoreElements_SignatureNotContainsModifierToken_returnsFalse() throws Exception {

        // Arrange
        int modifier = 1;
        Sequence s = new Sequence();
        String signature = "MethodName";
        Symbol attrName = OverrideSymbols.INTERFACE_;
        Symbol slotName = OverrideSymbols.METHOD_NAME_;
        Symbol slotValue = Symbol.intern("SetPropertyValue");

        s.add(new Structure( new Symbol[]{ attrName }, new Object[]{ slotValue } ));

        ClassOverrides classOverridesObj = initializeClassOverridesGetterMethods(attrName, slotName, slotValue, signature);
        ClassOverrides.OverrideMethodsEnumerator overrideMethodsEnumerator = classOverridesObj.new OverrideMethodsEnumerator(s, attrName, modifier);

        // Act
        boolean actualResult = overrideMethodsEnumerator.hasMoreElements();

        // Assert
        assertFalse(actualResult);
    }

    @Test
    public void test_hasMoreElements_zeroModifierIndexNullModifierToken_returnsTrue() throws Exception {

        // Arrange
        int modifier = 0;
        Sequence s = new Sequence();
        String signature = "MethodName";
        Symbol attrName = OverrideSymbols.INTERFACE_;
        Symbol slotName = OverrideSymbols.METHOD_NAME_;
        Symbol slotValue = Symbol.intern("SetPropertyValue");

        s.add(new Structure( new Symbol[]{ attrName }, new Object[]{ slotValue } ));

        ClassOverrides classOverridesObj = initializeClassOverridesGetterMethods(attrName, slotName, slotValue, signature);
        ClassOverrides.OverrideMethodsEnumerator overrideMethodsEnumerator = classOverridesObj.new OverrideMethodsEnumerator(s, attrName, modifier);

        // Act
        boolean actualResult = overrideMethodsEnumerator.hasMoreElements();

        // Assert
        assertTrue(actualResult);
        assertEquals(slotValue, overrideMethodsEnumerator.nextElement());
    }

    @Test (expected = RuntimeException.class)
    public void test_getMethodNameFromSignature_notParseMethodNameFromSignature_throwsRuntimeException() throws Exception {

        // Arrange
        String signature = "public \t\n\r\fB";

        // Act
        Whitebox.invokeMethod(classOverrides, "getMethodNameFromSignature", signature);
    }

    @Test
    public void test_getMethodNameFromSignature_tokenContainsMethodName_returnsMethodName() throws Exception {

        // Arrange
        String signature = "test \t\n\r\fSetMethodName";

        // Act
        String actualResult = Whitebox.invokeMethod(classOverrides, "getMethodNameFromSignature", signature);

        // Assert
        assertEquals("SetMethodName", actualResult);
    }

    @Test
    public void test_getProperties_onCall_returnsOverrideEnumerator() throws Exception {

        // Arrange
        Sequence propertySeq = new Sequence();
        propertySeq.add("ExpectedResult");
        Object[] values = new Object[]
                { new Structure(), propertySeq, new Sequence(), new Sequence(), new Sequence(), new Sequence() };
        ClassOverrides classOverridesObj = getClassOverridesObj(values);

        // Act
        Enumeration actualResult = classOverridesObj.getProperties();

        // Assert
        assertTrue(actualResult instanceof ClassOverrides.OverrideEnumerator);
        assertEquals(OverrideSymbols.PROPERTY_NAME_, ((ClassOverrides.OverrideEnumerator) actualResult).attrName);
        assertEquals("ExpectedResult", ((ClassOverrides.OverrideEnumerator) actualResult).seqEnum.nextElement());
    }

    @Test
    public void test_getMethods_onCall_returnsOverrideEnumerator() throws Exception {

        // Arrange
        Sequence methodSeq = new Sequence();
        methodSeq.add("ExpectedResult");
        Object[] values = new Object[]
                { new Structure(), new Sequence(), methodSeq, new Sequence(), new Sequence(), new Sequence() };
        ClassOverrides classOverridesObj = getClassOverridesObj(values);

        // Act
        Enumeration actualResult = classOverridesObj.getMethods();

        // Assert
        assertTrue(actualResult instanceof ClassOverrides.OverrideEnumerator);
        assertEquals(OverrideSymbols.METHOD_NAME_, ((ClassOverrides.OverrideEnumerator) actualResult).attrName);
        assertEquals("ExpectedResult", ((ClassOverrides.OverrideEnumerator) actualResult).seqEnum.nextElement());
    }

    @Test
    public void test_getEvents_onCall_returnsOverrideEnumerator() throws Exception {

        // Arrange
        Sequence eventSeq = new Sequence();
        eventSeq.add("ExpectedResult");
        Object[] values = new Object[]
                { new Structure(), new Sequence(), new Sequence(), eventSeq, new Sequence(), new Sequence() };
        ClassOverrides classOverridesObj = getClassOverridesObj(values);

        // Act
        Enumeration actualResult = classOverridesObj.getEvents();

        // Assert
        assertTrue(actualResult instanceof ClassOverrides.OverrideEnumerator);
        assertEquals(OverrideSymbols.EVENT_NAME_, ((ClassOverrides.OverrideEnumerator) actualResult).attrName);
        assertEquals("ExpectedResult", ((ClassOverrides.OverrideEnumerator) actualResult).seqEnum.nextElement());
    }

    @Test
    public void test_getFields_onCall_returnsOverrideEnumerator() throws Exception {

        // Arrange
        Sequence fieldSeq = new Sequence();
        fieldSeq.add("ExpectedResult");
        Object[] values = new Object[]
                { new Structure(), new Sequence(), new Sequence(), new Sequence(), fieldSeq, new Sequence() };
        ClassOverrides classOverridesObj = getClassOverridesObj(values);

        // Act
        Enumeration actualResult = classOverridesObj.getFields();

        // Assert
        assertTrue(actualResult instanceof ClassOverrides.OverrideEnumerator);
        assertEquals(OverrideSymbols.FIELD_NAME_, ((ClassOverrides.OverrideEnumerator) actualResult).attrName);
        assertEquals("ExpectedResult", ((ClassOverrides.OverrideEnumerator) actualResult).seqEnum.nextElement());
    }

    @Test
    public void test_getImports_onCall_returnsOverrideEnumerator() throws Exception {

        // Arrange
        Sequence importsSeq = new Sequence();
        importsSeq.add("ExpectedResult");
        Object[] values = new Object[]
                { new Structure(), new Sequence(), new Sequence(), new Sequence(), new Sequence(), importsSeq };
        ClassOverrides classOverridesObj = getClassOverridesObj(values);

        // Act
        Enumeration actualResult = classOverridesObj.getImports();

        // Assert
        assertTrue(actualResult instanceof ClassOverrides.OverrideEnumerator);
        assertEquals(OverrideSymbols.IMPORT_NAME_, ((ClassOverrides.OverrideEnumerator) actualResult).attrName);
        assertEquals("ExpectedResult", ((ClassOverrides.OverrideEnumerator) actualResult).seqEnum.nextElement());
        assertEquals(1, classOverridesObj.getImportsCount());
    }
}
