package com.gensym.jgi;

import com.gensym.util.*;

import java.lang.reflect.Constructor;
import java.lang.reflect.Member;
import java.lang.reflect.Method;
import java.lang.reflect.Modifier;
import java.util.Hashtable;

public class BeanInfoPropertiesHelper {
    private static final Symbol jgiG2CallRpcName = Symbol.intern("JGI-CALL-JAVA-PROXY-METHOD");
    private static final Symbol jgiG2CallStaticRpcName = Symbol.intern("JGI-CALL-JAVA-PROXY-STATIC-METHOD");
    private static final Symbol jgiG2CallG2ItemListenerRpcName = Symbol.intern("JGI-CALL-JAVA-PROXY-G2ITEM-LISTENER-METHOD");
    private static final Symbol jgiG2FullDisposeMethodName = Symbol.intern("JGI-JAVA-PROXY::DISPOSE");
    private static final Symbol jgiG2DisposeMethodName = Symbol.intern("DISPOSE");
    private static final Symbol METHOD_NAME_ = Symbol.intern("METHOD_NAME");
    private static final Symbol METHOD_TEXT_ = Symbol.intern("METHOD_TEXT");
    private static final Symbol METHOD_DECLARATION_ = Symbol.intern("METHOD_DECLARATION");
    private static final Symbol STATIC_DEFINITION_ = Symbol.intern("STATIC_DEFINITION");
    private static final Symbol JAVA_PARAMETER_TYPES_ = Symbol.intern("JAVA_PARAMETER_TYPES");

    private static final String
            ROOT_G2_EVENT_LISTENER_CLASS_NAME = "com.gensym.classes.modules.g2evliss.G2EventListener",
            ROOT_G2_EVENT_OBJECT_CLASS_NAME = "com.gensym.classes.modules.g2evliss.G2EventObject";

    private static final String proxyStaticRelateText = "conclude that interface is the-jgi-interface-of ret_val;";
    private static final String proxyRelateText = "conclude that the gsi-interface that is the-jgi-interface-of self is the-jgi-interface-of ret_val;";

    public Sequence expectedG2Stubs(Class beanClass, Symbol g2ClassName, boolean recurse) throws NtwIllegalArgumentException, ClassNotFoundException {
        Class parameterClasses[];
        Class returnClass;
        boolean isBadMethod;
        String g2MangledClassName = g2ClassName.toString();

        boolean isG2EventListenerClass = isClassInstanceOf(beanClass, ROOT_G2_EVENT_LISTENER_CLASS_NAME);

        Method javaMethods[] = beanClass.getMethods();
        Hashtable methodParamsTable = buildMethodParamConflicts(javaMethods);

        Symbol[] keys = new Symbol[5];
        Object[] values = new Object[5];
        Sequence returnVal = new Sequence();
        for (Method javaMethod : javaMethods)
            if (recurse || (!recurse && (javaMethod.getDeclaringClass()) == beanClass)) {
                String javaMethodName = javaMethod.getName();
                Symbol methodNameSymbol = G2ClassTranslator.createG2NameFromJavaName(javaMethodName);
                String methodName = methodNameSymbol.toString();
                methodName = G2ClassTranslator.checkAndReMapAttributeNames(methodName);
                methodNameSymbol = Symbol.intern(methodName.toUpperCase());

                if (!methodName.equals("<CLINIT>")) {
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

                    StringBuilder argumentsText = new StringBuilder();
                    StringBuilder parametersText = new StringBuilder();
                    StringBuilder nonTypedParametersText = new StringBuilder();
                    Sequence parameterTypesTextSeq = new Sequence(parameterClasses.length);
                    isBadMethod = false;

                    getParameters(beanClass, argumentsText, parameterClasses, g2MangledClassName, parametersText, nonTypedParametersText, parameterTypesTextSeq);

                    boolean isG2EventObjectMethod =
                            (isG2EventListenerClass &&
                                    parameterClasses.length == 1 &&
                                    isClassInstanceOf(parameterClasses[0], ROOT_G2_EVENT_OBJECT_CLASS_NAME));

                    returnClass = javaMethod.getReturnType();
                    boolean returnTypeIsProxy = false;

                    String returnType = getReturnType(beanClass, returnClass, g2MangledClassName);

                    String g2MethodDeclaration;
                    String methodText = "{ G2 Stub for Java " + staticMethod + " Method \n " +
                            javaMethod.toString() + "}\n\n" +
                            methodName + (isStatic ?
                            "( self: class " + g2MangledClassName + "_definition, interface : CLASS OBJECT" :
                            "( self: class " + g2MangledClassName);

                    if (methodParamConflict) {
                        g2MethodDeclaration = methodText + parametersText;
                        methodText = methodText + nonTypedParametersText;
                    } else {
                        methodText = methodText + parametersText;
                        g2MethodDeclaration = methodText;
                    }

                    methodText = methodText + " ) = ( " + returnType + " )\n";
                    g2MethodDeclaration = g2MethodDeclaration + " ) = ( " + returnType + " )\n";

                    String callText = getCallText(javaMethod, methodParamConflict, isStatic, isG2EventObjectMethod);
                    String relateText = getRelateText(isStatic);
                    methodText = getMethodText(parameterClasses, methodNameSymbol, returnTypeIsProxy, returnType, methodText, callText, relateText, argumentsText);

                    if (isBadMethod) {
                        methodText = "BAD-" + methodName +
                                "()=() begin end \n { ** AN ERROR WAS FOUND DURING STUB GENERATION **\n" +
                                methodText + "\n }";
                    }

                    returnVal.addElement(createStructure(keys, values, returnVal, methodNameSymbol, includeThisMethod, isStatic, parameterTypesTextSeq, g2MethodDeclaration, methodText));
                }
            }

        return returnVal;
    }

