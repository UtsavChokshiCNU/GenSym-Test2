package com.gensym.jgi.download;

import com.gensym.message.MessageKey;
import com.gensym.message.Resource;
import com.gensym.message.Trace;
import com.gensym.types.G2Type;
import com.gensym.util.G2ClassTranslator;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;

import java.io.ByteArrayOutputStream;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.nio.charset.Charset;
import java.util.Enumeration;
import java.util.Hashtable;
import java.util.Locale;

import static com.gensym.helpers.ObjectsFactory.anyStringsArray;
import static com.gensym.jgi.download.ClassGenerationContext.HAND_CODED_METHODS_;
import static com.gensym.jgi.download.ObjectsFactory.anyClassOverrides;
import static com.gensym.jgi.download.ObjectsFactory.anyMethodInfoArray;

public class ClassGenerationContextHelper extends ClassGenerationHelper {
    protected static final String[] JavaReservedWords = {
            "abstract", "boolean", "case", "catch", "char", "class", "const", "continue", "default", "do",
            "break", "byte", "double", "else", "extents", "final", "finally", "float", "for", "goto",
            "if", "implemenents", "import", "instanceof", "int", "interface", "long", "native",
            "new", "package", "private", "private", "public", "return", "short", "static",
            "super", "switch", "synchronized", "this", "throw", "throws", "transient", "try",
            "void", "volatile", "while"};

    protected static MessageKey traceKey = Trace.registerMessageKey("com.gensym.jgi.download.stubs", ClassGenerationContext.class);
    protected static Resource i18nTrace = Trace.getBundle("com.gensym.jgi.download.Messages", Locale.getDefault());

    private static final int DEF_TRACE_LEVEL = 5;

    protected boolean isG2EventObjectClass;
    protected boolean isG2ProxyObjectClass;
    protected boolean isInterface;
    protected ClassGenerationContext context;
    protected ClassNameMapper classNameMapper;
    protected Sequence opSignatures = new Sequence(101);
    protected String className;
    protected String javaClassName;
    protected String packageName;

    private Symbol realG2ClassForG2ProxyClass = null;

    protected static AttrInfo createAttrInfo() {
        Symbol[] attrTypes = com.gensym.jgi.download.ObjectsFactory.anyKnownG2TypesArray();
        Symbol[] attrNames = com.gensym.helpers.ObjectsFactory.anySymbolsArray();
        boolean[] systemDefined = com.gensym.helpers.ObjectsFactory.anyBooleansArray();
        boolean[] readable = com.gensym.helpers.ObjectsFactory.anyBooleansArray();
        boolean[] writable = com.gensym.helpers.ObjectsFactory.anyBooleansArray();
        boolean[] staticP = com.gensym.helpers.ObjectsFactory.anyBooleansArray();
        Symbol[] origNames = com.gensym.helpers.ObjectsFactory.anySymbolsArray();
        Symbol[] definingClasses = com.gensym.helpers.ObjectsFactory.anySymbolsArray();
        G2Type[] typeSpecifications = com.gensym.jgi.download.ObjectsFactory.anyG2TypesArray();
        Object[] initialValues = com.gensym.helpers.ObjectsFactory.anyObjectsArray();

        attrNames[1] = attrNames[0];
        origNames[1] = origNames[0];
        staticP[1] = staticP[0];

        AttrInfo attrInfo = new AttrInfo(
                attrTypes,
                attrNames,
                systemDefined,
                readable,
                writable,
                staticP,
                origNames,
                definingClasses,
                typeSpecifications,
                initialValues);
        return attrInfo;
    }

    protected String generateClass(String[] imports, String superClass, Symbol[] classesToCollect, String[] interfaces, Symbol[] classInheritancePath, AttrInfo attributes, MethodInfo[] methodInfos, Hashtable overridesInHashTable, java.util.Date date) {
        generateStaticHeader(date);
        return expectedGeneratedClass(imports, superClass, classesToCollect, interfaces, classInheritancePath, attributes, methodInfos, overridesInHashTable);
    }

