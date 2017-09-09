package com.gensym.jgi.download;

import com.gensym.classes.ClassDefinition;
import com.gensym.classes.ClassDefinitionImpl;
import com.gensym.classes.ModuleInformation;
import com.gensym.classes.ModuleInformationImpl;
import com.gensym.jgi.*;
import com.gensym.message.Trace;
import com.gensym.util.NoSuchAttributeException;
import com.gensym.util.Sequence;
import com.gensym.util.Structure;
import com.gensym.util.Symbol;
import org.junit.After;
import org.junit.Before;
import org.mockito.MockitoAnnotations;
import org.mockito.Spy;

import java.io.ByteArrayOutputStream;
import java.io.PrintStream;

import static com.gensym.helpers.ObjectsFactory.anyString;
import static com.gensym.util.symbol.AttributeExportSymbols.ATTRIBUTE_NAME_;
import static com.gensym.util.symbol.AttributeExportSymbols.DEFINING_CLASS_;
import static com.gensym.util.symbol.MethodExportSymbols.ARGUMENT_TYPES_;
import static com.gensym.util.symbol.MethodExportSymbols.METHOD_NAME_;
import static com.gensym.util.symbol.MethodExportSymbols.RESULT_TYPES_;
import static org.powermock.api.mockito.PowerMockito.mock;

public class StubClassLoaderTestHelper {
    private static final Symbol G2_GET_SHORT_CLASS_INFO_ = Symbol.intern("G2-GET-SHORT-CLASS-INFO");
    private static final Symbol MODULE_INFORMATION_ = com.gensym.util.symbol.G2ClassSymbols.MODULE_INFORMATION_;
    private static final Symbol JAVA_PACKAGE_FOR_EXPORT_ = Symbol.intern("JAVA-PACKAGE-FOR-EXPORT");
    private static final Symbol ANNOTATION_NAME_ = Symbol.intern("ANNOTATION-NAME");
    private static final Symbol ANNOTATION_VALUE_ = Symbol.intern("ANNOTATION-VALUE");
    private static final Symbol G2_GET_CLASS_INFO_ = Symbol.intern("G2-GET-CLASS-INFO");
    private static final Symbol CLASS_INHERITANCE_PATH_ = Symbol.intern("CLASS-INHERITANCE-PATH");
    private static final Symbol CLASS_NAME_ = Symbol.intern("CLASS-NAME");

    protected static final boolean[] booleanTestCases = new boolean[] { false, true };
    protected static final int TestSamplesCount = 3;
    protected static final Symbol CLASS_ATTRIBUTES_ = Symbol.intern("CLASS-ATTRIBUTES");
    protected static final Symbol INSTANCE_ATTRIBUTES_ = Symbol.intern("INSTANCE-ATTRIBUTES");
    protected static final Symbol INSTANCE_METHODS_ = Symbol.intern("INSTANCE-METHODS");
    protected static final Symbol G2_EVENT_LISTENER_ = Symbol.intern("G2-EVENT-LISTENER");
    protected static final String DUPLICATE_ATTRIBUTE_NAME = "duplicateAttributeName";

    @Spy
    protected G2AccessStub context = new G2AccessStub();

    @Spy
    private G2ConnectionInfo g2ConnectionInfo = new G2ConnectionInfo();

    private Symbol symbolG2ConnectionInterface;
    private Sequence classInheritancePathAttributeValue = new Sequence();
    private ClassDefinition classDefnition;
    private ModuleInformation moduleInformation;

    protected Sequence instanceMethods;
    protected Sequence staticMethods;
    protected Symbol className;
    protected Symbol[] classInheritancePath;
    protected Symbol[] collectedClasses;
    protected boolean isInterface;
    protected boolean isPseudoClass;
    protected StubClassLoader stubClassLoader;
    protected Symbol symbol;
    protected Symbol symbolInterface;
    protected boolean traceOn = false;
    protected final ByteArrayOutputStream outContent = new ByteArrayOutputStream();
    protected final ByteArrayOutputStream errContent = new ByteArrayOutputStream();
    private boolean debug = false;

