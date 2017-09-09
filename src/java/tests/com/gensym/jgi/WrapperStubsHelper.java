package com.gensym.jgi;

import com.gensym.util.*;

import java.lang.reflect.Constructor;
import java.lang.reflect.Member;
import java.lang.reflect.Method;
import java.lang.reflect.Modifier;
import java.util.Hashtable;

public class WrapperStubsHelper {
    private static final Symbol METHOD_NAME_ = Symbol.intern("METHOD_NAME");
    private static final Symbol METHOD_TEXT_ = Symbol.intern("METHOD_TEXT");
    private static final Symbol METHOD_DECLARATION_ = Symbol.intern("METHOD_DECLARATION");
    private static final Symbol STATIC_DEFINITION_ = Symbol.intern("STATIC_DEFINITION");
    private static final Symbol JAVA_PARAMETER_TYPES_ = Symbol.intern("JAVA_PARAMETER_TYPES");
    private static final Symbol CLASS_INFO_ = Symbol.intern("CLASS-INFO");
    private static final Symbol IS_ABSTRACT_ = Symbol.intern("IS-ABSTRACT");

    private static final String VOID_DISPATCH_METHOD = "_t2beans-dispatch-void";
    private static final String DISPATCH_METHOD_WITH_RETURN = "_t2beans-dispatch";

    public Sequence expectedStubs(Class beanClass, Symbol g2ClassName, boolean recurse) throws NtwIllegalArgumentException {
        Class parameterClasses[];
        Class returnClass;
        String g2MangledClassName = g2ClassName.toString();
        String beanClassName = g2ClassName.getPrintValue();

        Method javaMethods[] = beanClass.getMethods();
        Hashtable methodParamsTable = buildMethodParamConflicts(javaMethods);

        Symbol[] keys = new Symbol[5];
        Object[] values = new Object[5];
        Sequence retVal = new Sequence();
        for (Method javaMethod : javaMethods)
            if (recurse || javaMethod.getDeclaringClass() == beanClass) {
                String javaMethodName = javaMethod.getName();
                Symbol g2MethodNameSymbol = G2ClassTranslator.createG2NameFromJavaName(javaMethodName);
                String g2MethodName = g2MethodNameSymbol.toString();
                g2MethodName = G2ClassTranslator.checkAndReMapAttributeNames(g2MethodName);
                g2MethodNameSymbol = Symbol.intern(g2MethodName.toUpperCase());

                if (!g2MethodName.equals("<CLINIT>")) {
                    parameterClasses = javaMethod.getParameterTypes();

                    Hashtable methodParams = (Hashtable) methodParamsTable.get(javaMethod.getName());
                    Integer numParams = parameterClasses.length;
                    Integer numParamsForThisMethodSig = (Integer) methodParams.get(numParams);
                    boolean includeThisMethod = true;
                    boolean methodParamConflict = false;
                    if (numParamsForThisMethodSig == null) {
                        includeThisMethod = false;
                    } else {
                        methodParamConflict = numParamsForThisMethodSig > 1;
                        methodParams.remove(numParams);
                    }

                    boolean isStatic = Modifier.isStatic(javaMethod.getModifiers());
                    String staticMethod = isStatic ? "STATIC" : "";

                    String g2MethodText = "{ G2 Stub for Java " + staticMethod + " Method \n " +
                            javaMethod.toString() + "}\n\n" +
                            g2MethodName + (isStatic ?
                            "( self: class " + g2MangledClassName + "_definition, interface : CLASS OBJECT" :
                            "( self: class " + beanClassName);

                    StringBuilder g2ParsText = new StringBuilder();
                    StringBuilder g2NonTypedParsText = new StringBuilder();
                    Sequence parameterTypesTextSeq = new Sequence(parameterClasses.length);

                    for (int y = 0; y < parameterClasses.length; y++) {
                        parameterTypesTextSeq.addElement(parameterClasses[y].getName());
                        String G2_type = G2ClassTranslator.getG2TypeFromJavaClass(parameterClasses[y]);
                        if (G2_type == null) {
                            G2_type = getG2Type(parameterClasses[y], beanClass, g2MangledClassName);
                        }
                        String g2ParName = "par" + (y);
                        g2ParsText.append(",\n").append(g2ParName).append(" : ").append(G2_type);
                        g2NonTypedParsText.append(",\n").append(g2ParName).append(" : ITEM-OR-VALUE");
                    }

                    returnClass = javaMethod.getReturnType();

                    String return_type;

                    if (returnClass == null)
                        return_type = "";
                    else {
                        return_type = G2ClassTranslator.getG2ReturnTypeFromjavaClass(returnClass);

                        if (return_type == null) {
                            return_type = getG2Type(returnClass, beanClass, g2MangledClassName);
                        }

                        if (return_type.contains("CLASS")) {
                            String className = returnClass.getName();
                            StringBuffer mangledClassName;
                            if (className.charAt(0) == '[') {
                                mangledClassName = new StringBuffer(className.length());
                                for (int x = 0; x < className.length(); x++) {
                                    char ch = className.charAt(x);
                                    if (ch == '[')
                                        mangledClassName.append('@');
                                    mangledClassName.append(ch);
                                }
                            }
                        }
                    }

                    String g2MethodDeclaration;
                    if (methodParamConflict) {
                        g2MethodDeclaration = g2MethodText + g2ParsText;
                        g2MethodText = g2MethodText + g2NonTypedParsText;
                    } else {
                        g2MethodText = g2MethodText + g2ParsText;
                        g2MethodDeclaration = g2MethodText;
                    }

                    g2MethodText = g2MethodText + " ) = ( " + return_type + " )\n";
                    g2MethodDeclaration = g2MethodDeclaration + " ) = ( " + return_type + " )\n";

                    int numMethodParams = parameterClasses.length;
                    StringBuilder params = new StringBuilder(numMethodParams * 4);
                    for (int m = 0; m < numMethodParams; m++)
                        params.append(", par").append(m);

                    if (return_type.equals("")) {
                        g2MethodText +=
                                "\nBEGIN\n\n    call " +
                                        VOID_DISPATCH_METHOD +
                                        "(self, the symbol " + g2MethodNameSymbol +
                                        params + ");\n\nEND";
                    } else {
                        g2MethodText +=
                                "\nret_val : " + return_type +
                                        ";\n\nBEGIN\n\n    ret_val = call " +
                                        DISPATCH_METHOD_WITH_RETURN +
                                        "(self, the symbol " + g2MethodNameSymbol +
                                        params + ");\n    return ret_val;\n\nEND";
                    }

                    Structure g2MethodInformation = createStructure(keys, values, g2MethodNameSymbol, includeThisMethod, isStatic, g2MethodText, parameterTypesTextSeq, g2MethodDeclaration);
                    retVal.addElement(g2MethodInformation);

                }
            }

        Structure classInfo = new Structure();
        classInfo.setAttributeValue(METHOD_NAME_, CLASS_INFO_);
        classInfo.setAttributeValue(IS_ABSTRACT_, new Boolean(Modifier.isAbstract(beanClass.getModifiers())));
        classInfo.setAttributeValue(METHOD_TEXT_, "");
        classInfo.setAttributeValue(METHOD_DECLARATION_, "");
        classInfo.setAttributeValue(STATIC_DEFINITION_, Boolean.TRUE);
        classInfo.setAttributeValue(JAVA_PARAMETER_TYPES_, new Sequence());
        retVal.addElement(classInfo);
        return retVal;
    }

