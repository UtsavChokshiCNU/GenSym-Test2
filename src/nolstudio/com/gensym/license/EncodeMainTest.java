package com.gensym.license;

import static org.hamcrest.CoreMatchers.is;
import static org.hamcrest.MatcherAssert.assertThat;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Arrays;
import java.util.List;

import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.TemporaryFolder;


public class EncodeMainTest {

    @Rule
    public TemporaryFolder temporaryFolder=new TemporaryFolder();

    /**
     * Recursion And Deletion Are Set To True so it traverse through folders then encodes class files in unreadable format and removes .class files
     */
    @Test
    public void test_Main_classFileRecursionAndDeletionAreSetToTrue_TraverseInNestedFolderCreatesClsFileAndRemovesClassFile() throws IOException {
        //Arrange
        String fileName="temp";
        File file = temporaryFolder.newFile(fileName+".class");
        File nestedFolder = temporaryFolder.newFolder();
        File nestedFile = new File(Paths.get(nestedFolder.getPath(), fileName+".class").toString());
        nestedFile.createNewFile();
        List<String> lines = Arrays.asList("Class content 1");
        Files.write(Paths.get(file.getPath()), lines);
        String[] args= {"-d","-r",file.getParent()};

        //Act
        EncodeMain.main(args);

        //Assert
        assertThat(file.exists(), is(false));
        assertThat(nestedFile.exists(), is(false));
        assertThat(new File(file.getParent(),fileName+".cls").exists(), is(true));
        assertThat(new File(nestedFile.getParent(),fileName+".cls").exists(), is(true));
    }

    /**
     * Recursion And Deletion Are Set To false so it doesn't traverse through folders but encodes class files in unreadable format for root folder and doesn't removes .class files
     */
    @Test
    public void test_Main_classFileRecursionAndDeletionAreSetToFalse_NeitherTraverseInNestedFolderNorRemovesClassFile() throws IOException {
        //Arrange
        String fileName="temp";
        File file = temporaryFolder.newFile(fileName+".class");
        File nestedFolder = temporaryFolder.newFolder();
        File nestedFile = new File(Paths.get(nestedFolder.getPath(), fileName+".class").toString());
        nestedFile.createNewFile();
        List<String> lines = Arrays.asList("Class content 1");
        Files.write(Paths.get(file.getPath()), lines);
        String[] args= {file.getParent()};

        //Act
        EncodeMain.main(args);

        //Assert
        assertThat(file.exists(), is(true));
        assertThat(nestedFile.exists(), is(true));
        assertThat(new File(file.getParent(),fileName+".cls").exists(), is(true));
        assertThat(new File(nestedFile.getParent(),fileName+".cls").exists(), is(false));
    }
}