    @Before
    public void init() throws G2AccessException {
        this.traceOn = Trace.getTraceOn();
        Trace.setTraceOn(true);

        setupStreams();
        initializeAllVariables();
        setSystemProperties();
        createSut();
        this.debug = this.stubClassLoader.debug;
        this.stubClassLoader.debug = true;
    }

    @After
    public void teardown() {
        Trace.setTraceOn(traceOn);
        clearSystemProperties();
        this.stubClassLoader.debug = this.debug;
    }

    protected void arrangeForCollectInheritedAttributes() {
        this.collectedClasses = new Symbol[] {
                this.className,
                Symbol.intern("DefaultStubFactoryTestHelper"),
                Symbol.intern("OverrideAnalyzerTestHelper")
        };

        for (Symbol collectedClass : this.collectedClasses) {
            this.stubClassLoader.classInfoTable.put(collectedClass, createClassInfo());
        }
    }

    protected void arrangeForGenerateG2MethodStubInfo() {
        this.instanceMethods = new Sequence();
        this.staticMethods = new Sequence();
        this.classInheritancePath = new Symbol[] { this.className };
        this.isInterface = false;
        this.isPseudoClass = false;
    }

    protected void clearSystemProperties() {
        System.clearProperty("com.gensym.class.user.package");
        System.clearProperty("com.gensym.class.user.repository");
        System.clearProperty("com.gensym.class.g2.package");
    }

    protected Structure createClassInfo() {
        Structure classInfo = new Structure();
        Sequence classInstanceMethods = createClassInstanceMethods();
        classInfo.setAttributeValue(INSTANCE_METHODS_, classInstanceMethods);
        addClassAttributes(classInfo, CLASS_ATTRIBUTES_);
        addClassAttributes(classInfo, INSTANCE_ATTRIBUTES_);
        return classInfo;
    }

    protected Sequence createClassInstanceMethods() {
        Sequence classInstanceMethods = new Sequence();

        for (int idx = 0; idx < TestSamplesCount; idx++) {
            Structure methodsStructure = new Structure();
            methodsStructure.setAttributeValue(METHOD_NAME_, Symbol.intern(anyString()));
            methodsStructure.setAttributeValue(RESULT_TYPES_, new Sequence());

            addClassAttributes(methodsStructure, ARGUMENT_TYPES_);

            classInstanceMethods.add(methodsStructure);
        }

        return classInstanceMethods;
    }

    protected void createSut() {
        this.stubClassLoader = new StubClassLoader(this.context);
        this.stubClassLoader.setTraceOn();
    }

    protected Sequence expectedCollectedInheritedAttributes(boolean staticAttributes) throws NoSuchAttributeException {
        Sequence attributes = new Sequence();

        for (Symbol collectedClass : this.collectedClasses) {
            Structure classInfo = (Structure) this.stubClassLoader.classInfoTable.get(collectedClass);
            Sequence classAttributes = (Sequence) classInfo.getAttributeValue(staticAttributes ? CLASS_ATTRIBUTES_ : INSTANCE_ATTRIBUTES_);

            for (Object elem : classAttributes) {
                Structure classAttribute = (Structure) elem;

                Symbol attributeName = (Symbol) classAttribute.getAttributeValue(ATTRIBUTE_NAME_);
                if (attributes.contains(attributeName) == false) {
                    attributes.add(attributeName);
                }
            }
        }

        return attributes;
    }

