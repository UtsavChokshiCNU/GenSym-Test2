package com.gensym.jgi.download;

import com.gensym.message.Trace;
import com.gensym.util.G2ClassTranslator;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;

import java.util.Enumeration;
import java.util.Hashtable;
import java.util.Vector;

import static com.gensym.jgi.download.ClassGenerationContext.HAND_CODED_METHODS_;
import static com.gensym.jgi.download.StubGenerationContext.*;

public class StubGenerationContextHelper extends ClassGenerationContextHelper {
    private static final int DEF_TRACE_LEVEL = 5;
    private static final int PropertyGetter = 1, PropertySetter = 2, PropertyStatic = 4;
    private static final String ClassVarGetter = "getStaticAttributeValue", ClassVarSetter = "setStaticAttributeValue";
    private static final String InstVarGetter = "getAttributeValue", InstVarSetter = "setAttributeValue";
    protected String javaClassInterfaceName;
    private String[] symVarNames;

    @Override
    protected String generateConstructors() {
        javaClassName = G2ClassTranslator.createJavaClassNameFromG2ClassName(Symbol.intern(this.className)) + "Impl";
        iprintln("/* Generated constructors */");
        println();

        generateConstructors("public " + javaClassName + "() {", "super();");
        generateConstructors("public " + javaClassName + "(G2Access context, int handle, Structure attributes) {", "super (context, handle, attributes);");
        println();
        generateConstructors("public " + javaClassName + "(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {", "super (context, handle, handleVersion, wrap, attributes);");
        println();

        return this.testStream.toString();
    }

    @Override
    protected String generateFields(AttrInfo attributes, Symbol[] classInheritancePath, ClassOverrides overrides) {
        println();

        iprintln("static final long serialVersionUID = 2L;");
        Symbol[] attrNames = attributes.attrNames;
        Symbol[] origNames = attributes.origNames;
        Symbol[] defClasses = attributes.defClasses;
        boolean[] staticQ = attributes.staticP;
        boolean[] systemDefined = attributes.systemDefined;

        String symFieldModifiersAndType = "private static final Symbol ";
        symVarNames = createJavaSymbolVariableNames(systemDefined, attrNames, staticQ);
        Vector duplicates = determineDuplicateAttributeNames(origNames, defClasses, staticQ);
        for (int i = 0; i < symVarNames.length; i++) {
            if (!systemDefined[i]) {
                String g2AttributeName = getG2NameForAttribute(origNames[i], staticQ[i], defClasses[i], duplicates);
                iprintln(symFieldModifiersAndType + symVarNames[i] + " = " + javaCodeForInterningSymbol(systemDefined[i], attrNames[i], g2AttributeName) + ";");
            }
        }

        println();
        generateOverriddenFields(overrides);
        return testStream.toString();
    }

    @Override
    protected String generatePropertyAccessors(String[] jSlotTypes, String[] jSlotNames, Symbol[] slotNames, int[] generationFlags) {
        for (int i = 0; i < jSlotNames.length; i++) {
            Symbol currentSlot_ = slotNames[i];
            String currentSlot = jSlotNames[i], currentType = jSlotTypes[i];
            boolean staticField = ((generationFlags[i] & PropertyStatic) != 0);
            boolean getterExists = (generationFlags[i] & PropertyGetter) != 0;
            boolean setterExists = (generationFlags[i] & PropertySetter) != 0;
            String fieldName = G2ClassTranslator.initCap(makeFieldNameForSlot(currentSlot, staticField));
            String slotVarName = ensureLegalJavaVariableName(currentSlot);
            if (fieldName.equals("Text")) {
                getterExists = setterExists = true;
                currentType = "java.lang.String";
            }

            if (setterExists) {
                String setterInterface = ("public void set" + fieldName +
                        "(" + currentType + " " + slotVarName + ") throws G2AccessException {");
                Sequence intfSig = MethodInfo.getMethodSignatureAsSequence(setterInterface);
                if (!methodAlreadyDefined(intfSig)) {
                    iprintln("/**");
                    iprintln(" * Generated Property Setter for attribute -- " + currentSlot_);
                    iprintln(" * @param " + slotVarName + " new value to conclude for " + currentSlot_);
                    iprintln(" * @exception G2AccessException if there are any communication problems");
                    iprintln(" *              or the value does not match with the type specification");
                    iprintln(" */");

                    iprintln(setterInterface);
                    recordOpInterfaceSignature(setterInterface);
                    increaseIndent(2);
                    generateSetBody(currentType, slotVarName, symVarNames[i], staticField);
                    decreaseIndent(2);
                    iprintln("}");
                    println();
                }
            }

            if (getterExists) {
                String getterInterface = ("public " + currentType + " get" +
                        fieldName + "() throws G2AccessException {");
                Sequence intfSig = MethodInfo.getMethodSignatureAsSequence(getterInterface);
                if (!methodAlreadyDefined(intfSig)) {
                    iprintln("/**");
                    iprintln(" * Generated Property Getter for attribute -- " + currentSlot_);
                    iprint(" * @return the value of the " + currentSlot_ + " attribute of this ");
                    println(staticField ? "class" : "item");
                    iprintln(" * @exception G2AccessException if there are any communication problems");
                    iprintln(" */");
                    iprintln(getterInterface);
                    recordOpInterfaceSignature(getterInterface);
                    increaseIndent(2);
                    generateGetBody(currentType, symVarNames[i], staticField);
                    decreaseIndent(2);
                    iprintln("}");
                    println();
                }
            }
        }

        return testStream.toString();
    }