    protected String expectedGeneratedClass(String[] imports, String superClass, Symbol[] classesToCollect, String[] interfaces, Symbol[] classInheritancePath, AttrInfo attributes, MethodInfo[] methodInfos, Hashtable overridesInHashTable) {
        Symbol[] attrTypes = attributes.attrTypes, attrNames = attributes.attrNames;
        boolean[] readable = attributes.readable, writable = attributes.writable, isStatic = attributes.staticP;
        G2Type[] typeDescrpns = attributes.typeSpecifications;

        if (isInterface) {
            if (StubClassLoader.isG2ClassG2EventClass(Symbol.intern(this.className)))
                isG2EventObjectClass = true;
        } else if (StubClassLoader.isG2EventClass(Symbol.intern(this.className), classInheritancePath))
            isG2EventObjectClass = true;

        isG2ProxyObjectClass = (
                (realG2ClassForG2ProxyClass =
                        StubClassLoader.getRealG2ClassForG2ProxyClass(Symbol.intern(this.className), classInheritancePath)
                ) != null);

        ClassOverrides overrides = collectInheritedOverrides(overridesInHashTable, classesToCollect);
        String[] allImports = collectAllImports(imports, overrides);
        generateDynamicHeader(allImports, superClass, interfaces, overrides);
        increaseIndent(2);
        generateFields(attributes, classInheritancePath, overrides);
        generateConstructors();
        generatePropertyAccessors(attrTypes, attrNames, readable, writable, isStatic, overrides, typeDescrpns);
        generateEventMethods(overrides);
        generateMethods(methodInfos, overridesInHashTable, false);
        decreaseIndent(2);
        endClass();

        return this.testStream.toString();
    }

    protected String generateHeader(
            String[] imports,
            String superClass,
            String[] interfaces,
            ClassOverrides overrides,
	    java.util.Date date) {
        generateStaticHeader(date);
        return generateDynamicHeader(imports, superClass, interfaces, overrides);
    }

    protected void generateClass() {
        String[] imports = anyStringsArray();
        String superClass = com.gensym.helpers.ObjectsFactory.anyString();
        Symbol[] classesToCollect = com.gensym.helpers.ObjectsFactory.anySymbolsArray();
        String[] interfaces = anyStringsArray();
        Symbol[] classInheritancePath = com.gensym.helpers.ObjectsFactory.anySymbolsArray();
        AttrInfo attributes = createAttrInfo();
        MethodInfo[] methodInfos = anyMethodInfoArray();
        Hashtable overridesInHashTable = new Hashtable();
        final java.util.Date date = new java.util.Date();

        this.context.generateClass(imports, superClass, classesToCollect, interfaces, classInheritancePath, attributes, methodInfos, overridesInHashTable, date);
        generateClass(imports, superClass, classesToCollect, interfaces, classInheritancePath, attributes, methodInfos, overridesInHashTable, date);
    }

    protected String generateEventMethods(ClassOverrides overrides) {
        Enumeration e = overrides.getEvents();
        while (e.hasMoreElements()) {
            Symbol eventName = (Symbol) e.nextElement();
            String addIntf = overrides.getAddListenerInterface(eventName);
            String removeIntf = overrides.getRemoveListenerInterface(eventName);
            iprintln("/* Overriden  - " + eventName + " Event Listeners Management */");
            if (addIntf != null && addIntf.indexOf("public") >= 0) {
                iprintln("/* Adder */");
                iprintln(overrides.getAddListenerComments(eventName));
                iprint(addIntf);
                println(";");
                recordOpInterfaceSignature(addIntf);
            }
            if (removeIntf != null && removeIntf.indexOf("public") >= 0) {
                iprintln("/* Remover */");
                iprintln(overrides.getRemoveListenerComments(eventName));
                iprint(removeIntf);
                println(";");
                recordOpInterfaceSignature(removeIntf);
            }
            println();
        }

        return this.testStream.toString();
    }

    protected final void recordOpInterfaceSignature(String interfaceName) {
        opSignatures.addElement(MethodInfo.getMethodSignatureAsSequence(interfaceName));
    }

    protected final void recordOpInterfaceSignature(Sequence interfaceName) {
        opSignatures.addElement(interfaceName);
    }

    protected String generateConstructors() {
        println();
        return this.testStream.toString();
    }