    protected void initializeAllVariables() throws G2AccessException {
        MockitoAnnotations.initMocks(this);
        symbol = Symbol.intern(Designation.class.getName());
        symbolInterface = Symbol.intern(G2Access.class.getName());
        symbolG2ConnectionInterface = Symbol.intern(G2Connection.class.getName());
        g2ConnectionInfo.setDefaultBrokerURL("http://www.google.com");
        g2ConnectionInfo.setDefaultConnectionClassName(G2Access.class.getName());
        g2ConnectionInfo.setDefaultHostName("http://www.google.com");
        Sequence moduleAnnotations = new Sequence();
        moduleInformation = new ModuleInformationImpl();
        moduleInformation.setTopLevelModule(symbolInterface);
        moduleInformation.setModuleAnnotations(moduleAnnotations);
        classDefnition = new ClassDefinitionImpl();
        classInheritancePathAttributeValue = new Sequence();
        classInheritancePathAttributeValue.add(symbolInterface);
        Sequence k = new Sequence();
        Sequence r = new Sequence();
        k.add(symbolG2ConnectionInterface);
        k.add(symbolInterface);
        r.add(k);
        r.add(classDefnition);
        r.add(symbolInterface);

        context.canCallRPC(true);

        Sequence callRpcResponse = new Sequence();
        callRpcResponse.add(classInheritancePathAttributeValue);
        callRpcResponse.add(classDefnition);
        callRpcResponse.add(symbolInterface);
        context.setRpcCall(G2_GET_SHORT_CLASS_INFO_, callRpcResponse);

        Sequence moduleInformationInstances = new Sequence();
        moduleInformationInstances.add(moduleInformation);
        context.setStrictInstancesOfClass(MODULE_INFORMATION_, moduleInformationInstances);

        Structure classInfo = createRcpCallClassInfo();
        context.setRpcCall(G2_GET_CLASS_INFO_, classInfo);

        moduleAnnotations.add(classInfo);

        this.className = Symbol.intern("StubClassLoaderTestHelper");
        this.collectedClasses = new Symbol[] { this.className };
    }

    protected void setSystemProperties() {
        System.setProperty("com.gensym.class.user.package", "com.gensym.jgi.downloads");
        System.setProperty("com.gensym.class.user.repository", "com\\gensym\\jgi\\downloads");
        System.setProperty("com.gensym.class.g2.package", "com.gensym.jgi.downloads");
    }

    private void addClassAttributes(Structure classInfo, Symbol attribute) {
        Sequence value = new Sequence();
        value.add(createAttribute());
        value.add(createAttribute());
        value.add(createAttribute());
        value.add(createAttribute(DUPLICATE_ATTRIBUTE_NAME));
        classInfo.setAttributeValue(attribute, value);
    }

    private Structure createAttribute() {
        return createAttribute(anyString());
    }

    private Structure createAttribute(String attributeName) {
        Structure attribute = new Structure();
        attribute.setAttributeValue(ATTRIBUTE_NAME_, Symbol.intern(attributeName));
        attribute.setAttributeValue(DEFINING_CLASS_, Symbol.intern(attributeName));
        return attribute;
    }

    private Structure createRcpCallClassInfo() {
        Structure classInfo = new Structure();
        classInfo.setAttributeValue(ANNOTATION_NAME_, JAVA_PACKAGE_FOR_EXPORT_);
        classInfo.setAttributeValue(ANNOTATION_VALUE_, "com.gensym.jgi.rmi");

        addClassAttributes(classInfo, CLASS_ATTRIBUTES_);
        addClassAttributes(classInfo, INSTANCE_ATTRIBUTES_);

        classInfo.setAttributeValue(CLASS_INHERITANCE_PATH_, classInheritancePathAttributeValue);
        classInfo.setAttributeValue(CLASS_NAME_, symbolG2ConnectionInterface);
        return classInfo;
    }

    private void setupStreams() {
        System.setOut(new PrintStream(outContent));
        System.setErr(new PrintStream(errContent));
    }

    protected ClassNameMapper userClassNameMapper = new ClassNameMapper() {
        @Override
        public String javaClassNameFromG2ClassName(Symbol g2ClassName_) {
            return null;
        }

        @Override
        public String getVersionForClass(Symbol g2ClassName_) {
            return "5.1 Rev. 1";
        }
    };
}