    // -- Helper Methods --

    private String javaCodeForInterningSymbol(boolean isSystemDefined, Symbol attrName, String sym) {
        if (isSystemDefined) {
            return "SystemAttributeSymbols." + ClassGenerationContext.createJavaSymbolVariableName(attrName);
        } else {
            return "Symbol.intern (\"" + sym + "\")";
        }
    }

    private String[] createJavaSymbolVariableNames(
            boolean[] systemDefined,
            Symbol[] attrNames,
            boolean[] staticQ) {
        int numAttributes = attrNames.length;
        String[] javaSymbolVarNames = new String[numAttributes];
        for (int i = 0; i < numAttributes; i++) {
            if (systemDefined[i]) {
                javaSymbolVarNames[i] = "SystemAttributeSymbols." + ClassGenerationContext.createJavaSymbolVariableName(attrNames[i]);
            } else {
                javaSymbolVarNames[i] = ClassGenerationContext.createJavaSymbolVariableName(attrNames[i]);
                if (staticQ[i]) {
                    javaSymbolVarNames[i] += "FOR_CLASS_";
                }
            }
        }

        return javaSymbolVarNames;
    }

    protected String generateConstructors(String signature, String body) {
        iprintln(signature);
        increaseIndent(2);
        iprintln(body);
        decreaseIndent(2);
        iprintln("}");
        println();

        return this.testStream.toString();
    }

    private String makeFieldNameForSlot(final String slotName, final boolean staticQ) {
        if (staticQ) {
            return slotName + "ForClass";
        }

        return slotName;
    }

    private String ensureLegalJavaVariableName(String origName) {
        for (String word : JavaReservedWords) {
            if (origName.equals(word)) {
                return origName + "$";
            }
        }
        return origName;
    }

    private void generateOverriddenFields(ClassOverrides overrides) {
        Enumeration e = overrides.getFields();
        while (e.hasMoreElements()) {
            Symbol fieldName = (Symbol) e.nextElement();
            iprintln("/* Overriden Field */");
            iprint(overrides.getFieldDeclaration(fieldName));
            String initValue = overrides.getFieldInitialValue(fieldName);
            if (initValue != null && !initValue.equals("")) {
                print(" = " + initValue);
            }
            println(";");
        }
    }

    private void generateGetBody(String currentType,
                                 String symVarName,
                                 boolean staticField) {
        String getterFn = (staticField ? ClassVarGetter : InstVarGetter);
        String extraArgs = "";
        iprintln("java.lang.Object retnValue = " + getterFn + " (" + symVarName + extraArgs + ");");
        iprintln("return " + StubGenerationContext.codeToGetPrimitiveValueOrCastReturnObject("retnValue", currentType) + ";");
    }

