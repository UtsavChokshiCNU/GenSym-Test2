package com.gensym.jgi;

import com.gensym.classes.Definition;
import com.gensym.classes.Item;
import com.gensym.jgi.download.ClassGenerationHelper;
import com.gensym.jgi.download.G2AccessStub;
import com.gensym.util.*;
import org.mockito.Matchers;

import java.io.PrintWriter;
import java.io.StringWriter;
import java.lang.reflect.Method;
import java.lang.reflect.Modifier;
import java.util.Hashtable;
import java.util.Vector;

import static com.gensym.helpers.ObjectsFactory.anyString;
import static org.mockito.Matchers.any;
import static org.powermock.api.mockito.PowerMockito.mock;
import static org.powermock.api.mockito.PowerMockito.when;

public class G2JavaStubInterfaceGeneratorTestHelper extends ClassGenerationHelper {
    protected static String adapterPackageName = "g2proxyadapter";
    protected static String g2ProxyVarName = "g2InterfaceProxy";
    protected static Class[] constructorParams = new Class[]{ G2JavaStubController.class, G2Access.class, Item.class };

    private static Hashtable returnTypeConversionTable = new Hashtable(10);
    private static Hashtable typeConversionTable = new Hashtable(10);

    private PrintWriter output;
    private Vector generatedSymbols;

    protected boolean getDefinitionThrowsException;
    protected G2JavaStubInterfaceGenerator sut;
    protected String adapterClassName;
    protected StringWriter outputStringWriter;
    protected Vector interfacesToImplement;

    static {
        returnTypeConversionTable.put(Integer.TYPE, "(int)((Integer)retval).intValue();");
        returnTypeConversionTable.put(Double.TYPE, "(double)((Double)retval).doubleValue();");
        returnTypeConversionTable.put(Float.TYPE, "(float)((Float)retval).floatValue();");
        returnTypeConversionTable.put(Short.TYPE, "(Short)((Short)retval).shortValue();");
        returnTypeConversionTable.put(Long.TYPE, "(long)((Long)retval).longValue();");
        returnTypeConversionTable.put(Byte.TYPE, "(byte)((Byte)retval).byteValue();");
        returnTypeConversionTable.put(Boolean.TYPE, "(boolean)((Boolean)retval).booleanValue();");
        typeConversionTable.put(Integer.TYPE, "new Integer(");
        typeConversionTable.put(Double.TYPE, "new Double(");
        typeConversionTable.put(Float.TYPE, "new Float(");
        typeConversionTable.put(Short.TYPE, "new Short(");
        typeConversionTable.put(Long.TYPE, "new Long(");
        typeConversionTable.put(Byte.TYPE, "new Byte(");
        typeConversionTable.put(Boolean.TYPE, "new Boolean(");
    }

    protected String anyMultiLineString() {
        iprintln("Line 1");
        iprintln("Line 2");
        iprintln("Line 3");

        return this.testStream.toString();
    }

    protected DownLoad createDownLoad(Class adapterClass) throws ClassNotFoundException {
        DownLoad downloader = mock(DownLoad.class);
        when(downloader.lookupClass(Matchers.anyString())).thenReturn(adapterClass);
        return downloader;
    }

    protected void createSut() {
        this.sut = new G2JavaStubInterfaceGenerator(this.interfacesToImplement, this.adapterClassName);
    }

    protected void emitMethodAdapterCall(String javaG2MethodName) {
        println("controller." +
                G2JavaStubController.callG2ProxyFromJava_MethodName + "(");
        iprintln("    context, " + javaG2MethodName + ", new Object[] {" + g2ProxyVarName + ",");
    }

    protected String expectedEmittedClass() {
        expectedEmittedHeader();

        iprint("public class " + adapterClassName + " implements java.io.Serializable");
        for (int i = 0; i < interfacesToImplement.size(); i++) {
            String interfaceName = ((Class) interfacesToImplement.elementAt(i)).getName();
            iprint("," + interfaceName);
        }
        iprintln("{");
        iprintln("");
        increaseIndent(2);

        // Fields
        iprintln("");
        iprintln("static final long serialVersionUID = -441189241920989898L;");
        iprintln("private G2JavaStubController controller;");
        iprintln("private Item " + g2ProxyVarName + ";");
        iprintln("private G2Access context;");
        iprintln("");

        // Constructor
        iprintln("// Do not use, here due to JIT problems");
        iprintln("public " + adapterClassName + "() {}");
        iprintln("");

        iprintln("public " + adapterClassName +
                "(G2JavaStubController controller, G2Access context, Item g2Proxy) { ");
        increaseIndent(2);
        iprintln("this.controller = controller;");
        iprintln("this." + g2ProxyVarName + " = g2Proxy;");
        iprintln("this.context = context;");
        decreaseIndent(2);
        iprintln("}");

        // Interface implementation
        expectedEmittedImplementation();
        iprintln("");
        decreaseIndent(2);
        iprintln("}");

        return this.testStream.toString();
    }

    protected String expectedEmittedHeader() {
        iprintln("package " + adapterPackageName + ";");
        iprintln("");
        iprintln("import com.gensym.util.*;");
        iprintln("import com.gensym.jgi.*;");
        iprintln("import com.gensym.classes.Item;");
        iprintln("");

        return this.testStream.toString();
    }

    private String expectedEmittedImplementation() {
        Vector generatedMethods = new Vector(41);
        for (int i = 0; i < interfacesToImplement.size(); i++) {
            Class interfaceCls = (Class) interfacesToImplement.elementAt(i);
            Method[] methods = interfaceCls.getMethods();
            this.generatedSymbols = new Vector();
            for (int y = 0; y < methods.length; y++) {
                Method method = methods[y];
                if (!isMethodConflict(generatedMethods, method)) {
                    iprintln("");
                    generateWrapperMethod(method);
                    generatedMethods.addElement(method);
                }
            }
        }

        return this.testStream.toString();
    }