    protected void generatePropertyAccessors(Symbol[] slotTypes, Symbol[] slotNames, boolean[] readable, boolean[] writable, boolean[] isStatic, ClassOverrides overrides, G2Type[] typeSpecifications) {
        if (isG2ProxyObjectClass) {
            return;
        }

        String[] jSlotNames = new String[slotNames.length];
        String[] jSlotTypes = new String[slotNames.length];
        int[] generationFlags = new int[slotNames.length];
        for (int i = 0; i < slotNames.length; i++) {
            Trace.send(DEF_TRACE_LEVEL, traceKey, i18nTrace, "genProp", i, slotNames[i], slotTypes[i]);
            jSlotNames[i] = this.context.getJavaPropertyNameForG2Slot(slotNames[i]);
            jSlotTypes[i] = this.context.getJavaTypeNameForG2Type(slotTypes[i]);
            generationFlags[i] = (readable[i] ? ClassGenerationContext.PROPERTY_GETTER : 0) |
                    (writable[i] ? ClassGenerationContext.PROPERTY_SETTER : 0) |
                    (isStatic[i] ? ClassGenerationContext.PROPERTY_STATIC : 0);
        }

        if (overrides != null)
            writeOverriddenPropertyAccessors(overrides);

        if (!isInterface)
            generatePropertyAccessors(jSlotTypes, jSlotNames, slotNames, generationFlags, typeSpecifications);
        else
            generatePropertyAccessDeclarations(jSlotTypes, jSlotNames, slotNames, generationFlags, typeSpecifications);
    }

    protected void generatePropertyAccessors(String[] jSlotTypes,
                                             String[] jSlotNames,
                                             Symbol[] slotNames,
                                             int[] generationFlags,
                                             G2Type[] typeSpecifications) {
        throw new InternalError("Should never call ClassGenerationContext::generatePropertyAccessors");
    }

    private void generatePropertyAccessDeclarations(String[] types, String[] names, Symbol[] g2Names,
                                                    int[] generationFlags, G2Type[] typeSpecifications) {
        for (int i = 0; i < names.length; i++) {
            Symbol currentSlot_ = g2Names[i];
            String currentSlot = names[i];
            String currentType = types[i];
            boolean staticQ = (generationFlags[i] & ClassGenerationContext.PROPERTY_STATIC) != 0;
            String fieldName = G2ClassTranslator.initCap(this.context.makeFieldNameForSlot(currentSlot, staticQ));
            String slotVarName = this.context.ensureLegalJavaVariableName(currentSlot);
            boolean getterExists = (generationFlags[i] & ClassGenerationContext.PROPERTY_GETTER) != 0;
            boolean setterExists = (generationFlags[i] & ClassGenerationContext.PROPERTY_SETTER) != 0;
            G2Type type = typeSpecifications[i];
            if (fieldName.equals("Text")) {
                getterExists = setterExists = true;
                currentType = "java.lang.String";
            }
            if (getterExists) {
                String getterInterface = ("public " + currentType + " get" +
                        fieldName + "() throws G2AccessException;\n");
                Sequence intfSig = MethodInfo.getMethodSignatureAsSequence(getterInterface);
                if (!methodAlreadyDefined(intfSig)) {
                    iprintln("/**");
                    iprintln(" * Generated Property Getter for attribute -- " + currentSlot_);
                    iprint(" * @return the value of the " + currentSlot_ + " attribute of this ");
                    println(staticQ ? "class" : "item");
                    iprintln(" * @exception G2AccessException if there are any communication problems");
                    iprintln(" *");
                    if (type != null) {
                        iprintln(" * Type Specification for " + currentSlot_ + " is : ");
                        iprint(" * ");
                        type.pprint(this.printWriter, 2);
                        println("");
                    } else
                        iprintln(" * Attribute " + currentSlot_ + " has no type");
                    iprintln(" *");
                    iprintln(" */");
                    iprintln(getterInterface);
                    recordOpInterfaceSignature(intfSig);
                }
            }

            if (setterExists) {
                String setterInterface = ("public void set" + fieldName +
                        "(" + currentType + " " + slotVarName + ") throws G2AccessException;\n");
                Sequence intfSig = MethodInfo.getMethodSignatureAsSequence(setterInterface);
                if (!methodAlreadyDefined(intfSig)) {
                    iprintln("/**");
                    iprintln(" * Generated Property Setter for attribute -- " + currentSlot_);
                    iprintln(" * @param " + slotVarName + " new value to conclude for " + currentSlot_);
                    iprintln(" * @exception G2AccessException if there are any communication problems");
                    iprintln(" *              or the value does not match with the type specification");
                    iprintln(" */");

                    iprintln(setterInterface);
                    recordOpInterfaceSignature(intfSig);
                }
            }
        }
    }