    @Override
    protected String generateMethods(final MethodInfo methodInfoArray[], final Hashtable overridesTable, final boolean onlyEventMethods) {
        if (isG2EventObjectClass) {
            iprintln("/* " + StubClassLoader.g2EventTagInterfaceName + " support */");
            iprintln("public Class " + StubClassLoader.getExternalEventClassMethodName + "() {");
            increaseIndent(2);
            iprintln("return " + packageName + "." + StubClassLoader.getExternalG2EventClassName(javaClassInterfaceName) + ".class;");
            decreaseIndent(2);
            iprintln("}");
            println();
        }

        MethodInfo[] methodInfos = methodInfoArray;
        if (methodInfos == null) {
            methodInfos = new MethodInfo[0];
        }

        Hashtable decTable = new Hashtable(201);
        Trace.send(DEF_TRACE_LEVEL, traceKey, i18nTrace, "genStubMethod", methodInfos.length);

        boolean titleSent = false;
        for (MethodInfo mi : methodInfos) {

            if (mi.isActive()) {
                if (!titleSent) {
                    iprintln("// Method Name Constants");
                    titleSent = true;
                }
                String decName = (mi.generateRPCDeclarationName()).intern();
                if (decTable.get(decName) == null) {
                    iprintln(mi.generateRPCDeclarartion());
                    decTable.put(decName, this);
                }
            }
        }

        iprintln(MethodInfo.generateImplementationDeclarations());
        iprintln("");

        ClassOverrides overrides = (ClassOverrides) overridesTable.get(this.className);
        Sequence ovrInterfaceSig;
        String ovrInterface;

        if (overrides != null) {
            Enumeration e = overrides.getMethods();
            while (e.hasMoreElements()) {
                Symbol methodName = (Symbol) e.nextElement();
                ovrInterface = overrides.getMethodInterface(methodName);
                ovrInterfaceSig = MethodInfo.getMethodSignatureAsSequence(ovrInterface);
                opSignatures.addElement(ovrInterfaceSig);

                iprintln("/* Overriden method - " + methodName + " */");
                iprintln(ovrInterface);
                println(" {");
                increaseIndent(2);
                iprintMultiLineString(overrides.getMethodImplementation(methodName));
                decreaseIndent(2);
                iprintln("}");
                println();
            }
        }

        boolean conflict = false;
        Sequence inhOpSignatures = new Sequence(50);

        for (Enumeration ovrClassEnum = overridesTable.keys(); ovrClassEnum.hasMoreElements(); ) {
            Symbol inhClass = (Symbol) ovrClassEnum.nextElement();
            overrides = (ClassOverrides) overridesTable.get(inhClass);

            if (!HAND_CODED_METHODS_.equals(inhClass) && !inhClass.equals(this.className) && overrides != null) {
                Enumeration e = overrides.getMethods();
                while (e.hasMoreElements()) {
                    Symbol methodName = (Symbol) e.nextElement();
                    Trace.send(DEF_TRACE_LEVEL, traceKey, i18nTrace, "genMeth", methodName);
                    ovrInterface = overrides.getMethodInterface(methodName);
                    conflict = false;

                    ovrInterfaceSig = MethodInfo.getMethodSignatureAsSequence(ovrInterface);
                    for (Enumeration opsige = opSignatures.elements(); opsige.hasMoreElements(); ) {
                        if (ovrInterfaceSig.equals(opsige.nextElement())) {
                            conflict = true;
                            break;
                        }
                    }

                    if (!conflict) {
                        iprintln("/* Overriden method - " + methodName + " */");
                        iprintln(ovrInterface);
                        println(" {");
                        increaseIndent(2);
                        iprintMultiLineString(overrides.getMethodImplementation(methodName));
                        decreaseIndent(2);
                        iprintln("}");
                        println();
                        opSignatures.addElement(ovrInterfaceSig);
                    }
                }
            }
        }

        opSignatures.concatenate(inhOpSignatures);
        overrides = (ClassOverrides) overridesTable.get(HAND_CODED_METHODS_);
        Sequence hcInfoSeq = new Sequence(50);

        if (overrides != null) {
            Enumeration e = overrides.getMethods();
            while (e.hasMoreElements()) {
                Symbol methodName = (Symbol) e.nextElement();
                ovrInterface = overrides.getMethodInterface(methodName);
                ovrInterfaceSig = MethodInfo.getMethodSignatureAsSequence(ovrInterface);

                Object[] info = new Object[]{ovrInterfaceSig, ovrInterface, overrides.getMethodImplementation(methodName)};
                hcInfoSeq.addElement(info);
            }
        }

        if (isG2ProxyObjectClass) {
            return this.testStream.toString();
        }

        Sequence hcInfoSeqCopy = (Sequence) hcInfoSeq.clone();
        Sequence itemMethods = this.context.getItemMethodNames();
        iprintln("");
        for (int i = 0; i < methodInfos.length; i++) {
            if (i == 0) {
                iprintln("//Generated Methods \n");
            }

            MethodInfo mi = methodInfos[i];
            outputMethodInfoImplementation(mi, itemMethods, opSignatures, hcInfoSeq, hcInfoSeqCopy, false);
            if (mi.isAddListenerMethod() || mi.isRemoveListenerMethod())
                outputMethodInfoImplementation(mi, itemMethods, opSignatures, hcInfoSeq, hcInfoSeqCopy, true);
        }

        int i = 0;
        Enumeration e = hcInfoSeq.elements();
        while (e.hasMoreElements()) {
            if (i == 0)
                iprintln("// G2 Exported Overrides");

            Object[] info = (Object[]) e.nextElement();
            Sequence eSigSeq = (Sequence) info[SIG_POS];
            for (Enumeration opsige = opSignatures.elements(); opsige.hasMoreElements(); ) {
                if (eSigSeq.equals(opsige.nextElement())) {
                    conflict = true;
                    break;
                }
            }
            if (!conflict) {
                Trace.send(DEF_TRACE_LEVEL, traceKey, i18nTrace, "genMeth", eSigSeq.toString());
                iprintln((String) info[INT_POS]);
                iprintln("{");
                increaseIndent(2);
                iprintMultiLineString((String) info[IMP_POS]);
                decreaseIndent(2);
                iprintln("}");
                iprintln("");
                i++;
            }
        }

        return this.testStream.toString();
    }

