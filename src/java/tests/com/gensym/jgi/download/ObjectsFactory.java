package com.gensym.jgi.download;

import com.gensym.types.G2Type;
import com.gensym.util.Sequence;
import com.gensym.util.Structure;
import com.gensym.util.Symbol;
import org.mockito.Matchers;
import org.mockito.invocation.InvocationOnMock;
import org.mockito.stubbing.Answer;

import static com.gensym.helpers.ObjectsFactory.anyString;
import static com.gensym.helpers.ObjectsFactory.anyStringsSequence;
import static com.gensym.jgi.download.ExtendedTypeSymbols.*;
import static com.gensym.util.symbol.G2TypeSymbols.*;
import static com.gensym.util.symbol.OverrideSymbols.*;
import static org.mockito.Matchers.anyBoolean;
import static org.powermock.api.mockito.PowerMockito.*;

public class ObjectsFactory {
    private static int SamplesCount = 10;

    protected static final Symbol[] knownG2Types = new Symbol[]{
            ITEM_OR_VALUE_,
            VALUE_,
            SEQUENCE_,
            STRUCTURE_,
            TRUTH_VALUE_,
            QUANTITY_,
            INTEGER_,
            FLOAT_,
            TEXT_,
            SYMBOL_,
            TRUTH_VALUE_OR_NULL_,
            INTEGER_OR_NULL_,
            FLOAT_OR_NULL_
    };

    public static ClassOverrides anyClassOverrides() throws MalformedOverridesException {
        Structure overrides = new Structure();
        createClassOverrideFields(overrides);
        createClassOverrideProperties(overrides);
        createClassOverrideMethods(overrides);
        createClassOverrideEvents(overrides);
        createOverridesClassInfo( overrides);

        return new ClassOverrides(overrides);
    }

    private static void createClassOverrideEvents(Structure overrides) {
        Sequence events = com.gensym.helpers.ObjectsFactory.anyStructuresSequence();
        for (int idx = 0; idx < events.size(); idx++) {
            ((Structure)events.elementAt(idx)).setAttributeValue(EVENT_NAME_, Symbol.intern(anyString()));
            ((Structure)events.elementAt(idx)).setAttributeValue(ADD_LISTENER_INTERFACE_, anyString());
            ((Structure)events.elementAt(idx)).setAttributeValue(ADD_LISTENER_IMPLEMENTATION_, anyString());
            ((Structure)events.elementAt(idx)).setAttributeValue(REMOVE_LISTENER_INTERFACE_, anyString());
            ((Structure)events.elementAt(idx)).setAttributeValue(REMOVE_LISTENER_IMPLEMENTATION_, anyString());
        }

        overrides.setAttributeValue(EVENTS_, events);
    }

    private static void createClassOverrideFields(Structure overrides) {
        Sequence fields = com.gensym.helpers.ObjectsFactory.anyStructuresSequence();
        overrides.setAttributeValue(FIELDS_, fields);
    }

    private static void createClassOverrideMethods(Structure overrides) {
        Sequence methods = com.gensym.helpers.ObjectsFactory.anyStructuresSequence();
        for (int idx = 0; idx < methods.size(); idx++) {
            ((Structure)methods.elementAt(idx)).setAttributeValue(METHOD_NAME_, Symbol.intern(anyString()));

            String interfaceSignature = anyString() + " " + anyString() + "(" + anyString() + " " + anyString() + ", " + anyString() + " " + anyString() + ", " + anyString() + " " + anyString() + ")";
            ((Structure)methods.elementAt(idx)).setAttributeValue(INTERFACE_, interfaceSignature);

            String methodImplementation = "\t// Method Body Here " + anyString() + "\n";
            ((Structure)methods.elementAt(idx)).setAttributeValue(IMPLEMENTATION_, methodImplementation);
        }

        overrides.setAttributeValue(METHODS_, methods);
    }

    public static Symbol[] anyKnownG2TypesArray() {
        Symbol[] array = new Symbol[SamplesCount];
        System.arraycopy(knownG2Types, 0, array, 0, SamplesCount);
        return array;
    }

    public static G2Type anyG2Type() {
        return new G2Type() {
        };
    }

    public static G2Type[] anyG2TypesArray() {
        G2Type[] array = new G2Type[SamplesCount];

        for (int idx = 0; idx < SamplesCount; idx++) {
            array[idx] = ObjectsFactory.anyG2Type();
        }

        return array;
    }

    public static MethodInfo[] anyMethodInfoArray() {
        MethodInfo[] array = new MethodInfo[SamplesCount];

        for (int idx = 0; idx < SamplesCount; idx++) {
            array[idx] = anyMethodInfo();
        }

        return array;
    }

    public static MethodInfo anyMethodInfo() {
        return mock(MethodInfo.class);
    }

    public static void makeSomeMethodInfoAsActive(MethodInfo[] methodInfoArray) {
        int activeMethodInfoCount = 3;
        for (int idx = 0; idx < activeMethodInfoCount; idx++) {
            MethodInfo methodInfo = methodInfoArray[idx];
            when(methodInfo.isActive()).thenReturn(true);
            when(methodInfo.generateRPCDeclarationName()).thenReturn(anyString());
            when(methodInfo.generateMethodInterface(Matchers.any(ClassGenerationContext.class), anyBoolean(), anyBoolean()))
                    .thenReturn(anyString());
            when(methodInfo.generateInterfaceComment()).thenReturn(anyString());
            methodInfo.G2MethodName = Symbol.intern(anyString());
        }

        mockStatic(MethodInfo.class, new Answer() {
            @Override
            public Object answer(InvocationOnMock invocation) throws Throwable {
                Object[] arguments = invocation.getArguments();
                if (arguments.length == 1 && arguments[0] instanceof String) {
                    return anyStringsSequence();
                }

                return null;
            }
        });
    }

    // -- Helper Methods --

    private static void createOverridesClassInfo(Structure overrides) {
        Sequence interfaces = com.gensym.helpers.ObjectsFactory.anyStringsSequence();

        Structure classInfo = new Structure();
        classInfo.setAttributeValue(INTERFACES_, interfaces);

        overrides.setAttributeValue(CLASS_INFO_, classInfo);
    }

    private static void createClassOverrideProperties(Structure overrides) {
        Sequence properties = new Sequence();
        for (int idx = 0; idx < SamplesCount; idx++) {
            properties.addElement(createPropertyStructure());
        }

        overrides.setAttributeValue(PROPERTIES_, properties);
    }

    private static Structure createPropertyStructure() {
        Structure property = new Structure();
        property.setAttributeValue(PROPERTY_NAME_, Symbol.intern(anyString()));
        property.setAttributeValue(GETTER_INTERFACE_, "public " + anyString() + " get" + anyString() + "()");
        property.setAttributeValue(SETTER_INTERFACE_, "public void set" + anyString() + "()");
        property.setAttributeValue(GETTER_IMPLEMENTATION_, anyString());
        property.setAttributeValue(SETTER_IMPLEMENTATION_, anyString());
        return property;
    }
}