    protected boolean methodAlreadyDefined(Sequence mInterfaceSig) {
        for (Enumeration opsige = opSignatures.elements(); opsige.hasMoreElements(); ) {
            if (mInterfaceSig.equals(opsige.nextElement())) {
                return true;
            }
        }

        return false;
    }

    protected void endClass() {
        iprintln("}");
    }

    protected String writeOverriddenPropertyAccessors(ClassOverrides overrides) {
        Enumeration e = overrides.getProperties();
        while (e.hasMoreElements()) {
            Symbol propName = (Symbol) e.nextElement();
            String getterText = overrides.getGetterInterface(propName);
            String setterText = overrides.getSetterInterface(propName);
            boolean outputGetter = getterText != null && getterText.indexOf("public") >= 0;
            boolean outputSetter = setterText != null && setterText.indexOf("public") >= 0;
            if (outputGetter || outputSetter)
                iprintln("/* Overriden Property - " + propName + " */");
            if (outputGetter) {
                String comments = overrides.getGetterComments(propName);
                if (comments == null)
                    comments = "/**  Property Getter for " + propName + " */";
                iprintln(comments);
                iprint(getterText);
                recordOpInterfaceSignature(getterText);
                println(";");
            }
            if (outputSetter) {
                String comments = overrides.getSetterComments(propName);
                if (comments == null)
                    comments = "/**  Property Setter for " + propName + " */";
                iprintln(comments);
                iprint(setterText);
                recordOpInterfaceSignature(setterText);
                println(";");
            }
            println();
        }

        return this.testStream.toString();
    }

    // -- Helper Methods --

    private void generateImportsHeader(String[] imports) {
        iprintln("package " + this.packageName + ";\n");
        for (String imp : imports) {
            if (imp != null && !(imp).equals("")) {
                iprintln("import " + imp + ";");
            } else {
                println();
            }
        }
    }

    private void generateStaticHeader(java.util.Date date) {
        iprintln("/*");
        iprintln(" *  Copyright (c) " + "1998 " + G2ClassTranslator.companyName + ".");
        iprintln(" *  All Rights Reserved.");
        iprintln(" *");
        iprintln(" *      " + this.javaClassName + ".java");
        iprintln(" *");
        iprintln(" *   Description: Generated Interface file. Do not edit!");
        iprintln(" *");
        iprintln(" *        Author: Gensym Corp.");
        iprintln(" *");
        iprintln(" *       Version: " + this.classNameMapper.getVersionForClass(null));
        iprintln(" *");
        iprintln(" *          Date: " + date);
        iprintln(" *");
        iprintln(" */\n\n");
    }

    private String[] generateSuperClassHeader(String[] interfaces, String javaClassName, String superClass) {
        println();
        iprint("public ");
        print(isInterface ? "interface " : "class ");
        print(javaClassName);
        if (!isInterface && !"java.lang.Object".equals(superClass)) {
            print(" extends " + superClass);
        }

        return interfaces;
    }

    private String[] generateInterfacesHeader(ClassOverrides overrides, String[] interfaceNames) {
        Sequence additionalInterfaces = overrides.getImplementedInterfaces();
        int interfacesCount = additionalInterfaces.size();
        if (isInterface && interfacesCount > 0) {
            String[] fullInterfaces;
            if (interfaceNames != null) {
                int originalInterfacesCount = interfaceNames.length;
                fullInterfaces = new String[interfacesCount + originalInterfacesCount];
                additionalInterfaces.copyInto(fullInterfaces);
                System.arraycopy(interfaceNames, 0, fullInterfaces, interfacesCount, originalInterfacesCount);
            } else {
                fullInterfaces = new String[interfacesCount];
                additionalInterfaces.copyInto(fullInterfaces);
            }

            interfaceNames = fullInterfaces;
        }

        if (interfaceNames != null) {
            if (interfaceNames.length > 0) {
                print(isInterface ? " extends " : " implements ");
            }

            for (int i = 0; i < interfaceNames.length; i++) {
                print(interfaceNames[i]);
                if (i < interfaceNames.length - 1) {
                    print(", ");
                }
            }
        }
        return interfaceNames;
    }

    protected void generateSutFields() throws MalformedOverridesException {
        AttrInfo attrInfo = createAttrInfo();
        Symbol[] classInheritancePath = com.gensym.helpers.ObjectsFactory.anySymbolsArray();
        ClassOverrides overrides = anyClassOverrides();
        this.context.generateFields(attrInfo, classInheritancePath, overrides);

        generateFields(attrInfo, classInheritancePath, overrides);
    }