    @Override
    protected String generateEventMethods(ClassOverrides overrides) {
        Enumeration e = overrides.getEvents();
        while (e.hasMoreElements()) {
            Symbol eventName = (Symbol) e.nextElement();
            String addListenerInterface = overrides.getAddListenerInterface(eventName);
            String addListenerImplementation = overrides.getAddListenerImplementation(eventName);
            String removeListenerInterface = overrides.getRemoveListenerInterface(eventName);
            String removeListenerImplementation = overrides.getRemoveListenerImplementation(eventName);
            iprintln("/* Overriden  - " + eventName + " Event Listener - Adder1 */");
            if (addListenerInterface != null) {
                iprint(addListenerInterface);
                recordOpInterfaceSignature(addListenerInterface);
                println(" {");
                increaseIndent(2);
                iprintMultiLineString(addListenerImplementation);
                decreaseIndent(2);
                iprintln("}");
            }
            println();
            iprintln("/* Overriden  - " + eventName + " Event Listener - Remover1 */");
            if (removeListenerInterface != null) {
                iprint(removeListenerInterface);
                recordOpInterfaceSignature(removeListenerInterface);
                iprintln(" {");
                increaseIndent(2);
                iprintMultiLineString(removeListenerImplementation);
                decreaseIndent(2);
                iprintln("}");
            }
            println();
        }

        return this.testStream.toString();
    }

    @Override
    protected String writeOverriddenPropertyAccessors(ClassOverrides overrides) {
        Enumeration e = overrides.getProperties();
        while (e.hasMoreElements()) {
            Symbol propName = (Symbol) e.nextElement();
            String getterSign = overrides.getGetterInterface(propName);
            String setterSign = overrides.getSetterInterface(propName);
            String getterText = overrides.getGetterImplementation(propName);
            String setterText = overrides.getSetterImplementation(propName);
            iprintln("/* Overriden Property - " + propName + " */");
            if (getterSign != null) {
                String comments = overrides.getGetterComments(propName);
                if (comments == null)
                    comments = "/**  Property Getter for " + propName + " */";
                iprintln(comments);
                iprint(getterSign);
                println(" {");
                increaseIndent(2);
                iprintMultiLineString(getterText);
                decreaseIndent(2);
                iprintln("}");
                recordOpInterfaceSignature(getterSign);
            }
            println();
            if (setterSign != null) {
                String comments = overrides.getSetterComments(propName);
                if (comments == null)
                    comments = "/**  Property Setter for " + propName + " */";
                iprintln(comments);
                iprint(setterSign);
                iprintln(" {");
                increaseIndent(2);
                iprintMultiLineString(setterText);
                decreaseIndent(2);
                iprintln("}");
                recordOpInterfaceSignature(setterSign);
            }
            println();
        }

        return this.testStream.toString();
    }

