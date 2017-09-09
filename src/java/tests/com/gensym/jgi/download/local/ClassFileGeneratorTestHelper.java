package com.gensym.jgi.download.local;

import com.gensym.classtools.*;
import com.gensym.jgi.G2AccessException;
import com.gensym.util.Sequence;
import org.junit.Rule;
import org.junit.rules.TemporaryFolder;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.nio.charset.Charset;

import static com.gensym.classtools.RuntimeConstants.ACC_PUBLIC;
import static com.gensym.helpers.ObjectsFactory.anyBoolean;
import static com.gensym.helpers.ObjectsFactory.anyString;
import static org.junit.Assert.assertTrue;
import static org.powermock.api.mockito.PowerMockito.mock;

public class ClassFileGeneratorTestHelper {
    protected static final String VOID_DESCRIPTOR = "V";

    private InterfaceOrClassAccess classAccess;
    private boolean createZeroArgConstructor;

    protected Access access;
    protected Block block;
    protected ClassFileGenerator sut;
    protected ClassRef[] exceptions;
    protected ByteArrayOutputStream outputStream;
    protected String className;
    protected String superClassName;
    protected String methodName;
    protected String descriptor;
    protected String[] parameterNames;

    @Rule
    public TemporaryFolder temporaryFolder = new TemporaryFolder();

    protected void arrangeAddMethodParameters() throws ClassException {
        this.methodName = anyString();
        this.descriptor = VOID_DESCRIPTOR;
        this.parameterNames = null;
        this.access = new Access(ACC_PUBLIC);
        this.block = new Block();
        this.exceptions = new ClassRef[] {
                new ClassRef(IOException.class.getName()),
                new ClassRef(G2AccessException.class.getName())
        };
    }

    protected void assertOutputStreamContains(String content) {
        assertTrue(new String(this.outputStream.toByteArray(), Charset.defaultCharset()).contains(content));
    }

    protected Sequence createSequence(String type, int flags, String expr) {
        Sequence seq = new Sequence();
        seq.add(type);
        seq.add(flags);
        seq.add(expr);
        return seq;
    }

    protected void createSut() throws ClassException {
        this.sut = new ClassFileGenerator(this.classAccess, this.className, this.superClassName, this.createZeroArgConstructor, this.outputStream);
    }

    protected void initializeVariables() throws IOException {
        this.classAccess = mock(InterfaceOrClassAccess.class);
        this.className = ClassFileGeneratorTestHelperA.class.getName();
        this.superClassName = ClassFileGeneratorTestHelperB.class.getName();
        this.createZeroArgConstructor = anyBoolean();
        this.outputStream = new ByteArrayOutputStream();
    }

    protected void setSystemProperties() throws IOException {
        System.setProperty("com.gensym.class.user.repository", "");
        System.setProperty("file.separator", "\\");
    }

    public class ClassFileGeneratorTestHelperA extends ClassFileGeneratorTestHelperB {
        @Override
        protected void doJobA(int paramA, String paramB) {
            // Overridden in helper A
        }
    }

    public class ClassFileGeneratorTestHelperB implements IClassFileGeneratorTestB {
        protected void doJobA(int paramA, String paramB) {

        }
    }

    public interface IClassFileGeneratorTestB {

    }

    public class ExpressionStub extends Expression {

        public void setExpressionType(Type type) {
            super.setExpressionType(type);
        }
    }
}