    protected String generateG2EventListenerExternalInterface(final String[] imports, final String superClass, final String[] interfaces,
							      final Symbol[] classInheritancePath, final MethodInfo[] m,
							      final Hashtable overridesInhTable, final java.util.Date date
							      ) {
        ClassOverrides overrides = collectInheritedOverrides(overridesInhTable, classInheritancePath);
        String[] allImports = collectAllImports(imports, overrides);
        generateHeader(allImports, superClass, interfaces, overrides, date);
        increaseIndent(2);
        generateMethods(m, overridesInhTable, true);
        decreaseIndent(2);
        endClass();

        return this.testStream.toString();
    }

    protected String generateFields(AttrInfo attributes,
                                    Symbol[] classInheritancePath,
                                    ClassOverrides overrides) {
        String sym = ClassGenerationContext.createJavaSymbolVariableName(Symbol.intern(className));
        Trace.send(DEF_TRACE_LEVEL, traceKey, i18nTrace, "genField");
        if (!com.gensym.classes.SystemPredicate.isSystemClass(Symbol.intern(this.className)))
            iprintln("public static final Symbol " + sym + " = Symbol.intern (\"" +
                    className + "\");");
        else
            iprintln("public static final Symbol " + sym + " = com.gensym.util.symbol.G2ClassSymbols." + sym + ";");
        iprintln("static final Symbol g2ClassName = " + sym + ";");
        iprint("static final Symbol[] classInheritancePath = new Symbol[] {");
        for (int i = 0; i < classInheritancePath.length; i++) {
            print(ClassGenerationContext.createJavaSymbolVariableName(classInheritancePath[i]));
            if (i != (classInheritancePath.length - 1))
                print(", ");
        }
        println("};");
        println();

        if (isG2ProxyObjectClass) {
            iprintln("static final Symbol realG2ClassName " + " = Symbol.intern (\"" + realG2ClassForG2ProxyClass + "\");");
        } else {
            Symbol[] attrNames = attributes.attrNames;
            boolean[] staticP = attributes.staticP;
            for (int i = 0; i < attrNames.length; i++) {
                if (staticP[i]) {
                    Symbol attrName = attrNames[i];
                    iprintln("static final Symbol " + ClassGenerationContext.createJavaSymbolVariableName(attrName) + " = Symbol.intern (\"" + attrName + "\");");
                }
            }
            println();
            iprint("static final Symbol[] staticAttributes = new Symbol[] {");
            for (int i = 0; i < attrNames.length; i++) {
                if (staticP[i]) {
                    print(ClassGenerationContext.createJavaSymbolVariableName(attrNames[i]));
                    if (i != (attrNames.length - 1))
                        print(", ");
                }
            }
            println("};");
        }
        println();

        return this.testStream.toString();
    }

    protected String generatePropertyAccessors(
            String[] jSlotTypes,
            String[] jSlotNames,
            Symbol[] slotNames,
            int[] generationFlags) {
        return "No implementation yet.";
    }