    // -- Helper Methods --

    private Vector determineDuplicateAttributeNames(
            Symbol[] origNames,
            Symbol[] defClasses,
            boolean[] staticQ) {
        Vector duplicates = new Vector();
        for (int i = 0; i < origNames.length; i++) {
            Symbol attrName = origNames[i];
            boolean isStatic = staticQ[i];
            StubGenerationContext.AttrClassPair duplAttrInfo = null;

            if (mostSpecificClassDefiningDuplicateAttribute(attrName, isStatic, duplicates) == null) {
                for (int j = i + 1; j < origNames.length; j++) {
                    if (attrName.equals(origNames[j]) && (isStatic == staticQ[j])) {
                        duplAttrInfo = new StubGenerationContext.AttrClassPair(attrName, defClasses[i], isStatic);
                    }
                }
                if (duplAttrInfo != null) {
                    duplicates.addElement(duplAttrInfo);
                }
            }
        }

        return duplicates;
    }

    private static String getG2NameForAttribute(
            Symbol origName,
            boolean isStatic,
            Symbol definingClass,
            Vector duplicateNames) {
        Symbol classOfDuplAttr = mostSpecificClassDefiningDuplicateAttribute(origName, isStatic, duplicateNames);
        if (classOfDuplAttr == null || definingClass.equals(classOfDuplAttr)) {
            return origName.getPrintValue();
        } else {
            return definingClass.getPrintValue() + "::" + origName.getPrintValue();
        }
    }

    private static Symbol mostSpecificClassDefiningDuplicateAttribute(
            Symbol attrName,
            boolean isStatic,
            Vector duplicates) {
        Enumeration e = duplicates.elements();
        while (e.hasMoreElements()) {
            StubGenerationContext.AttrClassPair duplAttrInfo = (StubGenerationContext.AttrClassPair) e.nextElement();
            if (duplAttrInfo.attributeName.equals(attrName) && (duplAttrInfo.isStatic == isStatic)) {
                return duplAttrInfo.definingClass;
            }
        }

        return null;
    }

    private void generateSetBody(String currentType,
                                 String slotVarName,
                                 String symVarName,
                                 boolean staticField) {
        String setterFn = (staticField ? ClassVarSetter : InstVarSetter);
        String extraArgs = "";
        iprintln(setterFn + " (" + symVarName + ", " + StubGenerationContext.codeToMakeObject(slotVarName, currentType) + extraArgs + ");");
    }

    private void outputMethodInfoImplementation(MethodInfo mi,
                                                Sequence itemMethods,
                                                Sequence opSignatures,
                                                Sequence hcInfoSeq,
                                                Sequence hcInfoSeqCopy,
                                                boolean generateExternalAddRemoveListenerInterface) {
        boolean conflict;

        if (mi.isActive()) {

            String intf = mi.generateMethodInterface(this.context, generateExternalAddRemoveListenerInterface, false);
            Sequence mInterfaceSig = MethodInfo.getMethodSignatureAsSequence(intf);

            conflict = false;

            if (itemMethods.contains(mi.getJavaMethodName()))
                conflict = true;
            else {
                for (Enumeration opsige = opSignatures.elements(); opsige.hasMoreElements(); ) {
                    if (mInterfaceSig.equals(opsige.nextElement())) {
                        conflict = true;
                        break;
                    }
                }
            }
            if (!conflict) {
                Trace.send(DEF_TRACE_LEVEL, traceKey, i18nTrace, "genMeth", mi.G2MethodName.toString());
                iprintMultiLineString(mi.generateInterfaceComment());
                iprintln(intf);
                boolean gotImplementation = false;
                for (Enumeration e = hcInfoSeqCopy.elements(); e.hasMoreElements(); ) {
                    Object[] info = (Object[]) e.nextElement();
                    Sequence exSig = (Sequence) info[SIG_POS];
                    if (mInterfaceSig.equals(exSig)) {
                        mi.generateMethodImplementation((StubGenerationContext) this.context, (String) info[IMP_POS], generateExternalAddRemoveListenerInterface);
                        gotImplementation = true;
                        hcInfoSeq.removeElement(info);
                        break;
                    }
                }

                if (!gotImplementation) {
                    mi.generateMethodImplementation((StubGenerationContext) this.context, "", generateExternalAddRemoveListenerInterface);
                }
                iprintln("");
            }
        }
    }
}