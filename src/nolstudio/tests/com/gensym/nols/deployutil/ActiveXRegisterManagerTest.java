package com.gensym.nols.deployutil;

import static org.hamcrest.MatcherAssert.assertThat;
import static org.mockito.Mockito.mock;
import static org.mockito.Mockito.verify;
import static org.mockito.Mockito.when;
import static org.powermock.api.mockito.PowerMockito.mockStatic;
import static org.powermock.api.mockito.PowerMockito.whenNew;

import java.awt.*;
import java.io.File;
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Arrays;
import java.util.List;
import java.util.UUID;

import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.TemporaryFolder;
import org.junit.runner.RunWith;
import org.powermock.core.classloader.annotations.PrepareForTest;
import org.powermock.modules.junit4.PowerMockRunner;

@RunWith(PowerMockRunner.class)
@PrepareForTest(ActiveXRegisterManager.class)
public class ActiveXRegisterManagerTest {

    @Rule
    public TemporaryFolder temporaryFolder=new TemporaryFolder();

    /**
     * controlDir where controls are located modifies .reg File And Execute
     *
     */
    @Test
    public void test_registerControls_controlDir_modifiesFileAndExecute() throws Exception {
        //Arrange
        String activeX= "ActiveX";
        String bin= "bin";
        File folder1 = temporaryFolder.newFolder(activeX);
        File folder2 = temporaryFolder.newFolder(bin);
        File reg1=new File(folder1.getPath(), UUID.randomUUID().toString()+".reg");
        List<String> data= Arrays.asList("The first line", "beans.ocx","\"OnlineProcessor","\"ActiveX","NOLProcessor.tlb");
        Files.write(Paths.get(reg1.getPath()), data, Charset.forName("UTF-8"));
        reg1.createNewFile();
        Dialog dialog=mock(Dialog.class);
        Rectangle rectangle=new Rectangle(20,30);
        when(dialog.getBounds()).thenReturn(rectangle);
        when(dialog.getToolkit ()).thenReturn(mock(Toolkit.class));
        whenNew(Dialog.class).withAnyArguments().thenReturn(dialog);
        whenNew(Rectangle.class).withAnyArguments().thenReturn(rectangle);
        String tempFolderPath=temporaryFolder.getRoot().getPath().replace("\\","\\\\");
        List<String> expectedResult=Arrays.asList("The first line",
                tempFolderPath+"\\\\"+bin+"\\\\beans.ocx",
                "\""+tempFolderPath+"\\\\"+activeX+"\\\\OnlineProcessor",
                "\""+tempFolderPath+"\\\\"+activeX,
                tempFolderPath+"\\\\"+activeX+"\\\\NOLProcessor.tlb");
        mockStatic(System.class);
        mockStatic(Runtime.class);
        Runtime runtime=mock(Runtime.class);
        when(Runtime.getRuntime()).thenReturn(runtime);

        //Act
        ActiveXRegisterManager.registerControls(folder1.getParent(), folder2.getParent());

        //Assert
        List<String> fileContent=Files.readAllLines(Paths.get(reg1.getPath()));
        assertThat(fileContent,org.hamcrest.CoreMatchers.is(expectedResult));
        verify(runtime).exec("regedit /s "+reg1.getPath());
    }
}