    protected String generateMethods(MethodInfo[] methodInfoArray, Hashtable overridesTable, boolean generateMethodsForExternalEventListenerClass) {
        if (isG2EventObjectClass) {
            iprintln("/* " + StubClassLoader.g2EventTagInterfaceName + " support */");
            iprintln("public Class " + StubClassLoader.getExternalEventClassMethodName + "();");
            println();
        }

        if (!generateMethodsForExternalEventListenerClass) {
            ClassOverrides overrides = (ClassOverrides) overridesTable.get(Symbol.intern(this.className));
            if (overrides != null) {
                Enumeration e = overrides.getMethods(java.lang.reflect.Modifier.PUBLIC);
                while (e.hasMoreElements()) {
                    Symbol methodName = (Symbol) e.nextElement();
                    Trace.send(DEF_TRACE_LEVEL, traceKey, i18nTrace, "genMeth", methodName);
                    String ovrInterface = overrides.getMethodInterface(methodName);

                    Sequence ovrInterfaceSig = MethodInfo.getMethodSignatureAsSequence(ovrInterface);
                    opSignatures.addElement(ovrInterfaceSig);

                    iprintln("/* Overriden method - " + methodName + " */");
                    String methodComments = overrides.getMethodComments(methodName);
                    if (methodComments != null)
                        iprintln(methodComments);
                    iprint(ovrInterface);
                    println(";");
                    println();
                }
            }

            if (isG2ProxyObjectClass) {
                return this.testStream.toString();
            }

            overrides = (ClassOverrides) overridesTable.get(HAND_CODED_METHODS_);

            if (overrides != null) {
                Enumeration e = overrides.getMethods(java.lang.reflect.Modifier.PUBLIC);
                while (e.hasMoreElements()) {
                    Symbol methodName = (Symbol) e.nextElement();
                    String ovrInterface = overrides.getMethodInterface(methodName);

                    Sequence ovrInterfaceSig = MethodInfo.getMethodSignatureAsSequence(ovrInterface);
                    opSignatures.addElement(ovrInterfaceSig);

                    iprintln("/* Exported Override method - " + methodName + " */");
                    iprint(ovrInterface);
                    println(";");
                    println();
                }
            }
        }

        Sequence itemMethods = this.context.getItemMethodNames();
        if (methodInfoArray != null)
            for (int i = 0; i < methodInfoArray.length; i++) {
                MethodInfo methodInfo = methodInfoArray[i];
                outputMethodInfoInterface(methodInfo, itemMethods, opSignatures, false, generateMethodsForExternalEventListenerClass);

                if (methodInfo.isAddListenerMethod() || methodInfo.isRemoveListenerMethod())
                    outputMethodInfoInterface(methodInfo, itemMethods, opSignatures, true, false);
            }

        return this.testStream.toString();
    }

    // -- Helper Methods --

    private void outputMethodInfoInterface(MethodInfo methodInfo, Sequence itemMethods, Sequence opSignatures, boolean generateExternalAddRemoveListenerInterface, boolean externalListenerInterface) {
        boolean conflict = false;

        if (methodInfo.isActive()) {
            if (!methodInfo.isStatic()) {
                String methodInterface = methodInfo.generateMethodInterface(this.context, generateExternalAddRemoveListenerInterface, externalListenerInterface);
                if (itemMethods.contains(methodInfo.getJavaMethodName()))
                    conflict = true;
                else {
                    Sequence mInterfaceSig = MethodInfo.getMethodSignatureAsSequence(methodInterface);
                    for (Enumeration opsige = opSignatures.elements(); opsige.hasMoreElements(); ) {
                        if (mInterfaceSig.equals(opsige.nextElement())) {
                            conflict = true;
                            break;
                        }
                    }
                }

                if (!conflict) {
                    iprintMultiLineString(methodInfo.generateInterfaceComment());
                    iprint(methodInterface);
                    println(";");
                    iprintln("");
                }
            }
        }
    }

    private ClassOverrides collectInheritedOverrides(Hashtable overridesTable, Symbol[] classesToCollect) {

        ClassOverrides ov = new ClassOverrides();

        for (Symbol classToCollect : classesToCollect) {
            ClassOverrides ovInherited = (ClassOverrides) overridesTable.get(classToCollect);
            if (ovInherited != null)
                ov.concatenate(ovInherited);
        }
        return ov;
    }

    private String[] collectAllImports(String[] imports, ClassOverrides overrides) {
        if (overrides == null)
            return imports;
        int newImportsCount = overrides.getImportsCount();
        if (newImportsCount == 0)
            return imports;
        String[] fullImports = new String[imports.length + newImportsCount];
        System.arraycopy(imports, 0, fullImports, 0, imports.length);
        int i = imports.length;
        Enumeration e = overrides.getImports();
        while (e.hasMoreElements()) {
            Symbol importName = (Symbol) e.nextElement();
            fullImports[i++] = overrides.getImportTypeOrPackage(importName);
        }

        return fullImports;
    }

    private String generateDynamicHeader(String[] imports, String superClass, String[] interfaces, ClassOverrides overrides) {
        Symbol g2ClassName = Symbol.intern(this.className);
        generateImportsHeader(imports);
        String[] interfaceNames = generateSuperClassHeader(interfaces, javaClassName, superClass);
        interfaceNames = generateInterfacesHeader(overrides, interfaceNames);

        if (StubClassLoader.isG2ClassG2EventClass(g2ClassName) && isInterface) {
            if (interfaceNames != null && interfaceNames.length > 0) {
                print(",");
            }

            print(StubClassLoader.g2EventTagInterfaceName);
        }

        println(" {");
        println();

        return this.testStream.toString();
    }
}