    protected void generateWrapperMethod(Method m) {

        Class[] exceptionTypes = m.getExceptionTypes();
        String name = m.getName();
        Class[] parameterTypes = m.getParameterTypes();
        Class returnType = m.getReturnType();
        int modifiers = m.getModifiers() & ~(Modifier.ABSTRACT);

        if (Modifier.isStatic(modifiers)) {
            return;
        }

        Symbol g2MethodName = G2ClassTranslator.createG2NameFromJavaName(name);
        String javaG2MethodName = g2MethodName.toString().replace('-', '_') + "_";
        if (!generatedSymbols.contains(javaG2MethodName)) {
            iprintln("private static Symbol " + javaG2MethodName + " = Symbol.intern(\"" + g2MethodName + "\");");
            generatedSymbols.addElement(javaG2MethodName);
        }
        iprintln("");
        iprint(Modifier.toString(modifiers));
        print(" " + getJavaTypeString(returnType));
        print(" " + name + " (");

        for (int i = 0; i < parameterTypes.length; i++) {
            if (i > 0) {
                print(",");
            }
            print(getJavaTypeString(parameterTypes[i]) + " arg" + i);
        }

        if (exceptionTypes.length > 0) {
            println(")");
            for (int i = 0; i < exceptionTypes.length; i++) {
                if (i == 0) {
                    iprint(" throws ");
                }
                if (i > 0) {
                    print(",");
                }
                print(exceptionTypes[i].getName());
            }
            println(" {");
        } else {
            println(") {");
        }
        increaseIndent(2);

        iprintln("try {");
        increaseIndent(2);

        for (int i = 0; i < parameterTypes.length; i++) {
            if (parameterTypes[i].isPrimitive())
                iprintln("Object g2arg" + i + "= " + typeConversionTable.get(parameterTypes[i]) + "arg" + i + ");");
            else
                iprintln("Object g2arg" + i + "= arg" + i + ";");
        }

        // The wrapper call
        if (!returnType.getName().equals("void"))
            iprint("Object retval =");
        else
            iprint("");

        emitMethodAdapterCall(javaG2MethodName);

        for (int i = 0; i < parameterTypes.length; i++) {
            if (i > 0) {
                print(",");
            }
            print("g2arg" + i);
        }

        println("});");

        if (!returnType.getName().equals("void")) {
            if (!returnType.isPrimitive()) {
                iprintln("return (" + getJavaTypeString(returnType) + ")retval;");
            } else
                iprintln("return " + returnTypeConversionTable.get(returnType));
        }

        decreaseIndent(2);
        iprintln("} catch (G2AccessException e) {");
        increaseIndent(2);
        iprintln("throw new RuntimeException(e.toString());");
        decreaseIndent(2);
        iprintln("}");
        decreaseIndent(2);

        iprintln("}");

    }

    protected String getJavaTypeString(Class clazz) {
        String returnType = clazz.getName();
        if (returnType.endsWith(";")) {
            returnType = returnType.substring(0, returnType.lastIndexOf(";"));
            while (returnType.startsWith("["))
                returnType = returnType.substring(1) + "[]";

            if (returnType.startsWith("L"))
                returnType = returnType.substring(1);
        }

        return returnType;
    }

    protected void initializeParameters() {
        this.adapterClassName = anyString();
        this.getDefinitionThrowsException = false;
        this.interfacesToImplement = new Vector();
        this.interfacesToImplement.add(G2JavaStubInterfaceGeneratorTestHelperInterfaceA.class);
        this.interfacesToImplement.add(G2JavaStubInterfaceGeneratorTestHelperInterfaceB.class);
    }

    protected boolean isMethodConflict(Vector otherMethods, Method method) {
        boolean conflict;
        Class[] methodParamTypes = method.getParameterTypes();
        String methodName = method.getName();
        for (int i = 0; i < otherMethods.size(); i++) {
            Method otherMethod = (Method) otherMethods.elementAt(i);
            if (methodName.equals(otherMethod.getName())) {
                Class[] otherMethodParamTypes = otherMethod.getParameterTypes();
                if (methodParamTypes.length == otherMethodParamTypes.length) {
                    conflict = true;
                    for (int y = 0; y < methodParamTypes.length; y++)
                        for (int z = 0; z < otherMethodParamTypes.length; z++)
                            if (methodParamTypes[y] != otherMethodParamTypes[z])
                                conflict = false;
                    if (conflict) {
                        return true;
                    }
                }
            }
        }

        return false;
    }

    protected void setClassManager(G2AccessStub context) throws G2AccessException {
        Definition definition = mock(Definition.class);
        when(definition.getContainingModule()).thenReturn(Symbol.intern("com.gensym.jgi"));

        ClassManager classManager = mock(ClassManager.class);
        if (this.getDefinitionThrowsException == false) {
            when(classManager.getDefinition(any(Symbol.class))).thenReturn(definition);
        } else {
            when(classManager.getDefinition(any(Symbol.class))).thenThrow(new JavaClassCompilerException("Failed to get definition."));
        }

        context.setClassManager(classManager);
    }

    protected void setOutput() {
        this.outputStringWriter = new StringWriter();
        this.output = new PrintWriter(outputStringWriter, true);
        this.sut.setOutput(this.output);
    }

    protected void setSystemProperties() {
        System.setProperty("com.gensym.class.user.repository", anyString());
        System.setProperty("com.gensym.class.user.package", "com.gensym.classes.G2Definition");
        System.setProperty("file.separator", "\\");
    }
}