    protected Structure createStructure(Symbol[] keys, Object[] values, Symbol g2MethodNameSymbol, boolean includeThisMethod, boolean isStatic, String g2MethodText, Sequence parameterTypesTextSeq, String g2MethodDeclaration) throws NtwIllegalArgumentException {
        keys[0] = METHOD_NAME_;
        values[0] = g2MethodNameSymbol;
        keys[1] = METHOD_TEXT_;
        values[1] = (includeThisMethod ? g2MethodText : "");
        keys[2] = METHOD_DECLARATION_;
        values[2] = g2MethodDeclaration;
        keys[3] = STATIC_DEFINITION_;
        values[3] = new Boolean(isStatic);
        keys[4] = JAVA_PARAMETER_TYPES_;
        values[4] = parameterTypesTextSeq;

        return new Structure(keys, values);
    }

    private static Hashtable buildMethodParamConflicts(Member[] methods) {
        Hashtable methodParamConflicts = new Hashtable(21);
        for (Member method : methods) {
            String methodName = method.getName();
            Class[] paramTypes;
            if (method instanceof Method)
                paramTypes = ((Method) (method)).getParameterTypes();
            else
                paramTypes = ((Constructor) (method)).getParameterTypes();
            Integer paramsCount = paramTypes.length;
            Hashtable methodSignatures = (Hashtable) methodParamConflicts.get(methodName);
            if (methodSignatures == null) {
                methodSignatures = new Hashtable(2);
                methodSignatures.put(paramsCount, 1);
                methodParamConflicts.put(methodName, methodSignatures);
            } else {
                Integer numParamsCount = (Integer) methodSignatures.get(paramsCount);
                if (numParamsCount == null)
                    methodSignatures.put(paramsCount, 1);
                else
                    methodSignatures.put(paramsCount, numParamsCount + 1);
            }
        }

        return methodParamConflicts;
    }

    private static String getG2Type(Class paramClass, Class thisClass, String thisG2ClassName) {
        String g2Type;
        if (paramClass == thisClass)
            g2Type = "CLASS " + thisG2ClassName;
        else {
            String paramType = paramClass.getComponentType() == null ?
                    paramClass.getName() :
                    getArrayComponent(paramClass).getName() + "@[@]";

            g2Type = "CLASS " + G2ClassTranslator.createG2NameFromJavaName(paramType);
        }

        return g2Type;
    }

    private static Class getArrayComponent(final Class javaClass) {
        Class javaClassLocal = javaClass;
        while (javaClassLocal.isArray()) {
            javaClassLocal = javaClassLocal.getComponentType();
        }

        return javaClassLocal;
    }
}