    protected String getReturnType(Class beanClass, Class returnClass, String g2MangledClassName) {
        String returnType;

        if (returnClass == null) {
            returnType = "";
        } else {
            returnType = G2ClassTranslator.getG2ReturnTypeFromjavaClass(returnClass);

            if (returnType == null)
                returnType = getG2Type(returnClass, beanClass, g2MangledClassName);

            if (returnType.contains("CLASS")) {
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
        return returnType;
    }

    private String getRelateText(boolean isStatic) {
        String relateText;

        if (isStatic) {
            relateText = proxyStaticRelateText;
        } else {
            relateText = proxyRelateText;
        }

        return relateText;
    }

    private String getCallText(Method java_method, boolean methodParamConflict, boolean isStatic, boolean isG2EventObjectMethod) {
        String callText;
        if (isStatic) {
            callText = "CALL " + jgiG2CallStaticRpcName.toString()
                    + "(self, interface, \"" + java_method.getName() + "\""
                    + (methodParamConflict ? "" : ",this procedure")
                    + ",args); ";
        } else {
            if (!isG2EventObjectMethod) {
                callText = "CALL " + jgiG2CallRpcName.toString()
                        + "(self, \"" + java_method.getName() + "\""
                        + (methodParamConflict ? "" : ",this procedure")
                        + ",args); ";
            } else {
                callText = "CALL " + jgiG2CallG2ItemListenerRpcName.toString()
                        + "(self, \"" + java_method.getName() + "\""
                        + (methodParamConflict ? "" : ",this procedure")
                        + ",par0, true); ";
            }
        }
        return callText;
    }

    private String getMethodText(
            Class[] parameterClasses,
            Symbol methodNameSymbol,
            boolean returnTypeIsProxy,
            String returnType,
            String methodText,
            String callText,
            String relateText,
            StringBuilder argumentsText) {
        String seqText = "   args = Sequence (" + argumentsText + ");";
        if (returnType.equals("")) {
            methodText = methodText + "\nargs: Sequence; \n" +
                    "\nBEGIN \n" +
                    seqText +
                    "\n  " + callText +    // internal dispose name also needs to get called
                    ((parameterClasses.length == 0 && methodNameSymbol.equals(jgiG2DisposeMethodName)) ?
                            "call " + jgiG2FullDisposeMethodName + "(self);\n" : "") +
                    "\nEND";
        } else {
            methodText = methodText +
                    "\nret_val : " + returnType +
                    ";\nargs: Sequence; \nBEGIN \n" +
                    seqText +
                    " \n " +
                    " \n  ret_val = " + callText +
                    (returnTypeIsProxy ? relateText : "") +
                    "\n return ret_val; \nEND";
        }
        return methodText;
    }

    private Structure createStructure(Symbol[] keys, Object[] values, Sequence ret_val, Symbol methodNameSymbol, boolean includeThisMethod, boolean isStatic, Sequence parameterTypesTextSeq, String g2MethodDeclaration, String methodText) throws NtwIllegalArgumentException {
        keys[0] = METHOD_NAME_;
        values[0] = methodNameSymbol;
        keys[1] = METHOD_TEXT_;
        values[1] = (includeThisMethod ? methodText : "");
        keys[2] = METHOD_DECLARATION_;
        values[2] = g2MethodDeclaration;
        keys[3] = STATIC_DEFINITION_;
        values[3] = new Boolean(isStatic);
        keys[4] = JAVA_PARAMETER_TYPES_;
        values[4] = parameterTypesTextSeq;

        return new Structure(keys, values);
    }

    private void getParameters(Class beanClass, StringBuilder argumentsText, Class[] parameterClasses, String g2_mangled_class_name, StringBuilder parametersText, StringBuilder nonTypedParametersText, Sequence parameterTypesTextSeq) {
        for (int y = 0; y < parameterClasses.length; y++) {
            parameterTypesTextSeq.addElement(parameterClasses[y].getName());
            String G2_type = G2ClassTranslator.getG2TypeFromJavaClass(parameterClasses[y]);
            if (G2_type == null) {
                G2_type = getG2Type(parameterClasses[y], beanClass, g2_mangled_class_name);
            }
            String G2_par_name = "par" + (y);
            parametersText.append(",\n").append(G2_par_name).append(" : ").append(G2_type);
            nonTypedParametersText.append(",\n").append(G2_par_name).append(" : ITEM-OR-VALUE");
            if (parameterClasses.length == 1) {
                argumentsText.append(G2_par_name);
            } else {
                if (y < parameterClasses.length - 1) {
                    argumentsText.append(G2_par_name).append(",");
                } else {
                    argumentsText.append(G2_par_name);
                }
            }
        }
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
            Hashtable methodSigs = (Hashtable) methodParamConflicts.get(methodName);
            if (methodSigs == null) {
                methodSigs = new Hashtable(2);
                methodSigs.put(paramsCount, 1);
                methodParamConflicts.put(methodName, methodSigs);
            } else {
                Integer numParamsCount = (Integer) methodSigs.get(paramsCount);
                if (numParamsCount == null)
                    methodSigs.put(paramsCount, 1);
                else
                    methodSigs.put(paramsCount, numParamsCount + 1);
            }
        }

        return methodParamConflicts;
    }

    private static Class getArrayComponent(final Class java_class) {
        Class javaClass = java_class;
        while (javaClass.isArray()) {
            javaClass = javaClass.getComponentType();
        }

        return javaClass;
    }

    private static String getG2Type(Class param_class, Class thisClass, String thisG2ClassName) {
        String G2_type;

        // We know are own class, as we have created a proxy for it
        if (param_class == thisClass)
            G2_type = "CLASS " + thisG2ClassName;
        else {
            String paramType = param_class.getComponentType() == null ?
                    param_class.getName() :
                    getArrayComponent(param_class).getName() + "@[@]";

            G2_type = "CLASS " + G2ClassTranslator.createG2NameFromJavaName(paramType);

        }

        return G2_type;
    }

    private boolean isClassInstanceOf(Class lowerClass, String superClassName) throws ClassNotFoundException {
        Class superClass = Class.forName(superClassName);
        return superClass.isAssignableFrom(lowerClass);
    }
}
